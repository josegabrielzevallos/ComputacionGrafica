#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <Windows.h>
#include <iostream>
#include <cmath>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"uniform mat4 transform;\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";

glm::vec3 vecRombo = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 vecEstrella = glm::vec3(0.0f, 0.0f, 0.0f);

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

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // link shaders
    unsigned int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader);
    glLinkProgram(shaderProgram2);
    // check for linking errors
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram3 = glCreateProgram();
    glAttachShader(shaderProgram3, vertexShader);
    glAttachShader(shaderProgram3, fragmentShader);
    glLinkProgram(shaderProgram3);
    // check for linking errors
    glGetProgramiv(shaderProgram3, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram3, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram4 = glCreateProgram();
    glAttachShader(shaderProgram4, vertexShader);
    glAttachShader(shaderProgram4, fragmentShader);
    glLinkProgram(shaderProgram4);
    // check for linking errors
    glGetProgramiv(shaderProgram4, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram4, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float verticesT[] = {
        //Triangulo
        -0.1f, -0.1f, 0.0f, 0.88f, 0.2f, 0.38f,
        0.1f, -0.1f, 0.0f, 0.88f, 0.2f, 0.38f,
        0.0f, 0.1f, 0.0f, 0.88f, 0.2f, 0.38f,

        -0.1f, -0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.1f, -0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.1f, -0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
    };
    float verticesC[] = {
        //Cuadrado
        0.2f, -0.1f, 0.0f, 0.92f, 0.75f, 0.59f,
        0.4f, -0.1f, 0.0f, 0.92f, 0.75f, 0.59f,
        0.2f, 0.1f, 0.0f, 0.92f, 0.75f, 0.59f,
        0.4f, -0.1f, 0.0f, 0.92f, 0.75f, 0.59f,
        0.2f, 0.1f, 0.0f, 0.92f, 0.75f, 0.59f,
        0.4f, 0.1f, 0.0f, 0.92f, 0.75f, 0.59f,

        0.2f, -0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.4f, -0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.4f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.2f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.2f, -0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
    };
    float verticesR[] = {
        //Rombo
        0.5f, 0.0f, 0.0f, 0.57f, 0.57f, 0.52f,
        0.6f, 0.1f, 0.0f, 0.57f, 0.57f, 0.52f,
        0.7f, 0.0f, 0.0f, 0.57f, 0.57f, 0.52f,
        0.5f, 0.0f, 0.0f, 0.57f, 0.57f, 0.52f,
        0.7f, 0.0f, 0.0f, 0.57f, 0.57f, 0.52f,
        0.6f, -0.1f, 0.0f, 0.57f, 0.57f, 0.52f,

        0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.6f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.6f, -0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    };
    float verticesE[] = {
        //Estrella
        0.8f, 0.03f, 0.0f, 0.37f, 0.23f, 0.43f,
        1.0f, 0.03f, 0.0f, 0.37f, 0.23f, 0.43f,
        0.9f, -0.055f, 0.0f, 0.37f, 0.23f, 0.43f,
        0.9f, -0.055f, 0.0f, 0.37f, 0.23f, 0.43f,
        0.9f, 0.1f, 0.0f, 0.37f, 0.23f, 0.43f,
        0.82f, -0.1f, 0.0f, 0.37f, 0.23f, 0.43f,
        0.9f, -0.055f, 0.0f, 0.37f, 0.23f, 0.43f,
        0.9f, 0.1f, 0.0f, 0.37f, 0.23f, 0.43f,
        0.98f, -0.1f, 0.0f, 0.37f, 0.23f, 0.43f,

        0.8f, 0.03f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.872f, 0.03f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.9f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.928f, 0.03f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.03f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.9462686572003f, -0.0156716421572f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.98f, -0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.9f, -0.055f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.82f, -0.1f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.8537313432469f, -0.0156716418147f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.8f, 0.03f, 0.0f, 0.0f, 0.0f, 0.0f,
    };
    unsigned int VBOs[4], VAOs[4];
    glGenVertexArrays(4, VAOs); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(4, VBOs);
    // first triangle setup
    // --------------------
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesT), verticesT, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
    // second triangle setup
    // ---------------------
    glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesC), verticesC, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)
    // second triangle setup
    // ---------------------
    glBindVertexArray(VAOs[2]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesR), verticesR, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)
    // second triangle setup
    // ---------------------
    glBindVertexArray(VAOs[3]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesE), verticesE, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 06 * sizeof(float), (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float direccionR = 2.0f;
    float direccionE = 2.0f;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 trans2 = glm::mat4(1.0f);
        glm::mat4 trans3 = glm::mat4(1.0f);
        glm::mat4 trans4 = glm::mat4(1.0f);
        
        glUseProgram(shaderProgram);
        
        glBindVertexArray(VAOs[0]);
        trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_LINE_STRIP, 3, 4);
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            trans = glm::scale(trans, glm::vec3(2.5f, 2.5f, 1.0f));
        }
        unsigned int transformLoc1 = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(trans));

        glUseProgram(shaderProgram2);

        glBindVertexArray(VAOs[1]);
        trans2 = glm::rotate(trans2, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawArrays(GL_LINE_STRIP, 6, 5);
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
            trans2 = glm::rotate(trans2, (float)glfwGetTime() * 3, glm::vec3(0.0f, 0.0f, 1.0f));
        }
        unsigned int transformLoc2 = glGetUniformLocation(shaderProgram2, "transform");
        glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(trans2));

        glUseProgram(shaderProgram3);

        glBindVertexArray(VAOs[2]);
        if (direccionR == 2.0f) {
            trans3 = glm::translate(trans3, vecRombo);
            vecRombo.y += 0.02;
            if (vecRombo.y >= 0.6) {
                direccionR = -1.0f;
            }
        }
        if (direccionR == -1.0f) {
            trans3 = glm::translate(trans3, vecRombo);
            vecRombo.x -= 0.02;
            if (vecRombo.x <= -1.2) {
                direccionR = -2.0f;
            }
        }
        if (direccionR == -2.0f) {
            trans3 = glm::translate(trans3, vecRombo);
            vecRombo.y -= 0.02;
            if (vecRombo.y <= -0.6) {
                direccionR = 1.0f;
            }
        }
        if (direccionR == 1.0f) {
            trans3 = glm::translate(trans3, vecRombo);
            vecRombo.x += 0.02;
            if (vecRombo.x >= 0.0) {
                direccionR = 2.0f;
            }
        }
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawArrays(GL_LINE_STRIP, 6, 5);
        unsigned int transformLoc3 = glGetUniformLocation(shaderProgram3, "transform");
        glUniformMatrix4fv(transformLoc3, 1, GL_FALSE, glm::value_ptr(trans3));

        glUseProgram(shaderProgram4);

        glBindVertexArray(VAOs[3]);
        if (direccionE == 2.0f) {
            trans4 = glm::translate(trans4, vecEstrella);
            vecEstrella.y += 0.02;
            if (vecEstrella.y >= 0.9) {
                direccionE = -1.0f;
            }
        }
        if (direccionE == -1.0f) {
            trans4 = glm::translate(trans4, vecEstrella);
            vecEstrella.x -= 0.02;
            if (vecEstrella.x <= -1.8) {
                direccionE = -2.0f;
            }
        }
        if (direccionE == -2.0f) {
            trans4 = glm::translate(trans4, vecEstrella);
            vecEstrella.y -= 0.02;
            if (vecEstrella.y <= -0.9) {
                direccionE = 1.0f;
            }
        }
        if (direccionE == 1.0f) {
            trans4 = glm::translate(trans4, vecEstrella);
            vecEstrella.x += 0.02;
            if (vecEstrella.x >= 0.0) {
                direccionE = 2.0f;
            }
        }
        Sleep(100);
        glDrawArrays(GL_TRIANGLES, 0, 9);
        glDrawArrays(GL_LINE_STRIP, 9, 11);
        unsigned int transformLoc4 = glGetUniformLocation(shaderProgram4, "transform");
        glUniformMatrix4fv(transformLoc4, 1, GL_FALSE, glm::value_ptr(trans4));

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(4, VAOs);
    glDeleteBuffers(4, VBOs);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgram2);
    glDeleteProgram(shaderProgram3);
    glDeleteProgram(shaderProgram4);

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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}