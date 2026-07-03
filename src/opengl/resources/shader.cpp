#include"shader.h"

std::string get_file_contents(const std::string& filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw std::runtime_error("[ERROR][SHADER] Could not open file: " + filename);
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const std::string& vertFile, const std::string& fragFile)
{
	std::string base = vertFile.substr(vertFile.find_last_of('/') + 1);
	shaderName = base.substr(0, base.find_last_of('.'));
	this->vertFile = vertFile;
	this->fragFile = fragFile;
	
	std::string vertexCode = get_file_contents(vertFile);
	std::string fragmentCode = get_file_contents(fragFile);
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Activates the Shader Program
void Shader::Activate() const
{
	glUseProgram(ID);
}

// Reloads the Shader Program
void Shader::Reload()
{
	uniformLocationCache.clear();
	printConsole= true;
	std::cout << "[VERBOSE][SHADER] Reloaded: " << shaderName << std::endl;

	std::string vertexCode = get_file_contents(vertFile);
	std::string fragmentCode = get_file_contents(fragFile);
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");
	
	glDeleteProgram(ID);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Deletes the Shader Program on OpenGL's side
void Shader::Delete()
{
	glDeleteProgram(ID);
}

// GLuint ID getter
GLuint Shader::getID() const
{
    return ID;
}

Shader::~Shader()
{
	Delete();
}

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (std::string(type) != std::string("PROGRAM"))
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "[ERROR][Shader] Shader compilation error for: " << type << "\n" << infoLog << std::endl;
			// throw std::runtime_error("Shader comp failed"); 
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "[ERROR][Shader] Shader linking error for:" << type << "\n" << infoLog << std::endl;
			throw std::runtime_error("Shader link failed"); 
		}
	}
}