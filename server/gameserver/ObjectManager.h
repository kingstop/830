#ifndef __object_manager_h__
#define __object_manager_h__
class Player;
class Session;
class ObjectManager : public EventableObject
{
public:
    ObjectManager();
    virtual ~ObjectManager();
	Player* getPlayer(u32 guid);
    Player* getPlayerByAccount(account_type a);
	Player* createPlayer(Session* s, const msgs2s::PlayerInfo * p);

    void savePlayerinfo(const msgs2s::PlayerInfo& info, msgs2s::LineState state);
    void saveAllPlayers();
    void removePlayer(Player* p);

    void updateObject(u32 ndiff);
    void logInfo();
public:
	obj_ptr_map<u32, Player> m_PlayerMap;
    obj_map<account_type, u32> m_AccountMap;
};
#endif