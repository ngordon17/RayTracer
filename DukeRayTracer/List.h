//
//  List.h
//  RayTracer
//
//  Created by Dustin Alin on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__List__
#define __RayTracer__List__

#include <iostream>

// Dynamic array that stores data in ordered structure with
// no delete operations. Items are added with append. Base array
// doubles in side when full.

template <class T> class List {
public:
    List();
    List(int);
    ~List(void);
    
    bool append(T item);
    bool truncate();
    void clear() { numData = 0; }
    int length() const { return numData; }
    bool empty() const { return numData == 0; }
    const T &operator[](int i) const { return data[i]; }
    T &operator[](int i) { return data[i]; }
    
private:
    T *data;
    int numData;
    int arraySize;
};

#endif /* defined(__RayTracer__List__) */
