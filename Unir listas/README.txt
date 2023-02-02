Unir duas listas ligadas simples, não circulares, sem cabeça e sem nó sentinela, eliminando as repetições e ordenando-as
1. Entrada: duas listas ligadas ordenadas (vazias ou não). Saída: nova lista ligada ordenada unindo ambas as listas (eliminando repetições)
2. A assinatura da função é a seguinte:
NO* uniao(NO* p1, NO* p2);
3. Os ponteiros fornecidos como entrada (*p1 e *p2) são o início de listas que contém inteiros em ordem crescente
Exemplo: p1={1,1,2,3,4,4} e p2={1,2,2,3,5,5}: união = {1,2,3,4,5}.
4. Restrições de implementação:
(a) Não use nenhum vetor na sua implementação. Estruturas auxiliares de implementação dinâmica podem ser utilizadas livremente, 
mas caso haja uso de qualquer tipo de estrutura estática o EP será considerado inválido.