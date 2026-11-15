#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class ServiceRecord {
public:
    string dueDate;
    explicit ServiceRecord(string d) : dueDate(std::move(d)) {}
};
class Vehicle {
protected:
    string registration;
    double dailyRate;
public:
    Vehicle(string r, double rate) : registration(std::move(r)), dailyRate(rate) {}
    virtual double charge(int days) const = 0;
    virtual string type() const = 0;
    virtual void list() const {
        cout << type() << " " << registration << " daily rate Rs." << dailyRate << '\n';
    }
    virtual ~Vehicle() = default;
};
class Bicycle : public Vehicle {
public:
    Bicycle(string r, double rate) : Vehicle(std::move(r), rate) {}
    double charge(int days) const override { return dailyRate * days; }
    string type() const override { return "Bicycle"; }
};
class MotorVehicle : public Vehicle {
protected:
    double fuelOrCharge;
    ServiceRecord service;
    MotorVehicle(string r, double rate, double level, string due)
        : Vehicle(std::move(r), rate), fuelOrCharge(level), service(std::move(due)) {}
};
class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(string r, double rate, double fuel, string due)
        : MotorVehicle(std::move(r), rate, fuel, std::move(due)) {}
    double charge(int days) const override { return dailyRate * days; }
    string type() const override { return "TwoWheeler"; }
};
class Car : public MotorVehicle {
protected:
    int seats;
public:
    Car(string r, double rate, double fuel, string due, int s)
        : MotorVehicle(std::move(r), rate, fuel, std::move(due)), seats(s) {}
    double charge(int days) const override { return dailyRate * days + (seats > 5 ? 200 : 0); }
    string type() const override { return "Car"; }
};
class ElectricCar : public Car {
    double batteryKWh;
    double kWhRate;
public:
    ElectricCar(string r, double rate, double level, string due, int s, double battery, double kRate)
        : Car(std::move(r), rate, level, std::move(due), s), batteryKWh(battery), kWhRate(kRate) {}
    double charge(int days) const override { return dailyRate * days + batteryKWh * kWhRate; }
    string type() const override { return "ElectricCar"; }
};
class ElectricBus : public Vehicle {
    int seats;
    double batteryKWh, kWhRate;
public:
    ElectricBus(string r, double rate, int s, double battery, double kRate)
        : Vehicle(std::move(r), rate), seats(s), batteryKWh(battery), kWhRate(kRate) {}
    double charge(int days) const override { return dailyRate * days + batteryKWh * kWhRate + seats * 5; }
    string type() const override { return "ElectricBus"; }
};
class Fleet {
    vector<unique_ptr<Vehicle>> vehicles;
public:
    void add(unique_ptr<Vehicle> v) { vehicles.push_back(std::move(v)); }
    void list() const { for (const auto& v : vehicles) v->list(); }
    void rent(size_t index, int days) const {
        if (index < vehicles.size())
            cout << "Rent " << vehicles[index]->type() << " for " << days
                 << " day(s): Rs." << vehicles[index]->charge(days) << '\n';
    }
    void returnVehicle(size_t index, int daysLate) const {
        if (index < vehicles.size()) {
            const double lateFee = daysLate * 250.0;
            cout << "Return " << vehicles[index]->type() << ": late fee Rs."
                 << lateFee << ", total due Rs."
                 << vehicles[index]->charge(1) + lateFee << '\n';
        }
    }
};
int main() {
    cout << fixed << setprecision(2);
    Fleet fleet;
    fleet.add(make_unique<Bicycle>("BIC-101", 100));
    fleet.add(make_unique<TwoWheeler>("TW-202", 300, 8, "2026-12-01"));
    fleet.add(make_unique<Car>("CAR-303", 1000, 30, "2026-12-10", 5));
    fleet.add(make_unique<ElectricCar>("EV-404", 1500, 80, "2026-12-15", 5, 60, 8));
    fleet.list();
    for (size_t i = 0; i < 4; ++i) fleet.rent(i, 2);
    fleet.returnVehicle(2, 2);
    // Extension: new derived type is added without editing Vehicle or Fleet.
    fleet.add(make_unique<ElectricBus>("BUS-505", 2500, 30, 120, 7));
    fleet.rent(4, 2);
}