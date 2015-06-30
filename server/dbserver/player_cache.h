#ifndef __player_cache_h__
#define __player_cache_h__

/************************************************************************/
/*  玩家数据的内存  Cache , 只保存登录过的玩家.                         */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/************************************************************************/

struct PlayerData
{
    PlayerData(msgs2s::PlayerInfo* d, u16 g):gs(g)
    {
        p = new msgs2s::PlayerInfo(*d);
        if (p)
        {
            guid = p->sc_data().guid();
            account = p->ss_data().account();
        }else
        {
            assert(false);
        }
    }
    ~PlayerData()
    {
        if (p)
        {
            delete p;
        }
    }

    msgs2s::PlayerInfo* p;
    u16 gs;
    account_type account;
    u32 guid;
};
class PlayerCache 
{
public:
    PlayerCache();
    ~PlayerCache();

    PlayerData* addCacheData( msgs2s::PlayerInfo* p, u16 gs);
    PlayerData* getCacheData(account_type a);
    bool hasUserName(const std::string& str) const {return m_NameCache.find(str)!= m_NameCache.end();}

	void removeOnline(tran_id_type t){ m_onlineGuid.eraseData(t);}
	void addOnline(tran_id_type t, u32 guid){ m_onlineGuid.addData(t, guid);}
	u32 getGuid(tran_id_type t);
	bool getTransAndgs(u32 guid, tran_id_type& t, u16& gs);
	PlayerData*  getCacheDataByTrans(tran_id_type t);
protected:
    obj_ptr_map<account_type, PlayerData> m_PlayerCache;	// key account
	obj_ptr_map<u32, PlayerData> m_GuidPlayers;				// key guid 
    obj_map<tran_id_type, u32> m_onlineGuid;				// 动态ID 和玩家GUID对应表
    std::set<std::string> m_NameCache;
    
private:
};
#endif