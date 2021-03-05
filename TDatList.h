#pragma once
#include <iostream>

using namespace std;

#include "TDatlink.h"
#include "TItemValue.h"
enum TLinkPos { FIRST, CURRENT, LAST };
class TDatList;
typedef TDatList* PTDatList;
class TDatList
{
protected:
  PTDatLink pFirst; // ������ �����
  PTDatLink pLast; // ��������� �����
  PTDatLink pCurrLink; // ������� �����
  PTDatLink pPrevLink; // ����� ����� �������
  PTDatLink pStop; // �������� ���������, ����������� ����� ������ (=NULL) //� ��� �� ���������.
  int CurrPos; // ����� �������� ����� (��������� �� 0)
  int ListLen; // ���������� ������� � ������
public:


  TDatList();
  TDatList(PTDatValue* listElems, int listElemsCount);
  ~TDatList() { DelList(); }

  // ������ --------------------------------------------------------------
  PTDatValue GetDatValue(TLinkPos mode = CURRENT) const; // ��������
  int GetListLength() const { return ListLen; } // �-�� �������
  bool IsEmpty() const { return  (ListLen == 0); } // ������ ����?

  // ��������� ------------------------------------------------------------
  int SetCurrentPos(int pos); // ���������� ������� �����
  int GetCurrentPos(void) const; // �������� ����� �������� �����

  // �������� -------------------------------------------------------------
  int Reset(void); // ���������� �� ������ ������
  bool IsListEnded(void) const; // ������ ��������?
  // =true ����� ���������� GoNext
  // � ���������� ����� ������
  int GoNext(void); // ����� ������ �������� �����

  // ������� ������� ------------------------------------------------------
  void InsFirst(PTDatValue pVal = nullptr); // �������� ����� ������
  void InsLast(PTDatValue pVal = nullptr); // �������� ���������
  void InsCurrent(PTDatValue pVal = nullptr); // �������� ����� �������

  // �������� �������
  void DelFirst(void); // ������� ������ ����� (#�2)
  void DelCurrent(void); // ������� ������� ����� (#�2)
  void DelList(void); // ������� ���� ������

  friend ostream& operator<<(ostream& os, TDatList& q);
};