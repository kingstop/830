#include "stdafx.h"
#include "gate_session.h"

GateSession::GateSession(): tcp_session( *net_global::get_io_service() )
{
	_proto_user_ptr = this;
}
GateSession::~GateSession()
{

}
void GateSession::parseGateOnlines(google::protobuf::Message* p, pb_flag_type flag)
{
    msgs2s::MsgGT2LNOnlines* msg = static_cast<msgs2s::MsgGT2LNOnlines*>(p);
    if (msg)
    {
        m_GateInfo.onlines = msg->onlines();
    }
}
void GateSession::parseGateUserPrepar(google::protobuf::Message* p, pb_flag_type flag)
{
    msgs2s::MsgGT2LNPrepar* msg = static_cast<msgs2s::MsgGT2LNPrepar*>(p);
    if (msg)
    {
        u32 account = msg->account();
		gLGGateManager.receiveUserPrepar(account, m_GateInfo.out_ip, m_GateInfo.out_port);
		//Mylog::log_player(LOG_INFO, "gate is wait for player [%u] login", account);
    }
}
void GateSession::parseGateRegister(google::protobuf::Message* p, pb_flag_type flag)
{
	msgs2s::MsgGTRegisterLG* msg = static_cast<msgs2s::MsgGTRegisterLG*>(p);
	if (msg)
	{
        const ::msgs2s::MsgServerRegister& info = msg->gateinfo();
        const ::msgs2s::ServerVersion& v = info.version();
        m_GateInfo.gate_id = info.serverid();
        if (!gLGVersion.checkVersion(v.major(), v.minor(), v.build(), v.appsvn()))
        {
            Mylog::log_server(LOG_ERROR,"register Gate [%u] error, version is too old! ",info.serverid());
            close();
        }
        m_GateInfo.onlines = msg->accounts_size();
		m_GateInfo.out_ip = msg->ip();
		m_GateInfo.out_port = msg->port();
		gLGGateManager.addGate(m_GateInfo.gate_id, this);
		Mylog::log_server(LOG_INFO,"register Gate [%u] ip[%s] port[%u] Onlines [%u]",info.serverid(), m_GateInfo.out_ip.c_str(), m_GateInfo.out_port, m_GateInfo.onlines);

        for (int i = 0; i < msg->accounts_size(); ++i)
        {
            const msgs2s::GTLGData& d = msg->accounts(i);
			Account* p = gLGAccountMgr.getAccount(d.account());
			if (NULL != p)
			{
				assert( p->nGateId == m_GateInfo.gate_id);
				if (p->nGateId != m_GateInfo.gate_id)
				{	gLGGateManager.kickUserFromGate(p);}
			}
			gLGAccountMgr.addAccount(d.account(), d.transid(), m_GateInfo.gate_id);
        }
	}

}
void GateSession::initPBModule()
{
	ProtocMsgBase<GateSession>::registerSDFun(&GateSession::send_message, NULL);
	ProtocMsgBase<GateSession>::registerCBFun(PROTOCO_NAME(msgs2s::MsgGTRegisterLG),    &GateSession::parseGateRegister);
    ProtocMsgBase<GateSession>::registerCBFun(PROTOCO_NAME(msgs2s::MsgGT2LNOnlines),    &GateSession::parseGateOnlines);
    ProtocMsgBase<GateSession>::registerCBFun(PROTOCO_NAME(msgs2s::MsgGT2LNPrepar),     &GateSession::parseGateUserPrepar);
}
void GateSession::proc_message( const message_t& msg )
{
	parsePBMessage(msg.data, msg.len);
}
void GateSession::on_close( const boost::system::error_code& error )
{
	gLGGateManager.removeGate(this);
	tcp_session::on_close(error);
	Mylog::log_server(LOG_INFO, "server gate close");
}