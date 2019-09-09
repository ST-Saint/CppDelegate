// #include <vector>
// #include <algorithm>
// #include <functional>
#include <bits/stdc++.h>

template<typename RT, typename... AT>
class Delegate{
private:
  std::vector<std::function<RT(AT...)>*> funclist;
public:
  void operator += (std::function<RT(AT...)>* f){
    funclist.push_back(f);
  }
  void operator -= (std::function<RT(AT...)>* f){
    auto pos = find(funclist.begin(), funclist.end(), f);
    if( pos != funclist.end() ){
      funclist.erase(pos);
    }
  }
  template<typename ...Args>
  RT operator ()(Args&& ...args){
    for(auto fn: funclist){
      (*fn)(std::forward<Args>(args)...);
    }
    return ;
  }
};

class Foo{
public:
  void print(int a,int b){
    printf("Test %d %d\n", a, b);
  }
};

int main(){
  Delegate<void, int, int> d = Delegate<void, int, int>();
  std::function<void(int, int)> F = [](int a,int b)->void{
      printf("a + b = %d\n", a+b);
  };
  std::function<void(int, int)> FF = [](int a,int b)->void{
    printf("a - b = %d\n", a-b);
  };
  d += &F;
  d += &FF;
  d(2, 3);
  std::cout << "--------------------------------------------------" << std::endl ;
  d -= &F;
  d(2, 3);
  std::cout << std::endl << "ClassDelegate "<< std::endl << "--------------------------------------------------" << std::endl ;
  // d -= &FF;

  Foo* t = new(Foo);
  std::function<void(int, int)> CF = std::bind(&Foo::print, t, std::placeholders::_1, std::placeholders::_2);

  d += &CF;
  d(2, 3);

  return 0;
}
