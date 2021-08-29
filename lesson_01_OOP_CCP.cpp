//============================================================================
// Name        : lesson_01_OOP_CPP.cpp
// Author      : andry antonenko
// IDE         : Qt Creator 4.14.2 based on Qt 5.15.2
// Description : lesson 01 of the object-oriented programming on C++ course
//============================================================================

#include <QCoreApplication>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <cmath>
#include <chrono>

using namespace std;
//----------------------------------------------------------------------------
//#define NDEBUG
#include <cassert>
//----------------------------------------------------------------------------
int getRandomNum(int min, int max)
{
  const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::mt19937_64 generator(seed);
  std::uniform_int_distribution<int> dis(min, max);
  return dis(generator);
}
//----------------------------------------------------------------------------
/*
1. Создать класс Power, который содержит два вещественных числа.
Этот класс должен иметь две переменные-члена
для хранения этих вещественных чисел.
Еще создать два метода: один с именем set,
который позволит присваивать значения переменным,
второй — calculate, который будет выводить
результат возведения первого числа в степень второго числа.
Задать значения этих двух чисел по умолчанию.
//*/

class Power
{
  double a,b;
public:
  Power(double aA = 0, double aB = 0)
    :a(aA),b(aB){};

  void set(double aA, double aB)
  {
    a = aA;
    b = aB;
  }

  double calculate()
  {
    return pow(a,b);
  }
};

/*
2. Написать класс с именем RGBA,
который содержит 4 переменные-члена типа
std::uint8_t: m_red, m_green, m_blue и m_alpha
(#include cstdint для доступа к этому типу).
Задать 0 в качестве значения по умолчанию для
m_red, m_green, m_blue и 255 для m_alpha.
Создать конструктор со списком инициализации членов,
который позволит пользователю передавать значения для
m_red, m_blue, m_green и m_alpha.
Написать функцию print(), которая будет выводить значения переменных-членов.
*/

class RGBA
{
  std::uint8_t m_red, m_green, m_blue, m_alpha;

public:
  RGBA()
    : m_red(0),m_green(0),m_blue(0),m_alpha(255)
  {}
  RGBA(std::uint8_t a_red,
       std::uint8_t a_green,
       std::uint8_t a_blue,
       std::uint8_t a_alpha)
    : m_red(a_red),m_green(a_green),m_blue(a_blue),m_alpha(a_alpha)
  {}
  void print()
  {
    cout << "m_red = " << (int)m_red;
    cout << " m_green = " << (int)m_green;
    cout << " m_blue = " << (int)m_blue;
    cout << " m_alpha = " << (int)m_alpha << endl;
  }
};

/*
3. Написать класс, который реализует функциональность стека. Класс Stack должен иметь:
        ◦ private-массив целых чисел длиной 10;
        ◦ private целочисленное значение для отслеживания длины стека;
        ◦ public-метод с именем reset(), который будет сбрасывать длину и все значения элементов на 0;
        ◦ public-метод с именем push(), который будет добавлять значение в стек.
push() должен возвращать значение false, если массив уже заполнен, и true в противном случае;
        ◦ public-метод с именем pop() для вытягивания и возврата значения из стека.
Если в стеке нет значений, то должно выводиться предупреждение;
        ◦ public-метод с именем print(), который будет выводить все значения стека.
//*/

enum Status
{
  STACK_OK,
  STACK_OVERFLOW,
  STACK_EMPTY
};

class Stack
{
  vector<int> mas;
  size_t cnt;
  const size_t SIZE;

public:
  Stack(const size_t aSize = 10)
    : cnt(0), SIZE(aSize)
  {
    assert(aSize > 0);

    mas.resize(aSize);
  }

  ~Stack() {}

  void reset()
  {
    cnt = 0;
    for(size_t i = 0; i < SIZE; i++)
      mas[i] = 0;
  }
  Status push(const int d)
  {
    if(cnt == SIZE) return STACK_OVERFLOW;
    mas[cnt++] = d;
    return STACK_OK;
  }
  int pop(Status &status)
  {
    if(cnt == 0)
    {
      status = STACK_EMPTY;
      return 0;
    }
    status = STACK_OK;
    return mas[--cnt];
  }
  void print()
  {
    if(cnt == 0)
    {
      cout << "Stack is empty.";
      return;
    }
    for(size_t i = 0; i < cnt; i++)
    {
      cout << mas[i] << " ";
    }
    cout << endl;
  }
};

//----------------------------------------------------------------------------
void task_1()
{
  cout << "Task 1\n" << endl;

  Power p;

  const double MIN_A = -5;
  const double MAX_A = 5;
  const double STEP_A = 1;
  const double MIN_B = -3;
  const double MAX_B = 3;
  const double STEP_B = 2;

  for(double b = MIN_B; b < MAX_B; b += STEP_B)
  {
    for(double a = MIN_A; a < MAX_A; a += STEP_A)
    {
      p.set(a,b);
      cout << "Number A = " << a << " to degree B = " << b << " equal " << p.calculate() << endl;
    }
  }
  cout << endl;
}
//----------------------------------------------------------------------------
void task_2()
{
  cout << "Task 2\n" << endl;

  const uint8_t MIN = 0;
  const uint8_t MAX = 255;
  const uint8_t STEP = 100;

  for(int r = MIN; r <= MAX; r += STEP)
  {
    for(int g = MIN; g <= MAX; g += STEP)
    {
      for(int b = MIN; b <= MAX; b += STEP)
      {
        for(int a = MIN; a <= MAX; a += STEP)
        {
          RGBA rgba(r,g,b,a);
          rgba.print();
        }
      }
    }
  }
  cout << endl;
}
//----------------------------------------------------------------------------
void task_3()
{
  cout << "Task 3\n" << endl;

  Status st = STACK_OK;

  const size_t SIZE = 10;
  Stack stack(SIZE);

  const int MIN = -100;
  const int MAX = 100;

  cout << "Size of a stack equals " << SIZE << endl;

  //Test 1
  cout << "Test 1\n" << endl;
  int AMOUND = 8;

  cout << "Push " << AMOUND << " of numbers:" << endl;
  for(int i = 0; i < AMOUND; i++)
  {
    st = stack.push(getRandomNum(MIN,MAX));
    if(st == STACK_OVERFLOW)
    {
      cout << "STACK_OVERFLOW" << endl;
    }
  }
  stack.print();
  cout << "Pop one number " << stack.pop(st);
  cout << " of numbers (Status is " << st << "):" << endl;
  stack.print();
  stack.reset();
  cout << "Reset stack:" << endl;
  stack.print();

  //Test 2
  cout << "\nTest 2\n" << endl;
  AMOUND = 13;

  cout << "Push " << AMOUND << " of numbers:" << endl;
  for(int i = 0; i < AMOUND; i++)
  {
    st = stack.push(getRandomNum(MIN,MAX));
    if(st == STACK_OVERFLOW)
    {
      cout << "STACK_OVERFLOW (Status is " << st << ")" << endl;
    }
  }
  stack.print();
  cout << "Pop one number " << stack.pop(st);
  cout << " of numbers (Status is " << st << "):" << endl;
  stack.reset();

  //Test 3
  cout << "\nTest 3\n" << endl;
  AMOUND = 3;

  cout << "Push " << AMOUND << " of numbers:" << endl;
  for(int i = 0; i < AMOUND; i++)
  {
    st = stack.push(getRandomNum(MIN,MAX));
    if(st == STACK_OVERFLOW)
      cout << "STACK_OVERFLOW" << endl;
  }
  stack.print();

  AMOUND = 5;
  cout << "Pop " << AMOUND << " of numbers:" << endl;
  for(int i = 0; i < AMOUND; i++)
  {
    int d = stack.pop(st);
    if(st == STACK_EMPTY)
      cout << "\nSTACK_EMPTY (Status is " << st << ")" << endl;
    else
      cout << d << " ";
  }
  stack.reset();

  cout << endl;
}
//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  //----------------------------------------------------------------------------
  // Task 1
  //*
  task_1();
  //*/
  //----------------------------------------------------------------------------
  // Task 2
  //*
  task_2();
  //*/
  //----------------------------------------------------------------------------
  // Task 3
  //*
  task_3();
  //*/
  //----------------------------------------------------------------------------
  return a.exec();
}
