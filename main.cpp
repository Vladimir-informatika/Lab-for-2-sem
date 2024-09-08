#include "cmath"
#include <iostream>
#include <limits>
#include <string>
using namespace std;
int quantity = 0; //изначальный размер массива
double InputProve(double var);
int InputProve(int var);
class Transport {
private:
    double TankCapacity; //обЪём бака литры l
    double speed; //скорость км/ч km/h
    double engine_consumption; //потребление двигателя литров/км l/km
    double power_engine; //мощность двигателя HP horsepower
    int Nwheels;

public:///////////////////////////////////////////////////////
    double mileage; //пробег km
    double NRefuel; //количесвто дозаправок
    string name;
    double Time; //время пути hour
    inline double CalculateSpeed() {
        return fabs(sqrt(power_engine) * ((70 / double(Nwheels)) - 2.5));
    }
    inline double CalculateIntake() {
        return fabs(pow(power_engine, 1 / 3) + sqrt(power_engine) - 6.25);
    }
    double CalculateRefuel(double raceLength) {
        double Nrefuel = (raceLength * (engine_consumption / 100)) / TankCapacity;
        if (Nrefuel > 1)
            return ceil(Nrefuel);
        else
            return floor(Nrefuel);
    };
    inline double CalculateRaceTime(double raceLength) {
        return (raceLength / speed);
    };
    Transport() {
        name = "ADDVEHICLE";
        mileage = Time = NRefuel = 0;
    }
    Transport(string vehicle_name, double tank, double power, int wheels) {
        mileage = Time = NRefuel = 0;
        cout << "\nName of the car: ";
        cin >> vehicle_name;
        SetName(vehicle_name);
        cout << "Number of wheels: ";
        wheels = InputProve(wheels);
        while (wheels < 2) {
            cout << "Uncorrect number of wheels! try again:" << endl;
            wheels = InputProve(wheels);
        }
        SetNWheels(wheels);
        cout << "Power of the engine (HP): "; // horse power
        power = InputProve(power);
        SetPowerEngine(power);
        cout << "Tank capacity (l): ";
        tank = InputProve(tank);
        SetTankCapacity(tank);
        speed = CalculateSpeed();
        engine_consumption = CalculateIntake();
        cout << "\nCar added successfully!" << endl;
    }
    void SetTankCapacity(double tank) { TankCapacity = tank; }
    void SetPowerEngine(double power) { power_engine = power; }
    void SetName(string vehicle_name) { name = vehicle_name; }
    void SetNWheels(int wheels) { Nwheels = wheels; }
    ~Transport() { cout << "Destruction of " << name << endl; }
    void Output();
    void TimeDisplay();
};
int Menu(int& flag);
void Clean(int var = 1);
void AddTransport(Transport*& adres, int& quantity, Transport cars);
Transport* RatingResults(Transport*& adres, int quantity);
void OutputResults(Transport*& adres, int quantity);
/////////////////////////////////MAIN/////////////////////////
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
                break;
        case (1): {
            Clean();
            string vehicle_name = "";
            double tank = 0;
            double power = 0;
            int Nwheels = 0;
            Transport cars(vehicle_name, tank, power, Nwheels);
            Clean();
            AddTransport(adres, quantity, cars);
            rez = 0;
            break;
        }
        case (2): {
            Clean();
            for (int i = 0; i < quantity; i++) {
                cout << adres[i].name << endl;
                adres[i].Output();
                cout << endl;
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
                    adres[i].Time = adres[i].CalculateRaceTime(trackLen);
                    adres[i].mileage = trackLen;
                    adres[i].NRefuel = adres[i].CalculateRefuel(trackLen);
                }
            }
            break;
        }
        case (5): {
            Clean();
            OutputResults(*&adres, quantity);
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
void AddTransport(Transport*& adres, int& quantity, Transport cars) {
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
            if ((results[i].Time - results[j].Time < 0) &&
                (results[i].NRefuel - results[i].NRefuel <= 0)) {
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
        cout << endl << results[i].name << endl;
        results[i].TimeDisplay();
        cout << "Refuel times: " << int(ceil(results[i].NRefuel)) << endl << endl;
    }
    delete[] results;
}
void Transport::Output() {
    cout << "Number of wheels: " << Nwheels << ";\n"
        << "Power of engine: " << power_engine << " HP;\n"
        << "Speed of transport: " << speed << " km/h;\n"
        << "Engine consumprion: " << engine_consumption << " l/100km;\n"
        << "Mileage: " << mileage << " km;" << endl;
}
double InputProve(double var) {
    cin >> var;
    if (cin.fail() || var <= 0) {
        while (!(cin >> var) || var <= 0) {
            cout << "Incorrect, try again, please\n";
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
            cout << "Incorrect, try again, please\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return var;
}
void Transport::TimeDisplay() {
    double t = this->Time;
    int hours = static_cast<int>(t);
    double cur_time = (t - hours) * 60;
    int minutes = static_cast<int>((cur_time));
    int seconds = static_cast<int>((cur_time - minutes) * 60);
    cout << "TIME: " << hours << ":" << minutes << ":" << seconds << endl;
}
