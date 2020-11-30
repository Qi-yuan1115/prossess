#include "StdAfx.h"
#include "OutLineArithmetic.h"
#include <cmath>
#include <set>
#include<algorithm>
using namespace std;



//double a,b,r,*z=NULL;



OutLineArithmetic::OutLineArithmetic(void)
{
}


OutLineArithmetic::~OutLineArithmetic(void)
{
}

double OutLineArithmetic::Average(double A[], int n)
{
	int i;
	double tmp = 0;
	for (i = 0;i<n;i++)tmp += A[i];
	tmp = tmp / (double)n;
	return tmp;
}


void OutLineArithmetic::MatrixProduct(double A[], double B[], int l, int m, int n, double *C)
{
	int i, j, k;
	//double *C=NULL;
	//C=(double *)malloc(m*m*sizeof(double));
	for (i = 0;i<l;i++)
		for (j = 0;j<n;j++)C[i*n + j] = 0;
	for (i = 0;i<l;i++)
		for (j = 0;j<n;j++)
			for (k = 0;k<m;k++) C[i*n + j] += A[i*m + k] * B[k*n + j];
	/*return C;
	free(C);*/
}



double OutLineArithmetic::Surplus(double A[], int m, int n) //求矩阵行列式
{
	int i, j, k, p, r;
	double X, temp = 1.0, temp1 = 1.0, s = 0, s1 = 0;

	if (n == 2)
	{
		for (i = 0;i<m;i++)
			for (j = 0;j<n;j++)
				if ((i + j) % 2) temp1 *= A[i*n + j];
				else temp *= A[i*n + j];
				X = temp - temp1;
	}
	else
	{
		for (k = 0;k<n;k++)
		{
			for (i = 0, j = k;i<m, j<n;i++, j++)temp *= A[i*n + j];
			if (m>i)
			{
				for (p = m - i, r = m - 1;p>0;p--, r--)temp *= A[r*n + p - 1];
			}
			s += temp;
			temp = (double)1;
		}
		for (k = n - 1;k >= 0;k--)
		{
			for (i = 0, j = k;i<m, j >= 0;i++, j--)temp1 *= A[i*n + j];
			if (m>i)
			{
				for (p = m - 1, r = i;r<m;p--, r++)temp1 *= A[r*n + p];
			}
			s1 += temp1;
			temp1 = (double)1;
		}
		X = s - s1;
	}
	return X;
}



void OutLineArithmetic::MatrixInver(double A[], int m, int n, double *B) //矩阵转置
{
	int i, j;
	for (i = 0;i<n;i++)
		for (j = 0;j<m;j++)
			B[i*m + j] = A[j*n + i];

}



void OutLineArithmetic::MatrixOpp(double A[], int m, int n, double *C) //矩阵求逆
{
	int i, j, x, y, k;
	double *SP = NULL, *AB = NULL, *B = NULL, X;
	SP = (double *)malloc(m*n * sizeof(double));
	AB = (double *)malloc(m*n * sizeof(double));
	B = (double *)malloc(m*n * sizeof(double));

	X = Surplus(A, m, n);
	//printf("|F|=%e  \n ",X);
	X = (double)1 / X;

	for (i = 0;i<m;i++)
		for (j = 0;j<n;j++)
		{
			for (k = 0;k<m*n;k++)B[k] = A[k];
			{
				for (x = 0;x<n;x++)B[i*n + x] = 0;
				for (y = 0;y<m;y++)B[m*y + j] = 0;
				B[i*n + j] = 1;
				SP[i*n + j] = Surplus(B, m, n);
				AB[i*n + j] = X*SP[i*n + j];
			}
		}
	MatrixInver(AB, m, n, C);

	free(AB);
	free(SP);
	free(B);
	//return C;

}






double* OutLineArithmetic::CircleParaInit(std::vector<double> X, std::vector<double> Y, int N, double &a, double &b) //求圆参数初值
{
	int i;
	double tmp = 0;
	double *z = NULL;
	for (i = 0;i<N;i++)tmp += X[i];

	a = tmp / (double)N;

	tmp = 0;
	for (i = 0;i<N;i++)tmp += Y[i];
	b = tmp / (double)N;
	//tmp=0;
	//for(i=0;i<N;i++)tmp+=sqrt(pow(X[i]-a,2.0)+pow(Y[i]-b,2.0));
	//r=tmp/(double)N;//新增
	z = (double*)malloc((unsigned)(N * sizeof(double)));
	for (i = 0;i<N;i++)z[i] = X[i] * X[i] + Y[i] * Y[i];
	return z;
}


void OutLineArithmetic::CircleSim(std::vector<double> X, std::vector<double> Y, double Z[], double a, double b, double r, int N, double *P)
{
	if (N == 0)
	{
		return;
	}
	int j, m = 2;//m=3 新增
	double *C, *D, *E, *F, *T, *H = NULL;
	T = (double *)malloc(N * sizeof(double));
	// Z(j)=X[j]*X[j]+Y[j]*Y[j];  f(Xj,Yj;a,b,r)=2ax+2by+r*r-a*a-b*b; T[j]=Z(j)-f(Xj,Yj;a,b,r);

	for (j = 0;j<N;j++)
		T[j] = Z[j] - ((double)2 * a*X[j] + (double)2 * b*Y[j] + r*r - a*a - b*b);

	if ((C = (double*)malloc((unsigned)(m*N * sizeof(double)))) == NULL)exit(1);
	if ((D = (double*)malloc((unsigned)(m*N * sizeof(double)))) == NULL)exit(1);

	if ((E = (double*)malloc((unsigned)(m*m * sizeof(double)))) == NULL)exit(1);
	if ((F = (double*)malloc((unsigned)(m*m * sizeof(double)))) == NULL)exit(1);
	//if( (P = ( double*)malloc((unsigned)(m*sizeof(  double)))) == NULL )exit( 1 );
	if ((H = (double*)malloc((unsigned)(m*N * sizeof(double)))) == NULL)exit(1);


	//C是偏导矩阵
	for (j = 0;j<N;j++)C[j*m] = (double)2 * (X[j] - a);
	for (j = 0;j<N;j++)C[j*m + 1] = (double)2 * (Y[j] - b);
	//for(j=0;j<N;j++)C[j*m+2]=(double)2*r;
	//D是C的转置
	//for(j=0;j<N;j++)printf("C=%E; ",C[j]);
	MatrixInver(C, N, m, D);//D是C的转置
							//for(j=0;j<N;j++)printf("D=%E; ",D[j]);
	MatrixProduct(D, C, m, N, m, E);// E=DC
	MatrixOpp(E, m, m, F);         // F 是E的逆
	MatrixProduct(D, T, m, N, 1, H); // H=DT

	MatrixProduct(F, H, m, m, 1, P);
	//for(j=0;j<m;j++)printf("P*=%E; ",P[j]);
	free(C);
	free(D);
	free(E);
	free(F);
	free(H);
	free(T);
	//return P;
}


//============圆的拟合主程序==============
void  OutLineArithmetic::FittingCircle(std::vector<double> x, std::vector<double> y, int N, double r, double *R)
{
	//long loop;
	int iloopcontrol = 0;
	int i = 0, j = 0, m = 5;
	double s = 0, t = 0, *P = NULL;
	double Fitting_a = 0, Fitting_b = 0;
	double* Fitting_z = NULL;
	//T=(double *)malloc(N*sizeof(double));
	//double R[2]={0};

	P = (double*)malloc((unsigned)(m*m * sizeof(double)));
	//===========初值=============//
	/*for (loop=0;loop<1000;loop++){*/
	i = 0;
	Fitting_z = CircleParaInit(x, y, N, Fitting_a, Fitting_b);

	do {
		CircleSim(x, y, Fitting_z, Fitting_a, Fitting_b, r, N, P);
		i++;
		iloopcontrol++;
		Fitting_a += P[0];
		Fitting_b += P[1];
	} while ((fabs(P[0])>0.0000001 || fabs(P[1])>0.0000001) && iloopcontrol<20);
	/*while( fabs(P[0])>0.0000001 || fabs(P[1])>0.0000001 );*/
	//}

	R[0] = Fitting_a;
	R[1] = Fitting_b;

	free(Fitting_z);
	free(P);
	//return R;


	/*free(P);
	free(z);*/
}

double  OutLineArithmetic::Pos_Max(double A[], int n)
{
	double max = 0;
	for (int i = 0;i<n;i++)
	{
		if (max<A[i])
			max = A[i];
	}
	return max;
}


int  OutLineArithmetic::Pos_MaxIndex(double A[], int n)
{
	double max = 0;
	int PMaxIndex = 0;
	for (int i = 0;i<n;i++)
	{
		if (max<A[i])
		{
			max = A[i];
			PMaxIndex = i;
		}
	}
	return PMaxIndex;
}
//5点中值滤波
void OutLineArithmetic::smooth_5(double D[], int nn, int k, double *Z)
{
	double *a = 0;
	/*Z=(double *)malloc(nn*sizeof(double));*/
	a = (double *)malloc(k * sizeof(double));

	for (int i = 2;i<nn - 2;i++)
	{
		a[0] = D[i - 2];
		a[1] = D[i - 1];
		a[2] = D[i];
		a[3] = D[i + 1];
		a[4] = D[i + 2];
		sort(a, a + k);
		D[i] = a[2];
	}
	for (int i = 0;i<nn;i++)
		Z[i] = D[i];
	free(a);
}
//9点中值滤波
void OutLineArithmetic::smooth_9(double D[], int nn, int k, double Z[])
{
	double *a = 0;
	a = (double *)malloc(k * sizeof(double));
	for (int i = 4;i<nn - 5;i++)
	{
		a[0] = D[i - 4];
		a[1] = D[i - 3];
		a[2] = D[i - 2];
		a[3] = D[i - 1];
		a[4] = D[i];
		a[5] = D[i + 1];
		a[6] = D[i + 2];
		a[7] = D[i + 3];
		a[8] = D[i + 4];
		std::sort(a, a + k);//将九点进行排序
		D[i] = a[4];//用中点代替该点的值
	}
	for (int i = 0;i<nn;i++)
		Z[i] = D[i];
	free(a);
}
void OutLineArithmetic::smooth_20(double D[], int nn, int k, double Z[])
{
	double *a = 0;
	a = (double *)malloc(k * sizeof(double));
	for (int i = 9;i<nn - 10;i++)
	{
		for (int j = 0;j<19;j++)
		{
			a[j] = D[i - 9 + j];
		}
		/*a[0]=D[i-4];
		a[1]=D[i-3];
		a[2]=D[i-2];
		a[3]=D[i-1];
		a[4]=D[i];
		a[5]=D[i+1];
		a[6]=D[i+2];
		a[7]=D[i+3];
		a[8]=D[i+4];*/
		std::sort(a, a + k);//将九点进行排序
		D[i] = a[9];//用中点代替该点的值
	}
	for (int i = 0;i<nn;i++)
		Z[i] = D[i];
	free(a);
}
//均值滤波
void OutLineArithmetic::smooth_ave(double X[], double Y[], int pNum, double newX[], double newY[])
{
	for (int i = 4; i <pNum - 5; i++)
	{
		double sumX = 0;
		double sumY = 0;

		for (int j = -4;j<5;j++)
		{
			sumX += X[i + j];
			sumY += Y[i + j];
		}
		X[i] = sumX / 9.0;
		Y[i] = sumY / 9.0;
	}
	for (int i = 0;i<pNum;i++)
	{
		newX[i] = X[i];
		newY[i] = Y[i];
	}
}
//去重排序程序
int OutLineArithmetic::RemoveRep(int array[], int n)
{
	//int *arrayflag = (int *)malloc(n*sizeof(int));
	set<int> tmpSet;
	for (int i = 0;i<n;++i)
	{
		tmpSet.insert(array[i]);
	}
	int left = 0;
	for (set<int>::iterator it = tmpSet.begin();it != tmpSet.end();++it)
	{
		array[left++] = *it;
	}
	//int left = 0, i = 0;

	////while(i<n)
	//int arrayflag[1280] = {0}; //初始化标志数组

	//for(i=0;i<n;i++)//剔除算法
	//{
	//	arrayflag[array[i]] = array[i]; //将出现过的数保存到对应的位置
	//}
	//memset(array, 0, n*sizeof(array));
	//for(i=0;i<1280;i++) //取出有效数
	//{
	//	if(arrayflag[i] != 0)
	//		array[left++] = arrayflag[i];
	//}

	return left;
}

double OutLineArithmetic::Fabs_max(double A[], int n)
{
	double max = 0;
	int i = 0;
	for (i = 0;i<n;i++)
	{
		if (fabs(A[i])>max)
		{
			max = A[i];
		}
	}

	return max;
}

//去除原始轮廓中的异常点

//int OutLineArithmetic::delErrorPoints(double* pDataX, double* pDataY, int pointNum)
//{
//	double ave_Y = 0;
//	for (int i=0;i<pointNum;i++)
//	{
//		ave_Y += pDataY[i];
//	}
//	double dpointNum = pointNum;
//	ave_Y = ave_Y / dpointNum;
//	double new_DataX[700];
//	double new_DataY[700];
//	int k = 0;
//	for (int i=0;i<pointNum;i++)
//	{
//		if (abs(pDataY[i]-ave_Y)<80)
//		{
//			new_DataX[k] = pDataX[i];
//			new_DataY[k] = pDataY[i];
//			k++;
//		}
//	}
//	for (int i=0;i<k;i++)
//	{
//		pDataX[i] = new_DataX[i];
//		pDataY[i] = new_DataY[i];
//	}
//	
//	return k;
//}
//12-18,添加Y值异常范围判断

int OutLineArithmetic::delErrorPoints(double* pDataX, double* pDataY, int pointNum)
{
	double boxPointsX[700];
	double boxPointsY[700];
	int newPointNums = 0;
	for (int i = 0;i<pointNum;i++)
	{
		if (pDataY[i]>100)
		{
			boxPointsX[newPointNums] = pDataX[i];
			boxPointsY[newPointNums] = pDataY[i];
			newPointNums++;
		}
	}
	double ave_Y = 0;
	for (int i = 0;i<newPointNums;i++)
	{
		ave_Y += boxPointsY[i];
	}
	ave_Y = ave_Y / newPointNums;
	double new_DataX[700];
	double new_DataY[700];
	int k = 0;
	for (int i = 0;i<newPointNums;i++)
	{
		if (abs(boxPointsY[i] - ave_Y)<80)
		{
			new_DataX[k] = boxPointsX[i];
			new_DataY[k] = boxPointsY[i];
			k++;
		}
	}
	for (int i = 0;i<k;i++)
	{
		pDataX[i] = new_DataX[i];
		pDataY[i] = new_DataY[i];
	}

	return k;
}

double OutLineArithmetic::LineFitLeastSquares(std::vector<double> data_x, std::vector<double> data_y, int data_n/*, vector<float> &vResult*/)
{

	double A = 0.0;
	double B = 0.0;
	double C = 0.0;
	double D = 0.0;
	double E = 0.0;
	double F = 0.0;

	for (int i = 0; i < data_n; i++)
	{
		A += data_x[i] * data_x[i];
		B += data_x[i];
		C += data_x[i] * data_y[i];
		D += data_y[i];
	}

	// 计算斜率a和截距b  
	double a, b, temp = 0;
	if (temp = (data_n*A - B*B))// 判断分母不为0  
	{
		a = (data_n*C - B*D) / temp;
		b = (A*D - B*C) / temp;
	}
	else
	{
		a = 1;
		b = 0;
	}
	return a;
	// 计算相关系数r  
	// 	float Xmean, Ymean;
	// 	Xmean = B / data_n;
	// 	Ymean = D / data_n;
	// 
	// 	float tempSumXX = 0.0, tempSumYY = 0.0;
	// 	for (int i = 0; i < data_n; i++)
	// 	{
	// 		tempSumXX += (data_x[i] - Xmean) * (data_x[i] - Xmean);
	// 		tempSumYY += (data_y[i] - Ymean) * (data_y[i] - Ymean);
	// 		E += (data_x[i] - Xmean) * (data_y[i] - Ymean);
	// 	}
	// 	/*	F = sqrt(tempSumXX) * sqrt(tempSumYY);*/
	// 
	// 	float r;
	// 	r = E / F;
	// 	// 	vResult.push_back(a);
	// 	vResult.push_back(b);
	// 	vResult.push_back(r*r);
}

//轨头平滑
int OutLineArithmetic::HeadSmooth(double * pDataX, double * pDataY, int& nums, int& R400_start)
{
	double tmpX[700];
	double tmpY[700];
	for (int i = 0; i < nums; i++)
	{
		tmpX[i] = pDataX[i];
		tmpY[i] = pDataY[i];
	}

	double prePosY = tmpY[R400_start - 5];
	int errFlag = -12345;//杂点标志
	for (int i = R400_start - 5 - 1; i >= 0; i--)
	{
		if (abs(prePosY - tmpY[i]) >= 4)
		{
			tmpY[i] = errFlag;
		}
		else
			prePosY = tmpY[i];
	}
	int tmpNums = 0;
	for (int i = 0; i < nums; i++)
	{
		if (tmpY[i] != errFlag)
		{
			pDataX[tmpNums] = tmpX[i];
			pDataY[tmpNums] = tmpY[i];
			tmpNums++;
		}
		else
		{
			R400_start--;
		}
	}
	nums = tmpNums;
	return 0;
}
double OutLineArithmetic::median(std::vector <double> array, int n)
{
	double medium;
	if (n % 2 == 1)
		medium = array[n / 2];
	else
		medium = (array[n / 2 - 1] + array[n / 2]) / 2;
	return medium;
}
double OutLineArithmetic::Hausdorff(std::vector <double> array1, std::vector <double> array2, double *array3, double *array4)//标准轨腰取47-78点
{
	//vector <double>().swap(array1); vector <double>().swap(array2);
	int ind1, ind2, lenxs, lenxB,flag=0;
	lenxs = size(array1);
	lenxB = 86;
	for (int i = 0;i < lenxB;i++)
	{
		if (array4[i] > array2[0])
		{
			ind1 = i;
			break;
		}	
	}
	for (int i = ind1;i < lenxB;i++)
	{
		if (array4[i] > array2[lenxs - 1])
		{
			ind2 = i - 1; flag = 1;
			break;
		}	
	}
	if (flag == 0)
		ind2 =lenxB-1;
	int num = 0, ind;
	double dis[86], tmp;
	for (int i = ind1;i <= ind2;i++)
	{
		if (num == 0)
		{
			for (int j = 0;j < lenxs;j++)
			{
				if (array2[j] >= array4[i])
				{
					ind = j;
					dis[num] = fabs(array1[j] - array3[i]);
					num++;
					break;
				}
			}
		}
		else
		{
			for (int j = ind;j < lenxs;j++)
			{
				if (array2[j] >= array4[i])
				{
					ind = j;
					dis[num] = fabs(array1[j] - array3[i]);
					num++;
					break;
				}
			}
		}
	}
	tmp = Average(dis, num);
	return tmp;
}