#include "TDatList.h"

void TDatList::DelLink(PTDatLink pLink)
{

}

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
    SetCurrentPos(1);
    PTDatLink* zn = new PTDatLink[ListLen - 1];
    for (int i = 0; i < ListLen - 2; i++) {
      zn[i] = pCurrLink;
      GoNext();
    }
    SetCurrentPos(0);
    delete[] pFirst->pNext; //вроде как удалили массив с числами
    ListLen--;              //а может только один указатель...
    pFirst = zn[0];
    pLast = zn[ListLen - 1];
    pCurrLink = pFirst;
    pPrevLink->pNext = pFirst;
    CurrPos = 0;
    }
  }

void TDatList::DelCurrent(void)
{
  if (!IsEmpty()) {
    int point = CurrPos - 1;
    PTDatLink* zn = new PTDatLink[ListLen - 1];

    for (int i = 0; i < ListLen - 2; i++) {
      zn[i] = pCurrLink;
      //если след элемент мы удаляем, то мы перезабиваем в pointer адрес на след элемент.
      if (point == CurrPos) {
        GoNext();
        zn[i]->pNext = pCurrLink->pNext;
      }
      GoNext();
    }
    //забиваем новый массив звеньев
    SetCurrentPos(0);
    delete[] pFirst->pNext; //вроде как все удалили
    ListLen--;
    pFirst = zn[0];
    pLast = zn[ListLen - 1];
    Reset();
  }
}

void TDatList::DelList(void)
{
  if (!IsEmpty()) {
    delete[] pFirst->pNext;
  }
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
  if (!IsListEnded()) {
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
  PTDatLink* zven= new PTDatLink[ListLen +1];
  zven[0]->pValue = pVal;
  zven[0]->pNext = pFirst;
  Reset();
  GoNext();
  for (int i = 1; i < ListLen + 1; i++) {
    zven[i] = pCurrLink;
    GoNext();
  }
  delete[] pFirst->pNext;
  pFirst = zven[0];
  pLast = zven[ListLen];
  ListLen++;
}

void TDatList::InsLast(PTDatValue pVal)
{
  PTDatLink* zven = new PTDatLink[ListLen - 1];
  Reset();
  GoNext();
  for (int i = 0; i < ListLen - 1; i++) {
    zven[i] = pCurrLink;
    GoNext();
  }
  ListLen--;
  zven[ListLen-1]->pValue = pVal;
  zven[ListLen - 1]->pNext = NULL;
  delete[] pFirst->pNext;
  pFirst = zven[0];
  pLast = zven[ListLen];
}

void TDatList::InsCurrent(PTDatValue pVal)
{

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
  PTItemValue pVal;
  pVal = (PTItemValue)q.pCurrLink->GetDatValue();
  os << pVal->GetValue();
  while (q.GoNext()) {
    pVal = (PTItemValue)q.pCurrLink->GetDatValue();
    os << " -> " << pVal->GetValue();
  }
  os << "\n";
  return os;
}
