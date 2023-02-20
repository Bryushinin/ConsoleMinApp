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

vector<double> Function_4::eval_gr(vector<double> x)
{
	vector<double> y; y.clear();
	for (size_t i = 0; i < x.size(); ++i)
		y.push_back(0.);
	y[0] = cos(x[0])*(x[1]*x[1]+1) + x[2]*sin(x[0]);
	y[1] = 2*x[1]*sin(x[0]);
	y[2] = -cos(x[0]);
	return y;
}
vector<vector<double>> Function_4::eval_Gesse(vector<double> x)
{
	vector<vector<double>> y; y.clear();
	for (size_t i = 0; i < x.size(); ++i)
	{
		vector<double> t; t.clear();
		y.push_back(t);
		for (size_t j = 0; j < x.size(); ++j)
			y[i].push_back(0.);
	}
	y[0][0] = -sin(x[0]) * (x[1] * x[1] + 1) + x[2] * cos(x[0]);
	y[0][1] = y[1][0] = 2 * x[1] * cos(x[0]);
	y[1][1] = 2 * sin(x[0]);
	y[0][2] = y[2][0] = sin(x[0]);
	return y;
}

vector<double> Function_5::eval_gr(vector<double> x)
{
	vector<double> y; y.clear();
	for (size_t i = 0; i < x.size(); ++i)
		y.push_back(0.);
	y[0] = 2 * x[0] * x[1] * x[1] * x[3] + 2 * x[0] * x[2] * x[3];
	y[1] = 2 * x[0] * x[0] * x[1] * x[3];
	y[2] = x[0] * x[0] * x[3] - x[3] * x[3];
	y[3] = x[0] * x[0] * x[1] * x[1] + x[0] * x[0] * x[2] - 2 * x[2] * x[3];
	return y;
}

vector<vector<double>> Function_5::eval_Gesse(vector<double> x)
{
	vector<vector<double>> y; y.clear();
	for (size_t i = 0; i < x.size(); ++i)
	{
		vector<double> t; t.clear();
		y.push_back(t);
		for (size_t j = 0; j < x.size(); ++j)
			y[i].push_back(0.);
	}
	y[0][0] = 2 * x[1] * x[1] * x[3] + 2 * x[2] * x[3];
	y[0][1] = y[1][0] = 4 * x[1] * x[0] * x[3];
	y[1][1] = 2 * x[0] * x[0] * x[3];
	y[0][2] = y[2][0] = 2 * x[0] * x[3];
	y[0][3] = y[3][0] = 2 * x[0] * x[1] * x[1] + 2 * x[0] * x[2];
	y[1][3] = y[3][1] = 2 * x[0] * x[0] * x[1];
	y[2][3] = y[3][2] = x[0] * x[0] - 2 * x[3];
	y[3][3] = -2 * x[2];
	return y;
}