#include <iostream>
#include "cmath"

using namespace std;
int count_square(int amount, int length);
int count_perimetr(int *amount, int *length);
void clean(int var =1);

int main()
{
    clean();
    setlocale(LC_ALL,"RUS");
    struct polynom
    {
        int amount;
        int length;
        int square=count_square(amount, length);
        int perimetr=count_perimetr(&amount, &length);
        int x;
        int y;
    }poly;
    int flag=1;
    while(flag==1)
    {
        cout<<"Введите 1, чтобы начать ввод параметров многоугольника\n";
        cout<<"Введите 0, чтобы выйти из программы\n";
        int choice=10;
        cin>> choice;
        if(choice==0)
        {
            cout<<"Вы уыерены, что хотите выйти? 0-Да, 1-Продолжить работу\n";
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
        if (choice==1)
        {
            cout<<"Введите количество сторон:\n";
            cin>>poly.amount;
            cout<<"Введите длину стороны:\n";
            cin>>poly.length;
            cout<<poly.length<<"\n";
            cout<<poly.perimetr<<"\n";
        }
    }


    return 0;
}
int count_square(int amount, int length)
{
    int result=0;
    result=((amount*length*length)/4)*(cos(180/amount)/sin(180/amount));

   return result;
}

int count_perimetr(int *amount, int *length)
{
    int result;
    result=*amount**length;
    return result;
}

void clean(int var)
{
    for(int i=0; i<100; i=i+1)
    {
        cout<<"\n";
    }
}
