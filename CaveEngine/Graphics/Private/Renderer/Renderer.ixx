/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <iostream>
#include "Graphics.h"
import DdsTextureLoader;

export module Renderer;

//namespace cave
//{
//	namespace Renderer
//	{
//		/**
//		 * @brief Simple Vertex Structure, acts as the input to the Vertex Shader
//		 * @details Contains position and texture coordinate
//		 * @author Alegruz
//		 * @version 0.0.1
//		 * 
//		 */
//		struct SimpleVertex
//		{
//			DirectX::XMFLOAT3 mPosition;	/*!< Vertex position data */
//			DirectX::XMFLOAT2 mTexCoord;	/*!< Vertex texture coordinate data */
//		};
//
//		struct ConstantBufferNeverChanges
//		{
//			DirectX::XMMATRIX mView;
//		};
//
//		struct ConstantBufferChangeOnResize
//		{
//			DirectX::XMMATRIX mProjection;
//		};
//
//		struct ConstantBufferChangesEveryFrame
//		{
//			DirectX::XMMATRIX mWorld;
//			DirectX::XMFLOAT4 mvMeshColor;
//		};
//
//		//--------------------------------------------------------------------------------------
//		// Global Variables
//		//--------------------------------------------------------------------------------------
//		HINSTANCE					gHInstance = nullptr;
//		HWND						gHWindow = nullptr;
//		D3D_DRIVER_TYPE				gDriverType = D3D_DRIVER_TYPE_NULL;
//		D3D_FEATURE_LEVEL			gFeatureLevel = D3D_FEATURE_LEVEL_11_0;
//		ID3D11Device*				gD3dDevice = nullptr;
//		ID3D11Device1*				gD3dDevice1 = nullptr;
//		ID3D11DeviceContext*		gImmediateContext = nullptr;
//		ID3D11DeviceContext1*		gImmediateContext1 = nullptr;
//		IDXGISwapChain*				gSwapChain = nullptr;
//		IDXGISwapChain1*			gSwapChain1 = nullptr;
//		ID3D11RenderTargetView*		gRenderTargetView = nullptr;
//		ID3D11Texture2D*			gDepthStencil = nullptr;
//		ID3D11DepthStencilView*		gDepthStencilView = nullptr;
//		ID3D11VertexShader*			gVertexShader = nullptr;
//		ID3D11PixelShader*			gPixelShader = nullptr;
//		ID3D11InputLayout*			gVertexLayout = nullptr;
//		ID3D11Buffer*				gVertexBuffer = nullptr;
//		ID3D11Buffer*				gIndexBuffer = nullptr;
//		ID3D11Buffer*				gConstantBufferNeverChanges = nullptr;
//		ID3D11Buffer*				gConstantBufferChangeOnResize = nullptr;
//		ID3D11Buffer*				gConstantBufferChangesEveryFrame = nullptr;
//		ID3D11ShaderResourceView*	gTextureRv = nullptr;
//		ID3D11SamplerState*			gSamplerLinear = nullptr;
//		DirectX::XMMATRIX			gWorld;
//		DirectX::XMMATRIX			gView;
//		DirectX::XMMATRIX			gProjection;
//		DirectX::XMFLOAT4			gvMeshColor(0.7f, 0.7f, 0.7f, 1.0f);
//		// �ؽ�ó ������� �����Ƿ� shader resource view�� ������� ����
//
//		//--------------------------------------------------------------------------------------
//		// Forward declarations
//		//--------------------------------------------------------------------------------------
//		void CleanupDevice();
//		HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
//		void Destroy();
//		HRESULT Init(HINSTANCE hInstance, int nCmdShow, LONG width, LONG height, LPCWSTR className, LPCWSTR windowName);
//		HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, LONG width, LONG height, LPCWSTR className, LPCWSTR windowName);
//		HRESULT InitDevice();
//		void Render();
//		LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//
//		//--------------------------------------------------------------------------------------
//		// Clean up the objects we've created
//		//--------------------------------------------------------------------------------------
//		void CleanupDevice()
//		{
//			if (gImmediateContext)
//			{
//				gImmediateContext->ClearState();
//			}
//
//			if (gSamplerLinear)
//			{
//				gSamplerLinear->Release();
//			}
//			if (gTextureRv)
//			{
//				gTextureRv->Release();
//			}
//			if (gConstantBufferNeverChanges)
//			{
//				gConstantBufferNeverChanges->Release();
//			}
//			if (gConstantBufferChangeOnResize)
//			{
//				gConstantBufferChangeOnResize->Release();
//			}
//			if (gConstantBufferChangesEveryFrame)
//			{
//				gConstantBufferChangesEveryFrame->Release();
//			}
//			if (gVertexBuffer)
//			{
//				gVertexBuffer->Release();
//			}
//			if (gIndexBuffer)
//			{
//				gIndexBuffer->Release();
//			}
//			if (gVertexLayout)
//			{
//				gVertexLayout->Release();
//			}
//			if (gVertexShader)
//			{
//				gVertexShader->Release();
//			}
//			if (gPixelShader)
//			{
//				gPixelShader->Release();
//			}
//			if (gDepthStencil)
//			{
//				gDepthStencil->Release();
//			}
//			if (gDepthStencilView)
//			{
//				gDepthStencilView->Release();
//			}
//			if (gRenderTargetView)
//			{
//				gRenderTargetView->Release();
//			}
//			if (gSwapChain1)
//			{
//				gSwapChain1->Release();
//			}
//			if (gSwapChain)
//			{
//				gSwapChain->Release();
//			}
//			if (gImmediateContext1)
//			{
//				gImmediateContext1->Release();
//			}
//			if (gImmediateContext)
//			{
//				gImmediateContext->Release();
//			}
//			if (gD3dDevice1)
//			{
//				gD3dDevice1->Release();
//			}
//			if (gD3dDevice)
//			{
//				gD3dDevice->Release();
//			}
//		}
//
//		//--------------------------------------------------------------------------------------
//		// Helper for compiling shaders with D3DCompile
//		//
//		// With VS 11, we could load up prebuilt .cso files instead...
//		//--------------------------------------------------------------------------------------
//		HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
//		{
//			// szFileName ���� �̸�
//			// szEntryPoint �� ������ � �Լ� �������ҰŴ�
//			// szShaderModel ���̴� ��
//			HRESULT hResult = S_OK;
//
//			// ������ �ɼ�
//			DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
//#ifdef _DEBUG
//			// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
//			// Setting this flag improves the shader debugging experience, but still allows 
//			// the shaders to be optimized and to run exactly the way they will run in 
//			// the release configuration of this program.
//			dwShaderFlags |= D3DCOMPILE_DEBUG;
//			// �̰� ���� ������. ���̴� ������� �� ���� ��. �����ϸ� �ϱ� ������ ���� �������� �������� ����� ����
//
//			// Disable optimizations to further improve shader debugging
//			dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
//#endif
//
//			// ID3DBlob �ؽ�Ʈ ������ ���𰡸� ������ ��. ���̴� ����� �� ���� �ֳ�...?
//			// �̸� ���̴� ������ �صΰ� ��Ÿ�ӿ� ���̴� ���̳ʸ��� �ٷ� Blob�� �������� ������ ���� ����� �� ����
//			// ��κ��� ��� ���̴��� �ɼǿ� ���� ������ �ٸ��� �ؾ��� ���� ����
//			// �̷� �� ifdef�� ������ ��ÿ� �־��༭ �ٸ��� ���� ����
//			ID3DBlob* pErrorBlob = nullptr;
//
//			// GLUTó�� D3DX��� ���� ���̺귯���� ����. 12���� �����
//			// MS�� ��� ���� 11���� D3DX ���� ����
//			// d3dx���� prod �������� ���־� 12 ������ �� ����
//			// ���� �ι�° �Ű������� PDefines�ε� ���⿡ ifdef�� �ش��ϴ� �� �� �־���� �� ����
//			// ���̴� ������ ���Ƶ� ������ �� def�� ���� �ٸ� ���̳ʸ� �� ����
//			// �Ź� ������ �ٽ��ϸ� �������ϱ� ���̴� ĳ�� ���
//			// �� ������ �� ���̴� ������ ���� ������, ���� ���̴� ĳ�ö� ���ؼ�, 
//			// ������ / ���빰 �ٲ������ �������ؼ� ���̳ʸ��� ĳ�� �ʿ� ����
//			// ���̴� ĳ�� ���̳ʸ��κ��� ���̴� ����
//			// ���� ���� ������ �׳� ĳ�ÿ��� �ٷ� �о ����
//			hResult = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
//				dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
//			if (FAILED(hResult))
//			{
//				if (pErrorBlob)
//				{
//					OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
//					pErrorBlob->Release();
//				}
//				return hResult;
//			}
//			if (pErrorBlob)
//			{
//				pErrorBlob->Release();
//			}
//
//			return S_OK;
//		}
//
//		//--------------------------------------------------------------------------------------
//		// Destroy Renderer
//		//--------------------------------------------------------------------------------------
//		export void Destroy()
//		{
//			CleanupDevice();
//		}
//
//		//--------------------------------------------------------------------------------------
//		// Initialize Renderer
//		//--------------------------------------------------------------------------------------
//		export HRESULT Init(HINSTANCE hInstance, int nCmdShow, LONG width, LONG height, LPCWSTR className, LPCWSTR windowName)
//		{
//			HRESULT hResult = FAILED(InitWindow(hInstance, nCmdShow, width, height, className, windowName));
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			hResult = InitDevice();
//			if (FAILED(hResult))
//			{
//				Destroy();
//				return hResult;
//			}
//
//			return hResult;
//		}
//
//		//--------------------------------------------------------------------------------------
//		// Create Direct3D device and swap chain
//		//--------------------------------------------------------------------------------------
//		HRESULT InitDevice()
//		{
//			HRESULT hResult = S_OK;
//
//			RECT rect;    // ȭ�� ũ��
//			GetClientRect(gHWindow, &rect);
//			UINT width = rect.right - rect.left;
//			UINT height = rect.bottom - rect.top;
//
//			UINT createDeviceFlags = 0;
//#ifdef _DEBUG
//			createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
//#endif
//
//			D3D_DRIVER_TYPE driverTypes[] = {
//				D3D_DRIVER_TYPE_HARDWARE,   // GPU��
//				D3D_DRIVER_TYPE_WARP,       // CPU��
//				D3D_DRIVER_TYPE_REFERENCE,  // ��Ʈ�� GPU ������ ����
//			};
//			UINT numDriverTypes = ARRAYSIZE(driverTypes);
//
//			D3D_FEATURE_LEVEL featureLevels[] =
//			{
//				D3D_FEATURE_LEVEL_11_1,
//				D3D_FEATURE_LEVEL_11_0,
//				D3D_FEATURE_LEVEL_10_1,
//				D3D_FEATURE_LEVEL_10_0, // �� �־ �Ǳ� �ϴµ�, �ֿ켱���� ���ϴ� �� ������ �Ǿ��ִ� ��. �ǳ� ���δ� GPU�� ����
//			};
//			UINT numFeatureLevels = ARRAYSIZE(featureLevels);
//
//			for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
//			{
//				gDriverType = driverTypes[driverTypeIndex];
//				hResult = D3D11CreateDevice(nullptr, gDriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
//					D3D11_SDK_VERSION, &gD3dDevice, &gFeatureLevel, &gImmediateContext);
//
//				if (hResult == E_INVALIDARG)
//				{
//					// DirectX 11.0 platforg will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
//					hResult = D3D11CreateDevice(nullptr, gDriverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
//						D3D11_SDK_VERSION, &gD3dDevice, &gFeatureLevel, &gImmediateContext);
//					// ������ featureLevel�� gFeatureLevel�� ��������
//				}
//
//				if (SUCCEEDED(hResult))
//				{
//					break;
//				}
//			}
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
//			IDXGIFactory1* dxgiFactory = nullptr;
//			{
//				IDXGIDevice* dxgiDevice = nullptr;
//				hResult = gD3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
//				if (SUCCEEDED(hResult))
//				{
//					IDXGIAdapter* adapter = nullptr;
//					hResult = dxgiDevice->GetAdapter(&adapter);
//					if (SUCCEEDED(hResult))
//					{
//						hResult = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
//						adapter->Release();
//					}
//					dxgiDevice->Release();
//				}
//			}
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			// Create swap chain
//			IDXGIFactory2* dxgiFactory2 = nullptr;
//			hResult = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
//			if (dxgiFactory2)
//			{
//				// DirectX 11.1 or later
//				hResult = gD3dDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&gD3dDevice1));
//				if (SUCCEEDED(hResult))
//				{
//					static_cast<void>(gImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&gImmediateContext1)));
//				}
//
//				DXGI_SWAP_CHAIN_DESC1 sd = {};
//				sd.Width = width;
//				sd.Height = height;
//				sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//				sd.SampleDesc.Count = 1;
//				sd.SampleDesc.Quality = 0;
//				sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//				sd.BufferCount = 1;
//
//				hResult = dxgiFactory2->CreateSwapChainForHwnd(gD3dDevice, gHWindow, &sd, nullptr, nullptr, &gSwapChain1);
//				if (SUCCEEDED(hResult))
//				{
//					hResult = gSwapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&gSwapChain));
//				}
//
//				dxgiFactory2->Release();
//			}
//			else
//			{
//				// DirectX 11.0 systeg
//				DXGI_SWAP_CHAIN_DESC sd = {};   // w buffering. flip / bullet
//												// flip: front buffer�� back buffer�� ���������� �ٲ�
//												// bullet: back buffer�� front buffer�� ����
//				sd.BufferCount = 1; // �̰ŷ� ���� ���۸� / Ʈ���� ���۸� ���� ����
//				sd.BufferDesc.Width = width;
//				sd.BufferDesc.Height = height;
//				sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // UNORM -> 0.0 ~ 1.0
//				sd.BufferDesc.RefreshRate.Numerator = 60;   // 60 fps
//				sd.BufferDesc.RefreshRate.Denominator = 1;
//				sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//				sd.OutputWindow = gHWindow;
//				sd.SampleDesc.Count = 1;
//				sd.SampleDesc.Quality = 0;
//				sd.Windowed = TRUE; // window ����?
//
//				hResult = dxgiFactory->CreateSwapChain(gD3dDevice, &sd, &gSwapChain);
//			}
//
//			// Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
//			dxgiFactory->MakeWindowAssociation(gHWindow, DXGI_MWA_NO_ALT_ENTER);
//
//			dxgiFactory->Release();
//
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			// Create a render target view
//			// view��� ���� ���� ���ҽ��� ��� �����ϰ�, �� ���ҽ��� ����ϱ� ���� �Ļ� �������̽�. ������ read-only
//			// shader resource view�� shader �ȿ��� ����� resource�ε�, �� �ٿ��� �ؽ�ó. �̰� �� ���� / ���� ���� ����
//			// �� �� shader resource view�� �ƴ�
//			// �ؽ�ó�� �о ����Ϸ���, �ش� �ؽ�ó�� ����Ű�� �����͸� ���� �������̽��� �����ؼ� �����ֱ� (shader resource view)
//			// ȭ�� ���۵� �ؽ�ó ���ҽ�. ���⿡ write�� �ҰŸ� render target view�� �Ǿ����
//			ID3D11Texture2D* pBackBuffer = nullptr;
//			hResult = gSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
//			// swap chain�� ���� �ִ� �� ���� �����
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			// ID3D11Device         ��ü
//				// ���� / �����ϴ� ���
//			// ID3D11DeviceContext  �帧
//				// �׸��� / ���� �ٲٱ�. ��ü���� ���� ����
//				// ���� ���¿��� �ؽ�ó ����, �����, ȭ�� Ŭ���� ���̶�� �� ���� "���� ����"�� context
//				// opengl�� �Ϲ������� ���� �������ϰ� ���� ���´� �ϳ���� �����ϰ� �������� ȣ��
//				// 12���ʹ� ��Ƽ ������ ������ �����ؼ� ��������� context ����. context ���� ���� �� �� �ִ�
//				// ���� 12��� �ؼ� ���� context�� ���� �� ��������� ����. ���� ���� �ִµ� �� �� �ϳ��� �ַ� ����ϴ� ��.
//					// �װ� immediate context
//			// ID3D11RenderTargetView ȭ�鿡 write �Ǵ� ����
//				// ���̴��� ���� ȭ�鿡 �׸���, ��������� ȭ�� Ŭ������ �� ���
//			hResult = gD3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &gRenderTargetView);
//			pBackBuffer->Release(); // �̰� �� ������?
//									// gRenderTargetView�� pBackBuffer�� �����ؼ� ref count�� 1 �����ع����� ����
//									// ���� pBackBuffer �� �� �����״ϱ�...
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			// Create depth stencil texture
//			D3D11_TEXTURE2D_DESC descDepth = {};
//			descDepth.Width = width;
//			descDepth.Height = height;
//			descDepth.MipLevels = 1;
//			descDepth.ArraySize = 1;
//			descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
//			descDepth.SampleDesc.Count = 1;
//			descDepth.SampleDesc.Quality = 0;
//			descDepth.Usage = D3D11_USAGE_DEFAULT;
//			descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
//			descDepth.CPUAccessFlags = 0;
//			descDepth.MiscFlags = 0;
//			hResult = gD3dDevice->CreateTexture2D(&descDepth, nullptr, &gDepthStencil);
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			// Create the depth stencil view
//			D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
//			descDSV.Format = descDepth.Format;
//			descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
//			descDSV.Texture2D.MipSlice = 0;
//			hResult = gD3dDevice->CreateDepthStencilView(gDepthStencil, &descDSV, &gDepthStencilView);
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			// ���� target ���� ����. ������ 8 ����� ����
//			// ������ parameter�� depth buffer.
//			// �տ� OM �پ��ִٴ� �� Output Manager. ���ۿ� ���� ���ϰ� �ϴ� ���� ���ξ OM���� �Ǿ�����
//			// �츮�� �׸� buffer ����
//			gImmediateContext->OMSetRenderTargets(1, &gRenderTargetView, gDepthStencilView);
//
//			// gRenderTargetView�� ���� �� �������� �׸� ����?
//			// viewport�� 3ds max ����ٰ� �����ϸ� ȭ�� 4�����ؼ�
//			// ���� �������ϸ� ���� �ϳ��� viewport�� ���� 4������ ����ŭ �־ 
//			// �������� �� ���� RSSetViewports���ָ� ��
//			// Setup the viewport
//			D3D11_VIEWPORT vp;
//			vp.Width = static_cast<FLOAT>(width);
//			vp.Height = static_cast<FLOAT>(height);
//			vp.MinDepth = 0.0f;
//			vp.MaxDepth = 1.0f;
//			vp.TopLeftX = 0;
//			vp.TopLeftY = 0;
//			// Rasterizer Stage
//			gImmediateContext->RSSetViewports(1, &vp);
//
//			// ȭ���� �׸� ���ۿ� ���� ���� ���� �Ϸ�
//
//			// ���̴� ������
//			// 9 -> 10 �Ѿ �� iPhone ��õǸ鼭 ����� ȯ���� �������鼭 9 -> 11�� �ȳѾ
//			// �� ������ shader. DX9������ ���̴��� �ɼ��̾��µ� ���Ŀ� ���̴��� �ʼ��� ��
//			// ���������� fvf�� �����ؼ� ���� ���������� ��� (���̴� �� ����)
//			// 9.3.9.0c ������ GPU�� �������� ���̴� ��ĥ ����
//			// ���� ���������� ������. ���̴� �ϳ��� ������ ������ �ȵ�
//			// Compile the vertex shader
//			ID3DBlob* pVSBlob = nullptr;
//			// shader ���� vs 4.0�̱���~
//			// 4.0�� ��� 10 �����̰� 11�� 5.0�����ε� ������ �� ȣȯ ��
//			// �����̴ϱ� directx device�� ��� �ִ� �� �ƴϰڱ���~
//			// �̰� �� ���� �Լ���
//			hResult = CompileShaderFromFile(L"Graphics/Shader/DirectXTest.fxh", "VS", "vs_4_0", &pVSBlob);
//			if (FAILED(hResult))
//			{
//				MessageBox(nullptr,
//					L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
//				return hResult;
//			}
//
//			// Create the vertex shader
//			// ������ ��ü����. Blob���� get�ϱ�
//			// ���� ���� ���� ���� ���� ���� Compile Shader���� �ɸ�
//			// ���̴� �ڵ尡 �����ѵ� ����ī�尡 feature level�� 10.0 ���� �����ϴµ�
//			// ���̴� ��带 5.0�� ¥�� �����ϸ� �ǰ� ���̳ʸ��� ���̴� ������ �ȵ�
//
//			// ������ �Լ��� �����ߴ��� ���� ������ watch���� @err, hr�ϸ� ���� �����忡�� ������ �Լ��� ���� ������ �� �� �� ����
//			hResult = gD3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &gVertexShader);
//			if (FAILED(hResult))
//			{
//				pVSBlob->Release();
//				return hResult;
//			}
//
//			// layout�� GPU�� ������ ���ؽ��� � Ÿ������, ������Ұ� ��� �Ǵ��� �˷��ִ� ��
//			// DirectXTest.fxh �ڵ� �����غ���
//			// Vulkan�̳� Metal, DX11 �̻��� struct�� ��.
//			// �� ����ó�� simple�� Shader�� ��� 16byte ¥�� float ���� �ϳ���
//			// hlsl / glsl ���� ū �κ��� �տ� struct �����ϴ� �κ�
//			// glsl�� uniform���� string���� �̸� ����
//			// hlsl�� ����ü ������ �ۼ�
//			// "POSITION"�� �׳� D3D Semantic��
//			// 32bit RGB Float. �Է� ���� ��ü�� ������ float4. 16 byte ���ĵǾ��־��
//			// layout�� ���� ���� ������. position ��ǥ, �ؽ�ó ��ǥ �� �����ؼ�
//			// layout�� �������� ���� �ٸ��� ���� ���� ���� ����
//			// Define the input layout
//			D3D11_INPUT_ELEMENT_DESC layout[] =
//			{
//				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			};
//			UINT numElements = ARRAYSIZE(layout);
//
//			// gVertexLayout. ID3D11InputLayout ��ü. COM ��ü��.
//			// Create the input layout
//			hResult = gD3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
//				pVSBlob->GetBufferSize(), &gVertexLayout);
//			pVSBlob->Release();
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			// IA. Input Assembly
//			// Set the input layout
//			gImmediateContext->IASetInputLayout(gVertexLayout);
//
//			// Compile the pixel shader
//			ID3DBlob* pPSBlob = nullptr;
//			hResult = CompileShaderFromFile(L"Graphics/Shader/DirectXTest.fxh", "PS", "ps_4_0", &pPSBlob);
//			if (FAILED(hResult))
//			{
//				MessageBox(nullptr,
//					L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
//				return hResult;
//			}
//
//			// Create the pixel shader
//			hResult = gD3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &gPixelShader);
//			pPSBlob->Release();
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			// XMFLOAT3 32bit
//			// LHS. x ����(�ʺ�) y ����(����) z ����
//			// �� ���������� ȭ�� ���ۿ��� �ٷ� �� �� �ְ� x, y�� -1.0 ~ 1.0, z�� 0.0 ~ 1.0���� �־��ִ� ��
//			// Matrix ��ȯ �ϳ��� ����.
//			// Create vertex buffer
//			SimpleVertex vertices[] = {
//				{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
//				{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
//				{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
//				{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
//
//				{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
//				{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
//				{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
//				{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
//
//				{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
//				{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
//				{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
//				{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
//
//				{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
//				{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
//				{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
//				{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
//
//				{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
//				{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
//				{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
//				{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
//
//				{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
//				{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
//				{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
//				{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
//			};
//			D3D11_BUFFER_DESC bd = {};
//			// IMMUTABLE: ������ ��� �� ���ۿ� ���� �����ͷ� ������ ���� ���� �ǵ帮�� �ʱ�
//			// DYNAMIC: �� ������ �� �ɾ ���. ������ DEFAULT ���� ���. �ִ��� GPU �޸� �ȿ� ���ҽ� ��ġ. DYNAMIC ���� 
//			// �� ������ ���� �� �� �ִٴ� ��. �ý��� �޸𸮿� ���� GPU �޸𸮿� ���������� �����ϴ� ����
//			// STAGING�� GPU �޸� �ƴ�. ���� GPU�� ���� ����. DX ���ҽ� �ٷ�� ������� copy�� �� ȣȯ�� ������ ��
//				// GPU �޸� �ȿ� � ���� �˰� ������ ȭ�� ������ �����͸� staging���� copy�ؼ� �о����.
//				// GPU �޸𸮸� �ٷ� �� ����
//			bd.Usage = D3D11_USAGE_DEFAULT;
//			bd.ByteWidth = sizeof(SimpleVertex) * 24;
//			// ���� �޸� ����
//			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//			bd.CPUAccessFlags = 0;
//
//			// �ؽ�ó
//			D3D11_SUBRESOURCE_DATA InitData = {};
//			InitData.pSysMem = vertices;
//			hResult = gD3dDevice->CreateBuffer(&bd, &InitData, &gVertexBuffer);
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			// ���� context�� �����ֱ�
//			// Set vertex buffer
//			UINT stride = sizeof(SimpleVertex);
//			UINT offset = 0;
//			gImmediateContext->IASetVertexBuffers(0, 1, &gVertexBuffer, &stride, &offset);
//
//			// Create index buffer
//			WORD indices[] = {
//				3,1,0,
//				2,1,3,
//
//				6,4,5,
//				7,4,6,
//
//				11,9,8,
//				10,9,11,
//
//				14,12,13,
//				15,12,14,
//
//				19,17,16,
//				18,17,19,
//
//				22,20,21,
//				23,20,22
//			};
//			bd.Usage = D3D11_USAGE_DEFAULT;
//			bd.ByteWidth = sizeof(WORD) * 36;        // 36 vertices needed for 12 triangles in a triangle list
//			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//			bd.CPUAccessFlags = 0;
//			InitData.pSysMem = indices;
//			hResult = gD3dDevice->CreateBuffer(&bd, &InitData, &gIndexBuffer);
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			// Set index buffer
//			gImmediateContext->IASetIndexBuffer(gIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
//
//
//			// Set primitive topology
//			gImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//			// Create the constant buffer
//			bd.Usage = D3D11_USAGE_DEFAULT;
//			bd.ByteWidth = sizeof(ConstantBufferNeverChanges);
//			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//			bd.CPUAccessFlags = 0;
//			hResult = gD3dDevice->CreateBuffer(&bd, nullptr, &gConstantBufferNeverChanges);
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			bd.ByteWidth = sizeof(ConstantBufferChangeOnResize);
//			hResult = gD3dDevice->CreateBuffer(&bd, nullptr, &gConstantBufferChangeOnResize);
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			bd.ByteWidth = sizeof(ConstantBufferChangesEveryFrame);
//			hResult = gD3dDevice->CreateBuffer(&bd, nullptr, &gConstantBufferChangesEveryFrame);
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			// Load the Texture
//			hResult = cave::DdsTextureLoader::CreateDDSTextureFromFile(gD3dDevice, L"Graphics/Resource/seafloor.dds", nullptr, &gTextureRv);
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			// Create the sample state
//			D3D11_SAMPLER_DESC sampDesc = {};
//			sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
//			sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
//			sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
//			sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
//			sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
//			sampDesc.MinLOD = 0;
//			sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
//			hResult = gD3dDevice->CreateSamplerState(&sampDesc, &gSamplerLinear);
//			if (FAILED(hResult))
//			{
//				return hResult;
//			}
//
//			// Initialize the world matrix
//			gWorld = DirectX::XMMatrixIdentity();
//
//			// Initialize the view matrix
//			DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.0f, 0.0f, -6.0f, 0.0f);
//			DirectX::XMVECTOR at = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//			DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//			gView = DirectX::XMMatrixLookAtLH(eye, at, up);
//
//			ConstantBufferNeverChanges constantBufferNeverChanges;
//			constantBufferNeverChanges.mView = DirectX::XMMatrixTranspose(gView);
//			gImmediateContext->UpdateSubresource(gConstantBufferNeverChanges, 0, nullptr, &constantBufferNeverChanges, 0, 0);
//
//			// Initialize the projection matrix
//			gProjection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, width / static_cast<FLOAT>(height), 0.01f, 100.0f);
//
//			ConstantBufferChangeOnResize constantBufferChangesOnResize;
//			constantBufferChangesOnResize.mProjection = DirectX::XMMatrixTranspose(gProjection);
//			gImmediateContext->UpdateSubresource(gConstantBufferChangeOnResize, 0, nullptr, &constantBufferChangesOnResize, 0, 0);
//
//			return S_OK;
//		}
//
//		//--------------------------------------------------------------------------------------
//		// Register class and create window
//		//--------------------------------------------------------------------------------------
//		HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, LONG width, LONG height, LPCWSTR className, LPCWSTR windowName)
//		{
//			// Register class
//			WNDCLASSEX windowClassEx;
//			windowClassEx.cbSize = sizeof(WNDCLASSEX);
//			windowClassEx.style = CS_HREDRAW | CS_VREDRAW;
//			windowClassEx.lpfnWndProc = WndProc;
//			windowClassEx.cbClsExtra = 0;
//			windowClassEx.cbWndExtra = 0;
//			windowClassEx.hInstance = hInstance;
//			windowClassEx.hIcon = LoadIcon(hInstance, reinterpret_cast<LPCTSTR>(IDI_TUTORIAL1));
//			windowClassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
//			windowClassEx.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
//			windowClassEx.lpszMenuName = nullptr;
//			windowClassEx.lpszClassName = className;
//			windowClassEx.hIconSm = LoadIcon(windowClassEx.hInstance, reinterpret_cast<LPCTSTR>(IDI_TUTORIAL1));
//			if (!RegisterClassEx(&windowClassEx))
//			{
//				return E_FAIL;
//			}
//
//			// Create window
//			gHInstance = hInstance;
//			RECT rect = {0, 0, width, height};
//			AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
//			gHWindow = CreateWindow(className, windowName,
//				WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
//				CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance,
//				nullptr);
//			if (!gHWindow)
//			{
//				return E_FAIL;
//			}
//
//			ShowWindow(gHWindow, nCmdShow);
//
//			return S_OK;
//		}
//
//		//--------------------------------------------------------------------------------------
//		// Render a frame
//		//--------------------------------------------------------------------------------------
//		export void Render()
//		{
//			// Update our time
//			static float t = 0.0f;
//			if (gDriverType == D3D_DRIVER_TYPE_REFERENCE)
//			{
//				t += static_cast<float>(DirectX::XM_PI) * 0.0125f;
//			}
//			else
//			{
//				static ULONGLONG timeStart = 0;
//				ULONGLONG timeCur = GetTickCount64();
//				if (timeStart == 0)
//				{
//					timeStart = timeCur;
//				}
//				t = (timeCur - timeStart) / 1000.0f;
//			}
//
//			// 1st Cube : Rotate around the origin
//			gWorld = DirectX::XMMatrixRotationY(t);
//
//			// Modify the color
//			gvMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
//			gvMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
//			gvMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;
//
//			// ���� layout ����, topology �ٲٴ°�, vertex buffer �ٲٴ°� rendering �Լ� �ȿ� ���� ��찡 ����
//			// vertex buffer�� pixel shader �� ���� �ʼ�
//			// Clear the back buffer 
//			gImmediateContext->ClearRenderTargetView(gRenderTargetView, DirectX::Colors::MidnightBlue);
//
//			//
//			// Clear the depth buffer to 1.0 (max depth)
//			//
//			gImmediateContext->ClearDepthStencilView(gDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
//
//			//
//			// Update variables for the first cube
//			//
//			ConstantBufferChangesEveryFrame constantBuffer;
//			constantBuffer.mWorld = DirectX::XMMatrixTranspose(gWorld);
//			constantBuffer.mvMeshColor = gvMeshColor;
//			gImmediateContext->UpdateSubresource(gConstantBufferChangesEveryFrame, 0, nullptr, &constantBuffer, 0, 0);
//
//			//
//			// Render the first cube
//			//
//			gImmediateContext->VSSetShader(gVertexShader, nullptr, 0);
//			gImmediateContext->VSSetConstantBuffers(0, 1, &gConstantBufferNeverChanges);
//			gImmediateContext->VSSetConstantBuffers(1, 1, &gConstantBufferChangeOnResize);
//			gImmediateContext->VSSetConstantBuffers(2, 1, &gConstantBufferChangesEveryFrame);
//			gImmediateContext->PSSetShader(gPixelShader, nullptr, 0);
//			gImmediateContext->PSSetConstantBuffers(2, 1, &gConstantBufferChangesEveryFrame);
//			gImmediateContext->PSSetShaderResources(0, 1, &gTextureRv);
//			gImmediateContext->PSSetSamplers(0, 1, &gSamplerLinear);
//			// ���� production level���� Draw���ٴ� DrawIndexed�� �� ���� ���
//			// ù��°�� ���ؽ� ����. 3
//			// back buffer�� �׸���
//			//gImmediateContext->Draw(3, 0);
//			gImmediateContext->DrawIndexed(36, 0, 0);        // 36 vertices needed for 12 triangles in a triangle list
//
//			// ���� flip�̳� swap ���ؼ� front buffer�� ����
//			// front buffer�� ������
//			// ���� �׷����� ������ GPU Driver���� �ٸ�. ������ ���������� �񵿱�� �Ͼ
//			// Present the information rendered to the back buffer to the front buffer (the screen)
//			gSwapChain->Present(0, 0);
//		}
//
//		//--------------------------------------------------------------------------------------
//		// Called every time the application receives a message
//		//--------------------------------------------------------------------------------------
//		LRESULT CALLBACK WndProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam)
//		{
//			PAINTSTRUCT paintStruct;
//			HDC handleDeviceContext;
//
//			switch (message)
//			{
//			case WM_PAINT:
//				handleDeviceContext = BeginPaint(hWindow, &paintStruct);
//				EndPaint(hWindow, &paintStruct);
//				break;
//
//			case WM_DESTROY:
//				PostQuitMessage(0);
//				break;
//
//				// Note that this tutorial does not handle resizing (WM_SIZE) requests,
//				// so we created the window without the resize border.
//
//			default:
//				return DefWindowProc(hWindow, message, wParam, lParam);
//			}
//
//			return 0;
//		}
//	}
//}