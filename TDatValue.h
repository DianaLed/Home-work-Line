#pragma once

class TDatValue
{
public:
  virtual TDatValue* GetCopy() = 0; // �������� �����
  //virtual bool operator> (const TDatValue& d) = 0; // �������� �����
  virtual ~TDatValue() { }
};
typedef TDatValue* PTDatValue;