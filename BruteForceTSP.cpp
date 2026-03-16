#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include "BruteForceTSP.hpp"
using namespace std;


// definition for readDistance function
   void BruteForceTSP:: readDistances() {


        ifstream file("distances.txt");
    //error exception 
        if (!file) {

            cerr <<"Error openeing file" <<endl;

            return;

        }
        //reads distances and makes the 20*20 adjacency matrix, if on the same city then it doesnt read from file
        //as the file doesnt include 0s for the same city

        for (int i=0; i<20; i++){

            for (int j=0; j<20; j++){

                if (i==j) {

                    distances[i][j]=0;
                }

                else {

                    file >> distances[i][j];

                }

            }

        }

    }



    //calculates the cost of a specific tour by summing all distances between cities in the tour

     double BruteForceTSP::calculateCost(int tour[], int n) {

        double cost=0;

        for (int i=0; i<n-1; i++) {

            cost+=distances[tour[i]][tour[i+1]];

        }

        cost+=distances[tour[n-1]][tour[0]];

        return cost;
    }



    // this is the perm1 function that generates all possible tours
    // it is similar to the one in the project statement but will return a bool
    //all cities will have a tour starting at city 0 so we always have the correct starting city

     bool BruteForceTSP:: perm1(int s[], int numElements) {

        int m= numElements-2;

        //finds the rightest pair of cities that are increasing in order, if
        //none then we have made all permutations 

        while(m>=0 && s[m]>s[m+1]) {

            m=m-1;

        }
        //return for all permutaions made
        if (m<0){

            return false;

        };

        int k=numElements-1;

        while(s[m]>s[k]) {

            k=k-1;

        }

   //swaps the cities at m and k to make the next tour

        swap (s[m],s[k]);

        int p = m+1;

        int q = numElements-1;

    //swaps the cities to the right of m to make the next tour

        while(p<q) {

            swap(s[p],s[q]);

            p++;

            q--;

        }

    //returns true for the next tour generated
    // this function is used over and over again with tour modified each time then ran back through again


        return true;
    }




    //this is the actual brute force algorithm that does the legwork of making all tours then finding the best one

    double BruteForceTSP:: bruteForce(int n) {


        //initial tour with cities max amount of cities
        //we will only use the first n cities for the tour
        // in all honesty this never going to be more than 12/13 cities 
        //due to the time expenditure

        int tour[20];

        //ensures the tour has the correct starting city of 0

        tour[0] = 0;

        for (int i = 1; i < n; i++) {

            //makes initial tour with cities in order, we will modify this to make all perms

            tour[i] = i;


        }

        //calculate the cost of the first tour and uses it as baseline for best tour

        double minCost = calculateCost(tour, n);

        //sets the best tour to the first tour to initilize it

        bestTour = vector<int>(tour, tour + n);

        //generates all the tours by permuting the cities then comparing costs to find the best one
        //we start with start with the second permuattion as we have already initilized the first one and found its cost
        
        while (perm1(tour + 1, n - 1)) {

            double cost = calculateCost(tour, n);

            if (cost < minCost) {

                minCost = cost;

                //the +n is needed to only take in the correct amount of cities

                bestTour = vector<int>(tour, tour + n);

            }
        }

        return minCost;
    }

// prints the best tour and also its cost

     void BruteForceTSP::printBestTour() {

        cout<<"Best TSP TOUR: ";

        for (int i=0; i<bestTour.size(); i++) {

            cout<<bestTour[i]<<" ";

            
        }
        cout<<"Cost for this tour: "<< calculateCost(bestTour.data(), bestTour.size())<<endl;
        
        cout<<endl;
    }