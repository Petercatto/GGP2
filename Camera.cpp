#include "Camera.h"
#include "Input.h"
#include <algorithm>

using namespace DirectX;

Camera::Camera(float _x, float _y, float _z, float mSpeed, float lSpeed, float fov, float aspectRatio) :
	nearPlane(0.01f),
	farPlane(1000.0f)
{
	transform.SetPosition(_x, _y, _z);
	this->moveSpeed = mSpeed;
	this->lookSpeed = lSpeed;
	this->FOV = fov;

	//initialize starting matrices
	XMStoreFloat4x4(&viewMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&projMatrix, XMMatrixIdentity());

	//update the matrices
	UpdateViewMatrix();
	UpdateProjectionMatrix(aspectRatio);
}

//gets the view matrix
DirectX::XMFLOAT4X4 Camera::GetView()
{
	return viewMatrix;
}

//gets the projection matrix
DirectX::XMFLOAT4X4 Camera::GetProjection()
{
	return projMatrix;
}

Transform Camera::GetTransform()
{
	return transform;
}

float Camera::GetFOV()
{
	return FOV;
}

//updates the projection matrix and stores it
void Camera::UpdateProjectionMatrix(float aspectRatio)
{
	XMStoreFloat4x4(&projMatrix, XMMatrixPerspectiveFovLH(FOV, aspectRatio, nearPlane, farPlane));
}

//updates the view matrix and stores it
void Camera::UpdateViewMatrix()
{
	//position of the camera
	XMFLOAT3 pos = transform.GetPosition();
	//direction its looking
	XMFLOAT3 fwd = transform.GetForward();
	//make the view matrix with global up vector
	XMMATRIX view = XMMatrixLookToLH(XMLoadFloat3(&pos), XMLoadFloat3(&fwd), XMVectorSet(0, 1, 0, 0));
	//store view matrix
	XMStoreFloat4x4(&viewMatrix, view);
}

void Camera::Update(float dt)
{
	//WASD relative controls
	if (Input::KeyDown('W')) { transform.MoveRelative(0.0, 0.0, dt * moveSpeed); }
	if (Input::KeyDown('S')) { transform.MoveRelative(0.0, 0.0, dt * -moveSpeed); }
	if (Input::KeyDown('A')) { transform.MoveRelative(dt * -moveSpeed, 0.0, 0.0); }
	if (Input::KeyDown('D')) { transform.MoveRelative(dt * moveSpeed, 0.0, 0.0); }

	//up and down absolute controls
	if (Input::KeyDown(' ')) { transform.MoveAbsolute(0.0, dt * moveSpeed, 0.0); }
	if (Input::KeyDown(VK_LCONTROL)) { transform.MoveAbsolute(0.0, dt * -moveSpeed, 0.0); }

	//mouse movement
	if (Input::MouseLeftDown())
	{
		float cursorMovementX = static_cast<float>(Input::GetMouseXDelta());
		float cursorMovementY = static_cast<float>(Input::GetMouseYDelta());

		cursorMovementX *= lookSpeed;
		cursorMovementY *= lookSpeed;

		//apply the rotation
		transform.Rotate(cursorMovementY, cursorMovementX, 0);

		//clamp the x rotation so camera cant be flipped
		if (transform.GetPitchYawRoll().x > XM_PI / 2.0f - 0.1f)
		{
			transform.SetRotation(XM_PI / 2.0f - 0.1f, transform.GetPitchYawRoll().y, transform.GetPitchYawRoll().z);
		}
		else if (transform.GetPitchYawRoll().x < -XM_PI / 2.0f + 0.1f)
		{
			transform.SetRotation(-XM_PI / 2.0f + 0.1f, transform.GetPitchYawRoll().y, transform.GetPitchYawRoll().z);
		}
	}

	//update the view matrix
	UpdateViewMatrix();
}
