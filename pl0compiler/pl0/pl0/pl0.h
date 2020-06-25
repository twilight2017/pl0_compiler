/*
����������
�ʷ�����
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

//���õ��������ݽṹ�����ܺ�������ǰ����

struct semantics_list; //����������������������ṹ������
class ptree;//�﷨�����׶����ɵ��﷨��
struct tableitem;//���ű���
class symtab;//���ű�

//��ȡPL0����Դ����
string fr(char *name);
//���������ֱ�reverse(�ñ�ͬʱ���ε��ʱ����Ľ�ɫ)
//�Լ������Ӧ���ʱ�kw,�������optab
void create_keytable();
//��α����﷨��
void levelorder(ptree *root);

//�ʷ��������﷨��������������׶εĴ�������
void lexerror(int ,string );
void parserror();
void semanticserror();

//��Ļ�����ʾ����
void show_word_coding_table();//�����ʾ��������Ͳ������
void show();//��Ļ�����������
void showtab();//���table��
void showass();//����м������Ԫʽ����
void showS();//�������ջ

//������ʹ�õ���ȫ�ֱ���
const int maxnum = 1000;//�����г��ֵ����α�����������
string //�ؼ��ֱ�
keyword[] = {
	//�ؼ���13
	"const","var","procedure","begin","end",	"odd","if","then","call","while","do","read","write",
	//�����11
	"=",":=","+","-","*","/","#","<","<=",">",">=",
	//�ֽڷ�4
	",",";","(",")"
};
ll len;
int i, vnum,//��ʶ����Ŀ
    level;//��ע��ǰ���������Ĳ��

//�����ֱ�reverse�Ͳ����ֱ�optab
map<string, int> reverse, optab;
map<int, string> kw;//�����ֱ�����Ӧ�ĵ��ʷ���
//��������ֵ��num,����һ�����Է��ó����ĵ�ַ
int num[maxnum], ci;

//���ܺ�������string��������ת��Ϊint��
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

//***************��ȡԴ���򼰳���Ԥ����******************

//��ȡPL0����Դ����
string fr(char *name) {
	FILE *fp;
	if ((fp = fopen(name, "r")) == NULL) {
		printf("couldn't open input file %s\n", name);
		return 0;
	}
	fseek(fp, 0, 2);//��λָ�뵽β��
	int filelength = ftell(fp);
	fseek(fp, 0, 0);//���¶�λ��ͷָ��
	char *buff = new char[filelength];
	int amount = fread(buff, sizeof(bool), filelength, fp);
	if (fclose(fp) != 0) {
		cout << "close the file error!\n";
	}
	return buff;
}

//����Ԥ�����ӳ���ȥ������Ŀո�tab,�س���ע�ͣ����з�
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

//*******************�ʷ�����********************