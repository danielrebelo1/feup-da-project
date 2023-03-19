#ifndef NETWORK_H
#define NETWORK_H

#include <thread>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include "StationTrack.h"

class Network {
    std::vector<Station*> stationsSet;
public:
    Station* findStation(std::string stationName) const;
    bool addStation(Station* station);
    bool addTrack(const std::string &sourc, const std::string &dest, double capacity,const std::string &service);
    bool addBidirectionalTrack(const std::string &source,const std::string &dest, double capacity, const std::string &service);
    int getNumStations() const;
    [[nodiscard]] std::vector<Track*> getTracksSet() const;
    [[nodiscard]] std::vector<Station*> getStationsSet() const;

    /*
     * EdmondsKarp algorithm and its auxiliary functions
     * This functions refer to exercise 2.1
     * */
    void edmondsKarp(const std::string &source, const std::string &dest);
    bool findAugmentingPath(Station* source, Station* dest);
    void testAndVisit(std::queue<Station*> &q, Track *t, Station* s, double residual);
    double findMinResidualAlongPath(Station* source, Station* dest);
    void augmentFlowAlongPath(Station* source, Station* dest, double f);

    /*This function refers to exercise 2.2*/
    std::pair<double,std::vector<std::pair<Station*,Station*>>> topMaxFlow();

    /*This function refers to exercise 2.3*/
    std::vector<std::pair<std::string, double>>topTransportationNeeds(std::string location);

    /*This function refers to exercise 2.4*/
    double maxTrainsStation(Station* dest);

};


#endif //NETWORK_H
