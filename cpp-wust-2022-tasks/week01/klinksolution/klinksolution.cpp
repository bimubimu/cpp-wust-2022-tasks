#include<iostream>
#include"KLinkSolution.h"
using namespace std;

//翻转改组链表，并将前一组尾结点指向改组翻转后的头结点
LinkNode* Solve(LinkNode* preTail, LinkNode* curHead, size_t reverseIndex) {
    LinkNode* pre = nullptr;
    LinkNode* cur = curHead;
    LinkNode* test = curHead;
    for (size_t i = 0; i < reverseIndex; i++) {
        //若当前组节点个数小于k则不用翻转，直接将前一组尾结点指向改组头结点，且返回空指针
        if (test == nullptr) {
            preTail->next = curHead;
            return nullptr;
        }
        test = test->next;
    }
    //实现每组链表翻转
    for (size_t i = 0; i < reverseIndex; i++) {
        //如果该节点是整个最后一个节点，连接后返回空指针，翻转完成
        if (cur->next == nullptr) {
            cur->next = pre;
            if (preTail != nullptr)
                preTail->next = cur;
            return nullptr;
        }
        LinkNode* next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;   //指向下一组头结点
        //如果该节点是该组最后一个节点，返回下一组头结点
        if (i == reverseIndex - 1) {
            if (preTail != nullptr)
                preTail->next = pre;
            return cur;
        }
    }
    return nullptr;
}

//因为类中带有指针成员变量，所以重载拷贝构造函数实现深拷贝
KLinkSolution::KLinkSolution(const KLinkSolution& obj) {
    m_head = new LinkNode(obj.m_head->val);
    LinkNode* p1 = obj.m_head;
    LinkNode* p2 = m_head;
    while (p1->next != nullptr) {
        //借用参数对象节点的值构造新的节点，并将这些节点串连
        p2->next = new LinkNode(p1->next->val);
        p1 = p1->next;
        p2 = p2->next;
    }
}

KLinkSolution::~KLinkSolution() {
    LinkNode* temp = nullptr;
    //链表从前往后遍历，依次销毁每个节点的空间
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

//翻转函数的基本思路为将链表按组翻转，然后将每组前后相接串连出新的链表
LinkNode* KLinkSolution::reverseKGroup(size_t reverseIndex) {
    LinkNode* curHead = m_head;   //curHead记录当前组的头结点 
    LinkNode* preTail = nullptr;   //preTail记录前一组的尾结点
    //将m_head指向翻转后的链表头
    for (size_t i = 0; i < reverseIndex - 1; i++) {
        m_head = m_head->next;
    }
    while (curHead != nullptr) {  //没有下一组时跳出循环 
        LinkNode* tmp = curHead;   //记录该组头结点，翻转后变为尾结点连接下一组
        curHead = Solve(preTail, curHead, reverseIndex);  //函数返回值为下一组头结点
        preTail = tmp;
    }
    return m_head;
}

//按序输出链表节点的值
void KLinkSolution::showLinkList() {
    LinkNode* p = m_head;
    //指针p指向头结点，然后判断p是否为空指针，若不为空则输出节点的值，然后指针后移
    while (p != nullptr) {
        cout << p->val << ' ';
        p = p->next;
    }
    cout << endl;
}