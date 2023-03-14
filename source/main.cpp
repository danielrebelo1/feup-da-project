#include <string>
#include <fstream>
#include "iostream"
#include "headers/FileReader.h"

int main(){
    Graph *g;
    FileReader fr("../dataset", g);
    std::string test = fr.strip("   ..-.-.. asdasdasdasda  .-. . --.. ");
    std::cout << test << std::endl;
    std::vector<Station*> stations = fr.readStations();

    for (Station *station : stations)
        std::cout << station->getName() << '_' << station->getDistrict() << '_' << station->getMunicipality()
        << '_' << station->getTownship() << '_' << station->getLine() << std::endl;

    return 0;
}