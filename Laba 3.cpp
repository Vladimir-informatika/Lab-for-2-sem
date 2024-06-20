#include <iostream>
#include <string>
#include <cmath>
#include <limits>
#include <random>

using namespace std;

//доделать меню, сделать все как надо. Переопределить некоторые методы, которые были щадекларированы во второй лабе
// если скорость равно 0, транспорт выбывает из гонки
//сделать лимиты - адеквватных значений

int InputValue(int var);
double InputValue(double var);
int Probability();

class Wheel;
class Engine;
class Fuel_System;
class Transports;

class Wheel
{
    double current_mileage;
    bool status; // целое или нет
public:
    Wheel();
    bool CheckStatus(double mileage, double speed);
    void DefWheel(double mileage, double speed);
    bool GetStatus();
    virtual void Output();
};
Wheel::Wheel() {
    current_mileage = 0;
    status = true;
}



bool Wheel::CheckStatus(double mileage, double speed) {
    const int probability = Probability();
    if (mileage >= 60000) return false;
    else if (mileage >= 45000 && mileage < 60000) {
        if (probability <= 75) {
            return false;
        }
        else return true;
    }

    else if (mileage >= 30000 && mileage < 45000) {
        if (probability <= 50) {
            return false;
        }
        else return true;
    }
    else if (mileage >= 15000 && mileage < 30000) {
        if (probability <= 25) {
            return false;
        }
        else return true;
    }
    else if (mileage > 5000 && mileage < 15000) {
        if (probability < 10) {
            return false;
        }
        else return true;
    }
    else return true;
}
void Wheel::DefWheel(double mileage, double speed) {
    current_mileage = mileage;
    if (status) status = CheckStatus(mileage, speed);
    //return current_mileage; ///////////////////////////////?????????????????????????????????????????????
}
bool Wheel::GetStatus() {
    return status;
}
void Wheel::Output() {
    if (!status){
        cout << "Damaged" << endl;
    }
    else{
        cout << "Not damaged" << endl;
    }
}



class Engine
{
protected:
    double power;
    double consumption;
public:
    Engine();
    void DefEngine(double powerEn);
    inline double Calculate_Consumption(); // define
    virtual void Output();
};

Engine::Engine() {
    power = consumption = 0;
}
void Engine::DefEngine(double powerEn) {
    cout << "Engine power in HP (0.01 < x < 114 800): ";
    powerEn = InputValue(powerEn);
    bool flag = true;
    if (powerEn >= 114800 || powerEn < 0.01) {
        cout << "THIS IS A MADNESS!! Have you ever seen a car with SOOO powerful engine?"
        << endl << "I refuse to accept this, try again" << endl;
        flag = false;
        while (!flag) {
            powerEn = InputValue(powerEn);
            if (powerEn < 114800 && powerEn >= 0.01) flag = true;
            else {
                cout << "You seem to have misunderstood me, let's do it again" << endl;
            }
        }
    }
    power = powerEn;
    consumption = Calculate_Consumption();
}
void Engine::Output() {
    cout << "Power of engine: " << power << " HP" << endl;
    cout << "Consumption of engine: " << consumption << " l/100 km" << endl;
}
double Engine::Calculate_Consumption() {
    return fabs(pow(power, 1/3) + sqrt(power) - 6.25);//////////////////////////////////////////////////// formula
}



class Fuel_System
{
protected:
    double volume_tank;
    double current_fuel;
public:
    Fuel_System();
    void CalculateCurrentFuel(double power, int distance, double refills);
    void DefFuelSystem(double capacity, double consumption, double mileage);
    virtual void Output();
};
Fuel_System::Fuel_System() {
    volume_tank = current_fuel = 0;
}

void Fuel_System::CalculateCurrentFuel(double power, int distance, double refills) {
    // if (refills == 0) current_fuel = double(volume_tank - (consumption * mileage));
    // else current_fuel = ((refills * volume_tank) - (consumption * mileage));
    if (refills == 0) {
        current_fuel = distance * ( power/100 );
    }
    else {
        current_fuel = (distance * (power / 100)) - (refills * volume_tank);
    }
}
void Fuel_System::DefFuelSystem(double capacity, double consumption, double mileage) {
    capacity = volume_tank;
    cout << "Input Volume Tank in l:";
    capacity = InputValue(capacity);
    bool flag = true;
    if (capacity >= 1000 || capacity < 0.01) {
        cout << "THIS IS A MADNESS!! Have you ever seen a car with SOOO volume tank?"
        << endl << "I refuse to accept this, try again" << endl;
        flag = false;
        while (!flag) {
            capacity = InputValue(capacity);
            if (capacity < 1000 && capacity >= 0.01) flag = true;
            else {
                cout << "You seem to have misunderstood me, let's do it again" << endl;
            }
        }
    }
    volume_tank = capacity;
    current_fuel = capacity;
}
void Fuel_System::Output() {
    cout << "Fuel capacity: " << volume_tank << " l" << endl;
    cout << "Current fuel: " << current_fuel << " l" << endl
    << "-----------------------------" << endl;
}



class Transports : public Engine, public Fuel_System
{
    int count_wheels;
    double speed;
    double time;
    int damaged_wheels = 0;
    double mileage;
    int refills;
public:
    Wheel* wheel_ptr;
    string name;
    Transports();
    Transports(string name_Transports, int wheels);
    void CalculateSpeed();
    void SetName(string name_Transports);
    void SetWheels(int countWheels);
    void SetMileage(double distance);
    double GetTime();
    double GetRefills();
    double GetSpeed();
    double GetPower();
    void CalculateRefills(double distance);
    void TimeDisplay();
    int GetWheels();
    void NumberOfDamagedWheels();
    inline void CalculateRaceTime(double distance);
    void Output();
    friend Transports* RacingResults(Transports *&transp, int quantity);
    friend void OutputResult(Transports *&transp, int quantity);
    ~Transports();
};
Transports::Transports() {
    name = "AddTransports";
    time = mileage = refills = damaged_wheels = 0;
    wheel_ptr = nullptr;
}
Transports::Transports(string name_Transports, int wheels) {
    mileage = damaged_wheels = 0;
    SetName(name_Transports);
    SetWheels(wheels);
    wheel_ptr = new Wheel[wheels];
    for (int i = 0; i < wheels; i++) wheel_ptr[i] = Wheel();
    DefFuelSystem(0, power, mileage);
    DefEngine(0);
    CalculateSpeed();
}

void Transports::CalculateSpeed() {
    if (damaged_wheels == 0) speed = double(fabs( sqrt(power) * (70.0 / double(count_wheels) - 2.5) * (current_fuel / 100.0)));
    else speed = fabs( sqrt(power) * (70.0 / double(count_wheels) - 2.5) * (current_fuel / 100.0)) / (pow(2, double(damaged_wheels)));
}

void Transports::CalculateRefills(double distance) {
    refills = floor((distance * (power / 100)) / volume_tank);
}

void Transports::TimeDisplay()
{
    int hours = (int) time;
    double tim = (time - hours) * 60;
    int minutes = (int)tim;
    int seconds = int(tim - minutes) * 60;

    if (hours < 24)
    {
        cout << hours << ":" << minutes << ":" << seconds << endl;
    }
    else
    {
        int days = (int) time/24;
        hours = int(time  - days*24);
        cout << days << " days " << hours << " hours " << minutes << " minutes " << seconds << " seconds" << endl;
    }
}

int Transports::GetWheels() {
    return count_wheels;
}

void Transports::NumberOfDamagedWheels() {
    int count = 0;
    for (int i = 0; i < count_wheels; i++) if (!wheel_ptr[i].GetStatus()) count++;
    damaged_wheels = count;
}

void Transports::Output() {
    cout << name << endl
    << "Count wheels: " << count_wheels << endl
    << "Damaged wheels: " << damaged_wheels << endl
    << "Speed: " << speed << " km/h" << endl
    << "Mileage: " << mileage << " km" << endl;
    Engine::Output();
    Fuel_System::Output();
}

void Transports::SetName(string name_Transports) {
    name = name_Transports;
}

void Transports::SetWheels(int countWheels) {
    count_wheels = countWheels;
}

void Transports::SetMileage(double distance) {
    mileage += distance;
}

double Transports::GetPower() {
    return power;
}

double Transports::GetTime() {
    return time;
}

double Transports::GetRefills() {
    return refills;
}

double Transports::GetSpeed() {
    return speed;
}

Transports::~Transports() {
    cout << "Destruct " << name << endl;
}

void Transports::CalculateRaceTime(double distance) {
    time = (distance / speed);
}



Transports* RacingResults(Transports *&transp, int quantity);
int Menu(); //Делаем меню
Transports* AddTransport(Transports* Transports, int amount); //Создаем и перезаписываем массив транспортов
void SetData(Transports* transport, int quantity);  // Добавляем данные с консоли для нашего транспорта
int StringReaderForInt(string value); //Конвертируем строку в целое число
void Sort(Transports* Transports, int amount); // Сортируем для 5 пункта меню



int main()
{
    Transports* transports = nullptr;


    int quantity = 0;
    double distance = 0;

    bool flag = false;
    bool menu = true;

    while (menu) {
        int k = Menu();
        switch (k) {
            case 1:
                transports = AddTransport(transports, quantity);
                SetData(transports, quantity);
                quantity++;
                break;
            case 2:
                if (quantity == 0)
                {
                    cout << "Julius Sergeevich, you didn't add any transport. What did you expected to see?" << endl;
                }
                else for (int i = 0; i < quantity; i ++) transports[i].Output();
                break;
            case 3:
                cout << "Input/change route length: ";
                distance = InputValue(distance);
                flag = false;
                break;
            case 4:
                if (quantity == 0 || distance == 0) {
                    cout << "Array of transport is empty or distance is null\n";
                }
                else {
                    for (int i = 0; i < quantity; i++) {
                        transports[i].CalculateRaceTime(distance);
                        transports[i].SetMileage(distance);
                        for (int j = 0; j < transports[i].GetWheels(); j++) {
                            transports[i].wheel_ptr[j].DefWheel(distance, transports[i].GetSpeed());
                        }
                        transports[i].NumberOfDamagedWheels();
                        transports[i].CalculateRefills(distance);
                        double power;
                        power = transports[i].GetPower();
                        transports[i].CalculateCurrentFuel(power, distance, transports[i].GetRefills());
                        transports[i].CalculateSpeed();
                    }
                    flag = true;
                    cout << "Calculating...\n";
                }
                break;
            case 5:
                if (!flag) {
                    cout << "No-no-no! Firstly calculate THESE routes for each transport! Have you just changed distance and didn't calculate it for each transport?" << endl;
                }
                else{
                    OutputResult(transports, quantity);
                }
                break;
            case 6:
                cout << "Are you sure? (y/n)" << endl;
                char quit;
                cin >> quit;
                if (quit == 'y' || quit == 'Y')
                {
                    cout << "OK, as you wish" << endl;
                    menu = false;
                }
                break;
            default:

                break;
        }
    }
}

// Функции друзья

Transports* RacingResults(Transports *&transp, int quantity)
{
    Transports* result = new Transports[quantity];
    Transports* temp = new Transports[quantity];
    for (int i = 0; i < quantity; i++) {
        result[i] = transp[i];
    }
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity; j++) {
            if ((result[i].GetTime()- result[j].GetTime() < 0) && (result[i].GetRefills() - result[i].GetRefills() <= 0)) {
                temp[0] = result[i];
                result[i] = result[j];
                result[j] = temp[0];
            }
        }
    }
    delete[] temp;
    return result;
}

void OutputResult(Transports *&transp, int quantity)
{
    Transports *results = RacingResults(transp,quantity);
    cout << "Name\t\t\tRefills\t\t\tTravel time\n";
    for (int i = 0; i < quantity; i++) {
       // cout << results[i].name << ;
        cout << results[i].name << "\t\t\t" << results[i].refills << "\t\t\t";
        results[i].TimeDisplay();
       // cout << "Refuel times: " << int(results[i].refills) << endl;
    }
    delete[] results;
}



// Консольное меню
int Menu ()
{
    cout << "========================================" << endl;
    cout << "\tMENU" << endl;
    cout << "1. Add transport" << endl;
    cout << "2. Show existing transports" << endl;
    cout << "3. Enter/change route length" << endl;
    cout << "4. Calculate routes for each transport" << endl;
    cout << "5. See the result of completing the route" << endl;
    cout << "6. Quit the program\n" << endl;
    cout << "Your choice: " << endl;
    int choice = 0;
    choice = InputValue(choice);
    cout << '\n';
    return choice;
}

//Создаем и перезаписываем массив транспортов
Transports* AddTransport(Transports* transports, int amount)
{
    if (amount == 0) transports = new Transports[amount+1];
    else
    {
        Transports* temp = new Transports[amount + 1];
        for (int i = 0; i < amount; i++) temp[i] = transports[i];
        delete[] transports;
        transports = temp;
    }
    return transports;
}

// Добавляем данные с консоли для нашего транспорта
void SetData(Transports* transport, int quantity)
{
    //Кол-во колес

    cout << "Input count of wheels (less than 100! I think it is enough): ";// количество колес;
    int count_wheels_for_constr = 0;
    count_wheels_for_constr = InputValue(count_wheels_for_constr);
    bool flag = true;
    if (count_wheels_for_constr > 100 || count_wheels_for_constr < 1) {
        cout << "THIS IS A MADNESS!! Have you ever seen a similar car?"
        << endl << "I refuse to accept this, try again" << endl;
        flag = false;
        while (!flag) {
            count_wheels_for_constr = InputValue(count_wheels_for_constr);
            if (count_wheels_for_constr < 1000 && count_wheels_for_constr >= 0.01) flag = true;
            else {
                cout << "You seem to have misunderstood me, let's do it again" << endl;
            }
        }
    }


    cout << "Input the name of transport :";  //название.
    string name_for_constr;
    cin >> name_for_constr;

    //Конструктор нашего транспорта
    transport[quantity] = Transports(name_for_constr, count_wheels_for_constr);
    cout << endl << "Transport added!" << endl;
}





int InputValue(int var)
{
    cin >> var;
    if (cin.fail() || var <= 0)
    {
        while (!(cin >> var) || var <= 0)
        {
            cout << "Incorrect, try again!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize> :: max(), '\n');
        }
    }
    return var;
}

double InputValue(double var)
{
    cin >> var;
    if (cin.fail() || var <= 0)
    {
        while (!(cin >> var) || var <= 0)
        {
            cout << "Incorrect, try again!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize> :: max(), '\n');
        }
    }
    return var;
}

int Probability() {
    random_device rd;
    mt19937 gen(rd());
    return gen()%100;
}
