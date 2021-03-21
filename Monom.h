#pragma once
#include <iostream>
#include "tdatvalue.h"

using namespace std;
class TMonom;
typedef TMonom* PTMonom;
class TMonom : public TDatValue
{
protected:
  float Coeff; // коэффициент монома 
  int Index; // индекс (свертка степеней) 
public:
  TMonom(float cval = 1, int ival = 0) : Coeff(cval), Index(ival) { }
  virtual ~TMonom() { }
  virtual TDatValue* GetCopy(); // изготовить копию //???
  void SetCoeff(float cval) { Coeff = cval; }
  float GetCoeff(void) { return Coeff; }
  void SetIndex(int ival) { Index = ival; }
  int GetIndex(void) { return Index; }
  TMonom& operator=(const TMonom& tm)
  {
    Coeff = tm.Coeff;
    Index = tm.Index;
    return *this;
  }
  int operator==(const TMonom& tm)
  {
    return (Coeff == tm.Coeff) && (Index == tm.Index);
  }
  bool operator>(const TMonom& tm)
  {
    if(Index > tm.Index)
    return 1;
    return 0;
  }

  friend ostream& operator<<(ostream& os, TMonom& tm)
  {
    os << tm.Coeff << "(" << tm.Index << ")";
    return os;
  }

  friend class TPolinom;

};