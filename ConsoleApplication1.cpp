#include <iostream>
#include "Eigen/QR"
#include <vector>
#include <cmath>
#include "R64M.hpp"

using namespace std;

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

class Function {
public:
	virtual double eval(vector<double> x) {
		double s = 0;
		for (size_t i = 0; i < x.size(); ++i)
			s += x[i] * x[i] / 2.;
		return s;
	};
	virtual vector<double> eval_gr(vector<double> x)
	{
		/*vector<double> y; y.clear();
		for (size_t i = 0; i < x.size(); ++i)
			y.push_back(0.);
		y[0] = 1;*/
		return x;
	}
	virtual vector<vector<double>> eval_Gesse(vector<double> x)
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
};


class StopCriterion {
protected:
	int bound;
public:
	double eps;
	virtual bool do_we_stop(vector<vector<double>>& a, Function* F, int iteration_number) { return true; };
	StopCriterion(double ep = 0.001, int bo = 1000) : eps(ep), bound(bo) {}//todo
};

class SC_GradientNorm : public StopCriterion {
	//SC_GradientNorm() {}
	bool do_we_stop(vector<vector<double>>& a, Function* F, int iteration_number)
	{
		if (iteration_number >= bound)
			std::cout << " !!! There were more than " << bound << " iterations\n";
		bool res = norm(F->eval_gr(a[iteration_number])) < eps || iteration_number >= bound;
		if (res)
			std::cout << "There were " << iteration_number << " iterations\n";
		return res;
	};
};

class SC_PointsClose : public StopCriterion {
	//SC_PointsClose() {}
	bool do_we_stop(vector<vector<double>>& a, Function* F, int iteration_number)
	{
		if (iteration_number >= bound)
			std::cout << " !!! There were more than " << bound << " iterations\n";
		if (iteration_number > 1)
		{
			bool res = norm(a[iteration_number] - a[iteration_number - 1]) < eps || iteration_number >= bound;
			if (res)
				std::cout << "There were " << iteration_number << " iterations\n";
			return res;
		}
		else
			return false;
	};
};

class SC_FuncRelative : public StopCriterion {
	//SC_FuncRelative() {}
	bool do_we_stop(vector<vector<double>>& a, Function* F, int iteration_number)
	{
		if (iteration_number >= bound)
			std::cout << " !!! There were more than " << bound << " iterations\n";

		if (iteration_number > 1)
		{
			double f_x_n = F->eval(a[iteration_number]);
			bool res = abs((f_x_n - F->eval(a[iteration_number - 1])) / f_x_n) < eps || iteration_number >= bound;
			if (res)
				std::cout << "There were " << iteration_number << " iterations\n";
			return res;
		}
		else
			return false;
	};
};



class Area {
public:
	int dim;
	vector<double> left_borders;
	vector<double> right_borders;
	bool is_in(vector<double> x)
	{
		if (dim != x.size())
			return false;
		bool f = true;
		for (int i = 0; i < dim; ++i)
			if (x[i] < left_borders[i] || x[i] > right_borders[i])
				f = false;
		return f;
	}
	Area(vector<double> lefts, vector<double> rights) : left_borders(lefts), right_borders(rights), dim(rights.size() == lefts.size() ? rights.size() : 0) {}
};


class OptimizationMethod {
public:
	Area D;
	Function* f;
	StopCriterion* SC;
	vector<double> x_0;
	double answer;
	OptimizationMethod(Function* F, vector<double> x_0_, vector<double> l_border, vector<double> r_border, int SC_var = 1, double eps = 0.001) :f(F), x_0(x_0_), D(l_border, r_border), answer(F->eval(x_0_))
	{
		switch (SC_var)
		{
		case 1:
			SC = new SC_GradientNorm;
			SC->eps = eps;
			break;
		case 2:
			SC = new SC_PointsClose;
			SC->eps = eps;
			break;
		case 3:
			SC = new SC_FuncRelative;
			SC->eps = eps;
			break;
		default:
			break;
		}
	}
	virtual vector<double> optimize() { return x_0; };
};

class Newton : public OptimizationMethod {
public:
	vector<double> p_n;
	double get_alpha_alt(vector<double> x_n)
	{
		vector<vector<double>> t = f->eval_Gesse(x_n);
		vector<double> t1 = -(f->eval_gr(x_n));
		Eigen::Matrix2d A;
		Eigen::Vector2d b;
		A << t[0][0], t[0][1], t[1][0], t[1][1];
		b << t1[0], t1[1];
		Eigen::Vector2d x = A.colPivHouseholderQr().solve(b);
		//std::cout << endl<<"p_n " << x << endl;
		p_n.clear(); p_n.push_back(x[0]); p_n.push_back(x[1]);
		double alp = 0., step = 0.001, min_ = f->eval(x_n), alpha = 0.;
		while (alp < 1.)
		{
			alp += step;
			double t = f->eval(x_n + alp * p_n);
			if (t < min_ && D.is_in(x_n + alp * p_n))
			{
				min_ = t;
				alpha = alp;
			}
		}
		answer = min_;
		return alpha;
	}
	//double get_alpha(vector<double> x_n)
	//{
	//	vector<vector<double>> t = f->eval_Gesse(x_n);
	//	t = Opposite_mx(t);
	//	p_n = -(t * f->eval_gr(x_n));
	//	//std::cout << endl << "p_n " << p_n[0] <<"  "<<p_n[1] << endl;
	//	double alp = 0., step = 0.001, min_ = f->eval(x_n), alpha = 0.;
	//	while (alp < 1.)
	//	{
	//		alp += step;
	//		double t = f->eval(x_n + alp * p_n);
	//		if (t < min_ && D.is_in(x_n + alp * p_n))
	//		{
	//			min_ = t;
	//			alpha = alp;
	//		}
	//	}
	//	answer = min_;
	//	return alpha;
	//}
	Newton(Function* F, vector<double> x_0_, vector<double> l_border, vector<double> r_border, int SC_var = 1, double eps_ = 0.001) :p_n(), OptimizationMethod(F, x_0_, l_border, r_border, SC_var, eps_) {}
	vector<double> iteration(vector<double>& x_, double alpha)
	{
		return x_ + alpha * p_n;
	}
	vector<double> optimize()
	{
		int k = 0;
		vector<vector<double>> a; a.clear();
		vector<double> x_ = x_0;
		a.push_back(x_0);
		while (!SC->do_we_stop(a, f, k))
		{
			k++;
			x_ = iteration(x_, get_alpha_alt(x_));
			a.push_back(x_);
		}
		return a[a.size() - 1];
	}
};

class Function_1 : public Function {
public:
	//f(x, y) = sin(x)*cos(y)
	double eval(vector<double> x) { return sin(x[0]) * cos(x[1]); };
	vector<double> eval_gr(vector<double> x)
	{
		vector<double> y; y.clear();
		for (size_t i = 0; i < x.size(); ++i)
			y.push_back(0.);
		y[0] = cos(x[0]) * cos(x[1]);
		y[1] = -sin(x[0]) * sin(x[1]);
		return y;
	}
	vector<vector<double>> eval_Gesse(vector<double> x)
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
};

class Function_2 : public Function {
public:
	//f(x, y) = 20*exp(sin((x+y)/20))+xy
	double eval(vector<double> x) { return 20. * exp(sin((x[0] + x[1]) / 20.)) + x[0] * x[1]; };
	vector<double> eval_gr(vector<double> x)
	{
		vector<double> y; y.clear();
		for (size_t i = 0; i < x.size(); ++i)
			y.push_back(0.);
		y[0] = cos((x[0] + x[1]) / 20.) * exp(sin((x[0] + x[1]) / 20.)) + x[1];
		y[1] = cos((x[0] + x[1]) / 20.) * exp(sin((x[0] + x[1]) / 20.)) + x[0];
		return y;
	}
	vector<vector<double>> eval_Gesse(vector<double> x)
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
};



class Function_3 : public Function {
public:
	//f(x, y) = (1-х)^2 + 100(y-x^2)^2
	double eval(vector<double> x) { return (1. - x[0]) * (1. - x[0]) + 100. * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]); };
	vector<double> eval_gr(vector<double> x)
	{
		vector<double> y; y.clear();
		for (size_t i = 0; i < x.size(); ++i)
			y.push_back(0.);
		y[0] = -2. * (1 - x[0]) - 400. * x[0] * (x[1] - x[0] * x[0]);
		y[1] = 200. * (x[1] - x[0] * x[0]);
		return y;
	}
	vector<vector<double>> eval_Gesse(vector<double> x)
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
};


class Stochastic : public OptimizationMethod {
public:
	double alpha;
	double p;
	vector<double> iteration(vector<double> x, double& delta)
	{
		vector<double> next; next.clear();
		double p_ = rnunif();
		if (p_ < p)
		{
			delta = 10 * SC->eps;
			for (size_t i = 0; i < x.size(); ++i)
			{
				next.push_back(D.left_borders[i] + rnunif() * (D.right_borders[i] - D.left_borders[i]));
			}
		}
		else
		{
			bool flag = false;
			while (!flag)
			{
				double s = 0;
				for (size_t i = 0; i < x.size(); ++i)
				{
					next.push_back(rnunif() * delta - delta / 2 + x[i]);
					//std::cout << x[i] - delta / 2 << " " << next[i] << " " << x[i] + delta / 2 << endl;
					s += next[i] * next[i];
				}
				if (D.is_in(next))
					flag = true;
				else
					next.clear();
			}
		}
		return next;
	}
	vector<double> optimize()
	{
		int k = 0;
		double delta = 10 * SC->eps;
		vector<vector<double>> a; a.clear();
		vector<double> x_ = x_0;
		a.push_back(x_0);
		while (!SC->do_we_stop(a, f, k))
		{
			k++;
			vector<double> y_ = iteration(x_, delta);
			if (f->eval(y_) < f->eval(x_))
			{
				answer = f->eval(y_);
				x_ = y_;
				delta *= alpha;
			}
			a.push_back(x_);
		}
		return a[a.size() - 1];
	}
	Stochastic(Function* F, vector<double> x_0_, vector<double> l_border, vector<double> r_border,
		int SC_var = 1, double eps_ = 0.001, double alpha_ = 0.2, double p_ = 0.5) :
		alpha(alpha_), p(p_), OptimizationMethod(F, x_0_, l_border, r_border, SC_var, eps_) {}
};



int main()
{
	int replay = 1;
	while (replay)
	{
		cout << "Enter the number of the function:\n"
			<< "1. f(x, y) = sin(x)*cos(y)\n"
			<< "2. f(x, y) = 20*exp(sin((x+y)/20))+x*y\n"
			<< "3. f(x, y) = (1-x)^2 + 100(y-x^2)^2\n";
		int func_num = 0;
		while (func_num < 1 || func_num > 3)
			cin >> func_num;
		cout << "Choose the stop criterion:\n"
			<< "1. The norm of the function's gradient is less than eps.\n"
			<< "2. The distance between points representing adjacent iterations is less than eps.\n"
			<< "3. The quotient of values of the function at points\nrepresenting adjacent iterations is less than eps.\n";
		int sc_num = 0;
		while (sc_num < 1 || sc_num > 3)
			cin >> sc_num;
		cout << "Choose the optimization method:\n"
			<< "1. Determined Newton's method with derivatives and Hessian derived manually.\n"
			<< "2. Stochastic search.\n";
		int det_or_stoc = -1;
		while (det_or_stoc < 1 || det_or_stoc > 2)
			cin >> det_or_stoc;
		cout << "Enter the eps\n";
		double eps;
		cin >> eps;
		std::cout << "  Enter left and right borders (x_1, y_1), (x_2, y_2) in format \"x_1 y_1 x_2 y_2\"\n";
		vector<double> lefts, rights, x_0;
		double a;
		std::cin >> a; lefts.push_back(a); std::cin >> a; lefts.push_back(a);
		std::cin >> a; rights.push_back(a); std::cin >> a; rights.push_back(a);
		Area D(lefts, rights);
		x_0.push_back(rights[0] * 2);
		x_0.push_back(rights[1] * 2);
		while (!D.is_in(x_0))
		{
			x_0.clear();
			std::cout << "  Enter the starting point (x_0, y_0) in format \"x_0 y_0\"\n";
			std::cin >> a;
			x_0.push_back(a);
			std::cin >> a;
			x_0.push_back(a);
		}

		vector<Function*> funcs;

		Function* f_1 = new Function_1;
		funcs.push_back(f_1);

		Function* f_2 = new Function_2;
		funcs.push_back(f_2);

		Function* f_3 = new Function_3;
		funcs.push_back(f_3);

		Function* f = funcs[func_num - 1];
		int cont = 1;
		while (cont)
		{
			vector<double> ans;
			if (det_or_stoc == 1)
			{
				Newton OM(f, x_0, lefts, rights, sc_num, eps);
				ans = OM.optimize();
				std::cout << "  Result of optimization: " << OM.answer << endl;
			}
			else
			{
				rninit(time(0));
				Stochastic OM(f, x_0, lefts, rights, sc_num, eps);
				ans = OM.optimize();
				std::cout << "  Result of optimization: " << OM.answer << endl;
			}
			std::cout << "  At point: " << endl;
			for (size_t i = 0; i < ans.size(); ++i)
				std::cout << " " << ans[i];
			std::cout << endl << endl;
			std::cout << "1 - Compute again\n0 - Stop\n";
			std::cin >> cont;
		}
		std::cout << "1 - Run again with other parameters\n0 - Quit\n";
		std::cin >> replay;
	}
	
	return 0;
}
