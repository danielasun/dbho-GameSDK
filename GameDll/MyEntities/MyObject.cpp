#include "StdAfx.h"

#include "MyObject.h"

DECLARE_DEFAULT_COMPONENT_FACTORY(CMyObject, CMyObject)

CMyObject::CMyObject()
{
}

CMyObject::~CMyObject()
{
}

bool CMyObject::Init(IGameObject* const pGameObject)
{
	SetGameObject(pGameObject);

	return true;
}

void CMyObject::PostInit(IGameObject* const pGameObject)
{
	pGameObject->EnableUpdateSlot(this, 0);

	Reset();
}

void CMyObject::Reset()
{
	IEntity* const pEntity = GetEntity();

	// Load model
	if (IScriptTable* pScriptTable = pEntity->GetScriptTable())
	{
		SmartScriptTable propertiesTable;
		if (pScriptTable->GetValue("Properties", propertiesTable))
		{
			const char* modelName = NULL;
			if (propertiesTable->GetValue("objModel", modelName) && modelName)
			{
				const int slot = 0;
				pEntity->LoadGeometry(slot, modelName);
			}
		}
	}
}

void CMyObject::OnScriptEvent(const char* eventName)
{
	assert(eventName != NULL);

	const bool isOnPropertyChangeEvent = 0 == strcmp(eventName, "OnPropertyChange");
	if (isOnPropertyChangeEvent)
	{
		Reset();
	}
}

void CMyObject::ProcessEvent(SEntityEvent& evt)
{
	switch (evt.event)
	{
	case ENTITY_EVENT_RESET:
	{
		Reset();
	}
	break;

	case ENTITY_EVENT_SCRIPT_EVENT:
	{
		const char* eventName = reinterpret_cast<const char*>(evt.nParam[0]);
		OnScriptEvent(eventName);
	}
	break;
	}
}

void CMyObject::Update(SEntityUpdateContext& ctx, int updateSlot)
{

}