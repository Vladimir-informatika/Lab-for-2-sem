#include <iostream>

using namespace std;

void time_calc(double distance, double strong);


class Vehicle{
    public:
        char name;
        double mileage;
        double power;
        double speed;
        int count_wheels;
        double volume;
        double consumption;
        double time;
} Car;
int main()
{
    Vehicle *ptr = &Car;
    
    cout << "Enter power: " << endl;
    cin << ptr->power << endl;

    cout << "Enter the distance: " << endl;
    cin << distance << endl;

    cout << "Enter engine capacity: " << endl;
    cin << ptr->V << endl;
    
    cout << "Enter mileage: " << endl;
    cin << ptr->mileage << endl;

    ptr->consump = 100 * ptr->V / ptr->mileage;

    cout << ptr->consump << endl;

    cout << "time:"
    time_calc(distance, strong);

    return 0;
}

void time_calc(double distance, double strong){
    double mass = 1250;
    double mu = 0.02;
    strong = mu * mass * 10;
    speed = ptr->power / strong;
    time = distance / speed;
    cout << speed << endl;
}
