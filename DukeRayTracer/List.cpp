//
//  List.cpp
//  RayTracer
//
//  Created by Dustin Alin on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "List.h"

//initializes list with a size of 4
template <class T> List<T>::List() {
    numData = 0;
    arraySize = 4;
    data = new T[arraySize];
}

//initializes list with specified size
template <class T> List<T>::List(int a) {
    numData = 0;
    arraySize = a;
    data = new T[arraySize];
}

template <class T> List<T>::~List() {
    numData = 0;
    delete [] data;
}

//adds item to the end of the list and doubles the size if full
template <class T> bool List<T>::append(T item) {
    if (numData == arraySize) {
        arraySize *=2;
        T *temp = data;
        if (!(data = new T[arraySize])) return false;
        for (int i = 0; i < numData; i++) {
            data[i] = temp[i];
        }
        delete [] temp;
    }
    data[numData++] = item;
    return true;
}

//makes the size of the list equal to the number of items in the list if room available
template <class T> bool List<T>::truncate() {
    if (numData != arraySize) {
        T *temp = data;
        arraySize = numData;
        if (!(data = new T[arraySize])) return false;
        for (int i = 0; i < numData; i++) {
            data[i] = temp[i];
        }
        delete [] temp;
    }
    return true;
}