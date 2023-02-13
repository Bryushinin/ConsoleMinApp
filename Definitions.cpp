#include "Definitions.h"

vector<double> operator-(vector<double> x, vector<double> y)
{
	int len = x.size();
	if (len != y.size())
		return x;
	for (int i = 0; i < len; ++i)
		x[i] -= y[i];
	return x;
}

vector<double> operator-(vector<double> x)
{
	int len = x.size();
	for (int i = 0; i < len; ++i)
		x[i] = -x[i];
	return x;
}

vector<double> operator+(vector<double> x, vector<double> y)
{
	return x - (-y);
}

vector<double> operator*(vector<vector<double>> a, vector<double> y)
{
	int len = a[0].size();
	if (len != y.size())
		return y;
	vector<double> x;
	for (int i = 0; i < len; ++i)
	{
		double s = 0;
		for (int j = 0; j < len; ++j)
		{
			s += a[i][j] * y[j];
		}
		x.push_back(s);
	}
	return x;
}

vector<double> operator*(double c, vector<double> x)
{
	int len = x.size();
	for (int i = 0; i < len; ++i)
		x[i] *= c;
	return x;
}



double norm(vector<double> x)
{
	double s = 0;
	int len = x.size();
	for (int i = 0; i < len; ++i)
		s += x[i] * x[i];
	return sqrt(s);
}

double f_0(vector<double>& x)
{
	return x[1];
}



bool Area::is_in(vector<double> x)
{
	if (dim != x.size())
		return false;
	bool f = true;
	for (int i = 0; i < dim; ++i)
		if (x[i] < left_borders[i] || x[i] > right_borders[i])
			f = false;
	return f;
}