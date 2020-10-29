#include "../sequence/Sequence.h"

#ifndef HASH_H 
#define HASH_H 

template <class Tkey, class Tval> 
struct node {
    Tkey key;
    Tval val;
    node *next;
};

template <class Tkey, class Tval> 
class Hash 
{
    public:

        /* Construction takes:
         *  - initial capacity (can be expanded later at O(n) cost, where 
         *    n is number of key-value pairs in table)
         *  - Hash function
         *  - Comparison function for comparing keys */
        Hash(int initCap, 
             int (*hashFun) (Tkey), 
             bool (*cmpFun) (Tkey, Tkey));

        ~Hash();
    
        int size();    
     
        /* bind value to key in table */
        void bind (Tkey key, Tval val);

        /* Find value by key-return NULL if key-valaue air does not exist */
        Tval find(Tkey key);

    private:

        Sequence<node<Tkey, Tval> * > table;
        int  (*hashfun) (Tkey);
        bool (*cmp)     (Tkey, Tkey);

        node<Tkey, Tval> *newPair(Tkey key, 
                                  Tval val, 
                                  node<Tkey, Tval> *next);
};

template <class Tkey, class Tval> 
Hash<Tkey, Tval>::Hash(int  initCap, 
                       int  (*hashFun) (Tkey), 
                       bool (*cmpFun) (Tkey, Tkey)) : table   (initCap, NULL),
                                                      hashfun (hashFun),
                                                      cmp     (cmpFun)
{}

template <class Tkey, class Tval> 
Hash<Tkey, Tval>::~Hash()
{
    for (int i = 0; i < table.size(); ++i) {
        node<Tkey, Tval> *chain = table.at(i);
        while (chain != NULL) {
            node<Tkey, Tval> *temp = chain;
            chain = chain->next;
            delete temp;            
        }
    }
}

template <class Tkey, class Tval>
int Hash<Tkey, Tval>::size()
{
    return table.size();
}

/*
 * binds key to value
 * if key already in table, binds new value
 */
template <class Tkey, class Tval> 
void Hash<Tkey, Tval>::bind(Tkey key, Tval val)
{
    int index = hashfun(key);    
    if (table.at(index) == NULL) {
        table.at(index) = newPair(key, val, NULL);
    } else { 
        node<Tkey, Tval> *chain = table.at(index);

        while (chain->next != NULL) {
            if (cmp(key, chain->key)) {
                chain->val = val;
                return;
            }
            chain = chain->next;
        }

        if (cmp(key, chain->key)) {
            chain->val = val;
        } else {
            chain->next = newPair(key, val, NULL);
        }        
    }        
}

template <class Tkey, class Tval> 
Tval Hash<Tkey, Tval>::find(Tkey key)
{
    int index = hashfun(key);
    node<Tkey, Tval> *chain = table.at(index); 
    if (chain == NULL)
        return NULL;
       
    while (!cmp(key, chain->key)) {
        chain = chain->next;
        if (chain == NULL)
            return NULL;        
    }

    return chain->val;
}

/****************************Private helpers******************************/
template <class Tkey, class Tval> 
node<Tkey, Tval> *Hash<Tkey, Tval>::newPair(Tkey key, 
                                            Tval val, 
                                            node<Tkey, Tval> *next)
{
    node<Tkey, Tval> *nodePtr = new node<Tkey, Tval>;
    nodePtr->key  = key;
    nodePtr->val  = val;
    nodePtr->next = next;
    return nodePtr;
}

#endif
