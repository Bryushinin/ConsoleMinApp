#pragma once
#include "Definitions.h"
#include "StopCriteria.h"
/**
@brief Optimizing class containing realization of determined or stochastic method.
@detailed Different methods are being applied using polymorphism.

*/
class OptimizationMethod {
public:
	Area D;
	Function* f;
	StopCriterion* SC;
	vector<double> x_0;
	double answer;
	/**
	@brief Constructor
	@param F is one of the hardcoded functions (see Functions.h for more)
	@param x_0_ starting point
	@param SC_var current variant of stop criterion (see StopCriteria.h for more)
	*/
	OptimizationMethod(Function* F, vector<double> x_0_, vector<double> l_border,
		vector<double> r_border, int SC_var = 1, double eps = 0.001);
	/**
	@brief Main function
	@return The point of last iteration
	*/
	virtual vector<double> optimize() { return x_0; };
};

/**
@brief Class containing Newton's optimization method
@detailed That involves computing Gesse's matrixes and gradients.
*/
class Newton : public OptimizationMethod {
public:
	vector<double> p_n;
	/**
	@brief Function that computes the best step length in the direction p_n
	@param x_n The point of current iteration
	@return The fraction of p_n with which the next iteration will be optimal
	*/
	double get_alpha_alt(vector<double> x_n);
	/**
	@brief Constructor
	@detailed See OptimizationMethod constructor for more
	*/
	Newton(Function* F, vector<double> x_0_, vector<double> l_border, vector<double> r_border, int SC_var = 1, double eps_ = 0.001) :p_n(), OptimizationMethod(F, x_0_, l_border, r_border, SC_var, eps_) {}
	vector<double> iteration(vector<double>& x_, double alpha){return x_ + alpha * p_n;}
	/**
	@brief Main function
	@return The point of last iteration
	*/
	vector<double> optimize();
};

/**
@brief Class containing stochastic optimization method
@detailed That involves finding random points in general area and locally.
*/
class Stochastic : public OptimizationMethod {
public:
	double alpha;
	double p;
	/**
	@brief Function computing the next iteration
	@param delta is the local square's rib length. Where local square is an area in which the local search will be done with the probability p
	*/
	vector<double> iteration(vector<double> x, double& delta);
	/**
	@brief Main function
	@return The point of last iteration
	*/
	vector<double> optimize();
	/**
	@brief Constructor
	@param alpha is delta's iterational multiplier
	@detailed See OptimizationMethod constructor for more
	*/
	Stochastic(Function* F, vector<double> x_0_, vector<double> l_border, vector<double> r_border,
		int SC_var = 1, double eps_ = 0.001, double alpha_ = 0.2, double p_ = 0.5) :
		alpha(alpha_), p(p_), OptimizationMethod(F, x_0_, l_border, r_border, SC_var, eps_) {}
};