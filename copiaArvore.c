/*
Copiar uma árvore de busca binária para sua versão com a altura mínima possível (sem modificá-la)
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

// no de arvore
typedef struct estr {
    int chave;
    struct estr *esq;
    struct estr *dir;
} NO;

// no de lista ligada (caso queira usar alguma estrutura auxiliar)
typedef struct estrL {
        int chave;
        struct estrL *prox;
} NOL;

NO* busca (NO* raiz, int ch, NO* *pai) {
    NO* p = raiz;
    *pai = NULL;
    while (p) {
        if (p->chave == ch) return p;
        *pai = p;
        if (ch < p->chave) p = p->esq;
        else p = p->dir;
    }
    return NULL;
}

void exibirArvore(NO* p, int n) {
    if (p) {
        if (p->dir) exibirArvore(p->dir, n + 1);
        int i;
        for (i = 0; i < n; i++)
            printf("     ");
        printf("%d\n", p->chave);
        
        if (p->esq) exibirArvore(p->esq, n + 1);
    }
}

void exibirLista (NOL* p) {
	while (p != NULL) {
		printf("%d ", p->chave);
		p = p->prox;
	}
}

NO* criarNovoNo (int ch) {
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->esq = NULL;
    novo->dir = NULL;
    novo->chave = ch;
    return novo;
}

NO* inserirNo(NO* *raiz, int ch) {
    NO* novo = criarNovoNo(ch);
    NO* pai = NULL;
    NO* atual = busca (*raiz, ch, &pai);
    if(pai) {
        if (ch < pai->chave) pai->esq = novo;
        else pai->dir = novo;
    } 
    else *raiz = novo;
    return novo;
}


NOL *arvoreParaLista(NO* raiz, NOL **lista) {
    if (raiz) {
        NOL *novo = (NOL*) malloc(sizeof(NOL));
        novo->chave = raiz->chave;
        novo->prox = *lista;
        *lista = novo;
        arvoreParaLista(raiz->esq, lista);
        arvoreParaLista(raiz->dir, lista);
    }
    return *lista;
}

void ordenaLista (NOL* p) {
	for (NOL* i = p; i->prox != NULL; i = i->prox) {
		NOL* menor = i;
		for (NOL* j = i->prox; j != NULL; j = j->prox) {
			if(j->chave < menor->chave) menor = j;
		}
		int aux = i->chave;
		i->chave = menor->chave;
		menor->chave = aux;
	}
}

NO *listaParaArvore (NOL* lista, NO* raiz, int inicio, int n) {
    NOL* p = lista;
    if (inicio > n) return NULL;

    int meio = (inicio + n) / 2;
    int i = 0;
    NOL* atual = NULL;
    //encontrar o meio da lista
    while (p) {
        if (i == meio) {
            atual = p;
            break;
        }
        p = p->prox;
        i++;
    }
    inserirNo(&raiz, atual->chave);
    raiz->esq = listaParaArvore(lista, raiz->esq, inicio, meio - 1);
    raiz->dir = listaParaArvore(lista, raiz->dir, meio + 1, n);

    return raiz;
}

// caso o compilador exija declarar a funcao aqui
NO* copiaCompleta(NO* raiz);
//------------------------------------------
// O EP consiste em implementar esta funcao
//------------------------------------------
NO* copiaCompleta(NO* raiz) {

	// seu codigo AQUI

}

int main() {

	NO* raiz = NULL;
    //inserirNo(&raiz, 20);
    // inserirNo(&raiz, 35);
    // inserirNo(&raiz, 25);
    // inserirNo(&raiz, 45);
    // inserirNo(&raiz, 10);
    // inserirNo(&raiz, 15);
    // inserirNo(&raiz, 14);
    // inserirNo(&raiz, 13);
    // inserirNo(&raiz, 12);
    inserirNo(&raiz, 20);
    inserirNo(&raiz, 21);
    inserirNo(&raiz, 22);
    inserirNo(&raiz, 23);
    inserirNo(&raiz, 24);
    inserirNo(&raiz, 25);
    inserirNo(&raiz, 26);
    inserirNo(&raiz, 27);
    inserirNo(&raiz, 28);
    exibirArvore(raiz, 0);


    NOL* lista = NULL;
    int n = 0;
    //nro de elementos da lista
    arvoreParaLista(raiz, &lista);
    ordenaLista(lista);
    exibirLista(lista);
    printf("\n");
    NOL* p = lista;
    while (p) {
        p = p->prox;
        n++;
    }
    
    NO* resp = NULL;
    resp = listaParaArvore(lista, resp, 0, n - 1);
    exibirArvore(resp, 0);
	// serao realizadas chamadas como esta:
	// NO* resp = copiaCompleta(raiz);

}
