#pragma once
#include "Outline.h"
#include <string>
#include <fstream>
#include <map>
#include<memory>
#include<iostream>
/**
	用于操作轮廓文件
**/
class OutlineFileHelper
{
public:
	OutlineFileHelper(std::string filePath);
	virtual ~OutlineFileHelper();

	//根据轮廓序号来获取轮廓,从0开始
	Outline getOutlineByIndex(int index);
	
	Outline getNextOutline();
	
	Outline getPreviousOutline();

	//根据轮廓里程获取轮廓，从0.1开始
	Outline getOutlineByMileage(double meters);

	double getStartPos();

	double getEndPos();

	double getCurrentPos();

private:
	void parseLine(std::string line, double& meter, double& coordX, double& coordY);
	Outline getOutlineByMileageInternal(double meters);
	Outline getOutlineByIndexInternal(int index);

private:
	//当前轮廓里程
	double m_currentOutlineMeter;
	//轮廓起止里程
	double m_outlineStartMeter;

	double m_outlineEndMeter;
	int m_strLengthOneLine;
	std::shared_ptr<std::map<int, Outline>> m_Outlines;
	
	std::ifstream m_fileStream;

	void init();
};

