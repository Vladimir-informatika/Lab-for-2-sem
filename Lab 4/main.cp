#include <iostream>
#include "cmath"
#include <limits>
#include <string>
#include <ctime>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>
using namespace std;
double Refuel_time=0.0003;//примерно 1 секунда
double Change_time=0.008;//примерно 30 секунд
double dt=0.0003;
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
  virtual ~wheel(){};//требуется для корректной работы компилятора 
  void def_wheel(double mileage, double speed);
  void output();
  int get_status() { return status; }
  void set_status(int status) {
    this->status = status;
  }
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
  void calculate_cur_fuel(double engIntake, double mileage);
  fuel_system(){TankCapacity=0;current_fuel=0;};
  void def_fuel_system();
};

class vehicle : public engine, public fuel_system {
private:
  int Nwheels;
  double speed; //скорость км/ч km/h
  double Time;    //время пути hour
  int damaged_wheels;
  double NRefuel; //количесвто дозаправок
  double mileage; //пробег km
  double current_mileage;//текущее положение на круге km
  int current_circles;
public:
  vector<wheel> vec_wheels;
  string name;
  double pit_stop_time;
  vehicle() {
    name = "ADDVEHICLE";
    Time = current_mileage=mileage = NRefuel = pit_stop_time = 0;
    damaged_wheels=current_circles=0;
  }
  vehicle(string vehicle_name, int wheels) {
    current_mileage=mileage=pit_stop_time=0;
    damaged_wheels=current_circles=0; 
    name=vehicle_name;
    Nwheels=wheels;
    for (int i = 0; i < wheels; i++) {
      wheel newWheel;
      vec_wheels.push_back(newWheel);
    }
    def_fuel_system();
    def_engine(0);
    calculateSpeed();
  }
  
  void calculateSpeed();
  void setMileage(double tracklen) { mileage=tracklen; }
  ~vehicle() { cout << "Destruction of " << name << endl; }
  inline void calculateRaceTime(double raceLength) {
    Time = (raceLength / speed);}
   void reset();

  void total_time()
  {
    Time=Time+pit_stop_time;
  }

  int calc_circles(double trackLen)
  {
    if (current_mileage-trackLen>=0)
    {
      current_circles=int(mileage/trackLen);
      current_mileage=0;
      return 1;
    }
    else {return 0;}
  }  

  double wheels_change()
  {
    double time=damaged_wheels*Change_time;
    return time;
  }

  double refuel_time()
  {
    double time=((TankCapacity-current_fuel)*Refuel_time);
    return time;
  } 

  double get_Time(){return Time;};
  void set_Time(double Time){this->Time=Time;};
  double get_NRefuel(){return NRefuel;};
  void plus_NRefuel(){NRefuel++;}
  double get_speed(){return speed;};
  int get_damaged_wheels(){return damaged_wheels;};
  double get_mileage(){return mileage;};
  void set_mileage(double len){this->mileage=len;};
  void mileage_plus(){this->mileage+=(speed*dt);};
  double get_current_mileage(){return current_mileage;};
  void set_current_mileage(double len){this->current_mileage=len;};
  void current_mileage_plus(){this->current_mileage+=(speed*dt);};
  int get_current_circles(){return current_circles;};
  void set_current_circles(int circles){this->current_circles=circles;};
  void calculateRefuel(double raceLength,int circles);
  void need_refuel(double tracklen);
  void need_change();
  void time_display();
  int getNwheels() { return Nwheels; }
  double get_current_fuel() { return current_fuel; }
  void number_of_damaged_wheels();
  void output();
  friend vehicle *RatingResults(int qty);
  friend void outputResults(vector <vehicle> car,int qty);

  friend ostream &operator<<(ostream &stream, const vehicle &obj) {
    return stream <<"\n"<<"Name: "<<obj.name<<"\n"
      << "Number of wheels: " << obj.Nwheels << ";\n"
                  << "Damaged wheels: " << obj.damaged_wheels << ";\n"
                  << "Speed: " << obj.speed << " km/h;\n"
                  << "Mileage: " << obj.mileage << " km;\n"
                  << "fuel capacity: " << obj.TankCapacity << " l;\n"
                  << "current fuel: " << obj.current_fuel << " l\n"
                  << "engine power: " << obj.engPow << " HP;\n"
                  << "engine intake: " << obj.engIntake << " l/100km;" << endl;
  }

  friend istream &operator >> (istream &stream,vehicle& obj)
    {
      cout<<"Vehicle name: ";
      stream>>obj.name;
      try
        {
          cout<<"Number of wheels: ";
          stream>>obj.Nwheels;
          if (obj.Nwheels < 2){
              throw "Uncorrect number of wheels! try again";
        }
        }    
        catch (const char* msg) {
          cerr << "Exception caught: " << msg <<endl;
          obj.Nwheels=InputProve(obj.Nwheels);
        }
        for (int i = 0; i < obj.Nwheels; i++) {
          wheel newWheel;
          obj.vec_wheels.push_back(newWheel);
          }
        try
          {
            cout<<"Tank capacity: ";
            stream>>obj.TankCapacity;
            if (obj.TankCapacity<=0){
              throw "Uncorrect tank capacity! try again";
            }
          }
          catch (const char* msg)
          {
            cerr << "Exception caught: " << msg <<endl;
            obj.TankCapacity=InputProve(obj.TankCapacity);
          }
        try
          {
            cout<<"Engine power: ";
            stream>>obj.engPow;
            if (obj.engPow<=0){
              throw "Uncorrect power of engine! try again";
            }
          }
          catch (const char* msg)
          {
            cerr << "Exception caught: " << msg <<endl;
            obj.engPow=InputProve(obj.engPow);
          }
          obj.current_fuel=obj.TankCapacity;
          obj.def_engine(obj.engPow);
          obj.calculateSpeed();
      return stream;
    }

vehicle& operator=(const vehicle& other) {
  name = other.name;
  Nwheels = other.Nwheels;
  speed = other.speed;
  mileage = other.mileage;
  current_mileage=other.current_mileage;
  current_circles=other.current_circles;
  Time=other.Time;
  return *this;
}
};

int allfinished(vector<vehicle> &v,double trackLen,int circles);
int skip(vector<int> skip_id, int i);

vector<vehicle>RatingResults(vector<vehicle> v);
void outputResults(vector<vehicle> v);
//////////////////////////////////////////////////////////
int main() {
  srand(time(NULL));
  vector<vehicle> race_rez;
  vector<vehicle> cars;
  int NumCircles;
  double trackLen = 0;
  int flag = 1;
  int rez = 0;
  while (flag == 1) {
    int choice = 10;
    try
      {
      choice = menu(rez);
      if ((choice > 5) || (choice < 0)) {
        throw "Error, try another number!";
        }
      }
    catch (const char* msg)
      {
        cerr << "Exception caught: " << msg << endl;
        cout<<"try again ";
        choice = InputProve(choice);
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
      break;
    case (1): {
      clean();
      /*string vehicle_name = "";
      cout << "\nName of the car: ";
      cin >> vehicle_name;
      int Nwheels = 0;
      cout << "Number of wheels: ";
      Nwheels = InputProve(Nwheels);
      while ((Nwheels < 2) || (Nwheels == 5) || (Nwheels == 7)) {
        cout << "Uncorrect number of wheels! try again:" << endl;
        Nwheels = InputProve(Nwheels);
      }
      vehicle addcar(vehicle_name, Nwheels);*/
      vehicle addcar;
      cin>>addcar;
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
      try{
        cout<<"The number of circles: ";
        NumCircles=InputProve(NumCircles);
        if (NumCircles<=0){
          throw "Uncorrect number of circles! try again";
        }
      }
      catch (const char* msg)
        {
          cerr << "Exception caught: " << msg << endl;
          cout<<"try again ";
          NumCircles=InputProve(NumCircles);
        }
      cout << "Enter the length of the track (km): ";
      trackLen = InputProve(trackLen);
      rez = 0;
      break;
    }
    case (4): {
      clean();
      if (trackLen == 0 || NumCircles==0) {
        cout << "You haven't entered the length of the track!\n";
        rez = 0;
        break;
      } 
      else 
      {
        for(int i=0;i<cars.size();i++)
          {
            cars[i].reset();
          }
        double current_time=0;
        vector<int> skip_id{-1};
        int racing_cars=cars.size();
        while(!allfinished(cars,trackLen,NumCircles))
          {
            if(racing_cars<=0)
              {
                break;//не работает если переместить это условие в while
              }
            for (int i = 0; i <cars.size(); i++)
              {
                int exit=0;
                if (find(skip_id.begin(), skip_id.end(), i) == skip_id.end()) 
                {
                  cars[i].mileage_plus();
                  cars[i].current_mileage_plus();
                  for (int j = 0; j < cars[i].vec_wheels.size(); j++)
                  {
                    cars[i].vec_wheels[j].def_wheel(cars[i].get_mileage(),cars[i].get_speed());
                  }
                  cars[i].number_of_damaged_wheels();
                  cars[i].calculate_cur_fuel(cars[i].calculateIntake(),cars[i].get_current_mileage());
                  cars[i].calculateSpeed();
                  cars[i].set_Time(current_time);
                  cars[i].time_display();
                  cout<<"car: "<<cars[i].name
                    <<" circle: "<<cars[i].get_current_circles()+1
                    <<" speed: "<<cars[i].get_speed()<<"\n"
                    <<" Current fuel "<<cars[i].get_current_fuel()
                    <<" Damaged wheels: "<<cars[i].get_damaged_wheels()<<"\n"
                    <<" Mileage: "<<cars[i].get_mileage()<<"\n";
                  if (cars[i].get_damaged_wheels()==cars[i].vec_wheels.size() || (cars[i].get_current_fuel()<=0))
                  {
                      exit=1;
                      cars[i].set_Time(current_time);
                  }
                  if ((trackLen*NumCircles)-(cars[i].get_mileage())<=0) 
                  {
                    exit=1;
                    cars[i].set_Time(current_time);
                    cars[i].set_current_circles(NumCircles);
                  }
                  if (exit==1)
                    {
                      skip_id.push_back(i); // ТС будет пропускаться, так как финишировала
                      racing_cars=racing_cars-1;
                      break;
                    }
                  if (cars[i].calc_circles(trackLen))
                    {
                      cars[i].need_refuel(trackLen);
                      cars[i].need_change();
                    }
                }
                else
                { 
                  continue; // Пропускаем итерацию
                }             
              }
            current_time+=dt;
          }
        for(int i=0;i<cars.size();i++)
          {
            cars[i].total_time();
          }
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
  cout << "3 to enter the track\n";
  cout << "4 to start the race\n"; //расчет прохождения трассы
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
    sort(v.begin(), v.end(), []( vehicle& a,  vehicle& b) {
    if (a.get_Time() != b.get_Time()) {
      return a.get_Time() < b.get_Time();
    } 
    else {
      return a.get_NRefuel() < b.get_NRefuel(); 
    }
  });
  return v;
}

void outputResults(vector<vehicle> v) {
  vector<vehicle> results = RatingResults(v);
  for (int i = 0; i < results.size(); i++) {
    cout << results[i].name << endl;
    results[i].time_display();
    cout<<"Circles "<<results[i].get_current_circles()<<endl;
    cout << "Refuel times: " << int(results[i].get_NRefuel()) << endl;
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

void wheel :: def_wheel(double mileage, double speed) {
  if (mileage==0.) {
    current_mileage=0.;
    status=0.;
  }
  else{
    current_mileage = mileage;
    status = check_status(current_mileage,speed);
  }
}

int wheel::check_status(double mileage, double speed) {
  if (status == 0){
  double ratio = 1/(mileage*0.01)*sqrt(speed);
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
  else return 1;
}

/*int wheel::check_status(double mileage, double speed) {
  if (status == 0){ 
  srand(time(0));
  int ratio = ceil((1/(mileage*0.01)*sqrt(speed))));
  int damageProb = (rand() % (ratio+5));
  if (damageProb - ratio<=0) 
    {
      return 1;
    } 
    else 
    {
      return 0;
    }
    }
  else return 1;
}*/
void wheel ::output() {
  if (status == 1) {
    cout << "damaged" << endl;
  } else {
    cout << "not damaged" << endl;
  }
}

void engine::def_engine(double power) {
  //cout << "Engine power in HP: ";
  //power = InputProve(power);
  engPow = power;
  engIntake = calculateIntake();
}

void fuel_system ::calculate_cur_fuel(double engIntake, double mileage) { //расчёт текущего обЪёма топлива
    current_fuel=double(TankCapacity - ((engIntake / 100) * mileage));
}

void fuel_system ::def_fuel_system() {
  cout << "fuel capacity: ";
  double capacity=0.;
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
  cout << "TIME: " << setw(4)<<setfill('0')<<hours << ":" << setw(2)<<setfill('0')<<minutes << ":" << setw(2)<<setfill('0')<<seconds << endl;
}

void vehicle ::calculateSpeed() {
  if (damaged_wheels == 0) {
speed= double(fabs(sqrt(engPow) * (70.0 / double(Nwheels) - 2.5) * (current_fuel / 100.0)));
 }
 else
 {
   speed = (fabs(sqrt(engPow) * (70.0 / double(Nwheels) - 2.5) * (current_fuel / 100.0))*(pow(0.75, double(damaged_wheels))));
     }
  }


void vehicle ::number_of_damaged_wheels() 
{
  int count = 0;
  for (int i = 0; i < vec_wheels.size(); i++) 
  {
    if (vec_wheels[i].get_status() == 1) {
      count++;
    }
  }
  damaged_wheels = count;
}

void vehicle ::need_refuel(double tracklen)
{
  if (current_fuel < (engIntake*100) * tracklen)
  {
    this->plus_NRefuel();
    pit_stop_time+=this->refuel_time();
    current_fuel=TankCapacity;
  }
}

void vehicle :: need_change()
{
  if (damaged_wheels!=0)
  {
    pit_stop_time+=this->wheels_change();
    for(int i=0;i<vec_wheels.size();i++)
      {
        if (vec_wheels[i].get_status()==1)
        {
          vec_wheels[i].def_wheel(0.,0.);
        }
      }
  }
}
void vehicle::reset()
 {
   for(int i=0;i<vec_wheels.size();i++)
     {
       vec_wheels[i].set_status(0);
     }
   damaged_wheels=0;
   current_mileage=mileage=0;
   NRefuel=current_circles=0;
   Time=0;
   current_fuel=TankCapacity;
   calculateSpeed();
   for (int j = 0; j < vec_wheels.size(); j++)
     {
       vec_wheels[j].def_wheel(mileage,get_speed());
     }
   cout<<"\n"<<name<<" reseted"<<endl;
 }

int allfinished(vector<vehicle> &v,double trackLen,int circles)
{
  int count=0;
  for (int i=0;i<v.size();i++)
    {
      if (v[i].get_current_mileage()-trackLen*circles>=0)
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

