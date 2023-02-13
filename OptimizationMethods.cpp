#include "OptimizationMethods.h"


OptimizationMethod::OptimizationMethod(Function* F, vector<double> x_0_, vector<double> l_border, vector<double> r_border, int SC_var, double eps) :f(F), x_0(x_0_), D(l_border, r_border), answer(F->eval(x_0_))
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


double Newton::get_alpha_alt(vector<double> x_n)
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
vector<double> Newton::optimize()
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


vector<double> Stochastic::iteration(vector<double> x, double& delta)
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
vector<double> Stochastic::optimize()
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