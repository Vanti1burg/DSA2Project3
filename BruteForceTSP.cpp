#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include "BruteForceTSP.hpp"
using namespace std;

   void BruteForceTSP:: readDistances() {


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




     double BruteForceTSP::calculateCost(int tour[], int n) {

        double cost=0;

        for (int i=0; i<n-1; i++) {

            cost+=distances[tour[i]][tour[i+1]];

        }

        cost+=distances[tour[n-1]][tour[0]];

        return cost;
    }




     bool BruteForceTSP:: perm1(int s[], int numElements) {

        int m= numElements-2;

        while(m>=0 && s[m]>s[m+1]) {

            m=m-1;

        }

        if (m<0){

            return false;

        };

        int k=numElements-1;

        while(s[m]>s[k]) {

            k=k-1;

        }

        swap (s[m],s[k]);

        int p = m+1;

        int q = numElements-1;

        while(p<q) {

            swap(s[p],s[q]);

            p++;

            q--;

        }

        return true;
    }





    double BruteForceTSP:: bruteForce(int n) {

        int tour[20];

        tour[0] = 0;

        for (int i = 1; i < n; i++) {

            tour[i] = i;

        }
        double minCost = calculateCost(tour, n);

        bestTour = vector<int>(tour, tour + n);

        
        while (perm1(tour + 1, n - 1)) {

            double cost = calculateCost(tour, n);

            if (cost < minCost) {

                minCost = cost;

                bestTour = vector<int>(tour, tour + n);

            }
        }

        return minCost;
    }


     void BruteForceTSP::printBestTour() {

        cout<<"Best TSP TOUR: ";

        for (int i=0; i<bestTour.size(); i++) {

            cout<<bestTour[i]<<" ";

            
        }
        cout<<"Cost for this tour: "<< calculateCost(bestTour.data(), bestTour.size())<<endl;
        
        cout<<endl;
    }