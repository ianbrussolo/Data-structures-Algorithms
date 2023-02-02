/*
Listas ligadas simples, não circulares, sem cabeça e sem nó sentinela .
1. Entrada: duas listas ligadas ordenadas (vazias ou não). Saída: nova lista ligada ordenada unindo ambas as listas (eliminando repetições)
2. A assinatura da função é a seguinte:
NO* uniao(NO* p1, NO* p2);
3. Os ponteiros fornecidos como entrada (*p1 e *p2) são o início de listas que contém inteiros em ordem crescente
Exemplo: p1={1,1,2,3,4,4} e p2={1,2,2,3,5,5}: união = {1,2,3,4,5}.
4. Restrições de implementação:
(a) Não use nenhum vetor na sua implementação. Estruturas auxiliares de implementação dinâmica podem ser utilizadas livremente, 
mas caso haja uso de qualquer tipo de estrutura estática o EP será considerado inválido.
(b) Não exiba nenhuma mensagem na tela, nem solicite que o usuário pressione nenhuma tecla etc. 
5. A função main() serve apenas para seus testes particulares, e não precisa ser entregue. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct estr {
        int valor;
        struct estr* prox;
} NO;

void anexarElemento (NO** p, int ch) {
	NO* atual = *p;
	NO* novo =  (NO*) malloc(sizeof(NO));
	novo->valor = ch;
	novo->prox = NULL; //anexa no fim da lista
	NO* ant = NULL;
	while (atual != NULL) { //se a lista nao estiver vazia, procurar o fim
		ant = atual;
		atual = atual->prox;
	}
	ant->prox = novo;
	novo->prox = NULL;
	atual = novo;
	/*if (ant) ant->prox = novo; //se existir um anterior, anexar 'novo' depois dele
	else atual = novo;*/ //primeiro elemento
}

void exibirLista (NO* p) {
	printf("printando lista:\n");
	while (p != NULL) {
		printf("%d\n", p->valor);
		p = p->prox;
	}
}

void ordenaLista (NO* p) {
	for (NO* i = p; i->prox != NULL; i = i->prox) {
		NO* menor = i;
		for (NO* j = i->prox; j != NULL; j = j->prox) {
			if(j->valor < menor->valor) menor = j;
		}
		int aux = i->valor;
		i->valor = menor->valor;
		menor->valor = aux;
	}
}

// funcao principal
NO* uniao(NO* p1, NO* p2) {
	printf("uniao:\n");
	NO* resp = NULL;
	resp = (NO*)malloc(sizeof(NO));
	if (p1 == NULL && p2 == NULL) return resp;
	//p1 vazia:
	//else if (p1 == NULL) 
	//p2 vazia:
	//else if (p2 == NULL)  
	//anexando os primeiros elementos de p1 e p2
	NO* novo = (NO*)malloc(sizeof(NO));
	novo->valor = p1->valor;
	novo->prox = NULL;
	resp = novo;
	NO* p = resp;
	if (novo->valor != p2->valor) anexarElemento(&resp, p2->valor);
	//percorre a lista 1, tira as repetições
	while (p1->prox) { 
		if (p1->valor != p1->prox->valor) anexarElemento(&resp, p1->prox->valor);
		p1 = p1->prox;
	}
	printf("lista 1 anexada\n");
	exibirLista(resp);
	//percorre a lista 2, tira as repetições
	while (p2->prox) {
		if (p2->valor != p2->prox->valor) anexarElemento(&resp, p2->prox->valor);
		p2 = p2->prox;
	}
	printf("lista 2 anexada\n");
	exibirLista(resp);
	//ordena e retira as repetições de resp
	if (resp != NULL) {
		ordenaLista(resp);
		exibirLista(resp);
		NO* p = resp;
		while (p) {
			if(p->prox && (p->valor == p->prox->valor)){
				NO* guardar = p->prox->prox;
				free(p->prox);
				p->prox = guardar;
				continue;
			}
			p = p->prox;
    	}
	}
	return resp;
}

int main() {
	
	NO* p1 = NULL;	
	printf("Qual o tamanho da lista 1?\n");
	int n1;
	scanf("%i", &n1);
	if (n1 >= 1) {
		printf("Insira os elementos:\n");
		for (int i = 1; i <= n1; i++){
			int chave;
			scanf("%i", &chave);
			if (i == 1) { //primeira insercao
				NO* novo = (NO*)malloc(sizeof(NO));
				novo->valor = chave;
				novo->prox = NULL;
				p1 = novo;
			} else {
				anexarElemento (&p1, chave);
			}
		}
		exibirLista(p1); 
	}  	

	NO* p2 = NULL;
	printf("Qual o tamanho da lista 2?\n");
	int n2;
	scanf("%i", &n2);
	if (n2 >= 1) {
		printf("Insira os elementos:\n");
		for (int i = 1; i <= n2; i++){
			int chave;
			scanf("%i", &chave);
			if (i == 1) { //primeira insercao
				NO *novo = (NO *)malloc(sizeof(NO));
				novo->valor = chave;
				novo->prox = NULL;
				p2 = novo;
			} else {
				anexarElemento (&p2, chave);
			}
		}
		exibirLista(p2);
	} 

	NO* teste = NULL;
	teste = uniao(p1,p2);
	printf("listas unidas com sucesso\n");
	exibirLista(teste);
	return 0;
}