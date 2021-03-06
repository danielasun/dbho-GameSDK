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

// GameLocalizationManager is designed to look after the loading of strings
// and be the sole place in the game that loads and unloads localization tags

#ifndef GAME_LOCALIZATION_MANAGER_H
#define GAME_LOCALIZATION_MANAGER_H

#pragma once

class CGameLocalizationManager
{
public:
	CGameLocalizationManager();
	virtual ~CGameLocalizationManager();

	void SetGameType();
	void SetCredits(bool enable);

#if !defined(_RELEASE)
	static void LocalizationDumpLoadedTags(IConsoleCmdArgs* pArgs);
#endif //#if !defined(_RELEASE)

protected:
	enum ELocalizationTag
	{
		eLT_Init,
		eLT_GameType,
		eLT_Credits,
		eLT_Num
	};

	void LoadLocalizationData();
	void LegacyLoadLocalizationData();

	void LoadTag(ELocalizationTag tag);
	void LoadTagInternal( ELocalizationTag tag , const char* pTag );
	void UnloadTag(ELocalizationTag tag);

	string m_loadedTag[eLT_Num];
};

#endif //#ifndef GAME_LOCALIZATION_MANAGER_H
