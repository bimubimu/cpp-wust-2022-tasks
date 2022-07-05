// -------------------------------------------------------
// main.cpp
// 创建者： 王子懿
// 创建时间： 2022/5/2
// 功能描述： 对创建容器的基本功能测试
// Copyright 2022 by 王子懿
// --------------------------------------------------------

#include"ksostring.h"
#include<regex>

const int g_strLength = 50;

bool IsNumber(string str) {   //判断输入是否为数字
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

int GetValidNumber() {     //得到有效的数字输入
	string str;
	getline(cin, str);
	while (str.size() > 9 || !IsNumber(str)) {
		cout << "请输入合法非负整数:";
		getline(cin, str);
	}
	return stoi(str);
}

char GetValidChar() {     //得到有效的字符输入
	string str;
	getline(cin, str);
	while (str.size() > 1) {
		cout << "请输入合法字符:";
		getline(cin, str);
	}
	return str[0];
}

WCHAR GetValidWCHAR() {     //得到有效的宽字符输入
	wstring str;
	wcin >> str;
	while (str.size() > 1) {
		cout << "请输入合法字符:";
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
		cout << "字符个数：" << charTest.size() << endl;
		cout << "1.插入字符 2.删除字符 3.更改字符 4.查找 5.追加字符 6.追加字符串 0.退出" << endl;
		cout << "输入操作项:";

		int choose = GetValidNumber();
		switch (choose) {
		case 1: {
			cout << "输入下标:";
			int index = GetValidNumber();
			while (index < 0 || index > charTest.size()) {
				cout << "下标不合法，重新输入:";
				index = GetValidNumber();
			}

			cout << "输入字符：";
			char ch = GetValidChar();
			charTest.insert(ch, index);
			break;
		}

		case 2: {
			cout << "输入下标：";
			int index = GetValidNumber();
			while (index < 0 || index > charTest.size() - 1) {
				cout << "下标不合法，重新输入:";
				index = GetValidNumber();
			}
			charTest.erase(index);
			break;
		}

		case 3: {
			cout << "输入更改下标：";
			int index = GetValidNumber();
			while (index < 0 || index > charTest.size() - 1) {
				cout << "下标不合法，重新输入：";
				index = GetValidNumber();
			}
			cout << "输入更改字符：";
			char ch = GetValidChar();
			charTest.erase(index);
			charTest.insert(ch, index);
			break;
		}

		case 4: {   
			cout << "输入查找下标：";
			int index = GetValidNumber();
			//这里下标不合法不要求重新输入，因为如果该对象为空查找会一直失败
			if (index < 0 || index > charTest.size() - 1)
				cout << "下标不合法" << endl;
			else
				cout << "查找结果：" << charTest[index] << endl;
			break;
		}

		case 5: {
			cout << "输入字符:";
			char ch = GetValidChar();
			charTest.append(ch);
			break;
		}

		case 6: {
			int check = 1;
			cout << "输入字符串：";
			char ch[g_strLength];
			string str;
			getline(cin, str);
			while (str.size() == 0 || str.size() > g_strLength - 1) {
				cout << "字符串长度不合法，重新输入:";
				getline(cin, str);
			}
			int i = 0;
			for (; i < str.size(); i++) {
				ch[i] = str[i];
				if ((i < str.size() - 1) && (ch[i] & 0x80) && (ch[i + 1] & 0x80)) {
					cout << "字符串含多字节字符，不能添加";  
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
			cout << "非法操作项，重新输入！" << endl;
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
		cout << "字符个数：" << wcharTest.size() << endl;
		cout << "1.插入字符 2.删除字符 3.更改字符 4.查找 5.追加字符 6.追加字符串 0.退出" << endl;
		cout << "输入操作项:";

		int choose = GetValidNumber();
		switch (choose) {
		case 1: {
			cout << "输入下标:";
			int index = GetValidNumber();
			while (index < 0 || index > wcharTest.size()) {
				cout << "下标不合法，重新输入:";
				index = GetValidNumber();
			}

			cout << "输入字符：";
			WCHAR ch = GetValidWCHAR();
			wcharTest.insert(ch, index);
			noUse = getchar();  //防止换行符被读入，以下同理
			break;
		}

		case 2: {
			cout << "输入下标：";
			int index = GetValidNumber();
			while (index < 0 || index > wcharTest.size() - 1) {
				cout << "下标不合法，重新输入:";
				index = GetValidNumber();
			}
			wcharTest.erase(index);
			break;
		}

		case 3: {
			cout << "输入更改下标：";
			int index = GetValidNumber();
			while (index < 0 || index > wcharTest.size() - 1) {
				cout << "下标不合法，重新输入：";
				index = GetValidNumber();
			}
			cout << "输入更改字符：";
			WCHAR ch = GetValidWCHAR();
			wcharTest.erase(index);
			wcharTest.insert(ch, index);
			noUse = getchar();
			break;
		}

		case 4: {  
			cout << "输入查找下标：";
			int index = GetValidNumber();
			//这里下标不合法不要求重新输入，因为如果该对象为空查找会一直失败
			if (index < 0 || index > wcharTest.size() - 1)
				cout << "下标不合法" << endl;
			else
				wcout << L"查找结果：" << wcharTest[index] << endl;
			break;
		}

		case 5: {
			cout << "输入字符:";
			WCHAR ch = GetValidWCHAR();
			wcharTest.append(ch);
			noUse = getchar();
			break;
		}

		case 6: {     
			cout << "输入字符串：";
			WCHAR ch[g_strLength];
			wstring str;
			wcin >> str;
			while (str.size() == 0 || str.size() > g_strLength - 1) {
				cout << "字符串长度不合法，重新输入:";
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
			cout << "非法操作项，重新输入！" << endl;
			break;
		}

	}
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);  //检测内存泄漏
	setlocale(LC_ALL, "chs");   //设置字符编码环境，使WCHAR可显示中文

	//在ksostring中只实例化了char和WCHAR类型，其他类型访问容器均会报错,如:
	//KsoString<int>* p = new KsoString<int>;

	int flag = 1;
	while (flag) {
		cout << endl << endl << "---------------------------------------------------------" << endl;
		cout << "容器功能测试";
		cout << "1.char  2.WCHAR  0.退出" << endl;
		cout << "选择测试类型:";
		
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
			cout << "非法操作项，重新输入！" << endl;
			break;
		}
	}
	return 0;
}