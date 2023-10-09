#pragma once

#include "Shader.h"
#include "Sprite.h"
#include <vector>

using namespace std;

class Jogo {
public:
    Jogo();
    ~Jogo();
    void inicializacao();

private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    int setupTexture(string filePath, int& width, int& height);

    void checkColisao();
    void checkFinal();

    GLFWwindow* window;
    Shader* shader;
    glm::mat4 projection;

    vector <Sprite*> objects;
};