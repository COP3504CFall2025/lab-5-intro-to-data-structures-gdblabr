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
        list.AddHead(item);
    }

    // Deletion
    T dequeue() override {
        return list.RemoveHead();
    }

    // Access
    T peek() const override {
        return list.GetHead();
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.GetCount();
    }

};