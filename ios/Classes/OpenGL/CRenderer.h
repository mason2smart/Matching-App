/* Copyright (c) 1996-2014 Clickteam
*
* This source code is part of the iOS exporter for Clickteam Multimedia Fusion 2
* and Clickteam Fusion 2.5.
* 
* Permission is hereby granted to any person obtaining a legal copy 
* of Clickteam Multimedia Fusion 2 or Clickteam Fusion 2.5 to use or modify this source 
* code for debugging, optimizing, or customizing applications created with 
* Clickteam Multimedia Fusion 2 and/or Clickteam Fusion 2.5. 
* Any other use of this source code is prohibited.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/
//
//  CPPRenderer.h
//  RuntimeIPhone
//
//  Created by Anders Riggelsen on 8/20/13.
//  Copyright (c) 2013 Clickteam. All rights reserved.
//

#pragma once

#include <QuartzCore/QuartzCore.h>

#include <OpenGLES/EAGL.h>
#include <OpenGLES/EAGLDrawable.h>

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#import "CTexture.h"
#import "CoreMath.h"
#import "CRect.h"

#import "Array.h"

@class CRenderToTexture;
@class CRunView;
@class CArrayList;
@class CRunApp;
@class CLayer;
class CShader;

struct Viewport
{
	Viewport();
	Viewport(int x, int y, int width, int height);
	Viewport(Vec2i position, Vec2i size);

	bool operator==(const Viewport &rhs) const;
	bool operator!=(const Viewport &rhs) const;

	float aspect();		//The current aspect ratio of this viewport

	Vec2i position;		//Position in pixels
	Vec2i size;			//Size in pixels
};

class RenderingState
{
public:
	Viewport viewport;
	Vec2i framebufferSize;
	unsigned int framebuffer;

	Vec2f contentSize;	//The size of the underlying game in game-units
	Mat3f transform;	//The transform matrix of this viewport (scroll, zoom, rotation ect. ect.)
	Mat3f projection;	//The projection matrix of this viewport (based on the contentSize)
};

class CRenderer
{
public:
	EAGLContext* context;
	CRunView* view;

    // The pixel dimensions of the CAEAGLLayer
    GLint backingWidth;
    GLint backingHeight;

	RenderingState currentRenderState;
	Array<RenderingState> renderStateStack;

	GLuint buffer;

	//OpenGL capabilities
	GLint maxTextureSize;

	int originX, originY;
	CGPoint topLeft;

	int textureUsage;
	NSMutableSet* usedTextures;

	NSMutableSet* supportedExtensions;

    // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view
    GLuint defaultFramebuffer, colorRenderbuffer;

	CAEAGLLayer* glLayer;
	CGSize windowSize;
	CArrayList* texturesToRemove;

	//Current OpenGL state to minimize redundant state changes
	int currentTextureID;
	int currentBlendEquationA;
	int currentBlendEquationB;
	int currentBlendFunctionA;
	int currentBlendFunctionB;
	float cR, cG, cB, cA;
	BOOL usesBlending;
	BOOL usesScissor;

	CLayer* currentLayer;
	int currentEffect;
	float currentParam;
	Viewport currentViewport;

	CShader* defaultShader;
	CShader* gradientShader;
	CShader* currentShader;

	CRenderer(CRunView* runView);
	~CRenderer();

	void pushRenderingState();
	void popRenderingState();

	void destroyFrameBuffers();

	bool resizeFromLayer(CAEAGLLayer* layer);
	void clear(float red, float green, float blue);
	void clear();
	void clearWithRunApp(CRunApp* app);
	void swapBuffers();
	void flush();
	void forgetCachedState();
	void setCurrentShader(CShader* shader);

	void bindRenderBuffer();
	void updateViewport();
	void setViewport(Viewport viewport);

	void setCurrentLayer(CLayer* layer);

	void setInkEffect(int effect, int effectParam, CShader* shader);
	void setProjectionMatrix(int x, int y, int width, int height);

	void renderSimpleImage(int x, int y, int w, int h);
	void renderImage(CTexture* image, int x, int y, int w, int h, int inkEffect, int inkEffectParam);
	void renderPattern(CTexture* image, int x, int y, int w, int h, int inkEffect, int inkEffectParam);
	void renderPattern(CTexture* image, int x, int y, int w, int h, int inkEffect, int inkEffectParam, bool flipX, bool flipY, float scaleX = 1.0f, float scaleY = 1.0f);
	void renderScaledRotatedImage(CTexture* image, float angle, float sX, float sY, int hX, int hY, int x, int y, int w, int h, int inkEffect, int inkEffectParam);
	void renderLine(Vec2f a, Vec2f b, int color, float thickness);

	void renderGradient(GradientColor gradient, int x, int y, int w, int h, int inkEffect, int inkEffectParam);
	void renderGradient(GradientColor gradient, CRect rect, int inkEffect, int inkEffectParam);
	void renderSolidColor(int color, int x, int y, int w, int h, int inkEffect, int inkEffectParam);
	void renderSolidColor(int color, CRect rect, int inkEffect, int inkEffectParam);

	//For transitions
	void setOrigin(int x, int y);
	void renderBlitFull(CRenderToTexture* source);
	void renderBlit(CRenderToTexture* source, int xDst, int yDst, int xSrc, int ySrc, int width, int height);
	void renderStretch(CRenderToTexture* source, int xDst, int yDst, int wDst, int hDst, int xSrc, int ySrc, int wSrc, int hSrc, int inkEffect = 0, int inkEffectParam = 0);
	void renderFade(CRenderToTexture* source, int alpha);

	void useBlending(BOOL useBlending);

	void setBlendEquation(GLenum equation);
	void setBlendEquationSeperate(GLenum equationA, GLenum equationB);
	void setBlendFunction(GLenum sFactor, GLenum dFactor);
	void setBlendColor(float red, float green, float blue, float alpha);

	//Clipping
	void setClip(int x, int y, int w, int h);
	void resetClip();

	static void checkForError();
	static CRenderer* getRenderer();

	void uploadTexture(CTexture* texture);
	void removeTexture(CTexture* texture, BOOL cleanMemory);
	void cleanMemory();
	void cleanUnused();
	void pruneTexture();
	void clearPruneList();

};
