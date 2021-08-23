#include <glad/glad.h>
#include <glfw/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "shader_s.h"
#include "Rubik.hpp"
#include "camera.h"

#include <iostream>
#include <vector>
#include <cstring>
#include <string.h>

using namespace std;
using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;    

//******************************************************************************
//*******        para compilar copie la direcion del proyecto 
//******************************************************************************

string mainPath =  "C:\\Users\\Jose Gabriel\\Documents\\C.Computacion\\2021-I\\Computacion Grafica\\GLFW_GLAD_GLUT_GLEW_cmake_project\\src\\hw\\";
glm::vec3 upVector = glm::vec3(0.0f, 0.0f, 1.0f);
glm::mat4 model1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
unsigned int VBO[27], VAO[27];
unsigned int textures[6];
bool presionado = false;
                                   //D Yellow       U White         B Blue         F Green          L Orange        R RED
vector<vector<float>> colores = { {1.0, 1.0, 0.0}, {1.0,1.0,1.0},{0.0, 0.0, 1.0},{0.0, 1.0, 0.0},{1.0, 0.647, 0.0}, {1.0, 0.0, 0.0} };




//Camera camera(glm::vec3(5.0f, 5.0f, 3.0f));
Camera camera(glm::vec3(3.0f, 3.0f, 15.0f));

//Camera camera(glm::vec3(5.0f, 5.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


float intervalo = 1.1;      //intervalo entre cubos


int getIndex(char side) {
    int ind;
    switch (side) {
    case 'D':
        ind = 0;
        break;
    case 'U':
        ind = 1;
        break;
    case 'B':
        ind = 2;
        break;
    case 'F':
        ind = 3;
        break;
    case 'L':
        ind = 4;
        break;
    case 'R':
        ind = 5;
        break;
    default:
        ind = -1;
        break;
    }
    return ind;
}


//ROTACIONES
int anguloDividido = 10;
float angulo = 90.0f;

void rotateVec(mat4& model, vec3 val) {  //count 2000 veces como m�ximo
    //rotaci�n en eje origen del mundo
    mat4 nuevo(1.0f);
    nuevo= glm::rotate(nuevo,glm::radians(angulo / anguloDividido), val);
    model = nuevo * model;
}

//hace que gire en el eje "x, y, z" del mundo
void rotateVecSame(mat4& model, vec3 val) {
    mat4 nuevo(1.0f);
    nuevo = glm::rotate(nuevo, glm::radians(angulo / anguloDividido), val);
    model = nuevo * model;
    //hace que gire en el eje "x, y, z" del mundo
}



void menu() {
    cout << "Controlar la Camara  :" << endl;
    cout << "   W:       para acercarte" << endl;
    cout << "   S:       para alejarte" << endl;
    cout << "   A:       para mover la camara a la izquierda" << endl;
    cout << "   D:       para mover la camara a la derecha" << endl;
    cout << endl;

    cout << "----GIROS DE LAS CARAS: " << endl;
    cout << " En sentido horario: " << endl;
    cout << "   F:       para mover la cara amarilla" << endl;
    cout << "   G:       para mover la cara blanca" << endl;
    cout << "   H:       para mover la cara azul" << endl;
    cout << "   J:       para mover la cara verde" << endl;
    cout << "   K:       para mover la cara naranja" << endl;
    cout << "   L:       para mover la cara roja" << endl;
    cout << " En sentido antihorario: " << endl;
    cout << "   Z:       para mover la cara amarilla" << endl;
    cout << "   X:       para mover la cara blanca" << endl;
    cout << "   C:       para mover la cara azul" << endl;
    cout << "   V:       para mover la cara verde" << endl;
    cout << "   B:       para mover la cara naranja" << endl;
    cout << "_------Solver-----------------" << endl;
    cout << "   T:       Resolver el cubo" << endl;
    cout << "-------ANIMACIONES---------------"<<endl;
    cout << "   1:       Expandir" << endl;
    cout << "   2:       Detener Expandir" << endl;
    cout << "   3:       Contraer" << endl;
    cout << "   4:       Detener Contraer" << endl;
    cout << "   Y:       Una Expansion" << endl;
    cout << "   U:       Una contracion" << endl;
    cout << "   I:       Rotar en cruz" << endl;
}

vector<float> vertices0 = {
        //  D            U       B           F       L         R
        //amarillo T   blanco    azul      verde T    naranja   rojo

        -0.5f, -0.5f, -0.5f,    0.0,0.0, 0.0,      1.0f, 0.0f,      //I1
         0.5f, -0.5f, -0.5f,     0.0,0.0, 0.0,     0.0f, 0.0f,      //D1               //  DOWN
         0.5f,  0.5f, -0.5f,    0.0,0.0, 0.0,      0.0f, 1.0f,      //I2

         0.5f,  0.5f, -0.5f,    0.0,0.0, 0.0,     0.0f, 1.0f,       //I2
        -0.5f,  0.5f, -0.5f,    0.0,0.0, 0.0,     1.0f, 1.0f,       //D2
        -0.5f, -0.5f, -0.5f,    0.0,0.0, 0.0,    1.0f, 0.0,       //I1

        -0.5f, -0.5f,  0.5f,     0.0,0.0, 0.0,     0.0f, 0.0f,      //I1
         0.5f, -0.5f,  0.5f,    0.0,0.0, 0.0,     1.0f, 0.0f,       //D1                    //UP FACE
         0.5f,  0.5f,  0.5f,     0.0,0.0, 0.0,     1.0f, 1.0f,      //I2
         0.5f,  0.5f,  0.5f,     0.0,0.0, 0.0,     1.0f, 1.0f,      //I2
        -0.5f,  0.5f,  0.5f,    0.0,0.0, 0.0,     1.0f, 1.0f,       //D2
        -0.5f, -0.5f,  0.5f,    0.0,0.0, 0.0,     0.0f, 0.0f,       //I1

        -0.5f,  0.5f, -0.5f,     0.0,0.0, 0.0,     0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,     0.0,0.0, 0.0,     1.0f, 1.0f,          //BOT
        -0.5f, -0.5f,  0.5f,     0.0,0.0, 0.0,     1.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,     0.0,0.0, 0.0,     1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,     0.0,0.0, 0.0,     0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,     0.0,0.0, 0.0,     0.0f, 1.0f,



         0.5f, -0.5f, -0.5f,       0.0,0.0, 0.0,     1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,      0.0,0.0, 0.0,      0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,       0.0,0.0, 0.0,     0.0f, 1.0f,

         0.5f,  0.5f,  0.5f,      0.0,0.0, 0.0,      0.0f, 1.0f,        //FRONT maybe
         0.5f,  0.5f, -0.5f,      0.0,0.0, 0.0,      1.0f, 1.0f,        //cara de al frente
         0.5f, -0.5f, -0.5f,      0.0,0.0, 0.0,    1.0f, 0.0,



        -0.5f, -0.5f, -0.5f,       0.0,0.0, 0.0,      1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,       0.0,0.0, 0.0,     1.0f, 1.0f,        //Left
         0.5f, -0.5f,  0.5f,       0.0,0.0, 0.0,     0.0f, 1.0f,

         0.5f, -0.5f,  0.5f,       0.0,0.0, 0.0,     0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,       0.0,0.0, 0.0,     0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,       0.0,0.0, 0.0,     1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,       0.0,0.0, 0.0,     0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,       0.0,0.0, 0.0,     0.0f, 0.0f,        //Right
         0.5f,  0.5f,  0.5f,       0.0,0.0, 0.0,     1.0f, 0.0f,        //cara derecha
         0.5f,  0.5f,  0.5f,       0.0,0.0, 0.0,     1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,       0.0,0.0, 0.0,     1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,       0.0,0.0, 0.0,     0.0f, 1.0f
};

class cubie
{
public:
    unsigned int idVAO;
    mat4 model;
    vec3 puntoInicial;
    vector<float> vertices;
    vector<bool> carasActivas;                      //D U B F L R
    vector<int> carasColores;                       //D U B F L R           cada uno con su colo, -1 si no tiene color
    vec3 direccion;

    cubie()=default;
    cubie(vec3 point, int id);

    void configVertex();                                //configura el VAO, VBO
    void drawing(Shader* myShader);                     //dibuja el cubie
    int setFace(char side);                          //coloca true en el vector y te devuelve el �ndice
    void setColors();
    void setTextures(int indexCara, int index);


private:

};

cubie::cubie(vec3 point,int id) {
    idVAO = id;
    //getting initial point
    puntoInicial = point;
    //setting model
    model = mat4(1.0f);

    model = glm::translate(model, puntoInicial);

    vertices = vertices0;

    carasActivas.resize(6);
    fill(carasActivas.begin(), carasActivas.end(), false);

    //inicializando carasColores en -1
    vector<int> carasColoresTemp(6, -1);
    carasColores = carasColoresTemp;

    direccion = vec3(0.0, 0.0, 0.0);
}

void cubie::drawing(Shader* myShader) {

    //Setting nwew matrix 1 VAO0
    myShader->setMat4("model", model);
    // render box
    /*
    int in = 0;
    glBindVertexArray(VAO[idVAO]);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    */
    int in = 0;
    glBindVertexArray(VAO[idVAO]);
    for (int i = 0; i < 36; i += 6) {
        glBindTexture(GL_TEXTURE_2D, textures[in]);
        myShader->setInt("texture1", in);
        textures[in++];
        glDrawArrays(GL_TRIANGLES, i, 6);

    }
    configVertex();
}




int cubie::setFace(char side) {
    int ind;
    switch (side) {
    case 'D':
        ind = 0;
        break;
    case 'U':
        ind = 1;
        break;
    case 'B':
        ind = 2;
        break;
    case 'F':
        ind = 3;
        break;
    case 'L':
        ind = 4;
        break;
    case 'R':
        ind = 5;
        break;
    default:
        ind = -1;
        break;
    }
    carasActivas[ind] = true;
    carasColores[ind] = ind;
    return ind;
}


void cubie::setColors() {
    for (int i = 0; i < carasColores.size(); i++) {     //i: 0 1 2 3 4 5
        if (carasColores[i] != -1) {        //si es diferente a negro
            int indice = i * 6;
            indice *= 8;
            indice += 3;
            for (int j = 0; j < 6; j++, indice += 8) {
                vertices[indice] = colores[carasColores[i]][0];
                vertices[indice + 1] = colores[carasColores[i]][1];
                vertices[indice + 2] = colores[carasColores[i]][2];

            }
        }
    }

}


void cubie::setTextures(int indexCara, int index)       //indexCara es la cara a la que pertenece, index es el nro de cubo
{
    vector<vector<pair<float, float>>> texturas;
    if (indexCara == 0 || indexCara == 3 ) {
        texturas = {
                { make_pair(1.0f , 0.0f),make_pair(1.0f , 0.333f),make_pair(0.666f , 0.0f),  make_pair(0.666f , 0.333f) },         //6
                { make_pair(0.333f , 0.0f), make_pair(0.333f , 0.333f),make_pair(0.666f , 0.0f),make_pair(0.666f , 0.333f)  },     //3
                { make_pair(0.333f, 0.0f),make_pair(0.333f, 0.333f),make_pair(0.0f, 0.0f),  make_pair(0.0f, 0.333f) },       //0
                { make_pair(1.0f , 0.333f), make_pair(1.0f , 0.666f), make_pair(0.666f , 0.333f),  make_pair(0.666f , 0.666f) },     //7
                { make_pair(0.666f , 0.333f), make_pair(0.666f , 0.666f),make_pair(0.333f , 0.333f),  make_pair(0.333f , 0.666f) },     //4
                { make_pair(0.333f , 0.333f), make_pair(0.333f , 0.666f),make_pair(0.0f , 0.333f),  make_pair(0.0f , 0.666f) },     //1
                { make_pair(1.0f , 0.666f), make_pair(1.0f , 1.0f), make_pair(0.666f , 0.666f),  make_pair(0.666f , 1.0f) },          //8
                { make_pair(0.666f , 0.666f),make_pair(0.666f , 1.0f), make_pair(0.333f , 0.666f),  make_pair(0.333f , 1.0f) },         //5
                { make_pair(0.333f , 0.666f), make_pair(0.333f , 1.0f), make_pair(0.0f , 0.666f),  make_pair(0.0f , 1.0f) },         //2


        };

    }
    else {
        if (indexCara == 5) {
            texturas = {
            {    make_pair(0.333f, 0.333f), make_pair(0.0f, 0.333f),make_pair(0.333f, 0.0f), make_pair(0.0f, 0.0f)},
            {  make_pair(0.333f , 0.666f), make_pair(0.0f , 0.666f),make_pair(0.333f , 0.333f),make_pair(0.0f , 0.333f) },
            {   make_pair(0.333f , 1.0f),make_pair(0.0f , 1.0f),make_pair(0.333f , 0.666f), make_pair(0.0f , 0.666f) },

            { make_pair(0.666f , 0.333f),make_pair(0.333f , 0.333f),make_pair(0.666f , 0.0f),make_pair(0.333f , 0.0f)    },
            {  make_pair(0.666f , 0.666f),make_pair(0.333f , 0.666f),make_pair(0.666f , 0.333f),make_pair(0.333f , 0.333f)  },
            {  make_pair(0.666f , 1.0f), make_pair(0.333f , 1.0f),make_pair(0.666f , 0.666f), make_pair(0.333f , 0.666f) },

            { make_pair(1.0f , 0.333f),make_pair(0.666f , 0.333f),make_pair(1.0f , 0.0f),make_pair(0.666f , 0.0f) },
            {  make_pair(1.0f , 0.666f), make_pair(0.666f , 0.666f),make_pair(1.0f , 0.333f), make_pair(0.666f , 0.333f) },
            { make_pair(1.0f , 1.0f), make_pair(0.666f , 1.0f),make_pair(1.0f , 0.666f),make_pair(0.666f , 0.666f) }
            };
        }
        else {
            if (indexCara == 1 ) {
                texturas = {
                { make_pair(0.666f , 0.0f),  make_pair(0.666f , 0.333f),make_pair(1.0f , 0.0f),make_pair(1.0f , 0.333f) },         //6

                { make_pair(0.666f , 0.0f),make_pair(0.666f , 0.333f),make_pair(0.333f , 0.0f), make_pair(0.333f , 0.333f)  },     //3
                { make_pair(0.0f, 0.0f),  make_pair(0.0f, 0.333f),make_pair(0.333f, 0.0f),make_pair(0.333f, 0.333f) },       //0


                { make_pair(0.666f , 0.333f),  make_pair(0.666f , 0.666f),make_pair(1.0f , 0.333f), make_pair(1.0f , 0.666f) },     //7
                { make_pair(0.333f , 0.333f),  make_pair(0.333f , 0.666f),make_pair(0.666f , 0.333f), make_pair(0.666f , 0.666f) },     //4
                { make_pair(0.0f , 0.333f),  make_pair(0.0f , 0.666f),make_pair(0.333f , 0.333f), make_pair(0.333f , 0.666f) },     //1

                { make_pair(0.666f , 0.666f),  make_pair(0.666f , 1.0f), make_pair(1.0f , 0.666f), make_pair(1.0f , 1.0f) },          //8
                { make_pair(0.333f , 0.666f),  make_pair(0.333f , 1.0f),make_pair(0.666f , 0.666f),make_pair(0.666f , 1.0f) },         //5
                { make_pair(0.0f , 0.666f),  make_pair(0.0f , 1.0f),make_pair(0.333f , 0.666f), make_pair(0.333f , 1.0f) },         //2


                };
            }
            else {
                if (indexCara == 2 ) {
                    texturas = {
                { make_pair(0.666f , 0.333f),make_pair(0.666f , 0.0f),make_pair(1.0f , 0.333f),make_pair(1.0f , 0.0f) },         //6

                {make_pair(0.666f , 0.333f), make_pair(0.666f , 0.0f), make_pair(0.333f , 0.333f),make_pair(0.333f , 0.0f)  },     //3
                {   make_pair(0.0f, 0.333f),make_pair(0.0f, 0.0f),make_pair(0.333f, 0.333f), make_pair(0.333f, 0.0f) },       //0


                { make_pair(0.666f , 0.666f),make_pair(0.666f , 0.333f), make_pair(1.0f , 0.666f),make_pair(1.0f , 0.333f) },     //7
                {   make_pair(0.333f , 0.666f),make_pair(0.333f , 0.333f), make_pair(0.666f , 0.666f),make_pair(0.666f , 0.333f) },     //4
                {   make_pair(0.0f , 0.666f),make_pair(0.0f , 0.333f), make_pair(0.333f , 0.666f),make_pair(0.333f , 0.333f) },     //1

                {   make_pair(0.666f , 1.0f),make_pair(0.666f , 0.666f), make_pair(1.0f , 1.0f), make_pair(1.0f , 0.666f) },          //8
                {   make_pair(0.333f , 1.0f),make_pair(0.333f , 0.666f),make_pair(0.666f , 1.0f),make_pair(0.666f , 0.666f) },         //5
                {   make_pair(0.0f , 1.0f),make_pair(0.0f , 0.666f), make_pair(0.333f , 1.0f),make_pair(0.333f , 0.666f) },         //2


                    };
                }
                else {
                    texturas = {
                    { make_pair(1.0f , 0.0f),make_pair(0.666f , 0.0f),  make_pair(1.0f , 0.333f),make_pair(0.666f , 0.333f) },         //6

                    { make_pair(0.333f , 0.0f),make_pair(0.666f , 0.0f), make_pair(0.333f , 0.333f),make_pair(0.666f , 0.333f)  },     //3
                    { make_pair(0.333f, 0.0f),make_pair(0.0f, 0.0f),make_pair(0.333f, 0.333f),  make_pair(0.0f, 0.333f) },       //0


                    { make_pair(1.0f , 0.333f), make_pair(0.666f , 0.333f), make_pair(1.0f , 0.666f),  make_pair(0.666f , 0.666f) },     //7
                    { make_pair(0.666f , 0.333f),make_pair(0.333f , 0.333f), make_pair(0.666f , 0.666f),  make_pair(0.333f , 0.666f) },     //4
                    { make_pair(0.333f , 0.333f),make_pair(0.0f , 0.333f), make_pair(0.333f , 0.666f),  make_pair(0.0f , 0.666f) },     //1

                    {  make_pair(1.0f , 0.666f), make_pair(0.666f , 0.666f), make_pair(1.0f , 1.0f),  make_pair(0.666f , 1.0f) },          //8
                    {make_pair(0.666f , 0.666f),make_pair(0.333f , 0.666f),make_pair(0.666f , 1.0f),   make_pair(0.333f , 1.0f) },         //5
                    {make_pair(0.333f , 0.666f), make_pair(0.0f , 0.666f), make_pair(0.333f , 1.0f),   make_pair(0.0f , 1.0f) },         //2


                    };
                }
            }

        }
    }


    int indice = indexCara * 6; //colocando en la fila inicial de la cara   0 - 6 - 12 - ... - 30
    indice *= 8;    //colocando el
    indice += 6;   //colocandolo en el primer color
    //cambiando los colores  en las 6 filas que pertenecen a la cara    estan en el �ndice  3(empezando con 0)

    vertices[indice] = texturas[index][0].first;            //I1
    vertices[indice + 1] = texturas[index][0].second;

    indice += 8;

    vertices[indice] = texturas[index][2].first;            //D1
    vertices[indice + 1] = texturas[index][2].second;

    indice += 8;

    vertices[indice] = texturas[index][3].first;            //I2
    vertices[indice + 1] = texturas[index][3].second;

    indice += 8;

    vertices[indice] = texturas[index][3].first;            //I2
    vertices[indice + 1] = texturas[index][3].second;

    indice += 8;

    vertices[indice] = texturas[index][1].first;            //D2
    vertices[indice + 1] = texturas[index][1].second;

    indice += 8;

    vertices[indice] = texturas[index][0].first;            //I1
    vertices[indice + 1] = texturas[index][0].second;


}


bool texture=0;

void cubie::configVertex() {

    glBindVertexArray(VAO[idVAO]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[idVAO]);
    glBufferData(GL_ARRAY_BUFFER, vertices0.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color  attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    if(texture){
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

}



class RubikCube
{
public:
    cubie* cubos[27];
    vector<vector<cubie*>> caras;                           //D U B F L R
    vector<pair<bool,bool>> animaciones;                    //clock? , animation?
    Shader* myShader;
    int contador = 0;
    string solving;
    string disordered;
    bool solved, proceso;
    bool animando;
    bool procesoExplotar, explotarVariable;
    bool rotar_cubos = false;

    RubikCube(Shader &nuevo);
    RubikCube();

    void reloj(vector<cubie*>& cara, vector<cubie*>& cara1, vector<cubie*>& cara2, vector<cubie*>& cara3, vector<cubie*>& cara4, vector<int> indices);    //cambiar en orden del reloj
    void contrarreloj(vector<cubie*>& cara, vector<cubie*>& cara1, vector<cubie*>& cara2, vector<cubie*>& cara3, vector<cubie*>& cara4, vector<int> indices);
    void setInitialPoints();
    void vertexConfig();                                    //config all VAO VBO
    void drawing();
    void moveTo();
    void setRotation(bool clock, int face);
    void solvingCube();
    void solve();
    void running();
    void insertMovement(bool clock, int face);

    //animaciones de Expandir y contraer los cubos
    void Expandir();
    void Contraer();
    void animar_Explota_Contrae();

    //Rotar cubos al rededor de la cruz
    void rotar_cruz();
    void animar_rotacion();


private:

};
RubikCube* cuboPrincipal;

RubikCube::RubikCube() {
}

RubikCube::RubikCube(Shader &nuevo) {
    myShader = &nuevo;
    int RR = 6, CC = 9;
    vector<vector<cubie*>> matrix(RR, vector<cubie*>(CC));
    caras = matrix;
    vector<pair<bool, bool>> animacionesTemp(6, make_pair( false,false ));
    animaciones = animacionesTemp;
    solved = true;
    proceso = false;
    animando = false;
    procesoExplotar = false;

    setInitialPoints();

}



//cambiando posiciones correctas de cada cara
//cara es la que se mueve, cara 1 2 3 4 son las
void RubikCube::reloj(vector<cubie*>& cara, vector<cubie*>& cara1, vector<cubie*>& cara2, vector<cubie*>& cara3, vector<cubie*>& cara4,vector<int> indices) {
    vector<cubie*> temp(9);
    vector<int> index = {
        //2,5,8,1,4,7,0,3,6             //indices contrarreloj
        6,3,0,7,4,1,8,5,2             //indices reloj
    };
    //cambiando el orden de los cubos de la nueva cara al dar la vuelta
    for (int i = 0; i < index.size(); i++) {
        temp[i] = cara[index[i]];
    }
    cara = temp;
    vector<cubie*> cara1Temp=cara1, cara2Temp = cara2,cara3Temp = cara3, cara4Temp = cara4;


    //cara 1 recibe 3 cubitos de la cara 4
    cara1Temp[indices[0]] = cara4[indices[9]];
    cara1Temp[indices[1]] = cara4[indices[10]];
    cara1Temp[indices[2]] = cara4[indices[11]];
    //cara 2 recibe 3 cubitos de la cara 1
    cara2Temp[indices[3]] = cara1[indices[0]];
    cara2Temp[indices[4]] = cara1[indices[1]];
    cara2Temp[indices[5]] = cara1[indices[2]];
    //cara 3 recibe 3 cubitos de la cara 2
    cara3Temp[indices[6]] = cara2[indices[3]];
    cara3Temp[indices[7]] = cara2[indices[4]];
    cara3Temp[indices[8]] = cara2[indices[5]];
    //cara 4 recibe 3 cubitos de la cara 3
    cara4Temp[indices[9]] = cara3[indices[6]];
    cara4Temp[indices[10]] = cara3[indices[7]];
    cara4Temp[indices[11]] = cara3[indices[8]];

    cara1 = cara1Temp;
    cara2 = cara2Temp;
    cara3 = cara3Temp;
    cara4 = cara4Temp;

}
//cambiando posiciones correctas de cada cara
//cara es la que se mueve, cara 1 2 3 4 son las
void RubikCube::contrarreloj(vector<cubie*>& cara, vector<cubie*>& cara1, vector<cubie*>& cara2, vector<cubie*>& cara3, vector<cubie*>& cara4, vector<int> indices) {
    vector<cubie*> temp(9);
    vector<int> index = {
        2,5,8,1,4,7,0,3,6             //indices contrarreloj
        //6,3,0,7,4,1,8,5,2             //indices reloj
    };
    //cambiando el orden de los cubos de la nueva cara al dar la vuelta
    for (int i = 0; i < index.size(); i++) {
        temp[i] = cara[index[i]];
    }
    cara = temp;
    vector<cubie*> cara1Temp = cara1, cara2Temp = cara2, cara3Temp = cara3, cara4Temp = cara4;


    //cara 1 recibe 3 cubitos de la cara 2
    cara1Temp[indices[0]] = cara2[indices[3]];
    cara1Temp[indices[1]] = cara2[indices[4]];
    cara1Temp[indices[2]] = cara2[indices[5]];
    //cara 2 recibe 3 cubitos de la cara 3
    cara2Temp[indices[3]] = cara3[indices[6]];
    cara2Temp[indices[4]] = cara3[indices[7]];
    cara2Temp[indices[5]] = cara3[indices[8]];
    //cara 3 recibe 3 cubitos de la cara 4
    cara3Temp[indices[6]] = cara4[indices[9]];
    cara3Temp[indices[7]] = cara4[indices[10]];
    cara3Temp[indices[8]] = cara4[indices[11]];
    //cara 4 recibe 3 cubitos de la cara 1
    cara4Temp[indices[9]]  = cara1[indices[0]];
    cara4Temp[indices[10]] = cara1[indices[1]];
    cara4Temp[indices[11]] = cara1[indices[2]];




    cara1 = cara1Temp;
    cara2 = cara2Temp;
    cara3 = cara3Temp;
    cara4 = cara4Temp;

}



void RubikCube::setInitialPoints() {
    //punto inicial de donde se dibuja
    vec3 init = vec3(-1.1, -1.1, -1.1);
    vector<vec3> puntos;
    vec3 capa = init;

    //generando 3 matrices de 3 x 3 para el cubo
    for (int k = 0; k < 3; k++) {
        vec3 fila = capa;
        for (int j = 0; j < 3; j++) {
            puntos.push_back(fila);
            vec3 columna = fila;
            //creando dos cubos avanzando en eje x
            for (int i = 0; i < 2; i++) {
                //avanza la columna
                columna = columna + vec3(intervalo, 0.0, 0.0);
                puntos.push_back(columna);
            }
            fila = fila + vec3(0.0, intervalo, 0.0);
        }
        capa = capa + vec3(0.0, 0.0, intervalo);
    }

    //Creando 27 cubos peque�os
    for (int i = 0; i < puntos.size(); i++) {
        cubos[i] = new cubie(puntos[i], i);
    }

    //Colocando que tienen el lado Down activo      0 1 2 3 4 5... 8
    char lado = 'D';
    for (int i = 0,cont=0; i < 9; i++,cont++) {
        cubos[i]->setFace(lado);
    }

    //Colocando que tienen el lado Up activo
    lado = 'U';
    for (int i = 18,cont=0; i < 27; i++,cont++) {
        cubos[i]->setFace(lado);
    }

    //Colocando que tienen el lado Bot activo
    lado = 'B';
    for (int i = 0,cont=0; i < 27; i += 3,cont++) {
        cubos[i]->setFace(lado);
    }

    //Colocando que tienen el lado Front activo
    lado = 'F';
    for (int i = 2,cont=0; i < 27; i += 3,cont++) {
        cubos[i]->setFace(lado);
    }

    //Colocando que tienen el lado Left activo
    lado = 'L';
    for (int i = 0,cont=0; i < 27; i += 9,cont++) {
        cubos[i]->setFace(lado);
        cubos[i+1]->setFace(lado);
        cubos[i+2]->setFace(lado);
    }

    //Colocando que tienen el lado Right activo
    lado = 'R';
    for (int i = 6,cont=0; i < 27; i += 9, cont++) {
        cubos[i]->setFace(lado);
        cubos[i + 1]->setFace(lado);
        cubos[i + 2]->setFace(lado);
    }

    //Colocando los colores correctos de cada cubo  en los vertices (iniciaban con negro todos sus lados)
    for (int i = 0; i < 27; i++) {
        cubos[i]->setColors();
    }

    //colocar en orden los cubos en cada cara
    //DOWN
    caras[0][0] = cubos[0];
    caras[0][1] = cubos[1];
    caras[0][2] = cubos[2];
    caras[0][3] = cubos[3];
    caras[0][4] = cubos[4];
    caras[0][5] = cubos[5];
    caras[0][6] = cubos[6];
    caras[0][7] = cubos[7];
    caras[0][8] = cubos[8];

    //UP
    caras[1][0] = cubos[20];
    caras[1][1] = cubos[19];
    caras[1][2] = cubos[18];
    caras[1][3] = cubos[23];
    caras[1][4] = cubos[22];
    caras[1][5] = cubos[21];
    caras[1][6] = cubos[26];
    caras[1][7] = cubos[25];
    caras[1][8] = cubos[24];

    //BOT
    caras[2][0] = cubos[18];
    caras[2][1] = cubos[9];
    caras[2][2] = cubos[0];
    caras[2][3] = cubos[21];
    caras[2][4] = cubos[12];
    caras[2][5] = cubos[3];
    caras[2][6] = cubos[24];
    caras[2][7] = cubos[15];
    caras[2][8] = cubos[6];

    //FRONT
    caras[3][0] = cubos[2];
    caras[3][1] = cubos[11];
    caras[3][2] = cubos[20];
    caras[3][3] = cubos[5];
    caras[3][4] = cubos[14];
    caras[3][5] = cubos[23];
    caras[3][6] = cubos[8];
    caras[3][7] = cubos[17];
    caras[3][8] = cubos[26];

    //LEFT
    caras[4][0] = cubos[0];
    caras[4][1] = cubos[9];
    caras[4][2] = cubos[18];
    caras[4][3] = cubos[1];
    caras[4][4] = cubos[10];
    caras[4][5] = cubos[19];
    caras[4][6] = cubos[2];
    caras[4][7] = cubos[11];
    caras[4][8] = cubos[20];

    //RIGHT
    caras[5][0] = cubos[26];
    caras[5][1] = cubos[25];
    caras[5][2] = cubos[24];
    caras[5][3] = cubos[17];
    caras[5][4] = cubos[16];
    caras[5][5] = cubos[15];
    caras[5][6] = cubos[8];
    caras[5][7] = cubos[7];
    caras[5][8] = cubos[6];

    for (int i = 0; i < caras.size(); i++) {
        for (int j = 0; j < caras[i].size(); j++) {
            caras[i][j]->setTextures(i, j);
        }
    }
//asignar direciones a las caras
    vector<vec3>direcciones = { vec3(0.0, 0.0, -1.0) ,vec3(0.0, 0.0, 1.0),vec3(-1.0, 0.0, 0.0),vec3(1.0, 0.0, 0.0),vec3(0.0, -1.0, 0.0),vec3(0.0, 1.0, 0.0) };
    for (int i = 0; i < caras.size(); i++) {
        for (int j = 0; j < caras[i].size(); j++) {
            caras[i][j]->direccion = vec3(caras[i][j]->direccion.x + direcciones[i].x, caras[i][j]->direccion.y + direcciones[i].y, caras[i][j]->direccion.z + direcciones[i].z);
        }
    }
}

void RubikCube::drawing() {
    for (int i = 0; i < 27; i++) {
        //Sleep(50);
        cubos[i]->drawing(myShader);
    }
}

void RubikCube::vertexConfig() {
    for (int i = 0; i < 27; i++) {
        cubos[i]->configVertex();
    }
}

void RubikCube::setRotation(bool clock,int face) {
    if (animando) {
        return;
    }
    animaciones[face].first = clock;        //clockwise?
    animaciones[face].second=true;          //animation
    animando = true;

}

void RubikCube::moveTo() {
    vector<vec3> direcciones(6);                       //   D                B           F       L           R      INDICES
    vector< vector<int>> facesAroundIndex = {
        {0, 3, 6, 6, 7, 8, 8, 5, 2, 0, 3, 6},          //D  0
        {0, 3, 6, 2, 1, 0, 8, 5, 2, 8, 5, 2},          //U  1
        {0, 3, 6, 8, 5, 2, 8, 5, 2, 2, 1, 0},          //B  2
        {0, 3, 6, 0, 3, 6, 8, 5, 2, 6, 7, 8},          //F  3
        {2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0},          //L  4
        {6, 7, 8, 6, 7, 8, 6, 7, 8, 6, 7, 8} };        //R  5

    vector< vector<int>> facesAround = {
        {3,5,2,4},     //D
        {2,5,3,4},     //U
        {0,5,1,4},     //B
        {1,5,0,4},     //F
        {1,3,0,2},     //L
        {2,0,3,1}      //R
    };



    for (int j = 0; j < animaciones.size(); j++) {
        if (animaciones[j].second == true) {        //is animation true?
            //cout << "ENTRA " << endl;
            if (animaciones[j].first == true) {     //is clockwise?
                direcciones = { vec3(0.0, 0.0, 1.0) ,vec3(0.0, 0.0, -1.0),vec3(1.0, 0.0, 0.0),vec3(-1.0, 0.0, 0.0),vec3(0.0, 1.0, 0.0),vec3(0.0, -1.0, 0.0) };
            }
            else {
                direcciones = { vec3(0.0, 0.0, -1.0) ,vec3(0.0, 0.0, 1.0),vec3(-1.0, 0.0, 0.0),vec3(1.0, 0.0, 0.0),vec3(0.0, -1.0, 0.0),vec3(0.0, 1.0, 0.0) };
            }


            //Recorriendo cada cubo en una cara, en total 9 cubos en cada cara
            for (int i = 0; i < caras[j].size(); i++) {

                rotateVecSame(caras[j][i]->model, direcciones[j]);
                caras[j][i]->configVertex();
                caras[j][i]->drawing(myShader);

            }

            //cout << "contador: " << contador<< endl;
            contador++;

            // }
            if(contador == anguloDividido) {
                if (animaciones[j].first == true) {     //is is clock
                           reloj(caras[j], caras[facesAround[j][0]], caras[facesAround[j][1]], caras[facesAround[j][2]], caras[facesAround[j][3]], facesAroundIndex[j]);
                }
                else {
                    contrarreloj(caras[j], caras[facesAround[j][0]], caras[facesAround[j][1]], caras[facesAround[j][2]], caras[facesAround[j][3]], facesAroundIndex[j]);
                }
                contador = 0;
                presionado = false;
                animaciones[j].second = false;      //animation set false
                animando = false;


            }
        }
    }
}
int sol=0;
void RubikCube::solvingCube() {
    if (!animando && proceso) {
        if (solving.empty()){
            proceso=false;
            solved = true;
        }
        else {
            if (solving[0] == ' ') {        // " U D"
                solving = solving.substr(1);
                return;
            }
            //si llega aqui significa que es una letra
            if (solving[1] == ' ') {        //  "U D"
                setRotation(true, getIndex(solving[0]));        //girar sentido horario
                solving = solving.substr(2);
                return;
            }

            if (solving[1] == '\'') {        //  "U' D"
                setRotation(false, getIndex(solving[0]));       //girar sentido antihorario
                solving = solving.substr(3);
                return;
            }

            if (solving[1] == '2') {        //  "U2 D"
                char temp = solving[0];
                solving = solving.substr(1);
                solving[0] = temp;
                setRotation(true, getIndex(solving[0]));        //girar sentido horario
                return;
            }

        }

    }
    if(sol){
    cout<<solving.size()<<endl;
    }

}
void RubikCube::solve()
{
     //ya se esta resolviendo
    if (proceso || animando) {
        return;
    }

    if (disordered.empty()) {
        solved = true;
        proceso = false;
    }
    else {
        proceso = true;
        solved = false;

        //cout << "Disordered: " << disordered << endl;
        solving = Rubik::solve(disordered);
        disordered = "";
        cout << "Solving " << endl;
    }
}
void RubikCube::Expandir()
{
    if (animando)
        return;
    animando = true;
    procesoExplotar = true;
    explotarVariable = true;
}
void RubikCube::Contraer()
{
    if (animando)
        return;
    animando = true;
    procesoExplotar = true;
    explotarVariable = false;
}
void RubikCube::animar_Explota_Contrae() {
    if (!procesoExplotar)
        return;

    int times = 50;
    if (contador < times) {

        for (int i = 0; i < 27; i++) {
            vec3 tempDireccion;

            if (explotarVariable) {
                tempDireccion = vec3(cubos[i]->direccion.x/100, cubos[i]->direccion.y / 100, cubos[i]->direccion.z / 100);
            }
            else {
                tempDireccion = -vec3(cubos[i]->direccion.x /100, cubos[i]->direccion.y / 100, cubos[i]->direccion.z / 100);
            }
            glm::mat4 translation = glm::translate(glm::mat4(1.f), tempDireccion);
            cubos[i]->model =  cubos[i]->model* translation;
        }
        contador++;
    }

    if (contador == times) {
        animando = false;
        procesoExplotar = false;
        contador = 0;
    }
}

void RubikCube::rotar_cruz()
{
    if (animando)
        return;
    animando = true;
    rotar_cubos = true;
}

void RubikCube::animar_rotacion()
{
    if (!rotar_cubos) {
        return;
    }
    float anguloVueltas = 360;
    float anguloDivididoTemp = 100;

    if (contador < anguloDivididoTemp) {
        vector<vector<cubie*>> map_cubos;

        vector<vec3>direcciones = { vec3(1.0, 0.0, 0.0) ,vec3(0.0, 1.0, 0.0),vec3(0.0, 0.0, 1.0),vec3(0.0, 1.0, 1.0),vec3(0.0, -1.0, 1.0) };
        vector<cubie*> EnX, EnY, EnZ, esquinas1, esquinas2;

        EnX = { caras[0][1],caras[0][7],caras[1][1],caras[1][7] };
        EnY = { caras[2][3],caras[2][5],caras[3][3],caras[3][5] };
        EnZ = { caras[3][1],caras[3][7],caras[2][1],caras[2][7] };

        esquinas1 = { caras[2][0],caras[2][8],caras[3][2],caras[3][6] };
        esquinas2 = { caras[2][2],caras[2][6],caras[3][0],caras[3][8] };

        map_cubos.push_back(EnX);
        map_cubos.push_back(EnY);
        map_cubos.push_back(EnZ);
        map_cubos.push_back(esquinas1);
        map_cubos.push_back(esquinas2);

        for (int i = 0; i < map_cubos.size(); i++) {
            for (int j = 0; j < map_cubos[i].size(); j++) {
                mat4 nuevo(1.0f);
                nuevo = glm::rotate(nuevo, glm::radians(anguloVueltas / anguloDivididoTemp), direcciones[i]);
                map_cubos[i][j]->model = nuevo * map_cubos[i][j]->model;
            }
        }
        contador++;
    }
    else {
        animando = false;
        rotar_cubos = false;
        contador = 0;
    }
}
int cont=0;


bool voltear=0;
bool explotar=0;
void RubikCube::running()
{
    solvingCube();
    moveTo();
    if(cont<1){
     Contraer();
     cont++;
    }
    if(voltear){
     Contraer();
    }
    if(explotar){
     Expandir();
    }
    animar_Explota_Contrae();
    animar_rotacion();

}

void RubikCube::insertMovement(bool clock, int face)
{//si esta ocupado animando alguna cara no lo hace
    if (animando || proceso)
        return;
    vector<char> ffaces = { 'D', 'U', 'B', 'F', 'L', 'R' };
    if (clock) {
        disordered.push_back(ffaces[face]);
        disordered.push_back(' ');
    }
    else {
        disordered.push_back(ffaces[face]);
        disordered.push_back('\'');
    }
    setRotation(clock, face);
}
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    string vs = mainPath + "3.3.shader.vs", fs = mainPath + "3.3.shader.fs";
    Shader ourShader(vs.c_str(), fs.c_str());

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    //unsigned int VBO[3], VAO[3];
    glGenVertexArrays(27, VAO);
    glGenBuffers(27, VBO);




    vector<string> nombresTexturas = {
        "U.png",
        "C.png",
        "S.png",
        "P.png",
        "C.png",
        "G.png"

    };

    for (int i = 0; i < 6; i++) {
        // texture 1
    // ---------
        glGenTextures(1, &textures[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        string path = mainPath + nombresTexturas[i];
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

    }


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();

    RubikCube CUBOOS(ourShader);

    cuboPrincipal = &CUBOOS;


    float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    // render loop
    // -----------

    menu();
    int val = 0;
    int config =1;
    bool vista=0;

    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        processInput(window);
        glfwSetKeyCallback(window, key_callback);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        //draw
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, textures[2]);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, textures[3]);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, textures[5]);
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {     //animar en forma de planeta
                texture=1;
        }
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {     //animar en forma de planeta
                voltear=1;
        }
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {     //animar en forma de planeta
                voltear=0;
        }
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {     //animar en forma de planeta
                explotar=1;
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {     //animar en forma de planeta
                explotar=0;
        }


        // activate shader
        ourShader.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation|
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        CUBOOS.running(); // mover 5 grados

        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {     //animar en forma de planeta
              vista=1;
              cuboPrincipal->Contraer();
        }
        if(vista){
            CUBOOS.drawing();
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(27, VAO);
    glDeleteBuffers(27, VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //if (!presionado) {
        //Clockwise
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
            cuboPrincipal->insertMovement(true, 0);
            presionado = true;
        }

        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
            cuboPrincipal->insertMovement(true, 1);
            presionado = true;
        }
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
            cuboPrincipal->insertMovement(true, 2);
            presionado = true;
        }
        if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
            cuboPrincipal->insertMovement(true, 3);
            presionado = true;
        }
        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
            cuboPrincipal->insertMovement(true, 4);
            presionado = true;
        }
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
            cuboPrincipal->insertMovement(true, 5);
            presionado = true;
        }

        //Counter-Clockwise
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            cuboPrincipal->insertMovement(false, 0);
            presionado = true;
        }
        if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
            cuboPrincipal->insertMovement(false, 1);
            presionado = true;

        }
        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
            cuboPrincipal->insertMovement(false, 2);
            presionado = true;

        }
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
            cuboPrincipal->insertMovement(false, 3);
            presionado = true;

        }
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
            cuboPrincipal->insertMovement(false, 4);
            presionado = true;
        }
        //-------------animaciones------------
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            cuboPrincipal->solve();sol=1;
        }
        if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {     //Expandir
            cuboPrincipal->Expandir();
        }
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {     //Contraer
            cuboPrincipal->Contraer();
        }
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {     //animar en forma de planeta
            cuboPrincipal->rotar_cruz();
        }

    //}

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

