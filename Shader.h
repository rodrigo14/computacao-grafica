#include <GL/glew.h>
#include "vec.h"
#include "mesh.h"

class ShaderManager {
public:

	void setVertexShader(const char* vertex);
    void setFragmentShader(const char* fragment);
    void setVertex(Vertex *vertex);
    void setIndice(Face *indice);

    GLuint initShader();
    void criarVertexArray();
    void criarBufferDeVertex();
    void criarBufferDeIndex();
    void renderizarCena();

  private:

    char* readShaderSource(const char* shaderFile);

    Shader shaders[2];
    GLuint VBO, IBO, vertexArrayID;
    Vertex *buffer;
    Face *indice;
};