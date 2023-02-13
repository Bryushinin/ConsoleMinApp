#pragma once

#include <iostream>
#include <vector>
#include "Functions.h"
#include "Definitions.h"

using namespace std;
/**
@brief Class containing a criterion with which iterations are being stopped.
@detailed There are three of them. They are implemented using polymorphism.
*/
class StopCriterion {
protected:
	int bound;
public:
	double eps;
	/**
	@brief Main function
	@param a contains the trajectory of iterations
	@param F is a function that is being minimized
	@return true if iterations are to be stopped, false otherwise
	*/
	virtual bool do_we_stop(vector<vector<double>>& a, Function* F, int iteration_number) { return true; };
	/**
	@brief Constructor
	@param bo is the upper bound of iterations number
	*/
	StopCriterion(double ep = 0.001, int bo = 1000) : eps(ep), bound(bo) {}
};
/**
@brief Class that stops iterations if the norm of the gradient in the current point is less than eps
*/
class SC_GradientNorm : public StopCriterion {
	/**
	@brief Main function
	@param a contains the trajectory of iterations
	@param F is a function that is being minimized
	@return true if iterations are to be stopped, false otherwise
	*/
	bool do_we_stop(vector<vector<double>>& a, Function* F, int iteration_number);
};
/**
@brief Class that stops iterations if the norm of the difference between current and previous points are less than eps
*/
class SC_PointsClose : public StopCriterion {
	/**
	@brief Main function
	@param a contains the trajectory of iterations
	@param F is a function that is being minimized
	@return true if iterations are to be stopped, false otherwise
	*/
	bool do_we_stop(vector<vector<double>>& a, Function* F, int iteration_number);
};
/**
@brief Class that stops iterations if the absolute difference between current and previous values related to the current value is less than eps
*/
class SC_FuncRelative : public StopCriterion {
	/**
	@brief Main function
	@param a contains the trajectory of iterations
	@param F is a function that is being minimized
	@return true if iterations are to be stopped, false otherwise
	*/
	bool do_we_stop(vector<vector<double>>& a, Function* F, int iteration_number);
};