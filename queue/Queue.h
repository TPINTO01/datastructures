#include "LinkedList.h"

#ifndef QUEUE_H 
#define QUEUE_H

template <class T> class Queue
{
    public:

        /* constructors */
        Queue();
        Queue(Queue<T> &queue);

        /* destructor */
        ~Queue();

        /* true if empty */
        bool isEmpty();

        /* empties queue */
        void clear();

        /* return number of elements in queue */
        int size();

        /* return element at front of queue */
        T front();

        /* remove element at front of queue. returns that element */
        T pop();

        /* add element to end of queue */
        void push(T elt);

    private:

        int           numElts;
        LinkedList<T> elts;
};

template <class T> Queue<T>::Queue()
{
    numElts = 0;
}

template <class T> Queue<T>::Queue(Queue<T> &queue)
{
    for (int i = 0; i < queue.size(); ++i) 
        elts.pushAtBack(queue.elts.at(i));

    numElts = queue.size();
}

template <class T> Queue<T>::~Queue()
{}

template <class T> bool Queue<T>::isEmpty()
{
    return numElts == 0;
}

template <class T> void Queue<T>::clear()
{
    elts.clear();
    numElts = 0;
}

template <class T> int Queue<T>::size()
{
    return numElts;
}

template <class T> T Queue<T>::front()
{
    return elts.front();
}

template <class T> T Queue<T>::pop()
{
    --numElts; 
    return elts.popFromFront(); 
}

template <class T> void Queue<T>::push(T elt)
{
    ++numElts;    
    elts.pushAtBack(elt); 
}

#endif
