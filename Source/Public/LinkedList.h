#pragma once
#include <iostream>

template<typename Type>
class Node
{
	template <typename Type>
	friend class LinkedList;
private: 
	Node<Type>* NextNode; 
	Type value; 
public:
	Node(Type NodeValue) : NextNode(nullptr), value(NodeValue) {}

	Type GetNodeValue() const { return value;  };
	Node<Type>* GetNextNode() const { return NextNode; };
};

template<typename Type>
class LinkedList
{
private: 
	Node<Type>* headNode; 

public: 
	LinkedList() : headNode(nullptr) {};
	

	void push_front(Type type)
	{
		Node<Type>* newNode = new Node<Type>(type);
		newNode->NextNode = headNode;
		headNode = newNode;
	}

	void Display()
	{
		Node<Type>* node = headNode;
		int i = 0; 
		
		while (node != nullptr)
		{
			std::cout << "Node " << i << ": " << node->value << std::endl;
			node = node->GetNextNode();
			i++;
		}
	}
};