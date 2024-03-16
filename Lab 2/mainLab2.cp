#include <iostream>
#include "cmath"
#include <string>
using namespace std;
class vehicle
{
 private:
 double TankCapacity;//обЪём бака
 double speed;
 double engIntake;//потребление двигателя
 public:///////////////////////////////////////////////////////
 double mileage;//пробег
 double NRefuel;//количесвто дозаправок
 int Nwheels;
 double engPow;//мощность двигателя
 string name;
 double Time;//время пути
 inline double calculateSpeed(){return sqrt(engPow)*(70/Nwheels-2.5);}
 inline double calculateIntake(){return pow(engPow,1/3)+sqrt(engPow)-6.25;}
 inline double calculateRefuel(){return ((mileage*(engIntake/100))/TankCapacity);};
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
  NRefuel=0;
}
~vehicle()
{
  cout<<"Destruction of "<<name<<endl;
}
void output()
{
  cout<<"Number of wheels: "<<Nwheels<<";\t"<<"power of engine: "<<engPow<<"HP;\t"<<"speed: "<<speed<<"km/h;\t"<<"Engine intake: "<<engIntake<<"l/100km;\t"<<"mileage: "<<mileage<<"km;"<<endl;
}
void inputVeh()
{
  cout<<"\nName of the car: ";
  //getline(cin,name);
  cin>>name;
  cout<<"Number of wheels: ";
  cin>>Nwheels;
  while ((Nwheels<2)|| (Nwheels>8) || (Nwheels==5) || (Nwheels==7))
    {cout<<"Uncorrect number of wheels, try again\n";cin>>Nwheels; }
  cout<<"Power of the engine (HP): ";//horse power?
  cin>>engPow;
  while (engPow<0)
    {cout<<"Uncorrect, try again\n";cin>>engPow; };
  cout<<"Tank capacity (l): ";
  cin>>TankCapacity;
  while (TankCapacity<0)
    {cout<<"Uncorrect, try again\n";cin>>TankCapacity; };
  speed=calculateSpeed();
  engIntake=calculateIntake();
}
};
int menu(int &flag);
void clean(int var =1);
void create_vehicle(vehicle *&adres,int &qty, vehicle cars);
vehicle* RatingResults(vehicle *&adres, int qty);
void outputResults(vehicle *&adres, int qty);
/////////////////////////////////MAIN/////////////////////////
int main()
{
  clean();
  int qty=0;//изначальный размер массива 
  vehicle *  adres = nullptr;
  vehicle cars;
  double trackLen=0;
  int flag=1;
  int rez=0;
  while(flag==1)
    {
      int choice=10;
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
            clean();
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
              cout<<"Enter the length of the track (km): ";
              cin>>trackLen;
              rez=0;
              break;
            }
          case(4):
            {
              clean();
              if (trackLen==0)
              {
                cout<<"You haven't entered the length of the track!\n";rez=0;break;
              }
              else
              {
                for (int i=0;i<qty;i++)
                  {
                    adres[i].Time=adres[i].calculateRaceTime(trackLen);
                    adres[i].mileage=(adres[i].mileage)+trackLen;
                    adres[i].NRefuel=adres[i].calculateRefuel();
                  }
              }
              break;
            }
          case(5):
          {
            clean();
            outputResults(*&adres,qty);
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
      for (int i = 0; i < qty; i++) 
      {
          tempArray[i] = adres[i];
      }
      delete[] adres;
  } 
  else 
  {
      tempArray = new vehicle[1];
  }
  tempArray[qty] = cars;
  adres = tempArray;
  qty++;
}
vehicle* RatingResults(vehicle *&adres, int qty)
{
  vehicle *results = new vehicle[qty];
  int resultIndex = 0;
  for (int i = 0; i < qty; i++)
  {
    for (int j = 0; j < qty; j++)
    {
      if ((adres[i].Time - adres[j].Time <= 0) && (adres[i].NRefuel - adres[j].NRefuel <= 0))
      {
        results[resultIndex] = adres[i];
        resultIndex++;
        break;
      }
    }
  }
  return results;
}
void outputResults(vehicle *&adres, int qty)
{
  vehicle *results = RatingResults(adres, qty);
  for (int i=0; i<qty;i++)
    {
      cout<<results[i].name<<endl;
      cout<<"TIME: "<<results[i].Time<<endl;
      cout<<"Refuel times: "<<int(ceil(results[i].NRefuel))<<endl; 
    }
  delete[] results;
}