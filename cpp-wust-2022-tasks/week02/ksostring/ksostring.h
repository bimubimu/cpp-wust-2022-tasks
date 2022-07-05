// -------------------------------------------------------
// ksostring.h
// 创建者： 王子懿
// 创建时间： 2022/5/2
// 功能描述： 容器类声明
// Copyright 2022 by 王子懿
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
	//为了让模板类实现特定类型
	//第一种方法：使用非char, WCHAR类型时会在编译期不通过，提示错误信息  
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
	void append(KsoString<T>* obj);  //通过已有的对象扩展，并且不改变对象
	void append(const T ch);  //追加字符
	void append(const T ch[]);  //追加字符串
	void insert(const T ch, int index);
	void erase(int index);
	T operator[](const int index);

private:
	LinkNode<T>* m_head;
	LinkNode<T>* m_tail;
	int m_length;
};

