/*
********************************************************
Computación Gráfica
GRUPO:
- Yhon yerson sanchez yucra
- Jose Gabriel Zevallos Delgado de la Flor
- Christopher Yquira Miranda

<PRESIONE P PARA VER LAS LINEAS>
*******************************************************
*/
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width,int height);
void key_callback(GLFWwindow* window,int key,int scancode,int action,int mods);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"my version opengl",NULL,NULL);
    if(window == NULL)
    {
        std::cout<<"Failed to create glfw window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glfwSetKeyCallback(window,key_callback);
    // glad: load all opengl function pouinter
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<"Failed to initialize GLAD"<<std::endl;
        return -1;
    }

    //*****************VertexShader******************
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    //**************check vertex shader*********
    int success;
    char infolog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infolog);
        std::cout<<"ERROR VERTER:_SHADER_COMPILATION"<<std::endl;
    }
    //**************CREATE AND COMPILE Fragment shadre***********
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //**************FRAGMENTSHADER**********************
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
    }
    //***********LINK SHADER*************************
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //***********check for linking errors************
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //***************END CONCIFG AND LINKED ***************
    float Aureola1[] = {
          0.0f, 0.36f, 0.0f,
          0.0f, 0.64f, 0.0f,
          0.2f, 0.6f, 0.0f,
          0.31f, 0.45f, 0.0f,
          0.32f, 0.35f, 0.0f,
          0.28f, 0.22f, 0.0f,
          0.17f, 0.16f, 0.0f,
          0.04f, 0.11f, 0.0f,
          -0.08f, 0.09f, 0.0f,
          -0.19f, 0.14f, 0.0f,
          -0.28f, 0.21f, 0.0f,
          -0.32f, 0.31f, 0.0f,
          -0.31f, 0.44f, 0.0f,
          -0.26f, 0.53f, 0.0f,
          -0.17f, 0.6f, 0.0f,
                    
        };
    unsigned int IndiceAureola1[] = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,10,
        0,10,11,
        0,11,12,
        0,12,13,
        13,0,1
    };

    float Rostro[] = {
         -0.17f, 0.37f, 0.0f,
         -0.16f, 0.27f, 0.0f,
         -0.06f, 0.32f, 0.0f,
         0.02f, 0.24f, 0.0f,
         -0.13f, 0.2f, 0.0f,
         -0.1f, 0.16f, 0.0f,
         -0.05f, 0.13f, 0.0f,
         -0.01f, 0.13f, 0.0f,
          0.04f, 0.17f, 0.0f,
         0.05f, 0.12f, 0.0f,
         0.0f, 0.1f, 0.0f 
    };
    unsigned int IndiceRostro[] = {
        0,1,2,
        1,2,3,
        3,1,4,
        3,4,5,
        3,5,6,
        3,6,7,
        3,7,8,
        7,8,9,
        7,9,10
    };


    float Tunica[] = {
        0.04f, 0.38f, 0.0f,//cero
        0.02f, 0.26f, 0.0f,
        -0.07f, 0.33f, 0.0f,
        -0.13f, 0.36f, 0.0f,
        -0.17f, 0.38f, 0.0f,
        -0.14f, 0.44f, 0.0f,
        -0.07f, 0.5f, 0.0f,
        -0.01f, 0.52f, 0.0f,
        0.07f, 0.5f, 0.0f,
        0.13f, 0.45f, 0.0f,
        0.17f, 0.4f, 0.0f,
        0.2f, 0.35f, 0.0f,
        0.14f, 0.15f, 0.0f, //DOS
        0.02f, 0.26f, 0.0f, // k1
        0.2f, 0.35f, 0.0f, //f2
        0.23f, 0.27f, 0.0f,
        0.24f, 0.13f, 0.0f,
        0.25f, 0.06f, 0.0f,
        0.06f, 0.02f, 0.0f,
        0.03f, 0.13f, 0.0f,//=================
        0.0f, 0.1f, 0.0f, //h120
        -0.04f, 0.06f, 0.0f, //L
        0.09f, -0.03f, 0.0f,
        0.07f, -0.41f, 0.0f, //UNO23
        0.28f, -0.09f, 0.0f,
        0.3f, -0.24f, 0.0f,
        0.26f, -0.44f, 0.0f,
        0.22f, -0.54f, 0.0f,
        0.13f, -0.57f, 0.0f,
        0.0f, -0.57f, 0.0f,
        -0.07f, -0.56f, 0.0f,
        -0.14f, -0.53f, 0.0f,
        -0.19f, -0.48f, 0.0f,
        -0.22f, -0.37f, 0.0f, //P1
        -0.1f, -0.35f, 0.0f,
        -0.01f, -0.27f, 0.0f,
        -0.09f, -0.2f, 0.0f,
        0.06f, -0.17f, 0.0f

    };
    unsigned int IndiceTunica[] = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,10,
        0,10,11,
        0,11,1,
        12,13,14,
        12,14,15,
        12,15,16, 
        12,16,17,
        12,17,18,
        12,18,19,
        12,19,13,//===========
        18,19,20,
        18,20,21,
        17,18,22,
        23,22,17,
        23,17,24,
        23,24,25,
        23,25,26,
        23,26,27,
        23,27,28,
        23,28,29,
        23,29,30,
        23,30,31,
        23,31,32,
        23,32,33,
        23,33,34,
        23,34,35,
        23,35,36,
        23,36,37,
        23,37,22
 };
     float Aureola2[] = {
         -0.07f, -0.08f,0.0f,//c0
         -0.14f, 0.03f,0.0f, //O
         -0.2f, -0.03f,0.0f,   //R
         -0.2f, -0.13f,0.0f,
         -0.13f, -0.18f,0.0f,
         -0.06f, -0.2f,0.0f,
          0.06f, -0.17f,0.0f,
         0.09f, -0.13f,0.0f,
         0.1f, -0.06f,0.0f,
         0.07f, 0.0f,0.0f,
         0.01f, 0.05f,0.0f,
         -0.06f, 0.05f,0.0f,
         -0.07f, -0.08f,0.0f
    };
    unsigned int IndiceAureola2[] = {  // note that we start from 0!
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,10,
        0,10,11,
        0,11,1
 };

      float Cabello[] = {
         -0.06f, 0.38f,0.0f,//c0
         -0.14f, 0.45f,0.0f,//Z
         -0.16f, 0.41f,0.0f,
         -0.17f, 0.36f,0.0f,
         -0.13f, 0.35f,0.0f,
         -0.1f, 0.34f,0.0f,
         -0.07f, 0.32f,0.0f,
         -0.03f, 0.29f,0.0f,
         0.03f, 0.23f,0.0f,
         -0.01f, 0.33f,0.0f,
         -0.02f, 0.36f,0.0f,
         -0.04f, 0.39f,0.0f,
         -0.08f, 0.42f,0.0f
    };
    unsigned int IndiceCabello[] = {  // note that we start from 0!
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,10,
        0,10,11,
        0,11,1
 };
     float Cuadro[] = {
         -0.46f, 0.64f, 0.0f,
         0.44f, 0.64f, 0.0f,
         0.44f, -0.57f, 0.0f,
         -0.45f, -0.57f, 0.0f
    };
    unsigned int IndiceCuadro[] = {
        0,1,2,
        2,3,0
    };

    float Ninio[] = {
         -0.02f, -0.13f, 0.0f, 
        -0.1f, -0.13f, 0.0f,//1
        -0.07f, -0.11f, 0.0f,
        0.0f, -0.1f, 0.0f,
        0.04f, -0.08f, 0.0f,
        0.05f, -0.12f, 0.0f,
        0.02f, -0.16f, 0.0f,
        0.0f, -0.17f, 0.0f,
        -0.01f, -0.19f, 0.0f,
        -0.04f, -0.19f, 0.0f,//9
        -0.09f, -0.26f, 0.0f, //CEN10
        -0.01f, -0.27f, 0.0f,
        -0.08f, -0.34f, 0.0f,
        -0.12f, -0.33f, 0.0f,
        -0.15f, -0.31f, 0.0f,
        -0.18f, -0.27f, 0.0f,
        -0.19f, -0.24f, 0.0f,
        -0.17f, -0.22f, 0.0f,
        -0.11f, -0.22f, 0.0f,//18
        -0.09f, -0.19f, 0.0f,
        -0.07f, -0.16f, 0.0f,
        -0.11f, -0.17f, 0.0f,
        -0.15f, -0.13f, 0.0f,
        -0.17f, -0.16f, 0.0f
    };
    unsigned int IndiceNinio[] = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,1,
        10,9,11,
        10,11,12,
        10,12,13,
        10,13,14,
        10,14,15,
        10,15,16,
        10,16,17,
        10,17,18,
        10,18,9,
        18,9,19,
        9,19,20,
        19,20,21,
        20,21,1,
        1,21,22,
        23,22,21
    };

    float CabelloNinio[] = {
        -0.07f, -0.08f, 0.0f,
        -0.17f, -0.11f, 0.0f,
        -0.12f, -0.06f, 0.0f,
        -0.07f, -0.01f, 0.0f,
        -0.02f, -0.0f, 0.0f,
        0.03f, -0.02f, 0.0f,
        0.05f, -0.06f, 0.0f,
        0.04f, -0.08f, 0.0f,
        0.0f, -0.1f, 0.0f,
        -0.07f, -0.11f, 0.0f,
        -0.1f, -0.13f, 0.0f,
        -0.15f, -0.13f, 0.0f
    };
    unsigned int IndiceCabelloNinio[] = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,10,
        0,10,11,
        0,11,1
    };

    float ManoMabre[] = {
        -0.22f,-0.2f,0.0f,
        -0.1f, -0.03f, 0.0f,
        -0.15f, -0.02f, 0.0f,
        -0.22f, -0.15f, 0.0f,
        -0.24f, -0.2f, 0.0f,
        -0.25f, -0.25f, 0.0f,
        -0.24f, -0.3f, 0.0f,
        -0.23f, -0.34f, 0.0f,
        -0.22f, -0.38f, 0.0f,
        -0.17f, -0.36f, 0.0f,
        -0.13f, -0.36f, 0.0f,
        -0.1f, -0.35f, 0.0f,
        -0.18f, -0.23f, 0.0f,
        -0.14f, -0.22f, 0.0f,
        -0.1f, -0.21f, 0.0f,
        -0.09f, -0.18f, 0.0f,
        -0.11f, -0.17f, 0.0f,
        -0.16f, -0.17f, 0.0f,
        -0.19f, -0.17f, 0.0f

    };
    unsigned int IndiceManoMadre[] = {//19
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,10,
        0,10,11,
        0,11,12,
        0,12,13,
        0,13,14,
        0,14,15,
        0,15,16,
        0,16,17,
        0,17,18,
        0,18,1
    };

    float LineasCuadro[] = {
        -0.46f, 0.64f, 0.0f,
        0.44f, 0.64f, 0.0f,

        0.44f, 0.64f, 0.0f,
        0.44f, -0.57f, 0.0f,

        0.44f, -0.57f, 0.0f,
        -0.45f, -0.56f, 0.0f,

        -0.45f, -0.56f, 0.0f,
         -0.46f, 0.64f, 0.0f,
        ////line1
        -0.43,0.64f,0.0f,
        -0.32f,-0.55f,0.0f,
        ////line2
        -0.45f,-0.02,0.0f,
        -0.31f,0.03,0.0f,
        -0.31f,0.03,0.0f,
        -0.06f,0.1,0.0f,
        ////linea3
        0.25f,0.1,0.0f,
        0.43f,0.06,0.0f,
        ////linea 4
        -0.45f, 0.13f, 0.0f,
        -0.34f, 0.21f, 0.0f,
        
        -0.34f, 0.21f, 0.0f,
        -0.19f, 0.37f, 0.0f,

        -0.19f, 0.37f, 0.0f,
        -0.1f, 0.5f, 0.0f,

        -0.1f, 0.5f, 0.0f,
        -0.03f, 0.63f, 0.0f,

        -0.46f, 0.48f, 0.0f,
        0.07f, 0.33f, 0.0f,

        0.07f, 0.33f, 0.0f,
        0.43f, -0.52f, 0.0f,

        -0.45f, -0.38f, 0.0f,
        0.15f, 0.63f, 0.0f,

        -0.13f, -0.56f, 0.0f,
        0.42f, 0.37f, 0.0f
    };
    float vertices[] = {
        0.17f, 0.16f, 0.0f,  
        0.17f, 0.26f, 0.0f, 
        0.08f, 0.4f, 0.0f,
        -0.02f, 0.46f, 0.0f, 
        -0.13f, 0.45f, 0.0f,
        -0.02f, 0.41f, 0.0f,
        0.13f, 0.11f, 0.0f,
        0.11f, -0.36f, 0.0f,
        0.2f, -0.12f, 0.0f,
        0.23f, 0.08f, 0.0f,
        0.24f, 0.13f, 0.0f,

        -0.02f,-0.35f,0.0f,//11
        0.0f,-0.25f,0.0f,
        -0.07f,-0.37f,0.0f,
        -0.19f,-0.46f,0.0f,
        -0.15f,-0.52f,0.0f,
        -0.04f,-0.56f,0.0f,
        -0.03f,-0.45f,0.0f

    };
    unsigned int IndiceVertices[] = {//19
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,10,
        0,10,1,

        11,12,13,
        11,13,14,
        11,14,15,
        11,15,16,
        11,16,12
    };
    //*****array para dos figuras y EBO para un indice
    unsigned int VBO[11], VAO[11], EBO,TRI,FG3,FG4,FG5,FG6,FG7,FG8,FG9,FG10;
    glGenVertexArrays(11, VAO);
    glGenBuffers(11, VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &TRI);
    glGenBuffers(1, &FG3);
    glGenBuffers(1, &FG4);
    glGenBuffers(1, &FG5);//marco
    glGenBuffers(1, &FG6);//niño
    glGenBuffers(1, &FG7);//cabelloniño
    glGenBuffers(1, &FG8);//manomadre
    glGenBuffers(1, &FG9);//manomadre
    glGenBuffers(1, &FG10);//manomadre
    
    //**********primera figura en VAO[0]******    
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Aureola1), Aureola1, GL_STATIC_DRAW);
    //********indcies para la figura en VAO[0]******
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceAureola1), IndiceAureola1, GL_STATIC_DRAW);
    //*********pointer para la figura VAO[0]************
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //**********segunda figura en VAO[1]**************
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Rostro), Rostro, GL_STATIC_DRAW);
    //***********creamos el indice*****************
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TRI);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceRostro), IndiceRostro, GL_STATIC_DRAW);
    //**************pointer para nuestro triangulo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //**********segunda figura en FG3[1]**************
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Tunica), Tunica, GL_STATIC_DRAW);
    //***********creamos el indice*****************
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, FG3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceTunica), IndiceTunica, GL_STATIC_DRAW);
    //**************pointer para nuestro triangulo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

     //**********segunda figura en FG3[1]**************
    glBindVertexArray(VAO[3]);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Aureola2), Aureola2, GL_STATIC_DRAW);
    //***********creamos el indice*****************
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, FG4);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceAureola2), IndiceAureola2, GL_STATIC_DRAW);
    //**************pointer para nuestro triangulo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

     //**********segunda figura en FG3[1]**************
    glBindVertexArray(VAO[4]);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Cabello), Cabello, GL_STATIC_DRAW);
    //***********creamos el indice*****************
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, FG5);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceCabello), IndiceCabello, GL_STATIC_DRAW);
    //**************pointer para nuestro triangulo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //*******************MARCO**********************
    //**********segunda figura en FG5[1]**************
    glBindVertexArray(VAO[5]);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Cuadro), Cuadro, GL_STATIC_DRAW);
    //***********creamos el indice*****************
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, FG6);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceCuadro), IndiceCuadro, GL_STATIC_DRAW);
    //**************pointer para nuestro triangulo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //**********segunda figura en FG5[1]**************
    glBindVertexArray(VAO[6]);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[6]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Ninio), Ninio, GL_STATIC_DRAW);
    //***********creamos el indice*****************
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, FG6);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceNinio), IndiceNinio, GL_STATIC_DRAW);
    //**************pointer para nuestro triangulo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //**********segunda figura en FG5[1]**************
    glBindVertexArray(VAO[7]);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[7]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CabelloNinio), CabelloNinio, GL_STATIC_DRAW);
    //***********creamos el indice*****************
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, FG7);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceCabelloNinio), IndiceCabelloNinio, GL_STATIC_DRAW);
    //**************pointer para nuestro triangulo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //**********segunda figura en FG5[1]**************
    glBindVertexArray(VAO[8]);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[8]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ManoMabre), ManoMabre, GL_STATIC_DRAW);
    //***********creamos el indice*****************
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, FG8);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceManoMadre), IndiceManoMadre, GL_STATIC_DRAW);
    //**************pointer para nuestro triangulo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[9]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[9]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(LineasCuadro), LineasCuadro, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	
    glEnableVertexAttribArray(0);


    //**********segunda figura en FG5[1]**************
    glBindVertexArray(VAO[10]);
    glBindBuffer(GL_ARRAY_BUFFER,VBO[10]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //***********creamos el indice*****************
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, FG10);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceVertices), IndiceVertices, GL_STATIC_DRAW);
    //**************pointer para nuestro triangulo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glPointSize(10);
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        //**********Marco *******
        glLineWidth(5.0f);
        glUniform4f(vertexColorLocation, 1.0f, 0.2f, 0.2f, 0.0f);
        glBindVertexArray(VAO[5]);
        glDrawElements(GL_TRIANGLES,7,GL_UNSIGNED_INT,0);

        glUniform4f(vertexColorLocation, 1.0f, 1.0f, 0.0f, 0.0f);
        //**********Aureola_madre*******
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES,39,GL_UNSIGNED_INT,0);
        //glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 0.0f);
        //glDrawElements(GL_LINE_STRIP,39,GL_UNSIGNED_INT,0);


                //Lineas del cuadrado
        glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 0.0f);
        glBindVertexArray(VAO[9]);
        glLineWidth(5.0f);
        glDrawArrays(GL_LINES, 0,100);

         glUniform4f(vertexColorLocation, 0.98f, 0.4f, 0.3f, 0.0f);
        //**********Cara_madre********
        //glLineWidth(7.0f);
        glBindVertexArray(VAO[1]);
        glDrawElements(GL_TRIANGLES,27,GL_UNSIGNED_INT,0);

        glUniform4f(vertexColorLocation, 0.0f, 0.2f, 0.6f, 1.0f);
        //**********Tunica_madre********
        glBindVertexArray(VAO[2]);
        glDrawElements(GL_TRIANGLES,111,GL_UNSIGNED_INT,0);

        //**********Aureola_niño *******
        glUniform4f(vertexColorLocation, 1.0f, 1.0f, 0.0f, 0.0f);
        glBindVertexArray(VAO[3]);
        glDrawElements(GL_TRIANGLES,33,GL_UNSIGNED_INT,0);

        glUniform4f(vertexColorLocation, 0.3f, 0.0f, 0.0f, 1.0f);
        //**********Cabello********
        glBindVertexArray(VAO[4]);
        glDrawElements(GL_TRIANGLES,33,GL_UNSIGNED_INT,0);

        glUniform4f(vertexColorLocation, 0.98f, 0.5f, 0.3f, 0.0f);
        //**********Niño********
        //glLineWidth(7.0f);
        glBindVertexArray(VAO[6]);
        glDrawElements(GL_TRIANGLES,72,GL_UNSIGNED_INT,0);

        glUniform4f(vertexColorLocation, 0.4f, 0.0f, 0.0f, 1.0f);
        //**********Cabello_niño********
        glBindVertexArray(VAO[7]);
        glDrawElements(GL_TRIANGLES,33,GL_UNSIGNED_INT,0);

         glUniform4f(vertexColorLocation, 0.98f, 0.4f, 0.3f, 0.0f);
        //**********Mano_madre********
        //glLineWidth(7.0f);
        glBindVertexArray(VAO[8]);
        glDrawElements(GL_TRIANGLES,55,GL_UNSIGNED_INT,0);


        glUniform4f(vertexColorLocation, 0.3f, 0.2f, 0.6f, 1.0f);
        //**********Mano_madre********
        //glLineWidth(7.0f);
        glBindVertexArray(VAO[10]);
        glDrawElements(GL_TRIANGLES,48,GL_UNSIGNED_INT,0);

            if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
            {
                glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
                glLineWidth(5.0f);

                glBindVertexArray(VAO[10]);
                glDrawElements(GL_LINE_STRIP,48,GL_UNSIGNED_INT,0);

                glBindVertexArray(VAO[8]);
                glDrawElements(GL_LINE_STRIP,55,GL_UNSIGNED_INT,0);


                //**********Cabello_niño********
                glBindVertexArray(VAO[7]);
                glDrawElements(GL_LINE_STRIP,33,GL_UNSIGNED_INT,0);


                        //Lineas del cuadrado

                glBindVertexArray(VAO[9]);
                glLineWidth(3.0f);
                glDrawArrays(GL_LINES, 0,100);

        
                //**********Cara_madre********
                //glLineWidth(7.0f);
                glBindVertexArray(VAO[1]);
                glDrawElements(GL_LINE_STRIP,27,GL_UNSIGNED_INT,0);

        
                //**********Tunica_madre********
                glBindVertexArray(VAO[2]);
                glDrawElements(GL_LINE_STRIP,111,GL_UNSIGNED_INT,0);

                //**********Aureola_niño *******
            
                glBindVertexArray(VAO[3]);
                glDrawElements(GL_LINE_STRIP,33,GL_UNSIGNED_INT,0);

            
                //**********Cabello********
                glBindVertexArray(VAO[4]);
                glDrawElements(GL_LINE_STRIP,33,GL_UNSIGNED_INT,0);

        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(3,VAO);
    glDeleteBuffers(3,VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteBuffers(1,&TRI);
    glDeleteBuffers(1,&FG3);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
    


}
