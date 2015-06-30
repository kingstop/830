#include "stdafx.h"
#include "clien_player.h"
#include "tcpclient.h"
#include "message/login.pb.h"
#include "message/common.pb.h"
#include "message/map.pb.h"


clien_player::clien_player(void) :tcp_client( *net_global::get_io_service() )
{
	_proto_user_ptr = this;
	_password = "123456";
	_is_connect_login = true;
	ProtocMsgBase<clien_player>::registerSDFun(&clien_player::send_message, NULL);
	ProtocMsgBase<clien_player>::registerCBFun(PROTOCO_NAME(clientmsg::LoginResponse),  &clien_player::parseLoginGameRespone);
	ProtocMsgBase<clien_player>::registerCBFun(PROTOCO_NAME(clientmsg::ClientInit), &clien_player::parsClientinit);
	ProtocMsgBase<clien_player>::registerCBFun(PROTOCO_NAME(clientmsg::MapScreenRefreshCharacter), &clien_player::parseReflashcharacter);
	ProtocMsgBase<clien_player>::registerCBFun(PROTOCO_NAME(clientmsg::NineScreenRefreshPlayer),&clien_player::parseReflashplayers);
	_connect_gate_server = false;
}


clien_player::~clien_player(void)
{
}

void clien_player::on_connect()
{
	
	tcp_client::on_connect();
	if (_is_connect_login)
	{
		clientmsg::LoginRequest msg;
		msg.set_name(_accid.c_str());
		msg.set_pwd(_password.c_str());
		sendPBMessage(&msg);
		Mylog::log_player(LOG_INFO, "clien_player login request msg account<%s> password<%s>", _accid.c_str(), _password.c_str());
	}
	else
	{
		clientmsg::LoginGame msg;
		msg.set_user_account(_account);
		sendPBMessage(&msg);
		Mylog::log_player(LOG_INFO, "clien_player login game msg useraccount<%lu> account<%s> password<%s>",_account,
			_accid.c_str(), _password.c_str());
	}
	
}
void clien_player::on_close( const boost::system::error_code& error )
{
	tcp_client::on_close(error);
	Mylog::log_player(LOG_INFO, "clien_player close");
	if (_is_connect_login == false && _connect_gate_server)
	{
		connect(_gate_ip.c_str(), _gate_port);
		Mylog::log_player(LOG_INFO, "player connect gate ip<%s> port<%d> useraccount<%lu>",
			_gate_ip.c_str(), _gate_port, _account);
	}
}
void clien_player::on_connect_failed( boost::system::error_code error )
{

	Mylog::log_player(LOG_INFO, "on_connect_failed");
	//tcp_client::on_connect_failed(error);
}
void clien_player::proc_message( const message_t& msg )
{
	parsePBMessage(msg.data, msg.len);
}

void clien_player::parsClientinit(google::protobuf::Message* p, pb_flag_type flag)
{
	clientmsg::ClientInit* msg = (clientmsg::ClientInit*) p;
	_charid = msg->charinfo().charid();
	Mylog::log_player(LOG_INFO, "receive clien init msg", msg->charinfo().charid());
	

}
void clien_player::parseReflashcharacter(google::protobuf::Message* p, pb_flag_type flag)
{
	clientmsg::MapScreenRefreshCharacter* msg = (clientmsg::MapScreenRefreshCharacter*)p;
	Mylog::log_player(LOG_INFO, "receive MapScreenRefreshCharacter msg");

}
void clien_player::parseReflashplayers(google::protobuf::Message* p, pb_flag_type flag)
{
	clientmsg::NineScreenRefreshPlayer* msg = (clientmsg::NineScreenRefreshPlayer *) p;
	Mylog::log_player(LOG_INFO, "receive NineScreenRefreshPlayer msg");
}

void clien_player::parseLoginGameRespone(google::protobuf::Message* p, pb_flag_type flag)
{
	clientmsg::LoginResponse* msg = (clientmsg::LoginResponse*)(p);
	switch(msg->result())
	{
	case clientmsg::enumLoginResult_Success:
		{
			_gate_ip = msg->gate_ip();
			_gate_port = msg->gate_port();
			_account = msg->user_account();
			Mylog::log_player(LOG_INFO, "player receive gate ip<%s> port<%d> useraccount<%lu>", _gate_ip.c_str(), _gate_port, _account);
			close();
			_is_connect_login = false;
			_connect_gate_server = true;
			
		}
		break;
	case clientmsg::enumLoginResult_Fail:
	case clientmsg::enumLoginResult_NameFail:
	case clientmsg::enumLoginResult_PwdFail:
	case clientmsg::enumLoginResult_HaveLogin:
		{
			Mylog::log_player(LOG_INFO, "player login failed  error code is <%d>",msg->result() );
		}
	};

}
