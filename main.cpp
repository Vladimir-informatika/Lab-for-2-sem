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




int main()
{
    regular_polygon *rg;
    rg = &reg_pol;
    input(rg);
    return 0;
}
