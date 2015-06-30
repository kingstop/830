#include "stdafx.h"


PlayerCache::PlayerCache()
{

}
PlayerCache::~PlayerCache()
{

}
PlayerData* PlayerCache::addCacheData( msgs2s::PlayerInfo* p, u16 gs)
{
    u32 guid = p->sc_data().guid();
    u32 a = p->ss_data().account();
    PlayerData* pc = m_PlayerCache.getData(a);
    if (pc)
    {
		// do nothing . cache is the new data ..
	}
    else
    {
        pc = new PlayerData(p, gs);
        m_PlayerCache.addData(a, pc);
		m_GuidPlayers.addData(pc->p->sc_data().guid(), pc);
    }
    m_NameCache.insert(p->sc_data().name());
	return pc;
}
PlayerData*  PlayerCache::getCacheDataByTrans(tran_id_type t)
{
	return m_GuidPlayers.getData(getGuid(t));
}
PlayerData* PlayerCache::getCacheData(account_type a)
{
    return m_PlayerCache.getData(a);
}
u32 PlayerCache::getGuid(tran_id_type t)
{
	u32 guid = INVALID_PLAYER_ID; 
	m_onlineGuid.getData(t, guid); 
	return guid;
}
bool PlayerCache::getTransAndgs(u32 guid, tran_id_type& t, u16& gs)
{
	t = INVALID_TRANS_ID;
	if(m_onlineGuid.getKey(t, guid))
	{
		PlayerData* pkData = m_GuidPlayers.getData(guid);
		if (pkData)
		{
			gs = pkData->gs;
			return true;
		}
	}
	return false;
}