//
//  helper.hpp
//  VectorUpgrades
//
//  Created by Tailang  Cao on 9/13/23.
//

#ifndef helper_hpp
#define helper_hpp

#include <stdio.h>
#include <iostream>

template <typename T>
class myVector {
private:
    T * data;
    size_t size;
    size_t capacity;
    
public:
    myVector (size_t initialCapacity);
    myVector(const myVector<T>&rhs);
    ~myVector();
    
    void pushBack(T newData);
    T popBack();
    T get(size_t index);
    void set(size_t index, T newValue);
    void growVector();
    
    size_t getSize ();
    myVector<T>& operator=(const myVector<T>& rhs);
    T& operator[](size_t index);
    const T& operator[](size_t index)const;
    bool operator==(const myVector& rhs);
    bool operator!=(const myVector& rhs);
    bool operator<(const myVector& rhs);
    bool operator<=(const myVector& rhs);
    bool operator>(const myVector& rhs);
    bool operator>=(const myVector& rhs);
    
    
};

template <typename T>
myVector<T>::myVector(size_t initialCapacity){
    size = 0;
    capacity = initialCapacity;
    data = new T[capacity];
}
template <typename T>
myVector<T>::~myVector(){
    delete [] data;
    data = nullptr;
    size = 0;
    capacity = 0;
//    std::cout << "destructor has been called\n";
}

template <typename T>
myVector<T> &myVector<T>:: operator=(const myVector& rhs){
    if (this == &rhs){
        return *this;
    }
    
    else{
        delete[] data;
        size = rhs.size;
        capacity = rhs.capacity;
        data = new T [capacity];
        for(T i = 0; i < rhs.size; i++){
            data[i] = rhs.data[i];
        }
        return *this;
    }
}

template <typename T>
myVector<T>::myVector(const myVector<T>&rhs){
    if(this != &rhs){
        delete []data;
        data=nullptr;
        size= rhs.getSize();
        capacity=rhs.capacity;
        
        if(capacity>0){
            data = new T[capacity];
            for(size_t i=0;i<getSize();i++){
                data[i]= rhs.get(i);
            }
        }
    }
}


template <typename T>
T& myVector<T>::operator[](size_t index){
    std::cout << "int& is called!\n";
    assert(index < size);
    return data[index];
}

template <typename T>
const T& myVector<T>::operator[](size_t index) const
{
    std::cout << "const int& is called!\n";
    assert(index < size);
    return data[index];
}

template <typename T>
bool myVector<T>::operator==(const myVector<T>& rhs){
    if(size == rhs.size){
        for(int i = 0; i < size; i ++){
            if(data[i]!=rhs.data[i]){
                return false;
            }
        }
        return true;
        }
    else{
        return false;
    }
}

template <typename T>
bool myVector<T>::operator!=(const myVector<T>& rhs){
    return !(*this == rhs);
}

template <typename T>
bool myVector<T>::operator<(const myVector<T>& rhs){
    for(int i = 0; i < std::min(size,rhs.size); i++){
        if(data[i] < rhs.data[i]){
            return true;
        }
        else if (data[i] > rhs.data[i]){
            return false;
        }
    }
    return(size<rhs.size);
}

template <typename T>
bool myVector<T>::operator<=(const myVector<T>& rhs){
    return ((*this == rhs) || (*this < rhs));
}

template <typename T>
bool myVector<T>::operator>(const myVector<T>& rhs){
    return (!(*this == rhs) && !(*this < rhs));
}

template <typename T>
bool myVector<T>::operator>=(const myVector<T>& rhs){
    return (!(*this < rhs));
}

template <typename T>
void myVector<T>::pushBack(T newData){
    if (size == capacity){
        growVector();
    }
    data[size] = newData;
    size += 1;
}

template <typename T>
T myVector<T>::popBack(){
    int popData = data[size-1];
    size -= 1;
    return popData;
}

template <typename T>
T myVector<T>::get(size_t index){
    assert(index < size);
    int desNum = data[index];
    return  desNum;
}

template <typename T>
void myVector<T>::set(size_t index, T newValue){
    assert(index < size);
    data[index] = newValue;
}

template <typename T>
void myVector<T>::growVector(){
    T* tempVec = new T [capacity*2];
    for(int i =0; i<size; i++){
      tempVec[i] = data[i];
    }
    delete[] data;
    data = tempVec;
    capacity = capacity*2;
    tempVec = nullptr;
}

template <typename T>
size_t myVector<T>::getSize (){
    return size;
}



#endif /* helper_hpp */
