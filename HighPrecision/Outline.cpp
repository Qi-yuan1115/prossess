#include "stdafx.h"
#include "Outline.h"

void Outline::addPoint(double x, double y) {
	m_coordinateX.push_back(x);
	m_coordinateY.push_back(y);
	m_pointNum = m_coordinateX.size();
}

bool Outline::isEmpty() {
	return m_pointNum <= 0;
}
