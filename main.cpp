#include <iostream>
#include "task.h"

std::string makeEqByCoef(std::vector<double> coef){
	std::string equation = "y=";
	int i = 0;
	for (auto& value: coef){
		std::cout << value << std::endl;
		if (i != 0 && value >= 0)
			equation += "+";
		equation += std::to_string(value) + "*x^" + std::to_string(i);
		i += 1;
	}
	return equation;
}

void makeSystemEq(double**& systemEq, int countEq, const char* fileName){
	WorkFile workFile(fileName);
	std::vector<std::pair<double, double>> points = workFile.getPoints();
	double** eqSystem = new double*[countEq];
	for (int d = 0; d <= 2*(countEq-1); d++){
		double sumDegreeX = 0;
		double sumDegreeXY = 0;
		for (auto& [x, y]: points){
			sumDegreeX += std::pow(x, d);
			sumDegreeXY += std::pow(x, d)*y;
		}
        for (int i = 0; i < d+1 && i < countEq; i++){
            if (d-i < countEq)
                systemEq[i][d-i] = sumDegreeX;
        }
        if (d < countEq)
        	systemEq[d][countEq] = sumDegreeXY;
	}
}

int main(int argc, const char* argv[]){
	Matrix matrix;
	int size = 4;/*
	double staticMatrix[size][size+1] = {
		{2, 2, 10},
		{3, -6, 11}
	};
	double staticMatrix[size][size+1] = {
		{10,      5,       85,      125,	86},
		{5,   85,      125,     1333,	102},
		{85,      125,     1333,    3125,	1284},
		{125,     1333,    3125,    25405,	2868}
	};


	/*double fMatrix[size][size+1] = {
		{2, 3, -8, 6},
		{-10, 7, -1, 2},
		{5, 9, -2, -4}
	};
	double fMatrix[size][size+1] = {
		{-2, 9, 5, -4},
		{-1, 7, -10, 2},
		{-8, 3, 2, 6}
	};
    double** fMatrix = new double*[size];
    for (int i = 0; i < size; ++i){
        fMatrix[i] = new double[size+1];
        for (int j = 0; j < size+1; j++){
            fMatrix[i][j] = staticMatrix[i][j];
            std::cout << fMatrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
	std::cout << matrix.getDeterminant(fMatrix, size) << std::endl;
	SolverLinearEq s;
	for (auto value : s.solveByKramer(fMatrix, size)){
		std::cout << value << std::endl;
	}*/

	WorkFile workFile("test.txt");
	std::vector<std::pair<double, double>> points = workFile.getPoints();
	for (auto& [x, y]: points){
		std::cout << x << "\t" << y << std::endl;
	}


	int countEq = atoi(argv[1]);
	double** eqSystem = new double*[countEq];
	for (int i = 0; i < countEq; i++){
		eqSystem[i] = new double[countEq+1];
		for (int j = 0; j < countEq+1; j++){
			eqSystem[i][j] = 0;
		}
	}

	for (int i = 0; i < countEq; i++){
		for (int j = 0; j < countEq+1; j++){
			std::cout << eqSystem[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	makeSystemEq(eqSystem, countEq, "test.txt");

	for (int i = 0; i < countEq; i++){
		for (int j = 0; j < countEq+1; j++){
			std::cout << eqSystem[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	SolverLinearEq s;
	std::cout << makeEqByCoef(s.solveByKramer(eqSystem, countEq)) << std::endl;

	for (int i = 0; i < countEq; i++){
		delete [] eqSystem[i];
	}
	delete [] eqSystem;

	return 0;
}