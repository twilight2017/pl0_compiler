#include<iostream>
#include "parse.h"
using namespace std;

const char *name = "D:\\study\\compile_theory";
int main()
{
	/*
	���������ֱ�reverse(�ñ�ͬ���е����ʱ����Ĺ���)
	�������Ӧ���ʱ�kw
	*/
	create_keytable();
	string t = fr(name);
	cout << name << endl;
	cout << t << endl;
	//��Ļ�����������Ͳ�����
	show_word_coding_table();

	// �ʷ��������򣬲���������������,head
	lexer(t);
	//����������б�head
	show(head);
	//�﷨�������ݹ��ӳ��򷢣��Լ��������
	P();
	//��α�������﷨��
	levelorder(root);
	//���table��
	showtab(table);
	//����м����
	showass();
	//����ִ��
	exec();
	return 0;

}