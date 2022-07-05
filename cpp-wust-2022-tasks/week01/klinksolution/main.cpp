#include<iostream>
#include"klinksolution.h"
using namespace std;

int main() {
    //测试结果：
    //5                        
    //1 2 3 4 5
    //原链表: 1 2 3 4 5
    //3
    //翻转后 : 3 2 1 4 5

    //5
    //1 2 3 4 5
    //原链表: 1 2 3 4 5
    //5
    //翻转后 : 5 4 3 2 1

    size_t numNode = 0;  //n代表要构造的链表节点个数
    cout << "输入链表长度:";
    cin >> numNode;
    KLinkSolution testLinkList;  //构造链表 
    cout << "输入链表各节点值:";
    testLinkList.init(numNode);  //初始化
    cout << "原链表: ";
    testLinkList.showLinkList();
    size_t reverseIndex = 0;  //reverseIndex为翻转链表参数
    cin >> reverseIndex;
    testLinkList.reverseKGroup(reverseIndex);  //翻转链表
    cout << "翻转后: ";
    testLinkList.showLinkList();
    return 0;
}
