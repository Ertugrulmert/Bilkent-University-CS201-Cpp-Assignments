/*
 * Homework Assignment 2
 * main.cpp
 *
 * 25 November 2020
 * Mert Ertugrul
 */

#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <iomanip>


using namespace std;

//Implementation of the first algorithm
void algorithm1(const int* arr1, const int* arr2, const int N, int* arr3 ) {

    //appending elements of array 1
    for ( int i = 0; i < N; i++ ){
        arr3[i] = arr1[i];
    }

    int n = 0;
    int i = 0;

    while (n-i < N && i<N ){
        //if nth element of array 3 is the first element larger than the ith element of array 2
        if (arr3[n]>=arr2[i]){
            //shift array elements
            for (int j= N+i; j>n; j--){
                arr3[j] = arr3[j-1];
            }
            arr3[n] = arr2[i];
            n++;
            i++;
        }
        else
            n++;
    }

    while(i<N){
        arr3[n] = arr2[i];
        n++;
        i++;
    }
}


//Implementation of the second algorithm
void algorithm2(const int* arr1, const int* arr2, const int N, int* arr3 ) {

    int n1 = 0, n2 = n1;

    while (n1 < N && n2 < N){
        if (arr1[n1]<=arr2[n2]){
            arr3[n1+n2]=arr1[n1];
            n1++;
        }
        else {
            arr3[n1+n2]=arr2[n2];
            n2++;
        }
    }
    while (n1 < N ){
        arr3[n1+n2]=arr1[n1];
        n1++;
    }
    while (n2 < N ){
        arr3[n1+n2]=arr2[n2];
        n2++;
    }

 }


//initializes an array with random numbers between given upper and lower bounds
 void randomArray(int * arr, const int size, const int lower_bound, const int upper_bound) {

    for (int i = 0; i < size; i++) {
        int randNum = rand()%( upper_bound - lower_bound + 1) + lower_bound;
        arr[i] = randNum;
    }
    sort(arr, arr + size);
}


//fills array based on array element ordering cases specified in the instructions
void fillArrays(int * arr1, int * arr2, const int size, const int ordering_case) {

    switch (ordering_case) {
        case 1:
            //array 1 is initialized with elements strictly smaller than those of array 2
            randomArray(arr1, size, 1, size*2);
            randomArray(arr2, size, 2*size+1, 4*size);

//            cout << "case 1, array1: ";
//            for (int i = 0; i < size; ++i)
//                cout << arr1[i] << " ";
//            cout << endl;
//
//            cout << "case 1, array2: ";
//            for (int i = 0; i < size; ++i)
//                cout << arr2[i] << " ";
//            cout << endl;

            break;

        case 2:
            //array 2 is initialized with elements strictly smaller than those of array 1
            randomArray(arr2, size, 1, size*2);
            randomArray(arr1, size, 2*size+1, 4*size);

//            cout << "case 2, array1: ";
//            for (int i = 0; i < size; ++i)
//                cout << arr1[i] << " ";
//            cout << endl;
//
//            cout << "case 2, array2: ";
//            for (int i = 0; i < size; ++i)
//                cout << arr2[i] << " ";
//            cout << endl;
            break;

        case 3:
            //there is no ordering between  elements of array 1 and 2
            randomArray(arr1, size, 1, size*4);
            randomArray(arr2, size, 1, size*4);

//            cout << "case 3, array1: ";
//            for (int i = 0; i < size; ++i)
//                cout << arr1[i] << " ";
//            cout << endl;
//
//            cout << "case 3, array2: ";
//            for (int i = 0; i < size; ++i)
//                cout << arr2[i] << " ";
//            cout << endl;

            break;
    }
}


int main() {

    //number of repetitions for measurement
    //(to avoid getting 0 milliseconds when smaller N values are used)
    //can be reduced or increased based on your machine or the size of array (N) chosen
    const int rep = 1000;

    //array size for arr1 and arr2
    const int N = 1000  ;

    //in the original implementation and measurement, high_resolution_clock from <chrono> was used
    //to make sure that dijkstra does not cause problems, I changed it to <ctime> before submission,
    //results may not be as precise
    clock_t startTime;

    int* arr1;
    int* arr2;
    int* arr3;

    for (int c = 1; c<4; c++){

        arr1 = new int[N];
        arr2 = new int[N];
        arr3 = new int[2*N];

        //initializing arrays
        fillArrays(arr1, arr2, N, c);

        //******************************ALGORITHM 1

        //Declare necessary variables
        //Store the starting time
        double duration;
        clock_t startTime = clock();

        //calling the function repeatedly
        for(int i = 0; i<rep; i++){
            algorithm1(arr1, arr2, N, arr3 );
        }

        //Compute the number of milliseconds that passed since the starting time
        duration = 1000.0 * double( clock() - startTime ) / (rep*CLOCKS_PER_SEC);
        cout << "Execution of algorithm 1 for case "<< c<<" took " << duration <<std::setprecision(5)<< " milliseconds." << endl;

        delete [] arr3;
        arr3 = new int[2*N];

        //******************************ALGORITHM 2

        startTime = clock();

        //calling the function repeatedly
        for(int i = 0; i<rep; i++){
            algorithm2(arr1, arr2, N, arr3 );
        }

        //Compute the number of milliseconds that passed since the starting time
        duration = 1000.0 * double( clock() - startTime ) / (rep*CLOCKS_PER_SEC);
        cout << "Execution of algorithm 2 for case "<< c<<" took " << duration <<std::setprecision(5)<< " milliseconds." << endl;



        delete [] arr3;
        delete [] arr2;
        delete [] arr1;

    }

}

