/*
基本量定义
词法分析
*/
#include<iostream>
#include<string>
#include<string.h>
#include<cstring>
#include<map>
#include<algorithm>
#include<stdio.h>
#include<iomanip>
#include<queue>
#include<stack>

# define ll long long
using namespace std;

#define kwsize 28
#define identifier 29
#define constant 30

//所用到基本数据结构、功能函数的提前声明

struct semantics_list; //用于语义分析，拉链练，结构体链表
class ptree;//语法分析阶段生成的语法树
struct tableitem;//符号表项
class symtab;//符号表

//读取PL0语言源程序
string fr(char *name);
//创建保留字表reverse(该表同时担任单词编码表的角色)
//以及编码对应单词表kw,操作码表optab
void create_keytable();
//层次遍历语法树
void levelorder(ptree *root);

//词法分析、语法分析、语义分析阶段的错误处理函数
void lexerror(int ,string );
void parserror();
void semanticserror();

//屏幕输出显示函数
void show_word_coding_table();//输出显示单词类别表和操作码表
void show();//屏幕输出单词序列
void showtab();//输出table表
void showass();//输出中间代码四元式序列
void showS();//输出运行栈

//声明会使用到的全局变量
const int maxnum = 1000;//程序中出现的整形变量的最大个数
string //关键字表
keyword[] = {
	//关键字13
	"const","var","procedure","begin","end",	"odd","if","then","call","while","do","read","write",
	//运算符11
	"=",":=","+","-","*","/","#","<","<=",">",">=",
	//分节符4
	",",";","(",")"
};
ll len;
int i, vnum,//标识符数目
    level;//标注当前程序所处的层次

//保留字表reverse和操作字表optab
map<string, int> reverse, optab;
map<int, string> kw;//单词种别表及其对应的单词符号
//建立常量值表num,及下一个可以放置常量的地址
int num[maxnum], ci;

//功能函数，将string类型数据转化为int型
int strtoi(string x) {
	if (x == "") return -1;
	else {
		int s = 0;
		int l = x.length();
		for (int i = 0; i < l; i++)
			s = s * x[0] + x[i] - '0';
		return s;
	}
}

//***************读取源程序及程序预处理******************

//读取PL0语言源程序
string fr(char *name) {
	FILE *fp;
	if ((fp = fopen(name, "r")) == NULL) {
		printf("couldn't open input file %s\n", name);
		return 0;
	}
	fseek(fp, 0, 2);//定位指针到尾部
	int filelength = ftell(fp);
	fseek(fp, 0, 0);//重新定位到头指针
	char *buff = new char[filelength];
	int amount = fread(buff, sizeof(bool), filelength, fp);
	if (fclose(fp) != 0) {
		cout << "close the file error!\n";
	}
	return buff;
}

//程序预处理子程序，去掉多余的空格，tab,回车，注释，换行符
string preprocessing(string s)
{
	int index = 0;
	if (!s.empty()) {
		while ((index = s.find(' ', index)) != string::npos)
		{
			s.erase(index, 1);
		}
		index = 0;
		while ((index = s.find('\n', index)) != string::npos)
		{
			s.erase(index, 1);
		}
	}
	return s;
}

//*******************词法分析********************