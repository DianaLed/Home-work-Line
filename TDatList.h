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
  PTDatLink pFirst; // первое звено
  PTDatLink pLast; // последнее звено
  PTDatLink pCurrLink; // текущее звено
  PTDatLink pPrevLink; // звено перед текущим
  PTDatLink pStop; // значение указателя, означающего конец списка (=NULL) //Я его не использую.
  int CurrPos; // номер текущего знена (нумерация от 0)
  int ListLen; // количество звеньев в списке
public:


  TDatList();
  TDatList(PTDatValue* listElems, int listElemsCount);
  ~TDatList() { DelList(); }

  // доступ --------------------------------------------------------------
  PTDatValue GetDatValue(TLinkPos mode = CURRENT) const; // значение
  int GetListLength() const { return ListLen; } // к-во звеньев
  bool IsEmpty() const { return  (ListLen == 0); } // список пуст?

  // навигация ------------------------------------------------------------
  int SetCurrentPos(int pos); // установить текущее звено
  int GetCurrentPos(void) const; // получить номер текущего звена

  // итератор -------------------------------------------------------------
  int Reset(void); // установить на начало списка
  bool IsListEnded(void) const; // список завершен?
  // =true после применения GoNext
  // к последнему звену списка
  int GoNext(void); // сдвиг вправо текущего звена

  // вставка звеньев ------------------------------------------------------
  void InsFirst(PTDatValue pVal = nullptr); // вставить перед первым
  void InsLast(PTDatValue pVal = nullptr); // вставить последним
  void InsCurrent(PTDatValue pVal = nullptr); // вставить перед текущим

  // удаление звеньев
  void DelFirst(void); // удалить первое звено (#Л2)
  void DelCurrent(void); // удалить текущее звено (#П2)
  void DelList(void); // удалить весь список

  friend ostream& operator<<(ostream& os, TDatList& q);
};