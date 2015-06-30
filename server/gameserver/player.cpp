#include "stdafx.h"
#include "player.h"
#include "session.h"
#include "FRWorld.h"
#include "FRMap.h"
#include "message/map.pb.h"
Player::Player(Session* p, const msgs2s::PlayerInfo* info)
    :m_pkSession(p), m_playerInfo(*info), _map(NULL), _is_move(false)
{
    onCheckNewPlayer();
	_last_update_range_time =  boost::posix_time::microsec_clock::universal_time();
}
Player::~Player()
{
    m_pkSession = NULL;
}
void Player::onCheckNewPlayer()
{
    //新建立的玩家需要初始化城市，地图以及坐标。出生点
    // 标识检查是否是新建立的玩家

    msgs2s::PlayerSSData* p = m_playerInfo.mutable_ss_data();
    const msgs2s::PlayerSCData& scd = m_playerInfo.sc_data();
    u32 flag = p->flag();
    if (CheckFlag::hasFlag(flag, _PLAYER_INFO_FLAG_INIT_MAP_POS_))
    {
        //这里需要初始化
       CheckFlag::addFlag(flag, _PLAYER_INFO_FLAG_INIT_MAP_POS_);
       p->set_flag(flag);
       setPosition(100.f, 100.f, 10.f);
       Mylog::log_player(LOG_ERROR, "Init Player Create Data");
    }

    changeScene(scd.city(), scd.mapid(), scd.posx(),scd.posy(),scd.dir());
}
void Player::setReconnet(Session* pksession)
{
    if (pksession != m_pkSession)
    {
        Mylog::log_player(LOG_ERROR, "player [%u], old session[%u], new [%u] quit game", m_playerInfo.sc_data().guid(), m_pkSession->getTranId(), pksession->getTranId());
        assert(false);
    }
    
    m_pkSession = pksession;
}
void Player::makeClientCharInfo(CharInfo* p)
{
    const msgs2s::PlayerSCData& scd = m_playerInfo.sc_data();
    const msgs2s::PlayerSSData& ssd = m_playerInfo.ss_data();
    p->set_charid(scd.guid());
    p->set_user_account(ssd.account());
    p->set_name(scd.name());
    p->set_head(scd.head());
    p->set_sex(scd.sex());
    p->set_chartype((enumCharType)scd.type());
}

void Player::makeMapCharInfo(MapCharInfo* p)
{
	if (p)
	{
		p->set_dir(_position.o);
		p->set_x(_position.x);
		p->set_y(_position.y);
		if (_is_move)
		{
			p->set_state(CharState_Move);
		}
		else
		{
			p->set_state(CharState_Stop);
		}
		
		CharInfo* info = p->mutable_charinfo();
		makeClientCharInfo(info);

	}
}
void Player::quitGame()
{
	leaveScene();
    //Mylog::log_player(LOG_INFO, "player guid[%u] name[%s], quit game", m_playerInfo.sc_data().guid(), getName());
    gGSObjectMgr.removePlayer(this);
	
}


void Player::changeScene(u32 cityID, u32 sceneID, float posX, float posY, float dir)
{
	leaveScene();
	if(gGSWorld.isRunCity(cityID))
	{
		if (gGSWorld.joinScene(this, cityID, sceneID, posX, posY, dir))
		{
			::msgs2s::PlayerSCData* psc = m_playerInfo.mutable_sc_data();
			psc->set_city(cityID);
			psc->set_mapid(sceneID);
		}else
		{
			// log error ...
		}
	}else
	{
		//切服务， 这个城市不在这个服务器
		//必须锁定数据
		::msgs2s::PlayerSCData* psc = m_playerInfo.mutable_sc_data();
		_is_move = false;
		_speed = 0.f;
		psc->set_city(cityID);
		psc->set_mapid(sceneID);
		psc->set_posx(posX);
		psc->set_posy(posY);
		psc->set_dir(dir);
		msgs2s::MsgGS2DBChangeServer msg;
		msg.set_city(cityID);
		gGSDBClient.sendPBMessage(&msg, m_pkSession->getTranId());
	}
	
}

void Player::moveMsgRequired(clientmsg::CharMove* msg)
{
    if (msg)
    {
        setPosition(msg->x(), msg->y(), msg->dir());
        _speed = msg->speed();
        _is_move = msg->state() == 2; // 1 stop 2 move
        msg->set_charid(getGuid());
        msg->set_timestamp(gGSServerTime);
        sendMsgToAll(msg);
       // Mylog::log_server(LOG_DEBUG, "player [%u] move msg x:%f y:%f dir:%f",getGuid(), msg->x(), msg->y(), msg->dir()); 
    }
}


void Player::update(u32 diff)
{
	updateMove(diff);
}

void Player::updateMove(u32 diff)
{
	if (_is_move && _map)
	{
		float dist = diff * _speed / _TIME_SECOND_MSEL_;
		if (dist < 0.0001f)
		{
			return;
		}
		float x = dist * cosf(_position.o);
		float y = dist * sinf(_position.o);

		_position.x += x;
		_position.y += y;


		::msgs2s::PlayerSCData* psc = m_playerInfo.mutable_sc_data();
		psc->set_posx(x);
		psc->set_posy(y);

		boost::posix_time::ptime current =  boost::posix_time::microsec_clock::universal_time();
		boost::posix_time::millisec_posix_time_system_config::time_duration_type time_elapse;
		time_elapse = current - _last_update_range_time;
		if (time_elapse.total_seconds() > 5)
		{
			_last_update_range_time = current;
			onPlayerUpdateSeen();
		}
	}
}

void Player::leaveScene()
{
	if (_map)
	{
		_map->removePlayer(this);
		_map = NULL;
		_is_move = false;
		clientmsg::PlayerLeaveScene msg;
		sendMsg(&msg);
	}
}

void Player::onJoinScene()
{
	if (_map)
	{
		clientmsg::MapScreenRefreshCharacter refreshmsg;
		MapCharInfo* selfmapinfo = refreshmsg.mutable_mapinfo();

		makeMapCharInfo(selfmapinfo);
		refreshmsg.set_cityid(_map->getCityId());
		refreshmsg.set_mapid(_map->getSceneId());
		sendMsg(&refreshmsg);
		Player* target = NULL;
		clientmsg::NineScreenRefreshPlayer msg;
   
		PLAYERSET::iterator it = _map->getPlayerBegin();
		for (; it != _map->getPlayerEnd(); ++ it)
		{
			target = (*it);
			if (target == this)
			{
				continue;
			}
			LocationVector targetpos = target->getPosition();
			if (isInRange(target))
			{
				MapCharInfo* mapCharInfo = msg.add_users();
				target->makeMapCharInfo(mapCharInfo);
				_range_players.insert(target);
				if (target->playerJoinRange(this))
				{
				}
			}
		}

		sendMsg(&msg);
	}
}

void Player::onLeaveScene()
{
	Player* p = NULL;
	PLAYERSET::iterator it = _range_players.begin();
	for (; it != _range_players.end(); ++ it)
	{
		p = (*it);
        if (p!=this)
        {
            p->removePlayerFromRange(this);
        }
	}
	_range_players.clear();
}

void Player::setPosition(float x, float y, float dir)
{
	_position.x = x;
	_position.y = y;
	_position.o = dir;

	::msgs2s::PlayerSCData* psc = m_playerInfo.mutable_sc_data();
	psc->set_posx(x);
	psc->set_posy(y);
	psc->set_dir(dir); 
}

bool Player::isInRange(Player* p)
{
    if (_map)
    {
        LocationVector targetPos = p->getPosition();
        if (targetPos.Distance2D(_position) <= _map->getMapView())
        {
            return true;
        }
    }
	
	return false;
}

void Player::onPlayerLeaveRange(Player* p)
{
	clientmsg::MapRemoveChar msg;
	msg.add_users(p->getGuid());
	sendMsg(&msg);

	//Mylog::log_server(LOG_INFO,"player<%llu> leave player<%llu> range", p->getGuid(),getGuid());
}

void Player::onPlayerJoinRange(Player* p)
{
	clientmsg::PlayerJoinRange msg;
	MapCharInfo* infomap = msg.mutable__joinuser();
	p->makeMapCharInfo(infomap);
	sendMsg(&msg);
	//Mylog::log_server(LOG_INFO,"player<%llu> join player<%llu> range", p->getGuid(),getGuid());
}

bool Player::playerJoinRange(Player* p)
{
	bool ret = false;
	PLAYERSET::iterator it = _range_players.find(p);
	if (it == _range_players.end())
	{
		_range_players.insert(p);
		onPlayerJoinRange(p);
		ret = true;
	}
	return ret;
}

bool Player::removePlayerFromRange(Player* p)
{
	bool ret = false;
	PLAYERSET::iterator it = _range_players.find(p);
	if (it != _range_players.end())
	{
		onPlayerLeaveRange(p);
		_range_players.erase(it);
		ret = true;
	}
	return ret;
}

void Player::sendMsgToAll(google::protobuf::Message* p, bool sendself)
{
	Player* target = NULL;
	PLAYERSET::iterator it = _range_players.begin();
	for (; it != _range_players.end(); ++ it)
	{
		target = (*it);
		target->sendMsg(p);
	}
}

void Player::sendMsg(google::protobuf::Message* p)
{
	if (m_pkSession)
	{
		m_pkSession->sendPBMessage(p);
	}
}

void Player::onPlayerUpdateSeen()
{
	Player* player_target;
	PLAYERSET::const_iterator it = _map->getPlayerBegin();
	PLAYERSET::const_iterator itend = _map->getPlayerEnd();
	for (; it != itend; ++ it)
	{
		player_target = (*it);
		if (player_target == this)
		{
			continue;
		}
		if (isInRange(player_target))
		{
			player_target->playerJoinRange(this);
			playerJoinRange(player_target);
		}
		else
		{
			player_target->removePlayerFromRange(this);
			removePlayerFromRange(player_target);
		}

	}

}