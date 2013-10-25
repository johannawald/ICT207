#include "CollisionDetection.h"
#include <iostream>


CollisionDetection::CollisionDetection(void)
{

}

CollisionDetection::~CollisionDetection(void)
{
}

bool CollisionDetection::Collision(GLfloat x, GLfloat y, GLfloat z)
{
	bool collision = false;
	for (int i = 0; i<static_box.size(); i++) 
	{
		collision = collision || Collision(static_box[i], x, y, z);
	}
	return collision;
}

bool CollisionDetection::Collision(BoundingBox *b, GLfloat x,GLfloat y,GLfloat z)
{
	if ((x!=x_old) || (y!=y_old) || (z!=z_old)) 
	{
		std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
	}
	x_old = x;
	y_old = y;
	z_old = z;
	
    return x <= b->max.x && x>= b->min.x && y<= b->max.y && y>= b->min.y && z<= b->max.z && z >= b->min.z;
}

void CollisionDetection::drawBox(BoundingBox *b)
{
    glColor3f(1,0,0);
	glBegin(GL_POLYGON);
    glVertex3f(b->max.x,b->max.y,b->min.z);
    glVertex3f(b->min.x,b->max.y,b->min.z);
    glVertex3f(b->min.x,b->min.y,b->min.z);
    glVertex3f(b->max.x,b->min.y,b->min.z);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(b->max.x,b->min.y,b->max.z);
    glVertex3f(b->max.x,b->max.y,b->max.z);
    glVertex3f(b->min.x,b->max.y,b->max.z);
    glVertex3f(b->min.x,b->min.y,b->max.z);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(b->max.x,b->max.y,b->min.z);
    glVertex3f(b->max.x,b->max.y,b->max.z);
    glVertex3f(b->min.x,b->max.y,b->max.z);
    glVertex3f(b->min.x,b->max.y,b->min.z);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(b->max.x,b->min.y,b->max.z);
    glVertex3f(b->min.x,b->min.y,b->max.z);
    glVertex3f(b->min.x,b->min.y,b->min.z);
    glVertex3f(b->max.x,b->min.y,b->min.z);
    glEnd();
}

//display function
void CollisionDetection::display(){
   
	//drawBox();
    //DefineCollisionBoxes(pmodel1,"body"); // actual function call
    //drawBox(static_box[0]); //draw bounding box
    //glPopMatrix();

    //test if the character collides with any of the walls - not working
    /*for(int i=0;i<static_boxes;i++){
        if(CollisionTest(box_mo,static_box[i]) == true){
            printf("collision");
        }
    }*/

    //swap buffers
}

void CollisionDetection::translateBoundingBox(int i, const GLfloat x, const GLfloat y, const GLfloat z)
{
	static_box[i]->max.x += x;
	static_box[i]->max.y += y;
	static_box[i]->max.z += z;
	
	static_box[i]->min.x += x;
	static_box[i]->min.y += y;
	static_box[i]->min.z += z;
}

void CollisionDetection::addCollisionBox(const GLfloat pMinX, const GLfloat pMinY, const GLfloat pMinZ,
										 const GLfloat pMaxX, const GLfloat pMaxY, const GLfloat pMaxZ) 
{
	BoundingBox* bb;
	bb = new BoundingBox;
	bb->max.x = pMaxX;
	bb->max.y = pMaxY;
	bb->max.z = pMaxZ;
	
	bb->min.x = pMinX;
	bb->min.y = pMinY;
	bb->min.z = pMinZ;
	static_box.push_back(bb);
}