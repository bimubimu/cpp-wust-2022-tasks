#include<iostream>
#include"klinksolution.h"
using namespace std;

int main() {
    //���Խ����
    //5                        
    //1 2 3 4 5
    //ԭ����: 1 2 3 4 5
    //3
    //��ת�� : 3 2 1 4 5

    //5
    //1 2 3 4 5
    //ԭ����: 1 2 3 4 5
    //5
    //��ת�� : 5 4 3 2 1

    size_t numNode = 0;  //n����Ҫ���������ڵ����
    cout << "����������:";
    cin >> numNode;
    KLinkSolution testLinkList;  //�������� 
    cout << "����������ڵ�ֵ:";
    testLinkList.init(numNode);  //��ʼ��
    cout << "ԭ����: ";
    testLinkList.showLinkList();
    size_t reverseIndex = 0;  //reverseIndexΪ��ת�������
    cin >> reverseIndex;
    testLinkList.reverseKGroup(reverseIndex);  //��ת����
    cout << "��ת��: ";
    testLinkList.showLinkList();
    return 0;
}
