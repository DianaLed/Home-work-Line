#include <iostream>
#include "TDatList.h"
#include "TDatValue.h"
#include "TDatLink.h"
#include "TItemValue.h"
using namespace std;

#include "Polinom.h"

//void printList(TDatList& st)
//{
//  cout << st << " ";
//  cout << endl;
//}
//
//void main()
//{
//  setlocale(LC_ALL, "Russian");
//  cout << "������������ ������" << endl;
//  // ����������� --------------------------------------------
//  cout << "\n����������� --------------------------------------------" << endl;
//  int elemsCount = 5;
//  PTDatValue* listElems = new PTDatValue[elemsCount];
//  PTItemValue pVal;
//  for (int i = 0; i < elemsCount; i++)
//  {
//    pVal = new TItemValue(10 * i);
//    listElems[i] = pVal;
//  }
//  TDatList st(listElems, elemsCount);
//  // ������ ������
//  printList(st);
//  // �������� �������� ������
//  cout << "\n�������� �������� ������: 11 - � ������, 12 - � �����, 13 - ����� ������� ----" << endl;
//  st.Reset();
//  PTItemValue iVal1 = new TItemValue(11);
//  PTItemValue iVal2 = new TItemValue(12);
//  PTItemValue iVal3 = new TItemValue(13);
//  int cur2 = st.GetCurrentPos();
//  cout << "������� �������: " << cur2 << endl;
//  st.GoNext();
//  st.GoNext();
//
//  int cur1 = st.GetCurrentPos();
//  cout << "������� �������: " << cur1 << endl;
//  st.InsCurrent(iVal3);
//  cout << st.GetCurrentPos() << endl;
//  printList(st);
//  st.InsFirst(iVal1);
//  st.InsLast(iVal2);
//  printList(st);
//   //����� ������� ������� ������
//
//  cout << "\n����� ������� ������� ������ ------------------------------------------" << endl;
//  st.Reset();
//  st.GoNext();
//  st.GoNext();
//  int cur4 = st.GetCurrentPos();
//
//  cout << "������� �������: " << cur4 << endl;
//  PTItemValue iVal4 = (PTItemValue)(st.GetDatValue(CURRENT));
//  cout << "������� = " << iVal4->GetValue() << endl;
//  printList(st);
//  // ������� ������� ������
//  cout << "\n������� �������� ������: �������, ������ ----------------------------" << endl;
//  st.Reset();
//  st.GoNext();
//  st.GoNext();
//  int cur5 = st.GetCurrentPos();
//  cout << "������� �������: " << cur5 << endl;
//  st.DelCurrent();
//  st.DelFirst();
//  printList(st);
//  st.DelList();
//  cout << "����� ��������: \n" << st;
//
//}

void main()
{
  setlocale(LC_ALL, "Russian");
  cout << "������������ ���������" << endl;
  int ms1[][2] = { {1, 543}, {3, 432}, {5, 321}, {7, 210}, {9, 100} }; 
  int mn1 = sizeof(ms1) / (2 * sizeof(int));
  TPolinom p(ms1, mn1);

  cout << "1 �������" << endl << p << endl;

  TMonom a(5, 111);
  PTMonom b = &a;
  p.SetMonom(b);

  cout << "1 �������" << endl << p << endl;

  int ms2[][2] = { {2, 643}, {4, 432}, {-5, 321}, {8, 110}, {10, 50} };
  int mn2 = sizeof(ms2) / (2 * sizeof(int));
  TPolinom q(ms2, mn2);

  cout << "2 �������" << endl << q << endl;

  TPolinom r = p + q;
  /*cout << "�������-��������� + " << endl << r;*/
  /*TPolinom r1 = r;
  cout << "�������-��������� = " << endl << r1;
  TPolinom c(r);
  cout << "�������-����� = " << endl << c;*/
}