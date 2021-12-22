#include <iostream>

using namespace std;

double** CalculateA(int n);
double** CalculateR(double** A, int n);
double** GaussMethod(double** R, int n);
double** MultiplyMatrix(double** A, double** B, int n);

int main()
{
	int n = 8;
	double** A = CalculateA(n);
	double** R = CalculateR(A, n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 2 * n; j++)
		{
			cout << R[i][j] << " ";
		}
		cout << endl;
	}
	double** X = GaussMethod(R, n);

	cout << endl;
	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = 0; j < 2 * n; j++)
	//	{
	//		cout << X[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	double** Check = MultiplyMatrix(A, X, n);

	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = 0; j < n; j++)
	//	{
	//		cout << Check[i][j] << " ";
	//	}
	//	cout << endl;
	//}
}


double F(int i, int j)
{
	return 1 / pow(cos(i - j), 2);
}


double** CalculateA(int n)
{
	double** A = new double* [n];
	for (int i = 0; i < n; i++) A[i] = new double[n];


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A[i][j] = 0.0;
			A[i][j] = F(i, j);
		}
	}

	return A;
}

double** CalculateR(double** A, int n)
{
	double** R = new double* [n];
	for (int i = 0; i < n; i++) R[i] = new double[2 * n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			R[i][j] = A[i][j];
		}
		for (int k = n; k < 2 * n; k++)
		{
			if (n + i == k) R[i][k] = 1.0;
			else R[i][k] = 0.0;
		}
	}


	return R;
}

double** GaussMethod(double** R, int n)
{
	double** RR = new double* [n];
	for (int i = 0; i < n; i++) RR[i] = new double[2 * n];

	double detR = 1;

	double** X = new double* [n];
	for (int i = 0; i < n; i++) X[i] = new double[n];

	for (int k = 0; k < n; k++)// Прямой ход
	{
		for (int i = 0; i < n; i++)
		{
			if (i == k)
			{
				for (int j = 0; j < 2 * n; j++)
				{
					RR[k][j] = R[k][j] / R[k][k];
				}
			}
			else
			{
				for (int j = 0; j < 2 * n; j++)
				{
					RR[i][j] = R[i][j] - R[i][k] * RR[k][j];
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 2 * n; j++)
			{
				R[i][j] = RR[i][j];
			}
		}
	}

	cout << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 2 * n; j++)
		{
			cout << R[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < n; i++)
	{
		detR *= R[i][i];
	}
	cout << detR << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			X[i][j] = R[i][j + n];
		}
	}

	return X;
}

double** MultiplyMatrix(double** A, double** B, int n)
{
	double** C = new double* [n];
	for (int i = 0; i < n; i++) C[i] = new double[n + 1];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = 0;
			for (int k = 0; k < n; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
	}

	return C;
}

























//for (int i = k + 1; i < n + 1; i++)
//{
//	if (abs(R[i][k]) > Amax)
//	{
//		Amax = abs(R[i][k]);
//		p = i;
//	}
//}
//for (int j = k; j < n + 2; j++)
//{
//	Pr = R[k][j];
//	R[k][j] = R[p][j];
//	R[p][j] = Pr;
//}
//for (int i = k + 1; i < n + 1; i++)
//{
//	for (int j = k + 1; j < n + 2; j++)
//	{
//		R[i][j] = R[i][j] - (R[i][k] * R[k][j]) / R[k][k];
//	}
//}