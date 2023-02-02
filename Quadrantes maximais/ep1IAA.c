#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void imprimeMatriz(int tamanho, int matriz[tamanho][tamanho]) {
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }
}

int contaQuad (int tamOrig, char matriz[tamOrig][tamOrig], int linIni, int colIni, int tamanho, int brancos[(int)log2(tamOrig)], int pretos[(int)log2(tamOrig)]) {
  if (tamanho == 1) {
    if (matriz[linIni][colIni] == 0) pretos[0]++; // guarda os quadrantes maximais 1x1 pretos no vetor resposta
    else if (matriz[linIni][colIni] == 1) brancos[0]++; // "" brancos
    return matriz[linIni][colIni]; 
  } 

  int primeiroQuad = contaQuad (tamOrig, matriz, linIni, colIni, tamanho/2, brancos, pretos);
  int segundoQuad = contaQuad (tamOrig, matriz, linIni, colIni + tamanho/2, tamanho/2, brancos, pretos);
  int terceiroQuad = contaQuad (tamOrig, matriz, linIni + tamanho/2, colIni, tamanho/2, brancos, pretos);
  int quartoQuad = contaQuad (tamOrig, matriz, linIni + tamanho/2, colIni + tamanho/2, tamanho/2, brancos, pretos);

  int i = (int) log2(tamanho);
  if (primeiroQuad + segundoQuad + terceiroQuad + quartoQuad == 0) { //maximal preto
    pretos[i]++;
    pretos[i - 1] = pretos[i - 1] - 4; //retira os maximais já considerados anteriormente
  }
  else if (primeiroQuad + segundoQuad + terceiroQuad + quartoQuad == tamanho*tamanho) {  //maximal branco
    brancos[i]++;
    brancos[i - 1] = brancos[i - 1] - 4;
  }   

  return primeiroQuad + segundoQuad + terceiroQuad + quartoQuad;
} 

int main(int argc, char const *argv[]) {
  
  int tamanho = atoi(argv[1]);
  FILE *file = fopen(argv[2], "r");

  char matriz[tamanho][tamanho];
  char elemento;
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      elemento = fgetc(file);
      if (elemento == '\n') elemento = fgetc(file); 
      if (elemento == '0') matriz[i][j] = 0;
      else if (elemento == '1') matriz[i][j] = 1;
    }
  } 

  //2^0 = 1x1; 2^1 = 2x2; 2^2 = 4x4; ... 2^n = 2^nx2^n
  int tamanhoVetor = (int)log2(tamanho) + 1;

  int brancos[tamanhoVetor]; 
  int pretos [tamanhoVetor];

  int j, i;
  for (i = 0; i < tamanhoVetor; i++) {
    brancos[i] = 0;
    pretos[i] = 0;
  }

  contaQuad(tamanho, matriz, 0, 0, tamanho, brancos, pretos);
  for (i = tamanhoVetor - 1; i >= 0; i--) {
    j = pow(2, i);
    printf("%ix%i %i %i\n", j, j, brancos[i], pretos[i]); 
  }  

  fclose(file);
  return 0;
}
