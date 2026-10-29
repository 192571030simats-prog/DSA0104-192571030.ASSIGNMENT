#include <iostream>
enum class Zone { Inner, Middle, Outer };
constexpr long long MIN_BALANCE_PAISE = 5000;
constexpr int PEAK_PERCENT = 20;
constexpr long long FARE_PAISE[] = {1000, 2000, 3000};
int main(){ Zone z=Zone::Outer; std::cout << "Inner fare (paise): " << FARE_PAISE[0] << "\nMiddle fare (paise): " << FARE_PAISE[1] << "\nOuter fare (paise): " << FARE_PAISE[2] << "\nPeak surcharge (%): " << PEAK_PERCENT << "\nMinimum remaining balance (paise): " << MIN_BALANCE_PAISE << "\nOuter zone selected safely with enum class: " << (z==Zone::Outer) << '\n'; }
