CXX = g++
CXXFLAGS = -g -Wall

TARGET = main
OBJECTS = main.o BruteForceTSP.o GeneticAlgorithmTSP.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.cpp BruteForceTSP.hpp GeneticAlgorithmTSP.hpp

	$(CXX) $(CXXFLAGS) -c main.cpp

BruteForceTSP.o: BruteForceTSP.cpp BruteForceTSP.hpp

	$(CXX) $(CXXFLAGS) -c BruteForceTSP.cpp

GeneticAlgorithmTSP.o: GeneticAlgorithmTSP.cpp GeneticAlgorithmTSP.hpp

	$(CXX) $(CXXFLAGS) -c GeneticAlgorithmTSP.cpp
	
run: $(TARGET)

	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)