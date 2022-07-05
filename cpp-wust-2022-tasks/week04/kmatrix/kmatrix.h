#pragma once
#include<cstdlib>
#include<iostream>
using namespace std;

template <typename T>
struct OLNode {
	//������Ԫ���С��С�ֵ�Լ�ָ����
	int row, column;                        
	T elem;                            
	struct OLNode<T>* right;
	struct OLNode<T>* down;
};


template <typename T>
class KMatrix
{
public:
	KMatrix();
	KMatrix(int row, int column);
	KMatrix(const KMatrix<T>& other);
	KMatrix<T>& operator=(const KMatrix<T>& other);
	~KMatrix();

	void init(int row, int column);  //��ʼ��������Ϣ
	void destroy();  
	int getRows() const; //�����
	int getCols() const; //�����
	void setData(int row, int col, T value); //����ֵ
	void setZero(int row, int col);  //��0���ͷŸ�λ���ڴ�
	T getData(int row, int col); //�õ�ֵ
	void eraseRow(int row); //ɾ����
	void eraseCol(int col); //ɾ����

	KMatrix<T>* operator+(const KMatrix<T>& other);
	KMatrix<T>& operator+=(const KMatrix<T>& other);
	KMatrix<T>* operator-(const KMatrix<T>& other);
	KMatrix<T>& operator-=(const KMatrix<T>& other);
	KMatrix<T>* operator*(const KMatrix<T>& other);
	KMatrix<T>* dotMul(const KMatrix<T>& other);   //���
	void transpose();   //ת��
	void print() const;    //���

private:
	OLNode<T>** m_rHead;   //������ָ��
	OLNode<T>** m_cHead;   //������ָ��
	int m_mu, m_nu;  //���� ����
};



