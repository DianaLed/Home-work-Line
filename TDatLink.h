#pragma once
#include "TDatvalue.h"
class TDatLink;
typedef TDatLink* PTDatLink;
class TDatLink
{
protected:
  PTDatValue pValue; // указатель на объект значения 2 3
  PTDatLink pNext; // указатель на следующее звено
public:
  TDatLink(PTDatValue pVal = nullptr, PTDatLink pN = nullptr): pNext(pN), pValue(pVal) { }
  void SetDatValue(PTDatValue pVal) { pValue = pVal; }
  PTDatValue GetDatValue() { return pValue; }
  PTDatLink GetNextDatLink() { return (PTDatLink)pNext; } //в чем разница?
  PTDatLink GetNextLink() { return pNext; }               //
  void SetNextLink(PTDatLink pLink) { pNext = pLink; }
  void InsNextLink(PTDatLink pLink)
  {
    PTDatLink p = pNext;
    pNext = pLink;
    if (pLink != nullptr)
      pLink->pNext = p;
  }
  TDatLink& operator= (const TDatLink& p)
  {
    pValue = p.pValue;
    pNext = p.pNext;
    return *this;
  }
  bool operator> (const TDatLink& p)
  {
    if (*pValue > *p.pValue) return true;
    return 0;
  }
  friend class TDatList;
};
