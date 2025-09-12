#include "Header.h"
#include <iostream>
using namespace std;

IntArray::IntArray(size_t initialCapacity)
    : m_data(nullptr), m_size(0), m_capacity(initialCapacity)
{
    if (m_capacity == 0) m_capacity = 100;
    m_data = new int[m_capacity];
}

IntArray::~IntArray() {
    delete[] m_data;
}

IntArray::IntArray(IntArray&& other) noexcept
    : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
{
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

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

void IntArray::initializeGrid() {
    m_size = 0;
    for (int i = 1; i <= 100; i++) {
        ensureCapacity(m_size + 1);
        m_data[m_size++] = i;
    }
}

int IntArray::find(int value) const {
    for (size_t i = 0; i < m_size; ++i) {
        if (m_data[i] == value) return static_cast<int>(i);
    }
    return -1;
}

int IntArray::modifyAt(size_t index, int newValue, int& oldValueOut) {
    if (index >= m_size) throw out_of_range("modifyAt: index out of range");
    oldValueOut = m_data[index];
    m_data[index] = newValue;
    return newValue;
}

void IntArray::pushBack(int value) {
    ensureCapacity(m_size + 1);
    m_data[m_size++] = value;
}

void IntArray::removeAt(size_t index) {
    if (index >= m_size) throw out_of_range("removeAt: index out of range");
    for (size_t i = index + 1; i < m_size; ++i) {
        m_data[i - 1] = m_data[i];
    }
    --m_size;
}

int IntArray::at(size_t index) const {
    if (index >= m_size) throw out_of_range("at: index out of range");
    return m_data[index];
}

void IntArray::printAsGrid() const {
    for (size_t i = 0; i < m_size; ++i) {
        cout << m_data[i] << "\t";
        if ((i + 1) % 10 == 0) cout << "\n";
    }
    cout << "(size=" << m_size << ")\n";
}

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
