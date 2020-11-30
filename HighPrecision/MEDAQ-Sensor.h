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
	int Open_1420(DWORD sensor, string com, int Baudrate);//打开传感器
	int GetInfo(DWORD sensor);//获取传感器信息
	int SetSamplerate(int sensor, double Samplerate, int Baudrate);//设置采样频率
	void Cleanup(int sensor);//断开传传感器
	int DataAvail1(int sensor, int *avail1);//传感器采集个数
	int TransferData1(int sensor, int *rawData, double *dataa, int length, int *read1);//获取数据
	void CreateSensorInstance1(ME_SENSOR sensorType, DWORD *sensor);//初始化传感器
};