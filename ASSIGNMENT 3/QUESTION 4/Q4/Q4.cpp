#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

class Money {
    long long paise;
    Money(long long totalPaise, bool) : paise(totalPaise) {}
public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}
    Money operator+(const Money& rhs) const { return Money(paise + rhs.paise, true); }
    Money operator-(const Money& rhs) const { return Money(paise - rhs.paise, true); }
    Money& operator+=(const Money& rhs) { paise += rhs.paise; return *this; }
    bool operator==(const Money& rhs) const { return paise == rhs.paise; }
    bool operator<(const Money& rhs) const { return paise < rhs.paise; }
    friend std::ostream& operator<<(std::ostream& out, const Money& m) {
        long long magnitude = m.paise < 0 ? -m.paise : m.paise;
        if (m.paise < 0) out << "-";
        return out << "Rs " << magnitude / 100 << '.' << std::setw(2) << std::setfill('0') << magnitude % 100 << std::setfill(' ');
    }
    friend std::istream& operator>>(std::istream& in, Money& m) {
        long long rupees; int p;
        if (in >> rupees >> p) m.paise = rupees * 100 + p;
        return in;
    }
};
int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha << (c == Money(200, 0)) << '\n';
    std::cout << "Carry test: " << Money(0, 75) + Money(0, 50) << '\n';
    std::cout << "Negative subtraction: " << Money(1, 0) - Money(2, 0) << '\n';
    Money bill(100); bill += Money(25, 50); std::cout << "Bill total: " << bill << '\n';
}
