#include "Polinom.h"
#include "TItemValue.h"

TPolinom::TPolinom(int monoms[][2], int km)
{
  PTMonom pm = new TMonom(0, 1);
  for (int i = 0; i < km; i++)
  {
    pm = new TMonom(monoms[i][0], monoms[i][1]);
    InsLast(pm); //вставляю в конец через list
  }
}

TPolinom::TPolinom(TPolinom& q)
{
  PTMonom pm = new TMonom(0, 1);
  for (q.Reset(); !q.IsListEnded(); q.GoNext())
  {
    PTMonom pm = q.GetMonom();
    InsLast(pm->GetCopy());
  }
}


TPolinom& TPolinom::operator+(TPolinom& q)
{
  TPolinom res=*this;
  TPolinom dop;
  PTMonom max;
  PTMonom sum = nullptr;
  for (q.Reset(); !q.IsListEnded(); q.GoNext()) {
    res.InsLast(q.GetMonom());
  }
  q.GoNext();
  res.InsLast(q.GetMonom());
  //обьединили два полинома в один
  cout << res << endl;
  res.sortPolinm();
  cout << res << endl;
  //мы имеем единый отсорированный список в dop
  //в res у нас пусто
  //само сложение
  while (!dop.IsEmpty()) {
    dop.Reset();
    max = dop.GetMonom();
    dop.GoNext();
    //если первое число больше
    if (max > dop.GetMonom()) {
      res.InsLast(max);
      dop.DelFirst();
    }
    else 
      //сложение если равные индексы (while, так как их может быть больше 2х)
    { 
      while ((max->GetIndex() == dop.GetMonom()->GetIndex())&& dop.GetListLength()!=0) {
        max->SetCoeff(max->GetCoeff() + dop.GetMonom()->GetCoeff()); //сумируем коэф
        dop.DelFirst();
        cout << dop << "\n";
        cout << dop.GetListLength() << "-listlen\n";
        //надо проверить следующие элементы
      }
      //если при сложении получился не 0, то добавляем
      if (max->GetCoeff() != 0) {
        sum->SetIndex(max->GetIndex());//в сумму забиваем индексы
        sum->SetCoeff(max->GetCoeff());//в сумму забиваем саму сумму
        res.InsLast(sum);//добавляем в результат
      }
    }
  }
  //если в доп вдруг остался один элемент
  if (dop.GetListLength() == 1) {
    dop.Reset();
    res.InsLast(dop.GetMonom());
    dop.DelCurrent();
  }
  //теперь в допе ничего нет, можно радоваться

  //сложение полиномов
  *this = res;
  return *this;
}



TPolinom& TPolinom::operator=(TPolinom& q)
{
  DelList();
  for (q.Reset(); !q.IsListEnded(); q.GoNext())
  {
    PTMonom pm = q.GetMonom();
    InsLast(pm->GetCopy());
  }
  q.GoNext();
  PTMonom pm = q.GetMonom();
  InsLast(pm->GetCopy());
  return (*this);
  //DelList();
  //*this = q;
  //return (*this);
}

void TPolinom::sortPolinm()
{
  PTDatValue max;
    for (int j = 0; j < ListLen - 1; j++) { //ставим на это место max
      SetCurrentPos(j);
      max = pCurrLink->GetDatValue();
      GoNext();
      for (int i = j + 1; i < ListLen; i++) {
        if (pCurrLink->GetDatValue() > max) //не сможем реализовать
          change(j, i);
          GoNext();
      }
    }
}

int get_one(int a) {
  int res = a/100;
  return res;
}
int get_two(int a) {
  int res = a % 100-(a%10);
  return res;
}
int get_three(int a) {
  int res = a % 10;
  return res;
}

int how_m_el(int a) {
  int res = 0;
  while (a != 0) {
    res++;
    a = a / 10;
  }
  return res;
}


ostream& operator<<(ostream& os, TPolinom& q)
{
  //TMonom a;
  //int dop, d1, d2, d3;
  //q.Reset();
  //a = *(q.GetMonom());
  //if (a.GetCoeff() > 0)os << a.GetCoeff();
  //if (a.GetCoeff() < 0)os << "-" << a.GetCoeff();
  //q.GoNext();
  //for (; !q.IsListEnded(); q.GoNext()) {
  //  a = *(q.GetMonom());
  //  if(a.GetCoeff() >0)os << "+" << a.GetCoeff();
  //  if (a.GetCoeff() >0)os << "-" << a.GetCoeff();
  //  dop = a.GetIndex();
  //  d1 = d2 = d3 = 0;
  //  if (how_m_el(dop) >=1) d3 = dop % 10;
  //  if (how_m_el(dop) >= 2) d2 = (dop % 100-d3)/10;
  //  if (how_m_el(dop) == 3) d1 = dop / 100;
  //  //______
  //  if (d1 + d2 + d3 != 0) {
  //    if (a.GetCoeff() > 0)os << "*";
  //    if (d1 > 0) os << "x^(" << d1 << ")*";
  //    if (d2 > 0) os << "y^(" << d2 << ")*";
  //    if (d3 > 0) os << "z^(" << d3 << ")";
  //  } //вывели моном
  //}
  //return os;
  if (q.GetListLength() != NULL && q.GetListLength() != 0) {
    TMonom a;
    for (q.Reset(); !q.IsListEnded(); q.GoNext()) {
      a = *(q.GetMonom());
      os << a << " ";
    }
    a = *(q.GetMonom());
    os << a << " ";
  }
  return os;
}
