//
//  FlightMap.h
//  Homework Assignment 4
//
//  Author: Mert Ertugrul
//  Date: 26.12.2020
//

#ifndef __FLIGHT_MAP_H
#define __FLIGHT_MAP_H

#include <iostream>
#include <fstream>
#include<cstdlib>
#include <vector>
#include <sstream>
#include "Stack.h"

using namespace std;


class FlightMap {

public:

    FlightMap( const string cityFile, const string flightFile );
    ~FlightMap();

    void displayAllCities() const;

    void displayAdjacentCities( const string cityName ) const;

    void displayFlightMap() const;

    void findFlights( const string deptCity, const string destCity ) const;

    void findLeastCostFlight( const string deptCity, const string destCity )const;

    void runFlightRequests( const string requestFile ) const;

private:

    int getCityIndex(const string CityName) const;

    void extractFlights(const string flightFile);

    void extractCities(const string cityFile);

    void displayAdjacentUtil(const int cityIndex) const;

    void flightSearchUtil( const int deptIndex, const int destIndex, vector<Stack*> &pathsFound)const;

    int processPath(Stack path) const;

    int cityNumber;
    vector<string> cityNames;

    struct flight
    {
        flight() : ID(""), cost(0) {}

        string ID;
        int cost;
    };

    flight** flightMatrix;

};

#endif
