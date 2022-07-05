# 第一次作业
## 主要代码段
翻转函数的基本思路为将链表按组翻转，然后将每组前后相接串连出新的链表。  
本程序使用常数额外空间的算法来解决此问题，没有单纯改变节点内部的值，是进行了节点的交互。
```c++
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
```

```
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
```
## 运行效果
第一行输入要创建链表的节点个数  
第二行输入各个节点的值  
回车后显示我们创建的链表  
然后输入翻转参数  
回车后显示翻转后的链表
```
输入链表长度:5
输入链表各节点值:1 2 3 4 5
原链表: 1 2 3 4 5
2
翻转后: 2 1 4 3 5
```
```
输入链表长度:5
输入链表各节点值:1 2 3 4 5
原链表: 1 2 3 4 5
3
翻转后: 3 2 1 4 5
```


