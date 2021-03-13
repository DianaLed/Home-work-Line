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
  bool operator>(const TDatValue& tm) //пергрузка оператора сравнения для производного класса
  {
    const TDatValue* pTM = &tm;
    const TMonom* pTM2 = reinterpret_cast<const TMonom*>(pTM);
    return Index > pTM2->Index;
  }

  friend ostream& operator<<(ostream& os, TMonom& tm)
  {
    os << tm.Coeff << "(" << tm.Index << ")";
    return os;
  }

  friend class TPolinom;

};