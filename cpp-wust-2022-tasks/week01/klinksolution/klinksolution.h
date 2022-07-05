#pragma once

struct LinkNode {
    int val;
    LinkNode* next;
    LinkNode() : val(0), next(nullptr) {}
    LinkNode(int x) : val(x), next(nullptr) {}
    LinkNode(int x, LinkNode* next) : val(x), next(next) {}
};

class KLinkSolution {
public:
    KLinkSolution() : m_head(nullptr) {}
    KLinkSolution(const KLinkSolution& obj); //�������캯��
    ~KLinkSolution();
    void init(size_t numNode);   //��ʼ��
    LinkNode* reverseKGroup(size_t reverseIndex);  //��ת����
    void showLinkList();  //�������
private:
    LinkNode* m_head;
};