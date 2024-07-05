#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <random>


// Виртуальные деструкторы
// обработка исключений когда переполнение идет
// подумать как время реализовать--------------------------------- проверить
// итерации цикла ежесекундно тоже подумать
// схождение с трассы реализовать
//перегрузить операторы только какие подумать
// переделать рассчет трассы, и потом уже схождение писать, а не как я - решил сразу сошедшие отбросить



template<typename Input>
Input InputValue(Input var) {
    std::cin >> var;
    if (std::cin.fail() || var <= 0)
    {
        while (!(std::cin >> var) || var <= 0)
        {
            std::cout << "Incorrect, try again!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize> :: max(), '\n');
        }
    }
    return var;
}

template<typename Type>
Type max(Type a, Type b) {
    return (a >= b ? a : b);
}



int Probability();


class Wheel;
class Fuel_System;
class Engine;
class Transports;

using vektor = std::vector<Transports>;


class Wheel {
private:
    double current_mileage;
    bool status;
public:
    Wheel();
    bool CheckStatus();
    void DefWheel(double mileage, double speed);
    bool GetStatus();
    virtual void Output();
    virtual ~Wheel();
};

Wheel::Wheel() {
    current_mileage = 0;
    status = true;
}
bool Wheel::CheckStatus(){
    const int probability = Probability();
    if (current_mileage >= 60000) return false;
    else if (current_mileage >= 45000 && current_mileage < 60000) {
        if (probability <= 75) {
            return false;
        }
        else return true;
    }

    else if (current_mileage >= 30000 && current_mileage < 45000) {
        if (probability <= 50) {
            return false;
        }
        else return true;
    }
    else if (current_mileage >= 15000 && current_mileage < 30000) {
        if (probability <= 25) {
            return false;
        }
        else return true;
    }
    else if (current_mileage > 5000 && current_mileage < 15000) {
        if (probability < 10) {
            return false;
        }
        else return true;
    }
    else return true;
}

void Wheel::DefWheel(double mileage, double speed) {
    current_mileage += mileage;
    if (status) status = CheckStatus();
}

bool Wheel::GetStatus() {
    return status;
}
void Wheel::Output() {
    if (!status){
        std::cout << "Damaged" << std::endl;
    }
    else{
        std::cout << "Not damaged" << std::endl;
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
    virtual ~Engine();
};

Engine::Engine() {
    power = consumption = 0;
}

void Engine::DefEngine(double powerEn) {
    std::cout << "Engine power in HP: ";
    powerEn = InputValue<double>(powerEn);
    power = powerEn;
    consumption = Calculate_Consumption();
}

void Engine::Output() {
    std::cout << "Power of engine: " << power << " HP" << std::endl;
    std::cout << "Consumption of engine: " << consumption << " l/100 km" << std::endl;
}

double Engine::Calculate_Consumption() {
    return fabs(pow(power, 1/3) + sqrt(power) - 6.25);
}




class Fuel_System
{
protected:
    double volume_tank;
    double current_fuel;
public:
    Fuel_System();
    void CalculateCurrentFuel(double power, int distance, double refills);
    void DefFuelSystem(double capacity, double mileage);
    virtual void Output();
    virtual ~Fuel_System();
};

Fuel_System::Fuel_System() {
    volume_tank = current_fuel = 0;
}

void Fuel_System::CalculateCurrentFuel(double consumption, int distance, double refills = 0) {
    if (refills == 0) {
        current_fuel = volume_tank - distance * ( consumption /100 );
    }
    else {
        current_fuel = (distance * (consumption / 100)) - (refills * volume_tank);
    }
}

void Fuel_System::DefFuelSystem(double capacity, double mileage) {
    std::cout << "Input Volume Tank in l:";
    capacity = InputValue<double>(capacity);
    volume_tank = capacity;
    current_fuel = capacity;
}

void Fuel_System::Output() {
    std::cout << "Fuel capacity: " << volume_tank << " l" << std::endl;
    std::cout << "Current fuel: " << current_fuel << " l" << std::endl
    << "-----------------------------" << std::endl;
}


// 1 колесо за 0,5 сек, заливаем бак со скоростью литр/секунда. дозаправка при условии если полбака ушло

class Transports : public Engine, public Fuel_System
{
private:
    int count_wheels;
    double speed;
    double time;
    int damaged_wheels = 0;
    double mileage;
    int refills;
public:
    std::vector<Wheel> wheel_vector;
    std::vector<double> pit_stop_time;
    std::string name;
    Transports();
    Transports(const std::string &name_Transports, int wheels);
    void CalculateSpeed();
    void SetName(const std::string &name_Transports);
    void SetWheels(int countWheels);
    void SetMileage(double distance);
    double GetTime();
    double GetRefills();
    double GetSpeed();
    double GetConsumption();
    void CalculateRefills(double distance);
    void TimeDisplay();
    int GetWheels();
    void NumberOfDamagedWheels();
    int GetDamagedWheels();
    inline void CalculateRaceTime(double distance, double pit_stop);
    void Output() override;
    friend vektor RacingResults(vektor &transp);
    friend void OutputResult(vektor &transp);

    double GetVolumeTank();
    double GetCurrentFuel();
    bool CanEndLap(double route);

    friend void GameCycle(const vektor &race);

    friend std::ostream& operator << (std::ostream &os, const Transports &obj);
    ~Transports();
};


std::ostream& operator << (std::ostream &os, const Transports &obj) {
    return os <<"\n"<<"Name: "<<obj.name<<"\n"
                  << "Number of wheels: " << obj.count_wheels << ";\n"
                  << "Damaged wheels: " << obj.damaged_wheels << ";\n"
                  << "Speed: " << obj.speed << " km/h;\n"
                  << "Mileage: " << obj.mileage << " km;\n"
                  << "fuel capacity: " << obj.volume_tank << " l;\n"
                  << "current fuel: " << obj.current_fuel << " l\n"
                  << "engine power: " << obj.power << " HP;\n"
                  << "engine intake: " << obj.consumption << " l/100km;" << std::endl;
}
Transports::Transports() {
    name = "AddTransports";
    count_wheels = speed = time = mileage = refills = damaged_wheels = 0;
}
Transports::Transports(const std::string &name_Transports, int wheels) {
    mileage = damaged_wheels = 0;
    name = name_Transports;
    count_wheels = wheels;
    for (size_t i = 0; i != wheels; i++) wheel_vector[i] = Wheel();
    DefFuelSystem(0, mileage);
    DefEngine(0);
    CalculateSpeed();
}
void Transports::CalculateSpeed() {
    if (damaged_wheels == 0) speed = double(fabs( sqrt(power) * (70.0 / double(count_wheels) - 2.5)));
    else speed = fabs( sqrt(power) * (70.0 / double(count_wheels) - 2.5)) / (pow(2, double(damaged_wheels)));
}
void Transports::CalculateRefills(double distance) {
    refills = floor((distance * (consumption / 100)) / volume_tank);
}
void Transports::TimeDisplay()
{
    int hours = (int) time;
    double tim = (time - hours) * 60;
    int minutes = (int)tim;
    int seconds = int((tim - minutes) * 60);

    if (hours < 24)
    {
        std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
    }
    else
    {
        int days = (int) time/24;
        hours = int(time  - days*24);
        std::cout << days << " days " << hours << " hours " << minutes << " minutes " << seconds << " seconds" << std::endl;
    }
}
int Transports::GetWheels() {
    return count_wheels;
}
void Transports::NumberOfDamagedWheels() {
    int count = 0;
    for (size_t i = 0; i != count_wheels; i++) if (!wheel_vector[i].GetStatus()) count++;
    damaged_wheels = count;
}
void Transports::Output() {
    std::cout << name << std::endl
    << "Count wheels: " << count_wheels << std::endl
    << "Damaged wheels: " << damaged_wheels << std::endl
    << "Speed: " << speed << " km/h" << std::endl
    << "Mileage: " << mileage << " km" << std::endl;
    Engine::Output();
    Fuel_System::Output();
}
void Transports::SetName(const std::string &name_Transports) {
    name = name_Transports;
}
void Transports::SetWheels(int countWheels) {
    count_wheels = countWheels;
}
void Transports::SetMileage(double distance) {
    mileage += distance;
}
double Transports::GetTime() {
    return time;
}
double Transports::GetRefills() {
    return refills;
}
double Transports::GetConsumption() {
    return consumption;
}
double Transports::GetSpeed() {
    return speed;
}
Transports::~Transports() {
    std::cout << "Destruct " << name << std::endl;
}
void Transports::CalculateRaceTime(double distance, double pit_stop) {
    time = (distance / speed) + pit_stop;
}
bool Transports::CanEndLap(double route) {
    if (((route * (consumption / 100)) / volume_tank) > 1) return false;
    else return true;
}
double Transports::GetVolumeTank() {
    return volume_tank;
}
double Transports::GetCurrentFuel() {
    return current_fuel;
}
int Transports::GetDamagedWheels() {
    return damaged_wheels;
}
// class MyClass {
// public:
//     int data;
//     MyClass(int a) {
//         data = a;
//     };
// };
///////////////////////////////////////////////////////////////

int Menu();
vektor AddTransport(vektor &transports);
vektor Race(vektor &transports, double route);
void GameCycle();
vektor RacingResults(vektor &transp);




void OutputResult(vektor &transp);


int main() {
    vektor transports;
    double distance = 0;
    double route = 0;
    double pit_stop = 0;
    int rings = 0;
    bool menu = true;
    bool flag = false;

    while (menu) {
        switch(Menu()) {
            case 1:
                AddTransport(transports);
                flag = false;
                break;
            case 2:
                if (transports.empty())
                {
                    std::cout << "Julius Sergeevich, you didn't add any transport. What did you expected to see?" << std::endl;
                }
                else for (size_t i = 0; i != transports.size(); i ++) transports[i].Output();
                break;
            case 3:
                std::cout << "Input length of the lip" << std::endl;
                route = InputValue<double>(route);
                std::cout << "Input count of lips" << std::endl;
                rings = InputValue<int>(rings);
                distance = route * rings;
                std::cout << std::endl;
                flag = false;
                break;
            case 4:
                if (transports.empty() || distance == 0) {
                    std::cout << "Array of transport is empty or distance is null\n";
                }
                else {
                    //////////////////// СДЕЛАТЬ ГЛОБАЛЬНЫЙ ЦИКЛ ТУТ, ЛУЧШЕ КОНЕЧНО В ОТДЕЛЬНЫЙ МЕТОД ЕГО ВЫНЕСТИ
                    flag = true;
                    std::cout << "Calculating...\n";
                }
                break;
            case 5:
                if (!flag) {
                    std::cout << "No-no-no! Firstly calculate THESE routes for each transport! Have you just changed distance and didn't calculate it for each transport?" << std::endl;
                }
                else {
                    OutputResult(transports);
                }
                break;
            case 6:
                std::cout << "Are you sure? (y/n)" << std::endl;
                char quit;
                std::cin >> quit;
                if (quit == 'y' || quit == 'Y')
                {
                    std::cout << "OK, as you wish" << std::endl;
                    transports.resize(0);
                    menu = false;
                }
                break;
            default:
                std::cout << "Hmm, incorrect!!!" << std::endl;
                break;
        }
    }
    // MyClass class1(1);
    // std::cout << classes.size() << std::endl;
    // classes.push_back(class1);
    // std::cout << classes.size() << std::endl;
    // classes.pop_back();
    // std::cout << classes.size() << std::endl;

    return 0;
}

int Menu ()
{
    std::cout << "========================================" << std::endl;
    std::cout << "\tMENU" << std::endl;
    std::cout << "1. Add transport" << std::endl;
    std::cout << "2. Show existing transports" << std::endl;
    std::cout << "3. Enter/change route length" << std::endl;
    std::cout << "4. Calculate routes for each transport" << std::endl;
    std::cout << "5. See the result of completing the route" << std::endl;
    std::cout << "6. Quit the program\n" << std::endl;
    std::cout << "Your choice: " << std::endl;
    int choice = 0;
    choice = InputValue<int>(choice);
    std::cout << '\n';
    return choice;
}
vektor AddTransport(vektor &transports) {
    std::cout << "Input count of wheels: ";// количество колес;
    int count_wheels_for_constr = 0;
    count_wheels_for_constr = InputValue<int>(count_wheels_for_constr);


    std::cout << "Input the name of transport :";  //название.
    std::string name_for_constr;
    std::cin >> name_for_constr;

    //Конструктор нашего транспорта
    Transports Car(name_for_constr, count_wheels_for_constr);
    transports.emplace_back(Car); //сразу добавляем объект в конце, а не копируем его туда
    std::cout << std::endl << "Transport added!" << std::endl;
    return transports;
}

vektor Race(vektor &transports, double route) {
    vektor racing;


    for (size_t i = 0; i != transports.size(); ++i) {
        if (transports[i].CanEndLap(route)) {
            racing.emplace_back(transports[i]);
        }
    }
    ////остальные может просто тут вывести хз
    return racing;
}

int Probability() {
    std::random_device rd;
    std::mt19937 gen(rd());
    return gen() % 100;
}

void GameCycle(const vektor &race) {
    double max_time = 0;
    for (size_t i = 0; i != race.size(); ++i) {
        if (race[i].time - max_time > 0) max_time = race[i].time;
    }
    const double race_time = max_time;

}

void OutputResult(vektor &transp)
{
    vektor results = RacingResults(transp);
    std::cout << "Name\t\t\tRefills\t\t\tTravel time\n";
    for (size_t i = 0; i != transp.size(); ++i) {
        std::cout << results[i].name << "\t\t\t" << results[i].refills << "\t\t\t";
        results[i].TimeDisplay();
    }
}

vektor RacingResults(vektor &transp) {
    vektor result;
    vektor temp;
    Transports Car;
    temp.push_back(Car);
    for (size_t i = 0; i != transp.size(); ++i) {
        result[i] = transp[i];
    }
    for (size_t i = 0; i != transp.size(); ++i) {
        for (size_t j = 0; j < transp.size(); ++j) {
            if ((result[i].GetTime() - result[j].GetTime() < 0) && (result[i].GetRefills() - result[i].GetRefills() <= 0)) {
                temp[0] = result[i];
                result[i] = result[j];
                result[j] = temp[0];
            }
        }
    }
    return result;
}
