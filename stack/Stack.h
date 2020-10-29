#include "LinkedList.h"

#ifndef STACK_H
#define STACK_H

template <class T> class Stack
{
    public:

        /* constructors */
        Stack();
        Stack(Stack<T> &stack);

        /* destructor */
        ~Stack();

        /* true if empty */
        bool isEmpty();

        /* empties stack */
        void clear();

        /* return number of elements in stack */
        int size();

        /* return element at top of stack */
        T top();

        /* remove element at top of stack. returns that element */
        T pop();

        /* add element to top of stack */
        void push(T elt);

    private:

        int           numElts;
        LinkedList<T> elts;
};

template <class T> Stack<T>::Stack()
{
    numElts = 0;
}

template <class T> Stack<T>::Stack(Stack<T> &stack)
{
    for (int i = 0; i < stack.size(); ++i) {
        elts.pushAtBack(stack.elts.at(i));
        std::cout << elts.at(i) << std::endl;
    }

    numElts = stack.size();
}

template <class T> Stack<T>::~Stack()
{}

template <class T> bool Stack<T>::isEmpty()
{
    return numElts == 0;
}

template <class T> void Stack<T>::clear()
{
    elts.clear();
    numElts = 0;
}

template <class T> int Stack<T>::size()
{
    return numElts;
}

template <class T> T Stack<T>::top()
{
    return elts.back();
}

template <class T> T Stack<T>::pop()
{
    --numElts; 
    return elts.popFromBack(); 
}

template <class T> void Stack<T>::push(T elt)
{
    elts.pushAtBack(elt); 
    ++numElts;    
}

#endif
