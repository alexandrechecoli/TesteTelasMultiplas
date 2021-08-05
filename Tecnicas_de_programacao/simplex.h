#ifndef SIMPLEX_H
#define SIMPLEX_H

#endif // SIMPLEX_H

#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

int seleciona_coluna_pivo(vector<vector<double>> &M);
int seleciona_linha_pivo(vector<vector<double>> &M ,int coluna_pivo);
void atualiza_linha_pivo(vector<vector<double>> &M,int linha_pivo, int coluna_pivo);
void atualiza_tabela(vector<vector<double>> &M, int linha_pivo, int coluna_pivo);
void atualiza_vetor_resposta(vector<vector<double>> &M, vector<double> &X);
void imprime_matriz(vector<vector<double>> &M);

vector<double> otimiza_simplex(vector<vector<double>> &M)
{

    /*
      Esta função otimiza um modelo pelo método Simplex, com os dados já em formato de igualdade, por exemplo, o
      modelo:
      max 2x1 + 3x2
      sa:                             -2 -3 0 0 0
          5x1 + 2x2 <= 10    =>  M =   5  2 1 0 10
          x1        <= 40              1  0 0 1 40

      O retorno da função  é um vetor com o valor das variáveis em ordem, po exemplo
      (x1,x2,x3,x4, Z) = (0, 3.8, 0, 10, 100, e o ultimo elemento é o valor da f.o)
      e o valor da f.o é armazenado em Z
    */

    bool criterio_parada = false;
    vector<double> X(M[0].size(), -1); //inicializa todas as var. de resposta com -1

    while(criterio_parada == false)
    {
        imprime_matriz(M);
        int coluna_pivo = seleciona_coluna_pivo(M);
        if(coluna_pivo != -1)
        {
            int linha_pivo = seleciona_linha_pivo(M, coluna_pivo);
            if(linha_pivo != -1)
            {
                atualiza_linha_pivo(M, linha_pivo, coluna_pivo);
                atualiza_tabela(M, linha_pivo, coluna_pivo);
            }else
            {
                criterio_parada = true;
            }
        }else
        {
            atualiza_vetor_resposta(M, X);
            criterio_parada = true;
        }
    }

    return X;
}

int seleciona_coluna_pivo(vector<vector<double>> &M)
{
    /*
     * Percorre todas as colunas (exceto a última, que é o valor de b) da primeira linha da matriz M e seleciona o vaor mais negativo,
     * se não existirem valores negativos, o valor retornado é -1
     */

    int coluna_mais_negativo = -1;
    int menor_valor = 0; //inicializando como zero, só é necessário fazer uma 'pergunta', se é < 0

    for(int j = 0; j < M[0].size()-1; j++) //não verifica o última valor
    {
        if(M[0][j] < menor_valor)
        {
            menor_valor = M[0][j];
            coluna_mais_negativo = j;
        }
    }

    return coluna_mais_negativo;
}

int seleciona_linha_pivo(vector<vector<double>> &M ,int coluna_pivo)
{

    /*
     * Realiza a divisão de todos os elementos 'b' (última coluna) de M, pelos valores
     * de todas as linhas (exceto a primeiro - fo), e seleciona a menor destas divisões,
     * que seja > 0;
     */

    int linha_menor_divisao = -1; //se nenhuma divisao for possivel, o valor retornado é -1
    double menor_divisao = INT_MAX;
    for(int i = 1; i < M.size(); i++)
    {
        if(M[i][coluna_pivo] > 0) //se o valor for positivo
        {
            //M[0].size()-1 : indice da ultima coluna da matriz
            double divisao = M[i][M[0].size()-1] / M[i][coluna_pivo];
            if(divisao < menor_divisao)
            {
                menor_divisao = divisao;
                linha_menor_divisao = i;
            }
        }

    }

    return  linha_menor_divisao;
}

void atualiza_linha_pivo(vector<vector<double>> &M, int linha_pivo, int coluna_pivo)
{

    /*
     * Divide todos os elementos da linha_pivo, pelo elemento M[linha_pivo][coluna_pivo]
     */

    double elemento_pivo = M[linha_pivo][coluna_pivo];
    for(int j = 0; j < M[0].size(); j++)
    {
        M[linha_pivo][j] = M[linha_pivo][j] / elemento_pivo;
    }
}

void atualiza_tabela(vector<vector<double>> &M, int linha_pivo, int coluna_pivo)
{

    /*
     * Atualiza a tabela Simplex
     */

    for(int i = 0; i < M.size(); i++)
    {
        if(i != linha_pivo) //não atualiza a linha pivo (já esta atualizada)
        {
            double elemento = -M[i][coluna_pivo];
            for(int j = 0; j < M[0].size(); j++)
            {
                M[i][j] = M[i][j] + elemento * M[linha_pivo][j];
            }
        }
    }
}

void atualiza_vetor_resposta(vector<vector<double>> &M, vector<double> &X)
{

    for(int j = 0; j < M[0].size(); j++)
    {
        int soma_linha = 0;
        int linha_com_1 = 0;
        for(int i = 0; i < M.size(); i++)
        {
            soma_linha += M[i][j];
            if(M[i][j] == 1)
            {
                linha_com_1 = i;
            }
        }
        if(soma_linha == 1)
        {
            X[j] = M[linha_com_1][M[0].size()-1];
        }
        else
        {
            X[j] = 0;
        }
    }
    X[X.size()-1] = M[0][M[0].size()-1];
}

void imprime_matriz(vector<vector<double>> &M)
{
    for(int i = 0; i < M.size(); i++)
    {
        for(int j = 0; j < M[0].size(); j++)
        {
            cout << M[i][j] << " ";
        }
        cout << " \n";
    }
    cout << "\n";
}

vector<vector<double>> le_matriz_txt(string caminho)
{
    ifstream leitor(caminho);
    int linhas, colunas;
    leitor >> linhas;
    leitor >> colunas;

    vector<vector<double>> M(linhas, vector<double>(colunas));

    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {
            leitor >> M[i][j];
        }
    }

    leitor.close();
    return M;
}






