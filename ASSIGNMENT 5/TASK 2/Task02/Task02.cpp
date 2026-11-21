#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
class ClaimError:public runtime_error{public:using runtime_error::runtime_error;};
double approve(double billed,double cover){if(billed<0||cover<0)throw invalid_argument("negative amount");if(billed>cover)throw ClaimError("exceeds cover");return billed;}
double settle(double b,double c){try{return approve(b,c);}catch(const ClaimError&e){cout<<"audit: "<<e.what()<<'\n';throw;}}
void validate(double x){if(x<0)throw invalid_argument("negative");if(x>1e6)throw out_of_range("too large");cout<<"ok ";}
void process(double x){try{validate(x);}catch(const out_of_range&e){cout<<"[log "<<e.what()<<"] ";throw;}}
struct Guard{string n;Guard(string s):n(s){}~Guard(){cout<<"destroy "<<n<<'\n';}};
int main(){cout<<"Validation and rethrow test:\n";for(double x:{100.0,-5.0,2e6})try{process(x);cout<<"done ";}catch(const exception&e){cout<<"caught "<<e.what()<<' ';}cout<<"\n\nClaim settlement:\n";double cases[][2]={{40000,50000},{60000,50000},{-1,50000}};for(auto&c:cases)try{cout<<"approved "<<settle(c[0],c[1])<<'\n';}catch(const ClaimError&e){cout<<"claim rejected: "<<e.what()<<'\n';}catch(const exception&e){cout<<"error: "<<e.what()<<'\n';}cout<<"\nRAII during exception:\n";try{Guard g("temporary resource");throw runtime_error("demonstration error");}catch(const exception&e){cout<<"caught: "<<e.what()<<'\n';}cout<<"Other error inputs:\n";try{stod("not-a-number");}catch(const invalid_argument&e){cout<<"text conversion: "<<e.what()<<'\n';}try{vector<int>v;v.at(3);}catch(const out_of_range&e){cout<<"array access: "<<e.what()<<'\n';}try{throw bad_alloc();}catch(const bad_alloc&){cout<<"allocation failure handled\n";}}
