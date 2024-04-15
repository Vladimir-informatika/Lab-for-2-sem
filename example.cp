#include <iostream>
#include <cmath>
using namespace std;

double calculateArea(double radius) {
    return  M_PI * radius * radius; // Площадь круга
}

double calculateArea(double length, double width) {
    return length * width; // Площадь прямоугольника
}

double calculateArea(double side1, double side2, double side3) {
    double s = (side1 + side2 + side3) / 2;
    return sqrt(s * (s - side1) * (s - side2) * (s - side3)); // площадь треугольника
}

int main() {
    cout << "Площадь круга: " << calculateArea(5.0) <<endl;
    cout << "Площадь прямоугольника: " << calculateArea(4.0, 6.0) << endl;
    cout << "Площадь треугольника: " << calculateArea(3.0, 4.0, 5.0) <<endl;

    return 0;
}
