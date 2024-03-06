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
    double amount;
    double length;
    double square;
    double perimetr;
    coordinates *coords=new coordinates[NumCoords];
};
double count_square(polygon *poly);
double count_perimetr(polygon *poly);
void clean(int var =1);
int menu(int var=1);
int prove(polygon *poly);
void search_coords(polygon *poly);
void output_coords(polygon *poly);
void create_polygon(polygon *&adres, int &size, polygon *poly);
void delete_polygon(polygon *poly, int &size,int del_index);
void maxMenu(polygon *poly,int size);
double maxPerimetr(polygon *poly,int size);
double maxSquare(polygon *poly,int size);
void PolyOutput(polygon *poly,int size, polygon *adres);
int main()
{
    clean();
    int size=0;//изначальный размер массива структур
    polygon *  adres = nullptr;
    polygon poly;
    int flag=1;
    while(flag==1)
    {
      int choice=10;
      choice=menu();
      if (choice>5){
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
          cin>>poly.coords->x>>poly.coords->y;
          create_polygon(adres,size,&poly);
          clean();
          break;}
        case(2):
          { 
            clean();
            PolyOutput(&poly,size,adres);
            break;
          }
        case(3):
          {
            clean();
            cout<<"\nInput number of polygon you want delete: ";
            int del_index=0;
            cin>>del_index;
            del_index--;
            delete_polygon(adres,size,del_index);
            cout<<"SIZE:"<<size<<"\n";
            break;
          }
        case(4):
          {
            maxMenu(adres,size);
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
  choice =cin.get();
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
  /* float a=0;//angle
  float a_temp=0;
  a=((poly->amount-2)*M_PI)/poly->amount;
  //cout<<"\n"<<a<<"\n";
  if(poly->coords[0].x>0)
  {
  poly->coords[1].x=poly->coords[0].x-(poly->length);
  poly->coords[1].y=poly->coords[0].y;

  for(int j=2; j<poly->amount; j=j+1)
    {
      poly->coords[j].x=poly->coords[j-1].x-cos(M_PI-a+a_temp);
      poly->coords[j].y=poly->coords[j-1].y-(pow(-1,j))*(poly->length)*sin(M_PI-a+a_temp);
      a_temp=(M_PI-a)+a_temp;
      
    }
  }
  else{
    poly->coords[1].x=poly->coords[0].x+(poly->length);
  poly->coords[1].y=poly->coords[0].y;
  cout<<"\n"<<poly->coords[1].x<<"\t"<<poly->coords[1].y;
  for(int j=2; j<poly->amount; j=j+1)
    {
      poly->coords[j].x=poly->coords[j-1].x+cos(M_PI-a+a_temp);
      poly->coords[j].y=poly->coords[j-1].y-(pow(-1,j))*(poly->length)*sin(M_PI-a+a_temp);
      a_temp=(M_PI-a)+a_temp;
  }
  }*/
}

void output_coords(polygon *poly)
{
  for (int j=0; j<poly->amount; j=j+1)
    {
      cout<<poly->coords[j].x<<"\t"<<poly->coords[j].y<<"\n";
    }
}
void create_polygon(polygon *&adres, int &size, polygon *poly)
{
    polygon* tempArray = new polygon[size+1];
    for (int i = 0; i < size; i++)
    {
        tempArray[i] = adres[i];
    }
    tempArray[size] = *poly;
    delete[] adres;
    adres = tempArray;
    size++;
}
void delete_polygon(polygon *adres, int &size,int del_index)
{
  cout<<"SIZE:"<<size<<"\n";
    if (del_index>=0 && del_index<size)
    {
        polygon* newTempArray=new polygon[size-1];
        int newIndex=0;
        for(int i=0; i<size; i=i+1)
        {
            if(i!=del_index)
            {
                newTempArray[newIndex]=adres[i];
                newIndex++;
            }
        }
        //delete[] adres;
        adres=newTempArray;
        size--;
        cout<<"Polygon deleted\n";
    }
    else{
        cout<<"\nError\tNO SUCH POLYGON\n";
    }
}
double maxSquare(polygon *poly,int size){
    double maxsquare = 0;
    for(int i = 0; i < size; i++){
        if((poly[i].square - maxsquare)>0){
              maxsquare = poly[i].square;
        }
    }
  return maxsquare;
}
double maxPerimetr(polygon *poly,int size){
    double maxperimetr = 0;
    for(int i = 0; i < size; i++){
        if((poly[i].square > maxperimetr)>0){
                maxperimetr = poly[i].square;
        }
    }
  return maxperimetr;
}
void maxMenu(polygon *poly,int size)
{
  int choice=0;
  cout<<"\nChoose what you want to find:\n1-MAX PERIMETR\n2-MAX SQUARE\n";
  cin>>choice;
  clean();
  if(choice==1)
  {
    cout<<"Max perimetr is "<<maxPerimetr(poly,size);
  }
  else if(choice==2)
  {
    cout<<"Max square is "<<maxSquare(poly,size);
  }
  else{cout<<"\nError, try another number!\n";}
}
void PolyOutput(polygon *poly,int size, polygon *adres)
{
  for (int i=0;i<size;i++){
  cout<<"Polygone #"<<i+1<<"\n";
  cout<<"amount of angles: "<<adres[i].amount;
  cout<<"\nlength of side: "<<adres[i].length;
  cout<<"\nPerimrtr: "<<adres[i].perimetr;
  cout<<"\nSquare: "<<adres[i].square<<"\n";
  search_coords(&adres[i]);
  output_coords(&adres[i]);
  }
  cin.get();
}
