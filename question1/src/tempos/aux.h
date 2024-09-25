#pragma once

#define QTDTESTES 30

typedef enum enTipoDeOrdenacao
{
  CRESCENTE,
  DECRESCENTE,
  ALEATORIO,
} TipoDeOrdenacao;

void vetIntAleatorioSemRepeticao(int *vetor, int qtd);
void vetIntCrescente(int *vetor, int qtd);
void vetIntDecrescente(int *vetor, int qtd);

typedef struct stRelatorio
{
  char *titulo;
  int quantidadeDeElementos;
  double tempo;
} Relatorio;

void showRelatorio(Relatorio *relatorio);
