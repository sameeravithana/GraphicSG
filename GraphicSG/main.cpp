#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <iostream>
#include <cstdio>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <png.h>


#include <vr/Vec3.h>
#include <vr/Vec4.h>


#include "sceneroot.h"
#include "geometry.h"
#include "group.h"
#include "reader.h"
#include "transform.h"
#include "scene.h"
#include "camera.h"

#define WINDOW_WIDTH  1600
#define WINDOW_HEIGHT 1200


using namespace std;

CCamera camera;

Reader r1("./models/SubdividedDragon.ac");

//Reader r2("./models/tuxedo.ac");

Reader r3("./models/box.ac");

Reader r4("./models/mydesk4.ac");

Reader r5("./models/world.ac");

Scene* scene;
       
float angle,x,y,z;

static void update(int angle){
    angle+=2.0f;
    if(angle>360) angle-=360;
    glutPostRedisplay();
    glutTimerFunc(4000,update,0);
}


//handles the window's resizing event
static void reshape(int x, int y)
{
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return
	
	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	//Angle of view:40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0
	gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,x,y);  //Use the whole window for rendering
        
        
}

static void RenderSceneCB()
{
    
    
    glClear(GL_COLOR_BUFFER_BIT);    
    
    
    glClearColor(0.0, 0.0, 0.0, 10.0);
    
    camera.Render();
    
    
    scene->renderScene();
    
   

    glutSwapBuffers();
}

//handles the key down events
static void KeyDown(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 27:		//ESC
            exit(0);
		break;
	case 'a':		
		camera.RotateY(5.0);
		RenderSceneCB();
		break;
	case 'd':		
		camera.RotateY(-5.0);
		RenderSceneCB();
		break;
	case 'w':		
		camera.MoveForward( -0.1 ) ;
		RenderSceneCB();
		break;
	case 's':		
		camera.MoveForward( 0.5 ) ;
		RenderSceneCB();
		break;
	case 'x':		
		camera.RotateX(5.0);
		RenderSceneCB();
		break;
	case 'y':		
		camera.RotateX(-5.0);
		RenderSceneCB();
		break;
	case 'c':		
		camera.StrafeRight(-0.1);
		RenderSceneCB();
		break;
	case 'v':		
		camera.StrafeRight(0.1);
		RenderSceneCB();
		break;
	case 'f':
		camera.MoveUpward(-0.3);
		RenderSceneCB();
		break;
	case 'r':
		camera.MoveUpward(0.3);
		RenderSceneCB();
		break;

	case 'm':
		camera.RotateZ(-5.0);
		RenderSceneCB();
		break;
	case 'n':
		camera.RotateZ(5.0);
		RenderSceneCB();
		break;
        case 'q':
                glutTimerFunc(4000,update,0);
                break;
                

	}
}



int main(int argc, char** argv)
{
        glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT); //Set the window size

	//Create the window
	glutCreateWindow("Basic Scene Graph Rendering");
        
        //glutGameModeString("1920x1200@32");
        //glutEnterGameMode();
	
        Scene s;
          
        scene=&s;
        
        scene->setReader(&r3);        
                Group* group1=scene->createSceneGraph();
                group1->setNodeName("GROUP_1");
                
        scene->setReader(&r4);        
                Group* group2=scene->createSceneGraph();
                group2->setNodeName("GROUP_2");
                
                //Geometry* geo=group2->GetChildNodeByName("Transform")->GetChildNodeByName("Geometry");
                
        scene->setReader(&r1);        
                Group* group3=scene->createSceneGraph();
                group3->setNodeName("GROUP_3");
                
                Transform* tran=new Transform();
                
                angle=20;
                x=2;y=0.5;z=1;
                
                vr::Vec4 rotate(x,y,z,-angle);
                
                tran->setRotate(rotate);
                                
                vr::Vec3 trans(-4,0,0);
                tran->setTranslate(trans);
                
                tran->AddChildNode(group3);
                
                scene->getRoot()->AddChildNode(tran);
                
                /*Geometry* geo=new Geometry(6);
                const vr::Vec3 tri1(0.0,1.0,0.0);
                const vr::Vec3 tri2(2.0,0.0,3.0);
                const vr::Vec3 tri3(0.0,3.0,3.0);
                const vr::Vec3 tri4(4.0,1.0,0.0);
                const vr::Vec3 tri5(2.0,4.0,3.0);
                const vr::Vec3 tri6(0.0,3.0,4.0);
                geo->addVertexCoordinate(0,tri1);
                geo->addVertexCoordinate(1,tri2);
                geo->addVertexCoordinate(2,tri3);
                geo->addVertexCoordinate(3,tri4);
                geo->addVertexCoordinate(4,tri5);
                geo->addVertexCoordinate(5,tri6);
                State* sta=new State();sta->setEnablePolygonMode(WIREFRAME,FRONT_BACK);
                geo->setState(sta);
                tran->AddChildNode(geo);*/
                
                
        
        camera.Move( F3dVector(0.0, 0.0, 2.0 ));
	camera.MoveForward( 1.0 );
	
	glutReshapeFunc(reshape);
	glutKeyboardFunc(KeyDown);
        
        
        glutDisplayFunc(RenderSceneCB);
        
        
        glutMainLoop();
        
        
    return 0;
}

