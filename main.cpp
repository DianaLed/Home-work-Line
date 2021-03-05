#include <iostream>
#include "TDatList.h"
#include "TDatValue.h"
#include "TDatLink.h"
#include "TItemValue.h"
using namespace std;

void printList(TDatList& st)
{
  cout << st << " ";
  cout << endl;
}

void main()
{
  setlocale(LC_ALL, "Russian");
  cout << "Тестирование списка" << endl;
  // Конструктор --------------------------------------------
  cout << "\nКонструктор --------------------------------------------" << endl;
  int elemsCount = 5;
  PTDatValue* listElems = new PTDatValue[elemsCount];
  PTItemValue pVal;
  for (int i = 0; i < elemsCount; i++)
  {
    pVal = new TItemValue(10 * i);
    listElems[i] = pVal;
  }
  TDatList st(listElems, elemsCount);
  // печать списка
  printList(st);
  // Вставить элементы списка
  cout << "\nВставить элементы списка: 11 - в начало, 12 - в конец, 13 - перед текущим ----" << endl;
  st.Reset();
  PTItemValue iVal1 = new TItemValue(11);
  PTItemValue iVal2 = new TItemValue(12);
  PTItemValue iVal3 = new TItemValue(13);
  int cur2 = st.GetCurrentPos();
  cout << "Текущий элемент: " << cur2 << endl;
  st.GoNext();
  st.GoNext();

  int cur1 = st.GetCurrentPos();
  cout << "Текущий элемент: " << cur1 << endl;
  st.InsCurrent(iVal3);
 /* st.InsFirst(iVal1);
  st.InsLast(iVal2);
  printList(st);*/
  // Взять текущий элемент списка

  //cout << "\nВзять текущий элемент списка ------------------------------------------" << endl;
  //st.Reset();
  //st.GoNext();
  //st.GoNext();
  //int cur4 = st.GetCurrentPos();

  //cout << "Текущий элемент: " << cur4 << endl;
  //PTItemValue iVal4 = (PTItemValue)(st.GetDatValue(CURRENT));
  //cout << "Элемент = " << iVal4->GetValue() << endl;
  //printList(st);
  //// Удалить элемент списка
  //cout << "\nУдалить элементы списка: текущий, первый ----------------------------" << endl;
  //st.Reset();
  //st.GoNext();
  //st.GoNext();
  //int cur5 = st.GetCurrentPos();
  //cout << "Текущий элемент: " << cur5 << endl;
  //st.DelCurrent();
  //st.DelFirst();
  //printList(st);
}

//#include <iostream>
//#include "TDatList.h"
//#include "TDatValue.h"
//#include "TDatLink.h"
//#include "TItemValue.h"
//
//using namespace std;
//
//void main()
//{
//  int b = 9;
//  TItemValue a1(b);
//  PTDatList ptd(a1, 1);
//  system("pause");
//}