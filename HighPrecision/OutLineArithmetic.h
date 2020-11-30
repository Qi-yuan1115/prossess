#pragma once
#include<vector>
#include<algorithm>
class OutLineArithmetic
{
public:
	OutLineArithmetic(void);
	~OutLineArithmetic(void);
	double Average(double A[], int n);
	//double * MatrixProduct(double A[],double B[],int l,int m,int n);
	void MatrixProduct(double A[], double B[], int l, int m, int n, double *C);
	double Surplus(double A[], int m, int n);				//求矩阵行列式
															//double * MatrixInver(double A[],int m,int n);		//矩阵转置
	void MatrixInver(double A[], int m, int n, double *B); //矩阵转置
														   //double * MatrixOpp(double A[],int m,int n);			//矩阵求逆
	void MatrixOpp(double A[], int m, int n, double *C); //矩阵求逆
	double* CircleParaInit(std::vector<double> X, std::vector<double> Y, int N, double &a, double &b);	//求圆参数初值
	void CircleSim(std::vector<double> X, std::vector<double> Y, double Z[], double a, double b, double r, int N, double *P);
	//============圆的拟合主程序==============
	void FittingCircle(std::vector<double> x, std::vector<double> y, int N, double r, double *R);
	double Pos_Max(double A[], int n);
	void smooth_5(double D[], int nn, int k, double *Z);
	void smooth_9(double D[], int nn, int k, double *Z);
	void smooth_20(double D[], int nn, int k, double *Z);
	//均值滤波
	void smooth_ave(double X[], double Y[], int pNum, double* newX, double* newY);

	int RemoveRep(int array[], int n);
	int  OutLineArithmetic::Pos_MaxIndex(double A[], int n);
	double Fabs_max(double A[], int n);
	//=========去除原始轮廓中的异常点，返回处理后的点数
	int delErrorPoints(double* pDataX, double* pDataY, int pointNum);
	double LineFitLeastSquares(std::vector<double> data_x, std::vector<double> data_y, int data_n);
	//轨头平滑
	int HeadSmooth(double* pDataX, double* pDataY, int& nums, int& R400_start);
	double OutLineArithmetic::median(std::vector <double> array, int n);
	double Hausdorff(std::vector <double> array1, std::vector <double> array2, double *array3, double *array4);
};

