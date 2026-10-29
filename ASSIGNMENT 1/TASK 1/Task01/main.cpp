#include <iostream>
#include <string>
class SmartCard { long long balance_; public: explicit SmartCard(long long b): balance_(b) {} long long balance() const { return balance_; } bool deduct(long long fare) { if (fare < 0 || balance_ - fare < 5000) return false; balance_ -= fare; return true; } };
int main(){ SmartCard card(10000); std::cout << "Objects: Passenger, SmartCard, Journey, Zone, FareTable\n"; std::cout << "Card starts at Rs 100.00\n"; std::cout << "Inner fare Rs 10.00 accepted: " << std::boolalpha << card.deduct(1000) << "\n"; std::cout << "Remaining balance paise: " << card.balance() << "\n"; std::cout << "Invariant balance >= 5000 paise: " << (card.balance() >= 5000) << "\n"; }
