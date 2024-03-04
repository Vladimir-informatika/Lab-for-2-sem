#include <iostream>
#include "cmath"
using namespace std;
struct coordinates
{
float x;
float y;
};
struct polygon
{
    int amount;
    int length;
    int square;
    int perimetr;
    coordinates *coords=new coordinates[200];
};
int count_square(polygon *poly);
int count_perimetr(polygon *poly);
void clean(int var =1);
int menu(int var=1);
int prove(polygon *poly);
void search_coords(polygon *poly);
void output_coords(polygon *poly);
void delete_polygon(polygon *poly, int &size,int del_index);
int main()
{
    clean();
    int size=0;//изначальный размер массива структур
    polygon *  adres = nullptr;
    int flag=1;
    while(flag==1)
    {
      int choice=10;
      choice=menu();
      switch(choice)
        {
        case(0):
          {
            cout<<"Are you sure you want to exit?\n0-yes\n1-go back\n";
              int exit=2;
              cin>> exit;
              if(exit==0)
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
          polygon poly;
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
          search_coords(&poly);
          polygon* tempArray=new polygon[size+1];
            for (int i=0;i<size;i++)
              {
                tempArray[i]=adres[i];
              }
            tempArray[size]=poly;
            delete[] adres;
            adres=tempArray;
            size++;
          clean();
          break;}
        case(2):
          { 
            clean();
            int i=0;
            cout<<"\nInput number of your polygon:";
            cin>>i;
            i--;
            if ((i<size) && (i>=0)){
            cout<<"Polygone #"<<i+1;
            cout<<"amount of angles: "<<adres[i].amount;
            cout<<"\nlength of side: "<<adres[i].length;
            cout<<"\nPerimrtr: "<<adres[i].perimetr;
            cout<<"\nSquare: "<<adres[i].square<<"\n";
            output_coords(&adres[i]);
            }
            else{
              cout<<"NO SUCH POLYGON\n";
            }
            cin.get();
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
            break;
          }
        default: clean();cout<<"\nError, try another number!\n";break;
    }
    }
    return 0;
}
int count_square(polygon *poly)
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

int count_perimetr(polygon *poly)
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
  cout<<"Inter a number to choose action:\n";
  cout<<"0 for exit\n";
  cout<<"1 for adding polygon\n";
  cout<<"2 for output information about polygon\n";
  cout<<"3 for deleting polygon\n";
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
    }
  else if((poly->length<1) or (poly->length>1000))
    {
      flag=1;
      cout<<"Uncorrect length\n";
    }
  return flag;
}
void search_coords(polygon *poly)
{
  float a=0;//angle
  float a_temp=0;
  a=((poly->amount-2)*M_PI)/poly->amount;
  cout<<"\n"<<a<<"\n";
  poly->coords[1].x=poly->coords[0].x-(poly->length);
  poly->coords[1].y=poly->coords[0].y;
  cout<<"\n"<<poly->coords[1].x<<"\t"<<poly->coords[1].y;
  for(int j=2; j<poly->amount; j=j+1)
    {
      poly->coords[j].x=poly->coords[j-1].x-cos(M_PI-a+a_temp);
      poly->coords[j].y=poly->coords[j-1].y-(pow(-1,j))*(poly->length)*sin(M_PI-a+a_temp);
      a_temp=(M_PI-a)+a_temp;
      cout<<"\n"<<poly->coords[j].x<<"\t"<<poly->coords[j].y;
    }
}
void output_coords(polygon *poly)
{
  for (int j=0; j<poly->amount; j=j+1)
    {
      cout<<poly->coords[j].x<<"\t"<<poly->coords[j].y<<"\n";
    }
}
void delete_polygon(polygon *adres, int &size,int del_index)
{
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
        delete[] adres;
        adres=newTempArray;
        size--;
        cout<<"Polygon deleted\n";
    }
    else{
        cout<<"\nError\tNO SUCH POLYGON\n";
    }
}
