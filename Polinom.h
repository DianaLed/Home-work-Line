#pragma once
#include "tdatlist.h"
#include "monom.h"

class TPolinom : public TDatList
{
public:
  TPolinom(int monoms[][2] = nullptr, int km = 0);
  TPolinom(TPolinom& q); // ����������� �����������
  TPolinom& operator+(TPolinom& q); // �������� ���������
  TPolinom& operator=(TPolinom& q); // ������������
  PTMonom GetMonom() { return (PTMonom)GetDatValue(); }
  void sortPolinm();
  void SetMonom(PTMonom a) { InsLast(a); } 
  friend ostream& operator<<(ostream& os, TPolinom& q);
};