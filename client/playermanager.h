#pragma once
#include <map>

class clien_player;
class playermanager
{
public:
	typedef std::map<int, clien_player*> MAPPLAYERS;
public:
	playermanager(int beginplayer, int endplayer, const char* ip, int port);
	virtual ~playermanager(void);
	bool create();
	bool process();



public:
	int _player_begin;
	int _player_end;
	MAPPLAYERS _players;
	std::string _server_ip;
	int	_port;	

};

