#ifndef FRENMAP_H
#define FRENMAP_H
struct mapInfo;

class Player;
typedef std::set<Player*> PLAYERSET;
class FRMap
{
public:
	FRMap(void);
	~FRMap(void);
public:
	void init(mapInfo* info);
	bool removePlayer(Player* p);
	bool joinPlayer(Player* p);
	void update(u32 diff);

	u32 getMapID();
	int getCityId();
	int getSceneId();
    float getMapView();
public:
	PLAYERSET::const_iterator getPlayerBegin(){ return _players.begin();}
	PLAYERSET::const_iterator getPlayerEnd(){return _players.end();}

    
	
protected:
	PLAYERSET _players;
	mapInfo* _mapInfo;


};
#endif