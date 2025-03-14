#pragma once
#include <iostream>

template < typename T>
class priNode
{
private:
    T item;		// A data item
    int pri;	//priority of the item
    priNode<T>* next; // Pointer to next node
public:
    priNode(const T& r_Item, int PRI)
    {
        setItem(r_Item, PRI);
        next = nullptr;
    }
    void setItem(const T& r_Item, int PRI)
    {
        item = r_Item;
        pri = PRI;
    }
    void setNext(priNode<T>* nextNodePtr)
    {
        next = nextNodePtr;
    }

    T getItem(int& PRI) const
    {
        PRI = pri;
        return item;
    }

    priNode<T>* getNext() const
    {
        return next;
    }

    int getPri() const
    {
        return pri;
    }
}; // end Node

//This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue
template <typename T>
class priQueue
{
protected:
    priNode<T>* head;
public:
    priQueue() : head(nullptr) {
        count = 0;
    }
    int count = 0;
    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }

    //insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);
        count++;
        if (head == nullptr || priority > head->getPri()) {

            newNode->setNext(head);
            head = newNode;
            return;
        }

        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        count--;
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        pri = head->getPri();
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void print()
    {
        priNode<T>* iteratorPtr = head;
        if (!iteratorPtr)
        {
            std::cout << "[EMPTY]" << std::endl;
            return;
        }
        std::cout << "[ ";
        while (iteratorPtr)
        {
            int pri;
			std::cout << *(iteratorPtr->getItem(pri));
			if (iteratorPtr->getNext())
			{
				std::cout << " --> ";
			}
			iteratorPtr = iteratorPtr->getNext();
        }
        std::cout << " ]" << std::endl;
		return;
    }

    priNode<T>* getHead()
    {
        return head;
    }

    priQueue(const priQueue<T>& PQ)
    {
        head = nullptr;
        priNode<T>* NodePtr = PQ.head;	//start at the front node in PQ
        while (NodePtr)
        {
            int pri;
            enqueue(NodePtr->getItem(pri), NodePtr->getPri());	//get data of each node and enqueue it in this queue 
            NodePtr = NodePtr->getNext();
        }
    }
};
