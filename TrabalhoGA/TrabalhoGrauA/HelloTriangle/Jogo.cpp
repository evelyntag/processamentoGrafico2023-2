#include "Jogo.h"
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//STB_IMAGE
#include <stb_image.h>

//Classe para manipula��o dos shaders
#include "Shader.h"

//Classe Sprite 
#include "Sprite.h"

//Classe Timer
#include "Timer.h"

Jogo::Jogo() {}

Jogo::~Jogo() {}

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 600;

Sprite personagem;
Sprite buraco;

// Fun��o MAIN
void Jogo::inicializacao()
{
	// Inicializa��o da GLFW
	glfwInit();

	// Cria��o da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Cuidado! Buraco na via... - Evelyn Tag e Pedro Henrique Fleck", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da fun��o de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informa��es de vers�o
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
	int width, height;

	// Compilando e buildando o programa de shader
	Shader shader("../shaders/helloTriangle.vs", "../shaders/helloTriangle.fs");

	shader.Use();

	int larguraPersonagem, alturaPersonagem, larguraBuraco, alturaBuraco, larguraFundo, alturaFundo;

	//Fazendo a leitura da textura do personagem
	int texID = setupTexture("../../Textures/characters/PNG/car.png", larguraPersonagem, alturaPersonagem);

	//Fazendo a leitura da textura de fundo
	int texID2 = setupTexture("../../Textures/backgrounds/PNG/street.jpg", larguraFundo, alturaFundo);

	//Fazendo a leitura da textura do buraco
	int texID3 = setupTexture("../../Textures/hole.png", larguraBuraco, alturaBuraco);

	// Criando a instância de nosso objeto sprite do Personagem
	personagem.initialize(1, 1);
	personagem.setPosition(glm::vec3(150.0, 300.0, 0.0));
	personagem.setDimensions(glm::vec3(larguraPersonagem / 2, alturaPersonagem / 2, 1.0));
	personagem.setShader(&shader);
	personagem.setTexID(texID);

	// Criando a instância de nosso objeto sprite do Personagem
	buraco.initialize(1, 1);
	buraco.setPosition(glm::vec3(540.0, 300.0, 0.0));
	buraco.setDimensions(glm::vec3(larguraBuraco / 3, alturaBuraco / 3, 1.0));
	buraco.setShader(&shader);
	buraco.setTexID(texID3);

	//Criando a instância de nosso objeto sprite do fundo (background)
	Sprite background;
	background.initialize(1, 1);
	background.setPosition(glm::vec3(400.0, 300.0, 0.0));
	background.setDimensions(glm::vec3(larguraFundo, alturaFundo / 1.5, 1.0));
	background.setShader(&shader);
	background.setTexID(texID2);

	//Cria a matriz de projeção paralela ortog�fica
	glm::mat4 projection = glm::mat4(1); //matriz identidade
	projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

	shader.setMat4("projection", glm::value_ptr(projection));
	shader.setInt("texbuffer", 0);

	glActiveTexture(GL_TEXTURE0);

	//Habilitando a transpar�ncia
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Habilitando o teste de profundidade
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	Timer timer;

	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		timer.start();

		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		// Recuperando o tamanho da janela da aplica��o
		glfwGetFramebufferSize(window, &width, &height);
		// Dimensiona a viewport
		glViewport(0, 0, width, height);


		//-------------------------------------------------------------
		background.update();
		background.draw();
		//-------------------------------------------------------------

		//-------------------------------------------------------------
		buraco.update();
		buraco.draw();
		//--------------------------------------------------------------

		//-------------------------------------------------------------
		personagem.update();
		personagem.draw();
		//--------------------------------------------------------------

		timer.finish();
		double waitingTime = timer.calcWaitingTime(24, timer.getElapsedTimeMs());
		if (waitingTime)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds((int)waitingTime));
			buraco.moveLeft();
			checkColisao();
			checkFinal();
		}

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}

	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
}

// Fun��o de callback de teclado - s� pode ter uma inst�ncia (deve ser est�tica se
// estiver dentro de uma classe) - � chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void Jogo::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_W || key == GLFW_KEY_UP)
	{
		personagem.moveUp();
	}
	else if (key == GLFW_KEY_S || key == GLFW_KEY_DOWN)
	{
		personagem.moveDown();
	}
}

int Jogo::setupTexture(string filePath, int& width, int& height)
{
	GLuint texID;
	// Gera��o do identificador do buffer
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Configurando par�metro de wrapping da textura em s e t
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Configurando o par�metro de filtering de magnifica��o e minifica��o da textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int nrChannels;
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		if (nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

	}
	else
	{
		cout << "Erro ao ler a textura!" << endl;
		return -1;
	}

	return texID;
}

void Jogo::checkColisao()
{
	int margemX = 150, margemY = 50;

	if (
		personagem.getPositionX() + margemX >= buraco.getPositionX() &&
		personagem.getPositionX() - margemX <= buraco.getPositionX() &&
		personagem.getPositionY() <= buraco.getPositionY() + margemY &&
		personagem.getPositionY() >= buraco.getPositionY() - margemY
	) 
	{
		personagem.setPosition(glm::vec3(150.0, 300.0, 0.0));
		buraco.setPosition(glm::vec3(700.0, 300.0, 0.0));
		buraco.resetaVelocidadeX();
	}
}

void Jogo::checkFinal()
{
	if (buraco.getPositionX() + 50 <= 0) {
		buraco.setPosition(glm::vec3(700.0, personagem.getPositionY(), 0.0));
		buraco.aumentaVelocidadeX();
	}
}
