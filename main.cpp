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
    double CalcTravelTime();
    int CalcRefills();
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
    return 0;
}

double Transport::CalcEngineConsumption() {
    return 0;
}

double Transport::CalcTravelTime() {
    return 0;
}

int Transport::CalcRefills() {
    return 0;
}

void Transport::Print() {
    return;
}

int main()
{
    Transport Car(3, 5, 5, 5, 5, "car");
    Car.Print();
}
