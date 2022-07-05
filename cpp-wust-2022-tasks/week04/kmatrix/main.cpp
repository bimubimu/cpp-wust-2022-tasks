#include"kmatrix.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//������������
	KMatrix<int> matrixA(3, 3);
	matrixA.setData(1, 1, 1);
	matrixA.setData(2, 2, 2);
	matrixA.setData(3, 3, 3);
	cout << "����A: ����" << matrixA.getRows() << " ����" << matrixA.getCols() << endl;
	matrixA.print();
	cout << endl;

	KMatrix<int> matrixB(3, 3);
	matrixB.setData(1, 2, 1);
	matrixB.setData(2, 2, 2);
	matrixB.setData(3, 2, 5);
	matrixB.setData(3, 3, 3);
	cout << "����B: ����" << matrixB.getRows() << " ����" << matrixB.getCols() << endl;
	matrixB.print();
	cout << endl;

	KMatrix<int>* matrixC;
	cout << "C = A + B:" << endl;
	matrixC = matrixA + matrixB;
	matrixC->print();
	cout << endl;	

	KMatrix<int>* matrixD;
	cout << "D = A - B:" << endl;
	matrixD = matrixA - matrixB;
	matrixD->print();
	cout << endl;

	KMatrix<int>* matrixE;
	cout << "E = A * B:" << endl;
	matrixE = matrixA * matrixB;
	matrixE->print();
	cout << endl;

	KMatrix<int>* matrixF;
	cout << "F = A * B(���):" << endl;
	matrixF = matrixA.dotMul(matrixB);
	matrixF->print();
	cout << endl;

	cout << "Eת�ã�" << endl;
	matrixE->transpose();
	matrixE->print();
	cout << endl;

	cout << "Eɾ����һ�У�" << endl;
	matrixE->eraseCol(1);
	matrixE->print();
	cout << endl;

	cout << "Eɾ���ڶ��У�" << endl;
	matrixE->eraseRow(2);
	matrixE->print();
	cout << endl;

	cout << "A += B:" << endl;
	matrixA += matrixB;
	matrixA.print();
	cout << endl;

	cout << "A -= B:" << endl;
	matrixA -= matrixB;
	matrixA.print();
	cout << endl;

	delete matrixC;
	delete matrixD;
	delete matrixE;
	delete matrixF;
	return 0;
}