#include <iostream>
#include "cmath"
#include <string>
using namespace std;
class vehicle
{
 private:
 //int NumOwners;
 //int NumCrashes;
 //double mileage;//пробег
 //double TankCapacity;//обЪём бака
 double speed=calculateSpeed();
 double engIntake=calculateIntake();//потребление двигателя
 public:
 int Nwheels;
 double engPow;//мощность двигателя
 string name;
 double raceTime;//время пути
 inline double calculateSpeed(){return engPow / (10 * Nwheels);}
 inline double calculateIntake(){return engPow*0.1;}
 vehicle ()
{
}
void output()
{
  cout<<"количество колес: "<<Nwheels<<"\t"<<"мощность двигателя: "<<engPow<<"\t"<<"скорость: "<<speed<<"\t"<<endl;
}
};
int main()
{
  vehicle lada;
  lada.Nwheels=4;
  lada.engPow=100;
  lada.name="Lada";
  lada.output();
}