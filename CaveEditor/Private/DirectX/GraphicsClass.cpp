#include "pch.h"
#include "framework.h"
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"
#include "graphicsclass.h"
#include "Squere.h"
#include "BitmapClass.h"


GraphicsClass::GraphicsClass()
{
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	m_screenHeight = screenHeight;
	m_screenWidth = screenWidth;
	// Direct3D ��ü ����
	m_Direct3D = new D3DClass;
	if(!m_Direct3D)
	{
		return false;
	}

	// Direct3D ��ü �ʱ�ȭ
	if(!m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR))
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// m_Camera ��ü ����
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// ī�޶� ������ ����
	m_Camera->SetPosition(0.0f, 0.0f, -100.0f);

	// m_Model ��ü ����
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}
	m_Model->SetMoveX(-3);
	m_Model->SetColor(XMFLOAT4(1, 0.5f, 0.0f, 1));
	// m_Model ��ü �ʱ�ȭ
	if (!m_Model->Initialize(m_Direct3D->GetDevice()))
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	m_Squere = new Squere;

	if (!m_Squere->Initialize(m_Direct3D->GetDevice(),screenWidth,screenHeight, L"seafloor.dds",100,100)) {
		MessageBox(hwnd, L"Could not initialize the squere object", L"Error", MB_OK);
		return false;
	}

	//m_Bitmap = new BitmapClass;
	//
	//if (!m_Bitmap->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, L"test.bmp", 200, 200)) {
	//	MessageBox(hwnd, L"Could not initialize the bitmap object", L"Error", MB_OK);
	//	return false;
	//}
	
	// m_ColorShader ��ü ����
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	// m_ColorShader ��ü �ʱ�ȭ
	if (!m_ColorShader->Initialize(m_Direct3D->GetDevice(), hwnd))
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}
	
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// m_TextureShader ��ü �ʱ�ȭ
	if (!m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd))
	{
		MessageBox(hwnd, L"Could not initialize the Texture shader object.", L"Error", MB_OK);
		return false;
	}


	return true;
}


void GraphicsClass::Shutdown()
{
	if (m_Bitmaps.empty()) {
		for (BitmapClass* i : m_Bitmaps) {
			i->Shutdown();
			delete i;
		}
		m_Bitmaps.clear();
	}
	// m_TextureShader ��ü ��ȯ
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	if (m_Bitmap) {
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	if (m_Squere) {
		m_Squere->Shutdown();
		delete m_Squere;
		m_Squere = 0;
	}

	// m_Model ��ü ��ȯ
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// m_Camera ��ü ��ȯ
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Direct3D ��ü ��ȯ
	if(m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
}


bool GraphicsClass::Frame()
{
	static float rotation = 0.0f;

	// �� �������� rotation ������ ������Ʈ�մϴ�.
	rotation += (float)XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}


	// �׷��� ������ ó��
	return Render(rotation);
}

void GraphicsClass::MoveObject(int index, float posX, float posY)
{
	if (index < m_Bitmaps.size()) {
		m_Bitmaps[index]->SetPos(posX, posY);
	}
}

bool GraphicsClass::AddBitmap(WCHAR* filename, int bitmapWidth, int bitmapHeight)
{
	BitmapClass* temp = new BitmapClass;

	if (!temp->Initialize(m_Direct3D->GetDevice(), m_screenWidth, m_screenHeight, filename, bitmapWidth, bitmapHeight)) {
		return false;
	}

	m_Bitmaps.push_back(temp);

	return true;
	
}

void GraphicsClass::ZoomInScreen()
{
	m_Camera->ZoomIn();
}

void GraphicsClass::ZoomOutScreen()
{
	m_Camera->ZoomOut();
}


bool GraphicsClass::Render(float rotation)
{
	// ���� �׸��� ���� ���۸� ����ϴ�
	m_Direct3D->BeginScene(0.2f, 0.2f, 0.2f, 1.0f);

	// ī�޶��� ��ġ�� ���� �� ����� �����մϴ�
	m_Camera->Render();

	// ī�޶� �� d3d ��ü���� ����, �� �� ���� ����� �����ɴϴ�
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	// �� ���ؽ��� �ε��� ���۸� �׷��� ������ ���ο� ��ġ�Ͽ� ������� �غ��մϴ�.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	// ���� ���̴��� ����Ͽ� ���� �������մϴ�.
	if (!m_ColorShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix))
	{
		return false;
	}

	//m_Direct3D->TurnZBufferOff();

	m_Squere->Render(m_Direct3D->GetDeviceContext(), 50, 50);

	// �ؽ�ó ���̴��� ��Ʈ ���� �������մϴ�.	
	if (!m_ColorShader->Render(m_Direct3D->GetDeviceContext(), m_Squere->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix))
	{
		return false;
	}

	for (BitmapClass* bitmap : m_Bitmaps) {
		bitmap->Render(m_Direct3D->GetDeviceContext());
		if (!m_TextureShader->Render(m_Direct3D->GetDeviceContext(), bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, bitmap->GetTexture()))
		{
			return false;
		}
	}

	/*
	m_Bitmap->Render(m_Direct3D->GetDeviceContext(),200,50);

	if (!m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture()))
	{
		return false;
	}
	*/

	m_Direct3D->TurnZBufferOn();

	// ������ ������ ȭ�鿡 ����մϴ�
	m_Direct3D->EndScene();

	return true;
}