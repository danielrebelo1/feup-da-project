#include "../include/Network.h"

using namespace std;

Station* Network::findStation(const string &stationName) const {
    for (Station* station : stations)
        if (station->getName() == stationName)
            return station;
    return nullptr;
}

void Network::addStation(Station *station) {
    if (findStation(station->getName()) == nullptr)
        stations.push_back(station);
}

void Network::addTrack(const string &source, const string &dest, int capacity, const string &service) const {
    Station* s1 = findStation(source);
    Station* s2 = findStation(dest);
    if (s1 == nullptr || s2 == nullptr) return;
    Track* t1 = s1->addTrack(s2, capacity, service);
    Track* t2 = s2->addTrack(s1, capacity, service);
}

void Network::removeTrack(const std::string &src, const std::string &dest) {
    auto srcItr = stations.begin(), destItr = stations.begin();
    while (srcItr != stations.end() && (*srcItr)->getName() != src) srcItr++;     // Find source station
    while (destItr != stations.end() && (*destItr)->getName() != dest) destItr++;     // Find source station
    if (srcItr == stations.end() || destItr == stations.end()) return;                                 // Source or destination station not found
    Station *srcStation = *srcItr;
    Station *destStation = *destItr;
    srcStation->removeOutgoingTrack(dest);
    destStation->removeIncomingTrack(src);
}

void Network::removeStation(const string &name) {
    auto itr = stations.begin();
    while (itr != stations.end() && (*itr)->getName() != name) itr++;    // Find station
    if (itr == stations.end()) return;                                   // Station not found
    (*itr)->removeIncomingTracks();
    (*itr)->removeOutgoingTracks();
    stations.erase(itr);                                         // Remove station from set
}

int Network::getNumStations()  const {
    return (int) stations.size();
}

vector<Station*> Network::getStations() const {
    return stations;
}

void Network::testAndVisit(queue<Station *> &q, Track *t, Station *s, double residual) {
    if (!s->isVisited() && residual > 0) {
        s->setVisited(true);
        s->setPath(t);
        q.push(s);
    }
}

bool Network::findAugmentingPath(Station *source, Station *dest) {
    for (Station* station : stations) {
        if (station->getName() != source->getName())
            station->setVisited(false);
        else
            station->setVisited(true);
    }

    queue<Station*> q;
    q.push(source);

    while(!q.empty() && !(dest->isVisited())) {
        Station* v = q.front();
        q.pop();
        for (Track* t : v->getAdj())
            testAndVisit(q, t, t->getDestination(),  t->getCapacity() - t->getFlow());
        for (Track* t : v->getIncoming())
            testAndVisit(q, t, t->getSource(), t->getFlow());
    }
    return dest->isVisited();
}

int Network::findMinResidualAlongPath(Station *source, Station *dest) {
    int f = INT16_MAX;
    int cost = 0;
    for (auto v = dest; v != source; ) {
        auto e = v->getPath();
        if (e->getDestination() == v) {
            f = min(f, e->getCapacity() - e->getFlow());
            v = e->getSource();
        }
        else {
            f = min(f, e->getFlow());
            v = e->getDestination();
        }
        cost += e->getService() == "STANDARD" ? 4 : 2;
    }
    return f;
}

pair<int,int> Network::edmondsKarpCost(Station *src, Station *dest) {

    vector<pair<int,int>> all_flowCosts;

    for (Station *station: stations)
        for (Track *track: station->getAdj())
            track->setFlow(0);

    while (findAugmentingPath(src, dest)) {
        pair<int,int> flowCost = findMinResidualCostAlongPath(src, dest);
        all_flowCosts.push_back(flowCost);
        augmentFlowAlongPath(src, dest, flowCost.first);
    }
    if (all_flowCosts.empty()) { return {-1,-1};}
    std::sort(all_flowCosts.begin(), all_flowCosts.end(),
              [](pair<int,int> p1,pair<int,int> p2) {
        if (p1.first == p2.first) return p1.second < p2.second; return p1.first > p2.first;
    });
    return all_flowCosts.at(0);
}

std::pair<int,int> Network::findMinResidualCostAlongPath(Station *source, Station *dest) {
    int f = INT16_MAX;
    int cost = 0;
    for (auto v = dest; v != source; ) {
        auto e = v->getPath();
        if (e->getDestination() == v) {
            f = min(f, e->getCapacity() - e->getFlow());
            v = e->getSource();
        }
        else {
            f = min(f, e->getFlow());
            v = e->getDestination();
        }
        cost += e->getService() == "Standard" ? 2 : 4;
    }
    return {f,f * cost};
}

void Network::augmentFlowAlongPath(Station *source, Station *dest, double f) {
    for (auto v = dest; v != source; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDestination() == v) {
            e->setFlow(flow + f);
            v = e->getSource();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDestination();
        }
    }
}

void Network::edmondsKarp(Station *source, Station *dest) {
    if (source == nullptr || dest == nullptr || source == dest)
        throw logic_error("Invalid source and/or target vertex");

    for (Station *station: stations)
        for (Track *track: station->getAdj())
            track->setFlow(0);

    while (findAugmentingPath(source, dest)) {
        double f = findMinResidualAlongPath(source, dest);
        augmentFlowAlongPath(source, dest, f);
    }
}

pair<double,vector<pair<string,string>>> Network::topMaxFlow() {
    vector<pair<string,string>> ans;
    vector<pair<string,string>> analysedCases;
    double maxFlow = 0, calculatedCases = 0, cases = (double) (stations.size() * (stations.size() - 1)) / 2;
    int percentage = 0;

    for (size_t i = 0; i != stations.size(); i++) {
        for (size_t j = i; j != stations.size(); j++) {
            Station* src = stations[i];
            Station* dest = stations[j];
            if (src == dest) continue;
            edmondsKarp(src, dest);
            if (percentage < round(calculatedCases++ / cases * 100)) {
                percentage = (int) round(calculatedCases / cases * 100);
                Util::cleanTerminal();
                Util::printLoadingBar(percentage, "Calculating max flow between all pairs of stations...");
            }
            double flow = dest->getFlow();
            if (flow < maxFlow) continue;
            if (flow > maxFlow) {
                maxFlow = flow;
                ans.clear();
            }
            ans.emplace_back(src->getName(), dest->getName());
        }
    }
    return {maxFlow, ans};
}

struct {
        bool operator() (const pair<string, double>& pair1, const pair<string, double>& pair2) {
            return (pair1.second > pair2.second);
        }
} customComparator;

vector<pair<string,int>> Network::topTransportationNeeds(string location) {
    vector<pair<string,int>> res;
    auto cases = (double) (pow(getNumStations(), 2) - getNumStations()) / 2;
    double calculatedCases = 0;
    int percentage = 0;
    auto getLocationString = [&](Station* station) {
        if (location == "district") return station->getDistrict();
        else if (location == "municipality") return station->getMunicipality();
        return string("");
    };
    for (Station* station : stations) {
        string locStr = getLocationString(station);
        auto itr = find_if(res.begin(), res.end(), [&](const auto& p) {
            return p.first == locStr;
        });
        if ((itr == res.end() ) && !locStr.empty())
            res.emplace_back(locStr, 0);
        if ((itr == res.end() || res.empty()) && !locStr.empty())
            res.emplace_back(locStr, 0);
    }
    for (int i = 0; i < getNumStations(); i++) {
        Station* src = stations[i];
        string srcLocStr = getLocationString(src);
        for (int j = i; j < getNumStations(); j++) {
            Station* dest = stations[j];
            if (src == dest) continue;

            edmondsKarp(src, dest);
            int flow = dest->getFlow();

            auto itrSource = find_if(res.begin(), res.end(), [&](const auto& p) {
                return p.first == srcLocStr;
            });
            itrSource->second += flow;

            string destLocStr = getLocationString(dest);
            auto itrDest = find_if(res.begin(), res.end(), [&](const auto& p) {
                return p.first == destLocStr;
            });
            itrDest->second += flow;
            if (percentage < round(calculatedCases++ / cases * 100)) {
                percentage = (int) round(calculatedCases / cases * 100);
                Util::cleanTerminal();
                Util::printLoadingBar(percentage, "Calculating top transportation needs according to " + location + "...");
            }
        }
    }
    sort(res.begin(), res.end(), customComparator);
    return res;
}

void Network::DFS(vector<Station *> &endStations, Station *srcStation) {

    srcStation->setVisited(true);
    bool unvisitedNeighbours = false;
    for (Track* track : srcStation->getIncoming()) {
        if (!track->getSource()->isVisited()) {
            unvisitedNeighbours = true;
            DFS(endStations, track->getSource());
        }
    }
    if (!unvisitedNeighbours)
        endStations.push_back(srcStation);
}

int Network::maxTrainsStation(Station* dest) {

    vector<Station*> endStations;
    for (Station* station : stations)
        station->setVisited(false);
    DFS(endStations, dest);

    Station *superSource = new Station("test", "test", "test", "test", "test");

    for (Station* station : endStations)
        superSource->addTrack(station, INT16_MAX, "REGULAR");
    addStation(superSource);
    edmondsKarp(superSource, dest);
    removeStation(superSource->getName());

    return dest->getFlow();
}


