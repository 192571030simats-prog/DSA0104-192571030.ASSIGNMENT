#include <iostream>
#include <string>
#include <chrono>

class Prescription {
    int n;
    std::string* medicines;
public:
    explicit Prescription(int count) : n(count), medicines(count ? new std::string[count] : nullptr) {}
    Prescription(const Prescription& other)
        : n(other.n), medicines(n ? new std::string[n] : nullptr) {
        for (int i = 0; i < n; ++i) medicines[i] = other.medicines[i];
        std::cout << "[copy constructor: " << n << " medicines]\n";
    }
    Prescription& operator=(const Prescription& other) {
        if (this != &other) {
            std::string* fresh = other.n ? new std::string[other.n] : nullptr;
            for (int i = 0; i < other.n; ++i) fresh[i] = other.medicines[i];
            delete[] medicines;
            medicines = fresh;
            n = other.n;
        }
        return *this;
    }
    ~Prescription() { delete[] medicines; }
    void set(int i, const std::string& m) { if (i >= 0 && i < n) medicines[i] = m; }
    std::string get(int i) const { return (i >= 0 && i < n) ? medicines[i] : "<out-of-range>"; }
};

void byValue(Prescription p) { std::cout << "Passed by value.\n"; }
void byConstReference(const Prescription& p) { std::cout << "Passed by const reference.\n"; }

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol"); p.set(1, "ORS");
    Prescription q = p;
    q.set(1, "Cetirizine");
    Prescription r(1); r = p;
    p.set(0, "Ibuprofen");
    std::cout << p.get(0) << ' ' << p.get(1) << " | " << q.get(0) << ' ' << q.get(1)
              << " | " << r.get(0) << ' ' << r.get(1) << '\n';
    p = p;
    byValue(p);
    byConstReference(p);
    for (int count : {10, 1000, 100000}) {
        Prescription source(count);
        auto start = std::chrono::steady_clock::now();
        Prescription copy = source;
        auto stop = std::chrono::steady_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        std::cout << "Copy " << count << " medicines: " << us << " us (one local measurement)\n";
    }
}
