#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() {
        capacity_ = 4;
        size_ = 0;
        data_ = new T[capacity_];
        front_ = 0;
        back_ = 0;
    }
    explicit ABDQ(const size_t capacity) {
        capacity_ = capacity;
        size_ = 0;
        data_ = new T[capacity_];
        front_ = 0;
        back_ = 0;
    }
    ABDQ(const ABDQ& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[capacity_];
        for(size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];
        }
        front_ = 0;
        back_ = size_;
    }
    ABDQ& operator=(const ABDQ& rhs) {
        if(this == &rhs) {
            return *this;
        }
        delete[] data_;
        T* newArray = new T[rhs.capacity_];
        data_ = newArray;
        newArray = nullptr;

        capacity_ = rhs.capacity_;
        size_ = rhs.size_;
        front_ = rhs.front_;
        back_ = rhs.back_;
        for(size_t i = 0; i < size_; i++) {
            data_[i] = rhs.data_[(rhs.front_ + i) % rhs.capacity_];
        }
        front_ = 0;
        back_ = size_;
        return *this;
    }
    ABDQ(ABDQ&& other) noexcept {
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = other.data_;
        front_ = other.front_;
        back_ = other.back_;

        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;
    }
    ABDQ& operator=(ABDQ&& rhs) noexcept {
        if(this == &rhs) {
            return *this;
        }
        delete[] data_;
        capacity_ = rhs.capacity_;
        size_ = rhs.size_;
        data_ = rhs.data_;
        front_ = rhs.front_;
        back_ = rhs.back_;

        rhs.front_ = 0;
        rhs.back_ = 0;
        rhs.capacity_ = 0;
        rhs.size_ = 0;
        rhs.data_ = nullptr;
        return *this;
    }
    ~ABDQ() noexcept {
        front_ = 0;
        back_ = 0;
        capacity_ = 0;
        size_ = 0;
        delete[] data_;
        data_ = nullptr;
    }

    // Insertion
    void pushFront(const T& item) override {
        if(size_ == capacity_) {
            T* newArray = new T[capacity_ * SCALE_FACTOR];
            for(size_t i = 0; i < capacity_; i++) {
                newArray[i] = data_[(front_ + i)% capacity_];
            }
            delete[] data_;
            data_ = newArray;
            newArray = nullptr;
            front_ = 0;
            back_ = size_;
            capacity_ = capacity_ * SCALE_FACTOR;
        }
        if(front_ == 0) {
            front_ = capacity_ - 1;
        }
        else {
            front_ --;
        }
        data_[front_] = item;
        size_++;
    }
    void pushBack(const T& item) override {
        if(size_ == capacity_) {
            T* newArray = new T[capacity_ * SCALE_FACTOR];
            for(size_t i = 0; i < capacity_; i++) {
                newArray[i] = data_[(front_ + i) % capacity_];
            }
            delete[] data_;
            data_ = newArray;
            capacity_ = capacity_ * SCALE_FACTOR;
            front_ = 0;
            back_ = size_;
            newArray = nullptr;
        }
        data_[back_] = item;
        back_= (back_ + 1) % capacity_;
        size_++;
    }

    // Deletion
    T popFront() override {
        if(size_ == 0) {
            throw std::runtime_error("Deque is empty");
        }
        T res = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        return res;
    }
    T popBack() override {
        if(size_ == 0) {
            throw std::runtime_error("Deque is empty");
        }
        back_ = (back_ + capacity_ - 1) % capacity_;
        T res = data_[back_];
        size_--;
        return res;
    }

    // Access
    const T& front() const override {
        if(size_ == 0) {
            throw std::runtime_error("Empty deque");
        }
        return data_[front_];
    }
    const T& back() const override {
        if(size_ == 0) {
            throw std::runtime_error("Empty deque");
        }
        std::size_t lastItem = (back_ + capacity_ - 1) % capacity_;
        return data_[lastItem];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

};
