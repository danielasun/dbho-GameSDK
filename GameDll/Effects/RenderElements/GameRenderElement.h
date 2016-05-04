/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
// Original file Copyright Crytek GMBH or its affiliates, used under license.

#ifndef _IGAME_RENDERELEMENT_
#define _IGAME_RENDERELEMENT_

#pragma once

// Includes
#include "Effects/GameEffectsSystem.h"
#include "CREGameEffect.h"

// Forward declares
struct IGameRenderElementParams;

//==================================================================================================
// Name: IGameRenderElement
// Desc: Base interface for all game render elements
// Author: James Chilvers
//==================================================================================================
struct GameSDKIGameRenderElement : public IREGameEffect, public _i_reference_target_t
{
    DECLARE_TYPELIB(GameSDKIGameRenderElement); // Allow soft coding on this interface

    virtual ~GameSDKIGameRenderElement() {}

	virtual bool InitialiseGameRenderElement() = 0;
	virtual void ReleaseGameRenderElement() = 0;
	virtual void UpdatePrivateImplementation() = 0;

	virtual CREGameEffect*	GetCREGameEffect() = 0;

	virtual IGameRenderElementParams* GetParams() = 0;
};//------------------------------------------------------------------------------------------------

//==================================================================================================
// Name: CGameRenderElement
// Desc: Base class for all game render elements
// Author: James Chilvers
//==================================================================================================
class GameSDKCGameRenderElement : public GameSDKIGameRenderElement
{
    DECLARE_TYPE(GameSDKCGameRenderElement, GameSDKIGameRenderElement); // Exposes this type for SoftCoding
public:
	GameSDKCGameRenderElement();
	virtual ~GameSDKCGameRenderElement() {}

	virtual bool InitialiseGameRenderElement();
	virtual void ReleaseGameRenderElement();
	virtual void UpdatePrivateImplementation();

	virtual CREGameEffect*	GetCREGameEffect();

protected:
	CREGameEffect*		SOFT(m_pREGameEffect);
};//------------------------------------------------------------------------------------------------

//==================================================================================================
// Name: IGameRenderElementParams
// Desc: Game Render Element params
// Author: James Chilvers
//==================================================================================================
struct IGameRenderElementParams
{
	virtual ~IGameRenderElementParams() {}
};//------------------------------------------------------------------------------------------------

#endif // _IGAME_RENDERELEMENT_
