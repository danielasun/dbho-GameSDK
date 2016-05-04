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

// Description : C4 projectile specific stuff


#ifndef __C4PROJECTILE_H__
#define __C4PROJECTILE_H__

#if _MSC_VER > 1000
# pragma once
#endif


#include "Projectile.h"
#include "StickyProjectile.h"
#include "GameRulesModules/IGameRulesTeamChangedListener.h"
#include "GameRulesModules/IGameRulesClientConnectionListener.h"

struct IAttachmentManager;

class CC4Projectile : public CProjectile
										, public IGameRulesTeamChangedListener
										,	public IGameRulesClientConnectionListener
{
private:
	typedef CProjectile BaseClass;

	static const NetworkAspectType ASPECT_C4_STATUS	= eEA_GameServerA;


public:
	DECLARE_COMPONENT_TYPE("CC4Projectile", 0x5FB8207F3FF04F1D, 0x8BAC526EBA70B229);
	CC4Projectile();
	virtual ~CC4Projectile();

	virtual bool Init(IGameObject *pGameObject);
	virtual void HandleEvent(const SGameObjectEvent &event);
	virtual void Launch(const Vec3 &pos, const Vec3 &dir, const Vec3 &velocity, float speedScale);
	virtual bool CanDetonate();
	virtual bool Detonate();
	virtual void ProcessEvent(SEntityEvent &event);
	virtual void FullSerialize(TSerialize ser);
	virtual bool NetSerialize(TSerialize ser, EEntityAspects aspect, uint8 profile, int pflags);
	virtual NetworkAspectType GetNetSerializeAspects();
	virtual void Update(SEntityUpdateContext &ctx, int updateSlot);
	virtual void PostRemoteSpawn();
	virtual void Explode(const CProjectile::SExplodeDesc& explodeDesc);

	virtual void OnHit(const HitInfo&);
	virtual void OnServerExplosion(const ExplosionInfo&);
	virtual void OnExplosion(const ExplosionInfo&);
	virtual EntityId GetStuckToEntityId() const;

	virtual void SerializeSpawnInfo( TSerialize ser, IEntity * );
	virtual ISerializableInfoPtr GetSpawnInfo();

	// IGameRulesTeamChangedListener
	virtual void OnChangedTeam(EntityId entityId, int oldTeamId, int newTeamId);
	// ~IGameRulesTeamChangedListener

	// IGameRulesClientConnectionListener
	virtual void OnClientConnect(ChannelId channelId, bool isReset, EntityId playerId) {};
	virtual void OnClientDisconnect(ChannelId channelId, EntityId playerId) {};
	virtual void OnClientEnteredGame(ChannelId channelId, bool isReset, EntityId playerId) {};
	virtual void OnOwnClientEnteredGame();
	// ~IGameRulesClientConnectionListener

protected:

	struct SC4Info : public SInfo
	{
		int team;

		void SerializeWith( TSerialize ser )
		{
			SInfo::SerializeWith(ser);

			ser.Value("team", team, 'team');
		}
	};

private:

	virtual void SetParams(const SProjectileDesc& projectileDesc);
	void Arm(bool arm);
	void CreateLight();
	void UpdateLight(float fFrameTime, bool forceColorChange);
	void SetLightParams();
	void RemoveLight();
	void SetupUIIcon();

	CStickyProjectile	m_stickyProjectile;
	int					m_teamId;
	bool				m_armed;
	bool				m_OnSameTeam;
	bool				m_isShowingUIIcon;
	float				m_disarmTimer;
	float				m_pulseTimer;
	
	IStatObj*		m_pStatObj;
	IMaterial*	m_pArmedMaterial;
	IMaterial*	m_pDisarmedMaterial;
	ILightSource*	m_pLightSource;
};

#endif
