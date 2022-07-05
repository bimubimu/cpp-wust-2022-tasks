#pragma once
#include"shape.h"

class Round :public Shape
{
public:
	Round(double radius) : m_radius(radius) {
		if (radius <= 0)
			throw ErrorInfo{ __FILE__, __LINE__ };
	}
	virtual ~Round() {}

	virtual double perimeter() const
	{
		return 2 * 3.14159 * m_radius;
	}

	virtual double area() const
	{
		return 3.14159 * m_radius * m_radius;
	}

	virtual void shapeType() const
	{
		cout << "Բ ";
	}

private:
	double m_radius;
};