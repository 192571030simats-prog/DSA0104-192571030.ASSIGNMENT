#include <cmath>
#include <iostream>
#include <stdexcept>

class Complex {
    double re, im;
public:
    Complex() : re(0), im(0) {}
    Complex(double real) : re(real), im(0) {}
    Complex(double real, double imag) : re(real), im(imag) {}
    double real() const { return re; }
    double imag() const { return im; }
    double magnitude() const { return std::hypot(re, im); }
    Complex operator+(const Complex& z) const { return {re + z.re, im + z.im}; }
    Complex operator-(const Complex& z) const { return {re - z.re, im - z.im}; }
    Complex operator*(const Complex& z) const { return {re*z.re - im*z.im, re*z.im + im*z.re}; }
    Complex operator/(const Complex& z) const {
        double d = z.re*z.re + z.im*z.im;
        if (d == 0.0) throw std::domain_error("division by zero impedance");
        return {(re*z.re + im*z.im)/d, (im*z.re - re*z.im)/d};
    }
    bool operator==(const Complex& z) const { return re == z.re && im == z.im; }
    friend std::ostream& operator<<(std::ostream& out, const Complex& z) {
        return out << z.re << (z.im < 0 ? " - j" : " + j") << std::abs(z.im);
    }
};
int main() {
    const double omega = 100.0, L = 0.01, C = 0.001;
    Complex resistor(10.0, 0.0);
    Complex inductor(0.0, omega * L);
    Complex capacitor(0.0, -1.0 / (omega * C));
    Complex series = resistor + inductor + capacitor;
    Complex parallel = (resistor * inductor * capacitor) /
                       (resistor * inductor + resistor * capacitor + inductor * capacitor);
    std::cout << "R = " << resistor << " | magnitude=" << resistor.magnitude() << '\n';
    std::cout << "L = " << inductor << " | magnitude=" << inductor.magnitude() << '\n';
    std::cout << "C = " << capacitor << " | magnitude=" << capacitor.magnitude() << '\n';
    std::cout << "Series RLC = " << series << " | magnitude=" << series.magnitude() << '\n';
    std::cout << "Parallel RLC = " << parallel << " | magnitude=" << parallel.magnitude() << '\n';
    try { Complex invalid = resistor / Complex(); std::cout << invalid << '\n'; }
    catch (const std::domain_error& e) { std::cout << "Safe division: " << e.what() << '\n'; }
}
