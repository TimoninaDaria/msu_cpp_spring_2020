#pragma once
#include <string>
#include <iostream>
#include <stdexcept>

template <class T>
class Iterator: public std::iterator<std::random_access_iterator_tag, T> {
    T *ptr_;
 public:
    using iterator = Iterator<T>;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    Iterator(T* ptr):
            ptr_(ptr)
            {}

    Iterator(const iterator& it):
            ptr_(it.ptr_)
            {}

    bool operator==(const iterator& other) {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const iterator& other) {
        return !(*this == other);
    }

    bool operator<(const iterator& other) {
        return ptr_ < other.ptr_;
    }

    bool operator>(const iterator& other) {
        return ptr_ > other.ptr_;
    }

    reference operator*() {
        return *ptr_;
    }

    iterator& operator++() {
        ++ptr_;
        return *this;
    }

    iterator& operator--() {
        --ptr_;
        return *this;
    }

    iterator& operator+=(size_t count) {
        ptr_ += count;
        return *this;
    }

    iterator& operator-=(size_t count) {
        ptr_ -= count;
        return *this;
    }

    iterator operator+(size_t count) {
        iterator tmp(ptr_ + count);
        return tmp;
    }

    iterator operator-(size_t count) {
        iterator tmp(ptr_ - count);
        return tmp;
    }

   iterator operator+(const iterator& other) {
      iterator tmp(ptr_ + other.ptr_);
      return tmp;
   }

   iterator operator-(const iterator& other) {
      iterator tmp(ptr_ - other.ptr_);
      return tmp;
   }


    reference operator[](size_t count) {
        return ptr_[count];
    }
};


template<class T>
class Allocator
{
public:
    T* allocate(size_t n)
    {
        T* ptr = (T*)malloc(sizeof(T) * n);
        if (!ptr) throw std::bad_alloc();
        return ptr;
    }

    void deallocate(T* ptr){
        free(ptr);

    }

    void construct(T* ptr, const T& val)  {
       new (ptr) T (val);
  }

    void construct(T* ptr)  {
        new (ptr) T ();
    }

    void destroy(T* ptr){
        ptr->~T();
    }
};


template<class T,
    class Alloc = Allocator<T>>
class Vector
{
public:
    using size_type = size_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
	using allocator_type = Alloc;
    using pointer = T*;
    using iterator = Iterator<T>;
    using const_iterator = const Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    pointer data;
    allocator_type al;
    size_type len;
    size_type capac;

    explicit Vector(size_type count = 1): data(al.allocate(count*2)), len(0), capac(count*2){
    }

    ~Vector(){
        clear();
        al.deallocate(data);
    }

    iterator begin(){
        return iterator(data);
   }

    iterator end(){
        return iterator(data + len);
   }

    reverse_iterator rbegin(){
        return reverse_iterator(data + len);
   }

    reverse_iterator rend(){
        return reverse_iterator(data);
   }

    const_reference operator[](size_t val) const{
        if (val > len-1) throw std::out_of_range("out");
        else return (*(data+val));
    }
    bool empty() const {
        return (!len);
    }

    void pop_back() {
        if (len > 0) {
            al.destroy(data + len - 1);
            --len;
        }
    }

    void push_back(value_type&& value){
        if (capac == len){
            reserve(2*capac);
        }
        al.construct(data + len, value);
        ++len;
    }
    void push_back(const value_type& value){
        if (capac == len){
            reserve(capac);
        }
        al.construct(data + len, value);
        ++len;
    }
    void reserve(size_type count){
        if (count > capac){
            T*ptr_tmp = al.allocate(count);
            for (size_t i = 0; i < len; ++i) {
                al.construct(ptr_tmp + i, data[i]);
            }
             for (size_t i = 0; i < len; ++i) {
                 al.destroy(ptr_tmp + i);
          }
             al.deallocate(data);
             data = ptr_tmp;
             capac = count;
         }
    }

    size_type capacity() const noexcept{
        return capac;
    }

    void resize(size_type newSize){
        if (newSize > len){
            if (capac < newSize) reserve(newSize);
            for (size_t i = len; i < newSize; ++i){
                al.construct(data+i);
            }
        }
        else {
            for (size_t i = newSize; i < len; ++i) {
                al.destroy(data+i);
            }
        }
        len = newSize;
    }

    size_t size() const{
        return len;
    }

    void clear() noexcept{
        for (size_t i=0; i<len; ++i) {
              al.destroy(data + i);
          }
        len = 0;
    }

};

