
// HighPrecisionDlg.h : ͷ�ļ�
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


/**********�궨��**************/
//#define  Encoder_Distance		 0.1			//�ɼ�����̵�λ
#define  SensorMaxPoint			 700			//�������ɼ���������
#define  Num_Node				 23				//����澫�ȼ����ܵ���
#define  Num_Node_50			 19			//����澫�ȼ����ܵ���
#define  Num_BuffLunkuo  		 524288			//���������������������
#define  Num_BuffLunkuoPoint	 65536			//��������������
#define  Num_Duan_50			 4				//50�����ֶ���
#define  Num_Duan_60			 6				//60�����ֶ���
#define  ComBaud				 "115200"
#define  Pi						 3.14159
#define  Num_StInterval			 500	        //ÿ��Num_StInterval�������洢һ��TXT����ԭʼ�����⣩ԭ����10000
#define  MotorMoveLmt			 2		//�����ת���Ҽ��޾���

#define  Motor_DaoCheng 75  //�������

// CHighPrecisionDlg �Ի���
class CHighPrecisionDlg : public CDialogEx
{
// ����
public:
	CHighPrecisionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HIGHPRECISION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//���¼�������������밴���ܷ��ࣩ
public:
	 afx_msg LRESULT On2DMsgFunc_Xml_R(WPARAM wParam,LPARAM lParam);
	 afx_msg LRESULT On2DMsgFunc_Xml_L(WPARAM wParam,LPARAM lParam);
	 afx_msg LRESULT On2DMsgFunc_XmlScbz_R(WPARAM wParam,LPARAM lParam);
	 afx_msg LRESULT On2DMsgFunc_XmlScbz_L(WPARAM wParam,LPARAM lParam);
	 afx_msg LRESULT On2DMsgFunc_L(WPARAM wParam,LPARAM lParam);//��컭ͼ��Ϣ��Ӧ����
	 afx_msg LRESULT On2DMsgFunc_R(WPARAM wParam,LPARAM lParam);//�ҹ컭ͼ��Ϣ��Ӧ����
	 afx_msg LRESULT On2DDispDistance(WPARAM wParam,LPARAM lParam);//��ʾ�����WM_2DDISPLISTCTRL_L
	 afx_msg LRESULT On2DDispListCtrl_L(WPARAM wParam,LPARAM lParam);
	 afx_msg LRESULT On2DDispListCtrl_R(WPARAM wParam,LPARAM lParam);
	 void allSeriesClear();//�����������
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
	//�������½�����ϵ�л�ϳĥ�����߶��澫��ֵ��������
	CChartLineSerie* m_pLeftBottomLineSerie;
	CChartPointsSerie* m_pLeftBottomPointSerie;
	//�������Ͻ�����ϵ�л�ͳ�Ʒ����еĶ��澫�Ȼ���ϳĥ��ͳ��ƽ��ֵ/���ֵ��������
	CChartLineSerie* m_pLeftTopLineSerie;
	CChartPointsSerie* m_pLeftTopPointSerie;
	CChartLineSerie* m_pMaxLeftTopLineSerie;
	CChartPointsSerie* m_pMaxLeftTopPointSerie;
	//�������Ͻ�����ϵ�л���׼������ϳĥǰ��ϳĥ������
	CChartLineSerie* m_pLeftTopStandardLineSerie;
	CChartLineSerie* m_pLeftTopAfterLineSerie;
	CChartLineSerie* m_pLeftTopBeforeLineSerie;

	//�������½�����ϵ�л�ϳĥ�����߶��澫��ֵ��������
	CChartLineSerie* m_pRightBottomLineSerie;
	CChartPointsSerie* m_pRightBottomPointSerie;
	//�������Ͻ�����ϵ�л�ͳ�Ʒ����еĶ��澫�Ȼ���ϳĥ��ͳ��ƽ��ֵ/���ֵ��������
	CChartLineSerie* m_pRightTopLineSerie;
	CChartPointsSerie* m_pRightTopPointSerie;
	CChartLineSerie* m_pMaxRightTopLineSerie;
	CChartPointsSerie* m_pMaxRightTopPointSerie;
	//�������Ͻ�����ϵ�л���׼������ϳĥǰ��ϳĥ������
	CChartLineSerie* m_pRightTopStandardLineSerie;
	CChartLineSerie* m_pRightTopAfterLineSerie;
	CChartLineSerie* m_pRightTopBeforeLineSerie;
	//��������ϵ
	CChartAxis *pAxisLeft1;   
	CChartAxis *pAxisBottom1;   
	//��������ϵ
	CChartAxis *pAxisLeft3;   
	CChartAxis *pAxisBottom3;   
	//��������ϵ
	CChartAxis *pAxisLeft2;   
	CChartAxis *pAxisBottom2;   
	//��������ϵ
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

	int IsAfterMillFlag;  //�����ϳĥǰ��ϳĥ�����
	vector<vector<double>> m_startAndEndVec; //�洢ÿ���ļ�����ʼ����ֹ���
	vector<CString> m_fileLineVec;   //�洢����ϳĥ�е�ϳĥ���ļ�
	vector<CString> m_RightfileLineVec;   //�洢����ϳĥ�е�ϳĥ���ļ�
	vector<CString> m_fileBeforeLineVec; //�洢����ϳĥ�е�ϳĥǰ�ļ�
	vector<CString> m_RightfileBeforeLineVec; //�洢����ϳĥ�е�ϳĥǰ�ļ�
	vector<CString> m_HdmLineVec; //�洢����ϳĥ�еĶ��澫���ļ�
	vector<CString> m_RightHdmLineVec; //�洢����ϳĥ�еĶ��澫���ļ�
	vector<CString> m_XmlLineVec;  //�洢ϳĥ���ļ�
	vector<CString> m_RightXmlLineVec; //�洢ϳĥ���ļ�



	int currentFileIndex;  //�洢��ǰ�������ڵ��ļ�����
	int lastFileIndex;   //�洢��һ�β����������ڵ��ļ������������ж��Ƿ����ļ���Խ
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
	ULONGLONG m_LeftMillingFileOffset;  //������ϳĥ���ļ���ȡ�α�λ��
	ULONGLONG m_LeftBeforeOutlineFileOffset; //��ϳĥǰ�����ļ���ȡ�α�λ��
	ULONGLONG m_RightPrecisionFileOffset;
	ULONGLONG m_RightOutLineFileOffset;
	ULONGLONG m_RightMillingFileOffset;  //������ϳĥ���ļ���ȡ�α�λ��
	ULONGLONG m_RightBeforeOutlineFileOffset; //��ϳĥǰ�����ļ���ȡ�α�λ��
	vector<double*> localFileHdmVec;
	vector<double> OverValueHdmVec;  //�洢���������������
	vector<double> RightOverValueHdmVec;  //�洢���������������
	vector<double*> RightlocalFileHdmVec;
	//�����Ϣ
	CString CsDetectTime; //���ʱ��
	CString CsDetectGuiXing;//������
	CString CsDetectBegin; //������
	CString CsDetectEnd; //����յ�
	CString CsTongjiInterval;//ͳ�����䣬������̴�0.1��100
	CString CsDetectRoad; //����߱�
	CString CsDirection;//���������
	CString CsGongLiBiao;//����� ����ǰ���
	CString CsDetectDetail; //

	//�������ɱ���ı���
	bool bSingle;  //��������ģʽ
	bool bChaoXian; //����ģʽ
	bool bTongJi; //ͳ��ģʽ
	CString HdmORXmlFilePath;
	CString RightHdmORXmlFilePath; //���Ȼ���ϳĥ���ļ�·��
	CString dAcceptRate01;//������
	
	double maxLimit;
	int m_OutlineType;  //���浱ǰ����������
	string curFileDirection; //���浱ǰĿ¼�ľ���·��
	unsigned int m_curOverValueIndex;
	ULONGLONG m_PrecisionNumCnt;

	double pPrecisionAverage[23];
	double pPrecisionMax[23];
	double pRightPrecisionAverage[23];
	double pRightPrecisionMax[23];

	double m_fixedValueRatio;   // ��������
	double m_RightfixedValueRatio;//�ҹ������

	//�����ظ���ť������Ϊ
	bool m_havePressAnalyse;

   //����CAD�������
	//���λ�õ��߶ε������е�
	double startiLeftOutlineAnaPointX[23];
	double startiLeftOutlineAnaPointY[23];
	double endiLeftOutlineAnaPointX[23];
	double endiLeftOutlineAnaPointY[23];
	int precisionPointNum;   //����ͳһ�������ֹ��͵ľ��ȵ�鿴��Ŀ
	bool isCreateCad;
	bool leftOverValueFlag;
	bool rightOverValueFlag;

	// ϳĥ�󵥸��������澫�ȷ���
	void AfterSingleOutlinePrecisionDisp(double currentDistance,double RightcurrentDistance);
	void AfterStatisticOutlinePrecisionDisp();
	void AfterSingleOutlineMillingAmountDisp(double currentDistance,double RightcurrentDistance);
	void AfterStatisticOutlineMillingAmountDisp();
	void AfterTransfiniteDataViewDisp();

	void BeforeSingleOutlinePrecisionDisp(double  currentDistance,double RightcurrentDistance);
	void BeforeStatisticOutlinePrecisionDisp();
	void BeforeTransfiniteDataViewDisp();
	// �����пɵ����������³�ʼ��
	int ResetAllData(void);
	// ��ȡ����ʾ��׼����
	int DisplayStandardOutline(void);
	// ���·���ģʽѡ����Ϣ
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
	// //��ȡ����
	int ReadOutline(double currentDistance,double *outlineX,double *outlineY,int &outlinePointNum,ULONGLONG &fileOffset,CString filePath);
	// ��ȡ���澫�Ȼ���ϳĥ��
	int ReadPrecisionOrMill(double currentDistance,double* outLineError,int outLineErrorPointNum,ULONGLONG &fileOffset,CString filePath);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnMotorSetPara();//���õ������
	afx_msg void OnBnClickedButtonStopmotor();//��ͣ���
	afx_msg void OnEnSetfocusEditDistance();//
	afx_msg void OnSetReportParam();//�������Ʊ������
	afx_msg void allButtonDisable();//�����ʼ��⣬���ò��ְ�ť
	afx_msg void OnCbnSelchangeComboTotaldistance();
	//�˵���Ӧ��ť
	afx_msg void OnClickMenuLink();
	afx_msg void OnClickMenuTestinfo();
	afx_msg void OnClickMenuTeststart();
	afx_msg void OnClickMenuMotorstop();
	afx_msg void OnClickMenuTeststop();
	afx_msg void OnClickMenuInputfile();
	afx_msg void OnClickMenuAnaylze();
	afx_msg void OnClickMenuReprot();

	CButtonST btn1;//����
	CButtonST btn2;//����
	CButtonST btn3;//�����豸
	CButtonST btn4;//��ҵ��Ϣ
	CButtonST btn5;//������
	CButtonST btn6;//���ɱ���
	CButtonST btn7;//�ӷ���
	CButtonST btn8;//��ѡ���
	CButtonST btn9;//��ͣ
	CButtonST btn10;//��ʼ
	//�����ͣ��ť���õ��ı�־λ
	bool bFlagStopMt;//�����ͣ��ťĬ����ʾΪ��ͣ��FALSEʱ��ʾ��ʾΪ�������
	bool bFlagStopMt_L;
	bool bFlagStopMt_R;
	
	CFont m_editFont;

	CDrawing drawing;
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	// ��ȡ��׼����
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
		static UINT Bomo_Shujun_Caiji_01(LPVOID pParam);//��ĥ�ɼ��߳�
		static UINT Bomo_Shujun_Caiji_02(LPVOID pParam);//��ĥ�ɼ��߳�
		static UINT Bomo_Shujun_Caiji_03(LPVOID pParam);//��ĥ�ɼ��߳�
		static UINT Bomo_Shujun_to_txt(LPVOID pParam);//���ݴ洢�߳�


		static UINT Bomo_Shujun_chuli_01(LPVOID pParam);//��ĥ�ɼ��߳�


		static UINT  Bomo_paint_bomo(LPVOID pParam);//���Ի�ͼ���ƺ���


		afx_msg void OnTimer(UINT_PTR nIDEvent);
		afx_msg void OnStnClickedStaticSystemstatus();
		void Bomo_Calculate();

		void Bomo_Prepear_paint();
		//��ͼ����
		void Bomo_Huatu_DrawMoving_Calculate_three();
		void Bomo_Huatu_LeftMoveArray(double * ptr, size_t length2, double * data);
		void Bomo_Huatu_LeftMoveArray_shuju(double * ptr, size_t length2, double data);

		CChartCtrl Bomo_ChartCtrl_R;//����ϵ����


		CChartCtrl Bomo_ChartCtrl_R2;//����ϵ����
		//��ĥ�������ϵ
		CChartAxis *pAxisLeft_bomo_R;
		CChartAxis *pAxisBottom_bomo_R;
		//�����߶�
		CChartLineSerie *Bomo_pLineSerie_R1;
		CChartLineSerie *Bomo_pLineSerie_R2;
		CChartLineSerie *Bomo_pLineSerie_R3;
		//����״̬
		CString Bomo_caiji_zhuangtai;
		CString Bomo_chuli_zhuangtai;


};
