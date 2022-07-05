// -------------------------------------------------------
// ksostring.cpp
// 创建者： 王子懿
// 创建时间： 2022/5/2
// 功能描述： 容器类定义
// Copyright 2022 by 王子懿
// --------------------------------------------------------

#include"ksostring.h"
//模板未实例化时不会单独编译.cpp

//此处构造函数必须在ksostring.cpp中定义，防止构建非法类型容器
template<typename T>
KsoString<T>::KsoString() : m_head(nullptr), m_tail(nullptr), m_length(0) {}

template<typename T>
KsoString<T>::KsoString(const KsoString<T>& obj) {   //拷贝构造
	m_length = obj.m_length;  
	if (m_length == 0) {
		m_head = nullptr;
		m_tail = nullptr;
		return;
	}

	m_head = new LinkNode<T>(obj.m_head->m_data);
	m_tail = m_head;
	LinkNode<T>* objTemp = obj.m_head->m_next;

	while (objTemp != nullptr) {
		m_tail->m_next = new LinkNode<T>(objTemp->m_data);
		m_tail = m_tail->m_next;
		objTemp = objTemp->m_next;
	}
}

template<typename T>
KsoString<T>& KsoString<T>::operator=(const KsoString<T>& obj) {  //赋值构造   
	if (this == &obj)  //自身对自身赋值时直接返回
		return *this;

	while (m_head != nullptr) {  //自身不为空时需要清除自身元素
		LinkNode<T>* temp = m_head->m_next;
		delete m_head;
		m_head = temp;
	}

	m_length = obj.m_length;  //赋值对象为空直接返回自身
	if (m_length == 0)
		return *this;

	m_head = new LinkNode<T>(obj.m_head->m_data);
	m_tail = m_head;
	LinkNode<T>* objTemp = obj.m_head->m_next;

	while (objTemp != nullptr) {
		m_tail->m_next = new LinkNode<T>(objTemp->m_data);
		m_tail = m_tail->m_next;
		objTemp = objTemp->m_next;
	}
	return *this;
}

template<typename T>
KsoString<T>::~KsoString() {  
	if (m_head == nullptr)
		return;
	while (m_head != m_tail) {
		LinkNode<T>* temp = m_head->m_next;
		delete m_head;
		m_head = temp;
	}
	delete m_head;
}

template<typename T>
void KsoString<T>::show() {    //输出所有节点值
	LinkNode<T>* temp = m_head;
	while (temp != nullptr) {
		wcout << temp->m_data;
		temp = temp->m_next;
	}
	cout << endl;
	return;
}

template<typename T>
void KsoString<T>::append(KsoString<T>* obj) {  //追加对象的字符，并且不改变原对象
	if (obj->m_length == 0)
		return;

	LinkNode<T>* temp = obj->m_head;
	if (m_head == nullptr) {
		m_head = new LinkNode<T>(temp->m_data);
		m_tail = m_head;
		temp = temp->m_next;
	}

	while (temp != nullptr) {
		m_tail->m_next = new LinkNode<T>(temp->m_data);
		m_tail = m_tail->m_next;
		temp = temp->m_next;
	}
	m_length += obj->m_length;
}

template<typename T>
void KsoString<T>::append(const T ch) {  //追加单个字符
	if (m_head == nullptr) {
		m_head = new LinkNode<T>(ch);
		m_tail = m_head;
	}
	else {
		m_tail->m_next = new LinkNode<T>(ch);
		m_tail = m_tail->m_next;
	}
	m_length++;
}

template<typename T>
void KsoString<T>::append(const T ch[]) {   //追加字符数组
	int cnt = 0;
	if (m_head == nullptr) {
		if (ch[cnt] == '\0')
			return;
		m_head = new LinkNode<T>(ch[cnt]);
		m_tail = m_head;
		cnt++;
	}

	while (ch[cnt] != '\0') {
		m_tail->m_next = new LinkNode<T>(ch[cnt]);
		m_tail = m_tail->m_next;
		cnt++;
	}
	m_length += cnt;
}

template<typename T>
void KsoString<T>::insert(const T ch, int index) {
	while (index > m_length || index < 0) {
		cout << "插入位置不合法，重新输入:";
		cin >> index;
	}

	LinkNode<T>* insertNode = new LinkNode<T>(ch);  //为字符创建新的节点
	if (index == 0) {   
		insertNode->m_next = m_head;
		m_head = insertNode;
	}
	else {
		LinkNode<T>* temp = m_head;  
		for (int i = 1; i < index; i++)   //找到要插入位置的前一个节点 
			temp = temp->m_next;

		insertNode->m_next = temp->m_next;
		temp->m_next = insertNode;
	}

	//在容器尾部插入是要挪动尾指针
	if (index == m_length)
		m_tail = insertNode;
	m_length++;   //更新节点个数
}

template<typename T>
void KsoString<T>::erase(int index) {
	while (index > m_length - 1 || index < 0) {
		cout << "删除位置不合法，重新输入:";
		cin >> index;
	}

	LinkNode<T>* eraseNode = m_head;     //指向要删除的节点
	LinkNode<T>* erasePreNode = nullptr; //指向要删除节点的前一个节点

	for (int i = 0; i < index; i++) {
		if (i == 0)
			erasePreNode = m_head;
		else
			erasePreNode = erasePreNode->m_next;
		eraseNode = eraseNode->m_next;
	}

	//删除第一个节点时头指针往后挪动
	if (erasePreNode == nullptr)
		if(m_head != nullptr)
			m_head = m_head->m_next;         
	if(erasePreNode != nullptr)
		erasePreNode->m_next = eraseNode->m_next;

	delete eraseNode;

	//删除节点为最后一个节点时挪动尾指针
	if (index == m_length - 1)
		m_tail = erasePreNode;
	m_length--;
}

template<typename T>
T KsoString<T>::operator[](const int index) {
	//索引不合法时返回0
	if (index > m_length - 1 || index < 0)
		return 0;

	LinkNode<T>* temp = m_head;
	for (int i = 0; i < index; i++) {
		temp = temp->m_next;
	}
	return temp->m_data;
}

//第二种方法：显示实例化也可以让模板类实现特定类型,并且可以做到类的声明与定义分离
template class KsoString<char>;
template class KsoString<WCHAR>;
