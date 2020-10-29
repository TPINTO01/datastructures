#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

template <class T> class LinkedList
{
    public:
        /* Constructor 
         *  - Sequence() - Default constructor, size is 0, cpacity is 0
         *  - Sequence(int n, T init) - Constructs sequence of size n, all
         *    elements initialized to init.
         *  - Sequence(T elts[], int n) - Constructs sequence with a copy of
         *    each of the elements in initArray in the same order. n is size
         *    of initArray. */        
        LinkedList();
        LinkedList(T elt);
        LinkedList(T elts[], int size);
        LinkedList(LinkedList<T> &list);       
    
        /* destructor */
        ~LinkedList();            

        /* Capacity
         *  - int size() returns number of elements in container 
         *  - bool isEmpty() true if container is empty (size == 0) */
        int size();
        bool isEmpty();
    
        /* Element access
         *  - T &operator[] (int n) returns reference to element at index n.
         *      * when n out of range, causes undefined behavior
         *  - T at (int n) returns copy of element at index n. \
         *  - front, back return copy of first, last element in 
         *    container. 
         *      * when container empty, raises range error */
        T &operator[] (int n);
        T at   (int n);
        T front();
        T back ();

        /* Modifiers
         *  - void clear() clears elements from container, does not change 
         *    size of allocated storage capacity.
         *  - void pushAtFront(T elt) inserts element at front of list
         *  - void pushAtBack (T elt) inserts element at back of list
         *  - void insertAt(T elt, int n) inserts element at index n
         *  - T popFromFront() removes first element, returns elements.
         *  - T popFromBack () removes last element, returns removed element.
         *  - T removeAt(int n) removes element at index n, returns removed element.
         *  - T replaceAt(T elt, int n) replaces element at index n with elt. returns replaced element.
         *  - void concat(LinkedList<T> *list) concatenates list to end of LinkedList
         *  - bool has(T elt) returns true if element exists in container */
        void clear();
        void pushAtFront(T elt);
        void pushAtBack (T elt);
        void insertAt   (T elt, int n); 
        T    popFromFront();
        T    popFromBack ();
        T    removeAt    (int n);
        T    replaceAt   (T elt, int n);
        void concat(LinkedList<T> *list);
        bool has(T elt);

    private:

        int numNodes;   

        struct Node {
            T eltInNode;
            Node *next, *prev;
        };

        Node *first, *last, *curr;

        Node *newNode(T elt, Node *prevNode, Node *nextNode);
};

template <class T> LinkedList<T>::LinkedList()
{
	first    = NULL;
    last     = NULL;
	curr     = first;
	numNodes = 0;
}

template <class T> LinkedList<T>::LinkedList(T elt)
{	
	first    = newNode(elt, NULL, NULL);
    last     = first;
	curr     = first;
	numNodes = 1;
}

template <class T> LinkedList<T>::LinkedList(T elts[], int size)
{
	first    = newNode(elts[0], NULL, NULL);
	curr     = first;
	numNodes = 1;
	for (int i = 1; i < size; ++i) {
		curr->next = newNode(elts[i], curr, NULL);
		curr       = curr->next;
        ++numNodes;
	}
    last = curr;
    curr = first;
}

template <class T> LinkedList<T>::LinkedList(LinkedList<T> &list)
{
    first = newNode(list.front(), NULL, NULL);    
    curr  = first;
    numNodes = 1;
    for (int i = 1; i < list.size(); ++i) {
        curr->next = newNode(list.at(i), curr, NULL);
        curr       = curr->next;
        ++numNodes;
    }
    last = curr;    
    curr = first;
}

template <class T> LinkedList<T>::~LinkedList()
{
    curr = first;
	while (curr != NULL) {
		Node *temp = curr->next;
		delete curr;
		curr = temp;
	}
	first = NULL;
    last  = NULL;
}

template <class T> T &LinkedList<T>::operator[] (int n)
{
	if ((n < 0) || (n >= numNodes))
		throw std::range_error("index_out_of_range");
    if (n == 0)
        return first->eltInNode;
    if (n == numNodes - 1)
        return last->eltInNode;

	curr = first;
	for(int i = 0; i < n; ++i) 
		curr = curr->next;	

	return curr->eltInNode;
}

template <class T> bool LinkedList<T>::isEmpty()
{
	return size() == 0;
}

template <class T> void LinkedList<T>::clear()
{
	curr = first;
	while (curr != NULL) {
		Node *next = curr->next;
		delete curr;
		curr = next;
		--numNodes;
	}
	first = NULL;
    last  = NULL;
}

template <class T> int LinkedList<T>::size()
{
	return numNodes;
}

template <class T> T LinkedList<T>::front()
{
	if (first == NULL)
		throw std::runtime_error("list_is_empty");
	return first->eltInNode;
}

template <class T> T LinkedList<T>::back()
{
	if (last == NULL)
		throw std::runtime_error("list_is_empty");
	return last->eltInNode;
}

template <class T> T LinkedList<T>::at(int n)
{
	if ((n < 0) || (n >= numNodes))
		throw std::range_error("index_out_of_range");
    if (n == 0)
        return first->eltInNode;
    if (n == numNodes - 1)
        return last->eltInNode;

	curr = first;
	for(int i = 0; i < n; ++i) 
		curr = curr->next;	

	return curr->eltInNode;
}

template <class T> void LinkedList<T>::pushAtFront(T elt)
{
	if (first == NULL) {
		first = newNode(elt, first, NULL);
        last  = first;
		++numNodes;
	} else {
		first->prev = newNode(elt, NULL, first);
		first       = first->prev;
		++numNodes;
	}
}

template <class T> void LinkedList<T>::pushAtBack(T elt)
{
	if (first == NULL) {
		first = newNode(elt, NULL, NULL);
        last  = first;
		++numNodes;
	} else {
        last->next = newNode(elt, last, NULL);
        last       = last->next;
	    ++numNodes;
    }
}

template <class T> void LinkedList<T>::insertAt(T elt, int n)
{
	if (n < 0 || n > numNodes)
        throw std::range_error("index_out_of_range");
    else if (n == 0)
		pushAtFront(elt);
    else if (n == numNodes)
		pushAtBack(elt);
    else {
		curr = first;
		for (int i = 0; i < n; ++i) 
			curr = curr->next;

		curr->prev->next = newNode(elt, curr->prev, curr);
        curr->prev       = curr->prev->next;
		++numNodes;	
    }
}

template <class T> T LinkedList<T>::popFromFront()
{
	if (first == NULL)
		throw std::runtime_error("list_is_empty");
    T elt = first->eltInNode;
    if (first->next == NULL) {
        delete first;
        first = NULL;
        last  = NULL;
        --numNodes;
    } else {
        first = first->next;    
	    delete first->prev;
        first->prev = NULL;
        curr = first;
	    --numNodes;
    }
    return elt;
}

template <class T> T LinkedList<T>::popFromBack()
{
	if (first == NULL)
		throw std::runtime_error("list_is_empty");
    T elt = last->eltInNode;
    if (last->prev == NULL) {
        delete last;
        last  = NULL;
        first = NULL;
        curr  = NULL;
        --numNodes;
    } else {
        last = last->prev;
        delete last->next;
        last->next = NULL;
	    --numNodes; 
    }
    return elt;
}

template <class T> T LinkedList<T>::removeAt(int n)
{
	if (n < 0 || n >= numNodes)
		throw std::range_error("index_out_of_range");
	if (n == 0)
		return popFromFront();
	if ( n == numNodes - 1)
		return popFromBack();	

    curr = first;
	for(int i = 0; i < n; ++i) 
		curr = curr->next;

    T elt = curr->eltInNode;
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;
	delete curr;
    curr = first;
	numNodes--;

    return elt;
}

template <class T> T LinkedList<T>::replaceAt(T elt, int n)
{
	if (n < 0 || n >= numNodes)
		throw std::range_error("index_out_of_range");

	curr = first;
	for (int i = 0; i < n; ++i) 
		curr = curr->next;

    T oldElt        = curr->eltInNode;
	curr->eltInNode = elt;

    return oldElt;
}


template <class T> void LinkedList<T>::concat(LinkedList<T> *list)
{
    if (list->isEmpty())
        return;

    last->next = newNode(list->front(), last, NULL);
    curr = last->next;
    ++numNodes;

    for (int i = 1; i < list->size(); ++i) {
        curr->next = newNode(list->at(i), curr, NULL);
        curr       = curr->next;
        ++numNodes;
    }
    last = curr;    
}

template <class T> bool LinkedList<T>::has(T elt)
{
	if (first == NULL)
		return false;
	curr = first;
 	while (curr != NULL) {
        if (curr->eltInNode == elt)
            return true;
		curr = curr->next;
	}    
	return false;
}


/**************** private helpers ****************/

template <class T> 
typename LinkedList<T>::Node *LinkedList<T>::newNode(T elt, 
                                                     Node *prevNode, 
                                                     Node *nextNode)
{
	Node *newNode = new Node;
	newNode->eltInNode = elt;
	newNode->next = nextNode;
	newNode->prev = prevNode;
	return newNode;
}

#endif
