#pragma once
#include"shape.h"

class Triangle :public Shape {
public:
	Triangle(double sideA, double sideB, double sideC) : m_sideA(sideA), m_sideB(sideB), m_sideC(sideC) {
		if (sideA <= 0 || sideB <= 0 || sideC <= 0 || 
			sideA + sideB <= sideC ||
			sideA + sideC <= sideB ||
			sideB + sideC <= sideA)
			throw ErrorInfo{__FILE__, __LINE__};
	}
	virtual ~Triangle() {}

	virtual double perimeter() const
	{
		return m_sideA + m_sideB + m_sideC;
	}

	virtual double area() const
	{
		double p = perimeter() / 2;
		return sqrt(p * (p - m_sideA) * (p - m_sideB) * (p - m_sideC));
	}

	virtual void shapeType() const
	{
		cout << "Èý½ÇÐÎ ";
	}

private:
	double m_sideA, m_sideB, m_sideC;
};
