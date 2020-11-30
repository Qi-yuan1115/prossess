#include <WINSOCK2.H>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <IO.H>
#include <direct.h>
#include <MATH.H>
#include <time.h>
#include "include/ZLDS200LanInc.h"
#include "include/ZLDS200LanLib.h"
#include <process.h>
#include <string>
using namespace std;

//连接传感器，返回连接的传感器个数和传感器序列号，连接局域网上所有的传感器,-3和0代表搜索不到传感器
extern "C" int __stdcall  ZLDS200ConnectAll(int deviceType,int sn[]);
//获取传感器测量值，返回获取到的轮廓点数，-1代表iChoose超范围，-2代表获取数据失败，-3代表获取CRC校验失败，65535代表获取点个数超出限制值，0代表获取点个数为零
extern "C" int __stdcall  ZLDS200GetPoint(float *x_results,float *z_results,int *measureNum, int *packetNum, int *pointnum,BOOL bChecksumCheck,int iChoose_);
//获取传感器测量值,内置算法，返回获取到的轮廓点数，-1代表iChoose超范围，-2代表获取数据失败，-3代表获取CRC校验失败，65535代表获取点个数超出限制值，0代表获取点个数为零
extern "C" int __stdcall  ZLDS200GetResult(float *x_results,float *z_results,int *measureNum, int *packetNum, int *pointnum,BOOL bChecksumCheck,int iChoose_);
//读取传感器参数，返回1成功，-1不成功
extern "C" int __stdcall  ZLDS200ReadParams(void * lpBuffer,int iChoose_);
//修改传感器参数，返回1成功，-1不成功
extern "C" int __stdcall  ZLDS200WriteParams(void * lpBuffer,int iChoose_);
//把传感器参数写入闪存，返回1成功，-1不成功
extern "C" int __stdcall  ZLDS200FlushParams(BOOL bDefault,int iChoose_);
//重启传感器，返回1成功，-1不成功
extern "C" int __stdcall  ZLDS200Reboot(int iChoose_);
//关闭传感器，返回1成功，-1不成功
extern "C" int __stdcall  ZLDS200Shutdown(int iChoose_);
//连接单个传感器，返回1成功，-1不成功，必须要先ZLDS200ConnectAll获取传感器句柄
extern "C" int __stdcall  ZLDS200Connect(int iChoose_);
//传感器断开连接，返回1成功，-1不成功
extern "C" int __stdcall  ZLDS200DisConnect(int iChoose_);
//断开所有传感器连接，返回1成功，-1不成功
extern "C" int __stdcall  ZLDS200DisConnectAll();
//获取读取轮廓点个数，返回-1不成功，成功返回轮廓点个数
extern "C" int __stdcall  ZLDS200GetPointNum(int iChoose_);
//获取传感器Z轴和X轴的范围，返回-1不成功，成功返回1
extern "C" int __stdcall  ZLDS200GetRange(int iChoose_,int *Z_range,int *X_range);

void BufferInit(int sensorNum, int profileNum,int maxPointNum);
void DeleteBuffer();
bool Buffer_getValue(int sensorIndex,float *x, float *z, int *tmpIndex,char* tdate);
bool Buffer_addValue(int sensorIndex,float *x, float *z, int tmpIndex,SYSTEMTIME sys);
void BufferReset();
void BufferReset(int sensorIndex);
unsigned __stdcall handleDataThd(void *pvoid);
int CreatNewFile(int iChoose_);
unsigned __stdcall handleSaveThd(void *pvoid);
int confirmIndex(int n, float x[], float t);

extern "C" int __stdcall  ZLDS200GetBuffer(int iChoose_,float *x_results,float *z_results,int *pointnum);
extern "C" void __stdcall  ZLDS200StartStream(int iChoose_,char *str,int saveFrequency);
extern "C" void __stdcall  ZLDS200StopStream(int iChoose_);
extern "C" void __stdcall  ZLDS200RestFirst(int iChoose_);

