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

#pragma once

#ifndef COLOR_GRADIENT_NODE_H
#define COLOR_GRADIENT_NODE_H

#include "G2FlowBaseNode.h"

//namespace EngineFacade
//{
//	struct IGameEnvironment;
//}

class CFlowNode_ColorGradient : public CFlowBaseNode<eNCT_Instanced>
{
public:
	static const SInputPortConfig inputPorts[];

	CFlowNode_ColorGradient( SActivationInfo* activationInformation);
	~CFlowNode_ColorGradient();

	virtual void GetConfiguration(SFlowNodeConfig& config);
	virtual void ProcessEvent(EFlowEvent event, SActivationInfo* activationInformation);
	virtual void GetMemoryUsage(ICrySizer* sizer) const;

	virtual IFlowNodePtr Clone( SActivationInfo *pActInfo ) { return new CFlowNode_ColorGradient(pActInfo); }

	enum EInputPorts
	{
		eInputPorts_Trigger,
		eInputPorts_TexturePath,
		eInputPorts_TransitionTime,
		eInputPorts_Count,
	};

private:
//	IGameEnvironment& m_environment;
	ITexture *m_pTexture;
};

#endif 
