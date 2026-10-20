#include <iostream>
#include <string>
enum class Zone{Inner,Middle,Outer};
long long fare(Zone z,bool peak){long long b=(z==Zone::Inner?1000:(z==Zone::Middle?2000:3000)); return peak?b+b*20/100:b;}
int main(){ struct Test{const char* name; Zone z; bool peak; long long expected;}; Test tests[]={{"Inner off-peak",Zone::Inner,false,1000},{"Inner peak",Zone::Inner,true,1200},{"Middle off-peak",Zone::Middle,false,2000},{"Outer off-peak",Zone::Outer,false,3000},{"Outer peak",Zone::Outer,true,3600}}; int passed=0; for(const auto&t:tests){long long actual=fare(t.z,t.peak); bool ok=actual==t.expected; passed+=ok; std::cout<<t.name<<": expected "<<t.expected<<", actual "<<actual<<" paise - "<<(ok?"PASS":"FAIL")<<'\n';} std::cout<<"Tests passed: "<<passed<<'/'<<(sizeof(tests)/sizeof(tests[0]))<<'\n'; }
