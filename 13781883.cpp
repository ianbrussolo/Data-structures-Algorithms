//--------------------------------------------------------------
// NOME: Ian Tiozzo Brussolo 
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>


// ######### ESCREVA SEU NROUSP AQUI
const char* nroUSP() {
    return("13781883");
}


// no da arvore
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


// caso o compilador exija declarar a funcao aqui
NO* criarNovoNo (int ch);
NO* busca (NO* raiz, int ch, NO* *pai);
NO* inserirNo(NO* *raiz, int ch);
NOL* arvoreParaLista(NO* raiz, NOL **lista);
void ordenaLista (NOL* p);
NO* listaParaArvore (NOL* lista, NO* raiz, int inicio, int n);
NO* copiaCompleta(NO* raiz);


NO* criarNovoNo (int ch) {
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->esq = NULL;
    novo->dir = NULL;
    novo->chave = ch;
    return novo;
}


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


NOL* arvoreParaLista(NO* raiz, NOL **lista) {
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


NO* listaParaArvore (NOL* lista, NO* raiz, int inicio, int n) {
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


//------------------------------------------
// O EP consiste em implementar esta funcao
//------------------------------------------
NO* copiaCompleta(NO* raiz) {
    
    if (!raiz) return raiz;

    // seu codigo AQUI
    NOL* lista = NULL;
    arvoreParaLista(raiz, &lista);
    ordenaLista(lista);

    NOL* p = lista;
    //nro de elementos da lista
    int n = 0;
    while (p) {
        p = p->prox;
        n++;
    }

    NO* resp = NULL;
    resp = listaParaArvore(lista, resp, 0, n - 1);
    return resp;

}




//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {

	NO* raiz = NULL;

	// acrescente aqui alguns nos para criar uma arvore de teste
	
	// serao realizadas chamadas como esta:
	NO* resp = copiaCompleta(raiz);
   
}

// por favor nao inclua nenhum código abaixo da função main()