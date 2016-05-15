#include "StdAfx.h"

#include "Orange.h"

DECLARE_DEFAULT_COMPONENT_FACTORY(COrange, COrange)

COrange::COrange()
{
}

COrange::~COrange()
{
}

bool COrange::Init(IGameObject* const pGameObject)
{
	SetGameObject(pGameObject);

	return true;
}

void COrange::PostInit(IGameObject* const pGameObject)
{
	// Enable update function
	pGameObject->EnableUpdateSlot(this, 0);

	Reset();
}

void COrange::Reset()
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

void COrange::OnScriptEvent(const char* eventName)
{
	assert(eventName != NULL);

	const bool isOnPropertyChangeEvent = 0 == strcmp(eventName, "OnPropertyChange");
	if (isOnPropertyChangeEvent)
	{
		Reset();
	}
}

void COrange::ProcessEvent(SEntityEvent& evt)
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

void COrange::Update(SEntityUpdateContext& ctx, int updateSlot)
{

}
