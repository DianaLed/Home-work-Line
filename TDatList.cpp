#include "TDatList.h"

void TDatList::DelLink(PTDatLink pLink)
{

}

TDatList::TDatList()
{
  CurrPos = 0;
  ListLen = 0;
}

TDatList::TDatList(PTDatValue* listElems, int listElemsCount)
{
  if (listElemsCount > 0) {
    ListLen = listElemsCount;
    CurrPos = 0;
    pLast->pValue = listElems[listElemsCount - 1];
    pLast->pNext = NULL;
    pCurrLink = pLast;
    for (int i = listElemsCount - 2; i >= 0; i--) {
      pPrevLink->pValue = listElems[i];
      pPrevLink->pNext = listElems[i+1]; //???

    }

  }
}
