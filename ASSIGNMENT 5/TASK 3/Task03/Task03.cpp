#include <iostream>
#include <vector>
#include <variant>
#include <chrono>
#include <iomanip>
#include <memory>
#include <type_traits>
using namespace std;using Clock=chrono::steady_clock;
struct OP{double c,t;};struct IP{double d,r,s;};struct DC{double p;};struct ER{double b,h,x;};
struct Base{virtual ~Base()=default;virtual double total()const=0;};struct PolyOP:Base{double c,t;PolyOP(double a,double b):c(a),t(b){}double total()const override{return c+t;}};struct PolyIP:Base{double d,r,s;PolyIP(double a,double b,double c):d(a),r(b),s(c){}double total()const override{return d*r+s;}};
struct Tagged{int type;double a,b,c;};double sw(const Tagged&x){switch(x.type){case 0:return x.a+x.b;case 1:return x.a*x.b+x.c;case 2:return x.a;default:return x.a+x.b*x.c;}}
double vt(const variant<OP,IP,DC,ER>&v){return visit([](auto x)->double{using T=decltype(x);if constexpr(is_same_v<T,OP>)return x.c+x.t;else if constexpr(is_same_v<T,IP>)return x.d*x.r+x.s;else if constexpr(is_same_v<T,DC>)return x.p;else return x.b+x.h*x.x;},v);}
template<class F>double timeit(F f,int n){auto a=Clock::now();volatile double z=f(n);(void)z;return chrono::duration<double,milli>(Clock::now()-a).count();}
int main(){vector<Tagged>a;vector<variant<OP,IP,DC,ER>>v;vector<unique_ptr<Base>>p;for(int i=0;i<10;i++){int k=i%4;if(k==0){a.push_back({0,500,1200,0});v.push_back(OP{500,1200});}else if(k==1){a.push_back({1,3,2500,40000});v.push_back(IP{3,2500,40000});}else if(k==2){a.push_back({2,18000,0,0});v.push_back(DC{18000});}else{a.push_back({3,3000,800,2});v.push_back(ER{3000,800,2});}if(i%2==0)p.push_back(make_unique<PolyOP>(500,1200));else p.push_back(make_unique<PolyIP>(3,2500,40000));}double x=0,y=0,z=0;for(auto&q:a)x+=sw(q);for(auto&q:v)y+=vt(q);for(auto&q:p)z+=q->total();cout<<fixed<<setprecision(2)<<"10 bill totals: switch="<<x<<", variant="<<y<<", virtual="<<z<<'\n';cout<<"Timing in milliseconds (machine dependent):\n";for(int n:{1000,1000000,10000000}){double t1=timeit([](int m){double q=0;for(int i=0;i<m;i++)q+=sw({i%2,500,1200,40000});return q;},n);double t2=timeit([](int m){double q=0;for(int i=0;i<m;i++)q+=(i%2?3*2500+40000:500+1200);return q;},n);cout<<n<<" bills: switch="<<t1<<" ms, direct="<<t2<<" ms\n";}cout<<"Exception frequency test (1,000,000 claims):\n";for(int pct:{0,1,50}){int n=1000000,bad=n*pct/100;auto a1=Clock::now();long good=0;for(int i=0;i<n;i++)if(i>=bad)good++;auto a2=Clock::now();long good2=0;for(int i=0;i<n;i++)try{if(i<bad)throw 1;good2++;}catch(int){}auto a3=Clock::now();cout<<pct<<"% invalid: return-code="<<chrono::duration<double,milli>(a2-a1).count()<<" ms, exceptions="<<chrono::duration<double,milli>(a3-a2).count()<<" ms, accepted="<<good<<"/"<<good2<<'\n';}}
