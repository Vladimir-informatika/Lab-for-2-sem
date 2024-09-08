#include <iostream>
#include "cmath"
#include <limits>
#include <string>

#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>

using namespace std;

class Wheel;
class Engine;
class Fuel_System;

double refuel_time = 0.0003;
double change_time = 0.008; 
double dt = 0.0003;
double InputValues(double var); 
int InputValues(int var);
int Menu(int& rez);
void Clean(int var = 1);

class Wheel {
    double current_mileage;
    int status; 
public:
    int CheckStatus(double mileage, double speed);
    Wheel() { status = 0; current_mileage = 0; };
    virtual ~Wheel() {};//требуется для корректной работы компилятора 
    void DefWheel(double mileage, double speed);
    void Output();
    int GetStatus() { return status; }
    void SetStatus(int status) {
        this->status = status;
    }
};

class Engine {
protected:
    double power_engine; //мощность двигателя HP horsepower
    double consumption; //потребление двигателя литров/км l/100km
public:
    inline double CalculateConsumprion() { return fabs(pow(power_engine, 1 / 3) + sqrt(power_engine) - 6.25); }
    Engine() { consumption = 0; power_engine = 0; };
    void DefEngine(double power);
};

class Fuel_System {
protected:
    double current_fuel; //текущий обЪём топлива литры l;
public:
    double tank_capacity; //обЪём бака литры l
    void CalculateCurrentFuel(double consumption, double mileage);
    Fuel_System() { tank_capacity = 0; current_fuel = 0; };
    void DefFuelSystem();
};

class Transport : public Engine, public Fuel_System {
private:
    int count_wheels;
    double speed; //скорость км/ч km/h
    double Time;    //время пути hour
    int damaged_wheels;
    double count_refils; //количесвто дозаправок
    double mileage; //пробег km
    double current_mileage;//текущее положение на круге km
    int current_circles;
public:
    vector<Wheel> vec_wheels;
    string name;
    double pit_stop_time;
    Transport() {
        name = "ADDVEHICLE";
        Time = current_mileage = mileage = count_refils = pit_stop_time = 0;
        damaged_wheels = current_circles = 0;
    }
    Transport(string vehicle_name, int wheels) {
        current_mileage = mileage = pit_stop_time = 0;
        damaged_wheels = current_circles = 0;
        name = vehicle_name;
        count_wheels = wheels;
        for (int i = 0; i < wheels; i++) {
            Wheel newWheel;
            vec_wheels.push_back(newWheel);
        }
        DefFuelSystem();
        DefEngine(0);
        CalculateSpeed();
    }

    void CalculateSpeed();
    void SetMileage(double tracklen) { mileage = tracklen; }
    ~Transport() { cout << "Destruction of " << name << endl; }
    inline void CalculateRaceTime(double raceLength) {
        Time = (raceLength / speed);
    }
    void Reset();

    void TotalTime()
    {
        Time = Time + pit_stop_time;
    }

    int CalculateLaps(double trackLen)
    {
        if (current_mileage - trackLen >= 0)
        {
            current_circles = int(mileage / trackLen);
            current_mileage = 0;
            return 1;
        }
        else { return 0; }
    }

    double WheelsChange()
    {
        double time = damaged_wheels * change_time;
        return time;
    }

    double RefuelTime()
    {
        double time = ((tank_capacity - current_fuel) * refuel_time);
        return time;
    }

    double GetTime() { return Time; };
    void SetTime(double Time) { this->Time = Time; };
    double GetCountRefils() { return count_refils; };
    void PlusCountRefuel() { count_refils++; }
    double GetSpeed() { return speed; };
    int GetDamagedWheels() { return damaged_wheels; };
    double GetMileage() { return mileage; };
    void SETmileage(double len) { this->mileage = len; };
    void MileagePlus() { this->mileage += (speed * dt); };
    double GetCurrentMileagee() { return current_mileage; };
    void SetCurrentMileagee(double len) { this->current_mileage = len; };
    void CurrentMileageePlus() { this->current_mileage += (speed * dt); };
    int GetCurrentCircless() { return current_circles; };
    void SetCurrentCircless(int circles) { this->current_circles = circles; };
    void CurrentLapsPlus() { this->current_circles++; }
    void CalculateRefuelss(double raceLength, int circles);
    void NeedRefils(double tracklen);
    void NeedChange();
    void TimeDisplay();
    int GetCountOfWheels() { return count_wheels; }
    double GetCurrentFuels() { return current_fuel; }
    void NumberOfDAmagedWheels();
    void Output();
    friend Transport* RatingResults(int qty);
    friend void OutputResults(vector <Transport> car, int qty);

    friend ostream& operator<<(ostream& stream, const Transport& obj) {
        return stream << "\n" << "Name: " << obj.name << "\n"
            << "Number of wheels: " << obj.count_wheels << ";\n"
            << "Damaged wheels: " << obj.damaged_wheels << ";\n"
            << "Speed: " << obj.speed << " km/h;\n"
            << "Mileage: " << obj.mileage << " km;\n"
            << "fuel capacity: " << obj.tank_capacity << " l;\n"
            << "current fuel: " << obj.current_fuel << " l\n"
            << "Engine power: " << obj.power_engine << " HP;\n"
            << "Engine intake: " << obj.consumption << " l/100km;" << endl;
    }

    friend istream& operator >> (istream& stream, Transport& obj)
    {
        cout << "Vehicle name: ";
        stream >> obj.name;
        try
        {
            cout << "Number of wheels: ";
            stream >> obj.count_wheels;
            if (obj.count_wheels < 2) {
                throw "Uncorrect number of wheels! try again";
            }
        }
        catch (const char* msg) {
            cerr << "Exception caught: " << msg << endl;
            obj.count_wheels = InputValues(obj.count_wheels);
        }
        for (int i = 0; i < obj.count_wheels; i++) {
            Wheel newWheel;
            obj.vec_wheels.push_back(newWheel);
        }
        try
        {
            cout << "Tank capacity: ";
            stream >> obj.tank_capacity;
            if (obj.tank_capacity <= 0) {
                throw "Uncorrect tank capacity! try again";
            }
        }
        catch (const char* msg)
        {
            cerr << "Exception caught: " << msg << endl;
            obj.tank_capacity = InputValues(obj.tank_capacity);
        }
        try
        {
            cout << "Engine power: ";
            stream >> obj.power_engine;
            if (obj.power_engine <= 0) {
                throw "Uncorrect power of Engine! try again";
            }
        }
        catch (const char* msg)
        {
            cerr << "Exception caught: " << msg << endl;
            obj.power_engine = InputValues(obj.power_engine);
        }
        obj.current_fuel = obj.tank_capacity;
        obj.DefEngine(obj.power_engine);
        obj.CalculateSpeed();
        return stream;
    }

    Transport& operator=(const Transport& other) {
        name = other.name;
        count_wheels = other.count_wheels;
        speed = other.speed;
        mileage = other.mileage;
        current_mileage = other.current_mileage;
        current_circles = other.current_circles;
        Time = other.Time;
        return *this;
    }
};

int AllFinisheed(vector<Transport>& v, double trackLen, int circles);
int Skip(vector<int> skip_id, int i);

vector<Transport>RatingResults(vector<Transport> v);
void OutputResults(vector<Transport> v);





int main() {
    srand(time(NULL));
    vector<Transport> race_rez;
    vector<Transport> cars;
    int NumCircles{};
    double trackLen = 0;
    int flag = 1;
    int rez = 0;
    while (flag == 1) {
        int choice = 10;
        try
        {
            choice = Menu(rez);
            if ((choice > 5) || (choice < 0)) {
                throw "Error, try another number!";
            }
        }
        catch (const char* msg)
        {
            cerr << "Exception caught: " << msg << endl;
            cout << "try again ";
            choice = InputValues(choice);
        }
        switch (choice) {
        case (0): {
            cout << "Are you sure you want to exit?\n1-yes\n0-go back\n";
            int exit = 2;
            exit = InputValues(exit);
            if (exit == 1) {
                flag = 0;
                break;
            }
            else {
                Clean();
            }
            break;
        }
                break;
        case (1): {
            Clean();
            Transport addcar;
            cin >> addcar;
            cars.push_back(addcar);
            Clean();
            rez = 0;
            break;
        }
        case (2): {
            Clean();
            for (int i = 0; i < cars.size(); i++) {
                cout << cars[i];
            }
            break;
        }
        case (3): {
            Clean();
            try {
                cout << "The number of circles: ";
                NumCircles = 0;
                NumCircles = InputValues(NumCircles);
                if (NumCircles <= 0) {
                    throw "Uncorrect number of circles! try again";
                }
            }
            catch (const char* msg)
            {
                cerr << "Exception caught: " << msg << endl;
                cout << "try again ";
                NumCircles = InputValues(NumCircles);
            }
            cout << "Enter the length of the track (km): ";
            trackLen = InputValues(trackLen);
            rez = 0;
            break;
        }
        case (4): {
            Clean();
            if (trackLen == 0 || NumCircles == 0) {
                cout << "You haven't entered the length of the track!\n";
                rez = 0;
                break;
            }
            else
            {
                for (int i = 0; i < cars.size(); i++)
                {
                    cars[i].Reset();
                }
                double current_time = 0;
                vector<int> skip_id{ -1 };
                int racing_cars = cars.size();
                while (!AllFinisheed(cars, trackLen, NumCircles))
                {
                    if (racing_cars <= 0)
                    {
                        break;//не работает если переместить это условие в while
                    }
                    for (int i = 0; i < cars.size(); i++)
                    {
                        int exit = 0;
                        if (find(skip_id.begin(), skip_id.end(), i) == skip_id.end())
                        {
                            cars[i].MileagePlus();
                            cars[i].CurrentMileageePlus();
                            for (int j = 0; j < cars[i].vec_wheels.size(); j++)
                            {
                                cars[i].vec_wheels[j].DefWheel(cars[i].GetMileage(), cars[i].GetSpeed());
                            }
                            cars[i].NumberOfDAmagedWheels();
                            cars[i].CalculateCurrentFuel(cars[i].CalculateConsumprion(), cars[i].GetCurrentMileagee());
                            cars[i].CalculateSpeed();
                            cars[i].SetTime(current_time);
                            cars[i].TimeDisplay();
                            cout << "car: " << cars[i].name
                                << " circle: " << cars[i].GetCurrentCircless() + 1
                                << " speed: " << cars[i].GetSpeed() << "\n"
                                << " Current fuel " << cars[i].GetCurrentFuels()
                                << " Damaged wheels: " << cars[i].GetDamagedWheels() << "\n"
                                << " Mileage: " << cars[i].GetMileage() << "\n";
                            if (cars[i].GetDamagedWheels() == cars[i].vec_wheels.size() || (cars[i].GetCurrentFuels() <= 0))
                            {
                                exit = 1;
                                cars[i].SetTime(current_time);
                                cars[i].CurrentLapsPlus();
                            }
                            if ((trackLen * NumCircles) - (cars[i].GetMileage()) <= 0)
                            {
                                exit = 1;
                                cars[i].SetTime(current_time);
                                cars[i].SetCurrentCircless(NumCircles);
                                cars[i].TimeDisplay();
                                cout << "" << cars[i].name << " just finished" << endl;
                            }
                            if (exit == 1)
                            {
                                skip_id.push_back(i); // ТС будет пропускаться, так как финишировала
                                racing_cars = racing_cars - 1;
                                break;
                            }
                            if (cars[i].CalculateLaps(trackLen))
                            {
                                cars[i].NeedRefils(trackLen);
                                cars[i].NeedChange();
                            }
                        }
                        else
                        {
                            continue; // Пропускаем итерацию
                        }
                    }
                    current_time += dt;
                }
                for (int i = 0; i < cars.size(); i++)
                {
                    cars[i].TotalTime();
                }
            }
            break;
        }
        case (5): {
            Clean();
            OutputResults(cars);
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
    choice = InputValues(choice);
    if (choice == 4) {
        rez = 1;
    }
    return choice;
}

vector<Transport>  RatingResults(vector<Transport> v) {
    sort(v.begin(), v.end(), [](Transport& a, Transport& b) {
        if (a.GetTime() != b.GetTime()) {
            return a.GetTime() < b.GetTime();
        }
        else {
            return a.GetCountRefils() < b.GetCountRefils();
        }
        });
    return v;
}

void OutputResults(vector<Transport> v) {
    vector<Transport> results = RatingResults(v);
    for (int i = 0; i < results.size(); i++) {
        cout << results[i].name << endl;
        results[i].TimeDisplay();
        cout << "Circles " << results[i].GetCurrentCircless() << endl;
        cout << "Refuel times: " << int(results[i].GetCountRefils()) << endl << endl;
    }
}

double InputValues(double var) {
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

int InputValues(int var) {
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

void Wheel::DefWheel(double mileage, double speed) {
    if (mileage == 0.) {
        current_mileage = 0.;
        status = 0.;
    }
    else {
        current_mileage = mileage;
        status = CheckStatus(current_mileage, speed);
    }
}


int Wheel::CheckStatus(double mileage, double speed) {
    if (status == 0)
    {
        int end = ceil(sqrt(mileage)) + ceil(sqrt(speed));
        int start = -1000;//компенсирую большое кол-во итераций
        int ratio = ceil(((mileage) * (sqrt(speed) + 1)));
        int damageProb = rand() % (end - (start)+ratio) + start;
        if (damageProb - end >= 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else return 1;
}
void Wheel::Output() {
    if (status == 1) {
        cout << "damaged" << endl;
    }
    else {
        cout << "not damaged" << endl;
    }
}

void Engine::DefEngine(double power) {
    power_engine = power;
    consumption = CalculateConsumprion();
}

void Fuel_System::CalculateCurrentFuel(double consumption, double mileage) { //расчёт текущего обЪёма топлива
    current_fuel = double(tank_capacity - ((consumption / 100) * mileage));
}

void Fuel_System::DefFuelSystem() {
    cout << "fuel capacity: ";
    double capacity = 0.;
    capacity = InputValues(capacity);
    tank_capacity = capacity;
    current_fuel = capacity;
}


void Transport::TimeDisplay()
{
    double t = this->Time;
    int hours = int(t);
    double cur_time = (t - hours) * 60;
    int minutes = int(cur_time);
    int seconds = int((cur_time - minutes) * 60);
    cout << "TIME: " << setw(4) << setfill('0') << hours << ":" << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << seconds << endl;
}

void Transport::CalculateSpeed()
{
    if (damaged_wheels == 0) {
        speed = double(fabs(sqrt(power_engine) * (70.0 / double(count_wheels) - 2.5) / sqrt(current_fuel)));
    }
    else
    {
        speed = (fabs(sqrt(power_engine) * (70.0 / double(count_wheels) - 2.5) / sqrt(current_fuel)) * (pow(0.75, double(damaged_wheels))));
    }
}

void Transport::NumberOfDAmagedWheels()
{
    int count = 0;
    for (int i = 0; i < vec_wheels.size(); i++)
    {
        if (vec_wheels[i].GetStatus() == 1) {
            count++;
        }
    }
    damaged_wheels = count;
}

void Transport::NeedRefils(double tracklen)
{
    if (current_fuel < (consumption * 100) * tracklen)
    {
        this->PlusCountRefuel();
        pit_stop_time += this->RefuelTime();
        current_fuel = tank_capacity;
    }
}

void Transport::NeedChange()
{
    if (damaged_wheels != 0)
    {
        pit_stop_time += this->WheelsChange();
        for (int i = 0; i < vec_wheels.size(); i++)
        {
            if (vec_wheels[i].GetStatus() == 1)
            {
                vec_wheels[i].DefWheel(0., 0.);
            }
        }
    }
}

void Transport::Reset()
{
    for (int i = 0; i < vec_wheels.size(); i++)
    {
        vec_wheels[i].SetStatus(0);
    }
    damaged_wheels = 0;
    current_mileage = mileage = 0;
    count_refils = current_circles = 0;
    Time = 0;
    current_fuel = tank_capacity;
    CalculateSpeed();
    for (int j = 0; j < vec_wheels.size(); j++)
    {
        vec_wheels[j].DefWheel(mileage, GetSpeed());
    }
    cout << "\n" << name << " reseted" << endl;
}

int AllFinisheed(vector<Transport>& v, double trackLen, int circles)
{
    int count = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].GetCurrentMileagee() - trackLen * circles >= 0)
        {
            count++;
        }
    }
    if (count == v.size())
    {
        return 1;
    }
    else return 0;
}

