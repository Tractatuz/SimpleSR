#pragma once

#include "BaseObject.h"
#include "Vector3.h"

class Mesh : BaseObject
{
public:
	Mesh();
	~Mesh();

public:
	int numVertices = 0;
	int numFaces = 0;
	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<Vector3> texels;
	std::vector<IntVector3> vertexIndices;
	std::vector<IntVector3> textureIndices;
	std::vector<IntVector3> normalsIndices;

	//float rotX, rotY, rotZ;
	//float rotXSpeed = 0.0001f;
	//float rotYSpeed = 0.0000f;
	//float rotZSpeed = 0.000f;
	//Matrix4x4 local;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;

protected:
	virtual void Release() override;

private:
	void LoadMeshFromFile(std::string path);
	std::vector<std::string> SplitString(std::string & str, char delim);
};

