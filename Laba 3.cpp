#include <iostream>
#include <string>
#include <cmath>

using namespace std;


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
    powerEn = InputProve(power);
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
    capacity = InputProve(capacity);
    volume_tank = capacity;
    current_fuel = capacity;
}
void Fuel_System::Output() {
    cout << "Fuel capacity: " << volume_tank << " l" << endl;
    cout << "Current fuel: " << current_fuel << " l" << endl;
}




class Vehicle : public Engine, public Fuel_System
{
    int count_wheels;
    double speed;
    double time;
    int damaged_wheels = 0;
    double mileage;
    int refills;
public:
    Wheel * wheel_ptr;
    string name;
    Vehicle();
    Vehicle(string name_vehicle, int wheels);
    void CalculateSpeed();
    void SetName(string name_vehicle);
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
    //тут дальше перегрузки и функции друзья с указателем на этот класс
    void Output();
    
    ~Vehicle();
};
Vehicle::Vehicle() {
    name = "AddVehicle";
    time = mileage = refills = damaged_wheels = 0;
    wheel_ptr = nullptr;
}
Vehicle::Vehicle(string name_vehicle, int wheels) {
    mileage = damaged_wheels = 0;
    SetName(name_vehicle);
    SetWheels(wheels);
    wheel_ptr = new Wheel[wheels];
    for (int i = 0; i < wheels; i++) wheel_ptr[i] = Wheel();
    DefFuelSystem(0, power, mileage);
    DefEngine(0);
    CalculateSpeed();
}

void Vehicle::CalculateSpeed() {
    if (damaged_wheels == 0) speed = double(fabs( sqrt(power) * (70.0 / double(count_wheels) - 2.5) * (current_fuel / 100.0)));
    else speed = fabs( sqrt(power) * (70.0 / double(count_wheels) - 2.5) * (current_fuel / 100.0)) / (pow(2, double(damaged_wheels)));
}

void Vehicle::CalculateRefills(double distance) {
    refills = floor((distance * (power / 100)) / volume_tank);
}

void Vehicle::TimeDisplay() {

}

int Vehicle::GetWheels() {
    return count_wheels;
}

void Vehicle::NumberOfDamagedWheels() {
    int count = 0;
    for (int i = 0; i < count_wheels; i++) if (!wheel_ptr[i].GetStatus()) count++;
    damaged_wheels = count;
}

void Vehicle::Output() {
    cout << "Count wheels: " << count_wheels << endl
    << "Damaged wheels: " << damaged_wheels << endl
    << "Speed: " << speed << " km/h" << endl
    << "Mileage: " << mileage << " km" << endl;
    Engine::Output();
    Fuel_System::Output();
}

void Vehicle::SetName(string name_vehicle) {
    name = name_vehicle;
}

void Vehicle::SetWheels(int countWheels) {
    count_wheels = countWheels;
}

void Vehicle::SetMileage(double distance) {
    mileage = distance;
}

double Vehicle::GetTime() {
    return time;
}

double Vehicle::GetRefills() {
    return refills;
}

double Vehicle::GetSpeed() {
    return speed;
}

Vehicle::~Vehicle() {
    cout << "Destruct " << name << endl;
}

void Vehicle::CalculateRaceTime(double distance) {
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
//    cout << name << "\t\t" << refills << "\t\t" << travel_time << endl;
//}
//
//void Transport::PrintData() {
//    cout << name << endl;
//    cout << "Count wheels: " << count_wheels << endl
//    << "Power engine: " << power_engine << endl
//    << "Speed: " << speed << endl
//    << "Engine consumption: " << engine_consumption << endl << endl;
//}


































int Menu(); //Делаем меню
Transport* AddTransport(Transport* vehicle, int amount); //Создаем и перезаписываем массив транспортов
void SetData(Transport* transport, int quantity);  // Добавляем данные с консоли для нашего транспорта
double Check(bool checker, double value); // Делаем проверку на отрицательность при вводе
int Check(bool checker, int value);
int StringReaderForInt(string value); //Конвертируем строку в целое число
void Sort(Transport* vehicle, int amount); // Сортируем для 5 пункта меню
double InputDouble(bool flagg);
int InputInt(bool flagg);


int main()
{
    Transport* transport;
    int quantity = 0;
    double distance = 0;
    bool flag = false;
    bool menu = true;
    bool checker_for_route = true;
    while (menu) {
        int k = Menu();
        switch (k) {
            case 1:
                transport = AddTransport(transport, quantity);
                SetData(transport, quantity);
                quantity++;
                break;
            case 2:
                if (quantity == 0)
                {
                    cout << "Julius Sergeevich, you didn't add any transport. What did you expected to see?" << endl;
                }
                else for (int i = 0; i < quantity; i ++) transport[i].PrintData();
                break;
            case 3:
                cout << "Input/change route length: ";
                cin >> distance;
                Check(checker_for_route, distance);
                flag = false;
                break;
            case 4:
                if (quantity == 0 || distance == 0) {
                    cout << "Array of transport is empty or distance is null\n";
                }
                else
                {
                    for (int i = 0; i < quantity; i++) {
                        transport[i].CalcRefills(distance);
                        transport[i].CalcTravelTime(distance);
                    }
                    flag = true;
                    cout << "Calculating...\n";
                }
                break;
            case 5:
                if (!flag) {
                    cout << "No-no-no! Firstly calculate THESE routes for each transport! Have you just changed distance and didn't calculate it for each transport?" << endl;
                }
                else {
                    Sort(transport, quantity);
                    cout << "Name\t\tRefills\t\tTravel time\n";
                    for (int i = 0; i < quantity; i++) transport[i].PrintRefillsAndTravelTime();
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
Transport* AddTransport(Transport* vehicle, int amount)
{
    if (amount == 0) vehicle = new Transport[amount+1];
    else
    {
        Transport* temp = new Transport[amount + 1];
        for (int i = 0; i < amount; i++) temp[i] = vehicle[i];
        delete[] vehicle;
        vehicle = temp;
    }
    return vehicle;
}

// Добавляем данные с консоли для нашего транспорта
void SetData(Transport* transport, int quantity)
{
    bool checker = true;
    string str;
    //Кол-во колес
    cout << "Input count of wheels: ";// количество колес;
    int count_wheels_for_constr = InputInt(checker);


    // Пробег
    cout << "Input the mileage :"; //пробег;
    double mileage_for_constr = InputDouble(checker);

    // Объём бака
    cout << "Input the volume of the tank :";  //объем бака;
    double volume_tank_for_constr = InputDouble(checker);

    cout << "Input the power of the engine :";   //мощность двигателя;
    double power_engine_for_constr = InputDouble(checker);

    cout << "Input the name of transport :";  //название.
    string name_for_constr;
    cin >> name_for_constr;

    //Конструктор нашего транспорта
    transport[quantity] = Transport(count_wheels_for_constr, mileage_for_constr, volume_tank_for_constr, power_engine_for_constr, name_for_constr);
    cout << endl << "Transport added!" << endl;
}

// Делаем проверку на отрицательность при вводе
double Check(bool checker, double value) {
    if (value <= 0) checker = false;
    while (!checker){
        cout << "Incorrect, try again! Value must be greater than 0!";
        cin >> value;
        if (value > 0) checker = true;
    }
    cout << endl;
    return value;
}
int Check(bool checker, int value) {
    if (value < 1) checker = false;
    while (!checker) {
        cout << "Incorrect, try again! Value must be greater than 0!";
        cin >> value;
        if (value > 0) checker = true;
    }
    cout << endl;
    return value;
}

//Конвертируем строку в целое число
int StringReaderForInt(string value)
{
    int choice = 0;
    for (int i = 0; i < value.length(); i++)
    {
        if ((int(value[i]) > 47) && (int(value[i]) < 58))
        {
            choice += (int(value[i])-48) * pow(10, i) ;
        }
    }
    return choice;
}

void Sort(Transport* vehicle, int amount)
{
    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < amount; j++)
        {
            if (vehicle[i].GetTravelTime() > vehicle[j].GetTravelTime()) 
            {
                Transport temporary = vehicle[i];
                vehicle[i] = vehicle[j];
                vehicle[j] = temporary;
            }
            else if (vehicle[i].GetTravelTime() == vehicle[j].GetTravelTime())
            {
                if (vehicle[i].GetRefills() > vehicle[j].GetRefills())
                {
                    Transport temporary = vehicle[i];
                    vehicle[i] = vehicle[j];
                    vehicle[j] = temporary;
                }
            }
        }
    }
}

double InputDouble(bool flagg)
{
    double value = 0;
    cin >> value;
    value = Check(flagg, value);
    cout << endl;
    return value;
}

int InputInt(bool flagg)
{
    int value = 0;
    cin >> value;
    value = Check(flagg, value);
    cout << endl;
    return value;
}
