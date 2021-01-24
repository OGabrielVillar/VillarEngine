/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.cpp																		  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Graphics.h"
#include "DXErr.h"
#include "ChiliException.h"
#include <assert.h>
#include <string>
#include <array>

// Ignore the intellisense error "cannot open source file" for .shh files.
// They will be created during the build sequence before the preprocessor runs.
namespace FramebufferShaders
{
#include "FramebufferPS.shh"
#include "FramebufferVS.shh"
}

#pragma comment( lib,"d3d11.lib" )

#define CHILI_GFX_EXCEPTION( hr,note ) Graphics::Exception( hr,note,_CRT_WIDE(__FILE__),__LINE__ )

using Microsoft::WRL::ComPtr;

Graphics::Graphics( HWNDKey& key )
{
	assert( key.hWnd != nullptr );

	//////////////////////////////////////////////////////
	// create device and swap chain/get render target view
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = Graphics::ScreenWidth;
	sd.BufferDesc.Height = Graphics::ScreenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferDesc.RefreshRate.Denominator = 60;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = key.hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	HRESULT				hr;
	UINT				createFlags = 0u;
#ifdef CHILI_USE_D3D_DEBUG_LAYER
#ifdef _DEBUG
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
#endif
	
	// create device and front/back buffers
	if( FAILED( hr = D3D11CreateDeviceAndSwapChain( 
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pImmediateContext ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating device and swap chain" );
	}

	// get handle to backbuffer
	ComPtr<ID3D11Resource> pBackBuffer;
	if( FAILED( hr = pSwapChain->GetBuffer(
		0,
		__uuidof( ID3D11Texture2D ),
		(LPVOID*)&pBackBuffer ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Getting back buffer" );
	}

	// create a view on backbuffer that we can render to
	if( FAILED( hr = pDevice->CreateRenderTargetView( 
		pBackBuffer.Get(),
		nullptr,
		&pRenderTargetView ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating render target view on backbuffer" );
	}


	// set backbuffer as the render target using created view
	pImmediateContext->OMSetRenderTargets( 1,pRenderTargetView.GetAddressOf(),nullptr );


	// set viewport dimensions
	D3D11_VIEWPORT vp;
	vp.Width = float( Graphics::ScreenWidth );
	vp.Height = float( Graphics::ScreenHeight );
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pImmediateContext->RSSetViewports( 1,&vp );


	///////////////////////////////////////
	// create texture for cpu render target
	D3D11_TEXTURE2D_DESC sysTexDesc;
	sysTexDesc.Width = Graphics::ScreenWidth;
	sysTexDesc.Height = Graphics::ScreenHeight;
	sysTexDesc.MipLevels = 1;
	sysTexDesc.ArraySize = 1;
	sysTexDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sysTexDesc.SampleDesc.Count = 1;
	sysTexDesc.SampleDesc.Quality = 0;
	sysTexDesc.Usage = D3D11_USAGE_DYNAMIC;
	sysTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	sysTexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	sysTexDesc.MiscFlags = 0;
	// create the texture
	if( FAILED( hr = pDevice->CreateTexture2D( &sysTexDesc,nullptr,&pSysBufferTexture ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating sysbuffer texture" );
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = sysTexDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	// create the resource view on the texture
	if( FAILED( hr = pDevice->CreateShaderResourceView( pSysBufferTexture.Get(),
		&srvDesc,&pSysBufferTextureView ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating view on sysBuffer texture" );
	}


	////////////////////////////////////////////////
	// create pixel shader for framebuffer
	// Ignore the intellisense error "namespace has no member"
	if( FAILED( hr = pDevice->CreatePixelShader(
		FramebufferShaders::FramebufferPSBytecode,
		sizeof( FramebufferShaders::FramebufferPSBytecode ),
		nullptr,
		&pPixelShader ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating pixel shader" );
	}
	

	/////////////////////////////////////////////////
	// create vertex shader for framebuffer
	// Ignore the intellisense error "namespace has no member"
	if( FAILED( hr = pDevice->CreateVertexShader(
		FramebufferShaders::FramebufferVSBytecode,
		sizeof( FramebufferShaders::FramebufferVSBytecode ),
		nullptr,
		&pVertexShader ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating vertex shader" );
	}
	

	//////////////////////////////////////////////////////////////
	// create and fill vertex buffer with quad for rendering frame
	const FSQVertex vertices[] =
	{
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,1.0f,0.5f,1.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,-1.0f,0.5f,0.0f,1.0f },
	};
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( FSQVertex ) * 6;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0u;
	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;
	if( FAILED( hr = pDevice->CreateBuffer( &bd,&initData,&pVertexBuffer ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating vertex buffer" );
	}

	
	//////////////////////////////////////////
	// create input layout for fullscreen quad
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};

	// Ignore the intellisense error "namespace has no member"
	if( FAILED( hr = pDevice->CreateInputLayout( ied,2,
		FramebufferShaders::FramebufferVSBytecode,
		sizeof( FramebufferShaders::FramebufferVSBytecode ),
		&pInputLayout ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating input layout" );
	}


	////////////////////////////////////////////////////
	// Create sampler state for fullscreen textured quad
	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	if( FAILED( hr = pDevice->CreateSamplerState( &sampDesc,&pSamplerState ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Creating sampler state" );
	}

	// allocate memory for sysbuffer (16-byte aligned for faster access)
	pSysBuffer = reinterpret_cast<Color*>( 
		_aligned_malloc( sizeof( Color ) * Graphics::ScreenWidth * Graphics::ScreenHeight,16u ) );
}

Graphics::~Graphics()
{
	// free sysbuffer memory (aligned free)
	if( pSysBuffer )
	{
		_aligned_free( pSysBuffer );
		pSysBuffer = nullptr;
	}
	// clear the state of the device context before destruction
	if( pImmediateContext ) pImmediateContext->ClearState();
}

RectI Graphics::GetScreenRect()
{
	return{ 0,ScreenWidth,0,ScreenHeight };
}

void Graphics::EndFrame()
{
	HRESULT hr;

	// lock and map the adapter memory for copying over the sysbuffer
	if( FAILED( hr = pImmediateContext->Map( pSysBufferTexture.Get(),0u,
		D3D11_MAP_WRITE_DISCARD,0u,&mappedSysBufferTexture ) ) )
	{
		throw CHILI_GFX_EXCEPTION( hr,L"Mapping sysbuffer" );
	}
	// setup parameters for copy operation
	Color* pDst = reinterpret_cast<Color*>(mappedSysBufferTexture.pData );
	const size_t dstPitch = mappedSysBufferTexture.RowPitch / sizeof( Color );
	const size_t srcPitch = Graphics::ScreenWidth;
	const size_t rowBytes = srcPitch * sizeof( Color );
	// perform the copy line-by-line
	for( size_t y = 0u; y < Graphics::ScreenHeight; y++ )
	{
		memcpy( &pDst[ y * dstPitch ],&pSysBuffer[y * srcPitch],rowBytes );
	}
	// release the adapter memory
	pImmediateContext->Unmap( pSysBufferTexture.Get(),0u );

	// render offscreen scene texture to back buffer
	pImmediateContext->IASetInputLayout( pInputLayout.Get() );
	pImmediateContext->VSSetShader( pVertexShader.Get(),nullptr,0u );
	pImmediateContext->PSSetShader( pPixelShader.Get(),nullptr,0u );
	pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	const UINT stride = sizeof( FSQVertex );
	const UINT offset = 0u;
	pImmediateContext->IASetVertexBuffers( 0u,1u,pVertexBuffer.GetAddressOf(),&stride,&offset );
	pImmediateContext->PSSetShaderResources( 0u,1u,pSysBufferTextureView.GetAddressOf() );
	pImmediateContext->PSSetSamplers( 0u,1u,pSamplerState.GetAddressOf() );
	pImmediateContext->Draw( 6u,0u );

	// flip back/front buffers
	if( FAILED( hr = pSwapChain->Present( 1u,0u ) ) )
	{
		if( hr == DXGI_ERROR_DEVICE_REMOVED )
		{
			throw CHILI_GFX_EXCEPTION( pDevice->GetDeviceRemovedReason(),L"Presenting back buffer [device removed]" );
		}
		else
		{
			throw CHILI_GFX_EXCEPTION( hr,L"Presenting back buffer" );
		}
	}
}

void Graphics::BeginFrame()
{
	// clear the sysbuffer
	memset( pSysBuffer,0u,sizeof( Color ) * Graphics::ScreenHeight * Graphics::ScreenWidth );
}

void Graphics::PutPixel( int x,int y,Color c )
{
	assert( x >= 0 );
	assert( x < int( Graphics::ScreenWidth ) );
	assert( y >= 0 );
	assert( y < int( Graphics::ScreenHeight ) );
	pSysBuffer[Graphics::ScreenWidth * y + x] = c;
}

void Graphics::PutPixelInCanvas(int x, int y, Color c)
{
	if (!(x < 0 || x >= Graphics::ScreenWidth))
	{
		if (!(y < 0 || y >= Graphics::ScreenHeight)) {
			PutPixel(x, y, c);
		}
	}
}

void Graphics::DrawCircle(Vec2 position_in, float radius_in, Color c)
{
	if (position_in.x - radius_in <= Graphics::ScreenWidth || position_in.y - radius_in <= Graphics::ScreenHeight || position_in.x + radius_in > 0.0f || position_in.y + radius_in > 0.0f)
	{
		float circumference = radius_in * PI * 2.0f;
		Vec2 current_pixel(radius_in, 0.0f);
		Vec2 rotation(std::cos(PI / (radius_in * PI)), std::sin(PI / (radius_in * PI)));
		for (int i = 0; i < (int)circumference / 4; i++)
		{
			for (size_t i = 0; i < 4; i++)
			{
				int x = (int)current_pixel.x + (int)position_in.x;
				int y = (int)current_pixel.y + (int)position_in.y;
				if (x < 0 || x >= Graphics::ScreenWidth)
				{
					current_pixel = GetRotated90(current_pixel);
					continue;
				}
				if (y < 0 || y >= Graphics::ScreenHeight)
				{
					current_pixel = GetRotated90(current_pixel);
					continue;
				}
				PutPixel(x, y, c);
				current_pixel = GetRotated90(current_pixel);
			}
			current_pixel = GetRotated(current_pixel, rotation);
		}
	}
}

void Graphics::DrawLine(Vec2& a, Vec2& b, Color c)
{
	float xstart = (float)a.x;
	float ystart = (float)a.y;
	float xend = b.x - a.x;
	float yend = b.y - a.y;
	if (abs(xend) > abs(yend))
	{
		if (xend >= 0.0f)
		{
			for (int x = 0; x < xend; x++)
			{
				int y = (int)(((float)x / xend)*(yend));

				PutPixelInCanvas(x + (int)xstart, y + (int)ystart, c);
			}
			return;
		}
		else
		{
			for (int x = 0; x > xend; x--)
			{
				int y = (int)(((float)x / xend)*(yend));

				PutPixelInCanvas(x + (int)xstart, y + (int)ystart, c);
			}
			return;
		}
	}else{
		if (yend >= 0.0f)
		{
			for (int y = 0; y < yend; y++)
			{
				int x = (int)(((float)y / yend)*(xend));

				PutPixelInCanvas(x + (int)xstart, y + (int)ystart, c);
			}
			return;
		}
		else
		{
			for (int y = 0; y > yend; y--)
			{
				int x = (int)(((float)y / yend)*(xend));

				PutPixelInCanvas(x + (int)xstart, y + (int)ystart, c);
			}
			return;
		}
		
	}
}

void Graphics::DrawCurve3Ptestes(Vec2 & p0, Vec2 & p1, Vec2 & p2, float radius_in, Color c)
{
	//Belzier Curve:
	float tpixels_by_pdistances = 10.0f / (p2 - p0).Len();
	float t = 0.0f;					//0.0f~1.0f run paramiter
	Vec2 p0_to_p1 = p1 - p0;
	Vec2 p1_to_p2 = p2 - p1;
	Vec2 ip0;						//p0_to_p1 interpollation point
	Vec2 ip1;						//p1_to_p2 interpollation point
	Vec2 ip0_to_ip1;
	for (; t < 1.0f;)
	{
		//float newt = std::sqrt(t);
		float newt = t;
		ip0 = p0_to_p1 * newt;
		ip1 = p1_to_p2 * newt;
		ip0_to_ip1 = (ip1 + p1) - (ip0 + p0);
		Vec2 final = (ip0_to_ip1 * newt) + ip0 + p0;
		DrawCircle(final, radius_in, c);
		t += tpixels_by_pdistances;
	}
	return;
}

void Graphics::DrawCurve3P(Vec2 & p0, Vec2 & p1, Vec2 & p2, Color c)
{
	//Belzier Curve:
	float tpixels_by_pdistances = 10.0f / (p2 - p0).Len();
	float t = 0.0f;//0.0f~1.0f run paramiter
	Vec2 p0_to_p1 = p1 - p0;
	Vec2 p1_to_p2 = p2 - p1;
	Vec2 ip0;						//p0_to_p1 interpollation point
	Vec2 ip1;						//p1_to_p2 interpollation point
	Vec2 ip0_to_ip1;
	//float mediadeespaçamento = 0.0f;
	//float umdivididoporME = 0.0f;
	Vec2 lastpixel = p0;

	for (; t <= 1.0f;)
	{
		//float newt = std::sqrt(t);
		float newt = t;
		ip0 = p0_to_p1 * newt;
		ip1 = p1_to_p2 * newt;
		ip0_to_ip1 = (ip1+p1) - (ip0+p0);
		Vec2 final = (ip0_to_ip1 * newt)+ip0+p0;
		DrawLine(final, lastpixel,c);
		t += tpixels_by_pdistances;
		//mediadeespaçamento += (final - lastpixel).Len() * tpixels_by_pdistances;
		//umdivididoporME = 1 / mediadeespaçamento;
		lastpixel = final;
	}
	DrawLine(lastpixel, p2,c);
	return;
}

void Graphics::DrawCircleLine(Vec2 & start, Vec2 & end, float radius_in, Color c)
{
	Vec2 upline_slop = (GetRotated90((start - end).GetNormalized()) * radius_in);
	DrawLine(start + upline_slop, end + upline_slop, c);
	DrawLine(start - upline_slop, end - upline_slop, c);
	for (int x_a = (int)-radius_in; x_a < (int)radius_in + 1; x_a++)
	{
		for (int y_a = (int)-radius_in; y_a < (int)radius_in + 1; y_a++)
		{
			if ((x_a * x_a) + (y_a * y_a) < radius_in*radius_in)
			{
				if ((x_a * x_a) + (y_a * y_a) > (radius_in - 1.0f) * (radius_in - 1.0f))
				{
					int x_b;
					int y_b;
					if (Dot((start - end), Vec2( (float)x_a, (float)y_a )) > 0.0f)
					{
						x_b = x_a + (int)start.x;
						y_b = y_a + (int)start.y;
					}
					else
					{
						x_b = x_a + (int)end.x;
						y_b = y_a + (int)end.y;
					}
					PutPixelInCanvas(x_b, y_b, c);
				}
			}
		}
	}
}

void Graphics::DrawCircleCurve3P(Vec2 & start, Vec2 & mid, Vec2 & end, float radius_in, Color c)
{
	Vec2 angleOfMatrix = (end - start).GetNormalized();
	Vec2 angleOfMatrix2 = (mid - start).GetNormalized();
	float scalar = Dot(angleOfMatrix, angleOfMatrix2);
	Vec2 xx = (GetRotated(mid, GetInvertedAngle(angleOfMatrix)));
	Vec2 upline_slop1 = (mid - GetRotated((GetRotated(mid, GetInvertedAngle(angleOfMatrix)) + Vec2(0.0f, -radius_in)),angleOfMatrix));
	PutPixelInCanvas((int)(mid.x + upline_slop1.x), (int)(mid.x + upline_slop1.y), Colors::Yellow);
	PutPixelInCanvas((int)(mid.x - upline_slop1.x), (int)(mid.x - upline_slop1.y), Colors::Yellow);
	PutPixelInCanvas((int)(mid).x, (int)(mid).y, Colors::Yellow);
	Vec2 upline_slop0 = GetRotated90((start - mid).GetNormalized()) * radius_in;
	Vec2 upline_slop2 = GetRotated90((mid - end).GetNormalized()) * radius_in;
	DrawCurve3P(start + upline_slop0, mid + upline_slop1, end + upline_slop2, c);
	DrawCurve3P(start - upline_slop0, mid - upline_slop1, end - upline_slop2, c);
	for (int x_a = (int)-radius_in; x_a < (int)radius_in; x_a++)
	{
		for (int y_a = (int)-radius_in; y_a < (int)radius_in; y_a++)
		{
			if ((x_a * x_a) + (y_a * y_a) < radius_in*radius_in)
			{
				if ((x_a * x_a) + (y_a * y_a) > (radius_in - 1.0f) * (radius_in - 1.0f))
				{
					int x_b;
					int y_b;
					if (Dot((start - mid), Vec2((float)x_a, (float)y_a)) > 0.0f)
					{
						x_b = x_a + (int)start.x;
						y_b = y_a + (int)start.y;
						PutPixelInCanvas(x_b, y_b, c);
					}
					if (Dot((end - mid), Vec2((float)x_a, (float)y_a)) > 0.0f)
					{
						x_b = x_a + (int)end.x;
						y_b = y_a + (int)end.y;
						PutPixelInCanvas(x_b, y_b, c);
					}
				}
			}
		}
	}
}

void Graphics::DrawSpriteNonChroma( int x,int y,const Texture& s )
{
	DrawSpriteNonChroma( x,y,s.GetRect(),s );
}

void Graphics::DrawSpriteNonChroma( int x,int y,const RectI& srcRect,const Texture& s )
{
	DrawSpriteNonChroma( x,y,srcRect,GetScreenRect(),s );
}

void Graphics::DrawSpriteNonChroma( int x,int y,RectI srcRect,const RectI& clip,const Texture& s )
{
	assert( srcRect.left >= 0 );
	assert( srcRect.right <= s.GetWidth() );
	assert( srcRect.top >= 0 );
	assert( srcRect.bottom <= s.GetHeight() );
	if( x < clip.left )
	{
		srcRect.left += clip.left - x;
		x = clip.left;
	}
	if( y < clip.top )
	{
		srcRect.top += clip.top - y;
		y = clip.top;
	}
	if( x + srcRect.GetWidth() > clip.right )
	{
		srcRect.right -= x + srcRect.GetWidth() - clip.right;
	}
	if( y + srcRect.GetHeight() > clip.bottom )
	{
		srcRect.bottom -= y + srcRect.GetHeight() - clip.bottom;
	}
	for( int sy = srcRect.top; sy < srcRect.bottom; sy++ )
	{
		for( int sx = srcRect.left; sx < srcRect.right; sx++ )
		{
			PutPixel( x + sx - srcRect.left,y + sy - srcRect.top,s.GetPixel( sx,sy ) );
		}
	}
}

void Graphics::DrawTexture(const Texture & s, const Vec2 & topleft, const Vec2 & offset, float scale, const Vec2 & angle)
{
	Vec2 texture_center(GetRotated((((float)s.GetWidth() * scale) / 2.0f, ((float)s.GetHeight()  * scale) / 2.0f), angle));
	if (screen_center.LenSqrd() < (screen_center - (texture_center +topleft)).LenSqrd())
	{
		return;
	}

	if (scale > 1.0f)
	{
		Vec2 offset_final = offset*scale;
		for (int ty = 0; ty < s.GetHeight(); ty++)
		{
			for (int tx = 0; tx < s.GetWidth(); tx++)
			{
				Color c(s.GetPixel(tx, ty));
				if (c != Colors::Magenta)
				{
					float pre_x((float)tx*scale);
					float pre_y((float)ty*scale);
					for (float sy = 0.0f; sy < scale; sy++)
					{
						for (float sx = 0.0f; sx < scale; sx++)
						{
							float x = pre_x + sx - offset_final.x;
							float y = pre_y + sy - offset_final.y;
							float nowpixel_x((angle.x*x) - angle.y*y);
							float nowpixel_y((angle.y*x) + angle.x*y);
							PutPixelInCanvas(int(nowpixel_x + topleft.x), int(nowpixel_y + topleft.y), c);
						}
					}
				}
			}
		}
		return;
	}
	Vec2 offset_final = offset * scale;
	for (float sy = 0.0f; sy < s.GetHeight()*scale; sy ++)
	{
		for (float sx = 0.0f; sx < s.GetWidth()*scale; sx++)
		{
			Color c(s.GetPixel(int(sx / scale), int(sy / scale)));
			if (c != Colors::Magenta)
			{
				float x = sx - offset_final.x;
				float y = sy - offset_final.y;
				float nowpixel_x((angle.x*x) - angle.y*y);
				float nowpixel_y((angle.y*x) + angle.x*y);
				PutPixelInCanvas(int(nowpixel_x + topleft.x), int(nowpixel_y + topleft.y), c);
			}
		}
	}
	return;
}

//void Graphics::DrawTexture(const Texture& s, Vec2 a_corner, Vec2 b_corner, Vec2 c_corner, Vec2 d_corner)
//{
	//assert(a_corner.x < 0);
	//assert(a_corner.x >= ScreenWidth);
	//assert(a_corner.y < 0);
	//assert(a_corner.y >= ScreenHeight);
	//assert(b_corner.x < 0);
	//assert(b_corner.x >= ScreenWidth);
	//assert(b_corner.y < 0);
	//assert(b_corner.y >= ScreenHeight);
	//assert(c_corner.x < 0);
	//assert(c_corner.x >= ScreenWidth);
	//assert(c_corner.y < 0);
	//assert(c_corner.y >= ScreenHeight);
	//assert(d_corner.x < 0);
	//assert(d_corner.x >= ScreenWidth);
	//assert(d_corner.y < 0);
	//assert(d_corner.y >= ScreenHeight);
	
	//TEXTURE RASTERIZATION:

	//triangle setup
	//
	//if (a_corner.y > b_corner.y)
	//{
	//
	//}
	//Vec2* bot = &a_corner;
	//Vec2* mid = &b_corner;
	//Vec2* top = &c_corner;
	////texture setup
	//Vec2 texture_dimensions((float)s.GetWidth(), (float)s.GetHeight());
	//Vec2 texture_interpolation;
	//Vec2 texture_cicle_interpolation;
	//Vec2 texture_line_interpolation;
	//
	//Vec2 bot_to_top(*top - *bot);
	//Vec2 bot_to_mid(*mid - *bot);
	//Vec2 mid_to_top(*top - *mid);
	//float firsthalf_percentage(bot_to_mid.y / bot_to_top.y);
	//
	//Vec2 tracing_start(bot->x, bot->y);
	//Vec2 tracing(tracing_start);
	//Vec2 tracing_offset(bot_to_top.x / bot_to_top.y, 1.0f);
	//float bot_y = bot->y;
	//
	//float tracing_x_limit(tracing.x);
	//float tracing_x_limit_offset(bot_to_mid.x / bot_to_mid.y);
	//float mid_y = mid->y;
	//
	//
	//// FIRST HALF
	//for (; tracing.y < mid_y; tracing += tracing_offset)
	//{
	//	float y_percent = (tracing.y - tracing_start.y) / bot_to_mid.y;
	//	if (tracing.x < tracing_x_limit)
	//	{
	//		for (float x = tracing.x; x < tracing_x_limit; x += 1.0f)
	//		{
	//			float x_percent = (x - tracing.x) / (tracing.x + tracing_x_limit);
	//			//texture_cicle_interpolation = texture_dimensions * firsthalf_percentage * y_percent;
	//			//texture_line_interpolation = (Vec2(texture_dimensions.x * y_percent, 0.0f) - Vec2(texture_dimensions * firsthalf_percentage * y_percent)) * x_percent + texture_cicle_interpolation;
	//			//const Color srcPixel = s.GetPixel((int)texture_line_interpolation.x, (int)texture_line_interpolation.y);
	//			//if (srcPixel != Colors::Magenta)
	//			//{
	//				PutPixelInCanvas(x, tracing.y, Colors::Blue);
	//			//}
	//		}
	//	}
	//	//else
	//	//{
	//	//	for (float x = tracing.x; x > tracing_x_limit; x -= 1.0f)
	//	//	{
	//	//		float x_percent = (x - tracing.x) / (tracing.x + tracing_x_limit);
	//	//		texture_cicle_interpolation = texture_dimensions * firsthalf_percentage * y_percent;
	//	//		texture_line_interpolation = (Vec2(texture_dimensions.x * y_percent,0.0f) - Vec2(texture_dimensions * firsthalf_percentage * y_percent)) * x_percent + texture_cicle_interpolation;
	//	//		const Color srcPixel = s.GetPixel((int)texture_line_interpolation.x, (int)texture_line_interpolation.y);
	//	//		if (srcPixel != Colors::Magenta)
	//	//		{
	//	//			PutPixelInCanvas(x, tracing.y, srcPixel);
	//	//		}
	//	//	}
	//	//}
	//	tracing_x_limit += tracing_x_limit_offset;
	//}

	// SECOND HALF
	//tracing_x_limit_offset = mid_to_top.x / mid_to_top.y;
	//
	//for (; tracing.y < mid_y; tracing += tracing_offset)
	//{
	//	float y_percent = (tracing.y - tracing_start.y) / bot_to_mid.y;
	//	if (tracing.x < tracing_x_limit)
	//	{
	//		for (float x = tracing.x; x < tracing_x_limit; x += 1.0f)
	//		{
	//			float x_percent = (x - tracing.x) / (tracing.x + tracing_x_limit);
	//			texture_cicle_interpolation = texture_dimensions * (1.0 - firsthalf_percentage) * y_percent + (texture_dimensions * firsthalf_percentage);
	//			texture_line_interpolation = (Vec2(texture_dimensions.x,texture_dimensions.y * y_percent) - Vec2(texture_dimensions * firsthalf_percentage * y_percent)) * x_percent + texture_cicle_interpolation;
	//			const Color srcPixel = s.GetPixel((int)texture_line_interpolation.x, (int)texture_line_interpolation.y);
	//			if (srcPixel != Colors::Magenta)
	//			{
	//				PutPixelInCanvas(x, tracing.y, srcPixel);
	//			}
	//		}
	//	}
	//	else
	//	{
	//		for (float x = tracing.x; x > tracing_x_limit; x -= 1.0f)
	//		{
	//			float x_percent = (x - tracing.x) / (tracing.x + tracing_x_limit);
	//			texture_cicle_interpolation = texture_dimensions * (1.0 - firsthalf_percentage) * y_percent + (texture_dimensions * firsthalf_percentage);
	//			texture_line_interpolation = (Vec2(texture_dimensions.x, texture_dimensions.y * y_percent) - Vec2(texture_dimensions * firsthalf_percentage * y_percent)) * x_percent + texture_cicle_interpolation;
	//			const Color srcPixel = s.GetPixel((int)texture_line_interpolation.x, (int)texture_line_interpolation.y);
	//			if (srcPixel != Colors::Magenta)
	//			{
	//				PutPixelInCanvas(x, tracing.y, srcPixel);
	//			}
	//		}
	//	}
	//	tracing_x_limit += tracing_x_limit_offset;
	//}
//}

void Graphics::DrawSprite( int x,int y,const Texture& s,Color chroma )
{
	DrawSprite( x,y,s.GetRect(),s,chroma );
}

void Graphics::DrawSprite( int x,int y,const RectI& srcRect,const Texture& s,Color chroma )
{
	DrawSprite( x,y,srcRect,GetScreenRect(),s,chroma );
}

void Graphics::DrawSprite( int x,int y,RectI srcRect,const RectI& clip,const Texture& s,Color chroma )
{
	assert( srcRect.left >= 0 );
	assert( srcRect.right <= s.GetWidth() );
	assert( srcRect.top >= 0 );
	assert( srcRect.bottom <= s.GetHeight() );
	if( x < clip.left )
	{
		srcRect.left += clip.left - x;
		x = clip.left;
	}
	if( y < clip.top )
	{
		srcRect.top += clip.top - y;
		y = clip.top;
	}
	if( x + srcRect.GetWidth() > clip.right )
	{
		srcRect.right -= x + srcRect.GetWidth() - clip.right;
	}
	if( y + srcRect.GetHeight() > clip.bottom )
	{
		srcRect.bottom -= y + srcRect.GetHeight() - clip.bottom;
	}
	for( int sy = srcRect.top; sy < srcRect.bottom; sy++ )
	{
		for( int sx = srcRect.left; sx < srcRect.right; sx++ )
		{
			const Color srcPixel = s.GetPixel( sx,sy );
			if( srcPixel != chroma )
			{
				PutPixel( x + sx - srcRect.left,y + sy - srcRect.top,srcPixel );
			}
		}
	}
}

void Graphics::DrawSpriteSubstitute( int x,int y,Color substitute,const Texture& s,Color chroma )
{
	DrawSpriteSubstitute( x,y,substitute,s.GetRect(),s,chroma );
}

void Graphics::DrawSpriteSubstitute( int x,int y,Color substitute,const RectI& srcRect,const Texture& s,Color chroma )
{
	DrawSpriteSubstitute( x,y,substitute,srcRect,GetScreenRect(),s,chroma );
}

void Graphics::DrawSpriteSubstitute( int x,int y,Color substitute,RectI srcRect,const RectI& clip,const Texture& s,Color chroma )
{
	assert( srcRect.left >= 0 );
	assert( srcRect.right <= s.GetWidth() );
	assert( srcRect.top >= 0 );
	assert( srcRect.bottom <= s.GetHeight() );
	if( x < clip.left )
	{
		srcRect.left += clip.left - x;
		x = clip.left;
	}
	if( y < clip.top )
	{
		srcRect.top += clip.top - y;
		y = clip.top;
	}
	if( x + srcRect.GetWidth() > clip.right )
	{
		srcRect.right -= x + srcRect.GetWidth() - clip.right;
	}
	if( y + srcRect.GetHeight() > clip.bottom )
	{
		srcRect.bottom -= y + srcRect.GetHeight() - clip.bottom;
	}
	for( int sy = srcRect.top; sy < srcRect.bottom; sy++ )
	{
		for( int sx = srcRect.left; sx < srcRect.right; sx++ )
		{
			const Color srcPixel = s.GetPixel( sx,sy );
			if( srcPixel != chroma )
			{
				// use substitute color instead of color from the surface (if not chroma)
				PutPixel( x + sx - srcRect.left,y + sy - srcRect.top,substitute );
			}
		}
	}
}


//////////////////////////////////////////////////
//           Graphics Exception
Graphics::Exception::Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line )
	:
	ChiliException( file,line,note ),
	hr( hr )
{}

std::wstring Graphics::Exception::GetFullMessage() const
{
	const std::wstring empty = L"";
	const std::wstring errorName = GetErrorName();
	const std::wstring errorDesc = GetErrorDescription();
	const std::wstring& note = GetNote();
	const std::wstring location = GetLocation();
	return    (!errorName.empty() ? std::wstring( L"Error: " ) + errorName + L"\n"
		: empty)
		+ (!errorDesc.empty() ? std::wstring( L"Description: " ) + errorDesc + L"\n"
			: empty)
		+ (!note.empty() ? std::wstring( L"Note: " ) + note + L"\n"
			: empty)
		+ (!location.empty() ? std::wstring( L"Location: " ) + location
			: empty);
}

std::wstring Graphics::Exception::GetErrorName() const
{
	return DXGetErrorString( hr );
}

std::wstring Graphics::Exception::GetErrorDescription() const
{
	std::array<wchar_t,512> wideDescription;
	DXGetErrorDescription( hr,wideDescription.data(),wideDescription.size() );
	return wideDescription.data();
}

std::wstring Graphics::Exception::GetExceptionType() const
{
	return L"Chili Graphics Exception";
}