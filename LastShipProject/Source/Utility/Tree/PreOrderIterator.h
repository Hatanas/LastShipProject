#pragma once

#include "BaseTreeIterator.h"

template<typename T>
class PreOrderIterator : public BaseTreeIterator<T>
{
	friend class Tree<T>;
	PreOrderIterator(){}
public:
	explicit PreOrderIterator(TreeNode<T>* node) : BaseTreeIterator<T>(node){}
	PreOrderIterator &pre_order_increment();
	PreOrderIterator &pre_order_decrement();

	PreOrderIterator &operator++();
	PreOrderIterator &operator++(int);
	PreOrderIterator &operator--();
	PreOrderIterator &operator--(int);
};

template<typename T>
PreOrderIterator<T> &PreOrderIterator<T>::pre_order_increment()
{
	if (isParent()) {
		goFirstChild();
	}
	else {
		while (isLast()) {
			if (!goParent()){ break; }
		}
		goNextSibling();
	}

	return *this;
}

template<typename T>
PreOrderIterator<T> &PreOrderIterator<T>::pre_order_decrement()
{
	if (isFirst()){
		goParent();
	}
	else{
		goPrevSibling();
		while (!isLeaf()) {
			if (!goLastChild()){ break; }
		}
	}

	return *this;
}

template<typename T>
inline PreOrderIterator<T> &PreOrderIterator<T>::operator++(){ return pre_order_increment(); }

template<typename T>
inline PreOrderIterator<T> &PreOrderIterator<T>::operator++(int)
{
	++(*this);
	return *this;
}

template<typename T>
inline PreOrderIterator<T> &PreOrderIterator<T>::operator--(){ return pre_order_decrement(); }

template<typename T>
inline PreOrderIterator<T> &PreOrderIterator<T>::operator--(int)
{
	--(*this);
	return *this;
}


/*
template<typename T>
class PostOrderIterator :
	public std::iterator<std::bidirectional_iterator_tag, T>,
	public BaseTreeIterator<T>
{
	friend class Tree<T>;
	PostOrderIterator() : myNode_m(nullptr){}
public:
	explicit PostOrderIterator(TreeNode<T>* node) : myNode_m(node){}
	PostOrderIterator &postorder_increment()
	{
		if (isParent()) {
			goFirstChild();
		}
		else {
			while (isLast()) {
				if (!goParent()){ break; }
			}
			goNextSibling();
		}

		return *this;
	}
	PostOrderIterator &postorder_decrement()
	{
		if (isFirstChild()){
			goParent();
		}
		else{
			goPrevSibling();
			while (!isLeaf()) {
				if (!goLastChild()){ break; }
			}
		}

		return *this;
	}

	PostOrderIterator &operator++(){ return postorder_increment(); }
	PostOrderIterator &operator++(int)
	{
		++(*this);
		return *this;
	}
	PostOrderIterator &operator--(){ return postorder_decrement(); }
	PreOrdPostOrderIteratorerIterator &operator--(int)
	{
		--(*this);
		return *this;
	}
};
*/
