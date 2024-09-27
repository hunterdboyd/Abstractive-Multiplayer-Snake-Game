#include "objPosDlinkedList.h"
#include <iostream>
using namespace std;


objPosDLinkedList::objPosDLinkedList()
{
    //dummy nodes    
    listHead = new DNode();
    listTail = new DNode();
    listHead->next = listTail;
    listTail->prev = listHead;

    persistHead = listHead->next;

    listSize = 0;
}

objPosDLinkedList::~objPosDLinkedList()
{
    DNode* currentElement = listHead;
    DNode* targetElement = listHead;

    while(currentElement != nullptr)
    {
        currentElement = currentElement->next;
        delete targetElement;
        targetElement = currentElement;
    }
}

int objPosDLinkedList::getSize()
{
    return listSize;
}

int objPosDLinkedList::isEmpty()
{
    return (listSize == 0);
}

void objPosDLinkedList::insertHead(const objPos &thisPos)
{
    DNode* temp = new DNode();
    temp->data.setX(thisPos.getX());
    temp->data.setY(thisPos.getY());
    temp->data.setNum(thisPos.getNum());
    temp->data.setPF(thisPos.getPF());
    temp->data.setSym(thisPos.getSym());

    temp->next = listHead->next;  // old head is now the second element
    temp->prev = listHead;
    listHead->next = temp;  // new head is the current element
    temp->next->prev = temp;
    
    listSize++;
}

void objPosDLinkedList::insertTail(const objPos &thisPos)
{
    DNode* temp = new DNode();
    temp->data.setX(thisPos.getX());
    temp->data.setY(thisPos.getY());
    temp->data.setNum(thisPos.getNum());
    temp->data.setPF(thisPos.getPF());
    temp->data.setSym(thisPos.getSym());
    
    temp->prev = listTail->prev;
    temp->next = listTail;
    listTail->prev = temp;
    temp->prev->next = temp;

    listSize++;
}

void objPosDLinkedList::insert(const objPos &thisPos, int index)
{
    if(index < 0) index = 0;
    if(index > listSize - 1) index = listSize - 1;

    DNode* readerHead = listHead; 
    
    DNode* temp = new DNode();
    temp->data.setX(thisPos.getX());
    temp->data.setY(thisPos.getY());
    temp->data.setNum(thisPos.getNum());
    temp->data.setPF(thisPos.getPF());
    temp->data.setSym(thisPos.getSym());
    temp->next = NULL;

    // traverse to the target insertion spot
    for(int i = 0; i < index; i++)
        readerHead = readerHead->next;

    temp->next = readerHead->next;
    temp->prev = readerHead;
    readerHead->next = temp;
    temp->next->prev = temp;

    listSize++;
}

objPos objPosDLinkedList::getHead() const
{
    return listHead->next->data;
}

objPos objPosDLinkedList::getTail() const
{
    return listTail->prev->data;
}

objPos objPosDLinkedList::get(int index) const
{
    DNode* readerHead = listHead->next; 
    // traverse to the target insertion spot
    for(int i = 0; i < index; i++)
        readerHead = readerHead->next;

    return readerHead->data;
}

objPos objPosDLinkedList::getNext()
{
    if(persistHead == listTail)
    {
        persistHead = listHead->next;
        cout << "reader head reaching the END!" << endl;        
        return objPos(-99,0,0,0,0); // indicating end of list
    }
    
    objPos temp = persistHead->data;
    persistHead = persistHead->next;
    return temp;
}

void objPosDLinkedList::resetReadPos()
{
    persistHead = listHead->next;
}

void objPosDLinkedList::set(const objPos &thisPos, int index)
{
    if(index < 0) index = 0;
    if(index > listSize - 1) index = listSize - 1;
    
    DNode* readerHead = listHead->next; 
    // traverse to the target replacement spot
    for(int i = 0; i < index; i++)
        readerHead = readerHead->next;

    readerHead->data.setX(thisPos.getX());
    readerHead->data.setY(thisPos.getY());
    readerHead->data.setNum(thisPos.getNum());
    readerHead->data.setPF(thisPos.getPF());
    readerHead->data.setSym(thisPos.getSym());
}


objPos objPosDLinkedList::removeHead()
{
    if(listSize == 0) return objPos(-99,0,0,0,0);  // do not delete if no elements to delete
    
    DNode* target = listHead->next;  // set deletion target to first element
    listHead->next = target->next;  // skip the link over the first element
    target->next->prev = listHead;  // set the prev pointer properly
    objPos tempPos = target->data;
    delete target;  // remove the head element
    
    listSize--;
    return tempPos;
}

objPos objPosDLinkedList::removeTail()
{
    if(listSize == 0) return objPos(-99,0,0,0,0);

    DNode* target = listTail->prev;
    listTail->prev = target->prev;
    target->prev->next = listTail;
    objPos tempPos = target->data;
    delete target;

    listSize--;
    return tempPos;
}

objPos objPosDLinkedList::remove(int index)
{
    if(listSize == 0) return objPos(-99,0,0,0,0);
    if(index <= 0) return removeHead();
    if(index >= listSize) return removeTail();
    
    DNode* target;
    DNode* readerHead = listHead; 
    // traverse to the element before the target
    for(int i = 0; i < index - 1; i++)
        readerHead = readerHead->next;
    
    target = readerHead->next;  // set deletion target
    readerHead->next = target->next;  // skip the link over the target
    target->next->prev = readerHead;
    objPos tempPos = target->data;
    delete target;

    listSize--;
    return tempPos;
}


void objPosDLinkedList::printList() const
{
    DNode* readerHead = listHead;  // skip the header
    
    cout << "List Contains:" << endl;
    cout << "Dummy: ";
    
    while(readerHead != listTail)
    {
        cout << readerHead << " :: ";
        readerHead->data.printObjPos();
        cout << "prev(" << readerHead->prev << ") ";
        cout << "next(" << readerHead->next << ")" << endl;
        readerHead = readerHead->next;
    }

    cout << "Dummy:";
    cout << readerHead << " :: ";
    readerHead->data.printObjPos();
    cout << "prev(" << readerHead->prev << ") ";
    cout << "next(" << readerHead->next << ")" << endl;

    cout << "END OF LIST" << endl;

    cout << "List Head: " << listHead << endl;
    cout << "List Tail: " << listTail << endl;
    cout << "List Size: " << listSize << endl;
    cout << "Internal Reader Head Pos: " << persistHead << endl;
}


