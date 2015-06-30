#ifndef FRWORLD_H
#define FRWORLD_H
#include "LocationVector.h"
#include "FRMap.h"


struct maprect
{
	maprect():top(0),bottom(0),left(0),right(0)
	{

	}
	int top;
	int bottom;
	int left;
	int right;
};
struct mapInfo
{
	mapInfo()
	{
		_id = INVALID_MAP_ID;
		_city = INVALID_CITY_ID;
		_scene = INVALID_SCENE_ID;
        _view = 0.f;
	}
	u32 _id;
	u32 _city;
	u32 _scene;
    float _view;
	LocationVector _transportPosition;
	maprect _mapRect;
};
class FRMap;
typedef std::map<u32,FRMap*> MAP_FRENMAP;
typedef std::map<u32,mapInfo*> MAP_MAPINFO;
class FRWorld : public EventableObject
{
public:
	FRWorld();
	virtual ~FRWorld();
public:
	void update(u32 difftime);
	bool isHaveMap(u32 id);
	bool joinScene(Player* p, u32 cityID, u32 sceneID, float posX, float posY, float dir);
    u32  getFRMapID(u32 cityID, u32 sceneID);
    FRMap* getMap(u32 mapId);
    FRMap* getMap(u32 cityID, u32 sceneID);
    float getSeenRange(){return _seen_range;}
	bool isRunCity(u32 city){return _runCitys.find(city) != _runCitys.end() ;}
	void addRunCity(u32 city){ _runCitys.insert(city);}
	void addMapInfo(mapInfo* p);
    mapInfo* getMapInfo(u32 city, u32 sceneID);
    mapInfo* getMapInfo(u32 id);
protected:
	obj_ptr_map<u32, FRMap> _maps;
	obj_ptr_map<u32, mapInfo> _infos;
	std::set<u32> _runCitys;
	float		_seen_range;
};


#endif