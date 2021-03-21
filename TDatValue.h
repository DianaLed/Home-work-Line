#pragma once

class TDatValue
{
public:
  virtual TDatValue* GetCopy() = 0; // создание копии
  //virtual bool operator> (const TDatValue& d) = 0; // создание копии
  virtual ~TDatValue() { }
};
typedef TDatValue* PTDatValue;