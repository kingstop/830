#include "stdafx.h"
#include "message/msg_gate_login.pb.h"
#include "session.h"
GameDBClient::GameDBClient():tcp_client( *net_global::get_io_service() )
{
	_proto_user_ptr = this;
	m_isreconnect = true;
}
GameDBClient::~GameDBClient()
{

}
void GameDBClient::parseDBMsgDefault(google::protobuf::Message* p, pb_flag_type flag)
{
    // GameDBClient 除了在注册函数列表外， 默认转发DB过来的消息到对应的客户端
    if (flag != INVALID_TRANS_ID)
    {
        Session* pkSession = gGSGateManager.getUser(flag);
        if (p && pkSession)
        {
            pkSession->sendPBMessage(p);
        }
    }
}
void GameDBClient::parseQueryChar(google::protobuf::Message* p, pb_flag_type flag)
{
    msgs2s::MsgDB2GSQueryCharResult* msg = static_cast<msgs2s::MsgDB2GSQueryCharResult*>(p);
    Session* pkSession = gGSGateManager.getUser(flag);
    if (msg && pkSession)
    {
        pkSession->queryDBPlayerInfoCall(msg);
    }else
    {
        Mylog::log_server(LOG_ERROR, "parse error MsgDB2GSQueryCharResult msg");
    }
}
void GameDBClient::initPBModule()
{
	ProtocMsgBase<GameDBClient>::registerSDFun(&GameDBClient::send_message, &GameDBClient::parseDBMsgDefault);
    ProtocMsgBase<GameDBClient>::registerCBFun(PROTOCO_NAME(msgs2s::MsgDB2GSQueryCharResult),   &GameDBClient::parseQueryChar);
    //ProtocMsgBase<GameDBClient>::registerCBFun(PROTOCO_NAME(msgs2s::MsgGT2GSAddUser),       &GameDBClient::parseAddUser);
    //ProtocMsgBase<GameDBClient>::registerCBFun(PROTOCO_NAME(msgs2s::MsgGT2GSRemoveUser),    &GameDBClient::parseRemoveUser);
}
void GameDBClient::on_close( const boost::system::error_code& error )
{
	tcp_session::on_close( error );
	Mylog::log_server(LOG_INFO, "DB server close");
}

void GameDBClient::on_connect()
{
	tcp_client::on_connect();
	Mylog::log_server(LOG_INFO, "connect db server success!");
    const service_config& conf = gGameServer.getServiceConf();
    msgs2s::MsgServerRegister msg;
    msg.set_serverid(conf.id);
    msgs2s::ServerVersion* p2 = msg.mutable_version();
    p2->set_major(gGSVersion.nMajor);
    p2->set_minor(gGSVersion.nMinor);
    p2->set_build(gGSVersion.nBuild);
    p2->set_appsvn(gGSVersion.nAppSvn);
    sendPBMessage(&msg);
}
void GameDBClient::on_connect_failed( boost::system::error_code error )
{
	 Mylog::log_server(LOG_ERROR, "connect DBServer ip:[%s] failed!", get_remote_address_string().c_str());
}
void GameDBClient::proc_message( const message_t& msg )
{
	parsePBMessage(msg.data, msg.len);
}