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

// Description: 
//     Interface for a class that received events when items are picked up


#ifndef _IGAME_RULES_PICKUP_LISTENER_H_
#define _IGAME_RULES_PICKUP_LISTENER_H_

#if _MSC_VER > 1000
# pragma once
#endif

class IGameRulesPickupListener
{
public:
	virtual ~IGameRulesPickupListener() {}

	virtual void OnItemPickedUp(EntityId itemId, EntityId actorId) = 0;
	virtual void OnItemDropped(EntityId itemId, EntityId actorId) = 0;

	virtual void OnPickupEntityAttached(EntityId entityId, EntityId actorId) = 0;
	virtual void OnPickupEntityDetached(EntityId entityId, EntityId actorId, bool isOnRemove) = 0;
};

#endif // _IGAME_RULES_PICKUP_LISTENER_H_
