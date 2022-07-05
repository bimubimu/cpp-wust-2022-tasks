#pragma once
#include"shape.h"

class Trapezium :public Shape {
public:
	Trapezium(double top, double bottom, double left, double right)
		: m_top(top), m_bottom(bottom), m_left(left), m_right(right) {
		if (top <= 0 || bottom <= 0 || left <= 0 || right <= 0 || top >= bottom ||
			left + right <= bottom - top || abs(left - right) >= bottom - top)   //������>���ײ������<���ײ�
			throw ErrorInfo{ __FILE__, __LINE__ };
	}
	virtual ~Trapezium() {}
	virtual double perimeter() const
	{
		return m_top + m_bottom + m_left + m_right;
	}

	virtual double area() const
	{
		//�����ε��������κ�ƽ���ı��ε���������
		double p = ((m_bottom - m_top) + m_left + m_right) / 2;
		double triangleArea = sqrt(p * (p - m_left) * (p - m_right) * (p - (m_bottom - m_top)));
		double height = 2 * triangleArea / (m_bottom - m_top);
		double parallelogramArea = m_top * height;
		return triangleArea + parallelogramArea;
	}

	virtual void shapeType() const
	{
		cout << "���� ";
	}

private:
	double m_top, m_bottom, m_left, m_right;
};