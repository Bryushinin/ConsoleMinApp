#include "OptimizationMethods.h"


OptimizationMethod::OptimizationMethod(Function* F, vector<double> x_0_, vector<double> l_border, vector<double> r_border,
	int SC_var, double eps, ostream* out_) :f(F), x_0(x_0_), D(l_border, r_border), answer(F->eval(x_0_))
{
	switch (SC_var)
	{
	case 1:
		SC = new SC_GradientNorm;
		SC->eps = eps;
		SC->out = out_;
		break;
	case 2:
		SC = new SC_PointsClose;
		SC->eps = eps;
		SC->out = out_;
		break;
	case 3:
		SC = new SC_FuncRelative;
		SC->eps = eps;
		SC->out = out_;
		break;
	default:
		break;
	}
}


double Newton::get_alpha_alt(vector<double> x_n)
{
	vector<vector<double>> t = f->eval_Gesse(x_n);
	vector<double> t1 = -(f->eval_gr(x_n));
	
	Eigen::MatrixXd A;
	vector<double> entries;
	vector<double> entries1;
	Eigen::Matrix<double, Eigen::Dynamic, 1> b;
	for (size_t i = 0; i < x_n.size(); ++i)
	{
		for (size_t j = 0; j < x_n.size(); ++j)
			//A << t[i][j];
			entries.push_back(t[i][j]);
		//b << t1[i];
		entries1.push_back(t1[i]);
	}
	A = A.Map(&entries[0], int(x_n.size()), int(x_n.size()));
	b = b.Map(&entries1[0], int(x_n.size()));
	Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);
	p_n.clear();
	for (size_t j = 0; j < x_n.size(); ++j)
		p_n.push_back(x[j]);
	
	double alp = 0., step = 0.001, min_ = f->eval(x_n), alpha = 0.;
	while (alp < 1.)
	{
		alp += step;
		double temp = f->eval(x_n + alp * p_n);
		if (temp < min_ && D.is_in(x_n + alp * p_n))
		{
			min_ = temp;
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

	std::uniform_real_distribution<> distr(0., 1.);
	random_device rd;
	std::mt19937 gen(rd());
	double p_ = distr(gen);
	if (p_ < p)
	{
		delta = 10 * SC->eps;
		for (size_t i = 0; i < x.size(); ++i)
		{
			next.push_back(D.left_borders[i] + distr(gen) * (D.right_borders[i] - D.left_borders[i]));
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
				next.push_back(distr(gen) * delta - delta / 2 + x[i]);
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