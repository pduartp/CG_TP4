# CG_TP4

## DESCRIÇÃO ## 

Vocês irão trabalhar com os seguintes temas em CG:
- Modelagem Hierárquica
- Transformações geométricas e posicionamento de câmeras
- Mapeamento de Textura
- Iluminação
- Animação
  
A primeira parte é necessária para introduzir o assunto sobre mapeamento de texturas em OpenGL e consistirá em
resolver uma pequena lista de exercícios sobre o assunto (5pts). Exercicos_Mapeamento_Textura_OpenGL.zip

PARA TRABALHAR COM TEXTURAS, ao invés de usar a função *LoadBMP,  vocês farão uso de uma biblioteca para carregar 
imagens que se mostrou mais estável e sem necessidade de instalação de bibliotecas adicionais (como a glaux). 
Trata-se da biblioteca STB_IMAGE que não requer instalação, apenas a inclusão de um arquivo .h e um pequeno código 
objeto junto a pasta do seu projeto (ambos os arquivos estão incluidos aqui na descrição do trabalho). As instruções 
de uso estão no arquivo stb_image.h, mas trata-se de um processo bem simples. Por exemplo, para ler uma imagem 
pode-se usar uma função como esta a seguir:

           (unsigned char*) img_data = stbi_load(filename, &width, &height, &channels, 3);

(vou forcer a implementação de uma função para isto em um arquivo .cpp)

Não se esqueçam de incluir no início do arquivo em que a biblioteca stb_image será utilizada os comandos:
          #define STB_IMAGE_IMPLEMENTATION 
          #include "stb_image.h"

Alguns exemplos e informações adicionais sobre o uso de texturas em OpenGL podem ser encontradas no seguinte endereço:
https://learnopengl.com/getting-started/textures

A segunda parte tem como objetivo proporcionar um maior conhecimento na área de modelagem geométrica e animação 
utilizando Modelagem Hierárquica em OpenGL. vocês terão que melhorar e documentar um trabalho que realiza uma 
animação de um cavalo em um ambiente externo arborizado.

Para ajudar no processo, são disponibilizados dois trabalhos práticos já desenvolvidos:
(T1) o código de um trabalho meu de CG (onde é modelado um robô humanoide) ( Trab2-Wagner.zip)
(T2) e o código de um trabalho realizado por três alunos da UFSC em 2004, onde é modelado um 
cavalo no bosque em OpenGL. (CavaloOpenGLDanielEduardoJose.zip)

O objetivo de vocês é unir as qualidades de navegação e movimentação de câmera de T1  com o modelo desenvolvido 
em T2. A este último, vocês irão melhorar a aparência final do modelo adicionando alguma textura e iluminação a 
ele (como no exercício da primeira parte)  e, com a ajuda das técnicas usadas em T1, permitir uma melhor interação 
do usuário. 

Deverá ser entregue:
- um Código funcional em C/C++ bem modularizado, com funções de câmera como aquelas desenvolvidas em T1, de fácil manipulação
  e comentado de forma adequada, sem excessos.
- um pequeno manual de uso do programa desenvolvido e uma descrição tanto da arvore do modelo hierárquico 3D do cavalo,
  quanto das informações referentes ao entendimento de como a câmera se move em torno do objeto alvo (ilustre como a camera
  fica em torno do objeto à medida que ele se move e como se dá a modificação da posição da câmera usando os comandos
  disponíveis no teclado para aproximar, afastar e rotacionar em torno do objeto).
