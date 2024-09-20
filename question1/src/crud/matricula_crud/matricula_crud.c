#include <stdlib.h>
#include <stdio.h>

#include "../matricula_crud/matricula_crud.h"
#include "../disciplina_crud/disciplina_crud.h"

#include "../../utils/utils.h"


/**
 * @brief Aloca memória para uma nova estrutura NodeMatricula e inicializa seus membros.
 *
 * Esta função aloca memória para uma nova estrutura NodeMatricula e define seus membros
 * para valores padrão. Especificamente, define 'codDissciplina' com -1, 'dir' e 'esq' com NULL.
 *
 * @param node Uma refernecia para um ponteiro para uma estrutura NodeMatricula que será alocada e inicializada.
 */
static void alocMatricula(NodeMatricula **node)
{
  *node = (NodeMatricula *)malloc(sizeof(NodeMatricula));
  (*node)->codDisciplina = -1;
  (*node)->dir = NULL;
  (*node)->esq = NULL;
}

/**
 * @brief Libera a memória alocada para um objeto do tipo NodeMatricula.
 *
 * Esta função libera toda a memória associada ao objeto NodeMatricula passado como parâmetro,
 * garantindo que não haja vazamentos de memória.
 *
 * @param node Ponteiro para o uma struct NodeMatricula que será liberado.
 */
static void freeNodeMatricula(NodeMatricula *node)
{
  free(node);
}

/**
 * @brief Libera a memória alocada para todos os objetos do tipo NodeMatricula.
 *
 * Esta função percorre a árvore binária de Matriculas e libera toda a memória associada a cada nó.
 * @param raiz Ponteiro para o uma struct NodeMatricula que será liberado.
 */
void freeNodeMatriculas(NodeMatricula *raiz)
{
  if (raiz)
  {
    freeNodeMatriculas(raiz->esq);
    freeNodeMatriculas(raiz->dir);
    freeNodeMatricula(raiz);
  }
}

/*
 * @brief Exibe as informações de uma matriculaa.
 * Esta função imprime no console o codigo de matricula.
 *
 * @param node Ponteiro para a estrutura NodeMatricula que contém a informação da matricula.
 */
static void showMatricula(NodeMatricula *node)
{
  printf("Matricula:\n");
  printf("\tCodDisciplina: %d\n", node->codDisciplina);
}

/**
 * @brief Exibe todas as matriculas.
 *
 * Função recursiva que percorre a arvore de matriculas e exibe o codigo de cada matricula
 * . A função chama `showAllMatriculas` para percorrer todos os nós, e em seguida chama
 * `showMatricula` para exibir a matricula atual.
 *
 * @param raiz Ponteiro para o nó raiz da arvore de matriculas.
 */
void showAllMatriculas(NodeMatricula *raiz)
{
  if (raiz)
  {
    showAllMatriculas(raiz->esq);
    showAllMatriculas(raiz->dir);
    showMatricula(raiz);
  }
}

/**
 * @brief Insere um novo nó na árvore binária de matriculas.
 *
 * A função insere um novo nó `node` na árvore binária de matriculas com base
 * no código de matricula. Ela percorre a árvore comparando os códigos para garantir
 * que os nós à esquerda tenham valores menores e os nós à direita tenham valores maiores.
 *
 * @param raiz Ponteiro duplo para o nó raiz da árvore de disciplinas.
 * @param node Ponteiro para o nó de disciplina a ser inserido.
 */
void inserctionMatricula(NodeMatricula **raiz, NodeMatricula *new)
{
  if (!*raiz)
    *raiz = new;
  else
  {
    if (new->codDisciplina < (*raiz)->codDisciplina)
      inserctionMatricula(&(*raiz)->esq, new);
    else
      inserctionMatricula(&(*raiz)->dir, new);
  }
}

void search_matricula(NodeMatricula *raiz, int code, NodeMatricula **result)
{
  if (raiz)
  {
    if (raiz->codDisciplina == code)
      *result = raiz;
    else if (raiz->codDisciplina < code)
      search_matricula(raiz->dir, code, result);
    else if (raiz->codDisciplina > code)
      search_matricula(raiz->esq, code, result);
  }
}

NodeMatricula *esqRoot(NodeMatricula *node)
{
  NodeMatricula *current = node;
  while (current && current->esq != NULL)
    current = current->esq;
  return current;
}

// Tem que testar ainda. (Quebrou a parte que os cursos não tem o codigo correto.)
void removerDisciplinaDaArvoreDeMatricula(NodeMatricula **matricula, int codDisciplina)
{
  NodeMatricula *atual = *matricula;
  NodeMatricula *temp = *matricula;

  if (matricula)
  {
    if (atual->codDisciplina > codDisciplina)
      removerDisciplinaDaArvoreDeMatricula(&(atual->esq), codDisciplina);
    else if (atual->codDisciplina < codDisciplina)
      removerDisciplinaDaArvoreDeMatricula(&(atual->dir), codDisciplina);
    else
    {
      if (atual->esq == NULL)
        temp = atual->dir;
      else if (atual->dir == NULL)
        temp = atual->esq;
      else
        temp = esqRoot(atual->dir);

      *matricula = temp;
      free(atual);
    }
  }
}


//precia testar esta função de remoção 
// NodeMatricula *removerMatricula(NodeMatricula *raiz, int codDisciplina) {
//     if (raiz == NULL) {
//         return NULL;
//     }

//     if (raiz->codDisciplina == codDisciplina) {
//         // Remove nos folhas
//         if (raiz->esq == NULL && raiz->dir == NULL) {
//             free(raiz);
//             return NULL;
//         }
//         // Remove nós que possuem apenas um filho
//         else if (raiz->esq == NULL || raiz->dir == NULL) {
//             NodeMatricula *temp = (raiz->esq != NULL) ? raiz->esq : raiz->dir;
//             free(raiz);
//             return temp;
//         }
//         // Remove nós que possuem dois filhos
//         else {
//             NodeMatricula *aux = raiz->esq;
//             while (aux->dir != NULL) {
//                 aux = aux->dir;
//             }
//             raiz->codDisciplina = aux->codDisciplina;
//             raiz->esq = removerMatricula(raiz->esq, aux->codDisciplina);
//             return raiz;
//         }
//     } else if (raiz->codDisciplina > codDisciplina) {
//         raiz->esq = removerMatricula(raiz->esq, codDisciplina);
//     } else {
//         raiz->dir = removerMatricula(raiz->dir, codDisciplina);
//     }

//     return raiz;
// }

/**
 * @brief Cadastra uma nova matrícula para um aluno em uma disciplina.
 *
 * Esta função cria uma nova matrícula e a insere na árvore de matrículas de um aluno,
 * associando a matrícula à disciplina correspondente.
 *
 * @param aluno Lista de alunos onde a matrícula será adicionada.
 * @param raizDisciplina Raiz da árvore de disciplinas disponíveis.
 */
void cadastrarMatriculas(ListAluno *aluno, int idDisciplina)
{
  NodeMatricula *new;
  alocMatricula(&new);
  
  new->codDisciplina = idDisciplina;

  if (new)
  {
    ListAluno *auxAluno = aluno;
    inserctionMatricula(&(auxAluno->aluno.nodeMatricula), new);
  }
}