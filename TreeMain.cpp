// ConsoleApplication9.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "QuadTree.h"


int _tmain(int argc, _TCHAR* argv[])
{
	QuadTree<int>tree(3,Rect(0,0,400,300));
	tree.print();
	system("pause");
	return 0;
}

