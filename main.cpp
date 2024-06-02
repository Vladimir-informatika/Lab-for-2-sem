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
public:
    Transport(int countWheels, double mil, double volumeTank, double power, double time, string n)
    {
        count_wheels = countWheels;
        mileage = mil;
        volume_tank = volumeTank;
        power_engine = power;
        travel_time = time;
        name = n;
    }
    //double CalcEngineConsumption();
    //double CalcSpeed();
    //double CalcTime();
    //int CalcRefills();
    void Print()
    {
        cout << name << travel_time << power_engine << volume_tank << mileage << count_wheels;
    }
    ~Transport() { cout << "Deleled object"; };
};
int main()
{
    Transport Car(3, 5, 5, 5, 5, "car");
    Car.Print();
}
