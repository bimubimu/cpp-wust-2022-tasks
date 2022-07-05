#pragma once
#include<cstdlib>
#include<iostream>
using namespace std;

template <typename T>
struct OLNode {
	//矩阵中元素行、列、值以及指针域
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

	void init(int row, int column);  //初始化行列信息
	void destroy();  
	int getRows() const; //获得行
	int getCols() const; //获得列
	void setData(int row, int col, T value); //设置值
	void setZero(int row, int col);  //置0即释放该位置内存
	T getData(int row, int col); //得到值
	void eraseRow(int row); //删除行
	void eraseCol(int col); //删除列

	KMatrix<T>* operator+(const KMatrix<T>& other);
	KMatrix<T>& operator+=(const KMatrix<T>& other);
	KMatrix<T>* operator-(const KMatrix<T>& other);
	KMatrix<T>& operator-=(const KMatrix<T>& other);
	KMatrix<T>* operator*(const KMatrix<T>& other);
	KMatrix<T>* dotMul(const KMatrix<T>& other);   //点乘
	void transpose();   //转置
	void print() const;    //输出

private:
	OLNode<T>** m_rHead;   //行链表指针
	OLNode<T>** m_cHead;   //列链表指针
	int m_mu, m_nu;  //行数 列数
};



