#pragma once
#ifndef _QUAD_TREE_
#define _QUAD_TREE_
#include <vector>
#include <iostream>
#include <string>

template <class P>
inline void safeDelete(P p)
{
	if (p != nullptr)
	{
		delete p;
		p = nullptr;
	}
}

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
	bool operator ==(const Rect &r) const
	{
		if (_x == r._x && _y == r._y && _width == r._width && _height == r._height)
			return true;
		return false;
	}
	//match with [first,last)
	bool containsPoint(const Point &p) const
	{
		if (p._x >= _x && p._x < _x + _width && p._y >= _y && p._y < _y + _height)
			return true;
		return false;
	}
	bool containsPoint(float x, float y) const
	{
		if (x >= _x && x < _x + _width && y >= _y && y < _y + _height)
			return true;
		return false;
	}
	bool containsRect(const Rect &r) const
	{
		if (containsPoint(r._x, r._y) || containsPoint(r._x + r._width, r._y) || containsPoint(r._x, r._y + r._height) || containsPoint(r._x + r._width, r._y + r._height))
			return true;
		return false;
	}
};
struct Object
{
	Object(Rect r)
	:_contentSize(r){};
	~Object(){};
	Rect _contentSize;
	bool operator == (const Object &o) const
	{
		if (_contentSize == o._contentSize) return true;
		return false;
	}
};
template<class T = Object>
class QuadTree
{
	typedef T valueType;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T* iterator;
	typedef const T* const_iterator;

public:

	QuadTree(const std::size_t depth,const Rect &rect)
		:_elemts(nullptr), _depth(depth), _root(nullptr),_rect(rect)
	{
		if (depth == 0)
		{
			_elemts = new std::vector<T*>();
		}
		else
		{
			_root = new std::vector<QuadTree*>();
			setRootRect();
		}
	}

	~QuadTree(){
		if (_depth == 0)
		{
			safeDelete(_elemts);
		}
		else
		{
			safeDelete(_root);
		}
	};

	void print() const
	{
		if (_depth == 0)
		{
			std::cout << "End at here " << _rect << std::endl;
			if (!_elemts->empty())
			{
				std::cout << "Elemts : " << _elemts->size() << std::endl;
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

	void insertChild(T *t)
	{
		if (_depth == 0)
		{
			_elemts->push_back(t);
		}
		else
		{
			for (auto &r : *_root)
			{
				if (containsRect(r,t))
				{
					r->insertChild(t);
				}
			}
		}
	}

	bool findChild(T *t) const
	{
		if (_depth == 0)
		{
			return findValue(t);
		}
		else
		{
			for (auto &r : *_root)
			{
				if (containsRect(r, t))
				{
					return r->findChild(t);
				}
			}
			return false;
		}
	}

	bool deleteChild(const T *t)
	{
		if (_depth == 0)
		{
			return deleteValue(t);
		}
		else
		{
			for (auto &r : *_root)
			{
				if (containsRect(r, t))
				{
					return r->deleteChild(t);
				}
			}
			return false;
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
	
	bool findValue(const T *t) const
	{
		auto iter = _elemts->begin();
		for (; iter != _elemts->end(); ++iter)
		{
			if (**iter == *t) return true;
		}
		return false;
	}

	bool deleteValue(const T *t)
	{
		auto iter = _elemts->begin();
		for (; iter != _elemts->end(); ++iter)
		{
			if (**iter == *t)
			{
				_elemts->erase(iter);
				return true;
			}
		}
		return false;
	}

	bool containsRect(const QuadTree *a, const T *b) const
	{
		if (a->_rect.containsRect(b->_contentSize) || b->_contentSize.containsRect(a->_rect))
			return true;
		return false;
	}
private:

	Rect _rect;
	const int _depth;// elemts in this what depth equal to zero
	std::vector<QuadTree<T>*> *_root;
	std::vector<T*> *_elemts;
};

#endif