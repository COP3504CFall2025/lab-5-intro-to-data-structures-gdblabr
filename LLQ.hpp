#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() {}

    // Insertion
    void enqueue(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T dequeue() override {
        list.removeHead();
    }

    // Access
    T peek() const override {
        list.getHead();
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

};