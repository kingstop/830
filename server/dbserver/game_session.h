#ifndef __game_session_h__
#define __game_session_h__

class GameSession : public tcp_session, public ProtocMsgBase<GameSession>
{
public:
	GameSession(void);
	~GameSession(void);

	static void initPBModule();
	void parseGameRegister(google::protobuf::Message* p, pb_flag_type flag);
    void parseGameMsg(google::protobuf::Message* p, pb_flag_type flag);
	void parseQueryPlayerInfo(google::protobuf::Message*p, pb_flag_type flag);
    void parseCreatePlayer(google::protobuf::Message*p, pb_flag_type flag);
    void parseSavePlayerInfo(google::protobuf::Message*p, pb_flag_type flag);
	void parseChangeCity(google::protobuf::Message*p, pb_flag_type flag);
	void parseMailList(google::protobuf::Message*p, pb_flag_type flag);
	void parseMailRead(google::protobuf::Message*p, pb_flag_type flag);
	void parseMailDelete(google::protobuf::Message*p, pb_flag_type flag);
	void parseSendMail(google::protobuf::Message*p, pb_flag_type flag);

	u16  getGameId() const{return m_game_id;}

	//查询玩家数据结果。
	void checkPlayerData( PlayerData* p, tran_id_type t);
	//
	void checkMailData(MailData* p , tran_id_type t);

	
	
public:
	virtual void proc_message( const message_t& msg );
	virtual void on_close( const boost::system::error_code& error );
private:
	u16 m_game_id;
};
#endif