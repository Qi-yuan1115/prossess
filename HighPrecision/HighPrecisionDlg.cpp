
// HighPrecisionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HighPrecision.h"
#include "HighPrecisionDlg.h"
#include "afxdialogex.h"
#include "ConnectDeviceDlg.h"
#include "TestInfoInputDlg.h"
#include "include/ZLDS200_TCP_DLL.H"
#include "LoopBuf.h"
#include "OutLineArithmetic.h"
#include "SetParameterDlg.h"
#include "MotorPara.h"
#include "MyFileDialog.h"
#include "ExcelOutput/CApplication.h"
#include "ExcelOutput/CFont0.h"
#include "ExcelOutput/CRange.h"
#include "ExcelOutput/CWorkbook.h"
#include "ExcelOutput/CWorkbooks.h"
#include "ExcelOutput/CWorksheet.h"
#include "ExcelOutput/CWorksheets.h"
#include "ExcelOutput/CChart.h"
#include "ExcelOutput/CChartObject.h"
#include "ExcelOutput/CChartObjects.h"
#include "ExcelOutput/CInterior.h"
#include "ReprtParamDlg.h"
#include "OutlineFileHelper.h"
#include "Outline.h"
#include<stdlib.h>
#include<time.h>
#include<math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



/*��ĥ��ⶨ�岿��*/
#include "LoopBuf_Bomo.h"
#include "MEDAQ-Sensor.h"

#define  Bomo_Caiyang_jiange 0.002  //ÿ�δ���Ĳ������0.002m
#define  Bomo_Chuli_lengthe 4  //ÿ�δ���Ĳ������0.002m
#define Bomo_length  (int)(Bomo_Chuli_lengthe/ Bomo_Caiyang_jiange)  //ÿ�δ���ĳ���

#define Bomo_Xianshi_Length 2 //������Ļ��ʾ�ò�ĥ����/m
#define Bomo_Xianshi_dum (int)(Bomo_Xianshi_Length/0.002) //������Ļ��ʾ�ò�ĥ����



float Bomo_sensor_data_R1[Bomo_length];//���ڶ������������
float Bomo_sensor_data_R2[Bomo_length];
float Bomo_sensor_data_R3[Bomo_length];
//���ݴ��������Ҫ������
double Bomo_sensor_jisun_data_R1[Bomo_length];//�������ݼ����ԭʼ����
double Bomo_sensor_jisun_data_R2[Bomo_length];
double Bomo_sensor_jisun_data_R3[Bomo_length];

double Bomo_sensor_Pre_data_R1[Bomo_length];
double Bomo_sensor_Pre_data_R2[Bomo_length];
double Bomo_sensor_Pre_data_R3[Bomo_length];

double Bomo_a_1_3Hz_signal_R[Bomo_length];
double Bomo_a_3_10Hz_signal_R[Bomo_length];
double Bomo_a_10_100Hz_signal_R[Bomo_length];

//���޽��
double Bomo_RMS_30_100mm_R[100], Bomo_RMS_100_300mm_R[100], Bomo_RMS_300_100mm_R[100];

int Bomo_PSD_jiegou_R = 0;
int Bomo_Chaoxianbi_30_100mm_R = 0;
int Bomo_Chonxianbi_100_300mm_R = 0;
int Bomo_Chaoxianbi_300_1000mm_R = 0;
//
int  Bomo_paint_count_tow_R = 0;//����ѭ���ô���

//����������
ME_Sonser Bomo_sensor_R1;
ME_Sonser Bomo_sensor_R2;
ME_Sonser Bomo_sensor_R3;

//ѭ���Ĵ���
int Bomo_SJCJ_sensor_count_R = 0;//��¼���ݲɼ��Ĵ���



//���ɼ���־λ
int Bomo_Flag_bomo_Caiji_R = 1;//���ݲɼ���־
BOOL Bomo_Flag_bomo_Jisuan_R = FALSE;//��ʼ����
BOOL Bomo_Flag_bomo_TxT_R = FALSE;//��ʼ����


//��ͼ����
int  Bomo_paint_count_R = 0;//����ѭ���ô���

BOOL Bomo_Flag_huantu_vector_read_or_write_R = FALSE;//�������ɼ����׼����ͼ
BOOL Bomo_Flag_huantu_Qudengdai_R = FALSE;//�������ɼ����׼����ͼ
BOOL Bomo_Flag_huantu_DrawMoving_R = FALSE;//�������ɼ����׼����ͼ


vector<float> Bomo_huantu_vector_read_or_write_sensor_R1;//��ͼ���봦��������м�����
vector<float> Bomo_huantu_vector_read_or_write_sensor_R2;//��ͼ���봦�������
vector<float> Bomo_huantu_vector_read_or_write_sensor_R3;//��ͼ���봦�������
//���ڻ�ͼ����
double Bomo_huantu_a_1_3Hz_signal_R[Bomo_length];//���ڻ�ͼ������
double Bomo_huantu_a_3_10Hz_signal_R[Bomo_length];
double Bomo_huantu_a_10_100Hz_signal_R[Bomo_length];

//����Ч������
int Bomo_paint_step_R;//����drawin�����ڵ��δ�����
int Bomo_paint_X_cout_R;//���ڼ�¼X�������λ������x��������
const int Bomo_huatu_yidong_length = 30;//ÿ���ƶ��ó���
const size_t Bomo_paint_arrayLength = Bomo_Xianshi_dum;

double Bomo_paint_X_R1[Bomo_paint_arrayLength];
double Bomo_paint_X_R2[Bomo_paint_arrayLength];
double Bomo_paint_X_R3[Bomo_paint_arrayLength];
double Bomo_paint_Y_TeeChartArray_R1[Bomo_paint_arrayLength];
double Bomo_paint_Y_TeeChartArray_R2[Bomo_paint_arrayLength];
double Bomo_paint_Y_TeeChartArray_R3[Bomo_paint_arrayLength];


bool m_zanting = 0;



//����
CLoopBuf_Bomo Bomo_Psd_Loop_Buf_R1;//ƽ˳��ѭ��������
CLoopBuf_Bomo Bomo_Psd_Loop_Buf_R2;
CLoopBuf_Bomo Bomo_Psd_Loop_Buf_R3;

float * Bomo_LoopBuf100_R1;//���100�ɼ������ݣ��������׵�ַ
float * Bomo_LoopBuf100_R2;
float * Bomo_LoopBuf100_R3;

LoopBuffCtl Bomo_LoopBuffCtl_100_R1;//���ƻ������Ľṹ��
LoopBuffCtl Bomo_LoopBuffCtl_100_R2;
LoopBuffCtl Bomo_LoopBuffCtl_100_R3;

CCriticalSection Bomo_m_Buf_Critical_R1;//�ٽ���
CCriticalSection Bomo_m_Buf_Critical_R2;
CCriticalSection Bomo_m_Buf_Critical_R3;

//���ݴ���
BOOL Bomo_Flag_CalPsd_113_R1 = FALSE;//���������Խ������ݴ���
BOOL Bomo_Flag_CalPsd_113_R2 = FALSE;
BOOL Bomo_Flag_CalPsd_113_R3 = FALSE;






/*��ĥ��ⶨ�岿�ֽ���*/





//����ṹ��
//�߳�֮�䴫�ݵĲ�������ͼ��

//������ȫ�ֱ���

#define MotorMoveLmt 3
CString csPath;
CFile fpHNUFile;
CString HnuFilePath;
HANDLE handle=CreateSemaphore(NULL,1,1,NULL);
typedef struct THREAD_PARAM2D
{
	HWND hWnd;//���ھ��
	double xData[SensorMaxPoint];//��ͼʹ�õĴ��������
	double zData[SensorMaxPoint];
	double WdqData_X[SensorMaxPoint];//����ϳĥ��Ҫ�õ���δ�������������ļ���
	double WdqData_Y[SensorMaxPoint];
	double DistXml[Num_Node];//ϳĥ��
	double DistHdm[Num_Node];//����ֵ
	double DistXml_50[Num_Node_50];//ϳĥ��
	double DistHdm_50[Num_Node_50];//����ֵ
	int DataNum;
	int WdqNum;
}_THREAD_PARAM2D;
//����ѡ��ṹ��
struct TrackSelAndMHStruct
{
	int Num_Pos_R20;				//R20�ܵ���(����Ϊ����)
	int Num_Pos_R400;				//R350�ܵ���(����Ϊ����)
	double  Pos_BZ_R20_X;		//R20Բ������
	double  Pos_BZ_R20_Y;		
	double  Pos_BZ_R400_X;	//R400Բ������ 
	double  Pos_BZ_R400_Y;
};
//����Ԥ��������������Ϣ
struct PreprocessINfO
{
	double* pInDataX;//�����ԭʼ����
	double* pInDataY;
	int In_Num;     //����ԭʼ��������
	int FittingRadius_R20; //R20��ϰ뾶
	int FittingRadius_R400;//R400��ϰ뾶
	int RamerIndexArray[500];//����αƽ��߶����к�
	int RamerIndexNum;//����αƽ��߶���Ŀ
	double pOutDataX[SensorMaxPoint];//������ԭʼ����
	double pOutDataY[SensorMaxPoint];
	int  Out_Num;//������������
	int Num_R400Start;//R400���
}PreprocessINfO1={0,0,0,20,400,0,0,0,0,0,0};//Ĭ��ʹ��60Kg��İ뾶
//��������ṹ��(��ͷԲ����Բ������)
struct CalHdmStruct
{
	int    Index_Zero;//����ڱ�׼���е����
	double Pos_BZ_Aln_X;//���������
	double Pos_BZ_Aln_Y;

	double Pos_BZ_R13L_X;//R13����Բ������
	double Pos_BZ_R13_Y;
	double Pos_BZ_R13R_X;

	double Pos_BZ_R300L_X;//R300����Բ������
	double Pos_BZ_R300_Y;
	double Pos_BZ_R300R_X;

	double Pos_BZ_R80L_X;//R80����Բ������
	double Pos_BZ_R80_Y;
	double Pos_BZ_R80R_X;

	int iTrackSel;//����ѡ��0��ʾ50�죬1��ʾ60��2��ʾ75
};
//�洢��׼����
double xB[86],yB[86];

//ȫ�ֺ�������
int Preproccess(PreprocessINfO &PreINFO,TrackSelAndMHStruct &TrackSel);
void RamerFunc(double* xdata,double* ydata,int beginpoint,int endpoint,int* ResultArray,int &Index);
double Func_CZ(double xx,double x[],double y[]);
double FuncCalculatingHdm(CalHdmStruct &CalculatingHdm,bool bDuiQi,bool bLOrR,int &CalPointNum,double* pInDataX,double* pInDataY,int R400_Start);
void FuncCalculatingXml(CalHdmStruct &CalculatingHdm,bool bDuiQi,bool bLOrR,int &CalPointNum,double* pInDataX,double* pInDataY,int R400_Start,double* pScbzPoint_X,double* pScbzPoint_Y);
///
double FuncCalculatingHdm_Xml(CalHdmStruct &CalculatingHdm,bool bDuiQi,bool bLOrR,int &CalPointNum,double* pInDataX,double* pInDataY,int R400_Start,double* pScbzPoint_X,double* pScbzPoint_Y);
void SaveInvalidOutline(int m_nIsNormal,PreprocessINfO &PreINFO,TrackSelAndMHStruct &TrackSel);
//����º���
void GuiDiPoRevolve(int &PointNum, double *pInDataX, double *pInDataY, bool HdmOrXml,double &m_dGdpRad);

//����ȫ�ֱ���
double iDisdanceCount=0;//��̼�����ÿ�ɼ�һ�����������+0.1m
const bool bFlagWeiDuiQi=false;//û�ж���
const bool bFlagDuiQi=true;//������
bool bFlagTrack_L=false;//false��ʾ���
bool bFlagTrack_R=true;//true��ʾ�ҹ�
bool bFlagQiangzhiStart=true;//ǿ�ƿ���Ĭ��false����Ĭ��ǿ��ֹͣ��
CHighPrecisionDlg *pdlg;//����ȫ��ָ�룬����thisָ��Ĵ���
CRect rect;//����Ϊȫ�ֱ���


bool bFlagPOrder_L=true; 
bool bFlagPOrder_R=true; 
CMachineControl m_MachineCtrl_L;
CMachineControl m_MachineCtrl_R;
CMscomm1 m_Mscomm_L;
CMscomm1 m_Mscomm_R;
double m_MotorSpeed;//����ٶȣ��ɴ˱���Ψһȷ��
BOOL g_bFLagIsRunBack = FALSE;//��¼��ʻ�ķ�����Ϊǰ������Ϊ����

//������ñ���
bool moveBefore_L=TRUE; //�ж��Ƿ���һ��ָ��ʹ�������
int continueErrorCnt_L=0;  //�������쳣�������м���
bool moveBefore_R=TRUE; //�ж��Ƿ���һ��ָ��ʹ�������
int continueErrorCnt_R=0;  //�������쳣�������м���
bool bFlagStopMt=true;//�����ͣ��ťĬ����ʾΪ��ͣ��FALSEʱ��ʾ��ʾΪ�������
double Guidipo_L = 0.014958;
double Guidipo_R = 0.014958;

//�������ñ���--
#define PRECISION_NUM_60 23
#define PRECISION_NUM_50 19
#define PRECISION_NUM_75 15

#define PRECISION_STANDARD 0.35
enum ANALYSE_MODE{Before_SinglePrecision,Before_StatisticPrecision,Before_Transfinite,
	After_SinglePrecision,After_StatisticPrecision,After_SingleMilling,After_StatisticMilling
	,After_Transfinite}analyseMode;

int perMi=10;
//--�������ñ���
extern double dNegetiveLimit;
extern double dPositiveLimit;

//CONNECTDEVICE���ڴ��ݵ�ȫ�ֱ���
extern bool   g_bFlagSensorL;   //�����������ϱ�־
extern bool   g_bFlagSensorR;
extern bool   g_bFlagMotor_L;
extern bool   g_bFlagMotor_R;
extern int    g_InitiChooseL;    ///���ҹ���������
extern int    g_InitiChooseR;
extern struct SdandardINFO g_Sdandard_INFO;//��׼��������Ϣ
extern struct TestInfo     g_TestInfo_L;//��ҵ��Ϣ�������߳�
extern struct TestInfo     g_TestInfo_R;//��ҵ��Ϣ�������߳�
//extern double g_MotorSpeed_Qian;//���ת��
extern CString g_MotorBaud;//���������
extern int IsPowerON_L;
extern bool bIsConnectedL;
extern bool bIsConnectedR;
extern double g_MotorSpeed_Qian;//ϳĥǰת��
extern double g_MotorSpeed_Hou;//ϳĥ��ת��
extern double Encoder_Distance;	//�ɼ�����̵�λ
extern CString strpath;

//Բ����������///
//const double Std_Ang_60[Num_Node]={-13,-10,-8,-6,-4,-2,-1,0,1,2,4,6,8,10,13,20,30,40,50,60,70,80,87};//60��Ƕȷֲ�
//const double Std_Ang_50[Num_Node_50]={-10,-4,-3,-2,-1,0,1,2,3,4,10,20,30,40,50,60,70,80,90};
const double Std_Ang_60[Num_Node]={13,10,8,6,4,2,1,0,-1,-2,-4,-6,-8,-10,-13,-20,-30,-40,-50,-60,-70,-80,-87};//60��Ƕȷֲ�
const double Std_Ang_50[Num_Node_50]={10,4,3,2,1,0,-1,-2,-3,-4,-10,-20,-30,-40,-50,-60,-70,-80,-90};
TrackSelAndMHStruct Track_50={41,101,28.9291,111.6169,357.7476,83.7173};				//50��
TrackSelAndMHStruct Track_60={41,101,30.1016,134.4187,408.2584,97.0363};			   //60��
CalHdmStruct  Hdm_50={6,0,0,-22,13.8615,22,0,300,0,-7.39,80.16,7.39,0};
CalHdmStruct  Hdm_60={8,0,0,-22.417,14.8648,22.417,0,300,0,-7.3874,80.1573,7.3874,1};
//��׼������///
const double Pos_BZ_X_50[Num_Node_50]={-24.3052,-23,-17.2575,-11.5086,-5.7554,0,5.7554,11.5086,17.2575,23,24.3052,
	                                26.4198,28.4707,30.3007,31.9526,33.2307,34.2142,34.8045,35};
const double Pos_BZ_Y_50[Num_Node_50]={1.0675,0.9,0.5095,0.2293,0.0595,0,0.0595,0.2293,0.5095,0.9,1.0675,1.6359,2.5863,
	                                3.8565,5.4981,7.3138,9.4102,11.6149,13.9};
const double Pos_BZ_X_60[Num_Node]={-25.35,-21.2609,-18.162,-15.4047,-13.0575,-10,-5.0008,0,5.0008,10,13.0575,15.4047,
                                   18.162,21.26,25.35,26.85,28.921,30.83,32.4404,33.7,34.6389,35.24,35.4};
const double Pos_BZ_Y_60[Num_Node]={2.2,1.3695,0.8793,0.5601,0.3585,0.2,0.0583,0,0.0583,0.2,0.3585,0.5601,0.8793,1.37,
                                   2.2,2.65,3.6088,4.96,6.5864,8.4,10.4347,12.7,14.2};
//�߳�����
CWinThread *pGetDataThread_L;
CWinThread *pDealThread_L;
CWinThread *pStDataThread_L;
CWinThread *pGetDataThread_R;
CWinThread *pDealThread_R;
CWinThread *pStDataThread_R;

UINT ThreadGetDataLeft(LPVOID pParam);//�����ݲɼ��߳�
UINT ThreadDealLeft(LPVOID pParam);
UINT ThreadStData_L(LPVOID pParam);//��ߴ洢�߳�

UINT ThreadGetDataRight(LPVOID pParam);//�����ݲɼ��߳�
UINT ThreadDealRight(LPVOID pParam);
UINT ThreadStData_R(LPVOID pParam);//�ұߴ洢�߳�
UINT ThreadSaveExcel(LPVOID pParam);//�洢Excel

bool bFlagStartThread = false;//��ʼ��ť��ֹͣ��ť���л���־,��Ϊ�̵߳Ŀ����͹ر�(TRUE=����)
//���
//�������ɼ��̱߳���
THREAD_PARAM2D m_2DThreadParam_L;//��������߳�
PreprocessINfO Point_50INFO_L;
PreprocessINfO Point_60INFO_L;

CCriticalSection GetDataSection_L;//�ɼ������ٽ���
CCriticalSection OutLineSection_L;
bool g_StopDrawFlag_L=false;//��ͼ��־λ
//��ͼ�ؼ��ı�������
CChartLineSerie*  m_pLineSerie_LT;//����
CChartLineSerie*  m_pLineSerie_LB;//��������
CChartLineSerie*  m_sLineSerie_LT;//���ϱ�׼����
CChartPointsSerie* m_PointSerie_LB;//���µ�ͼ
CChartLineSerie*  m_pLineSerieStd_LT;//����
//��ദ���߳�
double HdmScbz_XL[Num_Node+1]={0},HdmScbz_YL[Num_Node+1]={0};//23��ʵ���׼��ӹ����
double HdmNode_XL[Num_Node+1]={0},HdmNode_YL[Num_Node+1]={0};//23������潻��ӹ����
double HdmScbz_XL_50[Num_Node_50+1]={0},HdmScbz_YL_50[Num_Node_50+1]={0};//23��ʵ���׼��ӹ����
double HdmNode_XL_50[Num_Node_50+1]={0},HdmNode_YL_50[Num_Node_50+1]={0};//23������潻��ӹ����

double Dist_Hdmjd_L[Num_Node];			//�������澫�ȵ�23��ֵ
double Dist_Hdmjd_L_50[Num_Node_50];			//�������澫�ȵ�23��ֵ


double XmlScbz_XL[Num_Node+1]={0},XmlScbz_YL[Num_Node+1]={0};//23��ϳĥ��ʵ���׼��ӹ����
double Dist_Xmljd_L[Num_Node];			//����ϳĥ����23��ֵ

double XmlScbz_XL_50[Num_Node_50+1]={0},XmlScbz_YL_50[Num_Node_50+1]={0};//23��ϳĥ��ʵ���׼��ӹ����
double Dist_Xmljd_L_50[Num_Node_50];			//����ϳĥ����23��ֵ

#define WM_2DTHREADMSG_L WM_USER+2      //��໭ͼ��Ϣ
#define WM_2DTHREADMSG_XML_L  WM_USER+6 //���ϳĥ����ͼ��Ϣ
#define WM_2DTHREADMSG_XMLscbz_L  WM_USER+7 //���ʵ���׼������
#define WM_DISPLAYCTRL WM_USER+8 //�ɼ��߳���������̼�������Ϣ��Ӧ����
#define WM_2DDISPLISTCTRL_L  WM_USER+9 //���ListCtrl��ʾ
#define WM_2DDISPLISTCTRL_R  WM_USER+10 //�Ҳ�ListCtrl��ʾ
//�Ҳ�
THREAD_PARAM2D     m_2DThreadParam_R;//��������߳�
CChartLineSerie*   m_pLineSerie_RT;//����
CChartLineSerie*   m_pLineSerie_RB;//��������
CChartPointsSerie* m_PointSerie_RB; //���µ�ͼ
CChartLineSerie*   m_sLineSerie_RT;//���ϱ�׼����
CChartLineSerie*   m_pLineSerieStd_RT;//����ϳĥ��ʵ���׼������
//�����Ҳ�ɼ��̱߳���
CCriticalSection GetDataSection_R;
bool g_StopDrawFlag_R=false;//��ͼ��־λ
//�Ҳദ���߳�
PreprocessINfO Point_50INFO_R;
PreprocessINfO Point_60INFO_R;
double HdmScbz_XR[Num_Node+1]={0},HdmScbz_YR[Num_Node+1]={0};//23��ʵ���׼��ӹ����
double HdmNode_XR[Num_Node+1]={0},HdmNode_YR[Num_Node+1]={0};//23������潻��ӹ����
double Dist_Hdmjd_R[Num_Node];
double XmlScbz_XR[Num_Node+1]={0},XmlScbz_YR[Num_Node+1]={0};//23��ϳĥ��ʵ���׼��ӹ����
double Dist_Xmljd_R[Num_Node];			//����ϳĥ����23��ֵ

double HdmScbz_XR_50[Num_Node_50+1]={0},HdmScbz_YR_50[Num_Node_50+1]={0};//23��ʵ���׼��ӹ����
double HdmNode_XR_50[Num_Node_50+1]={0},HdmNode_YR_50[Num_Node_50+1]={0};//23������潻��ӹ����
double Dist_Hdmjd_R_50[Num_Node_50];
double XmlScbz_XR_50[Num_Node_50+1]={0},XmlScbz_YR_50[Num_Node_50+1]={0};//23��ϳĥ��ʵ���׼��ӹ����
double Dist_Xmljd_R_50[Num_Node_50];			//����ϳĥ����23��ֵ

#define WM_2DTHREADMSG_R WM_USER+3     //�Ҳ໭ͼ��Ϣ
#define WM_2DTHREADMSG_XML_R  WM_USER+4 //�Ҳ�ϳĥ����ͼ��Ϣ
#define WM_2DTHREADMSG_XMLscbz_R  WM_USER+5 //�Ҳ�ʵ���׼������


////����������
CLoopBuf LoopBuff;
//���
DoubleLoopBuffCtl xGetData_LoopBuff_L;//X���꣬�ɼ��߳���洢�ɼ����ݵĻ�����
DoubleLoopBuffCtl zGetData_LoopBuff_L;//Z����
IntLoopBuffCtl	  GetDataNum_LoopBuff_L;//��Ųɼ�����������Ŀ�Ļ�����
DoubleLoopBuffCtl xSave_LoopBuff_L;//
DoubleLoopBuffCtl zSave_LoopBuff_L;
IntLoopBuffCtl    GetDataNumSt_LoopBuff_L;//�ɼ��������ݴ���txtʱ�õ���������Ŀ������
DoubleLoopBuffCtl xScbzLoopBuff_L;//ʵ���׼��X����
DoubleLoopBuffCtl zScbzLoopBuff_L;//ʵ���׼��Z����
DoubleLoopBuffCtl xHdmNodeLoopBuff_L;//����澫�ȵ�X����
DoubleLoopBuffCtl zHdmNodeLoopBuff_L;//����澫�ȵ�Z����
DoubleLoopBuffCtl DistHdmJd_LoofBuff_L;//����ֵ
DoubleLoopBuffCtl DistXmlJd_LoopBuff_L;//ϳĥ��
//IntLoopBuffCtl    OutLine_LoopBuff_L;
//IntLoopBuffCtl    HdmORXmlNum_loopBuff_L;


//�Ҳ�
DoubleLoopBuffCtl xGetData_LoopBuff_R;//X���꣬�ɼ��߳���洢�ɼ����ݵĻ�����
DoubleLoopBuffCtl zGetData_LoopBuff_R;//Z����
IntLoopBuffCtl    GetDataNum_LoopBuff_R;
DoubleLoopBuffCtl xSave_LoopBuff_R;
DoubleLoopBuffCtl zSave_LoopBuff_R;
IntLoopBuffCtl    GetDataNumSt_LoopBuff_R;//�ɼ��������ݴ���txtʱ�õ���������Ŀ������
DoubleLoopBuffCtl xScbzLoopBuff_R;//ʵ���׼��X����
DoubleLoopBuffCtl zScbzLoopBuff_R;//ʵ���׼��Z����
DoubleLoopBuffCtl xHdmNodeLoopBuff_R;//����澫�ȵ�X����
DoubleLoopBuffCtl zHdmNodeLoopBuff_R;//����澫�ȵ�Z����
DoubleLoopBuffCtl DistHdmJd_LoofBuff_R;//����ֵ
DoubleLoopBuffCtl DistXmlJd_LoopBuff_R;//ϳĥ��
////BUFF����
//���
double  xGetData_Buff_L[Num_BuffLunkuo];
double  zGetData_Buff_L[Num_BuffLunkuo];
int     GetDataNum_Buff[Num_BuffLunkuoPoint];
double  x_Buff[Num_BuffLunkuo];
double  z_Buff[Num_BuffLunkuo];
int     GetDataNumSt_Buff[Num_BuffLunkuoPoint];
double  xScbzBuff_L[Num_BuffLunkuo];//ʵ���׼��X����
double  zScbzBuff_L[Num_BuffLunkuo];//ʵ���׼��Z����
double  xHdmNodeBuff_L[Num_BuffLunkuo];//����澫�ȵ�X����
double  zHdmNodeBuff_L[Num_BuffLunkuo];//����澫�ȵ�Z����
double  DistHdmNode_Buff_L[Num_BuffLunkuo];
double  DistXmlJd_Buff_L[Num_BuffLunkuo];
//int    OutLineNum_Buff_L[Num_BuffLunkuoPoint];
//int    HdmORXmlNum_Buff_L[Num_BuffLunkuoPoint];
//�Ҳ�
double  xGetData_Buff_R[Num_BuffLunkuo];
double  zGetData_Buff_R[Num_BuffLunkuo];
int  	GetDataNum_Buff_R[Num_BuffLunkuoPoint];
double  x_Buff_R[Num_BuffLunkuo];
double  z_Buff_R[Num_BuffLunkuo];
int     GetDataNumSt_Buff_R[Num_BuffLunkuoPoint];
double  xScbzBuff_R[Num_BuffLunkuo];//ʵ���׼��X����
double  zScbzBuff_R[Num_BuffLunkuo];//ʵ���׼��Z����
double  xHdmNodeBuff_R[Num_BuffLunkuo];//����澫�ȵ�X����
double  zHdmNodeBuff_R[Num_BuffLunkuo];//����澫�ȵ�Z����
double  DistHdmNode_Buff_R[Num_BuffLunkuo];
double  DistXmlJd_Buff_R[Num_BuffLunkuo];
//�洢�߳�
bool bStartStFlag = false;//�洢�߳�ȫ������Ϊfalse���߳̿���Ϊtrue
//���洢�߳�
bool bEndDealingFlag_L=false;//������ɱ�־λ
CCriticalSection HnuFileSection;
bool bEndSaveFlag_L=true;//�洢��ɱ�־λ
//�Ҳ�洢�߳�
bool bEndDealingFlag_R=false;//������ɱ�־λ		
CCriticalSection OutLineSection_R;
bool bEndSaveFlag_R=true;//�洢��ɱ�־λ


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHighPrecisionDlg �Ի���




CHighPrecisionDlg::CHighPrecisionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHighPrecisionDlg::IDD, pParent)
	, m_Edit_Distance2(0)
	, m_edit_distance_str(_T(""))
	, m_edit_distance2_str(_T(""))
	, Bomo_caiji_zhuangtai(_T(""))
	, Bomo_chuli_zhuangtai(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Edit_Distance = 0.0;
	m_Edit_DistanceReal=0.0;
	IsAfterMillFlag=FALSE;
	//double tmpPos[23]={-13,-10,-8,-6,-4,-2,-1,0,1,2,4,6,8,10,13,20,30,40,50,60,70,80,87};
	double tmpPos[23]={13,10,8,6,4,2,1,0,-1,-2,-4,-6,-8,-10,-13,-20,-30,-40,-50,-60,-70,-80,-87};
	//double tmp50Pos[19]={10,4,3,2,1,0,-1,-2,-3,-4,-10,-20,-30,-40,-50,-60,-70,-80,-90};
	for (int i=0;i<23;++i)
	{
		f60leftOutlinePos[i]=tmpPos[i];
		f60RightOutlinePos[i]=tmpPos[i];
	}
	//double tmp50Pos[19]={-10,-4,-3,-2,-1,0,1,2,3,4,10,20,30,40,50,60,70,80,90};
	double tmp50Pos[19]={10,4,3,2,1,0,-1,-2,-3,-4,-10,-20,-30,-40,-50,-60,-70,-80,-90};

	for (int i=0;i<19;++i)
	{
		f50leftOutlinePos[i]=tmp50Pos[i];
		f50RightOutlinePos[i]=tmp50Pos[i];
	}
	currentFileIndex=0;
	m_PrecisionFileOffset=0;
	m_LeftOutLineFileOffset=0;
	m_LeftMillingFileOffset=0;
	m_LeftBeforeOutlineFileOffset=0;
	m_RightOutLineFileOffset=0;
	m_RightMillingFileOffset=0;
	m_RightBeforeOutlineFileOffset=0;
	m_RightPrecisionFileOffset=0;
	localFileHdmVec.resize(23);
	RightlocalFileHdmVec.resize(23);
	m_PrecisionNumCnt=0;
	for (int i=0;i<23;++i)
	{
		localFileHdmVec[i]=NULL;
		RightlocalFileHdmVec[i]=NULL;
	}
	m_curOverValueIndex=0;
	m_OutlineType=1;
	bSingle=FALSE;  //��������ģʽ
	bChaoXian=FALSE; //����ģʽ
	HdmORXmlFilePath="";
	RightHdmORXmlFilePath=""; //���Ȼ���ϳĥ���ļ�·��
	bTongJi=FALSE; //ͳ��ģʽ
	maxLimit=0.5;
	/*pPrecisionAverage=NULL;
	pPrecisionMax=NULL;
	pRightPrecisionAverage=NULL;
	pRightPrecisionMax=NULL;*/
	/*pPrecisionAverage.resize(PRECISION_NUM_60);
	pPrecisionMax.resize(PRECISION_NUM_60);
	pRightPrecisionAverage.resize(PRECISION_NUM_60);
	pRightPrecisionMax.resize(PRECISION_NUM_60);*/
	m_fixedValueRatio=0.0;
	m_RightfixedValueRatio=0.0;

	double tmpX[8]={-21.62,-10.05,0.05,10.11,25.79,31.23,33.86,37.19};
	for (int i=0;i<8;++i)
	{
		startiLeftOutlineAnaPointX[i]=tmpX[i];
	}
	double tmpY[8]={0.94,1.94,2,1.59,-0.62,-3.2,-5.74,-14.63};
	for (int i=0;i<8;++i)
	{
		startiLeftOutlineAnaPointY[i]=tmpY[i];
	}

	double tmpendX[8]={-20.98,-9.96,0.05,9.88,24.84,28.82,30.75,33.19};
	for (int i=0;i<8;++i)
	{
		endiLeftOutlineAnaPointX[i]=tmpendX[i];
	}
	double tmpendY[8]={-3.04,-2.05,-2,-2.34,-4.51,-6.4,-8.26,-14.78};
	for (int i=0;i<8;++i)
	{
		endiLeftOutlineAnaPointY[i]=tmpendY[i];
	}
	StandardPointNum=0;
	StandardPointNum50=0;
	m_havePressAnalyse=FALSE;
}

void CHighPrecisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHARTCTRL1, m_ChartCtrl_LeftTop);
	DDX_Control(pDX, IDC_CHARTCTRL2, m_ChartCtrl_RightTop);
	DDX_Control(pDX, IDC_CHARTCTRL3, m_ChartCtrl_LeftDown);
	DDX_Control(pDX, IDC_CHARTCTRL4, m_ChartCtrl_RightDown);
	DDX_Control(pDX, IDC_COMBO_ModelSel, m_Combo_ModelSel);
	DDX_Control(pDX, IDC_COMBO_TotalDistance, m_Combo_TotalDistance);
	//DDX_Text(pDX, IDC_EDIT_Distance, m_Edit_Distance);
	//DDX_Text(pDX, IDC_EDIT_Distance, m_Edit_Distance);

	DDX_Control(pDX, IDC_SPIN1, m_Spin1);
	DDX_Control(pDX, IDC_LIST_FileName, m_List_FileName);
	DDX_Control(pDX, IDC_LIST_RES_DISP, m_List_ResultInfo);

	DDX_Control(pDX, IDC_MSCOMM_L, m_Mscomm_L);
	DDX_Control(pDX, IDC_MSCOMM_R, m_Mscomm_R);
	DDX_Radio(pDX, IDC_RADIO_FRONT, g_bFLagIsRunBack);
	//DDX_Text(pDX, IDC_EDIT_Distance2, m_Edit_Distance2);
	DDX_Text(pDX, IDC_EDIT_Distance, m_edit_distance_str);
	DDX_Text(pDX, IDC_EDIT_Distance2, m_edit_distance2_str);
	DDX_Control(pDX, IDC_CHARTCTRL5, Bomo_ChartCtrl_R2);
	DDX_Text(pDX, IDC_BMSTATA2, Bomo_caiji_zhuangtai);
	DDX_Text(pDX, IDC_BMSTATA1, Bomo_chuli_zhuangtai);
}

BEGIN_MESSAGE_MAP(CHighPrecisionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_2DTHREADMSG_L, On2DMsgFunc_L)
	ON_MESSAGE(WM_2DTHREADMSG_R, On2DMsgFunc_R)
	ON_MESSAGE(WM_2DTHREADMSG_XML_R,On2DMsgFunc_Xml_R)//�Ҳ�ϳĥ��
	ON_MESSAGE(WM_2DTHREADMSG_XMLscbz_R,On2DMsgFunc_XmlScbz_R)//�����Ҳ�ʵ���׼��
	ON_MESSAGE(WM_2DTHREADMSG_XML_L,On2DMsgFunc_Xml_L)//�Ҳ�ϳĥ��
	ON_MESSAGE(WM_2DTHREADMSG_XMLscbz_L,On2DMsgFunc_XmlScbz_L)//�����Ҳ�ʵ���׼��
	ON_MESSAGE(WM_DISPLAYCTRL,On2DDispDistance)
	ON_MESSAGE(WM_2DDISPLISTCTRL_L,On2DDispListCtrl_L)//��ʾ���ListCtrl
	ON_MESSAGE(WM_2DDISPLISTCTRL_R,On2DDispListCtrl_R)//��ʾ�Ҳ�ListCtrl

	ON_BN_CLICKED(IDC_BUTTON_LINK, &CHighPrecisionDlg::OnBnClickedButtonLink)
	ON_BN_CLICKED(IDC_BUTTON_TESTINFO, &CHighPrecisionDlg::OnBnClickedButtonTestinfo)
	ON_BN_CLICKED(IDC_BUTTON_START, &CHighPrecisionDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_TESTFLAG, &CHighPrecisionDlg::OnBnClickedButtonTestflag)
	ON_BN_CLICKED(IDC_BUTTON_ANALYZEFLAG, &CHighPrecisionDlg::OnBnClickedButtonAnalyzeflag)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_COMMAND(ID_32779, &CHighPrecisionDlg::OnSetSensorPara)
	ON_BN_CLICKED(IDC_BUTTON_INPUTFILE, &CHighPrecisionDlg::OnBnClickedButtonInputfile)
	ON_BN_CLICKED(IDC_BUTTON_ANALYZE, &CHighPrecisionDlg::OnBnClickedButtonAnalyze)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CHighPrecisionDlg::OnDeltaposSpin1)
	ON_CBN_SELCHANGE(IDC_COMBO_ModelSel, &CHighPrecisionDlg::OnCbnSelchangeComboModelsel)
	ON_BN_CLICKED(IDC_BUTTON_REPORT, &CHighPrecisionDlg::OnBnClickedButtonReport)
	ON_COMMAND(ID_32780, &CHighPrecisionDlg::OnMotorSetPara)
	ON_BN_CLICKED(IDC_BUTTON_STOPMOTOR, &CHighPrecisionDlg::OnBnClickedButtonStopmotor)
	ON_EN_SETFOCUS(IDC_EDIT_Distance, &CHighPrecisionDlg::OnEnSetfocusEditDistance)
	ON_COMMAND(ID_SETREPORTPARAM, &CHighPrecisionDlg::OnSetReportParam)
	ON_CBN_SELCHANGE(IDC_COMBO_TotalDistance, &CHighPrecisionDlg::OnCbnSelchangeComboTotaldistance)
	ON_COMMAND(ID_Menu_Link, &CHighPrecisionDlg::OnClickMenuLink)
	ON_COMMAND(ID_Menu_TestInfo, &CHighPrecisionDlg::OnClickMenuTestinfo)
	ON_COMMAND(ID_Menu_TestStart, &CHighPrecisionDlg::OnClickMenuTeststart)
	ON_COMMAND(ID_Menu_MotorStop, &CHighPrecisionDlg::OnClickMenuMotorstop)
	ON_COMMAND(ID_Menu_TestStop, &CHighPrecisionDlg::OnClickMenuTeststop)
	ON_COMMAND(ID_Menu_InputFile, &CHighPrecisionDlg::OnClickMenuInputfile)
	ON_COMMAND(ID_Menu_Anaylze, &CHighPrecisionDlg::OnClickMenuAnaylze)
	ON_COMMAND(ID_Menu_Reprot, &CHighPrecisionDlg::OnClickMenuReprot)
//	ON_EN_UPDATE(IDC_EDIT_Distance, &CHighPrecisionDlg::OnEnUpdateEditDistance)
//	ON_EN_CHANGE(IDC_EDIT_Distance, &CHighPrecisionDlg::OnEnChangeEditDistance)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RES_DISP, &CHighPrecisionDlg::OnNMDblclkListResDisp)
	//ON_BN_CLICKED(IDC_RADIO_BACK1, &CHighPrecisionDlg::OnBnClickedRadioBack1)
	ON_BN_CLICKED(IDC_RADIO_FRONT, &CHighPrecisionDlg::OnBnClickedRadioFront)
	ON_BN_CLICKED(IDC_RADIO_BACK, &CHighPrecisionDlg::OnBnClickedRadioBack)
//	ON_EN_UPDATE(IDC_EDIT_Distance2, &CHighPrecisionDlg::OnEnUpdateEditDistance2)
	ON_STN_CLICKED(IDC_STATIC10, &CHighPrecisionDlg::OnStnClickedStatic10)
//	ON_EN_CHANGE(IDC_EDIT_Distance2, &CHighPrecisionDlg::OnEnChangeEditDistance2)
//ON_EN_CHANGE(IDC_EDIT_Distance, &CHighPrecisionDlg::OnEnChangeEditDistance)
//ON_EN_CHANGE(IDC_EDIT_Distance2, &CHighPrecisionDlg::OnEnChangeEditDistance2)
ON_EN_KILLFOCUS(IDC_EDIT_Distance, &CHighPrecisionDlg::OnEnKillfocusEditDistance)
ON_EN_KILLFOCUS(IDC_EDIT_Distance2, &CHighPrecisionDlg::OnEnKillfocusEditDistance2)
ON_EN_SETFOCUS(IDC_EDIT_Distance2, &CHighPrecisionDlg::OnEnSetfocusEditDistance2)
ON_STN_CLICKED(IDC_DISTANCE_LINE, &CHighPrecisionDlg::OnStnClickedDistanceLine)


/////////////////////////////////////////////////////////////zhang

ON_COMMAND(IDC_TOOlBT_LINK, &CHighPrecisionDlg::OnTbtClicklink)
ON_COMMAND(IDC_TOOlBT_TESTINFO, &CHighPrecisionDlg::OnTbtClicktestinfo)
ON_COMMAND(IDC_TOOlBT_CONTOUR, &CHighPrecisionDlg::OnTbtClickcontour)
ON_COMMAND(IDC_TOOlBT_BOMO, &CHighPrecisionDlg::OnTbtClickbomo)
ON_COMMAND(IDC_TOOlBT_ANALYZE, &CHighPrecisionDlg::OnTbtClickanalyze)
ON_COMMAND(IDC_TOOlBT_HDATA, &CHighPrecisionDlg::OnTbtClickhdata)
ON_COMMAND(IDC_TOOlBT_START, &CHighPrecisionDlg::OnTbtClickstart)
ON_COMMAND(IDC_TOOlBT_PAUSE, &CHighPrecisionDlg::OnTbtClickpause)
ON_COMMAND(IDC_TOOlBT_STOP, &CHighPrecisionDlg::OnTbtClickstop)
/////////////////////////////////////////////////////////////zhang
ON_STN_CLICKED(IDC_BMSTATA1, &CHighPrecisionDlg::OnStnClickedBmstata1)
ON_STN_CLICKED(IDC_BMSTATA5, &CHighPrecisionDlg::OnStnClickedBmstata5)
ON_WM_TIMER()
ON_STN_CLICKED(IDC_STATIC_SYSTEMSTATUS, &CHighPrecisionDlg::OnStnClickedStaticSystemstatus)
END_MESSAGE_MAP()


// CHighPrecisionDlg ��Ϣ�������

BOOL CHighPrecisionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*��ĥ����*/





	/*��ĥ����*/

	CFont* f;
	f=new CFont;
	f->CreateFont(11,0,0,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,_T("����"));
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(false);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, false);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);//�������
	btn1.SubclassDlgItem(IDC_BUTTON_TESTFLAG,this);
	btn1.SetAlign(CButtonST::ST_ALIGN_VERT);
	btn1.DrawTransparent(TRUE);
	btn1.SetIcon(IDI_ICON1);
	

	btn2.SubclassDlgItem(IDC_BUTTON_ANALYZEFLAG,this);
	btn2.SetAlign(CButtonST::ST_ALIGN_VERT);
	btn2.DrawTransparent(TRUE);
	btn2.SetIcon(IDI_ICON2);
	

	btn3.SubclassDlgItem(IDC_BUTTON_LINK,this);
	btn3.SetAlign(CButtonST::ST_ALIGN_VERT);
	btn3.DrawTransparent(TRUE);
	btn3.SetIcon(IDI_ICON3);
	GetDlgItem(IDC_BUTTON_LINK)->SetFont(f);
	

	btn4.SubclassDlgItem(IDC_BUTTON_TESTINFO,this);
	btn4.SetAlign(CButtonST::ST_ALIGN_VERT);
	btn4.DrawTransparent(TRUE);
	btn4.SetIcon(IDI_ICON4);
	GetDlgItem(IDC_BUTTON_TESTINFO)->SetFont(f);
	

	btn5.SubclassDlgItem(IDC_BUTTON_INPUTFILE,this);
	btn5.SetAlign(CButtonST::ST_ALIGN_VERT);
	btn5.DrawTransparent(TRUE);
	btn5.SetIcon(IDI_ICON5);
	GetDlgItem(IDC_BUTTON_INPUTFILE)->SetFont(f);
	

	btn6.SubclassDlgItem(IDC_BUTTON_REPORT,this);
	btn6.SetAlign(CButtonST::ST_ALIGN_VERT);
	btn6.DrawTransparent(TRUE);
	btn6.SetIcon(IDI_ICON7);
	GetDlgItem(IDC_BUTTON_REPORT)->SetFont(f);
	

	btn7.SubclassDlgItem(IDC_BUTTON_ANALYZE,this);
	GetDlgItem(IDC_BUTTON_ANALYZE)->SetFont(f);
	btn7.SetAlign(CButtonST::ST_ALIGN_VERT);
	btn7.DrawTransparent(TRUE);
	btn7.SetIcon(IDI_ICON6);
	
	
	btn9.SubclassDlgItem(IDC_BUTTON_STOPMOTOR,this);
	btn9.SetAlign(CButtonST::ST_ALIGN_VERT);
	btn9.DrawTransparent(TRUE);
	btn9.SetIcon(IDI_ICON10);
	GetDlgItem(IDC_BUTTON_STOPMOTOR)->SetFont(f);

	btn10.SubclassDlgItem(IDC_BUTTON_START,this);
	btn10.SetAlign(CButtonST::ST_ALIGN_VERT);
	btn10.DrawTransparent(TRUE);
	btn10.SetIcon(IDI_ICON8);
	GetDlgItem(IDC_BUTTON_START)->SetFont(f);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	pdlg= this;//�����߳��в������еĿؼ�
	//CRect rect;//����Ϊȫ�ֱ���
	m_List_ResultInfo.GetClientRect(&rect);
	//��դ��
	m_List_ResultInfo.SetExtendedStyle(m_List_ResultInfo.GetExtendedStyle() 
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List_ResultInfo.InsertColumn(0,_T("�Ƕ�"),LVCFMT_CENTER,30,0);

	
	//m_List_ResultInfo.InsertColumn(1,_T("���Ͼ���"),LVCFMT_CENTER,100,1);
	//m_List_ResultInfo.InsertColumn(2,_T("�Һ�Ͼ���"),LVCFMT_CENTER,100,2);	
	//m_MainMenu.LoadMenu(IDR_MAINMENU);
	//SetMenu(&m_MainMenu);//���ò˵�
	//skinppSetSkinResID(m_hWnd,IDD_HIGHPRECISION_DIALOG);
	//skinppSetDrawMenu(m_MainMenu,FALSE);
	m_MainMenu=GetMenu();
	//�˵�����
	m_MainMenu->EnableMenuItem(ID_Menu_Anaylze,MF_DISABLED|MF_GRAYED);//�ļ�����
	m_MainMenu->EnableMenuItem(ID_Menu_Reprot,MF_DISABLED|MF_GRAYED);//���ɱ���
	m_MainMenu->EnableMenuItem(ID_Menu_InputFile,MF_DISABLED|MF_GRAYED);//�����ļ�
	m_MainMenu->EnableMenuItem(ID_SETREPORTPARAM, MF_DISABLED | MF_GRAYED);//�����ļ�shen

	m_MainMenu->EnableMenuItem(ID_Menu_Link,MF_DISABLED|MF_GRAYED);//�����豸
	m_MainMenu->EnableMenuItem(ID_Menu_TestInfo,MF_DISABLED|MF_GRAYED);//��������Ϣ
	m_MainMenu->EnableMenuItem(ID_Menu_TestStart,MF_DISABLED|MF_GRAYED);//��ʼ���
	m_MainMenu->EnableMenuItem(ID_Menu_TestStop,MF_DISABLED|MF_GRAYED);//ֹͣ���
	m_MainMenu->EnableMenuItem(ID_Menu_MotorStop,MF_DISABLED|MF_GRAYED);//��ͣ���
	//����
	GetDlgItem(IDC_BUTTON_LINK)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_TESTINFO)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_ANALYZE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_INPUTFILE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_REPORT)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_STOPMOTOR)->EnableWindow(false);
	GetDlgItem(IDC_SPIN1)->EnableWindow(false);
	GetDlgItem(IDC_EDIT_Distance)->EnableWindow(false);
	GetDlgItem(IDC_EDIT_Distance2)->EnableWindow(false);

	GetDlgItem(IDC_COMBO_ModelSel)->EnableWindow(false);
	//�����ʼ��ťǰ�ǵ�����ť�ġ��ǡ�Ϊ�ң���ʼ֮����ܵ������
	GetDlgItem(IDC_RADIO_BACK)->EnableWindow(false);
	//������̼��
	GetDlgItem(IDC_STATIC_TotalDistance)->ShowWindow(SW_HIDE);
	m_Combo_TotalDistance.ShowWindow(SW_HIDE);
	//��ͼ�ؼ��ĳ�ʼ��

	//*********************************************/��ĥ��ʼ*********************************************//
	//*********************************************/��ĥ��ʼ*********************************************//
	//*********************************************/��ĥ��ʼ*********************************************//
	//*********************************************/��ĥ��ʼ*********************************************//


	//�ֿ۳�ʼ��
	CChartAxis *pAxis = NULL;
	//�ײ��Ĳ���
	pAxisBottom_bomo_R = Bomo_ChartCtrl_R2.CreateStandardAxis(CChartCtrl::BottomAxis);
	//pAxisBottom1->SetAutomatic(true); 
	pAxisBottom_bomo_R->GetLabel()->SetText(_T("���(mm)"));
	pAxisBottom_bomo_R->SetAutomatic(true);
	//pAxisBottom_bomo_R->SetMinMax(-30, 40);



	//��ߵ�����
	pAxisLeft_bomo_R = Bomo_ChartCtrl_R2.CreateStandardAxis(CChartCtrl::LeftAxis);
	//pAxisBottom1->SetAutomatic(true); 
	pAxisLeft_bomo_R->GetLabel()->SetText(_T("����(mm)"));
	pAxisLeft_bomo_R->SetAutomatic(true);
	//pAxisLeft_bomo_R->SetMinMax(-30, 40);
	//CChartAxis *pAxis = NULL;


	//CRect Bomo_rect;
	//CChartAxis *Bomo_pAxis = NULL;
	//CChartDateTimeAxis* Bomo_pDateAxis = NULL;
	//Bomo_pDateAxis = NULL;
	////ƽ˳�������꽨��
	//GetDlgItem(IDC_STATIC_paint)->GetWindowRect(Bomo_rect);
	//GetDlgItem(IDC_STATIC_paint)->ShowWindow(SW_HIDE);
	//ScreenToClient(Bomo_rect);
	//Bomo_ChartCtrl_R2.Create(this, Bomo_rect, 4);
	////��ʼ������

	//Bomo_pAxis = Bomo_ChartCtrl_R2.CreateStandardAxis(CChartCtrl::BottomAxis);
	//Bomo_pAxis->SetAutomatic(true);//�Զ��������꺯��
	//Bomo_pAxis->GetLabel()->SetText(_T("����(mm)"));
	//						  //pDateAxis->SetTickLabelFormat(false,_T("%m��%d��"));  
	//Bomo_pAxis = Bomo_ChartCtrl_R2.CreateStandardAxis(CChartCtrl::LeftAxis);
	//Bomo_pAxis->SetAutomatic(true);







	Bomo_ChartCtrl_R2.SetBackGradient(RGB(255, 255, 255), RGB(213, 223, 243), gtVertical);//���ñ�����ɫ


	CChartFont titleFont_bomo;
	titleFont_bomo.SetFont(_T("����"), 100, false, true, false);
	Bomo_ChartCtrl_R2.GetTitle()->SetFont(titleFont_bomo);
	Bomo_ChartCtrl_R2.GetTitle()->SetColor(RGB(156, 170, 193));

	Bomo_ChartCtrl_R2.GetTitle()->AddString(_T("��첨ĥ"));
	Bomo_ChartCtrl_R2.GetTitle()->SetFont(titleFont_bomo);
	Bomo_ChartCtrl_R2.GetTitle()->SetColor(RGB(156, 170, 193));
	//����������



	//for (int i = 0; i < Bomo_paint_arrayLength; i++)
	//{
	//	Bomo_paint_X_R1[i] = i;
	//	Bomo_paint_Y_TeeChartArray_R1[i] = 1;
	//}

	//Bomo_pLineSerie_R1->AddPoints(Bomo_paint_X_R1, Bomo_paint_Y_TeeChartArray_R1, Bomo_paint_arrayLength);
	//Bomo_ChartCtrl_R.EnableRefresh(true);

	Bomo_paint_X_cout_R = Bomo_paint_arrayLength;//��ͼ�ƶ�������ʼ��ֵ
	Bomo_paint_X_cout_R = Bomo_paint_arrayLength;//��¼������
	Bomo_paint_count_R = 0;//��ͼ����
	//*********************************************/��ĥ����*********************************************//
	//*********************************************/��ĥ����*********************************************//
	//*********************************************/��ĥ����*********************************************//
	//*********************************************/��ĥ����*********************************************//

	//���IDC_CHARTCTRL1
 
	pAxisBottom1 = m_ChartCtrl_LeftTop.CreateStandardAxis(CChartCtrl::BottomAxis); 
	//pAxisBottom1->SetAutomatic(true); 
	pAxisBottom1->GetLabel()->SetText(_T("���(mm)"));
	pAxisBottom1->SetAutomatic(false);  
	pAxisBottom1->SetMinMax(-30,40);


	pAxisLeft1 = m_ChartCtrl_LeftTop.CreateStandardAxis(CChartCtrl::LeftAxis); 
	//pAxisLeft1->SetAutomatic(true); 
	pAxisLeft1->SetAutomatic(false);
	pAxisLeft1->SetMinMax(-35,5);

	m_ChartCtrl_LeftTop.SetBackGradient(RGB(255,255,255),RGB(213,223,243),gtVertical); 
	m_pLineSerie_LT = m_ChartCtrl_LeftTop.CreateLineSerie();
	m_pLineSerie_LT->SetSeriesOrdering(poNoOrdering);
	m_pLineSerie_LT->SetColor(RGB(0,0,255));//��ɫ
	m_sLineSerie_LT = m_ChartCtrl_LeftTop.CreateLineSerie();
	m_sLineSerie_LT->SetSeriesOrdering(poNoOrdering);
	m_sLineSerie_LT->SetColor(RGB(255,0,0));//��ɫ
	//����ϳĥʵ���׼��
	m_pLineSerieStd_LT=m_ChartCtrl_LeftTop.CreateLineSerie();
	m_pLineSerieStd_LT->SetSeriesOrdering(poNoOrdering);
	m_pLineSerieStd_LT->SetColor(RGB(255,0,0));//��ɫ

	pAxisBottom3 = m_ChartCtrl_LeftDown.CreateStandardAxis(CChartCtrl::BottomAxis);
	//pAxisBottom3->SetAutomatic(true); 
	pAxisBottom3->SetAutomatic(false);  
	pAxisBottom3->SetMinMax(-10,90);
	pAxisBottom3->GetLabel()->SetText(_T("�Ƕ�(��)"));
	pAxisBottom3->SetInverted(TRUE);

	pAxisLeft3 = m_ChartCtrl_LeftDown.CreateStandardAxis(CChartCtrl::LeftAxis);  
	//pAxisLeft3->SetAutomatic(true); 
	pAxisLeft3->SetAutomatic(true);
	pAxisLeft3->SetMinMax(-1,1);
	 m_ChartCtrl_LeftDown.SetBackGradient(RGB(255,255,255),RGB(213,223,243),gtVertical); 
	m_pLineSerie_LB = m_ChartCtrl_LeftDown.CreateLineSerie();//��������
	m_pLineSerie_LB->SetColor(RGB(0,0,255));//��ɫ
	//m_pLineSerie_LB->SetWidth(2);
	m_PointSerie_LB = m_ChartCtrl_LeftDown.CreatePointsSerie();//���µ�ͼ
	m_PointSerie_LB->SetPointSize(4,4);
	m_PointSerie_LB->SetColor(RGB(255,0,0));//��ɫ
	m_PointSerie_LB->SetBorderColor(RGB(255,0,0));
	//�Ҳ� 
	pAxisBottom2 = m_ChartCtrl_RightTop.CreateStandardAxis(CChartCtrl::BottomAxis);  
	pAxisBottom2->SetAutomatic(false);  
	pAxisBottom2->SetMinMax(-40,30);
	pAxisBottom2->GetLabel()->SetText(_T("���(mm)"));
	//pAxisBottom2->SetAutomatic(true); 
	pAxisLeft2 = m_ChartCtrl_RightTop.CreateStandardAxis(CChartCtrl::LeftAxis);  
	pAxisLeft2->SetAutomatic(false);
	pAxisLeft2->SetMinMax(-35,5);
	//pAxisLeft2->SetAutomatic(true); 
	m_ChartCtrl_RightTop.SetBackGradient(RGB(255,255,255),RGB(213,223,243),gtVertical); 
	m_pLineSerie_RT= m_ChartCtrl_RightTop.CreateLineSerie();
	m_pLineSerie_RT->SetSeriesOrdering(poNoOrdering);
	m_pLineSerie_RT->SetColor(RGB(0,0,255));//��ɫ
	m_sLineSerie_RT =m_ChartCtrl_RightTop.CreateLineSerie();
	m_sLineSerie_RT->SetSeriesOrdering(poNoOrdering);
	m_sLineSerie_RT->SetColor(RGB(255,0,0));//��ɫ
	pAxisBottom4 = m_ChartCtrl_RightDown.CreateStandardAxis(CChartCtrl::BottomAxis);  
	pAxisBottom4->SetAutomatic(false);  
	pAxisBottom4->SetMinMax(-10,90);
	pAxisBottom4->SetInverted(FALSE);
	pAxisBottom4->GetLabel()->SetText(_T("�Ƕ�(��)"));
	//pAxisBottom4->SetAutomatic(true); 
	pAxisLeft4 = m_ChartCtrl_RightDown.CreateStandardAxis(CChartCtrl::LeftAxis);  
	pAxisLeft4->SetAutomatic(true);
	pAxisLeft4->SetMinMax(-1,1);
	//pAxisLeft4->SetAutomatic(true); 
	m_ChartCtrl_RightDown.SetBackGradient(RGB(255,255,255),RGB(213,223,243),gtVertical); 
	m_pLineSerie_RB = m_ChartCtrl_RightDown.CreateLineSerie();//��������
	m_pLineSerie_RB->SetColor(RGB(0,0,255));//��ɫ
	//m_pLineSerie_RB->SetWidth(2);

	m_PointSerie_RB = m_ChartCtrl_RightDown.CreatePointsSerie();//���µ�ͼ
	m_PointSerie_RB->SetPointSize(4,4);
	m_PointSerie_RB->SetColor(RGB(255,0,0));//��ɫ
	m_PointSerie_RB->SetBorderColor(RGB(255,0,0));
	//�Ҳ�ʵ���׼��
	m_pLineSerieStd_RT=m_ChartCtrl_RightTop.CreateLineSerie();
	m_pLineSerieStd_RT->SetSeriesOrdering(poNoOrdering);
	m_pLineSerieStd_RT->SetColor(RGB(255,0,0));//��ɫ
	m_ChartCtrl_LeftTop.GetTitle()->AddString(_T("�������"));

	CChartFont titleFont;
	titleFont.SetFont(_T("����"),100,false,true,false);
	m_ChartCtrl_LeftTop.GetTitle()->SetFont(titleFont);
	m_ChartCtrl_LeftTop.GetTitle()->SetColor(RGB(156,170,193));

	m_ChartCtrl_RightTop.GetTitle()->AddString(_T("�ҹ�����"));
	m_ChartCtrl_RightTop.GetTitle()->SetFont(titleFont);
	m_ChartCtrl_RightTop.GetTitle()->SetColor(RGB(156,170,193));

	m_ChartCtrl_LeftDown.GetTitle()->AddString(_T("�����"));
	m_ChartCtrl_LeftDown.GetTitle()->SetFont(titleFont);
	m_ChartCtrl_LeftDown.GetTitle()->SetColor(RGB(156,170,193));

	m_ChartCtrl_RightDown.GetTitle()->AddString(_T("�����"));
	m_ChartCtrl_RightDown.GetTitle()->SetFont(titleFont);
	m_ChartCtrl_RightDown.GetTitle()->SetColor(RGB(156,170,193));


	CChartFont axisFont;
	axisFont.SetFont(_T("����"),100,false,false,false);
	pAxisBottom1->GetLabel()->SetFont(axisFont);
	pAxisBottom1->GetLabel()->SetColor(RGB(0,0,0));
	pAxisBottom2->GetLabel()->SetFont(axisFont);
	pAxisBottom2->GetLabel()->SetColor(RGB(0,0,0));
	pAxisBottom3->GetLabel()->SetFont(axisFont);
	pAxisBottom3->GetLabel()->SetColor(RGB(0,0,0));
	pAxisBottom4->GetLabel()->SetFont(axisFont);
	pAxisBottom4->GetLabel()->SetColor(RGB(0,0,0));
	//��������С
	CRect rect1;      
	GetClientRect(&rect1);     
	Old.x=rect1.right-rect1.left;
	Old.y=rect1.bottom-rect1.top;
	rect1.top=0;
	rect1.left=0;
	//��������ʼ��
	//���
	LoopBuff.LoopBuffInit(&xGetData_LoopBuff_L,Num_BuffLunkuo,xGetData_Buff_L);
	LoopBuff.LoopBuffInit(&zGetData_LoopBuff_L,Num_BuffLunkuo,zGetData_Buff_L);
	LoopBuff.LoopBuffInit(&GetDataNum_LoopBuff_L,Num_BuffLunkuoPoint,GetDataNum_Buff);
	LoopBuff.LoopBuffInit(&xSave_LoopBuff_L,Num_BuffLunkuo,x_Buff);
	LoopBuff.LoopBuffInit(&zSave_LoopBuff_L,Num_BuffLunkuo,z_Buff);
	LoopBuff.LoopBuffInit(&GetDataNumSt_LoopBuff_L,Num_BuffLunkuoPoint,GetDataNumSt_Buff);
	LoopBuff.LoopBuffInit(&xScbzLoopBuff_L,Num_BuffLunkuo,xScbzBuff_L);
	LoopBuff.LoopBuffInit(&zScbzLoopBuff_L,Num_BuffLunkuo,zScbzBuff_L);
	LoopBuff.LoopBuffInit(&xHdmNodeLoopBuff_L,Num_BuffLunkuo,xHdmNodeBuff_L);
	LoopBuff.LoopBuffInit(&zHdmNodeLoopBuff_L,Num_BuffLunkuo,zHdmNodeBuff_L);
	LoopBuff.LoopBuffInit(&DistHdmJd_LoofBuff_L,Num_BuffLunkuo,DistHdmNode_Buff_L);
	LoopBuff.LoopBuffInit(&DistXmlJd_LoopBuff_L,Num_BuffLunkuo,DistXmlJd_Buff_L);
	//LoopBuff.LoopBuffInit(&OutLine_LoopBuff_L,Num_BuffLunkuoPoint,OutLineNum_Buff_L);
	//LoopBuff.LoopBuffInit(&HdmORXmlNum_loopBuff_L,Num_BuffLunkuoPoint,HdmORXmlNum_Buff_L);
	//�Ҳ�
	LoopBuff.LoopBuffInit(&xGetData_LoopBuff_R,Num_BuffLunkuo,xGetData_Buff_R);
	LoopBuff.LoopBuffInit(&zGetData_LoopBuff_R,Num_BuffLunkuo,zGetData_Buff_R);
	LoopBuff.LoopBuffInit(&GetDataNum_LoopBuff_R,Num_BuffLunkuoPoint,GetDataNum_Buff_R);
	LoopBuff.LoopBuffInit(&xSave_LoopBuff_R,Num_BuffLunkuo,x_Buff_R);
	LoopBuff.LoopBuffInit(&zSave_LoopBuff_R,Num_BuffLunkuo,z_Buff_R);
	LoopBuff.LoopBuffInit(&GetDataNumSt_LoopBuff_R,Num_BuffLunkuoPoint,GetDataNumSt_Buff_R);
	LoopBuff.LoopBuffInit(&xScbzLoopBuff_R,Num_BuffLunkuo,xScbzBuff_R);
	LoopBuff.LoopBuffInit(&zScbzLoopBuff_R,Num_BuffLunkuo,zScbzBuff_R);
	LoopBuff.LoopBuffInit(&xHdmNodeLoopBuff_R,Num_BuffLunkuo,xHdmNodeBuff_R);
	LoopBuff.LoopBuffInit(&zHdmNodeLoopBuff_R,Num_BuffLunkuo,zHdmNodeBuff_R);
	LoopBuff.LoopBuffInit(&DistHdmJd_LoofBuff_R,Num_BuffLunkuo,DistHdmNode_Buff_R);	
	LoopBuff.LoopBuffInit(&DistXmlJd_LoopBuff_R,Num_BuffLunkuo,DistXmlJd_Buff_R);
	bFlagStartThread =false;


	//�����������
	//ϳĥ��ϳĥǰ����׼�������߳�ʼ��
	m_pLeftTopStandardLineSerie=m_ChartCtrl_LeftTop.CreateLineSerie();
	m_pLeftTopStandardLineSerie->SetColor(RGB(255,0,0));
	m_pLeftTopStandardLineSerie->SetSeriesOrdering(poNoOrdering);//���ó�����
	/*m_pLeftTopStandardLineSerie->SetWidth(4);*/

	m_pLeftTopAfterLineSerie=m_ChartCtrl_LeftTop.CreateLineSerie();
	m_pLeftTopAfterLineSerie->SetColor(RGB(0,0,255));
	m_pLeftTopAfterLineSerie->SetSeriesOrdering(poNoOrdering);//���ó�����
	/*m_pLeftTopAfterLineSerie->SetWidth(4);*/

	m_pLeftTopBeforeLineSerie=m_ChartCtrl_LeftTop.CreateLineSerie();
	m_pLeftTopBeforeLineSerie->SetColor(RGB(255,0,0));
	m_pLeftTopBeforeLineSerie->SetSeriesOrdering(poNoOrdering);//���ó�����
	/*m_pLeftTopBeforeLineSerie->SetWidth(4);*/

	m_pLeftTopLineSerie=m_ChartCtrl_LeftTop.CreateLineSerie();
	m_pLeftTopLineSerie->SetColor(RGB(0,0,255));
	/*m_pLeftTopLineSerie->SetWidth(4);*/
	m_pLeftTopPointSerie=m_ChartCtrl_LeftTop.CreatePointsSerie();

	//set the color of point
	m_pLeftTopPointSerie->SetColor(RGB(255,0,0));
	m_pLeftTopPointSerie->SetBorderColor(RGB(255,0,0));
	//set the size of point
	m_pLeftTopPointSerie->SetPointSize(4,4);

	m_pMaxLeftTopLineSerie=m_ChartCtrl_LeftTop.CreateLineSerie();
	m_pMaxLeftTopLineSerie->SetColor(RGB(0,255,0));
	m_pMaxLeftTopPointSerie=m_ChartCtrl_LeftTop.CreatePointsSerie();
	//set the color of point
	m_pMaxLeftTopPointSerie->SetColor(RGB(0,0,0));
	m_pMaxLeftTopPointSerie->SetBorderColor(RGB(0,0,0));
	//set the size of point
	m_pMaxLeftTopPointSerie->SetPointSize(4,4);


	m_pLeftBottomPointSerie=m_ChartCtrl_LeftDown.CreatePointsSerie();
	m_pLeftBottomPointSerie->SetColor(RGB(255,0,0));
	m_pLeftBottomPointSerie->SetBorderColor(RGB(255,0,0));
	//set the size of point
	m_pLeftBottomPointSerie->SetPointSize(4,4);

	m_pLeftBottomLineSerie = m_ChartCtrl_LeftDown.CreateLineSerie();
	//set the color of point
	m_pLeftBottomLineSerie->SetColor(RGB(0,0,255));


	//ϳĥ��ϳĥǰ����׼�������߳�ʼ��
	m_pRightTopStandardLineSerie=m_ChartCtrl_RightTop.CreateLineSerie();
	m_pRightTopStandardLineSerie->SetColor(RGB(255,0,0));
	m_pRightTopStandardLineSerie->SetSeriesOrdering(poNoOrdering);//���ó�����
	/*m_pRightTopStandardLineSerie->SetWidth(4);*/

	m_pRightTopAfterLineSerie=m_ChartCtrl_RightTop.CreateLineSerie();
	m_pRightTopAfterLineSerie->SetColor(RGB(0,0,255));
	m_pRightTopAfterLineSerie->SetSeriesOrdering(poNoOrdering);//���ó�����
	/*m_pRightTopAfterLineSerie->SetWidth(4);*/

	m_pRightTopBeforeLineSerie=m_ChartCtrl_RightTop.CreateLineSerie();
	m_pRightTopBeforeLineSerie->SetColor(RGB(255,0,0));
	m_pRightTopBeforeLineSerie->SetSeriesOrdering(poNoOrdering);//���ó�����
	/*m_pRightTopBeforeLineSerie->SetWidth(4);*/

	m_pRightTopLineSerie=m_ChartCtrl_RightTop.CreateLineSerie();
	m_pRightTopLineSerie->SetColor(RGB(0,0,255));
	/*m_pRightTopLineSerie->SetWidth(4);*/
	m_pRightTopPointSerie=m_ChartCtrl_RightTop.CreatePointsSerie();

	//set the color of point
	m_pRightTopPointSerie->SetColor(RGB(255,0,0));
	m_pRightTopPointSerie->SetBorderColor(RGB(255,0,0));
	//set the size of point
	m_pRightTopPointSerie->SetPointSize(4,4);

	m_pMaxRightTopLineSerie=m_ChartCtrl_RightTop.CreateLineSerie();
	m_pMaxRightTopLineSerie->SetColor(RGB(0,255,0));
	/*m_pMaxRightTopLineSerie->SetWidth(4);*/
	m_pMaxRightTopPointSerie=m_ChartCtrl_RightTop.CreatePointsSerie();
	//set the color of point
	m_pMaxRightTopPointSerie->SetColor(RGB(0,0,0));
	m_pMaxRightTopPointSerie->SetBorderColor(RGB(0,0,0));
	//set the size of point
	m_pMaxRightTopPointSerie->SetPointSize(4,4);

	m_pRightBottomPointSerie=m_ChartCtrl_RightDown.CreatePointsSerie();
	m_pRightBottomPointSerie->SetColor(RGB(255,0,0));
	m_pRightBottomPointSerie->SetBorderColor(RGB(255,0,0));
	//set the size of point
	m_pRightBottomPointSerie->SetPointSize(4,4);

	m_pRightBottomLineSerie = m_ChartCtrl_RightDown.CreateLineSerie();
	//set the color of point
	m_pRightBottomLineSerie->SetColor(RGB(0,0,255));

	m_Spin1.SetRange(0,20000);
	UDACCEL Acc;
	Acc.nSec = 0;
	Acc.nInc = 1;
	m_Spin1.SetAccel(1, &Acc);

	//��Combo�ؼ����ֻ��
	CEdit *pEdit=(CEdit *)m_Combo_ModelSel.GetWindow(GW_CHILD);
	pEdit->SetReadOnly(TRUE);
	pEdit=(CEdit *)m_Combo_TotalDistance.GetWindow(GW_CHILD);
	pEdit->SetReadOnly(TRUE);

	m_editFont.CreatePointFont(180,"����");
	GetDlgItem(IDC_STATIC12)->SetFont(&m_editFont);

	bFlagStopMt=true;//�����ͣ��ťĬ����ʾΪ��ͣ��FALSEʱ��ʾ��ʾΪ�������
	bFlagStopMt_L=true;
    bFlagStopMt_R=true;


	/////////////////////////////////////////////////////////////zhang
	if (!m_toolbar.CreateEx(this, TBSTYLE_TOOLTIPS | TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) || !m_toolbar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to Create Dialog ToolBar\n");
		EndDialog(IDCANCEL);
	}
	m_toolbar.EnableToolTips(TRUE);
	m_toolbar.ShowWindow(SW_SHOW);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	///GetDlgItem(IDC_BMCHECK1)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMCHECK2)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMCHECK3)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATA1)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATA2)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATA3)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATA4)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATA5)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATA6)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATA7)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATA8)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATA9)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATA10)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATAL1)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATAL2)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATAL3)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATAL4)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATAL5)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_BMSTATAL6)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_CHARTCTRL5)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_CHARTCTRL6)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_GROUP_BOMO)->ShowWindow(SW_HIDE);

//
//	GetDlgItem(IDC_GROUP_BOMO)->ShowWindow(SW_HIDE);
	//Bomo_TestDlg = new CBomo_TestDlg();
	//Bomo_TestDlg->Create(IDD_DIALOG_BOMO, GetDlgItem(IDC_GROUP_BOMO));
	//Bomo_TestDlg->ShowWindow(SW_HIDE);
	/////////////////////////////////////////////////////////////zhang

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHighPrecisionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHighPrecisionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	//����������ʱ�Զ����������豸����
	//CConnectDeviceDlg obj_ConnectDevice;
	//obj_ConnectDevice.DoModal();
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHighPrecisionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CHighPrecisionDlg::OnBnClickedButtonLink()
{

	if(g_bFlagSensorL/*&&g_bFlagSensorR&&g_bFlagMotor_L&&g_bFlagMotor_R*/)
	{
		ZLDS200DisConnectAll();		
		//m_MachineCtrl_L.DisConnectMotor(m_Mscomm_L,true,false);
		//m_MachineCtrl_L.DisConnectMotor(m_Mscomm_R,true,false);
		SetDlgItemText(IDC_BUTTON_LINK,_T("�����豸"));
		g_bFlagSensorL=false;
		g_bFlagSensorR=false;
		/*g_bFlagMotor_L=false;
		g_bFlagMotor_R=false;*/
	}
	else 
	{
		CConnectDeviceDlg obj_ConnectDevice;
		if(obj_ConnectDevice.DoModal() == IDOK)
		{
			if(g_bFlagSensorL/*&&g_bFlagSensorR&&g_bFlagMotor_L&&g_bFlagMotor_R*/)
			{
				SetDlgItemText(IDC_BUTTON_LINK,_T("�Ͽ��豸"));
				SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,_T("���ӳɹ�"));				
			}
		}
	}
}



void CHighPrecisionDlg::OnBnClickedButtonTestinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestInfoInputDlg obj_TestInfoInput;
	if(IDOK==obj_TestInfoInput.DoModal())
	{
		//����ͼ�ռ���Ϊ�Զ�
		if(g_TestInfo_L.TestInfoYES_NO)//������Ϣ�ɹ�
		{
			pAxisLeft1->SetAutomatic(false); 
			pAxisLeft1->SetMinMax(-35,5);
			pAxisBottom1->SetAutomatic(false); 
			pAxisBottom1->SetMinMax(-30,40);
			pAxisBottom1->SetInverted(FALSE);

			pAxisLeft2->SetAutomatic(false); 
			pAxisLeft2->SetMinMax(-35,5);
			pAxisBottom2->SetAutomatic(false); 
			pAxisBottom2->SetMinMax(-40,30);
			pAxisBottom2->SetInverted(false);

			pAxisLeft3->SetAutomatic(true); 
			pAxisLeft3->SetMinMax(-2,2);
			pAxisBottom3->SetAutomatic(false);
			pAxisBottom3->SetMinMax(-90,20);
			pAxisBottom3->SetInverted(true);

			pAxisLeft4->SetAutomatic(true); 
			pAxisBottom4->SetAutomatic(false); 
			pAxisBottom4->SetMinMax(-90,20);
			pAxisBottom4->SetInverted(false);

			//pAxisBottom4->SetInverted(false);
			allSeriesClear();
			CString strCurDist;
			int iK=(int)g_TestInfo_L.DistanceStart/1000;
			double iD=g_TestInfo_L.DistanceStart-1000*iK;
			strCurDist.Format("%s%d + %0.1f",g_TestInfo_L.Xianbie,iK,iD);
			SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);		
			if(g_TestInfo_L.XM_QianHou==0)//ϳĥǰ
			{
				double X_temp[2]={-10,90};
				double Y_temp[2]={0,0};
				//�������ҹ��׼����
				m_pLineSerie_LB->AddPoints(X_temp,Y_temp,2);
				m_pLineSerie_RB->AddPoints(X_temp,Y_temp,2);

				m_List_FileName.ResetContent();
				CString tepInfo;
				switch(g_TestInfo_L.TrackSel)
				{
				case 0: tepInfo.Format(_T("��׼�ļ�����50kg/m��׼����"));
					m_sLineSerie_LT->AddPoints(pStandardDataX50,pStandardDataY50,StandardPointNum50);			
					m_sLineSerie_RT->AddPoints(pRightStandDataX50,pStandardDataY50,StandardPointNum50);
					break;
				case 1: tepInfo.Format(_T("��׼�ļ�����60kg/m��׼����"));
					m_sLineSerie_LT->AddPoints(pStandardDataX,pStandardDataY,StandardPointNum);			
					m_sLineSerie_RT->AddPoints(pRightStandDataX,pStandardDataY,StandardPointNum);
					break;
				default:tepInfo.Format(_T("�ļ�����ʧ�ܣ�"));
					break;
				}
				//��ʾ��׼��������Ϣ
				m_List_FileName.InsertString(0,tepInfo);
				tepInfo.Format(_T("���β������ͣ�ϳĥǰ���"));
				m_List_FileName.InsertString(1,tepInfo);
				if (Encoder_Distance > 0)
				{
					tepInfo.Format(_T("��/���У�����"));
				}
				else
					tepInfo.Format(_T("��/���У�����"));
				m_List_FileName.InsertString(2, tepInfo);



			}
			if(g_TestInfo_L.XM_QianHou==1)//ϳĥ��
			{
				//���Ͻ���ʾ����Ļ�׼����
				m_List_FileName.ResetContent();
				CString tmpInfo;
				CString tmpStart;
				CString tmpEnd;
				CString tmpDirection;
				CString tmpXianbie;
				CString tmpGuiXing;
				char Flagchar = '\\';
				for(int i=0;i<g_TestInfo_L.XMH_BaseFileNum;i++)
				{
					////�Զ�ʶ��������/////
					//tmpDirection = g_TestInfo_L.Direction;
					if (Encoder_Distance>0)
					{
						tmpDirection = _T("��");
					} 
					else
					{
						tmpDirection = _T("��");
					}
					tmpXianbie = g_TestInfo_L.Xianbie;
					int Pos = g_TestInfo_L.XMH_BaseFile[i].ReverseFind(Flagchar);
					tmpInfo = g_TestInfo_L.XMH_BaseFile[i].Right(strlen(g_TestInfo_L.XMH_BaseFile[i])-Pos-1);
					Pos = tmpInfo.FindOneOf("-");


					if(0==i)
					{
						tmpStart = tmpInfo.Mid(Pos+1,6);//������ʼ��
						int iK=atoi(tmpStart)/1000;
						int iD=atoi(tmpStart)%1000;
						tmpStart.Format("%s%d+%d",tmpXianbie,iK,iD);
					}				
					tmpEnd = tmpInfo.Mid(Pos+8,6);
					int iK=atoi(tmpEnd)/1000;
					int iD=atoi(tmpEnd)%1000;
					tmpEnd.Format("%s%d+%d",tmpXianbie,iK,iD);;
				}
				switch(g_TestInfo_L.TrackSel)
				{
				case 0: tmpGuiXing="50Kg/m";
					break;
				case 1: tmpGuiXing="60Kg/m";
					break;
				default:tmpGuiXing="60Kg/m";
					break;
				}
				tmpInfo.Format("��׼�ļ�����%s-%sMϳĥǰ����",tmpStart,tmpEnd);
				m_List_FileName.InsertString(0,tmpInfo);
				tmpInfo.Format("��/���У� %s��",tmpDirection);
				m_List_FileName.InsertString(1,tmpInfo);
				tmpInfo.Format("��ʼ��̣� %s",tmpStart);
				m_List_FileName.InsertString(2,tmpInfo);
				tmpInfo.Format("��ֹ��̣� %s",tmpEnd);
				m_List_FileName.InsertString(3,tmpInfo);
				tmpInfo.Format("���ͣ� %s",tmpGuiXing);
				m_List_FileName.InsertString(4,tmpInfo);
				tmpInfo.Format(_T("���β������ͣ�ϳĥ����"));
				m_List_FileName.InsertString(5,tmpInfo);
			}
		}
		else
		{
			m_List_FileName.ResetContent();
			allSeriesClear();
		}
	}
}


void CHighPrecisionDlg::OnBnClickedButtonTestflag()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	allSeriesClear();
	//��������з����е���Ϣ
	m_List_ResultInfo.DeleteAllItems();
	m_List_FileName.ResetContent();
	m_MainMenu->EnableMenuItem(ID_Menu_Anaylze,MF_DISABLED|MF_GRAYED);//�ļ�����
	m_MainMenu->EnableMenuItem(ID_Menu_Reprot,MF_DISABLED|MF_GRAYED);//���ɱ���
	m_MainMenu->EnableMenuItem(ID_Menu_InputFile,MF_DISABLED|MF_GRAYED);//�����ļ�
	m_MainMenu->EnableMenuItem(ID_SETREPORTPARAM, MF_DISABLED | MF_GRAYED);//�����ļ�shen

	m_MainMenu->EnableMenuItem(ID_Menu_Link,MF_ENABLED|MF_BYCOMMAND);//�����豸
	m_MainMenu->EnableMenuItem(ID_Menu_TestInfo,MF_ENABLED|MF_BYCOMMAND);//��������Ϣ
	m_MainMenu->EnableMenuItem(ID_Menu_TestStart,MF_ENABLED|MF_BYCOMMAND);//��ʼ���
	m_MainMenu->EnableMenuItem(ID_Menu_TestStop,MF_ENABLED|MF_BYCOMMAND);//ֹͣ���
	m_MainMenu->EnableMenuItem(ID_Menu_MotorStop,MF_ENABLED|MF_BYCOMMAND);//��ͣ���

	GetDlgItem(IDC_BUTTON_TESTFLAG)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_LINK)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_TESTINFO)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_ANALYZEFLAG)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_STOPMOTOR)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_ANALYZE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_INPUTFILE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_REPORT)->EnableWindow(false);
	GetDlgItem(IDC_SPIN1)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC10)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Distance)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Distance2)->EnableWindow(false);

	GetDlgItem(IDC_COMBO_ModelSel)->EnableWindow(FALSE);

	//��������ļ���Ϣ
	g_TestInfo_L.TestInfoYES_NO=false;
	g_TestInfo_R.TestInfoYES_NO=true;
	//����ļ����е���Ϣ
	m_List_FileName.ResetContent();
	SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,_T("��⹦��"));


	//��ȡ60��׼����
	if (StandardPointNum==0)
	{
		CString CstrStandardPath50or60="StandardOutline\\StandardOutline_60track.txt";
		ReadStandardOutline(pStandardDataX,pStandardDataY,pRightStandDataX,StandardPointNum,CstrStandardPath50or60);
		//����ȫ����׼������
		std::ifstream infile;
		std::string curLine;
		bool finishOneOutline = FALSE;

		infile.open(CstrStandardPath50or60);
		int N0 = 0;
		while (!infile.eof())
		{
			std::getline(infile, curLine);
			if (infile.eof())
			{
				break;
			}
			int firstSpaceIndex = curLine.find_first_of(" ");
			xB[N0] = std::atof(curLine.substr(0, firstSpaceIndex).c_str());
			int coordYIndex = curLine.find_first_not_of(" ", firstSpaceIndex);
			yB[N0] = std::atof(curLine.substr(coordYIndex, curLine.length() - coordYIndex).c_str());
			N0++;
		}
		infile.close();
	}
	//��ȡ50��׼����
	if (StandardPointNum50==0)
	{
		CString CstrStandardPath50or60="StandardOutline\\StandardOutline_50track.txt";
		ReadStandardOutline(pStandardDataX50,pStandardDataY50,pRightStandDataX50,StandardPointNum50,CstrStandardPath50or60);
		
	}
	m_startAndEndVec.clear();
	m_Combo_TotalDistance.ResetContent();
	m_Combo_ModelSel.ResetContent();
}


void CHighPrecisionDlg::OnBnClickedButtonAnalyzeflag()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	allSeriesClear();
	//�˵���ť
	m_MainMenu->GetSubMenu(0)->EnableMenuItem(ID_Menu_Link,MF_BYPOSITION | MF_ENABLED);
	m_MainMenu->EnableMenuItem(ID_Menu_Link,MF_DISABLED|MF_GRAYED);//�����豸���
	m_MainMenu->EnableMenuItem(ID_Menu_TestInfo,MF_DISABLED|MF_GRAYED);//��������Ϣ
	m_MainMenu->EnableMenuItem(ID_Menu_TestStart,MF_DISABLED|MF_GRAYED);//��ʼ���
	m_MainMenu->EnableMenuItem(ID_Menu_TestStop,MF_DISABLED|MF_GRAYED);//ֹͣ���
	m_MainMenu->EnableMenuItem(ID_Menu_MotorStop,MF_DISABLED|MF_GRAYED);//��ͣ���

	m_MainMenu->EnableMenuItem(ID_Menu_Anaylze,MF_ENABLED|MF_BYCOMMAND);//�ļ�����
	m_MainMenu->EnableMenuItem(ID_Menu_Reprot,MF_ENABLED|MF_BYCOMMAND);//���ɱ���
	m_MainMenu->EnableMenuItem(ID_Menu_InputFile,MF_ENABLED|MF_BYCOMMAND);//�����ļ�
	m_MainMenu->EnableMenuItem(ID_SETREPORTPARAM, MF_ENABLED | MF_BYCOMMAND);//�����ļ�shen
	//��ť����
	GetDlgItem(IDC_BUTTON_ANALYZEFLAG)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_LINK)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_TESTINFO)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_STOPMOTOR)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_TESTFLAG)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_ANALYZE)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_INPUTFILE)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_REPORT)->EnableWindow(true);
	GetDlgItem(IDC_SPIN1)->EnableWindow(true);
	GetDlgItem(IDC_STATIC10)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Distance)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Distance2)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_ModelSel)->EnableWindow(TRUE);
	SetDlgItemText(IDC_DISTANCE_CNT,_T("K0+0.0"));
	//����ļ����е���Ϣ
	m_List_FileName.ResetContent();
	//

	SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,_T("��������"));
	m_havePressAnalyse=FALSE;
	//��ȡ60��׼����
	if (StandardPointNum==0)
	{
		CString CstrStandardPath50or60="StandardOutline\\StandardOutline_60track.txt";
		ReadStandardOutline(pStandardDataX,pStandardDataY,pRightStandDataX,StandardPointNum,CstrStandardPath50or60);
		
	}
	//��ȡ50��׼����
	if (StandardPointNum50==0)
	{
		CString CstrStandardPath50or60="StandardOutline\\StandardOutline_50track.txt";
		ReadStandardOutline(pStandardDataX50,pStandardDataY50,pRightStandDataX50,StandardPointNum50,CstrStandardPath50or60);
		
	}
	//�����ͷ
	do 
	{
		BOOL bbbb= m_List_ResultInfo.DeleteColumn(1);
	} while (m_List_ResultInfo.DeleteColumn(1));
}

void CHighPrecisionDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	bFlagStartThread=false;
	int IsDisConnect=ZLDS200DisConnectAll();
	/*if (g_bFlagMotor_L)
	{
		m_MachineCtrl_L.SetSpeed(m_Mscomm_L,1500);
		m_MachineCtrl_L.MotorMove(-MotorMoveLmt,bFlagPOrder_L,m_Mscomm_L);
		
	}
	if (g_bFlagMotor_R)
	{
		m_MachineCtrl_R.SetSpeed(m_Mscomm_R,1500);		
		m_MachineCtrl_R.MotorMove(-MotorMoveLmt,bFlagPOrder_R,m_Mscomm_R);

	}
	if (g_bFlagMotor_L||g_bFlagMotor_R)
	{
		Sleep(2000);
	}	
	if (g_bFlagMotor_L)
	{
		m_MachineCtrl_L.DisConnectMotor(m_Mscomm_L,bFlagPOrder_L,false);
		g_bFlagMotor_L=false;
	}
	if (g_bFlagMotor_R)
	{
		m_MachineCtrl_R.DisConnectMotor(m_Mscomm_R,bFlagPOrder_R,false);
		g_bFlagMotor_R=false;
	}*/

	if (!bEndSaveFlag_R||!bEndSaveFlag_L)
	{
		//�洢δ�����ǿ���޷��ر�
		MessageBox(_T("ϳĥ���ݴ洢δ��ɣ�"),_T("�ر�ʧ�ܣ�"),MB_ICONERROR|MB_OKCANCEL);
		return;
	}
	CDialogEx::OnClose();

}

void CHighPrecisionDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED )  
	{  
		ReSize();  
	} 
}

void CHighPrecisionDlg::ReSize(void)
{
	float fsp[2];  
	CPoint Newp,Newtl,Newbr; //��ȡ���ڶԻ���Ĵ�С  
	CRect recta;   
	GetClientRect(&recta); //ȡ�ͻ�����С  
	Newp.x=recta.right-recta.left;
	Newp.y=recta.bottom-recta.top;
	fsp[0]=(float)Newp.x/Old.x;
	fsp[1]=(float)Newp.y/Old.y;  
	CRect Rect;  
	int woc;  
	CPoint OldTLPoint,TLPoint; //���Ͻ�  
	CPoint OldBRPoint,BRPoint; //���½�  
	HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //�г����пؼ�    
	while(hwndChild)      
	{      
		woc=::GetDlgCtrlID(hwndChild);//ȡ��ID  
		switch (woc)
		{
		case IDC_COMBO_ModelSel:
		case IDC_COMBO_TotalDistance:
		case IDC_STATIC_TotalDistance:
		//case IDC_STATIC14:
			GetDlgItem(woc)->GetWindowRect(Rect);    
			ScreenToClient(Rect);    
			OldTLPoint = Rect.TopLeft();  
			TLPoint.x = long(OldTLPoint.x*fsp[0]);  
			TLPoint.y = long(OldTLPoint.y*fsp[1]);  
			OldBRPoint = Rect.BottomRight();  
			BRPoint.x = long(OldBRPoint.x *fsp[0]);  
			//BRPoint.y = long(OldBRPoint.y *fsp[1]); //�߶Ȳ��ɶ��Ŀؼ�����:combBox),��Ҫ�ı��ֵ.
			Rect.SetRect(TLPoint,BRPoint); 
			GetDlgItem(woc)->MoveWindow(Rect,TRUE);
			break;
		default:
			GetDlgItem(woc)->GetWindowRect(Rect);    
			ScreenToClient(Rect);    
			OldTLPoint = Rect.TopLeft();  
			TLPoint.x = long(OldTLPoint.x*fsp[0]);  
			TLPoint.y = long(OldTLPoint.y*fsp[1]);  
			OldBRPoint = Rect.BottomRight();  
			BRPoint.x = long(OldBRPoint.x *fsp[0]);  
			BRPoint.y = long(OldBRPoint.y *fsp[1]); //�߶Ȳ��ɶ��Ŀؼ�����:combBox),��Ҫ�ı��ֵ.
			Rect.SetRect(TLPoint,BRPoint); 
			GetDlgItem(woc)->MoveWindow(Rect,TRUE);
			break;

		}

		hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);    

	}  

	Old=Newp;
}


void CHighPrecisionDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	//SetDlgItemText(IDC_DISTANCE_LINE,g_TestInfo_L.Xianbie);
	
	//��ʼ���ǰ�������Ƿ�ϳĥǰ�������Ҳ���ʾ���С�
	CStdioFile SpeedInfo;
	CString strLinetemp;
	strpath=_T("D:\\config");
	if (!PathIsDirectory(strpath))
	{
		CreateDirectory(strpath, 0);
	}
	bool openflag=SpeedInfo.Open(_T("D:\\config\\MotorSpeed.txt"),CFile::modeRead);
	if (openflag)
	{
		SpeedInfo.SeekToBegin();
		SpeedInfo.ReadString(strLinetemp);
		char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
				
		if(str != NULL)
		{
			char *TopData1 = str;
			g_MotorSpeed_Qian=atof(TopData1);
		}
		SpeedInfo.ReadString(strLinetemp);
		str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
		
		if(str != NULL)
		{
			char *TopData1 = str;
			g_MotorSpeed_Hou=atof(TopData1);
		}
		SpeedInfo.Close();
	}
	else
	{
		CString strspeed;
		CFile SpeedInfo;	
		CString filename(_T("D:\\config\\MotorSpeed.txt"));//�ļ�����·��	
		bool openflag=SpeedInfo.Open(filename,CFile::modeCreate|CFile::modeReadWrite);
		g_MotorSpeed_Qian = 800;
		g_MotorSpeed_Hou =400;
		if (openflag)
		{
			strspeed.Format(_T("%.2f\r\n"),g_MotorSpeed_Qian);
			SpeedInfo.Write(strspeed,strlen(strspeed));
			strspeed.Format(_T("%.2f\r\n"),g_MotorSpeed_Hou);
			SpeedInfo.Write(strspeed,strlen(strspeed));
			SpeedInfo.Close();
		}
		
	}


	if((!bFlagStartThread)&&(!bStartStFlag))
	{
		
		m_List_ResultInfo.DeleteAllItems();
		int nStNumNode;
		switch(g_TestInfo_L.TrackSel)
		{
		case 0://50��
			{
				nStNumNode=19;
				break;
			}

		case 1://60��
			{
				nStNumNode=23;
				break;
			}
		}
		iDisdanceCount=0;//�ڶ��ο�ʼʱ���¼���
		CString* strListAng=NULL;
		strListAng=new CString[nStNumNode];
		switch(g_TestInfo_L.TrackSel)
		{
		case 0:
			
			for (int i=0;i<Num_Node_50;i++)
			{
				strListAng[i].Format("%2.0f��",Std_Ang_50[i]);
				m_List_ResultInfo.InsertItem(i,strListAng[i]);
			}
			break;
		case 1:
			
			for (int i=0;i<Num_Node;i++)
			{
				strListAng[i].Format("%2.0f��",Std_Ang_60[i]);
				m_List_ResultInfo.InsertItem(i,strListAng[i]);
			}
			break;
		}
		if (strListAng)
		{
			delete[] strListAng;
			strListAng=NULL;
		}
		if (g_TestInfo_L.XM_QianHou==0)//ϳĥǰ
	{
		do 
		{
			BOOL bbbb= m_List_ResultInfo.DeleteColumn(1);
		} while (m_List_ResultInfo.DeleteColumn(1));
		
				
		m_List_ResultInfo.InsertColumn(1,_T("����澫��"),LVCFMT_CENTER,(rect.Width()-28)/2,1);
		m_List_ResultInfo.InsertColumn(2,_T("�Ҷ��澫��"),LVCFMT_CENTER,(rect.Width()-28)/2,2);

	}
		else if (g_TestInfo_L.XM_QianHou==1)//ϳĥ��
		{
		
			do 
			{
				BOOL bbbb= m_List_ResultInfo.DeleteColumn(1);
			} while (m_List_ResultInfo.DeleteColumn(1));
			
			m_List_ResultInfo.InsertColumn(1,_T("��ϳĥ��"),LVCFMT_CENTER,(rect.Width()-28)/4-1,1);
			m_List_ResultInfo.InsertColumn(2,_T("��ϳĥ��"),LVCFMT_CENTER,(rect.Width()-28)/4-1,2);
			m_List_ResultInfo.InsertColumn(3,_T("����澫��"),LVCFMT_CENTER,(rect.Width()-28)/4+2,3);
			m_List_ResultInfo.InsertColumn(4,_T("�Ҷ��澫��"),LVCFMT_CENTER,(rect.Width()-28)/4+2,4);

		}	
		//�����߳�
		if(g_TestInfo_L.TestInfoYES_NO)//��ҵ��Ϣ����ɹ�
		{

			//if(g_bFlagSensorL&&g_bFlagSensorR&&g_bFlagMotor_L&&g_bFlagMotor_R)//����������
			if(g_bFlagSensorL/*&&g_bFlagSensorR*/)
			{
			
				CFont* f;
				f=new CFont;
				f->CreateFont(11,0,0,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,_T("����"));
				bFlagQiangzhiStart =true;//�����߳̿�����
				bFlagStartThread = true;
				SetDlgItemText(IDC_BUTTON_START,_T("ֹͣ"));
				//��ʼ�󣬿�ѡ����
				GetDlgItem(IDC_RADIO_BACK)->EnableWindow(true);

				btn10.SetAlign(CButtonST::ST_ALIGN_VERT);
				btn10.DrawTransparent(TRUE);
				btn10.SetIcon(IDI_ICON9);
				GetDlgItem(IDC_BUTTON_START)->SetFont(f);
				allButtonDisable();
				//�����߳�
				m_2DThreadParam_L.hWnd = m_hWnd;//�����ڵľ�����뵽�ṹ���У������е���Ϣ���ص����ڴ���
				pGetDataThread_L=AfxBeginThread(ThreadGetDataLeft,&m_2DThreadParam_L);//�������ɼ��߳�
				pDealThread_L=AfxBeginThread(ThreadDealLeft, &m_2DThreadParam_L);     //�������2D�����߳�
				pStDataThread_L=AfxBeginThread(ThreadStData_L,&m_2DThreadParam_L);


				m_2DThreadParam_R.hWnd = m_hWnd;
				//pGetDataThread_R=AfxBeginThread(ThreadGetDataRight,&m_2DThreadParam_R);//�����Ҳ�ɼ��߳�
				pDealThread_R=AfxBeginThread(ThreadDealRight, &m_2DThreadParam_R);     //�����Ҳ�2D�����߳�
				pStDataThread_R=AfxBeginThread(ThreadStData_R,&m_2DThreadParam_R);

				bStartStFlag=true;
				//
			
				//�����ļ��д洢����
				//�ȸ�csPath��ֵ
				csPath=_T("D:\\Result");
				if (!PathIsDirectory(csPath))
				{
					CreateDirectory(csPath, 0);
				}
				CTime CurTime;
				CString strTime;
				CurTime=CurTime.GetTickCount();
				strTime.Format("%d%02d%02d",CurTime.GetYear(),CurTime.GetMonth(),CurTime.GetDay());
				switch(g_TestInfo_L.XM_QianHou)
				{
				case 0:
					csPath=csPath+_T("\\")+strTime+_T("ϳĥǰ");
					SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,_T("��ɫΪ��׼��������ɫΪʵ������"));
					//m_MachineCtrl_L.SetSpeed(m_Mscomm_L,g_MotorSpeed_Qian);//���õ���ٶ�Ϊϳĥǰ�ٶ�
					//m_MachineCtrl_R.SetSpeed(m_Mscomm_R,g_MotorSpeed_Qian);
					break;
				case 1:
					csPath=csPath+_T("\\")+strTime+_T("ϳĥ��");
					SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,_T("��ɫΪϳĥǰ��������ɫΪʵ������"));
					//m_MachineCtrl_L.SetSpeed(m_Mscomm_L,g_MotorSpeed_Hou);//���õ���ٶ�Ϊϳĥ���ٶ�
					//m_MachineCtrl_R.SetSpeed(m_Mscomm_R,g_MotorSpeed_Hou);
					break;
				}
				if (!PathIsDirectory(csPath))
				{
					CreateDirectory(csPath, 0);//������D:\\20161020ǰ �򴴽�
				}	
				strTime.Format("%02d-%02d-%02d",CurTime.GetHour(),CurTime.GetMinute(),CurTime.GetSecond());
				csPath=csPath+_T("\\")+strTime;
				if (!PathIsDirectory(csPath))
				{
					CreateDirectory(csPath, 0);//������D:\Result\20160101�򴴽�
				}	
				//ϳĥ��Ҫ�洢ϳĥǰ�Ļ�׼����
				char Flagchar = '\\';
				CString FileName1;
				CString FileName2;
				CString NewPath;
				if(1==g_TestInfo_L.XM_QianHou)//ϳĥ��
				{
				
					int  cPos = g_TestInfo_L.XMH_BaseFile[0].ReverseFind(Flagchar);		
					FileName1=g_TestInfo_L.XMH_BaseFile[0].Right(strlen(g_TestInfo_L.XMH_BaseFile[0])-cPos-1);
					NewPath = csPath+"\\"+FileName1;
					CopyFile((LPCSTR)g_TestInfo_L.XMH_BaseFile[0],(LPCSTR)NewPath,false);
					cPos = g_TestInfo_R.XMH_BaseFile[0].ReverseFind(Flagchar);
					FileName2 = g_TestInfo_R.XMH_BaseFile[0].Right(strlen(g_TestInfo_R.XMH_BaseFile[0])-cPos-1);
					NewPath = csPath+"\\"+FileName2;
					CopyFile((LPCSTR)g_TestInfo_R.XMH_BaseFile[0],(LPCSTR)NewPath,false);

				}


				HnuFilePath=csPath+_T("\\")+_T("�����ļ�.Hnu");
				fpHNUFile.Open(HnuFilePath,CFile::modeCreate|CFile::modeWrite);
				if(1==g_TestInfo_L.XM_QianHou)//ϳĥ��
				{
				fpHNUFile.SeekToEnd();
				int iReplace = FileName1.Replace(_T(".txt"),_T("\r\n"));
				iReplace = FileName2.Replace(_T(".txt"),_T("\r\n"));
				fpHNUFile.Write(FileName1,strlen(FileName1));
				fpHNUFile.Write(FileName2,strlen(FileName2));
				}
				fpHNUFile.Close();
							
			}
			else
				MessageBox(_T("�豸�쳣"),_T("�ֹ�����������"));
				
			
		}		
		else
		{
			MessageBox(_T("��������ҵ��Ϣ��"),_T("�ֹ�����������"));
			
		}

	}
	else
	{
		bFlagStartThread = false;
		g_StopDrawFlag_L =true;
		g_StopDrawFlag_R =true;
		g_TestInfo_L.TestInfoYES_NO=false;//ֹ֮ͣ��Ҫ����������ҵ��Ϣ
		g_TestInfo_R.TestInfoYES_NO=false;
		
		//SetDlgItemText(IDC_BUTTON_START,_T("��ʼ"));//7.17�Լ���
	}
	
}

//���ɼ��߳�
UINT ThreadGetDataLeft(LPVOID pParam)
{	
	//thisָ��
	//CHighPrecisionDlg *thisDlg; //��void����ǿ��ת����dlg����
	//thisDlg = (CMainTestDlg *)pdlg;

	int GetDataPointnum;
	int GetDataOutLineNum[1]={0};//��¼ÿ���������ɵĵ���
	int nGetDataOutlineNo=0;//��¼�������
	int GetDataOutLineNumSt[1]={0};
	double x_GetData_results_L[SensorMaxPoint]={0},z_GetData_results_L[SensorMaxPoint]={0};
	int measureNum=0;
	int packetNum=0;
	int ZeroGetPoint=0;//��¼�ɼ�����������
	float x_results[SensorMaxPoint]={0}, z_results[SensorMaxPoint]={0};				//ÿ������������
	int nRtrValueGetPoint=0;

	THREAD_PARAM2D* pThreadParam = (THREAD_PARAM2D*)pParam;
	
	int flagconnect = 1;

	while(bFlagStartThread)
	{
		//Sleep(100);
		
		nRtrValueGetPoint =ZLDS200GetPoint(x_results , z_results , &measureNum, &packetNum, &GetDataPointnum, TRUE,g_InitiChooseL); //��ȡ����
		//�������
		if (nRtrValueGetPoint>0&&nRtrValueGetPoint<SensorMaxPoint)
		{
			ZeroGetPoint=0;
			if(bFlagStartThread)
			g_StopDrawFlag_L=false;
			
			if (!g_bFLagIsRunBack)
			{
				for (unsigned int iTransfer = 0; iTransfer < nRtrValueGetPoint; ++iTransfer)
				{
					//x_GetData_results[nRtrValueGetPoint-iTransfer-1]=-x_results[iTransfer];
					//z_GetData_results[nRtrValueGetPoint-iTransfer-1]=z_results[iTransfer];
					//assert(iTransfer <= 640 && iTransfer >= 0);
					//x_GetData_results_L[iTransfer] = x_results[nRtrValueGetPoint - iTransfer - 1];
					//z_GetData_results_L[iTransfer] = z_results[nRtrValueGetPoint - iTransfer - 1];

					x_GetData_results_L[iTransfer] = x_results[iTransfer];
					z_GetData_results_L[iTransfer] = z_results[iTransfer];
				}


				GetDataSection_L.Lock();

				GetDataOutLineNum[0] = nRtrValueGetPoint;
				GetDataOutLineNumSt[0] = nRtrValueGetPoint;

				////���ڴ����߳�
				LoopBuff.LoopBuffWrite(&xGetData_LoopBuff_L, x_GetData_results_L, nRtrValueGetPoint);
				LoopBuff.LoopBuffWrite(&zGetData_LoopBuff_L, z_GetData_results_L, nRtrValueGetPoint);
				LoopBuff.LoopBuffWrite(&GetDataNum_LoopBuff_L, GetDataOutLineNum, 1);///�洢��������
				////����txt�ļ��洢�Ļ�����
				LoopBuff.LoopBuffWrite(&xSave_LoopBuff_L, x_GetData_results_L, nRtrValueGetPoint);
				LoopBuff.LoopBuffWrite(&zSave_LoopBuff_L, z_GetData_results_L, nRtrValueGetPoint);
				LoopBuff.LoopBuffWrite(&GetDataNumSt_LoopBuff_L, GetDataOutLineNumSt, 1);
				GetDataSection_L.Unlock();
				if (1)//CurDist > 0)
				{
					//iDisdanceCount++;
					if (Encoder_Distance > 0)
					{
						iDisdanceCount++;
					}
					else
						iDisdanceCount--;
				}
			}
			else
			{
				if (1)//CurDist > 0)
					//iDisdanceCount--;
				{
					if (Encoder_Distance > 0)
					{
						iDisdanceCount--;
					}
					else
						iDisdanceCount++;
				}
				//iDisdanceCount++;

			}
			//��̼���
			//iDisdanceCount++;
			//CurDist = g_TestInfo_L.DistanceStart + iDisdanceCount*abs(Encoder_Distance);

			::SendMessage(pThreadParam->hWnd,WM_DISPLAYCTRL,0,0);//��¼���
			//WM_DISPLAYCTRL

		}

		//if ((nRtrValueGetPoint < 0) && (flagconnect == 0))
		//{
		//		AfxMessageBox(_T("�����������쳣")); 
		//		flagconnect = 1;
		//}
				
		else
		{
				ZeroGetPoint++;

				if (ZeroGetPoint > 40)
					g_StopDrawFlag_L = true;
		}
			
		
	}
	//int i;
	//do
	//{
	//	i=ZLDS200GetPoint(x_results , z_results , &measureNum, &packetNum, &GetDataPointnum, TRUE,g_InitiChooseL); //��ȡ����
	//}while(i>0);

	return 0;
}
//�Ҳ�ɼ��߳�
UINT ThreadGetDataRight(LPVOID pParam)
{	

	//CMainTestDlg *thisDlg; //��void����ǿ��ת����dlg����
	//thisDlg = (CMainTestDlg *)pdlg;

	int GetDataOutLineNum[1]={0};//��¼ÿ���������ɵĵ���
	int nGetDataOutlineNo=0;//��¼�������
	int GetDataOutLineNumSt[1]={0};
	double x_GetData_results[SensorMaxPoint]={0},z_GetData_results[SensorMaxPoint]={0};
	int	GetDataPointnum;//�ɼ��߳��ﴫ�������βɼ��������ݵ���
	int measureNumRight=0;
	int packetNumRight=0;
	int ZeroGetPoint=0;//��¼�ɼ�����������
	float x_resultsRight[SensorMaxPoint]={0},z_resultsRight[SensorMaxPoint]={0};

	while(bFlagStartThread)
	{
		int nRtrValueGetPoint;
		nRtrValueGetPoint =ZLDS200GetPoint(x_resultsRight , z_resultsRight , &measureNumRight, 
			&packetNumRight, &GetDataPointnum, TRUE,g_InitiChooseR); //��ȡ����
		//�������
		if (nRtrValueGetPoint>0&&nRtrValueGetPoint<SensorMaxPoint)
		{
			//iDisdanceCountRight++;
			//thisDlg->SendMessage(WM_DISPLAYCTRL,1,0);
			ZeroGetPoint=0;
			if(bFlagStartThread)
			g_StopDrawFlag_R=false;

			if (!g_bFLagIsRunBack)
			{
				for (unsigned int iTransfer = 0; iTransfer < nRtrValueGetPoint; iTransfer++)
				{
					x_GetData_results[iTransfer] = x_resultsRight[iTransfer];
					z_GetData_results[iTransfer] = z_resultsRight[iTransfer];
				}

				GetDataOutLineNum[0] = nRtrValueGetPoint;
				GetDataOutLineNumSt[0] = nRtrValueGetPoint;
				GetDataSection_R.Lock();
				////���ڴ����߳�
				LoopBuff.LoopBuffWrite(&xGetData_LoopBuff_R, x_GetData_results, nRtrValueGetPoint);
				LoopBuff.LoopBuffWrite(&zGetData_LoopBuff_R, z_GetData_results, nRtrValueGetPoint);
				LoopBuff.LoopBuffWrite(&GetDataNum_LoopBuff_R, GetDataOutLineNum, 1);

				////����txt�ļ��洢�Ļ�����
				LoopBuff.LoopBuffWrite(&xSave_LoopBuff_R, x_GetData_results, nRtrValueGetPoint);
				LoopBuff.LoopBuffWrite(&zSave_LoopBuff_R, z_GetData_results, nRtrValueGetPoint);
				LoopBuff.LoopBuffWrite(&GetDataNumSt_LoopBuff_R, GetDataOutLineNumSt, 1);

				GetDataSection_R.Unlock();
			}
		}
		else
		{
			ZeroGetPoint++;
			if(ZeroGetPoint>40)
				g_StopDrawFlag_R=true;
		}
	}
	//int i;
	//do
	//{
	//	i=ZLDS200GetPoint(x_resultsRight , z_resultsRight , &measureNumRight, 
	//		&packetNumRight, &GetDataPointnum, TRUE,g_InitiChooseR); //��������������ݲ���
	//}while(i>0);
	return 0;
}
//��ദ���߳�
UINT ThreadDealLeft(LPVOID pParam)
{
	OutLineArithmetic CalculateOutline;
	double youyi_L;
    moveBefore_L=TRUE; //�ж��Ƿ���һ��ָ��ʹ�������
	continueErrorCnt_L=0;  //�������쳣�������м���
	int nMtStopDist=0;
	switch(g_TestInfo_R.TrackSel)
	{
	case 0:
		nMtStopDist=55;
		break;
	case 1:
		nMtStopDist=55;
		break;
	}
	
	int iGetDataOutLineCnt=0;//�ɼ����ݻ�����ȡ���ݼ�����
	double Pos_Init_X_L[SensorMaxPoint]={0},Pos_Init_Y_L[SensorMaxPoint]={0};//��������������ʱ�������
	double Pos_Rec_X_L[SensorMaxPoint]={0},Pos_Rec_Y_L[SensorMaxPoint]={0};//��Ŵ��������
	int nStNumNode;
	switch(g_TestInfo_L.TrackSel)
	{
	case 0://50��
		{
			nStNumNode=19;
			break;
		}

	case 1://60��
		{
			nStNumNode=23;
			break;
		}
	}
	int iGetDataTempArray[1]={0};//��Ŷ��������ĵ���
//	int HdmORXmlDataNum[1];//���ϳĥ�����߾���ֵ�ĵ���
	int Readpointnum=0;///��¼�ӻ���������������������
	int isInvalidOutline=1;//��־�����Ƿ���Ч
	int Pointnum_L=0;//Ԥ����֮�����������
	int Num_R400_Start=0; //����R400�����
	//�洢ϳĥ��ʵ���׼���ļ�
	double* pScbzPtr_X=NULL;
	pScbzPtr_X=new double[nStNumNode];
	double* pScbzPtr_Y=NULL;
	pScbzPtr_Y=new double[nStNumNode];
	
	int XmlPointNum=0;
	int iNeedCount=0;
	int ErrorSCBZD=0;
	int DrawNum=3;
	double Mileage=0;
	double MileageTop =0;
	int ScbzdFileNum=0;//�����Զ�����һ��ʵ���׼���ļ�
	bool IsReadStop=true;
	BOOL IsInvalidBZPoint=TRUE;
	

	CHighPrecisionDlg *dlg;
	dlg = (CHighPrecisionDlg *)pdlg;
	CStdioFile XML_SCBZDfile;
	CString    strLinetemp;
	double     XML_SCBZDbegin=0;
	double     XML_SCBZDend  =0;
	THREAD_PARAM2D* pThreadParam = (THREAD_PARAM2D*)pParam;


	double Motor_MovingDist=0;	//������о���
	double Motor_MovingRound=0; //���ת��Ȧ��


	GetDataSection_L.Lock();
	iGetDataOutLineCnt=LoopBuff.LoopBuffDataLength(&GetDataNum_LoopBuff_L);//iGetDataOutLineCnt�������ʾ�ɼ��߳��������ݿ��Կ�ʼ����
	GetDataSection_L.Unlock();
	/*WaitForSingleObject();
	ReleaseSemaphore();*/

	/*�Ķ�*/
	OutlineFileHelper fileHelper("����������L.txt");
	int randNum = 1;


	while((iGetDataOutLineCnt||bFlagStartThread)&&bFlagQiangzhiStart)//�߳�ѭ��
	{
		iNeedCount=0;//��ʼ��
		ErrorSCBZD=0;
		if (iGetDataOutLineCnt>0)
		{
			ZeroMemory(Pos_Init_X_L,sizeof(Pos_Init_X_L));
			ZeroMemory(Pos_Init_Y_L,sizeof(Pos_Init_Y_L));
			GetDataSection_L.Lock();
			LoopBuff.LoopBuffRead(&GetDataNum_LoopBuff_L,iGetDataTempArray,1);
			LoopBuff.LoopBuffRead(&xGetData_LoopBuff_L,Pos_Init_X_L,iGetDataTempArray[0]);
			LoopBuff.LoopBuffRead(&zGetData_LoopBuff_L,Pos_Init_Y_L,iGetDataTempArray[0]);
			GetDataSection_L.Unlock();
			XmlPointNum++;//����ϳĥ�����̼���
			Readpointnum=iGetDataTempArray[0];

			//switch()//�ж�ѡ�����50�컹��60��
			switch(g_TestInfo_L.TrackSel)
			{
			case 0:
				Point_50INFO_L.pInDataX           =Pos_Init_X_L;
				Point_50INFO_L.pInDataY           =Pos_Init_Y_L;
				Point_50INFO_L.In_Num             =Readpointnum;
				Point_50INFO_L.FittingRadius_R20  =20;
				Point_50INFO_L.FittingRadius_R400 =400;

				isInvalidOutline=Preproccess(Point_50INFO_L,Track_60);

				if(isInvalidOutline==1)
				{
					for(int i=0;i<Point_50INFO_L.Out_Num;i++)
					{
						Pos_Rec_X_L[i]=Point_50INFO_L.pOutDataX[i];
						Pos_Rec_Y_L[i]=Point_50INFO_L.pOutDataY[i];
					}
					Pointnum_L = Point_50INFO_L.Out_Num;///���洦����ɵ������ĵ�����pointnum
					Num_R400_Start  = Point_50INFO_L.Num_R400Start;
				}
				break;
			case 1:
				Point_60INFO_L.pInDataX           =Pos_Init_X_L;
				Point_60INFO_L.pInDataY           =Pos_Init_Y_L;
				Point_60INFO_L.In_Num             =Readpointnum;
				Point_60INFO_L.FittingRadius_R20  =20;
				Point_60INFO_L.FittingRadius_R400 =400;

				isInvalidOutline=Preproccess(Point_60INFO_L,Track_60);
				if(isInvalidOutline==1)
				{
					for(int i=0;i<Point_60INFO_L.Out_Num;i++)
					{
						Pos_Rec_X_L[i]=Point_60INFO_L.pOutDataX[i];
						Pos_Rec_Y_L[i]=Point_60INFO_L.pOutDataY[i];
					}
					Pointnum_L = Point_60INFO_L.Out_Num;///���洦����ɵ������ĵ�����pointnum
					Num_R400_Start  = Point_60INFO_L.Num_R400Start;
				}
				//else
				//{
				//	//AfxMessageBox(_T("�쳣"));
				//	/*isInvalidOutline = 1;*/
				//	/*int randNum =5;*/
				//	double targetMeter = 0.1 * (double)randNum;
				//	randNum++;
				//	if (randNum > 45)
				//		randNum = 1;

				//	Outline outline = fileHelper.getOutlineByMileage(targetMeter);
				//	for (int i = 0; i < outline.m_pointNum; i++)
				//	{
				//		Pos_Rec_X_L[i] = outline.m_coordinateX[i];
				//		Pos_Rec_Y_L[i] = outline.m_coordinateY[i];
				//	}
				//	Pointnum_L = outline.m_pointNum;
				//	for (int i = 0; i < outline.m_pointNum - 1; ++i)
				//	{
				//		double xDis = outline.m_coordinateX[i + 1] - outline.m_coordinateX[i];
				//		double yDis = outline.m_coordinateY[i + 1] - outline.m_coordinateY[i];
				//		if (sqrt(xDis * xDis + yDis * yDis) >= 5)
				//		{
				//			
				//			Num_R400_Start = i + 1;
				//			break;
				//		}
				//	}

				//}
				break;
				
			}
			
        //if(isInvalidOutline==1)//������Ч
		  //{
			  //ϳĥǰ
			  //continueErrorCnt_L=0;
			  double shangyi = 0;
			  if(g_TestInfo_L.XM_QianHou==0&&isInvalidOutline==1)
			  {
				  continueErrorCnt_L=0;//				  
				  switch(g_TestInfo_L.TrackSel)
				  {
				  case 0:
					  //FuncCalculatingHdm(Hdm_50,bFlagWeiDuiQi,bFlagTrack_L,Pointnum_L,Pos_Rec_X_L,Pos_Rec_Y_L,Num_R400_Start);
					  //HdmScbz_XL_50[Num_Node_50]=Pos_Rec_X_L[Num_R400_Start-5];
					  //HdmScbz_YL_50[Num_Node_50]=Pos_Rec_Y_L[Num_R400_Start-5];//����δ����Ĺ����
					 // HdmScbz_XL_50[Num_Node_50]=36.328;
					 // HdmScbz_YL_50[Num_Node_50]=32.753;
					  shangyi = FuncCalculatingHdm(Hdm_50,bFlagDuiQi,bFlagTrack_L,Pointnum_L,Pos_Rec_X_L,Pos_Rec_Y_L,Num_R400_Start);
					  //HdmNode_XL_50[Num_Node_50]=Pos_Rec_X_L[Num_R400_Start-5];
					  //HdmNode_YL_50[Num_Node_50]=Pos_Rec_Y_L[Num_R400_Start-5];//�������Ĺ����
					  HdmNode_XL_50[Num_Node_50] = 36.328;
					  HdmNode_YL_50[Num_Node_50] = 32.753;
					  for (int i=0;i<Num_Node_50;i++)
					  {
						  HdmScbz_XL_50[i]=HdmNode_XL_50[i];
						  HdmScbz_YL_50[i]=HdmNode_YL_50[i];
						  pThreadParam->DistHdm_50[i] = Dist_Hdmjd_L_50[i];
					  }
					  HdmScbz_XL_50[Num_Node_50]=36.328 + shangyi;
					  HdmScbz_YL_50[Num_Node_50]=32.753;
					  
					  //����״̬�õ��ֹͣ
					  //if (!moveBefore_L)/******7.17��ע��*******/
					  //{
						 // if (1)//Pos_Rec_X_L[Pointnum_L-1]>=30  && Pos_Rec_X_L[Pointnum_L-1]<=60)
						 // {
							//  continueErrorCnt_L=0;
							//  moveBefore_L=TRUE;
							//  m_MachineCtrl_L.MotorStop(m_Mscomm_L);
							//  //bFlagPOrder_L=m_MachineCtrl_L.MotorMove(0,bFlagPOrder_L,m_Mscomm_L);
							//  //bFlagPOrder_L=m_MachineCtrl_L.MotorMove(0,bFlagPOrder_L,m_Mscomm_L);
						 // }
					  //}/******7.17��ע��*******/
					  break;
				  case 1:
					  //FuncCalculatingHdm(Hdm_60,bFlagWeiDuiQi,bFlagTrack_L,Pointnum_L,Pos_Rec_X_L,Pos_Rec_Y_L,Num_R400_Start);
					 // HdmScbz_XL[Num_Node]=Pos_Rec_X_L[Num_R400_Start-5];
					 // HdmScbz_YL[Num_Node]=Pos_Rec_Y_L[Num_R400_Start-5];//����δ����Ĺ����
					 // HdmScbz_XL[Num_Node]=36.8;
					  //HdmScbz_YL[Num_Node]=32.753;
					  shangyi = FuncCalculatingHdm(Hdm_60,bFlagDuiQi,bFlagTrack_L,Pointnum_L,Pos_Rec_X_L,Pos_Rec_Y_L,Num_R400_Start);
					  //HdmNode_XL[Num_Node]=Pos_Rec_X_L[Num_R400_Start-5];
					 // HdmNode_YL[Num_Node]=Pos_Rec_Y_L[Num_R400_Start-5];//�������Ĺ����
					  HdmNode_XL[Num_Node]=36.8;
					  HdmNode_YL[Num_Node]=32.753;
					  for (int i=0;i<Num_Node;i++)
					  {
						  HdmScbz_XL[i]=HdmNode_XL[i];
						  HdmScbz_YL[i]=HdmNode_YL[i];
						  pThreadParam->DistHdm[i]=Dist_Hdmjd_L[i];
					  }
					  HdmScbz_XL[Num_Node]=36.8+shangyi;
					  HdmScbz_YL[Num_Node]=32.753;

					  //����״̬�õ��ֹͣ
					  //if (!moveBefore_L)/******7.17��ע��*******/
					  //{
						 // if (1)//Pos_Rec_X_L[Pointnum_L-1]>=40  && Pos_Rec_X_L[Pointnum_L-1]<=55)
						 // {
							//  continueErrorCnt_L=0;
							//  moveBefore_L=TRUE;
							//  m_MachineCtrl_L.MotorStop(m_Mscomm_L);
						
							//  //bFlagPOrder_L=m_MachineCtrl_L.MotorMove(0,bFlagPOrder_L,m_Mscomm_L);
							//  //bFlagPOrder_L=m_MachineCtrl_L.MotorMove(0,bFlagPOrder_L,m_Mscomm_L);
						 // }
					  //}/******7.17��ע��*******/
					  break;
				  }

				  //������Ϣ
				 
				  //��ʼ��ͼ
				  //����ֵ
				  //������
				  int m=0;
				  for (int n=0;n<Pointnum_L;n++)
				  {
					  if (Pos_Rec_X_L[n]>-26 && Pos_Rec_X_L[n]<38 && Pos_Rec_Y_L[n]>-5&& Pos_Rec_Y_L[n]<36.3)
					  {
						  pThreadParam->xData[m]=Pos_Rec_X_L[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
						  pThreadParam->zData[m]=Pos_Rec_Y_L[n];					 
						  m++;
					  }

				  }
				  pThreadParam->DataNum=m;
				  CString strtemppp;
				  if (!g_StopDrawFlag_L&&DrawNum/3)
				  {
					  ::SendMessage(pThreadParam->hWnd,WM_2DTHREADMSG_L,0,0);
					  Sleep(5);
					  ::SendMessage(pThreadParam->hWnd,WM_2DDISPLISTCTRL_L,0,0);//wParam==0,����ʾϳĥǰ��Ϣ
					
				  }				  


				  //�����ݴ��뻺����			 
				  iGetDataTempArray[0] =24;
				  //  HdmORXmlDataNum[0]   =23;
				 
				  OutLineSection_L.Lock();
				  //�洢����ϳĥ��ʱ��23��ʵ�⽻��ӹ���㣨���ƺ�
				  LoopBuff.LoopBuffWrite(&xHdmNodeLoopBuff_L,HdmNode_XL,nStNumNode+1);
				  
				  LoopBuff.LoopBuffWrite(&zHdmNodeLoopBuff_L,HdmNode_YL,nStNumNode+1);
				  //�洢����ϳĥ��ʱ��23��ʵ���׼��ӹ���㣨����ǰ��
				  LoopBuff.LoopBuffWrite(&xScbzLoopBuff_L,HdmScbz_XL,nStNumNode+1);
				  LoopBuff.LoopBuffWrite(&zScbzLoopBuff_L,HdmScbz_YL,nStNumNode+1);
				  //�洢23������澫��
				  LoopBuff.LoopBuffWrite(&DistHdmJd_LoofBuff_L,Dist_Hdmjd_L,nStNumNode);
				  //���ʵ�⽻�����Ŀ	
				  // LoopBuff.LoopBuffWrite(&OutLine_LoopBuff_L,iGetDataTempArray,1);
				  //��ž���ֵ����Ŀ
				  //LoopBuff.LoopBuffWrite(&HdmORXmlNum_loopBuff_L,HdmORXmlDataNum,1);
				  OutLineSection_L.Unlock();
			     }
			  if(g_TestInfo_L.XM_QianHou==1)
			  {
				  Mileage=XmlPointNum*Encoder_Distance+g_TestInfo_L.DistanceStart;//�������ǰ���
				  //��ȡϳĥ����׼������
				  //*��ʵ���׼�㸳ֵ��pScbzPtr_X,pScbzPtr_Y*//
				  BOOL IsOpen = XML_SCBZDfile.Open(g_TestInfo_L.XMH_BaseFile[ScbzdFileNum],CFile::modeRead);
				  if(IsOpen)
				  {
					  //������׼�ļ�����ʼ��̺���ֹ���
					  XML_SCBZDfile.SeekToBegin();
					  XML_SCBZDfile.ReadString(strLinetemp);//��ȡ��һ�У����뿪ʼ���
					  char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
					  char *strtemp = NULL;  
					  strtemp = strtok(str, " ");  
					  if(strtemp != NULL)
					  {
						  char *TopData1 = strtemp;
						  XML_SCBZDbegin=atof(TopData1);
					  }
					  XML_SCBZDfile.Seek(-80,CFile::end);//��ȡ�ļ�����ֹ���
					  XML_SCBZDfile.ReadString(strLinetemp);
					  XML_SCBZDfile.ReadString(strLinetemp);
					  char *str1 = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
					  char *strtemp1 = NULL;  
					  strtemp1 = strtok(str1, " ");  
					  if(strtemp1 != NULL)
					  {
						  char *TopData2 = strtemp1;
						  XML_SCBZDend=atof(TopData2);
					  }	
					  //��������У�����ʼ��̴�����ֹ��̣����ж��ǽ���
					  double tmpXML_SCBZDend = XML_SCBZDend;
					  double tmpXML_SCBZDbegin = XML_SCBZDbegin;
					  if (Encoder_Distance < 0)//����
					  {
						  double temp = tmpXML_SCBZDbegin;
						  tmpXML_SCBZDbegin = tmpXML_SCBZDend;
						  tmpXML_SCBZDend = temp;
					  }

					  //��ʼ��ȡ��Ӧ��̵�����
					  //if(!(Mileage>tmpXML_SCBZDend)&&!(Mileage<tmpXML_SCBZDbegin))
					  double eps = 0.001;//С���������洢���
					  if(!(Mileage>(tmpXML_SCBZDend+eps))&&!(Mileage<(tmpXML_SCBZDbegin-eps)))
					  {
						  //for(int i=0;i<int((Mileage-XML_SCBZDbegin)*10*24);i++)//����ǰ�����ɸ�����
						  //{
							 // XML_SCBZDfile.ReadString(strLinetemp);
						  //}
                        XML_SCBZDfile.Seek(int(abs(Mileage-XML_SCBZDbegin)*10*24*31),CFile::begin);//��������������
						while( XML_SCBZDfile.ReadString(strLinetemp))//��ȡʵ���׼��
						{
							char *str2 = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
							char *strtemp2 = NULL;  
							strtemp2 = strtok(str2, " "); 
							char *TopData = strtemp2;
							if(TopData != NULL)
							{		
								MileageTop = atof(TopData);
							}
							if(fabs(MileageTop-Mileage)<1e-8)
							{
								strtemp2 = strtok(NULL, " "); 							 
								char *Xdata = strtemp2; 
								if (Xdata != NULL)  
								{  
									pScbzPtr_X[iNeedCount] =atof(Xdata); 
								}  	
								strtemp2 = strtok(NULL, " ");  						
								char *Ydata = strtemp2;
								if (Ydata != NULL)  
								{  	
									pScbzPtr_Y[iNeedCount]= atof(Ydata);
									if(0==pScbzPtr_Y[iNeedCount])	
									{
										ErrorSCBZD++;
										if(ErrorSCBZD==nStNumNode+1)	
										IsInvalidBZPoint = FALSE;
									}
									else
										IsInvalidBZPoint = TRUE;

								} 
								iNeedCount++;
								IsReadStop = false;
							}
							else
							{
								if(IsReadStop==false)
								{
									IsReadStop=true;
									break;
								}
							}
						}			
						if(fabs(Mileage-XML_SCBZDend)<1e-8)//��������ļ�����ֹ��̣����Զ���ȡ��һ���ļ�
						  {
							  if(g_TestInfo_L.XMH_BaseFileNum-1>ScbzdFileNum)
							  {
								  ScbzdFileNum++;
							  }
						  }
					    XML_SCBZDfile.Close();
				      }
					  else
					  {
						  if(bFlagQiangzhiStart)
						  {
							   bFlagStartThread =false;  //�ɼ��߳�ֹͣ
							   bFlagQiangzhiStart = false;//�߳�ǿ��ֹͣ
							   bEndDealingFlag_L =TRUE;
							   bEndDealingFlag_R =TRUE;
							   AfxMessageBox(_T("������׼�ļ���̷�Χ"));
							  
							   
						  }
						 
						  XML_SCBZDfile.Close();
						  bFlagQiangzhiStart = false;//�߳�ǿ��ֹͣ
						  bFlagStartThread =false;  //�ɼ��߳�ֹͣ
						  //bEndDealingFlag_L =TRUE;
						  return 0;
					  }
				  }
				  else//������ܴ�
				  {
					  if(bFlagQiangzhiStart)
					  {
						  bFlagStartThread =false;  //�ɼ��߳�ֹͣ
						  bFlagQiangzhiStart = false;//�߳�ǿ��ֹͣ
						  bEndDealingFlag_L =TRUE;
						  bEndDealingFlag_R =TRUE;
						 AfxMessageBox(_T("��׼�ļ��쳣�������µ����׼�ļ�"));
						 
						  
					  }		
					  //bEndDealingFlag_L =TRUE;
					  bFlagQiangzhiStart = false;//�߳�ǿ��ֹͣ
					  bFlagStartThread =false;  //�ɼ��߳�ֹͣ
					  
					  return 0;
				  }
				  if(IsInvalidBZPoint)//�������Ļ�׼�����������ģ���������
				  {
					   //������׼������
					  int WdqCount=0;
					  for (int n=0;n<nStNumNode+1;n++)//��������ϳĥ��δ��������һ��24����
					  {		
						 // if(pScbzPtr_X[n]!=0&&pScbzPtr_Y[n]!=0)
						  //{
							  pThreadParam->WdqData_X[WdqCount] =pScbzPtr_X[n];
							  pThreadParam->WdqData_Y[WdqCount] =pScbzPtr_Y[n];
							  
							  if(WdqCount == nStNumNode)
							  {
								  shangyi = pThreadParam->WdqData_X[WdqCount]-36.8;
								  pThreadParam->WdqData_X[WdqCount] -= shangyi;
							  }
							  WdqCount++;
						  //}
						 
					  }
					   pThreadParam->WdqNum = WdqCount;
					  if (!g_StopDrawFlag_L&&DrawNum/3)
					  {
						  ::SendMessage(pThreadParam->hWnd, WM_2DTHREADMSG_XMLscbz_L, 0, 0);
						  Sleep(5);
					  }
					  if (isInvalidOutline==1)
					  {
						  //continueErrorCnt_L=0;//					  
					  //��ת֮�����������ϳĥǰ��������
						  for (int i = 0; i < Pointnum_L; i++)
						  {
							  Pos_Rec_Y_L[i] = Pos_Rec_Y_L[i] - shangyi;
						  }

						  double Pos_Tmp_X_L[700], Pos_Tmp_Y_L[700];//�м����飬���ڼ���ϳĥ��ǰ�Ĺ������ת
						  for (int i=0;i<Pointnum_L;i++)
						  {
							  Pos_Tmp_X_L[i] = Pos_Rec_X_L[i];
							  Pos_Tmp_Y_L[i] = Pos_Rec_Y_L[i];
						  }
						  GuiDiPoRevolve(Pointnum_L, Pos_Tmp_X_L, Pos_Tmp_Y_L, false,Guidipo_L);
					  //////////////////���춥��////////////////////////////////
					  //double Pos_Rec_X_Ltmp[700], Pos_Rec_Y_Ltmp[700];
					  //for (int i=0;i<Pointnum_L;i++)
					  //{
						 // Pos_Rec_X_Ltmp[i] = Pos_Rec_X_L[i];
						 // Pos_Rec_Y_Ltmp[i] = Pos_Rec_Y_L[i];
					  //}

					  //////����б��
					  //double Pos_X_Lxl[300], Pos_Y_Lxl[300];
					  //int n = 0;
					  //for (int i = 0; i < Pointnum_L; i++)
					  //{
						 // if (Pos_Rec_X_Ltmp[i] >= -10 && Pos_Rec_X_Ltmp[i] <= 10&&Pos_Rec_Y_Ltmp[i]<=20)
						 // {
							//  Pos_X_Lxl[n] = Pos_Rec_X_Ltmp[i];
							//  Pos_Y_Lxl[n] = Pos_Rec_Y_Ltmp[i];
							//  n++;
						 // }
					  //}
					  //double xielv = CalculateOutline.LineFitLeastSquares(Pos_X_Lxl, Pos_Y_Lxl, n);
					  //double gd_theta = atan(xielv);
					  //gd_theta = 0.024784;
					 
					  //double y_tmp;//xΪ0��λ�õ�y����
					  //for (int i = 0; i < Pointnum_L; i++)
					  //{
						 // if (Pos_Rec_X_L[i] <= 0 && Pos_Rec_X_L[i + 1] >= 0)
						 // {
							//  y_tmp = (-Pos_Rec_X_L[i+1])* (Pos_Rec_Y_L[i] - Pos_Rec_Y_L[i + 1]) / (Pos_Rec_X_L[i] - Pos_Rec_X_L[i + 1])+ Pos_Rec_Y_L[i+1];
							//  break;
						 // }
					  //}
					  //for (int i = 0; i < Pointnum_L; i++)
					  //{
						 // Pos_Rec_Y_L[i] -= y_tmp;
					  //}


					  //for (int i = 0; i < Pointnum_L; i++)
					  //{
						 // Pos_Rec_X_Ltmp[i] = Pos_Rec_X_L[i] * cos(-gd_theta) - Pos_Rec_Y_L[i] * sin(-gd_theta);
						 // Pos_Rec_Y_Ltmp[i] = Pos_Rec_X_L[i] * sin(-gd_theta) + Pos_Rec_Y_L[i] * cos(-gd_theta);
					  //}
					
					  //for (int i = 0; i < Pointnum_L; i++)
					  //{
						 // Pos_Rec_X_L[i] = Pos_Rec_X_Ltmp[i];
						 // Pos_Rec_Y_L[i] = Pos_Rec_Y_Ltmp[i];
					  //}
					  //for (int i = 0; i < Pointnum_L; i++)
					  //{
						 // if (Pos_Rec_Y_L[i] <= 14.2 && Pos_Rec_X_L[i + 1] >= 14.2)
						 // {
							//  double x_tmp = (14.2 - Pos_Rec_Y_L[i])*(Pos_Rec_X_L[i] - Pos_Rec_X_L[i + 1]) / (Pos_Rec_Y_L[i] - Pos_Rec_X_L[i + 1]) + Pos_Rec_X_L[i];
							//  youyi_L = 35.4 - x_tmp;
							//  break;
						 // }
					  //}
					  //for (int i = 0; i < Pointnum_L; i++)
					  //{
						 // Pos_Rec_X_L[i] += youyi_L;
					  //}
					  //for (int i = 0; i < Pointnum_L; i++)
					  //{
						 // Pos_Rec_Y_L[i] += y_tmp;
					  //}


					  //��ʼ����ϳĥ��
					  switch(g_TestInfo_L.TrackSel)
					  {
						  //double Pos_XMLPoint_X_L[SensorMaxPoint];
						  //double Pos_XMLPoint_Y_L[SensorMaxPoint];

					  case 0:
						  {
							  FuncCalculatingXml(Hdm_50,bFlagWeiDuiQi,bFlagTrack_L,Pointnum_L,Pos_Tmp_X_L,Pos_Tmp_Y_L,Num_R400_Start,pScbzPtr_X,pScbzPtr_Y);
							  //XmlScbz_XL[Num_Node_50]=Pos_Rec_X_L[Num_R400_Start-5];
							  //XmlScbz_YL[Num_Node_50]=Pos_Rec_Y_L[Num_R400_Start-5];//����δ����Ĺ����(����ϳĥ��ʱ������SCBZ��)
							  //XmlScbz_XL[Num_Node_50] = 36.328;
							  //XmlScbz_YL[Num_Node_50] = 32.753;
							  //������
							  /*int m=0;
							  for (int n=0;n<Pointnum_L;n++)
							  {
								  if (Pos_Rec_X_L[n]>-26 && Pos_Rec_X_L[n]<36.5 && Pos_Rec_Y_L[n]>0 && Pos_Rec_Y_L[n]<36.3)
								  {
									  pThreadParam->xData[m]=Pos_Rec_X_L[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
									  pThreadParam->zData[m]=Pos_Rec_Y_L[n];					 
									  m++;
								  }

							  }
							  pThreadParam->DataNum=m;
							  m=0;///����һ��Ҫ����*/

							  shangyi = FuncCalculatingHdm(Hdm_50,bFlagDuiQi,bFlagTrack_L,Pointnum_L,Pos_Rec_X_L,Pos_Rec_Y_L,Num_R400_Start);
							  HdmNode_XL_50[Num_Node_50] = 36.328;
							  HdmNode_YL_50[Num_Node_50] = 32.753;
							  for (int i = 0; i < Num_Node_50; i++)
							  {
								  XmlScbz_XL_50[i] = HdmNode_XL_50[i];
								  XmlScbz_YL_50[i] = HdmNode_YL_50[i];
								  pThreadParam->DistXml[i] = Dist_Xmljd_L_50[i];
								  pThreadParam->DistHdm[i] = Dist_Hdmjd_L_50[i];
							  }
							  XmlScbz_XL_50[Num_Node_50] = 36.328 + shangyi;
							  XmlScbz_YL_50[Num_Node_50] = 32.753;
							  //HdmNode_XL[Num_Node_50]=Pos_Rec_X_L[Num_R400_Start-5];
							  //HdmNode_YL[Num_Node_50]=Pos_Rec_Y_L[Num_R400_Start-5];//�������Ĺ���㣨����ʱ����㾫��ֵ��
							  //////////////////////////////////////////////////////////////////////////
							  int m=0;
							  for (int n=0;n<Pointnum_L;n++)
							  {
								  if (Pos_Rec_X_L[n]>-26 && Pos_Rec_X_L[n]<36.5 && Pos_Rec_Y_L[n]>0 && Pos_Rec_Y_L[n]<36.3)
								  {
									  pThreadParam->xData[m]=Pos_Rec_X_L[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
									  pThreadParam->zData[m]=Pos_Rec_Y_L[n];					 
									  m++;
								  }

							  }
							  pThreadParam->DataNum=m;
							  m=0;///����һ��Ҫ����
							  /*for (int i=0;i<Num_Node_50;i++)
							  {
								  pThreadParam->DistXml_50[i]=Dist_Xmljd_L_50[i];
								  pThreadParam->DistHdm_50[i]=Dist_Hdmjd_L_50[i];
							  }*/
//							  ////����״̬�õ��ֹͣ
//							  if (!moveBefore_L)
//							  {
//								  //if (1)//Pos_Rec_X_L[Pointnum_L-1]>=40  && Pos_Rec_X_L[Pointnum_L-1]<=55)
//								  //{
//									  continueErrorCnt_L=0;
//									  moveBefore_L=TRUE;
//									  m_MachineCtrl_L.MotorStop(m_Mscomm_L);
//
//									  //bFlagPOrder_L=m_MachineCtrl_L.MotorMove(0,bFlagPOrder_L,m_Mscomm_L);
//									  //bFlagPOrder_L=m_MachineCtrl_L.MotorMove(0,bFlagPOrder_L,m_Mscomm_L);
////								  }
//							  }
							  break;
						  }
					  case 1:
						  {
								
							  FuncCalculatingXml(Hdm_60,bFlagWeiDuiQi,bFlagTrack_L,Pointnum_L,Pos_Tmp_X_L,Pos_Tmp_Y_L,Num_R400_Start,pScbzPtr_X,pScbzPtr_Y);
							  //XmlScbz_XL[Num_Node]=Pos_Rec_X_L[Num_R400_Start-5];
							  //XmlScbz_YL[Num_Node]=Pos_Rec_Y_L[Num_R400_Start-5];//����δ����Ĺ����(����ϳĥ��ʱ������SCBZ��)

							  //������
							  /*int m=0;
							  for (int n=0;n<Pointnum_L;n++)
							  {
								  if (Pos_Rec_X_L[n]>-26 && Pos_Rec_X_L[n]<36.5 && Pos_Rec_Y_L[n]>0 && Pos_Rec_Y_L[n]<36.3)
								  {
									  pThreadParam->xData[m]=Pos_Rec_X_L[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
									  pThreadParam->zData[m]=Pos_Rec_Y_L[n];					 
									  m++;
								  }

							  }
							  pThreadParam->DataNum=m;
							  m=0;///����һ��Ҫ����*/

							  shangyi = FuncCalculatingHdm(Hdm_60,bFlagDuiQi,bFlagTrack_L,Pointnum_L,Pos_Rec_X_L,Pos_Rec_Y_L,Num_R400_Start);
							  //HdmNode_XL[Num_Node]=Pos_Rec_X_L[Num_R400_Start-5];
							  //HdmNode_YL[Num_Node]=Pos_Rec_Y_L[Num_R400_Start-5];//�������Ĺ���㣨����ʱ����㾫��ֵ��
							  HdmNode_XL[Num_Node]=36.8;
							  HdmNode_YL[Num_Node]=32.753;
							  for (int i=0;i<Num_Node;i++)
							  {
								  //XmlScbz_XL[i] = HdmNode_XL[i];
								  //XmlScbz_YL[i] = HdmNode_YL[i];
								  //========

								  //===========
								  pThreadParam->DistXml[i]=Dist_Xmljd_L[i];
								  pThreadParam->DistHdm[i]=Dist_Hdmjd_L[i];
							  }
							  XmlScbz_XL[Num_Node]=36.8+shangyi;
							  XmlScbz_YL[Num_Node]=32.753;
							  //////////////////////////////////////////////////////////////////////////
							  int m=0;
							  for (int n=0;n<Pointnum_L;n++)
							  {
								  if (Pos_Rec_X_L[n]>-26 && Pos_Rec_X_L[n]<36.5 && Pos_Rec_Y_L[n]>0 && Pos_Rec_Y_L[n]<36.3)
								  {
									  pThreadParam->xData[m]=Pos_Rec_X_L[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
									  pThreadParam->zData[m]=Pos_Rec_Y_L[n];					 
									  m++;
								  }

							  }
							  pThreadParam->DataNum=m;
							  m=0;///����һ��Ҫ����
//							  //����״̬�õ��ֹͣ
//							  if (!moveBefore_L)
//							  {
//								  //if (1)//Pos_Rec_X_L[Pointnum_L-1]>=40  && Pos_Rec_X_L[Pointnum_L-1]<=55)/*60����70*/
//								  //{
//									  continueErrorCnt_L=0;
//									  moveBefore_L=TRUE;
//									  m_MachineCtrl_L.MotorStop(m_Mscomm_L);
//
//									  //bFlagPOrder_L=m_MachineCtrl_L.MotorMove(0,bFlagPOrder_L,m_Mscomm_L);
//									  //bFlagPOrder_L=m_MachineCtrl_L.MotorMove(0,bFlagPOrder_L,m_Mscomm_L);
////								  }
//							  }
							  break;
						  }
					  }
					  //������Ϣ
					  
					  if (!g_StopDrawFlag_L&&DrawNum/3)
					  {
						  ::SendMessage(pThreadParam->hWnd, WM_2DTHREADMSG_XML_L, 0, 0);
						  Sleep(5);
						  ::SendMessage(pThreadParam->hWnd,WM_2DDISPLISTCTRL_L,1,0);//wParam==1,����ʾϳĥ����Ϣ
						  Sleep(5);
					  }

					  

					  OutLineSection_L.Lock();
					  //�洢����ϳĥ��ʱ��23��ʵ�⽻��ӹ���㣨���ƺ�
					  LoopBuff.LoopBuffWrite(&xHdmNodeLoopBuff_L,HdmNode_XL,nStNumNode+1);
					  LoopBuff.LoopBuffWrite(&zHdmNodeLoopBuff_L,HdmNode_YL,nStNumNode+1);
					  //�洢����ϳĥ��ʱ��23��ʵ���׼��ӹ���㣨����ǰ��
					  LoopBuff.LoopBuffWrite(&xScbzLoopBuff_L,XmlScbz_XL,nStNumNode+1);
					  LoopBuff.LoopBuffWrite(&zScbzLoopBuff_L,XmlScbz_YL,nStNumNode+1);
					  //�洢23������澫��
					  LoopBuff.LoopBuffWrite(&DistHdmJd_LoofBuff_L,Dist_Hdmjd_L,nStNumNode);
					  //�洢23��ϳĥ������
					  LoopBuff.LoopBuffWrite(&DistXmlJd_LoopBuff_L,Dist_Xmljd_L,nStNumNode);

					  OutLineSection_L.Unlock();
					  }
				  }
				  else if(isInvalidOutline==1)//��׼����������,��ʵ����������������ʵ������
				  {
					  switch(g_TestInfo_L.TrackSel)
					  {
					  case 0:
						  {
							  //shangyi = FuncCalculatingHdm(Hdm_50,bFlagWeiDuiQi,bFlagTrack_L,Pointnum_L,Pos_Rec_X_L,Pos_Rec_Y_L,Num_R400_Start);
							  //HdmScbz_XL[Num_Node_50]=Pos_Rec_X_L[Num_R400_Start-5];
							  //HdmScbz_YL[Num_Node_50]=Pos_Rec_Y_L[Num_R400_Start-5];//����δ����Ĺ����
							  //HdmScbz_XL[Num_Node]=36.8;
							  //HdmScbz_YL[Num_Node]=32.753;

							  ////������
							  //int m=0;
							  //for (int n=0;n<Pointnum_L;n++)
							  //{
								 // if (Pos_Rec_X_L[n]>-26 && Pos_Rec_X_L[n]<36.5 && Pos_Rec_Y_L[n]>0 && Pos_Rec_Y_L[n]<36.3)
								 // {
									//  pThreadParam->xData[m]=Pos_Rec_X_L[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
									//  pThreadParam->zData[m]=Pos_Rec_Y_L[n];					 
									//  m++;
								 // }

							  //}
							  //pThreadParam->DataNum=m;
							  //m=0;///����һ��Ҫ����

							  shangyi = FuncCalculatingHdm(Hdm_50,bFlagDuiQi,bFlagTrack_L,Pointnum_L,Pos_Rec_X_L,Pos_Rec_Y_L,Num_R400_Start);
							  //HdmNode_XL[Num_Node_50]=Pos_Rec_X_L[Num_R400_Start-5];
							  //HdmNode_YL[Num_Node_50]=Pos_Rec_Y_L[Num_R400_Start-5];//�������Ĺ����
							  HdmNode_XL[Num_Node_50]=36.328;
							  HdmNode_YL[Num_Node_50]=32.753;
							  for (int i=0;i<Num_Node_50;i++)
							  {
								  HdmScbz_XL[i] = HdmNode_XL[i];
								  HdmScbz_YL[i] = HdmNode_YL[i];
								  pThreadParam->DistXml[i]=Dist_Xmljd_L[i];
							  }
							  HdmScbz_XL[Num_Node_50]=36.328+shangyi;
							  HdmScbz_YL[Num_Node_50]=32.753;

							  //������
							  int m=0;
							  for (int n=0;n<Pointnum_L;n++)
							  {
								  if (Pos_Rec_X_L[n]>-26 && Pos_Rec_X_L[n]<36.5 && Pos_Rec_Y_L[n]>0 && Pos_Rec_Y_L[n]<36.3)
								  {
									  pThreadParam->xData[m]=Pos_Rec_X_L[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
									  pThreadParam->zData[m]=Pos_Rec_Y_L[n];					 
									  m++;
								  }

							  }
							  pThreadParam->DataNum=m;
							  m=0;///����һ��Ҫ����

							  for(int i=0;i<Num_Node_50;i++)////��׼��׼�����쳣�ǣ�ϳĥ����-1
							  {
								  Dist_Xmljd_L_50[i]=-1;
							  }
//							  ////����״̬�õ��ֹͣ
//							   if (isInvalidOutline==1)
//							   {
//								   if (!moveBefore_L)
//								   {
//									   //if (1)//Pos_Rec_X_L[Pointnum_L-1]>=40  && Pos_Rec_X_L[Pointnum_L-1]<=55)
//									   //{
//										   continueErrorCnt_L=0;
//										   moveBefore_L=TRUE;
//										   m_MachineCtrl_L.MotorStop(m_Mscomm_L);
//
//										   //bFlagPOrder_L=m_MachineCtrl_L.MotorMove(0,bFlagPOrder_L,m_Mscomm_L);
//										   //bFlagPOrder_L=m_MachineCtrl_L.MotorMove(0,bFlagPOrder_L,m_Mscomm_L);
////									   }
//								   }
//							   }
							  
							  
							  break;
						  }
					  case 1:
						  {
							  //shangyi = FuncCalculatingHdm(Hdm_60,bFlagWeiDuiQi,bFlagTrack_L,Pointnum_L,Pos_Rec_X_L,Pos_Rec_Y_L,Num_R400_Start);
							  //HdmScbz_XL[Num_Node]=Pos_Rec_X_L[Num_R400_Start-5];
							  //HdmScbz_YL[Num_Node]=Pos_Rec_Y_L[Num_R400_Start-5];//����δ����Ĺ����
							  //HdmScbz_XL[Num_Node]=36.8;
							 // HdmScbz_YL[Num_Node]=32.753;
							  //������
							  /*int m=0;
							  for (int n=0;n<Pointnum_L;n++)
							  {
								  if (Pos_Rec_X_L[n]>-26 && Pos_Rec_X_L[n]<36.5 && Pos_Rec_Y_L[n]>0 && Pos_Rec_Y_L[n]<36.3)
								  {
									  pThreadParam->xData[m]=Pos_Rec_X_L[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
									  pThreadParam->zData[m]=Pos_Rec_Y_L[n];					 
									  m++;
								  }

							  }
							  pThreadParam->DataNum=m;
							  m=0;///����һ��Ҫ����*/

							  shangyi = FuncCalculatingHdm(Hdm_60,bFlagDuiQi,bFlagTrack_L,Pointnum_L,Pos_Rec_X_L,Pos_Rec_Y_L,Num_R400_Start);
							 // HdmNode_XL[Num_Node]=Pos_Rec_X_L[Num_R400_Start-5];
							 // HdmNode_YL[Num_Node]=Pos_Rec_Y_L[Num_R400_Start-5];//�������Ĺ����
							  HdmNode_XL[Num_Node]=36.8;
							  HdmNode_YL[Num_Node]=32.753;
							  for (int i=0;i<Num_Node;i++)
							  {
								  HdmScbz_XL[i] = HdmNode_XL[i];
								  HdmScbz_YL[i] = HdmNode_YL[i];
								  pThreadParam->DistXml[i]=Dist_Xmljd_L[i];
							  }
							  HdmScbz_XL[Num_Node]=36.8+shangyi;
							  HdmScbz_YL[Num_Node]=32.753;
							  int m=0;
							  for (int n=0;n<Pointnum_L;n++)
							  {
								  if (Pos_Rec_X_L[n]>-26 && Pos_Rec_X_L[n]<36.5 && Pos_Rec_Y_L[n]>0 && Pos_Rec_Y_L[n]<36.3)
								  {
									  pThreadParam->xData[m]=Pos_Rec_X_L[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
									  pThreadParam->zData[m]=Pos_Rec_Y_L[n];					 
									  m++;
								  }

							  }
							  pThreadParam->DataNum=m;
							  m=0;///����һ��Ҫ����

							  for(int i=0;i<Num_Node;i++)////��׼��׼�����쳣�ǣ�ϳĥ����-1
							  {
								  Dist_Xmljd_L[i]=-1;
							  }
//							  if (isInvalidOutline==1)/******7.17��ע��*******/
//							  {
//								  ////����״̬�õ��ֹͣ
//								  if (!moveBefore_L)
//								  {
//									  //if (1)//Pos_Rec_X_L[Pointnum_L-1]>=40  && Pos_Rec_X_L[Pointnum_L-1]<=55)
//									  //{
//										  continueErrorCnt_L=0;
//										  moveBefore_L=TRUE;
//										  m_MachineCtrl_L.MotorStop(m_Mscomm_L);
//
//										  //bFlagPOrder_L=m_MachineCtrl_L.MotorMove(0,bFlagPOrder_L,m_Mscomm_L);
//										  //bFlagPOrder_L=m_MachineCtrl_L.MotorMove(0,bFlagPOrder_L,m_Mscomm_L);
////									}
//							   }
//							  }/******7.17��ע��*******/
							  
							  break;
						  }
					  }
					  //������Ϣ
					  
					   if (!g_StopDrawFlag_L&&DrawNum/3)
					   {
						   ::SendMessage(pThreadParam->hWnd, WM_2DTHREADMSG_XML_L, 0, 0);
						   Sleep(5);
						   ::SendMessage(pThreadParam->hWnd,WM_2DDISPLISTCTRL_L,1,0);
						   Sleep(5);
					   }
					  


					  OutLineSection_L.Lock();
					  //�洢����ϳĥ��ʱ��23��ʵ�⽻��ӹ���㣨���ƺ�
					  LoopBuff.LoopBuffWrite(&xHdmNodeLoopBuff_L,HdmNode_XL,nStNumNode+1);
					  LoopBuff.LoopBuffWrite(&zHdmNodeLoopBuff_L,HdmNode_YL,nStNumNode+1);
					  //�洢����ϳĥ��ʱ��23��ʵ���׼��ӹ���㣨����ǰ��		          
					  LoopBuff.LoopBuffWrite(&xScbzLoopBuff_L,XmlScbz_XL,nStNumNode+1);
					  LoopBuff.LoopBuffWrite(&zScbzLoopBuff_L,XmlScbz_YL,nStNumNode+1);
					  //�洢23������澫��
					  LoopBuff.LoopBuffWrite(&DistHdmJd_LoofBuff_L,Dist_Hdmjd_L,nStNumNode);
					  //�洢23��ϳĥ������
					  LoopBuff.LoopBuffWrite(&DistXmlJd_LoopBuff_L,Dist_Xmljd_L,nStNumNode);

					  OutLineSection_L.Unlock();
				  }		  
	
		      }
		  //}
		//else//�쳣����
		  if(isInvalidOutline!=1)
		  {
			  /*int nMtStopDist=0;
			  switch(g_TestInfo_L.TrackSel)
			  {
			  case 0:
			  nMtStopDist=55;
			  break;
			  case 1:
			  nMtStopDist=65;
			  break;
			  }*/
			  ++continueErrorCnt_L;//�쳣�����ĸ���
			 // 
			 // //if (moveBefore_L && isInvalidOutline==-2  &&continueErrorCnt_L>=10)//isInvalidOutLine =-2��ʾR400����Ҳ���
			 if (continueErrorCnt_L>=6)
			  {
				  /*if (isInvalidOutline==-3||isInvalidOutline==-8|isInvalidOutline==-11)
				  {
				  moveBefore_L=FALSE;
				  continueErrorCnt_L=0;
				  bFlagPOrder_L = m_MachineCtrl_L.MotorMove(MotorMoveLmt,bFlagPOrder_L,m_Mscomm_L);
				  }*/
				  //if(moveBefore_L)//�������쳣/******7.17��ע��*******/
				  //{
					 // if (Pos_Rec_X_L[Pointnum_L-1]<nMtStopDist)
					 // {
						//  moveBefore_L=FALSE; 
						//  continueErrorCnt_L=0;
						//  bFlagPOrder_L=m_MachineCtrl_L.MotorMove(MotorMoveLmt,bFlagPOrder_L,m_Mscomm_L);	
					 // }
					 // else
					 // {
						//  moveBefore_L=FALSE; 
						//  continueErrorCnt_L=0;
						//  bFlagPOrder_L=m_MachineCtrl_L.MotorMove(-MotorMoveLmt,bFlagPOrder_L,m_Mscomm_L);
					 // }
				  //}
				  //else//�쳣���쳣
				  //{
					 // int nResLimit=0;
					 // nResLimit=m_MachineCtrl_L.IsMotorLimit(m_Mscomm_L);
					 // if (nResLimit)//�ڼ���
					 // {
						//  if (nResLimit>0)//������
						//  { 
						//	  continueErrorCnt_L=0;
						//	  bFlagPOrder_L=m_MachineCtrl_L.MotorMove(-MotorMoveLmt,bFlagPOrder_L,m_Mscomm_L);
						//  }
						//  if (nResLimit<0)
						//  {
						//	  continueErrorCnt_L=0;
						//	  bFlagPOrder_L=m_MachineCtrl_L.MotorMove(MotorMoveLmt,bFlagPOrder_L,m_Mscomm_L);
						//  }
					 // }
				  //}/******7.17��ע��*******/
				  continueErrorCnt_L=0;
				  //////////////////////////////////////////////////////////////////////////
				   moveBefore_L=FALSE;
			  }
			  if (Readpointnum!=0)
			  {
				  memset(HdmNode_XL,0,(nStNumNode+1)*sizeof(double));
				  memset(HdmNode_YL,0,(nStNumNode+1)*sizeof(double));

				  memset(HdmScbz_XL,0,(nStNumNode+1)*sizeof(double));
				  memset(HdmScbz_YL,0,(nStNumNode+1)*sizeof(double));
				  memset(Dist_Hdmjd_L,0,nStNumNode*sizeof(double));
				  memset(Dist_Xmljd_L,0,nStNumNode*sizeof(double));

				  OutLineSection_L.Lock();
				  //�洢����ϳĥ��ʱ��23��ʵ�⽻��ӹ���㣨���ƺ�
				  LoopBuff.LoopBuffWrite(&xHdmNodeLoopBuff_L,HdmNode_XL,nStNumNode+1);
				  LoopBuff.LoopBuffWrite(&zHdmNodeLoopBuff_L,HdmNode_YL,nStNumNode+1);
				  //�洢����ϳĥ��ʱ��23��ʵ���׼��ӹ���㣨����ǰ��
				  LoopBuff.LoopBuffWrite(&xScbzLoopBuff_L,HdmScbz_XL,nStNumNode+1);
				  LoopBuff.LoopBuffWrite(&zScbzLoopBuff_L,HdmScbz_YL,nStNumNode+1);
				  //�洢23������澫��
				  LoopBuff.LoopBuffWrite(&DistHdmJd_LoofBuff_L,Dist_Hdmjd_L,nStNumNode);
				  //�洢23��ϳĥ������
				  if(1==g_TestInfo_L.XM_QianHou)//ϳĥ��
				  {
					 LoopBuff.LoopBuffWrite(&DistXmlJd_LoopBuff_L,Dist_Xmljd_L,nStNumNode);
				  }
				
				  OutLineSection_L.Unlock(); 
			  }
		  }

		}
		else
			Sleep(20);
		GetDataSection_L.Lock();
		iGetDataOutLineCnt=LoopBuff.LoopBuffDataLength(&GetDataNum_LoopBuff_L);
		GetDataSection_L.Unlock();
		if(iGetDataOutLineCnt>5)
			DrawNum++;
		else
			DrawNum=3;
		if(DrawNum>3)
			DrawNum=0;
	}
	if(bFlagQiangzhiStart)//�������if��Ϊ˳������������㼴Ϊ�쳣��׼�ļ����½���
	{
		bEndDealingFlag_L=true;
	}	
	return 0;
}
//�Ҳദ���߳�
UINT ThreadDealRight(LPVOID pParam)
{
//	OutLineArithmetic CalculateOutline;
//	double youyi_R;
//	moveBefore_R=TRUE; //�ж��Ƿ���һ��ָ��ʹ�������
//	continueErrorCnt_R=0;  //�������쳣�������м���
//	int nMtStopDist=0;
//	switch(g_TestInfo_R.TrackSel)
//	{
//	case 0:
//		nMtStopDist=55;
//		break;
//	case 1:
//		nMtStopDist=55;
//		break;
//	}
//
//	int iGetDataOutLineCnt=0;//�ɼ����ݻ�����ȡ���ݼ�����
//	double Pos_Init_X_R[SensorMaxPoint],Pos_Init_Y_R[SensorMaxPoint];//��������������ʱ�������
//	double Pos_Rec_X_R[SensorMaxPoint]={0},Pos_Rec_Y_R[SensorMaxPoint]={0};//��Ŵ��������
//	int iGetDataTempArray[1]={0};//��Ŷ��������ĵ���
//	//int HdmORXmlDataNum[1];//���ϳĥ�����߾���ֵ�ĵ���
//	int Readpointnum=0;///��¼�ӻ���������������������
//	int isInvalidOutline=-1;//��־�����Ƿ���Ч
//	int Pointnum_R=0;//Ԥ����֮�����������
//	int Num_R400_Start=0; //����R400�����
//	int nStNumNode;
//	switch(g_TestInfo_L.TrackSel)
//	{
//	case 0://50��
//		{
//			nStNumNode=19;
//			break;
//		}
//
//	case 1://60��
//		{
//			nStNumNode=23;
//			break;
//		}
//	}
//	//�洢ϳĥ��ʵ���׼���ļ�
//	double* pScbzPtr_X=NULL;
//	pScbzPtr_X=new double[nStNumNode];
//	double* pScbzPtr_Y=NULL;
//	pScbzPtr_Y=new double[nStNumNode];
//
//	CStdioFile XML_SCBZDfile;
//	CString strLinetemp;
//	int ScbzdFileNum=0;
//	int iNeedCount=0;
//	int ErrorSCBZD=0;
//	int XmlPointNum=0;//��̼���
//	int DrawNum=3;
//	double XML_SCBZDbegin=0;
//	double XML_SCBZDend=0;
//	double Mileage=0;
//	double MileageTop=0;
//	bool   IsReadStop=true;//Ĭ���ǲ�ֹͣѭ����ȡ
//	BOOL   IsInvalidBZPoint = TRUE;
//	THREAD_PARAM2D* pThreadParam = (THREAD_PARAM2D*)pParam;
//
//	OutlineFileHelper fileHelper("����������R.txt");
//
//	CHighPrecisionDlg *dlg;
//	dlg = (CHighPrecisionDlg *)pdlg;
//
//	GetDataSection_R.Lock();
//	iGetDataOutLineCnt=LoopBuff.LoopBuffDataLength(&GetDataNum_LoopBuff_R);
//	GetDataSection_R.Unlock();
//	while((iGetDataOutLineCnt||bFlagStartThread)&&bFlagQiangzhiStart)
//	{
//		iNeedCount=0;
//		ErrorSCBZD=0;
//		if (iGetDataOutLineCnt>0)
//		{
//			ZeroMemory(Pos_Init_X_R,sizeof(Pos_Init_X_R));
//			ZeroMemory(Pos_Init_Y_R,sizeof(Pos_Init_Y_R));
//			GetDataSection_R.Lock();
//			LoopBuff.LoopBuffRead(&GetDataNum_LoopBuff_R,iGetDataTempArray,1);
//			LoopBuff.LoopBuffRead(&xGetData_LoopBuff_R,Pos_Init_X_R,iGetDataTempArray[0]);
//			LoopBuff.LoopBuffRead(&zGetData_LoopBuff_R,Pos_Init_Y_R,iGetDataTempArray[0]);
//			GetDataSection_R.Unlock();
//			XmlPointNum++;
//			Readpointnum=iGetDataTempArray[0];
//
//			//switch()//�ж�ѡ�����50�컹��60��
//			switch(g_TestInfo_R.TrackSel)
//			{
//			case 0://50��
//				Point_50INFO_R.pInDataX           =Pos_Init_X_R;
//				Point_50INFO_R.pInDataY           =Pos_Init_Y_R;
//				Point_50INFO_R.In_Num             =Readpointnum;
//				Point_50INFO_R.FittingRadius_R20  =20;
//				Point_50INFO_R.FittingRadius_R400 =350;
//
//				isInvalidOutline=Preproccess(Point_50INFO_R,Track_50);	
//				if(isInvalidOutline==1)
//				{
//					for(int i=0;i<Point_50INFO_R.Out_Num;i++)
//					{
//						Pos_Rec_X_R[i]=Point_50INFO_R.pOutDataX[i];
//						Pos_Rec_Y_R[i]=Point_50INFO_R.pOutDataY[i];
//					}
//					Pointnum_R      = Point_50INFO_R.Out_Num;///���洦����ɵ������ĵ�����pointnum
//					Num_R400_Start  = Point_50INFO_R.Num_R400Start; 
//				}
//				break;
//			case 1://60��
//				Point_60INFO_R.pInDataX           =Pos_Init_X_R;
//				Point_60INFO_R.pInDataY           =Pos_Init_Y_R;
//				Point_60INFO_R.In_Num             =Readpointnum;
//				Point_60INFO_R.FittingRadius_R20  =20;
//				Point_60INFO_R.FittingRadius_R400 =400;
//
//				isInvalidOutline=Preproccess(Point_60INFO_R,Track_60);
//				if(isInvalidOutline==1)
//				{
//					for(int i=0;i<Point_60INFO_R.Out_Num;i++)
//					{
//						Pos_Rec_X_R[i]=Point_60INFO_R.pOutDataX[i];
//						Pos_Rec_Y_R[i]=Point_60INFO_R.pOutDataY[i];
//					}
//					Pointnum_R      = Point_60INFO_R.Out_Num;///���洦����ɵ������ĵ�����pointnum
//					Num_R400_Start  = Point_60INFO_R.Num_R400Start;
//				}
//				else
//				{
//					int randNum = std::rand() % 50;
//					double targetMeter = 0.1 * (double)randNum;
//					Outline outline = fileHelper.getOutlineByMileage(targetMeter);
//					for (int i = 0; i < outline.m_pointNum; i++)
//					{
//						Pos_Rec_X_R[i] = outline.m_coordinateX[i];
//						Pos_Rec_Y_R[i] = outline.m_coordinateY[i];
//					}
//
//					for (int i = 0; i < outline.m_pointNum - 1; ++i)
//					{
//						double xDis = outline.m_coordinateX[i + 1] - outline.m_coordinateX[i];
//						double yDis = outline.m_coordinateY[i + 1] - outline.m_coordinateY[i];
//						if (sqrt(xDis * xDis + yDis * yDis) >= 5)
//						{
//							Num_R400_Start = i + 1;
//							break;
//						}
//					}
//				}
//				break;
//			}		
//			//if(isInvalidOutline==1)//������Ч
//			//{
//				double shangyi = 0;
//				//ϳĥǰ
//				if(g_TestInfo_R.XM_QianHou==0&&isInvalidOutline==1)
//				{
//					//continueErrorCnt_L=0;//
//
//					switch(g_TestInfo_R.TrackSel)
//					{
//					case 0://50��						 
//
//						//FuncCalculatingHdm(Hdm_50,bFlagWeiDuiQi,bFlagTrack_R,Pointnum_R,Pos_Rec_X_R,Pos_Rec_Y_R,Num_R400_Start);
//						//HdmScbz_XR_50[Num_Node_50]=Pos_Rec_X_R[Num_R400_Start-5];
//						//HdmScbz_YR_50[Num_Node_50]=Pos_Rec_Y_R[Num_R400_Start-5];//����δ����Ĺ����
//						shangyi = FuncCalculatingHdm(Hdm_50,bFlagDuiQi,bFlagTrack_R,Pointnum_R,Pos_Rec_X_R,Pos_Rec_Y_R,Num_R400_Start);
//						//HdmNode_XR_50[Num_Node_50]=Pos_Rec_X_R[Num_R400_Start-5];
//						//HdmNode_YR_50[Num_Node_50]=Pos_Rec_Y_R[Num_R400_Start-5];//�������Ĺ����
//						HdmNode_XR_50[Num_Node_50] = 36.328;
//						HdmNode_YR_50[Num_Node_50] = 32.753;
//						for (int i=0;i<Num_Node_50;i++)
//						{
//							HdmScbz_XR_50[i]=HdmNode_XR_50[i];
//							HdmScbz_YR_50[i]=HdmNode_YR_50[i];
//							pThreadParam->DistHdm_50[i] = Dist_Hdmjd_R_50[i];
//						}
//						HdmScbz_XR_50[Num_Node_50] = 36.328 + shangyi;
//						HdmScbz_YR_50[Num_Node_50] = 32.753;
//
//						////����״̬�õ��ֹͣ
//						//if (!moveBefore_R)
//						//{
//						//	if (1)//Pos_Rec_X_R[Pointnum_R-1]>=30  && Pos_Rec_X_R[Pointnum_R-1]<=60)
//						//	{
//						//		continueErrorCnt_R=0;
//						//		moveBefore_R=TRUE;
//						//		m_MachineCtrl_R.MotorStop(m_Mscomm_R);
//						//		//bFlagPOrder_R=m_MachineCtrl_R.MotorMove(0,bFlagPOrder_R,m_Mscomm_R);
//						//		//bFlagPOrder_R=m_MachineCtrl_R.MotorMove(0,bFlagPOrder_R,m_Mscomm_R);
//						//	}
//						//}
//						break;
//					case 1: //60��
//						//FuncCalculatingHdm(Hdm_60,bFlagWeiDuiQi,bFlagTrack_R,Pointnum_R,Pos_Rec_X_R,Pos_Rec_Y_R,Num_R400_Start);
//						//HdmScbz_XR[Num_Node]=Pos_Rec_X_R[Num_R400_Start-5];
//						//HdmScbz_YR[Num_Node]=Pos_Rec_Y_R[Num_R400_Start-5];//����δ����Ĺ����
//						//HdmScbz_XR[Num_Node]=36.8;
//						//HdmScbz_YR[Num_Node]=32.753;
//						shangyi = FuncCalculatingHdm(Hdm_60,bFlagDuiQi,bFlagTrack_R,Pointnum_R,Pos_Rec_X_R,Pos_Rec_Y_R,Num_R400_Start);
//						//HdmNode_XR[Num_Node]=Pos_Rec_X_R[Num_R400_Start-5];
//						//HdmNode_YR[Num_Node]=Pos_Rec_Y_R[Num_R400_Start-5];//�������Ĺ����
//						HdmNode_XR[Num_Node]=36.8;
//						HdmNode_YR[Num_Node]=32.753;
//
//						FuncCalculatingHdm(Hdm_60,bFlagWeiDuiQi,bFlagTrack_R,Pointnum_R,Pos_Rec_X_R,Pos_Rec_Y_R,Num_R400_Start);
//
//
//						for (int i=0;i<Num_Node;i++)
//						{
//							//HdmScbz_XR[i]=HdmNode_XR[i];
//							//HdmScbz_YR[i]=HdmNode_YR[i];
//							//HdmScbz_XR[i]=HdmNode_XR[i]+shangyi;
//							//HdmScbz_YR[i]=HdmNode_YR[i]-shangyi;
//							pThreadParam->DistHdm[i]=Dist_Hdmjd_R[i];
//						}
//						HdmScbz_XR[Num_Node]=36.8+shangyi;
//						HdmScbz_YR[Num_Node]=32.753;
//						
//
//						////����״̬�õ��ֹͣ
//						//if (!moveBefore_R)
//						//{
//						//	if (1)//Pos_Rec_X_R[Pointnum_R-1]>=40  && Pos_Rec_X_R[Pointnum_R-1]<=70)
//						//	{
//						//		continueErrorCnt_R=0;
//						//		moveBefore_R=TRUE;
//						//		//bFlagPOrder_R=m_MachineCtrl_R.MotorMove(0,bFlagPOrder_R,m_Mscomm_R);
//						//		//bFlagPOrder_R=m_MachineCtrl_R.MotorMove(0,bFlagPOrder_R,m_Mscomm_R);
//						//		m_MachineCtrl_R.MotorStop(m_Mscomm_R);
//						//	}
//						//}
//						break;
//					}	
//					//��ʼ��ͼ
//					//����ֵ
//					
//					//������
//					int m=0;
//					for (int n=0;n<Pointnum_R;n++)
//					{
//						if (Pos_Rec_X_R[n]>-26 && Pos_Rec_X_R[n]<36.5 && Pos_Rec_Y_R[n]>0 && Pos_Rec_Y_R[n]<36.3)
//						{
//							pThreadParam->xData[m]=Pos_Rec_X_R[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
//							pThreadParam->zData[m]=Pos_Rec_Y_R[n];					 
//							m++;
//						}
//
//					}
//					pThreadParam->DataNum=m;
//					//������Ϣ
//					 if (!g_StopDrawFlag_R&&DrawNum/3)
//					 {
//						 ::SendMessage(pThreadParam->hWnd, WM_2DTHREADMSG_R, 0, 0);
//						  Sleep(5);
//						 ::SendMessage(pThreadParam->hWnd,WM_2DDISPLISTCTRL_R,0,0);//ϳĥǰ			
//					 }
//					// CString tempstr;
//					// tempstr.Format("%f",Pos_Rec_X_R[Pointnum_R-1]);
//					// dlg->m_List_ResultInfo.InsertItem(25,_T("���ҵ�"));
//					
//					// dlg->m_List_ResultInfo.SetItemText(25,2,tempstr);
//					 //������Ϣ
//					 		
//					//�����ݴ��뻺����					
//
//					OutLineSection_L.Lock();
//					//�洢����ϳĥ��ʱ��23��ʵ�⽻��ӹ���㣨���ƺ�
//					LoopBuff.LoopBuffWrite(&xHdmNodeLoopBuff_R,HdmNode_XR,nStNumNode+1);
//					LoopBuff.LoopBuffWrite(&zHdmNodeLoopBuff_R,HdmNode_YR,nStNumNode+1);
//					//�洢����ϳĥ��ʱ��23��ʵ���׼��ӹ���㣨����ǰ��
//					LoopBuff.LoopBuffWrite(&xScbzLoopBuff_R,HdmScbz_XR,nStNumNode+1);
//					LoopBuff.LoopBuffWrite(&zScbzLoopBuff_R,HdmScbz_YR,nStNumNode+1);
//					//�洢23������澫��
//					LoopBuff.LoopBuffWrite(&DistHdmJd_LoofBuff_R,Dist_Hdmjd_R,nStNumNode);
//					OutLineSection_L.Unlock();
//				}
//				////ϳĥ��
//				if(g_TestInfo_R.XM_QianHou==1)
//				{
//					//��ȡϳĥ����׼������
//					//*��ʵ���׼�㸳ֵ��pScbzPtr_X,pScbzPtr_Y*//
//					Mileage=XmlPointNum*Encoder_Distance+g_TestInfo_R.DistanceStart;//�������ǰ���
//					//��ȡϳĥ����׼������
//					//*��ʵ���׼�㸳ֵ��pScbzPtr_X,pScbzPtr_Y*//
//					BOOL IsOpen = XML_SCBZDfile.Open(g_TestInfo_R.XMH_BaseFile[ScbzdFileNum],CFile::modeRead);
//					if(IsOpen)
//					{
//						//������׼�ļ�����ʼ��̺���ֹ���
//						XML_SCBZDfile.SeekToBegin();
//						XML_SCBZDfile.ReadString(strLinetemp);//��ȡ��һ�У����뿪ʼ���
//						char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
//						char *strtemp = NULL;  
//						strtemp = strtok(str, " ");  
//						if(strtemp != NULL)
//						{
//							char *TopData1 = strtemp;
//							XML_SCBZDbegin = atof(TopData1);
//						}
//						XML_SCBZDfile.Seek(-80,CFile::end);//��ȡ�ļ�����ֹ���
//						XML_SCBZDfile.ReadString(strLinetemp);
//						XML_SCBZDfile.ReadString(strLinetemp);
//						char *str1 = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
//						char *strtemp1 = NULL;  
//						strtemp1 = strtok(str1, " ");  
//						if(strtemp1 != NULL)
//						{
//							char *TopData2 = strtemp1;
//							XML_SCBZDend=atof(TopData2);
//						}	
//						double tmpXML_SCBZDend = XML_SCBZDend;
//						double tmpXML_SCBZDbegin = XML_SCBZDbegin;
//						if (Encoder_Distance < 0)//����
//						{
//							double temp = tmpXML_SCBZDbegin;
//							tmpXML_SCBZDbegin = tmpXML_SCBZDend;
//							tmpXML_SCBZDend = temp;
//						}
//
//						//��ʼ��ȡ��Ӧ��̵�����
//						//if(!(Mileage>tmpXML_SCBZDend)&&!(Mileage<tmpXML_SCBZDbegin))
//						double eps = 0.001;//С���������洢���
//						//��ʼ��ȡ��Ӧ��̵�����
//						//if(!(Mileage>XML_SCBZDend)&&!(Mileage<XML_SCBZDbegin))
//						if(!(Mileage>(tmpXML_SCBZDend+eps))&&!(Mileage<(tmpXML_SCBZDbegin-eps)))
//						{
//							//�Ӿ���ֵ
//							XML_SCBZDfile.Seek(int(abs(((Mileage-XML_SCBZDbegin)*10*24*31))),CFile::begin);//��������������
//							while( XML_SCBZDfile.ReadString(strLinetemp))//��ȡʵ���׼��
//							{
//								char *str2 = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
//								char *strtemp2 = NULL;  
//								strtemp2 = strtok(str2, " "); 
//								char *TopData = strtemp2;
//								if(TopData != NULL)
//								{		
//									MileageTop = atof(TopData);
//								}
//								if(fabs(MileageTop-Mileage)<1e-8)
//								{
//									strtemp2 = strtok(NULL, " "); 							 
//									char *Xdata = strtemp2; 
//									if (Xdata != NULL)  
//									{  
//										pScbzPtr_X[iNeedCount] =atof(Xdata); 
//									}  	
//									strtemp2 = strtok(NULL, " ");  						
//									char *Ydata = strtemp2;
//									if (Ydata != NULL)  
//									{  	
//										pScbzPtr_Y[iNeedCount]= atof(Ydata);
//										if(0==pScbzPtr_Y[iNeedCount])	
//										{
//											ErrorSCBZD++;
//											if(ErrorSCBZD==nStNumNode+1)	
//												IsInvalidBZPoint = FALSE;
//										}
//										else
//											IsInvalidBZPoint = TRUE;
//									} 
//									iNeedCount++;
//									IsReadStop = false;
//								}
//								else
//								{
//									if(IsReadStop==false)
//									{
//										//XML_SCBZDfile.Seek(-35,CFile::current);
//										IsReadStop=true;
//										break;
//									}
//								}
//							}			
//							if(fabs(Mileage-XML_SCBZDend)<1e-8)//��������ļ�����ֹ��̣����Զ���ȡ��һ���ļ�
//							{
//								if(g_TestInfo_R.XMH_BaseFileNum-1>ScbzdFileNum)
//								{
//									ScbzdFileNum++;
//								}
//							}
//							XML_SCBZDfile.Close();
//						}
//						else
//						{
//							if(bFlagQiangzhiStart)
//							{
//								bFlagStartThread =false;  //�ɼ��߳�ֹͣ
//								bFlagQiangzhiStart = false;//�߳�ǿ��ֹͣ
//								bEndDealingFlag_L =TRUE;
//								bEndDealingFlag_R =TRUE;
//								AfxMessageBox(_T("������׼�ļ���̷�Χ"));
//								
//								
//							}							
//							XML_SCBZDfile.Close();
//							bFlagQiangzhiStart =false;//�����߳�ǿ��ֹͣ
//							bFlagStartThread =false;  //�ɼ��߳�ֹͣ
//							//bEndDealingFlag_R =TRUE;
//							return 0;
//						}
//					}
//					else//������ܴ�
//					{
//						if(bFlagQiangzhiStart)
//						{
//							bFlagStartThread =false;  //�ɼ��߳�ֹͣ
//							bFlagQiangzhiStart = false;//�߳�ǿ��ֹͣ
//							bEndDealingFlag_L =TRUE;
//							bEndDealingFlag_R =TRUE;
//							AfxMessageBox(_T("��׼�ļ��쳣�������µ����׼�ļ�"));
//							
//							
//						}
//						bFlagQiangzhiStart = false;//�߳�ǿ��ֹͣ
//						bFlagStartThread =false;  //�ɼ��߳�ֹͣ
//						//bEndDealingFlag_R =TRUE;
//						return 0;
//					}
//
//					if(IsInvalidBZPoint)//��׼������������������
//					{
//						//������׼������
//						int WdqCount=0;
//						for (int n=0;n<nStNumNode+1;n++)//��������ϳĥ��δ��������һ��24����
//						{		
//							//if(pScbzPtr_X[n]!=0&&pScbzPtr_Y[n]!=0)
//							//{
//								pThreadParam->WdqData_X[WdqCount] =pScbzPtr_X[n];
//								pThreadParam->WdqData_Y[WdqCount] =pScbzPtr_Y[n];
//								
//								if(WdqCount == nStNumNode)
//								{
//									shangyi = pThreadParam->WdqData_X[WdqCount]-36.8;
//									pThreadParam->WdqData_X[WdqCount] -= shangyi;
//								}
//								WdqCount++;
//							//}
//							
//						}
//						pThreadParam->WdqNum = WdqCount;
//						if (!g_StopDrawFlag_R)
//						{
//							::SendMessage(pThreadParam->hWnd, WM_2DTHREADMSG_XMLscbz_R, 0, 0);
//						    Sleep(5);
//						}
//						if (isInvalidOutline==1)
//						{
//							//continueErrorCnt_R=0;//						
//						//��������ϳĥǰ�ľ���
//						for(int i=0;i<Pointnum_R;i++)
//						{
//
//							Pos_Rec_Y_R[i] = Pos_Rec_Y_R[i]-shangyi;
//						}
//						
//						double Pos_Tmp_X_R[700], Pos_Tmp_Y_R[700];//�м����飬���ڼ���ϳĥ��ǰ�Ĺ������ת
//						for (int i = 0; i < Pointnum_R; i++)
//						{
//							Pos_Tmp_X_R[i] = Pos_Rec_X_R[i];
//							Pos_Tmp_Y_R[i] = Pos_Rec_Y_R[i];
//						}
//						GuiDiPoRevolve(Pointnum_R, Pos_Tmp_X_R,Pos_Tmp_Y_R,false,Guidipo_R);
//						//////////////////�Ҳ�춥��////////////////////////////////
//						//double Pos_Rec_X_Rtmp[700], Pos_Rec_Y_Rtmp[700];
//						//for (int i = 0; i < Pointnum_R; i++)
//						//{
//						//	Pos_Rec_X_Rtmp[i] = Pos_Rec_X_R[i];
//						//	Pos_Rec_Y_Rtmp[i] = Pos_Rec_Y_R[i];
//						//}
//						//double Pos_X_Rxl[300], Pos_Y_Rxl[300];
//						//int n = 0;
//						//for (int i = 0; i < Pointnum_R; i++)
//						//{
//						//	if (Pos_Rec_X_Rtmp[i] >= -10 && Pos_Rec_X_Rtmp[i] <= 10&&Pos_Rec_Y_Rtmp[i]<20)
//						//	{
//						//		Pos_X_Rxl[n] = Pos_Rec_X_Rtmp[i];
//						//		Pos_Y_Rxl[n] = Pos_Rec_Y_Rtmp[i];
//						//		n++;
//						//	}
//						//}
//						//double xielv = CalculateOutline.LineFitLeastSquares(Pos_X_Rxl, Pos_Y_Rxl, n);
//						//double gd_theta = atan(xielv);
//						//gd_theta = 0.024784;
//
//						//double y_tmp;
//						//for (int i = 0; i < Pointnum_R; i++)
//						//{
//						//	if (Pos_Rec_X_R[i] <= 0 && Pos_Rec_X_R[i + 1] >= 0)
//						//	{
//						//		y_tmp = (-Pos_Rec_X_R[i])* (Pos_Rec_Y_R[i] - Pos_Rec_Y_R[i + 1]) / (Pos_Rec_X_R[i] - Pos_Rec_X_R[i + 1])+ Pos_Rec_Y_R[i];
//						//		break;
//						//	}
//						//}
//						//for (int i = 0; i < Pointnum_R; i++)
//						//{
//						//	Pos_Rec_Y_R[i] -= y_tmp;
//						//}
//						//for (int i = 0; i < Pointnum_R; i++)
//						//{
//						//	Pos_Rec_X_Rtmp[i] = Pos_Rec_X_R[i] * cos(-gd_theta) - Pos_Rec_Y_R[i] * sin(-gd_theta);
//						//	Pos_Rec_Y_Rtmp[i] = Pos_Rec_X_R[i] * sin(-gd_theta) + Pos_Rec_Y_R[i] * cos(-gd_theta);
//						//}
//						//for (int i = 0; i < Pointnum_R; i++)
//						//{
//						//	Pos_Rec_X_R[i] = Pos_Rec_X_Rtmp[i];
//						//	Pos_Rec_Y_R[i] = Pos_Rec_Y_Rtmp[i];
//						//}
//						//for (int i = 0; i < Pointnum_R; i++)
//						//{
//						//	if (Pos_Rec_Y_R[i] <= 14.2 && Pos_Rec_X_R[i + 1] >= 14.2)
//						//	{
//						//		double x_tmp = (14.2 - Pos_Rec_Y_R[i])*(Pos_Rec_X_R[i] - Pos_Rec_X_R[i + 1]) / (Pos_Rec_Y_R[i] - Pos_Rec_X_R[i + 1]) + Pos_Rec_X_R[i];
//						//		youyi_R = 35.4 - x_tmp;
//						//		break;
//						//	}
//						//}
//						//for (int i = 0; i < Pointnum_R; i++)
//						//{
//						//	Pos_Rec_X_R[i] += youyi_R;
//						//}
//						//for (int i = 0; i < Pointnum_R; i++)
//						//{
//						//	Pos_Rec_Y_R[i] += y_tmp;
//						//}
//
//						//��ʼ����ϳĥ��
//						switch(g_TestInfo_R.TrackSel)
//						{
//							//double Pos_XMLPoint_X_R[SensorMaxPoint];
//							//double Pos_XMLPoint_Y_R[SensorMaxPoint];
//
//						case 0:
//							{
//								FuncCalculatingXml(Hdm_50,bFlagWeiDuiQi,bFlagTrack_R,Pointnum_R,Pos_Rec_X_R,Pos_Rec_Y_R,Num_R400_Start,pScbzPtr_X,pScbzPtr_Y);
//								//XmlScbz_XR_50[Num_Node_50]=Pos_Rec_X_R[Num_R400_Start-1];
//								//XmlScbz_YR_50[Num_Node_50]=Pos_Rec_Y_R[Num_R400_Start-1];//����δ����Ĺ����(����ϳĥ��ʱ������SCBZ��)
//
//								//������
//								/*int m=0;
//								for (int n=0;n<Pointnum_R;n++)
//								{
//									if (Pos_Rec_X_R[n]>-26 && Pos_Rec_X_R[n]<36.5 && Pos_Rec_Y_R[n]>0 && Pos_Rec_Y_R[n]<36.3)
//									{
//										pThreadParam->xData[m]=Pos_Rec_X_R[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
//										pThreadParam->zData[m]=Pos_Rec_Y_R[n];					 
//										m++;
//									}
//
//								}
//								pThreadParam->DataNum=m;
//								m=0;///����һ��Ҫ����*/
//
//
//								shangyi = FuncCalculatingHdm(Hdm_50,bFlagDuiQi,bFlagTrack_R,Pointnum_R,Pos_Rec_X_R,Pos_Rec_Y_R,Num_R400_Start);
//								//HdmNode_XR_50[Num_Node_50]=Pos_Rec_X_R[Num_R400_Start-1];
//								//HdmNode_YR_50[Num_Node_50]=Pos_Rec_Y_R[Num_R400_Start-1];//�������Ĺ���㣨����ʱ����㾫��ֵ��
//								HdmNode_XR_50[Num_Node_50] = 36.328;
//								HdmNode_YR_50[Num_Node_50] = 32.753;
//								for (int i=0;i<Num_Node_50;i++)
//								{
//									//XmlScbz_XR_50[i] = HdmNode_XR_50[i];
//									//XmlScbz_YR_50[i] = HdmNode_YR_50[i];
//									//====
//
//
//									pThreadParam->DistXml_50[i]=Dist_Xmljd_R_50[i];
//									pThreadParam->DistHdm_50[i]=Dist_Hdmjd_R_50[i];
//								}
//								XmlScbz_XR_50[Num_Node_50] = 36.328 + shangyi;
//								XmlScbz_YR_50[Num_Node_50] = 32.753;
//								//////////////////////////////////////////////////////////////////////////
//								int m=0;
//								for (int n=0;n<Pointnum_R;n++)
//								{
//									if (Pos_Rec_X_R[n]>-26 && Pos_Rec_X_R[n]<36.5 && Pos_Rec_Y_R[n]>0 && Pos_Rec_Y_R[n]<36.3)
//									{
//										pThreadParam->xData[m]=Pos_Rec_X_R[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
//										pThreadParam->zData[m]=Pos_Rec_Y_R[n];					 
//										m++;
//									}
//
//								}
//								pThreadParam->DataNum=m;
//								m=0;///����һ��Ҫ����
//								//if (isInvalidOutline==1)
//								//{
//								//	//����״̬�õ��ֹͣ
//								//	if (!moveBefore_R)
//								//	{
//								//		if (1)//Pos_Rec_X_R[Pointnum_R-1]>=40  && Pos_Rec_X_R[Pointnum_R-1]<=70)
//								//		{
//								//			continueErrorCnt_R=0;
//								//			moveBefore_R=TRUE;
//								//			//bFlagPOrder_R=m_MachineCtrl_R.MotorMove(0,bFlagPOrder_R,m_Mscomm_R);
//								//			//bFlagPOrder_R=m_MachineCtrl_R.MotorMove(0,bFlagPOrder_R,m_Mscomm_R);
//								//			m_MachineCtrl_R.MotorStop(m_Mscomm_R);
//								//		}
//								//	}
//								//}
//								
//								break;
//							}
//						case 1:
//							{
//								FuncCalculatingXml(Hdm_60,bFlagWeiDuiQi,bFlagTrack_R,Pointnum_R,Pos_Tmp_X_R,Pos_Tmp_Y_R,Num_R400_Start,pScbzPtr_X,pScbzPtr_Y);
//								//FuncCalculatingHdm_Xml(Hdm_60,bFlagWeiDuiQi,bFlagTrack_R,Pointnum_R,Pos_Rec_X_R,Pos_Rec_Y_R,Num_R400_Start,pScbzPtr_X,pScbzPtr_Y);
//								//XmlScbz_XR[Num_Node]=Pos_Rec_X_R[Num_R400_Start-1];
//								//XmlScbz_YR[Num_Node]=Pos_Rec_Y_R[Num_R400_Start-1];//����δ����Ĺ����(����ϳĥ��ʱ������SCBZ��)
//
//								////������
//								//int m=0;
//								//for (int n=0;n<Pointnum_R;n++)
//								//{
//								//	if (Pos_Rec_X_R[n]>-26 && Pos_Rec_X_R[n]<36.5 && Pos_Rec_Y_R[n]>0 && Pos_Rec_Y_R[n]<36.3)
//								//	{
//								//		pThreadParam->xData[m]=Pos_Rec_X_R[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
//								//		pThreadParam->zData[m]=Pos_Rec_Y_R[n];					 
//								//		m++;
//								//	}
//
//								//}
//								//pThreadParam->DataNum=m;
//								//m=0;///����һ��Ҫ����
//
//
//								//for (int i=0;i<Num_Node;i++)
//								//{
//								//	//XmlScbz_XR[i] = HdmNode_XR[i];
//								//	//XmlScbz_YR[i] = HdmNode_YR[i];
//								//	XmlScbz_XR[i] = HdmScbz_XR[i];
//								//	XmlScbz_YR[i] = HdmScbz_YR[i];
//								//}
//								shangyi = FuncCalculatingHdm(Hdm_60,bFlagDuiQi,bFlagTrack_R,Pointnum_R,Pos_Rec_X_R,Pos_Rec_Y_R,Num_R400_Start);
//								//HdmNode_XR[Num_Node]=Pos_Rec_X_R[Num_R400_Start-1];
//								//HdmNode_YR[Num_Node]=Pos_Rec_Y_R[Num_R400_Start-1];//�������Ĺ���㣨����ʱ����㾫��ֵ��
//								HdmNode_XR[Num_Node]=36.8;
//								HdmNode_YR[Num_Node]=32.753;
//								for (int i=0;i<Num_Node;i++)
//								{
//									//XmlScbz_XR[i] = HdmNode_XR[i];
//									//XmlScbz_YR[i] = HdmNode_YR[i];
//									//XmlScbz_XR[i] = HdmScbz_XR[i];
//									//XmlScbz_YR[i] = HdmScbz_YR[i];
//
//									//===========
//									//Dist_Xmljd_R[i] = sqrt((XmlScbz_XR[i]-pScbzPtr_X[i])*(XmlScbz_XR[i]-pScbzPtr_X[i])+(XmlScbz_YR[i]-pScbzPtr_Y[i])*(XmlScbz_YR[i]-pScbzPtr_Y[i]));
//
//									pThreadParam->DistXml[i]=Dist_Xmljd_R[i];
//									pThreadParam->DistHdm[i]=Dist_Hdmjd_R[i];
//								}
//								XmlScbz_XR[Num_Node]=36.8+shangyi;
//								XmlScbz_YR[Num_Node]=32.753;
//								//������
//								int m=0;
//								for (int n=0;n<Pointnum_R;n++)
//								{
//									if (Pos_Rec_X_R[n]>-26 && Pos_Rec_X_R[n]<36.5 && Pos_Rec_Y_R[n]>0 && Pos_Rec_Y_R[n]<36.3)
//									{
//										pThreadParam->xData[m]=Pos_Rec_X_R[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
//										pThreadParam->zData[m]=Pos_Rec_Y_R[n];					 
//										m++;
//									}
//
//								}
//								pThreadParam->DataNum=m;
//								m=0;///����һ��Ҫ����
//								//if (isInvalidOutline==1)
//								//{
//								//	//����״̬�õ��ֹͣ
//								//	if (!moveBefore_R)
//								//	{
//								//		if (1)//Pos_Rec_X_R[Pointnum_R-1]>=40  && Pos_Rec_X_R[Pointnum_R-1]<=70)
//								//		{
//								//			continueErrorCnt_R=0;
//								//			moveBefore_R=TRUE;
//								//			//bFlagPOrder_R=m_MachineCtrl_R.MotorMove(0,bFlagPOrder_R,m_Mscomm_R);
//								//			//bFlagPOrder_R=m_MachineCtrl_R.MotorMove(0,bFlagPOrder_R,m_Mscomm_R);
//								//			m_MachineCtrl_R.MotorStop(m_Mscomm_R);
//								//		}
//								//	}
//								//}
//								
//								break;
//							}
//						}
//						
//						//������Ϣ
//							
//
//						if (!g_StopDrawFlag_R&&DrawNum/3)
//						{
//							::SendMessage(pThreadParam->hWnd, WM_2DTHREADMSG_XML_R, 0, 0);
//							Sleep(5);
//							::SendMessage(pThreadParam->hWnd,WM_2DDISPLISTCTRL_R,1,0);//wParam==1,����ʾϳĥ����Ϣ
//						    Sleep(5);
//						}
//											 
//
//						OutLineSection_L.Lock();
//						//�洢����ϳĥ��ʱ��23��ʵ�⽻��ӹ���㣨���ƺ�
//						LoopBuff.LoopBuffWrite(&xHdmNodeLoopBuff_R,HdmNode_XR,nStNumNode+1);
//						LoopBuff.LoopBuffWrite(&zHdmNodeLoopBuff_R,HdmNode_YR,nStNumNode+1);
//						//�洢����ϳĥ��ʱ��23��ʵ���׼��ӹ���㣨����ǰ��
//						LoopBuff.LoopBuffWrite(&xScbzLoopBuff_R,XmlScbz_XR,nStNumNode+1);
//						LoopBuff.LoopBuffWrite(&zScbzLoopBuff_R,XmlScbz_YR,nStNumNode+1);
//						//�洢23������澫��
//						LoopBuff.LoopBuffWrite(&DistHdmJd_LoofBuff_R,Dist_Hdmjd_R,nStNumNode);
//						//�洢23��ϳĥ������
//						LoopBuff.LoopBuffWrite(&DistXmlJd_LoopBuff_R,Dist_Xmljd_R,nStNumNode);
//						OutLineSection_L.Unlock();
//						}
//					}
//					else if(isInvalidOutline==1)//��׼������������������ϳĥ��
//					{
//						switch(g_TestInfo_R.TrackSel)
//						{
//						case 0://50��
//							{
//								//shangyi = FuncCalculatingHdm(Hdm_50,bFlagWeiDuiQi,bFlagTrack_R,Pointnum_R,Pos_Rec_X_R,Pos_Rec_Y_R,Num_R400_Start);
//								////HdmScbz_XR_50[Num_Node_50]=Pos_Rec_X_R[Num_R400_Start-5];
//								////HdmScbz_YR_50[Num_Node_50]=Pos_Rec_Y_R[Num_R400_Start-5];//����δ����Ĺ����
//								//HdmScbz_XR_50[Num_Node]=36.8;
//								//HdmScbz_YR_50[Num_Node]=32.753;
//								//������
//								/*int m=0;
//								for (int n=0;n<Pointnum_R;n++)
//								{
//									if (Pos_Rec_X_R[n]>-26 && Pos_Rec_X_R[n]<36.5 && Pos_Rec_Y_R[n]>0 && Pos_Rec_Y_R[n]<36.3)
//									{
//										pThreadParam->xData[m]=Pos_Rec_X_R[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
//										pThreadParam->zData[m]=Pos_Rec_Y_R[n];					 
//										m++;
//									}
//								}
//								pThreadParam->DataNum=m;
//								m=0;///����һ��Ҫ����*/
//
//								shangyi = FuncCalculatingHdm(Hdm_50,bFlagDuiQi,bFlagTrack_R,Pointnum_R,Pos_Rec_X_R,Pos_Rec_Y_R,Num_R400_Start);
//								//HdmNode_XR_50[Num_Node_50]=Pos_Rec_X_R[Num_R400_Start-5];
//								//HdmNode_YR_50[Num_Node_50]=Pos_Rec_Y_R[Num_R400_Start-5];//�������Ĺ����
//								HdmNode_XR_50[Num_Node_50]=36.328;
//								HdmNode_YR_50[Num_Node_50]=32.753;
//								for (int i=0;i<Num_Node_50;i++)
//								{
//									HdmScbz_XR_50[i] = HdmNode_XR_50[i];
//									HdmScbz_YR_50[i] = HdmNode_YR_50[i];
//									pThreadParam->DistXml_50[i]=Dist_Xmljd_R_50[i];
//								}
//								HdmScbz_XR_50[Num_Node_50]=36.328+shangyi;
//								HdmScbz_YR_50[Num_Node_50]=32.753;
//								//////////////////////////////////////////////////////////////////////////
//								int m=0;
//								for (int n=0;n<Pointnum_R;n++)
//								{
//									if (Pos_Rec_X_R[n]>-26 && Pos_Rec_X_R[n]<36.5 && Pos_Rec_Y_R[n]>0 && Pos_Rec_Y_R[n]<36.3)
//									{
//										pThreadParam->xData[m]=Pos_Rec_X_R[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
//										pThreadParam->zData[m]=Pos_Rec_Y_R[n];					 
//										m++;
//									}
//								}
//								pThreadParam->DataNum=m;
//								m=0;///����һ��Ҫ����
//								for(int i=0;i<Num_Node_50;i++)////��׼��׼�����쳣�ǣ�ϳĥ����-1
//								{
//									Dist_Xmljd_R_50[i]=-1;
//								}
//								//if (isInvalidOutline==1)
//								//{
//								//	if (!moveBefore_R)
//								//	{
//								//		if (1)//Pos_Rec_X_R[Pointnum_R-1]>=40  && Pos_Rec_X_R[Pointnum_R-1]<=70)
//								//		{
//								//			continueErrorCnt_R=0;
//								//			moveBefore_R=TRUE;
//								//			//bFlagPOrder_R=m_MachineCtrl_R.MotorMove(0,bFlagPOrder_R,m_Mscomm_R);
//								//			//bFlagPOrder_R=m_MachineCtrl_R.MotorMove(0,bFlagPOrder_R,m_Mscomm_R);
//								//			m_MachineCtrl_R.MotorStop(m_Mscomm_R);
//								//		}
//								//	}
//								//}
//								//����״̬�õ��ֹͣ
//								
//								break;
//							}
//						case 1:
//							{
//								//shangyi = FuncCalculatingHdm(Hdm_60,bFlagWeiDuiQi,bFlagTrack_R,Pointnum_R,Pos_Rec_X_R,Pos_Rec_Y_R,Num_R400_Start);
//								////HdmScbz_XR[Num_Node]=Pos_Rec_X_R[Num_R400_Start-5];
//								////HdmScbz_YR[Num_Node]=Pos_Rec_Y_R[Num_R400_Start-5];//����δ����Ĺ����
//								//HdmScbz_XR[Num_Node]=36.8;
//								//HdmScbz_YR[Num_Node]=32.753;
//								////������
//								//int m=0;
//								//for (int n=0;n<Pointnum_R;n++)
//								//{
//								//	if (Pos_Rec_X_R[n]>-26 && Pos_Rec_X_R[n]<36.5 && Pos_Rec_Y_R[n]>0 && Pos_Rec_Y_R[n]<36.3)
//								//	{
//								//		pThreadParam->xData[m]=Pos_Rec_X_R[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
//								//		pThreadParam->zData[m]=Pos_Rec_Y_R[n];					 
//								//		m++;
//								//	}
//
//								//}
//								//pThreadParam->DataNum=m;
//								//m=0;///����һ��Ҫ����
//
//
//								shangyi = FuncCalculatingHdm(Hdm_60,bFlagDuiQi,bFlagTrack_R,Pointnum_R,Pos_Rec_X_R,Pos_Rec_Y_R,Num_R400_Start);
//								//HdmNode_XR[Num_Node]=Pos_Rec_X_R[Num_R400_Start-5];
//								//HdmNode_YR[Num_Node]=Pos_Rec_Y_R[Num_R400_Start-5];//�������Ĺ����
//								HdmNode_XR[Num_Node]=36.8;
//								HdmNode_YR[Num_Node]=32.753;
//								for (int i=0;i<Num_Node;i++)
//								{
//									HdmScbz_XR[i] = HdmNode_XR[i];
//									HdmScbz_YR[i] = HdmNode_YR[i];
//									pThreadParam->DistXml[i]=Dist_Xmljd_R[i];
//								}
//								HdmScbz_XR[Num_Node]=36.8+shangyi;
//								HdmScbz_YR[Num_Node]=32.753;
//								//////////////////////////////////////////////////////////////////////////
//								//������
//								int m=0;
//								for (int n=0;n<Pointnum_R;n++)
//								{
//									if (Pos_Rec_X_R[n]>-26 && Pos_Rec_X_R[n]<36.5 && Pos_Rec_Y_R[n]>0 && Pos_Rec_Y_R[n]<36.3)
//									{
//										pThreadParam->xData[m]=Pos_Rec_X_R[n];///���ݴ��ݹ�ͷ��������ֵ���л�ͼ
//										pThreadParam->zData[m]=Pos_Rec_Y_R[n];					 
//										m++;
//									}
//
//								}
//								pThreadParam->DataNum=m;
//								m=0;///����һ��Ҫ����
//
//
//								for(int i=0;i<Num_Node;i++)////��׼��׼�����쳣�ǣ�ϳĥ����-1
//								{
//									Dist_Xmljd_R[i]=-1;
//								
//								//if (isInvalidOutline==1)
//								//{
//								//	//����״̬�õ��ֹͣ
//								//	if (!moveBefore_R)
//								//	{
//								//		if (1)//Pos_Rec_X_R[Pointnum_R-1]>=40  && Pos_Rec_X_R[Pointnum_R-1]<=70)
//								//		{
//								//			continueErrorCnt_R=0;
//								//			moveBefore_R=TRUE;
//								//			//bFlagPOrder_R=m_MachineCtrl_R.MotorMove(0,bFlagPOrder_R,m_Mscomm_R);
//								//			//bFlagPOrder_R=m_MachineCtrl_R.MotorMove(0,bFlagPOrder_R,m_Mscomm_R);
//								//			m_MachineCtrl_R.MotorStop(m_Mscomm_R);
//								//		}
//								//	}
//								//}
//								
//								break;
//							}
//						}
//						
//						//������Ϣ
//							
//						if (!g_StopDrawFlag_R&&DrawNum/3)
//						{
//							::SendMessage(pThreadParam->hWnd, WM_2DTHREADMSG_XML_R, 0, 0);
//							Sleep(5);
//							::SendMessage(pThreadParam->hWnd,WM_2DDISPLISTCTRL_R,1,0);//wParam==1,����ʾϳĥ����Ϣ
//							Sleep(5);
//						}				
//						
//						OutLineSection_L.Lock();
//						//�洢����ϳĥ��ʱ��23��ʵ�⽻��ӹ���㣨���ƺ�
//						LoopBuff.LoopBuffWrite(&xHdmNodeLoopBuff_R,HdmNode_XR,nStNumNode+1);
//						LoopBuff.LoopBuffWrite(&zHdmNodeLoopBuff_R,HdmNode_YR,nStNumNode+1);
//						//�洢����ϳĥ��ʱ��23��ʵ���׼��ӹ���㣨����ǰ��
//						LoopBuff.LoopBuffWrite(&xScbzLoopBuff_R,XmlScbz_XR,nStNumNode+1);
//						LoopBuff.LoopBuffWrite(&zScbzLoopBuff_R,XmlScbz_YR,nStNumNode+1);
//						//�洢23������澫��
//						LoopBuff.LoopBuffWrite(&DistHdmJd_LoofBuff_R,Dist_Hdmjd_R,nStNumNode);
//						//�洢23��ϳĥ������
//						LoopBuff.LoopBuffWrite(&DistXmlJd_LoopBuff_R,Dist_Xmljd_R,nStNumNode);
//						OutLineSection_L.Unlock();
//					}
//
//					
//				}
//
//			}
//			//else//�쳣����
//			if(isInvalidOutline!=1)
//			{
//				
//				
//				//++continueErrorCnt_R;//�쳣�����ĸ���
//
//				////if (moveBefore_R && isInvalidOutline==-2  &&continueErrorCnt_R>=10)//isInvalidOutLine =-2��ʾR400����Ҳ���
//				//if (continueErrorCnt_R>=10)
//				//{		
//				//	
//				//    if(moveBefore_R)//�������쳣
//				//	{
//				//		if (Pos_Rec_X_R[Pointnum_R-1]<nMtStopDist)
//				//		{
//				//			bFlagPOrder_R=m_MachineCtrl_R.MotorMove(-MotorMoveLmt,bFlagPOrder_R,m_Mscomm_R);
//				//			moveBefore_R=FALSE; 
//				//			continueErrorCnt_R=0;
//				//		}
//				//		else
//				//		{
//				//			moveBefore_R=FALSE; 
//				//			bFlagPOrder_R=m_MachineCtrl_R.MotorMove(MotorMoveLmt,bFlagPOrder_R,m_Mscomm_R);
//				//			continueErrorCnt_R=0;
//				//		}	
//				//	}
//				//	else //�쳣���쳣
//				//	{
//				//		/*if (isInvalidOutline==-3)
//				//		{
//				//			moveBefore_R=FALSE;
//				//			continueErrorCnt_R=0;
//				//			bFlagPOrder_R = m_MachineCtrl_R.MotorMove(MotorMoveLmt,bFlagPOrder_R,m_Mscomm_R);
//				//		}*/
//				//		int nResLimit=0;
//				//		nResLimit=m_MachineCtrl_R.IsMotorLimit(m_Mscomm_R);
//				//		if (nResLimit)//�ڼ���
//				//		{
//				//			if (nResLimit>0)//������
//				//			{
//				//				bFlagPOrder_R=m_MachineCtrl_R.MotorMove(-MotorMoveLmt,bFlagPOrder_R,m_Mscomm_R);								
//				//				continueErrorCnt_R=0;
//				//			}
//				//			if (nResLimit<0)
//				//			{
//				//				bFlagPOrder_R=m_MachineCtrl_R.MotorMove(MotorMoveLmt,bFlagPOrder_R,m_Mscomm_R);								 
//				//				continueErrorCnt_R=0;
//				//			}
//				//		}
//				//	}
//				//	continueErrorCnt_R=0;
//				//}
//
//				if (Readpointnum!=0)
//				{
//					memset(HdmNode_XR,0,(nStNumNode+1)*sizeof(double));
//					memset(HdmNode_YR,0,(nStNumNode+1)*sizeof(double));
//
//					memset(HdmScbz_XR,0,(nStNumNode+1)*sizeof(double));
//					memset(HdmScbz_YR,0,(nStNumNode+1)*sizeof(double));
//					memset(Dist_Hdmjd_R,0,nStNumNode*sizeof(double));
//					memset(Dist_Xmljd_R,0,nStNumNode*sizeof(double));
//
//					OutLineSection_R.Lock();
//					//�洢����ϳĥ��ʱ��23��ʵ�⽻��ӹ���㣨���ƺ�
//					LoopBuff.LoopBuffWrite(&xHdmNodeLoopBuff_R,HdmNode_XR,nStNumNode+1);
//					LoopBuff.LoopBuffWrite(&zHdmNodeLoopBuff_R,HdmNode_YR,nStNumNode+1);
//					//�洢����ϳĥ��ʱ��23��ʵ���׼��ӹ���㣨����ǰ��
//					LoopBuff.LoopBuffWrite(&xScbzLoopBuff_R,HdmScbz_XR,nStNumNode+1);
//					LoopBuff.LoopBuffWrite(&zScbzLoopBuff_R,HdmScbz_YR,nStNumNode+1);
//					//�洢23������澫��
//					LoopBuff.LoopBuffWrite(&DistHdmJd_LoofBuff_R,Dist_Hdmjd_R,nStNumNode);
//					//�洢23��ϳĥ��
//					if(1==g_TestInfo_R.XM_QianHou)//ϳĥ��
//					{
//						//LoopBuff.LoopBuffWrite(&DistXmlJd_LoopBuff_L,Dist_Xmljd_L,nStNumNode);
//						LoopBuff.LoopBuffWrite(&DistXmlJd_LoopBuff_L,Dist_Xmljd_R,nStNumNode);
//
//					}
//					OutLineSection_R.Unlock(); 
//				}
//			}
//		
//		}
//		else
//			Sleep(20);
//		GetDataSection_R.Lock();
//		iGetDataOutLineCnt=LoopBuff.LoopBuffDataLength(&GetDataNum_LoopBuff_R);
//		GetDataSection_R.Unlock();
//		if(iGetDataOutLineCnt>5)
//			DrawNum++;
//		else
//			DrawNum=3;
//		if(DrawNum>3)
//			DrawNum=0;
//	
//
//	}
//	if(bFlagQiangzhiStart)//�������if��Ϊ˳������������㼴Ϊ�쳣��׼�ļ����½���
//	{
//		bEndDealingFlag_R=true;
//	}
//	
	return 0;
//
}

//int Preproccess(PreprocessINfO &PreINFO, TrackSelAndMHStruct &TrackSel)
//{
//	OutLineArithmetic CalculateOutline;//���㷽������
//									   //======��ȥ��ԭʼ�����е��쳣��
//	PreINFO.In_Num = CalculateOutline.delErrorPoints(PreINFO.pInDataX, PreINFO.pInDataY, PreINFO.In_Num);
//
//	int    Num_Smooth_Y_Max = 0;
//	double DealDataX[SensorMaxPoint];
//	double DealDataY[SensorMaxPoint];
//	PreINFO.Out_Num = 0;
//	int Count_R20 = 0, Count_R400 = 0;
//	int YuanXinDis = 0;
//	int Num_R20_Start = 0, Num_R20_End = 0;
//	PreINFO.Num_R400Start = 0;//ȫ�ֱ����������һ��Ҫ����
//							  /////�ָ��߶�����
//	int* DJArray = NULL;
//	double* xDataIndex = NULL;
//	double* yDataIndex = NULL;
//	double* SlopeArray = NULL;
//	double* XDJArray = NULL;
//
//	int indexarray[500] = { 0 };
//
//
//	/////�쳣�߶�����
//	int* OutIndexArray = NULL;
//	int* OutInitIndexArray = NULL;
//	double* OutxDataIndex = NULL;
//	double* OutyDataIndex = NULL;
//	double* OutSlopeArray = NULL;
//
//	int OutIndexNum = 0;
//	/////LS400��λ��
//	int Ls400Index = 0;
//	int Ls400InitIndex = 0;
//	int LS400ArrayPos = 0;
//	////ȥ���쳣��������ʼ��
//	int DeleteIndex1 = 0;
//	int DeleteIndex2 = 0;
//	//int MaxIndexY;
//	//����˶���������
//	double Motor_MovingDist = 0;	//������о���
//	double Motor_MovingRound = 0; //���ת��Ȧ��
//
//	int IsNormalSketch = -8;//Ԥ����������ֵ
//
//							//���R400���֮��ı���
//	int Index_Hor = 0;
//	int Index_Ver = 0;
//
//	double Center_R20_Fitting_X = 0, Center_R20_Fitting_Y = 0, Center_R400_Fitting_X = 0, Center_R400_Fitting_Y = 0,
//		Fun_A = 0, Fun_B = 0, Fun_D = 0, Fun_theta1[2] = { 0 }, Fun_theta2[2] = { 0 };
//
//	double Pos_R20_X[700] = { 0 }, Pos_R20_Y[700] = { 0 }, Center_R20_Fitting[2] = { 0 }, Pos_R400_X[700] = { 0 },
//		Pos_R400_Y[700] = { 0 }, Center_R400_Fitting[2] = { 0 };
//
//	double Fun_theta = 0, Fun_a = 0, Fun_b = 0, Pos_Rec_Ver_Y = 0, Pos_Rec_Hor_X = 0;
//	//------��Ԥ�����������------//
//	int NormalR20_X, NormalR20_Y;
//	double Dist_Center = 0;
//	int NormalR400_X, NormalR400_Y;
//	double Wear_Ver = 0, Wear_Hor = 0, Wear = 0;
//
//	double *Pos_Deal_X = new double[700];
//	double *Pos_Deal_Y = new double[700];
//
//	/*double *Pos_Deal_X, *Pos_Deal_Y;
//	Pos_Deal_X = (double *)malloc(PreINFO.In_Num * sizeof(double));
//	Pos_Deal_Y = (double *)malloc(PreINFO.In_Num * sizeof(double));*/
//	//CalculateOutline.smooth_9(PreINFO.pInDataX, PreINFO.In_Num, 9, Pos_Deal_X);
//	//CalculateOutline.smooth_9(PreINFO.pInDataY, PreINFO.In_Num, 9, Pos_Deal_Y);
//	//=======
//	for (int i = 0; i<PreINFO.In_Num; i++)
//	{
//		Pos_Deal_X[i] = PreINFO.pInDataX[i];
//		Pos_Deal_Y[i] = PreINFO.pInDataY[i];
//
//	}
//	//��ԭʼ���ݽ�����ֵ�˲�����
//	//CalculateOutline.smooth_20(PreINFO.pInDataX,PreINFO.In_Num,19,Pos_Deal_X);
//	//CalculateOutline.smooth_20(PreINFO.pInDataY,PreINFO.In_Num,19,Pos_Deal_Y);//��ԭʼ���ݽ�����ֵ�˲�����
//	//CalculateOutline.smooth_ave(PreINFO.pInDataX, PreINFO.pInDataY, PreINFO.In_Num, Pos_Deal_X, Pos_Deal_Y);
//	int i = 0, j = 0, LineNum = 0;
//	PreINFO.RamerIndexNum = 0;
//	RamerFunc(Pos_Deal_X, Pos_Deal_Y, 0, PreINFO.In_Num - 1, PreINFO.RamerIndexArray, PreINFO.RamerIndexNum);//�������αƽ����߶�
//																											 //====
//
//	if (PreINFO.RamerIndexNum>300)
//	{
//		IsNormalSketch = -1;
//		return IsNormalSketch;//����αƽ�����ֻҪ����300��ֱ���쳣
//	}
//	for (i = 0; i<PreINFO.RamerIndexNum; i++)
//	{
//		indexarray[i] = PreINFO.RamerIndexArray[i];
//	}
//	LineNum = CalculateOutline.RemoveRep(indexarray, PreINFO.RamerIndexNum);//���õ����߶α�Ž���ȥ������LineNumΪ�߶ε�����,indexarrayΪ�������зָ�ı��
//	PreINFO.RamerIndexNum = 0;//����洢�߶α��
//
//	DJArray = new int[LineNum];/////��̬��������
//	SlopeArray = new double[LineNum];
//	xDataIndex = new double[LineNum];
//	yDataIndex = new double[LineNum];
//	XDJArray = new double[LineNum];
//
//	OutSlopeArray = new double[LineNum];
//	OutIndexArray = new int[LineNum];
//	OutInitIndexArray = new int[LineNum];
//	OutxDataIndex = new double[LineNum];
//	OutyDataIndex = new double[LineNum];
//
//	/////�õ�ÿ���߶ε�б�ʡ���ž��롢�߶γ���
//	for (j = 0; j<LineNum; j++)
//	{
//		xDataIndex[j] = Pos_Deal_X[indexarray[j]];
//		yDataIndex[j] = Pos_Deal_Y[indexarray[j]];//xDataIndex,yDataIndexΪ�ָ��ŵ������
//
//		if (j>0)//��֤�ָ��ŵ���������������㣬������ŵ�ȷ��һ��ֱ��
//		{
//			SlopeArray[j - 1] = (yDataIndex[j] - yDataIndex[j - 1]) / (xDataIndex[j] - xDataIndex[j - 1]);///SlopeArray[]��ʾ�ָ��߶ε�б��
//			DJArray[j - 1] = indexarray[j] - indexarray[j - 1];//DJArray��ʾ�ָ���֮��ĵ��
//			XDJArray[j - 1] = sqrt((xDataIndex[j] - xDataIndex[j - 1])*(xDataIndex[j] - xDataIndex[j - 1]) +
//				(yDataIndex[j] - yDataIndex[j - 1])*(yDataIndex[j] - yDataIndex[j - 1]));    //XDJArray[]���߶εľ���ֵ
//		}
//
//	}
//	//�ҵ����е��쳣�߶Σ����Ҽ����
//
//	for (i = 0; i<LineNum; i++)
//	{
//
//		if (fabs(SlopeArray[i])>3 || (DJArray[i]<5 && XDJArray[i]>5))//�ҳ�б�ʴ���3������������������֮��������5���߶α�ź�ԭʼλ��
//		{
//			OutSlopeArray[OutIndexNum] = SlopeArray[i];///�쳣�߶ε�б��
//			OutIndexArray[OutIndexNum] = i;//OutIndexArray[]��ʾ�쳣�߶α��
//			OutInitIndexArray[OutIndexNum] = indexarray[i];//OutInitIndexArray[]��ʾ�쳣���߶ε�ԭʼ���
//			OutxDataIndex[OutIndexNum] = xDataIndex[i];//�쳣��ŵ������
//			OutyDataIndex[OutIndexNum] = yDataIndex[i];
//			OutIndexNum++;////OutIndexNum��ʾ�쳣�εĸ���
//		}
//
//	}
//	/////�ҵ�R400�����
//	for (j = 0; j <= OutIndexNum; j++)
//	{
//		if (OutInitIndexArray[j]>1)
//		{
//			int num1;
//			int num2;
//			num1 = indexarray[OutIndexArray[j]] - indexarray[OutIndexArray[j] - 1];
//			num2 = indexarray[OutIndexArray[j] + 2] - indexarray[OutIndexArray[j] + 1];
//			if (SlopeArray[OutIndexArray[j] - 1] >= 0 && SlopeArray[OutIndexArray[j] + 1] >= 0/* && num1 >= 5 && num2 >= 5*/
//				&& abs(yDataIndex[OutIndexArray[j] + 1] - OutyDataIndex[j])>20 && abs(yDataIndex[OutIndexArray[j] + 1] - OutyDataIndex[j])<60)
//			{
//				Ls400Index = OutIndexArray[j]; //�ҵ�LS400���ڷָ���е�λ��
//				Ls400InitIndex = indexarray[OutIndexArray[j] + 1];//�ҵ�LS400��ԭʼ�����е�λ��
//				LS400ArrayPos = j;///LS400���쳣�߶������е�λ��
//				break;
//			}
//		}
//	}
//	//======�����ͷ�����߶���̫�࣬˵����ͷ�쳣
//	if (Ls400Index>25)
//	{
//		IsNormalSketch = -10;
//		//return IsNormalSketch;
//	}
//
//	else if (Ls400InitIndex == 0)///Ls400�����ھ�ֱ����Ϊ�쳣
//	{
//		IsNormalSketch = -2;
//	}
//	else if (Ls400InitIndex>0)//��ʾLS400����
//	{
//
//		/////�ҵ�������LS400�߶�֮ǰ,�����Ǿ���LS400���5���߶ε��쳣�Σ����
//		//for(i=LS400ArrayPos-1;i>=0;i--)
//		//{
//		//	if(Ls400Index-OutIndexArray[i]>5)
//		//	{
//		//		DeleteIndex1 = indexarray[OutIndexArray[i]+1];/////�ҵ�ǰ��ɾ�����յ�
//		//		break;
//		//	}
//		//}
//		DeleteIndex1 = 0;
//		/////�ҵ�������LS400�߶�֮����쳣�Σ����
//		//for (i = LS400ArrayPos + 1; i <= OutIndexNum; i++)
//		//{
//		//	if (OutIndexArray[i] - Ls400Index>5)
//		//	{
//		//		DeleteIndex2 = indexarray[OutIndexArray[i]];////�ҵ����ɾ�������
//		//		break;
//		//	}
//		//	else
//		//		DeleteIndex2 = PreINFO.In_Num - 1;
//		//}
//		DeleteIndex2 = PreINFO.In_Num - 1;
//		for (i = DeleteIndex1; i <= DeleteIndex2; i++)
//		{
//			DealDataX[PreINFO.Out_Num] = Pos_Deal_X[i];
//			DealDataY[PreINFO.Out_Num] = Pos_Deal_Y[i];
//			PreINFO.Out_Num++;
//		}
//		Ls400InitIndex = Ls400InitIndex - DeleteIndex1;///����R400�Ľ��
//
//
//													   /*******ɾ����̬����������********/
//		if (DJArray)
//		{
//			delete[] DJArray;
//			DJArray = NULL;
//		}
//		if (SlopeArray)
//		{
//			delete[] SlopeArray;
//			SlopeArray = NULL;
//		}
//		if (XDJArray)
//		{
//			delete[] XDJArray;
//			XDJArray = NULL;
//
//		}
//		if (xDataIndex)
//		{
//			delete[] xDataIndex;
//			xDataIndex = NULL;
//		}
//		if (yDataIndex)
//		{
//			delete[] yDataIndex;
//			yDataIndex = NULL;
//		}
//		if (OutIndexArray)
//		{
//			delete[] OutIndexArray;
//			OutIndexArray = NULL;
//		}
//		if (OutInitIndexArray)
//		{
//			delete[] OutInitIndexArray;
//			OutInitIndexArray = NULL;
//		}
//		if (OutSlopeArray)
//		{
//			delete[] OutSlopeArray;
//			OutSlopeArray = NULL;
//		}
//		if (OutxDataIndex)
//		{
//			delete[] OutxDataIndex;
//			OutxDataIndex = NULL;
//		}
//		if (OutyDataIndex)
//		{
//			delete[] OutyDataIndex;
//			OutyDataIndex = NULL;
//		}
//
//
//		//------�¼����Ԥ����------//
//		//����R400���
//		PreINFO.Num_R400Start = Ls400InitIndex;
//		//===���յ�����
//		int endPointIdx = PreINFO.Out_Num;
//		if ((PreINFO.pInDataX[PreINFO.Out_Num - 1] - PreINFO.pInDataX[PreINFO.Num_R400Start]) > 70)
//		{
//			for (int i = PreINFO.Num_R400Start; i < PreINFO.Out_Num; i++)
//			{
//				if (PreINFO.pInDataX[i] - PreINFO.pInDataX[PreINFO.Num_R400Start] >= 70)
//				{
//					endPointIdx = i;
//					break;
//				}
//			}
//		}
//
//		//��R20Բ��
//		double DealDataY_Temp[SensorMaxPoint] = { 0 };
//		int index_temp = 0;
//		//for (int index_max = PreINFO.Num_R400Start; index_max<PreINFO.Out_Num - 1; index_max++)
//		for (int index_max = PreINFO.Num_R400Start; index_max < endPointIdx; index_max++)
//		{
//			DealDataY_Temp[index_temp] = DealDataY[index_max];
//			index_temp++;
//		}
//		double DealMax = CalculateOutline.Pos_Max(DealDataY_Temp, PreINFO.Out_Num - PreINFO.Num_R400Start + 1);
//		//for (int i = PreINFO.Num_R400Start; i<PreINFO.Out_Num; i++)
//
//		//for (int i = PreINFO.Num_R400Start; i < PreINFO.Out_Num; i++)
//		for (int i = PreINFO.Num_R400Start; i < endPointIdx; i++)
//		{
//			if (DealDataY[i] == DealMax)
//				Num_Smooth_Y_Max = i;
//		}
//		//�ж�R20�Ƿ񸲸ǲ���
//
//
//		if (Num_Smooth_Y_Max + 20 <= PreINFO.Out_Num)
//		{
//			double Dis_2;
//			double Dis_tmp = 0;
//			//=====
//			for (i = Num_Smooth_Y_Max - 20; i < Num_Smooth_Y_Max + 20; i++)
//			{
//				Dis_2 = sqrt((DealDataY[i + 1] - DealDataY[i])*(DealDataY[i + 1] - DealDataY[i]) + (DealDataX[i + 1] - DealDataX[i])*(DealDataX[i + 1] - DealDataX[i]));
//				if (Dis_2 > Dis_tmp)
//				{
//					Dis_tmp = Dis_2;
//				}
//			}
//			if (Dis_tmp>3)
//			{
//				IsNormalSketch = -3;
//			}
//
//			else
//			{
//				for (int i = Num_Smooth_Y_Max - (TrackSel.Num_Pos_R20 - 1) / 2; i<Num_Smooth_Y_Max + (TrackSel.Num_Pos_R20 - 1) / 2 + 1; i++)
//				{
//					Pos_R20_X[Count_R20] = DealDataX[i];
//					Pos_R20_Y[Count_R20] = DealDataY[i];
//					Count_R20++;
//				}
//				CalculateOutline.FittingCircle(Pos_R20_X, Pos_R20_Y, Count_R20, PreINFO.FittingRadius_R20, Center_R20_Fitting);
//				Center_R20_Fitting_X = Center_R20_Fitting[0];
//				Center_R20_Fitting_Y = Center_R20_Fitting[1];
//
//
//
//				//��R20���еڶ������
//				for (int i = Num_Smooth_Y_Max + (TrackSel.Num_Pos_R20 - 1) / 2 + 1; i<PreINFO.Out_Num; i++)
//				{
//
//					if ((sqrt((DealDataX[i] - Center_R20_Fitting_X)*(DealDataX[i] - Center_R20_Fitting_X) + (DealDataY[i] - Center_R20_Fitting_Y)*(DealDataY[i] - Center_R20_Fitting_Y)) - 20)>0.01)
//					{
//						Num_R20_End = i;
//						break;
//					}
//					Num_R20_End = i;
//
//				}
//				for (int i = Num_Smooth_Y_Max - (TrackSel.Num_Pos_R20 - 1) / 2 - 1; i >= PreINFO.Num_R400Start; i--)
//				{
//					if ((sqrt((DealDataX[i] - Center_R20_Fitting_X)*(DealDataX[i] - Center_R20_Fitting_X) + (DealDataY[i] - Center_R20_Fitting_Y)*(DealDataY[i] - Center_R20_Fitting_Y)) - 20)>0.01)
//					{
//						Num_R20_Start = i;
//						break;
//					}
//					Num_R20_Start = i;
//				}
//
//				//�ֱ����R20�������յ��ٴν������
//				Count_R20 = 0;
//				for (int i = Num_R20_Start; i <= Num_R20_End; i++)
//				{
//					Pos_R20_X[Count_R20] = DealDataX[i];
//					Pos_R20_Y[Count_R20] = DealDataY[i];
//					Count_R20++;
//				}
//				CalculateOutline.FittingCircle(Pos_R20_X, Pos_R20_Y, Count_R20, PreINFO.FittingRadius_R20, Center_R20_Fitting);
//				Center_R20_Fitting_X = Center_R20_Fitting[0];
//				Center_R20_Fitting_Y = Center_R20_Fitting[1];
//				//�ж�Բ�ĵ�����ֵ�Ƿ�ΪNAN����NormalR20_X������Y��=0��˵��Բ��������
//				//ֻҪx��y��һ��Ϊ��0����Բ�ľ�������
//				///int NormalR20_X,NormalR20_Y;
//				NormalR20_X = _isnan(Center_R20_Fitting_X);
//				NormalR20_Y = _isnan(Center_R20_Fitting_Y);
//
//				//�ж�RS20Բ���Ƿ������������������ֱ�ӷ���IsNormalFileΪfalse
//				if (NormalR20_X == 0 && NormalR20_Y == 0)
//				{
//					//��R400Բ��
//					Count_R400 = 0;
//					for (int i = PreINFO.Num_R400Start; i <= Num_R20_Start; i++)
//					{
//						Pos_R400_X[Count_R400] = DealDataX[i];
//						Pos_R400_Y[Count_R400] = DealDataY[i];
//						Count_R400++;
//					}
//					CalculateOutline.FittingCircle(Pos_R400_X, Pos_R400_Y, Count_R400, PreINFO.FittingRadius_R400, Center_R400_Fitting);
//					Center_R400_Fitting_X = Center_R400_Fitting[0];
//					Center_R400_Fitting_Y = Center_R400_Fitting[1];
//
//
//
//					//�ж�Բ�ĵ�����ֵ�Ƿ�ΪNAN����NormalR400_X������Y��=0��˵��Բ��������
//					//ֻҪx��y��һ��Ϊ��0����Բ�ľ�������
//
//					NormalR400_X = _isnan(Center_R400_Fitting_X);
//					NormalR400_Y = _isnan(Center_R400_Fitting_Y);
//					//�ж�R400Բ���Ƿ������������������ֱ�ӷ���IsNormalFileΪfalse
//					if (NormalR400_X == 0 && NormalR400_Y == 0)
//					{
//						//�����Ϻ��R400��R20��Բ�ľ���
//						Dist_Center = sqrt((Center_R20_Fitting_X - Center_R400_Fitting_X)*(Center_R20_Fitting_X - Center_R400_Fitting_X) + (Center_R20_Fitting_Y - Center_R400_Fitting_Y)*(Center_R20_Fitting_Y - Center_R400_Fitting_Y));
//						switch (PreINFO.FittingRadius_R400)
//						{
//						case 350:
//							YuanXinDis = 330;
//							break;
//						case 400:
//							YuanXinDis = 380;
//							break;
//						case 500:
//							YuanXinDis = 425;
//							break;
//						}
//
//						if (abs(Dist_Center - YuanXinDis) <= 5)
//						{
//							//Բ�ľ�ϱ�׼���5������Ϊ�쳣
//							//ԭʼ����׼Բ�Ĵ�����תƽ�Ʒ�����ȡ����
//							//Fun_A=Center_R400_Fitting_X-Center_R20_Fitting_X;
//							//Fun_B=Center_R400_Fitting_Y-Center_R20_Fitting_Y;
//							//Fun_D=TrackSel.Pos_BZ_R400_X-TrackSel.Pos_BZ_R20_X;
//							//Fun_theta1[0]=(-2)*atan((Fun_B+sqrt(Fun_A*Fun_A+Fun_B*Fun_B-Fun_D*Fun_D))/(Fun_A+Fun_D));
//							//Fun_theta1[1]=(-2)*atan((Fun_B-sqrt(Fun_A*Fun_A+Fun_B*Fun_B-Fun_D*Fun_D))/(Fun_A+Fun_D));
//
//							//Fun_A=Center_R400_Fitting_Y-Center_R20_Fitting_Y;
//							//Fun_B=Center_R400_Fitting_X-Center_R20_Fitting_X;
//							//Fun_D=TrackSel.Pos_BZ_R400_Y-TrackSel.Pos_BZ_R20_Y;
//							//Fun_theta2[0]=2*atan((Fun_B+sqrt(Fun_A*Fun_A+Fun_B*Fun_B-Fun_D*Fun_D))/(Fun_A+Fun_D));
//							//Fun_theta2[1]=2*atan((Fun_B-sqrt(Fun_A*Fun_A+Fun_B*Fun_B-Fun_D*Fun_D))/(Fun_A+Fun_D));
//
//							//Fun_theta=0;
//							////�����theta
//							//for(int i=0;i<2;i++)
//							//{
//							//	for(int j=0;j<2;j++)
//							//	{
//							//		if(abs(Fun_theta1[i]-Fun_theta2[j])<=0.1)
//							//		{
//							//			Fun_theta=0.5f*(Fun_theta1[i]+Fun_theta2[j]);
//							//			break;
//							//		}
//							//	}
//							//}
//							////�ж���ת�Ƕ��Ƿ�����
//							//if (Fun_theta!=0)
//							//{
//							Fun_theta = atan((TrackSel.Pos_BZ_R400_Y - TrackSel.Pos_BZ_R20_Y) / (TrackSel.Pos_BZ_R400_X - TrackSel.Pos_BZ_R20_X)) -
//								atan((Center_R400_Fitting_Y - Center_R20_Fitting_Y) / (Center_R400_Fitting_X - Center_R20_Fitting_X));
//							//�����a,b
//							//Fun_a=TrackSel.Pos_BZ_R20_X-Center_R20_Fitting_X*cos(Fun_theta)+Center_R20_Fitting_Y*sin(Fun_theta);
//							//Fun_b=TrackSel.Pos_BZ_R20_Y-Center_R20_Fitting_Y*cos(Fun_theta)-Center_R20_Fitting_X*sin(Fun_theta);
//							Fun_a = TrackSel.Pos_BZ_R400_X - (Center_R400_Fitting_X*cos(Fun_theta) - Center_R400_Fitting_Y*sin(Fun_theta));
//							Fun_b = TrackSel.Pos_BZ_R400_Y - (Center_R400_Fitting_X*sin(Fun_theta) + Center_R400_Fitting_Y*cos(Fun_theta));
//
//							//����ƽ����ת����
//							for (int i = 0; i<PreINFO.Out_Num; i++)
//							{
//								PreINFO.pOutDataX[i] = DealDataX[i] * cos(Fun_theta) - DealDataY[i] * sin(Fun_theta) + Fun_a;
//								PreINFO.pOutDataY[i] = DealDataY[i] * cos(Fun_theta) + DealDataX[i] * sin(Fun_theta) + Fun_b;
//							}
//							//=======12-23,��ӹ�ͷƽ������
//							CalculateOutline.HeadSmooth(PreINFO.pOutDataX, PreINFO.pOutDataY, PreINFO.Out_Num, PreINFO.Num_R400Start);
//							//=========12-14������쳣�����ж������������ͷȱʧ̫���أ��ж�Ϊ�쳣����
//							for (int i = 1; i < PreINFO.Num_R400Start - 1; i++)
//							{
//								double neiborDist = (PreINFO.pOutDataX[i] - PreINFO.pOutDataX[i - 1])*(PreINFO.pOutDataX[i] - PreINFO.pOutDataX[i - 1]) +
//									(PreINFO.pOutDataY[i] - PreINFO.pOutDataY[i - 1])*(PreINFO.pOutDataY[i] - PreINFO.pOutDataY[i - 1]);
//								if (neiborDist > 16 * 16)//Ϊ�˼�С���������������������16����Ϊ���쳣����
//								{
//									IsNormalSketch = -10;
//									return IsNormalSketch;
//								}
//							}
//							//=====ֻӰ�컭ͼ
//							double tmpdatax[700];
//							double tmpdatay[700];
//							int tmpPointNums = 0;
//							double leftPos = 0;//������λ��
//							for (int i = 0; i<PreINFO.Out_Num; i++)
//							{
//								if (PreINFO.pOutDataX[i] >= -40)
//								{
//									tmpdatax[tmpPointNums] = PreINFO.pOutDataX[i];
//									tmpdatay[tmpPointNums] = PreINFO.pOutDataY[i];
//									tmpPointNums++;
//								}
//								if (PreINFO.pOutDataX[i]<leftPos)
//								{
//									leftPos = PreINFO.pOutDataX[i];
//								}
//							}
//							if (leftPos >= 0)
//							{
//								IsNormalSketch = -11;
//								return IsNormalSketch;
//							}
//
//							for (int i = 0; i<tmpPointNums; i++)
//							{
//								PreINFO.pOutDataX[i] = tmpdatax[i];
//								PreINFO.pOutDataY[i] = tmpdatay[i];
//							}
//							PreINFO.Out_Num = tmpPointNums;
//
//							//==========
//							//=============���ǲ�����������в���
//							//=============�Զ˵㸲�ǲ�����������в���
//							//const int Num_Node = 23;
//							const double tmp_Pos_BZ_X_60[Num_Node + 1] = { -30.835,-25.35,-21.2609,-18.162,-15.4047,-13.0575,-10,-5.0008,0,5.0008,10,13.0575,15.4047,
//								18.162,21.26,25.35,26.85,28.921,30.83,32.4404,33.7,34.6389,35.24,35.4 };
//							const double tmp_Pos_BZ_Y_60[Num_Node + 1] = { 4.958,2.2,1.3695,0.8793,0.5601,0.3585,0.2,0.0583,0,0.0583,0.2,0.3585,0.5601,0.8793,1.37,
//								2.2,2.65,3.6088,4.96,6.5864,8.4,10.4347,12.7,14.2 };
//
//							int zeroIdx = 0;
//							for (int i = 0; i < PreINFO.Out_Num; i++)
//							{
//								if (PreINFO.pOutDataX[i] < 0 && PreINFO.pOutDataX[i + 1] > 0)
//								{
//									zeroIdx = i;
//									break;
//								}
//							}
//							double gap = 0.5*(PreINFO.pOutDataY[zeroIdx] + PreINFO.pOutDataY[zeroIdx + 1]);
//							//====ȥ�����ӵ�	
//							tmpPointNums = 0;
//							for (int i = 0; i < PreINFO.Out_Num; i++)
//							{
//								if ((PreINFO.pOutDataY[i] - gap) > -3)
//								{
//									tmpdatax[tmpPointNums] = PreINFO.pOutDataX[i];
//									tmpdatay[tmpPointNums] = PreINFO.pOutDataY[i];
//									tmpPointNums++;
//								}
//							}
//							for (int i = 0; i < tmpPointNums; i++)
//							{
//								PreINFO.pOutDataX[i] = tmpdatax[i];
//								PreINFO.pOutDataY[i] = tmpdatay[i];
//							}
//							PreINFO.Out_Num = tmpPointNums;
//
//
//
//							if (PreINFO.pOutDataX[0] > tmp_Pos_BZ_X_60[0])
//							{
//
//								int missNum = 0;
//								for (int i = 0; i < Num_Node; i++)
//								{
//									if (PreINFO.pOutDataX[0] > tmp_Pos_BZ_X_60[i])
//									{
//										missNum++;
//									}
//								}
//								if (missNum > 7)
//								{
//									IsNormalSketch = -8;
//									return IsNormalSketch;
//								}
//								else
//								{
//									for (int i = PreINFO.Out_Num + missNum - 1; i >= missNum; i--)
//									{
//										PreINFO.pOutDataX[i] = PreINFO.pOutDataX[i - missNum];
//										PreINFO.pOutDataY[i] = PreINFO.pOutDataY[i - missNum];
//									}
//									for (int i = 0; i < missNum; i++)
//									{
//										PreINFO.pOutDataX[i] = tmp_Pos_BZ_X_60[i];
//										PreINFO.pOutDataY[i] = tmp_Pos_BZ_Y_60[i] + gap;
//									}
//								}
//
//							}
//							//=========��R13Բ�����в���
//							int Rs = zeroIdx;
//							int Re = PreINFO.Num_R400Start;
//							int RerrStart = 0;
//							int RerrEnd = 0;
//							double Rcentx = 22.417;
//							double Rcenty = 14.8642 + gap;
//							double R13 = 30;
//							for (int i = zeroIdx; i<PreINFO.Num_R400Start; i++)
//							{
//								if (PreINFO.pOutDataX[i]<25.35 && PreINFO.pOutDataX[i + 1] >= 25.35 && Rs == zeroIdx)
//								{
//									Rs = i;
//									continue;
//								}
//								if (PreINFO.pOutDataY[i] < 14.2 + gap && PreINFO.pOutDataY[i + 1] >= 14.2 + gap && Re == PreINFO.Num_R400Start)
//								{
//									Re = i + 1;
//									break;
//								}
//							}
//							for (int i = Rs; i < Re; i++)
//							{
//								double dis1 = abs(sqrt((PreINFO.pOutDataX[i] - Rcentx)*(PreINFO.pOutDataX[i] - Rcentx) + (PreINFO.pOutDataY[i] - Rcenty)*(PreINFO.pOutDataY[i] - Rcenty)) - 13);
//								double dis2 = abs(sqrt((PreINFO.pOutDataX[i + 1] - Rcentx)*(PreINFO.pOutDataX[i + 1] - Rcentx) + (PreINFO.pOutDataY[i + 1] - Rcenty)*(PreINFO.pOutDataY[i + 1] - Rcenty)) - 13);
//
//								if (dis1 < 9 && dis2 >= 9)
//								{
//									RerrStart = i;
//									continue;
//								}
//								if (dis1 >= 9 && dis2 < 9)
//								{
//									RerrEnd = i + 1;
//									break;
//								}
//							}
//							//============��֪����Ͱ뾶��Բ��
//							if (RerrStart != 0 && RerrEnd != 0 && RerrStart < RerrEnd)
//							{
//								double Rx, Ry;
//								double midX = 0.5*(PreINFO.pOutDataX[RerrStart] + PreINFO.pOutDataX[RerrEnd]);
//								double midY = 0.5*(PreINFO.pOutDataY[RerrStart] + PreINFO.pOutDataY[RerrEnd]);
//								double angle0 = atan(abs(PreINFO.pOutDataY[RerrStart] - PreINFO.pOutDataY[RerrEnd]) / (PreINFO.pOutDataX[RerrStart] - PreINFO.pOutDataX[RerrEnd]));
//								double angle1 = angle0 + 3.14159 / 2;
//								double disMid2Start = sqrt((midX - PreINFO.pOutDataX[RerrStart])*(midX - PreINFO.pOutDataX[RerrStart]) + (midY - PreINFO.pOutDataY[RerrStart])*(midY - PreINFO.pOutDataY[RerrStart]));
//								double disMid2R = sqrt(R13*R13 - disMid2Start*disMid2Start);
//								Rx = midX - disMid2R*cos(angle1);
//								Ry = midY + disMid2R*sin(angle1);
//								//===��y���Ȳ�ֵ
//								double deltaY = abs(PreINFO.pOutDataY[RerrEnd] - PreINFO.pOutDataY[RerrStart]) / (RerrEnd - RerrStart);
//								for (int i = 1; i<(RerrEnd - RerrStart + 2); i++)
//								{
//									double tmpAng = atan(((PreINFO.pOutDataY[RerrEnd] - (double)i*deltaY) - Ry) / (PreINFO.pOutDataX[RerrEnd] - Rx));
//									PreINFO.pOutDataX[RerrEnd - i] = Rx + R13*cos(tmpAng);
//									PreINFO.pOutDataY[RerrEnd - i] = Ry + R13*sin(tmpAng);
//								}
//							}
//
//							//==========ȥ������ӵ�=======
//							for (int i = Re; i<PreINFO.Num_R400Start - 2; i++)
//							{
//								if (abs(PreINFO.pOutDataX[i] - 35) > 5)
//								{
//									//PreINFO.pOutDataX[i] = PreINFO.pOutDataX[i - 1];
//								}
//							}
//
//							//========R80����			
//							double R80 = 90;
//							int Rs80 = 0;
//							int Re80 = Rs;
//							int RerrStart80 = 0;
//							int RerrEnd80 = 0;
//
//							double Rcentx80 = 7.3874;
//							double Rcenty80 = 80.1573 + gap;
//							double Rx80 = Rcentx80;
//							double Ry80 = Rcenty80;
//
//							for (int i = 0; i < Rs; i++)
//							{
//								if (PreINFO.pOutDataX[i] <10 && PreINFO.pOutDataX[i + 1] >= 10 && Rs80 == 0)
//								{
//									Rs80 = i;
//									continue;
//								}
//								if (PreINFO.pOutDataX[i] < 25.35 + gap && PreINFO.pOutDataX[i + 1] >= 25.35 && Re80 == Rs)
//								{
//									Re80 = i + 1;
//									break;
//								}
//							}
//							for (int i = Rs80; i < Re80; i++)
//							{
//								double dis1 = abs(sqrt((PreINFO.pOutDataX[i] - Rcentx80)*(PreINFO.pOutDataX[i] - Rcentx80) + (PreINFO.pOutDataY[i] - Rcenty80)*(PreINFO.pOutDataY[i] - Rcenty80)) - 80);
//								double dis2 = abs(sqrt((PreINFO.pOutDataX[i + 1] - Rcentx)*(PreINFO.pOutDataX[i + 1] - Rcentx80) + (PreINFO.pOutDataY[i + 1] - Rcenty80)*(PreINFO.pOutDataY[i + 1] - Rcenty80)) - 80);
//
//								if (dis1 < 9 && dis2 >= 9)
//								{
//									RerrStart80 = i;
//									continue;
//								}
//								if (dis1 >= 9 && dis2 < 9)
//								{
//									RerrEnd80 = i + 1;
//									break;
//								}
//							}
//
//							if (RerrStart80 != 0 && RerrEnd80 != 0 && RerrStart80 < RerrEnd80)
//							{
//								double midX = 0.5*(PreINFO.pOutDataX[RerrStart80] + PreINFO.pOutDataX[RerrEnd80]);
//								double midY = 0.5*(PreINFO.pOutDataY[RerrStart80] + PreINFO.pOutDataY[RerrEnd80]);
//								double angle0 = atan(-(PreINFO.pOutDataY[RerrEnd80] - PreINFO.pOutDataY[RerrStart80]) / (PreINFO.pOutDataX[RerrEnd80] - PreINFO.pOutDataX[RerrStart80]));
//								double angle1;
//								if (angle0 <= 0)
//									angle1 = angle0 + 3.14159 / 2;
//								else
//									angle1 = angle0 - 3.14159 / 2;
//								double disMid2Start = sqrt((midX - PreINFO.pOutDataX[RerrStart])*(midX - PreINFO.pOutDataX[RerrStart]) + (midY - PreINFO.pOutDataY[RerrStart])*(midY - PreINFO.pOutDataY[RerrStart]));
//								double disMid2R = sqrt(R80*R80 - disMid2Start*disMid2Start);
//								if (angle1 <= 0)
//								{
//									Rx80 = midX + disMid2R*cos(angle1);
//								}
//								else
//									Rx80 = midX - disMid2R*cos(angle1);
//								Ry80 = midY + abs(disMid2R*sin(angle1));
//
//								//===��X���Ȳ�ֵ
//								double deltaX = abs(PreINFO.pOutDataX[RerrEnd80] - PreINFO.pOutDataX[RerrStart80]) / (RerrEnd80 - RerrStart80);
//								for (int i = 1; i < (RerrEnd - RerrStart + 2); i++)
//								{
//									double tmpAng = atan((PreINFO.pOutDataY[RerrEnd80] - Ry80) / (PreINFO.pOutDataX[RerrEnd80] - (double)i*deltaX - Rx80));
//									if (tmpAng >= 0)
//										PreINFO.pOutDataX[RerrEnd80 - i] = Rx80 + R80*cos(tmpAng);
//									else
//										PreINFO.pOutDataX[RerrEnd80 - i] = Rx80 - R80*cos(tmpAng);
//									PreINFO.pOutDataY[RerrEnd - i] = Ry80 + abs(R80*sin(tmpAng));
//								}
//							}
//
//
//
//
//							/*for (int i = RerrStart + 1; i < RerrEnd; i++)
//							{
//							double tmpAng = atan(abs(PreINFO.pOutDataY[i] - Ry) / (PreINFO.pOutDataX[i] - Rx));
//							PreINFO.pOutDataX[i] = Rx + R13*cos(tmpAng);
//							PreINFO.pOutDataY[i] = Ry - R13*sin(tmpAng);
//
//							}*/
//							/*if (RerrStart != 0 && RerrEnd != 0 && RerrStart < RerrEnd)
//							{
//							double midX = 0.5*(PreINFO.pOutDataX[RerrStart] + PreINFO.pOutDataX[RerrEnd]);
//							double midY = 0.5*(PreINFO.pOutDataY[RerrStart] + PreINFO.pOutDataY[RerrEnd]);
//							double angle0 = atan(abs(PreINFO.pOutDataY[RerrStart] - PreINFO.pOutDataY[RerrEnd]) / (PreINFO.pOutDataX[RerrStart] - PreINFO.pOutDataX[RerrEnd]));
//							double angle1 = angle0 + 3.14159 / 2;
//							double disMid2Start = sqrt((midX - PreINFO.pOutDataX[RerrStart])*(midX - PreINFO.pOutDataX[RerrStart]) + (midY - PreINFO.pOutDataY[RerrStart])*(midY - PreINFO.pOutDataY[RerrStart]));
//							double disMid2R = sqrt(R13*R13 - disMid2Start);
//							Rx = midX - disMid2R*cos(angle1);
//							Ry = midY + disMid2R*sin(angle1);
//							}
//							for (int i = RerrStart + 1; i < RerrEnd; i++)
//							{
//							double tmpAng = atan(abs(PreINFO.pOutDataX[i] - Ry) / (PreINFO.pOutDataX[i] - Rx));
//							PreINFO.pOutDataX[i] = Rx + R13*cos(tmpAng);
//							PreINFO.pOutDataY[i] = Ry - R13*sin(tmpAng);
//
//							}*/
//
//
//							IsNormalSketch = 1;
//						}
//						else//��Ӧ��Բ�ľ���ж�
//						{
//							IsNormalSketch = -6;
//						}
//
//					}
//					else//��Ӧ��R400Բ�ĵ��ж�
//					{
//						IsNormalSketch = -5;
//					}
//
//				}
//				else//��Ӧ��RS20Բ�ĵ��ж�
//				{
//					IsNormalSketch = -4;
//				}
//			}
//
//		}
//		else//��ӦR20���ǲ���
//		{
//			IsNormalSketch = -3;
//
//			// //R20��ϵ�������,������10mm
//			////Motor_MovingDist=10;
//			////Motor_MovingRound=Motor_MovingDist/Motor_DaoCheng;
//			////m_MachineCtrl_L.MotorMove(Motor_MovingRound,90,bFlagPR,m_Mscomm_L);
//
//		}
//
//		//------�¼�Ԥ�������-----//			
//
//	}
//	//std::cout << "IsNormalSketch = " << IsNormalSketch << endl;
//	return IsNormalSketch;
//}
//�����쳣��������Ϣ
int Preproccess(PreprocessINfO &PreINFO, TrackSelAndMHStruct &TrackSel)
{
	//��ʼ����
	OutLineArithmetic CalculateOutline;//���㷽������									
	int IsNormalSketch = 1;//Ĭ���������쳣�ø�����ʾ
						   //����
	int T1 = 2, num = 0;
	int P[100][2] = { 0 };
	for (int i = 0;i < PreINFO.In_Num - 1;i++)
	{
		double dis = hypot(PreINFO.pInDataX[i] - PreINFO.pInDataX[i + 1], PreINFO.pInDataY[i] - PreINFO.pInDataY[i + 1]);
		if (dis >= T1)
		{
			P[num][1] = i;P[num + 1][0] = i + 1;
			num = num + 1;
		}
	}
	P[0][0] = 0;P[num][1] = PreINFO.In_Num - 1;
	//ȥ��С��ģ��Ⱥ��
	int T2 = 50;
	std::vector<double> xs1, ys1;//ԭʼ����

	for (int i = 0;i <= num;i++)
	{
		if ((P[i][1] - P[i][0]) > T2)
		{
			for (int j = P[i][0];j <= P[i][1];j++)
			{
				xs1.push_back(PreINFO.pInDataX[j]);
				ys1.push_back(PreINFO.pInDataY[j]);

			}
		}
	}
	int N = xs1.size();
	//�ϲ�
	int T3 = 30, num2 = 0;
	int P2[100][2] = { 0 };
	for (int i = 0;i < N - 1;i++)
	{
		double dis = hypot(xs1[i] - xs1[i + 1], ys1[i] - ys1[i + 1]);
		if (dis >= T3)
		{
			P2[num2][1] = i;P2[num2 + 1][0] = i + 1;
			num2 = num2 + 1;
		}
	}
	P2[0][0] = 0;P2[num2][1] = N - 1;
	//ȥ�����ģ��Ⱥ��
	int P3[100][3] = { 0 };
	int num3 = 0;
	for (int i = 0;i <= num2 - 1;i++)
	{
		std::vector<double> yst1(ys1.begin() + P2[i][0], ys1.begin() + P2[i][1] + 1);
		std::vector<double> yst2(ys1.begin() + P2[i + 1][0], ys1.begin() + P2[i + 1][1] + 1);

		if (CalculateOutline.median(yst1, yst1.size()) < (0.5*(ys1[P2[i][0]] + ys1[P2[i][1]])) &&
			CalculateOutline.median(yst2, yst2.size()) > (0.5*(ys1[P2[i + 1][0]] + ys1[P2[i + 1][1]])))
		{
			P3[num3][0] = P2[i][0];P3[num3][1] = P2[i + 1][1];P3[num3][2] = P2[i][1] - P2[i][0] + 1;
			num3 = num3 + 1;
		}

	}
	if (P3[0][1] == 0)
	{
		IsNormalSketch = -1;//��͹�Լ��鲻ͨ��
		return IsNormalSketch;
	}
	else
	{
		std::vector<int>temp;
		for (int i = 0;i < num3;i++)
		{
			temp.push_back(P3[i][1] - P3[i][0]);
		}
		int ith = (int)(std::max_element(temp.begin(), temp.end()) - temp.begin());
		int lendata = P3[ith][1] - P3[ith][0] + 1;
		std::vector<double>xs2, ys2;//����������(��ͷ+����)
		for (int i = P3[ith][0];i <= P3[ith][1];i++)
		{
			xs2.push_back(xs1[i]);
			ys2.push_back(ys1[i]);

		}
		//��������׼
		double ges[2] = { 35.8645,34.9685 };
		int indge = P3[ith][2] - 1;
		std::vector<double>xs2L, ys2L;//���ֱ��
		int indmin = (int)(std::min_element(ys2.begin(), ys2.begin() + indge) - ys2.begin());
		for (int i = indmin; i <= indge; i++)
		{
			xs2L.push_back(xs2[i]);
			ys2L.push_back(ys2[i]);

		}

		double cof = CalculateOutline.LineFitLeastSquares(xs2L, ys2L, indge - indmin + 1);
		double dtheta = atan(20) - atan(cof);
		double T_1[2][1] = { ges[0] - xs2[indge] * cos(dtheta) + ys2[indge] * sin(dtheta),ges[1] - xs2[indge] * sin(dtheta) - ys2[indge] * cos(dtheta) };
		std::vector<double>xs2N, ys2N;//����������׼
		for (int i = 0;i < lendata;i++)
		{
			xs2N.push_back(cos(dtheta)*xs2[i] - sin(dtheta)*ys2[i] + T_1[0][0]);
			ys2N.push_back(sin(dtheta)*xs2[i] + cos(dtheta)*ys2[i] + T_1[1][0]);
		}
		//�������ƶ�
		int T5 = 15, inds = indge + 1, indend = 0;
		for (int i = 0;i < lendata;i++)
		{
			if (ys2N[i] > 153.4)
			{
				indend = i;
				break;
			}
		}
		if (indend == 0)
		{
			IsNormalSketch = -2;//�������ǲ���
			return IsNormalSketch;
		}
		else
		{
			std::vector<double>xs2Ngy, ys2Ngy;//����������
			for (int i = inds;i <= indend;i++)
			{
				xs2Ngy.push_back(xs2N[i]);
				ys2Ngy.push_back(ys2N[i]);

			}
			double hd = CalculateOutline.Hausdorff(xs2Ngy, ys2Ngy, xB, yB);//xB,yB�ֱ�Ϊ��׼������x����47-78���y����47-78��
			if (hd > T5)
			{
				IsNormalSketch = -3;//����������
				return IsNormalSketch;
			}
			else
			{
				//��������׼ȥ��ȫ����Ⱥ��
				double bz[1][2] = { xs2[0],ys2[0] };//��������ͷ��һ��
				int yh = (int)(std::max_element(ys2.begin(), ys2.end()) - ys2.begin());
				std::vector<double> xs2_20; 
				std::vector<double> ys2_20;//������R20
				int R20end = (yh + 20) > size(ys2)-1 ? size(ys2)-1 : yh + 20;
				for (int i = yh - 20;i <= R20end;i++)
				{
					xs2_20.push_back(xs2[i]);ys2_20.push_back(ys2[i]);

				}
				double Center_R20_Fitting[2] = { 0 }, Center_R400_Fitting[2] = { 0 };
				CalculateOutline.FittingCircle(xs2_20, ys2_20, R20end-yh+21, PreINFO.FittingRadius_R20, Center_R20_Fitting);
				int len_R400 = yh - 21 - inds + 1;
				std::vector<double>xs2_400, ys2_400;//������R400
				for (int i = inds;i <= yh - 21;i++)
				{
					xs2_400.push_back(xs2[i]);
					ys2_400.push_back(ys2[i]);
				}

				CalculateOutline.FittingCircle(xs2_400, ys2_400, len_R400, PreINFO.FittingRadius_R400, Center_R400_Fitting);
				double dtheta1 = atan((TrackSel.Pos_BZ_R400_Y - TrackSel.Pos_BZ_R20_Y) / (TrackSel.Pos_BZ_R400_X - TrackSel.Pos_BZ_R20_X)) -
					atan((Center_R400_Fitting[1] - Center_R20_Fitting[1]) / (Center_R400_Fitting[0] - Center_R20_Fitting[0]));
				if (fabs(dtheta1 - dtheta) > 0.1)
				{
					IsNormalSketch = -4;//������ƽ��
					return IsNormalSketch;
				}
				else
				{
					double T_2[2][1] = { TrackSel.Pos_BZ_R400_X - Center_R400_Fitting[0] * cos(dtheta1) + Center_R400_Fitting[1] * sin(dtheta1),
						TrackSel.Pos_BZ_R400_Y - Center_R400_Fitting[0] * sin(dtheta1) - Center_R400_Fitting[1] * cos(dtheta1) };
					std::vector<double>xs2NN, ys2NN;//������ϸ��׼
					for (int i = 0;i < lendata;i++)
					{
						xs2NN.push_back(cos(dtheta1)*xs2[i] - sin(dtheta1)*ys2[i] + T_2[0][0]);
						ys2NN.push_back(sin(dtheta1)*xs2[i] + cos(dtheta1)*ys2[i] + T_2[1][0]);
					}
					std::vector<double>xsNN, ysNN;//ԭʼ����ϸ��׼
					for (int i = 0;i < PreINFO.In_Num;i++)
					{
						xsNN.push_back(cos(dtheta1)*PreINFO.pInDataX[i] - sin(dtheta1)*PreINFO.pInDataY[i] + T_2[0][0]);
						ysNN.push_back(sin(dtheta1)*PreINFO.pInDataX[i] + cos(dtheta1)*PreINFO.pInDataY[i] + T_2[1][0]);
					}
					double bzn[1][2] = { xs2NN[0],ys2NN[0] };
					int ind;
					for (int i = 0;i < PreINFO.In_Num;i++)
					{
						if (fabs(xsNN[i] - bzn[0][0]) <= 0.001)
						{
							ind = i;
							break;
						}
					}
					std::vector<double>xs_ycd, ys_ycd;
					for (int i = 0;i < ind;i++)
					{
						if ((xsNN[i] > -30) && (xsNN[i] < bzn[0][0]) && (ysNN[i] > 0) && (ysNN[i] < bzn[0][1] + 3))
						{
							xs_ycd.push_back(xsNN[i]);
							ys_ycd.push_back(ysNN[i]);

						}
					}

					xs_ycd.insert(xs_ycd.end(), xs2NN.begin(), xs2NN.end());
					ys_ycd.insert(ys_ycd.end(), ys2NN.begin(), ys2NN.end());

					////////��ͷ���δ���
					//����
					int inds2, T4 = 2;
					for (int i = 0;i < xs_ycd.size();i++)
					{
						if (ys_ycd[i] > 40)
						{
							inds2 = i;
							break;
						}
					}
					int lengt = inds2;
					int P4[100][2] = { 0 }, num4 = 0;;
					for (int i = 0;i < lengt - 1;i++)
					{
						double dis = hypot(xs_ycd[i] - xs_ycd[i + 1], ys_ycd[i] - ys_ycd[i + 1]);
						if (dis >= T4)
						{
							P4[num4][1] = i;P4[num4 + 1][0] = i + 1;
							num4 = num4 + 1;
						}
					}
					P4[0][0] = 0;P4[num4][1] = lengt - 1;
					//ȥ��С��ģ��Ⱥ��
					int P5[100][2] = { 0 }, num5 = 0, T5 = 5;
					std::vector<double>xs_ycd_lgt, ys_ycd_lgt;

					for (int i = 0;i <= num4;i++)
					{
						if ((P4[i][1] - P4[i][0]) > T5)
						{
							P5[num5][0] = P4[i][0];P5[num5][1] = P4[i][1];
							num5++;
							for (int j = P4[i][0];j <= P4[i][1];j++)
							{
								xs_ycd_lgt.push_back(xs_ycd[j]);
								ys_ycd_lgt.push_back(ys_ycd[j]);

							}
						}
					}
					//��ͷ����
					std::vector<double>xbdL, ybdL;//����ͷ���ȱʧ������
					int indL;
					if (xs_ycd_lgt[0] > -28.921)
					{
						for (int i = 0;i < 39;i++)
						{
							if (xB[i] > xs_ycd_lgt[0])
							{
								indL = i - 1;
								for (int j = 0;j <= indL;j++)
								{
									xbdL.push_back(xB[j]);
									ybdL.push_back(yB[j] + ys_ycd_lgt[1] - yB[indL]);
								}
								break;
							}
						}
					}
					std::vector<double>xLastgt, yLastgt;
					xLastgt = xbdL;yLastgt = ybdL;
					if (num5 < 2)
					{
						xLastgt.insert(xLastgt.end(), xs_ycd_lgt.begin(), xs_ycd_lgt.end());
						yLastgt.insert(yLastgt.end(), ys_ycd_lgt.begin(), ys_ycd_lgt.end());
					}
					else
					{
						std::vector<double>xbdM, ybdM, xs_ycd_ngt, ys_ycd_ngt;//����ͷ�в�ȱʧ������
						int ind1, ind2;
						for (int i = 0;i < num5 - 1;i++)
						{
							for (int j = 0;j < 39;j++)
							{
								if (xB[j] > xs_ycd[P5[i][1]])
								{
									ind1 = j;
									break;
								}
							}
							for (int j = ind1;j < 39;j++)
							{
								if (xB[j] >= xs_ycd[P5[i + 1][0]])
								{
									ind2 = j - 1;
									break;
								}
							}
							for (int k = ind1;k <= ind2;k++)
							{
								xbdM.push_back(xB[k]);
								ybdM.push_back(yB[k] + 0.5*(ys_ycd[P5[i][1]] - yB[ind1] + ys_ycd[P5[i + 1][0]] - yB[ind2]));
							}
							if (i == 0)
							{
								for (int h = P5[0][0];h <= P5[0][1];h++)
								{
									xs_ycd_ngt.push_back(xs_ycd[h]);
									ys_ycd_ngt.push_back(ys_ycd[h]);
								}
								for (int h = 0;h < xbdM.size();h++)
								{
									xs_ycd_ngt.push_back(xbdM[h]);
									ys_ycd_ngt.push_back(ybdM[h]);

								}
								for (int h = P5[1][0];h <= P5[1][1];h++)
								{
									xs_ycd_ngt.push_back(xs_ycd[h]);
									ys_ycd_ngt.push_back(ys_ycd[h]);
								}
							}
							else
							{
								for (int h = 0;h < xbdM.size();h++)
								{
									xs_ycd_ngt.push_back(xbdM[h]);
									ys_ycd_ngt.push_back(ybdM[h]);
								}
								for (int h = P5[i + 1][0];h <= P5[i + 1][1];h++)
								{
									xs_ycd_ngt.push_back(xs_ycd[h]);
									ys_ycd_ngt.push_back(ys_ycd[h]);
								}
							}
						}
						xLastgt.insert(xLastgt.end(), xs_ycd_ngt.begin(), xs_ycd_ngt.end());
						yLastgt.insert(yLastgt.end(), ys_ycd_ngt.begin(), ys_ycd_ngt.end());
					}
					memcpy(PreINFO.pOutDataX, &xLastgt[0], xLastgt.size() * sizeof(double));
					memcpy(PreINFO.pOutDataY, &yLastgt[0], yLastgt.size() * sizeof(double));
					int N12 = xLastgt.size();
					PreINFO.Num_R400Start = N12 + 1;
					for (int i = inds2;i < xs_ycd.size();i++)
					{
						PreINFO.pOutDataX[N12] = xs_ycd[i];
						PreINFO.pOutDataY[N12] = ys_ycd[i];
						N12++;
					}
					PreINFO.Out_Num = N12;
					return IsNormalSketch;
				}

			}
		}
	}

}
void SaveInvalidOutline(int m_nIsNormal, PreprocessINfO &PreINFO,TestInfo &TestInformation,IntLoopBuffCtl GetDataNumSt_LoopBuff)
{
	CString WrongInfo;
	CString FilePath;
	switch (m_nIsNormal)
	{
	case -1:WrongInfo = "������� -1������αƽ���������300";
		break;
	case -2:WrongInfo = "������� -2��Ls400������";
		break;
	case -3:WrongInfo = "������� -3��R20���ǲ���";
		break;
	case -4:WrongInfo = "������� -4��R20Բ���жϴ���";
		break;
	case -5:WrongInfo = "������� -5��R400Բ���жϴ���";
		break;
	case -6:WrongInfo = "������� -6��Բ�ľ����";
		break;
	case -8:WrongInfo = "������� -8����㸲�ǲ���";
		break;
	case -10:WrongInfo = "������� -10����ͷ�쳣";
		break;
	case -11:WrongInfo = "������� -11����㸲�ǲ���";
		break;
	}

	CTime CurTime;
	CString strTime1,strTime2;
	CString XmInfo, TrackInfo;
	CurTime = CurTime.GetTickCount();
	strTime1.Format("%d%02d%02d", CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay());
	strTime2.Format("%d-%02d-%02d",CurTime.GetHour(),CurTime.GetMinute(),CurTime.GetSecond());
	
	switch (TestInformation.XM_QianHou)
	{
	case 0:XmInfo = "ϳĥǰ"; 
		break;
	case 1:XmInfo = "ϳĥ��"; 
		break;
	}
	switch (TestInformation.TrackSel)
	{
	case 0:TrackInfo = _T("a");
		break;
	case 1:TrackInfo = _T("b");
		break;
	}

	FilePath = _T("D:\\InvalidOutline\\")+strTime1+XmInfo+"\\"+strTime2;
	if (!PathIsDirectory(FilePath))
	{
		CreateDirectory(FilePath, 0);
	}
	CString strOriginOutline;
	CString g_strDirection = TestInformation.Direction;
	CString g_strXianbie = TestInformation.Xianbie;
	int OriginNum = LoopBuff.LoopBuffDataLength(&GetDataNumSt_LoopBuff); 
	int g_nStart = TestInformation.DistanceStart;
	int g_nEnd = g_nStart + Encoder_Distance*OriginNum;

	CFile InvalidInfo;
	strOriginOutline.Format(_T("%s%s-%.1fM-%s�쳣ԭʼ������%s"), g_strXianbie,g_strDirection, g_nEnd, XmInfo, TrackInfo);
	CString filename(_T("%s\\%s.txt",FilePath,strOriginOutline));//�ļ�����·��	
	bool openflag = InvalidInfo.Open(filename, CFile::modeCreate | CFile::modeReadWrite);
	if (openflag)
	{	
		CString x_Origin,y_Origin,str;
		x_Origin.Format(_T(""), PreINFO.pInDataX[1]);
		InvalidInfo.Write(str, strlen(str));
		InvalidInfo.Close();
	}
}




void RamerFunc(double* xdata,double* ydata,int beginpoint,int endpoint,int* ResultArray,int &Index)
{

	double Prethreshold = 0.6;
	double threshold = 0;
	int i,m,k;
	double x1,x2,y1,y2,d0,d;
	int markpoint;
	markpoint = 0;
	double xdata1[SensorMaxPoint]={0};
	double xdata2[SensorMaxPoint]={0};
	double ydata1[SensorMaxPoint]={0};
	double ydata2[SensorMaxPoint]={0};

	int fornum;
	fornum = endpoint-beginpoint-1;
	for(i=beginpoint+1;i<=beginpoint+fornum;i++)
	{
		x1=xdata[beginpoint];y1=ydata[beginpoint];
		x2=xdata[endpoint];y2=ydata[endpoint];
		d0=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		d=fabs(((x1-xdata[i])*(y2-ydata[i])-(x2-xdata[i])*(y1-ydata[i]))/d0);
		if(d>threshold)
		{
			markpoint = i;
			threshold = d;
		}		
	} 
	////////���������֮�����������ֵ֮�󣬱������ֵ�ı��///////////////////
	ResultArray[Index]=markpoint;
	Index++;
	for(k=beginpoint;k<=markpoint;k++)
	{
		xdata1[k]=xdata[k];
		ydata1[k]=ydata[k];   
	}

	for(m=markpoint;m<=endpoint;m++)
	{
		xdata2[m]=xdata[m];
		ydata2[m]=ydata[m];   
	}

	if( threshold> Prethreshold)
	{
		RamerFunc(xdata1, ydata1, beginpoint,markpoint,ResultArray,Index);
		RamerFunc(xdata2, ydata2, markpoint, endpoint,ResultArray,Index);
	}
	else
	{
		ResultArray[Index-1]=beginpoint;
		ResultArray[Index]=endpoint;
		Index++;
		if(Index>300)
		{
			return;
		}
	}
}



double FuncCalculatingHdm(CalHdmStruct &CalculatingHdm,bool bDuiQi,bool bLOrR,int &CalPointNum,double* pInDataX,double* pInDataY,int R400_Start)
{	
	OutLineArithmetic CalculateOutline;
	double youyi;
	int Count_Node=0;//������ʱ��23�������ű���
	int	Count_Range_Ang=0;//������ʱ��ʵ���������Ա�׼��Ϊ���ĵ����
	int Count_Zero;//�������λ��
	//int ind1=-1,ind2=0; 
	int ind1=0,ind2=0,indhd=0;
	int Count_Duan=0;//�������
	int i_sc;
	int index_xml_bz =0;					//��׼ϳĥ�����,��ʼ��Ϊ0
	double Pos_Rec_Aln_Y=0;
	double Ang_L=0,Ang_R=0,Para_Node_M=0,Para_Node_N=0;

	switch(CalculatingHdm.iTrackSel)
	{
	case 0:
		{

		
		int hs_Row1_50[Num_Duan_50]={0};//4��Բ��ÿ��Բ���ϱ�׼��ĸ���	
		const double hs_Row2_50[6]={Hdm_50.Pos_BZ_R13L_X,Hdm_50.Pos_BZ_R80L_X,Hdm_50.Pos_BZ_R300L_X,
			Hdm_50.Pos_BZ_R300R_X,Hdm_50.Pos_BZ_R80R_X,Hdm_50.Pos_BZ_R13R_X};
		const double hs_Row3_50[6]={Hdm_50.Pos_BZ_R13_Y,Hdm_50.Pos_BZ_R80_Y,Hdm_50.Pos_BZ_R300_Y,
			Hdm_50.Pos_BZ_R300_Y,Hdm_50.Pos_BZ_R80_Y,Hdm_50.Pos_BZ_R13_Y};
		double hd_Row1_50[Num_Node_50]={0},hd_Row2_50[Num_Node_50]={0};//50��׼������
		for (int i=0;i<Num_Node_50;i++)
		{
			hd_Row1_50[i]=Pos_BZ_X_50[i];
			hd_Row2_50[i]=Pos_BZ_Y_50[i];
		}
		int hd_Row4[Num_Node_50]={0};//ʵ���ͱ�׼�����λ��
		int hd_Row3[Num_Node_50]={0};//��׼������һ����
		int ud,df,loc[Num_Node_50]={0};
		double hdy[Num_Node_50]={0};//��ֵ���	
		double Ang_BZ[Num_Node_50]={0};
		double SCBZ_HDM_X[Num_Node_50]={0},SCBZ_HDM_Y[Num_Node_50]={0};
		double HDMJD[Num_Node_50]={0};
		//���indhd
		for (int i=0;i<SensorMaxPoint;i++)
		{
			if (Pos_BZ_X_50[i]<pInDataX[0]&&Pos_BZ_X_50[i+1]>pInDataX[0])
			{
				indhd++;
			} 
			else
			{
				break;
			}
		}
		//�ҳ�С�ڵ���Pos_BZ_Y_60[22]����������Ǹ��������
		for (int ind2Finder =0;ind2Finder<SensorMaxPoint;ind2Finder++)
		{
			if (pInDataY[ind2Finder] <Pos_BZ_Y_50[Num_Node_50-1])
			{
				ind2++;
			} 
			else if (pInDataY[ind2Finder] ==Pos_BZ_Y_50[Num_Node_50-1])
			{
				ind2++;
				break;
			}
			else if (pInDataY[ind2Finder] >Pos_BZ_Y_50[Num_Node_50-1])
			{
				break;
			}							
		}
		if (!bDuiQi)
		{
			//�ֶ�
			for (int i=0;i<Num_Node_50;i++)
			{
				if (hd_Row1_50[i]<=-23)
				{
					hs_Row1_50[0]=hs_Row1_50[0]+1;

					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_50[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_50[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_50[i])
						{
							break;
						}

					}

					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				} 
				else if(hd_Row1_50[i]>-23&&hd_Row1_50[i]<=0)
				{
					hs_Row1_50[1]=hs_Row1_50[1]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_50[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_50[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_50[i])
						{
							break;
						}

					}

					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else if (hd_Row1_50[i]>0&&hd_Row1_50[i]<=23)
				{
					hs_Row1_50[2]=hs_Row1_50[2]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_50[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_50[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_50[i])
						{
							break;
						}

					}

					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else
				{
					hs_Row1_50[3]=hs_Row1_50[3]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_50[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_50[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_50[i])
						{
							break;
						}

					}

					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
			}
			for(int i=0;i<Num_Node_50;i++)
			{
				double x_temp[2]={pInDataX[hd_Row3[i]],pInDataX[hd_Row3[i]+1]};
				double y_temp[2]={pInDataY[hd_Row3[i]],pInDataY[hd_Row3[i]+1]};

				hdy[i]=Func_CZ(hd_Row1_50[i],x_temp,y_temp);
			}
			for (int hdRow4Finder=0;hdRow4Finder<Num_Node_50;hdRow4Finder++)
			{
				if (hdy[hdRow4Finder]>=hd_Row2_50[hdRow4Finder])
				{
					hd_Row4[hdRow4Finder]=0;
				} 
				else
				{
					hd_Row4[hdRow4Finder]=1;
				}
			}
			ind1 =0;
			ind2=R400_Start-5;
			index_xml_bz=0;
			Count_Node=0;
			int Sum_Row1_50=0;
			for (int i=0;i<indhd;i++)
			{
				SCBZ_HDM_X[i]=hd_Row1_50[i];
				SCBZ_HDM_Y[i]=hd_Row2_50[i];
				if(i<Num_Duan_50)
				{
					Sum_Row1_50+=hs_Row1_50[i];
					if(indhd>=Sum_Row1_50)
					{
						hs_Row1_50[i]=0;
					}
					else
					{
						hs_Row1_50[i]=Sum_Row1_50-indhd;
					}
				}				
				Count_Node++;//��ʼλ�������ǰ�ƶ�indhd��(�൱��Count_Node=indhd;)
			}
			Count_Zero=CalculatingHdm.Index_Zero-1;//C++����ż�һ			
			for (Count_Duan=0;Count_Duan< Num_Duan_50;Count_Duan++)
			{
				if (hs_Row1_50[Count_Duan]!=0)
				{
					for (int i=0;i<hs_Row1_50[Count_Duan];i++)
					{
						if(Count_Node<Num_Node_50)
						{
							Ang_BZ[Count_Node]=atan((hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]))*180/Pi;
							if(Ang_BZ[Count_Node]<0)
								Ang_BZ[Count_Node]=Ang_BZ[Count_Node]+180;
							ud=hd_Row4[Count_Node];
							if (Count_Node==0)
							{
								df=ind1;
							}
							else
							{
								df=loc[Count_Node-1];
							}
							if (Count_Duan<2)//��
							{
								if (ud ==1)//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									    {
											Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
											Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
											if(Ang_L<0)
												Ang_L=Ang_L+180;
											if(Ang_R<0)
												Ang_R=Ang_R+180;
											if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
											{
												loc[Count_Node]=Count_Range_Ang;	
												if (Count_Node==Count_Zero)
												{											
													SCBZ_HDM_X[Count_Node]=0;
													SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
													break;
												}
												else
												{
													Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
													Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

													SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
													SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
													break;

												}

											}
											else
											{
												SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
												SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];										
											}
										}
									Count_Node++;
								}
								else//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									{
										Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{											
												SCBZ_HDM_X[Count_Node]=0;
												SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

												SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
												break;

											}

										}
										else
										{
											SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
											SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];										
										}
									}
									Count_Node++;
								}
							}
							else if (Count_Duan>=2&&Count_Duan<4)//��
							{
								if (ud ==1)//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									{
										Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{											
												SCBZ_HDM_X[Count_Node]=0;
												SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

												SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
												break;

											}

										}
										else
										{
											SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
											SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];										
										}
									}
									Count_Node++;
								}
								else//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									{
										Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{											
												SCBZ_HDM_X[Count_Node]=0;
												SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

												SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
												break;

											}

										}
										else
										{
											SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
											SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];										
										}
									}
									Count_Node++;
								}
							}
						}
					}
				}
			}
			if (bLOrR==bFlagTrack_L)//����false����ʾ���
			{
				for (int i=0;i<Num_Node_50;i++)
				{
					HdmScbz_XL_50[i]=SCBZ_HDM_X[i];
					HdmScbz_YL_50[i]=SCBZ_HDM_Y[i];
				}
			}
			else if (bLOrR==bFlagTrack_R)
			{
				for (int i=0;i<Num_Node_50;i++)
				{
					HdmScbz_XR_50[i]=SCBZ_HDM_X[i];
					HdmScbz_YR_50[i]=SCBZ_HDM_Y[i];
				}
			}
		}

		if (bDuiQi)
		{
			for(int i=0;i<CalPointNum-1;i++)
			{
				if((pInDataX[i]<=CalculatingHdm.Pos_BZ_Aln_X)&&(pInDataX[i+1]>=CalculatingHdm.Pos_BZ_Aln_X))
				{
					Pos_Rec_Aln_Y=(pInDataY[i+1]-pInDataY[i])*(CalculatingHdm.Pos_BZ_Aln_X-pInDataX[i])/(pInDataX[i+1]-pInDataX[i])+pInDataY[i];
					break;
				}
			}
			for(int i=0;i<CalPointNum;i++)
			{
				pInDataY[i]=pInDataY[i]-(Pos_Rec_Aln_Y-CalculatingHdm.Pos_BZ_Aln_Y);
			}
			//ind1��ind2��ֵ��ind2����
			if (bLOrR==bFlagTrack_L)
			{
				GuiDiPoRevolve(CalPointNum, pInDataX, pInDataY, true,Guidipo_L);
			} 
			else
			{
				GuiDiPoRevolve(CalPointNum, pInDataX, pInDataY, true, Guidipo_R);
			}
			//////////////�����춥��////////////////////////////////
			//double pInDataXtmp[700], pInDataYtmp[700];
			//for (int i = 0; i < CalPointNum; i++)
			//{
			//	pInDataXtmp[i] = pInDataX[i];
			//	pInDataYtmp[i] = pInDataY[i];
			//}
			//double pInDataXxl[300], pInDataYxl[300];
			//int n = 0;
			//for (int i = 0; i < CalPointNum; i++)
			//{
			//	if (pInDataX[i] >= -10 && pInDataX[i] <= 10&&pInDataY[i]<=20)
			//	{
			//		pInDataXxl[n] = pInDataX[i];
			//		pInDataYxl[n] = pInDataY[i];
			//		n++;
			//	}
			//}
			//double xielv = CalculateOutline.LineFitLeastSquares(pInDataXxl, pInDataYxl, 300);
			//double gd_theta = atan(xielv);
			//for (int i = 0; i < CalPointNum; i++)
			//{
			//	pInDataXtmp[i] = pInDataX[i] * cos(-gd_theta) - pInDataY[i] * sin(-gd_theta);
			//	pInDataYtmp[i] = pInDataX[i] * sin(-gd_theta) + pInDataY[i] * cos(-gd_theta);
			//	pInDataX[i] = pInDataXtmp[i];
			//	pInDataY[i] = pInDataYtmp[i];
			//}

			//for (int i = 0; i < CalPointNum; i++)
			//{
			//	if (pInDataY[i] >= -14.2 && pInDataY[i + 1] <= -14.2)
			//	{
			//		double x_tmp = (-14.2 - pInDataY[i])*(pInDataX[i] - pInDataX[i + 1]) / (pInDataY[i] - pInDataY[i + 1]) + pInDataX[i];
			//		youyi = 35.4 - x_tmp;
			//		break;
			//	}
			//}
			//for (int i = 0; i < CalPointNum; i++)
			//{
			//	pInDataX[i] += youyi;
			//}


			ind1=0;
			ind2=R400_Start-5;
			index_xml_bz=0;
			Count_Node=0;
			int Sum_Row1_50=0;
			for (int i=0;i<indhd;i++)
			{
				SCBZ_HDM_X[i]=hd_Row1_50[i];
				SCBZ_HDM_Y[i]=hd_Row2_50[i];
				if(i<Num_Duan_50)
				{
					Sum_Row1_50+=hs_Row1_50[i];
					if(indhd>=Sum_Row1_50)
					{
						hs_Row1_50[i]=0;
					}
					else
					{
						hs_Row1_50[i]=Sum_Row1_50-indhd;
					}
				}				
				Count_Node++;//��ʼλ�������ǰ�ƶ�indhd��(�൱��Count_Node=indhd;)
			}
			Count_Zero=CalculatingHdm.Index_Zero-1;//C++����ż�һ		

			for (Count_Duan=0;Count_Duan< Num_Duan_50;Count_Duan++)
			{
				if (hs_Row1_50[Count_Duan]!=0)
				{
					for (int i=0;i<hs_Row1_50[Count_Duan];i++)
					{
						if(Count_Node<Num_Node_50)
						{
							Ang_BZ[Count_Node]=atan((hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]))*180/Pi;
							if(Ang_BZ[Count_Node]<0)
								Ang_BZ[Count_Node]=Ang_BZ[Count_Node]+180;
							ud=hd_Row4[Count_Node];
							if (Count_Node==0)
							{
								df=ind1;
							}
							else
							{
								df=loc[Count_Node-1];
							}
							if (Count_Duan<2)//��
							{
								if (ud ==1)//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									{
										Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{											
												SCBZ_HDM_X[Count_Node]=0;
												SCBZ_HDM_Y[Count_Node]=0;
												HDMJD[Count_Node]=0;
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

												SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
												HDMJD[Count_Node]=-sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node]));


												break;

											}

										}
										else
										{
											SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
											SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];	
											HDMJD[Count_Node]=0;
										}
									}
									Count_Node++;
								}
								else//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									{
										Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{											
												SCBZ_HDM_X[Count_Node]=0;
												SCBZ_HDM_Y[Count_Node]=0;
												HDMJD[Count_Node]=0;
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

												SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
												HDMJD[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node]));
												break;

											}

										}
										else
										{
											SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
											SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];	
											HDMJD[Count_Node]=0;
										}
									}
									Count_Node++;
								}
							}
							else if (Count_Duan>=2&&Count_Duan<4)//��
							{
								if (ud ==1)//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									{
										Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{											
												SCBZ_HDM_X[Count_Node]=0;
												SCBZ_HDM_Y[Count_Node]=0;
												HDMJD[Count_Node]=0;
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

												SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
												HDMJD[Count_Node]=-sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node]));
												break;

											}

										}
										else
										{
											SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
											SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];		
											HDMJD[Count_Node]=0;
										}
									}
									Count_Node++;
								}
								else//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									{
										Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{											
												SCBZ_HDM_X[Count_Node]=0;
												SCBZ_HDM_Y[Count_Node]=0;
												HDMJD[Count_Node]=0;
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

												SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
												HDMJD[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node]));
												break;

											}

										}
										else
										{
											SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
											SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];
											HDMJD[Count_Node]=0;
										}
									}
									Count_Node++;
								}
							}
						}
					}
				}
			}

		}
		if (bLOrR==bFlagTrack_L)//����false����ʾ���
		{
			for (int i=0;i<Num_Node_50;i++)
			{
				HdmNode_XL_50[i]=SCBZ_HDM_X[i];
				HdmNode_YL_50[i]=SCBZ_HDM_Y[i];
				Dist_Hdmjd_L_50[i]=HDMJD[i];
			}
		}
		else if (bLOrR==bFlagTrack_R)
		{
			for (int i=0;i<Num_Node_50;i++)
			{
				HdmNode_XR_50[i]=SCBZ_HDM_X[i];
				HdmNode_YR_50[i]=SCBZ_HDM_Y[i];
				Dist_Hdmjd_R_50[i]=HDMJD[i];
			}
		}
		break;
		}
	case 1:
		{

		
		//------------60����------------//
		//60Բ������
		int hs_Row1_60[6]={0};//6��Բ��ÿ��Բ���ϱ�׼��ĸ���	
		const double hs_Row2_60[6]={Hdm_60.Pos_BZ_R13L_X,Hdm_60.Pos_BZ_R80L_X,Hdm_60.Pos_BZ_R300L_X,
			Hdm_60.Pos_BZ_R300R_X,Hdm_60.Pos_BZ_R80R_X,Hdm_60.Pos_BZ_R13R_X};
		const double hs_Row3_60[6]={Hdm_60.Pos_BZ_R13_Y,Hdm_60.Pos_BZ_R80_Y,Hdm_60.Pos_BZ_R300_Y,
			Hdm_60.Pos_BZ_R300_Y,Hdm_60.Pos_BZ_R80_Y,Hdm_60.Pos_BZ_R13_Y};
		double hd_Row1_60[Num_Node]={0},hd_Row2_60[Num_Node]={0};//60��׼������
		for (int i=0;i<Num_Node;i++)
		{
			hd_Row1_60[i]=Pos_BZ_X_60[i];
			hd_Row2_60[i]=Pos_BZ_Y_60[i];
		}
		int hd_Row4[Num_Node]={0};//ʵ���ͱ�׼�����λ��
		int hd_Row3[Num_Node]={0};//��׼������һ����
		int ud,df,loc[Num_Node]={0};
		double hdy[Num_Node]={0};//��ֵ���	
		double Ang_BZ[Num_Node]={0};
		double SCBZ_HDM_X[Num_Node]={0},SCBZ_HDM_Y[Num_Node]={0};
		double HDMJD[Num_Node]={0};		
		
		//���indhd
		for (int i=0;i<SensorMaxPoint;i++)
		{
			if (Pos_BZ_X_60[i]<pInDataX[0]&&Pos_BZ_X_60[i+1]>pInDataX[0])
			{
				indhd++;
			} 
			else
			{
				break;
			}
		}
		
		//�ҳ�С�ڵ���Pos_BZ_Y_60[22]����������Ǹ��������
		for (int ind2Finder =0;ind2Finder<SensorMaxPoint;ind2Finder++)
		{
			if (pInDataY[ind2Finder] <Pos_BZ_Y_60[Num_Node-1])
			{
				ind2++;
			} 
			else if (pInDataY[ind2Finder] ==Pos_BZ_Y_60[Num_Node-1])
			{
				ind2++;
				break;
			}
			else if (pInDataY[ind2Finder] >Pos_BZ_Y_60[Num_Node-1])
			{
				break;
			}							
		}
		if (!bDuiQi)
		{
			for (int i=0;i<Num_Node;i++)
			{
				if(hd_Row1_60[i]<=-25.35)
				{
					hs_Row1_60[0]=hs_Row1_60[0]+1;

					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;

				}
				else if (hd_Row1_60[i]>-25.35&&hd_Row1_60[i]<=-10)
				{
					hs_Row1_60[1]=hs_Row1_60[1]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else if (hd_Row1_60[i]>-10&&hd_Row1_60[i]<=0)
				{
					hs_Row1_60[2]=hs_Row1_60[2]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else if (hd_Row1_60[i]>0&&hd_Row1_60[i]<=10)
				{
					hs_Row1_60[3]=hs_Row1_60[3]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else if (hd_Row1_60[i]>10&&hd_Row1_60[i]<=25.35)
				{
					hs_Row1_60[4]=hs_Row1_60[4]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else
				{
					hs_Row1_60[5]=hs_Row1_60[5]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
			}
			

			for(int i=0;i<Num_Node;i++)
			{
				double x_temp[2]={pInDataX[hd_Row3[i]],pInDataX[hd_Row3[i]+1]};
				double y_temp[2]={pInDataY[hd_Row3[i]],pInDataY[hd_Row3[i]+1]};

				hdy[i]=Func_CZ(hd_Row1_60[i],x_temp,y_temp);
			}

			for (int hdRow4Finder=0;hdRow4Finder<Num_Node;hdRow4Finder++)
			{
				if (hdy[hdRow4Finder]>=hd_Row2_60[hdRow4Finder])
				{
					hd_Row4[hdRow4Finder]=0;
				} 
				else
				{
					hd_Row4[hdRow4Finder]=1;
				}
			}

			ind1 =0;
			ind2=R400_Start-5;

			//��ȡ����澫��
			//int Count_BZAng=0;
			index_xml_bz=0;
			Count_Node=0;
			int Sum_Row1_60=0;
			for (int i=0;i<indhd;i++)
			{
				SCBZ_HDM_X[i]=hd_Row1_60[i];
				SCBZ_HDM_Y[i]=hd_Row2_60[i];
				if(i<6)
				{
					Sum_Row1_60+=hs_Row1_60[i];
					if(indhd>=Sum_Row1_60)
					{
						hs_Row1_60[i]=0;
					}
					else
					{
						hs_Row1_60[i]=Sum_Row1_60-indhd;
					}
				}				
				Count_Node++;//��ʼλ�������ǰ�ƶ�indhd��(�൱��Count_Node=indhd;)
			}
			Count_Zero=CalculatingHdm.Index_Zero-1;//C++����ż�һ
			for (Count_Duan=0;Count_Duan< Num_Duan_60;Count_Duan++)
			{
				if (hs_Row1_60[Count_Duan]!=0)//�ö����б�׼�㣬�����ѭ��
				{
					for (int i=0;i<hs_Row1_60[Count_Duan];i++)
					{
						if(Count_Node<Num_Node)
						{
						Ang_BZ[Count_Node]=atan((hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]))*180/Pi;
						if(Ang_BZ[Count_Node]<0)
							Ang_BZ[Count_Node]=Ang_BZ[Count_Node]+180;
						ud=hd_Row4[Count_Node];
						//df�ĳ�ʼ������������������ж�����ǰ�棬����Ĭ�ϵ�һ����Ϊ���Ϸ�
						if (Count_Node==0)
						{
							df=ind1;
						}
						else
						{
							df=loc[Count_Node-1];
						}
						if (Count_Duan<3)//��
						{
							if (ud ==1)//����
							{
								
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											/*Dist_Node[Count_Node]=(FenZi1-FenZi2)/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											//Dist_Node[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}

									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];										
									}
								}
								//Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								//Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];
								////Dist_Hdm_Node[index_xml_bz]=Dist_Node[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
							else//����
							{
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											//Dist_Node[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}
									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];										
									}
								}
								//Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								//Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];
								////Dist_Hdm_Node[index_xml_bz]=Dist_Node[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
						}
						else if (Count_Duan>=3&&Count_Duan<6)
						{
							if (ud==1)//����
							{
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi+180;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi+180;

									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											//Dist_Node[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}
									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];										
									}
								}
								//Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								//Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];
								////Dist_Hdm_Node[index_xml_bz]=Dist_Node[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
							else//����
							{
								if (Count_Node==0)
								{
									df=ind1;
								}
								else
								{
									df=loc[Count_Node-1];
								}
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											//Dist_Node[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}
									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];										
									}
								}
									
								//Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								//Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];
								////Dist_Hdm_Node[index_xml_bz]=Dist_Node[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
						}
						} 



					}
				}
			}
			//�洢ʵ���׼��
			if (bLOrR==bFlagTrack_L)//����false����ʾ���
			{
				for (int i=0;i<Num_Node;i++)
				{
					HdmScbz_XL[i]=SCBZ_HDM_X[i];
					HdmScbz_YL[i]=SCBZ_HDM_Y[i];
				}
			}
			else if (bLOrR==bFlagTrack_R)
			{
				for (int i=0;i<Num_Node;i++)
				{
					HdmScbz_XR[i]=SCBZ_HDM_X[i];
					HdmScbz_YR[i]=SCBZ_HDM_Y[i];
				}
			}

		}
		if (bDuiQi)
		{
			//�ҵ�0mm������
			for(int i=0;i<CalPointNum-1;i++)
			{
				if((pInDataX[i]<=CalculatingHdm.Pos_BZ_Aln_X)&&(pInDataX[i+1]>=CalculatingHdm.Pos_BZ_Aln_X))
				{
					Pos_Rec_Aln_Y=(pInDataY[i+1]-pInDataY[i])*(CalculatingHdm.Pos_BZ_Aln_X-pInDataX[i])/(pInDataX[i+1]-pInDataX[i])+pInDataY[i];
					break;
				}
			}
			/*double* kk = new double[400];
			kk = pInDataX;*/
			for(int i=0;i<CalPointNum;i++)
			{
				pInDataY[i]=pInDataY[i]-(Pos_Rec_Aln_Y-CalculatingHdm.Pos_BZ_Aln_Y);
			}

			////////////���������////////////////////////////////
			if (bLOrR == bFlagTrack_L)
			{
				GuiDiPoRevolve(CalPointNum, pInDataX, pInDataY, true, Guidipo_L);
			}
			else
			{
				GuiDiPoRevolve(CalPointNum, pInDataX, pInDataY, true, Guidipo_R);
			}			
			/*double pInDataXtmp[700], pInDataYtmp[700];
			for (int i = 0; i < CalPointNum; i++)
			{
				pInDataXtmp[i] = pInDataX[i];
				pInDataYtmp[i] = pInDataY[i];
			}
			double pInDataXxl[300], pInDataYxl[300];
			int n = 0;
			for (int i = 0; i < CalPointNum; i++)
			{
				if (pInDataX[i] >= -10 && pInDataX[i] <= 10&&pInDataY[i]<1)
				{
					pInDataXxl[n] = pInDataX[i];
					pInDataYxl[n] = pInDataY[i];
					n++;
				}
			}
			double xielv = CalculateOutline.LineFitLeastSquares(pInDataXxl, pInDataYxl, n);
			double gd_theta = atan(xielv);
			gd_theta = 0;
			for (int i = 0; i < CalPointNum; i++)
			{
				pInDataXtmp[i] = pInDataX[i] * cos(-gd_theta) - pInDataY[i] * sin(-gd_theta);
				pInDataYtmp[i] = pInDataX[i] * sin(-gd_theta) + pInDataY[i] * cos(-gd_theta);
				pInDataX[i] = pInDataXtmp[i];
				pInDataY[i] = pInDataYtmp[i];
			}

			for (int i = 0; i < CalPointNum; i++)
			{
				if (pInDataY[i] <= 14.2 && pInDataY[i + 1] >= 14.2)
				{
					double x_tmp = (14.2 - pInDataY[i])*(pInDataX[i] - pInDataX[i + 1]) / (pInDataY[i] - pInDataY[i + 1]) + pInDataX[i];
					youyi = 35.4 - x_tmp;
					break;
				}
			}
			for (int i = 0; i < CalPointNum; i++)
			{
				pInDataX[i] += youyi;
			}*/

			//ind1��ind2��ֵ��ind2����
			ind1=0;
			
			//�ֶ�
			for (int i=0;i<Num_Node;i++)
				{
					if(hd_Row1_60[i]<=-25.35)
					{
						hs_Row1_60[0]=hs_Row1_60[0]+1;

						for (i_sc=ind1;i_sc<=ind2;i_sc++)
						{

							if (pInDataX[i_sc]<hd_Row1_60[i])
							{
								hd_Row3[i]++;
							}
							else if (pInDataX[i_sc]==hd_Row1_60[i])
							{
								hd_Row3[i]++;
								break;
							}
							else if (pInDataX[i_sc]>hd_Row1_60[i])
							{
								break;
							}

						}
						
						Count_Node++;
						hd_Row3[i]=hd_Row3[i]+ind1-1;

					}
					else if (hd_Row1_60[i]>-25.35&&hd_Row1_60[i]<=-10)
					{
						hs_Row1_60[1]=hs_Row1_60[1]+1;
						for (i_sc=ind1;i_sc<=ind2;i_sc++)
						{

							if (pInDataX[i_sc]<hd_Row1_60[i])
							{
								hd_Row3[i]++;
							}
							else if (pInDataX[i_sc]==hd_Row1_60[i])
							{
								hd_Row3[i]++;
								break;
							}
							else if (pInDataX[i_sc]>hd_Row1_60[i])
							{
								break;
							}

						}
						
						Count_Node++;
						hd_Row3[i]=hd_Row3[i]+ind1-1;
					}
					else if (hd_Row1_60[i]>-10&&hd_Row1_60[i]<=0)
					{
						hs_Row1_60[2]=hs_Row1_60[2]+1;
						for (i_sc=ind1;i_sc<=ind2;i_sc++)
						{

							if (pInDataX[i_sc]<hd_Row1_60[i])
							{
								hd_Row3[i]++;
							}
							else if (pInDataX[i_sc]==hd_Row1_60[i])
							{
								hd_Row3[i]++;
								break;
							}
							else if (pInDataX[i_sc]>hd_Row1_60[i])
							{
								break;
							}

						}
						
						Count_Node++;
						hd_Row3[i]=hd_Row3[i]+ind1-1;
					}
					else if (hd_Row1_60[i]>0&&hd_Row1_60[i]<=10)
					{
						hs_Row1_60[3]=hs_Row1_60[3]+1;
						for (i_sc=ind1;i_sc<=ind2;i_sc++)
						{

							if (pInDataX[i_sc]<hd_Row1_60[i])
							{
								hd_Row3[i]++;
							}
							else if (pInDataX[i_sc]==hd_Row1_60[i])
							{
								hd_Row3[i]++;
								break;
							}
							else if (pInDataX[i_sc]>hd_Row1_60[i])
							{
								break;
							}

						}
					
						Count_Node++;
						hd_Row3[i]=hd_Row3[i]+ind1-1;
					}
					else if (hd_Row1_60[i]>10&&hd_Row1_60[i]<=25.35)
					{
						hs_Row1_60[4]=hs_Row1_60[4]+1;
						for (i_sc=ind1;i_sc<=ind2;i_sc++)
						{

							if (pInDataX[i_sc]<hd_Row1_60[i])
							{
								hd_Row3[i]++;
							}
							else if (pInDataX[i_sc]==hd_Row1_60[i])
							{
								hd_Row3[i]++;
								break;
							}
							else if (pInDataX[i_sc]>hd_Row1_60[i])
							{
								break;
							}

						}
						
						Count_Node++;
						hd_Row3[i]=hd_Row3[i]+ind1-1;
					}
					else
					{
						hs_Row1_60[5]=hs_Row1_60[5]+1;
						for (i_sc=ind1;i_sc<=ind2;i_sc++)
						{

							if (pInDataX[i_sc]<hd_Row1_60[i])
							{
								hd_Row3[i]++;
							}
							else if (pInDataX[i_sc]==hd_Row1_60[i])
							{
								hd_Row3[i]++;
								break;
							}
							else if (pInDataX[i_sc]>hd_Row1_60[i])
							{
								break;
							}

						}
						
						Count_Node++;
						hd_Row3[i]=hd_Row3[i]+ind1-1;
					}
				}			
			for(int i=0;i<Num_Node;i++)
			{
				double x_temp[2]={pInDataX[hd_Row3[i]],pInDataX[hd_Row3[i]+1]};
				double y_temp[2]={pInDataY[hd_Row3[i]],pInDataY[hd_Row3[i]+1]};

				hdy[i]=Func_CZ(hd_Row1_60[i],x_temp,y_temp);
			}
			//hd_Row4��ʾӳ�䵽SC��ʱ��SC���Ƿ���BZ���·�(Yֵ������·�)�����·�Ϊ0
			//int hd_Row4[Num_Node]={0};
			for (int hdRow4Finder=0;hdRow4Finder<Num_Node;hdRow4Finder++)
			{
				if (hdy[hdRow4Finder]>=hd_Row2_60[hdRow4Finder])
				{
					hd_Row4[hdRow4Finder]=0;
				} 
				else
				{
					hd_Row4[hdRow4Finder]=1;
				}
			}

			//����ind1��ind2�ķ�Χ
			ind1 =0;
			ind2=R400_Start-5;

			//��ȡ����澫��
			//int Count_BZAng=0;
			index_xml_bz=0;
			Count_Node=0;
			Count_Zero=CalculatingHdm.Index_Zero-1;//C++����ż�һ
			int Sum_Row1_60=0;
			for (int i=0;i<indhd;i++)
			{
				HDMJD[i]=0;	
				if(i<6)
				{
					Sum_Row1_60+=hs_Row1_60[i];
					if(indhd>=Sum_Row1_60)
					{
						hs_Row1_60[i]=0;
					}
					else
					{
						hs_Row1_60[i]=Sum_Row1_60-indhd;
					}
				}
				Count_Node++;//��ʼλ�������ǰ�ƶ�indhd��(�൱��Count_Node=indhd;)
			}
			for (Count_Duan=0;Count_Duan< Num_Duan_60;Count_Duan++)
			{
				if (hs_Row1_60[Count_Duan]!=0)//�ö����б�׼�㣬�����ѭ��
				{
					for (int i=0;i<hs_Row1_60[Count_Duan];i++)
					{
						if(Count_Node<Num_Node)
						{
						Ang_BZ[Count_Node]=atan((hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]))*180/Pi;
						if(Ang_BZ[Count_Node]<0)
							Ang_BZ[Count_Node]=Ang_BZ[Count_Node]+180;
						ud=hd_Row4[Count_Node];
						if (Count_Node==0)
						{
							df=ind1;
						}
						else
						{
							df=loc[Count_Node-1];
						}
						if (Count_Duan<3)//��
						{
							if (ud ==1)//����
							{								
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											/*HDMJD[Count_Node]=(FenZi1-FenZi2)/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=0;
											HDMJD[Count_Node]=0;
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											HDMJD[Count_Node]=-sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}

									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];		
										HDMJD[Count_Node]=0;
									}
								}
								/*Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];*/
								//Dist_Hdm_Node[index_xml_bz]=HDMJD[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
							else//����
							{
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=0;
											HDMJD[Count_Node]=0;
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											HDMJD[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}
									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];		
										HDMJD[Count_Node]=0;
									}
								}
								/*Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];*/
								//Dist_Hdm_Node[index_xml_bz]=HDMJD[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
						}
						else if (Count_Duan>=3&&Count_Duan<6)
						{
							if (ud==1)//����
							{
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi+180;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi+180;

									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=0;
											HDMJD[Count_Node]=0;
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											HDMJD[Count_Node]=-sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}
									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];		
										HDMJD[Count_Node]=0;
									}
								}
								/*Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];*/
								//Dist_Hdm_Node[index_xml_bz]=HDMJD[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
							else//����
							{
								if (Count_Node==0)
								{
									df=ind1;
								}
								else
								{
									df=loc[Count_Node-1];
								}
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=0;
											HDMJD[Count_Node]=0;
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											HDMJD[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}
									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];		
										HDMJD[Count_Node]=0;
									}
								}
								/*Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];*/
								//Dist_Hdm_Node[index_xml_bz]=HDMJD[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
						}
						} 
					


					}
				}
			}	
			//�洢����ֵ
			if (bLOrR==bFlagTrack_L)//����false����ʾ���
			{
				for (int i=0;i<Num_Node;i++)
				{
					HdmNode_XL[i]=SCBZ_HDM_X[i];
					HdmNode_YL[i]=SCBZ_HDM_Y[i];
					Dist_Hdmjd_L[i]=HDMJD[i];
				}
			}
			else if (bLOrR==bFlagTrack_R)
			{
				for (int i=0;i<Num_Node;i++)
				{
					HdmNode_XR[i]=SCBZ_HDM_X[i];
					HdmNode_YR[i]=SCBZ_HDM_Y[i];
					Dist_Hdmjd_R[i]=HDMJD[i];
				}
			}
		}
		
		break;
		}
	}
	return Pos_Rec_Aln_Y-CalculatingHdm.Pos_BZ_Aln_Y;
	
}

////
double FuncCalculatingHdm_Xml(CalHdmStruct &CalculatingHdm,bool bDuiQi,bool bLOrR,int &CalPointNum,double* pInDataX,double* pInDataY,int R400_Start,double* pScbzPoint_X,double* pScbzPoint_Y)
{	
	int Count_Node=0;//������ʱ��23�������ű���
	int	Count_Range_Ang=0;//������ʱ��ʵ���������Ա�׼��Ϊ���ĵ����
	int Count_Zero;//�������λ��
	//int ind1=-1,ind2=0; 
	int ind1=0,ind2=0,indhd=0;
	int Count_Duan=0;//�������
	int i_sc;
	int index_xml_bz =0;					//��׼ϳĥ�����,��ʼ��Ϊ0
	double Pos_Rec_Aln_Y=0;
	double Ang_L=0,Ang_R=0,Para_Node_M=0,Para_Node_N=0;

	switch(CalculatingHdm.iTrackSel)
	{
	case 0:
		{

		
		int hs_Row1_50[Num_Duan_50]={0};//4��Բ��ÿ��Բ���ϱ�׼��ĸ���	
		const double hs_Row2_50[6]={Hdm_50.Pos_BZ_R13L_X,Hdm_50.Pos_BZ_R80L_X,Hdm_50.Pos_BZ_R300L_X,
			Hdm_50.Pos_BZ_R300R_X,Hdm_50.Pos_BZ_R80R_X,Hdm_50.Pos_BZ_R13R_X};
		const double hs_Row3_50[6]={Hdm_50.Pos_BZ_R13_Y,Hdm_50.Pos_BZ_R80_Y,Hdm_50.Pos_BZ_R300_Y,
			Hdm_50.Pos_BZ_R300_Y,Hdm_50.Pos_BZ_R80_Y,Hdm_50.Pos_BZ_R13_Y};
		double hd_Row1_50[Num_Node_50]={0},hd_Row2_50[Num_Node_50]={0};//50��׼������
		for (int i=0;i<Num_Node_50;i++)
		{
			hd_Row1_50[i]=Pos_BZ_X_50[i];
			hd_Row2_50[i]=Pos_BZ_Y_50[i];
		}
		int hd_Row4[Num_Node_50]={0};//ʵ���ͱ�׼�����λ��
		int hd_Row3[Num_Node_50]={0};//��׼������һ����
		int ud,df,loc[Num_Node_50]={0};
		double hdy[Num_Node_50]={0};//��ֵ���	
		double Ang_BZ[Num_Node_50]={0};
		double SCBZ_HDM_X[Num_Node_50]={0},SCBZ_HDM_Y[Num_Node_50]={0};
		double HDMJD[Num_Node_50]={0};
		//���indhd
		for (int i=0;i<SensorMaxPoint;i++)
		{
			if (Pos_BZ_X_50[i]<pInDataX[0]&&Pos_BZ_X_50[i+1]>pInDataX[0])
			{
				indhd++;
			} 
			else
			{
				break;
			}
		}
		//�ҳ�С�ڵ���Pos_BZ_Y_60[22]����������Ǹ��������
		for (int ind2Finder =0;ind2Finder<SensorMaxPoint;ind2Finder++)
		{
			if (pInDataY[ind2Finder] <Pos_BZ_Y_50[Num_Node_50-1])
			{
				ind2++;
			} 
			else if (pInDataY[ind2Finder] ==Pos_BZ_Y_50[Num_Node_50-1])
			{
				ind2++;
				break;
			}
			else if (pInDataY[ind2Finder] >Pos_BZ_Y_50[Num_Node_50-1])
			{
				break;
			}							
		}
		if (!bDuiQi)
		{
			//�ֶ�
			for (int i=0;i<Num_Node_50;i++)
			{
				if (hd_Row1_50[i]<=-23)
				{
					hs_Row1_50[0]=hs_Row1_50[0]+1;

					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_50[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_50[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_50[i])
						{
							break;
						}

					}

					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				} 
				else if(hd_Row1_50[i]>-23&&hd_Row1_50[i]<=0)
				{
					hs_Row1_50[1]=hs_Row1_50[1]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_50[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_50[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_50[i])
						{
							break;
						}

					}

					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else if (hd_Row1_50[i]>0&&hd_Row1_50[i]<=23)
				{
					hs_Row1_50[2]=hs_Row1_50[2]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_50[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_50[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_50[i])
						{
							break;
						}

					}

					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else
				{
					hs_Row1_50[3]=hs_Row1_50[3]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_50[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_50[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_50[i])
						{
							break;
						}

					}

					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
			}
			for(int i=0;i<Num_Node_50;i++)
			{
				double x_temp[2]={pInDataX[hd_Row3[i]],pInDataX[hd_Row3[i]+1]};
				double y_temp[2]={pInDataY[hd_Row3[i]],pInDataY[hd_Row3[i]+1]};

				hdy[i]=Func_CZ(hd_Row1_50[i],x_temp,y_temp);
			}
			for (int hdRow4Finder=0;hdRow4Finder<Num_Node_50;hdRow4Finder++)
			{
				if (hdy[hdRow4Finder]>=hd_Row2_50[hdRow4Finder])
				{
					hd_Row4[hdRow4Finder]=0;
				} 
				else
				{
					hd_Row4[hdRow4Finder]=1;
				}
			}
			ind1 =0;
			ind2=R400_Start-5;
			index_xml_bz=0;
			Count_Node=0;
			int Sum_Row1_50=0;
			for (int i=0;i<indhd;i++)
			{
				SCBZ_HDM_X[i]=hd_Row1_50[i];
				SCBZ_HDM_Y[i]=hd_Row2_50[i];
				if(i<Num_Duan_50)
				{
					Sum_Row1_50+=hs_Row1_50[i];
					if(indhd>=Sum_Row1_50)
					{
						hs_Row1_50[i]=0;
					}
					else
					{
						hs_Row1_50[i]=Sum_Row1_50-indhd;
					}
				}				
				Count_Node++;//��ʼλ�������ǰ�ƶ�indhd��(�൱��Count_Node=indhd;)
			}
			Count_Zero=CalculatingHdm.Index_Zero-1;//C++����ż�һ			
			for (Count_Duan=0;Count_Duan< Num_Duan_50;Count_Duan++)
			{
				if (hs_Row1_50[Count_Duan]!=0)
				{
					for (int i=0;i<hs_Row1_50[Count_Duan];i++)
					{
						if(Count_Node<Num_Node_50)
						{
							Ang_BZ[Count_Node]=atan((hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]))*180/Pi;
							if(Ang_BZ[Count_Node]<0)
								Ang_BZ[Count_Node]=Ang_BZ[Count_Node]+180;
							ud=hd_Row4[Count_Node];
							if (Count_Node==0)
							{
								df=ind1;
							}
							else
							{
								df=loc[Count_Node-1];
							}
							if (Count_Duan<2)//��
							{
								if (ud ==1)//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									    {
											Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
											Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
											if(Ang_L<0)
												Ang_L=Ang_L+180;
											if(Ang_R<0)
												Ang_R=Ang_R+180;
											if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
											{
												loc[Count_Node]=Count_Range_Ang;	
												if (Count_Node==Count_Zero)
												{											
													SCBZ_HDM_X[Count_Node]=0;
													SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
													break;
												}
												else
												{
													Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
													Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

													SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
													SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
													break;

												}

											}
											else
											{
												SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
												SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];										
											}
										}
									Count_Node++;
								}
								else//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									{
										Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{											
												SCBZ_HDM_X[Count_Node]=0;
												SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

												SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
												break;

											}

										}
										else
										{
											SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
											SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];										
										}
									}
									Count_Node++;
								}
							}
							else if (Count_Duan>=2&&Count_Duan<4)//��
							{
								if (ud ==1)//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									{
										Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{											
												SCBZ_HDM_X[Count_Node]=0;
												SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

												SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
												break;

											}

										}
										else
										{
											SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
											SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];										
										}
									}
									Count_Node++;
								}
								else//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									{
										Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{											
												SCBZ_HDM_X[Count_Node]=0;
												SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

												SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
												break;

											}

										}
										else
										{
											SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
											SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];										
										}
									}
									Count_Node++;
								}
							}
						}
					}
				}
			}
			if (bLOrR==bFlagTrack_L)//����false����ʾ���
			{
				for (int i=0;i<Num_Node_50;i++)
				{
					HdmScbz_XL_50[i]=SCBZ_HDM_X[i];
					HdmScbz_YL_50[i]=SCBZ_HDM_Y[i];
				}
			}
			else if (bLOrR==bFlagTrack_R)
			{
				for (int i=0;i<Num_Node_50;i++)
				{
					HdmScbz_XR_50[i]=SCBZ_HDM_X[i];
					HdmScbz_YR_50[i]=SCBZ_HDM_Y[i];
				}
			}
		}

		if (bDuiQi)
		{
			for(int i=0;i<CalPointNum-1;i++)
			{
				if((pInDataX[i]<=CalculatingHdm.Pos_BZ_Aln_X)&&(pInDataX[i+1]>=CalculatingHdm.Pos_BZ_Aln_X))
				{
					Pos_Rec_Aln_Y=(pInDataY[i+1]-pInDataY[i])*(CalculatingHdm.Pos_BZ_Aln_X-pInDataX[i])/(pInDataX[i+1]-pInDataX[i])+pInDataY[i];
					break;
				}
			}
			for(int i=0;i<CalPointNum;i++)
			{
				pInDataY[i]=pInDataY[i]-(Pos_Rec_Aln_Y-CalculatingHdm.Pos_BZ_Aln_Y);
			}
			//ind1��ind2��ֵ��ind2����
			ind1=0;
			ind2=R400_Start-5;
			index_xml_bz=0;
			Count_Node=0;
			int Sum_Row1_50=0;
			for (int i=0;i<indhd;i++)
			{
				SCBZ_HDM_X[i]=hd_Row1_50[i];
				SCBZ_HDM_Y[i]=hd_Row2_50[i];
				if(i<Num_Duan_50)
				{
					Sum_Row1_50+=hs_Row1_50[i];
					if(indhd>=Sum_Row1_50)
					{
						hs_Row1_50[i]=0;
					}
					else
					{
						hs_Row1_50[i]=Sum_Row1_50-indhd;
					}
				}				
				Count_Node++;//��ʼλ�������ǰ�ƶ�indhd��(�൱��Count_Node=indhd;)
			}
			Count_Zero=CalculatingHdm.Index_Zero-1;//C++����ż�һ		

			for (Count_Duan=0;Count_Duan< Num_Duan_50;Count_Duan++)
			{
				if (hs_Row1_50[Count_Duan]!=0)
				{
					for (int i=0;i<hs_Row1_50[Count_Duan];i++)
					{
						if(Count_Node<Num_Node_50)
						{
							Ang_BZ[Count_Node]=atan((hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]))*180/Pi;
							if(Ang_BZ[Count_Node]<0)
								Ang_BZ[Count_Node]=Ang_BZ[Count_Node]+180;
							ud=hd_Row4[Count_Node];
							if (Count_Node==0)
							{
								df=ind1;
							}
							else
							{
								df=loc[Count_Node-1];
							}
							if (Count_Duan<2)//��
							{
								if (ud ==1)//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									{
										Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{											
												SCBZ_HDM_X[Count_Node]=0;
												SCBZ_HDM_Y[Count_Node]=0;
												HDMJD[Count_Node]=0;
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

												SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
												HDMJD[Count_Node]=-sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node]));


												break;

											}

										}
										else
										{
											SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
											SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];	
											HDMJD[Count_Node]=0;
										}
									}
									Count_Node++;
								}
								else//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									{
										Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{											
												SCBZ_HDM_X[Count_Node]=0;
												SCBZ_HDM_Y[Count_Node]=0;
												HDMJD[Count_Node]=0;
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

												SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
												HDMJD[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node]));
												break;

											}

										}
										else
										{
											SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
											SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];	
											HDMJD[Count_Node]=0;
										}
									}
									Count_Node++;
								}
							}
							else if (Count_Duan>=2&&Count_Duan<4)//��
							{
								if (ud ==1)//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									{
										Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{											
												SCBZ_HDM_X[Count_Node]=0;
												SCBZ_HDM_Y[Count_Node]=0;
												HDMJD[Count_Node]=0;
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

												SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
												HDMJD[Count_Node]=-sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node]));
												break;

											}

										}
										else
										{
											SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
											SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];		
											HDMJD[Count_Node]=0;
										}
									}
									Count_Node++;
								}
								else//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)									
									{
										Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{											
												SCBZ_HDM_X[Count_Node]=0;
												SCBZ_HDM_Y[Count_Node]=0;
												HDMJD[Count_Node]=0;
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

												SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);											
												HDMJD[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_50[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_50[Count_Node]));
												break;

											}

										}
										else
										{
											SCBZ_HDM_X[Count_Node]=hd_Row1_50[Count_Node];
											SCBZ_HDM_Y[Count_Node]=hd_Row2_50[Count_Node];
											HDMJD[Count_Node]=0;
										}
									}
									Count_Node++;
								}
							}
						}
					}
				}
			}

		}
		if (bLOrR==bFlagTrack_L)//����false����ʾ���
		{
			for (int i=0;i<Num_Node_50;i++)
			{
				HdmNode_XL_50[i]=SCBZ_HDM_X[i];
				HdmNode_YL_50[i]=SCBZ_HDM_Y[i];
				Dist_Hdmjd_L_50[i]=HDMJD[i];
			}
		}
		else if (bLOrR==bFlagTrack_R)
		{
			for (int i=0;i<Num_Node_50;i++)
			{
				HdmNode_XR_50[i]=SCBZ_HDM_X[i];
				HdmNode_YR_50[i]=SCBZ_HDM_Y[i];
				Dist_Hdmjd_R_50[i]=HDMJD[i];
			}
		}
		break;
		}
	case 1:
		{

		
		//------------60����------------//
		//60Բ������
		int hs_Row1_60[6]={0};//6��Բ��ÿ��Բ���ϱ�׼��ĸ���	
		const double hs_Row2_60[6]={Hdm_60.Pos_BZ_R13L_X,Hdm_60.Pos_BZ_R80L_X,Hdm_60.Pos_BZ_R300L_X,
			Hdm_60.Pos_BZ_R300R_X,Hdm_60.Pos_BZ_R80R_X,Hdm_60.Pos_BZ_R13R_X};
		const double hs_Row3_60[6]={Hdm_60.Pos_BZ_R13_Y,Hdm_60.Pos_BZ_R80_Y,Hdm_60.Pos_BZ_R300_Y,
			Hdm_60.Pos_BZ_R300_Y,Hdm_60.Pos_BZ_R80_Y,Hdm_60.Pos_BZ_R13_Y};
		double hd_Row1_60[Num_Node]={0},hd_Row2_60[Num_Node]={0};//60��׼������
		for (int i=0;i<Num_Node;i++)
		{
			hd_Row1_60[i]=pScbzPoint_X[i];
			hd_Row2_60[i]=pScbzPoint_Y[i];
		}
		int hd_Row4[Num_Node]={0};//ʵ���ͱ�׼�����λ��
		int hd_Row3[Num_Node]={0};//��׼������һ����
		int ud,df,loc[Num_Node]={0};
		double hdy[Num_Node]={0};//��ֵ���	
		double Ang_BZ[Num_Node]={0};
		double SCBZ_HDM_X[Num_Node]={0},SCBZ_HDM_Y[Num_Node]={0};
		double HDMJD[Num_Node]={0};		
		
		//���indhd
		for (int i=0;i<SensorMaxPoint;i++)
		{
			if (Pos_BZ_X_60[i]<pInDataX[0]&&Pos_BZ_X_60[i+1]>pInDataX[0])
			{
				indhd++;
			} 
			else
			{
				break;
			}
		}
		
		//�ҳ�С�ڵ���Pos_BZ_Y_60[22]����������Ǹ��������
		for (int ind2Finder =0;ind2Finder<SensorMaxPoint;ind2Finder++)
		{
			if (pInDataY[ind2Finder] <Pos_BZ_Y_60[Num_Node-1])
			{
				ind2++;
			} 
			else if (pInDataY[ind2Finder] ==Pos_BZ_Y_60[Num_Node-1])
			{
				ind2++;
				break;
			}
			else if (pInDataY[ind2Finder] >Pos_BZ_Y_60[Num_Node-1])
			{
				break;
			}							
		}
		if (!bDuiQi)
		{
			for (int i=0;i<Num_Node;i++)
			{
				if(hd_Row1_60[i]<=-25.35)
				{
					hs_Row1_60[0]=hs_Row1_60[0]+1;

					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;

				}
				else if (hd_Row1_60[i]>-25.35&&hd_Row1_60[i]<=-10)
				{
					hs_Row1_60[1]=hs_Row1_60[1]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else if (hd_Row1_60[i]>-10&&hd_Row1_60[i]<=0)
				{
					hs_Row1_60[2]=hs_Row1_60[2]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else if (hd_Row1_60[i]>0&&hd_Row1_60[i]<=10)
				{
					hs_Row1_60[3]=hs_Row1_60[3]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else if (hd_Row1_60[i]>10&&hd_Row1_60[i]<=25.35)
				{
					hs_Row1_60[4]=hs_Row1_60[4]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else
				{
					hs_Row1_60[5]=hs_Row1_60[5]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
			}
			

			for(int i=0;i<Num_Node;i++)
			{
				double x_temp[2]={pInDataX[hd_Row3[i]],pInDataX[hd_Row3[i]+1]};
				double y_temp[2]={pInDataY[hd_Row3[i]],pInDataY[hd_Row3[i]+1]};

				hdy[i]=Func_CZ(hd_Row1_60[i],x_temp,y_temp);
			}

			for (int hdRow4Finder=0;hdRow4Finder<Num_Node;hdRow4Finder++)
			{
				if (hdy[hdRow4Finder]>=hd_Row2_60[hdRow4Finder])
				{
					hd_Row4[hdRow4Finder]=0;
				} 
				else
				{
					hd_Row4[hdRow4Finder]=1;
				}
			}

			ind1 =0;
			ind2=R400_Start-5;

			//��ȡ����澫��
			//int Count_BZAng=0;
			index_xml_bz=0;
			Count_Node=0;
			int Sum_Row1_60=0;
			for (int i=0;i<indhd;i++)
			{
				SCBZ_HDM_X[i]=hd_Row1_60[i];
				SCBZ_HDM_Y[i]=hd_Row2_60[i];
				if(i<6)
				{
					Sum_Row1_60+=hs_Row1_60[i];
					if(indhd>=Sum_Row1_60)
					{
						hs_Row1_60[i]=0;
					}
					else
					{
						hs_Row1_60[i]=Sum_Row1_60-indhd;
					}
				}				
				Count_Node++;//��ʼλ�������ǰ�ƶ�indhd��(�൱��Count_Node=indhd;)
			}
			Count_Zero=CalculatingHdm.Index_Zero-1;//C++����ż�һ
			for (Count_Duan=0;Count_Duan< Num_Duan_60;Count_Duan++)
			{
				if (hs_Row1_60[Count_Duan]!=0)//�ö����б�׼�㣬�����ѭ��
				{
					for (int i=0;i<hs_Row1_60[Count_Duan];i++)
					{
						if(Count_Node<Num_Node)
						{
						Ang_BZ[Count_Node]=atan((hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]))*180/Pi;
						if(Ang_BZ[Count_Node]<0)
							Ang_BZ[Count_Node]=Ang_BZ[Count_Node]+180;
						ud=hd_Row4[Count_Node];
						//df�ĳ�ʼ������������������ж�����ǰ�棬����Ĭ�ϵ�һ����Ϊ���Ϸ�
						if (Count_Node==0)
						{
							df=ind1;
						}
						else
						{
							df=loc[Count_Node-1];
						}
						if (Count_Duan<3)//��
						{
							if (ud ==1)//����
							{
								
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											/*Dist_Node[Count_Node]=(FenZi1-FenZi2)/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											//Dist_Node[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}

									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];										
									}
								}
								//Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								//Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];
								////Dist_Hdm_Node[index_xml_bz]=Dist_Node[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
							else//����
							{
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											//Dist_Node[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}
									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];										
									}
								}
								//Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								//Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];
								////Dist_Hdm_Node[index_xml_bz]=Dist_Node[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
						}
						else if (Count_Duan>=3&&Count_Duan<6)
						{
							if (ud==1)//����
							{
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi+180;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi+180;

									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											//Dist_Node[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}
									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];										
									}
								}
								//Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								//Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];
								////Dist_Hdm_Node[index_xml_bz]=Dist_Node[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
							else//����
							{
								if (Count_Node==0)
								{
									df=ind1;
								}
								else
								{
									df=loc[Count_Node-1];
								}
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=hdy[Count_Node];
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											//Dist_Node[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}
									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];										
									}
								}
									
								//Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								//Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];
								////Dist_Hdm_Node[index_xml_bz]=Dist_Node[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
						}
						} 



					}
				}
			}
			//�洢ʵ���׼��
			if (bLOrR==bFlagTrack_L)//����false����ʾ���
			{
				for (int i=0;i<Num_Node;i++)
				{
					HdmScbz_XL[i]=SCBZ_HDM_X[i];
					HdmScbz_YL[i]=SCBZ_HDM_Y[i];
				}
			}
			else if (bLOrR==bFlagTrack_R)
			{
				for (int i=0;i<Num_Node;i++)
				{
					HdmScbz_XR[i]=SCBZ_HDM_X[i];
					HdmScbz_YR[i]=SCBZ_HDM_Y[i];
				}
			}

		}
		if (bDuiQi)
		{
			//�ҵ�0mm������
			for(int i=0;i<CalPointNum-1;i++)
			{
				if((pInDataX[i]<=CalculatingHdm.Pos_BZ_Aln_X)&&(pInDataX[i+1]>=CalculatingHdm.Pos_BZ_Aln_X))
				{
					Pos_Rec_Aln_Y=(pInDataY[i+1]-pInDataY[i])*(CalculatingHdm.Pos_BZ_Aln_X-pInDataX[i])/(pInDataX[i+1]-pInDataX[i])+pInDataY[i];
					break;
				}
			}
			/*double* kk = new double[400];
			kk = pInDataX;*/
			for(int i=0;i<CalPointNum;i++)
			{
				pInDataY[i]=pInDataY[i]-(Pos_Rec_Aln_Y-CalculatingHdm.Pos_BZ_Aln_Y);
			}
			//ind1��ind2��ֵ��ind2����
			ind1=0;
			
			//�ֶ�
			for (int i=0;i<Num_Node;i++)
				{
					if(hd_Row1_60[i]<=-25.35)
					{
						hs_Row1_60[0]=hs_Row1_60[0]+1;

						for (i_sc=ind1;i_sc<=ind2;i_sc++)
						{

							if (pInDataX[i_sc]<hd_Row1_60[i])
							{
								hd_Row3[i]++;
							}
							else if (pInDataX[i_sc]==hd_Row1_60[i])
							{
								hd_Row3[i]++;
								break;
							}
							else if (pInDataX[i_sc]>hd_Row1_60[i])
							{
								break;
							}

						}
						
						Count_Node++;
						hd_Row3[i]=hd_Row3[i]+ind1-1;

					}
					else if (hd_Row1_60[i]>-25.35&&hd_Row1_60[i]<=-10)
					{
						hs_Row1_60[1]=hs_Row1_60[1]+1;
						for (i_sc=ind1;i_sc<=ind2;i_sc++)
						{

							if (pInDataX[i_sc]<hd_Row1_60[i])
							{
								hd_Row3[i]++;
							}
							else if (pInDataX[i_sc]==hd_Row1_60[i])
							{
								hd_Row3[i]++;
								break;
							}
							else if (pInDataX[i_sc]>hd_Row1_60[i])
							{
								break;
							}

						}
						
						Count_Node++;
						hd_Row3[i]=hd_Row3[i]+ind1-1;
					}
					else if (hd_Row1_60[i]>-10&&hd_Row1_60[i]<=0)
					{
						hs_Row1_60[2]=hs_Row1_60[2]+1;
						for (i_sc=ind1;i_sc<=ind2;i_sc++)
						{

							if (pInDataX[i_sc]<hd_Row1_60[i])
							{
								hd_Row3[i]++;
							}
							else if (pInDataX[i_sc]==hd_Row1_60[i])
							{
								hd_Row3[i]++;
								break;
							}
							else if (pInDataX[i_sc]>hd_Row1_60[i])
							{
								break;
							}

						}
						
						Count_Node++;
						hd_Row3[i]=hd_Row3[i]+ind1-1;
					}
					else if (hd_Row1_60[i]>0&&hd_Row1_60[i]<=10)
					{
						hs_Row1_60[3]=hs_Row1_60[3]+1;
						for (i_sc=ind1;i_sc<=ind2;i_sc++)
						{

							if (pInDataX[i_sc]<hd_Row1_60[i])
							{
								hd_Row3[i]++;
							}
							else if (pInDataX[i_sc]==hd_Row1_60[i])
							{
								hd_Row3[i]++;
								break;
							}
							else if (pInDataX[i_sc]>hd_Row1_60[i])
							{
								break;
							}

						}
					
						Count_Node++;
						hd_Row3[i]=hd_Row3[i]+ind1-1;
					}
					else if (hd_Row1_60[i]>10&&hd_Row1_60[i]<=25.35)
					{
						hs_Row1_60[4]=hs_Row1_60[4]+1;
						for (i_sc=ind1;i_sc<=ind2;i_sc++)
						{

							if (pInDataX[i_sc]<hd_Row1_60[i])
							{
								hd_Row3[i]++;
							}
							else if (pInDataX[i_sc]==hd_Row1_60[i])
							{
								hd_Row3[i]++;
								break;
							}
							else if (pInDataX[i_sc]>hd_Row1_60[i])
							{
								break;
							}

						}
						
						Count_Node++;
						hd_Row3[i]=hd_Row3[i]+ind1-1;
					}
					else
					{
						hs_Row1_60[5]=hs_Row1_60[5]+1;
						for (i_sc=ind1;i_sc<=ind2;i_sc++)
						{

							if (pInDataX[i_sc]<hd_Row1_60[i])
							{
								hd_Row3[i]++;
							}
							else if (pInDataX[i_sc]==hd_Row1_60[i])
							{
								hd_Row3[i]++;
								break;
							}
							else if (pInDataX[i_sc]>hd_Row1_60[i])
							{
								break;
							}

						}
						
						Count_Node++;
						hd_Row3[i]=hd_Row3[i]+ind1-1;
					}
				}			
			for(int i=0;i<Num_Node;i++)
			{
				double x_temp[2]={pInDataX[hd_Row3[i]],pInDataX[hd_Row3[i]+1]};
				double y_temp[2]={pInDataY[hd_Row3[i]],pInDataY[hd_Row3[i]+1]};

				hdy[i]=Func_CZ(hd_Row1_60[i],x_temp,y_temp);
			}
			//hd_Row4��ʾӳ�䵽SC��ʱ��SC���Ƿ���BZ���·�(Yֵ������·�)�����·�Ϊ0
			//int hd_Row4[Num_Node]={0};
			for (int hdRow4Finder=0;hdRow4Finder<Num_Node;hdRow4Finder++)
			{
				if (hdy[hdRow4Finder]>=hd_Row2_60[hdRow4Finder])
				{
					hd_Row4[hdRow4Finder]=0;
				} 
				else
				{
					hd_Row4[hdRow4Finder]=1;
				}
			}

			//����ind1��ind2�ķ�Χ
			ind1 =0;
			ind2=R400_Start-5;

			//��ȡ����澫��
			//int Count_BZAng=0;
			index_xml_bz=0;
			Count_Node=0;
			Count_Zero=CalculatingHdm.Index_Zero-1;//C++����ż�һ
			int Sum_Row1_60=0;
			for (int i=0;i<indhd;i++)
			{
				HDMJD[i]=0;	
				if(i<6)
				{
					Sum_Row1_60+=hs_Row1_60[i];
					if(indhd>=Sum_Row1_60)
					{
						hs_Row1_60[i]=0;
					}
					else
					{
						hs_Row1_60[i]=Sum_Row1_60-indhd;
					}
				}
				Count_Node++;//��ʼλ�������ǰ�ƶ�indhd��(�൱��Count_Node=indhd;)
			}
			for (Count_Duan=0;Count_Duan< Num_Duan_60;Count_Duan++)
			{
				if (hs_Row1_60[Count_Duan]!=0)//�ö����б�׼�㣬�����ѭ��
				{
					for (int i=0;i<hs_Row1_60[Count_Duan];i++)
					{
						if(Count_Node<Num_Node)
						{
						Ang_BZ[Count_Node]=atan((hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]))*180/Pi;
						if(Ang_BZ[Count_Node]<0)
							Ang_BZ[Count_Node]=Ang_BZ[Count_Node]+180;
						ud=hd_Row4[Count_Node];
						if (Count_Node==0)
						{
							df=ind1;
						}
						else
						{
							df=loc[Count_Node-1];
						}
						if (Count_Duan<3)//��
						{
							if (ud ==1)//����
							{								
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											/*HDMJD[Count_Node]=(FenZi1-FenZi2)/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=0;
											HDMJD[Count_Node]=0;
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											HDMJD[Count_Node]=-sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}

									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];		
										HDMJD[Count_Node]=0;
									}
								}
								/*Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];*/
								//Dist_Hdm_Node[index_xml_bz]=HDMJD[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
							else//����
							{
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=0;
											HDMJD[Count_Node]=0;
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											HDMJD[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}
									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];		
										HDMJD[Count_Node]=0;
									}
								}
								/*Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];*/
								//Dist_Hdm_Node[index_xml_bz]=HDMJD[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
						}
						else if (Count_Duan>=3&&Count_Duan<6)
						{
							if (ud==1)//����
							{
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi+180;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi+180;

									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=0;
											HDMJD[Count_Node]=0;
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											HDMJD[Count_Node]=-sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}
									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];		
										HDMJD[Count_Node]=0;
									}
								}
								/*Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];*/
								//Dist_Hdm_Node[index_xml_bz]=HDMJD[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
							else//����
							{
								if (Count_Node==0)
								{
									df=ind1;
								}
								else
								{
									df=loc[Count_Node-1];
								}
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											/*double FenZi1,FenZi2;
											FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
											FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
											SCBZ_HDM_X[Count_Node]=0;
											SCBZ_HDM_Y[Count_Node]=0;
											HDMJD[Count_Node]=0;
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

											SCBZ_HDM_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_HDM_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_HDM_X[Count_Node]);
											HDMJD[Count_Node]=sqrt((SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_HDM_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_HDM_Y[Count_Node]-hd_Row2_60[Count_Node]));
											break;

										}
									}
									else
									{
										SCBZ_HDM_X[Count_Node]=hd_Row1_60[Count_Node];
										SCBZ_HDM_Y[Count_Node]=hd_Row2_60[Count_Node];		
										HDMJD[Count_Node]=0;
									}
								}
								/*Pos_Xml_X[index_xml_bz]=SCBZ_HDM_X[Count_Node];
								Pos_Xml_Y[index_xml_bz]=SCBZ_HDM_Y[Count_Node];*/
								//Dist_Hdm_Node[index_xml_bz]=HDMJD[Count_Node];
								//index_xml_bz++;	
								Count_Node++;
							}
						}
						} 
					


					}
				}
			}	
			//�洢����ֵ
			if (bLOrR==bFlagTrack_L)//����false����ʾ���
			{
				for (int i=0;i<Num_Node;i++)
				{
					HdmNode_XL[i]=SCBZ_HDM_X[i];
					HdmNode_YL[i]=SCBZ_HDM_Y[i];
					Dist_Hdmjd_L[i]=HDMJD[i];
				}
			}
			else if (bLOrR==bFlagTrack_R)
			{
				for (int i=0;i<Num_Node;i++)
				{
					HdmNode_XR[i]=SCBZ_HDM_X[i];
					HdmNode_YR[i]=SCBZ_HDM_Y[i];
					Dist_Hdmjd_R[i]=HDMJD[i];
				}
			}
		}
		
		break;
		}
	}
	return Pos_Rec_Aln_Y-CalculatingHdm.Pos_BZ_Aln_Y;
	
}


double Func_CZ(double xx,double x[],double y[])//xx  Ϊ��ֵ��  ycΪ��ֵ���
{	
	int i=0;                      //   iֵû�д�����
	double yc;
	yc=(xx-x[i])*(y[i+1]-y[i])/(x[i+1]-x[i])+y[i];
	return yc;
}

LRESULT CHighPrecisionDlg::On2DMsgFunc_L(WPARAM wParam,LPARAM lParam)
{
	int nStNumNode;
	switch(g_TestInfo_L.TrackSel)
	{
	case 0://50��
		{
			nStNumNode=19;
			break;
		}

	case 1://60��
		{
			nStNumNode=23;
			break;
		}
	}
		//�����ɼ���������
		unsigned i(0);
		double* pDataX = NULL;//T����˫�����͵�ָ�����pDateX
		double* pDataY = NULL;
		//�����ڴ�
		if(m_2DThreadParam_L.DataNum>0)
		{
			pDataX = new double[m_2DThreadParam_L.DataNum];//T����Ϊ�̲߳���������ݳ���
			pDataY = new double[m_2DThreadParam_L.DataNum];
			for (i=0;i<(unsigned)m_2DThreadParam_L.DataNum;i++)
			{
				pDataY[i] = -m_2DThreadParam_L.zData[i];//Tת���̲߳����������
				pDataX[i] =m_2DThreadParam_L.xData[i] ;
			}
			m_pLineSerie_LT->ClearSerie();
			m_pLineSerie_LT->AddPoints(pDataX,pDataY,(unsigned)m_2DThreadParam_L.DataNum);
			if (pDataX)
			{
				delete[] pDataX;
				pDataX = NULL;
			}
			if (pDataY)
			{
				delete[] pDataY;
				pDataY = NULL;
			}
		}
		double* pHdmJd=NULL;
		double* pHdmAng=NULL;
		pHdmJd=new double[nStNumNode];
		pHdmAng=new double[nStNumNode];


		
		


		switch(g_TestInfo_L.TrackSel)
		{
		case 0:
			{
				for (int j=0;j<nStNumNode;j++)
				{
					pHdmJd[j]=m_2DThreadParam_L.DistHdm_50[j];
					pHdmAng[j]=Std_Ang_50[j];
				}
				break;
			}
		case 1:
			{
				for (int j=0;j<nStNumNode;j++)
				{
					pHdmJd[j]=m_2DThreadParam_L.DistHdm[j];
					pHdmAng[j]=Std_Ang_60[j];
				}
				break;
			}
		}
		
		unsigned jjCnt(nStNumNode);
		m_pLineSerie_LB->ClearSerie();
		m_pLineSerie_LB->AddPoints(pHdmAng,pHdmJd,jjCnt);
		m_PointSerie_LB->ClearSerie();
		m_PointSerie_LB->AddPoints(pHdmAng,pHdmJd,jjCnt);
		if (pHdmJd)
		{
			delete[] pHdmJd;
			pHdmJd=NULL;
		}
		if (pHdmAng)
		{
			delete[] pHdmAng;
			pHdmAng=NULL;
		}
	
	return 0;
}

LRESULT CHighPrecisionDlg::On2DMsgFunc_R(WPARAM wParam,LPARAM lParam)
{
	int nStNumNode;
	switch(g_TestInfo_R.TrackSel)
	{
	case 0://50��
		{
			nStNumNode=19;
			break;
		}

	case 1://60��
		{
			nStNumNode=23;
			break;
		}
	}

		//�Ҳ໭ͼ��Ϣ��Ӧ����
		//�����ɼ���������
		unsigned i(0);
		double* pDataX = NULL;//T����˫�����͵�ָ�����pDateX
		double* pDataY = NULL;
		//�����ڴ�
		if(m_2DThreadParam_R.DataNum>0)
		{
			pDataX = new double[m_2DThreadParam_R.DataNum];//T����Ϊ�̲߳���������ݳ���
			pDataY = new double[m_2DThreadParam_R.DataNum];
			for (i=0;i<(unsigned)m_2DThreadParam_R.DataNum;i++)
			{
				pDataY[i] = -m_2DThreadParam_R.zData[i];//Tת���̲߳����������
				pDataX[i] =-m_2DThreadParam_R.xData[i] ;
			}
			m_pLineSerie_RT->ClearSerie();
			m_pLineSerie_RT->AddPoints(pDataX,pDataY,(unsigned)m_2DThreadParam_R.DataNum);
			if (pDataX)
			{
				delete[] pDataX;
			}
			if (pDataY)
			{
				delete[] pDataY;
			}
		}

		//�ͷ�ָ��

		//��������
		double* pHdmJd=NULL;
		double* pHdmAng=NULL;
		pHdmJd=new double[nStNumNode];
		pHdmAng=new double[nStNumNode];
		switch(g_TestInfo_R.TrackSel)
		{
		case 0:
			{
				for (int j=0;j<nStNumNode;j++)
				{
					pHdmJd[j]=m_2DThreadParam_R.DistHdm_50[j];
					pHdmAng[j]=Std_Ang_50[j];
				}
				break;
			}
		case 1:
			{
				for (int j=0;j<nStNumNode;j++)
				{
					pHdmJd[j]=m_2DThreadParam_R.DistHdm[j];
					pHdmAng[j]=Std_Ang_60[j];
				}
				break;
			}
		}
		
		unsigned jjCnt(nStNumNode);
		m_pLineSerie_RB->ClearSerie();
		m_pLineSerie_RB->AddPoints(pHdmAng,pHdmJd,jjCnt);
		m_PointSerie_RB->ClearSerie();
		m_PointSerie_RB->AddPoints(pHdmAng,pHdmJd,jjCnt);
		if (pHdmJd)
		{
			delete[] pHdmJd;
			pHdmJd=NULL;
		}
		if (pHdmAng)
		{
			delete[] pHdmAng;
			pHdmAng=NULL;
		}
	
	
	return 0;
}
UINT ThreadStData_R(LPVOID pParam)
{
	bEndSaveFlag_R=false;
	CHighPrecisionDlg *dlg;
	dlg = (CHighPrecisionDlg *)pdlg;

	CString g_strXianbie=g_TestInfo_R.Xianbie;//��ҵ�߱�
	CString g_strRunDirction =g_TestInfo_R.Direction;//��ҵ����
	CString strTrackSel;//����ѡ��

	CFont* f;
	f=new CFont;
	f->CreateFont(11,0,0,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,_T("����"));
	switch(g_TestInfo_R.TrackSel)
	{
	case 0:
		strTrackSel=_T("a");//50��
		break;
	case 1:
		strTrackSel=_T("b");//60��
		break;
	}	
	int g_strFileNameStart=(int)g_TestInfo_R.DistanceStart;//��ҵ���
	CString g_XMQianHou;
	switch(g_TestInfo_R.XM_QianHou)
	{
	case 0:
		g_XMQianHou=_T("ǰ");
		break;
	case 1:
		g_XMQianHou=_T("��");
		break;
	}


	int nStNumNode;
	switch(g_TestInfo_L.TrackSel)
	{
	case 0://50��
		{
			nStNumNode=19;
			break;
		}

	case 1://60��
		{
			nStNumNode=23;
			break;
		}
	}
	double* tempDistHdm=NULL;
	tempDistHdm=new double[nStNumNode];
	double*  tempDistXml=NULL;
	tempDistXml=new double[nStNumNode];
	double*  tempScbzNode_X=NULL;
	tempScbzNode_X=new double[nStNumNode+1];
	double*  tempScbzNode_Y=NULL;
	tempScbzNode_Y=new double[nStNumNode+1];
	double*  tempHdmNode_X=NULL;
	tempHdmNode_X=new double[nStNumNode+1];
	double*  tempHdmNode_Y=NULL;
	tempHdmNode_Y=new double[nStNumNode+1];

	
	//��ʱ����
	/*double tempDistHdm[nStNumNode];
	double tempDistXml[nStNumNode];
	double tempScbzNode_X[nStNumNode+1];
	double tempScbzNode_Y[nStNumNode+1];
	double tempHdmNode_X[nStNumNode+1];
	double tempHdmNode_Y[nStNumNode+1];*/
	double tempOrigin_X[SensorMaxPoint];
	double tempOrigin_Y[SensorMaxPoint];

	CTime TCurrentTime;//��ȡ��ǰʱ��
	int HdmJdNum;//ʵ���׼������潻�����Ŀ
	int ScbzNum;//�洢�ļ�
	int OriginNum;//ԭʼ�����ĸ���
	int XmlJdNum;//ϳĥ������

	//�ļ�����ض���
	//double HdmORXmlDistanceCnt;//����澫��ֵ���������
	int HdmFileNameStart=g_strFileNameStart;//�洢HDM�����ļ������
	int HdmFileNameEnd;//�洢HDM�����ļ����յ�
	int ScbzFileStart=g_strFileNameStart;//�洢ʵ���׼���ļ������
	int	ScbzFileEnd;
	int XmlFileNameStart=g_strFileNameStart;//�洢ϳĥ�������ļ������
	int XmlFileNameEnd;
	CString strTime00="";
	CString strDistHdm="";//txt��һ�еľ������
	CString strScbz="";
	CString strHdmNode="";
	CString strOrigin="";
	CString strDistXml="";

	int GDTempOutlineNum[500];		//��ȡ�洢�̻߳�������ԭʼ�����ĵ���

	CString strFileName2D00;//
	CString strOriginFileName="";//ԭʼ�����ļ���
	CString strDistHdmFileName="";//����澫�ȵ��ļ���
	CString strScbzFileName="";//ʵ���׼���ļ���
	CString strHdmNodeFileName="";//����澫�Ƚ����ļ���
	CString strDistXmlFileName="";//ϳĥ�����ȵ��ļ���
	double DistHdmCnt=g_strFileNameStart;//�Դ洢�ں���澫��txt�е���̵ļ�������㸳ֵΪ��������
	double ScbzCnt=g_strFileNameStart;//�Դ洢��ʵ���׼��txt�е���̵ļ�������㸳ֵΪ��������
	double OriginCnt=g_strFileNameStart;//�洢ԭʼ����
	double DistXmlCnt=g_strFileNameStart;

	int OriginFileStart=g_strFileNameStart;
	int OriginFileEnd;
	//HdmORXmlDistanceCnt=g_sdDistanceCountStart;//���ڴ洢����ֵ����ϳĥ�������
	//HdmORXmlFileNameStart = g_strFileNameStart;//����������λ����Ϊ�ļ����������


	//�ļ���������
	CFile fp2D00DistHdm;//����澫��
	CFile fp2D00Origin;//ԭʼ����
	CFile fp2D00Scbz;//ʵ���׼��
	CFile fp2D00HdmNode;//����澫�Ƚ���
	CFile fp2D00DistXml;//ϳĥ�����Ƚ���
	BOOL  nRes1,nRes2,nRes3;
	//ϳĥǰ
	while(!bEndDealingFlag_R)
	{
		OutLineSection_R.Lock();
		HdmJdNum=LoopBuff.LoopBuffDataLength(&DistHdmJd_LoofBuff_R);
		ScbzNum=LoopBuff.LoopBuffDataLength(&xScbzLoopBuff_R);
		OriginNum=LoopBuff.LoopBuffDataLength(&GetDataNumSt_LoopBuff_R);
		XmlJdNum=LoopBuff.LoopBuffDataLength(&DistXmlJd_LoopBuff_R);
		OutLineSection_R.Unlock();
		//�洢23������ֵ
		if(HdmJdNum>=nStNumNode*Num_StInterval)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();
			HdmFileNameEnd = (int)(HdmFileNameStart+Num_StInterval*Encoder_Distance);
			strDistHdmFileName.Format(_T("%s%s-%06d-%06dM-%s�Һ���澫��%s"),g_strXianbie,g_strRunDirction,HdmFileNameStart,HdmFileNameEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strDistHdmFileName);
			nRes1=fp2D00DistHdm.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1)
			{
				for (int i=0;i<Num_StInterval;i++)
				{
					DistHdmCnt +=Encoder_Distance;				
					OutLineSection_R.Lock();  //�����ٽ���
					LoopBuff.LoopBuffRead(&DistHdmJd_LoofBuff_R,tempDistHdm,nStNumNode);				
					OutLineSection_R.Unlock();
					for (int j=0;j<nStNumNode;j++)
					{
						strDistHdm.Format(_T("%.2f   %011.6f\r\n"),DistHdmCnt,tempDistHdm[j]);	
						fp2D00DistHdm.Write(strDistHdm,strlen(strDistHdm));	
					}
				}
				fp2D00DistHdm.Close();
				HdmFileNameStart = HdmFileNameEnd;
			}
			CString strHnuTemp=strDistHdmFileName+_T("\r\n");
			HnuFileSection.Lock();
			fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			fpHNUFile.SeekToEnd();
			fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			fpHNUFile.Close();
			HnuFileSection.Unlock();
		}
		if (ScbzNum>=(nStNumNode+1)*Num_StInterval)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();
			ScbzFileEnd=(int)(ScbzFileStart+Num_StInterval*Encoder_Distance);//��ȡʵ���׼���ļ����յ�

			strScbzFileName.Format(_T("%s%s-%06d-%06dM-%s��ʵ���׼��%s"),g_strXianbie,g_strRunDirction,ScbzFileStart,ScbzFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strScbzFileName);
			nRes1 = fp2D00Scbz.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);

			strHdmNodeFileName.Format(_T("%s%s-%06d-%06dM-%s�Һ���潻��%s"),g_strXianbie,g_strRunDirction,ScbzFileStart,ScbzFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strHdmNodeFileName);
			nRes2 = fp2D00HdmNode.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1&&nRes2)
			{
				for (int i=0;i<Num_StInterval;i++)
				{
					ScbzCnt+=Encoder_Distance;
					//strTime00.Format("%.2f",ScbzCnt);

					ZeroMemory(tempScbzNode_X,sizeof(tempScbzNode_X));
					ZeroMemory(tempScbzNode_Y,sizeof(tempScbzNode_Y));
					ZeroMemory(tempHdmNode_X,sizeof(tempHdmNode_X));
					ZeroMemory(tempHdmNode_Y,sizeof(tempHdmNode_Y));
					OutLineSection_R.Lock();
					LoopBuff.LoopBuffRead(&xHdmNodeLoopBuff_R,tempHdmNode_X,nStNumNode+1);
					LoopBuff.LoopBuffRead(&zHdmNodeLoopBuff_R,tempHdmNode_Y,nStNumNode+1);
					LoopBuff.LoopBuffRead(&xScbzLoopBuff_R,tempScbzNode_X,nStNumNode+1);
					LoopBuff.LoopBuffRead(&zScbzLoopBuff_R,tempScbzNode_Y,nStNumNode+1);
					OutLineSection_R.Unlock();
					for (int j=0;j<nStNumNode+1;j++)
					{
						strHdmNode.Format(_T("%.2f    %011.6f  %010.6f\r\n"),ScbzCnt,tempHdmNode_X[j],tempHdmNode_Y[j]);
						strScbz.Format(_T("%.2f    %011.6f  %010.6f\r\n"),ScbzCnt,tempScbzNode_X[j],tempScbzNode_Y[j]);
						fp2D00HdmNode.Write(strHdmNode,strlen(strHdmNode));
						fp2D00Scbz.Write(strScbz,strlen(strScbz));

					}				

				}
				fp2D00HdmNode.Close();
				fp2D00Scbz.Close();
				ScbzFileStart = ScbzFileEnd;
			}
			//���ļ���д��HNU�ļ�
			CString strHnuTemp=strScbzFileName+_T("\r\n")/*+strHdmNodeFileName+_T("\r\n")*/;
			HnuFileSection.Lock();
			fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			fpHNUFile.SeekToEnd();
			fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			fpHNUFile.Close();
			HnuFileSection.Unlock();
		}
		if (OriginNum>=500)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();
			OutLineSection_R.Lock();
			LoopBuff.LoopBuffRead(&GetDataNumSt_LoopBuff_R,GDTempOutlineNum,500);
			OutLineSection_R.Unlock();
			OriginFileEnd=(int)(OriginFileStart+Encoder_Distance*500);
			strOriginFileName.Format(_T("%s%s-%06d-%06dM-%s��ԭʼ������%s"),g_strXianbie,g_strRunDirction,OriginFileStart,OriginFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strOriginFileName);
			nRes1=fp2D00Origin.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);			
			if(nRes1)
			{
				for (int i=0;i<500;i++)
				{
					OriginCnt+=Encoder_Distance;
					ZeroMemory(tempOrigin_X,sizeof(tempOrigin_X));
					ZeroMemory(tempOrigin_Y,sizeof(tempOrigin_Y));
					OutLineSection_R.Lock();
					LoopBuff.LoopBuffRead(&xSave_LoopBuff_R,tempOrigin_X,GDTempOutlineNum[i]);
					LoopBuff.LoopBuffRead(&zSave_LoopBuff_R,tempOrigin_Y,GDTempOutlineNum[i]);
					OutLineSection_R.Unlock();
					for (int j=0;j<GDTempOutlineNum[i];j++)
					{
						strOrigin.Format(_T("%.2f    %011.6f  %010.6f\r\n"),OriginCnt,tempOrigin_X[j],tempOrigin_Y[j]);

						fp2D00Origin.Write(strOrigin,strlen(strOrigin));
					}
				}
				fp2D00Origin.Close();
				OriginFileStart = OriginFileEnd;
			}
			//////CString strHnuTemp=strOriginFileName+_T("\r\n");
			//////HnuFileSection.Lock();
			//////fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			//////fpHNUFile.SeekToEnd();
			//////fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			//////fpHNUFile.Close();
			//////HnuFileSection.Unlock();
		}
		//�洢ϳĥ��,�ж���ϳĥǰ����ϳĥ��
		if (g_TestInfo_R.XM_QianHou==1)//1����ϳĥ��
		{
			if (XmlJdNum>nStNumNode*Num_StInterval)//ϳĥ��
			{
				TCurrentTime=TCurrentTime.GetCurrentTime();
				XmlFileNameEnd=(int)(XmlFileNameStart+Num_StInterval*Encoder_Distance);
				strDistXmlFileName.Format(_T("%s%s-%06d-%06dM-%s��ϳĥ������%s"),g_strXianbie,g_strRunDirction,XmlFileNameStart,XmlFileNameEnd,g_XMQianHou,strTrackSel);
				strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strDistXmlFileName);
				nRes3=fp2D00DistXml.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
				if (nRes3)
				{
					for (int i=0;i<Num_StInterval;i++)
					{
						DistXmlCnt+=Encoder_Distance;
						OutLineSection_R.Lock();  //�����ٽ���
						LoopBuff.LoopBuffRead(&DistXmlJd_LoopBuff_R,tempDistXml,nStNumNode);				
						OutLineSection_R.Unlock();
						for (int j=0;j<nStNumNode;j++)
						{
							strDistXml.Format(_T("%.2f   %011.6f\r\n"),DistXmlCnt,tempDistXml[j]);	
							fp2D00DistXml.Write(strDistXml,strlen(strDistXml));	
						}					
					}
					fp2D00DistXml.Close();
					XmlFileNameStart=XmlFileNameEnd;
				} 
				CString strHnuTemp=strDistXmlFileName+_T("\r\n");
				HnuFileSection.Lock();
				fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
				fpHNUFile.SeekToEnd();
				fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
				fpHNUFile.Close();
				HnuFileSection.Unlock();
			}

		}
		
		if(HdmJdNum<nStNumNode*Num_StInterval)
			if(ScbzNum<(nStNumNode+1)*Num_StInterval)
				if(OriginNum<500)
					Sleep(50);

	}
	OutLineSection_R.Lock();
	HdmJdNum=LoopBuff.LoopBuffDataLength(&DistHdmJd_LoofBuff_R);
	ScbzNum=LoopBuff.LoopBuffDataLength(&xScbzLoopBuff_R);
	OriginNum=LoopBuff.LoopBuffDataLength(&GetDataNumSt_LoopBuff_R);
	XmlJdNum=LoopBuff.LoopBuffDataLength(&DistXmlJd_LoopBuff_R);
	OutLineSection_R.Unlock();
	if (HdmJdNum>0)
	{
		for(int i=0;i<HdmJdNum/(nStNumNode*Num_StInterval);i++)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();		
			CString strDist=_T(" ");		
			HdmFileNameEnd = (int)(HdmFileNameStart+Num_StInterval*Encoder_Distance);
			strDistHdmFileName.Format(_T("%s%s-%06d-%06dM-%s�Һ���澫��%s"),g_strXianbie,g_strRunDirction,HdmFileNameStart,HdmFileNameEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strDistHdmFileName);
			nRes1=fp2D00DistHdm.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1)
			{
				for (int i=0;i<Num_StInterval;i++)
				{
					DistHdmCnt +=Encoder_Distance;
					ZeroMemory(tempDistHdm,sizeof(tempDistHdm));				
					OutLineSection_R.Lock();  //�����ٽ���
					LoopBuff.LoopBuffRead(&DistHdmJd_LoofBuff_R,tempDistHdm,nStNumNode);				
					OutLineSection_R.Unlock();
					for (int j=0;j<nStNumNode;j++)
					{
						strDist.Format(_T("%.2f   %011.6f\r\n"),DistHdmCnt,tempDistHdm[j]);	
						fp2D00DistHdm.Write(strDist,strlen(strDist));	
					}	
				}
				fp2D00DistHdm.Close();
				HdmFileNameStart =HdmFileNameEnd;
			}
			//���ļ���д��HNU�ļ�
			CString strHnuTemp=strDistHdmFileName+_T("\r\n");
			HnuFileSection.Lock();
			fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			fpHNUFile.SeekToEnd();
			fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			fpHNUFile.Close();
			HnuFileSection.Unlock();
		}
		OutLineSection_R.Lock();
		HdmJdNum=LoopBuff.LoopBuffDataLength(&DistHdmJd_LoofBuff_R);
		OutLineSection_R.Unlock();
		if (HdmJdNum>0)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();		
			CString strDist=_T(" ");		
			HdmFileNameEnd = (int)(HdmFileNameStart+(HdmJdNum/nStNumNode)*Encoder_Distance);
			strDistHdmFileName.Format(_T("%s%s-%06d-%06dM-%s�Һ���澫��%s"),g_strXianbie,g_strRunDirction,HdmFileNameStart,HdmFileNameEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strDistHdmFileName);
			nRes1=fp2D00DistHdm.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1)
			{
				for (int i=0;i<(HdmJdNum/nStNumNode);i++)
				{
					DistHdmCnt +=Encoder_Distance;
					ZeroMemory(tempDistHdm,sizeof(tempDistHdm));				
					OutLineSection_R.Lock();  //�����ٽ���
					LoopBuff.LoopBuffRead(&DistHdmJd_LoofBuff_R,tempDistHdm,nStNumNode);				
					OutLineSection_R.Unlock();
					for (int j=0;j<nStNumNode;j++)
					{
						strDist.Format(_T("%.2f   %011.6f\r\n"),DistHdmCnt,tempDistHdm[j]);	
						fp2D00DistHdm.Write(strDist,strlen(strDist));	
					}	
				}
				fp2D00DistHdm.Close();
				HdmFileNameStart =HdmFileNameEnd;
			}
			//���ļ���д��HNU�ļ�
			CString strHnuTemp=strDistHdmFileName+_T("\r\n");
			HnuFileSection.Lock();
			fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			fpHNUFile.SeekToEnd();
			fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			fpHNUFile.Close();
			HnuFileSection.Unlock();
		}

	}	
	if (ScbzNum>0)
	{
		for(int i=0;i<ScbzNum/((nStNumNode+1)*Num_StInterval);i++)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();		
			ScbzFileEnd=(int)(ScbzFileStart+Num_StInterval*Encoder_Distance);//��ȡʵ���׼���ļ����յ�

			strScbzFileName.Format(_T("%s%s-%06d-%06dM-%s��ʵ���׼��%s"),g_strXianbie,g_strRunDirction,ScbzFileStart,ScbzFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strScbzFileName);
			nRes1=fp2D00Scbz.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);

			strHdmNodeFileName.Format(_T("%s%s-%06d-%06dM-%s�Һ���潻��%s"),g_strXianbie,g_strRunDirction,ScbzFileStart,ScbzFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strHdmNodeFileName);
			nRes2=fp2D00HdmNode.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1&&nRes2)
			{
				for (int i=0;i<Num_StInterval;i++)
				{
					ScbzCnt+=Encoder_Distance;

					ZeroMemory(tempScbzNode_X,sizeof(tempScbzNode_X));
					ZeroMemory(tempScbzNode_Y,sizeof(tempScbzNode_Y));
					ZeroMemory(tempHdmNode_X,sizeof(tempHdmNode_X));
					ZeroMemory(tempHdmNode_Y,sizeof(tempHdmNode_Y));
					OutLineSection_R.Lock();
					LoopBuff.LoopBuffRead(&xHdmNodeLoopBuff_R,tempHdmNode_X,nStNumNode+1);
					LoopBuff.LoopBuffRead(&zHdmNodeLoopBuff_R,tempHdmNode_Y,nStNumNode+1);
					LoopBuff.LoopBuffRead(&xScbzLoopBuff_R,tempScbzNode_X,nStNumNode+1);
					LoopBuff.LoopBuffRead(&zScbzLoopBuff_R,tempScbzNode_Y,nStNumNode+1);
					OutLineSection_R.Unlock();
					for (int j=0;j<nStNumNode+1;j++)
					{
						strHdmNode.Format(_T("%.2f    %011.6f  %010.6f\r\n"),ScbzCnt,tempHdmNode_X[j],tempHdmNode_Y[j]);
						strScbz.Format(_T("%.2f    %011.6f  %010.6f\r\n"),ScbzCnt,tempScbzNode_X[j],tempScbzNode_Y[j]);				
						fp2D00HdmNode.Write(strHdmNode,strlen(strHdmNode));
						fp2D00Scbz.Write(strScbz,strlen(strScbz));

					}				

				}
				fp2D00HdmNode.Close();
				fp2D00Scbz.Close();
				ScbzFileStart = ScbzFileEnd;
			}
			//���ļ���д��HNU�ļ�
			CString strHnuTemp=strScbzFileName+_T("\r\n")/*+strHdmNodeFileName+_T("\r\n")*/;
			HnuFileSection.Lock();
			fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			fpHNUFile.SeekToEnd();
			fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			fpHNUFile.Close();
			HnuFileSection.Unlock();
		}
		OutLineSection_R.Lock();
		ScbzNum=LoopBuff.LoopBuffDataLength(&xScbzLoopBuff_R);
		OutLineSection_R.Unlock();
		if(ScbzNum>0)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();		
			ScbzFileEnd=(int)(ScbzFileStart+ScbzNum/(nStNumNode+1)*Encoder_Distance);//��ȡʵ���׼���ļ����յ�

			strScbzFileName.Format(_T("%s%s-%06d-%06dM-%s��ʵ���׼��%s"),g_strXianbie,g_strRunDirction,ScbzFileStart,ScbzFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strScbzFileName);
			nRes1=fp2D00Scbz.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);

			strHdmNodeFileName.Format(_T("%s%s-%06d-%06dM-%s�Һ���潻��%s"),g_strXianbie,g_strRunDirction,ScbzFileStart,ScbzFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strHdmNodeFileName);
			nRes2=fp2D00HdmNode.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1&&nRes2)
			{
				for (int i=0;i<ScbzNum/(nStNumNode+1);i++)
				{
					ScbzCnt+=Encoder_Distance;

					ZeroMemory(tempScbzNode_X,sizeof(tempScbzNode_X));
					ZeroMemory(tempScbzNode_Y,sizeof(tempScbzNode_Y));
					ZeroMemory(tempHdmNode_X,sizeof(tempHdmNode_X));
					ZeroMemory(tempHdmNode_Y,sizeof(tempHdmNode_Y));
					OutLineSection_R.Lock();
					LoopBuff.LoopBuffRead(&xHdmNodeLoopBuff_R,tempHdmNode_X,nStNumNode+1);
					LoopBuff.LoopBuffRead(&zHdmNodeLoopBuff_R,tempHdmNode_Y,nStNumNode+1);
					LoopBuff.LoopBuffRead(&xScbzLoopBuff_R,tempScbzNode_X,nStNumNode+1);
					LoopBuff.LoopBuffRead(&zScbzLoopBuff_R,tempScbzNode_Y,nStNumNode+1);
					OutLineSection_R.Unlock();
					for (int j=0;j<nStNumNode+1;j++)
					{
						strHdmNode.Format(_T("%.2f    %011.6f  %010.6f\r\n"),ScbzCnt,tempHdmNode_X[j],tempHdmNode_Y[j]);
						strScbz.Format(_T("%.2f    %011.6f  %010.6f\r\n"),ScbzCnt,tempScbzNode_X[j],tempScbzNode_Y[j]);				
						fp2D00HdmNode.Write(strHdmNode,strlen(strHdmNode));
						fp2D00Scbz.Write(strScbz,strlen(strScbz));

					}				

				}
				fp2D00HdmNode.Close();
				fp2D00Scbz.Close();
				ScbzFileStart = ScbzFileEnd;
			}
			//���ļ���д��HNU�ļ�
			CString strHnuTemp=strScbzFileName+_T("\r\n")/*+strHdmNodeFileName+_T("\r\n")*/;
			HnuFileSection.Lock();
			fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			fpHNUFile.SeekToEnd();
			fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			fpHNUFile.Close();
			HnuFileSection.Unlock();
		}

	}
	if (OriginNum>0)
	{
		for(int i=0;i<OriginNum/500;i++)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();
			OriginFileEnd=(int)(OriginFileStart+Encoder_Distance*500);
			strOriginFileName.Format(_T("%s%s-%06d-%06dM-%s��ԭʼ������%s"),g_strXianbie,g_strRunDirction,OriginFileStart,OriginFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strOriginFileName);
			nRes1=fp2D00Origin.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1)//�ļ���ȷ��
			{
				OutLineSection_R.Lock();
				LoopBuff.LoopBuffRead(&GetDataNumSt_LoopBuff_R,GDTempOutlineNum,500);
				OutLineSection_R.Unlock();
				for (int i=0;i<500;i++)
				{
					OriginCnt+=Encoder_Distance;
					ZeroMemory(tempOrigin_X,sizeof(tempOrigin_X));
					ZeroMemory(tempOrigin_Y,sizeof(tempOrigin_Y));
					OutLineSection_R.Lock();
					LoopBuff.LoopBuffRead(&xSave_LoopBuff_R,tempOrigin_X,GDTempOutlineNum[i]);
					LoopBuff.LoopBuffRead(&zSave_LoopBuff_R,tempOrigin_Y,GDTempOutlineNum[i]);
					OutLineSection_R.Unlock();
					for (int j=0;j<GDTempOutlineNum[i];j++)
					{
						strOrigin.Format(_T("%.2f    %011.6f  %010.6f\r\n"),OriginCnt,tempOrigin_X[j],tempOrigin_Y[j]);
						fp2D00Origin.Write(strOrigin,strlen(strOrigin));
					}
				}
				fp2D00Origin.Close();
				OriginFileStart = OriginFileEnd;
			}
		}
		OutLineSection_R.Lock();
		OriginNum=LoopBuff.LoopBuffDataLength(&GetDataNumSt_LoopBuff_R);
		OutLineSection_R.Unlock();
		if(OriginNum>0)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();
			OriginFileEnd=(int)(OriginFileStart+Encoder_Distance*OriginNum);
			strOriginFileName.Format(_T("%s%s-%06d-%06dM-%s��ԭʼ������%s"),g_strXianbie,g_strRunDirction,OriginFileStart,OriginFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strOriginFileName);
			nRes1=fp2D00Origin.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1)//�ļ���ȷ��
			{
				OutLineSection_R.Lock();
				LoopBuff.LoopBuffRead(&GetDataNumSt_LoopBuff_R,GDTempOutlineNum,OriginNum);
				OutLineSection_R.Unlock();
				for (int i=0;i<OriginNum;i++)
				{
					OriginCnt+=Encoder_Distance;
					ZeroMemory(tempOrigin_X,sizeof(tempOrigin_X));
					ZeroMemory(tempOrigin_Y,sizeof(tempOrigin_Y));
					OutLineSection_R.Lock();
					LoopBuff.LoopBuffRead(&xSave_LoopBuff_R,tempOrigin_X,GDTempOutlineNum[i]);
					LoopBuff.LoopBuffRead(&zSave_LoopBuff_R,tempOrigin_Y,GDTempOutlineNum[i]);
					OutLineSection_R.Unlock();
					for (int j=0;j<GDTempOutlineNum[i];j++)
					{
						strOrigin.Format(_T("%.2f    %011.6f  %010.6f\r\n"),OriginCnt,tempOrigin_X[j],tempOrigin_Y[j]);
						fp2D00Origin.Write(strOrigin,strlen(strOrigin));
					}
				}
				fp2D00Origin.Close();
				OriginFileStart = OriginFileEnd;
			}
			//////CString strHnuTemp=strOriginFileName+_T("\r\n");
			//////HnuFileSection.Lock();
			//////fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			//////fpHNUFile.SeekToEnd();
			//////fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			//////fpHNUFile.Close();
			//////HnuFileSection.Unlock();
		}

	}
	if (g_TestInfo_R.XM_QianHou==1)
	{
		if (XmlJdNum>0)
		{
			for(int i=0;i<XmlJdNum/((nStNumNode)*Num_StInterval);i++)
			{
				TCurrentTime=TCurrentTime.GetCurrentTime();
				XmlFileNameEnd=(int)(XmlFileNameStart+Num_StInterval*Encoder_Distance);
				strDistXmlFileName.Format(_T("%s%s-%06d-%06dM-%s��ϳĥ������%s"),g_strXianbie,g_strRunDirction,XmlFileNameStart,XmlFileNameEnd,g_XMQianHou,strTrackSel);
				strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strDistXmlFileName);
				nRes3=fp2D00DistXml.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
				if (nRes3)
				{
					for (int i=0;i<Num_StInterval;i++)
					{
						DistXmlCnt+=Encoder_Distance;
						OutLineSection_R.Lock();  //�����ٽ���
						LoopBuff.LoopBuffRead(&DistXmlJd_LoopBuff_R,tempDistXml,nStNumNode);				
						OutLineSection_R.Unlock();
						for (int j=0;j<nStNumNode;j++)
						{
							strDistXml.Format(_T("%.2f   %011.6f\r\n"),DistXmlCnt,tempDistXml[j]);	
							fp2D00DistXml.Write(strDistXml,strlen(strDistXml));	
						}					
					}
					fp2D00DistXml.Close();
					XmlFileNameStart=XmlFileNameEnd;
				} 
							CString strHnuTemp=strDistXmlFileName+_T("\r\n");
			HnuFileSection.Lock();
			fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			fpHNUFile.SeekToEnd();
			fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			fpHNUFile.Close();
			HnuFileSection.Unlock();
			}
			OutLineSection_R.Lock();
			XmlJdNum=LoopBuff.LoopBuffDataLength(&DistXmlJd_LoopBuff_R);
			OutLineSection_R.Unlock();
			if (XmlJdNum>0)
			{
				TCurrentTime=TCurrentTime.GetCurrentTime();
				XmlFileNameEnd=(int)(XmlFileNameStart+(XmlJdNum/nStNumNode)*Encoder_Distance);
				strDistXmlFileName.Format(_T("%s%s-%06d-%06dM-%s��ϳĥ������%s"),g_strXianbie,g_strRunDirction,XmlFileNameStart,XmlFileNameEnd,g_XMQianHou,strTrackSel);
				strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strDistXmlFileName);
				nRes3=fp2D00DistXml.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
				if (nRes3)
				{
					for (int i=0;i<XmlJdNum/nStNumNode;i++)
					{
						DistXmlCnt+=Encoder_Distance;
						OutLineSection_R.Lock();  //�����ٽ���
						LoopBuff.LoopBuffRead(&DistXmlJd_LoopBuff_R,tempDistXml,nStNumNode);				
						OutLineSection_R.Unlock();
						for (int j=0;j<nStNumNode;j++)
						{
							strDistXml.Format(_T("%.2f   %011.6f\r\n"),DistXmlCnt,tempDistXml[j]);	
							fp2D00DistXml.Write(strDistXml,strlen(strDistXml));	
						}					
					}
					fp2D00DistXml.Close();
					XmlFileNameStart=XmlFileNameEnd;
				} 
				CString strHnuTemp=strDistXmlFileName+_T("\r\n");
				HnuFileSection.Lock();
				fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
				fpHNUFile.SeekToEnd();
				fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
				fpHNUFile.Close();
				HnuFileSection.Unlock();
			}
		}
	}
	if (tempDistHdm)
	{
		delete[] tempDistHdm;
		tempDistHdm=NULL;
	}
	if (tempDistXml)
	{
		delete[] tempDistXml;
		tempDistXml=NULL;
	}
	if (tempScbzNode_X)
	{
		delete[] tempScbzNode_X;
		tempScbzNode_X=NULL;
	}
	if (tempScbzNode_Y)
	{
		delete[] tempScbzNode_Y;
		tempScbzNode_Y=NULL;
	}
	if (tempHdmNode_X)
	{
		delete[] tempHdmNode_X;
		tempHdmNode_X=NULL;
	}
	if (tempHdmNode_Y)
	{
		delete[] tempHdmNode_Y;
		tempHdmNode_Y=NULL;
	}
	bEndSaveFlag_R=true;
	bEndDealingFlag_R=false;//�洢��ɣ���־λ��λ
	bStartStFlag=bEndDealingFlag_L||bEndDealingFlag_R;
	if(!bStartStFlag)
	{
		//bEndDealingFlag_R=true;//��ֹ��������AfxMessageBox(_T("���μ�������"));
		dlg->SetDlgItemText(IDC_BUTTON_START, _T("��ʼ"));
		//////////////
		dlg->GetDlgItem(IDC_RADIO_BACK)->EnableWindow(false);

		dlg->btn10.SetAlign(CButtonST::ST_ALIGN_VERT);
		dlg->btn10.DrawTransparent(TRUE);
		dlg->btn10.SetIcon(IDI_ICON8);
		dlg->GetDlgItem(IDC_BUTTON_START)->SetFont(f);
		g_TestInfo_L.TestInfoYES_NO=false;
		g_TestInfo_R.TestInfoYES_NO=false;
		//������ť
		dlg->GetDlgItem(IDC_BUTTON_LINK)->EnableWindow(true);
		dlg->GetDlgItem(IDC_BUTTON_TESTINFO)->EnableWindow(true);
		dlg->GetDlgItem(IDC_BUTTON_ANALYZEFLAG)->EnableWindow(true);
	
		////�����˵���ť
		//���ģʽ
		dlg->m_MainMenu->EnableMenuItem(ID_Menu_Link,MF_ENABLED|MF_BYCOMMAND);//�����豸
		dlg->m_MainMenu->EnableMenuItem(ID_Menu_TestInfo,MF_ENABLED|MF_BYCOMMAND);//��������Ϣ
		dlg->m_MainMenu->EnableMenuItem(ID_Menu_TestStart,MF_ENABLED|MF_BYCOMMAND);//��ʼ���
		dlg->m_MainMenu->EnableMenuItem(ID_Menu_TestStop,MF_ENABLED|MF_BYCOMMAND);//ֹͣ���
		//����ģʽ
		dlg->m_MainMenu->EnableMenuItem(ID_Menu_Anaylze,MF_ENABLED|MF_BYCOMMAND);//�ļ�����
		dlg->m_MainMenu->EnableMenuItem(ID_Menu_Reprot,MF_ENABLED|MF_BYCOMMAND);//���ɱ���
		dlg->m_MainMenu->EnableMenuItem(ID_Menu_InputFile,MF_ENABLED|MF_BYCOMMAND);//�����ļ�
		dlg->m_MainMenu->EnableMenuItem(ID_SETREPORTPARAM, MF_ENABLED | MF_BYCOMMAND);//�����ļ�shen
		AfxMessageBox(_T("���μ�������"));
	}
	//bEndDealingFlag_R=false;//�洢��ɣ���־λ��λ
	return 0;
}
UINT ThreadStData_L(LPVOID pParam)
{
	bEndSaveFlag_L=false;
	CHighPrecisionDlg *dlg;
	dlg = (CHighPrecisionDlg *)pdlg;

	CString g_strXianbie=g_TestInfo_L.Xianbie;//��ҵ�߱�
	CString g_strRunDirction =g_TestInfo_L.Direction;//��ҵ����
	CString strTrackSel;//����ѡ��

	CFont* f;
	f=new CFont;
	f->CreateFont(11,0,0,0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,_T("����"));
	switch(g_TestInfo_L.TrackSel)
	{
	case 0:
		strTrackSel=_T("a");//50��
		break;
	case 1:
		strTrackSel=_T("b");//60��
		break;
	}	
	int g_strFileNameStart=(int)g_TestInfo_L.DistanceStart;//��ҵ���
	CString g_XMQianHou;
	switch(g_TestInfo_L.XM_QianHou)
	{
	case 0:
		g_XMQianHou=_T("ǰ");
		break;
	case 1:
		g_XMQianHou=_T("��");
		break;
	}

	int nStNumNode;
	switch(g_TestInfo_L.TrackSel)
	{
	case 0://50��
		{
			nStNumNode=19;
			break;
		}

	case 1://60��
		{
			nStNumNode=23;
			break;
		}
	}

	double* tempDistHdm=NULL;
	 tempDistHdm=new double[nStNumNode];
	 double*  tempDistXml=NULL;
	 tempDistXml=new double[nStNumNode];
	 double*  tempScbzNode_X=NULL;
	 tempScbzNode_X=new double[nStNumNode+1];
	 double*  tempScbzNode_Y=NULL;
	 tempScbzNode_Y=new double[nStNumNode+1];
	 double*  tempHdmNode_X=NULL;
	 tempHdmNode_X=new double[nStNumNode+1];
	 double*  tempHdmNode_Y=NULL;
	 tempHdmNode_Y=new double[nStNumNode+1];

	 
	//��ʱ����
	 /*double tempDistHdm[Num_Node];
	 double tempDistXml[Num_Node];
	 double tempScbzNode_X[Num_Node+1];
	 double tempScbzNode_Y[Num_Node+1];
	 double tempHdmNode_X[Num_Node+1];
	 double tempHdmNode_Y[Num_Node+1];*/
	double tempOrigin_X[SensorMaxPoint];
	double tempOrigin_Y[SensorMaxPoint];
	

	CTime TCurrentTime;//��ȡ��ǰʱ��
	int HdmJdNum;//ʵ���׼������潻�����Ŀ
	int ScbzNum;//�洢�ļ�
	int OriginNum;//ԭʼ�����ĸ���
	int XmlJdNum;

	//�ļ�����ض���
	int HdmFileNameStart=g_strFileNameStart;//�洢HDM�����ļ������
	int HdmFileNameEnd;//�洢HDM�����ļ����յ�
	int ScbzFileStart=g_strFileNameStart;//�洢ʵ���׼���ļ������
	int	ScbzFileEnd;
	int OriginFileStart=g_strFileNameStart;
	int OriginFileEnd;
	int XmlFileNameStart=g_strFileNameStart;
	int XmlFileNameEnd;
	CString strTime00="";
	CString strDist="";//txt��һ�еľ������
	CString strScbz="";
	CString strHdmNode="";
	CString strOrigin="";
	CString strDistXml="";
	int GDTempOutlineNum[500];		//��ȡ�洢�̻߳�������ԭʼ�����ĵ���



	CString strFileName2D00;//
	CString strOriginFileName="";//ԭʼ�����ļ���
	CString strDistHdmFileName="";//����澫�ȵ��ļ���
	CString strScbzFileName="";//ʵ���׼���ļ���
	CString strHdmNodeFileName="";//����澫�Ƚ����ļ���
	CString strDistXmlFileName="";
	double DistHdmCnt=g_strFileNameStart;//�Դ洢�ں���澫��txt�е���̵ļ�������㸳ֵΪ��������
	double ScbzCnt=g_strFileNameStart;//�Դ洢��ʵ���׼��txt�е���̵ļ�������㸳ֵΪ��������
	double OriginCnt=g_strFileNameStart;//�洢ԭʼ����
	double DistXmlCnt=g_strFileNameStart;



	//�ļ���������
	CFile fp2D00DistHdm;//����澫��
	CFile fp2D00Origin;//ԭʼ����
	CFile fp2D00Scbz;//ʵ���׼��
	CFile fp2D00HdmNode;//����澫�Ƚ���
	CFile fp2D00DistXml;
	BOOL nRes1,nRes2,nRes3;
	
	


	while(!bEndDealingFlag_L)
	{
		OutLineSection_L.Lock();//��ȡ����������ĳ���
		HdmJdNum=LoopBuff.LoopBuffDataLength(&DistHdmJd_LoofBuff_L);
		ScbzNum=LoopBuff.LoopBuffDataLength(&xScbzLoopBuff_L);
		OriginNum=LoopBuff.LoopBuffDataLength(&GetDataNumSt_LoopBuff_L);
		XmlJdNum=LoopBuff.LoopBuffDataLength(&DistXmlJd_LoopBuff_L);
		OutLineSection_L.Unlock();

		//�洢23������ֵ
		if(HdmJdNum>=nStNumNode*Num_StInterval)//����ֵ��1KM�洢��һ���ļ�
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();			
			HdmFileNameEnd = (int)(HdmFileNameStart+Num_StInterval*Encoder_Distance);
			strDistHdmFileName.Format(_T("%s%s-%06d-%06dM-%s�����澫��%s"),g_strXianbie,g_strRunDirction,HdmFileNameStart,HdmFileNameEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strDistHdmFileName);//�ļ�����·��
			nRes1 = fp2D00DistHdm.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1)
			{
				for (int i=0;i<Num_StInterval;i++)
				{
					DistHdmCnt +=Encoder_Distance;				
					ZeroMemory(tempDistHdm,sizeof(tempDistHdm));				
					OutLineSection_L.Lock();  //�����ٽ���
					LoopBuff.LoopBuffRead(&DistHdmJd_LoofBuff_L,tempDistHdm,nStNumNode);				
					OutLineSection_L.Unlock();				
					for (int j=0;j<nStNumNode;j++)
					{
						strDist.Format(_T("%.2f   %011.6f\r\n"),DistHdmCnt,tempDistHdm[j]);
						fp2D00DistHdm.Write(strDist,strlen(strDist));	
					}
				}
				fp2D00DistHdm.Close();
				HdmFileNameStart = HdmFileNameEnd;
			}	
			CString strHnuTemp=strDistHdmFileName+_T("\r\n");
			HnuFileSection.Lock();
			fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			fpHNUFile.SeekToEnd();
			fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			fpHNUFile.Close();
			HnuFileSection.Unlock();

		}
		//�洢24��ʵ���׼��ͺ���潻�㣨23����+������ĵ㣩		
		if (ScbzNum>=(nStNumNode+1)*Num_StInterval)	
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();
			ScbzFileEnd=(int)(ScbzFileStart+Num_StInterval*Encoder_Distance);//��ȡʵ���׼���ļ����յ�

			strScbzFileName.Format(_T("%s%s-%06d-%06dM-%s��ʵ���׼��%s"),g_strXianbie,g_strRunDirction,ScbzFileStart,ScbzFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strScbzFileName);
			nRes1=fp2D00Scbz.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);

			strHdmNodeFileName.Format(_T("%s%s-%06d-%06dM-%s�����潻��%s"),g_strXianbie,g_strRunDirction,ScbzFileStart,ScbzFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strHdmNodeFileName);
			nRes2=fp2D00HdmNode.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1&&nRes2)
			{
				for (int i=0;i<Num_StInterval;i++)
				{
					ScbzCnt+=Encoder_Distance;
					ZeroMemory(tempScbzNode_X,sizeof(tempScbzNode_X));
					ZeroMemory(tempScbzNode_Y,sizeof(tempScbzNode_Y));
					ZeroMemory(tempHdmNode_X,sizeof(tempHdmNode_X));
					ZeroMemory(tempHdmNode_Y,sizeof(tempHdmNode_Y));
					OutLineSection_L.Lock();
					LoopBuff.LoopBuffRead(&xHdmNodeLoopBuff_L,tempHdmNode_X,nStNumNode+1);
					LoopBuff.LoopBuffRead(&zHdmNodeLoopBuff_L,tempHdmNode_Y,nStNumNode+1);
					LoopBuff.LoopBuffRead(&xScbzLoopBuff_L,tempScbzNode_X,nStNumNode+1);
					LoopBuff.LoopBuffRead(&zScbzLoopBuff_L,tempScbzNode_Y,nStNumNode+1);
					OutLineSection_L.Unlock();
					for (int j=0;j<nStNumNode+1;j++)
					{
						strHdmNode.Format(_T("%.2f    %011.6f  %010.6f\r\n"),ScbzCnt,tempHdmNode_X[j],tempHdmNode_Y[j]);
						strScbz.Format(_T("%.2f    %011.6f  %010.6f\r\n"),ScbzCnt,tempScbzNode_X[j],tempScbzNode_Y[j]);				
						fp2D00HdmNode.Write(strHdmNode,strlen(strHdmNode));
						fp2D00Scbz.Write(strScbz,strlen(strScbz));
					}				

				}
				fp2D00HdmNode.Close();
				fp2D00Scbz.Close();
				ScbzFileStart = ScbzFileEnd;
			}
			//���ļ���д��HNU�ļ�
			CString strHnuTemp=strScbzFileName+_T("\r\n")/*+strHdmNodeFileName+_T("\r\n")*/;
			HnuFileSection.Lock();
			fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			fpHNUFile.SeekToEnd();
			fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			fpHNUFile.Close();
			HnuFileSection.Unlock();
		}
		//�洢ԭʼ����
		if (OriginNum>=500)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();			
			OriginFileEnd=(int)(OriginFileStart+Encoder_Distance*500);
			strOriginFileName.Format(_T("%s%s-%06d-%06dM-%s��ԭʼ������%s"),g_strXianbie,g_strRunDirction,OriginFileStart,OriginFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strOriginFileName);
			nRes1=fp2D00Origin.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1)
			{
				OutLineSection_L.Lock();
				LoopBuff.LoopBuffRead(&GetDataNumSt_LoopBuff_L,GDTempOutlineNum,500);
				OutLineSection_L.Unlock();
				for (int i=0;i<500;i++)
				{
					OriginCnt+=Encoder_Distance;
					ZeroMemory(tempOrigin_X,sizeof(tempOrigin_X));
					ZeroMemory(tempOrigin_Y,sizeof(tempOrigin_Y));
					OutLineSection_L.Lock();
					LoopBuff.LoopBuffRead(&xSave_LoopBuff_L,tempOrigin_X,GDTempOutlineNum[i]);
					LoopBuff.LoopBuffRead(&zSave_LoopBuff_L,tempOrigin_Y,GDTempOutlineNum[i]);
					OutLineSection_L.Unlock();
					for (int j=0;j<GDTempOutlineNum[i];j++)
					{
						strOrigin.Format(_T("%.2f    %011.6f  %010.6f\r\n"),OriginCnt,tempOrigin_X[j],tempOrigin_Y[j]);

						fp2D00Origin.Write(strOrigin,strlen(strOrigin));
					}
				}
				fp2D00Origin.Close();
				OriginFileStart=OriginFileEnd;
			}
			//CString strHnuTemp=strOriginFileName+_T("\r\n");
			//HnuFileSection.Lock();
			//fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			//fpHNUFile.SeekToEnd();
			//fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			//fpHNUFile.Close();
			//HnuFileSection.Unlock();
		}
		//�洢ϳĥ��,�ж���ϳĥǰ����ϳĥ��		
		if (g_TestInfo_L.XM_QianHou==1)
		{
			if (XmlJdNum>nStNumNode*Num_StInterval)//ϳĥ��
			{
				TCurrentTime=TCurrentTime.GetCurrentTime();
				XmlFileNameEnd=(int)(XmlFileNameStart+Num_StInterval*Encoder_Distance);
				strDistXmlFileName.Format(_T("%s%s-%06d-%06dM-%s��ϳĥ������%s"),g_strXianbie,g_strRunDirction,XmlFileNameStart,XmlFileNameEnd,g_XMQianHou,strTrackSel);
				strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strDistXmlFileName);
				nRes3=fp2D00DistXml.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
				if (nRes3)
				{
					for (int i=0;i<Num_StInterval;i++)
					{
						DistXmlCnt+=Encoder_Distance;
						OutLineSection_R.Lock();  //�����ٽ���
						LoopBuff.LoopBuffRead(&DistXmlJd_LoopBuff_R,tempDistXml,nStNumNode);				
						OutLineSection_R.Unlock();
						for (int j=0;j<nStNumNode;j++)
						{
							strDistXml.Format(_T("%.2f   %011.6f\r\n"),DistXmlCnt,tempDistXml[j]);	
							fp2D00DistXml.Write(strDistXml,strlen(strDistXml));	
						}					
					}
					fp2D00DistXml.Close();
					XmlFileNameStart=XmlFileNameEnd;
				} 
				CString strHnuTemp=strDistXmlFileName+_T("\r\n");
				HnuFileSection.Lock();
				fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
				fpHNUFile.SeekToEnd();
				fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
				fpHNUFile.Close();
				HnuFileSection.Unlock();
			}

		}

		if(HdmJdNum<nStNumNode*Num_StInterval)
			if(ScbzNum<(nStNumNode+1)*Num_StInterval)
				if(OriginNum<500)
			Sleep(50);
		

	}
	//����ʱ��ȡ������
	OutLineSection_L.Lock();
	HdmJdNum=LoopBuff.LoopBuffDataLength(&DistHdmJd_LoofBuff_L);
	ScbzNum=LoopBuff.LoopBuffDataLength(&xScbzLoopBuff_L);
	OriginNum=LoopBuff.LoopBuffDataLength(&GetDataNumSt_LoopBuff_L);
	XmlJdNum=LoopBuff.LoopBuffDataLength(&DistXmlJd_LoopBuff_L);
	OutLineSection_L.Unlock();
	if (HdmJdNum>0)
	{		
		for(int i=0;i<HdmJdNum/(nStNumNode*Num_StInterval);i++)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();		
			HdmFileNameEnd = (int)(HdmFileNameStart+10000*Encoder_Distance);
			strDistHdmFileName.Format(_T("%s%s-%06d-%06dM-%s�����澫��%s"),g_strXianbie,g_strRunDirction,HdmFileNameStart,HdmFileNameEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strDistHdmFileName);
			nRes1=fp2D00DistHdm.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1)
			{
				for (int i=0;i<Num_StInterval;i++)
				{
					DistHdmCnt +=Encoder_Distance;			
					ZeroMemory(tempDistHdm,sizeof(tempDistHdm));				
					OutLineSection_L.Lock();  //�����ٽ���
					LoopBuff.LoopBuffRead(&DistHdmJd_LoofBuff_L,tempDistHdm,nStNumNode);				
					OutLineSection_L.Unlock();			
					for (int j=0;j<nStNumNode;j++)
					{
						strDist.Format(_T("%.2f   %011.6f\r\n"),DistHdmCnt,tempDistHdm[j]);					
						fp2D00DistHdm.Write(strDist,strlen(strDist));	
					}
				}
				fp2D00DistHdm.Close();
				HdmFileNameStart = HdmFileNameEnd;
			}
			CString strHnuTemp=strDistHdmFileName+_T("\r\n");
			HnuFileSection.Lock();
			BOOL nResHnu=fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			fpHNUFile.SeekToEnd();
			fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			fpHNUFile.Close();
			HnuFileSection.Unlock();
		}
		OutLineSection_L.Lock();
		HdmJdNum=LoopBuff.LoopBuffDataLength(&DistHdmJd_LoofBuff_L);
		OutLineSection_L.Unlock();
		if(HdmJdNum>0)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();		
			HdmFileNameEnd = (int)(HdmFileNameStart+(HdmJdNum/nStNumNode)*Encoder_Distance);
			strDistHdmFileName.Format(_T("%s%s-%06d-%06dM-%s�����澫��%s"),g_strXianbie,g_strRunDirction,HdmFileNameStart,HdmFileNameEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strDistHdmFileName);
			nRes1=fp2D00DistHdm.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1)
			{
				for (int i=0;i<(HdmJdNum/nStNumNode);i++)
				{
					DistHdmCnt +=Encoder_Distance;			
					ZeroMemory(tempDistHdm,sizeof(tempDistHdm));				
					OutLineSection_L.Lock();  //�����ٽ���
					LoopBuff.LoopBuffRead(&DistHdmJd_LoofBuff_L,tempDistHdm,nStNumNode);				
					OutLineSection_L.Unlock();			
					for (int j=0;j<nStNumNode;j++)
					{
						strDist.Format(_T("%.2f   %011.6f\r\n"),DistHdmCnt,tempDistHdm[j]);					
						fp2D00DistHdm.Write(strDist,strlen(strDist));	
					}
				}
				fp2D00DistHdm.Close();
				HdmFileNameStart = HdmFileNameEnd;
			}
			CString strHnuTemp=strDistHdmFileName+_T("\r\n");
			HnuFileSection.Lock();
			BOOL nResHnu=fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			fpHNUFile.SeekToEnd();
			fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			fpHNUFile.Close();
			HnuFileSection.Unlock();
		}

	}
	if (ScbzNum>0)
	{

		for(int i=0;i<HdmJdNum/((nStNumNode+1)*Num_StInterval);i++)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();
			ScbzFileEnd=(int)(ScbzFileStart+Num_StInterval*Encoder_Distance);//��ȡʵ���׼���ļ����յ�

			strScbzFileName.Format(_T("%s%s-%06d-%06dM-%s��ʵ���׼��%s"),g_strXianbie,g_strRunDirction,ScbzFileStart,ScbzFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strScbzFileName);
			nRes1=fp2D00Scbz.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);

			strHdmNodeFileName.Format(_T("%s%s-%06d-%06dM-%s�����潻��%s"),g_strXianbie,g_strRunDirction,ScbzFileStart,ScbzFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strHdmNodeFileName);
			nRes2=fp2D00HdmNode.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1&&nRes2)
			{
				for (int i=0;i<Num_StInterval;i++)
				{
					ScbzCnt+=Encoder_Distance;
					ZeroMemory(tempScbzNode_X,sizeof(tempScbzNode_X));
					ZeroMemory(tempScbzNode_Y,sizeof(tempScbzNode_Y));
					ZeroMemory(tempHdmNode_X,sizeof(tempHdmNode_X));
					ZeroMemory(tempHdmNode_Y,sizeof(tempHdmNode_Y));
					OutLineSection_L.Lock();
					LoopBuff.LoopBuffRead(&xHdmNodeLoopBuff_L,tempHdmNode_X,nStNumNode+1);
					LoopBuff.LoopBuffRead(&zHdmNodeLoopBuff_L,tempHdmNode_Y,nStNumNode+1);
					LoopBuff.LoopBuffRead(&xScbzLoopBuff_L,tempScbzNode_X,nStNumNode+1);
					LoopBuff.LoopBuffRead(&zScbzLoopBuff_L,tempScbzNode_Y,nStNumNode+1);
					OutLineSection_L.Unlock();
					for (int j=0;j<nStNumNode+1;j++)
					{
						strHdmNode.Format(_T("%.2f    %011.6f  %010.6f\r\n"),ScbzCnt,tempHdmNode_X[j],tempHdmNode_Y[j]);
						strScbz.Format(_T("%.2f    %011.6f  %010.6f\r\n"),ScbzCnt,tempScbzNode_X[j],tempScbzNode_Y[j]);

						fp2D00HdmNode.Write(strHdmNode,strlen(strHdmNode));
						fp2D00Scbz.Write(strScbz,strlen(strScbz));
					}
				}
				fp2D00HdmNode.Close();
				fp2D00Scbz.Close();
				ScbzFileStart = ScbzFileEnd;
				//���ļ���д��HNU�ļ�
				CString strHnuTemp=strScbzFileName+_T("\r\n")/*+strHdmNodeFileName+_T("\r\n")*/;
				HnuFileSection.Lock();
				BOOL nResHnu=fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
				fpHNUFile.SeekToEnd();
				fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
				fpHNUFile.Close();
				HnuFileSection.Unlock();
			}
		}
		OutLineSection_L.Lock();
		ScbzNum=LoopBuff.LoopBuffDataLength(&xScbzLoopBuff_L);
		OutLineSection_L.Unlock();
		if(ScbzNum>0)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();
			ScbzFileEnd=(int)(ScbzFileStart+ScbzNum/(nStNumNode+1)*Encoder_Distance);//��ȡʵ���׼���ļ����յ�

			strScbzFileName.Format(_T("%s%s-%06d-%06dM-%s��ʵ���׼��%s"),g_strXianbie,g_strRunDirction,ScbzFileStart,ScbzFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strScbzFileName);
			nRes1=fp2D00Scbz.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);

			strHdmNodeFileName.Format(_T("%s%s-%06d-%06dM-%s�����潻��%s"),g_strXianbie,g_strRunDirction,ScbzFileStart,ScbzFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strHdmNodeFileName);
			nRes2=fp2D00HdmNode.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1&&nRes2)
			{
				for (int i=0;i<ScbzNum/(nStNumNode+1);i++)
				{
					ScbzCnt+=Encoder_Distance;
					ZeroMemory(tempScbzNode_X,sizeof(tempScbzNode_X));
					ZeroMemory(tempScbzNode_Y,sizeof(tempScbzNode_Y));
					ZeroMemory(tempHdmNode_X,sizeof(tempHdmNode_X));
					ZeroMemory(tempHdmNode_Y,sizeof(tempHdmNode_Y));
					OutLineSection_L.Lock();
					LoopBuff.LoopBuffRead(&xHdmNodeLoopBuff_L,tempHdmNode_X,nStNumNode+1);
					LoopBuff.LoopBuffRead(&zHdmNodeLoopBuff_L,tempHdmNode_Y,nStNumNode+1);
					LoopBuff.LoopBuffRead(&xScbzLoopBuff_L,tempScbzNode_X,nStNumNode+1);
					LoopBuff.LoopBuffRead(&zScbzLoopBuff_L,tempScbzNode_Y,nStNumNode+1);
					OutLineSection_L.Unlock();
					for (int j=0;j<nStNumNode+1;j++)
					{
						strHdmNode.Format(_T("%.2f    %011.6f  %010.6f\r\n"),ScbzCnt,tempHdmNode_X[j],tempHdmNode_Y[j]);
						strScbz.Format(_T("%.2f    %011.6f  %010.6f\r\n"),ScbzCnt,tempScbzNode_X[j],tempScbzNode_Y[j]);

						fp2D00HdmNode.Write(strHdmNode,strlen(strHdmNode));
						fp2D00Scbz.Write(strScbz,strlen(strScbz));
					}
				}
				fp2D00HdmNode.Close();
				fp2D00Scbz.Close();
				ScbzFileStart = ScbzFileEnd;
				//���ļ���д��HNU�ļ�
				CString strHnuTemp=strScbzFileName+_T("\r\n");/*+strHdmNodeFileName+_T("\r\n")*/
				HnuFileSection.Lock();
				BOOL nResHnu=fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
				fpHNUFile.SeekToEnd();
				fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
				fpHNUFile.Close();
				HnuFileSection.Unlock();
			}

		}

	}
	if (OriginNum>0)
	{
		for(int i=0;i<OriginNum/500;i++)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();
			OriginFileEnd=(int)(OriginFileStart+Encoder_Distance*500);
			strOriginFileName.Format(_T("%s%s-%06d-%06dM-%s��ԭʼ������%s"),g_strXianbie,g_strRunDirction,OriginFileStart,OriginFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strOriginFileName);
			nRes1=fp2D00Origin.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1)
			{
				OutLineSection_L.Lock();
				LoopBuff.LoopBuffRead(&GetDataNumSt_LoopBuff_L,GDTempOutlineNum,500);
				OutLineSection_L.Unlock();
				for (int i=0;i<500;i++)
				{
					OriginCnt+=Encoder_Distance;
					ZeroMemory(tempOrigin_X,sizeof(tempOrigin_X));
					ZeroMemory(tempOrigin_Y,sizeof(tempOrigin_Y));
					OutLineSection_L.Lock();
					LoopBuff.LoopBuffRead(&xSave_LoopBuff_L,tempOrigin_X,GDTempOutlineNum[i]);
					LoopBuff.LoopBuffRead(&zSave_LoopBuff_L,tempOrigin_Y,GDTempOutlineNum[i]);
					OutLineSection_L.Unlock();
					for (int j=0;j<GDTempOutlineNum[i];j++)
					{
						strOrigin.Format(_T("%.2f    %011.6f  %010.6f\r\n"),OriginCnt,tempOrigin_X[j],tempOrigin_Y[j]);
						fp2D00Origin.Write(strOrigin,strlen(strOrigin));
					}
				}
				fp2D00Origin.Close();
				OriginFileStart = OriginFileEnd;
			}

			//CString strHnuTemp=strOriginFileName+_T("\r\n");
			//HnuFileSection.Lock();
			//BOOL nResHnu=fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			//fpHNUFile.SeekToEnd();
			//fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			//fpHNUFile.Close();
			//HnuFileSection.Unlock();
		}
		OutLineSection_L.Lock();
		OriginNum=LoopBuff.LoopBuffDataLength(&GetDataNumSt_LoopBuff_L);
		OutLineSection_L.Unlock();
		if(OriginNum>0)
		{
			TCurrentTime=TCurrentTime.GetCurrentTime();
			OriginFileEnd=(int)(OriginFileStart+Encoder_Distance*OriginNum);
			strOriginFileName.Format(_T("%s%s-%06d-%06dM-%s��ԭʼ������%s"),g_strXianbie,g_strRunDirction,OriginFileStart,OriginFileEnd,g_XMQianHou,strTrackSel);
			strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strOriginFileName);
			nRes1=fp2D00Origin.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
			if(nRes1)
			{
				OutLineSection_L.Lock();
				LoopBuff.LoopBuffRead(&GetDataNumSt_LoopBuff_L,GDTempOutlineNum,OriginNum);
				OutLineSection_L.Unlock();
				for (int i=0;i<OriginNum;i++)
				{
					OriginCnt+=Encoder_Distance;
					ZeroMemory(tempOrigin_X,sizeof(tempOrigin_X));
					ZeroMemory(tempOrigin_Y,sizeof(tempOrigin_Y));

					OutLineSection_L.Lock();
					LoopBuff.LoopBuffRead(&xSave_LoopBuff_L,tempOrigin_X,GDTempOutlineNum[i]);
					LoopBuff.LoopBuffRead(&zSave_LoopBuff_L,tempOrigin_Y,GDTempOutlineNum[i]);
					OutLineSection_L.Unlock();
					for (int j=0;j<GDTempOutlineNum[i];j++)
					{
						strOrigin.Format(_T("%.2f    %011.6f  %010.6f\r\n"),OriginCnt,tempOrigin_X[j],tempOrigin_Y[j]);
						fp2D00Origin.Write(strOrigin,strlen(strOrigin));
					}
				}
				fp2D00Origin.Close();
				OriginFileStart = OriginFileEnd;
			}

			//CString strHnuTemp=strOriginFileName+_T("\r\n");
			//HnuFileSection.Lock();
			//BOOL nResHnu=fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
			//fpHNUFile.SeekToEnd();
			//fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
			//fpHNUFile.Close();
			//HnuFileSection.Unlock();
		}

	}
	if (g_TestInfo_L.XM_QianHou==1)
	{
		if (XmlJdNum>0)
		{
			for(int i=0;i<XmlJdNum/((nStNumNode)*Num_StInterval);i++)
			{
				TCurrentTime=TCurrentTime.GetCurrentTime();
				XmlFileNameEnd=(int)(XmlFileNameStart+Num_StInterval*Encoder_Distance);
				strDistXmlFileName.Format(_T("%s%s-%06d-%06dM-%s��ϳĥ������%s"),g_strXianbie,g_strRunDirction,XmlFileNameStart,XmlFileNameEnd,g_XMQianHou,strTrackSel);
				strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strDistXmlFileName);
				nRes3=fp2D00DistXml.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
				if (nRes3)
				{
					for (int i=0;i<Num_StInterval;i++)
					{
						DistXmlCnt+=Encoder_Distance;
						OutLineSection_L.Lock();  //�����ٽ���
						LoopBuff.LoopBuffRead(&DistXmlJd_LoopBuff_L,tempDistXml,nStNumNode);				
						OutLineSection_L.Unlock();
						for (int j=0;j<nStNumNode;j++)
						{
							strDistXml.Format(_T("%.2f   %011.6f\r\n"),DistXmlCnt,tempDistXml[j]);	
							fp2D00DistXml.Write(strDistXml,strlen(strDistXml));	
						}					
					}
					fp2D00DistXml.Close();
					XmlFileNameStart=XmlFileNameEnd;
				} 
				CString strHnuTemp=strDistXmlFileName+_T("\r\n");
				HnuFileSection.Lock();
				fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
				fpHNUFile.SeekToEnd();
				fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
				fpHNUFile.Close();
				HnuFileSection.Unlock();
			}
			OutLineSection_L.Lock();
			XmlJdNum=LoopBuff.LoopBuffDataLength(&DistXmlJd_LoopBuff_L);
			OutLineSection_L.Unlock();
			if (XmlJdNum>0)
			{
				TCurrentTime=TCurrentTime.GetCurrentTime();
				XmlFileNameEnd=(int)(XmlFileNameStart+(XmlJdNum/nStNumNode)*Encoder_Distance);
				strDistXmlFileName.Format(_T("%s%s-%06d-%06dM-%s��ϳĥ������%s"),g_strXianbie,g_strRunDirction,XmlFileNameStart,XmlFileNameEnd,g_XMQianHou,strTrackSel);
				strFileName2D00.Format(_T("%s\\%s.txt"),csPath,strDistXmlFileName);
				nRes3=fp2D00DistXml.Open(strFileName2D00,CFile::modeCreate|CFile::modeReadWrite);
				if (nRes3)
				{
					for (int i=0;i<XmlJdNum/nStNumNode;i++)
					{
						DistXmlCnt+=Encoder_Distance;
						OutLineSection_L.Lock();  //�����ٽ���
						LoopBuff.LoopBuffRead(&DistXmlJd_LoopBuff_L,tempDistXml,nStNumNode);				
						OutLineSection_L.Unlock();
						for (int j=0;j<nStNumNode;j++)
						{
							strDistXml.Format(_T("%.2f   %011.6f\r\n"),DistXmlCnt,tempDistXml[j]);	
							fp2D00DistXml.Write(strDistXml,strlen(strDistXml));	
						}					
					}
					fp2D00DistXml.Close();
					XmlFileNameStart=XmlFileNameEnd;
				} 
				CString strHnuTemp=strDistXmlFileName+_T("\r\n");
				HnuFileSection.Lock();
				fpHNUFile.Open(HnuFilePath,CFile::modeReadWrite);
				fpHNUFile.SeekToEnd();
				fpHNUFile.Write(strHnuTemp,strlen(strHnuTemp));
				fpHNUFile.Close();
				HnuFileSection.Unlock();
			}
		}
	}
	if (tempDistHdm)
	{
		delete[] tempDistHdm;
		tempDistHdm=NULL;
	}
	if (tempDistXml)
	{
		delete[] tempDistXml;
		tempDistXml=NULL;
	}
	if (tempScbzNode_X)
	{
		delete[] tempScbzNode_X;
		tempScbzNode_X=NULL;
	}
	if (tempScbzNode_Y)
	{
		delete[] tempScbzNode_Y;
		tempScbzNode_Y=NULL;
	}
	if (tempHdmNode_X)
	{
		delete[] tempHdmNode_X;
		tempHdmNode_X=NULL;
	}
	if (tempHdmNode_Y)
	{
		delete[] tempHdmNode_Y;
		tempHdmNode_Y=NULL;
	}

	bEndSaveFlag_L=true;
	bEndDealingFlag_L=false;
	bStartStFlag=bEndDealingFlag_L||bEndDealingFlag_R;
	if(!bStartStFlag)
	{
		//bEndDealingFlag_L=true;//��ֹ��������AfxMessageBox(_T("���μ�������"));
		dlg->SetDlgItemText(IDC_BUTTON_START,_T("��ʼ"));
		/////////////////////
		dlg->GetDlgItem(IDC_RADIO_BACK)->EnableWindow(false);

		dlg->btn10.SetAlign(CButtonST::ST_ALIGN_VERT);
		dlg->btn10.DrawTransparent(TRUE);
		dlg->btn10.SetIcon(IDI_ICON8);
		dlg->GetDlgItem(IDC_BUTTON_START)->SetFont(f);
		g_TestInfo_L.TestInfoYES_NO=false;
		g_TestInfo_R.TestInfoYES_NO=false;
		//������ť
		dlg->GetDlgItem(IDC_BUTTON_LINK)->EnableWindow(true);
		dlg->GetDlgItem(IDC_BUTTON_TESTINFO)->EnableWindow(true);
		dlg->GetDlgItem(IDC_BUTTON_ANALYZEFLAG)->EnableWindow(true);
		////�����˵���ť
		////���ģʽ
		dlg->m_MainMenu->EnableMenuItem(ID_Menu_Link,MF_ENABLED|MF_BYCOMMAND);//�����豸
		dlg->m_MainMenu->EnableMenuItem(ID_Menu_TestInfo,MF_ENABLED|MF_BYCOMMAND);//��������Ϣ
		dlg->m_MainMenu->EnableMenuItem(ID_Menu_TestStart,MF_ENABLED|MF_BYCOMMAND);//��ʼ���
		dlg->m_MainMenu->EnableMenuItem(ID_Menu_TestStop,MF_ENABLED|MF_BYCOMMAND);//ֹͣ���
		//����ģʽ
		dlg->m_MainMenu->EnableMenuItem(ID_Menu_Anaylze,MF_ENABLED|MF_BYCOMMAND);//�ļ�����
		dlg->m_MainMenu->EnableMenuItem(ID_Menu_Reprot,MF_ENABLED|MF_BYCOMMAND);//���ɱ���
		dlg->m_MainMenu->EnableMenuItem(ID_Menu_InputFile,MF_ENABLED|MF_BYCOMMAND);//�����ļ�
		dlg->m_MainMenu->EnableMenuItem(ID_SETREPORTPARAM, MF_ENABLED | MF_BYCOMMAND);//�����ļ�shen
		AfxMessageBox(_T("���μ�������"));

	}
	//bEndDealingFlag_L=false;
	return 0;
}
void FuncCalculatingXml(CalHdmStruct &CalculatingHdm,bool bDuiQi,bool bLOrR,int &CalPointNum,double* pInDataX,double* pInDataY,int R400_Start,double* pScbzPoint_X,double* pScbzPoint_Y)
{

	int Count_Node=0;//������ʱ��23�������ű���
	int	Count_Range_Ang=0;//������ʱ��ʵ���������Ա�׼��Ϊ���ĵ����
	int Count_Zero;//�������λ��
	//int ind1=-1,ind2=0; 
	int ind1=0,ind2=0,indhd=0;
	int Count_Duan=0;//�������
	int i_sc;
	int index_xml_bz =0;					//��׼ϳĥ�����,��ʼ��Ϊ0
	double Pos_Rec_Aln_Y=0;
	double Ang_L=0,Ang_R=0,Para_Node_M=0,Para_Node_N=0;
	//double SCBZ_XML_X[Num_Node]={0},SCBZ_XML_Y[Num_Node]={0};
	double SCBZ_XML_X[Num_Node]={0},SCBZ_XML_Y[Num_Node]={0};
	double HDMJD[Num_Node]={0};//����澫��
	double XMLJD[Num_Node]={0};//ϳĥ������

	switch(CalculatingHdm.iTrackSel)
	{
	case  0://50��
		{
		
		int hs_Row1_50[6]={0};//6��Բ��ÿ��Բ���ϱ�׼��ĸ���	
		const double hs_Row2_50[6]={Hdm_50.Pos_BZ_R13L_X,Hdm_50.Pos_BZ_R80L_X,Hdm_50.Pos_BZ_R300L_X,//��׼Բ������
			Hdm_50.Pos_BZ_R300R_X,Hdm_50.Pos_BZ_R80R_X,Hdm_50.Pos_BZ_R13R_X};
		const double hs_Row3_50[6]={Hdm_50.Pos_BZ_R13_Y,Hdm_50.Pos_BZ_R80_Y,Hdm_50.Pos_BZ_R300_Y,
			Hdm_50.Pos_BZ_R300_Y,Hdm_50.Pos_BZ_R80_Y,Hdm_50.Pos_BZ_R13_Y};
		double hd_Row1_50[Num_Node_50]={0},hd_Row2_50[Num_Node_50]={0};//50��׼������
		for (int i=0;i<Num_Node_50;i++)
		{
			hd_Row1_50[i]=pScbzPoint_X[i];//��ʵ���׼�㸳ֵ��hd_Row1_50
			hd_Row2_50[i]=pScbzPoint_Y[i];
		}
		int hd_Row4[Num_Node_50]={0};//ʵ���ͱ�׼�����λ��
		int hd_Row3[Num_Node_50]={0};//��׼������һ����
		int ud,df,loc[Num_Node_50]={0};
		double hdy[Num_Node_50]={0};//��ֵ���	
		double Ang_BZ[Num_Node_50]={0};
		for (int i=0;i<SensorMaxPoint;i++)
		{
			if (pScbzPoint_X[i]<pInDataX[0]&&pScbzPoint_X[i+1]>pInDataX[0])
			{
				indhd++;
			} 
			else
			{
				break;
			}
		}
		//�ҳ�С�ڵ���pScbzPoint_Y[19]����������Ǹ��������
		for (int ind2Finder =0;ind2Finder<SensorMaxPoint;ind2Finder++)
		{
			if (pInDataY[ind2Finder] <pScbzPoint_Y[Num_Node_50-1])
			{
				ind2++;
			} 
			else if (pInDataY[ind2Finder] ==pScbzPoint_Y[Num_Node_50-1])
			{
				ind2++;
				break;
			}
			else if (pInDataY[ind2Finder] >pScbzPoint_Y[Num_Node_50-1])
			{
				break;
			}							
		}
		for (int i=0;i<Num_Node_50;i++)
		{
			if (hd_Row1_50[i]<=-23)
			{
				hs_Row1_50[0]=hs_Row1_50[0]+1;

				for (i_sc=ind1;i_sc<ind2;i_sc++)
				{

					if (pInDataX[i_sc]<hd_Row1_50[i])
					{
						hd_Row3[i]++;
					}
					else if (pInDataX[i_sc]==hd_Row1_50[i])
					{
						hd_Row3[i]++;
						break;
					}
					else if (pInDataX[i_sc]>hd_Row1_50[i])
					{
						break;
					}

				}

				Count_Node++;
				hd_Row3[i]=hd_Row3[i]+ind1-1;
			} 
			else if(hd_Row1_50[i]>-23&&hd_Row1_50[i]<=0)
			{
				hs_Row1_50[1]=hs_Row1_50[1]+1;
				for (i_sc=ind1;i_sc<ind2;i_sc++)
				{

					if (pInDataX[i_sc]<hd_Row1_50[i])
					{
						hd_Row3[i]++;
					}
					else if (pInDataX[i_sc]==hd_Row1_50[i])
					{
						hd_Row3[i]++;
						break;
					}
					else if (pInDataX[i_sc]>hd_Row1_50[i])
					{
						break;
					}

				}

				Count_Node++;
				hd_Row3[i]=hd_Row3[i]+ind1-1;
			}
			else if (hd_Row1_50[i]>0&&hd_Row1_50[i]<=23)
			{
				hs_Row1_50[2]=hs_Row1_50[2]+1;
				for (i_sc=ind1;i_sc<ind2;i_sc++)
				{

					if (pInDataX[i_sc]<hd_Row1_50[i])
					{
						hd_Row3[i]++;
					}
					else if (pInDataX[i_sc]==hd_Row1_50[i])
					{
						hd_Row3[i]++;
						break;
					}
					else if (pInDataX[i_sc]>hd_Row1_50[i])
					{
						break;
					}

				}

				Count_Node++;
				hd_Row3[i]=hd_Row3[i]+ind1-1;
			}
			else
			{
				hs_Row1_50[3]=hs_Row1_50[3]+1;
				for (i_sc=ind1;i_sc<ind2;i_sc++)
				{

					if (pInDataX[i_sc]<hd_Row1_50[i])
					{
						hd_Row3[i]++;
					}
					else if (pInDataX[i_sc]==hd_Row1_50[i])
					{
						hd_Row3[i]++;
						break;
					}
					else if (pInDataX[i_sc]>hd_Row1_50[i])
					{
						break;
					}

				}

				Count_Node++;
				hd_Row3[i]=hd_Row3[i]+ind1-1;
			}
		}
		for(int i=0;i<Num_Node;i++)
		{
			double x_temp[2]={pInDataX[hd_Row3[i]],pInDataX[hd_Row3[i]+1]};
			double y_temp[2]={pInDataY[hd_Row3[i]],pInDataY[hd_Row3[i]+1]};

			hdy[i]=Func_CZ(hd_Row1_50[i],x_temp,y_temp);
		}
		for (int hdRow4Finder=0;hdRow4Finder<Num_Node;hdRow4Finder++)
		{
			if (hdy[hdRow4Finder]>=hd_Row2_50[hdRow4Finder])
			{
				hd_Row4[hdRow4Finder]=0;
			} 
			else
			{
				hd_Row4[hdRow4Finder]=1;
			}
		}

		ind1 =0;
		ind2=R400_Start-5;
		index_xml_bz=0;
		Count_Node=0;
		int Sum_Row1_50=0;
		for (int i=0;i<indhd;i++)
		{
			SCBZ_XML_X[i]=hd_Row1_50[i];
			SCBZ_XML_Y[i]=hd_Row2_50[i];
			if(i<Num_Duan_50)
			{
				Sum_Row1_50+=hs_Row1_50[i];
				if(indhd>=Sum_Row1_50)
				{
					hs_Row1_50[i]=0;
				}
				else
				{
					hs_Row1_50[i]=Sum_Row1_50-indhd;
				}
			}				
			Count_Node++;//��ʼλ�������ǰ�ƶ�indhd��(�൱��Count_Node=indhd;)
		}
		Count_Zero=CalculatingHdm.Index_Zero-1;//C++����ż�һ
		for (Count_Duan=0;Count_Duan< Num_Duan_50;Count_Duan++)
		{
			if(hs_Row1_50[Count_Duan]!=0)
			{
				for (int i=0;i<hs_Row1_50[Count_Duan];i++)
				{
					if(Count_Node<Num_Node_50)
					{
						Ang_BZ[Count_Node]=atan((hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]))*180/Pi;
						if(Ang_BZ[Count_Node]<0)
							Ang_BZ[Count_Node]=Ang_BZ[Count_Node]+180;
						ud=hd_Row4[Count_Node];
						if (Count_Node==0)
						{
							df=ind1;
						}
						else
						{
							df=loc[Count_Node-1];
						}
						if (Count_Duan<2)
						{
							if (ud ==1)//����
							{								
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
												
											SCBZ_XML_X[Count_Node]=0;
											SCBZ_XML_Y[Count_Node]=hdy[Count_Node];
											XMLJD[Count_Node]=fabs(hdy[Count_Node]-hd_Row2_50[Count_Node]);
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

											SCBZ_XML_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_XML_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_XML_X[Count_Node]);
											XMLJD[Count_Node]=sqrt((SCBZ_XML_X[Count_Node]-hd_Row1_50[Count_Node])*(SCBZ_XML_X[Count_Node]-hd_Row1_50[Count_Node])+(SCBZ_XML_Y[Count_Node]-hd_Row2_50[Count_Node])*(SCBZ_XML_Y[Count_Node]-hd_Row2_50[Count_Node]));
											break;

										}

									}
									else
									{
										SCBZ_XML_X[Count_Node]=hd_Row1_50[Count_Node];
										SCBZ_XML_Y[Count_Node]=hd_Row2_50[Count_Node];
										XMLJD[Count_Node]=0;
									}

								}
								Count_Node++;
							}
							else
							{
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{

											SCBZ_XML_X[Count_Node]=0;
											SCBZ_XML_Y[Count_Node]=hdy[Count_Node];
											XMLJD[Count_Node]=fabs(hdy[Count_Node]-hd_Row2_50[Count_Node]);
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

											SCBZ_XML_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_XML_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_XML_X[Count_Node]);
											XMLJD[Count_Node]=sqrt((SCBZ_XML_X[Count_Node]-hd_Row1_50[Count_Node])*(SCBZ_XML_X[Count_Node]-hd_Row1_50[Count_Node])+(SCBZ_XML_Y[Count_Node]-hd_Row2_50[Count_Node])*(SCBZ_XML_Y[Count_Node]-hd_Row2_50[Count_Node]));
											break;

										}

									}
									else
									{
										SCBZ_XML_X[Count_Node]=hd_Row1_50[Count_Node];
										SCBZ_XML_Y[Count_Node]=hd_Row2_50[Count_Node];
										XMLJD[Count_Node]=0;
									}

								}
								Count_Node++;
							}
						} 
						else if (Count_Duan>=2&&Count_Duan<4)
						{
							if (ud ==1)//����
							{								
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{
											SCBZ_XML_X[Count_Node]=0;
											SCBZ_XML_Y[Count_Node]=hdy[Count_Node];
											XMLJD[Count_Node]=fabs(hdy[Count_Node]-hd_Row2_50[Count_Node]);
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

											SCBZ_XML_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_XML_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_XML_X[Count_Node]);
											XMLJD[Count_Node]=sqrt((SCBZ_XML_X[Count_Node]-hd_Row1_50[Count_Node])*(SCBZ_XML_X[Count_Node]-hd_Row1_50[Count_Node])+(SCBZ_XML_Y[Count_Node]-hd_Row2_50[Count_Node])*(SCBZ_XML_Y[Count_Node]-hd_Row2_50[Count_Node]));
											break;

										}

									}
									else
									{
										SCBZ_XML_X[Count_Node]=hd_Row1_50[Count_Node];
										SCBZ_XML_Y[Count_Node]=hd_Row2_50[Count_Node];
										XMLJD[Count_Node]=0;
									}

								}
								Count_Node++;
							}
							else//����
							{
								for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
								{
									Ang_L=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
									Ang_R=atan((hs_Row3_50[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_50[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
									if(Ang_L<0)
										Ang_L=Ang_L+180;
									if(Ang_R<0)
										Ang_R=Ang_R+180;
									if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
									{
										loc[Count_Node]=Count_Range_Ang;	
										if (Count_Node==Count_Zero)
										{

											SCBZ_XML_X[Count_Node]=0;
											SCBZ_XML_Y[Count_Node]=hdy[Count_Node];
											XMLJD[Count_Node]=fabs(hdy[Count_Node]-hd_Row2_50[Count_Node]);
											break;
										}
										else
										{
											Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
											Para_Node_N=(hs_Row3_50[Count_Duan]-hd_Row2_50[Count_Node])/(hs_Row2_50[Count_Duan]-hd_Row1_50[Count_Node]);

											SCBZ_XML_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_50[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_50[Count_Duan])/(Para_Node_N-Para_Node_M);
											SCBZ_XML_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_XML_X[Count_Node]);
											XMLJD[Count_Node]=sqrt((SCBZ_XML_X[Count_Node]-hd_Row1_50[Count_Node])*(SCBZ_XML_X[Count_Node]-hd_Row1_50[Count_Node])+(SCBZ_XML_Y[Count_Node]-hd_Row2_50[Count_Node])*(SCBZ_XML_Y[Count_Node]-hd_Row2_50[Count_Node]));
											break;

										}

									}
									else
									{
										SCBZ_XML_X[Count_Node]=hd_Row1_50[Count_Node];
										SCBZ_XML_Y[Count_Node]=hd_Row2_50[Count_Node];
										XMLJD[Count_Node]=0;
									}

								}
								Count_Node++;
							}
						}
						
						
					}
				}
			}
		}
		if (bLOrR==bFlagTrack_L)//����false����ʾ���
		{
			for (int i=0;i<Num_Node_50;i++)
			{
				Dist_Xmljd_L_50[i]=XMLJD[i];
				XmlScbz_XL_50[i]=SCBZ_XML_X[i];
				XmlScbz_YL_50[i]=SCBZ_XML_Y[i];
			}
		} 
		else if (bLOrR==bFlagTrack_R)
		{
			for (int i=0;i<Num_Node_50;i++)
			{
				Dist_Xmljd_R_50[i]=XMLJD[i];
				XmlScbz_XR_50[i]=SCBZ_XML_X[i];
				XmlScbz_YR_50[i]=SCBZ_XML_Y[i];
			}
		}


		break;
		}
	case  1://60��
		{

		
		int hs_Row1_60[6]={0};//6��Բ��ÿ��Բ���ϱ�׼��ĸ���	
		const double hs_Row2_60[6]={Hdm_60.Pos_BZ_R13L_X,Hdm_60.Pos_BZ_R80L_X,Hdm_60.Pos_BZ_R300L_X,//��׼Բ������
			Hdm_60.Pos_BZ_R300R_X,Hdm_60.Pos_BZ_R80R_X,Hdm_60.Pos_BZ_R13R_X};
		const double hs_Row3_60[6]={Hdm_60.Pos_BZ_R13_Y,Hdm_60.Pos_BZ_R80_Y,Hdm_60.Pos_BZ_R300_Y,
			Hdm_60.Pos_BZ_R300_Y,Hdm_60.Pos_BZ_R80_Y,Hdm_60.Pos_BZ_R13_Y};
		double hd_Row1_60[Num_Node]={0},hd_Row2_60[Num_Node]={0};//60��׼������
		for (int i=0;i<Num_Node;i++)
		{
			hd_Row1_60[i]=pScbzPoint_X[i];//��ʵ���׼�㸳ֵ��hd_Row1_60
			hd_Row2_60[i]=pScbzPoint_Y[i];
		}
		int hd_Row4[Num_Node]={0};//ʵ���ͱ�׼�����λ��
		int hd_Row3[Num_Node]={0};//��׼������һ����
		int ud,df,loc[Num_Node]={0};
		double hdy[Num_Node]={0};//��ֵ���	
		double Ang_BZ[Num_Node]={0};
		
		for (int i=0;i<SensorMaxPoint;i++)
		{
			if (pScbzPoint_X[i]<pInDataX[0]&&pScbzPoint_X[i+1]>pInDataX[0])
			{
				indhd++;
			} 
			else
			{
				break;
			}
		}

		//�ҳ�С�ڵ���pScbzPoint_Y[22]����������Ǹ��������
		for (int ind2Finder =0;ind2Finder<SensorMaxPoint;ind2Finder++)
		{
			if (pInDataY[ind2Finder] <pScbzPoint_Y[Num_Node-1])
			{
				ind2++;
			} 
			else if (pInDataY[ind2Finder] ==pScbzPoint_Y[Num_Node-1])
			{
				ind2++;
				break;
			}
			else if (pInDataY[ind2Finder] >pScbzPoint_Y[Num_Node-1])
			{
				break;
			}							
		}

		for (int i=0;i<Num_Node;i++)
			{
				if(hd_Row1_60[i]<=-25.35)
				{
					hs_Row1_60[0]=hs_Row1_60[0]+1;

					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;

				}
				else if (hd_Row1_60[i]>-25.35&&hd_Row1_60[i]<=-10)
				{
					hs_Row1_60[1]=hs_Row1_60[1]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else if (hd_Row1_60[i]>-10&&hd_Row1_60[i]<=0)
				{
					hs_Row1_60[2]=hs_Row1_60[2]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else if (hd_Row1_60[i]>0&&hd_Row1_60[i]<=10)
				{
					hs_Row1_60[3]=hs_Row1_60[3]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else if (hd_Row1_60[i]>10&&hd_Row1_60[i]<=25.35)
				{
					hs_Row1_60[4]=hs_Row1_60[4]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
				else
				{
					hs_Row1_60[5]=hs_Row1_60[5]+1;
					for (i_sc=ind1;i_sc<ind2;i_sc++)
					{

						if (pInDataX[i_sc]<hd_Row1_60[i])
						{
							hd_Row3[i]++;
						}
						else if (pInDataX[i_sc]==hd_Row1_60[i])
						{
							hd_Row3[i]++;
							break;
						}
						else if (pInDataX[i_sc]>hd_Row1_60[i])
						{
							break;
						}

					}
					
					Count_Node++;
					hd_Row3[i]=hd_Row3[i]+ind1-1;
				}
			}	

			for(int i=0;i<Num_Node;i++)
			{
				double x_temp[2]={pInDataX[hd_Row3[i]],pInDataX[hd_Row3[i]+1]};
				double y_temp[2]={pInDataY[hd_Row3[i]],pInDataY[hd_Row3[i]+1]};

				hdy[i]=Func_CZ(hd_Row1_60[i],x_temp,y_temp);
			}

			for (int hdRow4Finder=0;hdRow4Finder<Num_Node;hdRow4Finder++)
			{
				if (hdy[hdRow4Finder]>=hd_Row2_60[hdRow4Finder])
				{
					hd_Row4[hdRow4Finder]=0;
				} 
				else
				{
					hd_Row4[hdRow4Finder]=1;
				}
			}

			ind1 =0;
			ind2=R400_Start-5;

			//��ȡ����澫��
			//int Count_BZAng=0;
			index_xml_bz=0;
			Count_Node=0;
			int Sum_Row1_60=0;
			for (int i=0;i<indhd;i++)
			{
				SCBZ_XML_X[i]=hd_Row1_60[i];
				SCBZ_XML_Y[i]=hd_Row2_60[i];
				if(i<6)
				{
					Sum_Row1_60+=hs_Row1_60[i];
					if(indhd>=Sum_Row1_60)
					{
						hs_Row1_60[i]=0;
					}
					else
					{
						hs_Row1_60[i]=Sum_Row1_60-indhd;
					}
				}				
				Count_Node++;//��ʼλ�������ǰ�ƶ�indhd��(�൱��Count_Node=indhd;)
			}
			Count_Zero=CalculatingHdm.Index_Zero-1;//C++����ż�һ
			for (Count_Duan=0;Count_Duan< Num_Duan_60;Count_Duan++)
			{

				if(hs_Row1_60[Count_Duan]!=0)
				{
					for (int i=0;i<hs_Row1_60[Count_Duan];i++)
					{
						if(Count_Node<Num_Node)
						{
													
							Ang_BZ[Count_Node]=atan((hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]))*180/Pi;
							if(Ang_BZ[Count_Node]<0)
								Ang_BZ[Count_Node]=Ang_BZ[Count_Node]+180;
							ud=hd_Row4[Count_Node];
							//df�ĳ�ʼ������������������ж�����ǰ�棬����Ĭ�ϵ�һ����Ϊ���Ϸ�
							if (Count_Node==0)
							{
								df=ind1;
							}
							else
							{
								df=loc[Count_Node-1];
							}
							if (Count_Duan<3)//��
							{
								if (ud ==1)//����
								{
								
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
									{
										Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{
												/*double FenZi1,FenZi2;
												FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
												FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
												/*Dist_Node[Count_Node]=(FenZi1-FenZi2)/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);*/
												SCBZ_XML_X[Count_Node]=0;
												SCBZ_XML_Y[Count_Node]=hdy[Count_Node];
												XMLJD[Count_Node]=fabs(hdy[Count_Node]-hd_Row2_60[Count_Node]);
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

												SCBZ_XML_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_XML_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_XML_X[Count_Node]);
												//Dist_Node[Count_Node]=sqrt((SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node]));
												XMLJD[Count_Node]=sqrt((SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node]));
												break;

											}

										}
										else
										{
											SCBZ_XML_X[Count_Node]=hd_Row1_60[Count_Node];
											SCBZ_XML_Y[Count_Node]=hd_Row2_60[Count_Node];
											XMLJD[Count_Node]=0;
										}

									}
									//Pos_Xml_X[index_xml_bz]=SCBZ_XML_X[Count_Node];
									//Pos_Xml_Y[index_xml_bz]=SCBZ_XML_Y[Count_Node];
									////Dist_Hdm_Node[index_xml_bz]=Dist_Node[Count_Node];
									//index_xml_bz++;	
									Count_Node++;
								}
								else//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
									{
										Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{
												/*double FenZi1,FenZi2;
												FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
												FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
												SCBZ_XML_X[Count_Node]=0;
												SCBZ_XML_Y[Count_Node]=hdy[Count_Node];
												XMLJD[Count_Node]=fabs(hdy[Count_Node]-hd_Row2_60[Count_Node]);
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

												SCBZ_XML_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_XML_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_XML_X[Count_Node]);
												//Dist_Node[Count_Node]=sqrt((SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node]));
												XMLJD[Count_Node]=sqrt((SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node]));
												break;

											}
										}
										else
										{
											SCBZ_XML_X[Count_Node]=hd_Row1_60[Count_Node];
											SCBZ_XML_Y[Count_Node]=hd_Row2_60[Count_Node];
											XMLJD[Count_Node]=0;
										}
									}
									//Pos_Xml_X[index_xml_bz]=SCBZ_XML_X[Count_Node];
									//Pos_Xml_Y[index_xml_bz]=SCBZ_XML_Y[Count_Node];
									////Dist_Hdm_Node[index_xml_bz]=Dist_Node[Count_Node];
									//index_xml_bz++;	
									Count_Node++;
								}
							}
							else if (Count_Duan>=3&&Count_Duan<6)
							{
								if (ud==1)//����
								{
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
									{
										Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi+180;
										Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi+180;

										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{
												/*double FenZi1,FenZi2;
												FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
												FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
												SCBZ_XML_X[Count_Node]=0;
												SCBZ_XML_Y[Count_Node]=hdy[Count_Node];
												XMLJD[Count_Node]=fabs(hdy[Count_Node]-hd_Row2_60[Count_Node]);
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

												SCBZ_XML_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_XML_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_XML_X[Count_Node]);
												//Dist_Node[Count_Node]=sqrt((SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node]));
												XMLJD[Count_Node]=sqrt((SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node]));
												break;

											}
										}
										else
										{
											SCBZ_XML_X[Count_Node]=hd_Row1_60[Count_Node];
											SCBZ_XML_Y[Count_Node]=hd_Row2_60[Count_Node];
											XMLJD[Count_Node]=0;
										}
									}
									//Pos_Xml_X[index_xml_bz]=SCBZ_XML_X[Count_Node];
									//Pos_Xml_Y[index_xml_bz]=SCBZ_XML_Y[Count_Node];
									////Dist_Hdm_Node[index_xml_bz]=Dist_Node[Count_Node];
									//index_xml_bz++;	
									Count_Node++;
								}
								else//����
								{
									if (Count_Node==0)
									{
										df=ind1;
									}
									else
									{
										df=loc[Count_Node-1];
									}
									for (Count_Range_Ang=df;Count_Range_Ang<=ind2;Count_Range_Ang++)
									{
										Ang_L=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang]))*180/Pi;
										Ang_R=atan((hs_Row3_60[Count_Duan]-pInDataY[Count_Range_Ang+1])/(hs_Row2_60[Count_Duan]-pInDataX[Count_Range_Ang+1]))*180/Pi;
										if(Ang_L<0)
											Ang_L=Ang_L+180;
										if(Ang_R<0)
											Ang_R=Ang_R+180;
										if((Ang_BZ[Count_Node]>=Ang_L)&&(Ang_BZ[Count_Node]<=Ang_R))
										{
											loc[Count_Node]=Count_Range_Ang;	
											if (Count_Node==Count_Zero)
											{
												/*double FenZi1,FenZi2;
												FenZi1=(pInDataX[Count_Range_Ang]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang+1]-hd_Row2_60[Count_Node]);
												FenZi2=(pInDataX[Count_Range_Ang+1]-hd_Row1_60[Count_Node])*(pInDataY[Count_Range_Ang]-hd_Row2_60[Count_Node]);*/
												SCBZ_XML_X[Count_Node]=0;
												SCBZ_XML_Y[Count_Node]=hdy[Count_Node];
												XMLJD[Count_Node]=fabs(hdy[Count_Node]-hd_Row2_60[Count_Node]);
												break;
											}
											else
											{
												Para_Node_M=(pInDataY[Count_Range_Ang+1]-pInDataY[Count_Range_Ang])/(pInDataX[Count_Range_Ang+1]-pInDataX[Count_Range_Ang]);								//	�ⷽ�̵Ĳ���M��N
												Para_Node_N=(hs_Row3_60[Count_Duan]-hd_Row2_60[Count_Node])/(hs_Row2_60[Count_Duan]-hd_Row1_60[Count_Node]);

												SCBZ_XML_X[Count_Node]=(pInDataY[Count_Range_Ang+1]-hs_Row3_60[Count_Duan]-Para_Node_M*pInDataX[Count_Range_Ang+1]+Para_Node_N*hs_Row2_60[Count_Duan])/(Para_Node_N-Para_Node_M);
												SCBZ_XML_Y[Count_Node]=pInDataY[Count_Range_Ang+1]-Para_Node_M*(pInDataX[Count_Range_Ang+1]-SCBZ_XML_X[Count_Node]);
												//Dist_Node[Count_Node]=sqrt((SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node]));
												XMLJD[Count_Node]=sqrt((SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])*(SCBZ_XML_X[Count_Node]-hd_Row1_60[Count_Node])+(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node])*(SCBZ_XML_Y[Count_Node]-hd_Row2_60[Count_Node]));
												break;

											}
										}
										else
										{
											SCBZ_XML_X[Count_Node]=hd_Row1_60[Count_Node];
											SCBZ_XML_Y[Count_Node]=hd_Row2_60[Count_Node];
											XMLJD[Count_Node]=0;
										}
									}
									
									//Pos_Xml_X[index_xml_bz]=SCBZ_XML_X[Count_Node];
									//Pos_Xml_Y[index_xml_bz]=SCBZ_XML_Y[Count_Node];
									////Dist_Hdm_Node[index_xml_bz]=Dist_Node[Count_Node];
									//index_xml_bz++;	
									Count_Node++;
								}
							}
						}
				     } 				
				
			    }
				
			}

		break;
		}
	}
	if (bLOrR==bFlagTrack_L)//����false����ʾ���
	{
		for (int i=0;i<Num_Node;i++)
		{
			Dist_Xmljd_L[i]=XMLJD[i];
			XmlScbz_XL[i]=SCBZ_XML_X[i];
			XmlScbz_YL[i]=SCBZ_XML_Y[i];
		}
	} 
	else if (bLOrR==bFlagTrack_R)
	{
		for (int i=0;i<Num_Node;i++)
		{
			Dist_Xmljd_R[i]=XMLJD[i];
			XmlScbz_XR[i]=SCBZ_XML_X[i];
			XmlScbz_YR[i]=SCBZ_XML_Y[i];
		}
	}
}

LRESULT CHighPrecisionDlg::On2DMsgFunc_Xml_R(WPARAM wParam,LPARAM lParam)
{
	int nStNumNode;
	switch(g_TestInfo_R.TrackSel)
	{
	case 0://50��
		{
			nStNumNode=19;
			break;
		}

	case 1://60��
		{
			nStNumNode=23;
			break;
		}
	}
	unsigned i(0);
	double* pDataX = NULL;//T����˫�����͵�ָ�����pDateX
	double* pDataY = NULL;
	//�����ڴ�
	if(m_2DThreadParam_R.DataNum>0)
	{
		pDataX = new double[m_2DThreadParam_R.DataNum];//T����Ϊ�̲߳���������ݳ���
		pDataY = new double[m_2DThreadParam_R.DataNum];
		for (i=0;i<(unsigned)m_2DThreadParam_R.DataNum;i++)
		{
			pDataY[i] = -m_2DThreadParam_R.zData[i];//Tת���̲߳����������
			pDataX[i] =-m_2DThreadParam_R.xData[i] ;
		}
		m_pLineSerie_RT->ClearSerie();
		m_pLineSerie_RT->AddPoints(pDataX,pDataY,(unsigned)m_2DThreadParam_R.DataNum);

		//�ͷ�ָ��
		if (pDataX)
		{
			delete[] pDataX;
		}
		if (pDataY)
		{
			delete[] pDataY;
		}
	}
	
	//��������
	double* pXmlJd=NULL;
	double* pXmlAng=NULL;
	double* pHdmJd=NULL;
	pXmlJd=new double[nStNumNode];
	pXmlAng=new double[nStNumNode];
	pHdmJd=new double[nStNumNode];
	switch(g_TestInfo_R.TrackSel)
	{
	case 0:
		for (int j=0;j<nStNumNode;j++)
		{
			pXmlJd[j]=m_2DThreadParam_R.DistXml_50[j];
			pHdmJd[j]=m_2DThreadParam_R.DistHdm_50[j];
			pXmlAng[j]=Std_Ang_50[j];
		}
		break;
	case 1:
		for (int j=0;j<nStNumNode;j++)
		{
			pXmlJd[j]=m_2DThreadParam_R.DistXml[j];
			pHdmJd[j]=m_2DThreadParam_R.DistHdm[j];
			pXmlAng[j]=Std_Ang_60[j];
		}
		break;
	}	
	unsigned jjCnt(nStNumNode);
	m_pLineSerie_RB->ClearSerie();
	m_pLineSerie_RB->AddPoints(pXmlAng,pXmlJd,jjCnt);	//ϳĥ����ͼ
	m_PointSerie_RB->ClearSerie();
	m_PointSerie_RB->AddPoints(pXmlAng,pXmlJd,jjCnt);   //ϳĥ����ͼ
	if (pXmlJd)
	{
		delete[] pXmlJd;
		pXmlJd=NULL;
	}
	if (pXmlAng)
	{
		delete[] pXmlAng;
		pXmlAng=NULL;
	}
	if (pHdmJd)
	{
		delete[] pHdmJd;
		pHdmJd=NULL;
	}
	return 0;
}

LRESULT CHighPrecisionDlg::On2DMsgFunc_Xml_L(WPARAM wParam,LPARAM lParam)
{
	int nStNumNode;
	switch(g_TestInfo_L.TrackSel)
	{
	case 0://50��
		{
			nStNumNode=19;
			break;
		}

	case 1://60��
		{
			nStNumNode=23;
			break;
		}
	}
	unsigned i(0);
	double* pDataX = NULL;//T����˫�����͵�ָ�����pDateX
	double* pDataY = NULL;
	//�����ڴ�
	if(m_2DThreadParam_L.DataNum>0)
	{
		pDataX = new double[m_2DThreadParam_L.DataNum];//T����Ϊ�̲߳���������ݳ���
		pDataY = new double[m_2DThreadParam_L.DataNum];
		for (i=0;i<(unsigned)m_2DThreadParam_L.DataNum;i++)
		{
			pDataY[i] = -m_2DThreadParam_L.zData[i];//Tת���̲߳����������
			pDataX[i] =m_2DThreadParam_L.xData[i] ;
		}
		m_pLineSerie_LT->ClearSerie();
		m_pLineSerie_LT->AddPoints(pDataX,pDataY,(unsigned)m_2DThreadParam_L.DataNum);
		
		//�ͷ�ָ��
		if (pDataX)
		{
			delete[] pDataX;
		}
		if (pDataY)
		{
			delete[] pDataY;
		}
	}
	
	//��������
	double* pXmlJd=NULL;
	double* pXmlAng=NULL;
	double* pHdmJd=NULL;
	pXmlJd=new double[nStNumNode];
	pXmlAng=new double[nStNumNode];
	pHdmJd=new double[nStNumNode];
	switch(g_TestInfo_L.TrackSel)
	{
	case 0:
		for (int j=0;j<nStNumNode;j++)
		{
			pXmlJd[j]=m_2DThreadParam_L.DistXml_50[j];
			pHdmJd[j]=m_2DThreadParam_L.DistHdm_50[j];
			pXmlAng[j]=Std_Ang_50[j];
		}
		break;
	case 1:
		for (int j=0;j<nStNumNode;j++)
		{
			pXmlJd[j]=m_2DThreadParam_L.DistXml[j];
			pHdmJd[j]=m_2DThreadParam_L.DistHdm[j];
			pXmlAng[j]=Std_Ang_60[j];
		}
		break;
	}
	
	unsigned jjCnt(nStNumNode);
	m_pLineSerie_LB->ClearSerie();
	m_pLineSerie_LB->AddPoints(pXmlAng,pXmlJd,jjCnt);//������ͼ
	m_PointSerie_LB->ClearSerie();
	m_PointSerie_LB->AddPoints(pXmlAng,pXmlJd,jjCnt);//������ͼ
	
	if (pXmlJd)
	{
		delete[] pXmlJd;
		pXmlJd=NULL;
	}
	if (pXmlAng)
	{
		delete[] pXmlAng;
		pXmlAng=NULL;
	}
	if (pHdmJd)
	{
		delete[] pHdmJd;
		pHdmJd=NULL;
	}
	
	
	return 0;
}

LRESULT CHighPrecisionDlg::On2DMsgFunc_XmlScbz_R(WPARAM wParam,LPARAM lParam)
{	
	double* pScbzDataX = NULL;//T����˫�����͵�ָ�����pDateX
	double* pScbzDataY = NULL;
	//�����ڴ�
	if(m_2DThreadParam_R.WdqNum>0)
	{
		pScbzDataX = new double[m_2DThreadParam_R.WdqNum];//T����Ϊ�̲߳���������ݳ���
		pScbzDataY = new double[m_2DThreadParam_R.WdqNum];
		for (int i=0;i<m_2DThreadParam_R.WdqNum;i++)
		{
			pScbzDataY[i] = -m_2DThreadParam_R.WdqData_Y[i];//Tת���̲߳����������
			pScbzDataX[i] =-m_2DThreadParam_R.WdqData_X[i] ;
		}
		m_pLineSerieStd_RT->ClearSerie();
		m_pLineSerieStd_RT->AddPoints(pScbzDataX,pScbzDataY,m_2DThreadParam_R.WdqNum);

		//�ͷ�ָ��
		if (pScbzDataX)
		{
			delete[] pScbzDataX;
		}
		if (pScbzDataY)
		{
			delete[] pScbzDataY;
		}
		
	}
	return 0;
}

LRESULT CHighPrecisionDlg::On2DMsgFunc_XmlScbz_L(WPARAM wParam,LPARAM lParam)
{
	double* pScbzDataX = NULL;//T����˫�����͵�ָ�����pDateX
	double* pScbzDataY = NULL;
	//�����ڴ�
	if(m_2DThreadParam_L.WdqNum>0)
	{
		pScbzDataX = new double[m_2DThreadParam_L.WdqNum];//T����Ϊ�̲߳���������ݳ���
		pScbzDataY = new double[m_2DThreadParam_L.WdqNum];
		for (int i=0;i<m_2DThreadParam_L.WdqNum;i++)
		{
			pScbzDataY[i] = -m_2DThreadParam_L.WdqData_Y[i];//Tת���̲߳����������
			pScbzDataX[i] =m_2DThreadParam_L.WdqData_X[i] ;
		}
		m_pLineSerieStd_LT->ClearSerie();
		m_pLineSerieStd_LT->AddPoints(pScbzDataX,pScbzDataY,m_2DThreadParam_L.WdqNum);

		//�ͷ�ָ��
		if (pScbzDataX)
		{
			delete[] pScbzDataX;
		}
		if (pScbzDataY)
		{
			delete[] pScbzDataY;
		}
	  }
	
		
	return 0;
}

void CHighPrecisionDlg::OnSetSensorPara()
{
	// TODO: �ڴ���������������
	if(g_bFlagSensorL/*&&g_bFlagSensorR*/)
	{
		CSetParameterDlg obj_SetSensorPara;
		obj_SetSensorPara.DoModal();
	}
	else
		OnBnClickedButtonLink();
}

void CHighPrecisionDlg::OnBnClickedButtonInputfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	TCHAR szFilter[] =_T("�����ļ�(*.Hnu)|*.Hnu");
	CString lpszFileName = _T("D:\\Result\\.Hnu");
	CFileDialog OpenDlg( TRUE, NULL, lpszFileName/*LastFilePath*/, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL,0,FALSE);
	HWND myWnd=OpenDlg.m_hWnd;
	if(OpenDlg.DoModal()==IDOK)
	{
		
		//skinppSetNoSkinHwnd(OpenDlg,TRUE);
		
		CString HnuFileName( OpenDlg.GetPathName() );
		//��ȡ��ǰĿ¼
		curFileDirection=HnuFileName;
		if (curFileDirection.find("ϳĥ��")!=string::npos)
		{
			IsAfterMillFlag=TRUE;
		}
		else
			IsAfterMillFlag=FALSE;
		int tmpIndex=curFileDirection.rfind('\\');
		if (tmpIndex!=string::npos)
		{
			curFileDirection.erase(tmpIndex+1,curFileDirection.size()-tmpIndex-1);
		}
		else
			curFileDirection=".\\";         //��ǰĿ¼���Ǹ�Ŀ¼
		//�ָ�ʱ��
		int TimeRightFlag=curFileDirection.rfind('\\');
		TimeRightFlag=curFileDirection.rfind('\\',TimeRightFlag-1);
		int TimeLeftFlag=curFileDirection.rfind('\\',TimeRightFlag-1);
		string tmpDectectTime=curFileDirection.substr(TimeLeftFlag+1,TimeRightFlag-TimeLeftFlag-1);
		CString tmptime = curFileDirection.substr(TimeRightFlag+1,8).c_str();
		int itmp=tmptime.Replace("-",":");
		CsDetectTime=tmpDectectTime.substr(0,tmpDectectTime.find("ϳĥ")).c_str();
		CsDetectTime=CsDetectTime+"-"+tmptime;
		//CsDetectTime.Format("%s-%s",CsDetectTime,tmptime);

		CStdioFile myFile;
		//���ȳ�ʼ��
		m_fileLineVec.clear();
		m_RightfileLineVec.clear();
		m_fileBeforeLineVec.clear();
		m_RightfileBeforeLineVec.clear(); 
		m_HdmLineVec.clear();
		m_RightHdmLineVec.clear();
		m_XmlLineVec.clear();
		m_RightHdmLineVec.clear();
		m_startAndEndVec.clear();
		string startLine;
		string endLine;
		string strLine; 
		CString TmpLine;
		CString FileNameStr;
		if (myFile.Open(HnuFileName,CFile::modeCreate |CFile::modeNoTruncate|CFile::modeReadWrite,nullptr,nullptr))
		{
			m_fileLineVec.clear();
			m_RightfileLineVec.clear();
			m_fileBeforeLineVec.clear();
			m_RightfileBeforeLineVec.clear();
			m_HdmLineVec.clear();
			m_RightHdmLineVec.clear();
			m_XmlLineVec.clear();
			m_RightXmlLineVec.clear();
			while(myFile.ReadString(TmpLine))
			{	
				string strTmpLine=TmpLine;
				if (strTmpLine.find("-����ʵ���׼��")!=string::npos)
				{
					m_fileLineVec.push_back(TmpLine);
				}
				else if (strTmpLine.find("-����ʵ���׼��")!=string::npos)
				{
					m_RightfileLineVec.push_back(TmpLine);
				}
				else if (strTmpLine.find("-ǰ��ʵ���׼��")!=string::npos)
				{
					m_fileBeforeLineVec.push_back(TmpLine);
				}
				else if(strTmpLine.find("-ǰ��ʵ���׼��")!=string::npos)
				{
					m_RightfileBeforeLineVec.push_back(TmpLine);
				}
				else if(strTmpLine.find("-ǰ�����澫��")!=string::npos)
				{
					m_HdmLineVec.push_back(TmpLine);
				}
				else if(strTmpLine.find("-ǰ�Һ���澫��")!=string::npos)
				{
					m_RightHdmLineVec.push_back(TmpLine);
				}
				else if(strTmpLine.find("-�������澫��")!=string::npos)
				{
					m_HdmLineVec.push_back(TmpLine);
				}
				else if(strTmpLine.find("-���Һ���澫��")!=string::npos)
				{
					m_RightHdmLineVec.push_back(TmpLine);
				}
				else if(strTmpLine.find("-����ϳĥ������")!=string::npos)
				{
					m_XmlLineVec.push_back(TmpLine);
				}
				else if(strTmpLine.find("-����ϳĥ������")!=string::npos)
				{
					m_RightXmlLineVec.push_back(TmpLine);
				}
			}
			//ϳĥǰʱ��m_fileLineVec������ϳĥǰ�ļ����Ա�����ǰ�����ͳһ
			if (!IsAfterMillFlag)  
			{
				m_fileLineVec=m_fileBeforeLineVec;
				m_RightfileLineVec=m_RightfileBeforeLineVec;
			}
			if (m_fileLineVec.size()==0)
			{
				MessageBox(_T("����ϳĥ�ļ������ڣ�������ѡ��"),_T("�ֹ�����������"));
				myFile.Close();
				return;
			}
			//�ָ��߱�
			strLine=m_fileLineVec[0];
			CsDetectRoad=strLine.substr(0,strLine.find('-')).c_str();
			CsDirection =CsDetectRoad.Right(2);
			CsDetectRoad=CsDetectRoad.Left(CsDetectRoad.GetLength()-2);
			//�ָ����
			char OutlineType=strLine.back();
			if (OutlineType=='a')
			{
				CsDetectGuiXing="50Kg/m";
				m_OutlineType=0;
				precisionPointNum=PRECISION_NUM_50;
				//double tmp50Pos[PRECISION_NUM_50]={-10,-4,-3,-2,-1,0,1,2,3,4,10,20,30,40,50,60,70,80,90};
				double tmp50Pos[PRECISION_NUM_50]={10,4,3,2,1,0,-1,-2,-3,-4,-10,-20,-30,-40,-50,-60,-70,-80,-90};
				for (int i=0;i<PRECISION_NUM_50;++i)
				{
					f60leftOutlinePos[i]=tmp50Pos[i];
					f60RightOutlinePos[i]=tmp50Pos[i];
				}
			}
			else if (OutlineType=='b')
			{
				CsDetectGuiXing="60Kg/m";
				m_OutlineType=1;
				precisionPointNum=PRECISION_NUM_60;
				//double tmpPos[PRECISION_NUM_60]={-13,-10,-8,-6,-4,-2,-1,0,1,2,4,6,8,10,13,20,30,40,50,60,70,80,87};
				double tmpPos[PRECISION_NUM_60]={13,10,8,6,4,2,1,0,-1,-2,-4,-6,-8,-10,-13,-20,-30,-40,-50,-60,-70,-80,-87};

				for (int i=0;i<PRECISION_NUM_60;++i)
				{
					f60leftOutlinePos[i]=tmpPos[i];
					f60RightOutlinePos[i]=tmpPos[i];
				}
			}
			else
			{
				CsDetectGuiXing="75Kg/m";
				m_OutlineType=2;
				precisionPointNum=PRECISION_NUM_75;

			}
			if (m_fileLineVec.size()==1)  //����ϳĥֻ��һ���ļ������
			{
				strLine=m_fileLineVec[0];
				int firstFlag=strLine.find('-');
				int lastFlag=strLine.rfind('-');
				strLine=strLine.substr(firstFlag+1,lastFlag-firstFlag-1);  //���ս����000000-000500M-
				FileNameStr=strLine.c_str();
			}
			else                                 //����ϳĥ�ж���ļ�
			{
				startLine=m_fileLineVec[0];
				endLine=m_fileLineVec[m_fileLineVec.size()-1];
				int firstFlag=startLine.find('-');
				int lastFlag=endLine.rfind('-');
				strLine=startLine.substr(firstFlag+1,7)+endLine.substr(lastFlag-7,8);//���ս����000000-000500M-
				FileNameStr=strLine.c_str();
			}
			myFile.Close();
			//�ָ���ʼ��ֹ���
			CsDetectBegin=strLine.substr(0,6).c_str();
			int tmpDetectBegin=atoi(CsDetectBegin);
			CsDetectBegin.Format("%s%d+%d",CsDetectRoad,tmpDetectBegin/1000,tmpDetectBegin%1000);
			CsDetectEnd=strLine.substr(7,6).c_str();
			int tmpDetectEnd=atoi(CsDetectEnd);
			CsDetectEnd.Format("%s%d+%d",CsDetectRoad,tmpDetectEnd/1000,tmpDetectEnd%1000);
			CsTongjiInterval.Format("%s-%s",CsDetectBegin,CsDetectEnd);
		}
		FileNameStr.Format("�ļ�����%s-%sM",CsDetectBegin,CsDetectEnd);
		if (IsAfterMillFlag)
		{
			FileNameStr+="ϳĥ������";
		}
		else
		{
			FileNameStr+="ϳĥǰ����";
		}
		m_List_FileName.ResetContent();
		CString tmpInfo;
		m_List_FileName.InsertString(0,FileNameStr);
		tmpInfo.Format("���ʱ�䣺 %s",CsDetectTime);
		m_List_FileName.InsertString(1,tmpInfo);
		tmpInfo.Format("��/���У� %s��",CsDirection);
		m_List_FileName.InsertString(2,tmpInfo);
		tmpInfo.Format("��ʼ��̣� %s",CsDetectBegin);
		m_List_FileName.InsertString(3,tmpInfo);
		tmpInfo.Format("��ֹ��̣� %s",CsDetectEnd);
		m_List_FileName.InsertString(4,tmpInfo);
		tmpInfo.Format("���ͣ� %s",CsDetectGuiXing);
		m_List_FileName.InsertString(5,tmpInfo);


		//��ȡ��ʼ���
		vector<double> tmpStartEndVec(2,0.0);
		for (unsigned int i=0;i<m_fileLineVec.size();++i)
		{
			CString ClhSketchPath="";
			ClhSketchPath.Format("%s\\%s.txt",curFileDirection.c_str(),m_fileLineVec[i]);
			//����������ȡ�ļ���������//
			CStdioFile fMeasureFile;
			if(fMeasureFile.Open(ClhSketchPath, CFile::modeRead))
			{
				//��ȡ��ʼ���
				CString strLinetemp;
				fMeasureFile.ReadString(strLinetemp);
				char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
				char *strtemp = NULL;  
				strtemp = strtok(str, " ");  
				char *TopData = strtemp; 
				tmpStartEndVec[0]=atof(TopData);

				//��ȡ�������
				fMeasureFile.Seek(-40,CFile::end);
				fMeasureFile.ReadString(strLinetemp);
				if (fMeasureFile.ReadString(strLinetemp))
				{
					char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
					char *strtemp = NULL;  
					strtemp = strtok(str, " ");  
					char *EndData = strtemp; 
					tmpStartEndVec[1]=atof(EndData);
				}
				m_startAndEndVec.push_back(tmpStartEndVec);
				fMeasureFile.Close();
			}
		}
		vector<vector<double>> m_RightstartAndEndVec;
		for (unsigned int i=0;i<m_RightfileLineVec.size();++i)
		{
			CString RightClhSketchPath="";
			RightClhSketchPath.Format("%s\\%s.txt",curFileDirection.c_str(),m_RightfileLineVec[i]);
			//����������ȡ�ļ���������//
			CStdioFile fMeasureFile;
			if(fMeasureFile.Open(RightClhSketchPath, CFile::modeRead))
			{
				//��ȡ��ʼ���
				CString strLinetemp;
				fMeasureFile.ReadString(strLinetemp);
				char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
				char *strtemp = NULL;  
				strtemp = strtok(str, " ");  
				char *TopData = strtemp; 
				tmpStartEndVec[0]=atof(TopData);

				//��ȡ�������
				fMeasureFile.Seek(-40,CFile::end);
				fMeasureFile.ReadString(strLinetemp);
				if (fMeasureFile.ReadString(strLinetemp))
				{
					char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
					char *strtemp = NULL;  
					strtemp = strtok(str, " ");  
					char *EndData = strtemp; 
					tmpStartEndVec[1]=atof(EndData);
				}
				m_RightstartAndEndVec.push_back(tmpStartEndVec);
				fMeasureFile.Close();
			}
		}
		if (m_startAndEndVec.empty())
		{
			MessageBox(_T("ϳĥ�ļ�����"),_T("�ֹ�����������"));
			return;
		}
		//if (m_RightstartAndEndVec.back().back()<m_startAndEndVec.back().back())
		//{
		//	m_startAndEndVec=m_RightstartAndEndVec;
		//}
		m_Edit_Distance=m_startAndEndVec.at(0).at(0);
		m_Edit_DistanceReal=m_Edit_Distance;
		//�������
		CString strCurDist;
		int iK=(int)m_Edit_DistanceReal/1000;
		double iD=m_Edit_DistanceReal-1000*iK;
		m_edit_distance_str.Format("%0.1f", (float)iD);
		m_edit_distance2_str.Format("%d", (int)iK);
		m_Edit_Distance2 = iK;
		//string tmpDetectRoad=CsDetectRoad;
		//tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
		strCurDist.Format("%s%d + %0.1f",CsDetectRoad,iK,iD);
		SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
		UpdateData(FALSE);
		UpdateModelSelInfo((string)FileNameStr);
		ResetAllData();
		m_havePressAnalyse=FALSE;
	}
}

// ���·���ģʽѡ����Ϣ
void CHighPrecisionDlg::UpdateModelSelInfo(string strFileName)
{
	m_Combo_ModelSel.ResetContent();
	if (IsAfterMillFlag)
	{
		vector<CString> ModelForAfterMillVec(5,"");
		ModelForAfterMillVec[0]="�����������澫��";
		ModelForAfterMillVec[1]="�������澫��ͳ��ֵ";
		ModelForAfterMillVec[2]="��������ϳĥ��";
		ModelForAfterMillVec[3]="����ϳĥ��ͳ��ֵ";
		ModelForAfterMillVec[4]="������������";
		for (unsigned int i=0;i<ModelForAfterMillVec.size();++i)
		{
			m_Combo_ModelSel.InsertString(i,ModelForAfterMillVec[i]);
		}
	}
	else 
	{
		vector<CString> ModelForBeforeMillVec(3,"");
		ModelForBeforeMillVec[0]="�����������澫��";
		ModelForBeforeMillVec[1]="�������澫��ͳ��ֵ";
		ModelForBeforeMillVec[2]="������������";
		for (unsigned int i=0;i<ModelForBeforeMillVec.size();++i)
		{
			m_Combo_ModelSel.InsertString(i,ModelForBeforeMillVec[i]);
		}
	}
	m_Combo_ModelSel.SetCurSel(0);
	m_List_ResultInfo.DeleteColumn(2);
	m_List_ResultInfo.DeleteColumn(1);
	m_List_ResultInfo.DeleteColumn(0);
	m_List_ResultInfo.InsertColumn(0,_T("�Ƕ�"),LVCFMT_CENTER,45,0);
	m_List_ResultInfo.InsertColumn(1,_T("���Ͼ���"),LVCFMT_CENTER,(rect.Width()-45)/2,1);
	m_List_ResultInfo.InsertColumn(2,_T("�Һ�Ͼ���"),LVCFMT_CENTER,(rect.Width()-45)/2,2);	
}

// �����пɵ����������³�ʼ��
int CHighPrecisionDlg::ResetAllData(void)
{
	UpdateData(TRUE);
	for (unsigned int i=0;i<localFileHdmVec.size();++i)
	{
		if (localFileHdmVec[i]!=NULL)
		{
			delete [] localFileHdmVec[i];
			localFileHdmVec[i]=NULL;
		}
		if (RightlocalFileHdmVec[i]!=NULL)
		{
			delete [] RightlocalFileHdmVec[i];
			RightlocalFileHdmVec[i]=NULL;
		}
	}

	currentFileIndex=0;
	m_PrecisionFileOffset=0;
	m_LeftOutLineFileOffset=0;
	m_LeftMillingFileOffset=0;
	m_LeftBeforeOutlineFileOffset=0;
	m_RightPrecisionFileOffset=0;
	m_RightOutLineFileOffset=0;
	m_RightMillingFileOffset=0;
	m_RightBeforeOutlineFileOffset=0;
	m_curOverValueIndex=0;
	OverValueHdmVec.clear();      //�����������
	RightOverValueHdmVec.clear();
	m_Edit_DistanceReal=m_Edit_Distance;
	//���ݷ���ģʽ�ı����ؼ��ı仯
	int curSelIndex=m_Combo_ModelSel.GetCurSel();
	GetDlgItem(IDC_STATIC10)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC12)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_EDIT_Distance)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_Distance2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_MIlEAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DISTANCE_LINE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_SPIN1)->ShowWindow(SW_SHOW);

	pAxisLeft1->SetAutomatic(FALSE);
	pAxisLeft1->SetMinMax(-35,5);
	pAxisBottom1->SetAutomatic(FALSE);
	pAxisBottom1->SetMinMax(-30,40);
	pAxisBottom1->SetInverted(FALSE);

	pAxisLeft2->SetAutomatic(FALSE);
	pAxisLeft2->SetMinMax(-35,5);
	pAxisBottom2->SetAutomatic(FALSE);
	pAxisBottom2->SetMinMax(-40,30);
	pAxisBottom2->SetInverted(FALSE);

	pAxisLeft3->SetAutomatic(true);
	pAxisLeft3->SetMinMax(-2,2);
	pAxisBottom3->SetAutomatic(false);
	pAxisBottom3->SetMinMax(-90,20);
	pAxisBottom3->SetInverted(TRUE);

	pAxisLeft4->SetAutomatic(true);
	pAxisBottom4->SetAutomatic(false);
	pAxisBottom4->SetMinMax(-90,20);
	pAxisBottom4->SetInverted(FALSE);

	if (IsAfterMillFlag)
	{
		switch(curSelIndex)
		{
		case 0:
		case 2:
			//�����£���������ϵ��ʾ
			GetDlgItem(IDC_CHARTCTRL3)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHARTCTRL4)->ShowWindow(SW_SHOW);
			m_Combo_TotalDistance.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_TotalDistance)->ShowWindow(SW_HIDE);
			break;
		case 4:
			//�����£���������ϵ��ʾ
			GetDlgItem(IDC_CHARTCTRL3)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHARTCTRL4)->ShowWindow(SW_SHOW);
			m_Combo_TotalDistance.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_TotalDistance)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC10)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC12)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_Distance)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_Distance2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_MIlEAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_DISTANCE_LINE)->ShowWindow(SW_HIDE);
			break;
		case 1:
		case 3:
			//�����£���������ϵ����
			GetDlgItem(IDC_CHARTCTRL3)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHARTCTRL4)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_TotalDistance)->ShowWindow(SW_SHOW);
			m_Combo_TotalDistance.ResetContent();
			m_Combo_TotalDistance.ShowWindow(SW_SHOW);
			GetDlgItem(IDC_SPIN1)->ShowWindow(SW_HIDE);
			//��������ͳ�Ƽ��
			m_Combo_TotalDistance.InsertString(0,"10M");
			m_Combo_TotalDistance.InsertString(1,"50M");
			m_Combo_TotalDistance.InsertString(2,"100M");
			m_Combo_TotalDistance.InsertString(3,"ȫ��");
			m_Combo_TotalDistance.SetCurSel(3);
			pAxisLeft1->SetAutomatic(FALSE);
			pAxisLeft1->SetMinMax(-35,5);
			pAxisBottom1->SetAutomatic(FALSE);
			pAxisBottom1->SetMinMax(-30,40);
			pAxisBottom1->SetInverted(FALSE);
			pAxisLeft2->SetAutomatic(FALSE);
			pAxisLeft2->SetMinMax(-35,5);
			pAxisBottom2->SetAutomatic(FALSE);
			pAxisBottom2->SetMinMax(-40,30);
			pAxisBottom2->SetInverted(FALSE);
			break;
		}
	}
	else
	{
		switch(curSelIndex)
		{
		case 0:
			//�����£���������ϵ��ʾ
			GetDlgItem(IDC_CHARTCTRL3)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHARTCTRL4)->ShowWindow(SW_SHOW);
			m_Combo_TotalDistance.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_TotalDistance)->ShowWindow(SW_HIDE);
			break;
		case 2:
			//�����£���������ϵ��ʾ
			GetDlgItem(IDC_CHARTCTRL3)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHARTCTRL4)->ShowWindow(SW_SHOW);
			m_Combo_TotalDistance.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_TotalDistance)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC10)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC12)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_Distance)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_Distance2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_MIlEAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_DISTANCE_LINE)->ShowWindow(SW_HIDE);
			break;
		case 1:
			//�����£���������ϵ����
			GetDlgItem(IDC_CHARTCTRL3)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHARTCTRL4)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_TotalDistance)->ShowWindow(SW_SHOW);
			m_Combo_TotalDistance.ResetContent();
			m_Combo_TotalDistance.ShowWindow(SW_SHOW);
			GetDlgItem(IDC_SPIN1)->ShowWindow(SW_HIDE);
			//��������ͳ�Ƽ��
			m_Combo_TotalDistance.InsertString(0,"10M");
			m_Combo_TotalDistance.InsertString(1,"50M");
			m_Combo_TotalDistance.InsertString(2,"100M");
			m_Combo_TotalDistance.InsertString(3,"ȫ��");
			m_Combo_TotalDistance.SetCurSel(3);
			pAxisLeft1->SetAutomatic(FALSE);
			pAxisLeft1->SetMinMax(-35,5);
			pAxisBottom1->SetAutomatic(FALSE);
			pAxisBottom1->SetMinMax(-30,40);
			pAxisBottom1->SetInverted(FALSE);
			pAxisLeft2->SetAutomatic(FALSE);
			pAxisLeft2->SetMinMax(-35,5);
			pAxisBottom2->SetAutomatic(FALSE);
			pAxisBottom2->SetMinMax(-40,30);
			pAxisBottom2->SetInverted(FALSE);
			break;
		}
	}



	allSeriesClear();
	m_ChartCtrl_LeftDown.RefreshCtrl();
	m_ChartCtrl_RightDown.RefreshCtrl();
	m_ChartCtrl_LeftTop.RefreshCtrl();
	m_ChartCtrl_RightTop.RefreshCtrl();
	
	return 0;
}

void CHighPrecisionDlg::OnBnClickedButtonAnalyze()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_havePressAnalyse && !m_startAndEndVec.empty())
	{
		m_havePressAnalyse=TRUE;
		UpdateData(TRUE);

		m_LeftOutLineFileOffset=0;
		m_PrecisionFileOffset=0;
		m_LeftMillingFileOffset=0;
		m_LeftBeforeOutlineFileOffset=0;
		m_RightOutLineFileOffset=0;
		m_RightMillingFileOffset=0;
		m_RightBeforeOutlineFileOffset=0;
		m_RightPrecisionFileOffset=0;
		int modelSelIndex=m_Combo_ModelSel.GetCurSel();
		isCreateCad=FALSE;
		bTongJi=FALSE;
		bChaoXian=FALSE;

		CHeaderCtrl* pHDCtrl=m_List_ResultInfo.GetHeaderCtrl();
		//��ͷ�ṹ��
		HDITEM hditem;
		enum {SizeofBuffer =256};
		TCHAR strHD[SizeofBuffer];
		hditem.mask=HDI_TEXT;
		hditem.pszText=strHD;
		hditem.cchTextMax=SizeofBuffer;
		pHDCtrl->GetItem(1,&hditem);
		hditem.pszText=_T("����澫��");
		pHDCtrl->SetItem(1,&hditem);
		HDITEM hditem2;
		TCHAR strHD2[SizeofBuffer];
		hditem2.mask=HDI_TEXT;
		hditem2.pszText=strHD2;
		hditem2.cchTextMax=SizeofBuffer;
		pHDCtrl->GetItem(2,&hditem2);
		hditem2.pszText=_T("�Ҷ��澫��");
		pHDCtrl->SetItem(2,&hditem2);
		m_ChartCtrl_LeftTop.GetTitle()->RemoveAll();
		m_ChartCtrl_LeftTop.GetTitle()->AddString("�������");
		m_ChartCtrl_RightTop.GetTitle()->RemoveAll();
		m_ChartCtrl_RightTop.GetTitle()->AddString("�ҹ�����");
		pAxisBottom1->GetLabel()->SetText(_T("���(mm)"));
		pAxisBottom2->GetLabel()->SetText(_T("���(mm)"));


		//�����ұߵ���Ϣ����ʾ
		if (IsAfterMillFlag)
		{
			if (modelSelIndex==0 || modelSelIndex==2)
			{
				vector<CString> tmpMillingPrecision(precisionPointNum,"");
				m_List_ResultInfo.DeleteAllItems();
				for (int i=0;i<precisionPointNum;++i)
				{
					tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
					m_List_ResultInfo.InsertItem(i,tmpMillingPrecision[i]);
				}
			}
			else if (modelSelIndex==1)
			{
				vector<CString> tmpMillingPrecision(precisionPointNum,"");
				m_List_ResultInfo.DeleteAllItems();
				m_List_ResultInfo.InsertItem(0,"�����");
				m_List_ResultInfo.InsertItem(1,"���ֵ");
				for (int i=0;i<precisionPointNum;++i)
				{
					tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
					m_List_ResultInfo.InsertItem(i+2,tmpMillingPrecision[i]);
				}
				//��ʾƽ��ֵ
				m_List_ResultInfo.InsertItem(precisionPointNum+2,"ƽ��ֵ");
				for (int i=0;i<precisionPointNum;++i)
				{
					tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
					m_List_ResultInfo.InsertItem(i+precisionPointNum+3,tmpMillingPrecision[i]);
				}

				m_ChartCtrl_LeftTop.GetTitle()->RemoveAll();
				m_ChartCtrl_LeftTop.GetTitle()->AddString("�����");
				m_ChartCtrl_RightTop.GetTitle()->RemoveAll();
				m_ChartCtrl_RightTop.GetTitle()->AddString("�����");

				pAxisBottom1->GetLabel()->SetText(_T("�Ƕ�(��)"));
				pAxisBottom1->SetMinMax(-90,20);
				pAxisBottom1->SetInverted(TRUE);
				pAxisLeft1->SetMinMax(-5,5);
				pAxisBottom2->GetLabel()->SetText(_T("�Ƕ�(��)"));
				pAxisBottom2->SetMinMax(-90,20);
				pAxisBottom2->SetInverted(FALSE);
				pAxisLeft2->SetMinMax(-5,5);
			}
			else if (modelSelIndex==3)
			{
				vector<CString> tmpMillingPrecision(precisionPointNum,"");
				m_List_ResultInfo.DeleteAllItems();
				m_List_ResultInfo.InsertItem(0,"���ֵ");
				for (int i=0;i<precisionPointNum;++i)
				{
					tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
					m_List_ResultInfo.InsertItem(i+1,tmpMillingPrecision[i]);
				}
				//��ʾƽ��ֵ
				m_List_ResultInfo.InsertItem(precisionPointNum+1,"ƽ��ֵ");
				for (int i=0;i<precisionPointNum;++i)
				{
					tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
					m_List_ResultInfo.InsertItem(i+precisionPointNum+2,tmpMillingPrecision[i]);
				}
				m_ChartCtrl_LeftTop.GetTitle()->RemoveAll();
				m_ChartCtrl_LeftTop.GetTitle()->AddString("�����");
				m_ChartCtrl_RightTop.GetTitle()->RemoveAll();
				m_ChartCtrl_RightTop.GetTitle()->AddString("�����");

				pAxisBottom1->GetLabel()->SetText(_T("�Ƕ�(��)"));
				pAxisBottom1->SetMinMax(-90,20);
				pAxisBottom1->SetInverted(TRUE);
				pAxisLeft1->SetMinMax(-5,5);
				pAxisBottom2->GetLabel()->SetText(_T("�Ƕ�(��)"));
				pAxisBottom2->SetMinMax(-90,20);
				pAxisBottom2->SetInverted(FALSE);
				pAxisLeft2->SetMinMax(-5,5);

			}
			else if (modelSelIndex==4)
			{
				vector<CString> tmpMillingPrecision(precisionPointNum,"");
				m_List_ResultInfo.DeleteAllItems();
				for (int i=0;i<precisionPointNum;++i)
				{
					tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
					m_List_ResultInfo.InsertItem(i,tmpMillingPrecision[i]);
				}
				tmpMillingPrecision[0].Format("��̱�");
				m_List_ResultInfo.InsertItem(precisionPointNum,tmpMillingPrecision[0]);
			}

		}
		else
		{
			if (modelSelIndex==0)
			{
				vector<CString> tmpMillingPrecision(precisionPointNum,"");
				m_List_ResultInfo.DeleteAllItems();
				for (int i=0;i<precisionPointNum;++i)
				{
					tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
					m_List_ResultInfo.InsertItem(i,tmpMillingPrecision[i]);
				}
			}
			else if (modelSelIndex==1)
			{
				vector<CString> tmpMillingPrecision(precisionPointNum,"");
				m_List_ResultInfo.DeleteAllItems();
				m_List_ResultInfo.InsertItem(0,"�����");
				m_List_ResultInfo.InsertItem(1,"���ֵ");
				for (int i=0;i<precisionPointNum;++i)
				{
					tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
					m_List_ResultInfo.InsertItem(i+2,tmpMillingPrecision[i]);
				}
				//��ʾƽ��ֵ
				m_List_ResultInfo.InsertItem(precisionPointNum+2,"ƽ��ֵ");
				for (int i=0;i<precisionPointNum;++i)
				{
					tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
					m_List_ResultInfo.InsertItem(i+precisionPointNum+3,tmpMillingPrecision[i]);
				}
				m_ChartCtrl_LeftTop.GetTitle()->RemoveAll();
				m_ChartCtrl_LeftTop.GetTitle()->AddString("�����");
				m_ChartCtrl_RightTop.GetTitle()->RemoveAll();
				m_ChartCtrl_RightTop.GetTitle()->AddString("�����");

				pAxisBottom1->GetLabel()->SetText(_T("�Ƕ�(��)"));
				pAxisBottom1->SetMinMax(-90,20);
				pAxisBottom1->SetInverted(TRUE);
				pAxisLeft1->SetMinMax(-5,5);

				pAxisBottom2->GetLabel()->SetText(_T("�Ƕ�(��)"));
				pAxisBottom2->SetMinMax(-90,20);
				pAxisBottom2->SetInverted(FALSE);
				pAxisLeft2->SetMinMax(-5,5);

			}
			else if (modelSelIndex==2)
			{
				vector<CString> tmpMillingPrecision(precisionPointNum,"");
				m_List_ResultInfo.DeleteAllItems();
				for (int i=0;i<precisionPointNum;++i)
				{
					tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
					m_List_ResultInfo.InsertItem(i,tmpMillingPrecision[i]);
				}
				tmpMillingPrecision[0].Format("��̱�");
				m_List_ResultInfo.InsertItem(precisionPointNum,tmpMillingPrecision[0]);
			}

		}
		if (IsAfterMillFlag)
		{
			switch(modelSelIndex)
			{
			case 0:
				analyseMode=After_SinglePrecision;
				bSingle=TRUE;
				isCreateCad=TRUE;
				DisplayStandardOutline();
				AfterSingleOutlinePrecisionDisp(m_Edit_DistanceReal,m_Edit_DistanceReal);
				SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,"��ɫΪ��׼��������ɫΪʵ������");
				break;
			case 1:
				analyseMode=After_StatisticPrecision;
				CsDetectDetail.Format("ϳĥ����澫��ͳ��ֵ����");
				bTongJi=TRUE;
				AfterStatisticOutlinePrecisionDisp();
				SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,"��ɫΪƽ��ֵ����ɫΪ���ֵ");
				break;
			case 2:
				analyseMode=After_SingleMilling;
				bSingle=TRUE;
				isCreateCad=TRUE;
				AfterSingleOutlineMillingAmountDisp(m_Edit_DistanceReal,m_Edit_DistanceReal);
				SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,"��ɫΪϳĥǰ��������ɫΪϳĥ������");

				//��ͷ�ṹ��
				hditem.mask=HDI_TEXT;
				hditem.pszText=strHD;
				hditem.cchTextMax=SizeofBuffer;
				pHDCtrl->GetItem(1,&hditem);
				hditem.pszText=_T("��ϳĥ��");
				pHDCtrl->SetItem(1,&hditem);
				TCHAR strHD2[SizeofBuffer];
				hditem2.mask=HDI_TEXT;
				hditem2.pszText=strHD2;
				hditem2.cchTextMax=SizeofBuffer;
				pHDCtrl->GetItem(2,&hditem2);
				hditem2.pszText=_T("��ϳĥ��");
				pHDCtrl->SetItem(2,&hditem2);
				break;
			case 3:
				analyseMode=After_StatisticMilling;
				CsDetectDetail.Format("ϳĥ��ϳĥ��ͳ��ֵ����");
				SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,"��ɫΪƽ��ֵ����ɫΪ���ֵ");
				bTongJi=TRUE;
				AfterStatisticOutlineMillingAmountDisp();

				//��ͷ�ṹ��
				hditem.mask=HDI_TEXT;
				hditem.pszText=strHD;
				hditem.cchTextMax=SizeofBuffer;
				pHDCtrl->GetItem(1,&hditem);
				hditem.pszText=_T("��ϳĥ��");
				pHDCtrl->SetItem(1,&hditem);
				hditem2.mask=HDI_TEXT;
				hditem2.pszText=strHD2;
				hditem2.cchTextMax=SizeofBuffer;
				pHDCtrl->GetItem(2,&hditem2);
				hditem2.pszText=_T("��ϳĥ��");
				pHDCtrl->SetItem(2,&hditem2);
				break;
			case 4:
				analyseMode=After_Transfinite;
				bChaoXian=TRUE;
				CsDetectDetail.Format("ϳĥ������������");
				SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,"��ɫΪ��׼��������ɫΪʵ������");
				isCreateCad=TRUE;
				DisplayStandardOutline();
				AfterTransfiniteDataViewDisp();
				break;
			default:
				break;
			}
		}
		else
		{
			switch(modelSelIndex)
			{
			case 0:
				analyseMode=Before_SinglePrecision;
				bSingle=TRUE;
				isCreateCad=TRUE;
				DisplayStandardOutline();
				BeforeSingleOutlinePrecisionDisp(m_Edit_DistanceReal,m_Edit_DistanceReal);
				SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,"��ɫΪ��׼��������ɫΪʵ������");
				break;
			case 1:
				analyseMode=Before_StatisticPrecision;
				bTongJi=TRUE;
				CsDetectDetail.Format("ϳĥǰ���澫��ͳ�Ʒ���");
				SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,"��ɫΪƽ��ֵ����ɫΪ���ֵ");
				BeforeStatisticOutlinePrecisionDisp();
				break;
			case 2:
				analyseMode=Before_Transfinite;
				bChaoXian=TRUE;
				CsDetectDetail.Format("ϳĥǰ������������");
				SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,"��ɫΪ��׼��������ɫΪʵ������");
				isCreateCad=TRUE;
				DisplayStandardOutline();
				BeforeTransfiniteDataViewDisp();
				break;
			default:
				break;
			}
		}
	}
}
// ϳĥ�󵥸��������澫�ȷ���
void CHighPrecisionDlg::AfterSingleOutlinePrecisionDisp(double currentDistance,double RightcurrentDistance)
{
	UpdateData(TRUE);
	//���������õ�ʵ�������������������//
	CStdioFile fMeasureFile;
	CString HdmORXmlFilePath="";
	CString ClhSketchPath="";
	CString RightHdmORXmlFilePath="";
	CString RightClhSketchPath="";
	bool bFinishFlag=false;
	//////////////////////////////////////////////////////////////////////////
	vector<vector<double> > tmp_m_startAndEndVec(m_startAndEndVec); //�洢ÿ���ļ�����ʼ����ֹ���
	if (CsDirection==_T("��"))
	{
		double tmp;
		tmp = tmp_m_startAndEndVec[0][0];
		tmp_m_startAndEndVec[0][0] = tmp_m_startAndEndVec[0][1];
		tmp_m_startAndEndVec[0][1] = tmp;
		if (tmp_m_startAndEndVec.size()>1)
		{
			tmp = tmp_m_startAndEndVec.back()[0];
			tmp_m_startAndEndVec.back()[0] = tmp_m_startAndEndVec.back()[1];
			tmp_m_startAndEndVec.back()[1] = tmp;
		}
		
	}
	//if(currentDistance<m_startAndEndVec[0][0])
	if(currentDistance<tmp_m_startAndEndVec[0][0])
	{
		CString tmpMessage;
		tmpMessage.Format("����ϳĥ���Ϊ%.1f",tmp_m_startAndEndVec[0][0]);	
		m_Edit_Distance=m_startAndEndVec[0][0];

		if (CsDirection==_T("��"))
		{
			tmpMessage.Format("����ϳĥ�յ�Ϊ%.1f",tmp_m_startAndEndVec[0][0]);
			m_Edit_Distance = tmp_m_startAndEndVec.back()[0];


		}
		m_Edit_DistanceReal = m_Edit_Distance;
		MessageBox(tmpMessage,_T("�ֹ�����������"));
		//�������
		CString strCurDist;
		int iK=(int)m_Edit_DistanceReal/1000;
		double iD=m_Edit_DistanceReal-1000*iK;
		//string tmpDetectRoad=CsDetectRoad;
		//tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
		strCurDist.Format("%s%d + %0.1f",CsDetectRoad,iK,iD);
		SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
		m_havePressAnalyse=FALSE;
		UpdateData(FALSE);
		return;
	}
	else if (currentDistance>tmp_m_startAndEndVec.back()[1])
	{
		CString tmpMessage;
		tmpMessage.Format("����ϳĥ�յ�Ϊ%.1f",tmp_m_startAndEndVec.back()[1]);
		m_Edit_Distance=tmp_m_startAndEndVec.back()[1];

		if (CsDirection==_T("��"))
		{
			tmpMessage.Format("����ϳĥ���Ϊ%.1f",tmp_m_startAndEndVec.back()[1]);
			m_Edit_Distance=tmp_m_startAndEndVec[0][1];

		}
		m_Edit_DistanceReal = m_Edit_Distance;
		MessageBox(tmpMessage,_T("�ֹ�����������"));
		//�������
		CString strCurDist;
		int iK=(int)m_Edit_DistanceReal/1000;
		double iD=m_Edit_DistanceReal-1000*iK;
		string tmpDetectRoad=CsDetectRoad;
		tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
		strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
		SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
		m_havePressAnalyse=FALSE;
		UpdateData(FALSE);
		return;
	}
	for (unsigned int i=0;i<m_startAndEndVec.size();++i)
	{
		if (currentDistance>=tmp_m_startAndEndVec[i][0] && currentDistance<=tmp_m_startAndEndVec[i][1])
		{
			string tmpFileName=m_fileLineVec[i];
			int lastSymbolPos=tmpFileName.rfind('-');
			CString FileNameStr=tmpFileName.substr(0,lastSymbolPos+1).c_str();
			ClhSketchPath.Format("%s\\%s�������潻��%c.txt",curFileDirection.c_str(),FileNameStr,tmpFileName.back());

			tmpFileName=m_HdmLineVec[i];
			lastSymbolPos=tmpFileName.rfind('-');
			FileNameStr=tmpFileName.substr(0,lastSymbolPos+1).c_str();
			HdmORXmlFilePath.Format("%s\\%s�������澫��%c.txt",curFileDirection.c_str(),FileNameStr,tmpFileName.back());

			string RighttmpFileName=m_RightfileLineVec[i];
			int RightlastSymbolPos=RighttmpFileName.rfind('-');
			CString RightFileNameStr=RighttmpFileName.substr(0,RightlastSymbolPos+1).c_str();
			RightClhSketchPath.Format("%s\\%s���Һ���潻��%c.txt",curFileDirection.c_str(),RightFileNameStr,RighttmpFileName.back());

			RighttmpFileName=m_RightHdmLineVec[i];
			RightlastSymbolPos=RighttmpFileName.rfind('-');
			RightFileNameStr=RighttmpFileName.substr(0,RightlastSymbolPos+1).c_str();
			RightHdmORXmlFilePath.Format("%s\\%s���Һ���澫��%c.txt",curFileDirection.c_str(),RightFileNameStr,RighttmpFileName.back());
			currentFileIndex=i;
			if (currentFileIndex!=lastFileIndex)
			{
				lastFileIndex=currentFileIndex;
				m_LeftOutLineFileOffset=0;
				m_PrecisionFileOffset=0;
				m_RightOutLineFileOffset=0;
				m_RightPrecisionFileOffset=0;
			}
			break;
		}
	}
	//��ȡ��ʾ������
	ReadOutline(currentDistance,LastlocalFileX,LastlocalFileY,LastlocalFilePointNum,m_LeftOutLineFileOffset,ClhSketchPath);
	if (LastlocalFilePointNum<=0)
	{
		SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,"�쳣����");
	}
	else
	{
		m_pLeftTopAfterLineSerie->ClearSerie();
		m_pLeftTopAfterLineSerie->AddPoints(LastlocalFileX,LastlocalFileY,LastlocalFilePointNum);
	}

	//��ȡ��ʾ������
	ReadOutline(RightcurrentDistance,LastlocalFileRightX,LastlocalFileRightY,RightLastlocalFilePointNum,m_RightOutLineFileOffset,RightClhSketchPath);
	//������Xֵ��Ҫ������
	for (int i=0;i<RightLastlocalFilePointNum;++i)
	{
		LastlocalFileRightX[i]=-LastlocalFileRightX[i];
	}
	if (RightLastlocalFilePointNum<=0)
	{
		SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,"�쳣����");
	}
	else
	{
		m_pRightTopAfterLineSerie->ClearSerie();
		m_pRightTopAfterLineSerie->AddPoints(LastlocalFileRightX,LastlocalFileRightY,RightLastlocalFilePointNum);
	}

	//��ȡ��ʾ����澫��
	ReadPrecisionOrMill(currentDistance,f60LeftOutlineError,precisionPointNum,m_PrecisionFileOffset,HdmORXmlFilePath);
	m_pLeftBottomLineSerie->ClearSerie();
	m_pLeftBottomLineSerie->AddPoints(f60leftOutlinePos,f60LeftOutlineError,precisionPointNum);
	m_pLeftBottomPointSerie->ClearSerie();
	m_pLeftBottomPointSerie->AddPoints(f60leftOutlinePos,f60LeftOutlineError,precisionPointNum);

	//��ȡ��ʾ�Ҷ��澫��
	ReadPrecisionOrMill(RightcurrentDistance,f60RightOutlineError,precisionPointNum,m_RightPrecisionFileOffset,RightHdmORXmlFilePath);
	m_pRightBottomLineSerie->ClearSerie();
	m_pRightBottomLineSerie->AddPoints(f60RightOutlinePos,f60RightOutlineError,precisionPointNum);
	m_pRightBottomPointSerie->ClearSerie();
	m_pRightBottomPointSerie->AddPoints(f60RightOutlinePos,f60RightOutlineError,precisionPointNum);

	//�����ұ���ϢListctrl��
	//��ʾϳĥ����
	//��ʾ����ֵ
	
	CString tmpPrecisonLeft="";
	CString tmpPrecisonRight="";
	for (int i=0;i<precisionPointNum;++i)
	{
		tmpPrecisonLeft.Format("%7.4f",f60LeftOutlineError[i]);
		tmpPrecisonRight.Format("%7.4f",f60RightOutlineError[i]);
		m_List_ResultInfo.SetItemText(i,1,tmpPrecisonLeft);
		m_List_ResultInfo.SetItemText(i,2,tmpPrecisonRight);
	}
}
//ϳĥ����������ͳ��ֵ����
void CHighPrecisionDlg::AfterStatisticOutlinePrecisionDisp()
{
	
	UpdateData(TRUE);
	LONGLONG startIndex=0,endIndex=0;
	if (CsDirection == _T("��"))
	{
		startIndex = (LONGLONG)(abs(m_Edit_Distance * 10 - m_startAndEndVec[0][0] * 10));
	}
	else
	{
		startIndex = (LONGLONG)(m_Edit_Distance * 10 - m_startAndEndVec[0][0] * 10);
	}
	//startIndex = (LONGLONG)(m_Edit_Distance * 10 - m_startAndEndVec[0][0] * 10);

	if (startIndex<0)
	{
		CString tmpMessage;
		tmpMessage.Format("����ϳĥ���Ϊ%.1f",m_startAndEndVec[0][0]);
		MessageBox(tmpMessage,_T("�ֹ�����������"));
		m_Edit_Distance=m_startAndEndVec[0][0];
		m_Edit_DistanceReal=m_Edit_Distance;
		//�������
		CString strCurDist;
		int iK=(int)m_Edit_DistanceReal/1000;
		double iD=m_Edit_DistanceReal-1000*iK;
		string tmpDetectRoad=CsDetectRoad;
		tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
		strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
		SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
		m_havePressAnalyse=FALSE;
		UpdateData(FALSE);
		return;
	}
	else if (endIndex>m_PrecisionNumCnt)
	{
		CString tmpMessage;
		tmpMessage.Format("����ϳĥ�յ�Ϊ%.1f",m_startAndEndVec.back()[1]);
		MessageBox(tmpMessage,_T("�ֹ�����������"));
		m_Edit_Distance=m_startAndEndVec.back()[1];
		m_Edit_DistanceReal=m_Edit_Distance;
		//�������
		CString strCurDist;
		int iK=(int)m_Edit_DistanceReal/1000;
		double iD=m_Edit_DistanceReal-1000*iK;
		m_edit_distance_str.Format("%0.1f", (float)iD);
		m_edit_distance2_str.Format("%d", (int)iK);
		string tmpDetectRoad=CsDetectRoad;
		tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
		strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
		SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
		m_havePressAnalyse=FALSE;
		UpdateData(FALSE);
		return;
	}

	int offsetSel=m_Combo_TotalDistance.GetCurSel();
	double endDistance=0.0;
	switch(offsetSel)
	{
	case 0:
		endIndex=startIndex+10*10;
		endDistance=m_Edit_Distance+10;
		break;
	case 1:
		endIndex=startIndex+50*10;
		endDistance=m_Edit_Distance+50;
		break;
	case 2:
		endIndex=startIndex+100*10;
		endDistance=m_Edit_Distance+100;
		break;
	case 3:
		startIndex=0;
		endIndex=m_PrecisionNumCnt;
	default:
		break;
	}
	//���������
	if (offsetSel!=3)
	{
		int chaoxianCnt=0;
		bool startCntFlag=FALSE;
		for (unsigned int i=0;i<OverValueHdmVec.size();++i)
		{
			if (OverValueHdmVec[i]>=m_Edit_DistanceReal)
			{
				startCntFlag=TRUE;
			}
			if (startCntFlag && OverValueHdmVec[i]<endDistance)
			{
				++chaoxianCnt;
			}
		}
		m_fixedValueRatio=1-(double)chaoxianCnt/(double)(endIndex-startIndex);
		int RightchaoxianCnt=0;
		startCntFlag=FALSE;
		for (unsigned int i=0;i<RightOverValueHdmVec.size();++i)
		{
			if (RightOverValueHdmVec[i]>=m_Edit_DistanceReal)
			{
				startCntFlag=TRUE;
			}
			if (startCntFlag && RightOverValueHdmVec[i]<endDistance)
			{
				++RightchaoxianCnt;
			}
		}
		m_RightfixedValueRatio=1-(double)RightchaoxianCnt/(double)(endIndex-startIndex);
		if (m_fixedValueRatio<0)
		{
			m_fixedValueRatio=0;
		}
		if (m_RightfixedValueRatio<0)
		{
			m_RightfixedValueRatio=0;
		}
	}
	else
	{
		m_fixedValueRatio=1-(double)OverValueHdmVec.size()/(double)m_PrecisionNumCnt;
		m_RightfixedValueRatio=1-(double)RightOverValueHdmVec.size()/(double)m_PrecisionNumCnt;
		if (m_fixedValueRatio<0)
		{
			m_fixedValueRatio=0;
		}
		if (m_RightfixedValueRatio<0)
		{
			m_RightfixedValueRatio=0;
		}
	}
	/*pAxisLeft1->SetAutomatic(FALSE);
	pAxisLeft1->SetMinMax(-1,1);
	pAxisBottom1->SetAutomatic(FALSE);
	pAxisBottom1->SetMinMax(-20,100);

	pAxisLeft2->SetAutomatic(FALSE);
	pAxisLeft2->SetMinMax(-1,1);
	pAxisBottom2->SetAutomatic(FALSE);
	pAxisBottom2->SetMinMax(-20,100);*/
	if (startIndex<0 || endIndex>m_PrecisionNumCnt)
	{
		
		MessageBox(_T("��ѡ�����γ�����Χ��������ѡ��"),_T("�ֹ�����������"));
	}
	else
	{
		for (int i=0;i<precisionPointNum;++i)
		{
			pPrecisionAverage[i]=0.0;
			pPrecisionMax[i]=0.0;
			pRightPrecisionAverage[i]=0.0;
			pRightPrecisionMax[i]=0.0;
			for (ULONGLONG j=startIndex;j<endIndex;++j)
			{
				if (fabs(pPrecisionMax[i])<fabs(localFileHdmVec[i][j]))
				{
					pPrecisionMax[i]=localFileHdmVec[i][j];
				}
				pPrecisionAverage[i]+=localFileHdmVec[i][j];

				if (fabs(pRightPrecisionMax[i])<fabs(RightlocalFileHdmVec[i][j]))
				{
					pRightPrecisionMax[i]=RightlocalFileHdmVec[i][j];
				}
				pRightPrecisionAverage[i]+=RightlocalFileHdmVec[i][j];
			}
		}
		for (int j=0;j<precisionPointNum;++j)
		{
			pPrecisionAverage[j]/=(endIndex-startIndex+1);
			pRightPrecisionAverage[j]/=(endIndex-startIndex+1);
		}
		m_pLeftTopLineSerie->ClearSerie();
		m_pLeftTopLineSerie->AddPoints(f60leftOutlinePos,pPrecisionAverage,precisionPointNum);
		m_pLeftTopPointSerie->ClearSerie();
		m_pLeftTopPointSerie->AddPoints(f60leftOutlinePos,pPrecisionAverage,precisionPointNum);

		m_pMaxLeftTopLineSerie->ClearSerie();
		m_pMaxLeftTopLineSerie->AddPoints(f60leftOutlinePos,pPrecisionMax,precisionPointNum);
		m_pMaxLeftTopPointSerie->ClearSerie();
		m_pMaxLeftTopPointSerie->AddPoints(f60leftOutlinePos,pPrecisionMax,precisionPointNum);

		m_pRightTopLineSerie->ClearSerie();
		m_pRightTopLineSerie->AddPoints(f60RightOutlinePos,pRightPrecisionAverage,precisionPointNum);
		m_pRightTopPointSerie->ClearSerie();
		m_pRightTopPointSerie->AddPoints(f60RightOutlinePos,pRightPrecisionAverage,precisionPointNum);

		m_pMaxRightTopLineSerie->ClearSerie();
		m_pMaxRightTopLineSerie->AddPoints(f60RightOutlinePos,pRightPrecisionMax,precisionPointNum);
		m_pMaxRightTopPointSerie->ClearSerie();
		m_pMaxRightTopPointSerie->AddPoints(f60RightOutlinePos,pRightPrecisionMax,precisionPointNum);
		//��ʾϳĥ����
		//CHeaderCtrl* pHDCtrl=m_List_ResultInfo.GetHeaderCtrl();
		////��ͷ�ṹ��
		//HDITEM hditem;
		//enum {SizeofBuffer =256};
		//TCHAR strHD[SizeofBuffer];
		//hditem.mask=HDI_TEXT;
		//hditem.pszText=strHD;
		//hditem.cchTextMax=SizeofBuffer;
		//pHDCtrl->GetItem(1,&hditem);
		//hditem.pszText=_T("�����澫��");
		//pHDCtrl->SetItem(1,&hditem);
		//HDITEM hditem2;
		//TCHAR strHD2[SizeofBuffer];
		//hditem2.mask=HDI_TEXT;
		//hditem2.pszText=strHD2;
		//hditem2.cchTextMax=SizeofBuffer;
		//pHDCtrl->GetItem(2,&hditem2);
		//hditem2.pszText=_T("�Һ���澫��");
		//pHDCtrl->SetItem(2,&hditem2);
		////��ʾ����ͳ��ֵ
		CString tmpDispStrLeft="";
		CString tmpDispStrRight="";
		//��ʾ������
		tmpDispStrLeft.Format("%4.2f",m_fixedValueRatio);
		tmpDispStrRight.Format("%4.2f",m_RightfixedValueRatio);
		m_List_ResultInfo.SetItemText(0,1,tmpDispStrLeft);
		m_List_ResultInfo.SetItemText(0,2,tmpDispStrRight);
		//��ʾͳ�����ֵ

		for (int i=0;i<precisionPointNum;++i)
		{
			tmpDispStrLeft.Format("%7.4f",pPrecisionMax[i]);
			tmpDispStrRight.Format("%7.4f",pRightPrecisionMax[i]);
			m_List_ResultInfo.SetItemText(i+2,1,tmpDispStrLeft);
			m_List_ResultInfo.SetItemText(i+2,2,tmpDispStrRight);
		}
		for (int i=0;i<precisionPointNum;++i)
		{
			tmpDispStrLeft.Format("%7.4f",pPrecisionAverage[i]);
			tmpDispStrRight.Format("%7.4f",pRightPrecisionAverage[i]);
			m_List_ResultInfo.SetItemText(i+precisionPointNum+3,1,tmpDispStrLeft);
			m_List_ResultInfo.SetItemText(i+precisionPointNum+3,2,tmpDispStrRight);
		}


	}

}
//ϳĥ�󵥸�����ϳĥ������
void CHighPrecisionDlg::AfterSingleOutlineMillingAmountDisp(double currentDistance,double RightcurrentDistance)
{
	UpdateData(TRUE);
	//���������õ�ʵ�������������������//
	CStdioFile fMeasureFile;
	CString HdmORXmlFilePath="";
	CString ClhSketchPath="";
	CString ClhBeforeSketchPath="";
	CString RightHdmORXmlFilePath="";
	CString RightClhSketchPath="";
	CString RightClhBeforeSketchPath="";
	bool bFinishFlag=false;
	//////////////////////////////////////////////////////////////////////////
	vector<vector<double> > tmp_m_startAndEndVec(m_startAndEndVec); //�洢ÿ���ļ�����ʼ����ֹ���
	if (CsDirection == _T("��"))
	{
		double tmp;
		tmp = tmp_m_startAndEndVec[0][0];
		tmp_m_startAndEndVec[0][0] = tmp_m_startAndEndVec[0][1];
		tmp_m_startAndEndVec[0][1] = tmp;
		if (tmp_m_startAndEndVec.size() > 1)
		{
			tmp = tmp_m_startAndEndVec.back()[0];
			tmp_m_startAndEndVec.back()[0] = tmp_m_startAndEndVec.back()[1];
			tmp_m_startAndEndVec.back()[1] = tmp;
		}

	}

	if(currentDistance<tmp_m_startAndEndVec[0][0])
	{
		CString tmpMessage;
		tmpMessage.Format("����ϳĥ���Ϊ%.1f",tmp_m_startAndEndVec[0][0]);
		
		m_Edit_Distance=tmp_m_startAndEndVec[0][0];
		if (CsDirection == _T("��"))
		{
			tmpMessage.Format("����ϳĥ�յ�Ϊ%.1f", tmp_m_startAndEndVec[0][0]);
			m_Edit_Distance = tmp_m_startAndEndVec.back()[0];

		}
		MessageBox(tmpMessage, _T("�ֹ�����������"));
		m_Edit_DistanceReal=m_Edit_Distance;
		//�������
		CString strCurDist;
		int iK=(int)m_Edit_DistanceReal/1000;
		double iD=m_Edit_DistanceReal-1000*iK;
		string tmpDetectRoad=CsDetectRoad;
		tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
		strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
		SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
		m_havePressAnalyse=FALSE;
		UpdateData(FALSE);
		return;
	}
	else if (currentDistance>tmp_m_startAndEndVec.back()[1])
	{
		CString tmpMessage;
		tmpMessage.Format("����ϳĥ�յ�Ϊ%.1f",tmp_m_startAndEndVec.back()[1]);
		m_Edit_Distance=m_startAndEndVec.back()[1];
		if (CsDirection == _T("��"))
		{
			tmpMessage.Format("����ϳĥ���Ϊ%.1f", tmp_m_startAndEndVec.back()[1]);
			m_Edit_Distance = tmp_m_startAndEndVec[0][1];

		}
		MessageBox(tmpMessage, _T("�ֹ�����������"));
		m_Edit_DistanceReal=m_Edit_Distance;
		//�������
		CString strCurDist;
		int iK=(int)m_Edit_DistanceReal/1000;
		double iD=m_Edit_DistanceReal-1000*iK;
		string tmpDetectRoad=CsDetectRoad;
		tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
		strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
		SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
		m_havePressAnalyse=FALSE;
		UpdateData(FALSE);
		return;
	}


	for (unsigned int i=0;i<m_startAndEndVec.size();++i)
	{
		if (currentDistance>=tmp_m_startAndEndVec[i][0] && currentDistance<=tmp_m_startAndEndVec[i][1])
		{
			//����ʵ���׼��
			ClhSketchPath.Format("%s\\%s.txt",curFileDirection.c_str(),m_fileLineVec[i]);
			//����ϳĥ������
			HdmORXmlFilePath.Format("%s\\%s.txt",curFileDirection.c_str(),m_XmlLineVec[i]);
			//ǰ��ʵ���׼��
			ClhBeforeSketchPath.Format("%s\\%s.txt",curFileDirection.c_str(),m_fileBeforeLineVec[i]);

			//����ʵ���׼��
			RightClhSketchPath.Format("%s\\%s.txt",curFileDirection.c_str(),m_RightfileLineVec[i]);
			//����ϳĥ������
			RightHdmORXmlFilePath.Format("%s\\%s.txt",curFileDirection.c_str(),m_RightXmlLineVec[i]);
			//ǰ��ʵ���׼��
			RightClhBeforeSketchPath.Format("%s\\%s.txt",curFileDirection.c_str(),m_RightfileBeforeLineVec[i]);

			currentFileIndex=i;
			if (currentFileIndex!=lastFileIndex)
			{
				lastFileIndex=currentFileIndex;
				m_LeftOutLineFileOffset=0;
				m_LeftMillingFileOffset=0;
				m_LeftBeforeOutlineFileOffset=0;
				m_RightOutLineFileOffset=0;
				m_RightMillingFileOffset=0;
				m_RightBeforeOutlineFileOffset=0;
			}
			break;
		}
	}
	//��ȡ��ʾϳĥ��������
	ReadOutline(currentDistance,LastlocalFileX,LastlocalFileY,LastlocalFilePointNum,m_LeftOutLineFileOffset,ClhSketchPath);
	LastlocalFileX[LastlocalFilePointNum-1] = 36.8;
	if (LastlocalFilePointNum<=0)
	{
		SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,"�쳣����");
	}
	else
	{
		m_pLeftTopAfterLineSerie->ClearSerie();
		m_pLeftTopAfterLineSerie->AddPoints(LastlocalFileX,LastlocalFileY,LastlocalFilePointNum);
	}


	//��ȡ��ʾϳĥ��������
	ReadOutline(RightcurrentDistance,LastlocalFileRightX,LastlocalFileRightY,RightLastlocalFilePointNum,m_RightOutLineFileOffset,RightClhSketchPath);
	LastlocalFileRightX[RightLastlocalFilePointNum-1] = 36.8;
	//������Xֵ��Ҫ������
	for (int i=0;i<RightLastlocalFilePointNum;++i)
	{
		LastlocalFileRightX[i]=-LastlocalFileRightX[i];
	}
	if (RightLastlocalFilePointNum<=0)
	{
		SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,"�쳣����");
	}
	else
	{
		m_pRightTopAfterLineSerie->ClearSerie();
		m_pRightTopAfterLineSerie->AddPoints(LastlocalFileRightX,LastlocalFileRightY,RightLastlocalFilePointNum);
	}



	//��ȡ��ʾϳĥǰ������
	ReadOutline(currentDistance,localFileX,localFileY,localFilePointNum,m_LeftBeforeOutlineFileOffset,ClhBeforeSketchPath);
	localFileX[localFilePointNum-1] = 36.8;
	m_pLeftTopBeforeLineSerie->ClearSerie();
	m_pLeftTopBeforeLineSerie->AddPoints(localFileX,localFileY,localFilePointNum);

	//��ȡ��ʾϳĥǰ������
	ReadOutline(RightcurrentDistance,localFileRightX,localFileRightY,RightlocalFilePointNum,m_RightBeforeOutlineFileOffset,RightClhBeforeSketchPath);
	localFileRightX[RightlocalFilePointNum-1] =36.8;
	//������Xֵ��Ҫ������
	for (int i=0;i<RightlocalFilePointNum;++i)
	{
		localFileRightX[i]=-localFileRightX[i];
	}
	m_pRightTopBeforeLineSerie->ClearSerie();
	m_pRightTopBeforeLineSerie->AddPoints(localFileRightX,localFileRightY,RightlocalFilePointNum);


	//��ȡ��ʾϳĥ����
	ReadPrecisionOrMill(currentDistance,f60LeftOutlineError,precisionPointNum,m_PrecisionFileOffset,HdmORXmlFilePath);
	m_pLeftBottomLineSerie->ClearSerie();
	m_pLeftBottomLineSerie->AddPoints(f60leftOutlinePos,f60LeftOutlineError,precisionPointNum);
	m_pLeftBottomPointSerie->ClearSerie();
	m_pLeftBottomPointSerie->AddPoints(f60leftOutlinePos,f60LeftOutlineError,precisionPointNum);

	//��ȡ��ʾϳĥ����
	ReadPrecisionOrMill(RightcurrentDistance,f60RightOutlineError,precisionPointNum,m_RightPrecisionFileOffset,RightHdmORXmlFilePath);
	m_pRightBottomLineSerie->ClearSerie();
	m_pRightBottomLineSerie->AddPoints(f60RightOutlinePos,f60RightOutlineError,precisionPointNum);
	m_pRightBottomPointSerie->ClearSerie();
	m_pRightBottomPointSerie->AddPoints(f60RightOutlinePos,f60RightOutlineError,precisionPointNum);

	
	//��ʾϳĥ��
	CString tmpPrecisonLeft="";
	CString tmpPrecisonRight="";
	for (int i=0;i<precisionPointNum;++i)
	{
		tmpPrecisonLeft.Format("%7.4f",f60LeftOutlineError[i]);
		tmpPrecisonRight.Format("%7.4f",f60RightOutlineError[i]);
		m_List_ResultInfo.SetItemText(i,1,tmpPrecisonLeft);
		m_List_ResultInfo.SetItemText(i,2,tmpPrecisonRight);
	}

}
//ϳĥ������ϳĥ��ͳ��ֵ����
void CHighPrecisionDlg::AfterStatisticOutlineMillingAmountDisp()
{
	UpdateData(TRUE);
	LONGLONG startIndex=0,endIndex=0;
	startIndex=(LONGLONG)(abs(m_Edit_Distance*10-m_startAndEndVec[0][0]*10));
	int offsetSel=m_Combo_TotalDistance.GetCurSel();
	switch(offsetSel)
	{
	case 0:
		endIndex=startIndex+10*10;
		break;
	case 1:
		endIndex=startIndex+50*10;
		break;
	case 2:
		endIndex=startIndex+100*10;
		break;
	case 3:
		startIndex=0;
		endIndex=m_PrecisionNumCnt;
	default:
		break;
	}
	if (startIndex<0)
	{
		CString tmpMessage;
		tmpMessage.Format("����ϳĥ���Ϊ%.1f",m_startAndEndVec[0][0]);
		MessageBox(tmpMessage,_T("�ֹ�����������"));
		m_Edit_Distance=m_startAndEndVec[0][0];
		m_Edit_DistanceReal=m_Edit_Distance;
		//�������
		CString strCurDist;
		int iK=(int)m_Edit_DistanceReal/1000;
		double iD=m_Edit_DistanceReal-1000*iK;
		m_edit_distance_str.Format("%0.1f", (float)iD);
		m_edit_distance2_str.Format("%d", (int)iK);
		string tmpDetectRoad=CsDetectRoad;
		tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
		strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
		SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
		m_havePressAnalyse=FALSE;
		UpdateData(FALSE);
		return;
	}
	else if (endIndex>m_PrecisionNumCnt)
	{
		CString tmpMessage;
		tmpMessage.Format("����ϳĥ�յ�Ϊ%.1f",m_startAndEndVec.back()[1]);
		MessageBox(tmpMessage,_T("�ֹ�����������"));
		m_Edit_Distance=m_startAndEndVec.back()[1];
		m_Edit_DistanceReal=m_Edit_Distance;
		//�������
		CString strCurDist;
		int iK=(int)m_Edit_DistanceReal/1000;
		double iD=m_Edit_DistanceReal-1000*iK;
		m_edit_distance_str.Format("%0.1f", (float)iD);
		m_edit_distance2_str.Format("%d", (int)iK);

		string tmpDetectRoad=CsDetectRoad;
		tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
		strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
		SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
		m_havePressAnalyse=FALSE;
		UpdateData(FALSE);
		return;
	}
	/*pAxisLeft1->SetAutomatic(FALSE);
	pAxisLeft1->SetMinMax(-1,1);
	pAxisBottom1->SetAutomatic(FALSE);
	pAxisBottom1->SetMinMax(-20,100);
	pAxisLeft2->SetAutomatic(FALSE);
	pAxisLeft2->SetMinMax(-1,1);
	pAxisBottom2->SetAutomatic(FALSE);
	pAxisBottom2->SetMinMax(-20,100);*/
	if (startIndex<0 || endIndex>m_PrecisionNumCnt)
	{
		
		MessageBox(_T("��ѡ�����γ�����Χ��������ѡ��"),_T("�ֹ�����������"));
	}
	else
	{
		for (int i=0;i<precisionPointNum;++i)
		{
			pPrecisionAverage[i]=0.0;
			pPrecisionMax[i]=0.0;
			pRightPrecisionAverage[i]=0.0;
			pRightPrecisionMax[i]=0.0;
			for (ULONGLONG j=startIndex;j<endIndex;++j)
			{
				if (fabs(pPrecisionMax[i])<fabs(localFileHdmVec[i][j]))
				{
					pPrecisionMax[i]=localFileHdmVec[i][j];
				}
				pPrecisionAverage[i]+=localFileHdmVec[i][j];

				if (fabs(pRightPrecisionMax[i])<fabs(RightlocalFileHdmVec[i][j]))
				{
					pRightPrecisionMax[i]=RightlocalFileHdmVec[i][j];
				}
				pRightPrecisionAverage[i]+=RightlocalFileHdmVec[i][j];
			}
		}
		for (int j=0;j<precisionPointNum;++j)
		{
			pPrecisionAverage[j]/=(endIndex-startIndex+1);
			pRightPrecisionAverage[j]/=(endIndex-startIndex+1);
		}
		m_pLeftTopLineSerie->ClearSerie();
		m_pLeftTopLineSerie->AddPoints(f60leftOutlinePos,pPrecisionAverage,precisionPointNum);
		m_pLeftTopPointSerie->ClearSerie();
		m_pLeftTopPointSerie->AddPoints(f60leftOutlinePos,pPrecisionAverage,precisionPointNum);

		m_pMaxLeftTopLineSerie->ClearSerie();
		m_pMaxLeftTopLineSerie->AddPoints(f60leftOutlinePos,pPrecisionMax,precisionPointNum);
		m_pMaxLeftTopPointSerie->ClearSerie();
		m_pMaxLeftTopPointSerie->AddPoints(f60leftOutlinePos,pPrecisionMax,precisionPointNum);

		m_pRightTopLineSerie->ClearSerie();
		m_pRightTopLineSerie->AddPoints(f60RightOutlinePos,pRightPrecisionAverage,precisionPointNum);
		m_pRightTopPointSerie->ClearSerie();
		m_pRightTopPointSerie->AddPoints(f60RightOutlinePos,pRightPrecisionAverage,precisionPointNum);

		m_pMaxRightTopLineSerie->ClearSerie();
		m_pMaxRightTopLineSerie->AddPoints(f60RightOutlinePos,pRightPrecisionMax,precisionPointNum);
		m_pMaxRightTopPointSerie->ClearSerie();
		m_pMaxRightTopPointSerie->AddPoints(f60RightOutlinePos,pRightPrecisionMax,precisionPointNum);
		//��ʾϳĥ��
		
		//��ʾ����ͳ��ֵ
		/*vector<CString> tmpMillingPrecision(precisionPointNum,"");
		m_List_ResultInfo.DeleteAllItems();
		m_List_ResultInfo.InsertItem(0,"�����");*/
		CString tmpDispStrLeft="";
		CString tmpDispStrRight="";
		////��ʾ������
		//tmpDispStrLeft.Format("%4.2f",m_fixedValueRatio);
		//tmpDispStrRight.Format("%4.2f",m_RightfixedValueRatio);
		//m_List_ResultInfo.SetItemText(0,1,tmpDispStrLeft);
		//m_List_ResultInfo.SetItemText(0,2,tmpDispStrRight);
		//��ʾͳ�����ֵ
	/*	m_List_ResultInfo.InsertItem(1,"���ֵ");
		for (int i=0;i<precisionPointNum;++i)
		{
			tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
			m_List_ResultInfo.InsertItem(i+2,tmpMillingPrecision[i]);
		}*/
		for (int i=0;i<precisionPointNum;++i)
		{
			tmpDispStrLeft.Format("%.4f",pPrecisionMax[i]);
			tmpDispStrRight.Format("%.4f",pRightPrecisionMax[i]);
			m_List_ResultInfo.SetItemText(i+1,1,tmpDispStrLeft);
			m_List_ResultInfo.SetItemText(i+1,2,tmpDispStrRight);
		}
		//��ʾƽ��ֵ
		/*m_List_ResultInfo.InsertItem(precisionPointNum+2,"ƽ��ֵ");
		for (int i=0;i<precisionPointNum;++i)
		{
			tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
			m_List_ResultInfo.InsertItem(i+precisionPointNum+3,tmpMillingPrecision[i]);
		}*/
		for (int i=0;i<precisionPointNum;++i)
		{
			tmpDispStrLeft.Format("%.4f",pPrecisionAverage[i]);
			tmpDispStrRight.Format("%.4f",pRightPrecisionAverage[i]);
			m_List_ResultInfo.SetItemText(i+precisionPointNum+2,1,tmpDispStrLeft);
			m_List_ResultInfo.SetItemText(i+precisionPointNum+2,2,tmpDispStrRight);
		}
	}
}
//ϳĥ�������ݲ鿴
void CHighPrecisionDlg::AfterTransfiniteDataViewDisp()
{

	//���������õ�ʵ�������������������//
	CStdioFile fMeasureFile;
	CString HdmORXmlFilePath="";
	CString ClhSketchPath="";
	CString RightHdmORXmlFilePath="";
	CString RightClhSketchPath="";
	//////////////////////////////////////////////////////////////////////////
	//��������У��򽻻��յ�����λ��
	vector<vector<double> > tmp_m_startAndEndVec(m_startAndEndVec); //�洢ÿ���ļ�����ʼ����ֹ���
	if (CsDirection == _T("��"))
	{
		double tmp;
		tmp = tmp_m_startAndEndVec[0][0];
		tmp_m_startAndEndVec[0][0] = tmp_m_startAndEndVec[0][1];
		tmp_m_startAndEndVec[0][1] = tmp;
		if (tmp_m_startAndEndVec.size() > 1)
		{
			tmp = tmp_m_startAndEndVec.back()[0];
			tmp_m_startAndEndVec.back()[0] = tmp_m_startAndEndVec.back()[1];
			tmp_m_startAndEndVec.back()[1] = tmp;
		}
	}

	if (OverValueHdmVec.size()>0 ||RightOverValueHdmVec.size()>0)
	{
		//�����ұ���ϢListctrl��
		//��ʾϳĥ����
		//CHeaderCtrl* pHDCtrl=m_List_ResultInfo.GetHeaderCtrl();
		////��ͷ�ṹ��
		//HDITEM hditem;
		//enum {SizeofBuffer =256};
		//TCHAR strHD[SizeofBuffer];
		//hditem.mask=HDI_TEXT;
		//hditem.pszText=strHD;
		//hditem.cchTextMax=SizeofBuffer;
		//pHDCtrl->GetItem(1,&hditem);
		//hditem.pszText=_T("�����澫��");
		//pHDCtrl->SetItem(1,&hditem);
		//HDITEM hditem2;
		//TCHAR strHD2[SizeofBuffer];
		//hditem2.mask=HDI_TEXT;
		//hditem2.pszText=strHD2;
		//hditem2.cchTextMax=SizeofBuffer;
		//pHDCtrl->GetItem(2,&hditem2);
		//hditem2.pszText=_T("�Һ���澫��");
		//pHDCtrl->SetItem(2,&hditem2);
		//��ʾ����ֵ
		/*vector<CString> tmpMillingPrecision(precisionPointNum,"");
		m_List_ResultInfo.DeleteAllItems();
		for (int i=0;i<precisionPointNum;++i)
		{
			tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
			m_List_ResultInfo.InsertItem(i,tmpMillingPrecision[i]);
		}*/
		/*tmpMillingPrecision[0].Format("��̱�");
		m_List_ResultInfo.InsertItem(precisionPointNum,tmpMillingPrecision[0]);*/
		vector<CString> tmpMillingPrecision(precisionPointNum,"");
		double currentDistance=0.0,RightcurrentDistance=0.0;
		if (m_curOverValueIndex>=0 && m_curOverValueIndex<OverValueHdmVec.size())
		{
			currentDistance=OverValueHdmVec[m_curOverValueIndex];
			leftOverValueFlag=TRUE;

			for (unsigned int i=0;i<tmp_m_startAndEndVec.size();++i)
			{
				if (currentDistance>=tmp_m_startAndEndVec[i][0] && currentDistance<=tmp_m_startAndEndVec[i][1])
				{
					string tmpFileName=m_fileLineVec[i];
					int lastSymbolPos=tmpFileName.rfind('-');
					CString FileNameStr=tmpFileName.substr(0,lastSymbolPos+1).c_str();
					ClhSketchPath.Format("%s\\%s�������潻��%c.txt",curFileDirection.c_str(),FileNameStr,tmpFileName.back());
					HdmORXmlFilePath.Format("%s\\%s.txt",curFileDirection.c_str(),m_HdmLineVec[i]);

					currentFileIndex=i;
					if (currentFileIndex!=lastFileIndex)
					{
						lastFileIndex=currentFileIndex;
						m_LeftOutLineFileOffset=0;
						m_PrecisionFileOffset=0;
					}
					break;
				}
			}
			//��ȡ��ʾ������
			ReadOutline(currentDistance,LastlocalFileX,LastlocalFileY,LastlocalFilePointNum,m_LeftOutLineFileOffset,ClhSketchPath);
			m_pLeftTopAfterLineSerie->ClearSerie();
			m_pLeftTopAfterLineSerie->AddPoints(LastlocalFileX,LastlocalFileY,LastlocalFilePointNum);

			//��ȡ��ʾ����澫��
			ReadPrecisionOrMill(currentDistance,f60LeftOutlineError,precisionPointNum,m_PrecisionFileOffset,HdmORXmlFilePath);
			m_pLeftBottomLineSerie->ClearSerie();
			m_pLeftBottomLineSerie->AddPoints(f60leftOutlinePos,f60LeftOutlineError,precisionPointNum);
			m_pLeftBottomPointSerie->ClearSerie();
			m_pLeftBottomPointSerie->AddPoints(f60leftOutlinePos,f60LeftOutlineError,precisionPointNum);

			//�����ұ���Ϣ��
			CString tmpPrecisonLeft="";
			for (int i=0;i<precisionPointNum;++i)
			{
				tmpPrecisonLeft.Format("%7.4f",f60LeftOutlineError[i]);
				m_List_ResultInfo.SetItemText(i,1,tmpPrecisonLeft);
			}
			//�������
			int iK=(int)currentDistance/1000;
			double iD=currentDistance-1000*iK;
			string tmpDetectRoad=CsDetectRoad;
			tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
			tmpMillingPrecision[0].Format("%s%d+%0.1f",tmpDetectRoad.c_str(),iK,iD);
			m_List_ResultInfo.SetItemText(precisionPointNum,1,tmpMillingPrecision[0]);
		}
		else
		{
			tmpMillingPrecision[0].Format("���");
			m_List_ResultInfo.SetItemText(precisionPointNum,1,tmpMillingPrecision[0]);
			leftOverValueFlag=FALSE;
		}
		if (m_curOverValueIndex>=0 && m_curOverValueIndex<RightOverValueHdmVec.size())
		{

			RightcurrentDistance=RightOverValueHdmVec[m_curOverValueIndex];
			rightOverValueFlag=TRUE;
			for (unsigned int i=0;i<tmp_m_startAndEndVec.size();++i)
			{
				if (RightcurrentDistance>=tmp_m_startAndEndVec[i][0] && RightcurrentDistance<=tmp_m_startAndEndVec[i][1])
				{
					string RighttmpFileName=m_RightfileLineVec[i];
					int lastSymbolPos=RighttmpFileName.rfind('-');
					CString RightFileNameStr=RighttmpFileName.substr(0,lastSymbolPos+1).c_str();
					RightClhSketchPath.Format("%s\\%s���Һ���潻��%c.txt",curFileDirection.c_str(),RightFileNameStr,RighttmpFileName.back());
					RightHdmORXmlFilePath.Format("%s\\%s.txt",curFileDirection.c_str(),m_RightHdmLineVec[i]);
					currentFileIndex=i;
					if (currentFileIndex!=lastFileIndex)
					{
						lastFileIndex=currentFileIndex;
						m_RightOutLineFileOffset=0;
						m_RightPrecisionFileOffset=0;
					}
					break;
				}
			}
			//��ȡ��ʾ������
			ReadOutline(RightcurrentDistance,LastlocalFileRightX,LastlocalFileRightY,RightLastlocalFilePointNum,m_RightOutLineFileOffset,RightClhSketchPath);
			//������Xֵ��Ҫ������
			for (int i=0;i<RightLastlocalFilePointNum;++i)
			{
				LastlocalFileRightX[i]=-LastlocalFileRightX[i];
			}
			m_pRightTopAfterLineSerie->ClearSerie();
			m_pRightTopAfterLineSerie->AddPoints(LastlocalFileRightX,LastlocalFileRightY,RightLastlocalFilePointNum);

			//��ȡ��ʾ�Ҷ��澫��
			ReadPrecisionOrMill(RightcurrentDistance,f60RightOutlineError,precisionPointNum,m_RightPrecisionFileOffset,RightHdmORXmlFilePath);
			m_pRightBottomLineSerie->ClearSerie();
			m_pRightBottomLineSerie->AddPoints(f60RightOutlinePos,f60RightOutlineError,precisionPointNum);
			m_pRightBottomPointSerie->ClearSerie();
			m_pRightBottomPointSerie->AddPoints(f60RightOutlinePos,f60RightOutlineError,precisionPointNum);

			//������Ϣ��
			CString tmpPrecisonRight="";
			for (int i=0;i<precisionPointNum;++i)
			{
				tmpPrecisonRight.Format("%7.4f",f60RightOutlineError[i]);
				m_List_ResultInfo.SetItemText(i,2,tmpPrecisonRight);
			}
			//�������
			int iK=(int)RightcurrentDistance/1000;
			double iD=RightcurrentDistance-1000*iK;
			string tmpDetectRoad=CsDetectRoad;
			tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
			tmpMillingPrecision[0].Format("%s%d+%0.1f",tmpDetectRoad.c_str(),iK,iD);
			m_List_ResultInfo.SetItemText(precisionPointNum,2,tmpMillingPrecision[0]);
		}
		else
		{
			rightOverValueFlag=FALSE;
			tmpMillingPrecision[0].Format("���");
			m_List_ResultInfo.SetItemText(precisionPointNum,2,tmpMillingPrecision[0]);
		}
	}
	else
	{
		MessageBox(_T("�����ڳ��޵�����"),_T("�ֹ�����������"));
		
	}
}

// ϳĥǰ�����������澫�ȷ���
void CHighPrecisionDlg::BeforeSingleOutlinePrecisionDisp(double currentDistance,double RightcurrentDistance )
{
	UpdateData(TRUE);
	//���������õ�ʵ�������������������//
	CStdioFile fMeasureFile;
	CString HdmORXmlFilePath="";
	CString ClhSketchPath="";
	CString RightHdmORXmlFilePath="";
	CString RightClhSketchPath="";
	bool bFinishFlag=false;
	//////////////////////////////////////////////////////////////////////////
	vector<vector<double> > tmp_m_startAndEndVec(m_startAndEndVec); //�洢ÿ���ļ�����ʼ����ֹ���
	if (CsDirection==_T("��"))
	{
		double tmp;
		tmp = tmp_m_startAndEndVec[0][0];
		tmp_m_startAndEndVec[0][0] = tmp_m_startAndEndVec[0][1];
		tmp_m_startAndEndVec[0][1] = tmp;
		if (tmp_m_startAndEndVec.size()>1)
		{
			tmp = tmp_m_startAndEndVec.back()[0];
			tmp_m_startAndEndVec.back()[0] = tmp_m_startAndEndVec.back()[1];
			tmp_m_startAndEndVec.back()[1] = tmp;
		}	
	}
	if(currentDistance<m_startAndEndVec[0][0])
	//if(currentDistance< m_startAndEndVec[0][0])
	{
		CString tmpMessage;
		
		tmpMessage.Format("����ϳĥ���Ϊ%.1f",tmp_m_startAndEndVec[0][0]);
		
		m_Edit_Distance=tmp_m_startAndEndVec[0][0];
		if (CsDirection==_T("��"))
		{
			tmpMessage.Format("����ϳĥ�յ�Ϊ%.1f",tmp_m_startAndEndVec[0][0]);
			m_Edit_Distance=tmp_m_startAndEndVec.back()[0];

		}
		m_Edit_DistanceReal=m_Edit_Distance;
		MessageBox(tmpMessage,_T("�ֹ�����������"));

		//�������
		CString strCurDist;
		int iK=(int)m_Edit_DistanceReal/1000;
		double iD=m_Edit_DistanceReal-1000*iK;
		string tmpDetectRoad=CsDetectRoad;
		tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
		strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
		SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
		m_havePressAnalyse=FALSE;
		UpdateData(FALSE);
		return;
	}
	else if (currentDistance>m_startAndEndVec.back()[1])
	//else if (currentDistance>tmp_m_startAndEndVec.back()[1])
	{
		CString tmpMessage;
		tmpMessage.Format("����ϳĥ�յ�Ϊ%.1f",tmp_m_startAndEndVec.back()[1]);		
		m_Edit_Distance=tmp_m_startAndEndVec.back()[1];
		if (CsDirection==_T("��"))
		{
			tmpMessage.Format("����ϳĥ���Ϊ%.1f",tmp_m_startAndEndVec.back()[1]);
			m_Edit_Distance=tmp_m_startAndEndVec[0][1];

		}
		m_Edit_DistanceReal=m_Edit_Distance;
		MessageBox(tmpMessage,_T("�ֹ�����������"));

		//�������
		CString strCurDist;
		int iK=(int)m_Edit_DistanceReal/1000;
		double iD=m_Edit_DistanceReal-1000*iK;
		string tmpDetectRoad=CsDetectRoad;
		tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
		strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
		SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
		m_havePressAnalyse=FALSE;
		UpdateData(FALSE);
		return;
	}

	for (unsigned int i=0;i<m_startAndEndVec.size();++i)
	{
		if (currentDistance>=m_startAndEndVec[i][0] && currentDistance<=m_startAndEndVec[i][1])
		//if (currentDistance>=tmp_m_startAndEndVec[i][0] && currentDistance<=tmp_m_startAndEndVec[i][1])
		{
			string tmpFileName=m_fileLineVec[i];
			int lastSymbolPos=tmpFileName.rfind('-');
			CString FileNameStr=tmpFileName.substr(0,lastSymbolPos+1).c_str();
			ClhSketchPath.Format("%s\\%sǰ�����潻��%c.txt",curFileDirection.c_str(),FileNameStr,tmpFileName.back());
			HdmORXmlFilePath.Format("%s\\%s.txt",curFileDirection.c_str(),m_HdmLineVec[i]);


			string RighttmpFileName=m_RightfileLineVec[i];
			lastSymbolPos=tmpFileName.rfind('-');
			CString RightFileNameStr=RighttmpFileName.substr(0,lastSymbolPos+1).c_str();
			RightClhSketchPath.Format("%s\\%sǰ�Һ���潻��%c.txt",curFileDirection.c_str(),RightFileNameStr,RighttmpFileName.back());
			RightHdmORXmlFilePath.Format("%s\\%s.txt",curFileDirection.c_str(),m_RightHdmLineVec[i]);
			currentFileIndex=i;
			if (currentFileIndex!=lastFileIndex)
			{
				lastFileIndex=currentFileIndex;
				m_LeftOutLineFileOffset=0;
				m_PrecisionFileOffset=0;
				m_RightOutLineFileOffset=0;
				m_RightPrecisionFileOffset=0;
			}
			break;
		}
	}
	//��ȡ��ʾ������
	ReadOutline(currentDistance,LastlocalFileX,LastlocalFileY,LastlocalFilePointNum,m_LeftOutLineFileOffset,ClhSketchPath);
	if (LastlocalFilePointNum<=0)
	{
		SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,"�쳣����");
	}
	else
	{
		m_pLeftTopAfterLineSerie->ClearSerie();
		m_pLeftTopAfterLineSerie->AddPoints(LastlocalFileX,LastlocalFileY,LastlocalFilePointNum);
	}

	//��ȡ��ʾ������
	ReadOutline(RightcurrentDistance,LastlocalFileRightX,LastlocalFileRightY,RightLastlocalFilePointNum,m_RightOutLineFileOffset,RightClhSketchPath);
	//������Xֵ��Ҫ������
	for (int i=0;i<RightLastlocalFilePointNum;++i)
	{
		LastlocalFileRightX[i]=-LastlocalFileRightX[i];
	}
	if (RightLastlocalFilePointNum<=0)
	{
		SetDlgItemText(IDC_STATIC_SYSTEMSTATUS,"�쳣����");
	}
	else
	{
		m_pRightTopAfterLineSerie->ClearSerie();
		m_pRightTopAfterLineSerie->AddPoints(LastlocalFileRightX,LastlocalFileRightY,RightLastlocalFilePointNum);
	}

	//��ȡ��ʾ����澫��
	ReadPrecisionOrMill(currentDistance,f60LeftOutlineError,precisionPointNum,m_PrecisionFileOffset,HdmORXmlFilePath);
	m_pLeftBottomLineSerie->ClearSerie();
	m_pLeftBottomLineSerie->AddPoints(f60leftOutlinePos,f60LeftOutlineError,precisionPointNum);
	m_pLeftBottomPointSerie->ClearSerie();
	m_pLeftBottomPointSerie->AddPoints(f60leftOutlinePos,f60LeftOutlineError,precisionPointNum);

	//��ȡ��ʾ�Ҷ��澫��
	ReadPrecisionOrMill(RightcurrentDistance,f60RightOutlineError,precisionPointNum,m_RightPrecisionFileOffset,RightHdmORXmlFilePath);
	m_pRightBottomLineSerie->ClearSerie();
	m_pRightBottomLineSerie->AddPoints(f60RightOutlinePos,f60RightOutlineError,precisionPointNum);
	m_pRightBottomPointSerie->ClearSerie();
	m_pRightBottomPointSerie->AddPoints(f60RightOutlinePos,f60RightOutlineError,precisionPointNum);

	//�����ұ���ϢListctrl��
	//��ʾϳĥ����
	//CHeaderCtrl* pHDCtrl=m_List_ResultInfo.GetHeaderCtrl();
	////��ͷ�ṹ��
	//HDITEM hditem;
	//enum {SizeofBuffer =256};
	//TCHAR strHD[SizeofBuffer];
	//hditem.mask=HDI_TEXT;
	//hditem.pszText=strHD;
	//hditem.cchTextMax=SizeofBuffer;
	//pHDCtrl->GetItem(1,&hditem);
	//hditem.pszText=_T("�����澫��");
	//pHDCtrl->SetItem(1,&hditem);
	//HDITEM hditem2;
	//TCHAR strHD2[SizeofBuffer];
	//hditem2.mask=HDI_TEXT;
	//hditem2.pszText=strHD2;
	//hditem2.cchTextMax=SizeofBuffer;
	//pHDCtrl->GetItem(2,&hditem2);
	//hditem2.pszText=_T("�Һ���澫��");
	//pHDCtrl->SetItem(2,&hditem2);
	//��ʾ����ֵ
	/*vector<CString> tmpMillingPrecision(precisionPointNum,"");
	m_List_ResultInfo.DeleteAllItems();
	for (int i=0;i<precisionPointNum;++i)
	{
		tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
		m_List_ResultInfo.InsertItem(i,tmpMillingPrecision[i]);
	}*/
	CString tmpPrecisonLeft="";
	CString tmpPrecisonRight="";
	for (int i=0;i<precisionPointNum;++i)
	{
		tmpPrecisonLeft.Format("%7.4f",f60LeftOutlineError[i]);
		tmpPrecisonRight.Format("%7.4f",f60RightOutlineError[i]);
		m_List_ResultInfo.SetItemText(i,1,tmpPrecisonLeft);
		m_List_ResultInfo.SetItemText(i,2,tmpPrecisonRight);
	}

}

//ϳĥǰ��������ͳ��ֵ����
void CHighPrecisionDlg::BeforeStatisticOutlinePrecisionDisp()
{
	AfterStatisticOutlinePrecisionDisp();
}

//ϳĥǰ�������ݲ鿴
void CHighPrecisionDlg::BeforeTransfiniteDataViewDisp()
{
	//���������õ�ʵ�������������������//
	CStdioFile fMeasureFile;
	CString HdmORXmlFilePath="";
	CString ClhSketchPath="";
	CString RightHdmORXmlFilePath="";
	CString RightClhSketchPath="";
	//////////////////////////////////////////////////////////////////////////
	//��������У��򽻻���ֹ����ʼ���
	vector<vector<double> > tmp_m_startAndEndVec(m_startAndEndVec); //�洢ÿ���ļ�����ʼ����ֹ���
	if (CsDirection == _T("��"))
	{
		double tmp;
		tmp = tmp_m_startAndEndVec[0][0];
		tmp_m_startAndEndVec[0][0] = tmp_m_startAndEndVec[0][1];
		tmp_m_startAndEndVec[0][1] = tmp;
		if (tmp_m_startAndEndVec.size() > 1)
		{
			tmp = tmp_m_startAndEndVec.back()[0];
			tmp_m_startAndEndVec.back()[0] = tmp_m_startAndEndVec.back()[1];
			tmp_m_startAndEndVec.back()[1] = tmp;
		}
	}
	if (OverValueHdmVec.size()>0 ||RightOverValueHdmVec.size()>0)
	{
		//�����ұ���ϢListctrl��
		//��ʾϳĥ����
		
		////��ʾ����ֵ
		vector<CString> tmpMillingPrecision(precisionPointNum,"");
		//m_List_ResultInfo.DeleteAllItems();
		//for (int i=0;i<precisionPointNum;++i)
		//{
		//	tmpMillingPrecision[i].Format("%2.0f��",f60leftOutlinePos[i]);
		//	m_List_ResultInfo.InsertItem(i,tmpMillingPrecision[i]);
		//}
		//tmpMillingPrecision[0].Format("��̱�");
		//m_List_ResultInfo.InsertItem(precisionPointNum,tmpMillingPrecision[0]);
		double currentDistance=0.0,RightcurrentDistance=0.0;
		if (m_curOverValueIndex>=0 && m_curOverValueIndex<OverValueHdmVec.size())
		{
			currentDistance=OverValueHdmVec[m_curOverValueIndex];
			leftOverValueFlag=TRUE;

			for (unsigned int i=0;i<tmp_m_startAndEndVec.size();++i)
			{
				if (currentDistance>=tmp_m_startAndEndVec[i][0] && currentDistance<=tmp_m_startAndEndVec[i][1])
				{
					string tmpFileName=m_fileLineVec[i];
					int lastSymbolPos=tmpFileName.rfind('-');
					CString FileNameStr=tmpFileName.substr(0,lastSymbolPos+1).c_str();
					ClhSketchPath.Format("%s\\%sǰ�����潻��%c.txt",curFileDirection.c_str(),FileNameStr,tmpFileName.back());
				    HdmORXmlFilePath.Format("%s\\%s.txt",curFileDirection.c_str(),m_HdmLineVec[i]);

					currentFileIndex=i;
					if (currentFileIndex!=lastFileIndex)
					{
						lastFileIndex=currentFileIndex;
						m_LeftOutLineFileOffset=0;
						m_PrecisionFileOffset=0;
					}
					break;
				}
			}
			//��ȡ��ʾ������
			ReadOutline(currentDistance,LastlocalFileX,LastlocalFileY,LastlocalFilePointNum,m_LeftOutLineFileOffset,ClhSketchPath);
			m_pLeftTopAfterLineSerie->ClearSerie();
			m_pLeftTopAfterLineSerie->AddPoints(LastlocalFileX,LastlocalFileY,LastlocalFilePointNum);

			//��ȡ��ʾ����澫��
			ReadPrecisionOrMill(currentDistance,f60LeftOutlineError,precisionPointNum,m_PrecisionFileOffset,HdmORXmlFilePath);
			m_pLeftBottomLineSerie->ClearSerie();
			m_pLeftBottomLineSerie->AddPoints(f60leftOutlinePos,f60LeftOutlineError,precisionPointNum);
			m_pLeftBottomPointSerie->ClearSerie();
			m_pLeftBottomPointSerie->AddPoints(f60leftOutlinePos,f60LeftOutlineError,precisionPointNum);

			//�����ұ���Ϣ��
			CString tmpPrecisonLeft="";
			for (int i=0;i<precisionPointNum;++i)
			{
				tmpPrecisonLeft.Format("%7.4f",f60LeftOutlineError[i]);
				m_List_ResultInfo.SetItemText(i,1,tmpPrecisonLeft);
			}
			//�������
			int iK=(int)currentDistance/1000;
			double iD=currentDistance-1000*iK;
			string tmpDetectRoad=CsDetectRoad;
			tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
			tmpMillingPrecision[0].Format("%s%d+%0.1f",tmpDetectRoad.c_str(),iK,iD);
			m_List_ResultInfo.SetItemText(precisionPointNum,1,tmpMillingPrecision[0]);
		}
		else
		{
			tmpMillingPrecision[0].Format("�Ѵ��");
			m_List_ResultInfo.SetItemText(precisionPointNum,1,tmpMillingPrecision[0]);
			leftOverValueFlag=FALSE;
		}
		if (m_curOverValueIndex>=0 && m_curOverValueIndex<RightOverValueHdmVec.size())
		{

			RightcurrentDistance=RightOverValueHdmVec[m_curOverValueIndex];
			rightOverValueFlag=TRUE;
			for (unsigned int i=0;i<tmp_m_startAndEndVec.size();++i)
			{
				if (RightcurrentDistance>=tmp_m_startAndEndVec[i][0] && RightcurrentDistance<=tmp_m_startAndEndVec[i][1])
				{
					string RighttmpFileName=m_RightfileLineVec[i];
					int lastSymbolPos=RighttmpFileName.rfind('-');
					CString RightFileNameStr=RighttmpFileName.substr(0,lastSymbolPos+1).c_str();
					RightClhSketchPath.Format("%s\\%sǰ�Һ���潻��%c.txt",curFileDirection.c_str(),RightFileNameStr,RighttmpFileName.back());
					RightHdmORXmlFilePath.Format("%s\\%s.txt",curFileDirection.c_str(),m_RightHdmLineVec[i]);
					currentFileIndex=i;
					if (currentFileIndex!=lastFileIndex)
					{
						lastFileIndex=currentFileIndex;
						m_RightOutLineFileOffset=0;
						m_RightPrecisionFileOffset=0;
					}
					break;
				}
			}
			//��ȡ��ʾ������
			ReadOutline(RightcurrentDistance,LastlocalFileRightX,LastlocalFileRightY,RightLastlocalFilePointNum,m_RightOutLineFileOffset,RightClhSketchPath);
			//������Xֵ��Ҫ������
			for (int i=0;i<RightLastlocalFilePointNum;++i)
			{
				LastlocalFileRightX[i]=-LastlocalFileRightX[i];
			}
			m_pRightTopAfterLineSerie->ClearSerie();
			m_pRightTopAfterLineSerie->AddPoints(LastlocalFileRightX,LastlocalFileRightY,RightLastlocalFilePointNum);

			//��ȡ��ʾ�Ҷ��澫��
			ReadPrecisionOrMill(RightcurrentDistance,f60RightOutlineError,precisionPointNum,m_RightPrecisionFileOffset,RightHdmORXmlFilePath);
			m_pRightBottomLineSerie->ClearSerie();
			m_pRightBottomLineSerie->AddPoints(f60RightOutlinePos,f60RightOutlineError,precisionPointNum);
			m_pRightBottomPointSerie->ClearSerie();
			m_pRightBottomPointSerie->AddPoints(f60RightOutlinePos,f60RightOutlineError,precisionPointNum);

			//������Ϣ��
			CString tmpPrecisonRight="";
			for (int i=0;i<precisionPointNum;++i)
			{
				tmpPrecisonRight.Format("%7.4f",f60RightOutlineError[i]);
				m_List_ResultInfo.SetItemText(i,2,tmpPrecisonRight);
			}
			//�������
			int iK=(int)RightcurrentDistance/1000;
			double iD=RightcurrentDistance-1000*iK;
			string tmpDetectRoad=CsDetectRoad;
			tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
			tmpMillingPrecision[0].Format("%s%d+%0.1f",tmpDetectRoad.c_str(),iK,iD);
			m_List_ResultInfo.SetItemText(precisionPointNum,2,tmpMillingPrecision[0]);
		}
		else
		{
			rightOverValueFlag=FALSE;
			tmpMillingPrecision[0].Format("�Ѵ��");
			m_List_ResultInfo.SetItemText(precisionPointNum,2,tmpMillingPrecision[0]);
		}
	}
	else
	{
		MessageBox(_T("�����ڳ��޵�����"),_T("�ֹ�����������"));
		
	}
}


void CHighPrecisionDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_havePressAnalyse ||m_startAndEndVec.empty())
	{
		return;
	}
	m_Spin1.SetPos(5000);
	bool bIsStartOrEnd=false;
	if(pNMUpDown->iDelta == -1) // �����ֵΪ-1 , ˵�������Spin������ļ�ͷ
	{
		if (analyseMode==After_SinglePrecision ||analyseMode==After_SingleMilling ||analyseMode==Before_SinglePrecision)
		{
			if (fabs(m_Edit_DistanceReal-m_startAndEndVec[currentFileIndex][0])<1e-6)
			{
				if (currentFileIndex==0)
				{
					MessageBox(_T("�ѵ�����ϳĥ��һ������"),_T("�ֹ�����������"));
					
					bIsStartOrEnd=true;
				}
				else
					m_Edit_DistanceReal-=0.1;
			}
			else
				m_Edit_DistanceReal-=0.1;
			if (CsDirection ==_T("��"))
			{
				//m_Edit_DistanceReal+=0.2;
			}
		}
		else if (analyseMode==After_Transfinite || analyseMode==Before_Transfinite)
		{
			if (m_curOverValueIndex==0)
			{
				MessageBox(_T("�Ѿ����˵�һ����������"),_T("�ֹ�����������"));
				
				bIsStartOrEnd=true;
			}
			else
			{
				m_curOverValueIndex-=1;
			}
		}
		if (m_LeftOutLineFileOffset>=2000)
		{
			m_LeftOutLineFileOffset-=2000;
		}
		if (m_PrecisionFileOffset>=1200)
		{
			m_PrecisionFileOffset-=1200;
		}
		if (m_LeftMillingFileOffset>=1200)
		{
			m_LeftMillingFileOffset-=1200;
		}
		if (m_LeftBeforeOutlineFileOffset>=2000)
		{
			m_LeftBeforeOutlineFileOffset-=2000;
		}
		if (m_RightOutLineFileOffset>=2000)
		{
			m_RightOutLineFileOffset-=2000;
		}
		if (m_RightPrecisionFileOffset>=1200)
		{
			m_RightPrecisionFileOffset-=1200;
		}
		if (m_RightMillingFileOffset>=1200)
		{
			m_RightMillingFileOffset-=1200;
		}
		if (m_RightBeforeOutlineFileOffset>=2000)
		{
			m_RightBeforeOutlineFileOffset-=2000;
		}
		//����ʱ����������Ծ�ԣ����Ժ��˵�ʱ��û�������α�ֵ����ͷ��ʼ��
		if (analyseMode==After_Transfinite || analyseMode==Before_Transfinite)
		{
			m_LeftOutLineFileOffset=0;
			m_PrecisionFileOffset=0;
			m_LeftBeforeOutlineFileOffset=0;

			m_RightOutLineFileOffset=0;
			m_RightPrecisionFileOffset=0;
			m_RightBeforeOutlineFileOffset=0;
		}
	}
	else if (pNMUpDown->iDelta == 1)
	{
		if (analyseMode==After_SinglePrecision ||analyseMode==After_SingleMilling ||analyseMode==Before_SinglePrecision)
		{
			if (fabs(m_Edit_DistanceReal-m_startAndEndVec[currentFileIndex][1])<1e-6)
			{
				if (currentFileIndex==m_startAndEndVec.size()-1)
				{
					MessageBox(_T("�ѵ�����ϳĥ���һ������"),_T("�ֹ�����������"));
					
					bIsStartOrEnd=true;
				}
				else
					m_Edit_DistanceReal+=0.1;
			}
			else
				m_Edit_DistanceReal+=0.1;
			if (CsDirection ==_T("��"))
			{
				//m_Edit_DistanceReal-=0.2;
			}
		}
		else if (analyseMode==After_Transfinite ||analyseMode==Before_Transfinite)
		{
			if (m_curOverValueIndex+1>=OverValueHdmVec.size() &&m_curOverValueIndex+1>=RightOverValueHdmVec.size())
			{
				MessageBox(_T("�Ѿ��������һ����������"),_T("�ֹ�����������"));
				
				bIsStartOrEnd=true;
			}
			else
			{
				m_curOverValueIndex+=1;
			}
		}

		if (m_LeftOutLineFileOffset>=50)
		{
			m_LeftOutLineFileOffset-=50;
		}
		if (m_PrecisionFileOffset>=50)
		{
			m_PrecisionFileOffset-=50;
		}
		if (m_LeftMillingFileOffset>=50)
		{
			m_LeftMillingFileOffset-=50;
		}
		if (m_LeftBeforeOutlineFileOffset>=50)
		{
			m_LeftBeforeOutlineFileOffset-=50;
		}
		if (m_RightOutLineFileOffset>=50)
		{
			m_RightOutLineFileOffset-=50;
		}
		if (m_RightPrecisionFileOffset>=50)
		{
			m_RightPrecisionFileOffset-=50;
		}
		if (m_RightMillingFileOffset>=50)
		{
			m_RightMillingFileOffset-=50;
		}
		if (m_RightBeforeOutlineFileOffset>=50)
		{
			m_RightBeforeOutlineFileOffset-=50;
		}
		
	}
	UpdateData(FALSE);
	if (!bIsStartOrEnd)
	{
		if (analyseMode==After_SinglePrecision)
		{
			//�������
			CString strCurDist;
			UpdateData(TRUE);
			int iK=(int)m_Edit_DistanceReal/1000;
			double iD=m_Edit_DistanceReal-1000*iK;
			string tmpDetectRoad=CsDetectRoad;
			tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
			strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
			SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
			AfterSingleOutlinePrecisionDisp(m_Edit_DistanceReal,m_Edit_DistanceReal);
		}
		else if (analyseMode==After_SingleMilling)
		{
			//�������
			CString strCurDist;
			UpdateData(TRUE);
			int iK=(int)m_Edit_DistanceReal/1000;
			double iD=m_Edit_DistanceReal-1000*iK;
			string tmpDetectRoad=CsDetectRoad;
			tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
			strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
			SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
			AfterSingleOutlineMillingAmountDisp(m_Edit_DistanceReal,m_Edit_DistanceReal);
		}
		else if (analyseMode==After_Transfinite)
		{
			AfterTransfiniteDataViewDisp();
		}
		else if (analyseMode==Before_SinglePrecision)
		{
			//�������
			CString strCurDist;
			UpdateData(TRUE);
			int iK=(int)m_Edit_DistanceReal/1000;
			double iD=m_Edit_DistanceReal-1000*iK;

			m_edit_distance_str.Format("%0.1f", (float)iD);
			m_edit_distance2_str.Format("%d", (int)iK);

			UpdateData(FALSE);


			string tmpDetectRoad=CsDetectRoad;
			tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
			strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
			SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
			BeforeSingleOutlinePrecisionDisp(m_Edit_DistanceReal,m_Edit_DistanceReal);
		}
		else if (analyseMode==Before_Transfinite)
		{
			BeforeTransfiniteDataViewDisp();
		}
	}
	*pResult = 0;
}
// ��ȡ����ʾ��׼����
int CHighPrecisionDlg::DisplayStandardOutline(void)
{
		if (m_OutlineType==0)   //50��
		{
			m_pLeftTopStandardLineSerie->ClearSerie();
			m_pLeftTopStandardLineSerie->AddPoints(pStandardDataX50,pStandardDataY50,StandardPointNum50);

			m_pRightTopStandardLineSerie->ClearSerie();
			m_pRightTopStandardLineSerie->AddPoints(pRightStandDataX50,pStandardDataY50,StandardPointNum50);
		}
		else if (m_OutlineType==1) //60��
		{
			m_pLeftTopStandardLineSerie->ClearSerie();
			m_pLeftTopStandardLineSerie->AddPoints(pStandardDataX,pStandardDataY,StandardPointNum);

			m_pRightTopStandardLineSerie->ClearSerie();
			m_pRightTopStandardLineSerie->AddPoints(pRightStandDataX,pStandardDataY,StandardPointNum);
		}
		return 0;
}


void CHighPrecisionDlg::OnCbnSelchangeComboModelsel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ÿ�α任ģʽ����Ҫ�����еı������г�ʼ��
	ResetAllData();
	m_havePressAnalyse=FALSE;
	int curSelIndex=m_Combo_ModelSel.GetCurSel();
	//ϳĥ�����
	if (m_startAndEndVec.empty())
	{
		return;
	}
	if (IsAfterMillFlag)
	{
		if (curSelIndex==1 || curSelIndex==4)
		{
			//����������̬�����洢�ļ����ݵ������������//
			int Arraysize = (int)((abs(m_startAndEndVec.back()[1]-m_startAndEndVec[0][0])+0.1))*10+100;
			for (unsigned int i=0;i<localFileHdmVec.size();++i)
			{
				if (localFileHdmVec[i]==NULL &&RightlocalFileHdmVec[i]==NULL)
				{
					localFileHdmVec[i]=new double[Arraysize];
					RightlocalFileHdmVec[i]=new double[Arraysize];
				}
			}
			//�����󾫶�ֵ����
			//�������ʼ
			CStdioFile fMeasureFile;
			bool bFinishFlag=false;
			int CntLine=0;//��������
			int CntLine2=0;//��������
			for (unsigned int i=0;i<m_startAndEndVec.size();++i)
			{
				HdmORXmlFilePath.Format("%s\\%s.txt",curFileDirection.c_str(),m_HdmLineVec[i]);
				RightHdmORXmlFilePath.Format("%s\\%s.txt",curFileDirection.c_str(),m_RightHdmLineVec[i]);

				if(fMeasureFile.Open(HdmORXmlFilePath, CFile::modeRead))
				{
					CString strLinetemp="";
					while(fMeasureFile.ReadString(strLinetemp))
					{	
						char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
						char *strtemp = NULL;  
						strtemp = strtok(str, " ");  
						char *TopData = strtemp; 
						//////////////////////////////////////////////////////////////////////////
						if (CsDirection == _T("��"))
						{
							if (atof(TopData) - m_startAndEndVec.back()[1] < 0)
							{
								break;
							}
						}
						else
						{
							if (atof(TopData) - m_startAndEndVec.back()[1] > 0)
							{
								break;
							}
						}
						/*if (atof(TopData)-m_startAndEndVec.back()[1]>0)
						{
							break;
						}*/
						
						if(strtemp !=NULL)
						{
							strtemp = strtok(NULL, " ");  
						}
						char *PrecisionOrMill=strtemp;

						localFileHdmVec[0][CntLine]=atof(PrecisionOrMill);
						//========
						double isErrorData = 0;
						if (abs(atof(PrecisionOrMill))>5)
						{
							isErrorData = 1;
						}
						for (int i=1;i<precisionPointNum;++i)
						{
							fMeasureFile.ReadString(strLinetemp);
							str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
							strtemp = NULL; 
							strtemp = strtok(str, " ");  
							TopData = strtemp; 
							if(strtemp !=NULL)
							{
								strtemp = strtok(NULL, " ");  
							}
							PrecisionOrMill=strtemp;
							//========
							double tmpFlag = 0;
							tmpFlag = atof(PrecisionOrMill);

							if ((i==1||i==2)&&(tmpFlag==0||tmpFlag==-1)||abs(tmpFlag)>5)
							{
								isErrorData = 1;
								//break;
							}
							//======
							/*if (abs(tmpFlag)>5)
							{
							isErrorData = 1;
							break;
							}*/
							if (isErrorData==0)
							{
								localFileHdmVec[i][CntLine]=atof(PrecisionOrMill);
							}
						}
						//�洢��������
						for (int k=0;k<precisionPointNum;++k)
						{
							if ((localFileHdmVec[k][CntLine]>=0 && localFileHdmVec[k][CntLine]>dPositiveLimit) ||(localFileHdmVec[k][CntLine]<0 && localFileHdmVec[k][CntLine]<dNegetiveLimit))
							{
								OverValueHdmVec.push_back(atof(TopData));
								break;
							}
						}
						if (isErrorData==0)
						{
							++CntLine;
						}
						//++CntLine;
					}
					m_PrecisionNumCnt=CntLine;
					fMeasureFile.Close();
				}
				//��ȡ�Ҿ���
				if(fMeasureFile.Open(RightHdmORXmlFilePath, CFile::modeRead))
				{
					CString strLinetemp="";
					while(fMeasureFile.ReadString(strLinetemp))
					{	
						char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
						char *strtemp = NULL;  
						strtemp = strtok(str, " ");  
						char *TopData = strtemp; 
						//�Ѿ������յ�
						//////////////////////////////////////////////////////////////////////////
						if (CsDirection == _T("��"))
						{
							if (atof(TopData) - m_startAndEndVec.back()[1] < 0)
							{
								break;
							}
						}
						else
						{
							if (atof(TopData) - m_startAndEndVec.back()[1] > 0)
							{
								break;
							}
						}
						/*if (atof(TopData)-m_startAndEndVec.back()[1]>0)
						{
							break;
						}*/
						if(strtemp !=NULL)
						{
							strtemp = strtok(NULL, " ");  
						}
						char *PrecisionOrMill=strtemp;
						RightlocalFileHdmVec[0][CntLine2]=atof(PrecisionOrMill);
						//==========
						double isErrorDataR = 0;
						if (abs(atof(PrecisionOrMill))>5)
						{
							isErrorDataR = 1;
						}
						for (int i=1;i<precisionPointNum;++i)
						{
							fMeasureFile.ReadString(strLinetemp);
							str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
							strtemp = NULL; 
							strtemp = strtok(str, " ");  
							TopData = strtemp; 
							if(strtemp !=NULL)
							{
								strtemp = strtok(NULL, " ");  
							}
							PrecisionOrMill=strtemp;
							//========
							double tmpFlag = 0;
							tmpFlag = atof(PrecisionOrMill);

							if ((i==1||i==2)&&(tmpFlag==0||tmpFlag==-1)||abs(tmpFlag)>5)
							{
								isErrorDataR = 1;
								//break;
							}
							/*if (abs(tmpFlag)>5)
							{
							isErrorDataR = 1;
							break;
							}*/

							if (isErrorDataR==0)
							{
								RightlocalFileHdmVec[i][CntLine2]=atof(PrecisionOrMill);
							}
							//RightlocalFileHdmVec[i][CntLine2]=atof(PrecisionOrMill);
						}
						//�洢��������
						for (int k=0;k<precisionPointNum;++k)
						{
							if ((RightlocalFileHdmVec[k][CntLine2]>=0 && RightlocalFileHdmVec[k][CntLine2]>dPositiveLimit) ||(RightlocalFileHdmVec[k][CntLine2]<0 && RightlocalFileHdmVec[k][CntLine2]<dNegetiveLimit))
							{
								RightOverValueHdmVec.push_back(atof(TopData));
								break;
							}
						}
						//===========
						if (isErrorDataR==0)
						{
							++CntLine2;
						}
						//++CntLine2;
					}
					if (CntLine2<m_PrecisionNumCnt)
					{
						m_PrecisionNumCnt=CntLine2;
					}
					fMeasureFile.Close();
				}
			}
		}
		else if (curSelIndex==3)
		{
			//����������̬�����洢�ļ����ݵ������������//
			int Arraysize = (int)((abs(m_startAndEndVec.back()[1]-m_startAndEndVec[0][0])+0.1))*10+100;
			for (unsigned int i=0;i<localFileHdmVec.size();++i)
			{
				if (localFileHdmVec[i]==NULL)
				{
					localFileHdmVec[i]=new double[Arraysize];
					RightlocalFileHdmVec[i]=new double[Arraysize];
				}
			}
			//����ϳĥ������
			//�������ʼ
			CStdioFile fMeasureFile;
			bool bFinishFlag=false;
			int CntLine=0;//��������
			int CntLine2=0;//��������
			for (unsigned int i=0;i<m_startAndEndVec.size();++i)
			{
				HdmORXmlFilePath.Format("%s\\%s.txt",curFileDirection.c_str(),m_XmlLineVec[i]);
				RightHdmORXmlFilePath.Format("%s\\%s.txt",curFileDirection.c_str(),m_RightXmlLineVec[i]);

				//CStdioFile tmpfMeasureFile;
				//tmpfMeasureFile.Open(HdmORXmlFilePath, CFile::modeRead);
				//fMeasureFile.Open(HdmORXmlFilePath, CFile::modeRead)

				//��ȡ��ϳĥ��
				if(fMeasureFile.Open(HdmORXmlFilePath, CFile::modeRead))
				{
					CString strLinetemp="";
					while(fMeasureFile.ReadString(strLinetemp))
					{	
						char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
						char *strtemp = NULL;  
						strtemp = strtok(str, " ");  
						char *TopData = strtemp; 
						//////////////////////////////////////////////////////////////////////////
						if (CsDirection == _T("��"))
						{
							if (atof(TopData) - m_startAndEndVec.back()[1] < 0)
							{
								break;
							}
						}
						else
						{
							if (atof(TopData) - m_startAndEndVec.back()[1] > 0)
							{
								break;
							}
						}
						/*if (atof(TopData)-m_startAndEndVec.back()[1]>0)
						{
							break;
						}*/
						if(strtemp !=NULL)
						{
							strtemp = strtok(NULL, " ");  
						}
						char *PrecisionOrMill=strtemp;
						localFileHdmVec[0][CntLine]=atof(PrecisionOrMill);
						//===========�����쳣����
						/*double isErrorData = 1;
						CStdioFile tmpfMeasureFile(fMeasureFile);
						for (int i=1;i<precisionPointNum;++i)
						{
						tmpfMeasureFile.ReadString(strLinetemp);
						str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
						strtemp = NULL; 
						strtemp = strtok(str, " ");  
						TopData = strtemp; 
						if(strtemp !=NULL)
						{
						strtemp = strtok(NULL, " ");  
						}
						PrecisionOrMill=strtemp;
						double tmpFlag = atof(PrecisionOrMill);
						if (tmpFlag!=0&&tmpFlag!=-1)
						{
						isErrorData = 0;
						}
						}
						if (isErrorData==1)
						{
						continue;
						}*/
						//===========
						double isErrorData = 0;
						if (abs(atof(PrecisionOrMill))>3)
						{
							isErrorData = 1;
						}
						for (int i=1;i<precisionPointNum;++i)
						{
							fMeasureFile.ReadString(strLinetemp);
							str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
							strtemp = NULL; 
							strtemp = strtok(str, " ");  
							TopData = strtemp; 
							if(strtemp !=NULL)
							{
								strtemp = strtok(NULL, " ");  
							}
							PrecisionOrMill=strtemp;
							//=======
							double tmpFlag = 0;
							tmpFlag = atof(PrecisionOrMill);
							
							if ((i==1||i==2)&&(tmpFlag==0||tmpFlag==-1)||abs(tmpFlag)>3)
							{
								isErrorData = 1;
								//break;
							}
							/*if (abs(tmpFlag)>5)
							{
								isErrorData = 1;
								break;
							}*/
							//==========
							if (isErrorData==0)
							{
								localFileHdmVec[i][CntLine]=atof(PrecisionOrMill);
							}
							//localFileHdmVec[i][CntLine]=atof(PrecisionOrMill);
						}
						if (isErrorData==0)
						{
							++CntLine;
						}
						//++CntLine;
					}
					//m_PrecisionNumCnt=CntLine;
					if (CntLine<m_PrecisionNumCnt)
					{
						m_PrecisionNumCnt=CntLine;
					}
					fMeasureFile.Close();
				}
				//��ȡ��ϳĥ��
				CntLine=0;
				if(fMeasureFile.Open(RightHdmORXmlFilePath, CFile::modeRead))
				{
					CString strLinetemp="";
					while(fMeasureFile.ReadString(strLinetemp))
					{	
						char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
						char *strtemp = NULL;  
						strtemp = strtok(str, " ");  
						char *TopData = strtemp; 
						//////////////////////////////////////////////////////////////////////////
						if (CsDirection == _T("��"))
						{
							if (atof(TopData) - m_startAndEndVec.back()[1] < 0)
							{
								break;
							}
						}
						else
						{
							if (atof(TopData) - m_startAndEndVec.back()[1] > 0)
							{
								break;
							}
						}
						/*if (atof(TopData)-m_startAndEndVec.back()[1]>0)
						{
							break;
						}*/
						if(strtemp !=NULL)
						{
							strtemp = strtok(NULL, " ");  
						}
						char *PrecisionOrMill=strtemp;
						RightlocalFileHdmVec[0][CntLine2]=atof(PrecisionOrMill);
						//=====
						double isErrorDataR = 0;
						if (abs(atof(PrecisionOrMill))>3)
						{
							isErrorDataR = 1;
						}
						for (int i=1;i<precisionPointNum;++i)
						{
							fMeasureFile.ReadString(strLinetemp);
							str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
							strtemp = NULL; 
							strtemp = strtok(str, " ");  
							TopData = strtemp; 
							if(strtemp !=NULL)
							{
								strtemp = strtok(NULL, " ");  
							}
							else
								MessageBox("error ptr");
							PrecisionOrMill=strtemp;
							//======
							double tmpFlag = 0;
							tmpFlag = atof(PrecisionOrMill);
							//double isErrorDataR;
							if (((i==1||i==2)&&(tmpFlag==0||tmpFlag==-1))||abs(tmpFlag)>3)
							{
								isErrorDataR = 1;
								//isErrorDataR = 0;
								//break;
							}							
							//=====
							if (isErrorDataR==0)
							{
								RightlocalFileHdmVec[i][CntLine2]=atof(PrecisionOrMill);
							}
							//RightlocalFileHdmVec[i][CntLine2]=atof(PrecisionOrMill);
						}
						if (isErrorDataR==0)
						{
							++CntLine2;
						}
						//++CntLine2;
					}
					if (CntLine2<m_PrecisionNumCnt)
					{
						m_PrecisionNumCnt=CntLine2;
					}
					fMeasureFile.Close();
				}
			}
		}
		if (curSelIndex!=4)
		{
			m_Edit_DistanceReal=m_Edit_Distance;
			//�������
			CString strCurDist;
			UpdateData(TRUE);
			int iK=(int)m_Edit_DistanceReal/1000;
			double iD=m_Edit_DistanceReal-1000*iK;
			m_edit_distance_str.Format("%0.1f", (float)iD);
			m_edit_distance2_str.Format("%d", (int)iK);
			string tmpDetectRoad=CsDetectRoad;
			tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
			strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
			SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
		}
	}
	else //ϳĥǰ����
	{
		if (curSelIndex==1 ||curSelIndex==2)
		{
			//����������̬�����洢�ļ����ݵ������������//
			int Arraysize = (int)((abs(m_startAndEndVec.back()[1]-m_startAndEndVec[0][0])+0.1))*10+100;
			for (unsigned int i=0;i<localFileHdmVec.size();++i)
			{
				if (localFileHdmVec[i]==NULL &&RightlocalFileHdmVec[i]==NULL)
				{
					localFileHdmVec[i]=new double[Arraysize];
					RightlocalFileHdmVec[i]=new double[Arraysize];
				}
			}
			//�����󾫶�ֵ����
			//�������ʼ

			CStdioFile fMeasureFile;
			bool bFinishFlag=false;
			int CntLine=0;//��������
			int CntLine2=0;
			for (unsigned int i=0;i<m_startAndEndVec.size();++i)
			{
				HdmORXmlFilePath.Format("%s\\%s.txt",curFileDirection.c_str(),m_HdmLineVec[i]);
				RightHdmORXmlFilePath.Format("%s\\%s.txt",curFileDirection.c_str(),m_RightHdmLineVec[i]);
				if(fMeasureFile.Open(HdmORXmlFilePath, CFile::modeRead))
				{
					CString strLinetemp="";
					while(fMeasureFile.ReadString(strLinetemp))
					{	
						char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
						char *strtemp = NULL;  
						strtemp = strtok(str, " ");  
						char *TopData = strtemp; 
						//����������̾�ֹͣ��ʹ������̵������ҽ϶̵�
						if (CsDirection==_T("��"))
						{
							if (atof(TopData) - m_startAndEndVec.back()[1] < 0)
							{
								break;
							}
						}
						else
						{
							if (atof(TopData) - m_startAndEndVec.back()[1] > 0)
							{
								break;
							}
						}
						/*if (atof(TopData)-m_startAndEndVec.back()[1]>0)
						{
							break;
						}*/
						if(strtemp !=NULL)
						{
							strtemp = strtok(NULL, " ");  
						}
						//==========
						double isErrorData = 0;
						
						char *PrecisionOrMill=strtemp;
						//==============
						if (abs(atof(PrecisionOrMill))>5)
						{
							isErrorData = 1;
						}

						localFileHdmVec[0][CntLine]=atof(PrecisionOrMill);
						
						for (int i=1;i<precisionPointNum;++i)
						{
							fMeasureFile.ReadString(strLinetemp);
							str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
							strtemp = NULL; 
							strtemp = strtok(str, " ");  
							TopData = strtemp; 
							if(strtemp !=NULL)
							{
								strtemp = strtok(NULL, " ");  
							}
							PrecisionOrMill=strtemp;
							//=======
							//======
							double tmpFlag = 0;
							tmpFlag = atof(PrecisionOrMill);							
							if ((i==1||i==2)&&(tmpFlag==0||tmpFlag==-1)||abs(tmpFlag)>5)
							{
								isErrorData = 1;
								//break;
							}					
							//=====
							if (isErrorData==0)
							{
								localFileHdmVec[i][CntLine]=atof(PrecisionOrMill);								
							}
						}
						//�洢��������

						for (int k=0;k<precisionPointNum;++k)
						{
							if ((localFileHdmVec[k][CntLine]>=0 && localFileHdmVec[k][CntLine]>dPositiveLimit) ||(localFileHdmVec[k][CntLine]<0 && localFileHdmVec[k][CntLine]<dNegetiveLimit))
							{
								OverValueHdmVec.push_back(atof(TopData));
								break;
							}
						}
						//===
						if (isErrorData==0)
						{
							++CntLine;
						}

						//++CntLine;
					}
					m_PrecisionNumCnt=CntLine;
					fMeasureFile.Close();
				}
				//��ȡϳĥǰ�Ҿ���
				if(fMeasureFile.Open(RightHdmORXmlFilePath, CFile::modeRead))
				{
					CString strLinetemp="";
					while(fMeasureFile.ReadString(strLinetemp))
					{	
						char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
						char *strtemp = NULL;  
						strtemp = strtok(str, " ");  
						char *TopData = strtemp; 
						//����������̾�ֹͣ��ʹ������̵������ҽ϶̵�
						if (CsDirection == _T("��"))
						{
							if (atof(TopData) - m_startAndEndVec.back()[1] < 0)
							{
								break;
							}
						}
						else
						{
							if (atof(TopData) - m_startAndEndVec.back()[1] > 0)
							{
								break;
							}
						}
						/*if (atof(TopData)-m_startAndEndVec.back()[1]>0)
						{
							break;
						}*/
						if(strtemp !=NULL)
						{
							strtemp = strtok(NULL, " ");  
						}
						char *PrecisionOrMill=strtemp;
						//============
						double isErrorDataR = 0;
						if (abs(atof(PrecisionOrMill))>5)
						{
							isErrorDataR = 1;
						}
						RightlocalFileHdmVec[0][CntLine2]=atof(PrecisionOrMill);
						
						for (int i=1;i<precisionPointNum;++i)
						{
							fMeasureFile.ReadString(strLinetemp);
							str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
							strtemp = NULL; 
							strtemp = strtok(str, " ");  
							TopData = strtemp; 
							if(strtemp !=NULL)
							{
								strtemp = strtok(NULL, " ");  
							}
							PrecisionOrMill=strtemp;
							double tmpFlag = 0;
							tmpFlag = atof(PrecisionOrMill);							
							if ((i==1||i==2)&&(tmpFlag==0||tmpFlag==-1)||abs(tmpFlag)>5)
							{
								isErrorDataR = 1;
								//break;
							}							
							//=====
							if (isErrorDataR==0)
							{
								RightlocalFileHdmVec[i][CntLine2]=atof(PrecisionOrMill);
							}
						}
						//�洢��������
						for (int k=0;k<precisionPointNum;++k)
						{
							if ((RightlocalFileHdmVec[k][CntLine2]>=0 && RightlocalFileHdmVec[k][CntLine2]>dPositiveLimit) ||(RightlocalFileHdmVec[k][CntLine2]<0 && RightlocalFileHdmVec[k][CntLine2]<dNegetiveLimit))
							{
								RightOverValueHdmVec.push_back(atof(TopData));
								break;
							}
						}//=====
						if (isErrorDataR==0)
						{
							++CntLine2;
						}

						//++CntLine2;
					}
					if (CntLine2<CntLine)
					{
						m_PrecisionNumCnt=CntLine2;
					}
					fMeasureFile.Close();
				}
			}
		}
		if (curSelIndex!=2)
		{
			m_Edit_DistanceReal=m_Edit_Distance;
			//�������
			CString strCurDist;
			UpdateData(TRUE);
			int iK=(int)m_Edit_DistanceReal/1000;
			double iD=m_Edit_DistanceReal-1000*iK;
			m_edit_distance_str.Format("%0.1f", (float)iD);
			m_edit_distance2_str.Format("%d", (int)iK);
			string tmpDetectRoad=CsDetectRoad;
			tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
			strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
			SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
		}
	}
}


void CHighPrecisionDlg::OnBnClickedButtonSelectdistance()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_havePressAnalyse)
	{
		UpdateData(TRUE);
		m_LeftOutLineFileOffset=0;
		m_PrecisionFileOffset=0;
		m_LeftMillingFileOffset=0;
		m_LeftBeforeOutlineFileOffset=0;
		m_RightOutLineFileOffset=0;
		m_RightMillingFileOffset=0;
		m_RightBeforeOutlineFileOffset=0;
		m_RightPrecisionFileOffset=0;
		if (analyseMode==After_SinglePrecision)
		{
			AfterSingleOutlinePrecisionDisp(m_Edit_Distance,m_Edit_Distance);
		}
		else if (analyseMode==After_SingleMilling)
		{
			AfterSingleOutlineMillingAmountDisp(m_Edit_Distance,m_Edit_Distance);
		}
		else if(analyseMode==Before_SinglePrecision)
		{
			BeforeSingleOutlinePrecisionDisp(m_Edit_Distance,m_Edit_Distance);
		}
	}
}


void CHighPrecisionDlg::OnBnClickedButtonReport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_havePressAnalyse && !m_startAndEndVec.empty())
	{
		//����CADͼ
	if (isCreateCad)
	{
		
		if (m_OutlineType==0) //50��
		{
			double tmpX[PRECISION_NUM_50]={-24.6599,-23.1548,-17.3724,-11.5868,-5.7953,0,5.795,11.5868,17.3724,23.1548,24.4794,27.1304,29.4662,31.6509,33.4838,34.9904,36.0933,36.7722,37};
			for (int i=0;i<PRECISION_NUM_50;++i)
			{
				startiLeftOutlineAnaPointX[i]=tmpX[i];
			}
			double tmpY[PRECISION_NUM_50]={0.9008,1.094,1.4872,1.7691,1.9401,2,1.9401,1.7691,1.4872,1.094,0.9322,0.2339,-0.8516,-2.3784,-4.2114,-6.3615,-8.7254,-11.2568,-13.8615};
			for (int i=0;i<PRECISION_NUM_50;++i)
			{
				startiLeftOutlineAnaPointY[i]=tmpY[i];
			}

			double tmpendX[PRECISION_NUM_50]={-23.9506,-22.8452,-17.1394,-11.4301,-5.7156,0,5.7193,11.4304,17.1393,22.8462,23.8182,25.7623,27.4752,29.0774,30.4215,31.5263,32.3351,32.8329,33};
			for (int i=0;i<PRECISION_NUM_50;++i)
			{
				endiLeftOutlineAnaPointX[i]=tmpendX[i];
			}
			double tmpendY[PRECISION_NUM_50]={-3.0358,-2.894,-2.5061,-2.2278,-2.0594,-2,-2.0591,-2.2278,-2.506,-2.8941,-3.0128,-3.5249,-4.3209,-5.4406,-6.7848,-8.3615,-10.095,-11.9514,-13.8615};
			for (int i=0;i<PRECISION_NUM_50;++i)
			{
				endiLeftOutlineAnaPointY[i]=tmpendY[i];
			}

		}
		else if (m_OutlineType==1)
		{
			double tmpX[PRECISION_NUM_60]={-25.7913,-21.6077,-18.7996,-15.9587,-13.1074,-10.0653,-4.2727,0,4.2727,10.0733,13.1074,15.9587,18.7996,21.6077,25.7913,27.537,29.917,32.0588,33.9825,35.4074,36.5268,37.1891,37.3974};
			for (int i=0;i<PRECISION_NUM_60;++i)
			{
				startiLeftOutlineAnaPointX[i]=tmpX[i];
			}
			double tmpY[PRECISION_NUM_60]={-0.2493,0.6002,1.0447,1.3935,1.6429,1.7989,1.9557,2,1.9557,1.7989,1.6429,1.3935,1.0447,0.6002,-0.2493,-0.7657,-1.8744,-3.3741,-5.3129,-7.3648,-9.7744,-12.2601,-14.0977};
			for (int i=0;i<PRECISION_NUM_60;++i)
			{
				startiLeftOutlineAnaPointY[i]=tmpY[i];
			}

			double tmpendX[PRECISION_NUM_60]={-24.8915,-20.9141,-18.2429,-15.5406,-12.8284,-9.9267,-4.2029,0,4.2029,9.9267,12.8284,15.5406,18.2429,20.9141,24.8915,26.1717,27.917,29.4877,30.8984,31.9433,32.7642,33.2499,33.4026};
			for (int i=0;i<PRECISION_NUM_60;++i)
			{
				endiLeftOutlineAnaPointX[i]=tmpendX[i];
			}
			double tmpendY[PRECISION_NUM_60]={-4.1468,-3.3392,-2.9164,-2.5846,-2.3473,-2.1987,-2.0437,-2,-2.0437,-2.1987,-2.3473,-2.5846,-2.9164,-3.3392,-4.1468,-4.5254,-5.3385,-6.4383,-7.86,-9.3648,-11.1318,-12.9547,-14.3023};
			for (int i=0;i<PRECISION_NUM_60;++i)
			{
				endiLeftOutlineAnaPointY[i]=tmpendY[i];
			}
		}


		
		
		/*CDrawing drawing;*/
		static char szFilter[] = "DXF file format(*.dxf) |*.dxf|All Files (*.*)|*.*||";

		CFileDialog SaveDlg( FALSE, NULL, NULL/*LastFilePath*/, OFN_HIDEREADONLY | OFN_EXPLORER, szFilter, NULL ,0,FALSE);
		SaveDlg.m_ofn.lpstrTitle = "Save DXF File As";

		if(SaveDlg.DoModal()==IDOK)
		{	// Saving sample dxf file data
			CString DxfFileName( SaveDlg.GetPathName() );
			//		CDrawing drw;

			if(SaveDlg.GetFileExt().IsEmpty())
				DxfFileName += ".dxf";

			BOOL result=TRUE;

			// Create Drawing

			if (!drawing.isOpen())
			{
				if(!drawing.Create())
				{
					MessageBox("Fatal error on creating CDrawing!", "Error", MB_ICONERROR | MB_OK);
					return;
				}
			}
			
			// Tables Section ------------------------------------------
			//  LTYPE table type -------------------------
			LTYPE		ltype;
			OBJHANDLE	objhandle1;

			//  Continuous
			ZeroMemory(&ltype, sizeof(ltype));
			strcpy(ltype.Name, "Continuous");
			strcpy(ltype.DescriptiveText, "Solid line");
			objhandle1 = drawing.AddLinetype(&ltype);

			//  LAYER table type -------------------------
			LAYER	layer;

			// Layer1
			ZeroMemory(&layer, sizeof(layer));
			strcpy(layer.Name, "Layer1");
			layer.Color = COLOR_RED;
			layer.LineTypeObjhandle = objhandle1; // Continuous
			drawing.AddLayer(&layer);

			// Layer2
			ZeroMemory(&layer, sizeof(layer));
			strcpy(layer.Name, "Layer2");
			layer.Color = 2;
			layer.LineTypeObjhandle = objhandle1; // Continuous
			drawing.AddLayer(&layer);

			// Layer3
			ZeroMemory(&layer, sizeof(layer));
			strcpy(layer.Name, "Layer3");
			layer.Color = 3;
			layer.LineTypeObjhandle = objhandle1; // Continuous
			drawing.AddLayer(&layer);

			// Layer4
			ZeroMemory(&layer, sizeof(layer));
			strcpy(layer.Name, "Layer4");
			layer.Color = 4;
			layer.LineTypeObjhandle = objhandle1; // Continuous
			drawing.AddLayer(&layer);


			//��첿��
			//  DIMSTYLE table type ----------------------
			//DIMSTYLE	dimstyle;
			int originX=0,originY=0;
			result &=drawing.Line(-40-originX,originY+5,-40-originX,originY-40);
			//top axis
			result &=drawing.Line(-40-originX,originY+5,-40-originX+80,originY+5);
			//right axis
			result &=drawing.Line(-40-originX+80,originY+5,-40-originX+80,originY-40);
			//bottom axis
			result &=drawing.Line(-40-originX+80,originY-40,-40-originX,originY-40);
			//y�������
			int offset=5;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("5.00",-40-originX-12,originY+offset-1,3);

			offset=0;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("0.00",-40-originX-12,originY+offset-1,3);

			offset=-5;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-5.00",-40-originX-18,originY+offset-1,3);

			offset=-10;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-10.00",-40-originX-18,originY+offset-1,3);

			offset=-15;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-15.00",-40-originX-18,originY+offset-1,3);

			offset=-20;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-20.00",-40-originX-18,originY+offset-1,3);

			offset=-25;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-25.00",-40-originX-18,originY+offset-1,3);

			offset=-30;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-30.00",-40-originX-18,originY+offset-1,3);

			offset=-35;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-35.00",-40-originX-18,originY+offset-1,3);

			offset=-40;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-40.00",-40-originX-18,originY+offset-1,3);

			//x�������
			offset=0;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("-40",-40-originX+offset-3,originY-40-7,3);

			offset=10;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("-30",-40-originX+offset-3,originY-40-7,3);

			offset=20;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("-20",-40-originX+offset-3,originY-40-7,3);

			offset=30;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("-10",-40-originX+offset-3,originY-40-7,3);

			offset=40;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("0",-40-originX+offset-1,originY-40-7,3);

			offset=50;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("10",-40-originX+offset-1,originY-40-7,3);

			offset=60;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("20",-40-originX+offset-1,originY-40-7,3);

			offset=70;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("30",-40-originX+offset-1,originY-40-7,3);

			offset=80;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("40",-40-originX+offset-1,originY-40-7,3);

			// set current layer to Layer4
			result &= drawing.SetLayer("Layer4");
			result &= drawing.SetColor(COLOR_BLUE);

			//ʵ������
			ENTVERTEX vertexRealOutline[1280];
			ZeroMemory(vertexRealOutline, sizeof(ENTVERTEX)*1280);
			for (int i=0;i!=LastlocalFilePointNum;++i)
			{
				vertexRealOutline[i].Point.x=LastlocalFileX[i]-originX;
				//LastlocalFileY[i]=LastlocalFileY[i]-176;
				vertexRealOutline[i].Point.y=LastlocalFileY[i];
			}
			if (!((analyseMode==After_Transfinite ||analyseMode==Before_Transfinite)&& !leftOverValueFlag))
			{
				result &= drawing.PolyLine(vertexRealOutline, LastlocalFilePointNum);
			}
			result &= drawing.SetColor(COLOR_GREEN);
			//11����澫�ȱ�ǵ�
			char pNameTmp[PRECISION_NUM_60][8]={"13��","10��","8��","6��","4��","2��","1��","0��",
				"-1��","-2��","-4��","-6��","-8��","-10��","-13��","-20��","-30��","-40��","-50��","-60��","-70��","-80��","-87��"};
			for (int i=0;i<precisionPointNum;++i)
			{
				result &=drawing.Line(startiLeftOutlineAnaPointX[i],startiLeftOutlineAnaPointY[i],endiLeftOutlineAnaPointX[i],endiLeftOutlineAnaPointY[i]);
				result &=drawing.Text(pNameTmp[i],startiLeftOutlineAnaPointX[i],startiLeftOutlineAnaPointY[i],1);
			}
			/*result &=drawing.Line(startiLeftOutlineAnaPointX[0],startiLeftOutlineAnaPointY[0],endiLeftOutlineAnaPointX[0],endiLeftOutlineAnaPointY[0]);
			result &=drawing.Text("-10��",iLeftOutlineAnaPointX[0],iLeftOutlineAnaPointY[0]+2,3);
			result &=drawing.Line(iLeftOutlineAnaPointX[1],iLeftOutlineAnaPointY[1],iLeftOutlineAnaPointX[1],iLeftOutlineAnaPointY[1]+1);
			result &=drawing.Text("-2��",iLeftOutlineAnaPointX[1],iLeftOutlineAnaPointY[1]+2,3);
			result &=drawing.Line(iLeftOutlineAnaPointX[2],iLeftOutlineAnaPointY[2],iLeftOutlineAnaPointX[2],iLeftOutlineAnaPointY[2]+1);
			result &=drawing.Text("0��",iLeftOutlineAnaPointX[2]-1,iLeftOutlineAnaPointY[2]+2,3);
			result &=drawing.Line(iLeftOutlineAnaPointX[3],iLeftOutlineAnaPointY[3],iLeftOutlineAnaPointX[3],iLeftOutlineAnaPointY[3]+1);
			result &=drawing.Text("2��",iLeftOutlineAnaPointX[3],iLeftOutlineAnaPointY[3]+2,3);
			result &=drawing.Line(iLeftOutlineAnaPointX[4],iLeftOutlineAnaPointY[4]-1,iLeftOutlineAnaPointX[4],iLeftOutlineAnaPointY[4]);
			result &=drawing.Text("13��",iLeftOutlineAnaPointX[4],iLeftOutlineAnaPointY[4]-5,3);
			result &=drawing.Line(iLeftOutlineAnaPointX[5],iLeftOutlineAnaPointY[5],iLeftOutlineAnaPointX[5],iLeftOutlineAnaPointY[5]+1);
			result &=drawing.Text("36��",iLeftOutlineAnaPointX[5],iLeftOutlineAnaPointY[5]+2,3);
			result &=drawing.Line(iLeftOutlineAnaPointX[6],iLeftOutlineAnaPointY[6]-1,iLeftOutlineAnaPointX[6],iLeftOutlineAnaPointY[6]);
			result &=drawing.Text("50��",iLeftOutlineAnaPointX[6]-5,iLeftOutlineAnaPointY[6]-5,3);
			result &=drawing.Line(iLeftOutlineAnaPointX[7],iLeftOutlineAnaPointY[7],iLeftOutlineAnaPointX[7],iLeftOutlineAnaPointY[7]+1);
			result &=drawing.Text("87��",iLeftOutlineAnaPointX[7],iLeftOutlineAnaPointY[7]+2,3);
			*/
			char ptemp[PRECISION_NUM_60][8];
			char ptempPos[PRECISION_NUM_60][8];
			result &= drawing.SetColor(COLOR_WHITE);
			if (!((analyseMode==After_Transfinite ||analyseMode==Before_Transfinite)&& !leftOverValueFlag))
			{
				for (int i=0;i<precisionPointNum/3;++i)
				{
					sprintf(ptemp[i],"%06.4f",f60LeftOutlineError[i]);
					result &=drawing.Text(ptemp[i],-30+i*8,-15+originY,1);
					sprintf(ptempPos[i],"%d",i);
					result &=drawing.Text(pNameTmp[i],-30+i*8,-15+3+originY,1);
				}
				for (int i=precisionPointNum/3,j=0;i<precisionPointNum*2/3;++i,++j)
				{
					sprintf(ptemp[i],"%06.4f",f60LeftOutlineError[i]);
					result &=drawing.Text(ptemp[i],-30+j*8,-25+originY,1);
					sprintf(ptempPos[i],"%d",i);
					result &=drawing.Text(pNameTmp[i],-30+j*8,-25+3+originY,1);
				}

				for (int i=precisionPointNum*2/3,j=0;i<precisionPointNum;++i,++j)
				{
					sprintf(ptemp[i],"%06.4f",f60LeftOutlineError[i]);
					result &=drawing.Text(ptemp[i],-30+j*8,-35+originY,1);
					sprintf(ptempPos[i],"%d",i);
					result &=drawing.Text(pNameTmp[i],-30+j*8,-35+3+originY,1);
				}
			}
			result &= drawing.SetColor(COLOR_RED);
			//draw outline of iron
			ENTVERTEX vertexOutline[136];
			ZeroMemory(vertexOutline, sizeof(ENTVERTEX)*136);
			//double CalculatedOffset[11];
			//double TransectOffset[11]={-0.2,0,0.5,0.4,0.3,0.2,0.1,0.1,0.2,0.1,0.05};
			char acTempData[11];
			memset(acTempData,0,sizeof(acTempData));
			if (analyseMode==After_SinglePrecision||analyseMode==Before_SinglePrecision||analyseMode==After_Transfinite ||analyseMode==Before_Transfinite )						
			{
				for (int i=0;i!=StandardPointNum;++i)
				{
					vertexOutline[i].Point.x=pStandardDataX[i];
					//vertexOutline[i].Point.y=originY-pStandardDataY[i];
					vertexOutline[i].Point.y=pStandardDataY[i];
				}
				result &= drawing.PolyLine(vertexOutline, StandardPointNum);
			}
			else
			{
				for (int i=0;i!=localFilePointNum;++i)
				{
					vertexOutline[i].Point.x=localFileX[i];
					vertexOutline[i].Point.y=localFileY[i];
				}
				result &= drawing.PolyLine(vertexOutline, localFilePointNum);
			}
			result &= drawing.SetColor(COLOR_WHITE);
			//�ҹ첿��
			//  DIMSTYLE table type ----------------------
			originY=-80;
			result &=drawing.Line(-40-originX,originY+5,-40-originX,originY-40);
			//top axis
			result &=drawing.Line(-40-originX,originY+5,-40-originX+80,originY+5);
			//right axis
			result &=drawing.Line(-40-originX+80,originY+5,-40-originX+80,originY-40);
			//bottom axis
			result &=drawing.Line(-40-originX+80,originY-40,-40-originX,originY-40);
			//y�������
			offset=5;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("5.00",-40-originX-12,originY+offset-1,3);

			offset=0;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("0.00",-40-originX-12,originY+offset-1,3);

			offset=-5;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-5.00",-40-originX-18,originY+offset-1,3);

			offset=-10;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-10.00",-40-originX-18,originY+offset-1,3);

			offset=-15;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-15.00",-40-originX-18,originY+offset-1,3);

			offset=-20;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-20.00",-40-originX-18,originY+offset-1,3);

			offset=-25;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-25.00",-40-originX-18,originY+offset-1,3);

			offset=-30;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-30.00",-40-originX-18,originY+offset-1,3);

			offset=-35;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-35.00",-40-originX-18,originY+offset-1,3);

			offset=-40;
			result &=drawing.Line(-40-originX,originY+offset,-40-originX-3,originY+offset);
			result &=drawing.Text("-40.00",-40-originX-18,originY+offset-1,3);

			//x�������
			offset=0;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("-40",-40-originX+offset-3,originY-40-7,3);

			offset=10;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("-30",-40-originX+offset-3,originY-40-7,3);

			offset=20;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("-20",-40-originX+offset-3,originY-40-7,3);

			offset=30;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("-10",-40-originX+offset-3,originY-40-7,3);

			offset=40;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("0",-40-originX+offset-1,originY-40-7,3);

			offset=50;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("10",-40-originX+offset-1,originY-40-7,3);

			offset=60;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("20",-40-originX+offset-1,originY-40-7,3);

			offset=70;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("30",-40-originX+offset-1,originY-40-7,3);

			offset=80;
			result &=drawing.Line(-40-originX+offset,originY-40,-40-originX+offset,originY-40-3);
			result &=drawing.Text("40",-40-originX+offset-1,originY-40-7,3);

			// set current layer to Layer4
			result &= drawing.SetLayer("Layer4");
			result &= drawing.SetColor(COLOR_BLUE);

			//ʵ������
			ZeroMemory(vertexRealOutline, sizeof(ENTVERTEX)*1280);
			for (int i=0;i!=RightLastlocalFilePointNum;++i)
			{
				vertexRealOutline[i].Point.x=LastlocalFileRightX[i]-originX;
				LastlocalFileRightY[i]=LastlocalFileRightY[i]+originY;
				vertexRealOutline[i].Point.y=LastlocalFileRightY[i];
			}
			if (!((analyseMode==After_Transfinite ||analyseMode==Before_Transfinite)&& !rightOverValueFlag))
			{
				result &= drawing.PolyLine(vertexRealOutline, RightLastlocalFilePointNum);
			}

			//11����澫�ȱ�ǵ�
			//11����澫�ȱ�ǵ�
			result &= drawing.SetColor(COLOR_GREEN);
			for (int i=0;i<precisionPointNum;++i)
			{
				startiLeftOutlineAnaPointY[i]+=originY;
				endiLeftOutlineAnaPointY[i]+=originY;
			}

			for (int i=0;i<precisionPointNum;++i)
			{
				result &=drawing.Line(-startiLeftOutlineAnaPointX[i],startiLeftOutlineAnaPointY[i],-endiLeftOutlineAnaPointX[i],endiLeftOutlineAnaPointY[i]);
				result &=drawing.Text(pNameTmp[i],-startiLeftOutlineAnaPointX[i],startiLeftOutlineAnaPointY[i],1);
			}
			/*result &=drawing.Line(-startiLeftOutlineAnaPointX[5],startiLeftOutlineAnaPointY[5],-endiLeftOutlineAnaPointX[5],endiLeftOutlineAnaPointY[5]);
			result &=drawing.Text(pNameTmp[5],-startiLeftOutlineAnaPointX[5]-1,startiLeftOutlineAnaPointY[5]+2,3);
			for (int i=6;i<8;++i)
			{
				result &=drawing.Line(-startiLeftOutlineAnaPointX[i],startiLeftOutlineAnaPointY[i],-endiLeftOutlineAnaPointX[i],endiLeftOutlineAnaPointY[i]);
				result &=drawing.Text(pNameTmp[i],-startiLeftOutlineAnaPointX[i]-3,startiLeftOutlineAnaPointY[i]+2,3);
			}*/
			/*result &=drawing.Line(-iLeftOutlineAnaPointX[0],iLeftOutlineAnaPointY[0],-iLeftOutlineAnaPointX[0],iLeftOutlineAnaPointY[0]+1);
			result &=drawing.Text("-10��",-iLeftOutlineAnaPointX[0],iLeftOutlineAnaPointY[0]+2,3);
			result &=drawing.Line(iLeftOutlineAnaPointX[1],iLeftOutlineAnaPointY[1],-iLeftOutlineAnaPointX[1],iLeftOutlineAnaPointY[1]+1);
			result &=drawing.Text("-2��",-iLeftOutlineAnaPointX[1],iLeftOutlineAnaPointY[1]+2,3);
			result &=drawing.Line(-iLeftOutlineAnaPointX[2],iLeftOutlineAnaPointY[2],-iLeftOutlineAnaPointX[2],iLeftOutlineAnaPointY[2]+1);
			result &=drawing.Text("0��",-iLeftOutlineAnaPointX[2]-1,iLeftOutlineAnaPointY[2]+2,3);
			result &=drawing.Line(-iLeftOutlineAnaPointX[3],iLeftOutlineAnaPointY[3],-iLeftOutlineAnaPointX[3],iLeftOutlineAnaPointY[3]+1);
			result &=drawing.Text("2��",-iLeftOutlineAnaPointX[3],iLeftOutlineAnaPointY[3]+2,3);
			result &=drawing.Line(-iLeftOutlineAnaPointX[4],iLeftOutlineAnaPointY[4]-1,-iLeftOutlineAnaPointX[4],iLeftOutlineAnaPointY[4]);
			result &=drawing.Text("13��",-iLeftOutlineAnaPointX[4],iLeftOutlineAnaPointY[4]-5,3);
			result &=drawing.Line(-iLeftOutlineAnaPointX[5],iLeftOutlineAnaPointY[5],-iLeftOutlineAnaPointX[5],iLeftOutlineAnaPointY[5]+1);
			result &=drawing.Text("36��",-iLeftOutlineAnaPointX[5],iLeftOutlineAnaPointY[5]+2,3);
			result &=drawing.Line(-iLeftOutlineAnaPointX[6],iLeftOutlineAnaPointY[6]-1,-iLeftOutlineAnaPointX[6],iLeftOutlineAnaPointY[6]);
			result &=drawing.Text("50��",-iLeftOutlineAnaPointX[6],iLeftOutlineAnaPointY[6]+5,3);
			result &=drawing.Line(-iLeftOutlineAnaPointX[7],iLeftOutlineAnaPointY[7],-iLeftOutlineAnaPointX[7],iLeftOutlineAnaPointY[7]+1);
			result &=drawing.Text("87��",-iLeftOutlineAnaPointX[7],iLeftOutlineAnaPointY[7]+2,3);*/
			result &= drawing.SetColor(COLOR_WHITE);
			if (!((analyseMode==After_Transfinite ||analyseMode==Before_Transfinite)&& !rightOverValueFlag))
			{
				for (int i=0;i<precisionPointNum/3;++i)
				{
					sprintf(ptemp[i],"%06.4f",f60RightOutlineError[i]);
					result &=drawing.Text(ptemp[i],-30+i*8,-15+originY,1);
					sprintf(ptempPos[i],"%d",i);
					result &=drawing.Text(pNameTmp[i],-30+i*8,-15+3+originY,1);
				}
				for (int i=precisionPointNum/3,j=0;i<precisionPointNum*2/3;++i,++j)
				{
					sprintf(ptemp[i],"%06.4f",f60RightOutlineError[i]);
					result &=drawing.Text(ptemp[i],-30+j*8,-25+originY,1);
					sprintf(ptempPos[i],"%d",i);
					result &=drawing.Text(pNameTmp[i],-30+j*8,-25+3+originY,1);
				}

				for (int i=precisionPointNum*2/3,j=0;i<precisionPointNum;++i,++j)
				{
					sprintf(ptemp[i],"%06.4f",f60RightOutlineError[i]);
					result &=drawing.Text(ptemp[i],-30+j*8,-35+originY,1);
					sprintf(ptempPos[i],"%d",i);
					result &=drawing.Text(pNameTmp[i],-30+j*8,-35+3+originY,1);
				}
			}
		result &= drawing.SetColor(COLOR_RED);
			//draw outline of iron
			ZeroMemory(vertexOutline, sizeof(ENTVERTEX)*136);

			if (analyseMode==After_SinglePrecision||analyseMode==Before_SinglePrecision||analyseMode==After_Transfinite ||analyseMode==Before_Transfinite)						
			{
				for (int i=0;i!=StandardPointNum;++i)
				{
					vertexOutline[i].Point.x=pRightStandDataX[i]-originX;
					vertexOutline[i].Point.y=pStandardDataY[i]+originY;
				}
				result &= drawing.PolyLine(vertexOutline, StandardPointNum);
			}
			else
			{
				for (int i=0;i!=RightlocalFilePointNum;++i)
				{
					vertexOutline[i].Point.x=localFileRightX[i]-originX;
					vertexOutline[i].Point.y=originY+localFileRightY[i];
				}
				result &= drawing.PolyLine(vertexOutline, RightlocalFilePointNum);
			}
			// Save data to dxf file
			if(!drawing.SaveDXFFile(DxfFileName))
			{
				result = FALSE;
				MessageBox("����CAD(.dxf)�ļ�ʧ�ܣ�", "DXF���ɱ���", MB_ICONERROR | MB_OK);
			}
			else
				MessageBox("�ɹ�����CAD(.dxf)�ļ�", "DXF���ɱ���", MB_ICONINFORMATION | MB_OK);
			drawing.Destroy();
		}
	}
		
		int iSel=m_Combo_ModelSel.GetCurSel();
		if (IsAfterMillFlag)
		{
			if(iSel==1 || iSel==3)
				bTongJi=true;
			else if(iSel==4)
				bChaoXian=true;
		}
		else
		{
			if (iSel==1)
			{
				bTongJi=true;
			}
			else if (iSel==2)
			{
				bChaoXian=true;
			}
		}
		CStdioFile openfile;
		//CString strFilePath="D:\\CreatExcle\\test.xlsx";
		BOOL IsOutPutOK = FALSE;
		CString Handline = "";
		//Handline.Format("�ֹ����澫��ֵ");
		int pointNum;//��ͬ�����в�ͬ�����������50������19���㣬60������23���㣬75������15����
		//int raid50[19]={-10,-4,-3,-2,-1,0,1,2,3,4,10,20,30,40,50,60,70,80,90};
		//int raid60[23]={-13,-10,-8,-6,-4,-2,-1,0,1,2,4,6,8,10,13,20,30,40,50,60,70,80,87};
		int raid60[23]={13,10,8,6,4,2,1,0,-1,-2,-4,-6,-8,-10,-13,-20,-30,-40,-50,-60,-70,-80,-87};		
		int raid50[19]={10,4,3,2,1,0,-1,-2,-3,-4,-10,-20,-30,-40,-50,-60,-70,-80,-90};
		//int raid75[15]={-11,-6,-1,0,1,6,11,20,30,40,50,60,70,80,87};
		int raid75[15]={11,6,1,0,-1,-6,-11,-20,-30,-40,-50,-60,-70,-80,-87};
		char phase[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
		CApplication app;
		CWorkbooks books;
		CWorkbook  book;
		CWorksheets sheets;
		CWorksheet sheetData, sheetChart;
		CRange range;
		CRange unionRange;
		CFont0 font;
		CInterior Interior;
		//covTrue��ǰ���������ĺ�����ʲô��
		COleVariant covTrue((short)TRUE), covFalse((short)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		CString rowrange;
		int icount = 0;///���ݴӵ����п�ʼ
		double mileage=0;//��̱���
		if (!app.CreateDispatch(_T("Excel.Application")))
		{
			TRACE(_T("�޷�����Excel������"));
			//return FALSE;
		}
		books.AttachDispatch(app.get_Workbooks(),true);//����Ϊtrue��ʾ�Զ��ͷ�excel����
		book = books.Add(covOptional);//�½�һ��book
		sheets = book.get_Worksheets();// �õ�Worksheets

		//---------�ڵ�һ���������ɵĵ���excel���
		//��д���һ�к͵ڶ�������
		//---------�ڵڶ����������ɵĳ���excel���
		//---------
		//���ɱ���excle�����·������
		static char szFilter[] = "Excel file format(*.xlsx) |*.xlsx|All Files (*.*)|*.*||";
		CFileDialog SaveDlg( false, NULL, NULL/*LastFilePath*/, OFN_HIDEREADONLY | OFN_EXPLORER, szFilter, NULL,0,FALSE);
		SaveDlg.m_ofn.lpstrTitle = "Save Excel File As";
		if (bChaoXian|| bTongJi)
		{
			if(SaveDlg.DoModal()==IDOK)
		{	// Saving sample dxf file data
		if(bChaoXian)
	{
		bChaoXian=false;
		//CString strFilePath;
		CString SheetName;
		CString strLinetemp;
		vector<double>  OverValueTmpVec;
		vector<double*> vecTmp;
		for(int i=0;i<2;i++)
		{
			if(i==0)
			{
				SheetName="����-��";
				OverValueTmpVec=OverValueHdmVec;
				vecTmp=localFileHdmVec;
			}
			else
			{
				SheetName="����-��";
				OverValueTmpVec=RightOverValueHdmVec;
				vecTmp=RightlocalFileHdmVec;
			}

			sheetData.AttachDispatch(sheets.get_Item(COleVariant((short)(i+1))));//��õ�2��������
			sheetData.put_Name(SheetName);//��������Ҫ���ģ�
			rowrange.Format("A1");//��д���һ�к͵ڶ�������
			range  = sheetData.get_Range(COleVariant(rowrange), covOptional);  // ��ȡrowrange�涨������
			range.put_Value2(COleVariant("���ʱ��"));							//д�����
			rowrange.Format("A2");
			range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
			range.put_Value2(COleVariant(CsDetectTime));
			/*rowrange.Format("B1");
			range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
			range.put_Value2(COleVariant("��վ����"));
			rowrange.Format("B2");
			range  = sheetData.get_Range(COleVariant(rowrange), covOptional); */
			//range.put_Value2(COleVariant(CsDetectInterval));
			rowrange.Format("B1");
			range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
			range.put_Value2(COleVariant("�������"));
			rowrange.Format("B2");
			range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
			range.put_Value2(COleVariant(CsDetectDetail));
			rowrange.Format("C1");
			range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
			range.put_Value2(COleVariant("����"));
			rowrange.Format("C2");
			range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
			range.put_Value2(COleVariant(CsDetectGuiXing));
			rowrange.Format("D1");
			range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
			range.put_Value2(COleVariant("ƫ���޶�ֵ"));
			rowrange.Format("D2");
			range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
			rowrange.Format("%4.2f,%4.2f",dPositiveLimit,dNegetiveLimit);
			range.put_Value2(COleVariant(rowrange));
			//д��3��
			CString CsTailZone;
			int *res=NULL;
			if(CsDetectGuiXing=="50Kg/m")//50��
			{	
				CsTailZone.Format("S3");
				pointNum=19;
				res=raid50;
			}
			else if(CsDetectGuiXing=="60Kg/m")//60��
			{
				CsTailZone.Format("W3");
				pointNum=23;
				res=raid60;
			}
			else if(CsDetectGuiXing=="75Kg/m")//75��
			{
				CsTailZone.Format("O3");
				pointNum=15;
				res=raid75;
			}
			unionRange.AttachDispatch(sheetData.get_Range(_variant_t("A3"),_variant_t(CsTailZone)),TRUE);
			unionRange.Merge(COleVariant((long)0));
			Handline.Format("�����");
			unionRange.put_Value2(COleVariant(Handline));
			unionRange.put_HorizontalAlignment(COleVariant((short)3));//���õ�Ԫ��ˮƽ����
			//д��4��
			rowrange.Format("A4");
			range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
			range.put_Value2(COleVariant("�������"));
			CString Cstmp;
			for(int j=0;j<pointNum;j++)//д���4�нǶ�����
			{
				rowrange.Format("%c%d",phase[j+1],4);
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				Cstmp.Format("%d��",res[j]);
				range.put_Value2(COleVariant(Cstmp));
			}
			//д���5��
			icount=5;
			//��������ȡ���ݣ���ȡ����������أ���ô��ƣ�
			//�����㣬��Ҫ˼���Ȼ���˳��޵���̣���ô������������������ľ���Ϳ���ֱ�Ӷ�λ���ó����н��ж�ȡ����
			double dDisFromStartToPoint=0;//��ǰ������̾���������ľ��룬����ֱ�Ӷ�λ����Ӧ���н��ж�ȡ����
			int iOffset=0;
			double* dtmpPtr=NULL;
			for(unsigned int j=0;j<OverValueTmpVec.size();j++)
			{
				dDisFromStartToPoint=OverValueTmpVec[j]-m_startAndEndVec[0][0];
				iOffset=(int)(dDisFromStartToPoint*10);

				rowrange.Format("%c%d",phase[0],icount);//ÿһ�еĵ�һ��λ�ô������
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); //����̺;���ֵ������������һ��
				
				CString strCurDist;
				UpdateData(TRUE);
				int iK=(int)OverValueTmpVec[j]/1000;
				double iD=OverValueTmpVec[j]-1000*iK;
				string tmpDetectRoad=CsDetectRoad;
				tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
				strCurDist.Format("%s%d+%0.1f",tmpDetectRoad.c_str(),iK,iD);
				range.put_Value2(COleVariant(strCurDist));

				//dtmpPtr=vecTmp[iOffset];
				for(int k=0;k<pointNum;k++)
				{
					rowrange.Format("%c%d",phase[k+1],icount);
					range  = sheetData.get_Range(COleVariant(rowrange), covOptional); //����̺;���ֵ������������һ��
					range.put_Value2(COleVariant(vecTmp[k][iOffset]));
				}
				++icount;
			}
		}

	}
        if(bTongJi)
		{
			bTongJi=false;
			int iStart=0;//�õ���vector������Ǹ�double���鿪ʼд�뵽excel
			int iNum=0;//д����ٸ�������excel��
			iSel=m_Combo_TotalDistance.GetCurSel();
			double dStartPoint=0;
			if(iSel==0)//10
			{
				iNum=10*perMi;
				double dtmp=abs(m_Edit_DistanceReal-m_startAndEndVec[0][0]);
				iStart=(int)(dtmp/0.1);
				dStartPoint=m_Edit_DistanceReal;
			}
			else if(iSel==1)//50
			{
				iNum=50*perMi;
				double dtmp=abs(m_Edit_DistanceReal-m_startAndEndVec[0][0]);
				iStart=(int)(dtmp/0.1);
				dStartPoint=m_Edit_DistanceReal;
			}
			else if(iSel==2)//100
			{
				iNum=100*perMi;
				double dtmp=abs(m_Edit_DistanceReal-m_startAndEndVec[0][0]);
				iStart=(int)(dtmp/0.1);
				dStartPoint=m_Edit_DistanceReal;
			}
			else if(iSel==3)//ȫ��
			{
				//iNum=localFileHdmVec.size();
				iNum = (int)m_PrecisionNumCnt;
				iStart=0;
				dStartPoint=m_startAndEndVec[0][0];
			}
			double *dtmpPtr=NULL;
			CString SheetName;
			vector<double*> vecTmp;
			double* dTmpMaxPtr=NULL;//���ȵ����ֵ����
			double* dTmpAvePtr=NULL;//���ȵ�ƽ��ֵ����
			for(int i=0;i<2;i++)
			{
				if(i==0)
				{
					SheetName="ͳ��-��";
					vecTmp = localFileHdmVec;
					dTmpMaxPtr=pPrecisionMax;
					dTmpAvePtr=pPrecisionAverage;
					dAcceptRate01.Format("%.2f",m_fixedValueRatio);
				}
				else
				{
					SheetName="ͳ��-��";
					vecTmp = RightlocalFileHdmVec;
					dTmpMaxPtr=pRightPrecisionMax;
					dTmpAvePtr=pRightPrecisionAverage;
					dAcceptRate01.Format("%.2f",m_RightfixedValueRatio);
				}
				sheetData.AttachDispatch(sheets.get_Item(COleVariant((short)(i+1))));
				sheetData.put_Name(SheetName);

				rowrange.Format("A1");//��д���һ�к͵ڶ�������
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional);  // ��ȡrowrange�涨������
				range.put_Value2(COleVariant("���ʱ��"));							//д�����
				rowrange.Format("A2");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant(CsDetectTime));

				/*rowrange.Format("B1");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant("��վ����"));
				rowrange.Format("B2");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); */
				//range.put_Value2(COleVariant(CsDetectInterval));

				rowrange.Format("B1");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant("ͳ������"));
				/*rowrange.Format("B2");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant(CsTongjiInterval));*/

				rowrange.Format("C1");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant("�������"));
				rowrange.Format("C2");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant(CsDetectDetail));

				rowrange.Format("D1");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant("����"));
				rowrange.Format("D2");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant(CsDetectGuiXing));


				rowrange.Format("E1");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant("�����"));
				rowrange.Format("E2");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant(dAcceptRate01));

				rowrange.Format("F1");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant("ƫ���޶�ֵ"));
				rowrange.Format("F2");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				rowrange.Format("%4.2f,%4.2f",dPositiveLimit,dNegetiveLimit);
				range.put_Value2(COleVariant(rowrange));

				//д��3��
				CString CsTailZone;
				CString CsTailZone2;
				int *res=NULL;

				if(CsDetectGuiXing=="50Kg/m")//50��
				{	
					CsTailZone.Format("S3");
					CsTailZone2.Format("S7");
					pointNum=19;
					res=raid50;
				}
				else if(CsDetectGuiXing=="60Kg/m")//60��
				{
					CsTailZone.Format("W3");
					CsTailZone2.Format("W7");
					pointNum=23;
					res=raid60;
				}
				else if(CsDetectGuiXing=="75Kg/m")//75��
				{
					CsTailZone.Format("O3");
					CsTailZone2.Format("O7");
					pointNum=15;
					res=raid75;
				}
				unionRange.AttachDispatch(sheetData.get_Range(_variant_t("A3"),_variant_t(CsTailZone)),TRUE);
				unionRange.Merge(COleVariant((long)0));
				Handline.Format("ͳ�ƽ����ƽ��ֵ��");
				unionRange.put_Value2(COleVariant(Handline));
				unionRange.put_HorizontalAlignment(COleVariant((short)3));//���õ�Ԫ��ˮƽ����
				//д��4��
				rowrange.Format("A4");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant("ͳ��"));
				CString Cstmp;
				icount=4;
				for(int j=0;j<pointNum;j++)//д���4�нǶ�����
				{
					rowrange.Format("%c%d",phase[j+1],icount);
					range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
					Cstmp.Format("%d��",res[j]);
					range.put_Value2(COleVariant(Cstmp));
				}
				//д��5��
				rowrange.Format("A5");
				icount++;//icount=5
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant("���ֵ"));
				for(int j=0;j<pointNum;j++)
				{
					rowrange.Format("%c%d",phase[j+1],icount);
					range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
					Cstmp.Format("%f",dTmpMaxPtr[j]);
					range.put_Value2(COleVariant(Cstmp));
				}
				//д��6��
				rowrange.Format("A6");
				icount++;
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant("ƽ��ֵ"));
				for(int j=0;j<pointNum;j++)
				{
					rowrange.Format("%c%d",phase[j+1],icount);
					range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
					Cstmp.Format("%f",dTmpAvePtr[j]);
					range.put_Value2(COleVariant(Cstmp));
				}
				//д��7��
				icount++;
				rowrange.Format("A%d",icount);
				unionRange.AttachDispatch(sheetData.get_Range(_variant_t(rowrange),_variant_t(CsTailZone2)),TRUE);
				unionRange.Merge(COleVariant((long)0));
				Handline.Format("�����");
				unionRange.put_Value2(COleVariant(Handline));
				unionRange.put_HorizontalAlignment(COleVariant((short)3));//���õ�Ԫ��ˮƽ����
				//д��8��
				icount++;
				rowrange.Format("A%d",icount);
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				range.put_Value2(COleVariant("�����"));
				for(int j=0;j<pointNum;j++)//д���8�нǶ�����
				{
					rowrange.Format("%c%d",phase[j+1],icount);
					range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
					Cstmp.Format("%d��",res[j]);
					range.put_Value2(COleVariant(Cstmp));
				}
				//����ÿһ�����Ǵӵ�9�п�ʼд��
				icount++;
				//////////////////////////////////////////////////////////////////////////
				CString tmpCsTongjiInterval_begin;
				CString tmpCsTongjiInterval_end;

				for(int j=iStart;j<iStart+iNum;j++)
				{
					rowrange.Format("%c%d",phase[0],icount);//ÿһ�еĵ�һ��λ�ô������
					range  = sheetData.get_Range(COleVariant(rowrange), covOptional); //����̺;���ֵ������������һ��

					CString strCurDist;
					UpdateData(TRUE);
					double tmpDistance;
					if (CsDirection==_T("��"))
					{
						tmpDistance=dStartPoint-0.1*(j-iStart);
					}
					else
					{
						tmpDistance=dStartPoint+0.1*(j-iStart);
					}
					
					int iK=(int)tmpDistance/1000;
					double iD=tmpDistance-1000*iK;
					string tmpDetectRoad=CsDetectRoad;
					tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
					strCurDist.Format("%s%d+%0.1f",tmpDetectRoad.c_str(),iK,iD);
					range.put_Value2(COleVariant(strCurDist));

					if (j==iStart)
					{
						tmpCsTongjiInterval_begin = strCurDist;
					}
					if (j==iStart+iNum-1)
					{
						tmpCsTongjiInterval_end = strCurDist;
					}

					//dtmpPtr=vecTmp[i];
					for(int k=0;k<pointNum;k++)
					{
						rowrange.Format("%c%d",phase[k+1],icount);
						range  = sheetData.get_Range(COleVariant(rowrange), covOptional); //����̺;���ֵ������������һ��
						range.put_Value2(COleVariant(vecTmp[k][j]));
					}
					++icount;
				}
				//////////////////////////////////////////////////////////////////////////
				rowrange.Format("B2");
				range  = sheetData.get_Range(COleVariant(rowrange), covOptional); 
				CString tmpCsTongjiInterval;
				tmpCsTongjiInterval.Format("%s-%s",tmpCsTongjiInterval_begin,tmpCsTongjiInterval_end);
				range.put_Value2(COleVariant(tmpCsTongjiInterval));
			}

	}
			
			CString ExcelFileName( SaveDlg.GetPathName() );
			//		CDrawing drw;

			if(SaveDlg.GetFileExt().IsEmpty())
				ExcelFileName += ".xlsx";
			book.SaveAs(COleVariant(ExcelFileName),covOptional,covOptional,covOptional,covOptional,covOptional,(long)0,covOptional,covOptional,covOptional,covOptional,covOptional);
			
			MessageBox(_T("����Excel�ɹ�"),_T("Excel���ɱ���"));
		}
		books.ReleaseDispatch();
		book.ReleaseDispatch();
		sheets.ReleaseDispatch();
		sheetData.ReleaseDispatch();
		range.ReleaseDispatch();
		unionRange.ReleaseDispatch();
		app.Quit();
		IsOutPutOK = TRUE;
		}
	}
	else
		MessageBox(_T("���ȵ����ļ�!"),_T("�ֹ�����������"));
		

	//return IsOutPutOK;
}
// //��ȡ����
int CHighPrecisionDlg:: ReadOutline(double currentDistance,double *outlineX,double *outlineY,int &outlinePointNum,ULONGLONG &fileOffset,CString filePath)
{
	CStdioFile fMeasureFile;
	bool bFinishFlag=false;

	//��������
	if(currentDistance>=0 &&fMeasureFile.Open(filePath, CFile::modeRead))
	{
		int iNeedCount=0;
		CString strLinetemp;
		bFinishFlag=false;
		/*if (fileOffset>20000)
		{
		fileOffset-=20000;
		fMeasureFile.Seek(fileOffset,CFile::begin);
		fMeasureFile.ReadString(strLinetemp);
		}*/
		if (fileOffset>4000)
		{
			fMeasureFile.Seek(fileOffset,CFile::begin);
			fMeasureFile.ReadString(strLinetemp);
		}
		else
		{
			fMeasureFile.Seek(0,CFile::begin);
		}
		while(fMeasureFile.ReadString(strLinetemp))
		{					
			char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
			char *strtemp = NULL;  
			strtemp = strtok(str, " ");  
			char *TopData = strtemp; 
			double tmpOffset=fabs(atof(TopData)-currentDistance);
			//ɸѡ�������Ķ���̵�����
			if (tmpOffset<1e-6)
			{
				bFinishFlag=true;
				if (strtemp != NULL)  
				{  
					strtemp = strtok(NULL, " ");  
				}  
				char *XData = strtemp; 
				if (XData!=NULL)
				{
					outlineX[iNeedCount]=atof(XData);
				}
				if (strtemp != NULL)  
				{  
					strtemp = strtok(NULL, " ");  
				}
				char *YData = strtemp; 
				if (YData!=NULL)
				{
					outlineY[iNeedCount]=atof(YData);
				}
				outlineY[iNeedCount]=-outlineY[iNeedCount];
				iNeedCount++;
			}
			else
			{
				if (bFinishFlag)
				{
					bFinishFlag=false;
					break;
				}
			}
		}
		fileOffset=fMeasureFile.GetPosition();
		fMeasureFile.Close();
		outlinePointNum=iNeedCount;
	}

	return 0;
}

// ��ȡ���澫�Ȼ���ϳĥ��
int CHighPrecisionDlg:: ReadPrecisionOrMill(double currentDistance,double* outLineError,int outLineErrorPointNum,ULONGLONG &fileOffset,CString filePath)
{
	CStdioFile fMeasureFile;
	bool bFinishFlag=false;
	//��ȡ���澫��
	if(currentDistance>=0 && fMeasureFile.Open(filePath, CFile::modeRead))
	{
		CString strLinetemp;
		/*if (fileOffset>200)
		{
			fileOffset-=200;
			fMeasureFile.Seek(fileOffset,CFile::begin);
			fMeasureFile.ReadString(strLinetemp);
		}*/
		if (fileOffset>4000)
		{
			fMeasureFile.Seek(fileOffset,CFile::begin);
			fMeasureFile.ReadString(strLinetemp);
		}
		else
		{
			fMeasureFile.Seek(0,CFile::begin);
		}
		while(fMeasureFile.ReadString(strLinetemp))
		{					
			char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
			char *strtemp = NULL;  
			strtemp = strtok(str, " ");  
			char *TopData = strtemp; 
			double tmpOffset=fabs(atof(TopData)-currentDistance);
			//ɸѡ�������Ķ���̵�����
			if (tmpOffset<1e-6)
			{
				bFinishFlag=true;
				if (m_OutlineType==1)  //60��
				{
					if(strtemp !=NULL)
					{
						strtemp = strtok(NULL, " ");  
					}
					char *PrecisionOrMill=strtemp;
					outLineError[0]=atof(PrecisionOrMill);
					for (int i=1;i<outLineErrorPointNum;++i)
					{
						fMeasureFile.ReadString(strLinetemp);
						str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
						strtemp = NULL; 
						strtemp = strtok(str, " ");  
						TopData = strtemp; 
						if(strtemp !=NULL)
						{
							strtemp = strtok(NULL, " ");  
						}
						PrecisionOrMill=strtemp;
						outLineError[i]=atof(PrecisionOrMill);
					}
				}
			}
			else
			{
				if (bFinishFlag)
				{
					bFinishFlag=false;
					break;
				}
			}

		}
		fileOffset=fMeasureFile.GetPosition();
		fMeasureFile.Close();
	}
	return 0;
}

LRESULT CHighPrecisionDlg::On2DDispDistance(WPARAM wParam,LPARAM lParam)
{
	double CurDist=0;//��¼��ǰ���=��ʼ���+����ʻ����
	CString strCurDist;
	CurDist=g_TestInfo_L.DistanceStart+iDisdanceCount*abs(Encoder_Distance);
	int iK=(int)CurDist/1000;
	double iD=CurDist-1000*iK;
	strCurDist.Format("%s%d + %0.1f",g_TestInfo_L.Xianbie,iK,iD);
	SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);		
	return 0;
}

LRESULT CHighPrecisionDlg::On2DDispListCtrl_L(WPARAM wParam,LPARAM lParam)
{	
	int nStNumNode;
	switch(g_TestInfo_L.TrackSel)
	{
	case 0://50��
		{
			nStNumNode=19;
			break;
		}

	case 1://60��
		{
			nStNumNode=23;
			break;
		}
	}
	if (wParam==0)//ϳĥǰ
	{
		double* pHdmJd=NULL;	
		pHdmJd=new double[nStNumNode];

		switch(g_TestInfo_L.TrackSel)
		{
		case 0:
			{
				for (int j=0;j<nStNumNode;j++)
				{
					pHdmJd[j]=m_2DThreadParam_L.DistHdm_50[j];
				}	
				break;
			}
		case 1:
			{
				for (int j=0;j<nStNumNode;j++)
				{
					pHdmJd[j]=m_2DThreadParam_L.DistHdm[j];

				}	
				break;
			}
		}
		CString* strDisp=NULL;
		strDisp=new CString[nStNumNode];
		//CString strDisp[nStNumNode];
		
		for (int i=0;i<nStNumNode;i++)
		{
			strDisp[i].Format("%6.4f",pHdmJd[i]);
			m_List_ResultInfo.SetItemText(i,1,strDisp[i]);
		}
		if (pHdmJd)
		{
			delete[] pHdmJd;
			pHdmJd=NULL;
		}
		if (strDisp)
		{
			delete[] strDisp;
			strDisp=NULL;
		}
	} 
	else if(wParam==1)//ϳĥ��
	{
		double* pXmlJd=NULL;		
		double* pHdmJd=NULL;
		pXmlJd=new double[nStNumNode];
		pHdmJd=new double[nStNumNode];

		switch(g_TestInfo_L.TrackSel)
		{
		case 0:
			{
				for (int j=0;j<nStNumNode;j++)
				{
					pXmlJd[j]=m_2DThreadParam_L.DistXml_50[j];
					pHdmJd[j]=m_2DThreadParam_L.DistHdm_50[j];

				}
				break;
			}
		case 1:
			{
				for (int j=0;j<nStNumNode;j++)
				{
					pXmlJd[j]=m_2DThreadParam_L.DistXml[j];
					pHdmJd[j]=m_2DThreadParam_L.DistHdm[j];

				}
				break;
			}
		}
		CString* strDispXml=NULL;		
		CString* strDispHdm=NULL;
		strDispXml=new CString[nStNumNode];
		strDispHdm=new CString[nStNumNode];
		//CString strDispXml[nStNumNode],strDispHdm[nStNumNode];
		for (int i=0;i<nStNumNode;i++)
		{
			strDispXml[i].Format("%6.4f",pXmlJd[i]);
			strDispHdm[i].Format("%6.4f",pHdmJd[i]);
			m_List_ResultInfo.SetItemText(i,3,strDispHdm[i]);//�������ڵ�1�б�������ʾ
			m_List_ResultInfo.SetItemText(i,1,strDispXml[i]);//��ϳĥ���ڵ�3�б�������ʾ
		}

		if (pXmlJd)
		{
			delete[] pXmlJd;
			pXmlJd=NULL;
		}

		if (pHdmJd)
		{
			delete[] pHdmJd;
			pHdmJd=NULL;
		}
		if (strDispXml)
		{
			delete[] strDispXml;
			strDispXml=NULL;
		}
		if (strDispHdm)
		{
			delete[] strDispHdm;
			strDispHdm=NULL;
		}
	}
	return 0;
}

LRESULT CHighPrecisionDlg::On2DDispListCtrl_R(WPARAM wParam,LPARAM lParam)
{
	int nStNumNode;
	switch(g_TestInfo_R.TrackSel)
	{
	case 0://50��
		{
			nStNumNode=19;
			break;
		}

	case 1://60��
		{
			nStNumNode=23;
			break;
		}
	}	
	if (wParam==0)//ϳĥǰ
	{
		double* pHdmJd=NULL;	
		pHdmJd=new double[nStNumNode];
		switch(g_TestInfo_R.TrackSel)
		{
		case 0:
			{
				for (int j=0;j<nStNumNode;j++)
				{
					pHdmJd[j]=m_2DThreadParam_R.DistHdm_50[j];

				}	
				break;
			}
		case 1:
			{
				for (int j=0;j<nStNumNode;j++)
				{
					pHdmJd[j]=m_2DThreadParam_R.DistHdm[j];

				}	
				break;
			}
		}
		
		CString* strDisp=NULL;
		strDisp=new CString[nStNumNode];
		for (int i=0;i<nStNumNode;i++)
		{
			strDisp[i].Format("%6.4f",pHdmJd[i]);
			m_List_ResultInfo.SetItemText(i,2,strDisp[i]);
		}
		if (pHdmJd)
		{
			delete[] pHdmJd;
			pHdmJd=NULL;
		}
		if (strDisp)
		{
			delete[] strDisp;
			strDisp=NULL;
		}
	}
	else if(wParam==1)//ϳĥ��
	{		
		double* pXmlJd=NULL;		
		double* pHdmJd=NULL;
		pXmlJd=new double[nStNumNode];
		pHdmJd=new double[nStNumNode];
		switch(g_TestInfo_R.TrackSel)
		{
		case 0:
			{
				for (int j=0;j<nStNumNode;j++)
				{
					pXmlJd[j]=m_2DThreadParam_R.DistXml_50[j];
					pHdmJd[j]=m_2DThreadParam_R.DistHdm_50[j];
				}	
				break;
			}
		case 1:
			{
				for (int j=0;j<nStNumNode;j++)
				{
					pXmlJd[j]=m_2DThreadParam_R.DistXml[j];
					pHdmJd[j]=m_2DThreadParam_R.DistHdm[j];

				}	
				break;
			}
		}		

		//CString strDispXml[nStNumNode],strDispHdm[nStNumNode];
		CString* strDispXml=NULL;		
		CString* strDispHdm=NULL;
		strDispXml=new CString[nStNumNode];
		strDispHdm=new CString[nStNumNode];
		for (int i=0;i<nStNumNode;i++)
		{
			strDispXml[i].Format("%6.4f",pXmlJd[i]);
			strDispHdm[i].Format("%6.4f",pHdmJd[i]);
			m_List_ResultInfo.SetItemText(i,4,strDispHdm[i]);//�Һ�����ڵ�1�б�������ʾ
			m_List_ResultInfo.SetItemText(i,2,strDispXml[i]);//��ϳĥ���ڵ�3�б�������ʾ
		}

		if (pXmlJd)
		{
			delete[] pXmlJd;
			pXmlJd=NULL;
		}

		if (pHdmJd)
		{
			delete[] pHdmJd;
			pHdmJd=NULL;
		}
		if (strDispXml)
		{
			delete[] strDispXml;
			strDispXml=NULL;
		}
		if (strDispHdm)
		{
			delete[] strDispHdm;
			strDispHdm=NULL;
		}

	}
		
	return 0;
}

void CHighPrecisionDlg::OnMotorSetPara()
{
	// TODO: �ڴ���������������
 if(g_bFlagMotor_L&&g_bFlagMotor_R)
 {
	MotorPara objMotorPara;
	objMotorPara.DoModal();	
 }
 else
	 OnBnClickedButtonLink();
}
void CHighPrecisionDlg::allSeriesClear()
{
	//���������е�ȫ������
	m_pRightTopStandardLineSerie->ClearSerie();
	m_pRightTopAfterLineSerie->ClearSerie();
	m_pRightTopBeforeLineSerie->ClearSerie();
	m_pRightTopLineSerie->ClearSerie();
	m_pRightTopPointSerie->ClearSerie();
	m_pMaxRightTopLineSerie->ClearSerie();
	m_pMaxRightTopPointSerie->ClearSerie();
	m_pRightBottomPointSerie->ClearSerie();
	m_pRightBottomLineSerie->ClearSerie();

	m_pLeftTopStandardLineSerie->ClearSerie();
	m_pLeftTopAfterLineSerie->ClearSerie();
	m_pLeftTopBeforeLineSerie->ClearSerie();
	m_pLeftTopLineSerie->ClearSerie();
	m_pLeftTopPointSerie->ClearSerie();
	m_pMaxLeftTopLineSerie->ClearSerie();
	m_pMaxLeftTopPointSerie->ClearSerie();
	m_pLeftBottomPointSerie->ClearSerie();
	m_pLeftBottomLineSerie->ClearSerie();


	//����������з�������
	m_sLineSerie_LT->ClearSerie();
	m_pLineSerie_LB->ClearSerie();
	m_pLineSerie_LT->ClearSerie();
	m_PointSerie_LB->ClearSerie();
	m_pLineSerieStd_LT->ClearSerie();

	m_sLineSerie_RT->ClearSerie();
	m_pLineSerie_RB->ClearSerie();
	m_PointSerie_RB->ClearSerie();
	m_pLineSerie_RT->ClearSerie();
	m_pLineSerieStd_RT->ClearSerie();

}
BOOL CHighPrecisionDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CHighPrecisionDlg::OnBnClickedButtonStopmotor()
{	

	if(g_bFlagMotor_L&&g_bFlagMotor_R)
	{
		if (bFlagStopMt)
		{
			if (bFlagStopMt_L)//ִ����ͣ�������
			{
				if (m_MachineCtrl_L./*OnlyMotorPowerOFF*/MotorPause(m_Mscomm_L))
				{
					bFlagStopMt_L=false;
				}				
			}
			if (bFlagStopMt_R)
			{
				if (m_MachineCtrl_R./*OnlyMotorPowerOFF*/MotorPause(m_Mscomm_R))
				{
					bFlagStopMt_R=false;
				}				
			}
			if(!bFlagStopMt_L&&!bFlagStopMt_R)
			{
				SetDlgItemText(IDC_BUTTON_STOPMOTOR,_T("�������"));//��ͣ�����ť��Ϊ�������
				bFlagStopMt=false;//��ť��ʾΪ����
				MessageBox(_T("�ѳɹ���ͣ�����"),_T("�ֹ�����������"),MB_ICONQUESTION|MB_OK);
				
			}
			else
			{
				MessageBox(_T("����ʧ�ܣ������µ����"),_T("�ֹ�����������"),MB_ICONERROR|MB_OK);
			}
		}
		else if(!bFlagStopMt)//�����������
		{
			if (!bFlagStopMt_L)
			{
				if (m_MachineCtrl_L.MotorStart(m_Mscomm_L))
				{
					bFlagStopMt_L=true;
				}
			}
			if (!bFlagStopMt_R)
			{
				if (m_MachineCtrl_R.MotorStart(m_Mscomm_R))
				{
					bFlagStopMt_R=true;
				}
			}
			if (bFlagStopMt_L&&bFlagStopMt_R)
			{
				SetDlgItemText(IDC_BUTTON_STOPMOTOR,_T("�����ͣ"));//��ͣ�����ť��Ϊ�������
				bFlagStopMt=true;//��ť��ʾΪ��ͣ
				moveBefore_L=TRUE; 
				moveBefore_R=TRUE; 
				MessageBox(_T("�ѳɹ����������"),_T("�ֹ�����������"),MB_ICONQUESTION|MB_OK);
				
			}
			else
			{
				MessageBox(_T("����ʧ�ܣ������µ����"),_T("�ֹ�����������"),MB_ICONERROR|MB_OK);
			}

		}
	}
	else
	{
	CConnectDeviceDlg obj_ConnectDevice;
	obj_ConnectDevice.DoModal();
	}
}


void CHighPrecisionDlg::OnEnSetfocusEditDistance()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_havePressAnalyse=FALSE;
}


void CHighPrecisionDlg::OnSetReportParam()
{
	// TODO: �ڴ���������������
	//CReprtParamDlg obj_ReportParaDlg;
	//obj_ReportParaDlg.DoModal();
	OnBnClickedButtonInputfile();

}

void CHighPrecisionDlg::allButtonDisable()
{
	//���ð�ť
	GetDlgItem(IDC_BUTTON_LINK)->EnableWindow(false);//�����豸
	GetDlgItem(IDC_BUTTON_TESTINFO)->EnableWindow(false);//��������Ϣ
	GetDlgItem(IDC_BUTTON_ANALYZEFLAG)->EnableWindow(false);//�ļ�����

	////���ò˵���ť
	//���ģʽ
	m_MainMenu->EnableMenuItem(ID_Menu_Link,MF_DISABLED|MF_GRAYED);//�����豸
	m_MainMenu->EnableMenuItem(ID_Menu_TestInfo,MF_DISABLED|MF_GRAYED);//��������Ϣ
	m_MainMenu->EnableMenuItem(ID_Menu_TestStart,MF_DISABLED|MF_GRAYED);//��ʼ���
	//GetMenu()->EnableMenuItem(ID_Menu_TestStop,MF_DISABLED|MF_GRAYED);//ֹͣ���
	//����ģʽ
	m_MainMenu->EnableMenuItem(ID_Menu_Anaylze,MF_DISABLED|MF_GRAYED);//�ļ�����
	m_MainMenu->EnableMenuItem(ID_Menu_Reprot,MF_DISABLED|MF_GRAYED);//���ɱ���
	m_MainMenu->EnableMenuItem(ID_Menu_InputFile,MF_DISABLED|MF_GRAYED);//�����ļ�
	m_MainMenu->EnableMenuItem(ID_SETREPORTPARAM, MF_DISABLED | MF_GRAYED);//�����ļ�shen
}

void CHighPrecisionDlg::OnCbnSelchangeComboTotaldistance()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_havePressAnalyse=FALSE;
}


//�˵�����ť
void CHighPrecisionDlg::OnClickMenuLink()
{
	// TODO: �ڴ���������������
	if(g_bFlagMotor_L&&g_bFlagMotor_R&&g_bFlagSensorL&&g_bFlagSensorR)
	{
		CConnectDeviceDlg obj_ConnectDialog;
		obj_ConnectDialog.DoModal();
	}		
	else
	OnBnClickedButtonLink();
}


void CHighPrecisionDlg::OnClickMenuTestinfo()
{
	// TODO: �ڴ���������������

	OnBnClickedButtonTestinfo();
}


void CHighPrecisionDlg::OnClickMenuTeststart()
{
	// TODO: �ڴ���������������
	OnBnClickedButtonStart();
}


void CHighPrecisionDlg::OnClickMenuMotorstop()
{
	// TODO: �ڴ���������������
	OnBnClickedButtonStopmotor();
}


void CHighPrecisionDlg::OnClickMenuTeststop()
{
	// TODO: �ڴ���������������
	if(bFlagStartThread)
		OnBnClickedButtonStart();
}





void CHighPrecisionDlg::OnClickMenuInputfile()
{
	// TODO: �ڴ���������������
	OnBnClickedButtonInputfile();
}



void CHighPrecisionDlg::OnClickMenuAnaylze()
{
	// TODO: �ڴ���������������
	OnBnClickedButtonAnalyze();
}





void CHighPrecisionDlg::OnClickMenuReprot()
{
	// TODO: �ڴ���������������
	OnBnClickedButtonReport();
}


BOOL CHighPrecisionDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: �ڴ����ר�ô����/����û���
	//////HD_NOTIFY   *pHDN = (HD_NOTIFY*)lParam;
	//////if(pHDN->hdr.code==HDN_ITEMCHANGINGW||pHDN->hdr.code == HDN_ITEMCHANGINGA)        
	//////{
	//////	*pResult = TRUE;                // disable change
	//////	return TRUE;                    // Processed message
	//////}

	//return CListCtrl::OnNotify(wParam, lParam, pResult);
	return CDialogEx::OnNotify(wParam, lParam, pResult);
}

// ��ȡ��׼����
int CHighPrecisionDlg::ReadStandardOutline(double* pStandardDataX,double* pStandardDataY,double* pRightStandDataX,int &standardPointNum,CString path)
{
	//��ȡ��׼����
	CStdioFile fStandardFile;
	CString strLinetemp = _T("");
	int iNeedCount=0;
	//������������ѡ����ļ�������׼���������//
	if (fStandardFile.Open(path,CFile::modeRead))
	{
		while(fStandardFile.ReadString(strLinetemp))
		{
			char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
			char *strtemp = NULL;  
			strtemp = strtok(str, " ");  

			if (strtemp != NULL)  
			{  
				char *Xdata = strtemp; 
				pStandardDataX[iNeedCount] =atof(Xdata);
			}  				 
			strtemp = strtok(NULL, " ");  
			if (strtemp != NULL)  
			{ 
				char *Ydata = strtemp; 
				pStandardDataY[iNeedCount]= atof(Ydata);
			}  

			if (pStandardDataX[iNeedCount]>-30 && pStandardDataX[iNeedCount]<40 && pStandardDataY[iNeedCount]>0 && pStandardDataY[iNeedCount]<33.3)
			{
				pStandardDataY[iNeedCount]=-pStandardDataY[iNeedCount];
				pRightStandDataX[iNeedCount]=-pStandardDataX[iNeedCount];
				iNeedCount++;
			}
		}
		fStandardFile.Close();
		standardPointNum = iNeedCount;
	}
	return 0;
}


//void CHighPrecisionDlg::OnEnUpdateEditDistance()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
//	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam ������
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
// 	UpdateData(TRUE);
// 	m_Edit_Distance = _ttof(m_edit_distance_str);
// 	m_Edit_Distance += (m_Edit_Distance2 * 1000);
// 	m_Edit_DistanceReal=m_Edit_Distance;
// 	//�������
// 	CString strCurDist;
// 	//UpdateData(TRUE);
// 	int iK=(int)m_Edit_DistanceReal/1000;
// 	double iD=m_Edit_DistanceReal-1000*iK;
// 	string tmpDetectRoad=CsDetectRoad;
// 	tmpDetectRoad=tmpDetectRoad.substr(0,tmpDetectRoad.size()-2);
// 	strCurDist.Format("%s%d + %0.1f",tmpDetectRoad.c_str(),iK,iD);
// 	SetDlgItemText(IDC_DISTANCE_LINE,strCurDist);
// 	m_Edit_Distance2 = iK;
// 	m_Edit_Distance = iD;
// 	m_edit_distance_str.Format("%f", (float)m_Edit_Distance);
// 	m_edit_distance2_str.Format("%d", (int)m_Edit_Distance2);
// 
// 	UpdateData(FALSE);
//}


//void CHighPrecisionDlg::OnEnChangeEditDistance()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//	UpdateData(TRUE);
//	m_Edit_Distance = _ttof(m_edit_distance_str);
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


void CHighPrecisionDlg::OnNMDblclkListResDisp(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_List_ResultInfo
	if (g_TestInfo_L.XM_QianHou==0)//ϳĥǰ
	{	
		m_List_ResultInfo.SetColumnWidth(0,30);
		m_List_ResultInfo.SetColumnWidth(1,(rect.Width()-28)/2);
		m_List_ResultInfo.SetColumnWidth(2,(rect.Width()-28)/2);//���Ϊ325

		//m_List_ResultInfo.SetItemText(25,1,aaa);
	}
	else if (g_TestInfo_L.XM_QianHou==1)//ϳĥ��
	{
		
		m_List_ResultInfo.SetColumnWidth(0,30);
		m_List_ResultInfo.SetColumnWidth(1,(rect.Width()-28)/4-1);
		m_List_ResultInfo.SetColumnWidth(2,(rect.Width()-28)/4-1);
		m_List_ResultInfo.SetColumnWidth(3,(rect.Width()-28)/4+2);
		m_List_ResultInfo.SetColumnWidth(4,(rect.Width()-28)/4+2);

	}
	
	*pResult = 0;
}


//void CHighPrecisionDlg::OnBnClickedRadioFront()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	g_bFLagIsRunBack = FALSE;
//	UpdateData(FALSE);
//}


//void CHighPrecisionDlg::OnBnClickedRadioBack()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	g_bFLagIsRunBack = TRUE;
//	UpdateData(FALSE);
//}

void CHighPrecisionDlg::OnBnClickedRadioFront()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_bFLagIsRunBack = FALSE;
	UpdateData(FALSE);
}


void CHighPrecisionDlg::OnBnClickedRadioBack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_bFLagIsRunBack = TRUE;
	UpdateData(FALSE);
}


//void CHighPrecisionDlg::OnEnUpdateEditDistance2()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
//	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�
//	/*CString tmpstr;
//	GetDlgItem(IDC_EDIT_Distance)->GetWindowTextA(tmpstr);
//	double tmpd = _ttof(tmpstr);
//	m_Edit_Distance = tmpd;*/
// 	UpdateData(TRUE);
// 	m_Edit_Distance2 = _ttof(m_edit_distance2_str);
// 	OnEnUpdateEditDistance();
//}


void CHighPrecisionDlg::OnStnClickedStatic10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


//void CHighPrecisionDlg::OnEnChangeEditDistance2()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


//void CHighPrecisionDlg::OnEnChangeEditDistance()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


//void CHighPrecisionDlg::OnEnChangeEditDistance2()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


void CHighPrecisionDlg::OnEnKillfocusEditDistance()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	double m_Edit_DistanceTmp = _ttof(m_edit_distance_str);
	m_Edit_Distance = m_Edit_DistanceTmp+(m_Edit_Distance2 * 1000);
	m_Edit_DistanceReal = m_Edit_Distance;
	//�������
	CString strCurDist;
	//UpdateData(TRUE);
	int iK = (int)m_Edit_DistanceReal / 1000;
	double iD = m_Edit_DistanceReal - 1000 * iK;
	m_edit_distance_str.Format("%0.1f", (float)iD);
	m_edit_distance2_str.Format("%d", (int)iK);
	string tmpDetectRoad = CsDetectRoad;
	tmpDetectRoad = tmpDetectRoad.substr(0, tmpDetectRoad.size() - 2);
	strCurDist.Format("%s%d + %0.1f", tmpDetectRoad.c_str(), iK, iD);
	SetDlgItemText(IDC_DISTANCE_LINE, strCurDist);
	//m_Edit_Distance2 = iK;
	//m_Edit_Distance = iD;
	m_edit_distance_str.Format("%0.1f", (float)iD);
	m_edit_distance2_str.Format("%d", (int)iK);

	UpdateData(FALSE);
}


void CHighPrecisionDlg::OnEnKillfocusEditDistance2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	double m_Edit_DistanceTmp = _ttof(m_edit_distance_str);
	m_Edit_Distance2 = _ttof(m_edit_distance2_str);
	//OnEnUpdateEditDistance();
	m_Edit_Distance = m_Edit_Distance2 * 1000 + m_Edit_DistanceTmp;
}


void CHighPrecisionDlg::OnEnSetfocusEditDistance2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_havePressAnalyse = FALSE;
}


void GuiDiPoRevolve(int &PointNum,double *pInDataX, double *pInDataY,bool HdmOrXml,double &m_dGdpRad)
{
	OutLineArithmetic CalculateOutline;
	double youyi;
	double pInDataXtmp[700], pInDataYtmp[700];
	for (int i = 0; i < PointNum; i++)
	{
		pInDataXtmp[i] = pInDataX[i];
		pInDataYtmp[i] = pInDataY[i];
	}

	//����x����Ϊ0�ĵ��y����
	double y_tmp = 0;
	//����ϳĥ����ʱ��
	if (!HdmOrXml) 
	{
		for (int i = 0; i < PointNum; i++)
		{
			if (pInDataX[i] <= 0 && pInDataX[i + 1] >= 0)
			{
				y_tmp = (-pInDataX[i])* (pInDataY[i] - pInDataY[i + 1]) / (pInDataX[i] - pInDataX[i + 1]) + pInDataY[i];
				break;
			}
		}
	}	
	//������ת�Ƕ�
	std::vector<double> pInData_X_xl, pInData_Y_xl;
	int n = 0;
	for (int i = 0; i < PointNum; i++)
	{
		if (pInDataXtmp[i] >= -10 && pInDataXtmp[i] <= 10&&abs(pInDataYtmp[i])<=abs(y_tmp)+1)
		{
			pInData_X_xl.push_back(pInDataXtmp[i]);
			pInData_Y_xl.push_back(pInDataYtmp[i]);
		}
	}
	double xielv = CalculateOutline.LineFitLeastSquares(pInData_X_xl, pInData_Y_xl, pInData_X_xl.size());
	double gd_theta = atan(xielv);
	//gd_theta = 0;
	if (pInData_X_xl.size()<=10)
	{
		gd_theta = m_dGdpRad;
	}
	m_dGdpRad = gd_theta;
	//gd_theta = 0.024958;
	//�Ƚ�����������
	for (int i = 0; i < PointNum; i++)
	{
		pInDataY[i] -= y_tmp;
	}
	//�������ת
	for (int i = 0; i < PointNum; i++)
	{
		pInDataXtmp[i] = pInDataX[i] * cos(-gd_theta) - pInDataY[i] * sin(-gd_theta);
		pInDataYtmp[i] = pInDataX[i] * sin(-gd_theta) + pInDataY[i] * cos(-gd_theta);
	}
	for (int i = 0; i < PointNum; i++)
	{
		pInDataX[i] = pInDataXtmp[i];
		pInDataY[i] = pInDataYtmp[i];
	}
	//����y����Ϊ14.2����x���꣬������������
	for (int i = 0; i < PointNum; i++)
	{
		if (pInDataY[i] <= 14.2 && pInDataY[i + 1] >= 14.2)
		{
			double x_tmp = (14.2 - pInDataY[i])*(pInDataX[i] - pInDataX[i + 1]) / (pInDataY[i] - pInDataY[i + 1]) + pInDataX[i];
			youyi = 35.4 - x_tmp;
			break;
		}
	}
	//��������
	for (int i = 0; i < PointNum; i++)
	{
		pInDataX[i] += youyi;
	}
	//�������ƻص�������֮ǰ
	for (int i = 0; i < PointNum; i++)
	{
		pInDataY[i] += y_tmp;
	}
}


void CHighPrecisionDlg::OnStnClickedDistanceLine()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

/////////////////////////////////////////////////////////////zhang
void CHighPrecisionDlg::OnTbtClicklink()
{
	OnBnClickedButtonTestflag();//��ʼ��

	Sleep(100);
	// TODO: �ڴ���������������
	//if (g_bFlagMotor_L&&g_bFlagMotor_R&&g_bFlagSensorL&&g_bFlagSensorR)//����������
	//{
	//	CConnectDeviceDlg obj_ConnectDialog;
	//	obj_ConnectDialog.DoModal();
	//}
	//else
	//	OnBnClickedButtonLink();

	if (g_bFlagSensorL/*&&g_bFlagSensorR&&g_bFlagMotor_L&&g_bFlagMotor_R*/)
	{
		ZLDS200DisConnectAll();
		m_MachineCtrl_L.DisConnectMotor(m_Mscomm_L, true, false);
		//m_MachineCtrl_L.DisConnectMotor(m_Mscomm_R,true,false);
		SetDlgItemText(IDC_BUTTON_LINK, _T("�����豸"));
		g_bFlagSensorL = false;
		g_bFlagSensorR = false;
		/*g_bFlagMotor_L=false;
		g_bFlagMotor_R=false;*/
	}
	else
	{
		CConnectDeviceDlg obj_ConnectDevice;
		if (obj_ConnectDevice.DoModal() == IDOK)
		{
			if (g_bFlagSensorL/*&&g_bFlagSensorR&&g_bFlagMotor_L&&g_bFlagMotor_R*/)
			{
				SetDlgItemText(IDC_BUTTON_LINK, _T("�Ͽ��豸"));
				SetDlgItemText(IDC_STATIC_SYSTEMSTATUS, _T("���ӳɹ�"));
			}
		}
	}


}
void CHighPrecisionDlg::OnTbtClicktestinfo()
{
	// TODO: �ڴ���������������
	OnBnClickedButtonTestinfo();//������ҵ��Ϣ
}
void CHighPrecisionDlg::OnTbtClickcontour()
{
	// TODO: �ڴ���������������
	OnBnClickedButtonStart();//������ʼ���


}


void CHighPrecisionDlg::OnTbtClickanalyze()
{

	OnBnClickedButtonAnalyzeflag();
	// TODO: �ڴ���������������

}
void CHighPrecisionDlg::OnTbtClickhdata()
{
	// TODO: �ڴ���������������

}
void CHighPrecisionDlg::OnTbtClickstart()
{
	// TODO: �ڴ���������������
	//OnBnClickedButtonStart();
	AfxBeginThread((AFX_THREADPROC)Bomo_Shujun_Caiji_01, this);//��ĥ��ʼ
	AfxBeginThread((AFX_THREADPROC)Bomo_Shujun_Caiji_02, this);//��ĥ��ʼ
	AfxBeginThread((AFX_THREADPROC)Bomo_Shujun_Caiji_03, this);//��ĥ��ʼ
	AfxBeginThread((AFX_THREADPROC)Bomo_Shujun_chuli_01, this);//��ĥ��ʼ
	AfxBeginThread((AFX_THREADPROC)Bomo_Shujun_to_txt, this);//��ĥ��ʼ
	Bomo_caiji_zhuangtai = TEXT("���ݲɼ���...");	//�û���
	UpdateData(FALSE); //���ݸ��µ���Ӧ�Ŀؼ�
	
	KillTimer(0);
	SetTimer(0, 40, NULL);
}
void CHighPrecisionDlg::OnTbtClickpause()
{
	// TODO: �ڴ���������������

}
void CHighPrecisionDlg::OnTbtClickstop()
{
	// TODO: �ڴ���������������
	if (bFlagStartThread)
		OnBnClickedButtonStart();
}

//��ĥ���
void CHighPrecisionDlg::OnTbtClickbomo()
{
	
	Bomo_Flag_bomo_Caiji_R = !Bomo_Flag_bomo_Caiji_R;//���ݲɼ���־
	KillTimer(0);
	SetTimer(0, 40, NULL);
	AfxBeginThread((AFX_THREADPROC)Bomo_paint_bomo, this);//��ĥ��ʼ
}



/******************************************************************************************************************
******************************************************************************************************************
**************************************��ĥ�쳵����*****************************************************************
*****************************************************************************************************************
*******************************************************************************************************************/

//




void CHighPrecisionDlg::OnStnClickedBmstata1()
{
	// TODO: Add your control notification handler code here
}


void CHighPrecisionDlg::OnStnClickedBmstata5()
{
	// TODO: Add your control notification handler code here
}

/*������1���ݲɼ��߳�*/
UINT CHighPrecisionDlg::Bomo_Shujun_Caiji_01(LPVOID pParam)
{
	//��������������ʼ��
	Bomo_LoopBuf100_R1 = new float[524288];//������2���ݴ�
	Bomo_Psd_Loop_Buf_R1.LoopBuffInit(&Bomo_LoopBuffCtl_100_R1, 524288, Bomo_LoopBuf100_R1);


	CTime TCurrentTime;//��ȡ��ǰʱ��
	CString strTime;
	CString strFileName;
	CString PSD_strFileName01;

	TCurrentTime = TCurrentTime.GetCurrentTime();
	strTime.Format(_T("ƽ˳�����\\������1ƽ˳�����--%04d%02d%02d-%02d%02d%02d"), TCurrentTime.GetYear(), TCurrentTime.GetMonth(), TCurrentTime.GetDay(),
		TCurrentTime.GetHour(), TCurrentTime.GetMinute(), TCurrentTime.GetSecond());
	PSD_strFileName01.Format(_T("%s.txt"), strTime);


	FILE *fpz11;
	fpz11 = fopen(PSD_strFileName01, "a");
	//fpz22 = fopen("PSD_strFileName.txt", "a");
	//fp = fopen("ƽ˳��.txt", "r");
	if (fpz11 == NULL)
	{
		AfxMessageBox("cannot open file!\n");
		//return 0;
	}


	int avail1;
	int read1;

	double data[10000];
	float data_copy[10000];

	int err = 0;
	DWORD sensor;
	//DWORD sensor = CreateSensorInstance(SENSOR_ILD1420);

	Bomo_sensor_R1.CreateSensorInstance1(SENSOR_ILD1420, &sensor);
	string com = "Com1";
	int Baudrate = 921600;//���ò�����
	double Sampleshape = 4;//���ò���Ƶ��

	if (!sensor)
		AfxMessageBox(_T("1��ʼ��ʧ��"));

	if ((err = Bomo_sensor_R1.Open_1420(sensor, com, Baudrate))<0)
		AfxMessageBox(_T("�򿪴�����1ʧ��"));
	if ((err = Bomo_sensor_R1.SetSamplerate(sensor, Sampleshape, Baudrate))<0)//���ò���
		AfxMessageBox(_T("���ò�����ʧ��1ʧ��"));



	while (!Bomo_Flag_bomo_Caiji_R)	// 10 cycles
	{

		if ((err = Bomo_sensor_R1.DataAvail1((int)sensor, &avail1)<0))
			AfxMessageBox(_T("�򿪴�����1ʧ��"));
		//printf("Values avail: %04d\n", avail);

		Bomo_sensor_R1.TransferData1((int)sensor, NULL, data, sizeof(data), &read1);
		//printf("Few values: ");

		//���ݲɼ���ȡ���ļ�
		for (int j = 0; j < read1; j++)
		{
			fprintf(fpz11, "  %f \n", data[j]);
		}

		for (int i = 0; i<read1; i++)
			data_copy[i] = (float)data[i];

		//���ڻ���
		if (read > 0)
		{
			Bomo_m_Buf_Critical_R1.Lock();
			if (Bomo_Psd_Loop_Buf_R1.LoopBuffFreeSpace(&Bomo_LoopBuffCtl_100_R1) > read1)
			{
				Bomo_Psd_Loop_Buf_R1.LoopBuffWrite(&Bomo_LoopBuffCtl_100_R1, data_copy, read1);
			}
			Bomo_m_Buf_Critical_R1.Unlock();
		}


		Sleep(500);	// wait for new data
	}



	Bomo_sensor_R1.Cleanup(sensor);
	AfxMessageBox(_T("������1�ɼ�����"));
	return 0;



	return 0;
}
/*������2���ݲɼ��߳�*/
UINT CHighPrecisionDlg::Bomo_Shujun_Caiji_02(LPVOID pParam)
{
	//��������������ʼ��
	//��������������ʼ��
	Bomo_LoopBuf100_R2 = new float[524288];//������2���ݴ�


	Bomo_Psd_Loop_Buf_R2.LoopBuffInit(&Bomo_LoopBuffCtl_100_R2, 524288, Bomo_LoopBuf100_R2);



	CTime TCurrentTime;//��ȡ��ǰʱ��
	CString strTime;
	CString strFileName;
	CString PSD_strFileName01;

	TCurrentTime = TCurrentTime.GetCurrentTime();
	strTime.Format(_T("ƽ˳�����\\������2ƽ˳�����--%04d%02d%02d-%02d%02d%02d"), TCurrentTime.GetYear(), TCurrentTime.GetMonth(), TCurrentTime.GetDay(),
		TCurrentTime.GetHour(), TCurrentTime.GetMinute(), TCurrentTime.GetSecond());
	PSD_strFileName01.Format(_T("%s.txt"), strTime);


	FILE *fpz11;
	fpz11 = fopen(PSD_strFileName01, "a");
	//fpz22 = fopen("PSD_strFileName.txt", "a");
	//fp = fopen("ƽ˳��.txt", "r");
	if (fpz11 == NULL)
	{
		AfxMessageBox("cannot open file!\n");
		//return 0;
	}


	int avail1;
	int read1;

	double data[10000];
	float data_copy[10000];

	int err = 0;
	DWORD sensor;
	//DWORD sensor = CreateSensorInstance(SENSOR_ILD1420);

	Bomo_sensor_R2.CreateSensorInstance1(SENSOR_ILD1420, &sensor);
	string com = "Com3";
	int Baudrate = 921600;//���ò�����
	double Sampleshape = 4;//���ò���Ƶ��

	if (!sensor)
		AfxMessageBox(_T("2��ʼ��ʧ��"));

	if ((err = Bomo_sensor_R2.Open_1420(sensor, com, Baudrate))<0)
		AfxMessageBox(_T("�򿪴�����2ʧ��"));
	if ((err = Bomo_sensor_R2.SetSamplerate(sensor, Sampleshape, Baudrate))<0)//���ò���
		AfxMessageBox(_T("���ò�����ʧ��2ʧ��"));



	while (!Bomo_Flag_bomo_Caiji_R)	// 10 cycles
	{

		if ((err = Bomo_sensor_R2.DataAvail1((int)sensor, &avail1)<0))
			AfxMessageBox(_T("�򿪴�����2ʧ��"));
		//printf("Values avail: %04d\n", avail);

		Bomo_sensor_R2.TransferData1((int)sensor, NULL, data, sizeof(data), &read1);
		//printf("Few values: ");

		//���ݲɼ���ȡ���ļ�
		for (int j = 0; j < read1; j++)
		{
			fprintf(fpz11, "  %f \n", data[j]);
		}

		for (int i = 0; i<read1; i++)
			data_copy[i] = (float)data[i];

		//���ڻ���
		//���ڻ���
		if (read > 0)
		{
			Bomo_m_Buf_Critical_R2.Lock();
			if (Bomo_Psd_Loop_Buf_R2.LoopBuffFreeSpace(&Bomo_LoopBuffCtl_100_R2) > read1)
			{
				Bomo_Psd_Loop_Buf_R2.LoopBuffWrite(&Bomo_LoopBuffCtl_100_R2, data_copy, read1);
			}
			Bomo_m_Buf_Critical_R2.Unlock();
		}



		Sleep(500);	// wait for new data
	}



	Bomo_sensor_R2.Cleanup(sensor);
	AfxMessageBox(_T("������2�ɼ�����"));
	return 0;


	return 0;
}
/*������3���ݲɼ��߳�*/
UINT CHighPrecisionDlg::Bomo_Shujun_Caiji_03(LPVOID pParam)
{
	//��������������ʼ��
	Bomo_LoopBuf100_R3 = new float[524288];//������2���ݴ�
	Bomo_Psd_Loop_Buf_R3.LoopBuffInit(&Bomo_LoopBuffCtl_100_R3, 524288, Bomo_LoopBuf100_R3);


	CTime TCurrentTime;//��ȡ��ǰʱ��
	CString strTime;
	CString strFileName;
	CString PSD_strFileName01;

	TCurrentTime = TCurrentTime.GetCurrentTime();
	strTime.Format(_T("ƽ˳�����\\������3ƽ˳�����--%04d%02d%02d-%02d%02d%02d"), TCurrentTime.GetYear(), TCurrentTime.GetMonth(), TCurrentTime.GetDay(),
		TCurrentTime.GetHour(), TCurrentTime.GetMinute(), TCurrentTime.GetSecond());
	PSD_strFileName01.Format(_T("%s.txt"), strTime);


	FILE *fpz11;
	fpz11 = fopen(PSD_strFileName01, "a");
	//fpz22 = fopen("PSD_strFileName.txt", "a");
	//fp = fopen("ƽ˳��.txt", "r");
	if (fpz11 == NULL)
	{
		AfxMessageBox("cannot open file!\n");
		//return 0;
	}


	int avail1;
	int read1;

	double data[10000];
	float data_copy[10000];

	int err = 0;
	DWORD sensor;
	//DWORD sensor = CreateSensorInstance(SENSOR_ILD1420);

	Bomo_sensor_R3.CreateSensorInstance1(SENSOR_ILD1420, &sensor);
	string com = "Com5";
	int Baudrate = 921600;//���ò�����
	double Sampleshape = 4;//���ò���Ƶ��

	if (!sensor)
		AfxMessageBox(_T("3��ʼ��ʧ��"));

	if ((err = Bomo_sensor_R3.Open_1420(sensor, com, Baudrate))<0)
		AfxMessageBox(_T("�򿪴�����3ʧ��"));
	if ((err = Bomo_sensor_R3.SetSamplerate(sensor, Sampleshape, Baudrate))<0)//���ò���
		AfxMessageBox(_T("���ò�����ʧ��3ʧ��"));



	while (!Bomo_Flag_bomo_Caiji_R)	// 10 cycles
	{

		if ((err = Bomo_sensor_R3.DataAvail1((int)sensor, &avail1)<0))
			AfxMessageBox(_T("�򿪴�����3ʧ��"));
		//printf("Values avail: %04d\n", avail);

		Bomo_sensor_R3.TransferData1((int)sensor, NULL, data, sizeof(data), &read1);
		//printf("Few values: ");

		//���ݲɼ���ȡ���ļ�
		for (int j = 0; j < read1; j++)
		{
			fprintf(fpz11, "  %f \n", data[j]);
		}

		for (int i = 0; i<read1; i++)
			data_copy[i] = (float)data[i];

		//���ڻ���
		if (read > 0)
		{
			Bomo_m_Buf_Critical_R3.Lock();
			if (Bomo_Psd_Loop_Buf_R3.LoopBuffFreeSpace(&Bomo_LoopBuffCtl_100_R3) > read1)
			{
				Bomo_Psd_Loop_Buf_R3.LoopBuffWrite(&Bomo_LoopBuffCtl_100_R3, data_copy, read1);
			}
			Bomo_m_Buf_Critical_R3.Unlock();
		}



		Sleep(500);	// wait for new data
	}



	Bomo_sensor_R3.Cleanup(sensor);
	AfxMessageBox(_T("������3�ɼ�����"));



	return 0;
}



/*���ݴ����߳�*/
UINT CHighPrecisionDlg::Bomo_Shujun_chuli_01(LPVOID pParam)
{
	CHighPrecisionDlg *dlg = (CHighPrecisionDlg*)pParam;//���ú������߳�
	while (!Bomo_Flag_bomo_Caiji_R)
	{
		//��1�������ѻ��������ݱ��浽txt
		if (Bomo_Psd_Loop_Buf_R1.LoopBuffDataLength(&Bomo_LoopBuffCtl_100_R1) > Bomo_length)
		{
			if (Bomo_Psd_Loop_Buf_R2.LoopBuffDataLength(&Bomo_LoopBuffCtl_100_R2) > Bomo_length)
			{
				if (Bomo_Psd_Loop_Buf_R3.LoopBuffDataLength(&Bomo_LoopBuffCtl_100_R3) > Bomo_length)

				{

					Bomo_m_Buf_Critical_R1.Lock();	//�����ٽ�����Ȼ��رշ�ֹ��
					Bomo_Psd_Loop_Buf_R1.LoopBuffRead(&Bomo_LoopBuffCtl_100_R1, Bomo_sensor_data_R1, Bomo_length);
					Bomo_m_Buf_Critical_R1.Unlock(); // ��ȡ���ݺ��ͷ��ٽ���
					Bomo_Flag_CalPsd_113_R1 = TRUE;


					Bomo_m_Buf_Critical_R2.Lock();	//�����ٽ�����Ȼ��رշ�ֹ��
					Bomo_Psd_Loop_Buf_R2.LoopBuffRead(&Bomo_LoopBuffCtl_100_R2, Bomo_sensor_data_R2, Bomo_length);
					Bomo_m_Buf_Critical_R2.Unlock(); // ��ȡ���ݺ��ͷ��ٽ���
					Bomo_Flag_CalPsd_113_R2 = TRUE;


					Bomo_m_Buf_Critical_R3.Lock();	//�����ٽ�����Ȼ��رշ�ֹ��
					Bomo_Psd_Loop_Buf_R3.LoopBuffRead(&Bomo_LoopBuffCtl_100_R3, Bomo_sensor_data_R3, Bomo_length);
					Bomo_m_Buf_Critical_R3.Unlock(); // ��ȡ���ݺ��ͷ��ٽ���
					Bomo_Flag_CalPsd_113_R3 = TRUE;


	


					if ((Bomo_Flag_CalPsd_113_R3 == TRUE) && (Bomo_Flag_CalPsd_113_R2 == TRUE) && (Bomo_Flag_CalPsd_113_R1 == TRUE))

					{
						//�ļ��洢


						Bomo_SJCJ_sensor_count_R++;//���ݲɼ��Ĵ���
						Bomo_Flag_bomo_TxT_R = TRUE;//���ݵ���txt
						Bomo_Flag_bomo_Jisuan_R = TRUE;//���ݿ�ʼ����txt
						dlg->Bomo_Calculate();//�ǵ�ɾ��


					}



				}
			}
		}



	}




	return 0;
}


/*�ļ�����*/
UINT CHighPrecisionDlg::Bomo_Shujun_to_txt(LPVOID pParam)
{
	CString dss;

	CTime TCurrentTime;//��ȡ��ǰʱ��
	CString strTime;
	CString strFileName;
	CString TXT_strFileName;

	TCurrentTime = TCurrentTime.GetCurrentTime();
	strTime.Format(("ƽ˳�����\\��������ԭʼ����--%04d%02d%02d-%02d%02d%02d"), TCurrentTime.GetYear(), TCurrentTime.GetMonth(), TCurrentTime.GetDay(),
		TCurrentTime.GetHour(), TCurrentTime.GetMinute(), TCurrentTime.GetSecond());
	TXT_strFileName.Format(("%s.txt"), strTime);

	//PSD_strFileName.Format(("%s"), strFileName);

	while (!Bomo_Flag_bomo_Caiji_R)
	{

		//ԭʼ���ݴ洢�߳�
		if (Bomo_Flag_bomo_TxT_R == TRUE)
		{

			FILE *fpz22;
			fpz22 = fopen(TXT_strFileName, "a");
			//fpz22 = fopen("PSD_strFileName.txt", "a");
			//fp = fopen("ƽ˳��.txt", "r");
			if (fpz22 == NULL)
			{
				printf("cannot open file!\n");
				//return 0;
			}

			fprintf(fpz22, "   %dm__%dm \n", (Bomo_SJCJ_sensor_count_R - 1)*Bomo_Chuli_lengthe, (Bomo_SJCJ_sensor_count_R)*Bomo_Chuli_lengthe);
			for (int i = 0; i <  Bomo_length; i++)
			{
				fprintf(fpz22, "  %f ,  %f, %f \n", Bomo_sensor_data_R1[i], Bomo_sensor_data_R2[i], Bomo_sensor_data_R3[i]);
			}

			fclose(fpz22);

			Bomo_Flag_bomo_TxT_R = FALSE;
		}

	}

	return 0;
}









void CHighPrecisionDlg::OnStnClickedStaticSystemstatus()
{
	// TODO: Add your control notification handler code here

}

//��ĥ���ݴ�����
void CHighPrecisionDlg::Bomo_Calculate()
{

	if (Bomo_Flag_bomo_Jisuan_R == TRUE)
	{


				if (1)
				{
					for (int i = 0; i < Bomo_length; i++)
					{
						Bomo_sensor_jisun_data_R1[i] = (double)Bomo_sensor_data_R1[i];
						Bomo_sensor_jisun_data_R2[i] = (double)Bomo_sensor_data_R2[i];
						Bomo_sensor_jisun_data_R3[i] = (double)Bomo_sensor_data_R3[i];

						////����Ԥ������
						//if (sensor_data1[i]<7.0 || sensor_data1[i]>8.9)
						//	sensor_data1[i] = sensor_data1[i - 1];
						//if (sensor_data2[i]<7.0 || sensor_data2[i]>8.9)
						//	sensor_data2[i] = sensor_data2[i - 1];
						//if (sensor_data3[i]<7.0 || sensor_data3[i]>8.9)
						//	sensor_data3[i] = sensor_data3[i - 1];

					}

					/*����Ԥ����*/
					HINSTANCE hDll;//���
					typedef void(*PSD_Preproccess)(double[], double[], double[], int, double *, double *, double *);
					PSD_Preproccess Preproccess;//����ָ��

												/*���ݼ���*/
					HINSTANCE hDll1;//���
					typedef void(*PSD_Calculate)(double[], double[], double[], int, double *, double *, double *);
					PSD_Calculate Calculate;//����ָ��

											/*�������*/
					HINSTANCE hDll2;//���
					typedef void(*PSD_pingshundu)(double[], double[], double[], int, double *, double *, double *, int *, int *, int *, int *);
					PSD_pingshundu pingshundu;//����ָ��


					hDll = ::LoadLibrary("PSD_Preproccess.dll");//��̬��������ԤDLLģ����
					if (hDll == NULL)
						std::cout << "Error!!!\n";
					if (hDll)
					{
						Preproccess = (PSD_Preproccess)GetProcAddress(hDll, "PSD_Preproccess");//�õ�������DLLģ���к����ĵ�ַ													//CDLL *dll = instance();
						Preproccess(Bomo_sensor_jisun_data_R1, Bomo_sensor_jisun_data_R2, Bomo_sensor_jisun_data_R3, Bomo_length, Bomo_sensor_Pre_data_R1, Bomo_sensor_Pre_data_R2, Bomo_sensor_Pre_data_R3);
						FreeLibrary(hDll);//�ͷ��Ѿ����ص�DLLģ��
					}


					hDll1 = ::LoadLibrary("PSD_Calculate.dll");//��̬�������ݼ���DLLģ����
					if (hDll1 == NULL)
						std::cout << "Error!!!\n";


					if (hDll1)
					{
						Calculate = (PSD_Calculate)GetProcAddress(hDll1, "PSD_Calculate");//�õ�������DLLģ���к����ĵ�ַ													
						Calculate(Bomo_sensor_Pre_data_R1, Bomo_sensor_Pre_data_R2, Bomo_sensor_Pre_data_R3, Bomo_length, Bomo_a_1_3Hz_signal_R, Bomo_a_3_10Hz_signal_R, Bomo_a_10_100Hz_signal_R);
						FreeLibrary(hDll1);//�ͷ��Ѿ����ص�DLLģ��
					}




					hDll2 = ::LoadLibrary("PSD_pingshundu.dll");//��̬�����������DLLģ����
					if (hDll2 == NULL)
						std::cout << "Error!!!\n";


					if (hDll2)
					{
						pingshundu = (PSD_pingshundu)GetProcAddress(hDll2, "PSD_pingshundu");//�õ�������DLLģ���к����ĵ�ַ													//CDLL *dll = instance();
						pingshundu(Bomo_a_1_3Hz_signal_R, Bomo_a_3_10Hz_signal_R, Bomo_a_10_100Hz_signal_R, Bomo_length, Bomo_RMS_30_100mm_R, Bomo_RMS_100_300mm_R, Bomo_RMS_300_100mm_R,
							&Bomo_Chaoxianbi_30_100mm_R, &Bomo_Chonxianbi_100_300mm_R, &Bomo_Chaoxianbi_300_1000mm_R, &Bomo_PSD_jiegou_R);
						FreeLibrary(hDll2);//�ͷ��Ѿ����ص�DLLģ��
					}






//���屣���ļ���
	

					CTime TCurrentTime;//��ȡ��ǰʱ��
					CString strTime;
					CString strFileName;
					CString PSD_strFileName;
					//�ļ����������м��ļ�
					CString PSD_strFileName_zhongbo;
					CString PSD_strFileName_changbo;
					CString PSD_strFileName_duanbo;
					//�ļ����������м��ļ�
					CString strTime_zhongbo;
					CString strTime_changbo;
					CString strTime_duanbo;




					if (Bomo_paint_count_tow_R == 0)


					{
						//�ֲ���Ľ��
						TCurrentTime = TCurrentTime.GetCurrentTime();
						strTime.Format(("ƽ˳�����\\������\\ƽ˳�����--%04d%02d%02d-%02d%02d%02d"), TCurrentTime.GetYear(), TCurrentTime.GetMonth(), TCurrentTime.GetDay(),
							TCurrentTime.GetHour(), TCurrentTime.GetMinute(), TCurrentTime.GetSecond());
						PSD_strFileName.Format(("%s.txt"), strTime);

						strTime_changbo.Format(("ƽ˳�����\\������\\RMSֵ\\����RMSֵ--%04d%02d%02d-%02d%02d%02d"), TCurrentTime.GetYear(), TCurrentTime.GetMonth(), TCurrentTime.GetDay(),
							TCurrentTime.GetHour(), TCurrentTime.GetMinute(), TCurrentTime.GetSecond());
						PSD_strFileName_changbo.Format(("%s.txt"), strTime);

						strTime_zhongbo.Format(("ƽ˳�����\\������\\RMSֵ\\�в�RMSֵ--%04d%02d%02d-%02d%02d%02d"), TCurrentTime.GetYear(), TCurrentTime.GetMonth(), TCurrentTime.GetDay(),
							TCurrentTime.GetHour(), TCurrentTime.GetMinute(), TCurrentTime.GetSecond());
						PSD_strFileName_zhongbo.Format(("%s.txt"), strTime);

						strTime_duanbo.Format(("ƽ˳�����\\������\\RMSֵ\\�̲�RMSֵ--%04d%02d%02d-%02d%02d%02d"), TCurrentTime.GetYear(), TCurrentTime.GetMonth(), TCurrentTime.GetDay(),
							TCurrentTime.GetHour(), TCurrentTime.GetMinute(), TCurrentTime.GetSecond());
						PSD_strFileName_duanbo.Format(("%s.txt"), strTime);




					}
					//PSD_strFileName.Format(("%s"), strFileName);



					FILE *fpz22;
					fpz22 = fopen(PSD_strFileName, "a");
					//fpz22 = fopen("PSD_strFileName.txt", "a");
					//fp = fopen("ƽ˳��.txt", "r");
					if (fpz22 == NULL)
					{
						printf("cannot open file!\n");
						//return 0;
					}



					fprintf(fpz22, "   %dm__%dm \n", (Bomo_SJCJ_sensor_count_R)*Bomo_Chuli_lengthe, (Bomo_SJCJ_sensor_count_R + 1)*Bomo_Chuli_lengthe);
					for (int i = 0; i < Bomo_length; i++)
					{
						fprintf(fpz22, "  %f ,  %f, %f \n", Bomo_a_1_3Hz_signal_R[i], Bomo_a_3_10Hz_signal_R[i], Bomo_a_10_100Hz_signal_R[i]);
					}

				
					fclose(fpz22);



				}
				Bomo_SJCJ_sensor_count_R++;//���ݲɼ��Ĵ���

				/*�Ȼ�ͼ���ȴ����꣬vector�����*/
				if (Bomo_Flag_huantu_vector_read_or_write_R == TRUE)
					Sleep(1000);
			
				/*���ݵ��뵽vector*/
				if (1)
				{
					for (int i = 0; i < Bomo_length; i++)
					{
						Bomo_huantu_vector_read_or_write_sensor_R1.push_back(Bomo_a_1_3Hz_signal_R[i]);
						Bomo_huantu_vector_read_or_write_sensor_R2.push_back(Bomo_a_3_10Hz_signal_R[i]);
						Bomo_huantu_vector_read_or_write_sensor_R3.push_back(Bomo_a_10_100Hz_signal_R[i]);

					}
					//��������������ͻ��ʾ���ݴ�������Կ�ʼ��ͼ�Ĳ���
					Bomo_Flag_huantu_vector_read_or_write_R = TRUE;

				}


				 Bomo_Flag_bomo_Jisuan_R = FALSE;//������ɣ�׼����һ�μ���

	}
}


void CHighPrecisionDlg::Bomo_Prepear_paint()
{
}



/*****************************************��ͼ������Ч��******************************************/
//�ƶ����庯��
void CHighPrecisionDlg::Bomo_Huatu_DrawMoving_Calculate_three()
{



	//*��һ��*///


	double *line1 = new double[Bomo_huatu_yidong_length];//Bomo_huatu_yidong_length=10��ͼÿ���ƶ��ĳ���
	double *line2 = new double[Bomo_huatu_yidong_length];
	double *line3 = new double[Bomo_huatu_yidong_length];
	//���������
	Bomo_ChartCtrl_R2.RemoveAllSeries();//�����  
	Bomo_pLineSerie_R1 = Bomo_ChartCtrl_R2.CreateLineSerie();
	//Bomo_pLineSerie_R1->SetColor(RGB(255, 0, 0));
	Bomo_pLineSerie_R1->SetSeriesOrdering(poNoOrdering);//����Ϊ����  

	Bomo_pLineSerie_R2 = Bomo_ChartCtrl_R2.CreateLineSerie();
	//Bomo_pLineSerie_R2->SetColor(RGB( 0, 255, 0));
	Bomo_pLineSerie_R2->SetSeriesOrdering(poNoOrdering);//����Ϊ����  


	Bomo_pLineSerie_R3 = Bomo_ChartCtrl_R2.CreateLineSerie();

	//Bomo_pLineSerie_R3->SetColor(RGB( 0,0,255));
	Bomo_pLineSerie_R3->SetSeriesOrdering(poNoOrdering);//����Ϊ����  









	//������ȴ�ʱ�䣬��հ�������⴦��//
			if (Bomo_Flag_huantu_Qudengdai_R == TRUE)
			{
				//���������
					Bomo_pLineSerie_R1->AddPoints(Bomo_paint_X_R1, Bomo_paint_Y_TeeChartArray_R1, Bomo_paint_arrayLength);
					Bomo_ChartCtrl_R2.EnableRefresh(true);

					Bomo_pLineSerie_R2->AddPoints(Bomo_paint_X_R2, Bomo_paint_Y_TeeChartArray_R2, Bomo_paint_arrayLength);
					Bomo_pLineSerie_R3->AddPoints(Bomo_paint_X_R3, Bomo_paint_Y_TeeChartArray_R3, Bomo_paint_arrayLength);

			}


	//�����Ĵ���׶�
			else
			{
				//if((Boxin_Xunhuna<1600) ||
				if (Bomo_paint_step_R < Bomo_length)//��ͼ
				{
					for (int m = 0; m < Bomo_huatu_yidong_length; m++)
					{
						//����10��
						line1[m] = Bomo_a_1_3Hz_signal_R[Bomo_paint_step_R];
						line2[m] = Bomo_a_3_10Hz_signal_R[Bomo_paint_step_R];
						line3[m] = Bomo_a_10_100Hz_signal_R[Bomo_paint_step_R];
						Bomo_paint_step_R++;
					}
					///////////////////��ͼ//////////////////////////



					Bomo_Huatu_LeftMoveArray(Bomo_paint_Y_TeeChartArray_R1, Bomo_paint_arrayLength, line1);//�ƶ�y����
					Bomo_Huatu_LeftMoveArray_shuju(Bomo_paint_X_R1, Bomo_paint_arrayLength, Bomo_paint_X_cout_R);//�ƶ�x����

					Bomo_Huatu_LeftMoveArray(Bomo_paint_Y_TeeChartArray_R2, Bomo_paint_arrayLength, line2);//�ƶ�y����
					Bomo_Huatu_LeftMoveArray_shuju(Bomo_paint_X_R2, Bomo_paint_arrayLength, Bomo_paint_X_cout_R);//�ƶ�x����

					Bomo_Huatu_LeftMoveArray(Bomo_paint_Y_TeeChartArray_R3, Bomo_paint_arrayLength, line3);//�ƶ�y����
					Bomo_Huatu_LeftMoveArray_shuju(Bomo_paint_X_R3, Bomo_paint_arrayLength, Bomo_paint_X_cout_R);//�ƶ�x����



					//�����ͷ
					Bomo_pLineSerie_R2->AddPoints(Bomo_paint_X_R2, Bomo_paint_Y_TeeChartArray_R2, Bomo_paint_arrayLength);
					Bomo_pLineSerie_R1->AddPoints(Bomo_paint_X_R1, Bomo_paint_Y_TeeChartArray_R1, Bomo_paint_arrayLength);
					Bomo_pLineSerie_R3->AddPoints(Bomo_paint_X_R3, Bomo_paint_Y_TeeChartArray_R3, Bomo_paint_arrayLength);
					Bomo_ChartCtrl_R2.EnableRefresh(true);


					delete[] line1;
					delete[] line2;
					delete[] line3;


				}


				/*��ʾһ�δ����Ѿ�������ϣ��ر�ONTIME�����м����������ƶ�����*/
				else
				{
					Bomo_Flag_huantu_DrawMoving_R = FALSE;//�ر�ONTIME�����м����������ƶ�����

				}


				
			}

}

//X�����ƶ�����
void CHighPrecisionDlg::Bomo_Huatu_LeftMoveArray(double * ptr, size_t length2, double * data)
{

	for (size_t i = Bomo_huatu_yidong_length; i<length2; ++i)
	{
		ptr[i - Bomo_huatu_yidong_length] = ptr[i];
	}
	for (int i3 = 0; i3<Bomo_huatu_yidong_length; ++i3)
	{
		ptr[length2 - Bomo_huatu_yidong_length + i3] = data[i3];
	}


}
//Y�����ƶ�����
void CHighPrecisionDlg::Bomo_Huatu_LeftMoveArray_shuju(double * ptr, size_t length2, double data)
{

	for (size_t i = 0; i<length2; ++i)

		ptr[i] = data - Bomo_paint_arrayLength + i;
}
//ˢ�º���
void CHighPrecisionDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 0)
	{


		/*���´���ؼ�*/
		if (Bomo_Flag_bomo_Jisuan_R == TRUE)
		{
			Bomo_chuli_zhuangtai = TEXT("���ݴ�����...");	//�û���
			UpdateData(FALSE); //���ݸ��µ���Ӧ�Ŀؼ�
		}


		/*�Ƿ���������ƶ�����ȥ��һ�λ�ͼ�����������ÿ�δ������½�������*/
		if (Bomo_Flag_huantu_DrawMoving_R == TRUE)
		{
			Bomo_paint_X_cout_R = Bomo_paint_X_cout_R + Bomo_huatu_yidong_length;//��ͼ���ƶ�
			Bomo_Huatu_DrawMoving_Calculate_three();
			Bomo_Flag_huantu_Qudengdai_R = FALSE;//��ͼȥ�ȴ�ʱ��
		}

		/*�Ƿ��Ѿ�����һ�δ���ĳ��Ȼ�ͼ*/
		else if (Bomo_huantu_vector_read_or_write_sensor_R1.size() >Bomo_length - 1)
		{


			for (int i = 0; i < Bomo_length; i++)
			{
				Bomo_huantu_a_1_3Hz_signal_R[i] = Bomo_huantu_vector_read_or_write_sensor_R1[i];
				Bomo_huantu_a_3_10Hz_signal_R[i] = Bomo_huantu_vector_read_or_write_sensor_R2[i];
				Bomo_huantu_a_10_100Hz_signal_R[i] = Bomo_huantu_vector_read_or_write_sensor_R3[i];
			}
			/*ɾ���Ѿ��ù��ĵ�*/




			//�����ݴ����ʦ�����������������
			if (Bomo_Flag_huantu_vector_read_or_write_R == FALSE)
				Sleep(1000);

			//��ȥ�Ѿ������������
			Bomo_huantu_vector_read_or_write_sensor_R1.erase(Bomo_huantu_vector_read_or_write_sensor_R1.begin(), Bomo_huantu_vector_read_or_write_sensor_R1.begin() + Bomo_length);
			Bomo_huantu_vector_read_or_write_sensor_R2.erase(Bomo_huantu_vector_read_or_write_sensor_R2.begin(), Bomo_huantu_vector_read_or_write_sensor_R2.begin() + Bomo_length);
			Bomo_huantu_vector_read_or_write_sensor_R3.erase(Bomo_huantu_vector_read_or_write_sensor_R3.begin(), Bomo_huantu_vector_read_or_write_sensor_R3.begin() + Bomo_length);
			Bomo_Flag_huantu_vector_read_or_write_R = FALSE;


			/*��һ�δ���ͼ*/
			if (Bomo_paint_count_R == 0)
			{

				//��ʼ��
				for (size_t i = 0; i < Bomo_paint_arrayLength; i++)
				{

					Bomo_paint_X_R1[i] = i;
					Bomo_paint_X_R2[i] = i;
					Bomo_paint_X_R3[i] = i;
					Bomo_paint_Y_TeeChartArray_R1[i] = Bomo_huantu_a_1_3Hz_signal_R[i];
					Bomo_paint_Y_TeeChartArray_R2[i] = Bomo_huantu_a_3_10Hz_signal_R[i];
					Bomo_paint_Y_TeeChartArray_R3[i] = Bomo_huantu_a_10_100Hz_signal_R[i];

					Bomo_paint_step_R = Bomo_paint_arrayLength;
				}

			}

			/*֮��ͼ��ͼ*/
			else
			{
				Bomo_paint_step_R = 0;
				Bomo_paint_X_cout_R = Bomo_paint_count_R * Bomo_length + Bomo_paint_arrayLength;
			}

			Bomo_paint_count_R++;

			Bomo_Flag_huantu_DrawMoving_R = TRUE;//��������ƶ�
			Bomo_Flag_huantu_Qudengdai_R = FALSE;//ȥ�㲻ͬ��֮ǰ����ʱ��־
			Bomo_Huatu_DrawMoving_Calculate_three();
		}



		/*�ų���ͼ�����ݴ����ʱ�����⻭ͼ���ֿհ�*/
		else if ((Bomo_paint_count_R>0) && (Bomo_Flag_huantu_DrawMoving_R == FALSE) && (Bomo_huantu_vector_read_or_write_sensor_R1.size()<Bomo_length - 1))
		{
			if (Bomo_paint_count_R>0)//��ȥ��һ�ε��������
				Bomo_Flag_huantu_Qudengdai_R = TRUE;//���⻭ͼ���ֿհ׵ı�־����ͼ��Huatu_DrawMoving��һֱ��ʾ
			Bomo_Huatu_DrawMoving_Calculate_three();
		}






	}




	CDialogEx::OnTimer(nIDEvent);
}

/*****************************************��ͼ������Ч������****************************************/


//��ͼ�����߳�
UINT CHighPrecisionDlg::Bomo_paint_bomo(LPVOID pParam)
{
	CHighPrecisionDlg *dlg = (CHighPrecisionDlg*)pParam;//���ú������߳�


	while(1)
	{ 
		for (int i = 0; i < Bomo_length; i++)
		{
			Bomo_sensor_data_R1[i] = sin(i);
			Bomo_sensor_data_R2[i] = cos(i);
			Bomo_sensor_data_R3[i] = sin(2*i);

		}


		Bomo_Flag_bomo_Jisuan_R =TRUE;
		dlg->Bomo_Calculate();//�ǵ�ɾ��


		Sleep(1000);
	}

	return 0;
}






