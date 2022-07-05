#include"compoundshape.h"

void test() {
	Triangle triangle(3, 4, 5);
	triangle.shapeType();
	cout << triangle.perimeter() << ' ' << triangle.area() << endl;

	Square square(2.2);
	square.shapeType();
	cout << square.perimeter() << ' ' << square.area() << endl;

	Rectangle rectangle(4, 5);
	rectangle.shapeType();
	cout << rectangle.perimeter() << ' ' << rectangle.area() << endl;

	Trapezium trapezium(6, 12, 6, 6);
	trapezium.shapeType();
	cout << trapezium.perimeter() << ' ' << trapezium.area() << endl;

	Round round(2);
	round.shapeType();
	cout << round.perimeter() << ' ' << round.area() << endl;

	//Round round1(0);   //�����������߼�����״��������׳��쳣����ʾ������Ϣ���������
	//round1.shapeType();
	//cout << round1.perimeter() << ' ' << round1.area() << endl;

	CompoundShape compoundshape1;
	CompoundShape* compoundshape2 = new CompoundShape;

	compoundshape1.add(&triangle);
	compoundshape2->add(&square);

	compoundshape1.add(compoundshape2);
	compoundshape1.shapeType();
	cout << compoundshape1.perimeter() << ' ' << compoundshape1.area() << endl;
	delete compoundshape2;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	try {
		test();
	}
	catch (ErrorInfo info) {
		cout << "�������´���:" << endl;
		cout << info.first << "(" << info.second << ")   " << "��������״�Ĳ��������߼�" << endl;
		return 0;
	}
	return 0;
}