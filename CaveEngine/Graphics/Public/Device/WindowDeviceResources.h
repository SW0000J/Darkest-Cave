/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"
#include "GraphicsApiPch.h"
#include "Device/GenericDeviceResources.h"

#ifdef __WIN32__
namespace cave
{
	class WindowDeviceResources final : public GenericDeviceResources
	{
	public:
		WindowDeviceResources() = default;
		constexpr WindowDeviceResources(const WindowDeviceResources&) = delete;
		WindowDeviceResources& operator=(const WindowDeviceResources&) = delete;
		virtual ~WindowDeviceResources();

		int32_t CreateWindowResources(HWND window) override;
		int32_t CreateDeviceResources() override;
		void Destroy() override;

		int32_t ConfigureBackBuffer() override;
		int32_t ReleaseBackBuffer() override;
		int32_t GoFullScreen() override;
		int32_t GoWindowed() override;

		float GetAspectRatio() override;

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();
		ID3D11RenderTargetView* GetRenderTarget();
		ID3D11DepthStencilView* GetDepthStencil();
		D3D_DRIVER_TYPE GetDriverType() const;

		void Present() override;
	private:
		HINSTANCE	mInstance = nullptr;

		//-----------------------------------------------------------------------------
		// Direct3D device
		//-----------------------------------------------------------------------------
		ID3D11Device*        	mD3dDevice = nullptr;
		ID3D11Device1*       	mD3dDevice1 = nullptr;
		ID3D11DeviceContext*	mImmediateContext = nullptr; // immediate context
		ID3D11DeviceContext1*	mImmediateContext1 = nullptr;
		IDXGISwapChain*      	mSwapChain = nullptr;
		IDXGISwapChain1*      	mSwapChain1 = nullptr;


		//-----------------------------------------------------------------------------
		// DXGI swap chain device resources
		//-----------------------------------------------------------------------------
		ID3D11Texture2D*        mBackBuffer = nullptr;
		ID3D11RenderTargetView* mRenderTargetView = nullptr;


		//-----------------------------------------------------------------------------
		// Direct3D device resources for the depth stencil
		//-----------------------------------------------------------------------------
		ID3D11Texture2D*         mDepthStencil = nullptr;
		ID3D11DepthStencilView*  mDepthStencilView = nullptr;


		//-----------------------------------------------------------------------------
		// Direct3D device metadata and device resource metadata
		//-----------------------------------------------------------------------------
		D3D_FEATURE_LEVEL       mFeatureLevel = D3D_FEATURE_LEVEL_11_0;
		D3D11_TEXTURE2D_DESC    mBackBufferDesc;
		D3D11_VIEWPORT          mViewport;
		D3D_DRIVER_TYPE			mDriverType = D3D_DRIVER_TYPE_NULL;
	};

	typedef WindowDeviceResources DeviceResources;
}
#endif