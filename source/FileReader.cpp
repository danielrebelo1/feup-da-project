//
// Created by Daniel Rebelo on 08/03/2023.
//

#include "headers/FileReader.h"

using namespace std;


FileReader::FileReader(const string &path, Graph *graph) {
    this->path = path;
    this->graph = graph;
}


std::string FileReader::capitalizeFirstLetter(const std::string& str)
{
    std::string result = str;
    if (!result.empty()) {
        result[0] = std::toupper(result[0]);
        for (std::size_t i = 1; i < result.size(); ++i) {
            result[i] = std::tolower(result[i]);
        }
    }
    return result;
}

std::vector<Station *> FileReader::readStations() {
    ifstream stationsFile("dataset/stations.csv");
    stationsFile.ignore(numeric_limits<streamsize>::max(), '\n');

    std::vector<Station*> stations;
    while(stationsFile.good()){
        string sentence, data;
        vector<string> lineVector;
        getline(stationsFile, sentence);

        if(sentence.empty() || sentence == "\r") break;
        stringstream ss(sentence);

        while(getline(ss, data, ',')){
            if(data[0] == '\"'){
                if(data[data.size() - 1] == '\"' || data[data.size() - 1] == '\r'){
                    data = data.erase(0,1);
                    data = data.erase(data.size() - 1);
                }
                else{
                    string temp;
                    getline(ss, temp, '\"');
                    data = data.erase(0,1);
                    data += ',' + temp;
                    if (ss.peek() == ',') ss.ignore();
                }
            }
            lineVector.push_back(data);
        }

        string name = lineVector[0],
                district = capitalizeFirstLetter(lineVector[1]),
                municipality = capitalizeFirstLetter(lineVector[2]),
                township = lineVector[3],
                line = lineVector[4];
        auto* station = new Station(name, district, municipality, township, line);
        stations.push_back(station);
    }

    return stations;
}

/*
std::vector<Station*>  FileReader::readStations() {

    ifstream csv("/home/diogotvf7/Documents/2a2s/da/feup-da-project/dataset/stations.csv");
    vector<Station*> stations;
    string buffer;
    getline(csv, buffer, '\n'); // Ignore Header

    while (getline(csv, buffer, '\n')) {
        string name, district, municipality, township, line;
        stringstream tmp(buffer);

        getline(tmp, name, ',');
        getline(tmp, district, ',');
        getline(tmp, municipality, ',');

        if (tmp.peek()  == '"') {
            getline(tmp, township, '"');
            getline(tmp, township, '"');
        }
        else {
            getline(tmp, township, ',');
        }
        getline(tmp, line, ',');
        getline(tmp, line, '\n');

        stations.push_back(new Station(name, district, municipality, township, line));
    }
    return stations;
}
*/

/*void readNetworks(){

    vector<Segment *> segments;

    std::ifstream networkFile;

    try{
        networkFile.open(inputFile);
    }
    catch (exception e) {
        cout << "Couldn't open network file" << endl;
    }

    networkFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    string line;

    while(getline(networkFile, line)) {

        string src, dest, capacity, service;

        if (line.empty() || line == "\r") break;

        stringstream ss(line);

        getline(ss, src, ',');

        getline(ss, dest, ',');

        getline(ss, capacity, ',');

        getline(ss, service, ',');

        Segment *seg = new Segment(src,dest,stoi(capacity),service);

        segments.push_back(seg);
    }

}

void FileReader::readNetworks() {

}*/

string FileReader::strip(const string &str) const {
    string buffer;
    auto lowerBound = str.begin(), upperBound = str.end();
    while (!isalpha(*lowerBound++));
    while (!isalpha(*upperBound--));
    return {lowerBound, upperBound};
}
