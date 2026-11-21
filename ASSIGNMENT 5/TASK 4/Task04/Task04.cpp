#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <iomanip>
using namespace std;
class Bill{protected:string patient;public:explicit Bill(string p):patient(move(p)){}virtual ~Bill()noexcept=default;virtual double total()const=0;virtual string type()const=0;void print()const{cout<<type()<<" "<<patient<<": "<<total()<<'\n';}};
class OutPatient:public Bill{double c,t;public:OutPatient(string p,double x,double y):Bill(move(p)),c(x),t(y){}double total()const override{if(c<0||t<0)throw invalid_argument("negative charge");return c+t;}string type()const override{return "OP";}};
class InPatient:public Bill{int d;double r,s;public:InPatient(string p,int x,double y,double z):Bill(move(p)),d(x),r(y),s(z){}double total()const override{if(d<0||r<0||s<0)throw invalid_argument("negative charge");return d*r+s;}string type()const override{return "IP";}};
class DayCare:public Bill{double p;public:DayCare(string n,double x):Bill(move(n)),p(x){}double total()const override{if(p<0)throw invalid_argument("negative package");return p;}string type()const override{return "DayCare";}};
class CorporatePayer{double discount;public:explicit CorporatePayer(double d):discount(d){}double amountCovered(const Bill&b)const{if(discount<0||discount>100)throw invalid_argument("invalid discount");return b.total()*(1-discount/100);}};
int main(){cout<<fixed<<setprecision(2);unique_ptr<Bill>old=make_unique<OutPatient>("Ravi",500,1200),added=make_unique<DayCare>("Kiran",18000);old->print();added->print();CorporatePayer corp(15);cout<<"Corporate payer covers: "<<corp.amountCovered(*added)<<'\n';cout<<"Exception and resource test:\n";try{unique_ptr<Bill>bad=make_unique<OutPatient>("Invalid",-10,200);cout<<bad->total()<<'\n';}catch(const exception&e){cout<<"Handled: "<<e.what()<<'\n';}cout<<"Earlier bills remain available: "<<old->total()<<'\n';cout<<"All resource owners leave scope safely.\n";}
