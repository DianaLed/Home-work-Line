#include "TDatList.h"


TDatList::TDatList()
{
  pFirst = pCurrLink = pPrevLink = pLast = NULL;
  CurrPos = 0;
  ListLen = 0;
}

TDatList::TDatList(PTDatValue* listElems, int listElemsCount)
{
  if (listElemsCount > 0) {
    PTDatLink* zven;
    zven = new PTDatLink[listElemsCount];
    for (int i = 0; i < listElemsCount; i++) {
      zven[i] = new TDatLink();
      zven[i]->pValue = listElems[i];
    }
    zven[listElemsCount - 1]->pNext = NULL;
    for (int i = listElemsCount - 2; i >= 0; i--) {
      zven[i]->pNext = zven[i + 1];
    }
    ListLen = listElemsCount;
    CurrPos = 0;
    pFirst = zven[0];
    pLast = zven[listElemsCount - 1];
    pCurrLink = pFirst;
    pPrevLink = pLast;
  }
  else {
    pFirst = pCurrLink = pPrevLink = pLast = NULL;
    CurrPos = 0;
    ListLen = 0;
    cout << "ERROR in TDatList::TDatList(PTDatValue* listElems " << listElems[0] << "... int listElemsCount=";
    cout << listElemsCount << ".\n";
  }
}

PTDatValue TDatList::GetDatValue(TLinkPos mode) const
{
  PTDatValue a = (PTDatValue)pCurrLink->GetDatValue();
  return a;
}

void TDatList::DelFirst(void)
{
  if (!IsEmpty()) {
    if (ListLen == 1) {
      Reset();
      delete pCurrLink;
    }
    else {
      Reset();
      GoNext();
      pFirst = pCurrLink;
      delete pPrevLink;
      pPrevLink = pLast;
    }
      ListLen--;
  }
}

void TDatList::DelCurrent(void)
{
  if (!IsEmpty()) {
    if (CurrPos == 0) DelFirst();
    else
      if (CurrPos == ListLen - 1) {
        pLast = pPrevLink;
        delete pCurrLink->pNext;
        pCurrLink->pNext = NULL;
        pLast->pNext = NULL;
        ListLen--;
        Reset();
      }
      else {
        pPrevLink->pNext = pCurrLink->pNext;
        delete pCurrLink;
        pCurrLink = pPrevLink->pNext;
        ListLen--;
      }
  }
}

void TDatList::DelList(void)
{
  for (Reset(); !IsEmpty(); DelFirst()) {}
}

int TDatList::SetCurrentPos(int pos)
{
  int res = 0;
  if (pos >= 0 && pos <= ListLen) { //если это реально сделать
    Reset();
    // нулевое звено
    while ((pos != CurrPos) && (CurrPos <= ListLen)) {
      pPrevLink = pCurrLink;
      pCurrLink = pCurrLink->GetNextDatLink();
      CurrPos++;
      res = 1;
    }
  }
  return res;
}

int TDatList::GetCurrentPos(void) const
{
  return CurrPos;
}

int TDatList::Reset(void)
{
  pCurrLink = pFirst;
  pPrevLink = pLast;
  CurrPos = 0;
  return 0;
}

bool TDatList::IsListEnded(void) const
{
  if (CurrPos==ListLen-1)//(pCurrLink->pNext==NULL)
    return true;
  return false;
}

int TDatList::GoNext(void)
{
  if ((!IsListEnded()) && (!IsEmpty())) {
    PTDatLink next = pCurrLink->pNext;
    pPrevLink = pCurrLink;
    pCurrLink = next;
    CurrPos++;
    return 1;
  }
  return 0; //так как не получилось
}

void TDatList::InsFirst(PTDatValue pVal)
{
  PTDatLink* zven = new PTDatLink;
  zven[0] = new TDatLink();
  zven[0]->pValue = pVal;
  zven[0]->pNext = pFirst;
  pFirst = zven[0];
  pCurrLink = pFirst;
  pPrevLink = pLast;
  ListLen++;
}

void TDatList::InsLast(PTDatValue pVal)
{
  if (ListLen == 0) {
    PTDatLink* zven;
    zven = new PTDatLink[1];
    zven[0] = new TDatLink();
    zven[0]->pValue = pVal;
    zven[0]->pNext = NULL;
    CurrPos = 0;
    pFirst = zven[0];
    pLast = zven[0];
    pCurrLink = pFirst;
    pPrevLink = pLast;
  }
  else {
    PTDatLink zven = new TDatLink();
    //PTDatLink* zven = new PTDatLink;
    //*zven = new TDatLink();
    zven->pValue = pVal;
    zven->pNext = NULL;
    pLast->pNext= zven;
    pLast = zven;
  }
  ListLen++;
}

void TDatList::InsCurrent(PTDatValue pVal)// вставить перед текущим
{
  PTDatLink* zven = new PTDatLink;
  zven[0] = new TDatLink();
  zven[0]->pValue = pVal;
  zven[0]->pNext = pCurrLink;
  pPrevLink->pNext = zven[0];
  ListLen++;
  GoNext();
}

void TDatList::change(int nom1, int nom2)
{
  TDatLink a, b;
  SetCurrentPos(nom1);
  a = *pCurrLink;
  SetCurrentPos(nom2);
  b = *pCurrLink;
  pCurrLink->pValue = a.pValue;
  SetCurrentPos(nom1);
  pCurrLink->pValue = b.pValue;
}

ostream& operator<<(ostream& os, TDatList& q)
{
  q.Reset();
  os << "¬ывод адресов: ";
  while (q.GoNext()) {
    os << q.pCurrLink->GetDatValue() << "-> ";
  }
  os << "NULL\n";
  q.Reset();
  os << "¬ывод значений: ";
  if (q.ListLen > 0) {
    PTItemValue pVal;
    pVal = (PTItemValue)q.pCurrLink->GetDatValue();
    os << pVal->GetValue();
    while (q.GoNext()) {
      pVal = (PTItemValue)q.pCurrLink->GetDatValue();
      os << " -> " << pVal->GetValue();
    }
  }
  os << "\n";
  return os;
}
