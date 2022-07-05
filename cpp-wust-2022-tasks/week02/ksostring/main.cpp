// -------------------------------------------------------
// main.cpp
// �����ߣ� ����ܲ
// ����ʱ�䣺 2022/5/2
// ���������� �Դ��������Ļ������ܲ���
// Copyright 2022 by ����ܲ
// --------------------------------------------------------

#include"ksostring.h"
#include<regex>

const int g_strLength = 50;

bool IsNumber(string str) {   //�ж������Ƿ�Ϊ����
	if (str.size() > 1 && str[0] == '0' || str.size() == 0) 
		return false;
	for (int i = 0; i < str.size(); i++)
	{
		int tmp = (int)str[i];
		if (tmp >= 48 && tmp <= 57)
			continue;
		else
			return false;
	}
	return true;
}

int GetValidNumber() {     //�õ���Ч����������
	string str;
	getline(cin, str);
	while (str.size() > 9 || !IsNumber(str)) {
		cout << "������Ϸ��Ǹ�����:";
		getline(cin, str);
	}
	return stoi(str);
}

char GetValidChar() {     //�õ���Ч���ַ�����
	string str;
	getline(cin, str);
	while (str.size() > 1) {
		cout << "������Ϸ��ַ�:";
		getline(cin, str);
	}
	return str[0];
}

WCHAR GetValidWCHAR() {     //�õ���Ч�Ŀ��ַ�����
	wstring str;
	wcin >> str;
	while (str.size() > 1) {
		cout << "������Ϸ��ַ�:";
		wcin >> str;
	}
	return str[0];
}

void CharTest() {
	KsoString<char> charTest;
	int flag = 1;
	while (flag) {
		cout << endl << endl << "---------------------------------------------------------" << endl;
		cout << "charTest:";
		charTest.show();
		cout << "�ַ�������" << charTest.size() << endl;
		cout << "1.�����ַ� 2.ɾ���ַ� 3.�����ַ� 4.���� 5.׷���ַ� 6.׷���ַ��� 0.�˳�" << endl;
		cout << "���������:";

		int choose = GetValidNumber();
		switch (choose) {
		case 1: {
			cout << "�����±�:";
			int index = GetValidNumber();
			while (index < 0 || index > charTest.size()) {
				cout << "�±겻�Ϸ�����������:";
				index = GetValidNumber();
			}

			cout << "�����ַ���";
			char ch = GetValidChar();
			charTest.insert(ch, index);
			break;
		}

		case 2: {
			cout << "�����±꣺";
			int index = GetValidNumber();
			while (index < 0 || index > charTest.size() - 1) {
				cout << "�±겻�Ϸ�����������:";
				index = GetValidNumber();
			}
			charTest.erase(index);
			break;
		}

		case 3: {
			cout << "��������±꣺";
			int index = GetValidNumber();
			while (index < 0 || index > charTest.size() - 1) {
				cout << "�±겻�Ϸ����������룺";
				index = GetValidNumber();
			}
			cout << "��������ַ���";
			char ch = GetValidChar();
			charTest.erase(index);
			charTest.insert(ch, index);
			break;
		}

		case 4: {   
			cout << "��������±꣺";
			int index = GetValidNumber();
			//�����±겻�Ϸ���Ҫ���������룬��Ϊ����ö���Ϊ�ղ��һ�һֱʧ��
			if (index < 0 || index > charTest.size() - 1)
				cout << "�±겻�Ϸ�" << endl;
			else
				cout << "���ҽ����" << charTest[index] << endl;
			break;
		}

		case 5: {
			cout << "�����ַ�:";
			char ch = GetValidChar();
			charTest.append(ch);
			break;
		}

		case 6: {
			int check = 1;
			cout << "�����ַ�����";
			char ch[g_strLength];
			string str;
			getline(cin, str);
			while (str.size() == 0 || str.size() > g_strLength - 1) {
				cout << "�ַ������Ȳ��Ϸ�����������:";
				getline(cin, str);
			}
			int i = 0;
			for (; i < str.size(); i++) {
				ch[i] = str[i];
				if ((i < str.size() - 1) && (ch[i] & 0x80) && (ch[i + 1] & 0x80)) {
					cout << "�ַ��������ֽ��ַ����������";  
					check = 0;
					break;
				}
			}
			if (check) {
				ch[i] = '\0';
				charTest.append(ch);
			}
			break;
		}

		case 0:
			flag = 0;
			break;

		default:
			cout << "�Ƿ�������������룡" << endl;
			break;
		}
	}
}

void WCHARTest() {
	KsoString<WCHAR> wcharTest;
	int flag = 1;
	int noUse = 0;   
	while (flag) {
		cout << endl << endl << "---------------------------------------------------------" << endl;
		cout << "wchartest:";
		wcharTest.show();
		cout << "�ַ�������" << wcharTest.size() << endl;
		cout << "1.�����ַ� 2.ɾ���ַ� 3.�����ַ� 4.���� 5.׷���ַ� 6.׷���ַ��� 0.�˳�" << endl;
		cout << "���������:";

		int choose = GetValidNumber();
		switch (choose) {
		case 1: {
			cout << "�����±�:";
			int index = GetValidNumber();
			while (index < 0 || index > wcharTest.size()) {
				cout << "�±겻�Ϸ�����������:";
				index = GetValidNumber();
			}

			cout << "�����ַ���";
			WCHAR ch = GetValidWCHAR();
			wcharTest.insert(ch, index);
			noUse = getchar();  //��ֹ���з������룬����ͬ��
			break;
		}

		case 2: {
			cout << "�����±꣺";
			int index = GetValidNumber();
			while (index < 0 || index > wcharTest.size() - 1) {
				cout << "�±겻�Ϸ�����������:";
				index = GetValidNumber();
			}
			wcharTest.erase(index);
			break;
		}

		case 3: {
			cout << "��������±꣺";
			int index = GetValidNumber();
			while (index < 0 || index > wcharTest.size() - 1) {
				cout << "�±겻�Ϸ����������룺";
				index = GetValidNumber();
			}
			cout << "��������ַ���";
			WCHAR ch = GetValidWCHAR();
			wcharTest.erase(index);
			wcharTest.insert(ch, index);
			noUse = getchar();
			break;
		}

		case 4: {  
			cout << "��������±꣺";
			int index = GetValidNumber();
			//�����±겻�Ϸ���Ҫ���������룬��Ϊ����ö���Ϊ�ղ��һ�һֱʧ��
			if (index < 0 || index > wcharTest.size() - 1)
				cout << "�±겻�Ϸ�" << endl;
			else
				wcout << L"���ҽ����" << wcharTest[index] << endl;
			break;
		}

		case 5: {
			cout << "�����ַ�:";
			WCHAR ch = GetValidWCHAR();
			wcharTest.append(ch);
			noUse = getchar();
			break;
		}

		case 6: {     
			cout << "�����ַ�����";
			WCHAR ch[g_strLength];
			wstring str;
			wcin >> str;
			while (str.size() == 0 || str.size() > g_strLength - 1) {
				cout << "�ַ������Ȳ��Ϸ�����������:";
				wcin >> str;
			}
			int i = 0;
			for (; i < str.size(); i++) 
				ch[i] = str[i];
			
			ch[i] = '\0\0'; 
			wcharTest.append(ch);
			noUse = getchar();
			break;
		}

		case 0:
			flag = 0;
			break;

		default:
			cout << "�Ƿ�������������룡" << endl;
			break;
		}

	}
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);  //����ڴ�й©
	setlocale(LC_ALL, "chs");   //�����ַ����뻷����ʹWCHAR����ʾ����

	//��ksostring��ֻʵ������char��WCHAR���ͣ��������ͷ����������ᱨ��,��:
	//KsoString<int>* p = new KsoString<int>;

	int flag = 1;
	while (flag) {
		cout << endl << endl << "---------------------------------------------------------" << endl;
		cout << "�������ܲ���";
		cout << "1.char  2.WCHAR  0.�˳�" << endl;
		cout << "ѡ���������:";
		
		int choose = GetValidNumber();

		switch (choose) {
		case 1: 
			CharTest();
			break;

		case 2:
			WCHARTest();
			break;

		case 0:
			flag = 0;
			break;

		default:
			cout << "�Ƿ�������������룡" << endl;
			break;
		}
	}
	return 0;
}