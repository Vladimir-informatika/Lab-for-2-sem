#include <iostream>
#include <cmath>


using namespace std;

struct regular_polygon {
    int count_sides;
    double length;
    double square;
    double perimeter;
    double *x;
    double *y;
};

void square_perimeter(int k ,struct regular_polygon* reg_pol, int amount, int* output);
void SetData(regular_polygon* reg_pol, int amount, int* output);
regular_polygon* AddStruct(regular_polygon* reg_pol, int amount);
int* AddOutput(int amount, int* output);
void menu(regular_polygon* OurPolygon, int PolygonAmount, int* output);
void print(regular_polygon* OurPolygon, int amount, int* output);
void check(regular_polygon* OurPolygon, int PolygonAmount, int* output);
void submenu(regular_polygon* OurPolygon, int PolygonAmount, int* output);
void coordinates(struct regular_polygon* reg_pol, int amount);


int main()
{
    regular_polygon* OurPolygon = 0;
    int PolygonAmount = 0;
    int* output = new int[PolygonAmount];
    output[0] = 1;
    cout << "Hello!" << '\n';
    menu(OurPolygon, PolygonAmount, output);
    return 0;
}





// Создаём новую структуру и перезаписываем динамический массив структур

regular_polygon* AddStruct(regular_polygon* reg_pol, int amount)
{
    if (amount == 0)
    {
        reg_pol = new regular_polygon[amount + 1];
    }
    else
    {
        regular_polygon* temp = new regular_polygon[amount + 1];
        for (int i = 0; i < amount; i++)
        {
            temp[i] = reg_pol[i];
        }
        delete[] reg_pol;

        reg_pol = temp;
    }
    return reg_pol;
}

int* AddOutput(int amount, int* output)
{

    if (amount != 0)
    {
        int* temp2 = new int[amount + 1];
        for (int i = 0; i < amount; i++)
        {
            temp2[i] = output[i];
        }
        delete[] output;
        output = temp2;
        output[amount] = 1;
    }
    return output;
}

// Заполняем новую структуру

void SetData(regular_polygon* reg_pol, int amount, int* output)
{
    cout << "Enter count of sides:" << '\n';
    cin >> reg_pol[amount].count_sides;

    bool flag = false;
    if (reg_pol[amount].count_sides > 2) flag = true;
    while (flag == false)
    {
        cout << "Incorrect! Sides must be more than 2. Try again" << '\n';
        cin >> reg_pol[amount].count_sides;
        if (reg_pol[amount].count_sides > 2) flag = true;
    }


    cout << "Enter length of the side:" << '\n';
    cin >> reg_pol[amount].length;
    flag = false;
    if (reg_pol[amount].length > 0) flag = true;
    while (flag == false)
    {
        cout << "Incorrect! Length must be more than 0. Try again" << '\n';
        cin >> reg_pol[amount].count_sides;
        if (reg_pol[amount].length > 0) flag = true;
    }

    //square
    if (reg_pol[amount].length == 3) reg_pol[amount].square = reg_pol[amount].length * reg_pol[amount].length * sqrt(3) / 4;
    if (reg_pol[amount].length == 4) reg_pol[amount].square = reg_pol[amount].length * reg_pol[amount].length;
    else
    {
        reg_pol[amount].square = 0.25 * reg_pol[amount].count_sides * reg_pol[amount].length * reg_pol[amount].length * pow(tan(M_PI / ((double)reg_pol[amount].count_sides)), -1.0);
    }
    //perimeter
    reg_pol[amount].perimeter = reg_pol[amount].count_sides * reg_pol[amount].length;


    cout << "Enter vertex coordinates" << '\n';
    reg_pol[amount].x = new double[ reg_pol[amount].count_sides ];
    reg_pol[amount].y = new double[ reg_pol[amount].count_sides ];

    flag = false;
    cout << "Enter x:" << '\n';
    cin >> reg_pol[amount].x[ 0];
    cout << "Enter y:" << endl;
    cin >> reg_pol[amount].y[ 0];
    double pramaya = pow( pow(reg_pol[amount].x[0], 2) + pow(reg_pol[amount].y[0], 2), 0.5);
    double Radius = reg_pol[amount].length / (2 * sin(M_PI / (reg_pol[amount].count_sides)));
    if ( pramaya - Radius > 0) flag = true;
    while (flag == false)
    {
        cout << "According to the condition, the point should be the farthest from (0, 0)!!! Try again" << endl;
        cout << "Enter x:" << '\n';
        cin >> reg_pol[amount].x[ 0];
        cout << "Enter y:" << endl;
        cin >> reg_pol[amount].y[ 0];
        pramaya = pow( pow(reg_pol[amount].x[0], 2) + pow(reg_pol[amount].y[0], 2), 0.5);
        Radius = reg_pol[amount].length / (2 * sin(M_PI / (reg_pol[amount].count_sides)));
        if ( pramaya - Radius > 0) flag = true;
    }
    cout << "Good!" << endl;


    coordinates(reg_pol, amount);
}
////////////   regpol several, not one


/////// ОГРАНИЧЕНИЯ///////

/////////////// МЕНЮ////////////////

void menu(regular_polygon* OurPolygon, int PolygonAmount, int* output)
{
    int chosenForDelete = 0;
    cout << '\n' << "MENU" << '\n' << "----------------------" << '\n';
    cout << "Choose the action" << '\n';
    cout << "1 - Add polygon" << '\n';
    cout << "2 - Show polygons" << '\n';
    cout << "3 - Delete polygon" << '\n';
    cout << "4 - Square/perimeter" << '\n';
    cout << "5 - Close the programm" << '\n';
    cout << '\n' << "Your input: ";

    char choice = '0';
    cin >> choice;
    int choose = int(choice)-48;
    //int choose;
    //cin >> choose;
    cout << '\n';
    switch (choose)
    {
    case 1:
        OurPolygon = AddStruct(OurPolygon, PolygonAmount);
        output = AddOutput(PolygonAmount, output);
        SetData(OurPolygon, PolygonAmount, output);
        PolygonAmount++;
        break;
    case 2:
        cout << '\n';

        cout << "OK, let's look" << '\n';
        print(OurPolygon, PolygonAmount, output);
        break;
    case 3:
        cout << "Which polygon you want to delete? Input the sequence number:" << '\n';
        cin >> chosenForDelete;
        if (chosenForDelete > PolygonAmount)
        {
            cout << "There is no such polygon yet :( " << '\n';
        }
        else if (chosenForDelete < 1)
        {
            cout << "Error: try again! " << '\n';
        }
        else
        {
            cout << "As you wish" << '\n';
            output[chosenForDelete - 1] = 0;
            //output = del_struct(output, chosenForDelete);
        }
        break;
    case 4:
        submenu(OurPolygon, PolygonAmount, output);
        break;
    case 5:
        check(OurPolygon, PolygonAmount, output);
        return;
        break;
    default:
        cout << "Incorrect! Try again" << '\n';
        break;
    }
    menu(OurPolygon, PolygonAmount, output);
    return;
}

/// В Ы В О Д
void print(regular_polygon* reg_pol, int amount, int* output)
{
    for (int i = 0; i < amount; i++)
    {
        if (output[i] == 1)
        {
            cout << "Polygon number " << i + 1 << endl;

            cout << "quontity of vertexes: ";
            cout << reg_pol[i].count_sides << '\n';

            cout << "coordinates of vertexes: " << endl;
            for (int j = 0; j < reg_pol[i].count_sides; j++)
            {
                cout << "x" << j << ": " << reg_pol[i].x[j] << endl;
                cout << "y" << j << ": " << reg_pol[i].y[j] << endl << endl;
            }

            cout << "Square = " << reg_pol[i].square << '\n';
            cout << "Perimeter= " << reg_pol[i].perimeter << '\n';

            cout << "Good job!" << '\n' << '\n';
            cout << "---------------------------" << endl;
        }
        else
        {
            for (int i = 0; i < 7; i++) cout << '\n';
        }
    }
}

/// УДОСТОВЕРЕМСЯ ВЫХОДИТЬ ИЛИ НЕТ
void check(regular_polygon* OurPolygon, int PolygonAmount, int* output)
{
    cout << "Are you sure that you want to quit? (1 - yes; 0 - no)" << '\n';
    int k;
    cin >> k;
    switch (k)
    {
    case 1:
        return;
        break;
    case 0:
        menu(OurPolygon, PolygonAmount, output);
        break;
    default:
        cout << "Incorrect! Try again" << '\n';
        check(OurPolygon, PolygonAmount, output);
        break;
    }
    return;
}


///ПОДМЕНЮШКА
void submenu(regular_polygon* OurPolygon, int PolygonAmount, int* output)
{
    int k;
    cout << "What are you going to do?" << '\n';
    cout << "1 - Max Square" << endl << "2 - Max Perimeter"  << endl << "3 - quit" << endl;
    cin >> k;

    switch (k)
    {
    case 1:
        cout << "Let's look" << endl << "-----------------------" << endl;
        square_perimeter(k , OurPolygon, PolygonAmount, output);
        cout << "That's all" << '\n';
        break;
    case 2:
        cout << "Let's look" << endl << "-----------------------" << endl;
        square_perimeter(k , OurPolygon, PolygonAmount, output);
        cout << "That's all" << '\n';

        break;
    case 3:
        break;
    default:
        cout << "Incorrect! Try again" << '\n';
        submenu(OurPolygon, PolygonAmount, output);
        break;
    }
    return;
}



/// СЧИТАЕМ КООРДИНАТЫ
void coordinates(struct regular_polygon* reg_pol, int amount)
{
    long double Radius = reg_pol[amount].length / (2 * sin(M_PI / (reg_pol[amount].count_sides)));
    long double alpha = 2 * M_PI / reg_pol[amount].count_sides;

    if ((reg_pol[amount].x[0] > 0) && (reg_pol[amount].y[0] > 0))
    {
        long double phi = atan(reg_pol[amount].y[0]/reg_pol[amount].x[0]);
        long double Rx = Radius*cos(phi);
        long double Ry = Radius*sin(phi);
        long double O_x = reg_pol[amount].x[0] - Rx;
        long double O_y = reg_pol[amount].y[0] - Ry;
        for (int i = 1; i < reg_pol[amount].count_sides; i++)
        {
            reg_pol[amount].x[i] = O_x + Radius * cos(phi + i * alpha);
            reg_pol[amount].y[i] = O_y + Radius * sin(phi + i * alpha);
        }
    }
    else if ((reg_pol[amount].x[0] < 0) && (reg_pol[amount].y[0] < 0))
    {
        long double phi = atan(reg_pol[amount].y[0]/reg_pol[amount].x[0]);
        long double Rx = Radius*cos(phi);
        long double Ry = Radius*sin(phi);
        long double O_x = reg_pol[amount].x[0] + Rx;
        long double O_y = reg_pol[amount].y[0] + Ry;
        for (int i = 1; i < reg_pol[amount].count_sides; i++)
        {
            reg_pol[amount].x[i] = O_x - Radius * cos(phi + i * alpha);
            reg_pol[amount].y[i] = O_y - Radius * sin(phi + i * alpha);
        }
    }
    else if ((reg_pol[amount].x[0] < 0 ) && (reg_pol[amount].y[0] > 0))
    {
        long double phi = M_PI/2 + atan(reg_pol[amount].y[0]/reg_pol[amount].x[0]);
        long double Rx = Radius*cos(phi);
        long double Ry = Radius*sin(phi);
        long double O_x = reg_pol[amount].x[0] + Rx;
        long double O_y = reg_pol[amount].y[0] - Ry;
        for (int i = 1; i < reg_pol[amount].count_sides; i++)
        {
            reg_pol[amount].x[i] = O_x - Radius * cos(phi - i * alpha);
            reg_pol[amount].y[i] = O_y + Radius * sin(phi - i * alpha);
        }
    }
    else if ((reg_pol[amount].x[0] > 0) && (reg_pol[amount].y[0] < 0))
    {
        long double phi = M_PI/2 + atan(reg_pol[amount].y[0]/reg_pol[amount].x[0]);
        long double Rx = Radius*cos(phi);
        long double Ry = Radius*sin(phi);
        long double O_x = reg_pol[amount].x[0] - Rx;
        long double O_y = reg_pol[amount].y[0] + Ry;
        for (int i = 1; i < reg_pol[amount].count_sides; i++)
        {
            reg_pol[amount].x[i] = O_x + Radius * cos(phi - i * alpha);
            reg_pol[amount].y[i] = O_y - Radius * sin(phi - i * alpha);
        }
    }

    return;
}
void square_perimeter(int k ,struct regular_polygon* reg_pol, int amount, int* output)
{
    int i_max = 0;
    if (k == 1)
    {
        if (amount == 0) cout << "there are no polygons" << endl;
        else
        {

            for (int i = 0; i < amount; i++)
            {
                if (((reg_pol[i].square - reg_pol[i_max].square) > 0) && (output[i] == 1 )) i_max = i;
            }
            for (int i = i_max; i < amount; i++)
            {
                if (((reg_pol[i].square - reg_pol[i_max].square) == 0) && (output[i] == 1 ))
                {
                    cout << i + 1 << '\t';
                }
            }
            cout << endl;
        }
    }
    else if (k == 2)
    {
        if (amount == 0) cout << "there are no polygons" << endl;
        else
        {
            for (int i = 0; i < amount; i++)
            {
                if (((reg_pol[i].perimeter - reg_pol[i_max].perimeter) > 0) && (output[i] == 1 )) i_max = i;
            }
            for (int i = i_max; i < amount; i++)
            {
                if (((reg_pol[i].perimeter - reg_pol[i_max].perimeter) == 0) && (output[i] == 1 ))
                {
                    cout << i + 1 << '\t';
                }
            }
            cout << endl;
        }
    }

}
