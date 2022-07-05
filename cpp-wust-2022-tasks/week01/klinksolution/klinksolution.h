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
    KLinkSolution(const KLinkSolution& obj); //拷贝构造函数
    ~KLinkSolution();
    void init(size_t numNode);   //初始化
    LinkNode* reverseKGroup(size_t reverseIndex);  //翻转链表
    void showLinkList();  //输出链表
private:
    LinkNode* m_head;
};