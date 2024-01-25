#ifndef _task_h_
#define _task_h_
#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>

class WorkFile{
	private:
		FILE* f;
		std::vector<std::pair<double, double>> points;
		void openFile(const std::string& fileName);
		void parseFile();
		void closeFile();
	public:
		WorkFile() = delete;
		WorkFile(const std::string& fileName);
		WorkFile(const std::string& fileName, unsigned long long int maxWords);
		~WorkFile() { };
		const std::vector<std::pair<double, double>> getPoints() const {return points;};
};

class MNK{
	public:
		MNK();
		~MNK();
};

class Matrix{
	public:
		double getDeterminant(double** matrix, int count_row_col);
		Matrix(){};
		~Matrix(){};
	
};
class SolverLinearEq{
	public:
		std::vector<double> solveByKramer(double** matrix, int count_eq);
		SolverLinearEq(){};
		~SolverLinearEq(){};
	
};

#endif