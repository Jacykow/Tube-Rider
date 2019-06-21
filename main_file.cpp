/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myCube.h"
#include "gameObject.h"

#define OBSTACLES_PER_ROW 8
#define ROW_AMOUNT 12
#define FULL_CIRCLE 6.28318530718f

typedef unsigned int uint;

float speed_x=0;
float speed_y=0;
float shipAngle=0;
float timeDelta=0;
float aspectRatio=1;
float distanceTraveled=0;
int rowId=0;

std::vector<obstacle> objects;
gameObject ship;
using namespace Models;
using namespace glm;

void addRow(float z){
    for(uint x=0;x<OBSTACLES_PER_ROW;x++){
        obstacle o;
        o.model = &cube;
        o.shaderProgram = spLambert;
        o.z = z;
        o.orderInRow = x;
        objects.push_back(o);
    }
}



void init(){ // To się będzie działo raz na start
	glfwSetTime(0);

    ship.model = &teapot;
    ship.shaderProgram = spLambert;
}

void update(){ // W każdej klatce
    // GLOBAL
    timeDelta = glfwGetTime();
    glfwSetTime(0);

    // SHIP
    shipAngle+=speed_x*timeDelta;

    // OBSTACLES
    float distanceDelta = timeDelta * 2.5f;
    distanceTraveled -= distanceDelta;
    for(uint x=0;x<objects.size();x++){
        objects[x].z-=distanceDelta;
        if(objects[x].z < -5){
            objects.erase(objects.begin()+x);
            x--;
        }
    }

    while(objects.size() < ROW_AMOUNT*OBSTACLES_PER_ROW){
        addRow(distanceTraveled);
        distanceTraveled+=1.0f;
    }
}

void prepareToDraw(){ // Przed każdym narysowaniem
    mat4 M;

    // SHIP
    M = mat4(1.0f);
    M = rotate(M,shipAngle,vec3(0.0f,0.0f,1.0f));
    M = translate(M,vec3(0.0f,1.0f,0.0f));
    M = rotate(M,-shipAngle,vec3(0.0f,0.0f,1.0f));
    M = scale(M,vec3(0.5f,0.5f,0.5f));
    ship.drawM = M;

    // OBSTACLES
    for(uint x=0;x<objects.size();x++){
        float oAngle = FULL_CIRCLE * objects[x].orderInRow / OBSTACLES_PER_ROW;
        M = mat4(1.0f);
        M = rotate(M,oAngle,vec3(0.0f,0.0f,1.0f));
        M = translate(M,vec3(0.0f,-1.0f,objects[x].z));
        M = scale(M,vec3(0.2f,0.2f,0.2f));
        objects[x].drawM = M;
    }
}



//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {
    if (action==GLFW_PRESS) {
        if (key==GLFW_KEY_LEFT) speed_x=-PI/2;
        if (key==GLFW_KEY_RIGHT) speed_x=PI/2;
        if (key==GLFW_KEY_UP) speed_y=PI/2;
        if (key==GLFW_KEY_DOWN) speed_y=-PI/2;
    }
    if (action==GLFW_RELEASE) {
        if (key==GLFW_KEY_LEFT) speed_x=0;
        if (key==GLFW_KEY_RIGHT) speed_x=0;
        if (key==GLFW_KEY_UP) speed_y=0;
        if (key==GLFW_KEY_DOWN) speed_y=0;
    }
}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
    if (height==0) return;
    aspectRatio=(float)width/(float)height;
    glViewport(0,0,width,height);
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
    initShaders();
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window,windowResizeCallback);
	glfwSetKeyCallback(window,keyCallback);
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
}




//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 V=glm::lookAt(
         glm::vec3(0, 0, -5),
         glm::vec3(0,0,0),
         glm::vec3(0.0f,1.0f,0.0f)); //Wylicz macierz widoku

    glm::mat4 P=glm::perspective(50.0f*PI/180.0f, aspectRatio, 0.01f, 50.0f); //Wylicz macierz rzutowania


    spLambert->use();//Aktywacja programu cieniującego
    //Przeslij parametry programu cieniującego do karty graficznej
    glUniform4f(spLambert->u("color"),0,1,0,1);
    glUniformMatrix4fv(spLambert->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(spLambert->u("V"),1,false,glm::value_ptr(V));

    ship.draw();
    for(uint x=0;x<objects.size();x++){
        objects[x].draw();
    }

    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}


int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla
	init();
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
        update();
        prepareToDraw();
        drawScene(window); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
