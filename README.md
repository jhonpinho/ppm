# Implementação de um Tipo Abstrato de Dados para Manipulação de Imagens no Formato PPM
# Introdução
Este trabalho foi desenvolvido pelos alunos Jhon Pinho e Lucas Lopes para a matéria de Estrutura de Dados, lecionada pelo professor Thiago Paixão no Instituto Federal do Espírito Santo. O objetivo do programa é o de construir um TAD que possui como funcionalidade principal converter uma imagem colorida no formato PPM (p3), em uma imagem PPM em tons cinza (p2).
# Funcionalidades do Programa
O código desenvolvido na linguagem C possui 4 funções : CriarImagem, CarregarArquivo, colorida_para_cinza e escrever_em_ppm. A função CriarImagem tem como funcionalidade alocar na memória espaço para os dados da imagem ppm. Já a função carregar arquivo lê o arquivo ppm externo e passa os dados do arquivo para o objeto tipo Imagem da aplicação. A função colorida_para_cinza converte os pixels de uma Imagem colorida carregada na memória para que a Imagem se torne cinza. Por último, a função escrever_em_ppm escreve os dados de uma imagem carregada no programa num arquivo externo.
# Funcionamento do Programa
Ao rodar o programa, um menu de opções aparecerá para o usuário. O usuário deverá inserir a opção que deseja. 
- Caso o usuário opte pela opção 1 " Carregar imagem " , o usuário deverá inserir o caminho para a imagem. A imagem será então carregada do caminho para a memória. Após isso, será mostrado na tela a imagem que foi carregada e o usuário voltará ao menu principal.
- Caso o usuário opte pela opção 2 " Converter para niveis de cinza ", uma imagem deverá ter sido carregada previamente, do contrário, o programa retornará um erro. Caso já possua uma imagem carregada, o programa retornará um imprime de uma nova imagem cinza da imagem ( Nota: Não conseguimos mudar o conteúda da imagem colorida em si, por isso ele imprime uma nova imagem). Após isso, o usuário retornará ao menu principal.
- Caso o usuário opte pela opção 3 " Gravar imagem" , O usuário deverá inserir o nome do arquivo.ppm a ser gerado. Após isso, um novo arquivo será gravado no diretório do programa, contendo a imagem já gravada previamente. O usuário voltará ao programa principal.
- Caso o usuário opte pela opção 4 "Sair" , o programa se encerrará.


