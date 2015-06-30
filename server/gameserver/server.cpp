#include "stdafx.h"
#include "FRWorld.h"
GameServer::GameServer()
    :m_EventHold(WORLD_INSTANCE)
{

}
bool GameServer::init()
{
    ServerFrame::init();
    DataBaseConfig dbconfig;
    if (!ServerFrame::loadDBConfig(dbconfig, CENTER_DATABASE_CONFIG))
    {
        Mylog::log_server( LOG_ERROR, "load database config failed !");
        return false;
    }
   
    if (!Database::addBlockTask(dbconfig, this, &GameServer::initDataFromDatabase, NULL))
    {
        Mylog::log_server( LOG_ERROR, "Init Server from DataBase Error!");
        return false;
    }

    Mylog::log_server( LOG_INFO, "Start Game Server v:[%u] Success!", gGSVersion.toString().c_str());
    return true;
}

bool GameServer::onKey()
{
    return true;
}

void GameServer::runOnce(u32 nDiff)
{
    net_global::update_net_service();
	gGSServerTime = time(NULL);
    gGSGateServer.run_no_wait();
    gGSDBClient.run_no_wait();
    gGSObjectMgr.updateObject(nDiff);
    m_EventHold.update(nDiff);
	gGSWorld.update(nDiff);

    static u32 curtime = 0;
    curtime += nDiff;
    if (curtime > 15000)
    {
        gGSObjectMgr.logInfo();
        curtime = 0;
    }
    
    if (nDiff > 800)
    {
        Mylog::log_server(LOG_WARNING, "server delay [%u]", nDiff);
    }
	
}
void GameServer::shutDown()
{
    gGSDBClient.close();
    gGSGateServer.stop();
}

void GameServer::memoryLog() 
{

}
void GameServer::setStop()
{

}
void GameServer::checkStop()
{

}
bool GameServer::initDataFromDatabase(DBQuery* p, const void* data)
{
	if (!p)
	{ return false;}

 	net_info user_net;
 	DBQuery& query = *p;
 	DBQParms parms;
 
 	parms << _GAME_LISTEN_GATE_;
	parms << m_service_conf.id;
 	query << "SELECT * FROM `net_config` WHERE `Category` = %0 AND `ServerId` = %1";
 	query.parse();
 
 	if (!ServerFrame::getNetConfig(user_net, query.use(parms)))
 	{ 
 		Mylog::log_server( LOG_ERROR, "Init game server net config failed !");
 		return false;
 	}
 
 	if(!gGSGateServer.create( user_net._port, user_net._max_connect, user_net._thread_count))
 	{
 		Mylog::log_server( LOG_ERROR, "game Init NetConfig failed!");
 		return false;
 	}
 	
 	Mylog::log_server( LOG_INFO, "ListenGate begin lister port[%d], MaxConnect[%d], ThreadCount[%d]!", user_net._port, user_net._max_connect, user_net._thread_count);
 	
	parms.clear();
	query.reset();
	parms <<  m_service_conf.id;
	query << "SELECT * FROM `server_city_config` WHERE `serverid` = %0";
	query.parse();

	const SDBResult result = query.store(parms);
	for (u16 i = 0 ; i < result.num_rows(); ++i)
	{
		DBRow row = result[i];
		u8 city = row["city"];
		gGSWorld.addRunCity(city);
		Mylog::log_server( LOG_INFO, "game server add city:[%u] !", city);
	}

 	parms.clear();
 	query.reset();
 	parms << _DB_LISNEN_GAME_;
 	query << "SELECT * FROM `net_config` WHERE `Category` = %0";
 	query.parse();
 
 	if (!ServerFrame::getNetConfig(user_net, query.use(parms)))
 	{ 
 		Mylog::log_server( LOG_ERROR, "Init gate server net config failed !");
 		return false;
 	}
 	gGSDBClient.connect(user_net._ip.c_str(), user_net._port);

 	Mylog::log_server( LOG_INFO, "connect db  port[%d], ip[%s]!", user_net._port, user_net._ip.c_str());

	parms.clear();
	query.reset();

	parms << _FU_WORLD_DATABASE_;
	query << "SELECT * FROM `database_config` WHERE `Category` = %0";
	query.parse();

	if (!ServerFrame::getDatabaseConfig(m_world_db_conf, query.store(parms)))
	{ 
		Mylog::log_server( LOG_ERROR, "load world db config failed !");
		return false;
	}

	if (!Database::addBlockTask(m_world_db_conf, this, &GameServer::initDataFromWorldDB, NULL))
	{
		Mylog::log_server( LOG_ERROR, "Init Server from DataBase Error!");
		return false;
	}
    return true;
}
bool GameServer::initDataFromWorldDB(DBQuery* p, const void* data)
{
	if (!p)
	{ return false;}

	DBQuery& query = *p;
	query << "select `mapId`, `city`, `sceneid`,`top`, `bottom`, `left`, `right`, `center_x`, `center_y`,`view` from city_config left join map_config on city_config.scene = map_config.sceneid";
	query.parse();
	const SDBResult result = query.store();
	for (u16 i = 0 ; i < result.num_rows(); ++i)
	{
		DBRow row = result[i];
		mapInfo* pinfo = new mapInfo;
		if (!pinfo)
		{	return false;}

		pinfo->_id					= row["mapId"];
		pinfo->_city				= row["city"];
		pinfo->_scene				= row["sceneid"];
		pinfo->_mapRect.top			= row["top"];
		pinfo->_mapRect.bottom		= row["bottom"];
		pinfo->_mapRect.left		= row["left"];
		pinfo->_mapRect.right		= row["right"];
		pinfo->_transportPosition.x = row["center_x"];
		pinfo->_transportPosition.x = row["center_y"];
        pinfo->_view              = row["view"]; 
		gGSWorld.addMapInfo(pinfo);
		Mylog::log_server( LOG_INFO, "world add map:[%u] city:[%u] scene[%u] !", pinfo->_id, pinfo->_city, pinfo->_scene);
	}

	return true;
}
