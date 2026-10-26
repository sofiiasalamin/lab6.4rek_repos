#include <iostream>   // підключаємо введення/виведення: cin, cout, cerr, endl
#include <iomanip>    // підключаємо маніпулятори форматування: setw, fixed, setprecision
#include <cstdlib>    // підключаємо rand() і srand() для випадкових чисел
#include <ctime>      // підключаємо time() для початкового значення генератора
#include <windows.h>  // підключаємо функції WinAPI (SetConsoleOutputCP, SetConsoleCP)
using namespace std;  // щоб писати cout замість std::cout

// Заповнення масиву випадковими числами з [Low; High] з кроком 0.5
void Create(double* a, const int size, const int Low, const int High, int i)
{                                                    // початок тіла функції
    a[i] = (2 * Low + rand() % (2 * (High - Low) + 1)) / 2.0;
    // rand() % (2*(High-Low)+1) дає ціле від 0 до 2*(High-Low);
    // додаємо 2*Low і ділимо на 2.0 -> число від Low до High з кроком 0.5
    if (i < size - 1)                                // якщо поточний елемент не останній
        Create(a, size, Low, High, i + 1);           // рекурсія: заповнюємо наступний елемент
}                                                    // кінець функції (інакше рекурсія завершується)

// Виведення масиву в один рядок
void Print(double* a, const int size, int i)
{
    cout << setw(7) << a[i];                         // виводимо a[i], відводячи під нього 7 позицій
    if (i < size - 1)                                // якщо це не останній елемент
        Print(a, size, i + 1);                       // рекурсія: виводимо наступний
    else                                             // інакше (це останній елемент)
        cout << endl;                                // переходимо на новий рядок
}

// 1.1. Мінімальний елемент; виклик: Min(a, size, 1, a[0])
double Min(double* a, const int size, int i, double min)
{
    if (i >= size)                                   // базовий випадок: масив закінчився
        return min;                                  // повертаємо знайдений мінімум
    if (a[i] < min)                                  // якщо поточний елемент менший за мінімум
        min = a[i];                                  // запам'ятовуємо його як новий мінімум
    return Min(a, size, i + 1, min);                 // рекурсія: перевіряємо наступний елемент
}

// Індекс першого додатного елемента (-1, якщо немає)
int IFirstPositive(double* a, const int size, int i)
{
    if (i >= size)                                   // базовий випадок: дійшли до кінця масиву
        return -1;                                   // додатного не знайдено
    if (a[i] > 0)                                    // якщо елемент додатний
        return i;                                    // повертаємо його індекс (це перший)
    return IFirstPositive(a, size, i + 1);           // рекурсія: шукаємо далі вправо
}

// Індекс останнього додатного елемента (-1, якщо немає)
int ILastPositive(double* a, int i)
{
    if (i < 0)                                       // базовий випадок: вийшли за лівий край
        return -1;                                   // додатного не знайдено
    if (a[i] > 0)                                    // якщо елемент додатний
        return i;                                    // повертаємо індекс (йдемо з кінця, тож він останній)
    return ILastPositive(a, i - 1);                  // рекурсія: крок на один елемент вліво
}

// Сума елементів з індексами від i до to-1 (to не входить)
double SumRange(double* a, int i, const int to)
{
    if (i >= to)                                     // базовий випадок: діапазон закінчився
        return 0;                                    // сума порожнього діапазону = 0
    return a[i] + SumRange(a, i + 1, to);            // поточний елемент + сума решти діапазону
}

// Зсув елементів a[from..to-1] на одну позицію вправо
void ShiftRight(double* a, const int from, const int to)
{
    if (to > from)                                   // поки є що зсувати
    {
        a[to] = a[to - 1];                           // копіюємо лівого сусіда на місце a[to]
        ShiftRight(a, from, to - 1);                 // рекурсія: переходимо на крок вліво
    }
}

// 2. Спочатку всі нулі, потім решта; виклик: MoveZerosToFront(a, size, 0, 0)
void MoveZerosToFront(double* a, const int size, int i, int z)
{
    if (i >= size)                                   // базовий випадок: усі елементи розглянуто
        return;                                      // завершуємо рекурсію
    if (a[i] == 0)                                   // якщо поточний елемент - нуль
    {
        ShiftRight(a, z, i);                         // зсуваємо a[z..i-1] вправо, звільняючи місце a[z]
        a[z] = 0;                                    // ставимо нуль на позицію z
        MoveZerosToFront(a, size, i + 1, z + 1);     // далі; нулів на початку стало на один більше
    }
    else                                             // якщо елемент не нуль
        MoveZerosToFront(a, size, i + 1, z);         // просто йдемо далі, z не змінюється
}

// =====================================================================
// ЧАСТИНА 2. Шаблони тих самих функцій (тип елементів T)
// =====================================================================

template <typename T>                                // оголошення шаблону: T - довільний тип
void Create(T* a, const int size, const int Low, const int High, int i)
{
    a[i] = static_cast<T>(Low + rand() % (High - Low + 1));
    // випадкове ціле від Low до High, перетворене до типу T
    if (i < size - 1)                                // якщо не останній елемент
        Create<T>(a, size, Low, High, i + 1);        // рекурсія для наступного
}

template <typename T>
void Print(T* a, const int size, int i)
{
    cout << setw(7) << a[i];                         // виводимо елемент у полі шириною 7
    if (i < size - 1)                                // якщо не останній
        Print<T>(a, size, i + 1);                    // рекурсія: наступний елемент
    else
        cout << endl;                                // після останнього - новий рядок
}

template <typename T>
T Min(T* a, const int size, int i, T min)
{
    if (i >= size)                                   // масив закінчився
        return min;                                  // повертаємо мінімум
    if (a[i] < min)                                  // знайшли менший елемент
        min = a[i];                                  // оновлюємо мінімум
    return Min<T>(a, size, i + 1, min);              // рекурсія: наступний елемент
}

template <typename T>
int IFirstPositive(T* a, const int size, int i)
{
    if (i >= size)                                   // дійшли до кінця
        return -1;                                   // додатних немає
    if (a[i] > 0)                                    // знайшли додатний
        return i;                                    // повертаємо його індекс
    return IFirstPositive<T>(a, size, i + 1);        // шукаємо далі
}

template <typename T>
int ILastPositive(T* a, int i)
{
    if (i < 0)                                       // вийшли за лівий край
        return -1;                                   // додатних немає
    if (a[i] > 0)                                    // знайшли додатний (з кінця)
        return i;                                    // повертаємо індекс
    return ILastPositive<T>(a, i - 1);               // крок вліво
}

template <typename T>
T SumRange(T* a, int i, const int to)
{
    if (i >= to)                                     // діапазон закінчився
        return T();                                  // T() - нуль типу T (для int це 0)
    return a[i] + SumRange<T>(a, i + 1, to);         // поточний + сума решти
}

template <typename T>
void ShiftRight(T* a, const int from, const int to)
{
    if (to > from)                                   // поки є що зсувати
    {
        a[to] = a[to - 1];                           // копіюємо лівого сусіда вправо
        ShiftRight<T>(a, from, to - 1);              // рекурсія: крок вліво
    }
}

template <typename T>
void MoveZerosToFront(T* a, const int size, int i, int z)
{
    if (i >= size)                                   // усі елементи розглянуто
        return;                                      // кінець рекурсії
    if (a[i] == 0)                                   // знайшли нуль
    {
        ShiftRight<T>(a, z, i);                      // звільняємо місце на позиції z
        a[z] = 0;                                    // ставимо туди нуль
        MoveZerosToFront<T>(a, size, i + 1, z + 1);  // далі, нулів на початку на один більше
    }
    else
        MoveZerosToFront<T>(a, size, i + 1, z);      // не нуль - йдемо далі
}

// =====================================================================
// ГОЛОВНА ФУНКЦІЯ
// =====================================================================
int main()
{
    SetConsoleOutputCP(65001);                       // консоль виводить текст у UTF-8 (кирилиця)
    SetConsoleCP(65001);                             // консоль приймає введення в UTF-8
    srand((unsigned)time(NULL));                     // генератор випадкових чисел стартує від поточного часу
    cout << fixed << setprecision(1);                // дійсні числа - у фіксованому форматі з 1 цифрою після коми

    int n;                                           // розмір масиву
    cout << "Введіть n = "; cin >> n;                // просимо ввести n і зчитуємо його
    if (n <= 0)                                      // перевіряємо, що n додатне
    {
        cerr << "n має бути додатним числом" << endl;// виводимо повідомлення про помилку
        return 1;                                    // завершуємо програму з кодом помилки 1
    }

    const int Low = -5, High = 5;                    // межі діапазону випадкових чисел: [-5; 5]

    // ===== 1) Звичайні функції, масив double =====
    cout << endl << "--- звичайні рекурсивні функції (double) ---" << endl;  // заголовок розділу
    double* a = new double[n];                       // виділяємо динамічну пам'ять під n дійсних чисел

    Create(a, n, Low, High, 0);                      // заповнюємо масив, починаючи з індексу 0
    cout << "Початковий масив:" << endl;             // підпис перед масивом
    Print(a, n, 0);                                  // виводимо масив

    cout << "1.1 мінімальний елемент = " << Min(a, n, 1, a[0]) << endl;
    // шукаємо мінімум: починаємо з індексу 1, початковий мінімум - a[0]

    int first = IFirstPositive(a, n, 0);             // індекс першого додатного елемента
    int last = ILastPositive(a, n - 1);              // індекс останнього додатного (старт з кінця)
    if (first == -1 || first == last)                // додатних немає, або він лише один
        cout << "1.2 додатних елементів менше двох" << endl;   // "між ними" рахувати нічого
    else                                             // інакше є хоча б два додатні
        cout << "1.2 сума між першим і останнім додатними = " << SumRange(a, first + 1, last) << endl;
    // сумуємо від first+1 до last-1, самі додатні межі не входять

    MoveZerosToFront(a, n, 0, 0);                    // переставляємо нулі на початок масиву
    cout << "2. Після перетворення (спочатку нулі):" << endl;  // підпис
    Print(a, n, 0);                                  // виводимо перетворений масив

    delete[] a;                                      // звільняємо пам'ять масиву a

    // ===== 2) Шаблони, масив int =====
    cout << endl << "--- шаблони рекурсивних функцій (int) ---" << endl;  // заголовок розділу
    int* b = new int[n];                             // виділяємо пам'ять під n цілих чисел

    Create<int>(b, n, Low, High, 0);                 // заповнюємо масив (шаблон з типом int)
    cout << "Початковий масив:" << endl;             // підпис
    Print<int>(b, n, 0);                             // виводимо масив

    cout << "1.1 мінімальний елемент = " << Min<int>(b, n, 1, b[0]) << endl;  // мінімум

    first = IFirstPositive<int>(b, n, 0);            // індекс першого додатного (змінну використовуємо повторно)
    last = ILastPositive<int>(b, n - 1);             // індекс останнього додатного
    if (first == -1 || first == last)                // додатних менше двох
        cout << "1.2 додатних елементів менше двох" << endl;
    else
        cout << "1.2 сума між першим і останнім додатними = " << SumRange<int>(b, first + 1, last) << endl;

    MoveZerosToFront<int>(b, n, 0, 0);               // нулі - на початок
    cout << "2. Після перетворення (спочатку нулі):" << endl;  // підпис
    Print<int>(b, n, 0);                             // виводимо результат

    delete[] b;                                      // звільняємо пам'ять масиву b

    return 0;                                        // програма завершилась успішно
}