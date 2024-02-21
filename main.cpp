#include <iostream>
#include <cmath>

using namespace std;

struct regular_polygon{
    int count_sides;
    double length;
    double square;
    double perimeter;
    double x, y;

} reg_pol;

void input(struct regular_polygon *reg_pol)
{
    cout << "Enter count of sides:"<<'\n';
    cin >> reg_pol->count_sides;

    cout << "Enter length of the side:"<<'\n';
    cin >> reg_pol->length;

    cout << "Enter vertex coordinates"<<'\n';

    cout << "Enter x:"<<'\n';
    cin >> reg_pol->x;

    cout << "Enter y:"<<'\n';
    cin >> reg_pol->y;
}

void square(struct regular_polygon *reg_pol)
{
    reg_pol->square = 0.25 * (double)reg_pol->count_sides * reg_pol->length * reg_pol->length * pow(tan(M_PI/((double)reg_pol->count_sides)), -1.0);
    cout << "Square = " << reg_pol->square << '\n';
}

void perimeter(struct regular_polygon *reg_pol)
{
    reg_pol->perimeter = reg_pol->count_sides * reg_pol->length;
    cout << "Perimeter = " << reg_pol->perimeter << '\n';
}


int main()
{
    regular_polygon *rg;
    rg = &reg_pol;
    input(rg);
    perimeter(rg);
    square(rg);
    double ang = ((reg_pol.count_sides - 2) * M_PI)/(reg_pol.count_sides);
    double R = reg_pol.length/(2 * sin(M_PI/(reg_pol.count_sides)));
    double xO = reg_pol.x + R;
    double yO = reg_pol.y;
    for (int i = 0; i < reg_pol.count_sides; i++)
    {
        x1 = xO + R * sin(i * ang);
        y1 = yO + R * cos(i * ang);
        i++;
        cout << "x" << x1 << i << '\n';
        cout << "y" << y1 << i << '\n';

    }
    return 0;
}
