#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Definindo uma estrutura 'pixel_rgb'
typedef struct pixel_rgb {
  unsigned char r, g, b;
} PixelRGB;
// Definindo uma estrutura 'imagem'
typedef struct imagem {
// tipo p2 (cinza) ou p3(colorida);
  char tipo_imagem[3];
  int colunas;
  int linhas;
 // valor maximo de pixels
  int valor_maximo; 
// ponteiro void * para permitir acomodar tanto uma matriz p2 quanto p3.
  void ***pixels;            
} Imagem;
//Função que cria uma imagem a partir dos parametros linhas,colunas e tipo.
Imagem *criarImagem(int linhas, int colunas, const char *tipo) {
//Aloca dinamicamente o tamanho da nova imagem.
  Imagem *imagem = (Imagem *)malloc(sizeof(Imagem));
//Retornar NULL caso a imagem seja vazia.
  if (imagem == NULL) {
    return NULL;
  }
//Recebimento de dados na estrutura com base nos parâmetros da função.
  imagem->colunas = colunas;
  imagem->linhas = linhas;
  imagem->valor_maximo = 255; 
//copia o valor da string tipo p/ o ponteiro tipo_imagem da estrutura imagem
  strncpy(imagem->tipo_imagem, tipo, sizeof(imagem->tipo_imagem));
//Cria um inteiro 'tamanho_pixel' e usa strcmp para comparar se é P3, P2 ou NULL.
  int tamanho_pixel;
  if (strcmp(tipo, "P3") == 0) {
    tamanho_pixel = 3;
  } else if (strcmp(tipo, "P2") == 0) {
    tamanho_pixel = 1;
  } else {
    free(imagem);
    return NULL;
  }
//Aloca memória dinamicamente dos pixels da imagem para criar a matriz.
  imagem->pixels = (void ***)malloc(linhas * sizeof(void **));
  if (imagem->pixels == NULL) {
    free(imagem);
    return NULL;
  }

  for (int i = 0; i < linhas; i++) {
    imagem->pixels[i] = (void **)malloc(colunas * sizeof(void *));
    if (imagem->pixels[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(imagem->pixels[j]);
      }
      free(imagem->pixels);
      free(imagem);
      return NULL;
    }
    for (int j = 0; j < colunas; j++) {
      imagem->pixels[i][j] = malloc(tamanho_pixel);
      if (imagem->pixels[i][j] == NULL) {
        for (int k = 0; k < colunas; k++) {
          free(imagem->pixels[i][k]);
        }
        for (int l = 0; l < i; l++) {
          for (int m = 0; m < colunas; m++) {
            free(imagem->pixels[l][m]);
          }
          free(imagem->pixels[l]);
        }
        free(imagem->pixels);
        free(imagem);
        return NULL;
      }
    }
  }

  return imagem;
} 
//Função que carrega uma imagem .ppm para a memória.
Imagem *carregarArquivo(const char *nome_do_arquivo) {
//Abertura do arquivo no modo leitura.
  FILE *arquivo = fopen(nome_do_arquivo, "r");
//Condição para caso o arquivo ppm esteja vazio.
  if (arquivo == NULL) {
    return 0; 
  }
//Definição de variáveis para criar a imagem na memória.
  char tipos[3];
  int coluna, linha, valor_pixel;

  // Lê o tipo de imagem (P2 ou P3) do cabeçalho.
  fscanf(arquivo, "%s", tipos);
  const char *tipo = tipos;
  // Lê as dimensões da imagem.
  fscanf(arquivo, "%d %d", &coluna, &linha);
  // Lê o valor máximo de pixel.
  fscanf(arquivo, "%d", &valor_pixel);
  //Cria a imagem a partir dos dados retirados do arquivo .ppm.
  Imagem *imagem = criarImagem(linha, coluna, tipos);
  if (imagem == NULL) {
    fclose(arquivo);
    return NULL;
  }
// cria variável tamanho_pixel e atribui tamanho 3 caso seja p3 
// ou tamanho 1 caso seja p2
   int tamanho_pixel;
  if (strcmp(tipo, "P3") == 0) {
    tamanho_pixel = 3;
  } else if (strcmp(tipo, "P2") == 0) {
    tamanho_pixel = 1;
  } else {
    fclose(arquivo);
    free(imagem);
    return NULL;
  }

  // Preenche os pixels com os valores do arquivo.
  for (int i = 0; i < linha; i++) {
    for (int j = 0; j < coluna; j++) {
      if (tamanho_pixel == 1) {
        unsigned char *pixel = imagem->pixels[i][j];
        fscanf(arquivo, " %hhu", pixel);
      } else {
        PixelRGB *pixel = imagem->pixels[i][j];
        fscanf(arquivo, " %hhu %hhu %hhu", &pixel->r, &pixel->g, &pixel->b);
      }
    }
  }

  fclose(arquivo);

  return imagem;
}


void colorida_para_cinza(Imagem *imagem_colorida, Imagem *imagem_cinza) {
 // Cria imagem cinza com as mesmas dimensoes (linha,coluna,) da imagem RGB.
  imagem_cinza = criarImagem(imagem_colorida->linhas, imagem_colorida->colunas, "P2");
// Caso uma das imagens sejam nulas emite erro.
  if (imagem_colorida == NULL || imagem_cinza == NULL) {
    printf("Erro: Uma das imagens é nula.\n");
    return;
  }
// Caso não se tratem de imagens P3 e P2 emite erro.
  if (strcmp(imagem_colorida->tipo_imagem, "P3") != 0 ||
      strcmp(imagem_cinza->tipo_imagem, "P2") != 0) {
    printf("Erro: Tipos de imagem inválidos. A imagem de entrada deve ser P3 e "
           "a imagem de saída deve ser P2.\n");
    return;
  }
// Caso não tenha as mesmas dimensoes linhas x colunas emite erro.
  if (imagem_colorida->colunas != imagem_cinza->colunas ||
      imagem_colorida->linhas != imagem_cinza->linhas) {
    printf("Erro: As dimensões das imagens são diferentes. Elas devem ter as "
           "mesmas dimensões.\n");
    return;
  }
// realiza a conversão dos pixels RGB P/ cinza
  for (int i = 0; i < imagem_colorida->linhas; i++) {
    for (int j = 0; j < imagem_colorida->colunas; j++) {
      PixelRGB *pixel_colorido = ((PixelRGB ***)imagem_colorida->pixels)[i][j];
      int nivel_de_cinza = (int)(0.299 * pixel_colorido->r + 0.587 * pixel_colorido->g +0.114 * pixel_colorido->b);
      ((unsigned char **)imagem_cinza->pixels)[i][j] =
          (unsigned char)nivel_de_cinza;
     
    }
  }

}

void imprimirImagem(Imagem *imagem) {
  // Se a imagem for nula emite erro
  if (imagem == NULL) {
    printf("Imagem inválida.\n");
    return;
  }
  // imprime tipo da imagem, dimensões e valor máx. do pixel
  printf("Tipo de Imagem: %s\n", imagem->tipo_imagem);
  printf("Dimensões: %d x %d\n", imagem->colunas, imagem->linhas);
  printf("Valor Máximo de Pixel: %d\n", imagem->valor_maximo);
  
  
  // cria variável tamanho_pixel e atribui tamanho 3 caso seja p3 
  // ou tamanho 1 caso seja p2
  int tamanho_pixel;
  if (strcmp(imagem->tipo_imagem, "P3") == 0) {
    tamanho_pixel = 3;
  } else if (strcmp(imagem->tipo_imagem, "P2") == 0) {
    tamanho_pixel = 1;
  } else {
    printf("Tipo de imagem inválido.\n");
    return;
  }
// printa cada item da matriz, levando em conta tamanho do pixel 
//  (tanmanho 1 = matriz p2, tamanho 3 = matriz p3)
  for (int i = 0; i < imagem->linhas; i++) {
    for (int j = 0; j < imagem->colunas; j++) {
      if (tamanho_pixel == 3) {
        PixelRGB *pixel = ((PixelRGB ***)imagem->pixels)[i][j];
        printf("(%d, %d, %d) ", pixel->r, pixel->g, pixel->b);
      } else {
        unsigned char pixel = ((unsigned char **)imagem->pixels)[i][j];
        printf("%d ", pixel);
      }
    }
    printf("\n");
  }
}

void escrever_em_ppm(Imagem *imagem, const char *nome_do_arquivo) {
    FILE *arquivo = fopen(nome_do_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve o cabeçalho P2 ou P3 no arquivo com base no tipo de imagem.
    if (strcmp(imagem->tipo_imagem, "P2") == 0) {
        fprintf(arquivo, "P2\n");
    } else if (strcmp(imagem->tipo_imagem, "P3") == 0) {
        fprintf(arquivo, "P3\n");
    } else {
        printf("Tipo de imagem não suportado.\n");
        fclose(arquivo);
        return;
    }

    // Escreve as dimensões da imagem.
    fprintf(arquivo, "%d %d\n", imagem->colunas, imagem->linhas);

    // Escreve o valor máximo de pixel.
    fprintf(arquivo, "%d\n", imagem->valor_maximo);

    // Escreve os valores dos pixels da imagem.
    if (strcmp(imagem->tipo_imagem, "P2") == 0) {
        for (int i = 0; i < imagem->linhas; i++) {
            for (int j = 0; j < imagem->colunas; j++) {
                fprintf(arquivo, "%d ", ((unsigned char **)imagem->pixels)[i][j]);
            }
            fprintf(arquivo, "\n");
        }
    } else if (strcmp(imagem->tipo_imagem, "P3") == 0) {
        for (int i = 0; i < imagem->linhas; i++) {
            for (int j = 0; j < imagem->colunas; j++) {
                PixelRGB *pixel = ((PixelRGB ***)imagem->pixels)[i][j];
                fprintf(arquivo, "%d %d %d ", pixel->r, pixel->g, pixel->b);
            }
            fprintf(arquivo, "\n");
        }
    }

    fclose(arquivo);
}

