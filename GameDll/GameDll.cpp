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

// Description : Game DLL entry point.


#include "StdAfx.h"
#include "Game.h"
#include "GameStartup.h"
#include "EditorGame.h"

#include <CryLibrary.h>
#define GAME_API DLL_EXPORT


extern "C"
{
	GAME_API IGame *CreateGame(IGameFramework* pGameFramework)
	{
		ModuleInitISystem(pGameFramework->GetISystem(),"CryGame");

		static char pGameBuffer[sizeof(CGame)];
		return new ((void*)pGameBuffer) CGame();
	}

	GAME_API IGameStartup *CreateGameStartup()
	{
		return CGameStartup::Create();
	}
	GAME_API IEditorGame *CreateEditorGame()
	{
		return new CEditorGame();
	}
}


/*
 * this section makes sure that the framework dll is loaded and cleaned up
 * at the appropriate time
 */

#if !defined(_LIB)

static HMODULE s_frameworkDLL;


static void CleanupFrameworkDLL()
{
	assert( s_frameworkDLL );
	CryFreeLibrary( s_frameworkDLL );
	s_frameworkDLL = 0;
}

HMODULE GetFrameworkDLL(const char* binariesDir)
{
	MEMSTAT_CONTEXT_FMT(EMemStatContextTypes::MSC_Other, 0, "Load %s",GAME_FRAMEWORK_FILENAME );
	if (!s_frameworkDLL)
	{
		if (binariesDir && binariesDir[0])
		{
			string dllName = PathUtil::Make(binariesDir, GAME_FRAMEWORK_FILENAME);
			s_frameworkDLL = CryLoadLibrary(dllName.c_str());		
		}
		else
		{
			s_frameworkDLL = CryLoadLibrary(GAME_FRAMEWORK_FILENAME);
		}
		atexit( CleanupFrameworkDLL );
	}
	return s_frameworkDLL;
}

#endif //WIN32
