#pragma once
#include <Windows.h>
#include <string>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace Graphics
{
	// --- GLOBAL VARS ---
	// Debug Layer
	inline Microsoft::WRL::ComPtr<ID3D12InfoQueue> InfoQueue;

	const unsigned int NumBackBuffers = 2;

	inline Microsoft::WRL::ComPtr<ID3D12Device> Device;
	inline Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain;
	// Command submission
	inline Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CommandAllocator;
	inline Microsoft::WRL::ComPtr<ID3D12CommandQueue> CommandQueue;
	inline Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList;

	// Rendering buffers & descriptors:
	inline Microsoft::WRL::ComPtr<ID3D12Resource> BackBuffers[NumBackBuffers];
	inline Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> RTVHeap; // Render Target View Descriptor Heap which holds the RTV for each frame buffer
	inline D3D12_CPU_DESCRIPTOR_HANDLE RTVHandles[NumBackBuffers]{}; // CPU handles for each RTV in the heap which we can use to set the render target
	inline Microsoft::WRL::ComPtr<ID3D12Resource> DepthBuffer;
	inline Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DSVHeap; // Depth Stencil View Descriptor Heap which holds the DSV for the depth buffer
	inline D3D12_CPU_DESCRIPTOR_HANDLE DSVHandle{};

	//cpu/gpu sync:
	inline Microsoft::WRL::ComPtr<ID3D12Fence> WaitFence;
	inline HANDLE WaitFenceEvent = 0;
	inline UINT64 WaitFenceCounter = 0;

	//each buffer is 256bytes or less.
	const unsigned int maxConstantBuffers = 1000;
	inline Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CBVSRVDescriptorHeap;
	inline Microsoft::WRL::ComPtr<ID3D12Resource> CBUploadHeap;
	D3D12_GPU_DESCRIPTOR_HANDLE FillNextConstantBufferAndGetGPUDescriptorHandle(
		void* data,
		unsigned int dataSizeInBytes);

	// --- FUNCTIONS ---

	// Getters
	bool VsyncState();
	std::wstring APIName();
	unsigned int SwapChainIndex();

	// General functions
	HRESULT Initialize(unsigned int windowWidth, unsigned int windowHeight, HWND windowHandle, bool vsyncIfPossible);
	void ShutDown();
	void ResizeBuffers(unsigned int width, unsigned int height);
	void AdvanceSwapChainIndex();

	// Resource creation
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateStaticBuffer(
		size_t dataStride, size_t dataCount, void* data);
	// Command list & synchronization
	void ResetAllocatorAndCommandList();
	void CloseAndExecuteCommandList();
	void WaitForGPU();

	// Debug Layer
	void PrintDebugMessages();
}