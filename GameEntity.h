#pragma once
#include "Transform.h"
#include "Mesh.h"

class GameEntity
{
public:
	//constructor
	GameEntity(std::shared_ptr<Mesh> meshPtr);

	//getters
	std::shared_ptr<Mesh> GetMesh();
	Transform& GetTransform();

	//setters
	void SetMesh(std::shared_ptr<Mesh> meshPtr);

private:
	//transform and mesh data
	std::shared_ptr<Mesh> mesh;
	Transform transform;
};

