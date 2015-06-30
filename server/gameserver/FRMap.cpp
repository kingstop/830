#include "stdafx.h"
#include "FRMap.h"
#include "FRWorld.h"
#include "player.h"

FRMap::FRMap(void):_mapInfo(NULL)
{
}


FRMap::~FRMap(void)
{
}

void FRMap::init(mapInfo* info)
{
	_mapInfo = info;
}

u32 FRMap::getMapID()
{
	if (!_mapInfo)
	{
		 Mylog::log_server(LOG_ERROR,"_mapinfo is null,when get mapid");
	}
	
	return _mapInfo->_id;	
}

bool FRMap::removePlayer(Player* p)
{
	bool b = false;
	PLAYERSET::iterator it = _players.find(p);
	if (it != _players.end())
	{
		b = true;
		p->onLeaveScene();
		_players.erase(it);
		//Mylog::log_server(LOG_INFO,"player<%u> leave map<%u>", p->getGuid(), getMapID());
	}

	return b;
}

void FRMap::update(u32 diff)
{
// 	Player* player = NULL;
// 	PLAYERSET::iterator it = _players.begin();
// 	for (; it != _players.end(); ++ it)
// 	{
// 		player = (*it);
// 		player->update(diff);
// 	}
}

bool FRMap::joinPlayer(Player* p)
{
	bool ret = false;
	if (p->getFRMap())
	{
		Mylog::log_server(LOG_ERROR, "player is already in map, when join map");
		return ret;
	}
	
	
	PLAYERSET::iterator it = _players.find(p);

	if (it == _players.end())
	{
		ret = true;
		
		_players.insert(p);
		p->setFRMap(this);
		p->onJoinScene();

		//Mylog::log_server(LOG_INFO,"player<%u> join map<%u>", p->getGuid(), getMapID());
	}

	return ret;
}

int FRMap::getCityId()
{
	int city_id = 0;
	if (_mapInfo)
	{
		city_id = _mapInfo->_city;
	}
	return city_id;
}
int FRMap::getSceneId()
{
	int scene_id = 0;
	if (_mapInfo)
	{
		scene_id = _mapInfo->_scene;
	}
	return scene_id;
}
float FRMap::getMapView()
{
    if (_mapInfo)
    {
        return _mapInfo->_view;
    }

    return 0.f;
    
}