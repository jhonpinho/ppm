#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int escolha;
  char nomeDoArquivo[200];
  char nomeDoArquivo2[200];
  Imagem *imagem_carregada = NULL;
  Imagem *imagem_cinza = NULL;
  char tipo;

  do {
    printf("Menu:\n");
    printf("1. Carregar imagem\n");
    printf("2. Converter para niveis de cinza\n");
    printf("3. Gravar imagem\n");
    printf("4. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);

    switch (escolha) {
    case 1:
      printf("Digite o caminho para a imagem : ");
      scanf(" %s", nomeDoArquivo);
      imagem_carregada = carregarArquivo(nomeDoArquivo);
      if (imagem_carregada == NULL) {
        printf("Falha ao carregar o arquivo.\n");
      } else {
        printf("Imagem carregada com sucesso!\n");
        imprimirImagem(imagem_carregada);
      }
      break;

    case 2:
      if (imagem_carregada == NULL) {
        printf("Nenhuma imagem carregada.\n");
      } else {
        printf("Imagem alterada com sucesso!\n");
        colorida_para_cinza(imagem_carregada, imagem_cinza);
        imprimirImagem(imagem_cinza);
      }
      break;

    case 3:
      printf("Digite o nome do arquivo: ");
      scanf("%s", nomeDoArquivo2);
      escrever_em_ppm(imagem_carregada, nomeDoArquivo2);
      break;

    case 4:
      break;

    default:
      printf("Opção inválida.\n");
      break;
    }

  } while (escolha != 4);


  return 0;
}
