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
#include "Nodes/G2FlowBaseNode.h"

#include "Turret.h"
#include "TurretHelpers.h"


class CFlowNode_Turret_ForceTarget
	: public CFlowBaseNode< eNCT_Singleton >
{
	enum INPUTS
	{
		eInputPort_Start,
		eInputPort_Stop,
		eInputPort_AllowFire,
		eInputPort_TargetEntityId,
	};

public:
	CFlowNode_Turret_ForceTarget( SActivationInfo* pActInfo )
	{
	}

	~CFlowNode_Turret_ForceTarget()
	{
	}

	virtual void GetMemoryUsage( ICrySizer* s ) const
	{
		s->Add( *this );
	}

	void GetConfiguration( SFlowNodeConfig& config )
	{
		static const SInputPortConfig inPorts[] = 
		{
			InputPortConfig_Void( "Start" ),
			InputPortConfig_Void( "Stop" ),
			InputPortConfig< bool >( "AllowFire" ),
			InputPortConfig< EntityId >( "TargetEntity", _HELP( "Entity id that the turret will track." ) ),
			{ 0 }
		};

		static const SOutputPortConfig outPorts[] = 
		{
			{ 0 }
		};

		config.pInputPorts = inPorts;
		config.pOutputPorts = outPorts;
		config.nFlags |= EFLN_TARGET_ENTITY;
		config.sDescription = _HELP( "Turret force target");
		config.SetCategory( EFLN_APPROVED );
	}

	void ProcessEvent( EFlowEvent event, SActivationInfo* pActInfo )
	{
		if ( pActInfo->pEntity == NULL )
		{
			return;
		}
			
		const EntityId entityId = pActInfo->pEntity->GetId();
		CTurret* pTurret = TurretHelpers::FindTurret( entityId );
		if ( pTurret == NULL )
		{
			return;
		}

		switch( event )
		{
		case eFE_Activate:
			if ( IsPortActive( pActInfo, eInputPort_Start ) )
			{
				const EntityId targetEntityId = GetPortEntityId( pActInfo, eInputPort_TargetEntityId );
				pTurret->SetForcedVisibleTarget( targetEntityId );

				const bool allowFire = GetPortBool( pActInfo, eInputPort_AllowFire );
				pTurret->SetAllowFire( allowFire );
			}
			else if ( IsPortActive( pActInfo, eInputPort_Stop ) )
			{
				pTurret->ClearForcedVisibleTarget();
				pTurret->SetAllowFire( true );
			}
			break;
		}
	}
};

REGISTER_FLOW_NODE( "Turret:ForceTarget", CFlowNode_Turret_ForceTarget )
