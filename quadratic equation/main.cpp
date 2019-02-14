#include <iostream>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#define eps 1e-6


bool zeroComparison(double a)
{
	if (fabs(a) < eps)
		return (1);
	else
		return (0);
}

double discriminant(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

int checkCorrectness(bool e)
{
	if (!e)
		exit(0);
	return (0);
}

int linerEquationSolve(double b, double c, double &x1)
{
	if (zeroComparison(b))
		if (zeroComparison(c))
			return (3);
		else
			return (0);
	else
	{
		x1 = - c / b;
		if (zeroComparison(c))
			x1 = fabs(x1);
		return (1);
	}
}

int squareEquationSolve(double a, double b, double c, double &x1, double &x2)
{
	if (discriminant(a, b, c) >= 0)
	{
		x1 = (-b + sqrt(discriminant(a, b, c))) / (2 * a);
		x2 = (-b - sqrt(discriminant(a, b, c))) / (2 * a);
		if (x1 == x2)
			return (1);
		else
			return (2);
	}
	else
		return (0);
}

int EquationSolve(double a, double b, double c, double &x1,double &x2)
{
	assert(isfinite(a));
	assert(isfinite(b));
	assert(isfinite(c));
	assert(isfinite(x1));
	assert(isfinite(x2));
	
	if (zeroComparison(a))
		return (linerEquationSolve(b, c, x1));
	else
		return (squareEquationSolve(a, b, c, x1, x2));
}

int main()
{
	double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
	int correctness = scanf_s("%lg%lg%lg", &a, &b, &c);
	checkCorrectness(correctness == 3);
	switch (EquationSolve(a, b, c, x1, x2))
		{
			case 0:
				printf("no solves\n");
				break;
			case 1:
				printf("x=%lg\n", x1);
				break;
			case 2:
				printf("x1=%lg\nx2=%lg\n", x1, x2);
		}
	system ("pause");
}