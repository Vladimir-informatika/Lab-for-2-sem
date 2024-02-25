#include <iostream>
#include "cmath"

using namespace std;
int count_square(int *amount, int *length);
int count_perimetr(int &amount, int &length);
void clean(int var =1);
int menu(int var=1);
int main()
{
    clean();
    setlocale(LC_ALL,"RUS");
    struct polynom
    {
        int amount;
        int length;
        int square=count_square(&amount, &length);
        int perimetr=count_perimetr(amount, length);
        int x;
        int y;
    }poly;
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

        }
        case(1):
        {
            cout<<"amount of angles: ";
            cin>>poly.amount;
            cout<<"\nlength of side: ";
            cin>>poly.length;
            cout<<poly.length<<"\n";
            cout<<"Perimrtr: ";
            cout<<poly.perimetr<<"\n";
        }
          default: cout<<"\nError, try another number!\n";
    }
    }

    return 0;
}
int count_square(int *amount, int *length)
{
    int result=0;
  result = ((*amount * (*length) * (*length)) / 4) * (cos(180 / (*amount)) / sin(180 / (*amount)));

   return result;
}

int count_perimetr(int &amount, int &length)
{
    int result;
    result=(amount)*(length);
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
  int choice=10;
  cin>> choice;
  return choice;
}