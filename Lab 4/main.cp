#include <iostream>
#include "cmath"
#include <limits>
#include <string>
#include <ctime>
#include <vector>
using namespace std;
double Refuel_time=0.03;//примерно 2 минуты
double Change_time=0.017;//примерно 1 минута
double InputProve(double var);
int InputProve(int var);
int menu(int &rez);
void clean(int var = 1);

class wheel {
  double current_mileage;
  int status; //повреждено/неповреждено 1/0
public:
  int check_status(double mileage, double speed); 
  wheel() {status=0;current_mileage=0;};
  double def_wheel(double mileage, double speed) {
    current_mileage += mileage;
    status = check_status(current_mileage,speed);
    return current_mileage;
  }
  virtual void output();
  int get_status() { return status; }
};

class engine {
protected:
  double engPow; //мощность двигателя HP horsepower
  double engIntake; //потребление двигателя литров/км l/km
public:
 inline double calculateIntake() {return fabs(pow(engPow, 1 / 3) + sqrt(engPow) - 6.25);}
 engine(){engIntake=0;engPow=0;};
  void def_engine(double power);
};

class fuel_system {
protected:
  double current_fuel; //текущий обЪём топлива литры l;
public:
  double TankCapacity; //обЪём бака литры l
  void calculate_cur_fuel(double engIntake, double mileage, double NRefuel);
  fuel_system(){TankCapacity=0;current_fuel=0;};
  void def_fuel_system(double capacity, double engIntake, double mileage);
};

class vehicle : public engine, public fuel_system {
private:
  int Nwheels;
  double speed; //скорость км/ч km/h
  double Time;    //время пути hour
  int damaged_wheels = 0;
  double mileage; //пробег km
  double NRefuel; //количесвто дозаправок
public:
  wheel *ptr_wheel;
  string name;
  vehicle() {
    name = "ADDVEHICLE";
    Time = mileage = NRefuel = damaged_wheels = 0;
    ptr_wheel = 0;
  }
  vehicle(string vehicle_name, int wheels) {
    mileage =damaged_wheels = 0; 
    name=vehicle_name;
    Nwheels=wheels;
    ptr_wheel = new wheel[wheels];
    for (int i = 0; i < wheels; i++) {
      ptr_wheel[i] = wheel();
    }
    def_fuel_system(0, engIntake, mileage);
    def_engine(0);
    calculateSpeed();
  }
  void calculateSpeed();
  void setMileage(double tracklen) { mileage=tracklen; }
  ~vehicle() { cout << "Destruction of " << name << endl; }
  inline void calculateRaceTime(double raceLength) {
    Time = (raceLength / speed);
  };
  double get_mileage(){return mileage;};
  double get_Time(){return Time;};
  double get_NRefuel(){return NRefuel;};
  double get_speed(){return speed;};
  int get_damaged_wheels(){return damaged_wheels;};
  void calculateRefuel(double raceLength);
  int need_refuel(double tracklen);
  void time_display();
  int getNwheels() { return Nwheels; }
  double get_current_fuel() { return current_fuel; }
  void number_of_damaged_wheels();
  void output();
  friend vehicle *RatingResults(int qty);
  friend void outputResults(vector <vehicle> car,int qty);

  friend ostream &operator<<(ostream &stream, const vehicle &obj) {
    return stream <<"Name: "<<obj.name<<"\n"
      << "Number of wheels: " << obj.Nwheels << ";\n"
                  << "Damaged wheels: " << obj.damaged_wheels << ";\n"
                  << "Speed: " << obj.speed << " km/h;\n"
                  << "Mileage: " << obj.mileage << " km;\n"
                  << "fuel capacity: " << obj.TankCapacity << "l;\n"
                  << "current fuel: " << obj.current_fuel << "l\n"
                  << "engine power: " << obj.engPow << " HP;\n"
                  << "engine intake: " << obj.engIntake << " l/100km;" << endl;
  }

vehicle& operator=(const vehicle& other) {
  if (this == &other) { 
      return *this;
  }
  name = other.name;
  Nwheels = other.Nwheels;
  speed = other.speed;
  mileage = other.mileage;
  Time=other.Time;
  return *this;
};
};

int allfinished(vector<vehicle> &v);

vector<vehicle>RatingResults(vector<vehicle> v);
void outputResults(vector<vehicle> v);
//void drive(int qty, double tracklen, vector<vehicle> &v);
//////////////////////////////////////////////////////////
int main() {
  vector<vehicle> race_rez;
  vector<vehicle> cars;
  int NumCircles;
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
      for (int i = 0; i < cars.size(); i++) {
        delete[] cars[i].ptr_wheel;
      }
      break;
    case (1): {
      clean();
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
      vehicle addcar(vehicle_name, Nwheels);
      cars.push_back(addcar);
      clean();
      rez = 0;
      break;
    }
    case (2): {
      clean();
      for (int i = 0; i < cars.size(); i++) {
        cout << cars[i];
      }
      break;
    }
    case (3): {
      clean();
      cout<<"The number of circles: ";
      NumCircles=InputProve(NumCircles);
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
      } 
      else 
      {
         double current_time=0;
         double current_mileage=0;
         double dt=0.0003;//примерно 1 секунда
         /*int *skip_id[cars.size()];*/
         for(current_time=0;allfinished(cars)!=1;current_time+=dt)
            {
              for (int i = 0; i < cars.size(); i++) {
                /*if (*skip_id[i] == 1) {
                  continue;
                }*/
                current_mileage+=(cars[i].get_speed()*current_time);
                  cars[i].setMileage(current_mileage);
                for (int j = 0; j < cars[i].getNwheels(); j++) {
            cars[i].ptr_wheel[j].def_wheel(trackLen,cars[i].get_speed());
                }
                  cars[i].number_of_damaged_wheels();
cars[i].calculate_cur_fuel(cars[i].calculateIntake(),current_mileage,cars[i].get_NRefuel());
                  cars[i].calculateSpeed();
                /*if (cars[i].get_current_fuel()<=0 || cars[i].get_damaged_wheels()>0)
                {
                  *skip_id[i]=1;
                }*/
              }
              cout<<"1END"<<endl;
            }
          cout<<"2END"<<endl;
      }
      break;
    }
    case (5): {
      clean();
      outputResults(cars);
      break;
    }
    default:
      clean();
      break;
    }
  }
  
  cout<<"WOW"<<endl;
  
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

vector<vehicle>  RatingResults(vector<vehicle> v) {
  vector<vehicle> results;
  vehicle temp;
  results=v;
  cout<<"REZ"<<results[0]<<endl;
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v.size(); j++) {
      if ((v[i].get_Time() - v[j].get_Time() < 0))
        temp = results[i];
        results[i] = results[j];
        results[j] = temp;
      }
    }
  cout<<temp<<endl;
  return results;
}
void outputResults(vector<vehicle> v) {
  cout<<"Zzzzzz"<<endl;
  vector<vehicle> results = RatingResults(v);
  for (int i = 0; i < v.size(); i++) {
    cout << results[i].name << endl;
    results[i].time_display();
    //cout << "Refuel times: " << int(results[i].NRefuel) << endl;
  }
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

int wheel::check_status(double mileage, double speed) {
  double ratio = (1/(mileage)*sqrt(speed));
  if (ratio>=0.5)
  {
    //cout<< "Wheel is not damaged"<<endl;
    return 0;
  }
  else
  {
    //cout<<"Wheel is damaged"<<endl;
    return 1;
  }
}
void wheel ::output() {
  if (status == 1) {
    cout << "damaged" << endl;
  } else {
    cout << "not damaged" << endl;
  }
}

void engine::def_engine(double power) {
  cout << "Engine power in HP: ";
  power = InputProve(power);
  engPow = power;
  engIntake = calculateIntake();
}

void fuel_system ::calculate_cur_fuel(double engIntake, double mileage,double NRefuel) { //расчёт текущего обЪёма топлива
  if (NRefuel == 0) {
    current_fuel=double(TankCapacity - ((engIntake / 100) * mileage));
  } else {
    current_fuel=(((NRefuel)*TankCapacity) - ((engIntake / 100) * mileage));
  }
}

void fuel_system ::def_fuel_system(double capacity, double engIntake,double mileage) {
  cout << "fuel capacity: ";
  capacity = InputProve(capacity);
  TankCapacity = capacity;
  current_fuel = capacity;
}


void vehicle ::time_display() {
  double t = this->Time;
  int hours = int(t);
  double cur_time = (t - hours) * 60;
  int minutes = int(cur_time);
  int seconds = int((cur_time - minutes) * 60);
  cout << "TIME: " << hours << ":" << minutes << ":" << seconds << endl;
}

void vehicle ::calculateSpeed() {
  if (damaged_wheels == 0) {
speed= double(fabs(sqrt(engPow) * (70.0 / double(Nwheels) - 2.5) * (current_fuel / 100.0)));
 }
 else
 {
   speed = (fabs(sqrt(engPow) * (70.0 / double(Nwheels) - 2.5) * (current_fuel / 100.0))*(pow(20.75, double(damaged_wheels))));
     }
  }


void vehicle ::number_of_damaged_wheels() {
  int count = 0;
  for (int i = 0; i < Nwheels; i++) {
    if (ptr_wheel[i].get_status() == 1) {
      count++;
    }
  }
  damaged_wheels = count;
}

void vehicle ::calculateRefuel(double raceLength) {
  double Refuel = (raceLength * (engIntake / 100)) / TankCapacity;
  if (Refuel > 1)
    this->NRefuel= ceil(Refuel);
  else
    this->NRefuel= floor(Refuel);
}

int vehicle ::need_refuel(double tracklen)
{
  if (current_fuel < (engIntake / 100) * tracklen)
    return 1;
  else return 0;
}

int allfinished(vector<vehicle> &v)
{
  int count=0;
  for (int i=0;i<v.size();i++)
    {
      if (v[i].get_mileage()>=0)
      {
        count++;
      }
    }
  if (count==v.size())
  {
    return 1;
  }
  else return 0;
}

/*void drive(int qty, double tracklen, vector<vehicle> &v)
{
  double current_time=0;
  double current_mileage=0;
  double dt=0.0003;//примерно 1 секунда
  int *skip_id=nullptr;
  for(current_time=0;allfinished(v)==0;current_time+=dt)
    {
      for (int i = 0; i < v.size(); i++) {
        if (skip_id[i] == 1) {
          continue;
        }
        current_mileage+=(v[i].get_speed()*current_time);
        v[i].setMileage(current_mileage);
        for (int j = 0; j < v[i].getNwheels(); j++) {
  v[i].ptr_wheel[j].def_wheel(tracklen,v[i].get_speed());
        }
        v[i].number_of_damaged_wheels();
v[i].calculate_cur_fuel(v[i].calculateIntake(),current_mileage,v[i].get_NRefuel());
        v[i].calculateSpeed();
        if (v[i].get_current_fuel()<=0 || v[i].get_damaged_wheels()>0)
        {
          skip_id[i]=1;
        }
      }
    }
  cout<<"END"<<endl;
}*/