// -------------------------------------------------------
// ksostring.h
// �����ߣ� ����ܲ
// ����ʱ�䣺 2022/5/2
// ���������� ����������
// Copyright 2022 by ����ܲ
// --------------------------------------------------------

#pragma once
#include<iostream>
#include <locale>
#include<cstddef>
using namespace std;
typedef wchar_t WCHAR;

template<typename T>
struct LinkNode {
	T m_data;
	LinkNode<T>* m_next;
	LinkNode() {}    
	LinkNode(T x) : m_data(x), m_next(nullptr){}
	LinkNode(T x, T* next) : m_data(x), m_next(next){}
};

template<typename T>
class KsoString
{	
	//Ϊ����ģ����ʵ���ض�����
	//��һ�ַ�����ʹ�÷�char, WCHAR����ʱ���ڱ����ڲ�ͨ������ʾ������Ϣ  
	//static_assert(std::is_same<T, char>::value || std::is_same<T, WCHAR>::value,
	//	"T type is not the specified DataType including char and WCHAR");

public:
	KsoString();
	KsoString(const KsoString<T>& obj);
	KsoString& operator=(const KsoString& obj);
	~KsoString();

	bool empty() { return m_length == 0; }
	int size() { return m_length; }
	void show();
	void append(KsoString<T>* obj);  //ͨ�����еĶ�����չ�����Ҳ��ı����
	void append(const T ch);  //׷���ַ�
	void append(const T ch[]);  //׷���ַ���
	void insert(const T ch, int index);
	void erase(int index);
	T operator[](const int index);

private:
	LinkNode<T>* m_head;
	LinkNode<T>* m_tail;
	int m_length;
};

