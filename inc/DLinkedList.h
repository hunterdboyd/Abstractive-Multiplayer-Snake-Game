/*
 * DLinkedList.h
 *
 *  Created on: Dec 8, 2022
 *      Author: Scott Chen
 */

#ifndef DLINKEDLIST_H_
#define DLINKEDLIST_H_

// Node Template Class – Supporting Different Data Types
template <typename E>
class DpNode
{
	public:
		E data;
		DpNode<E> *next;
		DpNode<E> *prev;

		DpNode(const E &e, DpNode<E> *n, DpNode<E> *p)
		{
			data = e;
			next = n;
			prev = p;
		}
};


template <typename E>
class DLinkedList
{
	private:
		DpNode<E> *head;  	// data member
		DpNode<E> *tail;  	// data member
		int size;

	public:	// Public Interface
		DLinkedList();		// Constructor
		~DLinkedList();		// Destructor

		int getSize();
		void makeEmpty();    		// Clear the entire list
		void addFirst(const E &e);	// Add Element to Head
		void addLast(const E &e);	// Add Element to Tail
		E removeFirst();			// Remove Element from Head
		E removeLast();				// Remove Element from Tail;
		void remove(const E &e);	// Remove specified value
		void printList();		 	// Output list contents

		// More functionalities can be added to ADT
};

#endif /* DLINKEDLIST_H_ */
