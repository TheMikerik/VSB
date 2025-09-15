//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

// Ctverec se dela z 2 trianglu xdd wtf
float points[] = {
    -0.5f,  0.5f, 0.0f,
    	0.5f,  0.5f, 0.0f,
    	0.5f, -0.5f, 0.0f,
    	0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

const char* vertex_shader =
"#version 330 core\n"
"layout(location = 0) in vec3 vp;"
"void main() {"
"    gl_Position = vec4(vp, 1.0);"
"}";

const char* fragment_shader =
"#version 330 core\n"
"out vec4 frag_colour;"
"void main() {"
"    frag_colour = vec4(1.0, 1.0, 0.0, 1.0);"
"}";


static void error_callback(int error, const char* description){ fputs(description, stderr); }

// GLM test

// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
	glm::vec3(10, 10, 10), // Camera position
	glm::vec3(0, 0, 0),    // Look at origin
	glm::vec3(0, 1, 0)     // Head is up
);

// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f);

int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	// Initialize specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Start GLEW extension handler
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "ERROR: could not initialize GLEW\n");
		exit(EXIT_FAILURE);
	}

	// Get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	// float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	// Vertex Buffer Object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // Generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// Vertex Array Object (VAO)
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO); // Generate the VAO
	glBindVertexArray(VAO);      // Bind the VAO
	glEnableVertexAttribArray(0); // Enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Create and compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);

	// Check for vertex shader compilation errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
		glDeleteShader(vertexShader);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);

	// Check for fragment shader compilation errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Link shaders to create a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
		glDeleteProgram(shaderProgram);
		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Shaders are linked into the program and no longer needed separately
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	while (!glfwWindowShouldClose(window)){
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// Draw triangles
		glDrawArrays(GL_TRIANGLES, 0, 6); // mode, first, count
		// Update other events like input handling
		glfwPollEvents();
		// Put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}