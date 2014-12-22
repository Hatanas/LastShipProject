#pragma once


template<typename T>
class TreeNode
{
public:
	TreeNode<T>* parent_m;
	TreeNode<T>* first_child_m;
	TreeNode<T>* last_child_m;
	TreeNode<T>* prev_sibling_m;
	TreeNode<T>* next_sibling_m;
	T* key_m;
public:
	TreeNode();
	TreeNode(const T& key);
	~TreeNode();
};


template<typename T>
inline TreeNode<T>::TreeNode()
{
	parent_m = first_child_m = last_child_m = prev_sibling_m = first_child_m = nullptr;
	key_m = new T();
}

template<typename T>
inline TreeNode<T>::TreeNode(const T& key)
{
	parent_m = first_child_m = last_child_m = prev_sibling_m = first_child_m = nullptr;
	key_m = new T(key);
}

template<typename T>
inline TreeNode<T>::~TreeNode()
{
	delete key_m;
}

