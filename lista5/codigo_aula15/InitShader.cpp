#include "InitShader.h"

static char* readShaderSource(const char* shaderFile);
// Create a NULL-terminated string by reading the provided file
static char*
readShaderSource(const char* shaderFile)
{
    FILE* fp = fopen(shaderFile, "r");

    if ( fp == NULL ) {
		printf("\n Nao abriu arquivo");
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

// Create a GLSL program object from vertex and fragment shader files
GLuint
InitShader(const char* vShaderFile, const char* fShaderFile)
{
    struct Shader {
	const char*  filename;
	GLenum       type;
	GLchar*      source;
    }  shaders[2] = {
	{ vShaderFile, GL_VERTEX_SHADER, NULL },
	{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
    };


	
    GLuint program = glCreateProgram();
    
    for ( int i = 0; i < 2; ++i ) {
	Shader& s = shaders[i];
	s.source = readShaderSource( s.filename );
//	printf("\n \n\n %s",s.source);
	if ( shaders[i].source == NULL ) {
	    printf( "\nFailed to read %s ",s.filename);
	    exit( EXIT_FAILURE );
	}

	GLuint shader = glCreateShader( s.type );
	glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );
	 glCompileShader( shader );

	GLint  compiled;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );

	if ( !compiled ) {
		printf("\n \n failed to compile: %s", s.filename);
		GLint  logSize;
	    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
	    char* logMsg = new char[logSize];
	    glGetShaderInfoLog( shader, logSize, NULL, logMsg );
		
		printf("\n \n logSize %i failed to compile: %s",logSize, logMsg);
		scanf("%i",&i);
		exit( EXIT_FAILURE );
	}

	//delete [] s.source;

	glAttachShader( program, shader );
    }

    /* link  and error check */
    glLinkProgram(program);

    GLint  linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if ( !linked ) {
//	std::cerr << "Shader program failed to link" << std::endl;
	GLint  logSize;
	glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
	char* logMsg = new char[logSize];
	glGetProgramInfoLog( program, logSize, NULL, logMsg );
//	std::cerr << logMsg << std::endl;
	//delete [] logMsg;

	exit( EXIT_FAILURE );
    }

    /* use program object */
    glUseProgram(program);

    return program;
}

