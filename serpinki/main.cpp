/*
********
Computación Gráfica
GRUPO:
- Yhon yerson sanchez yucra
- Jose Gabriel Zevallos Delgado de la Flor
- Christopher Yquira Miranda

<presione R para rotar todo el triangulo  presione T para detenerlo
presione  W para rotar los subtriangulos y S para detenerlos>
*******
*/
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <cmath>
#include <cmath>
#include <time.h>
#include <vector>
using namespace std;
#define M_PI 3.14159265358979323846 /* pi */
GLfloat v[3][2] = {{-0.5, -0.5}, {0.5, -0.5}, {0.0, 0.5}};
vector<float> temp;

float colorr[] = {1.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0.0f, 0.0f, 2.0f, 0.5f, 1.0f};
float colorg[] = {1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.1f, 0.1f, 0.5f, 0.5f, 0.5f};
float colorb[] = {0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f};

float &Acceso(float *vector, int indice)
{
	return vector[indice];
}

void mostrar()
{
	cout << "Computación Gráfica" << endl;
	cout << "GRUPO:" << endl;
	cout << "- Yhon yerson sanchez yucra" << endl;
	cout << "- Jose Gabriel Zevallos Delgado de la Flor" << endl;
	cout << "- Christopher Yquira Miranda" << endl;

	cout << "presione R para rotar todo el triangulo  presione T para detenerlo" << endl;
	cout << "presione  W para rotar los subtriangulos y S para detenerlos" << endl;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 400;
const unsigned int SCR_HEIGHT = 400;
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

void triangle(GLfloat *a, GLfloat *b, GLfloat *c)
{
	temp.push_back(a[0]);
	temp.push_back(a[1]);
	temp.push_back(0.0);
	temp.push_back(b[0]);
	temp.push_back(b[1]);
	temp.push_back(0.0);
	temp.push_back(c[0]);
	temp.push_back(c[1]);
	temp.push_back(0.0);
}
void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int m)
{
	GLfloat center[3][2];
	int j;
	if (m > 0)
	{
		for (j = 0; j < 2; j++)
		{
			center[0][j] = (a[j] + b[j]) / 2;
		}
		for (j = 0; j < 2; j++)
		{
			center[1][j] = (a[j] + c[j]) / 2;
		}
		for (j = 0; j < 2; j++)
		{
			center[2][j] = (b[j] + c[j]) / 2;
		}
		divide_triangle(a, center[0], center[1], m - 1);
		divide_triangle(center[0], b, center[2], m - 1);
		divide_triangle(center[1], center[2], c, m - 1);
	}
	else
		(triangle(a, b, c));
}

void sleepcp(int milliseconds) // Cross-platform sleep function
{
	clock_t time_end;
	time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end)
	{
	}
}

float vertices[] = {
	// positions         // colors
	0.1f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
	-0.1f, -0.1f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
	0.0f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f	  // top

};

float circulo[] = {
	0.0f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f,
	0.497502f, 0.0499167f, 0.0f,
	0.490033f, 0.0993347f, 0.0f,
	0.477668f, 0.14776f, 0.0f,
	0.46053f, 0.194709f, 0.0f,
	0.438791f, 0.239713f, 0.0f,
	0.412668f, 0.282321f, 0.0f,
	0.382421f, 0.322109f, 0.0f,
	0.348353f, 0.358678f, 0.0f,
	0.310805f, 0.391663f, 0.0f,
	0.270151f, 0.420735f, 0.0f,
	0.226798f, 0.445604f, 0.0f,
	0.181179f, 0.46602f, 0.0f,
	0.133749f, 0.481779f, 0.0f,
	0.0849836f, 0.492725f, 0.0f,
	0.0353686f, 0.498747f, 0.0f,
	-0.0145998f, 0.499787f, 0.0f,
	-0.0644222f, 0.495832f, 0.0f,
	-0.113601f, 0.486924f, 0.0f,
	-0.161645f, 0.47315f, 0.0f,
	-0.208073f, 0.454649f, 0.0f,
	-0.252423f, 0.431605f, 0.0f,
	-0.294251f, 0.404248f, 0.0f,
	-0.333138f, 0.372853f, 0.0f,
	-0.368697f, 0.337732f, 0.0f,
	-0.400572f, 0.299236f, 0.0f,
	-0.428444f, 0.257751f, 0.0f,
	-0.452036f, 0.21369f, 0.0f,
	-0.471111f, 0.167494f, 0.0f,
	-0.485479f, 0.119625f, 0.0f,
	-0.494996f, 0.07056f, 0.0f,
	-0.499568f, 0.0207903f, 0.0f,
	-0.499147f, -0.0291871f, 0.0f,
	-0.49374f, -0.0788728f, 0.0f,
	-0.483399f, -0.127771f, 0.0f,
	-0.468228f, -0.175392f, 0.0f,
	-0.448379f, -0.22126f, 0.0f,
	-0.42405f, -0.264918f, 0.0f,
	-0.395484f, -0.305929f, 0.0f,
	-0.362966f, -0.343883f, 0.0f,
	-0.326822f, -0.378401f, 0.0f,
	-0.287412f, -0.409139f, 0.0f,
	-0.24513f, -0.435788f, 0.0f,
	-0.2004f, -0.458083f, 0.0f,
	-0.153666f, -0.475801f, 0.0f,
	-0.105398f, -0.488765f, 0.0f,
	-0.0560763f, -0.496846f, 0.0f,
	-0.00619433f, -0.499962f, 0.0f,
	0.0437495f, -0.498082f, 0.0f,
	0.0932562f, -0.491226f, 0.0f,
	0.141831f, -0.479462f, 0.0f,
	0.188989f, -0.462907f, 0.0f,
	0.234258f, -0.441727f, 0.0f,
	0.277187f, -0.416134f, 0.0f,
	0.317346f, -0.386382f, 0.0f,
	0.354335f, -0.35277f, 0.0f,
	0.387783f, -0.315633f, 0.0f,
	0.417356f, -0.275343f, 0.0f,
	0.44276f, -0.232301f, 0.0f,
	0.463739f, -0.186938f, 0.0f,
	0.480085f, -0.139708f, 0.0f,
	0.491634f, -0.0910813f, 0.0f,
	0.498271f, -0.0415447f, 0.0f

};
unsigned int indice_circulo[] = {
	0, 1, 2,
	0, 2, 3,
	0, 3, 4,
	0, 4, 5,
	0, 5, 6,
	0, 6, 7,
	0, 7, 8,
	0, 8, 9,
	0, 9, 10,
	0, 10, 11,
	0, 11, 12,
	0, 12, 13,
	0, 13, 14,
	0, 14, 15,
	0, 15, 16,
	0, 16, 17,
	0, 17, 18,
	0, 18, 19,
	0, 19, 20,
	0, 20, 21,
	0, 21, 22,
	0, 22, 23,
	0, 23, 24,
	0, 24, 25,
	0, 25, 26,
	0, 26, 27,
	0, 27, 28,
	0, 28, 29,
	0, 29, 30,
	0, 30, 31,
	0, 31, 32,
	0, 32, 33,
	0, 33, 34,
	0, 34, 35,
	0, 35, 36,
	0, 36, 37,
	0, 37, 38,
	0, 38, 39,
	0, 39, 40,
	0, 40, 41,
	0, 41, 42,
	0, 42, 43,
	0, 43, 44,
	0, 44, 45,
	0, 45, 46,
	0, 46, 47,
	0, 47, 48,
	0, 48, 49,
	0, 49, 50,
	0, 50, 51,
	0, 51, 52,
	0, 52, 53,
	0, 53, 54,
	0, 54, 55,
	0, 55, 56,
	0, 56, 57,
	0, 57, 58,
	0, 58, 59,
	0, 59, 60,
	0, 60, 61,
	0, 61, 62,
	0, 62, 63,
	0, 63, 1};

void mover_todo(float arr[], int pos, float value, int n)
{
	for (int i = 0; i < n / 3; ++i)
	{
		Acceso(arr, i * 3 + pos) += value;
	}
}

void print(float arr[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (i % 3 == 0)
			cout << endl;
		cout << arr[i] << " ";
	}
}
void rotar(float &x, float &y, float cx, float cy, float ang)
{
	float dx = x - cx;
	float dy = y - cy;
	float r = sqrt(dx * dx + dy * dy);
	float a = atan2(dy, dx);

	float da_rad = ang / 180 * M_PI;
	a -= da_rad;
	x = cx + r * cos(a);
	y = cy + r * sin(a);
}
void rotar_todo(float arr[], int n, int angle)
{
	for (int i = 0; i < n / 3; ++i)
	{
		rotar(Acceso(arr, i * 3 + 0), Acceso(arr, i * 3 + 1), 0, 0, angle);
	}
}

void rotar_un_triangulo(float arr[], int init, int end, float cx, float cy, float angulo)
{
	for (int i = init; i < end; i++)
	{
		rotar(Acceso(arr, i * 3 + 0), Acceso(arr, i * 3 + 1), cx, cy, 5);
	}
}

int niveles = 4;
bool rotar_all = false;
bool rotar_tri = false;

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	mostrar();

	//glfw window creation
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "my version opengl", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	// glad: load all opengl function pouinter
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//***VertexShader**
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//**check vertex shader*
	int success;
	char infolog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "ERROR VERTER:_SHADER_COMPILATION" << std::endl;
	}
	//**CREATE AND COMPILE Fragment shadre*
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//**FRAGMENTSHADER**
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
				  << infolog << std::endl;
	}
	//*LINK SHADER***
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//*check for linking errors**
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
				  << infolog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//***END CONCIFG AND LINKED ***

	//***array_triangle para dos figuras y EBO para un indice
	unsigned int VBO[11], VAO[11], EBO, TRI, FG3, FG4, FG5, FG6, FG7, FG8, FG9, FG10;
	glGenVertexArrays(11, VAO);
	glGenBuffers(11, VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &TRI);
	glGenBuffers(1, &FG3);
	glGenBuffers(1, &FG4);
	glGenBuffers(1, &FG5);	//marco
	glGenBuffers(1, &FG6);	//niño
	glGenBuffers(1, &FG7);	//cabelloniño
	glGenBuffers(1, &FG8);	//manomadre
	glGenBuffers(1, &FG9);	//manomadre
	glGenBuffers(1, &FG10); //manomadre
							/*
	//**lineas cuadro***
	glBindVertexArray(VAO[9]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[9]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(LineasCuadro), LineasCuadro, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
*/
	glBindVertexArray(VAO[9]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[9]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	divide_triangle(v[0], v[1], v[2], niveles);
	float arr[temp.size()];
	std::copy(temp.begin(), temp.end(), arr);

	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			mover_todo(arr, 0, 0.01, 6);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			mover_todo(arr, 0, -0.01, 6);
		}
		/*if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			rotar_all = true;
		}
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		{
			rotar_all = false;
		}*/

		//**primera figura en VAO[0]**
		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(circulo), circulo, GL_STATIC_DRAW);
		//**indcies para la figura en VAO[0]**
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indice_circulo), indice_circulo, GL_STATIC_DRAW);
		//*pointer para la figura VAO[0]**
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);
		//**endprimera_figura*

		//**triangulo sin indices VAO[1]**
		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);

		//*****INIT*****
		glUseProgram(shaderProgram);
		glPointSize(10);

		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//*****ENDINIT***

		//***triangulo con indices+****
		glLineWidth(2.0f);
		glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 0.5f);
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, 192, GL_UNSIGNED_INT, 0);

		glUniform4f(vertexColorLocation, 0.5f, 0.5f, 0.5f, 0.5f);
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, 128, GL_UNSIGNED_INT, 0);

		glUniform4f(vertexColorLocation, 0.0f, 0.0f, 1.0f, 0.5f);
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, 64, GL_UNSIGNED_INT, 0);

		glUniform4f(vertexColorLocation, 0.2f, 0.2f, 0.2f, 0.0f);
		glDrawElements(GL_LINE_STRIP, 192, GL_UNSIGNED_INT, 0);

		rotar_todo(circulo, 192, 5);

		//*****triangle no indice*****

		int r = rand() % 9 + 0;
		int g = rand() % 9 + 0;
		int b = rand() % 9 + 0;

		int n = pow(3, niveles);

		for (int i = 0; i < n; i++)
		{
			sleepcp(20);
			glUniform4f(vertexColorLocation, colorr[r], colorb[g], colorr[b], 0.0f);
			glBindVertexArray(VAO[1]);
			glDrawArrays(GL_TRIANGLES, 3 * i, 3 * i + 3);
			glUniform4f(vertexColorLocation, colorr[g], colorb[r], colorr[b], 0.0f);
			glLineWidth(2.0f);
			glDrawArrays(GL_LINES, 3 * i, 3 * i + 3);
		}

		//los subtriangulos color
		for (int i = 0; i < n; i++)
		{
			int rr = rand() % 9 + 0;
			int gg = rand() % 9 + 0;
			int bb = rand() % 9 + 0;
			glUniform4f(vertexColorLocation, colorr[gg], colorb[bb], colorr[rr], 0.0f);
			glBindVertexArray(VAO[1]);
			glDrawArrays(GL_TRIANGLES, n * i, n + niveles * 2);
		}

		if (rotar_all)
			rotar_todo(arr, pow(3, niveles + 2), -15);
		if (rotar_tri)
		{
			rotar_un_triangulo(arr, 0, n, -0.25, -0.25, 10);
			rotar_un_triangulo(arr, n, n * 2, 0.25, -0.25, 10);
			rotar_un_triangulo(arr, n * 2, n * 3, 0.0, 0.25, 10);
		}

		//glUniform4f(vertexColorLocation,1.0f,1.0f,1.0f, 0.0f);
		//glBindVertexArray(VAO[1]);
		//glDrawArrays(GL_TRIANGLES, 81,84);

		//**Lineas del cuadrado**
		/*
	        glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 0.0f);
       	 	glBindVertexArray(VAO[9]);
       	 	glLineWidth(5.0f);
        	glDrawArrays(GL_LINES, 0,100);
		*/

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(3, VAO);
	glDeleteBuffers(3, VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		rotar_all = true;
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		rotar_all = false;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		rotar_tri = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		rotar_tri = false;
	}
}
