// ConsoleApplication9.cpp : 定义控制台应用程序的入口点。
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

