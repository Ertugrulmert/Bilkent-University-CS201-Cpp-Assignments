//
//  FlightMap.cpp
//  Homework Assignment 4
//
//  Author: Mert Ertugrul
//  Date: 26.12.2020
//

#include "FlightMap.h"


using namespace std;

//forms the flight map given city and flight information
FlightMap::FlightMap( const string cityFile, const string flightFile ){

    extractCities(cityFile);
    extractFlights(flightFile);

}

//initializes city array from file
void FlightMap::extractCities(const string cityFile) {


    string cityName;
    ifstream inputFile;

    //First finding the number of cities

    try {
        inputFile.open( cityFile.c_str(), ios_base::in );
    }
    catch ( ifstream::failure e) {
        cout<<"Wrong file path"<<endl;
        cerr << "Exception opening file, file path may be wrong\n";
    }

    while ( getline( inputFile, cityName, '\n' ) ) {

        if (cityName[cityName.size() - 1] == '\r')
            cityName.resize(cityName.size() - 1);

        this->cityNames.push_back(cityName);
    }
    inputFile.close();
    inputFile.clear();

    this->cityNumber = cityNames.size();

}


//fills in the flight information on a flight matrix
void FlightMap::extractFlights(const string flightFile) {

    //allocating the flight matrix
    flightMatrix = new flight*[cityNumber];
    for (int i = 0; i < cityNumber; i++)
        flightMatrix[i] = new flight[cityNumber];

    ifstream inputFile;
    try {
        inputFile.open( flightFile.c_str(), ios_base::in );
    }
    catch ( ifstream::failure e) {
        cout<<"Wrong file path"<<endl;
        cerr << "Exception opening file, file path may be wrong\n";
    }

    string flightString;
    //reading lines
    while ( getline( inputFile, flightString, '\n' ) ) {

        // text file format varies so we account for an "\r" that might be left
        if (flightString[flightString.size() - 1] == '\r')
            flightString.resize(flightString.size() - 1);

        int departure, destination, cost;
        string ID;

        string value;
        stringstream linestream(flightString);

        //extract information from line string

            //Departure City
        getline(linestream,value,',');
        departure = getCityIndex(value);

            //Destination City
        getline(linestream,value,',');
        destination = getCityIndex(value);

            //Flight ID
        getline(linestream,value,',');
        ID = value;

            //Flight Cost
        getline(linestream,value,',');
        cost = atoi(value.c_str());

        //adding flight information to matrix
        if (departure > -1 && destination > -1){
            this->flightMatrix[departure][destination].ID = ID;
            this->flightMatrix[departure][destination].cost = cost;
        }
    }
    inputFile.close();
    inputFile.clear();

}
//retrieves the array index of the city given its name
int FlightMap::getCityIndex(const string cityName) const{

    for (int i = 0; i < cityNames.size(); i++) {
        if (cityNames[i] == cityName)
            return i;
    }
    return -1;
}

//destructor
FlightMap::~FlightMap(){

    //Deallocating flight matrix
    for (int i = 0; i < cityNumber; i++)
        delete[] flightMatrix[i];
    delete[] flightMatrix;
}


//displays city names
void FlightMap::displayAllCities() const{

    if (cityNumber > 0){
        for (int i = 0; i< cityNumber; i++)
            cout<<cityNames[i]<<", ";
        cout<<endl;
    }
    else
        cout<<"HPAir does not serve any cities currently."<<endl;
}

//displays departures from a given city
void FlightMap::displayAdjacentCities( const string cityName ) const{

    int cityIndex = getCityIndex(cityName);

    if (cityIndex == -1)
        cout<<"The city "<<cityName<<" could not be found."<<endl;
    else
       displayAdjacentUtil(cityIndex);
}

//displays departures from every city
void FlightMap::displayFlightMap() const{

    for (int i=0; i<cityNumber; i++)
        displayAdjacentUtil(i);
}

//displays adjacent cities given city index - internal function to avoid redundancy
void FlightMap::displayAdjacentUtil(const int cityIndex) const{

    cout<<cityNames[cityIndex]<<" -> ";
    for (int i=0; i<cityNumber; i++){
        //if a flight exists to the destination (cost is 0 when it does not)
        if( flightMatrix[cityIndex][i].cost != 0)
          cout<<cityNames[i]<<", ";
    }
    cout<<endl;
}


//finds all valid flight paths from an origin city to a destination
void FlightMap::findFlights( const string deptCity, const string destCity ) const{

    cout<<"Request is to fly from "<<deptCity<<" to "<<destCity<<":"<<endl;

    //We store the paths we found in a vector of stacks. Each path is a stack.
    vector<Stack*> pathsFound;

    //converting names to indexes
    int departure = getCityIndex(deptCity);
    int destination = getCityIndex(destCity);

    //search algorithm is run
    flightSearchUtil(departure,destination,pathsFound);

    //if no valid paths found
    if ( pathsFound.size()==0){
        cout<<"Sorry. HPAir does not fly from "<<deptCity<<" to "<<destCity<<endl;
        cout<<endl;
    }
    else {
        for(int i=0; i < pathsFound.size(); i++)
            //display flights along path and path cost
            processPath(*pathsFound[i]);
    }

    //deallocating the path stacks
    for(int i=0; i < pathsFound.size(); i++)
        delete pathsFound[i];
}

void FlightMap::findLeastCostFlight( const string deptCity, const string destCity )const{

    cout<<"Request is to fly from "<<deptCity<<" to "<<destCity<<":"<<endl;

    //We store the paths we found in a vector of stacks. Each path is a stack.
    vector<Stack*> pathsFound;

    //converting names to indexes
    int departure = getCityIndex(deptCity);
    int destination = getCityIndex(destCity);

    //search algorithm is run
    flightSearchUtil(departure,destination,pathsFound);
    //if no valid paths found
    if ( pathsFound.size()==0){
        cout<<"Sorry. HPAir does not fly from "<<deptCity<<" to "<<destCity<<endl;
        cout<<endl;
    }
    else {
        //keep track of the cheapest path index and cost while displaying path info
        int leastCost = processPath(*pathsFound[0]);
        int leastCostPath = 0;

        for(int i=1; i < pathsFound.size(); i++){
            int temp = processPath(*pathsFound[i]);
            if (temp<leastCost){
                leastCost=temp;
                leastCostPath = i;
            }
        }

        cout<<"A least cost path from "<<deptCity<<" to "<<destCity<<" is ";

        //displaying the cheapest path
        int temp;

        //beginning from the end of the path, we combine cities on the path in a string
        pathsFound[leastCostPath]->pop(temp);
        string pathString = cityNames[temp];

        while(pathsFound[leastCostPath]->pop(temp))
            pathString = cityNames[temp]+" -> "+pathString;

        cout<<pathString<<" and its cost is "<<leastCost<<" TL"<<endl;
        cout<<endl;
    }
    //deallocating the path stacks
    for(int i=0; i < pathsFound.size(); i++)
        delete pathsFound[i];
}

//automatically carries out least cost path finding for all city pairs in file
void FlightMap::runFlightRequests( const string requestFile ) const{

    ifstream inputFile;
    try {
        inputFile.open( requestFile.c_str(), ios_base::in );
    }
    catch ( ifstream::failure e) {
        cout<<"Wrong file path"<<endl;
        cerr << "Exception opening file, file path may be wrong\n";
    }

    string departure, destination;

    while (getline(inputFile,departure,',') ) {

            //Destination City
        getline(inputFile,destination,'\n');

        if (destination[destination.size() - 1] == '\r')
            destination.resize(destination.size() - 1);

        findLeastCostFlight( departure, destination );
    }
    inputFile.close();
}

//internal function for the path finding algorithm based on stacks
//once found, paths are stored as stacks inside a vector to be displayed later
void FlightMap::flightSearchUtil( const int deptIndex, const int destIndex, vector<Stack*> &pathsFound)const {

    //blocked flight mask prevents loops and repetitions of the same paths
    //creating the blocked flight mask (locally created as the functions are constant)
    bool** blocked_mask = new bool*[cityNumber];
    for (int i = 0; i < cityNumber; i++)
        blocked_mask[i] = new bool[cityNumber];

    //initializing the mask to false
    for (int i = 0; i < cityNumber; i++){
        for (int j = 0; j < cityNumber; j++)
            blocked_mask[i][j]= false;
    }

    //stack used to hold current path
    Stack cityStack;

    //Initialize with origin city
    cityStack.push(deptIndex);

    //edge case where destination is origin
    if (deptIndex == destIndex){
        pathsFound.push_back(new Stack(cityStack));
        return;
    }

    //while the flight graph has not been exhausted
    while ( !cityStack.isEmpty() ){

        //index of the city we are currently on
        int current = 0;
        cityStack.peek(current);

        //check if we reached our destination
        if ( current == destIndex){
            //making a copy of the stack, placing it in our paths vector to store as a valid path to be displayed
            pathsFound.push_back(new Stack(cityStack) );
            //backtracking
            cityStack.pop();
        }
        else{
            bool valid_destination = false;
            //check for valid flights departing from city
            for (int next=0; next<cityNumber; next++){
                //checks if any departures from a city are valid (not blocked) and not already in the path
                if ( flightMatrix[current][next].cost > 0 && !blocked_mask[current][next] ){
                    //we determine a loop is to occur when a city has a departing flight that is blocked
                    //because blocks are lifted from flights departing from a city when we backtrack from the city
                    //so if a block is present, that city is still / already in the path
                    valid_destination = true;

                    for (int departure=0; departure<cityNumber; departure++){
                        //if a flight departing from the candidate destination is blocked, it is already in the path
                        if (departure != next && blocked_mask[next][departure]){
                            valid_destination = false;
                            break;
                        }
                    }
                    if (valid_destination ){
                        //mark flight as blocked
                        blocked_mask[current][next] = true;
                        //going to the next city
                        cityStack.push(next);
                        break;
                    }
                }
            }

            //if no valid flight was found, backtrack to previous city
            if (!valid_destination){
                //lifting blocks on flights departing from the city
                for (int destination=0; destination<cityNumber; destination++)
                    blocked_mask[current][destination] = false;
                //backtracking
                cityStack.pop();
            }
        }
    }
    //deallocating blocked mask memory
    for (int i = 0; i < cityNumber; i++)
        delete[] blocked_mask[i];
    delete[] blocked_mask;
}

//displays details of flights in the path and returns total path cost
int FlightMap::processPath(Stack path) const{

    int cost = 0;
    int departure = 0;
    int destination = 0;
    string flights = "";

    //reversing the stack to print from beginning to the end
    Stack reversed;
    while( path.pop(destination) )
        reversed.push(destination);

    if ( reversed.pop(departure) ) {

        while ( reversed.pop(destination) ) {
            cout<<"Flight #"<<flightMatrix[departure][destination].ID;
            cout<<" from "<<cityNames[departure]<<" to "<<cityNames[destination];
            cout<<"    Cost: "<<flightMatrix[departure][destination].cost<<" TL"<<endl;
            cost += flightMatrix[departure][destination].cost;
            departure = destination;
        }
        cout<<"Total Cost .......... "<<cost<<" TL"<<endl;
        cout<<endl;
    }
    return cost;
}



