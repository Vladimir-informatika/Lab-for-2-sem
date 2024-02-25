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
int main()
{
    clean();
    int size=1;//количество фигур
    polygon *poly = new polygon[size];
    int flag=1;
    while(flag==1)
    {
      polygon *poly = new polygon[size];
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
            cout<<"amount of angles: ";
            cin>>poly[size].amount;
            cout<<"length of side: ";
            cin>>poly[size].length;
            cout<<poly[size].length<<"\n";
            poly[size].perimetr=count_perimetr(&poly[size]);
            poly[size].square=count_square(&poly[size]);
            size++;
          break;}
        case(2):
          { 
            int i=0;
            cout<<"\nInput number of your polygon:";
            cin>>i;
            cout<<"amount of angles: "<<poly[i-1].amount;
            cout<<"\nlength of side: "<<poly[i-1].length;
            cout<<"\nPerimrtr: "<<poly[i-1].perimetr;
            cout<<"\nSquare: "<<poly[i-1].square<<"\n";
          break;
          }
          
        default: cout<<"\nError, try another number!\n";break;
    }
    }
    delete[] poly;
    return 0;
}
int count_square(polygon *poly)
{
  int result=0;
  result = ((poly->amount) * (poly->length) * (poly->length)) / (4 * tan(M_PI / (poly->amount)));
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