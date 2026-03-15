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


class GeneticAlgorithmTSP{

    private:
       
        const int MAX_CITIES= 20;
        int numCities;
       
        vector<vector<int>> population;

        double mutationRate;
        int populationSize;
        double distances[20][20];
        vector<int> bestTour;
        
        vector<double> fitness;

        public:
        GeneticAlgorithmTSP(int n, double mutRate, int popSize);
        void readDistances();


    double calculateCost(const vector<int>& tour);

    void selectParents(int& parent1, int& parent2);

  void evaluateFitness();

  void crossover(int parent1, int parent2, vector<int>& child);

  void mutate(vector<int>& tour);

  void geneticAlgo(int generations);
  void printBestCost();
  void printBestTour();
 




};








#endif