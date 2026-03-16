# DSA2Project3
Repository for Project 3 in DSAII


PROJECT 3: GENETIC AND BRUTE FORCE ALGORITHMS FOR TSP PROBLEM

The program created for project 3 serves to solve the TSP problem in two different ways to showcase the ways in which algorithms
can solve extremely complex problems in ways that will not take as long
The problem here boils down to trying to travel from one city to every other city once and back to the first city.
This problem seems simple but can be of factorial complexity if done in the brute force way.
The brute force method simply makes every possible "tour" or vector of cities in order of how the salesman travels
but this method starts to become unmanageble for time on computers after around 13 on my current PC
The solution to find good routes in this case is generative algorithms that iterate generations of tours that are tested to find the best 
ones then modified to eventually create the best tours possible from the population

For USER INTERACTION
STEPS TO RUN 
step 1: Load this folder into a linux environment
step 2: Navigating into the directory with the terminal once inside you can run the "make main" command to generate the executables for the program to run
step 3: simply type into the terminal "./main" to run the program, this is a hands off program that only requires you to start it as it will finsh on its own