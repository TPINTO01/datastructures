#include <iostream>
#include "LinkedListrec.h"
 
using namespace std;

void test(bool condition, const std::string& prompt);

void testLinkedList();
void testConstructor();
void testSubscript();
void testIsEmpty();
void testClear();
void testElementAt();
void testPushAtBack();
void testPushAtFront();
void testInsertAt();
void testPopFromBack();
void testPopFromFront();
void testRemoveAt();
void testReplaceAt();
void testConcat();
void testHas();

bool intRaysEQ(int ray1[], int ray2[], int size);

int main()
{    
    testLinkedList();
	return 0;
}

void testLinkedList()
{
    testConstructor();
    testIsEmpty();
    testClear();
    testElementAt();
    testPushAtBack();
    testPushAtFront();
    testInsertAt();
    testPopFromBack();
    testPopFromFront();
    testRemoveAt();
    testReplaceAt();
    testConcat();
    testHas();
}

void test(bool condition, const std::string& prompt)
{
    if (!condition) 
        throw runtime_error(prompt + "Fails");
    else 
        cout << prompt << "passes" << endl;
}

void testConstructor()
{
    int ints[10];
    int intsFromList[10];

    for (int i = 0; i < 10; ++i) 
        ints[i] = i;    

    /* Construction of lists */    
    LinkedList<int> intList1;
    LinkedList<int> intList2(0);
    LinkedList<int> intList3(ints, 10);
    LinkedList<int> intList4(intList3);

    for (int i = 0; i < intList3.size(); ++i) 
        intsFromList[i] = intList3.at(i);

    test(intList1.size() == 0, "default constructor creates list with no elements : ");   
    test(intList2.size() == 1, "1-arg constructor creates list with 1 element : ");   
    test(intList2.at(0) == 0, "1-arg constructor creates list with correct elements : ");
    test(intList3.size() == 10, "2-arg constructor creates list with n elements : ");
    test(intRaysEQ(ints, intsFromList, 10), "2-arg constructor creates list with correct elements : ");

    intList3.replaceAt(9999, 5);
    for (int i = 0; i < intList4.size(); ++i) 
        intsFromList[i] = intList4.at(i);

    test(intRaysEQ(ints, intsFromList, 10), "copy constructor deep copies list with correct elements : ");    
}

/*
 * Not used for compatibility with LinkedListrec, which does not support 
 * subscript operator 
 *
 
void testSubscript()
{
    int ints[10];
    for (int i = 0; i < 10; ++i) 
        ints[i] = i;    

    LinkedList<int> intList(ints, 10);
    
    test(intList[0] == 0, "Subscript ([]) accesses correct element : ");
    test(intList[1] == 1, "Subscript ([]) accesses correct element : ");
    test(intList[9] == 9, "Subscript ([]) accesses correct element : ");

    intList[5] = 500;

    test(intList[5] == 500, "Subscript ([]) mutates correct element : ");
}

*/

void testIsEmpty()
{
    LinkedList<int> intList1;
    LinkedList<int> intList2(0);

    test(intList1.isEmpty(),  "Empty List is empty : ");      
    test(!intList2.isEmpty(), "Nonempty List is not empty : ");      
}

void testClear()
{
    int ints[10];   
    for (int i = 0; i < 10; ++i) 
        ints[i] = i;    
    
    LinkedList<int> intList(ints, 10); 
    intList.clear();

    test(intList.isEmpty(),  "Clear list : ");         
}

void testElementAt()
{
    int ints[10];   
    for (int i = 0; i < 10; ++i) 
        ints[i] = i;    

    LinkedList<int> intList(ints, 10);   

    bool allEltsEQ; 
    for (int i = 0; i < 10; ++i) {
        allEltsEQ = ints[i] == intList.at(i); 
        if (!allEltsEQ) break;
    }
  
    test(allEltsEQ, "at arbitrary index correct : ");
}

void testPushAtBack()
{
    int ints[10];   
    for (int i = 0; i < 10; ++i) 
        ints[i] = i;    
    
    LinkedList<int> intList(ints, 10); 

    intList.pushAtBack(10);
    
    test(intList.size() == 11, "pushAtBack updates size : ");
    test(intList.back() == 10, "pushAtBack last element correct value : "); 
}

void testPushAtFront()
{
    int ints[10];   
    for (int i = 0; i < 10; ++i) 
        ints[i] = i;    
    
    LinkedList<int> intList(ints, 10); 
    intList.pushAtFront(10);
    
    test(intList.size() == 11, "pushAtFront updates size : ");
    test(intList.front() == 10, "pushAtFront first element correct value : ");  
}

void testInsertAt()
{
    int ints[10];   
    int insertedInts[13] = {10, 0, 1, 2, 3, 13, 4, 5, 6, 7, 8, 9, 11}; 
    for (int i = 0; i < 10; ++i) 
        ints[i] = i;    
    
    LinkedList<int> intList(ints, 10); 
    intList.insertAt(10, 0);    
    intList.insertAt(11, 11);
    intList.insertAt(13, 5);

    bool allEltsEQ; 
    for (int i = 0; i < 13; ++i) {
        allEltsEQ = insertedInts[i] == intList.at(i);
        if (!allEltsEQ) break;
    }
 
    test(intList.size() == 13, "insertAt updates size : ");
    test(intList.front() == 10, "insertAt first element correct value : ");
    test(intList.back() == 11, "insertAt last element correct value : ");   
    test(allEltsEQ, "insertAt arbitrary index correct value : ");   
}

void testPopFromBack()
{
    int ints[10];   
    for (int i = 0; i < 10; ++i) 
        ints[i] = i;    
    
    LinkedList<int> intList(ints, 10); 
    intList.popFromBack();

    test(intList.size() == 9, "popFromBack updates size : ");
    test(intList.back() == 8, "popFromBack last element correct value : "); 
   
    LinkedList<int> intList2(0);
    
    test(intList2.front() == 0, "front refers to first/last elt in 1 elt list : "); 
    test(intList2.back() == 0, "back refers to first/last elt in 1 elt list : "); 

    intList2.popFromBack();

    test(intList2.size() == 0, "popFromBack updates size (2) : ");
}

void testPopFromFront()
{
    int ints[10];   
    for (int i = 0; i < 10; ++i) 
        ints[i] = i;    
    
    LinkedList<int> intList(ints, 10); 
    intList.popFromFront();

    test(intList.size() == 9, "popFromFront updates size : ");
    test(intList.front() == 1, "popFromFront first element correct value : "); 
}

void testRemoveAt()
{
    int ints[10];   
    int removedInts[7] = {1, 2, 3, 4, 5, 7, 8}; 

    for (int i = 0; i < 10; ++i) 
        ints[i] = i;    
    
    LinkedList<int> intList(ints, 10); 
    intList.removeAt(9);    
    intList.removeAt(0);
    intList.removeAt(5);

    bool allEltsEQ; 
    for (int i = 0; i < 7; ++i) {
        allEltsEQ = removedInts[i] == intList.at(i); 
//        cout << endl << removedInts[i] << " : " << intList.at(i) << endl;
        if (!allEltsEQ) break;
    }
 
    test(intList.size() == 7, "removeAt updates size : ");
    test(intList.front() == 1, "removeAt first element correct value : ");
    test(intList.back() == 8, "removeAt last element correct value : ");   
    test(allEltsEQ, "removeAt arbitrary index correct value : ");   
}

void testReplaceAt()
{
    int ints[10];    
    int replacedInts[10] = {10, 1, 2, 3, 4, 15, 6, 7, 8, 19};
    for (int i = 0; i < 10; ++i) 
        ints[i] = i;    
    
    LinkedList<int> intList(ints, 10); 
    intList.replaceAt(10, 0);
    intList.replaceAt(19, 9);
    intList.replaceAt(15, 5);

    bool allEltsEQ; 
    for (int i = 0; i < 10; ++i) {
        allEltsEQ = replacedInts[i] == intList.at(i); 
        if (!allEltsEQ) break;
    }

    test(intList.size() == 10, "replaceAt maintains size : ");
    test(intList.front() == 10, "replaceAt first element correct value : ");
    test(intList.back() == 19, "replaceAt last element correct value : "); 
    test(allEltsEQ, "replaceAt arbitrary index correct value : "); 
}

void testConcat()
{
    int ints[10];    
    int moreInts[20];    
    for (int i = 0; i < 10; ++i) {
        ints[i] = i;    
        moreInts[i] = i;
    }
    for (int i = 10; i < 20; ++i) 
        moreInts[i] = i - 10;

    LinkedList<int> intList1(ints, 10);
    LinkedList<int> intList2(ints, 10);
    
    intList1.concat(&intList2);
    
    bool allEltsEQ; 
    for (int i = 0; i < 10; ++i) {
        allEltsEQ = moreInts[i] == intList1.at(i); 
        if (!allEltsEQ) break;
    }

    test(intList1.size() == 20, "concat updates size : ");
    test(allEltsEQ, "concat correct values: "); 
}

void testHas()
{
    int ints[10];   
    for (int i = 0; i < 10; ++i) 
        ints[i] = i;    
   
    LinkedList<int> intList(ints, 10); 

    bool hasEltsEQ;
    for (int i = 0; i < 10; ++i) {
        hasEltsEQ = intList.has(ints[i]);
        if (!hasEltsEQ) break;
    }
 
    test(hasEltsEQ, "has correct values : ");
    test(! intList.has(10), "does not have nonexistent value : ");    
}


/* Takes two arrays of equal length and returns true if they contain same 
 * elements in same order */
bool intRaysEQ(int ray1[], int ray2[], int size)
{
    bool raysEq; 
    for (int i = 0; i < size; ++i) {
        raysEq = ray1[i] == ray2[i];
        if (! raysEq) break;
    }
    return raysEq;
}

