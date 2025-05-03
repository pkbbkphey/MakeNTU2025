#include <Arduino.h>
template<class T>
class pii{
public:
  T first, second;
  pii(T a, T b) : first(a), second(b){}
  pii<T> operator +(const pii<T> &o)const{
    return pii(first + o.first, second + o.second);
  }
  pii<T> operator -(const pii<T> &o)const{
    return pii(first - o.first, second - o.second);
  }
  int sqr(){
    return first * first + second * second;
  }
};

int dist(pii<int> a, pii<int> b){
  pii<int> c = a - b;
  return c.sqr();
}