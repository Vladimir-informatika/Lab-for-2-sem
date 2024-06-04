#include <iostream>
#include <string>
#include <cmath>

using namespace std;



// ДОБАВИТЬ ЕДИНИЦЫ ИЗМЕРЕНИЯ

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
public:
    Transport();
    Transport(int countWheels, double mil, double volumeTank, double power, string str);

    double CalcEngineConsumption();
    double CalcSpeed();
    void CalcTravelTime(double distance);
    void CalcRefills(double distance);
    void PrintData();
    void PrintRefillsAndTravelTime();
    ~Transport();
    double GetTravelTime();
    double GetRefills();
};

Transport::~Transport() {
    cout << "Transport " << name << " deleted!" << endl;
}

Transport::Transport() {
    count_wheels = 0;
    mileage = 0;
    volume_tank = 0;
    power_engine = 0;
    name = "";

    speed = 0;
    engine_consumption = 0;
    refills = 0;
    travel_time = 0;
}

Transport::Transport(int countWheels, double mil, double volumeTank, double power, string str) {
    count_wheels = countWheels;
    mileage = mil;
    volume_tank = volumeTank;
    power_engine = power;
    name = str;
    speed = CalcSpeed();
    engine_consumption = CalcEngineConsumption();
    refills = 0;
    travel_time = 0;
}

double Transport::CalcSpeed() {
    return power_engine * 0.5 / count_wheels;
}

double Transport::CalcEngineConsumption() {
    return power_engine * 0.5;
}

void Transport::CalcTravelTime(double distance) {
    travel_time = distance / CalcSpeed();
}

double Transport::GetTravelTime()
{
    return travel_time;
}

void Transport::CalcRefills(double distance) {
    refills = (int)floor(distance / (volume_tank
    * CalcEngineConsumption()));
}

double Transport::GetRefills() {
    return refills;
}

void Transport::PrintRefillsAndTravelTime() {
    cout << name << "\t\t" << refills << "\t\t" << travel_time << endl;
}

void Transport::PrintData() {
    cout << name << endl;
    cout << "Count wheels: " << count_wheels << endl
    << "Power engine: " << power_engine << endl
    << "Speed: " << speed << endl
    << "Engine consumption: " << engine_consumption << endl << endl;
}




int Menu(); //Делаем меню
Transport* AddTransport(Transport* vehicle, int amount); //Создаем и перезаписываем массив транспортов
void SetData(Transport* transport, int quantity);  // Добавляем данные с консоли для нашего транспорта
void Check(bool checker, double value); // Делаем проверку на отрицательность при вводе
int StringReaderForInt(string value); //Конвертируем строку в целое число
void Sort(Transport* vehicle, int amount); // Сортируем для 5 пункта меню

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
    cin >> str;
    int count_wheels_for_constr = StringReaderForInt(str);
    Check(checker, count_wheels_for_constr);
    cout << endl;

    // Пробег
    cout << "Input the mileage :"; //пробег;
    double mileage_for_constr = 0;
    cin >> mileage_for_constr;
    Check(checker, count_wheels_for_constr);
    cout << endl;

    // Объём бака
    cout << "Input the volume of the tank :";  //объем бака;
    double volume_tank_for_constr = 0;
    cin >> volume_tank_for_constr;
    Check(checker, volume_tank_for_constr);
    cout << endl;

    cout << "Input the power of the engine :";   //мощность двигателя;
    double power_engine_for_constr = 0;
    cin >> power_engine_for_constr;
    Check(checker, power_engine_for_constr);
    cout << endl;

    cout << "Input the name of transport :";  //название.
    string name_for_constr;
    cin >> name_for_constr;

    //Конструктор нашего транспорта
    transport[quantity] = Transport(count_wheels_for_constr, mileage_for_constr, volume_tank_for_constr, power_engine_for_constr, name_for_constr);
    cout << endl << "Transport added!" << endl;
}

// Делаем проверку на отрицательность при вводе
void Check(bool checker, double value) {
    if (value <= 0) checker = false;
    while (!checker){
        cout << "Incorrect, try again! Value must be greater than 0!";
        cin >> value;
        if (value > 0) checker = true;
    }
    cout << endl;
}
void Check(bool checker, int value) {
    if (value < 1) checker = false;
    while (!checker) {
        cout << "Incorrect, try again! Mileage must be greater than 0!";
        cin >> value;
        if (value > 0) checker = true;
    }
    cout << endl;
}

//Конвертируем строку в целое число
int StringReaderForInt(string value)
{
    int choice = 0;
    for (int i = 0; i < value.length(); i++)
    {
        if ((int(value[i]) > 47) && (int(value[i]) < 58))
        {
            choice += int(value[i])-48;
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
