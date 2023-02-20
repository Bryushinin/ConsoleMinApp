#pragma once

#include <vector>
#include <cmath>

using namespace std;
/**
@brief Class implementing computing of function's value, gradient and Gesse's matrix in the given point.
@detailed There are three hardcoded functions. The user is choosing one of them, implementation involved polymorphism.
*/
class Function {
public:
	/**
	@brief Computes function's value in the given point.
	@param x is the given point
	@return  Function's value
	*/
	virtual double eval(vector<double> x);
	/**
	@brief Computes function's gradient in the given point.
	@param x is the given point
	@return  Function's gradient
	*/
	virtual vector<double> eval_gr(vector<double> x);
	/**
	@brief Computes function's Gesse's matrix in the given point.
	@param x is the given point
	@return  Function's Gesse's matrix
	*/
	virtual vector<vector<double>> eval_Gesse(vector<double> x);
};
/**
@brief f(x, y) = sin(x)*cos(y)
*/
class Function_1 : public Function {
public:
	/**
	@brief Computes function's value in the given point.
	@param x is the given point
	@return  Function's value
	*/
	double eval(vector<double> x) { return sin(x[0]) * cos(x[1]); };
	/**
	@brief Computes function's gradient in the given point.
	@param x is the given point
	@return  Function's gradient
	*/
	vector<double> eval_gr(vector<double> x);
	/**
	@brief Computes function's Gesse's matrix in the given point.
	@param x is the given point
	@return  Function's Gesse's matrix
	*/
	vector<vector<double>> eval_Gesse(vector<double> x);
};

/**
@brief f(x, y) = 20*exp(sin((x+y)/20))+xy
*/
class Function_2 : public Function {
public:
	/**
	@brief Computes function's value in the given point.
	@param x is the given point
	@return  Function's value
	*/
	double eval(vector<double> x) { return 20. * exp(sin((x[0] + x[1]) / 20.)) + x[0] * x[1]; };
	/**
	@brief Computes function's gradient in the given point.
	@param x is the given point
	@return  Function's gradient
	*/
	vector<double> eval_gr(vector<double> x);
	/**
	@brief Computes function's Gesse's matrix in the given point.
	@param x is the given point
	@return  Function's Gesse's matrix
	*/
	vector<vector<double>> eval_Gesse(vector<double> x);
};


/**
@brief f(x, y) = (1-x)^2 + 100(y-x^2)^2
*/
class Function_3 : public Function {
public:
	/**
	@brief Computes function's value in the given point.
	@param x is the given point
	@return  Function's value
	*/
	double eval(vector<double> x) { return (1. - x[0]) * (1. - x[0]) + 100. * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]); };
	/**
	@brief Computes function's gradient in the given point.
	@param x is the given point
	@return  Function's gradient
	*/
	vector<double> eval_gr(vector<double> x);
	/**
	@brief Computes function's Gesse's matrix in the given point.
	@param x is the given point
	@return  Function's Gesse's matrix
	*/
	vector<vector<double>> eval_Gesse(vector<double> x);
};

/**
@brief f(x, y, z) = sin(x)*(y^2+1) - z*cos(x)
*/
class Function_4 : public Function {
public:
	/**
	@brief Computes function's value in the given point.
	@param x is the given point
	@return  Function's value
	*/
	double eval(vector<double> x) { return sin(x[0]) * (x[1]*x[1] + 1) - x[2] * cos(x[0]); };
	/**
	@brief Computes function's gradient in the given point.
	@param x is the given point
	@return  Function's gradient
	*/
	vector<double> eval_gr(vector<double> x);
	/**
	@brief Computes function's Gesse's matrix in the given point.
	@param x is the given point
	@return  Function's Gesse's matrix
	*/
	vector<vector<double>> eval_Gesse(vector<double> x);
};

/**
@brief f(x, y, z, w) = x^2 * y^2 * w + x^2 * z * w - z * w^2
*/
class Function_5 : public Function {
public:
	/**
	@brief Computes function's value in the given point.
	@param x is the given point
	@return  Function's value
	*/
	double eval(vector<double> x) { return x[0]*x[0]*x[1]*x[1]*x[3] + x[0]*x[0]*x[2]*x[3] - x[2]*x[3]*x[3]; };
	/**
	@brief Computes function's gradient in the given point.
	@param x is the given point
	@return  Function's gradient
	*/
	vector<double> eval_gr(vector<double> x);
	/**
	@brief Computes function's Gesse's matrix in the given point.
	@param x is the given point
	@return  Function's Gesse's matrix
	*/
	vector<vector<double>> eval_Gesse(vector<double> x);
};