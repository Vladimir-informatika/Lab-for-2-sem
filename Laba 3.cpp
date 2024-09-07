#include "cmath"
#include <iostream>
#include <limits>
#include <string>
#include <ctime>

using namespace std;
int quantity = 0; //изначальный размер массива
double InputProve(double var);
int InputProve(int var);

class Wheel;
class Engine;
class Fuel_System;

class Wheel {
    double current_mileage;
    int status; //повреждено/неповреждено 1/0
public:
    int Check_status(double mileage, double speed);
    Wheel() { status = 0; current_mileage = 0; };
    double DefWheel(double mileage, double speed) {
        current_mileage = mileage;
        status = Check_status(mileage, speed);
        return current_mileage;
    }
    virtual void Output();
    int GetStatus() { return status; }
};
class Engine {
protected:
    double engPow; //мощность двигателя HP horsepower
    double engIntake; //потребление двигателя литров/км l/km
public:
    inline double CalculateConsumption() { return fabs(pow(engPow, 1 / 3) + sqrt(engPow) - 6.25); }
    Engine() { engIntake = 0; engPow = 0; };
    void DefEngine(double power);
    virtual void Output();
};
class Fuel_System {
protected:
    double current_fuel; //текущий обЪём топлива литры l;
public:
    double TankCapacity; //обЪём бака литры l
    void CalculateCurrentFuel(double engIntake, double mileage, double NRefuel);
    Fuel_System() { TankCapacity = 0; current_fuel = 0; };
    void DefFuelSystem(double capacity, double engIntake, double mileage);
    virtual void Output();
};
class Transport : public Engine, public Fuel_System {
private:
    int Nwheels;
    double speed; //скорость км/ч km/h
    double Time;    //время пути hour
    int damaged_wheels = 0;
    double mileage; //пробег km
    double NRefuel; //количесвто дозаправок
public:
    Wheel* ptr_wheel;
    string name;
    Transport() {
        name = "ADDVEHICLE";
        Time = mileage = NRefuel = damaged_wheels = 0;
        ptr_wheel = 0;
    }
    Transport(string vehicle_name, int wheels) {
        mileage = damaged_wheels = 0;
        SetName(vehicle_name);
        SetWheels(wheels);
        ptr_wheel = new Wheel[wheels];
        for (int i = 0; i < wheels; i++) {
            ptr_wheel[i] = Wheel();
        }
        DefFuelSystem(0, engIntake, mileage);
        DefEngine(0);
        CalculateSpeed();
    }
    void CalculateSpeed();
    void SetName(string vehicle_name) { name = vehicle_name; }
    void SetWheels(int wheels) { Nwheels = wheels; }
    void SetMileage(double tracklen) { mileage = tracklen; }
    ~Transport() { cout << "Destruction of " << name << endl; }
    inline void CalculateRaceTime(double raceLength) {
        Time = (raceLength / speed);
    };
    double GetTime() { return Time; };
    double GetCountRefuel() { return NRefuel; };
    double GetSpeed() { return speed; };
    void CalculateRefuel(double raceLength);
    void TimeDisplay();
    int GetCountWheels() { return Nwheels; }
    void NumberOfDamagedWheels();
    void Output();
    friend Transport* RatingResults(int quantity);
    friend void OutputResults(Transport*& car, int quantity);
    friend ostream& operator<<(ostream& stream, const Transport& obj) {
        return stream << "Number of wheels: " << obj.Nwheels << ";\n"
            << "Damaged wheels: " << obj.damaged_wheels << ";\n"
            << "Speed: " << obj.speed << " km/h;\n"
            << "Mileage: " << obj.mileage << " km;\n"
            << "Fuel capacity: " << obj.TankCapacity << "l;\n"
            << "Current fuel: " << obj.current_fuel << "l\n"
            << "Engine power: " << obj.engPow << " HP;\n"
            << "Engine consumption: " << obj.engIntake << " l/100km;" << endl;
    }
};
int Menu(int& flag);
void Clean(int var = 1);
void AddTransports(Transport*& adres, int& quantity, Transport cars);
int main() {
    Clean();
    Transport* adres = nullptr;
    double trackLen = 0;
    int flag = 1;
    int rez = 0;
    while (flag == 1) {
        int choice = 10;
        choice = Menu(rez);
        if ((choice > 5) || (choice < 0)) {
            cout << "\nError, try another number!\n";
        }
        switch (choice) {
        case (0): {
            cout << "Are you sure you want to exit?\n1-yes\n0-go back\n";
            int exit = 2;
            exit = InputProve(exit);
            if (exit == 1) {
                flag = 0;
                break;
            }
            else {
                Clean();
            }
            break;
        }
                delete[] adres;
                for (int i = 0; i < quantity; i++) {
                    delete[] adres[i].ptr_wheel;
                }
                break;
        case (1): {
            Clean();
            string vehicle_name = "";
            cout << "\nName of the car: ";
            cin >> vehicle_name;
            int Nwheels = 0;
            cout << "Number of wheels: ";
            Nwheels = InputProve(Nwheels);
            while ((Nwheels < 2) || (Nwheels == 5) || (Nwheels == 7)) {
                cout << "Uncorrect number of wheels! try again:" << endl;
                Nwheels = InputProve(Nwheels);
            }
            Transport cars(vehicle_name, Nwheels);
            Clean();
            AddTransports(adres, quantity, cars);
            rez = 0;
            break;
        }
        case (2): {
            Clean();
            for (int i = 0; i < quantity; i++) {
                cout << adres[i].name << endl;
                adres[i].Output();
                cout << "__OR__" << endl;
                cout << adres[i] << endl;
            }
            break;
        }
        case (3): {
            Clean();
            cout << "Enter the length of the track (km): ";
            trackLen = InputProve(trackLen);
            rez = 0;
            break;
        }
        case (4): {
            Clean();
            if (trackLen == 0) {
                cout << "You haven't entered the length of the track!\n";
                rez = 0;
                break;
            }
            else {
                for (int i = 0; i < quantity; i++) {
                    adres[i].CalculateRaceTime(trackLen);
                    adres[i].SetMileage(trackLen);
                    for (int j = 0; j < adres[i].GetCountWheels(); j++) {
                        adres[i].ptr_wheel[j].DefWheel(trackLen, adres[i].GetSpeed());
                    }
                    adres[i].NumberOfDamagedWheels();
                    adres[i].CalculateRefuel(trackLen);
                    adres[i].CalculateCurrentFuel(adres[i].CalculateConsumption(), trackLen, adres[i].GetCountRefuel());
                    adres[i].CalculateSpeed();
                }
            }
            break;
        }
        case (5): {
            Clean();
            OutputResults(adres, quantity);
            break;
        }
        default:
            Clean();
            break;
        }
    }

    return 0;
}

void Clean(int var) {
    for (int i = 0; i < 3; i = i + 1) {
        cout << "\n";
    }
}
int Menu(int& rez) {
    cout << "\n-------------MENU------------\n";
    cout << "1 - Add Transport\n";
    cout << "2 - Output info about Transport\n";
    cout << "3 - Input distance\n";
    cout << "4 - Calculate the route\n"; //расчет прохождения трассы
    if (rez == 1)
        cout << "5 - Output results of last race\n";
    cout << "0 - Quit the program\n";
    int choice = 0;
    choice = InputProve(choice);
    if (choice == 4) {
        rez = 1;
    }
    return choice;
}
void AddTransports(Transport*& adres, int& quantity, Transport cars) {
    Transport* tempArray;
    if (adres != nullptr) {
        tempArray = new Transport[quantity + 1];
        for (int i = 0; i < quantity; i++) {
            tempArray[i] = adres[i];
        }
        delete[] adres;
    }
    else {
        tempArray = new Transport[1];
    }
    tempArray[quantity] = cars;
    adres = tempArray;
    quantity++;
}

Transport* RatingResults(Transport*& adres, int quantity) {
    Transport* results = new Transport[quantity];
    Transport* rez_copy = new Transport[1];
    for (int i = 0; i < quantity; i++) {
        results[i] = adres[i];
    }
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity; j++) {
            if ((results[i].GetTime() - results[j].GetTime() < 0) &&
                (results[i].GetCountRefuel() - results[i].GetCountRefuel() <= 0)) {
                rez_copy[0] = results[i];
                results[i] = results[j];
                results[j] = rez_copy[0];
            }
        }
    }
    delete[] rez_copy;
    return results;
}
void OutputResults(Transport*& adres, int quantity) {
    Transport* results = RatingResults(adres, quantity);
    for (int i = 0; i < quantity; i++) {
        cout << results[i].name << endl;
        results[i].TimeDisplay();
        cout << "Refuel times: " << int(results[i].NRefuel) << endl << endl;
    }
    delete[] results;
}

double InputProve(double var) {
    cin >> var;
    if (cin.fail() || var <= 0) {
        while (!(cin >> var) || var <= 0) {
            cout << "Uncorrect, try again\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return var;
}
int InputProve(int var) {
    cin >> var;
    if (cin.fail() || var < 0) {
        while (!(cin >> var) || var < 0) {
            cout << "Uncorrect, try again\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return var;
}

int Wheel::Check_status(double mileage, double speed) {
    double ratio = (1 / (mileage * sqrt(speed)));
    if (ratio >= 0.5)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void Wheel::Output() {
    if (status == 1) {
        cout << "damaged" << endl;
    }
    else {
        cout << "not damaged" << endl;
    }
}
void Engine::Output() {
    cout << "Engine power: " << engPow << " HP;" << endl;
    cout << "Engine intake: " << engIntake << " l/100km;" << endl;
}

void Engine::DefEngine(double power) {
    cout << "Engine power in HP: ";
    power = InputProve(power);
    engPow = power;
    engIntake = CalculateConsumption();
}
void Fuel_System::CalculateCurrentFuel(double engIntake, double mileage, double NRefuel) { //расчёт текущего обЪёма топлива
    if (NRefuel == 0) {
        current_fuel = double(TankCapacity - ((engIntake / 100) * mileage));
    }
    else {
        current_fuel = (((NRefuel)*TankCapacity) - ((engIntake / 100) * mileage));
    }
}
void Fuel_System::DefFuelSystem(double capacity, double engIntake, double mileage) {
    cout << "fuel capacity: ";
    capacity = InputProve(capacity);
    TankCapacity = capacity;
    current_fuel = capacity;
}
void Fuel_System::Output() {
    cout << "fuel capacity: " << TankCapacity << "l" << endl;
    cout << "current fuel: " << current_fuel << "l" << endl;
}

void Transport::Output() {
    cout << "Number of wheels: " << Nwheels << ";\n"
        << "Damaged wheels: " << damaged_wheels << ";\n"
        << "speed: " << speed << " km/h;\n"
        << "mileage: " << mileage << " km;" << endl;
    Engine::Output();
    Fuel_System::Output();
}

void Transport::TimeDisplay() {
    double t = this->Time;
    int hours = int(t);
    double cur_time = (t - hours) * 60;
    int minutes = int(cur_time);
    int seconds = int((cur_time - minutes) * 60);
    cout << "TIME: " << hours << ":" << minutes << ":" << seconds << endl;
}

void Transport::CalculateSpeed() {
    if (damaged_wheels == 0) {
        speed = double(fabs(sqrt(engPow) * (70.0 / double(Nwheels) - 2.5) * (current_fuel / 100.0)));
    }
    else
    {
        speed = (fabs(sqrt(engPow) * (70.0 / double(Nwheels) - 2.5) * (current_fuel / 100.0)) / (pow(2., double(damaged_wheels))));
    }
}


void Transport::NumberOfDamagedWheels() {
    int count = 0;
    for (int i = 0; i < Nwheels; i++) {
        if (ptr_wheel[i].GetStatus() == 1) {
            count++;
        }
    }
    damaged_wheels = count;
}

void Transport::CalculateRefuel(double raceLength) {
    double Refuel = (raceLength * (engIntake / 100)) / TankCapacity;
    if (Refuel > 1)
        this->NRefuel = ceil(Refuel);
    else
        this->NRefuel = floor(Refuel);
}
