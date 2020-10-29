#include <iostream>
#include "Hash.h"
 
void test(bool condition, const std::string& prompt);
int hashFunction(int value);
bool intCompare(int v1, int v2);

void testHash();
void testConstructor();
void testAddFind();

int main()
{    
    testHash();
	return 0;
}

void testHash()
{
    testConstructor();
    testAddFind();
}

void test(bool condition, const std::string& prompt)
{
    if (!condition) 
        throw std::runtime_error(prompt + "Fails");
    else 
        std::cout << prompt << "Passes" << std::endl;
}

int hashFunction(int value)
{
    if (value == 10)
        return 5;
    return value;
}

bool intCompare(int v1, int v2)
{
    if (v1 == v2) 
        return true;
    return false;
}

void testConstructor()
{        
    Hash<int, std::string> hashTable(10, hashFunction, intCompare);
}

void testAddFind()
{
    Hash<int, std::string> hashTable(10, hashFunction, intCompare);
    hashTable.bind(5, "five");
    test(hashTable.find(5) == "five", "Hash table inserts and returns key value pair : ");
    hashTable.bind(5, "six");
    test(hashTable.find(5) == "six", "Hash table binds key to new value: ");
    hashTable.bind(10, "ten");
    test(hashTable.find(5) == "six", "Hash table accesses value in chain: ");
    test(hashTable.find(10) == "ten", "Hash table accesses value in chain: ");
    
}

