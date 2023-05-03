#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

#include "Network.h"
#include "StationTrack.h"

class Network;

namespace Util {
    /**
     * Checks if a given character is either a withespace or a quotation mark
     * @param c the character to be checked
     * @return true if the character is a whitespace or a quotation mark, false otherwise
     */
    bool discard(char c);
    /**
     * @brief Prints multiple new lines to the terminal to clear it
     */
    void cleanTerminal();
    /**
     * @brief Creates a string that is a repetition of a given string n times
     * @param str the string to be repeated
     * @param times the number of times the string is to be repeated
     * @return the produced string
     */
    std::string repeat(const std::string &str, int times);
    /**
     * @brief Prints a loading bar to the terminal
     * @param percentage the percentage of the loading bar to be filled
     * @param message the message to be displayed above the loading bar
     */
    void printLoadingBar(int percentage, const std::string& message);
    /**
     * @brief Normalises a string by converting it to lowercase
     * @param s the string to be normalised
     * @return the normalised string
     */
    std::string normalise(const std::string &s);
    /**
     * @brief Checks if a string is numerical
     * @param str the string to be checked
     * @return true if the string is numerical, false otherwise
     */
    bool isNumerical(const std::string &str);
    /**
     * @brief Centers a string in a given width by adding spaces to the left and right
     * @param str the string to be centered
     * @param width the width of the centered string
     * @return the centered string
     */
    std::string center(const std::string &str, int width);
    /**
     * @brief Capitalizes the first letter of a string
     * @param str the string to be capitalized
     * @return the capitalized string
     */
    std::string capitalizeFirstLetter(const std::string &str);
    /**
     * @brief Removes the leading and trailing whitespaces of a string
     * @param str the string to be stripped
     * @return the stripped string
     */
    std::string strip(const std::string &str);
    /**
     * @brief Splits a string into a vector of strings by a given delimiter
     * @param str the string to be split
     * @param delimiter the delimiter to be used
     * @return a vector of split parts of the string
     */
    std::vector<std::string> split(const std::string &str, char delimiter);
    /**
     * @brief Reads the stations from a file and adds them to the network
     * @param path the path to the file
     * @param graph the network to which the stations are to be added
     */
    void readStations(const std::string &path, Network *graph);
    /**
     * @brief Reads the tracks from a file and adds them to the network
     * @param path the path to the file
     * @param graph the network to which the tracks are to be added
     */
    void readNetwork(const std::string &path, Network *graph);
}

#endif //FILEREADER_H
