#pragma once

#include <iostream>
#include "Eigen/QR"
#include <vector>
#include <cmath>
#include "R64M.hpp"
#include "Functions.h"

using namespace std;
/**
@brief Useful (vector, vector), (matrix, vector) and (vector, scalar) operations.
*/
vector<double> operator-(vector<double> x, vector<double> y);

vector<double> operator-(vector<double> x);

vector<double> operator+(vector<double> x, vector<double> y);

vector<double> operator*(vector<vector<double>> a, vector<double> y);

vector<double> operator*(double c, vector<double> x);

/**
@brief Computes Euclid's norm of a given vector
*/
double norm(vector<double> x);
/**
@brief Dummy function
*/
double f_0(vector<double>& x);

/**
@brief Class containing information about the given rectangular area.
*/
class Area {
public:
	int dim;
	vector<double> left_borders;
	vector<double> right_borders;
	/**
	@brief Answers the question "is the point x in this area?"
	*/
	bool is_in(vector<double> x);
	/**
	@brief Constructor
	@param lefts contains left borders of the rectangular area
	@param rights contains right borders of the rectangular area
	*/
	Area(vector<double> lefts, vector<double> rights) : left_borders(lefts), right_borders(rights),
		dim(rights.size() == lefts.size() ? rights.size() : 0) {}
};