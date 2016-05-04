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

#ifndef __ANIM_ACTION_AI_LOOKING_H__
#define __ANIM_ACTION_AI_LOOKING_H__

#include "ICryMannequin.h"


class CAnimActionAILooking
	: public TAction< SAnimationContext >
{
public:
	typedef TAction< SAnimationContext > TBase;

	DEFINE_ACTION( "AnimActionAILooking" );

	CAnimActionAILooking();

	// IAction
	virtual void OnInitialise();
	virtual EStatus Update( float timePassed );
	// ~IAction

	static bool IsSupported( const SAnimationContext& context );

private:
	static FragmentID FindFragmentId( const SAnimationContext& context );
};


#endif