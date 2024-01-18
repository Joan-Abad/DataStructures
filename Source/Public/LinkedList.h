#pragma once
#include <iostream>

template<typename Type>
class LinkedListNode
{
	template <typename Type>
	friend class LinkedList;
private: 
	LinkedListNode* NextNode;
	Type value; 
public:
	LinkedListNode(const Type& NodeValue) : NextNode(nullptr), value(NodeValue) {}

	Type GetNodeValue() const { return value;  };
	LinkedListNode* GetNextNode() const { return NextNode; };
};

template<typename Type>
class LinkedList
{
	using Node = LinkedListNode<Type>;
private: 
	Node* headNode;

public: 
	LinkedList() : headNode(nullptr) {};

	//Clears all the memory of the nodes allocated on the heap when this object is destroyed
	~LinkedList()
	{
		Node* node = headNode;
		while (node)
		{
			Node* tempNode = node->GetNextNode(); 
			delete node; 
			node = tempNode; 			
		}
	}
	
	//Add a node at the front of the list
	void push_front(const Type& type)
	{
		//Create new node
		Node* newNode = new Node(type);
		newNode->NextNode = headNode;
		headNode = newNode;
	}

	//Insert a new node to the pos and with its Value. Returns if could insert it or not. Won't add it if the position is not available
	bool Insert(unsigned int pos, const Type& Value)
	{
		// insert at pos 0
		if (pos == 0)
		{
			Node* newNode = new Node(Value);
			newNode->NextNode = headNode;
			headNode = newNode;

			return true;
		}
		else
		{
			unsigned int NodeCount = 0;

			Node* intNode = headNode;

			while (intNode)
			{
				NodeCount++;
				if (NodeCount == pos)
				{
					Node* newNode = new Node(Value);
					Node* followingNode = intNode->GetNextNode();
					intNode->NextNode = newNode;
					newNode->NextNode = followingNode;

					return true;
				}
				intNode = intNode->GetNextNode();
			}
		}
		return false;
	}

	//The value will be added in a sorted list in its corresponding position. > operator must be defined on the type
	void InsertOnSortedList(const Type& value)
	{
		Node* p = headNode;
		Node* q = nullptr;

		while (p && p->GetNodeValue() <= value)
		{
			q = p;
			p = p->GetNextNode();
		}

		//If has a previous element, update 
		Node* newNode = new Node(value);
		newNode->NextNode = p;

		if (p == headNode)
			headNode = newNode;

		if (q)
			q->NextNode = newNode;
	}

	//Deletes a value at a specific index starting by 0
	bool Delete(const unsigned int index)
	{
		Node* p = headNode;
		Node* q = nullptr;
		unsigned int internalIndex = 0;
		while (p)
		{
			if (index == 0)
				headNode = p->GetNextNode();

			if (index == internalIndex)
			{
				if(q)
					q->NextNode = p->GetNextNode();

				delete p;
				return true;
			}

			q = p;
			p = p->GetNextNode();
			internalIndex++;
		}
		return false;
	}

	//Returns if the list is sorted
	bool IsSorted() 
	{
		Node* q = headNode;
		Node* p = headNode->GetNextNode();
		
		while (p)
		{
			if (q->GetNodeValue() > p->GetNodeValue())
				return false;

			q = p;
			p = p->GetNextNode();
		}

		return true; 
	}

	//Removes all nodes that have the specified value
	void RemoveAllDuplicates(const Type& value)
	{
		Node* p = headNode;
		Node* q = nullptr;

		while (p)
		{
			if (p->GetNodeValue() == value)
			{
				if (q) {
					q->NextNode = p->GetNextNode();
					delete p;
					p = q->GetNextNode();
				}
				else {
					// Special case if the duplicate is at the head
					headNode = p->GetNextNode();
					delete p;
					p = headNode;
				}
			}
			else
			{
				q = p;
				p = p->GetNextNode();
			}
		}
	}

	//Display the content of the nodes
	void Display()
	{
		Node* node = headNode;
		int i = 0; 
		
		while (node)
		{
			std::cout << "Node " << i << ": " << node->value << " pointing to " << node->GetNextNode() << std::endl;
			node = node->GetNextNode();
			i++;
		}
	}

	//Gets the amount of nodes attached to this Linked List
	size_t Size()
	{
		size_t size = 0;
		Node* node = headNode;

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
		Node* node = headNode;

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
		Node* node = headNode;
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
		Node* node = headNode;

		while (node)
		{
			if (node->value == ValueToSearch)
				return true;

			node = node->GetNextNode();
		}

		return false; 
	}
	//Searches for the first node that has the parameter value and returns it if any. 
	Node* SearchNode(const Type& ValueToSearch)
	{
		Node* intNode = headNode;

		while (intNode)
		{
			if (intNode->value == ValueToSearch)
				return intNode;
		
			intNode = intNode->GetNextNode();
		}

		return nullptr; 
	}

	//Reverses the whole linked list
	void Reverse()
	{
		Node* p = headNode;
		Node* q = nullptr;
		Node* r = nullptr;

		while (p)
		{
			r = q;
			q = p;
			p = p->GetNextNode();
			q->NextNode = r; 
		}

		headNode = q;
	}

	//Joins two linked list in a single linked list
	void Concatenate(LinkedList& LinkedListToMerge)
	{
		Node* currentNode = headNode;
		while (currentNode)
		{
			if (!currentNode->GetNextNode())
			{
				currentNode->NextNode = LinkedListToMerge.headNode;
				return;
			}
			currentNode = currentNode->GetNextNode();
		}
	}

	//Merges the contents of a sorted list to the other list
	void Merge(LinkedList& LinkedListToMerge)
	{
		Node* q = headNode;
		Node* t = nullptr;
		Node* p = LinkedListToMerge.headNode;

		while (q && p)
		{
			if (q->GetNodeValue() < p->GetNodeValue())
			{
				t = q; 
				q = q->GetNextNode();
			}
			else
			{
				Node* temp = p->GetNextNode();

				if(t)
					t->NextNode = p; 

				p->NextNode = q;
				p = temp;
			}

		}

		if (!q && t->GetNodeValue() < p->GetNodeValue())
			t->NextNode = p;

		LinkedListToMerge.headNode = nullptr;
	}

	//Searches for the note associated with that value, and it puts it at the top of the linked list for quicker future access
	//This uses a MoveToHead metodology
	Node* SearchNodeMTH(const Type &ValueToSearch)
	{
		int i = 1; 
		Node* intNode = headNode;
		Node* q = nullptr;

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
};