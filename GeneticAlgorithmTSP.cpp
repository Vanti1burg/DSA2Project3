#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>

#include <random>
#include "GeneticAlgorithmTSP.hpp"

using namespace std;


 GeneticAlgorithmTSP::GeneticAlgorithmTSP(int n, double mutRate, int popSize) : numCities(n) {

            mutationRate=mutRate;

            populationSize=popSize;

            population.resize(populationSize, vector<int>(numCities));

            for (int i = 0; i < populationSize; i++) {
                population[i][0] = 0; // Start from city 0
                for (int j = 1; j < numCities; j++) {

                    population[i][j] = j;

                }

             //   random_shuffle(population[i].begin(), population[i].end());
                random_shuffle(population[i].begin() + 1, population[i].end()); // Keep city 0 fixed at the start
            }

                fitness.resize(populationSize);

        }

 void GeneticAlgorithmTSP::readDistances() {


             ifstream file("distances.txt");

             if (!file) {

                    cerr <<"Error openeing file" <<endl;

                 return;

             }
            
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


    double GeneticAlgorithmTSP:: calculateCost(const vector<int>& tour) {

        
        double cost=0;

        for (int i=0; i<numCities-1; i++) {

            cost+=distances[tour[i]][tour[i+1]];

        }

        cost+=distances[tour[numCities-1]][tour[0]];

        return cost;
    }

 void GeneticAlgorithmTSP:: selectParents(int& parent1, int& parent2) {
          
           double totalFitness=0;
// from 0 to population size, add up all fitness values 
            for(int i=0; i<populationSize;i++){
                totalFitness+=fitness[i];

            }
              double pick1=((double)rand()/RAND_MAX)*totalFitness;

              double pick2=((double)rand()/RAND_MAX)*totalFitness;

             double current=0;

             for(int i=0;populationSize;i++){

                current+=fitness[i];

                if(current>pick1 && parent1==-1){
                    parent1=i;
                }

                if (current>pick2 && parent2==-1) {

                    parent2=i;

                }
                if (parent1!=-1 && parent2!=-1) break;
             }
  }


  
  void GeneticAlgorithmTSP::evaluateFitness() {

          for(int i=0; i<populationSize; i++) {

            fitness[i]=1.0/calculateCost(population[i]);

          }
  }


  void GeneticAlgorithmTSP::crossover(int parent1, int parent2, vector<int>& child) {

    child[0] = 0;

    vector<bool> inChild(numCities, false);

    inChild[0] = true; 

    int start = 1 + rand() % (numCities - 1);

    int end = 1 + rand() % (numCities - 1);

    if (start > end) swap(start, end);

   
    for (int i = start; i <= end; i++) {

        child[i] = population[parent1][i];

        inChild[child[i]] = true;

    }

    // Fill remaining positions from parent2 (positions 1..numCities-1)
    int idx = 1;

    for (int i = 1; i < numCities; i++) {

        if (!inChild[population[parent2][i]]) {

            while (idx <= numCities - 1 && child[idx] != -1) idx++;

            if (idx <= numCities - 1) {

                child[idx] = population[parent2][i];

                inChild[child[idx]] = true;

            }
        }
    }
  }



   void GeneticAlgorithmTSP::mutate(vector<int>& tour) {

       double mutateChance= ((double)rand())/RAND_MAX;

       if (mutateChance<mutationRate) {

            int i= rand()%numCities;

            int j=rand()%numCities;

            //ensure we don't swap starting city
            if (i!=0 && j!=0) {

            swap(tour[i],tour[j]);

            }
            
  }
}


void GeneticAlgorithmTSP::geneticAlgo(int generations) {

           
    
            for(int gen=0; gen<generations; gen++) {

                evaluateFitness();

                int parent1=-1;

                int parent2=-1;

                selectParents(parent1,parent2);

               
               vector<int> child(numCities,-1);

               fill(child.begin(),child.end(),-1);

                crossover(parent1,parent2,child);

                mutate(child);

                int worstIndex=0;

                for(int i=1; i<populationSize; i++){

                    if (fitness[i]<fitness[worstIndex]) {

                        worstIndex=i;

                    }


                }
                population[worstIndex]=child;

            
                 
               
            }
     }

     

      void GeneticAlgorithmTSP::printBestCost() {

            double bestCost = 10000000;

            for (int i = 0; i < populationSize; i++) {

                double cost = calculateCost(population[i]);

                if (cost < bestCost) {

                    bestCost = cost;
                    bestTour = population[i];

                }

            }
            cout << "Best TSP Cost: " << bestCost << endl;

        }


         void GeneticAlgorithmTSP::printBestTour() {

            cout<<"Best TSP TOUR: ";

            for (int i=0; i<bestTour.size(); i++) {

                cout<<bestTour[i]<<" ";

                
            }
            cout<<"Cost for this tour: "<<calculateCost(bestTour)<<endl;

            cout<<endl;
        }