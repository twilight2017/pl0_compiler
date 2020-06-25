#include<iostream>
#include "parse.h"
using namespace std;

const char *name = "D:\\study\\compile_theory";
int main()
{
	/*
	创建保留字表reverse(该表同样承担单词编码表的功能)
	及编码对应单词表kw
	*/
	create_keytable();
	string t = fr(name);
	cout << name << endl;
	cout << t << endl;
	//屏幕输出单词类别表和操作码
	show_word_coding_table();

	// 词法分析程序，产生单词序列链表,head
	lexer(t);
	//输出单词序列表head
	show(head);
	//语法分析，递归子程序发；以及语义分析
	P();
	//层次遍历输出语法树
	levelorder(root);
	//输出table表
	showtab(table);
	//输出中间代码
	showass();
	//解释执行
	exec();
	return 0;

}