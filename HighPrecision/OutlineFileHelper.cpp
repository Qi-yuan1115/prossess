#include "stdafx.h"
#include "OutlineFileHelper.h"
#include <cmath>
#include<iostream>
#include <cstdlib>

#define SPACE " "
#define OUTLINE_SAMPLE_INTERVAL_METER 0.1f

OutlineFileHelper::OutlineFileHelper(std::string filePath) {
	m_Outlines = std::make_shared<std::map<int, Outline>>();
	m_fileStream.open(filePath);
	init();
}

OutlineFileHelper::~OutlineFileHelper() {
	if (m_fileStream.is_open()) {
		m_fileStream.close();
	}
}

void OutlineFileHelper::init() {
	std::string firstLine;
	std::getline(m_fileStream, firstLine);
	int firstSpaceIndex = firstLine.find(" ");
	m_currentOutlineMeter = std::atof(firstLine.substr(0, firstSpaceIndex).c_str());
	m_outlineStartMeter = m_currentOutlineMeter;
	m_fileStream.seekg(std::ios::beg);
	std::string lastLine;
	bool readFinish = FALSE;
	int outLineIndex = 0;
	while (!readFinish)
	{
		Outline outline = getOutlineByIndexInternal(outLineIndex);
		if (outline.isEmpty()) {
			readFinish = TRUE;
		}
		else
		{
			m_Outlines->insert(std::pair<int, Outline>(outLineIndex, outline));
			++outLineIndex;	
			if (outLineIndex > 45)
				break;
		}
	}
	m_outlineEndMeter = OUTLINE_SAMPLE_INTERVAL_METER * (outLineIndex - 1) + m_outlineStartMeter;

}

Outline OutlineFileHelper::getOutlineByIndex(int index) {
	auto iter = m_Outlines->find(index);
	Outline ret;
	if (iter != m_Outlines->end()) {
		ret = m_Outlines->at(index);
	}
	m_currentOutlineMeter = index * OUTLINE_SAMPLE_INTERVAL_METER + OUTLINE_SAMPLE_INTERVAL_METER;
	return ret;
}

Outline OutlineFileHelper::getOutlineByMileage(double targetMeter) {
	int index = (int)((int)(targetMeter * 10 - m_outlineStartMeter * 10) / (int)(OUTLINE_SAMPLE_INTERVAL_METER * 10));
	return getOutlineByIndex(index);
}


//根据轮廓序号来获取轮廓
Outline OutlineFileHelper::getOutlineByIndexInternal(int index) {
	double targetMeter = m_outlineStartMeter + (double)index * OUTLINE_SAMPLE_INTERVAL_METER;
	return getOutlineByMileageInternal(targetMeter);

}

Outline OutlineFileHelper::getNextOutline()
{
	double targetMeter = m_currentOutlineMeter + OUTLINE_SAMPLE_INTERVAL_METER;
	return getOutlineByMileage(targetMeter);
}

Outline OutlineFileHelper::getPreviousOutline()
{
	double targetMeter = m_currentOutlineMeter - OUTLINE_SAMPLE_INTERVAL_METER;
	return getOutlineByMileage(targetMeter);
}

//根据轮廓里程获取轮廓
Outline OutlineFileHelper::getOutlineByMileageInternal(double targetMeter) {
	Outline ret;
	//m_fileStream.seekg(std::ios::beg);
	std::string curLine;
	bool finishOneOutline = FALSE;
	double coordX;
	double coordY;
	double meter;
	while (!finishOneOutline)
	{
		std::getline(m_fileStream, curLine);
		if (m_fileStream.eof()) {
			break;
		}
		parseLine(curLine, meter, coordX, coordY);
		if (fabs(meter - targetMeter) < 10E-3) {
			ret.addPoint(coordX, coordY);
		}
		else if (meter - targetMeter > 10E-3){
			m_strLengthOneLine = curLine.length() + 2;
			m_fileStream.seekg(m_strLengthOneLine * (-1), SEEK_CUR);
			finishOneOutline = TRUE;
		}
	}
	return ret;
}

void OutlineFileHelper::parseLine(std::string curLine, double& meter, double& coordX, double& coordY) {
	int firstSpaceIndex = curLine.find_first_of(SPACE);
	meter = std::atof(curLine.substr(0, firstSpaceIndex).c_str());
	int coordXIndex = curLine.find_first_not_of(SPACE, firstSpaceIndex);
	int secondSpaceIndex = curLine.find_first_of(SPACE, coordXIndex);
	int coordYIndex = curLine.find_first_not_of(SPACE, secondSpaceIndex);
	coordX = std::atof(curLine.substr(coordXIndex, secondSpaceIndex - coordXIndex).c_str());
	coordY = std::atof(curLine.substr(coordYIndex, curLine.length() - coordYIndex).c_str());
}

double OutlineFileHelper::getStartPos() {
	return m_outlineStartMeter;
}

double OutlineFileHelper::getEndPos() {
	return m_outlineEndMeter;
}

double OutlineFileHelper::getCurrentPos() {
	return m_currentOutlineMeter;
}