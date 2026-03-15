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

        const int MAX_CITIES =20;

        double distances[20][20];

        vector<int> bestTour;

        //makes array that can store all necessary distances from file


    public:
       //reads the distances from the entire file and makes the adjacency matrix for problem
    void readDistances();

    double calculateCost(int tour[], int n);

    bool perm1(int s[], int numElements);
    double bruteForce(int n);
    void printBestTour();
        
};















#endif