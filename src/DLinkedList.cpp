/*
 * DLinkedList.cpp
 *
 *  Created on: Dec 8, 2022
 *      Author: Scott Chen
 */

#include <iostream>
#include <stddef.h>  				// required for NULL pointer

#include "DLinkedList.h"

using namespace std;


template <typename E>
DLinkedList<E>::DLinkedList()
{
	E e; 	// Dummy Data

	// Create two dummy nodes
	head = new DpNode<E>(e, NULL, NULL);
	tail = new DpNode<E>(e, NULL, NULL);

	// Connect them
	head->next = tail;
	tail->prev = head;

	size = 0;
}

template <typename E>
DLinkedList<E>::~DLinkedList()
{
	makeEmpty();					// Clean up the valid elements in the list

	// Then, delete the two headers
	delete head;
	delete tail;
}

template <typename E>
void DLinkedList<E>::makeEmpty()
{
	while(head->next != tail)    // doubly linked list modification
	{
		auto temp = head->next;  	// auto: let compiler deduct the implicit data type
									//  Identical to:  Node<E>* temp;

		head->next = temp->next;	// Move the head to the next valid element
		delete temp;				// Then delete the current element
	}
	
	tail->prev = head;			// Make sure the backward linkage is intact

	size = 0;
}

template <typename E>
void DLinkedList<E>::printList()
{
	if(size <= 0) 
	{	
		cout << "[EMPTY]" << endl;
		return;
	}
	
	DpNode<E>* readerHead;

	cout << "[";
	for(readerHead = head->next; readerHead != tail; readerHead = readerHead->next)
	{
		cout << " " << readerHead->data;
	}
	cout << " ]" << endl;
}

template <typename E>
int DLinkedList<E>::getSize()
{
	return size;
}

template <typename E>
void DLinkedList<E>::addFirst(const E &e)
{
	// Create the node with proper connections
	DpNode<E>* newElement = new DpNode<E>(e, head->next, head);

	// Modify the connections of the neighbouring elements
	head->next = newElement;
	newElement->next->prev = newElement;

	size++;
}

template <typename E>
void DLinkedList<E>::addLast(const E &e)
{
	// Verify this yourself

	DpNode<E>* newElement = new DpNode<E>(e, tail, tail->prev);

	tail->prev = newElement;
	newElement->prev->next = newElement;

	size++;
}

template <typename E>
E DLinkedList<E>::removeFirst()			// Remove Element from Head
{
	if(size <= 0) return 0;
	
	E temp;
	DpNode<E> *target = head->next;

	temp = target->data;
	head->next = target->next;
	target->next->prev = head;

	delete target;
	size--;
	return temp;
}

template <typename E>
E DLinkedList<E>::removeLast()				// Remove Element from Tail;
{
	if(size <= 0) return 0;

	E temp;
	DpNode<E> *target = tail->prev;

	temp = target->data;
	tail->prev = target->prev;
	target->prev->next = tail;

	delete target;
	size--;
	return temp;
}

template <typename E>
void DLinkedList<E>::remove(const E &e)
{
	if(size <= 0) return;

	DpNode<E>* readerHead = head->next;

	// Move reader head to the target
	while(readerHead != tail && readerHead->data != e)
	{
		readerHead = readerHead->next;
	}

	// If we hit the target
	if(readerHead != tail)
	{
		// Reconnect the pointers to skip over the target element
		readerHead->prev->next = readerHead->next;
		readerHead->next->prev = readerHead->prev;

		// Then, delete the target
		delete readerHead;
	}

	size--;
}



// These will instruct the C++ compiler to pre-generate these template classes of different types
//  So, is separating source code from header file for template classes really a good idea?
//     Scott's recommendation - keep everything in the header file, because it's template class anyways

template class DLinkedList<int>;
template class DLinkedList<char>;
template class DLinkedList<float>;
template class DLinkedList<double>;
template class DLinkedList<long>;
template class DLinkedList<bool>;
template class DLinkedList<short>;

