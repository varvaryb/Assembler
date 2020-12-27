// Задача 1 (5 вар.): указать те символы, которые есть и в первой и во второй строке.

#include <iostream>

int main()
{
    setlocale(0, "rus");
    const int N = 255;
    char res[N];
    char vvod1[] = "введите первую строку\n";
    char vvod2[] = "\nвведите вторую строку\n";
    char string[] = "\nЕще? Enter - да, ESC - выход\n";
    char ns[] = "Данные строки не имеют общих символов";
    char str1[N];
    char str2[N];
    __asm
    {
        // считываем строки
    BEGIN:
        lea     eax, vvod1      ; поместили в eax адрес на vvod1 
        push    eax     ; закинули eax в стэк для дальнейшего вывода 
        call    printf      ; вывели vvod1
        add     esp, 4      ; очистили стэк

        mov     eax, N
        push    eax
        lea     eax, str1
        push    eax 
        call    gets_s      ; считали строку str1 
        add     esp, 8

        lea     eax, vvod2
        push    eax
        call    printf      ; вывели vvod2
        add     esp, 4      ; очистили стэк

        mov     eax, N
        push    eax
        lea     eax, str2
        push    eax 
        call    gets_s      ; считали строку str2 
        add     esp, 8

        lea     edx, str2   ; сохранили адрес строки str2 
        lea     ebx, str1   ; сохранили адрес строки str1

        //  теперь нам надо посчитать количество совпавших элементов
        xor     eax, eax        ; обнуляем eax
        xor     edi, edi        ; в edi количество совпавших элементов

START:         ;внешний цикл

        xor     esi, esi        ; esi - текущий счетчик
        mov     cl, [ebx][eax]      ; положили в cl первый символ первой строки
        inc     eax     ; увеличили счетчик
        cmp     cl, 0       ; проверка конца строки
            je  NEW_RES     ; ушли на выделение памяти под результат

START2:
        mov ch, [edx][esi]      ; положили в ch следующий символ
        cmp     ch, 0       ; проверка конца строки
            je  END     ; ушли в обнуление текущего счетчика

        cmp     cl, ch      ; сравнили символы
        je      FOUND       ; если символы совпали - говорим нашли
        inc     esi     ; увеличили текущий счетчик
        jmp     START2

END:
            jmp START       ; возвращаемся в главный цикл

FOUND:
        inc     edi     ; увеличили счетчик совпавших символов
            jmp START       ; ушли в главный цикл
    
NEW_RES:
        cmp     edi, 0
            je  NOT_SOVP
        inc     edi     ; увеличили размер результатата под 0 символ
        push    edi     ; положили в eax размер результата
        mov     res, eax        ; записали адрес результата

        jmp     RES

NOT_SOVP:
        lea     eax, ns
        push    eax
        call    printf      ; вывели, что нет совпадений
        add     esp, 4
        // mov     eax, res
        xor     eax, eax
        xchg    res, eax
        xor     eax, eax
        jmp     REPEAT

RES:
        // lea     edx, str2       ; запомнили адрес первой строки, чтоб лишний раз не лазить в память
        // lea     ebx, str1       ; запомнили адрес первой строки, чтоб лишний раз не лазить в память
        // в еbx - адрес первой строки
        // в edx - адрес второй строки
        xor     ecx, ecx
        xor     eax, eax
        xor     edi, edi

START3:         ; внешний цикл

        xor     esi, esi        ; esi - текущий индекс второй строки
        mov     cl, [ebx][eax]      ; положили в cl первый символ первой строки
        inc     eax     ; увеличили счетчик
        cmp     cl, 0       ; проверка конца строки
            je  PRINT_RES       ; ушли на выделение памяти под результат

START4:
        mov     ch, [edx][esi]      ; положили в ch следующий символ
        cmp     ch, 0       ; проверка конца строки
            je  END1        ; ушли в обнуление текущего счетчика

        cmp     cl, ch      ; сравнили символы
        je      FOUND1      ; если символы совпали - говорим нашли
        inc     esi     ; увеличили текущий счетчик
        jmp     START4

END1:
            jmp START3      ; возвращаемся в главный цикл

FOUND1:

        xchg    esi, res
        //push  esi
        //mov       esi,res
        mov     [esi + edi], cl      ; на место res[edi] кладём совпавший символ
        xchg    esi, res
        //pop       esi
        inc     edi     ; увеличили счетчик совпавших символов
            jmp START3      ; ушли в главный цикл

PRINT_RES:
        //inc       edi
        //xor       eax,eax
        lea     esi, res
        xor     cl, cl
        mov     [esi + edi], cl

        push    esi
        call    printf
        add     esp, 4

REPEAT:
        lea     eax, str1
        push    eax
        call dword ptr free
        add     esp, 4
        lea     eax, str2
        push    eax
        call dword ptr free
        add     esp, 4
        lea     eax, res

        cmp     eax, 0

        je      NEXT
        push    eax
        call dword ptr free
        add     esp, 4

NEXT:
        lea     eax, string
        push    eax
        call    printf
        add     esp, 4

        call dword ptr getch        ; смотрим, что нажали
        cmp     eax, 27
        je      EXIT
        cmp     eax, 13
        je      BEGIN
        jmp     BEGIN

EXIT:
    }
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
