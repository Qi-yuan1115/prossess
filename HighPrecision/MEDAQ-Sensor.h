#pragma
#include <windows.h>
#include <string>
// MEDAQLib.h must be included to know it's functions
#include "MEDAQLib.h"
using namespace std;

// MEDAQLib.lib must be imported to call it's functions
#pragma comment (lib, "MEDAQLib.lib")
#ifndef _countof
#define _countof(x) (sizeof (x)/sizeof (x[0]))
#endif // _countof

#define CHECK_ERROR(errCode) \
	if ((errCode)!=ERR_NOERROR) \
		return Error (#errCode, sensor);

class ME_Sonser
{
public:
	int PrintError(LPCSTR err);
	int Error(LPCSTR err, int sensor);
	int Open_1420(DWORD sensor, string com, int Baudrate);//�򿪴�����
	int GetInfo(DWORD sensor);//��ȡ��������Ϣ
	int SetSamplerate(int sensor, double Samplerate, int Baudrate);//���ò���Ƶ��
	void Cleanup(int sensor);//�Ͽ���������
	int DataAvail1(int sensor, int *avail1);//�������ɼ�����
	int TransferData1(int sensor, int *rawData, double *dataa, int length, int *read1);//��ȡ����
	void CreateSensorInstance1(ME_SENSOR sensorType, DWORD *sensor);//��ʼ��������
};