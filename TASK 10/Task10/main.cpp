#include <iomanip>
#include <iostream>
int main(){ const long long n=3000000LL; const long long exactPaise=1001LL*n; const double rupees=10.01; const double totalDouble=rupees*n; std::cout<<"Journeys: "<<n<<'\n'; std::cout<<"Exact integer-paise total: "<<exactPaise<<" paise\n"; std::cout<<std::fixed<<std::setprecision(2)<<"Double-rupee total: Rs "<<totalDouble<<'\n'; std::cout<<"Exact total in rupees: Rs "<<static_cast<double>(exactPaise)/100.0<<'\n'; std::cout<<"int max: 2147483647; total paise exceeds int range: "<<std::boolalpha<<(exactPaise>2147483647LL)<<'\n'; }
