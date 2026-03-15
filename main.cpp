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
 
    srand(time(0));
    bool continueProgram=true;

    while(continueProgram) {
        int cityCountBF;
        int generations;
        double mutationRate;
        int populationSize;
        int cityCountGen;


        BruteForceTSP bForceSolver;

        cout<<"welcome to tsp solver" <<endl;
        cout<<"Enter number of cities for brute force method(up to 12 for reasonable time): ";
        cin>>cityCountBF;
        cout<<"Brute Force Method: " <<endl;
        bForceSolver.readDistances();
        clock_t startTime=clock();
        cout<<"Minimum TSP Cost: "<<bForceSolver.bruteForce(cityCountBF)<<endl;
        clock_t endTime=clock();
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
        GeneticAlgorithmTSP gaSolver(cityCountGen, mutationRate, populationSize);
        gaSolver.readDistances();
        clock_t gaStartTime=clock();
        gaSolver.geneticAlgo(generations);
        clock_t gaEndTime=clock();
        gaSolver.printBestCost();

        double gaElapsedTime= double(gaEndTime-gaStartTime)/CLOCKS_PER_SEC;
        cout<<"Elapsed Time for Genetic Algorithm: "<<gaElapsedTime<<" seconds"<<endl;
        cout<<"Best TSP tour from GA Algo"<<endl;
        gaSolver.printBestTour();
        int userChoice;
        cout<<"Do you want to solve another TSP problem (1 for yes and 0 for )";
        cin>>userChoice;
        if (userChoice==0){
            continueProgram=false;
        }        

    
    }
   
    return 0;
}