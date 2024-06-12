#ifndef __DIRECTX_H__
#define __DIRECTX_H__

#include <d3d11.h>
#include "TextureClass.h"

#pragma comment(lib, "d3d11.lib")

ID3D11Device* GetDevice();
ID3D11DeviceContext* GetContext();
IDXGISwapChain* GetSwapChain();

HRESULT InitDX(HWND hWnd, UINT width, UINT height, bool fullscreen);
void UninitDX();
void BeginDrawDX();
void EndDrawDX();

void SetRenderTargets(UINT num, RenderTarget** ppViews, DepthStencil* pView);
void SetCullingMode(D3D11_CULL_MODE cull);
void SetDefaultRenderTargets();



void EnableDepth(bool enable);

#endif // __DIRECTX_H__