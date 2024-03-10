#pragma once
#include <stdexcept>
#include <iostream>

template<typename T>
class Stack
{
public: 
	Stack(size_t StackSize)
	{
		size = StackSize;
		Top = -1; 
		s = new T[StackSize];
	}

	~Stack()
	{
		delete[] s;  // Deallocate the memory for the stack array
	}

	/*Checks if the stack is empty*/
	bool isEmpty()
	{
		if (Top == -1)
			return true;

		return false;
	}

	/*Checks if the stack is full*/
	bool isFull()
	{
		if (Top == size - 1)
			return true;

		return false; 
	}

	/*Adds a value to the top of the stack*/
	void Push(const T &value)
	{
		if(Top == size - 1)
			throw std::overflow_error("Stack overflow");
		else
		{
			Top++;
			s[Top] = value;
		}
	}

	void DisplayFromTop()
	{
		int index = Top; 
		while (index >= 0)
		{
			std::cout << "Stack[" << index << "]" << " = " << s[index] << std::endl;
			index--;
		}
	}

	void DisplayFromBottom()
	{
		int index = 0;
		while (index <= Top)
		{
			std::cout << "Stack[" << index << "]" << " = " << s[index] << std::endl;
			index++;
		}
	}

	/*Removes the value at the top of the stack
	  return: Returns the value popped*/
	T Pop()
	{
		T returnValue; 
		if (Top == -1)
			throw std::underflow_error("Stack underflow");
		else
		{
			returnValue = s[Top];
			Top--;
		}
		return returnValue;
	}

	//Returns a value at a certain index
	T peek(unsigned int index)
	{
		if(index < 0 || index > size - 1)
			throw std::out_of_range("Index out of range");
		else
		{
			return s[index];
		}
	}

	//Returns the value at the top of the stack
	T StackTop()
	{
		if (Top == -1)
			throw std::out_of_range("Index out of range");
		else
			return s[Top];
	}

private: 
	unsigned int size; 
	int Top;
	T* s; 
};

