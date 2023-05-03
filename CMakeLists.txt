cmake_minimum_required(VERSION 3.23)
project(feup_da_project)

set(CMAKE_CXX_STANDARD 17)

INCLUDE_DIRECTORIES(.)


add_executable(
        feup_da_project
        dataset/real-dataset/network.csv
        dataset/real-dataset/stations.csv
        dataset/test-dataset/network.csv
        dataset/test-dataset/stations.csv
        include/Util.h
        source/Util.cpp
        include/StationTrack.h
        source/StationTrack.cpp
        include/Network.h
        source/Network.cpp
        include/NetworkManager.h
        source/NetworkManager.cpp
        include/Menu.h source/Menu.cpp Test.hpp main.cpp)