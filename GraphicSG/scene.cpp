#include "scene.h"

#include "reader.h"

#include "geometry.h"
#include "transform.h"
#include "sceneroot.h"

#include "state.h"
#include "rendervisitor.h"

#include <cstdio>
#include <vr/AC3DLoader.h>
#include <vr/Vec3.h>
#include <stack>
#include <map>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <GL/freeglut.h>

using namespace std;


RenderVisitor rv;


void Scene::DFS(Node* u)
{
    u->setColor(1);
    
    //if(u->getNodeTy)
    glPushMatrix();
    u->accept(&rv);
    std::vector<Node*>* children = u->getChildNodes();
    if(u->CountChildNodes()>0){
        for (size_t i = 0; i < children->size(); i++) {
            Node* child = children->at(i);
            if(u->getColor()==0) DFS(child);
        }
    }
    
    u->setColor(0);
    glPopMatrix();
}

void Scene::renderScene()
{ 
     
    DFS(this->root); 
    
     
     
}

Scene::Scene() {    

    this->root = new SceneRoot();
    
    this->root->setColor(0);

    this->root->setNodeName("Root");

}

void Scene::setReader(Reader* r){
    this->cur_r = r;
}

Group* Scene::createSceneGraph()
{
    Group* ggroup;
    
    if (this->cur_r->getLoadFlag()) {
        vr::AC3DLoader::MaterialArray materials = *this->cur_r->getMaterials();

        vr::AC3DLoader::GeometryArray geometries = *this->cur_r->getGeometries();

        size_t gcount = this->cur_r->getNumGeometries();

        
        ggroup=new Group(this->root, "Group");
        
        ggroup->setNodeName("Group");

        //ggroup->SetParentNode(this->root);
        
        this->root->AddChildNode(ggroup);
        
        this->root->Update();
        
        ggroup->setColor(0);
        
        
        Transform* tparent;
        
        Geometry* gparent;

        for (size_t i = 0; i < gcount; i++) {

            const vr::AC3DLoader::Geometry g = geometries[i];

            int vcount = g.getNumVertices();


            gparent=new Geometry(vcount);
            //std::ostringstream ostr; //output string stream
            //ostr << i;
            //std::string number = ostr.str();
            //char* modeg="Geometry ";
            //modeg.append(number);                
            gparent->setNodeName("Geometry");

            tparent=new Transform();
            //char* modet="Transform ";
            //modet.append(number);                
            tparent->setNodeName("Transform");

            tparent->setColor(0);
            
            gparent->setColor(0);

            tparent->setTranslate(g.getTranslation());

            tparent->AddChildNode(gparent);            

            ggroup->AddChildNode(tparent);
            
            const vr::Image* gTextureImage=g.getTexture();
            
            State* state=new State();
            
             if(gTextureImage!=NULL){
                 
                  Texture* texture=new Texture(gTextureImage,GL_TEXTURE_2D);                 
                 
                  state->setEnableTexture(texture,true);
                        
             }
            
            Material material;
            
                material.setAmbient(materials[0].ambient);
                material.setDiffuse(materials[0].diffuse);
                material.setEmission(materials[0].emission);
                material.setSpecular(materials[0].specular);
                material.setShine(materials[0].shine);
                material.setTrans(materials[0].trans);
                
                material.setFace(FRONT_BACK);
                
                material.setMode(AMBIENT);
                
                //state->setEnableMaterial(&material,true);
            
            

            for (size_t j = 0; j < vcount; j++) {

                //Vertex
                const vr::Vec3 v = g.getVertex(j);
                gparent->addVertexCoordinate(j, v);
                
                
                //Material
                vr::AC3DLoader::Material m = materials[g.getMaterial(j)];
                gparent->setMaterial(j, m);

                //Normal
                const vr::Vec3 vnormal = g.getNormal(j);
                gparent->setNormal(j, vnormal);

                //Texture Coordinate
                const vr::Vec2 vTexC = g.getTexCoord(j);
                gparent->setTextureCoordinate(j, vTexC);




            }
            
            if(gcount==1){
                state->setEnablePolygonMode(WIREFRAME,FRONT_BACK);
                gparent->setAnimation(true);
                state->setEnableMaterial(&material,true);         
                vr::Vec3 trans(2,0,0);
                tparent->setTranslate(trans);
                
            }
                
            gparent->setState(state);

            cout << "# Geometry : " << (i + 1) << " Vertices count : " << gparent->getVCount() << "\n";


            cout << "# Transform member count : " << tparent->CountChildNodes() << "\n";
        }

        cout << "# Group member count : " << ggroup->CountChildNodes() << "\n";    

        //renderScene();

     }
    
    return ggroup;
}

Scene::~Scene() {

}

SceneRoot* Scene::getRoot() {
    return this->root;
}





