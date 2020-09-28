#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;
int main (int argc, char **argv){
	string inputFile = argv[1],
			  outputFile = argv[2];

	double values[9], value, count, countA;

	fstream inFile, outFile;

	cout << "Caculating average values from: " << inputFile.c_str() << " to: " << outputFile.c_str();
	cout << endl;

	inFile.open(inputFile.c_str(), fstream::in);
	outFile.open(outputFile.c_str(), fstream::out | fstream::app);

	assert(inFile.is_open());
	assert(outFile.is_open());

	for (int i = 0; i < 9; i++)
		values[i] = 0.0f;
	count = 0.0f;
	countA = 0.0f;
	while(!inFile.eof()){
		for (int i = 0; i < 9; i++){
			inFile >> value;
			values[i] += value;
			if (i == 6){
				if (fabs(value) > 0.00000001f)
					countA++;
			}
			value = 0.0f;

		}
		if (!inFile.eof())
			count++;
	}

	for (int i = 0; i < 9; i++){
			if (i == 6)
				outFile << values[i] / countA << " ";
			else
				outFile << values[i] / count << " ";
	}
	outFile << endl;
	inFile.close(); outFile.close();



	return EXIT_SUCCESS;
}
