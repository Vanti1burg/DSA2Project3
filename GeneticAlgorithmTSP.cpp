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

//constructor for class, sets the initlial parameters and creates initial population by 
//creating random tours of numbers from 1 to num cities with city 0 as the starting point for all tours

 GeneticAlgorithmTSP::GeneticAlgorithmTSP(int n, double mutRate, int popSize) : numCities(n) {

            mutationRate=mutRate;

            populationSize=popSize;

            population.resize(populationSize, vector<int>(numCities));

            for (int i = 0; i < populationSize; i++) {
                population[i][0] = 0;
                for (int j = 1; j < numCities; j++) {

                    population[i][j] = j;

                }

           //shuffle the cities in the tour to create random mixing of tours for intital population

                random_shuffle(population[i].begin() + 1, population[i].end()); 
            }
            // resize the fitness vector to the appropriate population size

                fitness.resize(populationSize);

        }

 void GeneticAlgorithmTSP::readDistances() {
    //readDistance file thats identical to the one used for brute force algorithm
    //just in two different classes

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

    //calculate cost function similar to the one in the BF algorithm
    
    double GeneticAlgorithmTSP:: calculateCost(const vector<int>& tour) {

        
        double cost=0;

        for (int i=0; i<numCities-1; i++) {

            cost+=distances[tour[i]][tour[i+1]];

        }

        cost+=distances[tour[numCities-1]][tour[0]];

        return cost;
    }

    //selects parents for crossover based on fitness values, uses pseudo random selection weighted by fitness
    //higher fitness means higher chance of being a parent

 void GeneticAlgorithmTSP:: selectParents(int& parent1, int& parent2) {
          
           double totalFitness=0;
    // from 0 to population size, add up all fitness values 
            for(int i=0; i<populationSize;i++){
                totalFitness+=fitness[i];

            }
            //picks the two parents from the population based on fitness values to create weighted chance for selction
              double pick1=((double)rand()/RAND_MAX)*totalFitness;

              double pick2=((double)rand()/RAND_MAX)*totalFitness;

             double current=0;
            //loop through population and add up fitness values until we find the first and second parent based on pick values
             for(int i=0;populationSize;i++){

                current+=fitness[i];

                if(current>pick1 && parent1==-1){
                    parent1=i;
                }

                if (current>pick2 && parent2==-1) {

                    parent2=i;

                }
                //find both parents and break loop
                if (parent1!=-1 && parent2!=-1){ 
                    break;
                }
             }
  }


    //evaluates the fitness of each tour in population by taking inverse of cost
  
  void GeneticAlgorithmTSP::evaluateFitness() {

          for(int i=0; i<populationSize; i++) {

            fitness[i]=1.0/calculateCost(population[i]);

          }
  }

    //crossover method to create a "child" tour from two parents tours

  void GeneticAlgorithmTSP::crossover(int parent1, int parent2, vector<int>& child) {

    //makes sure the starting city is 0

    child[0] = 0;

    //keeps track of the cities that have been added already so we dont get repeating cities 

    vector<bool> inChild(numCities, false);

    //mark city 0 as true since we already set it

    inChild[0] = true; 

    //randomly select start and end point from parent 1 for crossover

    int start = 1 + rand() % (numCities - 1);
    //rnadomly select end point from parent1 for crossover, ensure end point is after start point

    int end = 1 + rand() % (numCities - 1);


    if (start > end) swap(start, end);

   //copy the segment to the child tour and mark those cities as already have been added
    for (int i = start; i <= end; i++) {

        child[i] = population[parent1][i];

        inChild[child[i]] = true;

    }

   //fill the remaining cities from the second parent as long as they havent already been added 
    int index = 1;
    
    for (int i = 1; i < numCities; i++) {

        if (!inChild[population[parent2][i]]) {
            //finds next open spot 
            while (index <= numCities - 1 && child[index] != -1) index++;

            if (index <= numCities - 1) {

                child[index] = population[parent2][i];

                inChild[child[index]] = true;

            }
        }
    }
  }


//mutation method to make random changes to the child tour by swapping two cities

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

//genetic algorithm method that runs for a given number of generations

void GeneticAlgorithmTSP::geneticAlgo(int generations) {

           
    //generation loop, for each generation we evaluate fitness, select parents,create a child through crossover and if
    //its better than the worst tour in population we replace the worst tour with the child tour, this helps 
    //weed out bad tours
            for(int gen=0; gen<generations; gen++) {

                evaluateFitness();

                int parent1=-1;

                int parent2=-1;
                //select the parents for crossover 
                selectParents(parent1,parent2);

            //create a child tour through 
               vector<int> child(numCities,-1);
            
               //fill the child with -1 to show that cities havent been added yet

               fill(child.begin(),child.end(),-1);

                //create child tour through the crossover of parents

                crossover(parent1,parent2,child);

                //mutate the child tour to add some possible random changes

                mutate(child);

                int worstIndex=0;

                for(int i=1; i<populationSize; i++){

                    if (fitness[i]<fitness[worstIndex]) {

                        worstIndex=i;
                        //find worst tour

                    }


                }
                //replace worst tour with child 
                if (calculateCost(child)<calculateCost(population[worstIndex])) {
                population[worstIndex]=child;

            
                }
               
            }
     }

     
//printing function for terminal output of the best cost found from the genetic algorithm
//sets best cost to a very high number then loops through population to find best tour
      void GeneticAlgorithmTSP::printBestCost() {

            double bestCost = 10000000;

            for (int i = 0; i < populationSize; i++) {

                double cost = calculateCost(population[i]);

                if (cost < bestCost) {

                    bestCost = cost;
                    bestTour = population[i];

                }

            }
            bestCostReturn=bestCost;
            cout << "Best TSP Cost: " << bestCost << endl;

        }

//prints best tour
         void GeneticAlgorithmTSP::printBestTour() {

            cout<<"Best TSP TOUR: ";

            for (int i=0; i<bestTour.size(); i++) {

                cout<<bestTour[i]<<" ";

                
            }
            cout<<"Cost for this tour: "<<calculateCost(bestTour)<<endl;

            cout<<endl;
        }

    double GeneticAlgorithmTSP::getBestCost() {
        
           return bestCostReturn;

    }