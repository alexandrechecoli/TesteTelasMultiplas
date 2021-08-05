#include <iostream>

using namespace std;

int main()
{

  double a,b,c,d,e,f;
  cout<<"valor do salario\n";
  cin>>a;
  cout<<"quantidade de horas trabalhadas no mes\n";
  cin>>b;

  c=a/b;


cout<< "salario por hora\n"<<c;

d=0,5*c;
e=160*c;
f=d*c;

if (b>160)
{
    cout<<"salario total de\n"<<f;
} else if (b<160)
{

    cout<< "salario total de \n"<<e;

}
}
