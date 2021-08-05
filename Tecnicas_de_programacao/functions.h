#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#endif // FUNCTIONS_H
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int return_int_between(int a, int b)
{
    int random =  -1;
    if(a < b)
    {
        random = a + rand() % (b - a + 1);
    }

    return random;
}

void print_vector(vector<int> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        cout << v[i] << ",";
    }
    cout << "\n";
}

void print_vector(vector<double> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        cout << v[i] << ",";
    }
    cout << "\n";
}

vector<int> retorna_vetor_chegada(int a, int b, int n)
{
    vector<int> Vc(n,0);

    for(int i = 1; i < n; i ++)
    {
        Vc[i] = Vc[i-1] + return_int_between(a,b);
    }
    return Vc;
}

vector<int> retorna_vetor_atendimento(int a, int b, int n)
{
    vector<int> Va(n,0);

    for(int i = 0; i < n; i ++)
    {
        Va[i] = return_int_between(a,b);
    }
    return Va;
}

vector<int> retorna_vetor_saida(vector<int> &Vc, vector<int> &Va)
{
    vector<int> Vs(Va.size(),0);
    Vs[0] = Vc[0] + Va[0];
    for(int i = 1; i < Vs.size(); i ++)
    {
        if(Vs[i-1] > Vc[i])
        {
            Vs[i] = Vs[i-1] + Va[i];
        }else
        {
            Vs[i] = Vc[i] + Va[i];
        }
    }
    return Vs;
}

vector<int> retorna_vetor_fila(vector<int> &Vc, vector<int> &Va, vector<int> &Vs)
{
    vector<int> Vf(Va.size(),0);
    for(int i = 0; i < Vf.size(); i++)
    {
        Vf[i] = Vs[i] - (Vc[i] + Va[i]);
    }
    return Vf;
}

double calcula_media_vetor(vector<int> V)
{
    double media = 0;
    for(int i = 0; i< V.size(); i++)
    {
        media += V[i];
    }
    media = media/V.size();
    return media;
}

void simulacao_fila(int a, int b, int c, int d, int n)
{

    vector<int> Vc = retorna_vetor_chegada(a, b, n);
    vector<int> Va = retorna_vetor_atendimento(c, d, n);
    vector<int> Vs = retorna_vetor_saida(Vc, Va);
    vector<int> Vf = retorna_vetor_fila(Vc, Va, Vs);
    //print_vector(Vc);
    //print_vector(Va);
    //print_vector(Vs);
    //print_vector(Vf);
    double media = calcula_media_vetor(Vf);
    cout << "Parametros [a,b], [c,d] , b  = [" << a << "," << b << "][" << c << "," << d << "]"
    "n = " << n << " : Tempo médio de fila :" << media << " \n";
}

vector<double> retorna_vetor_intervalado(double a, double b, int n)
{
    double delta = (b - a)/n;
    vector<double> Vi(n + 1,0);

    Vi[0] = 0;

    for(int i = 1; i < Vi.size(); i++)
    {
        Vi[i] = Vi[i-1] + delta;
    }

    return Vi;
}

double fx2(double x)
{
    return pow(x,2);
}

vector<double> retorna_vetor_valores_funcao(vector<double> &v_dominio)
{
    vector<double> Vf(v_dominio.size(), 0);

    for(int i = 0; i < v_dominio.size(); i++)
    {
        Vf[i] = fx2(v_dominio[i]);
    }
    return Vf;
}

double calcula_area_trapezio(double B, double b, double h)
{
    double area = (B + b)*h/2;
    return area;
}

double calcula_integral(vector<double> Vdominio, vector<double> VImagem)
{
  double soma_integral = 0;
  double delta = Vdominio[1] - Vdominio[0];
  for(int i = 1; i < Vdominio.size(); i++)
  {
      soma_integral =  soma_integral + calcula_area_trapezio(VImagem[i],VImagem[i-1],delta);
  }
  return soma_integral;

}
