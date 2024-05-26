#include <iostream>
#include <string>
#include <vector>
using namespace std;
class vehicle
{
public:
  string name;
  int Nwheels;
  double speed;
  double mileage;
  double time;
  vehicle(){Nwheels=speed=mileage=0;}
  vehicle(string n,int w,double s,double m)
  {
    name=n;
    Nwheels=w;
    speed=s;
    mileage=m;
    time=calculate_time();
  }
  ~vehicle(){};
  double calculate_time()
{
  return mileage/speed;
}
  friend ostream &operator<<(ostream &stream, const vehicle &obj) {
    return stream <<"Name: "<<obj.name<<"\n"
      << "Number of wheels: " << obj.Nwheels << ";\n"
                  << "Speed: " << obj.speed << " km/h;\n"
                  << "Mileage: " << obj.mileage << " km;\n"
  <<"Time: "<<obj.time<<"\n";}
vehicle& operator=(const vehicle& other) {
  if (this == &other) { 
      return *this;
  }
  name = other.name;
  Nwheels = other.Nwheels;
  speed = other.speed;
  mileage = other.mileage;
  time=other.time;
  return *this;
  
};
int allfinished(vector<vehicle> &v)
{
  int count=0;
  for (int i=0;i<v.size();i++)
    {
      if (v[i].time==0)
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
int main() {
  cout << "Hello World!\n";
  vehicle car("0CAR",4,120,12.5);
  cout<<car<<endl;
  vector<vehicle> CARS;
  CARS.push_back(vehicle("1CAR",4,60,3));
  CARS.push_back(vehicle("2CAR",4,70,0));
  for (int i=0;i<CARS.size();i++)
    {
      cout<<CARS[i]<<endl;
    }
  int rounds=5;
  for (int j=0;j<rounds or allfinished(CARS);j++)
    {
      
    }
}

vehicle RatingResults(vector<vehicle> v, int qty) {
  vector<vehicle> results[qty];
  vector<vehicle> temp[0];
  for (int i = 0; i < qty; i++) {
    for (int j = 0; j < qty; j++) {
      if ((v[i].time- v[j].time < 0))
        temp[0] = results[i];
        results[i] = results[j];
        results[j] = temp[0];
      }
    }
  }
  
  return results;
}
void outputResults(vehicle *&adres, int qty) {
  vehicle *results = RatingResults(adres,qty);
  for (int i = 0; i < qty; i++) {
    cout << results[i].name << endl;
    results[i].time_display();
    cout << "Refuel times: " << int(results[i].NRefuel) << endl;
  }
  delete[] results;
}