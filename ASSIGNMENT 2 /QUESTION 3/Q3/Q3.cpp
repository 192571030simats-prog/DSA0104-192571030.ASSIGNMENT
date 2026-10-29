#include <iostream>
#include <string>
struct Parcel { double kg; bool express; bool insured; };
double charge(double kg, bool express = false, bool insured = false) {
    double total = 50.0 + kg * 20.0;
    if (express) total += 30.0;
    if (insured) total += 15.0;
    return total;
}
double charge(int grams) { return charge(grams / 1000.0, false, false); }
double charge(float kg) { return charge(static_cast<double>(kg), false, false); }
double charge(const Parcel& p) { return charge(p.kg, p.express, p.insured); }
int main() {
    std::cout << "charge(2) [int grams]: " << charge(2) << '\n';
    std::cout << "charge(2.0) [double kg]: " << charge(2.0) << '\n';
    std::cout << "charge(2.0f) [float kg]: " << charge(2.0f) << '\n';
    std::cout << "charge(2000) [int grams]: " << charge(2000) << '\n';
    std::cout << "charge(2.0, true) [express]: " << charge(2.0, true) << '\n';
    Parcel p{2.0, true, true};
    std::cout << "charge(Parcel) [express+insured]: " << charge(p) << '\n';
}