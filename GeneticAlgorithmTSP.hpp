#ifndef GENETICALGORITHMTSP_HPP
#define GENETICALGORITHMTSP_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <random>
using namespace std;


//class declaration for genetic algorithm, has all function declarations

class GeneticAlgorithmTSP{

    private:
       //max cities is 20 as again the file can only be used to make an adjacency matrix of 20 cities

        const int MAX_CITIES= 20;
        int numCities;
        double bestCostReturn;

       //population is a vector of vectors to hold different tours for genetic algorithm 

        vector<vector<int>> population;

      // mutation rate and other parameters for functions as well as the distance matrix for the adjacency matrix

        double mutationRate;
        int populationSize;
        double distances[20][20];
        vector<int> bestTour;

        //vectors for both the best tour an best fitness

        vector<double> fitness;

        public:

        //constructor for class, sets paremeters for everything except generation count

         GeneticAlgorithmTSP(int n, double mutRate, int popSize);

        //reads the distances from the file
         void readDistances();

        // calcualtes the cost of a given tour by summing 

         double calculateCost(const vector<int>& tour);
        
         void selectParents(int& parent1, int& parent2);
         
        //evaluates"fitness" of each tour in population by taking inverse of cost

         void evaluateFitness();

        //crossover method to create a "child" tour form two "parent" tours
        //still ensures the child has city 0 as starting point and all cities are visited exactly once

         void crossover(int parent1, int parent2, vector<int>& child);


        // mutation method to randomly swap two cities in tour, mutation chance depends on mut rate parameter

         void mutate(vector<int>& tour);

        //genetic algorithm method that runs for a given number of generations, creates new populations
        //through the alteration methods and keeps track of the best tour or "elite" tour found so far


         void geneticAlgo(int generations);

         //printing functions for terminal output


         void printBestCost();
         void printBestTour();
         double getBestCost();




};








#endif