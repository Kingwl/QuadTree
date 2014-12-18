#include "stdafx.h"
#include "QuadTree.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Object *i = new Object(Rect(10, 10, 101, 101));
	QuadTree<Object>tree(2,Rect(0,0,400,400));
	tree.insertChild(i);
	//tree.print();
	auto a = tree.findChild(i);
	if (a)
	{
		std::cout << "ok" << std::endl;
	}
	else
	{
		std::cout << "no" << std::endl;

	}
	tree.deleteChild(i);
	a = tree.findChild(i);
	if (a)
	{
		std::cout << "ok" << std::endl;
	}
	else
	{
		std::cout << "no" << std::endl;

	}
	delete i;
	system("pause");
	return 0;
}

