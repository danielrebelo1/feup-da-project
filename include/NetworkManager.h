#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <vector>
#include <string>
#include <utility>

#include "Network.h"
#include "StationTrack.h"
#include "Util.h"

#define tracks_vector std::vector<std::pair<std::string,std::string>>

namespace NetworkManager {
    /**
     * @brief Reduces the connectivity of the network by removing the given tracks and stations
     * @param network the network to be reduced
     * @param tracks the tracks to be removed
     * @param stations the stations to be removed
     */
    void reduceConnectivity(Network *network, const tracks_vector &tracks, const std::vector<std::string> &stations);
    /**
     * @brief Creates a network graph by reading the given dataset
     * @param datasetPath the dataset path where "network.csv" and "stations.csv" are located
     * @return a pointer to the network graph
     */
    Network *createGraph(const std::string &datasetPath);
    /**
     * @brief This function calls the edmonds karp algorithm to find the maximum flow between two stations
     * @param network a pointer to the network graph
     * @param source a pointer to the source station
     * @param target a pointer to the target station
     * @return an integer with the maximum flow between the two stations
     */
    int maxFlowBetween(Network *network, Station *source, Station *target);
    /**
     * @brief Calls the edmonds karp for every pair of stations in both networks, returns the top n stations that have the biggest difference in max flow
     * @param normalNetwork the normal network in question
     * @param reducedNetwork the reduced network in question
     * @param n the number of stations to be returned
     * @return a vector with pointers to the top n affected stations by the reduced circumstances in the reduced network
     */
    std::vector<Station*> topAffectedStations(Network *normalNetwork, Network *reducedNetwork, int n);
    /**
     * @brief Deletes the network graph
     * @param network a pointer to the network to be deleted
     */
    void deleteGraph(Network *network);
};


#endif //NETWORKMANAGER_H
