#pragma once
#include <iostream>

#include "TDatvalue.h"

using namespace std;

class TItemValue;

typedef TItemValue* PTItemValue; //указатель на класс

class TItemValue : public TDatValue
{
protected:
  int Value; // значение
public:
  TItemValue(int ival = 0) : Value(ival) { }
  virtual ~TItemValue() { }
  virtual TDatValue* GetCopy() // изготовить копию
  { 
    TDatValue* temp = new TItemValue(Value);
    return temp;
  }
  void SetValue(int ival) { Value = ival; }
  int GetValue(void) { return Value; }

  TItemValue& operator=(const TItemValue& tm)
  {
    Value = tm.Value;
    return *this;
  }
  int operator==(const TItemValue& tm)
  {
    return (Value == tm.Value);
  }
  int operator<(const TItemValue& tm)
  {
    return Value < tm.Value;
  }
  friend ostream& operator<<(ostream& os, TItemValue& tm)
  {
    os << tm.Value;
    return os;
  }
};
