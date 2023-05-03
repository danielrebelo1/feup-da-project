#ifndef STATIONTRACK_H
#define STATIONTRACK_H

#include <iostream>
#include <vector>
#include <string>


class Track;

/************************* Station  **************************/

class Station {
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;
    std::vector<Track*> adj;
    bool visited = false;
    Track *path = nullptr;
    std::vector<Track*> incoming;
public:
    /**
     * @brief Station class constructor
     * @param name the name of the station
     * @param district the district of the station
     * @param municipality the municipality of the station
     * @param township the township of the station
     * @param line the line of the station
     */
    Station(const std::string &name, const std::string &district, const std::string &municipality, const std::string &township, const std::string &line);
    /**
     * @brief Get function for the name of the station
     * @return a string with the name of the station
     */
    [[nodiscard]] std::string getName() const;
    /**
     * @brief Get function for the district of the station
     * @return a string with the district of the station
     */
    [[nodiscard]] std::string getDistrict() const;
    /**
     * @brief Get function for the municipality of the station
     * @return a string with the municipality of the station
     */
    [[nodiscard]] std::string getMunicipality() const;
    /**
     * @brief Get function for the township of the station
     * @return a string with the township of the station
     */
    [[nodiscard]] std::string getTownship() const;
    /**
     * @brief Get function for the line of the station
     * @return a string with the line of the station
     */
    [[nodiscard]] std::string getLine() const;
    /**
     * @brief Get function for the adjacency list of the station
     * @return a vector with the adjacent stations to the station
     */
    [[nodiscard]] std::vector<Track*> getAdj() const;
    /**
     * @brief Get function for the visited attribute of the station
     * @return a boolean with the value of the visited state of the station
     */
    [[nodiscard]] bool isVisited() const;
    /**
     * @brief Get function for the path attribute of the station
     * @return a pointer to the track that leads to the station
     */
    [[nodiscard]] Track *getPath() const;
    /**
     * @brief Get function for the incoming list of the station
     * @return a vector with the tracks that lead to the station
     */
    [[nodiscard]] std::vector<Track*> getIncoming() const;
    /**
     * @brief Get function that calculates the flow of the station
     * @return an integer with the flow of the station
     */
    [[nodiscard]] int getFlow() const;
    /**
     * @brief Set function for the visited attribute of the station
     * @param visited sets the station visited attribute to the value of the parameter
     */
    void setVisited(bool visited);
    /**
     * @brief Set function for the path attribute of the station
     * @param path sets the station path attribute to the value of the parameter
     */
    void setPath(Track *path);
    /**
     * @brief Adds a track to the station
     * @param dest the destination station of the track
     * @param capacity the capacity of the track
     * @param service the service of the track
     * @return a pointer to the track that was added
     */
    Track *addTrack(Station *dest, int capacity, const std::string &service);
    /**
     * @brief Removes a track with 'dest' as destination from the adjacency list of the station
     * @param dest the destination station of the track to be removed
     */
    void removeOutgoingTrack(const std::string &dest);
    /**
     * @brief Removes a track with 'src' as destination from the incoming list of the station
     * @param src the destination station of the track to be removed
     */
    void removeIncomingTrack(const std::string &src);
    /**
     * @brief Removes all tracks from the adjacency list of the station
     */
    void removeOutgoingTracks();
    /**
     * @brief Removes all tracks from the incoming list of the station
     */
    void removeIncomingTracks();
};

/********************** Track  ****************************/

class Track {
    Station *src;
    Station *dest;
    int capacity;
    double flow;
    std::string service;

public:
    /**
     * @brief Track class constructor
     * @param src pointer to the source station
     * @param dest pointer to the destination station
     * @param capacity the value of the capacity of the track
     * @param service the track type of service
     */
    Track(Station *src, Station *dest, int capacity, const std::string &service);
    /**
     * @brief Get function for the source station of the track
     * @return a pointer to the source station of the track
     */
    [[nodiscard]] Station *getSource() const;
    /**
     * @brief Get function for the destination station of the track
     * @return a pointer to the destination station of the track
     */
    [[nodiscard]] Station *getDestination() const;
    /**
     * @brief Get function for the capacity of the track
     * @return an integer with the value of the capacity of the track
     */
    [[nodiscard]] int getCapacity() const;
    /**
     * @brief Get function for the flow of the track
     * @return an integer with the value of the flow of the track
     */
    [[nodiscard]] int getFlow() const;
    /**
     * @brief Get function for the service of the track
     * @return a string with the value of the service of the track
     */
    [[nodiscard]] std::string getService() const;
    /**
     * @brief Set function for the flow of the track
     * @param flow sets the track flow attribute to the value of the parameter
     */
    void setFlow(int flow);
};

#endif //STATIONTRACK_H
