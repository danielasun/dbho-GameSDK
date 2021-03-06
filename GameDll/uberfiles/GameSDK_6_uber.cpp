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

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_devirt_defines.h>
#endif

#include "../RecordingSystem.cpp"
#include "../RecordingSystemClientSender.cpp"
#include "../RecordingSystemCompressor.cpp"
#include "../RecordingSystemDebug.cpp"
#include "../RecordingSystemServerForwarder.cpp"
#include "../RecordingSystemStreamer.cpp"
#include "../RevertibleConfigLoader.cpp"
#include "../RichPresence.cpp"
#include "../ScriptBind_ProtectedBinds.cpp"
#include "../ShotDebug.cpp"
#include "../SprintStamina.cpp"
#include "../StatsAgentPipe.cpp"
#include "../StatsEntityIdRegistry.cpp"
#include "../StatsStructures.cpp"
#include "../TeamVisualizationManager.cpp"
#include "../ThrowIndicator.cpp"
#include "../Turret/Turret/FlowNodesTurret.cpp"
#include "../Turret/Turret/ProceduralClipTurretAimPose.cpp"
#include "../Turret/Turret/ProceduralContextTurretAimPose.cpp"
#include "../Turret/Turret/ScriptBind_Turret.cpp"
#include "../Turret/Turret/Turret.cpp"
#include "../Turret/Turret/TurretBehavior.cpp"
#include "../Turret/Turret/TurretBehaviorParams.cpp"
#include "../UI/HUD/ErrorHandling.cpp"
#include "../UseableTurret.cpp"

#ifdef _DEVIRTUALIZE_
	#include <GameSDK_wrapper_includes.h>
#endif
