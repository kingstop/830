#ifndef __player_h__
#define __player_h__
#include "LocationVector.h"
#include "FRMap.h"
/************************************************************************/
/*                                                                      */
/* 服务器和客户端共用数据定义                                           */
/*message PlayerSCData                                                  */
/*{                                                                     */
/*    required uint32 guid = 1;                                         */
/*    required string name = 2;                                         */
/*    required uint32 type = 3;                                         */
/*    required uint32 sex = 4;                                          */
/*    required uint32 mapid = 5;                                        */
/*    required int32  posx = 6;                                         */
/*    required int32  posy = 7;                                         */
/*    required uint32 dir = 8;                                          */
/*    required uint32 city = 9;                                         */
/*    required uint32 head = 10;                                        */
/*}                                                                     */
/* 服务器内部数据定义                                                   */
/*message PlayerSSData                                                  */
/*{                                                                     */
/*    required uint32 account = 1;                                      */
/*    required uint32 flag = 2;                                         */
/*    required uint32 createtime = 3;                                   */
/*}                                                                     */
/*                                                                      */
/*message PlayerInfo                                                    */
/*{                                                                     */
/*    required PlayerSCData  sc_data = 1;                               */
/*    required PlayerSSData  ss_data = 2;                               */
/*}                                                                     */
/************************************************************************/

class FRMap;
class Player : PUBLIC_BASE_OBJECT(Player) ,public EventableObject
{
	REGISTER_POOL_INFO(Player, 100, 0)
public:
	Player(Session* p, const msgs2s::PlayerInfo* info);
	virtual ~Player();

    const msgs2s::PlayerInfo& getPlayerInfo(){return m_playerInfo;}
	void setReconnet(Session* pksession);
    void onCheckNewPlayer();
    void makeClientCharInfo(CharInfo* p);
	void makeMapCharInfo(MapCharInfo* p);
    void quitGame();
	void changeScene(u32 cityID, u32 sceneID, float posX, float posY, float dir);
	void moveMsgRequired(clientmsg::CharMove* msg);
	void updateMove(u32 diff);
	void update(u32 diff);
	void onPlayerUpdateSeen();
	bool removePlayerFromRange(Player* p);
	bool playerJoinRange(Player* p);
	bool isInRange(Player* p);
	void leaveScene();
	void onLeaveScene();
	void onJoinScene();
	void onPlayerJoinRange(Player* p);
	void onPlayerLeaveRange(Player* p);
	void setFRMap(FRMap* p){_map = p;}
	FRMap* getFRMap(){return _map;}
	void setPosition(float x, float y, float dir);
	LocationVector getPosition(){return _position;}

	void sendMsgToAll(google::protobuf::Message* p, bool sendself = false);
	void sendMsg(google::protobuf::Message* p);
	u32 getGuid() const {return m_playerInfo.sc_data().guid();}
    u32 getAccount() const {return m_playerInfo.ss_data().account();}
	const char* getName() {return m_playerInfo.sc_data().name().c_str();}
	
protected:
    msgs2s::PlayerInfo m_playerInfo;
    Session* m_pkSession;
	LocationVector _position;
	FRMap* _map; 	
	PLAYERSET _range_players;
	float _speed;
	bool _is_move;

	boost::posix_time::ptime _last_update_range_time;
	
	
private:
};
#endif