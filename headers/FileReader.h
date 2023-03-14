#ifndef PROJECT_FILEREADER_H
#define PROJECT_FILEREADER_H

#include <iostream>
#include "Station.h"
#include <limits>
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <fstream>
#include "headers/Segment.h"
#include "Graph.h"

class FileReader {
    std::string path;
    Graph *graph;

public:
    FileReader(const std::string &path, Graph *graph);
    std::vector<Station*> readStations();
    void readNetworks();
    std::string strip(const std::string &str) const;
    std::string capitalizeFirstLetter(const std::string &str);
};

#endif //PROJECT_FILEREADER_H

