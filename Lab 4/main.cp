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
  void time_display();
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
vector<vehicle>RatingResults(vector<vehicle> v);
void outputResults(vector<vehicle> v);
int main() {
  vector<vehicle> race_rez;
  vehicle car("0CAR",4,120,12.5);
  cout<<car<<endl;
  vector<vehicle> CARS;
  CARS.push_back(vehicle("1CAR",4,60,3));
  CARS.push_back(vehicle("2CAR",4,70,1));
  for (int i=0;i<CARS.size();i++)
    {
      cout<<CARS[i]<<endl;
    }
  //int rounds=5;
  race_rez=RatingResults(CARS);
  outputResults(race_rez);
  return 0;
}

vector<vehicle>  RatingResults(vector<vehicle> v) {
  vector<vehicle> results;
  vehicle temp;
  results=v;
  cout<<"REZ"<<results[0]<<endl;
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v.size(); j++) {
      if ((v[i].time- v[j].time < 0))
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
void vehicle::time_display() {
  double t = this->time;
  int hours = int(t);
  double cur_time = (t - hours) * 60;
  int minutes = int(cur_time);
  int seconds = int((cur_time - minutes) * 60);
  cout << "TIME: " << hours << ":" << minutes << ":" << seconds << endl;
}