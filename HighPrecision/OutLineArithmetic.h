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
	double Surplus(double A[], int m, int n);				//���������ʽ
															//double * MatrixInver(double A[],int m,int n);		//����ת��
	void MatrixInver(double A[], int m, int n, double *B); //����ת��
														   //double * MatrixOpp(double A[],int m,int n);			//��������
	void MatrixOpp(double A[], int m, int n, double *C); //��������
	double* CircleParaInit(std::vector<double> X, std::vector<double> Y, int N, double &a, double &b);	//��Բ������ֵ
	void CircleSim(std::vector<double> X, std::vector<double> Y, double Z[], double a, double b, double r, int N, double *P);
	//============Բ�����������==============
	void FittingCircle(std::vector<double> x, std::vector<double> y, int N, double r, double *R);
	double Pos_Max(double A[], int n);
	void smooth_5(double D[], int nn, int k, double *Z);
	void smooth_9(double D[], int nn, int k, double *Z);
	void smooth_20(double D[], int nn, int k, double *Z);
	//��ֵ�˲�
	void smooth_ave(double X[], double Y[], int pNum, double* newX, double* newY);

	int RemoveRep(int array[], int n);
	int  OutLineArithmetic::Pos_MaxIndex(double A[], int n);
	double Fabs_max(double A[], int n);
	//=========ȥ��ԭʼ�����е��쳣�㣬���ش����ĵ���
	int delErrorPoints(double* pDataX, double* pDataY, int pointNum);
	double LineFitLeastSquares(std::vector<double> data_x, std::vector<double> data_y, int data_n);
	//��ͷƽ��
	int HeadSmooth(double* pDataX, double* pDataY, int& nums, int& R400_start);
	double OutLineArithmetic::median(std::vector <double> array, int n);
	double Hausdorff(std::vector <double> array1, std::vector <double> array2, double *array3, double *array4);
};

