#ifndef __MYHUMAN_H__
#define __MYHUMAN_H__

#include "Player.h"

struct CMyHuman : public CPlayer
{
public:
	DECLARE_COMPONENT_TYPE("CMyHuman", 0xc72e154cecbc0530, 0x79727ecac5237975)

	CMyHuman();
	virtual ~CMyHuman();

	virtual bool Init(IGameObject *pGameObject);

	virtual void PostInit(IGameObject *pGameObject);

	virtual void Update(SEntityUpdateContext& ctx, int updateSlot);

	void GetMemoryUsage(ICrySizer *pSizer) const
	{
		pSizer->AddObject(this, sizeof(*this));
		CPlayer::GetInternalMemoryUsage(pSizer);
	}
};

#endif // __MYHUMAN_H__