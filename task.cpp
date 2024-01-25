#include "task.h"


void WorkFile::openFile(const std::string& fileName) {
	f = fopen(fileName.c_str(), "r");
}

void WorkFile::parseFile() {
	float point_x, point_y;
	int count;
	while ((count = fscanf(f, "(%f, %f)\n", &point_x, &point_y)) > 0){
		points.push_back({point_x, point_y});
	}
}

void WorkFile::closeFile() {
	fclose(f);
}

WorkFile::WorkFile(const std::string& fileName) {
	openFile(fileName);
	parseFile();
	closeFile();

}

WorkFile::WorkFile(const std::string& fileName, unsigned long long int maxWords) {
	openFile(fileName);
	parseFile();
	closeFile();
	while (points.size() > maxWords)
		points.pop_back();
}

double Matrix::getDeterminant(double** matrix, int count_row_col){
	if (count_row_col == 1)
		return **matrix;
	double** matrix2 = new double*[count_row_col-1];
	int isMinus = 1;
	long long int det = 0;
	for (int i = 0; i < count_row_col; i++){
		for (int row = 0; row < count_row_col-1; row++){
			matrix2[row] = new double[count_row_col-1];
			for (int col = 0, col2 = 0; col < count_row_col; col++){
				if (col != i)
					matrix2[row][col2++] = matrix[row+1][col];
			}
		}
		long long int det1 = getDeterminant(matrix2, count_row_col-1);
		det += matrix[0][i]*det1*isMinus;
		isMinus *= -1;
	}
	for (int row = 0; row < count_row_col-1; row++) delete [] matrix2[row];
	delete [] matrix2;

	return det;
}

std::vector<double> SolverLinearEq::solveByKramer(double** matrix, int count_eq){
	/*for (int j = 0; j < count_eq; j++){
		for (int l = 0; l < count_eq+1; ++l){
			std::cout << matrix[j][l] << "\t";
		}
		std::cout << std::endl;
	}*/
	Matrix mat;
	double** matrix_x = new double*[count_eq];
	double matrix_y[count_eq];
	for (int i = 0; i < count_eq; i++){
		matrix_x[i] = new double[count_eq];
		for (int j = 0; j < count_eq; j++){
			matrix_x[i][j] = matrix[i][j];
		}
		matrix_y[i] = matrix[i][count_eq];
		std::cout << matrix_y[i] << "\t";
	}
	std::cout << std::endl;
	std::vector<double> answer;
	int det = mat.getDeterminant(matrix_x, count_eq);
	std::cout << "\tDET :\t" << det << std::endl;
	for (int i = 0; i < count_eq; i++){
		for (int j = 0; j < count_eq; j++){
			if (i > 0)
				matrix_x[j][i-1] = matrix[j][i-1];
			matrix_x[j][i] = matrix_y[j];
		}
		/*for (int j = 0; j < count_eq; j++){
			for (int l = 0; l < count_eq; ++l){
				std::cout << matrix_x[j][l] << "\t";
			}
			std::cout << "\n" << std::endl;
		}*/
		double det1 = mat.getDeterminant(matrix_x, count_eq);
		answer.push_back(det1/det);
	}
	for (int i = 0; i < count_eq; i++) delete [] matrix_x[i];
	delete [] matrix_x;

	return answer;
}

/*
double Matrix::getDeterminant(double** matrix, int count_row_col){
	for (int i = 0; i < count_row_col*count_row_col; i++){
		std::cout << matrix[i] << "\t";
	}
	std::cout << "\n\n-----------------------------------------\n" << std::endl;
	if (count_row_col == 1)
		return *matrix;
	double matrix2[(count_row_col-1)*(count_row_col-1)];
	int isMinus = 1;
	int det = 0;
	for (int i = 0; i < count_row_col; ++i){
		for (int j = count_row_col, m2 = 0; j < count_row_col*count_row_col; j++){
			if ((j-i)/count_row_col*count_row_col != (j-i)){
				matrix2[m2] = matrix[j];
				m2++;
			}
		}
		int det1 = getDeterminant(&matrix2[0], count_row_col-1);
		det += matrix[i]*det1*isMinus;
		isMinus *= -1;
	}
	return det;
}

std::vector<double> SolverLinearEq::solveByKramer(const double* matrix, int count_eq){
	for (int i = 0; i < count_eq*count_eq; i++){
		std::cout << matrix[i] << "\t";
	}
	std::cout << "\n\n-----------------------------------------\n" << std::endl;
	Matrix mat;
	double matrix_x[count_eq*count_eq];
	double matrix_y[count_eq];
	for (int i = 0, m1 = 0; i < count_eq*(count_eq+1); ++i){
		if ((i+1)/(count_eq+1)*(count_eq+1) == (i+1)){
			matrix_y[(i+1)/(count_eq+1)-1] = matrix[i];
			continue;
		}
		matrix_x[m1] = matrix[i];
		m1++;
	}
	std::vector<double> answer;
	int det = mat.getDeterminant(matrix_x, count_eq);
	std::cout << "\tDET :\t" << det << std::endl;
	for (int i = 0; i < count_eq; i++){
		double matrix_temp[count_eq*count_eq];
		for (int j = 0; j < count_eq*count_eq; j++){
			if ((j-i)/count_eq*count_eq == (j-i)){
				matrix_temp[j] = matrix_y[(j-i)/count_eq];
				continue;
			}
			matrix_temp[j] = matrix_x[j];
		}
		double det1 = mat.getDeterminant(matrix_temp, count_eq);
		answer.push_back(det1/det);
	}
	return answer;
}

disp i
disp j
disp matrix[i]
disp matrix2[m2]
disp matrix_temp[j]

matrix2[row][col2]
matrix[row+1][col]
*/