

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <cmath>

#define PI 3.14159265359
#define TAM 4

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"uniform mat4 transform;\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.63f, 0.42f, 0.24f, 1.0f);\n"
"}\n\0";

float rotX = 60.0f, rotY = 49.0f, rotZ = 77.0f;
float transX = 0.42f, transY = 0.79f, transZ = 0.725f;
float scalX = 0.1f, scalY = 0.1f, scalZ = 0.1f;
/*
glm::mat4 trans = glm::mat4(1.0f);  // Matriz identidad maestra
glm::mat4 transA = glm::mat4(1.0f); // Matriz Rz
glm::mat4 transAinv = glm::mat4(1.0f); // Inversa de Rz-1
glm::mat4 transB = glm::mat4(1.0f); // Matriz S
glm::mat4 transC = glm::mat4(1.0f); // Matriz Ry
glm::mat4 transD = glm::mat4(1.0f); // Matriz T
*/
glm::mat4 trans = glm::mat4(1.0f);  // Matriz identidad maestra
glm::mat4 transA = glm::mat4(1.0f); // Matriz Ry
glm::mat4 transAinv = glm::mat4(1.0f); // Inversa de Ry-1
glm::mat4 transB = glm::mat4(1.0f); // Matriz T
glm::mat4 transC = glm::mat4(1.0f); // Matriz S
glm::mat4 transD = glm::mat4(1.0f); // Matriz Rz



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
	unsigned int hola = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glAttachShader(hola, vertexShader);
	glAttachShader(hola, fragmentShader);
	glLinkProgram(hola);
	// check for linking errors
	glGetProgramiv(hola, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(hola, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		0.75f, -0.5f, 0.0f,
		0.25f, 0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		//0.5f, -0.5f, 0.9f,

	};

	GLfloat cuadrado[] = {
	0.15f,0.1f,0.0f,
	0.35f,0.1f,0.0f,
	0.35f,-0.1f,0.0f,

	0.15f,0.1f,0.0f,
	0.15f,-0.1f,0.0f,
	0.35f,-0.1f,0.0f

	};

	unsigned int VBO[100], VAO[100];
	glGenVertexArrays(1, &VAO[0]);
	glGenBuffers(1, &VBO[0]);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cuadrado), cuadrado, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	cout << "Instrucciones:" << endl;
	cout << "hola" << endl;
	while (!glfwWindowShouldClose(window))
	{
		
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//TECLAS
		/**/
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			transA = glm::rotate(transA, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
			//transA = glm::rotate(transA, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
			transAinv = glm::inverse(transA);
			//transAinv = glm::inverse(transA);
			trans = transAinv;
			cout << glm::to_string(trans) << endl;
		}
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
			trans = glm::translate(transB, glm::vec3(transX, transY, transZ));
			//trans = glm::scale(transB, glm::vec3(scalX, scalY, scalZ));
			cout << glm::to_string(trans) << endl;
		}
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
			//trans = glm::rotate(transC, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
			trans = glm::scale(transC, glm::vec3(scalX, scalY, scalZ));
			cout << glm::to_string(trans) << endl;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			//trans = glm::translate(transD, glm::vec3(transX, transY, transZ));
			trans = glm::rotate(trans, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			cout << glm::to_string(trans) << endl;
		}
		if ((glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_B) != GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_C) != GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS)) {
			transD = glm::rotate(trans, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			transC = glm::scale(trans, glm::vec3(scalX, scalY, scalZ));
			transB = trans = glm::translate(trans, glm::vec3(transX, transY, transZ));
			transA = transA = glm::rotate(trans, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
			transAinv = glm::inverse(transA);
			trans = transC * transD;
			trans = transB * trans;
			trans = transAinv * trans;
			cout << glm::to_string(trans) << endl;

			/*
			transD = glm::translate(trans, glm::vec3(transX, transY, transZ));
			transC = glm::rotate(trans, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
			transB = glm::scale(trans, glm::vec3(scalX, scalY, scalZ));
			transA = glm::rotate(trans, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			transAinv = glm::inverse(transA);
			trans = transC * transD;
			trans = transB * trans;
			trans = transAinv * trans;
			cout << glm::to_string(trans) << endl;
			*/
		}

		// get matrix's uniform location and set matrix
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		unsigned int transformLochola = glGetUniformLocation(hola, "transform");
		glUniformMatrix4fv(transformLochola, 1, GL_FALSE, glm::value_ptr(trans));
		
		//Para que las regrese a su estado originalhola
		trans = glm::mat4(1.0f);
		transA = glm::mat4(1.0f);
		transB = glm::mat4(1.0f);
		transC = glm::mat4(1.0f);
		transD = glm::mat4(1.0f);

		// draw our first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO[0]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glUseProgram(hola);
		//glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 0.0f);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 0.0f);
		// glBindVertexArray(0); // no need to unbind it every time 

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO[0]);
	glDeleteBuffers(1, &VBO[0]);
	glDeleteProgram(shaderProgram);

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

