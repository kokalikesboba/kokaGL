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

// Reloads the Shader Program, on fail, keeps the previous one active.
void Shader::Reload()
{
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

void Shader::uploadMat4(const std::string &uniformName, const glm::mat4 matrix)
{
	Activate();
	auto it = uniformLocationCache.find(uniformName);
	if (it == uniformLocationCache.end()) {
		// GLint returns -1 when uniform is invalid
		auto uniLoc = glGetUniformLocation(ID, uniformName.c_str());
		if (uniLoc == -1) {	
			std::cerr << "[WARNING][SHADER] Unknown uniform in " << shaderName << ": " << uniformName << std::endl;
			return;
		}
		std::cerr << "[VERBOSE][SHADER] Uniform: " << uniformName << " inserted into " << shaderName << std::endl;
		uniformLocationCache.insert({uniformName, uniLoc});
		glUniformMatrix4fv(uniLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	} else {
		glUniformMatrix4fv(it->second, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}

void Shader::uploadVec3(const std::string &uniformName, const glm::vec3 vector)
{
	Activate();
	auto it = uniformLocationCache.find(uniformName);
	if (it == uniformLocationCache.end()) {
		// GLint returns -1 when uniform is invalid
		auto uniLoc = glGetUniformLocation(ID, uniformName.c_str());
		if (uniLoc == -1) {	
			std::cerr << "[WARNING][SHADER] Unknown uniform in " << shaderName << ": " << uniformName << std::endl;
			return;
		}
		std::cerr << "[VERBOSE][SHADER] Uniform: " << uniformName << " inserted into " << shaderName << std::endl;
		uniformLocationCache.insert({uniformName, uniLoc});
		glUniform3fv(uniLoc, 1, glm::value_ptr(vector));
	} else {
		glUniform3fv(it->second, 1, glm::value_ptr(vector));
	}
}

void Shader::uploadInt1(const std::string &uniformName, int value)
{
	Activate();
	auto it = uniformLocationCache.find(uniformName);
	if (it == uniformLocationCache.end()) {
		// GLint returns -1 when uniform is invalid
		auto uniLoc = glGetUniformLocation(ID, uniformName.c_str());
		if (uniLoc == -1) {	
			std::cerr << "[WARNING][SHADER] Unknown uniform in " << shaderName << ": " << uniformName << std::endl;
			return;
		}
		std::cerr << "[VERBOSE][SHADER] Uniform: " << uniformName << " inserted into " << shaderName << std::endl;
		uniformLocationCache.insert({uniformName, uniLoc});
		glUniform1i(uniLoc, value);
	} else {
		glUniform1i(it->second, value);
	}
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
			std::cerr << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
			// throw std::runtime_error("Shader comp failed"); 
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
			throw std::runtime_error("Shader link failed"); 
		}
	}
}