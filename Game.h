#pragma once

#include <d3d12.h>
#include <wrl/client.h>
#include "Camera.h"
#include "Mesh.h"
#include "Transform.h"
#include "GameEntity.h"
#include <memory>
#include "BufferStructs.h"

class Game
{
public:
	// Basic OOP setup
	Game() = default;
	~Game();
	Game(const Game&) = delete; // Remove copy constructor
	Game& operator=(const Game&) = delete; // Remove copy-assignment operator

	// Primary functions
	void Initialize();
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);
	void OnResize();

private:

	// Initialization helper methods - feel free to customize, combine, remove, etc.
	void CreateGeometry();
	void CreateRootSigAndPipelineState();

	// Note the usage of ComPtr below
	//  - This is a smart pointer for objects that abide by the
	//     Component Object Model, which DirectX objects do
	//  - More info here: https://github.com/Microsoft/DirectXTK/wiki/ComPtr

	// Pipeline
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

	// Other graphics data
	D3D12_VIEWPORT viewport{};
	D3D12_RECT scissorRect{};

	//camera
	std::shared_ptr<FPSCamera> camera;

	//entity vector
	std::vector<std::shared_ptr<GameEntity>> entities;
};

