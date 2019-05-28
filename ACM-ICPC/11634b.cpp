#include<iostream>
#include<set>
using namespace std;
main(){
  int n;
  while(cin>>n && n){
    set<int> S;S.insert(n);
    while(true){
      n = n*n;
      n=n/100;
      n=n%10000;
      if ( S.find(n) != S.end())break;
      S.insert(n);
    }
    cout << S.size() << endl;
  }
}

