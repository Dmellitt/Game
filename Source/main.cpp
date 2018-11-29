// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow* window;
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <SDL2_mixer/SDL_mixer.h>

#include "Setup/shader.hpp"
#include "Setup/texture.hpp"
#include "gameObject.hpp"
#include "light.hpp"
#include "background.hpp"
#include "screen.hpp"
#include "guy.hpp"
#include "fog.hpp"
#include "snow.hpp"
#include "floater.hpp"

#include <vector>
using std::vector;

bool buffer[255];
Mix_Music *mus = NULL;
GLuint vertexbuffer;
GLuint uvbuffer;
GLuint FramebufferName;
GLuint renderedTexture;
GLuint Texture;

// ambient light color
float br = 0, bg = 0, bb = 0;

// light color
float lr = 1, lg = 1, lb = 1;

vector<GameObject*> sceneLights;
vector<GameObject*> background;
vector<GameObject*> midground;
vector<GameObject*> foreground;
Screen screen(0,0);
Guy guy(0,-0.26);

void draw(const vector<GLfloat> vertices, const vector<GLfloat> uvs);

void updateGroup(vector<GameObject*>& vec, float delta) {
    for(int i=0; i<vec.size(); i++) {
        if(!vec[i]->update(delta)) {
            delete vec[i];
            vec.erase(vec.begin()+i);
        }
    }
}

void update(float delta) {
    guy.control(buffer, delta);
    guy.update(midground, delta);
    
    updateGroup(background, delta);
    updateGroup(midground, delta);
    updateGroup(foreground, delta);
    
    if(buffer['U']) {
        lr += delta*0.5;
        if(lr > 1)
            lr = 1;
    }
    if(buffer['I']) {
        lg += delta*0.5;
        if(lg > 1)
            lg = 1;
    }
    if(buffer['O']) {
        lb += delta*0.5;
        if(lb > 1)
            lb = 1;
    }
    if(buffer['J']) {
        lr -= delta*0.5;
        if(lr < 0)
            lr = 0;
    }
    if(buffer['K']) {
        lg -= delta*0.5;
        if(lg < 0)
            lg = 0;
    }
    if(buffer['L']) {
        lb -= delta*0.5;
        if(lb < 0)
            lb = 0;
    }
    
    if(buffer['R']) {
        br += delta*0.5;
        if(br > 1)
            br = 1;
    }
    if(buffer['T']) {
        bg += delta*0.5;
        if(bg > 1)
            bg = 1;
    }
    if(buffer['Y']) {
        bb += delta*0.5;
        if(bb > 1)
            bb = 1;
    }
    if(buffer['F']) {
        br -= delta*0.5;
        if(br < 0)
            br = 0;
    }
    if(buffer['G']) {
        bg -= delta*0.5;
        if(bg < 0)
            bg = 0;
    }
    if(buffer['H']) {
        bb -= delta*0.5;
        if(bb < 0)
            bb = 0;
    }
    
    printf("lr: %f lg: %f lb: %f\n", lr, lg, lb);
    printf("br: %f bg: %f bb: %f\n", br, bg, bb);
}

void render() {
    vector<GLfloat> vertices;
    vector<GLfloat> uvs;
    
    // scene
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
    glClearColor(0, 0, 0, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, Texture);

    for(GameObject* obj: background)
        obj->buffer(vertices, uvs);
    
    guy.buffer(vertices, uvs);
    for(GameObject* obj: midground)
        obj->buffer(vertices, uvs);
    
    for(GameObject* obj: foreground)
        obj->buffer(vertices, uvs);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    draw(vertices, uvs);
    
    // lights
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(br, bg, bb, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    vertices.clear();
    uvs.clear();
    
    for(GameObject* light: sceneLights)
        light->buffer(vertices, uvs);

    glBlendColor(lr, lg, lb, 1.0f);
    glBlendFunc(GL_CONSTANT_COLOR, GL_ONE);
    draw(vertices, uvs);
    
    // lighted scene
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    vertices.clear();
    uvs.clear();
    screen.buffer(vertices, uvs);
    glBlendFunc(GL_DST_COLOR, GL_ZERO);
    draw(vertices, uvs);
    
    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key < 0 || key > 254)
        return;

    if (action == GLFW_PRESS)
        buffer[key] = 1;
    else if(action == GLFW_RELEASE)
        buffer[key] = 0;
}

int main( int argc, char* args[] )
{
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    mus = Mix_LoadMUS( "./Menu.mp3" );
    Mix_FadeInMusic(mus, -1, 500);
    
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 511, 512, "Game", NULL, NULL);
    glfwPollEvents();
    glfwSetWindowSize(window, 512, 512);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
    
	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );
    glUseProgram(programID);
    
    // Texture
    GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
    glUniform1i(TextureID, 0);
    glActiveTexture(GL_TEXTURE0);
    Texture = loadBMP_custom("graphics.bmp");
    glBindTexture(GL_TEXTURE_2D, Texture);

    // Matrix
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	glm::mat4 Ortho = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Ortho[0][0]);

    FramebufferName = 0;
    glGenFramebuffers(1, &FramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
    
    // The texture we're going to render to
    glGenTextures(1, &renderedTexture);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, 0);
    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return 1;

    // Buffers
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &uvbuffer);
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    for(int i=0;i<255;i++)
        buffer[i] = 0;
    glfwSetKeyCallback(window, key_callback);

    glEnable(GL_BLEND);

    // Lights
    sceneLights.push_back(new Light(0,-0.1));
//    sceneLights.push_back(new Light(-1,0));
//    sceneLights.push_back(new Light(1,0));
    
    // snow
    for(int i = 0; i < 4; i++)
        background.push_back(new Snow(2*(i%2), 2*(i/2)-2, -0.05, -0.1));
    for(int i = 0; i < 4; i++)
        background.push_back(new Snow(2*(i%2)-1, 2*(i/2)-1, -0.02, -0.06*(i%2+1)));
    
    // cave
    foreground.push_back(new Background(0,0));
    
    // black rectangles
//    for(int i = 0; i < 12; i++)
//        midground.push_back(new Floater(i%3*4.f/5+2.f/5*(i/3%2)-1, (i/3)/1.9-1, -0.05, 0.1));

    double lastFrameTime = glfwGetTime();
	do{
        double delta = glfwGetTime() - lastFrameTime;
        double waitTime = 1.0/60 - delta;
        if(waitTime > 0)
            usleep((int)(waitTime*1000000));
        delta = glfwGetTime() - lastFrameTime;
        lastFrameTime = glfwGetTime();

        update(delta);
        render();
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
    glDeleteTextures(1, &renderedTexture);
    glDeleteFramebuffers(1, &FramebufferName);
	glDeleteVertexArrays(1, &VertexArrayID);
    
    for(GameObject* obj: background)
        delete obj;
    for(GameObject* obj: midground)
        delete obj;
    for(GameObject* obj: foreground)
        delete obj;
    for(GameObject* obj: sceneLights)
        delete obj;

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
    
    Mix_FreeMusic( mus );
    Mix_Quit();

	return 0;
}

void draw(const vector<GLfloat> vertices, const vector<GLfloat> uvs) {
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size()*sizeof(GLfloat), &uvs[0], GL_STATIC_DRAW);
    
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glDrawArrays(GL_TRIANGLES, 0, int(vertices.size())/2);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
