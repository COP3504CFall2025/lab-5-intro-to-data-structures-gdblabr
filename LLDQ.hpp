#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() {}

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.AddHead(item);
    }
    void pushBack(const T& item) override {
        list.AddTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        front = list.getHead();
        list.RemoveHead();
        return front;
    }
    T popBack() override {
        back = list.getTail();
        list.RemoveTail();
        return back;
    }

    // Element Accessors
    const T& front() const override {
        return list.getHead();
    }
    const T& back() const override {
        return list.getTail();
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};






