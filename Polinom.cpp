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

TPolinom::TPolinom(TPolinom& q) //???
{
  PTMonom pm = new TMonom(0, 1);
  for (q.Reset(); !q.IsListEnded(); q.GoNext())
  {
    PTMonom pm = q.GetMonom();
    InsLast(pm->GetCopy());
  }
}

bool can_sum_monom(PTMonom a, PTMonom b) {
  int ia = a->GetIndex(), ib = b->GetIndex();
  if (ia == ib) return 1;
  return 0;
}
PTMonom sum_monom(PTMonom a, PTMonom b) {
  int ires=a->GetCoeff() + b->GetCoeff();
  PTMonom res=new TMonom();
  res->SetCoeff(ires);
  res->SetIndex(a->GetIndex());
  return res;
}

TPolinom TPolinom::operator+(TPolinom& q)
{
  TPolinom res;
  PTMonom sum;
  //for (int i = 0; i < ListLen; i++) { //проход по основному
  //  SetCurrentPos(i);
  //  //res+осн 
  //  if (can_sum_monom(res.GetMonom(), GetMonom()))//res и осн 
  //  { 
  //    sum = sum_monom(res.GetMonom(), GetMonom()); //ссумируем
  //    res.SetCurrentPos(res.GetListLength() - 1); //удаляем просумированный элемент
  //    res.DelCurrent();
  //    if (sum->GetCoeff() != 0) res.SetMonom(sum);
  //  }
  //  //res+sum
  //  else { 
  //    if(nom_q<q.GetListLength())
  //      q.SetCurrentPos(i);
  //      //q+осн
  //      if (can_sum_monom(q.GetMonom(), GetMonom())) { 
  //        sum = sum_monom(q.GetMonom(), GetMonom()); //сложили
  //        //проверяем на сложение с последним эл из res
  //        if (can_sum_monom(res.GetMonom(), sum)) { //сложить можно q и res
  //          sum = sum_monom(res.GetMonom(), sum); //ссумируем
  //          res.SetCurrentPos(res.GetListLength() - 1); //удаляем просумированный элемент
  //          res.DelCurrent();
  //        }
  //        //добавляем результат в res
  //        if (sum->GetCoeff() != 0) res.SetMonom(sum);
  //      }
  //      else { //res+q
  //      //проверяем на сложение res и q
  //        if (can_sum_monom(res.GetMonom(), q.GetMonom())) { //сложить можно
  //          sum = sum_monom(res.GetMonom(), q.GetMonom()); //ссумируем
  //          res.SetCurrentPos(res.GetListLength() - 1); //удаляем просумированный элемент
  //          res.DelCurrent();
  //          if (sum->GetCoeff() != 0) res.SetMonom(sum);
  //        }
  //      }
  //    }
  //  }
  int ithis = 0, iq = 0;
  Reset();
  q.Reset();

  if (*GetMonom() > *q.GetMonom()) { sum = GetMonom(); GoNext(); ithis++; }
  else { sum = q.GetMonom(); q.GoNext(); iq++;}
  res.SetMonom(sum);
  
  //складываем пока одна из цепочек не кончится
  while ((ithis < GetListLength()&& iq< GetListLength())) {
    //ищем самый большой моном
    res.SetCurrentPos(res.GetListLength() - 1);
    if (*GetMonom() > *q.GetMonom())
      //и его добавляем в res
      if (can_sum_monom(GetMonom(), res.GetMonom())) {
        sum = sum_monom(GetMonom(), res.GetMonom());
        res.DelCurrent();
        if(sum->GetCoeff()!=0) res.SetMonom(sum);
        GoNext();
        ithis++;
      }
      else {
        res.SetMonom(GetMonom());
        GoNext();
        ithis++;
      }
    else {
      if (can_sum_monom(q.GetMonom(), res.GetMonom())) {
        sum = sum_monom(q.GetMonom(), res.GetMonom());
        res.DelCurrent();
        if (sum->GetCoeff() != 0) res.SetMonom(sum);
        q.GoNext();
        iq++;
      }
      else {
        res.SetMonom(q.GetMonom());
        q.GoNext();
        iq++;
      }
    }
    if (res.GetListLength() == 0) {
      if (ithis < GetListLength()) { res.SetMonom(GetMonom()); ithis++; GoNext();}
      if (iq < q.GetListLength()) { res.SetMonom(q.GetMonom()); iq++; q.GoNext(); }
    }
  }
  //когда одна из цепочек кончилась, мы добавляем вторую
  while (ithis < GetListLength()) {
    if (can_sum_monom(GetMonom(), res.GetMonom())) {
      sum = sum_monom(GetMonom(), res.GetMonom());
      res.DelCurrent();
      if (sum->GetCoeff() != 0) res.SetMonom(sum);
      GoNext();
      ithis++;
    }
    else {
      res.SetMonom(GetMonom());
      GoNext();
      ithis++;
    }
  }
  while (iq < GetListLength()) {
    if (can_sum_monom(q.GetMonom(), res.GetMonom())) {
      sum = sum_monom(q.GetMonom(), res.GetMonom());
      res.DelCurrent();
      if (sum->GetCoeff() != 0) res.SetMonom(sum);
      q.GoNext();
      iq++;
    }
    else {
      res.SetMonom(q.GetMonom());
      q.GoNext();
      iq++;
    }
  }
  return res;
}



TPolinom& TPolinom::operator=(const TPolinom& q)
{
    DelList();
    TDatLink* cur = q.pFirst;
    for (int i = 0; i < q.GetListLength(); i++) {
      TMonom* mon = (TMonom*)cur->GetDatValue();
      TDatValue* add = new TMonom(mon->GetCoeff(), mon->GetIndex());
      InsLast(add);
      cur = cur->GetNextLink();
    }
    return *this;
 /* PTMonom pm=new TMonom;
  for (q.Reset(); !q.IsListEnded(); q.GoNext())
  {
    pm = q.GetMonom();
    InsLast(pm->GetCopy());
  }
  q.GoNext();
   pm = q.GetMonom();
  InsLast(pm->GetCopy());
  return (*this);*/
}

int get_one(int a) {
  int res = a / 100;
  return res;
}
int get_two(int a) {
  int res = a % 100 - (a % 10);
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
    //a = *(q.GetMonom());
    //os << a << " ";
  }
  return os;
}
