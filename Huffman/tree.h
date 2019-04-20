#ifndef tree_h
#define tree_h

#include "header.h"
#include "heap.h"

/*Retira dois nós da fila de prioridade, faz o "merge" e manda para a heap*/
Node  *merge_nodes(Heap *heap);

/*Loop para criar a árvore enquanto o tamanho da fila for diferente de um, pois será o nó raiz*/
Node *create_tree_compact(Heap *heap);

#endif

