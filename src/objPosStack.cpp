#include "objPosStack.h"
#include "objPosDLinkedList.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

// Available Data Members from objPosStack.h (Must Review)
//
//      objPosList* myList
//      
//  This is the polymorphic list pointer to the underlying List data structure to
//   support all Stack functionalities
//
//  You should use objPosDLinkedList as your main design param


objPosStack::objPosStack()
{
    // Constructor
    //   Instantiate myList as objPosDLinkedList.  You may use objPosArrayList for testing purpose only.
    myList = new objPosDLinkedList();
}


objPosStack::~objPosStack()
{
    // Destructor
    //  Just delete myList (and all otherheap members, if any)
    delete myList;
}


// private helper function
void objPosStack::generateObjects(int count)
{
    // Generate and pushes individual objPos isntances with randomly generated Prefix, Number, and Symbol.
    // The total number of generated instances is capped by input variable **count**.

    // 1. Generate Prefix A-Z and a-z.  Alphabetic characters only.
    // 2. Generate Number [0, 99]
    // 3. Leave Symbol as *
    // Push every randomly generately objPos into the Stack.

    objPos temp(0,0,0,0,0);  
    int randCandidate;

    for(int i = 0; i < count; i++)
    {
        // Generate Prefix
        randCandidate = rand() % 26 + 'A';  // generaate 26 upper case alphabets
        //if(rand() % 2) randCandidate += 32;  // randomly lowercase the candidate
        temp.setPF((char)randCandidate);

        // Generate Number [0, 99]
        temp.setNum(rand() % 100);

        // Symbol should be fixed to *
        temp.setSym('*');

        // Push every randomly generately objPos into the Stack.
        push(temp);
    }
}


// private helper function
int objPosStack::sortByTenScoreBS()
{
    // Use BUBBLE SORT to sort all the objPos instances in the Stack in ascending order using the digit of 10
    //  of the **number** field of objPos.

    // You can use the relevant insertion and removal methods from the objPosDLinkedList interface
    //  to complete the sorting operations.

    // Recommendation - use set() and get()

    int passes = 0;
    int size = myList->getSize();
    bool notdone = false; 

    do
    {
        notdone = false;

        for(int i = 0; i < size - 1; i++)
        {
            objPos currPos = myList->get(i);
            objPos nextPos = myList->get(i + 1);

            // If ascending order in stack, then smaller elements move to tail
            if((currPos.getNum()/10) < (nextPos.getNum()/10))
            {
                // SWAP!
                myList->set(nextPos, i);
                myList->set(currPos, i + 1);

                notdone = true;
            }
        }
        passes++;
    } while(notdone);

    return passes;

}


void objPosStack::populateRandomElements(int size)
{
    // This function generates the number of randomly generated objPos instances with uninitialized
    //  x-y coordinate on the Stack, then sort them in ascending order using the digit of 10
    //  of the **number** field in objPos instances.

    // Implementation done.  You'd have to implement the following two private helper functions above.
    srand(time(NULL));
    generateObjects(size);
    sortByTenScoreBS();   // bubble sort
}



void objPosStack::push(const objPos &thisPos) const
{
    // Push thisPos on to the Stack.
    //  Think about which objPosDLinkedList method can realize this operation.
    
    // myList->insertTail(thisPos);  // may work on some systems

    // ALternative implementation
    objPos temp = thisPos;
    myList->insertTail(thisPos);  // definitely working
}

objPos objPosStack::pop()
{
    // Pop the top element of the Stack.
    //  If the Stack is empty, return objPos(-99, 0, 0, 0, 0)
    //  Think about which objPosDLinkedList method can realize this operation.
    if(myList->getSize() <= 0)
    {
        return objPos(-99, 0, 0, 0, 0);
    }
    return myList->removeTail();

    // what happens if the list is empty?
    //  nothing, because the underlying List implementation already
    //  takes care of the empty list condition

}

objPos objPosStack::top()
{
    // Return the top element of the Stack without removing it
    //  If the Stack is empty, return objPos(-99, 0, 0, 0, 0)
    //  Think about which objPosDLinkedList method can realize this operation.
    if(myList->getSize() <= 0)
    {
        return objPos(-99, 0, 0, 0, 0);
    }
    return myList->getTail();

    // What happens when the list is empty?
    //  Looking back to Lab 2 manual, getTail() never takes care
    //  of the empty case... in this case, we need to do something.
}

int objPosStack::size()
{
    // Return the size of the Stack 
    //  Think about which objPosDLinkedList method can realize this operation.
    return myList->getSize();
}

void objPosStack::printMe()
{
    // NOT GRADED
    //  Print the contents of the Stack
    //  Think about which objPosDLinkedList method can partially realize this operation.

    // IMPORTANT: USE THIS METHOD FOR DEBUGGING!!!
    cout << "vv Stack Bottom vv" << endl;
    myList->printList();
    cout << "^^ Stack Top ^^" << endl;
    cout << "Stack Size: " << myList->getSize() << endl;
}