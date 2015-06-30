#include "stdafx.h"
#include "player.h"
#include "session.h"

#define _SAVE_PLAYER_ONLINE_TIME_  (10 * 10 * _TIME_SECOND_MSEL_)
#define _ONCE_SAVE_PLAYE_COUNT 400
ObjectManager::ObjectManager()
{
    gEventMgr.addEvent(this, &ObjectManager::saveAllPlayers, EVENT_SAVE_PLAYER_DATA_, _SAVE_PLAYER_ONLINE_TIME_, 0, 0);
}
ObjectManager::~ObjectManager()
{

}
Player* ObjectManager::createPlayer(Session* s, const msgs2s::PlayerInfo* p)
{
    if (!s || !p )
    {   return NULL ;}

    u32 guid =  p->sc_data().guid();
    Player* pkPlayer = getPlayer(guid);
    if (NULL == pkPlayer)
    {
        pkPlayer = Memory::createObject<Player, Session*, const msgs2s::PlayerInfo*>(s, p);
        m_PlayerMap.addData(guid, pkPlayer);
        m_AccountMap.addData(p->ss_data().account(), guid);
    }else
    {
       // assert(false);
	    pkPlayer->setReconnet(s);
        Mylog::log_server(LOG_ERROR, "player [%u] memory error .......", guid);
    }
    return pkPlayer;
}
Player* ObjectManager::getPlayer(u32 guid)
{
    return m_PlayerMap.getData(guid);
}
Player* ObjectManager::getPlayerByAccount(account_type a)
{
    u32 guid = INVALID_PLAYER_ID;
    if (m_AccountMap.getData(a, guid))
    {
        return getPlayer(guid);
    }
    return NULL;
}
void ObjectManager::updateObject(u32 ndiff)
{
	const std::map<u32, Player*>& pmap = m_PlayerMap.getDataMap();
	std::map<u32, Player*>::const_iterator it = pmap.begin();
	std::map<u32, Player*>::const_iterator itend = pmap.end();
	for (it; it!= itend; ++it)
	{
	    Player* p = it->second;
		if (p)
		{
		     p->update(ndiff);
		}
	}
}
void ObjectManager::savePlayerinfo(const msgs2s::PlayerInfo& info, msgs2s::LineState state)
{
    msgs2s::MsgGS2DBSavePlaye msg;
    msgs2s::DBPlayerData* p = msg.add_players();
    p->set_state(state);
    *(p->mutable_data()) = info;
    gGSDBClient.sendPBMessage(&msg);
   // Mylog::log_player(LOG_DEBUG, "save player [%u]", info.sc_data().guid(), info.sc_data().posx(), info.sc_data().posy());
}
void ObjectManager::logInfo()
{
    if (m_PlayerMap.getSize() > 0)
        Mylog::log_player(LOG_DEBUG, "onlines player count :[%u]", m_PlayerMap.getSize());
}
void ObjectManager::saveAllPlayers()
{
   
    const std::map<u32, Player*>& pmap = m_PlayerMap.getDataMap();
    std::map<u32, Player*>::const_iterator it = pmap.begin();
    std::map<u32, Player*>::const_iterator itend = pmap.end();
     
    u32 count = 0;
    msgs2s::MsgGS2DBSavePlaye msg;
    for (it; it!= itend ; ++it)
    {
        Player* pkPlayer = it->second;
        if (pkPlayer)
        {
            msgs2s::DBPlayerData* p = msg.add_players();
            p->set_state(msgs2s::_ON_LINE_);
            const msgs2s::PlayerInfo& info = pkPlayer->getPlayerInfo();
            *(p->mutable_data()) = info;
            ++ count;
           // Mylog::log_player(LOG_DEBUG, "save player [%u]", info.sc_data().guid(), info.sc_data().posx(), info.sc_data().posy());

            if (count > _ONCE_SAVE_PLAYE_COUNT)
            {
                gGSDBClient.sendPBMessage(&msg);
                msg.clear_players();
                count = 0;
            }
        }
    }

    if (msg.players_size() > 0)
    {   gGSDBClient.sendPBMessage(&msg);}

}
void ObjectManager::removePlayer(Player* p)
{
    if (!p)
    {   return ;}

    const msgs2s::PlayerInfo& info = p->getPlayerInfo();
    u32 g =  info.sc_data().guid();
    u32 a = info.ss_data().account();
    savePlayerinfo(info, msgs2s::_OFF_LINE);

    m_AccountMap.eraseData(a);
    if(p != m_PlayerMap.eraseData(g))
    {
        assert(false);
        Mylog::log_server(LOG_ERROR, "player [%u] memory error .......", g);
    }
    Memory::releaseObject<Player>(p);
}