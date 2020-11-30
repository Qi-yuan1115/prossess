#include "stdafx.h"
#include "MEDAQ-Sensor.h"





int ME_Sonser::PrintError(LPCSTR err)
{
	printf("Error!\n%s", err);
	return -1;
}

int ME_Sonser::Error(LPCSTR err, int sensor)
{
	char out[1024], buf[1024];
	GetError(sensor, buf, sizeof(buf));

	sprintf(out, "Error in %s\n%s", err, buf);
	return PrintError(out);
}


int ME_Sonser::Open_1420(DWORD sensor, string com, int Baudrate)
{

	const char *com1 = com.data();
	//CHECK_ERROR (OpenSensorRS232 (sensor, "COM3"));	// also valid for RS422 to USB Converter (with RS232 driver emulation)
	CHECK_ERROR(SetParameterString(sensor, "IP_Interface", "RS232"));
	CHECK_ERROR(SetParameterString(sensor, "IP_Port", com1));
	CHECK_ERROR(SetParameterInt(sensor, "IP_Baudrate", Baudrate));
	CHECK_ERROR(OpenSensor(sensor));
	return ERR_NOERROR;
}

int ME_Sonser::GetInfo(DWORD sensor)
{

	int botel;
	double caiyanglv;
	CHECK_ERROR(ExecSCmdGetInt(sensor, "Get_Baudrate", "SA_SensorBaudrate", &botel));
	return ERR_NOERROR;
	//printf("波特率：%d", botel);

	CHECK_ERROR(ExecSCmdGetDouble(sensor, "Get_Samplerate", "SA_Measrate", &caiyanglv));
	return ERR_NOERROR;
	//printf("波特率：%lf", caiyanglv);
}

int ME_Sonser::SetSamplerate(int sensor, double Samplerate, int Baudrate)
{
	CHECK_ERROR(SetDoubleExecSCmd(sensor, "Set_Samplerate", "SP_Measrate", Samplerate));
	CHECK_ERROR(SetIntExecSCmd(sensor, "Set_Baudrate", "SP_SensorBaudrate", Baudrate));
	return ERR_NOERROR;
}

void ME_Sonser::Cleanup(int sensor)
{
	if (CloseSensor(sensor) != ERR_NOERROR)
		PrintError("Cannot close sensor!");
	if (ReleaseSensorInstance(sensor) != ERR_NOERROR)
		PrintError("Cannot release driver instance!");

}

int ME_Sonser::DataAvail1(int sensor, int *avail1)
{
	CHECK_ERROR(DataAvail(sensor, avail1));
	return ERR_NOERROR;
}

int ME_Sonser::TransferData1(int sensor, int * rawData, double * dataa, int length, int *read1)
{
	CHECK_ERROR(TransferData(sensor, NULL, dataa, length, read1));
	return ERR_NOERROR;
}

void ME_Sonser::CreateSensorInstance1(ME_SENSOR sensorType, DWORD *sensor)
{
	*sensor = CreateSensorInstance(sensorType);
}
