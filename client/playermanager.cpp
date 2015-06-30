#include "stdafx.h"
#include "playermanager.h"
#include "clien_player.h"

playermanager::playermanager(int beginplayer, int endplayer, const char* ip, int port)
{
	_player_begin = beginplayer;
	_player_end = endplayer;
	_server_ip = ip;
	_port = port;
}


playermanager::~playermanager(void)
{
}

bool playermanager::create()
{
	char sztemp[128];
	for (int i = _player_begin; i < _player_end; i ++)
	{
		sprintf(sztemp,"test%d",i);
		clien_player* player = new clien_player();
		player->set_accid(sztemp);
		player->connect(_server_ip.c_str(), _port);

		_players.insert(MAPPLAYERS::value_type(i, player));
	}

	return true;
}

bool playermanager::process()
{
	MAPPLAYERS::iterator it = _players.begin();
	for (; it != _players.end(); ++ it)
	{
		clien_player* player = it->second;
		player->run_no_wait();
	}

	return true;
}