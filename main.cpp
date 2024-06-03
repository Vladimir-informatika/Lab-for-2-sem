#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Transport
{
    int count_wheels;
    double mileage;
    double volume_tank;
    double power_engine;
    double travel_time;
    string name;
    double speed;
    double engine_consumption;
    int refills;
    double time;
public:
    Transport(int countWheels, double mil, double volumeTank, double power, double time, string str);

    double CalcEngineConsumption();
    double CalcSpeed();
    double CalcTravelTime(double distance);
    int CalcRefills(double distance);
    void Print();

    ~Transport();
};

Transport::~Transport() {
    cout << "Transport " << name << " deleted!" << endl;
}

Transport::Transport(int countWheels, double mil, double volumeTank, double power, double time1, string str) {
    count_wheels = countWheels;
    mileage = mil;
    volume_tank = volumeTank;
    power_engine = power;
    time = time1;
    name = str;

    speed = CalcSpeed();
    engine_consumption = CalcEngineConsumption();
    refills = CalcRefills();
    travel_time = CalcTravelTime();
}

double Transport::CalcSpeed() {
    return power_engine * 0.5 / count_wheels;
}

double Transport::CalcEngineConsumption() {
    return power_engine * 0.5;
}

double Transport::CalcTravelTime(double distance) {
    return distance / CalcSpeed();
}

int Transport::CalcRefills(double distance) {
    return (int)floor(distance / (volume_tank * CalcEngineConsumption()));
}

void Transport::Print() {

}

int main()
{
    Transport* vehicle;
    int amount = 0;

}

void menu ();

