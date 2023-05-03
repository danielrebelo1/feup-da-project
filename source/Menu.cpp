#include "../include/Menu.h"

using namespace std;

Menu::Menu(Network *network, const string &path) {
    this->path = path;
    this->network = network;
    this->input = "0";
    Util::cleanTerminal();
}

void Menu::run() {
    bool alive = true;
    while (alive) {
        switch (stoi(input)) {
            case 0: mainMenu(); break;
            case 1: exercise_2_1(); input = "0"; break;
            case 2: exercise_2_2(); input = "0"; break;
            case 3: exercise_2_3(); input = "0"; break;
            case 4: exercise_2_4(); input = "0"; break;
            case 5: exercise_3_1(); input = "0"; break;
            case 6: exercise_4_1(); input = "0"; break;
            case 7: exercise_4_2(); input = "0"; break;
            case 8: manageReducedNetworks(); input = "0"; break;
            case 9: alive = false; break;
        }
        Util::cleanTerminal();
    }
}

void Menu::mainMenu() {
    cout << string(190, '_') << endl
         << '|' << Util::center("Main menu", 188) << '|' << endl
         << '|' << Util::center("Choose an option to continue", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl
         << '|' << Util::center("", 188) << '|' << endl
         << '|' << Util::center("1. Calculate the maximum number of trains that can travel between two chosen stations. [exercise 2.1.]", 188) << '|' << endl
         << '|' << Util::center("2. Calculate the maximum number of trains that can travel between any two stations. [exercise 2.2.]", 188) << '|' << endl
         << '|' << Util::center("3. Display top n districts/municipalities according to budget needs. [exercise 2.3.]", 188) << '|' << endl
         << '|' << Util::center("4. Calculate the maximum number of trains that can arrive to a chosen station. [exercise 2.4.]", 188) << '|' << endl
         << '|' << Util::center("5. Calculate the maximum number of trains that can travel between two chosen stations with minimum cost. [exercise 3.1.]", 188) << '|' << endl
         << '|' << Util::center("6. Calculate the maximum number of trains that can travel between two chosen stations under reduced connectivity circumstances. [exercise 4.1.]", 188) << '|' << endl
         << '|' << Util::center("7. Display top n stations affected by the reduced connectivity circumstances. [exercise 4.2.]", 188) << '|' << endl
         << '|' << Util::center("8. Manage reduced connectivity graphs", 188) << '|' << endl
         << '|' << Util::center("9. Exit", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl
         << endl;

    while (true) {
        cout << "   - OPTION: " << std::flush;
        getline(cin >> ws, input);
        if (Util::isNumerical(input) && 1 <= stoi(input) && stoi(input) <= 10) break;
        else cout << "   - INVALID OPTION" << endl;
    }
}

void Menu::exercise_2_1() {
    Station *choice1 = listStations(network->getStations(), "Choose the source station: ");
    if (choice1 == nullptr) return;
    Station *choice2 = listStations(network->getStations(), "Choose the destination station: ", choice1);
    if (choice2 == nullptr) return;
    Util::cleanTerminal();
    string message = "From: " + choice1->getName() + " ---> To: " + choice2->getName();
    int result = NetworkManager::maxFlowBetween(network, choice1, choice2);
    while (true) {
        cout << string(190, '_') << endl
             << '|' << Util::center("Max flow", 188) << '|' << endl
             << '|' << Util::center(message, 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl
             << endl
             << Util::center("The calculated result is: " + to_string(result), 190) << endl
             << Util::center("This means that between the two stations there can be a maximum number of " + to_string(result) + " trains travelling simultaneously.", 190)
             << endl
             << string(190, '_') << endl
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;
        while (true) {
            cout << "   - OPTION: " << std::flush;
            getline(cin >> ws, input);
            cout << endl;
            if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}

void Menu::exercise_2_2() {
    pair<int,vector<pair<string,string>>> res = network->topMaxFlow();
    int MaxFlow = res.first;
    vector<pair<string,string>> v = res.second;
    Util::cleanTerminal();
    cout << string(190, '_') << endl
         << '|' << Util::center("Top max flow", 188) << '|' << endl
         << '|' << Util::center("This function calculates the max flow between all pairs of stations and", 188) << '|' << endl
         << '|' << Util::center("returns all the pairs that have the maximum max flow value.", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl
         << endl
         << Util::center("The calculated result is: " + to_string(MaxFlow), 188) << endl
         << Util::center("The pair(s) of stations that have this max flow is/are:", 188) << endl;
    for (int i = 1; i <= v.size(); i++)
        cout << Util::center(to_string(i) + ". " + v[i - 1].first + " -> " + v[i-1].second, 190) << endl;
    cout << endl;
    cout << string(190, '_') << endl
         << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl;
    while (true) {
        cout << "   - OPTION: " << std::flush << std::flush;
        getline(cin >> ws, input);
        cout << endl;
        if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
        else cout << "   - INVALID OPTION" << endl;
    }
}

void Menu::exercise_2_3() {
    string option;
    int no;
    vector<pair<string, int>> res;
    Util::cleanTerminal();
    cout << string(190, '_') << endl
         << '|' << Util::center("Top transportation needs", 188) << '|' << endl
         << '|' << Util::center("For this function you may choose to calculate the top", 188) << '|' << endl
         << '|' << Util::center("transportation needs according to:", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl
         << endl
         << Util::center("1. District", 190) << endl
         << Util::center("2. Municipality", 190) << endl
         << endl
         << string(190, '_') << endl
         << '|' << Util::center("WRITE 1 OR 2 TO DISPLAY RESULT", 188) << '|' << endl
         << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl;
    while (true) {
        cout << "   - OPTION: " << std::flush;
        getline(cin >> ws, input);
        cout << endl;
        if (input == "1") {
            option = "district";
            break;
        } else if (input == "2") {
            option = "municipality";
            break;
        } else if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
        else cout << "   - INVALID OPTION" << endl;
    }
    while (true) {
        Util::cleanTerminal();
        cout << string(190, '_') << endl
             << '|' << Util::center("WRITE THE MAX NUMBER OF STATIONS TO DISPLAY", 188) << '|' << endl
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;

        getline(cin >> ws, input);
        if (option == "district" && Util::isNumerical(input) && stoi(input) > 0 && stoi(input) <= 18) {
            no = stoi(input);
            break;
        }
        else if(option == "municipality" && Util::isNumerical(input) && stoi(input) > 0 && stoi(input) <= 135) {
            no = stoi(input);
            break;
        }
        else if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
        else cout << "   - INVALID OPTION" << endl;
    }

    res = network->topTransportationNeeds(option);
    res.resize(no);
    Util::cleanTerminal();
    cout << string(190, '_') << endl
         << '|' << Util::center("Top transportation needs", 188) << '|' << endl
         << '|' << Util::center("The top transportation needs according to " + option + " are:", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl
         << endl;
    for (auto &[place, flow] : res)
        cout << Util::center(place + " has " + to_string(flow) + " of total flow.", 190) << endl;
    cout << endl
         << string(190, '_') << endl
         << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl;
    while (true) {
        cout << "   - OPTION: " << std::flush;
        getline(cin >> ws, input);
        cout << endl;
        if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
        else cout << "   - INVALID OPTION" << endl;
    }
}

void Menu::exercise_2_4() {
    Station *st = listStations(network->getStations(), "Choose a station: ");
    if (st == nullptr) return;
    int maxFlow = network->maxTrainsStation(st);
    Util::cleanTerminal();
    cout << string(190, '_') << endl
         << '|' << Util::center("Maximum number of arriving trains to " + st->getName() + " considering entire railway:", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl
         << endl
         << Util::center("The maximum number of trains that can simultaneously arrive at " + st->getName() + " train station is " + to_string(maxFlow), 190) << endl
         << endl
         << string(190, '_') << endl
         << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl;
    while (true) {
        cout << "   - OPTION: " << std::flush;
        getline(cin >> ws, input);
        cout << endl;
        if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
        else cout << "   - INVALID OPTION" << endl;
    }
}

void Menu::exercise_3_1() {
    Station *src, *dest;
    pair<int,int> p;
    while (true) {
        Util::cleanTerminal();
        src = listStations(network->getStations(), "Choose the source station: ");
        if (src == nullptr) return;
        dest = listStations(network->getStations(), "Choose the destination station: ", src);
        if (dest == nullptr) return;
        p = network->edmondsKarpCost(src,dest);
        if (p.first != -1 && p.second != -1) break;
        cout << string(190, '_') << endl
             << '|' << Util::center("No path found", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << Util::center("WRITE ANYTHING ELSE TO TRY AGAIN", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;
        cout << "   - OPTION: " << std::flush;
        getline(cin >> ws, input);
        cout << endl;
        if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
    }

    /*Station *src = listStations(network->getStations(), "Choose the source station: ");
    if (src == nullptr) return;
    Station *dest = listStations(network->getStations(), "Choose the destination station: ", src);
    if (dest == nullptr) return;
    pair<int,int> p = network->edmondsKarpCost(src,dest);
    if (p.first == -1 && p.second == -1) {
        while (true) {
            cout << string(190, '_') << endl
                 << '|' << Util::center("No path found", 188) << '|' << endl
                    << '|' << string(188, '_') << '|' << endl
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
                    << '|' << string(188, '_') << '|' << endl;
            cout << "   - OPTION: " << std::flush;
            getline(cin >> ws, input);
            cout << endl;
            if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
            else cout << "   - INVALID OPTION" << endl;
        }
    }*/
    Util::cleanTerminal();
    cout << string(190, '_') << endl
         << '|' << Util::center("Maximum number of arriving trains travelling between", 188) << '|' << endl
         << '|' << Util::center(src->getName() + " and " + dest->getName(), 188) << '|' << endl
         << '|' << Util::center("with minimum costs for the company", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl
         << endl
         << Util::center("The max flow of trains between " + src->getName() + " and " + dest->getName() +  " is: " + to_string(p.first), 190) << endl
         << Util::center("The minimum cost for the company is: " + to_string(p.second) + "€", 190) << endl
         << endl
         << string(190, '_') << endl
         << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl;
    while (true) {
        cout << "   - OPTION: " << std::flush;
        getline(cin >> ws, input);
        cout << endl;
        if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
        else cout << "   - INVALID OPTION" << endl;
    }
}

void Menu::exercise_4_1() {
    Network *reducedNetwork = selectReducedNetwork();
    if (reducedNetwork == nullptr) return;
    Station *src = listStations(reducedNetwork->getStations(), "Choose the source station: ");
    if (src == nullptr) return;
    Station *dest = listStations(reducedNetwork->getStations(), "Choose the destination station: ", src);
    if (dest == nullptr) return;
    Util::cleanTerminal();
    string message = "From: " + src->getName() + " ---> To: " + dest->getName();
    int result = NetworkManager::maxFlowBetween(reducedNetwork, src, dest);
    while (true) {
        cout << string(190, '_') << endl
             << '|' << Util::center("Max flow in reduced connectivity circumstances", 188) << '|' << endl
             << '|' << Util::center(message, 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl
             << endl
             << Util::center("The calculated result is: " + to_string(result), 190) << endl
             << Util::center("This means that between the two stations there can be a maximum number of " + to_string(result) + " trains.", 190)
             << endl
             << string(190, '_') << endl
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;
        while (true) {
            cout << "   - OPTION: " << std::flush;
            getline(cin >> ws, input);
            cout << endl;
            if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}

void Menu::exercise_4_2() {
    int no;
    bool alive = true;
    while (alive) {
        cout << string(190, '_') << endl
             << '|' << Util::center("Calculate the most affected stations considering", 188) << '|' << endl
             << '|' << Util::center("reduced connectivity circumstances.", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl
             << string(190, '_') << endl
             << '|' << Util::center("WRITE THE MAX NUMBER OF STATIONS TO DISPLAY", 188) << '|' << endl
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;
        while (true) {
            cout << "   - OPTION: " << std::flush;
            getline(cin >> ws, input);
            cout << endl;
            if (Util::isNumerical(input) && stoi(input) > 0 && stoi(input) <= 10) {
                no = stoi(input);
                alive = false;
                break;
            }
            if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
    Network *reducedNetwork = selectReducedNetwork();
    if (reducedNetwork == nullptr) return;
    vector<Station*> topStations = NetworkManager::topAffectedStations(network, reducedNetwork, no);
    Util::cleanTerminal();
    while (true) {
        cout << string(190, '_') << endl
             << '|' << Util::center("The top " + to_string(no) + " affected stations by the selected reduced graph are:", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl
             << endl;
        for (int i = 0; i < topStations.size(); i++)
            cout << Util::center(to_string(i+1) + ". " + topStations.at(i)->getName(), 190) << endl;
        cout << endl
             << string(190, '_') << endl
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;
        while (true) {
            cout << "   - OPTION: " << std::flush;
            getline(cin >> ws, input);
            cout << endl;
            if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}

void Menu::manageReducedNetworks() {
    bool alive = true;
    while (alive) {
        Util::cleanTerminal();
        cout << string(190, '_') << endl
             << '|' << Util::center("Reduced Networks Manager", 188) << '|' << endl
             << '|' << Util::center("In this menu you can create, remove, or rename your reduced networks!", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl
             << endl
             << endl
             << Util::center("1. Create reduced network", 190) << endl
             << Util::center("2. Delete reduced network", 190) << endl
             << Util::center("3. Rename reduced network", 190) << endl
             << Util::center("4. Edit reduced network", 190) << endl
             << Util::center("5. See all reduced networks", 190) << endl
             << endl
             << string(190, '_') << endl
             << '|' << Util::center("WRITE A NUMBER OPTION TO PROCEED", 188) << '|' << endl
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;
        while (true) {
            cout << "   - OPTION: " << std::flush;
            getline(cin >> ws, input);
            cout << endl;
            if (Util::normalise(input) == "1") {
                alive = createReducedNetwork();
                break;
            } else if (Util::normalise(input) == "2") {
                alive = deleteReducedNetwork();
                break;
            } else if (Util::normalise(input) == "3") {
                alive = renameReducedNetwork();
                break;
            } else if (Util::normalise(input) == "4") {
                alive = editReducedNetwork();
                break;
            } else if (Util::normalise(input) == "5") {
                alive = seeReducedNetworks();
                break;
            } else if (Util::normalise(input) == "menu" || Util::normalise(input) == "back") return;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}

void Menu::listReducedNetworks() {
    cout << endl;
    if (reducedNetworks.empty()) {
        cout << Util::center("THERE ARE NO REDUCED NETWORKS YET", 190) << endl;
        cout << endl;
        return;
    }
    int i = 1;
    for (auto &reducedNetwork : reducedNetworks)
        cout << Util::center(to_string(i++) + " -   " + reducedNetwork.first, 190) << endl;
    cout << endl;
}

bool Menu::createReducedNetwork() {
    Network *reducedNetwork = NetworkManager::createGraph(path);
    while (true) {
        Util::cleanTerminal();
        cout << string(190, '_') << endl
             << '|' << Util::center("Create a reduced network", 188) << '|' << endl
             << '|' << Util::center("Choose one of the options to create a simulation of a reduced connectivity network!", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl
             << endl
             << endl
             << Util::center("1. Remove station", 190) << endl
             << Util::center("2. Remove path", 190) << endl
             << Util::center("3. Save", 190) << endl
             << endl
             << string(190, '_') << endl
             << '|' << Util::center("WRITE A NUMBER OPTION TO PROCEED", 188) << '|' << endl
             << '|' << Util::center("WRITE BACK TO GO TO THE PREVIOUS MENU", 188) << '|' << endl
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;
        while (true) {
            cout << "   - OPTION: " << std::flush;
            getline(cin >> ws, input);
            cout << endl;
            if (input == "1") {
                Station *st = listStations(reducedNetwork->getStations(), "Choose the station to remove: ");
                if (st == nullptr) break;
                reducedNetwork->removeStation(st->getName());
                break;
            }
            else if (input == "2") {
                Station *src = listStations(reducedNetwork->getStations(), "Choose the source station: ");
                if (src == nullptr) break;
                vector<Station*> possibleDestinations;
                for (Track *track : src->getAdj())
                    possibleDestinations.push_back(track->getDestination());
                Station *dest = listStations(possibleDestinations, "Choose the destination station: ", src);
                if (dest == nullptr) break;
                reducedNetwork->removeTrack(src->getName(), dest->getName());
                break;
            }
            else if (input == "3") {
                cout << Util::center("Write the name of the reduced network: ", 190) << endl;
                getline(cin >> ws, input);
                reducedNetworks.emplace(input, reducedNetwork);
                return true;
            }
            else if (Util::normalise(input) == "back") {
                NetworkManager::deleteGraph(reducedNetwork);
                return true;
            }
            else if (Util::normalise(input) == "menu") {
                NetworkManager::deleteGraph(reducedNetwork);
                return false;
            }
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}

bool Menu::deleteReducedNetwork() {
    while (true) {
        Util::cleanTerminal();
        cout << string(190, '_') << endl
             << '|' << Util::center("Delete a reduced network", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl
             << endl;
        listReducedNetworks();
        cout << endl
             << string(190, '_') << endl
             << '|' << Util::center("WRITE THE NAME OF A REDUCED NETWORK IN ORDER TO DELETE IT", 188) << '|' << endl
             << '|' << Util::center("WRITE BACK TO GO TO THE PREVIOUS MENU", 188) << '|' << endl
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;
        while (true) {
            cout << "   - OPTION: " << std::flush;
            getline(cin >> ws, input);
            cout << endl;
            if (reducedNetworks.find(input) != reducedNetworks.end()) {
                NetworkManager::deleteGraph(reducedNetworks.at(input));
                reducedNetworks.erase(input);
                break;
            }
            else if (Util::normalise(input) == "back") return true;
            else if (Util::normalise(input) == "menu") return false;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}

bool Menu::renameReducedNetwork() {
    string prevName;
    while (true) {
        Util::cleanTerminal();
        cout << string(190, '_') << endl
             << '|' << Util::center("Rename a reduced network", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl
             << endl;
        listReducedNetworks();
        cout << endl
             << string(190, '_') << endl
             << '|' << Util::center("WRITE THE NAME OF A REDUCED NETWORK IN ORDER TO RENAME IT", 188) << '|' << endl
             << '|' << Util::center("WRITE BACK TO GO TO THE PREVIOUS MENU", 188) << '|' << endl
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;
        while (true) {
            cout << "   - OPTION: " << std::flush;
            getline(cin >> ws, input);
            cout << endl;
            if (reducedNetworks.find(input) != reducedNetworks.end()) {
                prevName = input;
                cout << Util::center("Write the new name of the reduced network: ", 190) << endl;
                getline(cin >> ws, input);
                reducedNetworks.emplace(input, reducedNetworks[input]);
                reducedNetworks.erase(prevName);
                break;
            }
            else if (Util::normalise(input) == "back") return true;
            else if (Util::normalise(input) == "menu") return false;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}

bool Menu::seeReducedNetworks() {
    Util::cleanTerminal();
    cout << string(190, '_') << endl
         << '|' << Util::center("See all reduced networks", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl
         << endl;
    listReducedNetworks();
    cout << endl
         << string(190, '_') << endl
         << '|' << Util::center("WRITE BACK TO GO TO THE PREVIOUS MENU", 188) << '|' << endl
         << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl;
    while (true) {
        cout << "   - OPTION: " << std::flush;
        getline(cin >> ws, input);
        cout << endl;
        if (Util::normalise(input) == "back") return true;
        else if (Util::normalise(input) == "menu") return false;
        else cout << "   - INVALID OPTION" << endl;
    }
}

Network *Menu::selectReducedNetwork() {
    Util::cleanTerminal();
    cout << string(190, '_') << endl
         << '|' << Util::center("See all reduced networks", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl
         << endl;
    listReducedNetworks();
    cout << endl
         << string(190, '_') << endl
         << '|' << Util::center("WRITE THE REDUCED NETWORK NAME TO SELECT IT", 188) << '|' << endl
         << '|' << Util::center("WRITE BACK TO GO TO THE PREVIOUS MENU", 188) << '|' << endl
         << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
         << '|' << string(188, '_') << '|' << endl;
    while (true) {
        cout << "   - OPTION: " << std::flush;
        getline(cin >> ws, input);
        cout << endl;
        if (reducedNetworks.find(input) != reducedNetworks.end()) return reducedNetworks[input];
        if (Util::normalise(input) == "back" || Util::normalise(input) == "menu") return nullptr;
        else cout << "   - INVALID OPTION" << endl;
    }
}

bool Menu::editReducedNetwork() {
    Network *selectedNetwork = selectReducedNetwork();
    if (selectedNetwork == nullptr) return true;
    while (true) {
        Util::cleanTerminal();
        cout << string(190, '_') << endl
             << '|' << Util::center("Edit a reduced network", 188) << '|' << endl
             << '|'
             << Util::center("Choose one of the options to create a simulation of a reduced connectivity network!", 188)
             << '|' << endl
             << '|' << string(188, '_') << '|' << endl
             << endl
             << endl
             << Util::center("1. Remove station", 190) << endl
             << Util::center("2. Remove path", 190) << endl
             << Util::center("3. Finish", 190) << endl
             << endl
             << string(190, '_') << endl
             << '|' << Util::center("WRITE A NUMBER OPTION TO PROCEED", 188) << '|' << endl
             << '|' << Util::center("WRITE BACK TO GO TO THE PREVIOUS MENU", 188) << '|' << endl
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;
        while (true) {
            cout << "   - OPTION: " << std::flush;
            getline(cin >> ws, input);
            cout << endl;
            if (input == "1") {
                Station *st = listStations(selectedNetwork->getStations(), "Choose the station to remove: ");
                if (st == nullptr) break;
                selectedNetwork->removeStation(st->getName());
                break;
            } else if (input == "2") {
                Station *src = listStations(selectedNetwork->getStations(), "Choose the source station: ");
                if (src == nullptr) break;
                vector<Station *> possibleDestinations;
                for (Track *track: src->getAdj())
                    possibleDestinations.push_back(track->getDestination());
                Station *dest = listStations(possibleDestinations, "Choose the destination station: ", src);
                if (dest == nullptr) break;
                selectedNetwork->removeTrack(src->getName(), dest->getName());
                break;
            } else if (Util::normalise(input) == "back" || input == "3") return true;
            else if (Util::normalise(input) == "menu") return false;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}

Station *Menu::listStations(std::vector<Station*> stations, const string &message, Station *ignoreStation) {
    int page = 0;
    if (ignoreStation) {
        for (auto itr = stations.begin(); itr != stations.end(); itr++) {
            if (*itr == ignoreStation) {
                stations.erase(itr);
                break;
            }
        }
    }
    while (true) {
        Util::cleanTerminal();
        cout    << string(190, '_') << endl
                << '|' << Util::center("STATIONS", 188) << '|' << endl
                << '|' << Util::center(message, 188) << '|' << endl
                << '|' << string(188, '_') << '|' << endl;
        for (int i = page * 20; i < min(page * 20 + 20, (int) stations.size()); i++) {
            cout << right << setw(5) << to_string(i + 1) + ".   " << left
                 << setw(40) << stations[i]->getName()
                 << setw(20) << stations[i]->getDistrict()
                 << setw(30) << stations[i]->getMunicipality()
                 << setw(60) << stations[i]->getTownship()
                 << setw(30) << stations[i]->getLine() << endl;
        }
        cout << string(190, '_') << endl
             << '|' << Util::center("WRITE A NUMBER OR A STATION NAME TO SELECT A STATION", 188) << '|' << endl
             << '|' << Util::center("WRITE W TO MOVE UP", 188) << '|' << endl
             << '|' << Util::center("WRITE S TO MOVE DOWN", 188) << '|' << endl
             << '|' << Util::center("WRITE MENU TO GO TO THE MAIN MENU", 188) << '|' << endl
             << '|' << string(188, '_') << '|' << endl;

        while (true) {
            cout << "   - OPTION: " << std::flush;
            getline(cin >> ws, input);
            cout << endl;
            if (Util::isNumerical(input) && page * 20 + 1 <= stoi(input) &&
                stoi(input) <= min(page * 20 + 20, (int) stations.size())) {
                return stations[stoi(input) - 1];
            } else if (Util::normalise(input) == "w" && page * 20 - 20 >= 0) {
                page--;
                break;
            } else if (Util::normalise(input) == "s" && page * 20 + 20 < (int) stations.size()) {
                page++;
                break;
            } else if (Util::normalise(input) == "menu" || Util::normalise(input) == "back")
                return nullptr;
            for (Station *station : stations)
                if (station->getName() == input)
                    return station;
            cout << "   - INVALID OPTION" << endl;
        }
    }
}

