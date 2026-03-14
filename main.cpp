#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>

using namespace std;


class BruteForceTSP {
    private:

        const int MAX_CITIES =20;
        double distances[20][20];
        //makes array that can store all necessary distances from file


    public:
//reads the distances from the entire file and makes the adjacency matrix for problem
    void readDistances() {


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

    double calculateCost(int tour[], int n) {

        double cost=0;

        for (int i=0; i<n-1; i++) {

            cost+=distances[tour[i]][tour[i+1]];

        }

        cost+=distances[tour[n-1]][tour[0]];

        return cost;
    }

    bool perm1(int s[], int numElements) {

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
    double bruteForce(int n) {
        int tour[20];
        for (int i=0; i<n;i++){
            tour[i]=i;
        }
        double minCost=calculateCost(tour,n);
        while(perm1(tour,n)) {
            double cost=calculateCost(tour,n);
            if (cost<minCost) {
                minCost=cost;
            }

        }
        return minCost;
    }
        
};
//still need to implement ga
class GeneticAlgorithmTSP{};






int main () {
    cout<<"Hello World!" <<endl;
    cout<<"Brute Force Method: "<<endl;
    BruteForceTSP bForceSolver;
    bForceSolver.readDistances();
  
    cout<<"Minimum TSP Cost: "<<bForceSolver.bruteForce(10) <<endl;
    return 0;
}