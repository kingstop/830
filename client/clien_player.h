#pragma once
#include "tcpclient.h"
class clien_player : public tcp_client, public ProtocMsgBase<clien_player>
{
public:
	clien_player( );
	virtual ~clien_player(void);

	virtual void on_connect();
	virtual void on_close( const boost::system::error_code& error );
	virtual void on_connect_failed( boost::system::error_code error );
	virtual void proc_message( const message_t& msg );
	void parsClientinit(google::protobuf::Message* p, pb_flag_type flag);
	void parseReflashcharacter(google::protobuf::Message* p, pb_flag_type flag);
	void parseReflashplayers(google::protobuf::Message* p, pb_flag_type flag);
	void parseLoginGameRespone(google::protobuf::Message* p, pb_flag_type flag);
	void set_accid(const char* acc){_accid = acc;}
public:
	std::string _accid;
	std::string _password;

	std::string _gate_ip;
	int			_gate_port;
	u32			_account;
	bool		_is_connect_login;
	bool		_connect_gate_server;	
	u32			_charid;
};

