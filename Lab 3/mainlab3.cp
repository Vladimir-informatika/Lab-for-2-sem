#include "cmath"
#include <iostream>
#include <limits>
#include <string>
using namespace std;
int qty = 0; //изначальный размер массива
double InputProve(double var);
int InputProve(int var);
class wheel{
  double current_mileage;
public:
  int status;//повреждено/неповреждено 1/0
  int check_status();// Вроде норм
  wheel(){status=0;current_mileage=0;};
  double def_wheel(double mileage)
 {
   current_mileage=mileage;
   status=check_status();
   return current_mileage;
 }
 virtual void  output();
};
class engine
{
protected:
  double engPow; //мощность двигателя HP horsepower
public:
  double engIntake; //потребление двигателя литров/км l/km
 inline double calculateIntake() {return fabs(pow(engPow, 1 / 3) + sqrt(engPow) - 6.25);}
 engine(){engIntake=0;engPow=0;};
 void def_engine(double power);
 virtual void output();
};
class fuel_system
{
public:
  double TankCapacity; //обЪём бака литры l
  double current_fuel; //текущий обЪём топлива литры l;
  double calculate_cur_fuel(double engIntake,double mileage,double NRefuel);
  fuel_system(){TankCapacity=0;current_fuel=0;};
  void def_fuel_system(double capacity, double engIntake,double mileage );
 virtual void output();
};
class vehicle : public engine, public fuel_system {
private:
  int Nwheels;
public:
  double speed;        //скорость км/ч km/h
  wheel* ptr_wheel;
  int damaged_wheels=0;
  double mileage; //пробег km
  string name;
  double Time; //время пути hour
  double NRefuel; //количесвто дозаправок
  double calculateSpeed();
  vehicle() {
    name="ADDVEHICLE";
    Time=mileage=NRefuel=0;
    ptr_wheel=0;
  }
  vehicle(string vehicle_name,int wheels) 
  {
    mileage = 0;
    cout << "\nName of the car: ";
    cin >> vehicle_name;
    setName(vehicle_name);
    cout << "Number of wheels: ";
    wheels = InputProve(wheels);
    while ((wheels < 2) || (wheels == 5) || (wheels == 7)) {
      cout << "Uncorrect number of wheels! try again:" << endl;
      cin >> wheels;
    }
    setNwheels(wheels);
    ptr_wheel = new wheel[wheels];
    for (int i = 0; i < wheels; i++) {
        ptr_wheel[i] = wheel();
    }
    def_fuel_system(0, engIntake,mileage);
    def_engine(0);
    speed = calculateSpeed();
  }
  void setName(string vehicle_name) {name = vehicle_name;}
  void setNwheels(int wheels){Nwheels = wheels;}
  ~vehicle() { cout << "Destruction of " << name << endl;} 
  inline double calculateRaceTime(double raceLength) {
    return (raceLength / speed);
  };
  double calculateRefuel(double raceLength);
  void time_display();
  int getNwheels() { return Nwheels; } 
  int number_of_damaged_wheels();
  void output();

friend ostream& operator<<(ostream& stream, const vehicle& obj) {
    return stream << "Number of wheels: " << obj.Nwheels << ";\n"
    << "Damaged wheels: " << obj.damaged_wheels << ";\n"
    << "Speed: " << obj.speed << " km/h;\n"
    << "Mileage: " << obj.mileage << " km;\n"
    <<"fuel capacity: "<<obj.TankCapacity<<"l;\n"
    <<"current fuel: "<<obj.current_fuel<<"l\n"
    <<"engine power: "<<obj.engPow<<" HP;\n"
    <<"engine intake: "<<obj.engIntake<<" l/100km;"<<endl;
    
    
}
};
int menu(int &flag);
void clean(int var = 1);
void create_vehicle(vehicle *&adres, int &qty, vehicle cars);
vehicle *RatingResults(vehicle *&adres, int qty);
void outputResults(vehicle *&adres, int qty);
/////////////////////////////////MAIN/////////////////////////
int main() {
  clean();
  vehicle *adres = nullptr;
  double trackLen = 0;
  int flag = 1;
  int rez = 0;
  while (flag == 1) {
    int choice = 10;
    choice = menu(rez);
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
      } else {
        clean();
      }
      break;
    }
      delete[] adres;
      for (int i = 0; i < qty; i++) {
          delete[] adres[i].ptr_wheel;
      }
      break;
    case (1): {
      clean();
      string vehicle_name = "";
      int Nwheels = 0;
      vehicle cars(vehicle_name, Nwheels);
      clean();
      create_vehicle(adres, qty, cars);
      rez = 0;
      break;
    }
    case (2): {
      clean();
      for (int i = 0; i < qty; i++) {
        cout << adres[i].name << endl;
        adres[i].output();
        cout<<"__OR__"<<endl;
        cout<<adres[i];
      }
      break;
    }
    case (3): {
      clean();
      cout << "Enter the length of the track (km): ";
      trackLen = InputProve(trackLen);
      rez = 0;
      break;
    }
    case (4): {
      clean();
      if (trackLen == 0) {
        cout << "You haven't entered the length of the track!\n";
        rez = 0;
        break;
      } else {
        for (int i = 0; i < qty; i++) {
          adres[i].Time = adres[i].calculateRaceTime(trackLen);
          adres[i].mileage = trackLen;
          for (int j = 0; j < adres[i].getNwheels(); j++)
            {
              adres[i].ptr_wheel[j].def_wheel(trackLen);
            }
          adres[i].damaged_wheels = adres[i].number_of_damaged_wheels();
          adres[i].NRefuel = adres[i].calculateRefuel(trackLen);
          adres[i].current_fuel = adres[i].calculate_cur_fuel(adres[i].engIntake, trackLen,adres[i].NRefuel);
          adres[i].speed = adres[i].calculateSpeed();
        }
      }
      break;
    }
    case (5): {
      clean();
      outputResults(*&adres, qty);
      break;
    }
    default:
      clean();
      break;
    }
  }

  return 0;
}

void clean(int var) {
  for (int i = 0; i < 3; i = i + 1) {
    cout << "\n";
  }
}
int menu(int &rez) {
  cout << "\nInter a number to choose action:\n";
  cout << "0 for exit\n";
  cout << "1 for adding Vehicle\n";
  cout << "2 for output information about Vehicle\n";
  cout << "3 to enter length of the track\n";
  cout << "4 for route calculation\n"; //расчет прохождения трассы
  if (rez == 1)
    cout << "5 for results of last race\n";
  int choice = 0;
  choice = InputProve(choice);
  if (choice == 4) {
    rez = 1;
  }
  return choice;
}
void create_vehicle(vehicle *&adres, int &qty, vehicle cars) {
  vehicle *tempArray;
  if (adres != nullptr) {
    tempArray = new vehicle[qty + 1];
    for (int i = 0; i < qty; i++) {
      tempArray[i] = adres[i];
    }
    delete[] adres;
  } else {
    tempArray = new vehicle[1];
  }
  tempArray[qty] = cars;
  adres = tempArray;
  qty++;
}

vehicle *RatingResults(vehicle *&adres, int qty) {
  vehicle *results = new vehicle[qty];
  vehicle *rez_copy = new vehicle[1];
  for (int i = 0; i < qty; i++) {
    results[i] = adres[i];
  }
  for (int i = 0; i < qty; i++) {
    for (int j = 0; j < qty; j++) {
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
void outputResults(vehicle *&adres, int qty) {
  vehicle *results = RatingResults(adres, qty);
  for (int i = 0; i < qty; i++) {
    cout << results[i].name << endl;
    results[i].time_display();
    cout << "Refuel times: " << int(ceil(results[i].NRefuel)) << endl;
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

int wheel::check_status()
{
    //cout << "CHECKING STATUS OF WHEELS..." << endl;
    if (current_mileage > 100) {
        int damageProb = rand() % 100 + 1; // Генерируем вероятность повреждения
        if (current_mileage <= 500) {
            if (damageProb > 70) {
                return 1;
            }}
         else if (current_mileage <= 1000) {
            if (damageProb > 50) {
                return 1;
            }}
         else {
            if (damageProb > 30) {
                return 1;
            }
        }
    }
    return 0;
  }
void wheel :: output()
{
  if (status==1)
  {
    cout<<"damaged"<<endl;
  }
  else{cout<< "not damaged"<<endl;}
}
void engine :: output()
{
  cout<<"engine power: "<<engPow<<" HP;"<<endl;
  cout<<"engine intake: "<<engIntake<<" l/100km;"<<endl;
}

void engine::def_engine(double power)
 {
   cout<<"Engine power in HP: ";
   power=InputProve(power);
   engPow=power;
   engIntake=calculateIntake();
 }
double fuel_system :: calculate_cur_fuel(double engIntake,double mileage,double NRefuel) {//расчёт текущего обЪёма топлива
  if (NRefuel==0)
  {
    return double (TankCapacity - ((engIntake/100) * mileage));
  }
  else 
  {
    return (((NRefuel)*TankCapacity) - ((engIntake/100) * mileage));
  }
}
void fuel_system :: def_fuel_system(double capacity, double engIntake,double mileage )
   {
     cout<<"fuel capacity: ";
     capacity=InputProve(capacity);
     TankCapacity=capacity;
     current_fuel=capacity;
   }
void fuel_system :: output()
{
  cout<<"fuel capacity: "<<TankCapacity<<"l"<<endl;
  cout<<"current fuel: "<<current_fuel<<"l"<<endl;
}

void vehicle::output() {
  cout << "Number of wheels: " << Nwheels << ";\n"
        <<"Damaged wheels: "<<damaged_wheels<<";\n"
       << "speed: " << speed << " km/h;\n"
       << "mileage: " << mileage << " km;" << endl;
  engine::output();
  fuel_system::output();
}
    
void vehicle ::time_display() {
  double t = this->Time;
  int hours = static_cast<int>(t);
  double cur_time = (t - hours) * 60;
  int minutes = static_cast<int>((cur_time));
  int seconds = static_cast<int>((cur_time - minutes) * 60);
  cout << "TIME: " << hours << ":" << minutes << ":" << seconds << endl;
}

double vehicle :: calculateSpeed()
{
 if (damaged_wheels==0){
  return double(fabs(sqrt(engPow) * (70.0 / double(Nwheels) - 2.5) * (current_fuel / 100.0)));
 }
 else
 {
   return (fabs(sqrt(engPow) * (70.0 / double(Nwheels) - 2.5) * (current_fuel / 100.0))/(2*double(damaged_wheels)));
 }
}

int vehicle :: number_of_damaged_wheels()
{
  int count=0;
  for (int i = 0; i < Nwheels; i++)
    {
      if (ptr_wheel[i].status==1)
      {count++;}
    }
  return count;
}

double vehicle :: calculateRefuel(double raceLength)
  {
    double NRefuel=(raceLength * (engIntake / 100))/TankCapacity;
    if(NRefuel>1)
      return ceil(NRefuel);
    else
      return floor(NRefuel);
}