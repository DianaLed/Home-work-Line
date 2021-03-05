#include "TDatList.h"


TDatList::TDatList()
{
  pFirst = pCurrLink= pPrevLink =pLast = pStop = NULL;
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
    for (int i = listElemsCount-2; i >=0; i--) {
      zven[i]->pNext = zven[i + 1];
    }
    ListLen = listElemsCount;
    CurrPos = 0;
    pFirst = zven[0];
    pLast= zven[listElemsCount - 1];
    pCurrLink = pFirst;
    pPrevLink = pLast;
  }
  else {
    pFirst = pCurrLink = pPrevLink = pLast = pStop = NULL;
    CurrPos = 0;
    ListLen = 0;
    cout << "ERROR in TDatList::TDatList(PTDatValue* listElems " << listElems[0] << "... int listElemsCount=";
    cout << listElemsCount << ".\n";
  }
}

PTDatValue TDatList::GetDatValue(TLinkPos mode) const
{
  PTDatValue a=pCurrLink->pValue;
  return a;
}

void TDatList::DelFirst(void)
{
  if (!IsEmpty()){
    if (ListLen >1) {
      Reset();
      GoNext();
      pFirst = pCurrLink;
      delete pPrevLink->pValue;
      //delete pPrevLink->pNext;
      ListLen--;
    }
    else {
      DelList();
    }
    }
  }

void TDatList::DelCurrent(void)
{
  if (!IsEmpty()) {
    if (CurrPos == ListLen - 1) {
      pLast = pPrevLink;
      delete pCurrLink->pValue;
      delete pCurrLink->pNext; //???
      pLast->pNext = NULL;
      ListLen--;
      Reset();
    }
    if (CurrPos == 1) DelFirst();
    else {
      pPrevLink->pNext = pCurrLink->pNext;
      delete pCurrLink->pValue;
      //delete pCurrLink->pNext; //???
      ListLen--;
    }
   
  }
}

void TDatList::DelList(void)
{
  Reset();
  if (ListLen > 1) { //если много звеньев
    for (int i = 1; i < ListLen; i++) {
      GoNext();
      delete pPrevLink->pValue;
    }
    delete pLast->pValue;
    delete pFirst->pNext;
  }
  else 
  if(ListLen==1)
  { //если одно звено
    delete pFirst->pValue;
    delete pFirst->pNext;
  }

  //Reset();
  //delete pFirst->pValue;
  //delete pFirst->pNext;
  ListLen = 0;
  CurrPos = 0;
}

int TDatList::SetCurrentPos(int pos)
{
  if (pos >= 0 && pos <= ListLen) { //если это реально сделать
    Reset();
  // нулевое звено
    while ((pos != CurrPos)&&(pCurrLink->pNext != NULL)) {
      pCurrLink = pCurrLink->GetNextDatLink();
      pPrevLink = pPrevLink->GetNextDatLink();
      CurrPos++;
    }
    return 1;
  }
  return 0;
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
  if(pCurrLink->pNext==NULL) return true;
  return false;
}

int TDatList::GoNext(void)
{
  if ((!IsListEnded())&&(!IsEmpty())) {
    PTDatLink next = pCurrLink->pNext; //???
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
  ListLen++;
}

void TDatList::InsLast(PTDatValue pVal)
{
  PTDatLink* zven = new PTDatLink;
  zven[0] = new TDatLink();
  zven[0]->pValue = pVal;
  zven[0]->pNext = NULL;
  pLast->pNext = zven[0];
  pLast = zven[0];
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
}



ostream& operator<<(ostream& os, TDatList& q)
{
  q.Reset();
  os << "Вывод адресов: ";
  while (q.GoNext()) {
    os << q.pCurrLink->GetDatValue() << "-> ";
  }
  os << "NULL\n";
  q.Reset();
  os << "Вывод значений: ";
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
