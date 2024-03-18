#include <iostream>
#include <string>
using namespace std;

void Print_Menu();

class transport 
{
private:
    int cnt_wheels;
    double mileage;
    double eng_capacity;
    double speed;
    double power;
    double consump;
    double massa;
    double time;
    double len;
    string name;
public:
    transport()
    {
        int cnt_wheels = 0;
        double mileage = 0;
        double eng_capacity = 0;
        double speed = 0;
        double power = 0;
        double consump = 0;
        double massa = 0;
        double time = 0;
        double len = 0;
        string name = " ";
        cout << "ТС создано" << endl;
    }

    void Inprint(int cnt)
    {
        for (int i = 0; i < cnt; i++)
        {
            cout << "Транспорт №" << i + 1 << endl;
            cout << "Название ТС: " << endl;
            cin >> name;
            cout << "Количество колёс (шт.):" << endl;
            cin >> cnt_wheels;
            cout << "Мощность двигателя (л. с.):" << endl;
            cin >> power;
            cout << "Объём двигателя (л):" << endl;
            cin >> eng_capacity;
            cout << "Пробег (км):" << endl;
            cin >> mileage;
            consump = 100 * eng_capacity / mileage;
            cout << "Потребление двигателя (л/км):" << consump << endl;
            cout << "Масса (кг):" << endl;
            cin >> massa;
            speed = power * 735.5 / (0.02 * massa);
            cout << "Скорость транспортного средства (м/c):" << speed << endl;
            cout << "Название: " << name << "\t" << "Количество колёс: " << cnt_wheels << "\t" << "Мощность: " << power << "\t" << "Потребление: " << consump << "\t" << "Скорость: " << speed << endl;
        }
    }

    //~transport()
    //{
    //    cout << "Тут сработал деструктор!" << endl;
    //}

    void len_route()
    {
        cout << "Введите длину маршрута: " << endl;
        cin >> len;  
    }
    
    void calc_len_route()
    {
        time = len / speed;
        cout << "Время: " << time << endl;
    }
};

void Print_Menu()
{
    cout << "-------------------------||МЕНЮ||--------------------------\n 1. Ввести и посмотреть данные о ТС\n 2. Ввести протяженность трассы\n 3. Произвести расчет прохождения трассы\n 4. Осуществить вывод результатов прохождения трассы\n 5. Выход\n" << endl;
}

int main()
{
    setlocale(LC_ALL, "ru");
    Print_Menu();
    int choose, cnt;
    cout << "Выберите номер пункта меню" << endl;


    do
    {
        cin >> choose;

        if (choose == 1)
        {
            cout << "Ввод и вывод данных о транспортных средствах (TC)\n" << endl;
            cout << "Введите количество транспортных средств:" << endl;
            cin >> cnt;
            transport TS;
            TS.Inprint(cnt);
            break;
        }
        if (choose == 2)
        {
            cout << "Ввод данных о протяженности трассы (TC)\n" << endl;
            transport TS;
            TS.len_route();
            break;
        }
        if (choose == 3)
        {
            cout << "Расчёт протяжённости трассы" << endl;
            transport TS;
            TS.calc_len_route();
            break;
        }
        if (choose == 4)
            system("pause");
    } while (choose != 4);
}



