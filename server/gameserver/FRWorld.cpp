#include "stdafx.h"
#include "FRWorld.h"
#include "LocationVector.h"
#include "player.h"

FRWorld::FRWorld()
{
	_seen_range = 100.f;
}
FRWorld::~FRWorld()
{

}
mapInfo* FRWorld::getMapInfo(u32 city, u32 sceneID)
{
    const std::map<u32, mapInfo*>& infomap = _infos.getDataMap();
	std::map<u32, mapInfo*>::const_iterator it = infomap.begin();
	std::map<u32, mapInfo*>::const_iterator itend = infomap.end();
	for (it; it != itend; ++it)
	{
		mapInfo*p = it->second ;
		if (p && p->_city == city && p->_scene == sceneID)
		{	return p;}
	}
    return NULL;
}
mapInfo* FRWorld::getMapInfo(u32 id)
{
    return _infos.getData(id);
}
void FRWorld::addMapInfo(mapInfo* p)
{
	_infos.addData(p->_id, p);
	//如果是在本服上的城市，创建地图
	//if (isRunCity(p->_city))
	{
		FRMap*  pMap = new FRMap();
		if (pMap)
		{	
			pMap->init(p);
			_maps.addData(pMap->getMapID(), pMap);
			Mylog::log_server(LOG_INFO, "Init FMAP [%u], data city:[%u], scene:[%u]", p->_id, p->_city, p->_scene);
		}
	}
}
void FRWorld::update(u32 difftime)
{
	if (difftime == 0)
	{
		return;
	}
	FRMap* tempMap = NULL;
	std::map<u32, FRMap*>::const_iterator it = _maps.getDataMap().begin(); 
	for (; it != _maps.getDataMap().end(); ++ it)
	{
		tempMap = it->second;
		tempMap->update(difftime);
	}
	
}

bool FRWorld::isHaveMap(u32 id)
{
	return _maps.getData(id) != NULL ;
}

u32 FRWorld::getFRMapID(u32 cityID, u32 sceneID)
{
	if (INVALID_CITY_ID == cityID || INVALID_SCENE_ID == sceneID)
	{	return INVALID_MAP_ID;}

	const std::map<u32, mapInfo*>& infomap = _infos.getDataMap();
	std::map<u32, mapInfo*>::const_iterator it = infomap.begin();
	std::map<u32, mapInfo*>::const_iterator itend = infomap.end();

	for (it; it != itend; ++it)
	{
		mapInfo*p = it->second ;
		if (p && p->_city == cityID && p->_scene == sceneID)
		{	return p->_id;}
	}

	return INVALID_MAP_ID;
}
FRMap* FRWorld::getMap(u32 mapId)
{
	return _maps.getData(mapId);
}
FRMap* FRWorld::getMap(u32 cityID, u32 sceneID)
{
	u32 mapid = getFRMapID(cityID,  sceneID);
	if (INVALID_MAP_ID != mapid)
	{	return getMap(mapid);}

	return NULL;
}

bool FRWorld::joinScene(Player* p, u32 cityID, u32 sceneID, float posX, float posY, float dir)
{
	FRMap* targetmap =  getMap(cityID, sceneID);
	if (targetmap)
	{
		p->setPosition(posX, posY, dir);
		targetmap->joinPlayer(p);
		//Mylog::log_server(LOG_DEBUG, "player[%u] enter city<%d> scene<%d> ", p->getGuid(), cityID, sceneID);
		return true;
	}else
	{
		Mylog::log_server(LOG_ERROR, "city id<%d> scene id<%d> can not find mapid", cityID, sceneID);
		return false;
	}
}

