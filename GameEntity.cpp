#include "GameEntity.h"

GameEntity::GameEntity(std::shared_ptr<Mesh> meshPtr)
{
	mesh = meshPtr;
}

std::shared_ptr<Mesh> GameEntity::GetMesh()
{
	return mesh;
}

Transform& GameEntity::GetTransform()
{
	return transform;
}

void GameEntity::SetMesh(std::shared_ptr<Mesh> meshPtr)
{
	mesh = meshPtr;
}
