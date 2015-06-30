#include "stdafx.h"
#include "session.h"
#include "player.h"
#include "message/map.pb.h"
#include "FRWorld.h"
/************************************************************************/
/*                          注册消息实例                                */  
/*  msgs2s::MsgDB2GSQueryCharResult 注册回调    prasePBTest             */
/************************************************************************/
typedef void(Session::*pn_msg_cb)(google::protobuf::Message*);
static std::map<std::string, pn_msg_cb > static_session_cb_funs;

static void registerCBFun(std::string str, pn_msg_cb fun)
{
    static_session_cb_funs.insert(std::make_pair(str, fun));
}
void Session::parsePBCreatePlayer(google::protobuf::Message* p)
{
    clientmsg::CreateChar* msg = static_cast<clientmsg::CreateChar*>(p);
    if (msg && m_pkOwer == NULL )
    {
        //转发的时候 把账号ID加进来
        CharInfo* pChar = msg->mutable_charinfo();
        pChar->set_user_account(m_account);

        gGSDBClient.sendPBMessage(msg, m_tranid);
    }
}
// 没有找到注册函数就用这个函数处理
void Session::prasePBDefault(google::protobuf::Message* p)
{
     Mylog::log_server(LOG_INFO, "Parse message name [%s]", p->GetTypeName().c_str());
}

//这里负责注册消息
void Session::registerPBCall()
{
   registerCBFun(PROTOCO_NAME(clientmsg::CreateChar), &Session::parsePBCreatePlayer);
   registerCBFun(PROTOCO_NAME(clientmsg::CharMove), &Session::playerPlayerMove);
   registerCBFun(PROTOCO_NAME(clientmsg::CharChangeScene), &Session::parseChangeScene);
}

void Session::parsePBMessage(google::protobuf::Message* p)
{
    std::map<std::string, pn_msg_cb >::iterator it = static_session_cb_funs.find(p->GetTypeName());
    if (it != static_session_cb_funs.end())
    {
        pn_msg_cb fun = boost::ref( it->second);
        if ( NULL != fun )
        {
            (this->*fun)(p);
            return ;
        }
    }

    prasePBDefault(p);
}
//////////////////////////////////////////////////////////////////////////
Session::Session(tran_id_type t, account_type a, u16 gate)
    :m_tranid(t), m_account(a), m_gate(gate), m_pkOwer(NULL),m_state(_session_online_)
{
    // query player data from db server 
	queryDBPlayerInfo();
}
Session::~Session()
{

}
void Session::queryDBPlayerInfo()
{
	msgs2s::MsgGS2DBQueryChar msg;
	msgs2s::GTLGData* p = msg.mutable_data();
	p->set_account(m_account);
	p->set_transid(m_tranid);
	gGSDBClient.sendPBMessage(&msg, m_tranid);
}
void Session::queryDBPlayerInfoCall(msgs2s::MsgDB2GSQueryCharResult* p)
{
    clientmsg::ClientInit msg;
	CharInfo* pcinfo= msg.mutable_charinfo();
	pcinfo->set_charid(INVALID_ACCOUNT);
	pcinfo->set_user_account(m_account);
	pcinfo->set_name("input name");
	pcinfo->set_head(1);
	pcinfo->set_sex(1);
	pcinfo->set_chartype(enumChar_Person);
    if (_DB_FOUND_PLAYERINFO__ == p->result())
    {
        if (p->has_info())
        {   
            const ::msgs2s::PlayerInfo& info = p->info();
            m_pkOwer = gGSObjectMgr.createPlayer(this, &info);
        }else
        {
            Mylog::log_server(LOG_ERROR, "db MsgDB2GSQueryCharResult msg error");
        }
        if (m_pkOwer)
        {   
            m_pkOwer->makeClientCharInfo(pcinfo);
            msg.set_result(Response_Success);
			//Mylog::log_player(LOG_DEBUG, "session t[%u] a[%u] get char", m_tranid, m_account);
        }
        else
        {   
			
			msg.set_result(Response_SystemError);
			//Mylog::log_player(LOG_DEBUG, "session t[%u] a[%u] system error", m_tranid, m_account);
		}
    }else
    {   

		msg.set_result(Response_NewChar);
		Mylog::log_player(LOG_DEBUG, "session t[%u] a[%u] need create a new char", m_tranid, m_account);
	}

    sendPBMessage(&msg);

   
}
void Session::close()
{
   // Mylog::log_server(LOG_INFO, "session [%u] Player Quit");
    if (m_pkOwer)
    {
        m_pkOwer->quitGame();
        m_pkOwer = NULL;
    }
}
void Session::setReconnet()
{
    if (m_pkOwer)
    {
        clientmsg::ClientInit msg;
        CharInfo* pcinfo= msg.mutable_charinfo();
        m_pkOwer->makeClientCharInfo(pcinfo);
        msg.set_result(Response_Success);
        sendPBMessage(&msg);
    }else
    {
        Mylog::log_server(LOG_ERROR, "session reconnet not found the session");
    }

    m_state = _session_online_;
}
void Session::setWaitReconnet()
{
//     if (m_pkOwer)
//     {
//         m_pkOwer->setReconnet(NULL);
//     }
//     
    m_state = _session_offline_;
    //Mylog::log_player(LOG_INFO, "session [%u] will wait player reconnect");
}
void Session::sendPBMessage(google::protobuf::Message* p)
{
    if (m_state == _session_online_)
    {
	    gGSGateManager.sendMessage(p, m_tranid, m_gate);
    }else
    {
         //Mylog::log_player(LOG_DEBUG, "session [%u] is not online and wait reconnect... ", m_tranid);
    }
    
}
void Session::playerPlayerMove(google::protobuf::Message* p)
{
	if (m_pkOwer)
	{
		clientmsg::CharMove* msg =  static_cast<clientmsg::CharMove*>(p);
        if (msg)
        {
            m_pkOwer->moveMsgRequired(msg);
          
        }
	}
}

void Session::parseChangeScene(google::protobuf::Message* p)
{
	if (m_pkOwer)
	{
		clientmsg::CharChangeScene* msg = static_cast<clientmsg::CharChangeScene*>(p);
		m_pkOwer->changeScene(msg->cityid(), msg->mapid(), msg->x(), msg->y(), 0.f);
	}
	else
	{
		 Mylog::log_server(LOG_ERROR,"m_pkOwer == null failed to excute charChangeSceneHandler");
	}
	
	
}
