#include "../include/NetworkManager.h"

using namespace std;

struct CMP {
    bool operator()(const pair<string, double> &a, const pair<string, double> &b) {
        return a.second < b.second;
    }
};

namespace NetworkManager {
    void reduceConnectivity(Network *network, const tracks_vector &tracks,
                            const vector <string> &stations) {
        for (auto track: tracks)
            network->removeTrack(track.first, track.second);
        for (string station: stations)
            network->removeStation(station);
    }

    Network *createGraph(const string &datasetPath) {
        Network *network = new Network();
        Util::readStations(datasetPath, network);
        Util::readNetwork(datasetPath, network);
        return network;
    }

    int maxFlowBetween(Network *network, Station *source, Station *target) {
        network->edmondsKarp(source, target);
        return target->getFlow();
    }

    void deleteGraph(Network *network) {
        delete network;
    }

    vector<Station*> topAffectedStations(Network *normalNetwork, Network *reducedNetwork, int n) {
        unordered_map<string, double> realMaxFlow, reducedMaxFlow, diff;
        vector<Station*> res, stationSet = normalNetwork->getStations(), reducedStationSet = reducedNetwork->getStations();
        double cases = (double) (pow(normalNetwork->getNumStations(), 2) - normalNetwork->getNumStations()) / 2 +
                (pow(reducedNetwork->getNumStations(), 2) - reducedNetwork->getNumStations()) / 2;
        double calculatedCases = 0;
        int percentage = 0;

        for (int i = 0; i < normalNetwork->getNumStations(); i++) {
            Station *src = stationSet[i];
            for (int j = i; j < normalNetwork->getNumStations(); j++) {
                Station *dest = stationSet[j];
                if (src == dest) continue;
                normalNetwork->edmondsKarp(src, dest);
                if (percentage < round(calculatedCases++ / cases * 100)) {
                    percentage = (int) round(calculatedCases / cases * 100);
                    Util::cleanTerminal();
                    Util::printLoadingBar(percentage, "Calculating max flow between the original network stations");
                }
                double flow = dest->getFlow();
                string key = src->getName() + "/" + dest->getName();
                realMaxFlow.emplace(key, flow);
            }
        }

        for (int i = 0; i < reducedNetwork->getNumStations(); i++) {
            Station *src = reducedStationSet[i];
            for (int j = i; j < reducedNetwork->getNumStations(); j++) {
                Station *dest = reducedStationSet[j];
                if (src == dest) continue;     //  already exists
                reducedNetwork->edmondsKarp(src, dest);
                if (percentage < round(calculatedCases++ / cases * 100)) {
                    percentage = (int) round(calculatedCases / cases * 100);
                    Util::cleanTerminal();
                    Util::printLoadingBar(percentage, "Calculating max flow between the reduced network stations");
                }
                double flow = dest->getFlow();
                string key = src->getName() + "/" + dest->getName();
                reducedMaxFlow.emplace(key, flow);
            }
        }

        for (auto &[key, maxFlow]: realMaxFlow) {
            string src = Util::split(key, '/')[0], dest = Util::split(key, '/')[1];
            if (reducedNetwork->findStation(src) == nullptr) continue;
            if (reducedNetwork->findStation(dest) == nullptr) continue;
            double maxFlowDifference = abs(maxFlow - reducedMaxFlow[key]);
            diff[src] += maxFlowDifference;
            diff[dest] += maxFlowDifference;
        }

        priority_queue<pair<string, double>, vector<pair<string, double>>, CMP> pq;
        for (auto &[key, value]: diff)
            pq.emplace(key, value);

        while (!pq.empty() && n-- > 0) {
            res.push_back(normalNetwork->findStation(pq.top().first));
            pq.pop();
        }

        return res;
    }
}

