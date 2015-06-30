#ifndef __stdafx_h__
#define __stdafx_h__
#include <time.h>
#include "task_thread_pool.h"
#include "io_service_pool.h"
#include "tcpsession.h"
#include "tcpclient.h"
#include "tcpserver.h"
#include "net_type.h"
#include "my_log.h"
#include "crypt.h"
#include "memory.h"
#include "database.h"
#include "event_table_object.h"
#include "event_manager.h"
#include "server_frame.h"
#include "message/server_define.h"
#include "message/login.pb.h"
#include "message/msg_gate_login.pb.h"
#include "message/msgs2s.pb.h"
#include "protoc_common.h"
#include "version.h"
#include "random.h"
#include "client_manager.h"
enum EventTypes
{
    EVENT_UNK = 0,
    EVENT_ADD_TEST_ACCOUNT,
    EVENT_ROBOT_RAND_MOVE,
    EVENT_ROBOT_RAND_SEND,
    EVENT_RECONN_TEST_ACCOUNT,
};

struct FuTestClient
{
    ClientTest      _client_mgr;
    SRand          _sRand;
};
extern FuTestClient*   gFuTestClient;
#define gCLClientTese  gFuTestClient->_client_mgr
#define gCLRand       gFuTestClient->_sRand

#endif