#include <iostream>
#include "Shader.h"

using namespace std;

void
ShaderManager::setVertexShader(const char* vertex) {
	this->shaders[0] = Shader(vertex, GL_VERTEX_SHADER, NULL);
}

void
ShaderManager::setFragmentShader(const char* fragment) {
	this->shaders[1] = Shader(fragment, GL_FRAGMENT_SHADER), NULL);
}

void
ShaderManager::setVertex(Vertex *vertex)
{
  this->buffer = vertex;
}

void ShaderManager::setIndice(Face *indice) {
	this->indice = indice;
}

char *
ShaderManager::readShaderSource(const char *shaderFile) {
	FILE *fp = fopen(shaderFile, "r");
	if (fp == NULL) {
		cout << "Arquivo não encontrado" << endl;
		return NULL;
	}

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);

	buf[size] = '\0';
	fclose(fp);

	return buf;
}