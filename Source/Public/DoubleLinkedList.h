#pragma once

template <typename T>
class Node
{
public: 
	Node(T& NodeValue) : value(NodeValue), previous(nullptr), next(nullptr) 
	{ 
		
	} 

private: 
	T* previous; 
	T value; 
	T* next; 
}; 

//DoubleLinkedList class that has a collection of nodes that enables you to travel forward and backward
template <typename T>
class DoubleLinkedList
{
public: 
	DoubleLinkedList() : headNode(nullptr), lastNode(nullptr) {}

	//Add a node at the front of the list
	void push_front(const Type& type)
	{
		Node<Type>* newNode = new Node<Type>(type);
		newNode->NextNode = headNode;
		headNode = newNode;

		if (!lastNode)
			lastNode = newNode;
	}



private:
	Node<T>* headNode;
	Node<T>* lastNode;

};