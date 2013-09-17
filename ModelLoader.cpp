//--------------------------------------------------------------------------------------
// ModelLoader.cpp
// Implementation file for the ModelLoader class
// Stores details for a 3 dimensional model. Contains information for vertices, 
// normals, texels and faces. Loads and Draws a 3D model into a 3D environment.
//
// Author: Raymond Forster
// Version: 03
// Date: 20/08/2012 Raymond Forster - started
// Date: 07/09/2012 Raymond Forster - added texture mapping
// Date: 10/09/2013 Raymond Forster - modified texture mapping to match image orientation
//--------------------------------------------------------------------------------------

/*
Using the ModelLoader class

Using the class requires the .obj file passed to the load() function to be formatted in a specific way. The .obj file must include all of the following in order to work without error:

	1. All vertices (v)
	2. All vertex normals (vn)
	3. All vertex texture coordinates (vt)
	4. All faces (f)
	
Vertices (v)

Each vertex will be listed as a set of 3 coordinates representing x, y and z. These vertices will be referenced as an index by a face (f). A vertex will appear in the following format:

	v x y z

Vertext Normals (vn)

Each vertex normal will be listed as a set of 3 coordinates representing x, y and z. These vertex normals will be referenced as an index by a face (f). A vertex normal will appear in the following format:

	vn x y z

Vertex Texture Coordinates (vt)

Each vertex texture coordinate will be listed as a set of 3 coordinates representing x, y and z. These texture coordinates will apply a texture map to an image based on the coordinates listed for the associated face (f). A vertex texture coordinate will appear in the following format:

	vt x y z

Faces (f)

A face is represented as series of indexes to the vertex, normals and texture coordinate lists. Each face is listed as GL_TRIANGLES. Each face will be listed as a set of values in the following format:

	f xv/xvt/xvn yv/yvt/yvn zv/zvt/zvn
	
	Where f means the line is a face, x is the first vertex of the face, y is the second vertex of the face and z is the third vertex of the face. Each vertex will be represented by 3 values separated by a forward slash where v is the vertex vector for that vertex, vt is the texture coordinate for that vertex and vn is the vertex normal for that vertex.

	
Exporting the .obj using Autodesk 3DS Max

After your model is finished and ready to be exported use the following steps:

	1. Go to the main menu and select Export, this will open the file manager.
	2. Navigate to the folder you wish to save the file to.
	3. Enter the name to save the file as.
	4. In the Save as type dropdown menu select OBJ-Exporter(*.OBJ)
	5. Press save.
	6. This will open the OBJ export options menu.
	7. Make sure the Faces dropdown menu is set to TRIANGLES.
	8. Make sure texture coordinates and normals checkboxes are checked.
	9. Press the Export button.
	10. This will bring up the Export statistics window which will list the number of vertices, normals, texture coordinates and triangles saved.
	11. Press Done.
	
	Your .obj should be ready to use.
	
	
Using ModelLoader model loader to load a model

To use the model loader, first you need to declare an object of the ModelLoader type

	eg. ModelLoader cube;
	
To load the model from a .obj file use the load() function using the .obj filename as a parameter

	eg. cube.load("cube.obj");
	
To draw the model use the draw function

	eg. cube.draw();
*/

#include "ModelLoader.h"

bool ModelLoader::load(char *filename)
{
	fstream objFile;
	bool isGood;

	objFile.open(filename); //open the file to be read

	if(objFile.is_open()) //if the file was opened successfully
	{
		char line[255];

		while(objFile.good()) //while there is data to be read
		{
			objFile.getline(line, 255); //get a line from the file
			parseLine(line); //check if the line is a vertex, normal, texture coordinate or a face 
		}

		objFile.close(); //close the file
		isGood = true; //model loaded successfully
	}

	else
	{
		cout << "**Error: could not open Model file '" << filename << "'\n";
		isGood = false; //model could not be loaded
	}

	return isGood;
}

void ModelLoader::draw()
{
	glBegin(GL_TRIANGLES); //prepare to draw triangles

	for(int i=0; i<faces.size(); i++) //for each face of the model
	{
		glNormal3f(normals[faces[i].vn1 - 1].x, normals[faces[i].vn1 - 1].y, normals[faces[i].vn1 - 1].z); //set normals for vertex 1
		glTexCoord3f(texels[faces[i].vt1 - 1].x, texels[faces[i].vt1 - 1].y*-1, texels[faces[i].vt1 - 1].z); //set texture coordinates for vertex 1
		glVertex3f(vertices[faces[i].v1 - 1].x, vertices[faces[i].v1 - 1].y, vertices[faces[i].v1 - 1].z); //set vertex 1

		glNormal3f(normals[faces[i].vn2 - 1].x, normals[faces[i].vn2 - 1].y, normals[faces[i].vn2 - 1].z); //set normals for vertex 2
		glTexCoord3f(texels[faces[i].vt2 - 1].x, texels[faces[i].vt2 - 1].y*-1, texels[faces[i].vt2 - 1].z); //set texture coordinates for vertex 2
		glVertex3f(vertices[faces[i].v2 - 1].x, vertices[faces[i].v2 - 1].y, vertices[faces[i].v2 - 1].z); //set vertex 2

		glNormal3f(normals[faces[i].vn3 - 1].x, normals[faces[i].vn3 - 1].y, normals[faces[i].vn3 - 1].z); //set normals for vertex 3
		glTexCoord3f(texels[faces[i].vt3 - 1].x, texels[faces[i].vt3 - 1].y*-1, texels[faces[i].vt3 - 1].z); //set texture coordinates for vertex 3
		glVertex3f(vertices[faces[i].v3 - 1].x, vertices[faces[i].v3 - 1].y, vertices[faces[i].v3 - 1].z); //set vertex 3
	}

	glEnd(); //stop drawing triangles
}

void ModelLoader::parseLine(char *line)
{
	//check for an empty string
	if(!strlen(line))
	{
		return;
	}

	char *linetype;
	linetype = strtok(strdup(line), " ");

	if(!strcmp(linetype, "v"))
	{
		parseVertex(line); //line is a vertex
	}

	else if(!strcmp(linetype, "vn"))
	{
		parseNormal(line); //line is a normal
	}

	else if(!strcmp(linetype, "vt"))
	{
		parseTexel(line); //line is a texel
	}

	else if(!strcmp(linetype, "f"))
	{
		parseFace(line); //line is a face
	}

	return;
}

void ModelLoader::parseVertex(char *line)
{
	vertices.push_back(Vector()); //add a new vertex to list of vertices

	sscanf(line, "v %f %f %f", &vertices.back().x, &vertices.back().y, &vertices.back().z); //store the x, y and z coordinates of the new vertex

	return;
}

void ModelLoader::parseNormal(char *line)
{
	normals.push_back(Vector()); //add a new normal to list of normals

	sscanf(line, "vn %f %f %f", &normals.back().x, &normals.back().y, &normals.back().z); //store the x, y and z coordinates of the new normal

	return;
}

void ModelLoader::parseTexel(char *line)
{
	texels.push_back(Vector()); //add a new texel to list of texture coordinates

	sscanf(line, "vt %f %f %f", &texels.back().x, &texels.back().y, &texels.back().z); //store the x, y and z coordinates of the new texel

	return;
}

void ModelLoader::parseFace(char *line)
{
	faces.push_back(Face()); //add a new face to list of faces

	//if the .obj file does not include texture coordinates, store vertex and normal indexes for the face
	if(sscanf(line, "f %d//%d %d//%d %d//%d", &faces.back().v1, &faces.back().vn1, &faces.back().v2, &faces.back().vn2, &faces.back().v3, &faces.back().vn3) <= 1)
	{
		//if the .obj file includes texture coordinates, store vertex, normal and textel indexes
		sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &faces.back().v1, &faces.back().vt1, &faces.back().vn1, &faces.back().v2, &faces.back().vt2, &faces.back().vn2, &faces.back().v3, &faces.back().vt3, &faces.back().vn3);
	}
}
