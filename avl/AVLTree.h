#ifndef AVLTREE_H_
#define AVLTREE_H_

/**************************************************************************
 *                                                                        *
 *                           AVLNode Class                                *
 *                                                                        *
 *************************************************************************/

template <class T> class AVLNode
{
    public:
        AVLNode();
        AVLNode(T newElt);
        ~AVLNode();

        bool insert(AVLNode<T> *&subRoot, T elt, bool &taller, 
                                              int (*cmp) (T, T));

        T getElt() const { return elt; }
        T &getElt() { return elt; }
        AVLNode *getRight() const { return right; }
        AVLNode *getLeft()  const { return left; }
        AVLNode *&getRight() { return right; }
        AVLNode *&getLeft()  { return left; }
        void setRight(AVLNode *newRight) { right = newRight; }
        void setLeft (AVLNode *newLeft)  { left = newLeft; }

    private:
        T        elt;
        AVLNode *left, *right;
        int      bal,   height;

        void rightBal(AVLNode<T> *&subRoot);
        void leftBal (AVLNode<T> *&subRoot);
        void rightRot(AVLNode<T> *&subRoot);
        void leftRot (AVLNode<T> *&subRoot);
};

template <class T>
AVLNode<T>::AVLNode()
{
    left  = NULL;
    right = NULL; 
}

template <class T>
AVLNode<T>::AVLNode(T newElt)
{
    elt   = newElt;
    left  = NULL;
    right = NULL; 
    bal   = 0;
}

template <class T>
AVLNode<T>::~AVLNode() {}

template <class T>
bool AVLNode<T>::insert(AVLNode<T> *&subRoot, const T elt, bool &taller,
                                                     int (*cmp) (T, T))
{
    bool result = true;
    if (!subRoot) {
        subRoot = new AVLNode(elt);
        taller  = true;
    } else if (cmp (elt, subRoot->elt) == 0) {
        result = false;
        taller = true;
    } else if (cmp(elt, subRoot->elt) < 0) {
        result = insert(subRoot->getLeft(), elt, taller, cmp);
        if (taller) {
            switch (subRoot->bal) {
                case -1 :
                    leftBal(subRoot);
                    taller = false;
                    break;
                case 0 :
                    subRoot->bal = -1;
                    break;
                case 1 :
                    subRoot->bal = 0;
                    taller = false;
                    break;
            }
        }
    } else if (cmp(elt, subRoot->elt) > 0) {
        result = insert(subRoot->getRight(), elt, taller, cmp);
        if (taller) {
            switch (subRoot->bal) {
                case -1 :
                    subRoot->bal = 0; 
                    taller = false;
                    break;
                case 0 :
                    subRoot->bal = 1;
                    break;
                case 1 :
                    rightBal(subRoot); 
                    taller = false;
                    break;
            }
        }
    }     
    return result;    
}


/**************************** Private Members ****************************/

template <class T>
void AVLNode<T>::rightBal(AVLNode<T> *&subRoot)
{
    AVLNode *&rightTree = subRoot->getRight();
    switch (rightTree->bal) {
        case 1 :
            subRoot->bal = 0;
            rightTree->bal   = 0;
            leftRot(subRoot);
            break;
        case 0 :
            std::cout << "WARNING: program error in rightBal" << std::endl;
            break;
        case -1 :
            AVLNode *subTree = rightTree->getLeft();
            switch (subTree->bal) {
                case 0 :
                    subRoot->bal = 0;
                    rightTree->bal   = 0;
                    break;
                case -1 : 
                    subRoot->bal = 0;
                    rightTree->bal   = 1;
                    break;
                case 1 :
                    subRoot->bal = -1;
                    rightTree->bal   =  0;
                    break;
            }
            subTree->bal = 0;
            rightRot(rightTree);
            leftRot (subRoot);
            break;
    }
}

template <class T>
void AVLNode<T>::leftBal(AVLNode<T> *&subRoot)
{
    AVLNode *&leftTree = subRoot->getLeft();
    switch (leftTree->bal) {
        case -1 :
            subRoot->bal = 0;
            leftTree->bal    = 0;
            rightRot(subRoot);
            break;
        case 0 :
            std::cout << "WARNING: program error in leftBal" << std::endl;
            break;
        case 1 :
            AVLNode *subTree = leftTree->getRight();
            switch (subTree->bal) {
                case 0 :
                    subRoot->bal = 0;
                    leftTree->bal   = 0;
                    break;
                case -1 : 
                    subRoot->bal = 0;
                    leftTree->bal   = 1;
                    break;
                case 1 :
                    subRoot->bal = -1;
                    leftTree->bal   =  0;
                    break;
            }
            subTree->bal = 0;
            leftRot  (leftTree);
            rightRot (subRoot);
            break;
    }
}

template <class T>
void AVLNode<T>::rightRot(AVLNode<T> *&subRoot)
{
    if (subRoot == NULL || subRoot->getLeft() == NULL) {
        std::cout << "WARNING: program error detected in rotate right" << std::endl;
    } else {
        AVLNode *leftTree = subRoot->getLeft();
        subRoot->setLeft(leftTree->getRight());
        leftTree->setRight(subRoot);
        subRoot = leftTree;
    }
}

template <class T>
void AVLNode<T>::leftRot(AVLNode<T> *&subRoot)
{
    if (subRoot == NULL || subRoot->right == NULL) {
        std::cout << "WARNING: program error detected in rotate left" << std::endl;
    } else {
        AVLNode *rightTree = subRoot->right;
        subRoot->setRight(rightTree->getLeft());
        rightTree->setLeft(subRoot);
        subRoot         = rightTree;
    }
}


/**************************************************************************
 *                                                                        *
 *                           AVLTree Class                                *
 *                                                                        *
 *************************************************************************/

template <class T> class AVLTree
{
    public:
        AVLTree(int (*cmpFun) (T, T));
        AVLTree(T elts[], int n, int (*cmpFun) (T, T));
        ~AVLTree();

        bool insert(T elt);              
//        bool remove(T elt);
//        bool has   (T elt);
        
        void printInOrder();

    private:
        AVLNode<T> *root;
        int numElts;
        int (*cmp) (T, T);

        void printInOrder(AVLNode<T> *&subRoot);
};

template <class T>        
AVLTree<T>::AVLTree(int (*cmpFun) (T, T)) 
{
    root    = NULL;
    numElts = 0;
    cmp     = cmpFun;    
}

template <class T>
AVLTree<T>:: AVLTree(T elts[], int n, int (*cmpFun) (T, T))
{
    root    = NULL;
    numElts = 0;
    cmp     = cmpFun;
    for (int i = 0; i < n; ++i) {
        insert(elts[i]);
    }
}

template <class T>        
AVLTree<T>::~AVLTree() {}

template <class T>
bool AVLTree<T>::insert(T elt)
{
    bool taller = false;
    if (root->insert(root, elt, taller, cmp)) {
        ++numElts;
        return true;
    }
    
    return false;
}

template <class T>
void AVLTree<T>::printInOrder()
{
    printInOrder(root);
    std::cout << std::endl;
}

template <class T>
void AVLTree<T>::printInOrder(AVLNode<T> *&subRoot)
{
    if (subRoot != NULL) {
        printInOrder(subRoot->getLeft());
        std::cout << subRoot->getElt() << " ";
        printInOrder(subRoot->getRight());
    }    

}

#endif
