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

#ifndef __GAME_CODE_COVERAGE_GUI_H_
#define __GAME_CODE_COVERAGE_GUI_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "GameCodeCoverage/GameCodeCoverageEnabled.h"
#include "GameMechanismManager/GameMechanismBase.h"

#if ENABLE_GAME_CODE_COVERAGE

class CGameCodeCoverageGUI : public CGameMechanismBase
{
public:		// Construction & destruction
	CGameCodeCoverageGUI(void);
	~CGameCodeCoverageGUI(void);

	static ILINE CGameCodeCoverageGUI * GetInstance()
	{
		return s_instance;
	}

public:		// Operations
	void Draw();

private:	// Member data
	static CGameCodeCoverageGUI * s_instance;

	virtual void Update(float dt) {}

	int m_showListWhenNumUnhitCheckpointsIs;
};

#endif	// ENABLE_GAME_CODE_COVERAGE

#endif	// __GAME_CODE_COVERAGE_GUI_H_