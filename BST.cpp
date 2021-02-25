#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <iostream>
using namespace std;

int CheckErrors(char Expr[]) {
	int z = strlen(Expr);
	int i = 0;
	while (i < z) {
		switch (Expr[i]) {
		case '+': case '-':case'*':case'/':
			if (Expr[i + 1] == '+' || Expr[i + 1] == '-' || Expr[i + 1] == '/' || Expr[i + 1] == '*') {
				int g = i;
				for (g; g != z; g++) Expr[g] = Expr[g + 1];				
				z--;
				cout << "Найдена и исправлена ошибка " << Expr[i - 1] << Expr[i] << Expr[i + 1] << endl;
				i--;
			}
		}
		i++;
	}
	return z-1;
}

int Priority(char c)
{
	switch (c) {
	case '+': case '-': {
		return 1; }
	case '*': case '/':
		return 2;
	}
	return 100;
}
int LastOperation(char Expr[], int first, int last)
{
	int MinPrt, i, k, prt;
	MinPrt = 100;
	for (i = first; i <= last; i++) {
		prt = Priority(Expr[i]);
		if (prt <= MinPrt) {
			MinPrt = prt;
			k = i;
		}
	}
	return k;
}
typedef char Elem;
struct BinNode {
	Elem elem;
	BinNode *lc, *rc;
};
BinNode *mkNumberNode(char c)
{
	BinNode *root = new BinNode;
	root->elem = c;
	root->lc = NULL;
	root->rc = NULL;
	return root;
}
BinNode *MakeTree(char Expr[], int first, int last)
{
	BinNode *root;
	int k;
	if (first == last)
		return mkNumberNode(Expr[first]);
	k = LastOperation(Expr, first, last);
	root = new BinNode;
	root->elem = Expr[k];
	root->lc = MakeTree(Expr, first, k - 1);
	root->rc = MakeTree(Expr, k + 1, last);
	return root;
}
int CalcTree(BinNode *root)
{
	int num1, num2;
	if (!root->lc) return root->elem - '0';
	num1 = CalcTree(root->lc);
	num2 = CalcTree(root->rc);
	switch (root->elem) {
	case '+': return  num1 + num2;
	case '-': return  num1 - num2;
	case '*': return  num1*num2;
	case '/': return  num1 / num2;
	}
	return 32767;
}

void main()
{
	setlocale(LC_CTYPE, "rus");
	char s[80];
	BinNode *MyTreeRoot;
	printf("Введите выражение > ");
	gets(s);
	MyTreeRoot = MakeTree(s, 0, CheckErrors(s));
	cout << s << "=" << CalcTree(MyTreeRoot);
	getchar();
}