
// HighPrecisionDlg.h : 头文件
#include "ChartClass\ChartCtrl.h" 
#include "ChartClass\ChartLineSerie.h"
#include "ChartClass\ChartSerie.h"
#include "ChartClass\ChartPointsSerie.h"
//#include "Interface\\VC\\CadLib.h"
//#include "Interface\\VC\\DrawingView.h"
#include "CadLib.h"
#include "DrawingView.h"
#include "ChartClass\ChartAxisLabel.h"
#include <vector>
#include <string>
#include "mscomm1.h"
#include "MachineControl.h"
#include "ButtonST.h"
/////////////////////////////////////////////////////////////zhang
/////////////////////////////////////////////////////////////zhang


using namespace std;
#pragma once


/**********宏定义**************/
//#define  Encoder_Distance		 0.1			//采集的里程单位
#define  SensorMaxPoint			 700			//传感器采集的最大点数
#define  Num_Node				 23				//横断面精度计算总点数
#define  Num_Node_50			 19			//横断面精度计算总点数
#define  Num_BuffLunkuo  		 524288			//缓冲区所存轮廓坐标点数
#define  Num_BuffLunkuoPoint	 65536			//缓存区轮廓条数
#define  Num_Duan_50			 4				//50轨所分段数
#define  Num_Duan_60			 6				//60轨所分段数
#define  ComBaud				 "115200"
#define  Pi						 3.14159
#define  Num_StInterval			 500	        //每隔Num_StInterval个轮廓存储一个TXT（除原始轮廓外）原来是10000
#define  MotorMoveLmt			 2		//电机运转左右极限距离

#define  Motor_DaoCheng 75  //电机导程

// CHighPrecisionDlg 对话框
class CHighPrecisionDlg : public CDialogEx
{
// 构造
public:
	CHighPrecisionDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HIGHPRECISION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//以下加入代码声明（请按功能分类）
public:
	 afx_msg LRESULT On2DMsgFunc_Xml_R(WPARAM wParam,LPARAM lParam);
	 afx_msg LRESULT On2DMsgFunc_Xml_L(WPARAM wParam,LPARAM lParam);
	 afx_msg LRESULT On2DMsgFunc_XmlScbz_R(WPARAM wParam,LPARAM lParam);
	 afx_msg LRESULT On2DMsgFunc_XmlScbz_L(WPARAM wParam,LPARAM lParam);
	 afx_msg LRESULT On2DMsgFunc_L(WPARAM wParam,LPARAM lParam);//左轨画图消息响应函数
	 afx_msg LRESULT On2DMsgFunc_R(WPARAM wParam,LPARAM lParam);//右轨画图消息响应函数
	 afx_msg LRESULT On2DDispDistance(WPARAM wParam,LPARAM lParam);//显示里程数WM_2DDISPLISTCTRL_L
	 afx_msg LRESULT On2DDispListCtrl_L(WPARAM wParam,LPARAM lParam);
	 afx_msg LRESULT On2DDispListCtrl_R(WPARAM wParam,LPARAM lParam);
	 void allSeriesClear();//清除所有线条
	 afx_msg void OnBnClickedButtonLink();
	 afx_msg void OnBnClickedButtonTestinfo();
	 afx_msg void OnBnClickedButtonStart();
	 afx_msg void OnBnClickedButtonTestflag();
	 afx_msg void OnBnClickedButtonAnalyzeflag();
	 afx_msg void OnClose();
	 afx_msg void OnSize(UINT nType, int cx, int cy);
	 void ReSize(void);
	 afx_msg void OnSetSensorPara();
public:
	CMenu *m_MainMenu;

	/////////////////////////////////////////////////////////////zhang
	CToolBar    m_toolbar; 
	CImageList m_ImageList;
	//CBomo_TestDlg* Bomo_TestDlg;
	 
	/////////////////////////////////////////////////////////////zhang


	CChartCtrl m_ChartCtrl_LeftTop;
	CChartCtrl m_ChartCtrl_RightTop;
	CChartCtrl m_ChartCtrl_LeftDown;
	CChartCtrl m_ChartCtrl_RightDown;
	CPoint Old;
	
public:
	//用于左下角坐标系中画铣磨量或者断面精度值带点曲线
	CChartLineSerie* m_pLeftBottomLineSerie;
	CChartPointsSerie* m_pLeftBottomPointSerie;
	//用于左上角坐标系中画统计分析中的断面精度或者铣磨量统计平均值/最大值带点曲线
	CChartLineSerie* m_pLeftTopLineSerie;
	CChartPointsSerie* m_pLeftTopPointSerie;
	CChartLineSerie* m_pMaxLeftTopLineSerie;
	CChartPointsSerie* m_pMaxLeftTopPointSerie;
	//用于左上角坐标系中画标准轮廓、铣磨前、铣磨后轮廓
	CChartLineSerie* m_pLeftTopStandardLineSerie;
	CChartLineSerie* m_pLeftTopAfterLineSerie;
	CChartLineSerie* m_pLeftTopBeforeLineSerie;

	//用于右下角坐标系中画铣磨量或者断面精度值带点曲线
	CChartLineSerie* m_pRightBottomLineSerie;
	CChartPointsSerie* m_pRightBottomPointSerie;
	//用于右上角坐标系中画统计分析中的断面精度或者铣磨量统计平均值/最大值带点曲线
	CChartLineSerie* m_pRightTopLineSerie;
	CChartPointsSerie* m_pRightTopPointSerie;
	CChartLineSerie* m_pMaxRightTopLineSerie;
	CChartPointsSerie* m_pMaxRightTopPointSerie;
	//用于右上角坐标系中画标准轮廓、铣磨前、铣磨后轮廓
	CChartLineSerie* m_pRightTopStandardLineSerie;
	CChartLineSerie* m_pRightTopAfterLineSerie;
	CChartLineSerie* m_pRightTopBeforeLineSerie;
	//左上坐标系
	CChartAxis *pAxisLeft1;   
	CChartAxis *pAxisBottom1;   
	//左下坐标系
	CChartAxis *pAxisLeft3;   
	CChartAxis *pAxisBottom3;   
	//右上坐标系
	CChartAxis *pAxisLeft2;   
	CChartAxis *pAxisBottom2;   
	//右下坐标系
	CChartAxis *pAxisLeft4;   
	CChartAxis *pAxisBottom4;   

	double f60LeftOutlineError[23];
	double f60leftOutlinePos[23];
	double f60RightOutlineError[23];
	double f60RightOutlinePos[23];

	double f50LeftOutlineError[19];
	double f50leftOutlinePos[19];
	double f50RightOutlineError[19];
	double f50RightOutlinePos[19];

	int IsAfterMillFlag;  //标记是铣磨前或铣磨后分析
	vector<vector<double>> m_startAndEndVec; //存储每个文件的起始和终止里程
	vector<CString> m_fileLineVec;   //存储本次铣磨中的铣磨后文件
	vector<CString> m_RightfileLineVec;   //存储本次铣磨中的铣磨后文件
	vector<CString> m_fileBeforeLineVec; //存储本次铣磨中的铣磨前文件
	vector<CString> m_RightfileBeforeLineVec; //存储本次铣磨中的铣磨前文件
	vector<CString> m_HdmLineVec; //存储本次铣磨中的断面精度文件
	vector<CString> m_RightHdmLineVec; //存储本次铣磨中的断面精度文件
	vector<CString> m_XmlLineVec;  //存储铣磨量文件
	vector<CString> m_RightXmlLineVec; //存储铣磨量文件



	int currentFileIndex;  //存储当前轮廓所在的文件索引
	int lastFileIndex;   //存储上一次操作轮廓所在的文件索引，用于判断是否有文件跨越
	double localFileX[1280];
	double localFileRightX[1280];
	double localFileY[1280];
	double localFileRightY[1280];
	double LastlocalFileX[1280];
	double LastlocalFileRightX[1280];
	double LastlocalFileY[1280];
	double LastlocalFileRightY[1280];
	double pStandardDataX[150],pStandardDataY[150],pRightStandDataX[150];
	double pStandardDataX50[150],pStandardDataY50[150],pRightStandDataX50[150];
	int StandardPointNum;
	int StandardPointNum50;

	int localFilePointNum;
	int RightlocalFilePointNum;
	int LastlocalFilePointNum;
	int RightLastlocalFilePointNum;
	ULONGLONG m_PrecisionFileOffset;
	ULONGLONG m_LeftOutLineFileOffset;
	ULONGLONG m_LeftMillingFileOffset;  //左轮廓铣磨量文件读取游标位置
	ULONGLONG m_LeftBeforeOutlineFileOffset; //左铣磨前轮廓文件读取游标位置
	ULONGLONG m_RightPrecisionFileOffset;
	ULONGLONG m_RightOutLineFileOffset;
	ULONGLONG m_RightMillingFileOffset;  //左轮廓铣磨量文件读取游标位置
	ULONGLONG m_RightBeforeOutlineFileOffset; //左铣磨前轮廓文件读取游标位置
	vector<double*> localFileHdmVec;
	vector<double> OverValueHdmVec;  //存储超限数据轮廓里程
	vector<double> RightOverValueHdmVec;  //存储超限数据轮廓里程
	vector<double*> RightlocalFileHdmVec;
	//检测信息
	CString CsDetectTime; //检测时间
	CString CsDetectGuiXing;//检测轨型
	CString CsDetectBegin; //检测起点
	CString CsDetectEnd; //检测终点
	CString CsTongjiInterval;//统计区间，比如里程从0.1到100
	CString CsDetectRoad; //检测线别
	CString CsDirection;//检测上下行
	CString CsGongLiBiao;//公里标 即当前里程
	CString CsDetectDetail; //

	//用于生成报告的变量
	bool bSingle;  //单个轮廓模式
	bool bChaoXian; //超限模式
	bool bTongJi; //统计模式
	CString HdmORXmlFilePath;
	CString RightHdmORXmlFilePath; //精度或者铣磨量文件路径
	CString dAcceptRate01;//达限率
	
	double maxLimit;
	int m_OutlineType;  //保存当前轮廓检测轨型
	string curFileDirection; //保存当前目录的绝对路径
	unsigned int m_curOverValueIndex;
	ULONGLONG m_PrecisionNumCnt;

	double pPrecisionAverage[23];
	double pPrecisionMax[23];
	double pRightPrecisionAverage[23];
	double pRightPrecisionMax[23];

	double m_fixedValueRatio;   // 左轨达限率
	double m_RightfixedValueRatio;//右轨达限率

	//控制重复按钮错误行为
	bool m_havePressAnalyse;

   //生成CAD所需变量
	//标记位置的线段的起点和中点
	double startiLeftOutlineAnaPointX[23];
	double startiLeftOutlineAnaPointY[23];
	double endiLeftOutlineAnaPointX[23];
	double endiLeftOutlineAnaPointY[23];
	int precisionPointNum;   //用来统一保存三种轨型的精度点查看数目
	bool isCreateCad;
	bool leftOverValueFlag;
	bool rightOverValueFlag;

	// 铣磨后单个轮廓断面精度分析
	void AfterSingleOutlinePrecisionDisp(double currentDistance,double RightcurrentDistance);
	void AfterStatisticOutlinePrecisionDisp();
	void AfterSingleOutlineMillingAmountDisp(double currentDistance,double RightcurrentDistance);
	void AfterStatisticOutlineMillingAmountDisp();
	void AfterTransfiniteDataViewDisp();

	void BeforeSingleOutlinePrecisionDisp(double  currentDistance,double RightcurrentDistance);
	void BeforeStatisticOutlinePrecisionDisp();
	void BeforeTransfiniteDataViewDisp();
	// 对所有可调整变量重新初始化
	int ResetAllData(void);
	// 读取并显示标准轮廓
	int DisplayStandardOutline(void);
	// 更新分析模式选择信息
	void UpdateModelSelInfo(string strFileName);
public:
	afx_msg void OnBnClickedButtonInputfile();
	afx_msg void OnBnClickedButtonAnalyze();
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_Combo_ModelSel;
	CComboBox m_Combo_TotalDistance;
	double m_Edit_Distance;
	double m_Edit_DistanceReal;
	CSpinButtonCtrl m_Spin1;
	CListBox m_List_FileName;
	CListCtrl m_List_ResultInfo;
	afx_msg void OnCbnSelchangeComboModelsel();
	afx_msg void OnBnClickedButtonSelectdistance();
	afx_msg void OnBnClickedButtonReport();
private:
	// //读取轮廓
	int ReadOutline(double currentDistance,double *outlineX,double *outlineY,int &outlinePointNum,ULONGLONG &fileOffset,CString filePath);
	// 读取断面精度或者铣磨量
	int ReadPrecisionOrMill(double currentDistance,double* outLineError,int outLineErrorPointNum,ULONGLONG &fileOffset,CString filePath);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnMotorSetPara();//设置电机参数
	afx_msg void OnBnClickedButtonStopmotor();//暂停电机
	afx_msg void OnEnSetfocusEditDistance();//
	afx_msg void OnSetReportParam();//设置声称报告参数
	afx_msg void allButtonDisable();//点击开始检测，禁用部分按钮
	afx_msg void OnCbnSelchangeComboTotaldistance();
	//菜单响应按钮
	afx_msg void OnClickMenuLink();
	afx_msg void OnClickMenuTestinfo();
	afx_msg void OnClickMenuTeststart();
	afx_msg void OnClickMenuMotorstop();
	afx_msg void OnClickMenuTeststop();
	afx_msg void OnClickMenuInputfile();
	afx_msg void OnClickMenuAnaylze();
	afx_msg void OnClickMenuReprot();

	CButtonST btn1;//调试
	CButtonST btn2;//分析
	CButtonST btn3;//连接设备
	CButtonST btn4;//作业信息
	CButtonST btn5;//导入文
	CButtonST btn6;//生成报告
	CButtonST btn7;//子分析
	CButtonST btn8;//重选里程
	CButtonST btn9;//急停
	CButtonST btn10;//开始
	//电机暂停按钮中用到的标志位
	bool bFlagStopMt;//电机暂停按钮默认显示为暂停，FALSE时表示显示为开启电机
	bool bFlagStopMt_L;
	bool bFlagStopMt_R;
	
	CFont m_editFont;

	CDrawing drawing;
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	// 读取标准轮廓
	int ReadStandardOutline(double* pStandardDataX,double* pStandardDataY,double* pRightStandDataX,int &standardPointNum,CString path);
//	afx_msg void OnEnUpdateEditDistance();
//	afx_msg void OnEnChangeEditDistance();
	afx_msg void OnNMDblclkListResDisp(NMHDR *pNMHDR, LRESULT *pResult);
//	bool g_bFLagIsRunBack;
	afx_msg void OnBnClickedRadioFront();
	afx_msg void OnBnClickedRadioBack();
	double m_Edit_Distance2;
//	afx_msg void OnEnUpdateEditDistance2();
	afx_msg void OnStnClickedStatic10();
	CString m_edit_distance_str;
	CString m_edit_distance2_str;
//	afx_msg void OnEnChangeEditDistance2();
//	afx_msg void OnEnChangeEditDistance();
//	afx_msg void OnEnChangeEditDistance2();
	afx_msg void OnEnKillfocusEditDistance();
	afx_msg void OnEnKillfocusEditDistance2();
	afx_msg void OnEnSetfocusEditDistance2();
	afx_msg void OnStnClickedDistanceLine();


	/////////////////////////////////////////////////////////////zhang
	afx_msg void OnTbtClicklink();
	afx_msg void OnTbtClicktestinfo();
	afx_msg void OnTbtClickcontour();
	afx_msg void OnTbtClickbomo();
	afx_msg void OnTbtClickanalyze();
	afx_msg void OnTbtClickhdata();
	afx_msg void OnTbtClickstart();
	afx_msg void OnTbtClickpause();
	afx_msg void OnTbtClickstop();
	/////////////////////////////////////////////////////////////zhang
	afx_msg void OnStnClickedBmstata1();
	afx_msg void OnStnClickedBmstata5();

	public:
		CWinThread* pThread; //20190705
		static UINT Bomo_Shujun_Caiji_01(LPVOID pParam);//波磨采集线程
		static UINT Bomo_Shujun_Caiji_02(LPVOID pParam);//波磨采集线程
		static UINT Bomo_Shujun_Caiji_03(LPVOID pParam);//波磨采集线程
		static UINT Bomo_Shujun_to_txt(LPVOID pParam);//数据存储线程


		static UINT Bomo_Shujun_chuli_01(LPVOID pParam);//波磨采集线程


		static UINT  Bomo_paint_bomo(LPVOID pParam);//调试画图控制函数


		afx_msg void OnTimer(UINT_PTR nIDEvent);
		afx_msg void OnStnClickedStaticSystemstatus();
		void Bomo_Calculate();

		void Bomo_Prepear_paint();
		//画图函数
		void Bomo_Huatu_DrawMoving_Calculate_three();
		void Bomo_Huatu_LeftMoveArray(double * ptr, size_t length2, double * data);
		void Bomo_Huatu_LeftMoveArray_shuju(double * ptr, size_t length2, double data);

		CChartCtrl Bomo_ChartCtrl_R;//坐标系类名


		CChartCtrl Bomo_ChartCtrl_R2;//坐标系类名
		//波磨左边坐标系
		CChartAxis *pAxisLeft_bomo_R;
		CChartAxis *pAxisBottom_bomo_R;
		//三条线段
		CChartLineSerie *Bomo_pLineSerie_R1;
		CChartLineSerie *Bomo_pLineSerie_R2;
		CChartLineSerie *Bomo_pLineSerie_R3;
		//工作状态
		CString Bomo_caiji_zhuangtai;
		CString Bomo_chuli_zhuangtai;


};
