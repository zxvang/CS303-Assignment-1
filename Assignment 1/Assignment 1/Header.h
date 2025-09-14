#pragma once

#include <cstddef>
#include <stdexcept>
#include <string>
using namespace std;

class IntArray {
public:
    explicit IntArray(size_t initialCapacity = 100);
    ~IntArray();

    IntArray(const IntArray&) = delete;
    IntArray& operator=(const IntArray&) = delete;

    IntArray(IntArray&& other) noexcept;
    IntArray& operator=(IntArray&& other) noexcept;

    void initializeGrid();  // fill with 1–100

    int find(int value) const;
    int modifyAt(size_t index, int newValue, int& oldValueOut);
    void pushBack(int value);
    void removeAt(size_t index);

    size_t size() const { return m_size; }
    int at(size_t index) const;
    void printAsGrid() const;

private:
    void ensureCapacity(size_t needed);

    int* m_data;
    size_t m_size;
    size_t m_capacity;
};


