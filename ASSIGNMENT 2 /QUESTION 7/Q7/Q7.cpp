#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
void shiftAdd(std::vector<int>& values, int value, int capacity) {
    if ((int)values.size() == capacity) values.erase(values.begin());
    values.push_back(value);
}
class CircularLog {
    std::vector<int> data;
    int capacity, count = 0, next = 0;
public:
    explicit CircularLog(int cap) : data(cap), capacity(cap) {}
    void add(int value) {
        data[next] = value;
        next = (next + 1) % capacity;
        if (count < capacity) ++count;
    }
    void printOldestFirst() const {
        int start = (count == capacity) ? next : 0;
        for (int i = 0; i < count; ++i) std::cout << data[(start + i) % capacity] << ' ';
        std::cout << '\n';
    }
};
int main() {
    constexpr int capacity = 10;
    std::vector<int> shifted;
    CircularLog circular(capacity);
    for (int i = 1; i <= 15; ++i) {
        shiftAdd(shifted, i, capacity);
        circular.add(i);
    }
    std::cout << "Original shifting log (last 10): ";
    for (int x : shifted) std::cout << x << ' ';
    std::cout << "\nRedesigned circular log (last 10): ";
    circular.printOldestFirst();
    std::cout << "Both retain the same 10 newest values; circular insertion overwrites one slot in O(1).\n";
}