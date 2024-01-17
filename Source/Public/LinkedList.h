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
	
	//Add a node at the front of the list
	void push_front(Type type)
	{
		//Create new node
		Node<Type>* newNode = new Node<Type>(type);
		newNode->NextNode = headNode;
		headNode = newNode;
	}

	//Display the content of the nodes
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

	//Gets the amount of nodes attached to this Linked List
	size_t Size()
	{
		size_t size = 0;
		Node<Type>* node = headNode;

		while (node != nullptr)
		{
			size++;
			node = node->GetNextNode();
		}
		return size; 
	}
};