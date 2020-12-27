﻿/* Второе задание. Вычисление функции разложением в ряд Тейлора.
Вычислить значение функции f, которая указана в задании, в точке x, используя разложение в ряд Тейлора.
Суммирование выполнять до тех пор, пока общий член ряда не будет меньше, по модулю, заданного параметра epsilon.
Решение оформить в виде функции double имя_функции(double x, double epsilon = 1e-5);
5. exp(x)
*/

#include <iostream>

double Teulor(double x, double epsilon = 1e-5)
{
    __asm
    {
        fld1                ; 4 - Sum, /загрузили в стэк единицу/
        fld     epsilon     ; 3 - epsilon, /загрузили epsilon/
        fld     x           ; 2 - x, /загрузили x/
        fld1                ; 1 - i, /загрузили 1/
        fld     st(1)       ; 0 - Xi

    START:
        fadd    st(4), st(0)    ; Sum += Xi
        fld1                    ; st(0) = 1, st(2) = i
        faddp   st(2), st(0)    ; i++, /увеличили i и вытолкнули вершину стэка, в кот. была 1/
        fmul    st(0), st(2)    ; Xi *= x
        fdiv    st(0), st(1)    ; Xi /= i
        fld     st(0)           ; Xi
        fabs                    ; abs(Xi), /модуль Xi/
        fcomip  st(0), st(4)    ; while (abs(Xi) > epsilon), /сравниваем и выталкиваем вершину/ 
        jnbe START              ; возвращаемся к началу, если abs(Xi)>epsilon 

        fstp st(0)              ; выталкиваем i
        fstp st(0)              ; выталкиваем x
        fstp st(0)              ; выталкиваем epsilon 
        fstp st(0)              ; выталкиваем Sum, и она выводится при вызове функции  
    }
}

int main()
{
    std::cout << Teulor(1) << std::endl;

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.