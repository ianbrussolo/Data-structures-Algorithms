#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	bool ocorrendo;
  int tempo;
  int nroAtualizacao;
} Atualizacao;


void exibiratualizacoes(Atualizacao atualizacoes[], int n, int info) {
	if (info == 0) {
    printf("duracao: ");
    for (int i = 0; i < n; i++)
      printf("%d ", atualizacoes[i].tempo);
  }
  if (info == 1) {
    printf("numero: ");
    for (int i = 0; i < n; i++)
      printf("%d ", atualizacoes[i].nroAtualizacao);
	}
  printf("\n");
}


void ordenarAtualizacoes (Atualizacao vetor[], int n) {
  for (int i = 0; i < n - 1 ; i++) {
    int nroAtualizacaoMenor = i;
    for (int j = i + 1; j < n; j++) {
      if (vetor[j].tempo < vetor[nroAtualizacaoMenor].tempo) 
        nroAtualizacaoMenor = j;
    }
    if (vetor[i].tempo > vetor[nroAtualizacaoMenor].tempo) {
      int auxT = vetor[i].tempo;
      vetor[i].tempo = vetor[nroAtualizacaoMenor].tempo;
      vetor[nroAtualizacaoMenor].tempo = auxT;

      int auxN = vetor[i].nroAtualizacao;
      vetor[i].nroAtualizacao = vetor[nroAtualizacaoMenor].nroAtualizacao;
      vetor[nroAtualizacaoMenor].nroAtualizacao = auxN;
    }
  }
}


void ordenarDinamico(Atualizacao atualizacoes[], int n){ 
    int i; 
    int j;
    Atualizacao aux;
    for (i = 1; i < n; i++){
        j = i - 1;
        aux = atualizacoes[i];
        while ((j >= 0) && (aux.tempo < atualizacoes[j].tempo) && atualizacoes[j].ocorrendo == false){
            atualizacoes[j + 1] = atualizacoes[j];
            j--;
        }
        atualizacoes[j + 1] = aux;
    }
}


int maxAtualizacoes (Atualizacao atualiz[], int duracao) {
  int i = 0;
  int soma = 0;
  while (soma < duracao) {
    soma = soma + atualiz[i].tempo;
    i++;
    //printf("%d ", soma);
  } 
  if (soma > duracao){
    soma -= atualiz[i].tempo;
    i--;
  }

  return i;
}


int main(int argc, char const *argv[]) {
  
  //leitura da linha de comando e do arquivo
  int duracao = atoi(argv[1]);
  int cenario = atoi(argv[2]);
  FILE *file = fopen(argv[3], "r");
  int n;
    int input[101];

  if (cenario == 1) {
    int i = 0;
    while (!feof(file)) {
      fscanf(file, "%d", &input[i]);
      i++;
    }
    fclose(file);

    //criando vetor de atualizações
    n = input[0];
    Atualizacao atualizacoes[n];
    for (int j = 1; j <= n; j++) {
      atualizacoes[j-1].tempo = input[j];
      atualizacoes[j-1].nroAtualizacao = j;
    }

    //0 - tempo; 1 - nro da atualizacao
    //exibiratualizacoes(atualizacoes, n, 0);
    //exibiratualizacoes(atualizacoes, n, 1);
    ordenarAtualizacoes(atualizacoes, n);
    //exibiratualizacoes(atualizacoes, n, 0);
    //exibiratualizacoes(atualizacoes, n, 1);

    int maxAtt = maxAtualizacoes(atualizacoes, duracao);

    file = fopen("saida1.txt", "w");
        fprintf(file, "%i ", maxAtt);
        for(i = 0; i < maxAtt; i++){
            fprintf(file, "%i ", atualizacoes[i].nroAtualizacao);
        }
        fprintf(file, "\n");
    fclose(file);
  
  }
  
  if (cenario == 2) {
    //ler 1a linha do txt
    int i;
    fscanf(file, "%d", &input[0]);
    //criando vetor de atualizações
    n = input[0];
    Atualizacao atualizacoes[n];
    for (int j = 1; j <= n; j++) {
      fscanf(file, "%i", &input[j]);
      atualizacoes[j-1].tempo = input[j];
      atualizacoes[j-1].nroAtualizacao = j;
      atualizacoes[i].ocorrendo = false;
    }
    exibiratualizacoes(atualizacoes, n, 0);
    exibiratualizacoes(atualizacoes, n, 1);
    ordenarAtualizacoes(atualizacoes, n);
    exibiratualizacoes(atualizacoes, n, 0);
    exibiratualizacoes(atualizacoes, n, 1);

    char operacao;
    while(fscanf(file, " %c", &operacao) != EOF) {
      int newDuracao = 0;
      int newHora = 0;
      int newnroAtualizacao = 0;
      if(operacao == 'c'){                
        fscanf(file, "%i %i %i\n", &newHora, &newnroAtualizacao, &newDuracao);
        if(newHora > 1){
          atualizacoes[0].ocorrendo = true;    
        }
        int totalHoras = 0;
        for (i = 0; i < n; i++) {
          totalHoras += atualizacoes[i].tempo;
          if(totalHoras > newHora){
            atualizacoes[i].ocorrendo = true;
            break;
          } 
          atualizacoes[i].ocorrendo = true;
        }
        for(i = 0; i < n; i++){
          if(atualizacoes[i].nroAtualizacao == newnroAtualizacao){
            atualizacoes[i].tempo = newDuracao;
          }
        }
        ordenarDinamico(atualizacoes, n);
        exibiratualizacoes(atualizacoes, n, 0);
        exibiratualizacoes(atualizacoes, n, 1);
      } else if(operacao == 'i'){
          fscanf(file, "%i %i %i\n", &newHora, &newnroAtualizacao, &newDuracao);
          n++;
          int nAtualizacao = newnroAtualizacao - 1;
          atualizacoes[nAtualizacao].tempo = newDuracao;
          atualizacoes[i].nroAtualizacao = i + 1;
          atualizacoes[i].ocorrendo = false;
          ordenarDinamico(atualizacoes, n);  
          exibiratualizacoes(atualizacoes, n, 0);
          exibiratualizacoes(atualizacoes, n, 1);
        } 
    }
    fclose(file);

    //arquivo de saida
    int maxAtt = maxAtualizacoes(atualizacoes, duracao);
    file = fopen("saida2.txt", "w");
    fprintf(file, "%i ", maxAtt);
    for(i = 0; i < maxAtt; i++){
      fprintf(file, "%i ", atualizacoes[i].nroAtualizacao);
    }
    fprintf(file, "\n");
    fclose(file);
    // exibiratualizacoes(atualizacoes, n, 0);
    // exibiratualizacoes(atualizacoes, n, 1);

      
      
    // exibiratualizacoes(atualizacoes, n, 0);
    // exibiratualizacoes(atualizacoes, n, 1);
    // ordenaratualizacoes(atualizacoes, n);
    // exibiratualizacoes(atualizacoes, n, 0);
    // exibiratualizacoes(atualizacoes, n, 1);
  }
}