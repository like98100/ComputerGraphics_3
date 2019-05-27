#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_
//////////////
// INCLUDES //
//////////////
#include <windows.h>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"

#include "cameraclass.h"
#include "modelclass.h"
//#include "colorshaderclass.h"

#include "textureshaderclass.h"
#include "bitmapclass.h"

#include "lightshaderclass.h"
#include "lightclass.h"

#include "textclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


#include "inputclass.h"
////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	void SetSampling(int, HWND);
private:
	bool Render(float);
private:

	D3DClass* m_D3D;

	CameraClass* m_Camera;
	ModelClass* m_Model[5];
	//ColorShaderClass* m_ColorShader;

	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;

	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	InputClass* m_Input;
	TextClass* m_Text;
};
#endif