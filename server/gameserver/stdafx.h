#ifndef __stdafx_h__
#define __stdafx_h__
#include <time.h>
#include "task_thread_pool.h"
#include "io_service_pool.h"
#include "tcpsession.h"
#include "tcpclient.h"
#include "tcpserver.h"
#include "net_type.h"
#include "crypt.h"
#include "memory.h"
#include "database.h"
#include "server_frame.h"
#include "protoc_common.h"
#include "version.h"
#include "event_table_object.h"
#include "event_manager.h"
#include "message/common.pb.h"
#include "message/login.pb.h"
#include "message/server_define.h"
#include "message/msgs2s.pb.h"
#include "message/msg_gate_game.pb.h"
#include "message/msg_game_db.pb.h"
#include "server.h"
#include "gate_manager.h"
#include "gate_tcp_server.h"
#include "db_client.h"
#include "ObjectManager.h"
#include "FRWorld.h"
enum EventTypes
{
    EVENT_UNK = 0,
    EVENT_SAVE_PLAYER_DATA_,
};

struct FuGameFather
{
    FuGameFather():sSystemTime(time(NULL))
    {

    }

    time_t          sSystemTime;
    Version         sVersion;
    GameServer      sGameServer;
    GateManager     sGateManager;
    GateTcpServer   sGateTcpServer;
    GameDBClient    sGameConnDB;
    ObjectManager   sGSObjectMgr;
	FRWorld			sWorld;
};

extern FuGameFather* gFuGameFather;
#define gGSVersion			gFuGameFather->sVersion
#define gGSServerTime		gFuGameFather->sSystemTime
#define gGameServer			gFuGameFather->sGameServer
#define gGSGateManager		gFuGameFather->sGateManager
#define gGSDBClient			gFuGameFather->sGameConnDB
#define gGSGateServer		gFuGameFather->sGateTcpServer
#define gGSObjectMgr        gFuGameFather->sGSObjectMgr
#define gGSWorld			gFuGameFather->sWorld
#endif