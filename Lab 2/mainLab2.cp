#include <iostream>
#include "cmath"
#include <string>
using namespace std;
class vehicle
{
 private:
 double mileage;//пробег
 double TankCapacity;//обЪём бака
 double speed;
 double engIntake;//потребление двигателя
 public:///////////////////////////////////////////////////////
 int Nwheels;
 double engPow;//мощность двигателя
 string name;
 double Time;//время пути
 inline double calculateSpeed(){return sqrt(engPow)*(70/Nwheels-2.5);}
 inline double calculateIntake(){return engPow*0.1;}
 inline double calculateRefuel(){return ((mileage*engIntake)/TankCapacity);};
 inline double calculateRaceTime(double raceLength){return (raceLength/speed);};
 vehicle ()
{
  name="";
  Nwheels=0;
  engPow=0;
  mileage=0;
  TankCapacity=0;
  Time=0;
  speed=0;
  engIntake=0;
}
~vehicle()
{
  cout<<"Destruction of "<<name<<endl;
}
void output()
{
  cout<<"Number of wheels: "<<Nwheels<<";\t"<<"power of engine: "<<engPow<<"HP;\t"<<"speed: "<<speed<<"km/h;\t"<<"Engine intake: "<<engIntake<<"l/100km"<<endl;
}
void inputVeh()
{
  cout<<"\nName of the car: ";
  //getline(cin,name);
  cin>>name;
  cout<<"Number of wheels: ";
  cin>>Nwheels;
  while ((Nwheels<2)|| (Nwheels>8))
    {cout<<"Uncorrect number of wheels, try again\n";cin>>Nwheels; }
  cout<<"Power of the engine (HP): ";//horse power?
  cin>>engPow;
  while (engPow<0)
    {cout<<"Uncorrect, try again\n";cin>>engPow; };
  cout<<"Mileage (km): ";
  cin>>mileage;
  while (mileage<0)
    {cout<<"Uncorrect, try again\n";cin>>mileage; };
  cout<<"Tank capacity (l): ";
  cin>>TankCapacity;
  while (TankCapacity<0)
    {cout<<"Uncorrect, try again\n";cin>>TankCapacity; };
  cout<<"Time: ";
  cin>>Time;
  while (Time<0)
    {cout<<"Uncorrect, try again\n";cin>>Time; };
  speed=calculateSpeed();
  engIntake=calculateIntake();
}
};
int menu(int &flag);
void clean(int var =1);
void create_vehicle(vehicle *&adres,int &qty, vehicle cars);
/////////////////////////////////MAIN/////////////////////////
int main()
{
  //vehicle lada;
  //lada.inputVeh();
  //lada.output();
  clean();
  int qty=0;//изначальный размер массива 
  vehicle *  adres = nullptr;
  vehicle cars;
  int flag=1;
  while(flag==1)
    {
      int choice=10;
      int rez=0;
      choice=menu(rez);
      if ((choice>5) || (choice<0)){
        cout<<"\nError, try another number!\n";
      }
      switch(choice)
        {
        case(0):
          {
            cout<<"Are you sure you want to exit?\n1-yes\n0-go back\n";
            int exit=2;
            cin>> exit;
            if(exit==1)
            {
              flag=0;
              break;
            }
            else{
              clean();
            }
            break;
          }
              delete[] adres;
              break;
          case(1):
            {
            clean();
            cars.inputVeh();
            create_vehicle(adres,qty, cars);
            break;}
          case(2):
            { 
              clean();
              for (int i=0;i<qty;i++)
                {
                  cout<<adres[i].name<<endl;
                  adres[i].output();
                }
              break;
            }
          case(3):
            {
              clean();
              break;
            }
          case(4):
            {
              cout<<"rez"<<rez;
              break;
            }
          case(5):
          {
            break;
          }
          default: clean();break;
      }
      }
  return 0;
}

void clean(int var)
{
    for(int i=0; i<100; i=i+1)
    {
        cout<<"\n";
    }
}
int menu(int &rez)
{
  cout<<"\nInter a number to choose action:\n";
  cout<<"0 for exit\n";
  cout<<"1 for adding Vehicle\n";
  cout<<"2 for output information about Vehicle\n";
  cout<<"3 to enter length of the track\n";
  cout<<"4 for route calculation\n";//расчет прохождения трассы
  if (rez==1)
    cout<<"5 for results of race\n";
  char choice='0';
  cin>>choice;
  if ((int(choice)-48)==4)
  {
    rez=1;
  }
  return (int(choice)-48);
}
void create_vehicle(vehicle *&adres,int &qty, vehicle cars)
{
  vehicle* tempArray;
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