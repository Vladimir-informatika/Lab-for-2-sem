#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//доделать меню, сделать все как надо. Переопределить некоторые методы, которые были щадекларированы во второй лабе


//Красивее вывод результатов гонки селать. Также вывод (меню 2)

int InputValue(int var);
double InputValue(double var);

class Wheel
{
    double current_mileage;
    bool status; // целое или нет
public:
    Wheel();
    bool CheckStatus(double mileage, double speed);
    double DefWheel(double mileage, double speed);
    bool GetStatus();
    virtual void Output();
};
Wheel::Wheel() {
    current_mileage = 0;
    status = true;
}
bool Wheel::CheckStatus(double mileage, double speed) {
    double ratio = 1 / (mileage*sqrt(speed));
    if (ratio >= 0.5) return true;
    else return false;
}
double Wheel::DefWheel(double mileage, double speed) {
    current_mileage = mileage;
    status = CheckStatus(mileage, speed);
    return current_mileage; ///////////////////////////////?????????????????????????????????????????????
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
    cout << "Engine power in HP: ";
    powerEn = InputValue(power);
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
    void CalculateCurrentFuel(double consumption, double mileage, double refills);
    void DefFuelSystem(double capacity, double consumption, double mileage);
    virtual void Output();
};
Fuel_System::Fuel_System() {
    volume_tank = current_fuel = 0;
}
void Fuel_System::CalculateCurrentFuel(double consumption, double mileage, double refills) {
    if (refills == 0) current_fuel = double(volume_tank - ((consumption / 100) * mileage));
    else current_fuel = ((refills * volume_tank) - ((consumption / 100) * mileage));
}
void Fuel_System::DefFuelSystem(double capacity, double consumption, double mileage) {
    capacity = volume_tank;
    cout << "Input Volume Tank in l:";
    capacity = InputValue(capacity);
    volume_tank = capacity;
    current_fuel = capacity;
}
void Fuel_System::Output() {
    cout << "Fuel capacity: " << volume_tank << " l" << endl;
    cout << "Current fuel: " << current_fuel << " l" << endl;
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

void Transports::TimeDisplay() {
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
    cout << "Count wheels: " << count_wheels << endl
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
    mileage = distance;
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





//
//class Transport
//{
//    int count_wheels;
//    double mileage;
//    double volume_tank;
//    double power_engine;
//    double travel_time;
//    string name;
//    double speed;
//    double engine_consumption;
//    int refills;
//public:
//    Transport();
//    Transport(int countWheels, double mil, double volumeTank, double power, string str);
//
//    double CalcEngineConsumption();
//    double CalcSpeed();
//    void CalcTravelTime(double distance);
//    void CalcRefills(double distance);
//    void PrintData();
//    void PrintRefillsAndTravelTime();
//    double GetTravelTime();
//    double GetRefills();
//
//    ~Transport();
//};
//
//Transport::~Transport() {
//    cout << "Transport " << name << " deleted!" << endl;
//}
//
//Transport::Transport() {
//    count_wheels = 0;
//    mileage = 0;
//    volume_tank = 0;
//    power_engine = 0;
//    name = "";
//
//    speed = 0;
//    engine_consumption = 0;
//    refills = 0;
//    travel_time = 0;
//}
//
//Transport::Transport(int countWheels, double mil, double volumeTank, double power, string str) {
//    count_wheels = countWheels;
//    mileage = mil;
//    volume_tank = volumeTank;
//    power_engine = power;
//    name = str;
//    speed = CalcSpeed();
//    engine_consumption = CalcEngineConsumption();
//    refills = 0;
//    travel_time = 0;
//    cout << "Transport " << name << " added!" << endl;
//}
//
//double Transport::CalcSpeed() {
//    return power_engine * 0.5 / count_wheels;
//}
//
//double Transport::CalcEngineConsumption() {
//    return power_engine * 0.5;
//}
//
//void Transport::CalcTravelTime(double distance) {
//    travel_time = distance / CalcSpeed();
//}
//
//double Transport::GetTravelTime()
//{
//    return travel_time;
//}
//
//void Transport::CalcRefills(double distance) {
//    refills = (int)floor(distance / (volume_tank
//    * CalcEngineConsumption()));
//}
//
//double Transport::GetRefills() {
//    return refills;
//}
//
//void Transport::PrintRefillsAndTravelTime() {
//        int hours = (int) travel_time;
//    double tim = (travel_time - hours) * 60;
//    int minutes = (int)tim;
//    int seconds = int(tim - minutes) * 60;
//
//    if (hours < 24)
//    {
//        cout << hours << ":" << minutes << ":" << seconds << endl;
//    }
//    else
//    {
//        int days = (int) travel_time/24;
//        hours = int(travel_time  - days*24);
//        cout << days << " days " << hours << " hours " << minutes << " minutes " << seconds << " seconds" << endl;
//    }
//}
//
//void Transport::PrintData() {
//    cout << name << endl;
//    cout << "Count wheels: " << count_wheels << endl
//    << "Power engine: " << power_engine << endl
//    << "Speed: " << speed << endl
//    << "Engine consumption: " << engine_consumption << endl << endl;
//}


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
                        transports[i].CalculateCurrentFuel(transports[i].Calculate_Consumption(), distance, transports[i].GetRefills());
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
//                    Sort(transports, quantity);
//                    cout << "Name\t\tRefills\t\tTravel time\n";
//                    for (int i = 0; i < quantity; i++) transports[i].();
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
    for (int i = 0; i < quantity; i++) {
        cout << results[i].name << endl;
        results[i].TimeDisplay();
        cout << "Refuel times: " << int(results[i].refills) << endl;
    }
    delete[] results;
}



// Консольное меню
int Menu ()
{
    cout << "--------------------------------" << endl;
    cout << "\tMENU" << endl;
    cout << "1. Add transport" << endl;
    cout << "2. Show existing transports" << endl;
    cout << "3. Enter/change route length" << endl;
    cout << "4. Calculate routes for each transport" << endl;
    cout << "5. See the result of completing the route" << endl;
    cout << "6. Quit the program\n" << endl;
    cout << "Your choice: " << endl;
    string s;
    cin >> s;
    int choice = StringReaderForInt(s);
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

    cout << "Input count of wheels: ";// количество колес;
    int count_wheels_for_constr = InputValue(count_wheels_for_constr);

    // Пробег


//    cout << "Input the mileage :"; //пробег;
//    double mileage_for_constr = InputValue(mileage_for_constr);
//
//    // Объём бака
//
//    cout << "Input the volume of the tank :";  //объем бака;
//    double volume_tank_for_constr = InputValue(volume_tank_for_constr);
//
//    cout << "Input the power of the engine :";   //мощность двигателя;
//    double power_engine_for_constr = InputValue(power_engine_for_constr);


    cout << "Input the name of transport :";  //название.
    string name_for_constr;
    cin >> name_for_constr;

    //Конструктор нашего транспорта
    transport[quantity] = Transports(name_for_constr, count_wheels_for_constr);
    cout << endl << "Transport added!" << endl;
}



//Конвертируем строку в целое число
int StringReaderForInt(string value)
{
    int choice = 0;
    for (int i = 0; i < value.length(); i++)
    {
        if ((int(value[i]) > 47) && (int(value[i]) < 58)) choice += (int(value[i]) - 48) * pow(10, i);
    }
    return choice;
}
//
//void Sort(Transports* Transports, int amount)
//{
//    for (int i = 0; i < amount; i++)
//    {
//        for (int j = 0; j < amount; j++)
//        {
//            if (Transports[i].GetTravelTime() > Transports[j].GetTravelTime())
//            {
//                Transport temporary = Transports[i];
//                Transports[i] = Transports[j];
//                Transports[j] = temporary;
//            }
//            else if (Transports[i].GetTravelTime() == Transports[j].GetTravelTime())
//            {
//                if (Transports[i].GetRefills() > Transports[j].GetRefills())
//                {
//                    Transport temporary = Transports[i];
//                    Transports[i] = Transports[j];
//                    Transports[j] = temporary;
//                }
//            }
//        }
//    }
//}
//

int InputValue(int var)
{
    cin >> var;
    if(cin.fail() || var <= 0)
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
    if(cin.fail() || var <= 0)
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
