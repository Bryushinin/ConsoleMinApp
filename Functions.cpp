#include "Functions.h"

double Function::eval(vector<double> x) {
	double s = 0;
	for (size_t i = 0; i < x.size(); ++i)
		s += x[i] * x[i] / 2.;
	return s;
};

vector<double> Function::eval_gr(vector<double> x)
{
	/*vector<double> y; y.clear();
	for (size_t i = 0; i < x.size(); ++i)
		y.push_back(0.);
	y[0] = 1;*/
	return x;
}

vector<vector<double>> Function::eval_Gesse(vector<double> x)
{
	vector<vector<double>> y; y.clear();
	for (size_t i = 0; i < x.size(); ++i)
	{
		vector<double> t; t.clear();
		y.push_back(t);
		for (size_t j = 0; j < x.size(); ++j)
			y[i][j] = 0;
		y[i][i] = 1;
	}
	return y;
}

vector<double> Function_1::eval_gr(vector<double> x)
{
	vector<double> y; y.clear();
	for (size_t i = 0; i < x.size(); ++i)
		y.push_back(0.);
	y[0] = cos(x[0]) * cos(x[1]);
	y[1] = -sin(x[0]) * sin(x[1]);
	return y;
}

vector<vector<double>> Function_1::eval_Gesse(vector<double> x)
{
	vector<vector<double>> y; y.clear();
	for (size_t i = 0; i < x.size(); ++i)
	{
		vector<double> t; t.clear();
		y.push_back(t);
		for (size_t j = 0; j < x.size(); ++j)
			y[i].push_back(0.);
	}
	y[0][0] = y[1][1] = -sin(x[0]) * cos(x[1]);
	y[0][1] = y[1][0] = -cos(x[0]) * sin(x[1]);
	return y;
}

vector<double> Function_2::eval_gr(vector<double> x)
{
	vector<double> y; y.clear();
	for (size_t i = 0; i < x.size(); ++i)
		y.push_back(0.);
	y[0] = cos((x[0] + x[1]) / 20.) * exp(sin((x[0] + x[1]) / 20.)) + x[1];
	y[1] = cos((x[0] + x[1]) / 20.) * exp(sin((x[0] + x[1]) / 20.)) + x[0];
	return y;
}
vector<vector<double>> Function_2::eval_Gesse(vector<double> x)
{
	vector<vector<double>> y; y.clear();
	for (size_t i = 0; i < x.size(); ++i)
	{
		vector<double> t; t.clear();
		y.push_back(t);
		for (size_t j = 0; j < x.size(); ++j)
			y[i].push_back(0.);
	}
	y[0][0] = y[1][1] = exp(sin((x[0] + x[1]) / 20.)) * (cos((x[0] + x[1]) / 20.) * cos((x[0] + x[1]) / 20.) - sin((x[0] + x[1]) / 20.)) / 20.;
	y[0][1] = y[1][0] = y[0][0] + 1;
	return y;
}

vector<double> Function_3::eval_gr(vector<double> x)
{
	vector<double> y; y.clear();
	for (size_t i = 0; i < x.size(); ++i)
		y.push_back(0.);
	y[0] = -2. * (1 - x[0]) - 400. * x[0] * (x[1] - x[0] * x[0]);
	y[1] = 200. * (x[1] - x[0] * x[0]);
	return y;
}
vector<vector<double>> Function_3::eval_Gesse(vector<double> x)
{
	vector<vector<double>> y; y.clear();
	for (size_t i = 0; i < x.size(); ++i)
	{
		vector<double> t; t.clear();
		y.push_back(t);
		for (size_t j = 0; j < x.size(); ++j)
			y[i].push_back(0.);
	}
	y[0][0] = 2. - 400. * x[1] + 1200. * x[0] * x[0];
	y[0][1] = y[1][0] = -400. * x[0];
	y[1][1] = 200.;
	return y;
}