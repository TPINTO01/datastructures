/* Linked List usign recursive features */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

template <class T> class LinkedList
{
    public:

        /* constructors */
        LinkedList();
        LinkedList(T elt);
        LinkedList(T elts[], int size);
        LinkedList(LinkedList<T> &list);

        /* destructor */
        ~LinkedList();        
    
        /* true if list is empty, otherwis false*/
        bool isEmpty();

        /* clears list */ 
        void clear();

        /* number of elements in List */
        int size();

        /* Acces first, last element */
        T front();
        T back();

        /* element at nth index */ 
        T at(int n);

        /* insert element at front, back of list */
        void pushAtFront(T elt);
        void pushAtBack(T elt);

        /* Insert element at nth index */ 
        void insertAt(T elt, int n); 

        /* remove elements at front, back of list */
        T popFromFront();
        T popFromBack();

        /* remove element at nth index */
        T removeAt(int n);

        /* replace element at nth index */
        T replaceAt(T elt, int n);

        /* concatenate list to end of LinkedList */
        void concat(LinkedList<T> *list);

        /* true if element exists in list*/
        bool has(T elt);

    private:

        int numNodes, currIndex;

        struct Node {
            T eltInNode;
            Node *next;
            Node *prev;
        };

        Node *first, *last, *curr;

        Node *newNode(T elt, Node *prevNode, Node *nextNode);
};

template <class T> LinkedList<T>::LinkedList()
{
	first     = NULL;
    last      = NULL;
	curr      = first;
    currIndex = 0;
	numNodes  = 0;
}

template <class T> LinkedList<T>::LinkedList(T elt)
{	
	first     = newNode(elt, NULL, NULL);
    last      = first;
	curr      = first;
    currIndex = 0;
	numNodes  = 1;
}

template <class T> LinkedList<T>::LinkedList(T elts[], int size)
{
	first     = newNode(elts[0], NULL, NULL);
	curr      = first;
    currIndex = 0;
	numNodes  = 1;
  
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
    first     = newNode(list.front(), NULL, NULL);    
    curr      = first;
    currIndex = 0;
    numNodes  = 1;
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
		Node *nextNode = curr->next;
		delete curr;
		curr = nextNode;
	}
	first = NULL;
    last  = NULL;
}

template <class T> bool LinkedList<T>::isEmpty()
{
	return size() == 0;
}

template <class T> void LinkedList<T>::clear()
{
    /* Base case : curr is NULL, list is clear */
    if (curr == NULL) {
        first = NULL;
        last  = NULL;
        curr  = first;
        return; 
    } 
 	Node *next = curr->next;
	delete curr;
	curr = next;
	--numNodes;
    clear();
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
    if (currIndex == n) {
        T elt     = curr->eltInNode; 
	    curr      = first;
        currIndex = 0;
        return elt;
    } 
	curr = curr->next;	
    ++currIndex;
    return at(n);
}

template <class T> void LinkedList<T>::pushAtFront(T elt)
{
	if (first == NULL) {
		first = newNode(elt, first, NULL);
        last  = first;
        curr  = first;
		++numNodes;
	} else {
		first->prev = newNode(elt, NULL, first);
		first       = first->prev;
        curr        = first;
		++numNodes;
	}
}

template <class T> void LinkedList<T>::pushAtBack(T elt)
{
	if(first == NULL) {
		first = newNode(elt, NULL, NULL);
        last  = first;
        curr  = first;
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
    else if (currIndex == n) {
 		Node *temp = newNode(elt, curr->prev, curr);
        curr->prev->next = temp;
        curr->prev       = temp;
		++numNodes;	
        curr      = first;
        currIndex = 0;       
    } else {
		curr = curr->next;
        ++currIndex;
        insertAt(elt, n);
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
        curr  = first;
        --numNodes;
    } else {
        first = first->next;    
	    delete first->prev;
        first->prev = NULL;
        curr        = first;
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
    if (currIndex == n) {
        T elt            = curr->eltInNode;       
    	curr->prev->next = curr->next;
	    curr->next->prev = curr->prev;
	    delete curr;
	    --numNodes;
        curr      = first;
        currIndex = 0;
        return elt;
    }
    curr = curr->next;
    ++currIndex;
    return removeAt(n);
}

template <class T> T LinkedList<T>::replaceAt(T elt, int n)
{
	if (n < 0 || n >= numNodes)
		throw std::range_error("index_out_of_range");
    if (currIndex == n) {
        T oldElt = curr->eltInNode;
	    curr->eltInNode = elt;
        curr            = first;
        currIndex       = 0;
        return oldElt;
    }
    curr = curr->next;
    ++currIndex;
    return replaceAt(elt, n);
}

/* TODO: Use recursive features */
template <class T> void LinkedList<T>::concat(LinkedList<T> *list)
{
    last->next = newNode(list->front(), last, NULL);
    curr = last->next;
    ++numNodes;
    for (int i = 1; i < list->size(); ++i) {
        curr->next = newNode(list->at(i), curr, NULL);
        curr       = curr->next;
        ++numNodes;
    }
    last = curr;    
    curr = first;
}

template <class T> bool LinkedList<T>::has(T elt)
{
	if (first == NULL || curr == NULL) {
        curr = first;
		return false;
    }
    if (curr->eltInNode == elt) {
        curr = first;
        return true;
    } 
	curr = curr->next;
    return has(elt);
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
