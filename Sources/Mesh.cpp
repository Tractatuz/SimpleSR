#include "stdafx.h"
#include "Mesh.h"
#include <sstream>
#include <fstream>

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
	Release();
}

void Mesh::Initialize()
{
	LoadMeshFromFile("Meshes/cube.obj");
	//rotX = rotY = rotZ = 0.0f;
}

void Mesh::Update()
{
	/*rotX += rotXSpeed;
	rotY += rotYSpeed;
	rotZ += rotZSpeed;

	Matrix4x4 rotXmat, rotYmat, rotZmat;
	rotXmat.mMatrix[0] = 1.0f;
	rotXmat.mMatrix[5] = cos(rotX);
	rotXmat.mMatrix[6] = -sin(rotX);
	rotXmat.mMatrix[9] = sin(rotX);
	rotXmat.mMatrix[10] = cos(rotX);
	rotXmat.mMatrix[15] = 1.0f;

	rotYmat.mMatrix[0] = cos(rotY);
	rotYmat.mMatrix[2] = sin(rotY);
	rotYmat.mMatrix[5] = 1.0f;
	rotYmat.mMatrix[8] = -sin(rotY);
	rotYmat.mMatrix[10] = cos(rotY);
	rotYmat.mMatrix[15] = 1.0f;

	rotZmat.mMatrix[0] = cos(rotZ);
	rotZmat.mMatrix[1] = -sin(rotZ);
	rotZmat.mMatrix[4] = sin(rotZ);
	rotZmat.mMatrix[5] = cos(rotZ);
	rotZmat.mMatrix[10] = 1;
	rotZmat.mMatrix[15] = 1.0f;

	local = rotXmat;*/
}

void Mesh::Render()
{
}

void Mesh::Release()
{
}

void Mesh::LoadMeshFromFile(std::string path)
{
	std::ifstream file;
	file.open(path.c_str());

	std::string line, key, x, y, z;
	//float tempU, tempV, intpart;
	IntVector3 indices[3];
	char delimeter = '/';
	while (!file.eof()) 
	{
		std::getline(file, line);
		std::istringstream iss(line);
		iss >> key;

		if (key == "v") //Vertex data
		{ 
			iss >> x >> y >> z;
			Vector3 vertex(std::stof(x), std::stof(y), std::stof(z));
			vertices.push_back(vertex);
		}
		else if (key == "vn") //Normal data
		{
			iss >> x >> y >> z;
			Vector3 normal(std::stof(x), std::stof(y), std::stof(z));
			normals.push_back(normal);
		}
		else if (key == "vt") //Texture data
		{
			iss >> x >> y;
			Vector3 tex(std::stof(x), std::stof(y), 0);
			texels.push_back(tex);
		}
		else if (key == "f") //index data
		{
			iss >> x >> y >> z;
			std::vector<std::string> splitX = SplitString(x, delimeter);
			std::vector<std::string> splitY = SplitString(y, delimeter);
			std::vector<std::string> splitZ = SplitString(z, delimeter);

			int size = (int)splitX.size();
			for (int i = 0; i < size; ++i) 
			{
				indices[i] = IntVector3(std::stoi(splitX[i]) - 1, std::stoi(splitY[i]) - 1, std::stoi(splitZ[i]) - 1);
			}

			vertexIndices.push_back(indices[0]);
			textureIndices.push_back(indices[1]);
			normalsIndices.push_back(indices[2]);
		}
	}

	numVertices = vertices.size();
	numFaces = vertexIndices.size();

	file.clear();
	file.seekg(0, file.beg);

	file.close();
}

std::vector<std::string> Mesh::SplitString(std::string &str, char delim) 
{
	std::stringstream ss(str);
	std::string token;
	std::vector<std::string> splitString;

	while (std::getline(ss, token, delim)) 
	{
		if (token == "") 
		{
			splitString.push_back("0");
		}
		else 
		{
			splitString.push_back(token);
		}
	}

	return splitString;
}
