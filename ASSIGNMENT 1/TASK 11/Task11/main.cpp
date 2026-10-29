#include <iostream>
#include <array>
enum class Zone{Inner,Middle,Outer};
constexpr std::array<long long,3> BASE_PAISE={1000,2000,3000};
int main(){ std::cout<<"Recommended design: enum class Zone + constexpr fare table\n"; std::cout<<"Money storage: long long integer paise\n"; std::cout<<"Card balance: private member with canTravel() and deduct()\n"; std::cout<<"Peak surcharge: 20%; minimum post-trip balance: 5000 paise\n"; std::cout<<"Base fares (paise): "; for(auto f:BASE_PAISE)std::cout<<f<<' '; std::cout<<"\nComplexity per journey: O(1)\n"; }
