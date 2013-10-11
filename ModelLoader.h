/**
 * @class ModelLoader
 * @brief Stores details for a 3 dimensional model.
 *
 * Contains information for vertices, normals, texels and faces. Loads 
 * and Draws a 3D model into a 3D environment.
 *
 * @author Raymond Forster
 * @version 03
 * @date 20/08/2012 Raymond Forster - started
 * @date 07/09/2012 Raymond Forster - added texture mapping
 * @date 10/09/2013 Raymond Forster - modified texture mapping to match image orientation
 */

//--------------------------------------------------------------------------------------

#ifndef MODELLOADER_H
#define MODELLOADER_H

//--------------------------------------------------------------------------------------

#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <GL\gl.h>

using namespace std;

//--------------------------------------------------------------------------------------
// FData Structures

	/*
	 * @struct Vector
	 *
	 * @brief A structure to represent 3D vectors.
	 */
typedef struct
{
	float x; /**< the x coordinate of the 3D vector*/
	float y; /**< the y coordinate of the 3D vector*/
	float z; /**< the z coordinate of the 3D vector*/
}
Vector;

	/*
	 * @struct Face
	 *
	 * @brief A structure to represent 3D object polygons.
	 *
	 * Includes a list of vertices, surface normals and texture coordinates.
	 */
typedef struct
{
	int v1; /**< the first vertex of the face*/
	int v2; /**< the second vertex of the face*/
	int v3; /**< the third vertex of the face*/
	int vn1; /**< the normal for the first vertex of the face*/
	int vn2; /**< the normal for the second vertex of the face*/
	int vn3; /**< the normal for the third vertex of the face*/
	int vt1; /**< the texture coordinate for the first vertex of the face*/
	int vt2; /**< the texture coordinate for the second vertex of the face*/
	int vt3; /**< the texture coordinate for the third vertex of the face*/
}
Face;

//--------------------------------------------------------------------------------------

class ModelLoader
{
	public:

			/**
             * @brief Default constructor creates a new ModelLoader object.
             *
             * @param none
             */
		ModelLoader(){};

			/**
             * @brief Destructor destroys ModelLoader object when it goes out of scope.
             * @param none
             */
		~ModelLoader(){};

			/**
             * @brief Loads a 3D model from a .obj file.
			 *
			 * Loads a list of vertices, normals, texture coordinates and faces from a 
			 * Wavefront OBJ model file.
			 *
             * @param char *filename - the model file to be loaded.
			 * @return bool - returns true if the model was successfully loaded, otherwise returns false.
             */
		bool load(char *filename);

			/**
             * @brief Draws a 3D model object within a 3 dimensional world using OpenGL GL_TRIANGLES
             * @param none
			 * @return void
             */
		void draw();

	private:
		vector<Vector> vertices; /**< Stores a list of vertices used by the 3D model*/
		vector<Vector> normals; /**< Stores a list of normals used by the 3D model*/
		vector<Vector> texels; /**< Stores a list of texture coordinates used by the 3D model*/
		vector<Face> faces; /**< Stores a list of faces comprising the 3D model*/

			/**
             * @brief Parses a line read from a .obj file to determine if the line represents a vertex, normal, texture coordinate or face.
             * @param char *line - a line of text read from file
			 * @return void
             */
		void parseLine(char *line);

			/**
             * @brief Parses a line representing a vertex read from file and stores vertex coordinates
             * @param char *line - a line of text read from file
			 * @return void
             */
		void parseVertex(char *line);

			/**
             * @brief Parses a line representing a normal read from file and stores vector coordinates
             * @param char *line - a line of text read from file
			 * @return void
             */
		void parseNormal(char *line);

			/**
             * @brief Parses a line representing a texture coordinate read from file and stores coordinates
             * @param char *line - a line of text read from file
			 * @return void
             */
		void parseTexel(char *line);

			/**
             * @brief Parses a line representing a face read from file and stores vertex, normal and texel list indexes.
             * @param char *line - a line of text read from file
			 * @return void
             */
		void parseFace(char *line);
};

#endif //end of ModelLoader class