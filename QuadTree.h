#pragma once
#ifndef _QUAD_TREE_
#define _QUAD_TREE_
#include <vector>
#include <iostream>
#include <string>

struct Point
{
	float _x, _y;
	Point(float x = 0.0f, float y = 0.0f)
		:_x(x), _y(y){}
};

struct  Rect
{
	Rect(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f)
	:_x(x), _y(y), _width(width), _height(height){}
	float _x, _y;
	float _width, _height;
	friend std::ostream& operator<< (std::ostream &o, const Rect& r)
	{
		std::cout << " x : " << r._x << " y : " << r._y << " width : " << r._width << " height : " << r._height;
		return o;
	}
	//match with [first,last)
	bool containsPoint(const Point &p)
	{
		if (p._x >= _x && p._x < _x + _width && p._y >= _y && p._y < _y + _height)
			return true;
		return false;
	}
	bool containsPoint(float x, float y)
	{
		if (x >= _x && x < _x + _width && y >= _y && y < _y + _height)
			return true;
		return false;
	}
	bool containsRect(const Rect &r)
	{
		if (containsPoint(r._x, r._y) || containsPoint(r._x + r._width, r._y) || containsPoint(r._x, r._y + r._height) || containsPoint(r._x + r._width, r._y + r._height))
			return true;
		return false;
	}
};

template<class T>
class QuadTree
{
public:
	QuadTree(const std::size_t depth,const Rect &rect)
		:_elemts(nullptr), _depth(depth), _root(nullptr),_rect(rect)
	{
		if (depth == 0)
		{
			_elemts = new std::vector<std::pair<Rect,T*>>();
		}
		else
		{
			_root = new std::vector<QuadTree*>();
			setRootRect();
		}
	}
	~QuadTree(){};

	void print() const
	{
		if (_depth == 0)
		{
			std::cout << "End at here " << _rect << std::endl;
			if (!_elemts->empty())
			{

				std::cout << "elemts : " << _elemts->size() << std::endl;
			}
		}
		else
		{
			std::cout << "Node here Depth: "<<_depth << " " << _rect << std::endl;
			for (auto &r : *_root)
			{
				r->print();
			}
		}
	}

	void insertChild(Rect &p, T *t)
	{
		if (_depth == 0)
		{
			_elemts->push_back(std::make_pair(p,t));
		}
		else
		{
			for (auto &r : *_root)
			{
				if (r->_rect.containsRect(p))
				{
					r->insertChild(p, t);
				}
			}
		}
	}

protected:

	void setRootRect()
	{
		float tw = _rect._width / 2.0f;
		float th = _rect._height / 2.0f;
		_root->push_back(new QuadTree<T>(_depth - 1, Rect(_rect._x, _rect._y,tw, th)));
		_root->push_back(new QuadTree<T>(_depth - 1, Rect(_rect._x + tw, _rect._y, tw, th)));
		_root->push_back(new QuadTree<T>(_depth - 1, Rect(_rect._x, _rect._y + th, tw, th)));
		_root->push_back(new QuadTree<T>(_depth - 1, Rect(_rect._x + tw, _rect._y + th, tw, th)));
	}

private:

	Rect _rect;
	const int _depth;// elemts in this what depth equal to zero
	std::vector<QuadTree<T>*> *_root;
	std::vector<std::pair<Rect, T*>> *_elemts;
};

#endif