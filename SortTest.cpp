#include "SortTest.h"
#include <iostream>

void initSortTestStruct(SortTestStruct* structArray, int* array, int length);
void insert2Array (int value, int* newArray, int* newLength, int maxLen);
void sortStructArray(SortTestStruct* structArray, int length, int index, int* newArray, int* newLength);
void debug (SortTestStruct* sortArray, int* newArray, int length);

SortTest::SortTest(/* args */)
{
}

SortTest::~SortTest()
{
}

void SortTest::trySort(int* array, int length) {
    if (length <= 0 || array == nullptr) {
        return;
    }
    SortTestStruct sortArray [length];
    int newArray [length];
    int newLength = 0;
    initSortTestStruct(sortArray, array, length);
    sortStructArray(sortArray, length, 1, newArray, &newLength);
    debug(sortArray, newArray, length);
    if (newLength != length) {
        std::cout << "newLength != length" << std::endl;
        return;
    }
    for (int i = 0; i < length; i++) {
        array[i] = newArray[i];
    }
}

void initSortTestStruct(SortTestStruct* structArray, int* array, int length) {
    for (int i = 0; i < length; i++) {
        structArray[i].value = array[i];
        structArray[i].index = 1;
    }
}

void insert2Array (int value, int* newArray, int* newLength, int maxLen){
    if (*newLength >= maxLen) {
        return;
    }
    newArray[*newLength] = value;
    (*newLength)++;
}

void sortStructArray(SortTestStruct* structArray, int length, int index, int* newArray, int* newLength) {
    int reference = 0, littleCount = 0, bigCount = 0, firstLittleIndex = -1, firstBigIndex = -1;
    bool needReference = true;
    for (int i = 0; i < length; i++) {
        if (structArray[i].index == index) {
            if (needReference) {
                reference = structArray[i].value;
                needReference = false;
            } else {
                    structArray[i].index = index << 1;
                if (structArray[i].value > reference) {
                    structArray[i].index += 1;
                    bigCount++;
                    if (firstBigIndex == -1) {
                        firstBigIndex = i;
                    }
                } else {
                    littleCount++;
                    if (firstLittleIndex == -1) {
                        firstLittleIndex = i;
                    }
                }
            }
        }
    }

    if (littleCount > 1) {
        sortStructArray(structArray, length, index << 1, newArray, newLength);
    } else if (littleCount == 1 && firstLittleIndex != -1)
    {
        insert2Array(structArray[firstLittleIndex].value, newArray, newLength, length);
    }

    insert2Array(reference, newArray, newLength, length);

    if (bigCount > 1) {
        sortStructArray(structArray, length, (index << 1) + 1, newArray, newLength);
    } else if (bigCount == 1 && firstBigIndex != -1)
    {
        insert2Array(structArray[firstBigIndex].value, newArray, newLength, length);
    }
}

void debug (SortTestStruct* sortArray, int* newArray, int length){
    std::cout << "sortArray: ";
    for (int i = 0; i < length; i++) {
        std::cout << sortArray[i].value << "[" << sortArray[i].index << "]  ";
        if (i % 10 == 9) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "newArray: ";
    for (int i = 0; i < length; i++) {
        std::cout << newArray[i] << " ";
        if (i % 10 == 9) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}
