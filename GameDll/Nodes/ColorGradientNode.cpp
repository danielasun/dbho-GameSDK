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

#include "StdAfx.h"

#include "ColorGradientNode.h"
#include "Graphics/ColorGradientManager.h"
#include <IColorGradingController.h>

enum InputPorts
{
	eIP_Trigger,
};

const SInputPortConfig CFlowNode_ColorGradient::inputPorts[] =
{
	InputPortConfig_Void("Trigger", _HELP("")),
	InputPortConfig<string>("tex_TexturePath", _HELP("Path to the Color Chart texture.")),
	InputPortConfig<float>("TransitionTime", _HELP("Fade in time (Seconds).")),
	{0},    
};

CFlowNode_ColorGradient::CFlowNode_ColorGradient(SActivationInfo* activationInformation) :
m_pTexture(NULL)
{
}

CFlowNode_ColorGradient::~CFlowNode_ColorGradient()
{
	SAFE_RELEASE(m_pTexture);
}



void CFlowNode_ColorGradient::GetConfiguration(SFlowNodeConfig& config)
{
	config.pInputPorts = inputPorts;
	config.SetCategory(EFLN_ADVANCED);
}

void CFlowNode_ColorGradient::ProcessEvent(EFlowEvent event, SActivationInfo* activationInformation)
{
	//Preload texture
	if(event==IFlowNode::eFE_PrecacheResources && m_pTexture==NULL)
	{
		const string texturePath = GetPortString(activationInformation, eInputPorts_TexturePath);

		const uint32 COLORCHART_TEXFLAGS = FT_NOMIPS |  FT_DONT_STREAM | FT_DONT_RESIZE | FT_STATE_CLAMP;

		m_pTexture = gEnv->pRenderer->EF_LoadTexture(texturePath.c_str(), COLORCHART_TEXFLAGS);
		
		//CryLogAlways("CFlowNode_ColorGradient 0x%p: Precache texture %s", this, texturePath.c_str());
	}

	if (event==IFlowNode::eFE_Activate && IsPortActive(activationInformation, eIP_Trigger))
	{
		const string texturePath = GetPortString(activationInformation, eInputPorts_TexturePath);
		const float timeToFade = GetPortFloat(activationInformation, eInputPorts_TransitionTime);

		g_pGame->GetColorGradientManager().TriggerFadingColorGradient(texturePath, timeToFade);
	}
}

void CFlowNode_ColorGradient::GetMemoryUsage(ICrySizer* sizer) const
{
	sizer->Add(*this);
}

REGISTER_FLOW_NODE("CrysisFX:ColorGradient", CFlowNode_ColorGradient);
