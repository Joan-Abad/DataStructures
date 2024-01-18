#pragma once

template <typename T>
class DoubleLinkedListNode
{
	template <typename Type>
	friend class DoubleLinkedList;

public: 
	DoubleLinkedListNode(const T& NodeValue) : Value(NodeValue), PreviousNode(nullptr), NextNode(nullptr)
	{ 
		
	} 

	DoubleLinkedListNode<T>* GetPreviousNode() const { return PreviousNode; };
	DoubleLinkedListNode<T>* GetNextNode() const { return NextNode; };

private: 
	DoubleLinkedListNode<T>* PreviousNode;
	T Value; 
	DoubleLinkedListNode<T>* NextNode;
}; 

//DoubleLinkedList class that has a collection of nodes that enables you to travel forward and backward
template <typename Type>
class DoubleLinkedList
{
	using Node = DoubleLinkedListNode<Type>;

public:
	DoubleLinkedList() : headNode(nullptr), lastNode(nullptr) {}

	//Add a node at the front of the list
	void push_front(const Type& type)
	{
		Node* newNode = new Node(type);
		newNode->NextNode = headNode;
		headNode = newNode;

		if (!lastNode)
			lastNode = newNode;
	}

	void push_back(const Type& value)
	{
		Node* q = headNode;
		Node* p = nullptr;

		if (!headNode)
		{
			Node* r = new Node(value);
			headNode = r; 
			return;
		}

		while (q)
		{
			p = q; 
			q = q->GetNextNode();
		}


		if(p)
		{
			Node* r = new Node(value);
			p->NextNode = r; 
			r->PreviousNode = r; 
		}
		

	}

	bool Delete(int index)
	{		
		if (index < 0 || index > Length())
			return -1;

		Node* p = headNode; 
		Node* q = nullptr; 
		Node* r = nullptr; 

		if (index == 0)
		{
			if (headNode)
			{
				Node* newHeadNode = headNode->GetNextNode();
				
				delete headNode;

				headNode = newHeadNode;

				if (newHeadNode)
					newHeadNode->PreviousNode = nullptr; 
				return true;
			}
			else
				return false; 
		}
		else
		{
			for (int i = 0; i < index; i++)
			{
				r = q;
				q = p;
				p = p->GetNextNode();
			}
			Node* postNode = p->GetNextNode();

			if (postNode)
			{
				q->NextNode = postNode;
				postNode->PreviousNode = q;
			}

		}
	}
	
	size_t Length()
	{
		size_t len = 0; 

		Node* node = headNode; 
		while (node)
		{
			len++;
			node = node->GetNextNode();
		}
		return len;
	}


	//Insert a new node to the pos and with its Value. Returns if could insert it or not. Won't add it if the position is not available
	void Insert(unsigned int pos, const Type& Value)
	{
		Node* p = headNode;
		Node* q = nullptr;
		Node* t;

		if (pos < 0 || pos > Length())
			return;

		if (pos == 0)
		{
			t = new Node(Value);
			t->PreviousNode = 0;
			t->NextNode = headNode;
			if (headNode)
			{
				headNode->PreviousNode = t;
				headNode = t;
			}
			else
				headNode = t;
		}
		else
		{
			for (int i = 1; i < pos; i++)
				p = p->GetNextNode();

			t = new Node(Value);

			t->PreviousNode = p;
			t->NextNode = p->GetNextNode();

			if (p->GetNextNode())
				p->GetNextNode()->PreviousNode = t;

			p->NextNode = t;
		}
	}

	void Display()
	{
		Node* node = headNode;
		unsigned int numNodes = 0;
		while (node)
		{
			std::cout << "Node " << numNodes << ": " << node->Value <<
				" Previous pointing to: " << node->GetPreviousNode() << " and " "post pointing to: " << node->GetNextNode() << std::endl;
			node = node->GetNextNode();
			numNodes++;
		}
	}


private:
	Node* headNode;
	Node* lastNode;

};