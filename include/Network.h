#ifndef NETWORK_H
#define NETWORK_H

#include <cmath>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>

#include "StationTrack.h"
#include "Util.h"

class Network {
    std::vector<Station*> stations;
public:
    /**
     * @brief Constructor of the Network class
     * @param stationName the name of the intended station
     * @return a pointer to the station with the given name if it exists, nullptr otherwise
     */
    [[nodiscard]] Station *findStation(const std::string &stationName) const;
    /**
     * @brief Adds a station to the network
     * @param station the name of the station to be added
     */
    void addStation(Station *station);
    /**
     * @brief Removes a station from the network
     * @param name the name of the station to be removed
     */
    void removeStation(const std::string &name);
    /**
     * @brief Gets the number of stations in the network
     * @return the number of stations in the network
     */
    [[nodiscard]] int getNumStations() const;
    /**
     * @brief Gets the stations in the network
     * @return a vector with pointers to the stations in the network
     */
    [[nodiscard]] std::vector<Station*> getStations() const;    /**
     * @brief Adds a track to the network
     * @param source the name of the source station
     * @param dest the name of the destination station
     * @param capacity the capacity of the track
     * @param service the service of the track
     */
    void addTrack(const std::string &source, const std::string &dest, int capacity, const std::string &service) const;
    /**
     * @brief Removes a track from the network
     * @param src the name of the source station
     * @param dest the name of the destination station
     */
    void removeTrack(const std::string &src, const std::string &dest);
    /**
     * @brief Finds the maximum flow between two stations using the edmonds karp algorithm
     * @param source a pointer to the source station
     * @param dest a pointer to the destination station
     */
    void edmondsKarp(Station *source, Station *dest);
    /**
     * @brief Variation of Edmonds Karp that also stores the augmening paths with the smallest cost
     * @param src a pointer to the source station
     * @param dest a pointer to the destination station
     * @return a pair with the maximum flow and the cost of the augmenting paths with the smallest cost
     */
    std::pair<int,int> edmondsKarpCost(Station *src, Station *dest);
    /**
     * @brief Finds if there is an augmenting path between two stations
     * @param source a pointer to the source station
     * @param dest a pointer to the destination station
     * @return true if there is an augmenting path, false otherwise
     */
    bool findAugmentingPath(Station* source, Station* dest);
    /**
     * @brief If possible sets a station as visited and as part of a path
     * @param q the queue of stations to be visited
     * @param t the track that leads to the station
     * @param s the station to be visited
     * @param residual the residual capacity of the track
     */
    static void testAndVisit(std::queue<Station*> &q, Track *t, Station* s, double residual);
    /**
     * @brief Finds the minimum residual capacity along a path
     * @param source a pointer to the source station
     * @param dest a pointer to the destination station
     * @return the minimum residual capacity along a path
     */
    static int findMinResidualAlongPath(Station* source, Station* dest);
    /**
     * @brief Finds the minimum residual capacity and cost along a path
     * @param source a pointer to the source station
     * @param dest a pointer to the destination station
     * @return a pair with the minimum residual capacity and the cost of the path
     */
    static std::pair<int,int> findMinResidualCostAlongPath(Station *source, Station *dest);
    /**
     * @brief Augments the flow along a path
     * @param source a pointer to the source station
     * @param dest a pointer to the destination station
     * @param f the flow to be augmented
     */
    static void augmentFlowAlongPath(Station* source, Station* dest, double f);
    /**
     *
     * @brief Finds the maximum value of maximum flow between any two stations in the network
     * @return <maximum flow, vector of pairs of stations that have that maximum flow value>
     */
    std::pair<double,std::vector<std::pair<std::string,std::string>>> topMaxFlow();
    /**
     * @brief Finds the stations that have the highest transportation needs
     * @param location district or municipality
     * @return a vector of pairs of stations and their transportation needs
     */
    std::vector<std::pair<std::string, int>> topTransportationNeeds(std::string location);
    /**
     * @brief DFS traversal algorithm to find "terminal" stations
     * @param endStations vector where terminal stations are saved
     * @param srcStation current station
     */
    void DFS(std::vector<Station*> &endStations, Station* srcStation);
    /**
     * @brief Calculates the maximum amount of trains that can arrive simultaneously at a station
     * @param dest a pointer to the destination station
     * @return the maximum amount of trains that can arrive simultaneously at a station
     */
    int maxTrainsStation(Station* dest);
};

#endif //NETWORK_H
