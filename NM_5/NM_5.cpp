#include <iostream>
#include <fstream>

using namespace std;

double** CalculateA(int n);
double** CalculateR(double** A, int n);
double** GaussMethod(double** R, int n);
double** MultiplyMatrix(double** A, double** B, int n);
void OutputMatrix(double** A, int n);
double CalculateCond(double** A, int n);
void OutputMatixToFile(double** A, int n);

int main()
{
	setlocale(LC_ALL, "Russian");
	cout.precision(3);
	cout << scientific;
	ofstream fout("Output.txt");
	fout.clear();
	fout.close();

	int n = 8;
	double** A = CalculateA(n);
	cout << "Исходная матрица: " << endl;
	OutputMatrix(A, n);
	OutputMatixToFile(A, n);

	double** R = CalculateR(A, n);


	double** X = GaussMethod(R, n);
	cout << endl << "Искомая обратная матрица: " << endl;
	OutputMatrix(X, n);
	OutputMatixToFile(X, n);

	double** H = MultiplyMatrix(A, X, n);
	cout << endl << "Проверка единичной матрицей: " << endl;
	OutputMatrix(H, n);
	OutputMatixToFile(H, n);

	double maxA = CalculateCond(A, n);
	double maxX = CalculateCond(X, n);
	double cond = maxA * maxX;

	cout << fixed << endl << "Обусловленность матрицы: " << cond << endl;

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

	for (int k = 0; k < n; k++)// Прямой ход метода Гаусса-Жордана
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

	for (int k = n - 1; k >= 0; k--)//Обратный ход метода Гаусса-Жордана
	{
		for (int i = 2 * n - 1; i >= 0; i--) //i-номер столбца
			RR[k][i] = RR[k][i] / R[k][k];
		for (int i = k - 1; i >= 0; i--) //i-номер следующей строки после k
		{
			double K = RR[i][k] / RR[k][k];
			for (int j = 2 * n - 1; j >= 0; j--) //j-номер столбца следующей строки после k
				RR[i][j] = RR[i][j] - RR[k][j] * K;
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 2 * n; j++)
			{
				R[i][j] = RR[i][j];
			}
		}
	}

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

void OutputMatrix(double** A, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << A[i][j] << '\t';
		}
		cout << endl;
	}
}

double CalculateCond(double** A, int n)
{
	double maxCond = 0;

	for (int i = 0; i < n; i++)
	{
		double max = 0;
		for (int j = 0; j < n; j++)
		{
			max += abs(A[i][j]);
		}
		if (max > maxCond)
		{
			maxCond = max;
		}
	}
	return maxCond;
}

void OutputMatixToFile(double** A, int n)
{
	ofstream fout("Output.txt", ios::app);
	fout.precision(5);
	fout << scientific;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fout << A[i][j] << '\t';
		}
		fout << endl;
	}
	fout << endl;
	fout.close();
}