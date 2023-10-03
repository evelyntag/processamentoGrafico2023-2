*Lista 1*
*Evelyn Tag*

1.	O que é a GLSL? Quais os dois tipos de shaders são obrigatórios no pipeline programável da versão atual que trabalhamos em aula e o que eles processam?
GLSL é a linguagem de programação que usaremos para o desenvolvimento de shaders dentro do pipeline do OpenGL, GLSL vem de GL Shading Language e é baseada em C. Os dois tipos de shaders obrigatórios no pipeline são o Vertex Shader e o Fragment Shader, sendo o primeiro para o tratamento do vértice e o segundo para o tratamento da área.

2.	O que são primitivas gráficas? Como fazemos o armazenamento dos vértices na OpenGL?
São elementos básicos que compõem um desenho no OpenGL contamos com os seguintes: GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_TRIANGULOS, GL_TRIANGLE_STRIP e GL_TRIANGLE_FAN. Vertex Buffer Objects (VBO) são usados para armazenar dados de vértices (coordenadas, cores, normais e outros dados relevantes), os quais são necessários para desenhar geometria na tela.

3.	Explique o que é VBO, VAO e EBO, e como se relacionam (se achar mais fácil, pode fazer um gráfico representando a relação entre eles).
Vertex Buffer Objects (VBO) é um array de dados dos vértices que será enviado a GPU, o Vertex Array Objects (VAO) define qual VBO será utilizado, a localização dos dados do mesmo e o formato dos dados. Já Element Buffer Objects (EBO), associa a ideia de índices e evita a especificação de vértices replicados no VBO.

4.	Analise o código fonte do projeto Hello Triangle. Localize e relacione os conceitos de shaders, VBOs e VAO apresentados até então. Não precisa entregar nada neste exercício.

5.	Faça o desenho de 2 triângulos na tela. Desenhe eles:
a.	Apenas com o polígono preenchido

 ![image](https://github.com/evelyntag/processamentoGrafico2023-2/assets/142860203/4aade2b2-c2c7-45fb-9ca8-1ae80549a7b0)

b.	Apenas com contorno

 ![image](https://github.com/evelyntag/processamentoGrafico2023-2/assets/142860203/554deb69-6ba6-4ae1-91b8-cd3af848634a)

c.	Apenas como pontos

 ![image](https://github.com/evelyntag/processamentoGrafico2023-2/assets/142860203/b8bd61d4-837b-4ba6-b3bf-af72f0d9b9d8)

d.	Com as 3 formas de desenho juntas

 ![image](https://github.com/evelyntag/processamentoGrafico2023-2/assets/142860203/b64f6e51-fa32-4c9d-9666-ab5cd3998efe)

6.	Faça o desenho de um círculo na tela, utilizando a equação paramétrica do círculo para gerar os vértices. Depois disso:
a.	Desenhe um octágono

 ![image](https://github.com/evelyntag/processamentoGrafico2023-2/assets/142860203/5f5fab0b-15fd-4c88-9c43-b33da94d8001)

b.	Desenhe um pentágono

 ![image](https://github.com/evelyntag/processamentoGrafico2023-2/assets/142860203/7153c117-c13a-45c9-bef9-231def124026)

c.	Desenhe um pac-man!

 ![image](https://github.com/evelyntag/processamentoGrafico2023-2/assets/142860203/91e15c87-924c-4fa8-9696-26c4ea449b7c)

d.	Desenhe uma fatia de pizza

 ![image](https://github.com/evelyntag/processamentoGrafico2023-2/assets/142860203/f5325fbd-e624-4671-88db-ea648eafefc4)

e.	DESAFIO: desenhe uma “estrela”

![image](https://github.com/evelyntag/processamentoGrafico2023-2/assets/142860203/8fb5135e-064d-46d4-8549-8100e7c01bcf)

7.	Desenhe uma espiral, assim:
   
 ![image](https://github.com/evelyntag/processamentoGrafico2023-2/assets/142860203/3ba9df49-dcf0-4a5e-86ec-b4b29c9f0601)

8.	Considerando o seguinte triângulo abaixo, formado pelos vértices P1, P2 e P3, respectivamente com as cores vermelho, verde e azul.
a. Descreva uma possível configuração dos buffers (VBO, VAO e EBO) para representá-lo.
b. Como estes atributos seriam identificados no vertex shader?
Agora implemente!

 ![image](https://github.com/evelyntag/processamentoGrafico2023-2/assets/142860203/cfeb0422-d8f5-4d41-945a-53d28cf6a43e)

9.	Faça um desenho em um papel quadriculado (pode ser no computador mesmo) e reproduza-o utilizando primitivas em OpenGL. Neste exercício você poderá criar mais de um VAO e fazer mais de uma chamada de desenho para poder utilizar primitivas diferentes, se necessário.
    
![image](https://github.com/evelyntag/processamentoGrafico2023-2/assets/142860203/4c4ed516-afe3-42db-a0b1-75c7e26d47bb)
