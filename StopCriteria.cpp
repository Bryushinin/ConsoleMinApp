#include "StopCriteria.h"

bool SC_GradientNorm::do_we_stop(vector<vector<double>>& a, Function* F, int iteration_number)
{
	if (iteration_number >= bound && out)
		*out << " !!! There were more than " << bound << " iterations\n";
	bool res = norm(F->eval_gr(a[iteration_number])) < eps || iteration_number >= bound;
	if (res && out)
		*out << "There were " << iteration_number << " iterations\n";
	return res;
};


bool SC_PointsClose::do_we_stop(vector<vector<double>>& a, Function* F, int iteration_number)
{
	if (iteration_number >= bound && out)
		*out << " !!! There were more than " << bound << " iterations\n";
	if (iteration_number > 1)
	{
		bool res = norm(a[iteration_number] - a[iteration_number - 1]) < eps || iteration_number >= bound;
		if (res && out)
			*out << "There were " << iteration_number << " iterations\n";
		return res;
	}
	else
		return false;
};


bool SC_FuncRelative::do_we_stop(vector<vector<double>>& a, Function* F, int iteration_number)
{
	if (iteration_number >= bound && out)
		*out << " !!! There were more than " << bound << " iterations\n";
	if (iteration_number > 1)
	{
		double f_x_n = F->eval(a[iteration_number]);
		bool res = abs((f_x_n - F->eval(a[iteration_number - 1])) / f_x_n) < eps || iteration_number >= bound;
		if (res && out)
			*out << "There were " << iteration_number << " iterations\n";
		return res;
	}
	else
		return false;
};