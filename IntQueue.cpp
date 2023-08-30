#include <iostream>
#include "IntQueue.h"
using namespace std;

//*****************************************
// Constructor - creates an empty queue   *
// with given number of elements          *
//*****************************************
IntQueue::IntQueue(int s)
{
	queueArray = new int[s];
	queueSize = s;
	front = -1;
	rear = -1;
	numItems = 0;
}

/**
 * @brief Deep-copy constructor
 * @param s
 */
IntQueue::IntQueue(const IntQueue & q)
{
    queueArray = new int[q.queueSize];
    queueSize = q.queueSize;
    // Deep copy operation
    for (int i = 0; i < q.queueSize; ++i) {
        queueArray[i] = q.queueArray[i];
    }
    front = q.front;
    rear = q.rear;
    numItems = q.numItems;
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void IntQueue::enqueue(int num)
{
	if (isFull())
    {
        cout << "ERROR: Trying to enqueue to a full queue! Terminating..." << endl;
        exit(5);
    }
	else
	{
		// Calculate the new rear position circularly.
		rear = (rear + 1) % queueSize;
		// Insert new item.
		queueArray[rear] = num;
		// Update item count.
		numItems++;
	}
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void IntQueue::dequeue(int &num)
{
	if (isEmpty())
	{
        cout << "ERROR: Trying to dequeue from an empty queue! Terminating..." << endl;
        exit(6);
    }
	else
	{
		// Move front.
		front = (front + 1) % queueSize;
		// Retrieve the front item.
		num = queueArray[front];
		// Update item count.
		numItems--;
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool IntQueue::isEmpty() const
{
	if (numItems > 0)
		return false;
	else
		return true;	
}

//********************************************
// Function isFull returns true if the queue *
// is full, and false otherwise.             *
//********************************************
bool IntQueue::isFull() const
{
	if (numItems < queueSize)
		return false;
	else
		return true;
}

//*******************************************
// Function clear resets the front and rear *
// indices, and sets numItems to 0.         *
//*******************************************
void IntQueue::clear()
{
	front =  - 1;
	rear =  - 1;
	numItems = 0;
}

/**
 * @brief Destructor
 */
IntQueue::~IntQueue() {
    delete [] queueArray;
    queueSize = 0;
    front = -1;
    rear = -1;
    numItems = 0;
}

IntQueue &IntQueue::operator=(const IntQueue & rhs) {
    if (this == &rhs){
    }
    else
    {
        if (this->queueSize != rhs.queueSize)
        {
            delete [] queueArray;
            queueArray = new int[rhs.queueSize];
            queueSize = rhs.queueSize;
            // Deep assignment
            for (int i = 0; i < queueSize; i++) {
                queueArray[i] = rhs.queueArray[i];
            }
            front = rhs.front;
            rear = rhs.rear;
            numItems = rhs.numItems;
        }
    }
    return *this;
}
