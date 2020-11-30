#pragma once
#include <vector>
/*
´æ´¢ÂÖÀª
*/
class Outline
{
public:
	void addPoint(double x, double y);
	bool isEmpty();

public:
	std::vector<double> m_coordinateX;
	std::vector<double> m_coordinateY;
	int m_pointNum;
};

