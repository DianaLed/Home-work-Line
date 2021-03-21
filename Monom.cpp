#include "Monom.h"
#include "TItemValue.h"

TDatValue* TMonom::GetCopy()
{
  TDatValue* a = new TMonom(Coeff, Index);
  return a;
}