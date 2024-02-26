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


