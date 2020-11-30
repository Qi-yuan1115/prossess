#pragma once
#include "Outline.h"
#include <string>
#include <fstream>
#include <map>
#include<memory>
#include<iostream>
/**
	���ڲ��������ļ�
**/
class OutlineFileHelper
{
public:
	OutlineFileHelper(std::string filePath);
	virtual ~OutlineFileHelper();

	//���������������ȡ����,��0��ʼ
	Outline getOutlineByIndex(int index);
	
	Outline getNextOutline();
	
	Outline getPreviousOutline();

	//����������̻�ȡ��������0.1��ʼ
	Outline getOutlineByMileage(double meters);

	double getStartPos();

	double getEndPos();

	double getCurrentPos();

private:
	void parseLine(std::string line, double& meter, double& coordX, double& coordY);
	Outline getOutlineByMileageInternal(double meters);
	Outline getOutlineByIndexInternal(int index);

private:
	//��ǰ�������
	double m_currentOutlineMeter;
	//������ֹ���
	double m_outlineStartMeter;

	double m_outlineEndMeter;
	int m_strLengthOneLine;
	std::shared_ptr<std::map<int, Outline>> m_Outlines;
	
	std::ifstream m_fileStream;

	void init();
};

