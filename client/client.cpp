#include "stdafx.h"
#include "client.h"
Client::Client(u32 index, const net_info& info)
:tcp_client(*net_global::get_io_service()),m_testIndex(index), m_info(info), m_client_state(_client_init_), m_transid(INVALID_TRANS_ID), m_MoveStateEnable(false)
{
    _proto_user_ptr = this;
  // connect(m_info._ip.c_str(), m_info._port);
}
Client::~Client()
{

}
bool Client::reConnect()
{
   connect(m_info._ip.c_str(), m_info._port);
   return true;
}
void Client::initPBModule()
{
    ProtocMsgBase<Client>::registerSDFun(&Client::send_message, NULL);
    ProtocMsgBase<Client>::registerCBFun(PROTOCO_NAME(clientmsg::LoginResponse),                   &Client::parseLoginResult);
    ProtocMsgBase<Client>::registerCBFun(PROTOCO_NAME(clientmsg::ClientInit),                      &Client::parseClientInit);
    ProtocMsgBase<Client>::registerCBFun(PROTOCO_NAME(clientmsg::MapScreenRefreshCharacter),        &Client::parseClientChar);
}
void Client::parseClientChar(google::protobuf::Message* p, pb_flag_type flag)
{
    clientmsg::MapScreenRefreshCharacter* msg = static_cast<clientmsg::MapScreenRefreshCharacter*>(p);
    if (msg)
    {
        if (!m_MoveStateEnable)
        {
            const MapCharInfo& m = msg->mapinfo();
            m_MoveInfo.set_charid( m_PlayerData.charinfo().charid());
            m_MoveInfo.set_x(m.x());
            m_MoveInfo.set_y(m.y());
            m_MoveInfo.set_dir(m.dir());
            m_MoveInfo.set_speed(2.0f);
            m_MoveStateEnable = true;

            gEventMgr.addEvent(this, &Client::moveRand, EVENT_ROBOT_RAND_MOVE, 2*1000, 0 ,0);
            gEventMgr.addEvent(this, &Client::moveSend, EVENT_ROBOT_RAND_SEND, 200, 0 ,0);
        }
    }
}
void Client::parseLoginResult(google::protobuf::Message* p, pb_flag_type flag)
{
    clientmsg::LoginResponse* msg = static_cast<clientmsg::LoginResponse*>(p);
    if (msg)
    {
        m_transid = msg->user_account();
        m_info._ip = msg->gate_ip();
        m_info._port = msg->gate_port();
        close();
    }
}
void Client::parseClientInit(google::protobuf::Message* p, pb_flag_type flag)
{
    clientmsg::ClientInit* msg = static_cast<clientmsg::ClientInit*>(p);
    if (msg)
    {
       if (Response_NewChar == msg->result())
       {
           clientmsg::CreateChar m;
           m.set_cityid(2);
           m.set_mapid(1);
           CharInfo* pinfo = m.mutable_charinfo();
           pinfo->set_charid(INVALID_PLAYER_ID);
           pinfo->set_user_account(INVALID_ACCOUNT);
           char buff[20] = {0};
           sprintf(buff, "test:%u", m_testIndex);
           pinfo->set_name(buff);
           pinfo->set_head(1);
           pinfo->set_sex(1);
           pinfo->set_chartype(enumChar_Person);
           sendPBMessage(&m);
           //Mylog::log_player(LOG_INFO, "Create player by trans[%u]", m_transid);
       }else
       {
          m_PlayerData = *msg;
          //Mylog::log_player(LOG_INFO, "get player data  trans[%u]", m_transid);
       }
    }
}
void Client::update(u32 nDiff)
{
    run_no_wait();

    if (m_MoveStateEnable && m_MoveInfo.state() == 2)
    {
        float dist = nDiff * m_MoveInfo.speed() / _TIME_SECOND_MSEL_;
        if (dist < 0.0001f)
        {
            return;
        }
        float x = m_MoveInfo.x() + dist * cosf(m_MoveInfo.dir()) ;
        float y = m_MoveInfo.y() + dist * sinf(m_MoveInfo.dir());

        m_MoveInfo.set_x(x);
        m_MoveInfo.set_y(y);
    }
}
void Client::moveSend()
{
    if (m_MoveStateEnable)
    {
        if (m_MoveInfo.state() == 2)
        {  
            //sendPBMessage(&m_MoveInfo);
        }

        //Mylog::log_player(LOG_DEBUG, "Player [%u], Posx:[%f] PosY:[%f] Dir:[%f]", m_transid, m_MoveInfo.x(), m_MoveInfo.y(), m_MoveInfo.dir());
    }
}
void Client::moveRand()
{
    if (m_MoveStateEnable)
    {
        bool bMove = gCLRand.RandBool();
        bool bSend = false;
        u8 nState = 1;
        float dir = gCLRand.RandFloat(0.f, 360.f);
        if (bMove)
        {   nState = 2;}

        if (nState != m_MoveInfo.state())
        {   bSend = true;}

        m_MoveInfo.set_state(nState);
        if (bMove)
        {   m_MoveInfo.set_dir(dir);}

        if (bSend)
        {   sendPBMessage(&m_MoveInfo);}
    }
   
}
void Client::on_connect()
{
    gCLClientTese.removeFromReconn(this);
    tcp_client::on_connect();
    switch(m_client_state)
    {
    case _client_init_:
    case _client_wait_login_:
        {
            m_client_state = _client_conn_login_;
            clientmsg::LoginRequest msg;
            char buff[20] = {0};
            sprintf(buff, "%u", m_testIndex);
            msg.set_name(buff);
            msg.set_pwd("123456");
            sendPBMessage(&msg);
			//static int login = 0;
			//login ++;
            //Mylog::log_player(LOG_INFO, "login account[%s] count[%d]", buff, login);
			
        }break;
    case _client_wait_gate_:
        {
            m_client_state = _client_connet_gate_;
            clientmsg::LoginGame msg;
            msg.set_user_account(m_transid);
            sendPBMessage(&msg);
			//static int gate = 0;
			//gate ++;
            //Mylog::log_player(LOG_INFO, "Gate trans[%u] count[%d]", m_transid, gate);
        }break;
    default:
        break;    
    }
}
void Client::on_close( const boost::system::error_code& error )
{
    tcp_client::on_close(error);
    switch(m_client_state)
    {
    case _client_conn_login_:
        {
            m_client_state = _client_wait_gate_;
            connect(m_info._ip.c_str(), m_info._port);
			//static int connectgate = 0;
			//connectgate ++;
            //Mylog::log_player(LOG_INFO, "connect gate trans[%u] count[%d]", m_transid, connectgate);
        }break;   
    }
}
void Client::on_connect_failed( boost::system::error_code error )
{
    gCLClientTese.addToReconn(this);
}
void Client::proc_message( const message_t& msg )
{
    parsePBMessage(msg.data, msg.len);
}