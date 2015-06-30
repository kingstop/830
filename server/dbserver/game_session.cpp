#include "stdafx.h"
#include "game_session.h"


GameSession::GameSession(): tcp_session( *net_global::get_io_service() )
{
	_proto_user_ptr = this;
    m_game_id = INVALID_GAME_ID;
}
GameSession::~GameSession()
{

}

void GameSession::parseGameMsg(google::protobuf::Message* p, pb_flag_type flag)
{

}
void GameSession::parseCreatePlayer(google::protobuf::Message*p, pb_flag_type flag)
{
    clientmsg::CreateChar* msg = static_cast<clientmsg::CreateChar* >(p);
    if (msg)
    {
        if (gDBCache.hasUserName(msg->charinfo().name()))
        {
            msgs2c::MsgS2CCreatePlayerError m;
            m.set_result(msgs2c::Create_Name_Repeat);
            gDBGameManager.sendMessage(&m, flag, m_game_id);

        }else
        {   gDBQuestMgr.createPlayer(flag, msg, m_game_id);}
    }
}
void GameSession::parseQueryPlayerInfo(google::protobuf::Message*p, pb_flag_type flag)
{
	msgs2s::MsgGS2DBQueryChar* msg = static_cast<msgs2s::MsgGS2DBQueryChar*>(p);
	if (msg)
	{
		const msgs2s::GTLGData& d = msg->data();
        PlayerData* pkData = gDBCache.getCacheData(d.account());
        if (NULL == pkData)
        {
            gDBQuestMgr.queryPlayerInfo(d.account(), d.transid(), m_game_id);
        }else
        {
			checkPlayerData( pkData, d.transid());
        }
		//Mylog::log_server(LOG_INFO,"parse account[%u] query login", d.account());
	}
}
void GameSession::checkPlayerData( PlayerData * p, tran_id_type t)
{
	u16 cityGS = gDBServer.getCityGS( p->p->sc_data().city());
	if (cityGS == m_game_id)
	{
		gDBCache.addOnline(t, p->p->sc_data().guid());
		p->gs = cityGS;
		msgs2s::MsgDB2GSQueryCharResult msg;
		msgs2s::PlayerInfo* pinfo = msg.mutable_info();
		*pinfo = *(p->p);
		msg.set_result(_DB_FOUND_PLAYERINFO__);
		sendPBMessage(&msg, t);
	}else
	{
		if (NULL != gDBGameManager.getGameClient(cityGS))
		{
			msgs2s::MsgDB2GTChangeGS m;
			m.set_gameserverid(cityGS);
			sendPBMessage(&m, t);
		}else
		{
			Mylog::log_server(LOG_ERROR,"not found the active game server [%u]", cityGS);
		}
	}
}
void GameSession::parseChangeCity(google::protobuf::Message*p, pb_flag_type flag)
{
	msgs2s::MsgGS2DBChangeServer* msg = static_cast<msgs2s::MsgGS2DBChangeServer*>(p);
	u16 cityGS = gDBServer.getCityGS( msg->city());
	if (NULL != gDBGameManager.getGameClient(cityGS))
	{
		msgs2s::MsgDB2GTChangeGS m;
		m.set_gameserverid(cityGS);
		sendPBMessage(&m, flag);
	}else
	{
		Mylog::log_server(LOG_ERROR,"not found the active game server [%u]", cityGS);
	}
	
}
void GameSession::checkMailData(MailData* p , tran_id_type t)
{
	clientmsg::SendMailContent msg;
	for (u32 i = 0 ; i < p->mails.size(); ++i)
	{
		msgs2s::PlayerMail* pMail = p->mails[i];
		clientmsg::UserOneMailContent* pContent = msg.mutable_mail_contents(i);
		pContent->set_mailid(pMail->mailid());
		pContent->set_content(pMail->content());
		pContent->set_type((clientmsg::enumMailType)pMail->mailtype());
		pContent->set_isread(pMail->flag());
		pContent->set_isdelete(0);
	}
	sendPBMessage(&msg, t);
}
void GameSession::parseGameRegister(google::protobuf::Message* p, pb_flag_type flag)
{
	msgs2s::MsgServerRegister* msg = static_cast<msgs2s::MsgServerRegister*>(p);
	if (msg)
	{
        const ::msgs2s::ServerVersion& v = msg->version();
        m_game_id = msg->serverid();
        if (!gDBVersion.checkVersion(v.major(), v.minor(), v.build(), v.appsvn()))
        {
            Mylog::log_server(LOG_ERROR,"register Game [%u] error, version is too old! ",m_game_id);
            close();
        }

		gDBGameManager.addGame(m_game_id, this);
		Mylog::log_server(LOG_INFO,"register Game [%u] ", m_game_id);
	}

}
void GameSession::parseMailList(google::protobuf::Message*p, pb_flag_type flag)
{
	u32 guid = gDBCache.getGuid(flag);
	if (INVALID_PLAYER_ID != guid)
	{
		MailData* pMailData = gDBMailMgr.getMailData(guid);
		if (pMailData)
		{
			checkMailData(pMailData, flag);
		}else
		{
			gDBQuestMgr.queryPlayerMail(guid, flag, m_game_id);
		}
	}
}
void GameSession::parseSendMail(google::protobuf::Message*p, pb_flag_type flag)
{
	clientmsg::UserSendMailByid* msg = static_cast<clientmsg::UserSendMailByid*>(p);
	u32 guid = gDBCache.getGuid(flag);
	PlayerData* pkdata = gDBCache.getCacheDataByTrans(flag);
	std::string name = "";
	if(pkdata)
	{
		name = pkdata->p->sc_data().name();
	}
	if (INVALID_PLAYER_ID != guid && msg)
	{
		gDBMailMgr.addMail(name, guid, msg);
	}
}
void GameSession::parseMailDelete(google::protobuf::Message*p, pb_flag_type flag)
{
	clientmsg::DelMail* msg = static_cast<clientmsg::DelMail*>(p);
	u32 guid = gDBCache.getGuid(flag);

	if (INVALID_PLAYER_ID != guid && msg)
	{
		gDBMailMgr.deleteMail( guid, msg);
	}
}
void GameSession::parseMailRead(google::protobuf::Message*p, pb_flag_type flag)
{
	clientmsg::ReadMail* msg = static_cast<clientmsg::ReadMail*>(p);
	u32 guid = gDBCache.getGuid(flag);
	if (INVALID_PLAYER_ID != guid && msg)
	{
		gDBMailMgr.readMail(guid, msg);
	}
}

void GameSession::initPBModule()
{
	ProtocMsgBase<GameSession>::registerSDFun(&GameSession::send_message, &GameSession::parseGameMsg);
	ProtocMsgBase<GameSession>::registerCBFun(PROTOCO_NAME(msgs2s::MsgServerRegister),      &GameSession::parseGameRegister);
    ProtocMsgBase<GameSession>::registerCBFun(PROTOCO_NAME(msgs2s::MsgGS2DBQueryChar),      &GameSession::parseQueryPlayerInfo);
	ProtocMsgBase<GameSession>::registerCBFun(PROTOCO_NAME(msgs2s::MsgGS2DBSavePlaye),      &GameSession::parseSavePlayerInfo);
	ProtocMsgBase<GameSession>::registerCBFun(PROTOCO_NAME(msgs2s::MsgGS2DBChangeServer),    &GameSession::parseChangeCity);

    ProtocMsgBase<GameSession>::registerCBFun(PROTOCO_NAME(clientmsg::CreateChar),          &GameSession::parseCreatePlayer);
	ProtocMsgBase<GameSession>::registerCBFun(PROTOCO_NAME(clientmsg::UserOpenMail),		&GameSession::parseMailList);
	ProtocMsgBase<GameSession>::registerCBFun(PROTOCO_NAME(clientmsg::ReadMail),			&GameSession::parseMailRead);
	ProtocMsgBase<GameSession>::registerCBFun(PROTOCO_NAME(clientmsg::DelMail),				&GameSession::parseMailDelete);
	ProtocMsgBase<GameSession>::registerCBFun(PROTOCO_NAME(clientmsg::UserSendMailByid),	&GameSession::parseSendMail);
}
void GameSession::parseSavePlayerInfo(google::protobuf::Message*p, pb_flag_type flag)
{
    msgs2s::MsgGS2DBSavePlaye* msg = static_cast<msgs2s::MsgGS2DBSavePlaye*>(p);
    if (msg && msg->players_size() > 0)
    {
        for (int i = 0; i < msg->players_size(); ++i)
        {
            msgs2s::DBPlayerData& data = const_cast<msgs2s::DBPlayerData&>(msg->players(i));
			u16 gs = m_game_id;
			if (data.state() == msgs2s::_OFF_LINE)
			{	
				gDBCache.removeOnline(flag);
				gs = INVALID_GAME_ID ;
			}

            //Mylog::log_player(LOG_DEBUG,"save player data pox x:%f, y:%f", data.data().sc_data().posx(),data.data().sc_data().posy());
            gDBQuestMgr.savePlayerInfo(data.data());
            gDBCache.addCacheData(data.mutable_data(), gs);
            
        }
    }
}
void GameSession::proc_message( const message_t& msg )
{
	parsePBMessage(msg.data, msg.len);
}
void GameSession::on_close( const boost::system::error_code& error )
{
	gDBGameManager.removeGame(this);
	tcp_session::on_close(error);
	Mylog::log_server(LOG_INFO, "server game [%u] close", m_game_id);
}