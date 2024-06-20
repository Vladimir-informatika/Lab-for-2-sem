#include <iostream>
#include <string>
#include <cmath>
#include <limits>

using namespace std;


class Transport
{
    int count_wheels;
  //  double mileage;
    double volume_tank;
    double power_engine;
    double travel_time;
    string name;
    double speed;
    double engine_consumption;
    long int refills;
public:
    Transport();
    Transport(int countWheels, double volumeTank, double power, string str);

    double CalcEngineConsumption();
    double CalcSpeed();
    void CalcTravelTime(double distance);
    void CalcRefills(double distance);
    void PrintData();
    void PrintRefillsAndTravelTime();
    double GetTravelTime();
    double GetRefills();
    void Time_display();

    ~Transport();
};

Transport::~Transport() {
    cout << "Transport " << name << " deleted!" << endl;
}

Transport::Transport() {
    count_wheels = 0;
  //  mileage = 0;
    volume_tank = 0;
    power_engine = 0;
    name = "";

    speed = 0;
    engine_consumption = 0;
    refills = 0;
    travel_time = 0;
}

Transport::Transport(int countWheels, double volumeTank, double power, string str) {
    count_wheels = countWheels;
   // mileage = mil;
    volume_tank = volumeTank;
    power_engine = power;
    name = str;
    speed = CalcSpeed();
    engine_consumption = CalcEngineConsumption();
    refills = 0;
    travel_time = 0;
    cout << "Transport " << name << " added!" << endl;
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
    refills = (long int)floor(distance / (volume_tank
                                     * CalcEngineConsumption()));
}

double Transport::GetRefills() {
    return refills;
}

void Transport::Time_display()
{
    int hours = (int) travel_time;
    double tim = (travel_time - hours) * 60;
    int minutes = (int)tim;
    int seconds = int(tim - minutes) * 60;

    if (hours < 24)
    {
        cout << hours << ":" << minutes << ":" << seconds << endl;
    }
    else
    {
        int days = (int) travel_time/24;
        hours = int(travel_time  - days*24);
        cout << days << " days " << hours << " hours " << minutes << " minutes " << seconds << " seconds" << endl;
    }
}

void Transport::PrintRefillsAndTravelTime() {
    cout << name << "\t\t\t" << refills << "\t\t\t";
    Time_display();
}

void Transport::PrintData() {
    cout << name << endl;
    cout << "Count wheels: " << count_wheels << endl
         << "Power engine: " << power_engine << " HP" <<  endl
         << "Speed: " << speed << " kph" <<endl
         << "Engine consumption: " << engine_consumption << " l/ 100 km" << endl << endl;
}




int Menu(); //Делаем меню
Transport* AddTransport(Transport* vehicle, int amount); //Создаем и перезаписываем массив транспортов
void SetData(Transport* transport, int     quantity);  // Добавляем данные с консоли для нашего транспорта
double Check(bool checker, double value); // Делаем проверку на отрицательность при вводе
int StringReaderForInt(string value); //Конвертируем строку в целое число
void Sort(Transport* vehicle, int amount); // Сортируем для 5 пункта меню
int InputValue(int var);
double InputValue(double var);


int main()
{
    Transport* transport = nullptr;
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
                flag = false;
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
                distance = Check(checker_for_route, distance);
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
                    cout << "Name\t\t\tRefills\t\t\tTravel time\n";
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
    cout << "Input count of wheels (less than 100! I think it is enough): ";// количество колес;
    int count_wheels_for_constr = InputValue(count_wheels_for_constr);


    // Объём бака
    cout << "Input the volume of the tank (less than 1000) :";  //объем бака;
    double volume_tank_for_constr = InputValue(volume_tank_for_constr);
    bool flag = true;
    if (volume_tank_for_constr >= 1000 || volume_tank_for_constr < 0.01) {
        cout << "THIS IS A MADNESS!! Have you ever seen a car with SOOO volume tank?"
        << endl << "I refuse to accept this, try again" << endl;
        flag = false;
        while (!flag) {
            volume_tank_for_constr = InputValue(volume_tank_for_constr);
            if (volume_tank_for_constr < 1000 && volume_tank_for_constr >= 0.01) flag = true;
            else {
                cout << "You seem to have misunderstood me, let's do it again" << endl;
            }
        }
    }

    cout << "Input the power of the engine(less than 114 800):";   //мощность двигателя;
    double power_engine_for_constr = InputValue(power_engine_for_constr);
    if (power_engine_for_constr >= 114800 || power_engine_for_constr < 0.01) {
        cout << "THIS IS A MADNESS!! Have you ever seen a car with SOOO powerful engine?"
        << endl << "I refuse to accept this, try again" << endl;
        flag = false;
        while (!flag) {
            power_engine_for_constr = InputValue(power_engine_for_constr);
            if (power_engine_for_constr < 114800 && power_engine_for_constr >= 0.01) flag = true;
            else {
                cout << "You seem to have misunderstood me, let's do it again" << endl;
            }
        }
    }

    cout << "Input the name of transport :";  //название.
    string name_for_constr;
    cin >> name_for_constr;

    //Конструктор нашего транспорта
    transport[quantity] = Transport(count_wheels_for_constr, volume_tank_for_constr, power_engine_for_constr, name_for_constr);
    cout << endl << "Transport added!" << endl;
}

// Делаем проверку на отрицательность при вводе
double Check(bool checker, double value) {
    value = InputValue(value);
    if (value < 0.001 || value > 100000) checker = false;
    while (!checker){
        cout << "What are you doing?? Give me adequate route - more than 1 meter and less than 100.000 km (2.5 Earth equators)" << endl;
        value = InputValue(value);
        if (value >= 0.001 && value <= 100000) checker = true;
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
            choice += (int(value[i]) - 48) * pow(10, i) ;
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

int InputValue(int var)
{
    cin >> var;
    if(cin.fail() || var <= 0 || var >= 100)
    {
        cout << "Incorrect, try again!! " << endl;
        while (!(cin >> var) || var <= 0 || var >= 100)
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
        cout << "Incorrect, try again!! " << endl;
        while (!(cin >> var) || var <= 0)
        {
            cout << "Incorrect, try again!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize> :: max(), '\n');
        }
    }
    return var;
}
