#include "Header.h"
#include <iostream>
using namespace std;

// Constructor: Allocates array with given initial capacity (default 100).
IntArray::IntArray(size_t initialCapacity)
    : m_data(nullptr), m_size(0), m_capacity(initialCapacity)
{
    if (m_capacity == 0) m_capacity = 100;
    m_data = new int[m_capacity];
}

// Destructor: Releases allocated memory.
IntArray::~IntArray() {
    delete[] m_data;
}

// Move constructor: Transfers ownership of data from another IntArray.
IntArray::IntArray(IntArray&& other) noexcept
    : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
{
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

// Move assignment: Transfers data from another IntArray, cleaning up existing data.
IntArray& IntArray::operator=(IntArray&& other) noexcept {
    if (this != &other) {
        delete[] m_data;
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    return *this;
}

// Fills array with values 1 to 100, resizing if needed.
void IntArray::initializeGrid() {
    m_size = 0;
    for (int i = 1; i <= 100; i++) {
        ensureCapacity(m_size + 1);
        m_data[m_size++] = i;
    }
}

// Returns index of first occurrence of value, or -1 if not found.
int IntArray::find(int value) const {
    for (size_t i = 0; i < m_size; ++i) {
        if (m_data[i] == value) return static_cast<int>(i);
    }
    return -1;
}

// Modifies value at index, returns new value, outputs old value via reference.
int IntArray::modifyAt(size_t index, int newValue, int& oldValueOut) {
    if (index >= m_size) throw out_of_range("modifyAt: index out of range");
    oldValueOut = m_data[index];
    m_data[index] = newValue;
    return newValue;
}

// Appends value to end of array, resizing if needed.
void IntArray::pushBack(int value) {
    ensureCapacity(m_size + 1);
    m_data[m_size++] = value;
}

// Removes value at index, shifts remaining elements left.
void IntArray::removeAt(size_t index) {
    if (index >= m_size) throw out_of_range("removeAt: index out of range");
    for (size_t i = index + 1; i < m_size; ++i) {
        m_data[i - 1] = m_data[i];
    }
    --m_size;
}

// Returns value at index, throws if out of range.
int IntArray::at(size_t index) const {
    if (index >= m_size) throw out_of_range("at: index out of range");
    return m_data[index];
}

// Prints array as a 10x10 grid, shows current size.
void IntArray::printAsGrid() const {
    for (size_t i = 0; i < m_size; ++i) {
        cout << m_data[i] << "\t";
        if ((i + 1) % 10 == 0) cout << "\n";
    }
    cout << "(size=" << m_size << ")\n";
}

// Ensures array has enough capacity, doubles size as needed.
void IntArray::ensureCapacity(size_t needed) {
    if (needed <= m_capacity) return;
    size_t newCap = m_capacity * 2;
    while (newCap < needed) newCap *= 2;

    int* newData = new int[newCap];
    for (size_t i = 0; i < m_size; ++i) newData[i] = m_data[i];

    delete[] m_data;
    m_data = newData;
    m_capacity = newCap;
}
