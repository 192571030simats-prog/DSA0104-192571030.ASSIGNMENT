#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
using namespace std;
class Bill { protected: string patient; public: explicit Bill(string p):patient(p){} virtual ~Bill()=default; virtual double total()const=0; virtual string type()const{return "Bill";} void print()const{cout<<type()<<" "<<patient<<": "<<total()<<'\n';} };
class OutPatient:public Bill{double c,t;public:OutPatient(string p,double x,double y):Bill(p),c(x),t(y){} double total()const override{return c+t;} string type()const override{return "OP";}};
class InPatient:public Bill{int d;double r,s;public:InPatient(string p,int x,double y,double z):Bill(p),d(x),r(y),s(z){} double total()const override{return d*r+s;} string type()const override{return "IP";}};
class DayCare:public Bill{double p;public:DayCare(string n,double x):Bill(n),p(x){} double total()const override{return p;} string type()const override{return "DayCare";}};
class Emergency:public Bill{double b,h;int t;public:Emergency(string n,double x,double y,int z):Bill(n),b(x),h(y),t(z){} double total()const override{return b+h*t;} string type()const override{return "Emergency";}};
class Payer{public:virtual ~Payer()=default;virtual double amountCovered(const Bill&)const=0;virtual string name()const=0;};
class SelfPay:public Payer{public:double amountCovered(const Bill&b)const override{return b.total();}string name()const override{return "SelfPay";}};
class Insurance:public Payer{double limit,co;public:Insurance(double l,double c):limit(l),co(c){}double amountCovered(const Bill&b)const override{return min(b.total(),limit)*(1-co/100);}string name()const override{return "Insurance";}};
class GovernmentScheme:public Payer{double rate;public:explicit GovernmentScheme(double r):rate(r){}double amountCovered(const Bill&b)const override{return min(b.total(),rate);}string name()const override{return "GovernmentScheme";}};
int main(){vector<unique_ptr<Bill>> b;b.push_back(make_unique<OutPatient>("Ravi",500,1200));b.push_back(make_unique<InPatient>("Meena",3,2500,40000));b.push_back(make_unique<DayCare>("Arun",18000));b.push_back(make_unique<Emergency>("Sara",3000,800,2));cout<<fixed<<setprecision(2);double sum=0;for(auto&x:b){x->print();sum+=x->total();}cout<<"Total "<<sum<<'\n';SelfPay s;Insurance i(50000,10);GovernmentScheme g(20000);const Payer* p[]={&s,&i,&g};for(auto*x:p)cout<<x->name()<<" covers first bill: "<<x->amountCovered(*b[0])<<'\n';}
