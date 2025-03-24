#include<iostream>
using namespace std;
 
int main()
{
	cout << "abc" << "是一个字符串常量" << endl;	//abc是一个字符串常量
}

//字符串有三种实现方式：数组，指针变量，string类对象
//数组

int main()
{
	char eg1[10] = "abc";    //直接初始化
	char eg2[10];    //后面通过输入初始化
	cin >> eg2;	//此处输入def
	cout << eg1 << endl;	//abc
	cout << eg2 << endl;	//def
}

//指针变量

int main()
{
    char eg1[10] = "abc";
    char* eg2 = eg1;
    cout << eg2 << endl;	//abc
}

//string类对象

int main()
{
	string s1 = "123";	//利用“=”来初始化
	string s2("456");	//利用“()”来初始化，和上面本质一样
	string s3 = s1;		//利用“string”类对象来初始化
	string s4(s2);		//和上面本质一样
	char eg[10] = "abc";
	string s5 = eg;		//利用“eg数组”来初始化
	cout << s1 << endl;	//123
	cout << s2 << endl;	//456
	cout << s3 << endl;	//123
	cout << s4 << endl;	//456
	cout << s5 << endl;	//abc
}

//cin函数，空格 回车 tab 都可以作为分隔符

//getline函数，可以读取空格，遇到回车结束
int  main()
{
    string s;
    getline(cin,s); //getline(cin , s)
    cout << s << endl;
}

//cin.getline()函数，遇到回车结束,可以指定读取长度
int  main()
{
    char s[10];
    cin.getline(s,10); //cin.getline(s, 10)
    cout << s << endl;
}

//PS:"cin.getline()函数只能给'数组'形式的字符串使用,而getline()函数只能给'string类对象'形式的字符串使用"