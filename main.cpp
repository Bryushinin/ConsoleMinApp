#include "Definitions.h"
#include "StopCriteria.h"
#include "OptimizationMethods.h"


int main()
{
	int replay = 1;
	while (replay)
	{
		cout << "Enter the number of the function:\n"
			<< "1. f(x, y) = sin(x)*cos(y)\n"
			<< "2. f(x, y) = 20*exp(sin((x+y)/20))+x*y\n"
			<< "3. f(x, y) = (1-x)^2 + 100(y-x^2)^2\n"
			<< "4. f(x, y, z) = sin(x)*(y^2+1) - z*cos(x)\n"
			<< "5. f(x, y, z, w) = x^2 * y^2 * w + x^2 * z * w - z * w^2\n";
		int func_num = 0;
		while (func_num < 1 || func_num > 5)
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

		vector<double> lefts, rights, x_0; lefts.clear(); rights.clear(); x_0.clear();
		double a;
		int siize = 0;
		if (func_num < 4)
		{
			std::cout << "  Enter left and right borders (x_1, y_1), (x_2, y_2) in format \"x_1 y_1 x_2 y_2\"\n";
			siize = 2;
		}
		if (func_num == 4)
		{
			std::cout << "  Enter left and right borders (x_1, y_1, z_1), (x_2, y_2, z_2)\n in format \"x_1 y_1 z_1 x_2 y_2 z_2\"\n";
			siize = 3;
		}
		if (func_num == 5)
		{
			std::cout << "  Enter left and right borders (x_1, y_1, z_1, w_1), (x_2, y_2, z_2, w_2)\n in format \"x_1 y_1 z_1 w_1 x_2 y_2 z_2 w_2\"\n";
			siize = 4;
		}
		for (int i = 0; i < siize; ++i)
		{
			std::cin >> a; 
			lefts.push_back(a);
		}
		for (int i = 0; i < siize; ++i)
		{
			std::cin >> a;
			rights.push_back(a);
			x_0.push_back(rights[i] * 2);
		}
		Area D(lefts, rights);
		while (!D.is_in(x_0))
		{
			x_0.clear();
			if(siize == 2)
				std::cout << "  Enter the starting point (x_0, y_0) in format \"x_0 y_0\"\n";
			if (siize == 3)
				std::cout << "  Enter the starting point (x_0, y_0, z_0) in format \"x_0 y_0 z_0\"\n";
			if (siize == 4)
				std::cout << "  Enter the starting point (x_0, y_0, z_0, w_0) in format \"x_0 y_0 z_0 w_0\"\n";
			for (int i = 0; i < siize; ++i)
			{
				std::cin >> a;
				x_0.push_back(a);
			}
		}

		vector<Function*> funcs;

		Function* f_1 = new Function_1;
		funcs.push_back(f_1);

		Function* f_2 = new Function_2;
		funcs.push_back(f_2);

		Function* f_3 = new Function_3;
		funcs.push_back(f_3);

		Function* f_4 = new Function_4;
		funcs.push_back(f_4);

		Function* f_5 = new Function_5;
		funcs.push_back(f_5);

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
				//rninit(time(0));
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
