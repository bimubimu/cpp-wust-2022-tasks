#pragma once
#include<list>
#include"triangle.h"
#include"square.h"
#include"rectangle.h"
#include"trapezium.h"
#include"round.h"

class CompoundShape : public Shape {
public:
	CompoundShape() { m_num = 0; }
	virtual ~CompoundShape() {}

	void add(Shape* shape) {
		if (shape != nullptr) {
			m_listShape.push_back(shape);
			m_num ++;
		}
	}

	void remove(Shape* shape) {
		if (m_num != 0)
			for (auto iter = m_listShape.begin(); iter != m_listShape.end(); ) {
				if ((*iter) == shape) {
					m_listShape.erase(iter++);
					m_num--;
				}
				else
					iter++;
			}
	}

	virtual double perimeter() const{
		double perimeter = 0;
		for (auto iter = m_listShape.begin(); iter != m_listShape.end(); iter++) 
			perimeter += (*iter)->perimeter();
		return perimeter;
	}

	virtual double area() const{
		double area = 0;
		for (auto iter = m_listShape.begin(); iter != m_listShape.end(); iter++) 
			area += (*iter)->area();
		
		return area;
	}

	virtual void shapeType() const {
		cout << "¸´ºÏÐÎ×´[";
		if (m_num != 0)
			for (auto iter = m_listShape.begin(); iter != m_listShape.end(); iter++) 
				if ((*iter) != nullptr)
					(*iter)->shapeType();	
		cout << ']';
	}

private:	
	list<Shape*> m_listShape;
	int m_num;
};
