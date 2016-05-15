#ifndef __CMYOBJECT_H__
#define __CMYOBJECT_H__

#include <IGameObject.h>

class CMyObject : public CGameObjectExtensionHelper < CMyObject, IGameObjectExtension >
{
public:
	DECLARE_COMPONENT_TYPE("CMyObject", 0xa7dae65b099b0b92, 0xea5a875def8ea1c6)

	CMyObject();
	virtual ~CMyObject();

	// IGameObjectExtension
	virtual bool Init(IGameObject* pGameObject);
	virtual void InitClient(ChannelId channelId) {}
	virtual void PostInit(IGameObject* pGameObject);
	virtual void PostInitClient(ChannelId channelId) {}
	virtual bool ReloadExtension(IGameObject* pGameObject, const SEntitySpawnParams& params) { return false; }
	virtual void PostReloadExtension(IGameObject* pGameObject, const SEntitySpawnParams& params) {}
	virtual bool GetEntityPoolSignature(TSerialize signature) { return false; }
	virtual void FullSerialize(TSerialize ser) {}
	virtual bool NetSerialize(TSerialize ser, EEntityAspects aspect, uint8 profile, int flags) { return true; }
	virtual void PostSerialize() {}
	virtual void SerializeSpawnInfo(TSerialize ser, IEntity* entity) {}
	virtual ISerializableInfoPtr GetSpawnInfo() { return 0; }
	virtual void Update(SEntityUpdateContext& ctx, int updateSlot);
	virtual void PostUpdate(float frameTime) {}
	virtual void PostRemoteSpawn() {}
	virtual void HandleEvent(const SGameObjectEvent& event) {}
	virtual void ProcessEvent(SEntityEvent& event);
	virtual void SetChannelId(ChannelId id) {}
	virtual void SetAuthority(bool auth) {}
	virtual void GetMemoryUsage(ICrySizer* s) const { s->Add(*this); }
	// ~IGameObjectExtension

protected:
	void Reset();
	void OnScriptEvent(const char* eventName);
};

#endif // __CMYOBJECT_H_
