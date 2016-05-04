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

// Description : Implements a damage behavior which create an explosion

#include "StdAfx.h"
#include "IVehicleSystem.h"
#include "VehicleDamageBehaviorExplosion.h"
#include "Game.h"
#include "GameRules.h"

//------------------------------------------------------------------------
CVehicleDamageBehaviorExplosion::CVehicleDamageBehaviorExplosion() 
: m_pVehicle()
, m_damage(0.0f)
, m_minRadius(0.0f)
, m_radius(0.0f)
, m_minPhysRadius(0.0f)
, m_physRadius(0.0f)
, m_pressure(0.0f)
, m_soundRadius(0.0f)
, m_pHelper()
, m_exploded(false)
{

}

//------------------------------------------------------------------------
bool CVehicleDamageBehaviorExplosion::Init(IVehicle* pVehicle, const CVehicleParams& table)
{
	m_pVehicle = pVehicle;
  m_exploded = false;

	CVehicleParams explosionParams = table.findChild("Explosion");
	if (!explosionParams)
		return false;

	explosionParams.getAttr("damage", m_damage);
	explosionParams.getAttr("radius", m_radius);
	explosionParams.getAttr("pressure", m_pressure);
	
	if (!explosionParams.getAttr("minRadius", m_minRadius))
		m_minRadius = m_radius/2.0f;

	if (!explosionParams.getAttr("physRadius", m_physRadius))
		m_physRadius = min(m_radius, 5.0f);

	if (!explosionParams.getAttr("minPhysRadius", m_minPhysRadius))
		m_minPhysRadius = m_physRadius/2.0f;

	explosionParams.getAttr("soundRadius", m_soundRadius);

	if (explosionParams.haveAttr("helper"))
		m_pHelper = m_pVehicle->GetHelper(explosionParams.getAttr("helper"));
	else
		m_pHelper = NULL;

	return true;
}

//------------------------------------------------------------------------
void CVehicleDamageBehaviorExplosion::Reset()
{
  m_exploded = false;
}

//------------------------------------------------------------------------
void CVehicleDamageBehaviorExplosion::OnDamageEvent(EVehicleDamageBehaviorEvent event, const SVehicleDamageBehaviorEventParams& behaviorParams)
{
  if (event == eVDBE_Repair)
    return;

	if (!m_exploded && behaviorParams.componentDamageRatio >= 1.0f)
	{
		CGameRules *pGameRules = g_pGame->GetGameRules();
		if (pGameRules && gEnv->bServer)
		{
			ExplosionInfo explosionInfo;
			explosionInfo.damage = m_damage;
			explosionInfo.damage += (behaviorParams.randomness) * cry_random(-0.25f, 0.25f) * m_damage;

			if (m_pHelper)
				explosionInfo.pos = m_pHelper->GetWorldSpaceTranslation();
      else if (behaviorParams.pVehicleComponent)
        explosionInfo.pos = m_pVehicle->GetEntity()->GetWorldTM() * behaviorParams.pVehicleComponent->GetBounds().GetCenter();
			else
				explosionInfo.pos = m_pVehicle->GetEntity()->GetWorldTM().GetTranslation();

			explosionInfo.radius = m_radius;
			explosionInfo.minRadius = m_minRadius;
			explosionInfo.physRadius = m_physRadius;
			explosionInfo.minPhysRadius = m_minPhysRadius;
			explosionInfo.shooterId = behaviorParams.shooterId;
			explosionInfo.weaponId = m_pVehicle->GetEntityId();
			explosionInfo.pressure = m_pressure;
			explosionInfo.soundRadius = m_soundRadius;
			explosionInfo.type = CGameRules::EHitType::Frag;
			pGameRules->QueueExplosion(explosionInfo);
		}

    m_exploded = true;
	}
}

//------------------------------------------------------------------------
void CVehicleDamageBehaviorExplosion::Serialize(TSerialize ser, EEntityAspects aspects)
{
  if (ser.GetSerializationTarget() != eST_Network)
  {
    ser.Value("exploded", m_exploded);
  }
}

DEFINE_VEHICLEOBJECT(CVehicleDamageBehaviorExplosion);
