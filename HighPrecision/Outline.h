#pragma once
#include <vector>
/*
�洢����
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

