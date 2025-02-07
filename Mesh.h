#pragma once

#include <wrl/client.h>
#include <d3d12.h>
#include "DXCore.h"
#include "Vertex.h"
#include <vector>
#include <memory>
#include "Transform.h"
#include "Graphics.h"
#include <fstream>
#include <DirectXMath.h>

class Mesh
{
private:
	//buffers
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuffer;
	D3D12_INDEX_BUFFER_VIEW ibView{};

	//holds the number of indices a mesh contains
	int indexCount = 0;
	int vertexCount = 0;

	//helper methods
	void CreateBuffers(Vertex* vertices, int numVertices, UINT* indices, int numIndices);
public:
	//methods
	D3D12_VERTEX_BUFFER_VIEW GetVertexBuffer();
	D3D12_INDEX_BUFFER_VIEW GetIndexBuffer();
	int GetIndexCount();
	void CalculateTangents(Vertex* verts, int numVerts, unsigned int* indices, int numIndices);

	//constructor (takes in device context, device, vertices, vertex count, indices, & indice count)
	Mesh(Vertex* verts, int numVertices, UINT* indices, int numIndices);
	//constructor for files
	Mesh(const wchar_t* fileName);
	//destructor
	~Mesh();
};

