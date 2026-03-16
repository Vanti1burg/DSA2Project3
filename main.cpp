#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include "BruteForceTSP.hpp"
#include "GeneticAlgorithmTSP.hpp"
using namespace std;




int main () {
 //seed random number generator for multiple runs
    srand(time(0));
    bool continueProgram=true;

//initialize main loop for user to test different parameters for both algorithms

    while(continueProgram) {

        //variables for input parameters for algorithms

        int cityCountBF;
        int generations;
        double mutationRate;
        int populationSize;
        int cityCountGen;

   //initialize objects for brute force as constructor doesnt need user input
   
        BruteForceTSP bForceSolver;

        cout<<"welcome to tsp solver" <<endl;
        cout<<"Enter number of cities for brute force method(up to 12 for reasonable time): ";

     // take in the number of cities for the brute force algorithm, anything greater than 12 will take a long period of time

        cin>>cityCountBF;

        cout<<"Brute Force Method: " <<endl;

  //read the distance file for adjacency matrix for brute force algorithm

        bForceSolver.readDistances();
    //run brute force algorithm and time it for analysis later

        clock_t startTime=clock();
        double totalBruteTime=bForceSolver.bruteForce(cityCountBF);
        clock_t endTime=clock();
        


   // calculate the total time for brute force to complete from clock timer

        double elapsedTime= double(endTime-startTime)/CLOCKS_PER_SEC;

        cout<<"Elapsed Time for Brute Force: "<<elapsedTime<<" seconds"<<endl;
        cout<<"Best TSP tour from Brute Force Algo"<<endl;

        bForceSolver.printBestTour();

        cout<<"Enter number of cities for genetic algo method(up to 20): ";

        cin>>cityCountGen;

        cout<<"Enter mutation rate from 0.0 to 1.0: ";

        cin>>mutationRate;

        cout<<"Enter population per generation: ";

        cin>>populationSize;

        cout<<"Enter number of genrations: ";

        cin>>generations;

        cout<<"Genetic Algorithm Method: "<<endl;

       //initialize genetic algorithm object with the parameters needed for the constructor

        GeneticAlgorithmTSP gaSolver(cityCountGen, mutationRate, populationSize);

       //reads the distances from the file for genetic algorithm to create the adjacency matrix for the cities

        gaSolver.readDistances();

      //run the genetic algorithm and time it for analysis versus the brute force algorithm later

        clock_t gaStartTime=clock();

        gaSolver.geneticAlgo(generations);

        clock_t gaEndTime=clock();

      //print the best cost found from genetic algorithm, now redundant but was useful for debugging functions printing best tours

        gaSolver.printBestCost();

      //calculate total time for genetic algorithm to complete from clock

        double gaElapsedTime= double(gaEndTime-gaStartTime)/CLOCKS_PER_SEC;

        double bestGACost=gaSolver.getBestCost();
        
        cout<<"Elapsed Time for Genetic Algorithm: "<<gaElapsedTime<<" seconds"<<endl;
        
        cout<<"Best TSP tour from GA Algo"<<endl;

       //shows route taken for the best tour found from the genetic algorithm

        gaSolver.printBestTour();
        
        int userChoice;




       //asks if the user wants to continue the program or end it

        cout<<"Percent optimal GA compared to Brute Force Optimal Solution: "<<fixed<<setprecision(2)<<(bestGACost/totalBruteTime)*100<<"%"<<endl;
        cout<<"Do you want to solve another TSP problem (1 for yes and 0 for no): ";

        cin>>userChoice;

        if (userChoice==0){

            continueProgram=false;

        }        


    
    }
   
    return 0;
}