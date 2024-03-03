#include <iostream>
#include "cmath"
using namespace std;
struct polygon
{
    int amount;
    int length;
    int square;
    int perimetr;
    int x;
    int y;
};
int count_square(polygon *poly);
int count_perimetr(polygon *poly);
void clean(int var =1);
int menu(int var=1);
int prove(polygon *poly);
void search_coords(polygon *poly,int i);
void output_coords(polygon *poly);
int main()
{
    clean();
    int size=100;//количество фигур
    polygon *poly = new polygon[size];
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
        case(1):
          {
          clean();
          int i=0;
          cout<<"Input number of your polygon";
          cin>>i;
          cout<<"amount of angles: ";
          cin>>poly[i].amount;
          cout<<"length of side: ";
          cin>>poly[i].length;
          if (prove(&poly[i])==1)
          {
            cout<<"Error\n";
            break;
          }
          cout<<poly[i].length<<"\n";
          poly[i].perimetr=count_perimetr(&poly[i]);
          poly[i].square=count_square(&poly[i]);
          clean();
          break;}
        case(2):
          { 
            clean();
            int i=0;
            int cont=0;
            cout<<"\nInput number of your polygon:";
            cin>>i;
            cout<<"amount of angles: "<<poly[i].amount;
            cout<<"\nlength of side: "<<poly[i].length;
            cout<<"\nPerimrtr: "<<poly[i].perimetr;
            cout<<"\nSquare: "<<poly[i].square<<"\n";
            output_coords(&poly[i]);
            cout<<"input 1 to continue ";
            cin>>cont;
            if(cont==1)
            {
              clean();
              break;
            }
          }
        default: clean();cout<<"\nError, try another number!\n";break;
    }
    }
  delete[] poly;
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
  cout<<"1 for adding polynom\n";
  cout<<"2 for output information about polygon\n";
  int choice=10;
  cin>> choice;
  return choice;
}
int prove(polygon *poly)
{
  int flag=0;
  if((poly->amount<3) or (poly->amount>100) or (poly->length<1) or (poly->length>1000))
    {
      flag=1;
    }
  return flag;
}
void search_coords(polygon *poly,int i)
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
      poly->coords[j].x=poly->coords[j-1].x-(pow(-1,j+1))*(poly->length)*cos(M_PI-a+a_temp);
      poly->coords[j].y=poly->coords[j-1].y-(pow(-1,j))*(poly->length)*sin(M_PI-a+a_temp);
      a_temp=(a)+a_temp;
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

