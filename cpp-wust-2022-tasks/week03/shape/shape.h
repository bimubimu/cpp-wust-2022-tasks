#pragma once
#include<iostream>
#include<cmath>
using namespace std;

typedef pair<string, int> ErrorInfo;

class Shape {
public:
	virtual ~Shape() {}
	virtual double perimeter() const = 0;
	virtual double area() const = 0;
	virtual void shapeType() const = 0;
};
