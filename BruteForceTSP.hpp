#ifndef BRUTEFORCETSP_HPP
#define BRUTEFORCETSP_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>

using namespace std;

class BruteForceTSP {

    private:
    //max amount of cities as the file only contains data for an adjacency matrix of 20 cities
        const int MAX_CITIES =20;

        double distances[20][20];
//vector to store best tour for printing 
        vector<int> bestTour;

        //makes array that can store all necessary distances from file


    public:
       //reads the distances from the entire file and makes the adjacency matrix for problem
    void readDistances();
// calculates cost of a specific tour by summing all distances between cities in tour 
    double calculateCost(int tour[], int n);

//homemade permutation function to generate all the possible tours, similar to the one in the project statement
//but not a void function as it returns bool to know when we have made all permutations 

    bool perm1(int s[], int numElements);
    //brute force algorithm that returns best tour cost
    double bruteForce(int n);
    //prints the best tour found from algorithm
    void printBestTour();
        
};















#endif