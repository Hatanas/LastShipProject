#pragma once

#include "BaseTreeIterator.h"

template<typename T>
class PreOrderIterator : public BaseTreeIterator<T>
{
	friend class Tree<T>;
	PreOrderIterator(){}
public:
	explicit PreOrderIterator(TreeNode<T>* node) : BaseTreeIterator<T>(node){}
	PreOrderIterator &postOrderIncrement();
	PreOrderIterator &preOrderDecrement();

	PreOrderIterator &operator++();
	PreOrderIterator &operator++(int);
	PreOrderIterator &operator--();
	PreOrderIterator &operator--(int);
};

template<typename T>
PreOrderIterator<T> &PreOrderIterator<T>::postOrderIncrement()
{
	if (isNull()){ return *this; }

	if (isParent()) { goFirstChild(); }
	else {
		while (isLast()) {
			if (isRoot()){ break; }
			else{ goParent(); }
		}
		goNextSibling();
	}

	return *this;
}

template<typename T>
PreOrderIterator<T> &PreOrderIterator<T>::preOrderDecrement()
{
	if (isNull()){ return *this; }
	
	if (isFirst()){
		if (isRoot()){ goPrevSibling(); }
		else{ goParent(); }
	}
	else{
		goPrevSibling();
		while (isParent()) {
			goLastChild();
		}
	}

	return *this;
}

template<typename T>
inline PreOrderIterator<T> &PreOrderIterator<T>::operator++(){ return postOrderIncrement(); }

template<typename T>
inline PreOrderIterator<T> &PreOrderIterator<T>::operator++(int)
{
	++(*this);
	return *this;
}

template<typename T>
inline PreOrderIterator<T> &PreOrderIterator<T>::operator--(){ return preOrderDecrement(); }

template<typename T>
inline PreOrderIterator<T> &PreOrderIterator<T>::operator--(int)
{
	--(*this);
	return *this;
}


/*
template<typename T>
class PostOrderIterator :
*/

