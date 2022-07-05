#include<iostream>
#include"KLinkSolution.h"
using namespace std;

//��ת������������ǰһ��β���ָ����鷭ת���ͷ���
LinkNode* Solve(LinkNode* preTail, LinkNode* curHead, size_t reverseIndex) {
    LinkNode* pre = nullptr;
    LinkNode* cur = curHead;
    LinkNode* test = curHead;
    for (size_t i = 0; i < reverseIndex; i++) {
        //����ǰ��ڵ����С��k���÷�ת��ֱ�ӽ�ǰһ��β���ָ�����ͷ��㣬�ҷ��ؿ�ָ��
        if (test == nullptr) {
            preTail->next = curHead;
            return nullptr;
        }
        test = test->next;
    }
    //ʵ��ÿ������ת
    for (size_t i = 0; i < reverseIndex; i++) {
        //����ýڵ����������һ���ڵ㣬���Ӻ󷵻ؿ�ָ�룬��ת���
        if (cur->next == nullptr) {
            cur->next = pre;
            if (preTail != nullptr)
                preTail->next = cur;
            return nullptr;
        }
        LinkNode* next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;   //ָ����һ��ͷ���
        //����ýڵ��Ǹ������һ���ڵ㣬������һ��ͷ���
        if (i == reverseIndex - 1) {
            if (preTail != nullptr)
                preTail->next = pre;
            return cur;
        }
    }
    return nullptr;
}

//��Ϊ���д���ָ���Ա�������������ؿ������캯��ʵ�����
KLinkSolution::KLinkSolution(const KLinkSolution& obj) {
    m_head = new LinkNode(obj.m_head->val);
    LinkNode* p1 = obj.m_head;
    LinkNode* p2 = m_head;
    while (p1->next != nullptr) {
        //���ò�������ڵ��ֵ�����µĽڵ㣬������Щ�ڵ㴮��
        p2->next = new LinkNode(p1->next->val);
        p1 = p1->next;
        p2 = p2->next;
    }
}

KLinkSolution::~KLinkSolution() {
    LinkNode* temp = nullptr;
    //�����ǰ�����������������ÿ���ڵ�Ŀռ�
    while (m_head != nullptr) {
        temp = m_head->next;
        delete m_head;
        m_head = temp;
    }
    delete m_head;
}

void KLinkSolution::init(size_t numNode) {
    int newNodeVal = 0;
    cin >> newNodeVal;
    LinkNode* pTemp = m_head = new LinkNode(newNodeVal);
    for (int i = 1; i < numNode; i++) {
        cin >> newNodeVal;
        pTemp->next = new LinkNode(newNodeVal);
        pTemp = pTemp->next;
    }
}

//��ת�����Ļ���˼·Ϊ�������鷭ת��Ȼ��ÿ��ǰ����Ӵ������µ�����
LinkNode* KLinkSolution::reverseKGroup(size_t reverseIndex) {
    LinkNode* curHead = m_head;   //curHead��¼��ǰ���ͷ��� 
    LinkNode* preTail = nullptr;   //preTail��¼ǰһ���β���
    //��m_headָ��ת�������ͷ
    for (size_t i = 0; i < reverseIndex - 1; i++) {
        m_head = m_head->next;
    }
    while (curHead != nullptr) {  //û����һ��ʱ����ѭ�� 
        LinkNode* tmp = curHead;   //��¼����ͷ��㣬��ת���Ϊβ���������һ��
        curHead = Solve(preTail, curHead, reverseIndex);  //��������ֵΪ��һ��ͷ���
        preTail = tmp;
    }
    return m_head;
}

//�����������ڵ��ֵ
void KLinkSolution::showLinkList() {
    LinkNode* p = m_head;
    //ָ��pָ��ͷ��㣬Ȼ���ж�p�Ƿ�Ϊ��ָ�룬����Ϊ��������ڵ��ֵ��Ȼ��ָ�����
    while (p != nullptr) {
        cout << p->val << ' ';
        p = p->next;
    }
    cout << endl;
}