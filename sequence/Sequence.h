#ifndef SEQUENCE_H_ 
#define SEQUENCE_H_ 

template <class T> class Sequence
{
    public:

        /* Constructor 
         *  - Sequence() - Default constructor, size is 0, cpacity is 0
         *  - Sequence(int n, T init) - Constructs sequence of size n, all
         *    elements initialized to init.
         *  - Sequence(T elts[], int n) - Constructs sequence with a copy of
         *    each of the elements in initArray in the same order. n is size
         *    of initArray. */        
        Sequence();
        Sequence(int n);       
        Sequence(int n,    T   init); 
        Sequence(T elts[], int n);
        Sequence(Sequence<T> &seq);

        /* Destructpr */
        ~Sequence();        

        /* Capacity
         *  - int size() returns number of elements in container
         *  - int cap () returns size of allocated storage capacity, in 
         *    terms of elements.
         *  - bool isEmpty() true if container is empty (size == 0) 
         *  - void reserve(int n) requests that capacity be at least enough 
         *    to contain n elements. If n is greater than current capacity, 
         *    causes container to reallocate its storage, increasing its 
         *    capacity to n.
         *    In all other cases, does not cause reallocation and capacity 
         *    unaffected. */
        int  size   ();
        int  cap    ();
        bool isEmpty();  
        void reserve(int n);

        /* Element access
         *  - T &operator[] (int n) returns reference to element at index n.
         *      * when n out of range, causes undefined behavior
         *  - T &at (int n) is like operator[] but raises range error if n 
         *    out of bounds.
         *  - front, back return reference to first, last element in 
         *    container. 
         *      * when container empty, raises range error */
        T &operator[] (int n);        
        T &at         (int n);
        T &front      ();
        T &back       ();

        /* Modifiers
         *  - void clear() clears elements from container, does not change 
         *    size of allocated storage capacity.
         *  - void memClear() clears elements from container, deletes 
         *    elements. Capacity set to 0.
         *  - void reset(T elt) sets all elements in container to elt. 
         *  - void pushAtBack(T elt) adds new element to end of sequence.
         *  - T popFromBack() removes last element in sequence, returns 
         *    element.
         *  - void insertAt(T elt, int n) inserts elt before the element
         *    at index n All elements after (to right of index n) are 
         *    shifted right by 1 .
         *  - void removeAt(int n) removes element at index n. All elements
         *    after (to right of index n) are shifted left by 1 
         *  - void concat(Sequence<T> *seq) concateneates the elements in 
         *    seq to the end of current container.*/
        void clear      ();
        void memClear   ();
        void reset      (T elt);
        void pushAtBack (T elt);
        T    popFromBack();
        void insertAt   (T elt, int n); 
        T    removeAt   (int n);
        void concat(Sequence<T> *seq);

    private:

        int capacity, numElts, resFactor; //Factor by which amount of previously allocated memory is expanding upon reserve
        T   *elts;
};

template <class T> Sequence<T>::Sequence()
{
    elts      = new T[0];
    capacity  = 0;
    numElts   = 0;
    resFactor = 2;    
}

template <class T> Sequence<T>::Sequence(int n)
{	
    elts      = new T[n];
    capacity  = n; 
    numElts   = 0;
    resFactor = 2;
}

template <class T> Sequence<T>::Sequence(int n, T init)
{	
    elts        = new T[n];
    for (int i  = 0; i < n; ++i)
        elts[i] = init;
    capacity    = n;
    numElts     = n;
    resFactor   = 2;
}

template <class T> Sequence<T>::Sequence(T initArray[], int n)
{	
    elts     = new T[n];
    std::copy(initArray, initArray + n, elts);
    capacity    = n;
    numElts     = n;
    resFactor   = 2;
}

template <class T> Sequence<T>::Sequence(Sequence<T> &initSeq)
{
    int initSize = initSeq.size();

    elts        = new T[initSize];
    std::copy(initSeq.elts, initSeq.elts + initSeq.numElts, elts);
    capacity    = initSize;
    numElts     = initSize;
    resFactor   = 2;
}

template <class T> Sequence<T>::~Sequence()
{
    delete [] elts; 
}

template <class T> int Sequence<T>::size()
{
	return numElts;
}

template <class T> int Sequence<T>::cap()
{
	return capacity;
}

template <class T> bool Sequence<T>::isEmpty()
{
	return numElts == 0;
}

template <class T> void Sequence<T>::reserve(int n)
{
    if (n <= capacity) return;

    T *reserved = new T[n];

    std::copy(elts, elts + numElts, reserved);
        
    delete [] elts;        
    capacity = n;
    elts     = reserved;
}

template <class T> T &Sequence<T>::operator[] (int n)
{
    return elts[n];
}

template <class T> T &Sequence<T>::at(int n)
{     
    if (n < 0 || n >= numElts)
        throw std::out_of_range("element_access_out_of_range:");

    return elts[n];
}

template <class T> T &Sequence<T>::front()
{
    return at(0);
}

template <class T> T &Sequence<T>::back()
{     
    return at(numElts - 1); 
}

template <class T> void Sequence<T>::clear()
{
    numElts = 0;    
}

template <class T> void Sequence<T>::memClear()
{
    delete [] elts;
    elts     = new T[0];
    numElts  = 0;    
    capacity = 0;
}

template <class T> void Sequence<T>::reset(T elt)
{
    for (int i = 0; i < numElts; ++i) 
        elts[i] = elt; 
}

template <class T> void Sequence<T>::pushAtBack(T elt)
{
    if (numElts == capacity)
        reserve(resFactor * capacity + 1); 
    elts[numElts] = elt;
    ++numElts;
}

template <class T> T Sequence<T>::popFromBack()
{
    T elt = back();
    --numElts;
    return elt;
}

template <class T> void Sequence<T>::insertAt(T elt, int n)
{
    if (n < 0 || n > numElts) 
        throw std::out_of_range("index_out_of_range");        

    if (n == numElts) {
        pushAtBack(elt); 
    } else {
        if (numElts == capacity)
            reserve(resFactor * capacity + 1);

        std::copy(elts + n, elts + numElts, elts + (n + 1));
        elts[n] = elt;
        ++numElts;
    }
}

template <class T> T Sequence<T>::removeAt(int n)
{
    T elt = at(n);

    std::copy(elts + (n + 1), elts + numElts, elts + n); 
    --numElts;     
    return elt;
}

template <class T> void Sequence<T>::concat(Sequence<T> *seq)
{
    if (numElts + seq->numElts > capacity)
        reserve(numElts + seq->numElts);

    std::copy(seq->elts, seq->elts + seq->numElts, elts + numElts);    
    numElts = numElts + seq->numElts;
}

#endif
