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

// Description : AI grenade weapon implemenation


#include "StdAfx.h"
#include "AIGrenade.h"
#include "Actor.h"
#include "FireMode.h"
#include "Throw.h"
#include "ItemSharedParams.h"
#include "IAIActor.h"

DECLARE_DEFAULT_COMPONENT_FACTORY(CAIGrenade, CAIGrenade)

CAIGrenade::CAIGrenade()
: m_waitingForAnimEvent(false)
, m_grenadeLaunchPosition(ZERO)
, m_grenadeLaunchVelocity(ZERO)
{
}

CAIGrenade::~CAIGrenade()
{
	SetFiringLocator(NULL);
};

//-------------------------------------------------------------------------
struct CAIGrenade::FinishGrenadeAction
{
	FinishGrenadeAction(CAIGrenade &aiGrenade): m_aiGrenade(aiGrenade) {};
	CAIGrenade &m_aiGrenade;

	void execute(CItem *_this)
	{
		CActor *pActor = m_aiGrenade.GetOwnerActor();
		CItem *pMain = pActor ? m_aiGrenade.GetActorItem(pActor) : NULL;
		if (pMain)
		{
			// If the action finished without receiving the animation event, fire the grenade anyway.
			if (m_aiGrenade.m_waitingForAnimEvent)
			{
				m_aiGrenade.m_waitingForAnimEvent = false;
				m_aiGrenade.StopFire();
			}
		}
	}
};

//-------------------------------------------------------------------------
void CAIGrenade::StartFire()
{
	CRY_ASSERT_MESSAGE(false, "CAIGrenade::StartFire Called without launch params, ignoring");
}

//-------------------------------------------------------------------------
void CAIGrenade::StartFire(const SProjectileLaunchParams& launchParams)
{
	CFireMode* pCurrentFireMode = GetCFireMode(GetCurrentFireMode());
	CThrow* pThrow = crygti_cast<CThrow*>(pCurrentFireMode);
	if (pThrow)
	{
		SProjectileLaunchParams modifiedLaunchParams = launchParams;
		modifiedLaunchParams.fSpeedScale = 0.0f;
		pThrow->SetProjectileLaunchParams(modifiedLaunchParams);

		pThrow->StartFire();
		m_waitingForAnimEvent = true;

		m_grenadeLaunchPosition.zero();
		m_grenadeLaunchVelocity.zero();

		// Capture the launch position and velocity of the throw from the
		// ai object state. This data will be used later when CAIGrenade
		// takes the responsibility of a weapon firing locator.
		if (IEntity* ownerEntity = GetOwner())
		{
			if (IAIObject* aiObject = ownerEntity->GetAI())
			{
				if (IAIActor* aiActor = aiObject->CastToIAIActor())
				{
					const SOBJECTSTATE& state = aiActor->GetState();

					m_grenadeLaunchPosition = state.vLobLaunchPosition;
					m_grenadeLaunchVelocity = state.vLobLaunchVelocity;
				}
			}
		}

		// Adjust this time value to work with the delay values in the scripts!! (must be a greater delay)
		// Schedule to revert back to main weapon.
		GetScheduler()->TimerAction(5000,
			CSchedulerAction<FinishGrenadeAction>::Create(FinishGrenadeAction(*this)), false);
	}
}

//-------------------------------------------------------------------------
void CAIGrenade::OnAnimationEventShootGrenade(const AnimEventInstance &event)
{
	if (m_waitingForAnimEvent)
	{
		m_waitingForAnimEvent = false;

		if (m_grenadeLaunchPosition.IsZero())
			SetFiringPos(event.m_BonePathName);

		StopFire();
	}
}

void CAIGrenade::SetFiringPos(const char* boneName)
{ 
 	if(IEntity* ownerEntity = GetOwner())
	{
 		if(ICharacterInstance* character = ownerEntity->GetCharacter(0))
		{
			if(ISkeletonPose* skeletonPose = character->GetISkeletonPose())
			{
			  IDefaultSkeleton& rIDefaultSkeleton = character->GetIDefaultSkeleton();
				int32 jointID = rIDefaultSkeleton.GetJointIDByName(boneName);
				if(jointID != -1)
				{
					m_grenadeLaunchPosition = ownerEntity->GetSlotWorldTM(0) * (skeletonPose->GetAbsJointByID(jointID).t);
					return;
				}
			}
		}
	}
	CRY_ASSERT_MESSAGE(false, "CAIGrenade::SetFiringPos - Failed to get the position of the bone");
 	m_grenadeLaunchPosition.zero();
}

//-------------------------------------------------------------------------
void CAIGrenade::OnReset()
{
	BaseClass::OnReset();
	SetFiringLocator(this);
	m_grenadeLaunchPosition.zero();
	m_grenadeLaunchVelocity.zero();
}

void CAIGrenade::SetCurrentFireMode(int idx)
{
	BaseClass::SetCurrentFireMode(idx);
	SetFiringLocator(this);
}


//-------------------------------------------------------------------------
bool CAIGrenade::GetProbableHit(EntityId weaponId, const IFireMode* pFireMode, Vec3& hit)
{
	return false;
}

//-------------------------------------------------------------------------
bool CAIGrenade::GetFiringPos(EntityId weaponId, const IFireMode* pFireMode, Vec3& pos)
{
	if(!m_grenadeLaunchPosition.IsZero())
	{
		pos = m_grenadeLaunchPosition;
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------
bool CAIGrenade::GetFiringDir(EntityId weaponId, const IFireMode* pFireMode, Vec3& dir, const Vec3& probableHit, const Vec3& firingPos)
{
	if(!m_grenadeLaunchVelocity.IsZero())
	{
		dir = m_grenadeLaunchVelocity.GetNormalized();
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------
bool CAIGrenade::GetActualWeaponDir(EntityId weaponId, const IFireMode* pFireMode, Vec3& dir, const Vec3& probableHit, const Vec3& firingPos)
{
	return false;
}

//-------------------------------------------------------------------------
bool CAIGrenade::GetFiringVelocity(EntityId weaponId, const IFireMode* pFireMode, Vec3& vel, const Vec3& firingDir)
{
	if(!m_grenadeLaunchVelocity.IsZero())
	{
		vel = m_grenadeLaunchVelocity;
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------
void CAIGrenade::WeaponReleased()
{
}

//-------------------------------------------------------------------------
void CAIGrenade::PostSerialize()
{
	BaseClass::PostSerialize();

	CActor* pOwnerActor = GetOwnerActor();
	if (!pOwnerActor || pOwnerActor->IsDead())
	{
		Hide(true);
	}
}
