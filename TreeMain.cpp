// ConsoleApplication9.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "QuadTree.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int i = 42;
	QuadTree<int>tree(2,Rect(0,0,400,400));
	tree.insertChild(Rect(10, 10, 101, 101), &i);
	tree.print();
	system("pause");
	return 0;
}

