#include <iostream>
#include "cmath"
#include <cstdlib>
using namespace std;
int NumCoords=200;
struct coordinates
{
double x;
double y;
};
struct polygon
{
    int amount;
    double length;
    double square;
    double perimetr;
    double X;
    double Y;
};
double count_square(polygon *poly);
double count_perimetr(polygon *poly);
void clean(int var =1);
int menu(int var=1);
int prove(polygon *poly);
void search_coords(polygon *poly);
int Prove_Coords(polygon *poly);
void create_polygon(polygon *&adres, int &qty, polygon *poly);
void delete_polygon(polygon *&adres, int &qty, int del_index);
void maxMenu(polygon *poly,int qty);
double maxParam(polygon *poly,int qty,int choice, int *&IndArr,int &index);
void PolyOutput(polygon *poly,int qty, polygon *adres);
int main()
{
    clean();
    int qty=0;//изначальный размер массива структур
    polygon *  adres = nullptr;
    polygon poly;
    int flag=1;
    while(flag==1)
    {
      int choice=10;
      choice=menu();
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
          cout<<"amount of angles: ";
          cin>>poly.amount;
          cout<<"length of side: ";
          cin>>poly.length;
          if (prove(&poly)==1)
          {
            break;
          }
          poly.perimetr=count_perimetr(&poly);
          poly.square=count_square(&poly);
          cout<<"input coords x and y: ";
          cin>>poly.X>>poly.Y;
          if (Prove_Coords(&poly)==0){
            break;
          }
          create_polygon(adres,qty,&poly);
          clean();
          break;}
        case(2):
          { 
            clean();
            PolyOutput(&poly,qty,adres);
            break;
          }
        case(3):
          {
            clean();
            cout<<"\nInput number of polygon you want delete: ";
            int del_index=0;
            cin>>del_index;
            del_index--;
            delete_polygon(adres,qty,del_index);
            break;
          }
        case(4):
          {
            maxMenu(adres,qty);
            cin.get();
            break;
          }
        default: clean();break;
    }
    }
    return 0;
}
double count_square(polygon *poly)
{
  int result=0;
  if(poly->amount==3){
    result=(((poly->length)*(poly->length))*sqrt(3))/4;
  }
  else if(poly->amount==4){
    result=((poly->length)*(poly->length));
  }
  else
  {
  result = ((poly->amount) * (poly->length) * (poly->length)) / (4 * tan(M_PI / (poly->amount)));
  }
   return result;
}

double count_perimetr(polygon *poly)
{
    int result;
    result=(poly->amount)*(poly->length);
    return result;
}

void clean(int var)
{
    for(int i=0; i<100; i=i+1)
    {
        cout<<"\n";
    }
}
int menu(int var)
{
  cout<<"\nInter a number to choose action:\n";
  cout<<"0 for exit\n";
  cout<<"1 for adding polygon\n";
  cout<<"2 for output information about polygon\n";
  cout<<"3 for deleting polygon\n";
  cout<<"4 for MAX menu\n";
  char choice='0';
  cin>>choice;
  return (int(choice)-48);
    }
int prove(polygon *poly)
{
  int flag=0;
  if((poly->amount<3) or (poly->amount>100))
    {
      flag=1;
      cout<<"Uncorrect amount of angles\n";
      cin.get();
    }
  else if((poly->length<1) or (poly->length>1000))
    {
      flag=1;
      cout<<"Uncorrect length\n";
      cin.get();
    }
  return flag;
}
void search_coords(polygon *poly)
{
  coordinates *coords=new coordinates[poly->amount];
  double R=poly->length/(2*sin(M_PI/poly->amount));
  double k=atan2(poly->X,poly->Y);
  double Nx=poly->X-R*cos(k);
  double Ny=poly->Y-R*sin(k);
  for(int i=1;i<poly->amount;i++){
     double angle= 2*M_PI*i/poly->amount;
     coords[i].x=Nx+R*cos(k+angle);
     coords[i].y=Ny+R*sin(k+angle);
  }
  cout<<poly->X<<"\t"<<poly->Y<<"\n";
  for (int j=1; j<poly->amount; j=j+1)
  {
    cout<<coords[j].x<<"\t"<<coords[j].y<<"\n";
  }
}
int Prove_Coords(polygon *poly)
{
  int flag=1;
  double R=poly->length/(2*sin(M_PI/poly->amount));
  double CheckR=0;
  CheckR=sqrt(pow(poly->X,2)+pow(poly->Y,2));
  if(R>CheckR){
      flag=0;
      cout<<"Uncorrect coords or length of side\n";
  }
  return flag;
}
void create_polygon(polygon *&adres, int &qty, polygon *poly)
{
    polygon* tempArray;
    if (adres != nullptr) {
        tempArray = new polygon[qty + 1];
        for (int i = 0; i < qty; i++) {
            tempArray[i] = adres[i];
        }
        delete[] adres;
    } else {
        tempArray = new polygon[1];
    }

    tempArray[qty] = *poly;
    adres = tempArray;
    qty++;
}
void delete_polygon(polygon *&adres, int &qty, int del_index)
{
    if (del_index >= 0 && del_index < qty)
    {
        polygon* newTempArray = new polygon[qty - 1];
        int newIndex = 0;
        for (int i = 0; i < qty; i++)
        {
            if (i != del_index)
            {
                newTempArray[newIndex] = adres[i];
                newIndex++;
            }
        }

        delete[] adres; 
        adres = newTempArray;
        qty--;
        cout << "Polygon deleted\n";
    }
    else {
        cout << "\nError\tNO SUCH POLYGON\n";
    }
}
double maxParam(polygon *poly,int qty,int choice, int *&IndArr,int &index){
    double maxparam = 0;
    index=0;
    if (choice==1){
    for(int i = 0; i < qty; i++){
        if((poly[i].perimetr - maxparam)>=0){
                  maxparam = poly[i].perimetr;
                  IndArr[index]=i;
                  index++;      
        }
    }
    }
    else if(choice==2)
    {
      for(int i = 0; i < qty; i++){
      if((poly[i].square - maxparam)>=0){
            maxparam = poly[i].square;
            IndArr[index]=i;
            index++;
      }
    }
    }
  return maxparam;
}
void maxMenu(polygon *poly, int qty) {
    clean();
    int choice = 0;
    int *IndArr = new int[qty];
    int index = 0;

    cout << "\nChoose what you want to find:\n1-MAX PERIMETER\n2-MAX SQUARE\n3-Exit max menu\n";
    cin >> choice;
    clean();

    if (choice == 1) {
        cout << "Max perimeter is " << maxParam(poly, qty, choice, IndArr, index) << "\n";
        if (index > 0) {
            for (int i = 0; i < index; i++) {
                cout << "Index of polygon: #" << IndArr[i] + 1 << "\n";
            }
        }
    } else if (choice == 2) {
        cout << "Max square is " << maxParam(poly, qty, choice, IndArr, index) << "\n";
        if (index > 0) {
            for (int i = 0; i < index; i++) {
                cout << "Index of polygon: #" << IndArr[i] + 1 << "\n";
            }
        }
    } else if (choice == 3) {
        clean();
    } else {
        cout << "\nError, try another number!\n";
    }

    delete[] IndArr;
}

void PolyOutput(polygon *poly,int qty, polygon *adres)
{
  for (int i=0;i<qty;i++){
  cout<<"Polygone #"<<i+1<<"\n";
  cout<<"amount of angles: "<<adres[i].amount;
  cout<<"\nlength of side: "<<adres[i].length;
  cout<<"\nPerimrtr: "<<adres[i].perimetr;
  cout<<"\nSquare: "<<adres[i].square<<"\n";
  search_coords(&adres[i]);
  }
  cin.get();
}
