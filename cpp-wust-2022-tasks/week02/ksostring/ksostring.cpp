// -------------------------------------------------------
// ksostring.cpp
// �����ߣ� ����ܲ
// ����ʱ�䣺 2022/5/2
// ���������� �����ඨ��
// Copyright 2022 by ����ܲ
// --------------------------------------------------------

#include"ksostring.h"
//ģ��δʵ����ʱ���ᵥ������.cpp

//�˴����캯��������ksostring.cpp�ж��壬��ֹ�����Ƿ���������
template<typename T>
KsoString<T>::KsoString() : m_head(nullptr), m_tail(nullptr), m_length(0) {}

template<typename T>
KsoString<T>::KsoString(const KsoString<T>& obj) {   //��������
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
KsoString<T>& KsoString<T>::operator=(const KsoString<T>& obj) {  //��ֵ����   
	if (this == &obj)  //���������ֵʱֱ�ӷ���
		return *this;

	while (m_head != nullptr) {  //����Ϊ��ʱ��Ҫ�������Ԫ��
		LinkNode<T>* temp = m_head->m_next;
		delete m_head;
		m_head = temp;
	}

	m_length = obj.m_length;  //��ֵ����Ϊ��ֱ�ӷ�������
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
void KsoString<T>::show() {    //������нڵ�ֵ
	LinkNode<T>* temp = m_head;
	while (temp != nullptr) {
		wcout << temp->m_data;
		temp = temp->m_next;
	}
	cout << endl;
	return;
}

template<typename T>
void KsoString<T>::append(KsoString<T>* obj) {  //׷�Ӷ�����ַ������Ҳ��ı�ԭ����
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
void KsoString<T>::append(const T ch) {  //׷�ӵ����ַ�
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
void KsoString<T>::append(const T ch[]) {   //׷���ַ�����
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
		cout << "����λ�ò��Ϸ�����������:";
		cin >> index;
	}

	LinkNode<T>* insertNode = new LinkNode<T>(ch);  //Ϊ�ַ������µĽڵ�
	if (index == 0) {   
		insertNode->m_next = m_head;
		m_head = insertNode;
	}
	else {
		LinkNode<T>* temp = m_head;  
		for (int i = 1; i < index; i++)   //�ҵ�Ҫ����λ�õ�ǰһ���ڵ� 
			temp = temp->m_next;

		insertNode->m_next = temp->m_next;
		temp->m_next = insertNode;
	}

	//������β��������ҪŲ��βָ��
	if (index == m_length)
		m_tail = insertNode;
	m_length++;   //���½ڵ����
}

template<typename T>
void KsoString<T>::erase(int index) {
	while (index > m_length - 1 || index < 0) {
		cout << "ɾ��λ�ò��Ϸ�����������:";
		cin >> index;
	}

	LinkNode<T>* eraseNode = m_head;     //ָ��Ҫɾ���Ľڵ�
	LinkNode<T>* erasePreNode = nullptr; //ָ��Ҫɾ���ڵ��ǰһ���ڵ�

	for (int i = 0; i < index; i++) {
		if (i == 0)
			erasePreNode = m_head;
		else
			erasePreNode = erasePreNode->m_next;
		eraseNode = eraseNode->m_next;
	}

	//ɾ����һ���ڵ�ʱͷָ������Ų��
	if (erasePreNode == nullptr)
		if(m_head != nullptr)
			m_head = m_head->m_next;         
	if(erasePreNode != nullptr)
		erasePreNode->m_next = eraseNode->m_next;

	delete eraseNode;

	//ɾ���ڵ�Ϊ���һ���ڵ�ʱŲ��βָ��
	if (index == m_length - 1)
		m_tail = erasePreNode;
	m_length--;
}

template<typename T>
T KsoString<T>::operator[](const int index) {
	//�������Ϸ�ʱ����0
	if (index > m_length - 1 || index < 0)
		return 0;

	LinkNode<T>* temp = m_head;
	for (int i = 0; i < index; i++) {
		temp = temp->m_next;
	}
	return temp->m_data;
}

//�ڶ��ַ�������ʾʵ����Ҳ������ģ����ʵ���ض�����,���ҿ���������������붨�����
template class KsoString<char>;
template class KsoString<WCHAR>;
