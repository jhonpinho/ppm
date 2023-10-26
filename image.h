
#include <stdio.h>
typedef struct imagem Imagem;
typedef struct pixel_rgb PixelRGB;
void liberarImagem(Imagem *imagem);
Imagem *criarImagem(int linhas, int colunas, const char *tipo);
void imprimirImagem(Imagem *imagem);
Imagem *carregarArquivo(const char *nome_do_arquivo);
void colorida_para_cinza(Imagem *imagem_colorida, Imagem *imagem_cinza);
void escrever_em_ppm(Imagem *imagem, const char *nome_do_arquivo);