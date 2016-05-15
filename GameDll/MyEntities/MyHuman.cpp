#include "StdAfx.h"

#include "MyHuman.h"

DECLARE_DEFAULT_COMPONENT_FACTORY(CMyHuman, CMyHuman)

CMyHuman::CMyHuman()
{
}

CMyHuman::~CMyHuman()
{
}

bool CMyHuman::Init(IGameObject *pGameObject)
{
	if (!CPlayer::Init(pGameObject))
		return false;

	SetGameObject(pGameObject);

	return true;
}

void CMyHuman::PostInit(IGameObject *pGameObject)
{
	CPlayer::PostInit(pGameObject);

	// Enable update function
	pGameObject->EnableUpdateSlot(this, 0);

	// Initialize other components here
}

void CMyHuman::Update(SEntityUpdateContext& ctx, int updateSlot)
{
	CPlayer::Update(ctx, updateSlot);

	//gEnv->pLog->Log("Test");
}