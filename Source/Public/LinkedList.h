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
		
		while (node)
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

		while (node)
		{
			size++;
			node = node->GetNextNode();
		}
		return size; 
	}

	//Summs all the elements and return the total sum. The operator + must be available for the Type of the nodes of the Linked List. 
	Type SumOfAllElements()
	{
		Type returnValue = 0;
		Node<Type>* node = headNode;

		while (node)
		{
			returnValue += node->value;
			node = node->GetNextNode();
		}

		return returnValue;
	}

	//Gets the maximum value of all the nodes on the linked list. Operator > should be declared for the Type of the nodes of the Linked List. 
	Type GetMaximumValue()
	{
		Node<Type>* node = headNode;
		Type returnValue = node->value;

		while (node)
		{
			if (node->value > returnValue)
				returnValue = node->value;

			node = node->GetNextNode();
		}

		return returnValue;
	}

	//Checks if a specific value is on the Linked List. 
	bool HasValue(const Type& ValueToSearch)
	{
		Node<Type>* node = headNode;

		while (node)
		{
			if (node->value == ValueToSearch)
				return true;

			node = node->GetNextNode();
		}

		return false; 
	}
	//Searches for the first node that has the parameter value and returns it if any. 
	Node<Type>* SearchNode(const Type& ValueToSearch)
	{
		Node<Type>* intNode = headNode;

		while (intNode)
		{
			if (intNode->value == ValueToSearch)
				return intNode;
		
			intNode = intNode->GetNextNode();
		}

		return nullptr; 
	}

	//Searches for the note associated with that value, and it puts it at the top of the linked list for quicker future access
	//This uses a MoveToHead metodology
	Node<Type>* SearchNodeMTH(const Type &ValueToSearch)
	{
		int i = 1; 
		Node<Type>* intNode = headNode;
		Node<Type>* q = nullptr;

		while (intNode)
		{
			if (intNode->value == ValueToSearch)
			{
				if (q)
				{
					q->NextNode = intNode->GetNextNode();
					intNode->NextNode = headNode;
					headNode = intNode;
				}
				return headNode;
			}
			q = intNode; 
			intNode = intNode->GetNextNode();
			i++;
		}

		return nullptr;
	}

	//Insert a new node to the pos and with its Value. Returns if could insert it or not. Won't add it if the position is not available
	bool Insert(unsigned int pos, const Type& Value)
	{
		// insert at pos 0
		if (pos == 0)
		{
			Node<Type>* newNode = new Node<Type>(Value);
			newNode->NextNode = headNode;
			headNode = newNode;
			return true;
		}
		else
		{
			unsigned int NodeCount = 0; 
			
			Node<Type>* intNode = headNode;
			
			while (intNode)
			{
				NodeCount++;
				if (NodeCount == pos)
				{
					Node<Type>* newNode = new Node<Type>(Value);
					Node<Type>* followingNode = intNode->GetNextNode();
					intNode->NextNode = newNode;
					newNode->NextNode = followingNode;
					return true;
				}
				intNode = intNode->GetNextNode();
			}
		}
		return false; 
	}
};