#ifndef __client_h__
#define __client_h__

enum
{
    _client_init_,
    _client_wait_login_,
    _client_conn_login_,     
    _client_wait_gate_,   
    _client_connet_gate_,
    _client_close_,
};
class Client : public tcp_client, public ProtocMsgBase<Client>, public EventableObject
{
public:
    Client(u32 index, const net_info& info);
    ~Client();
    
    bool reConnect();
    static void initPBModule();
    
    void parseLoginResult(google::protobuf::Message* p, pb_flag_type flag);
    void parseClientInit(google::protobuf::Message* p, pb_flag_type flag);
    void parseClientChar(google::protobuf::Message* p, pb_flag_type flag);

    virtual void on_connect();
    virtual void on_close( const boost::system::error_code& error );
    virtual void on_connect_failed( boost::system::error_code error );
    virtual void proc_message( const message_t& msg );

    void update(u32 nDiff);
    void moveRand();
    void moveSend();
    bool IsOK(){return m_MoveStateEnable;}
    bool IsGetTrans(){return m_transid > 0;}
protected:
private:
    u32 m_testIndex;
    u8  m_client_state;
    u32 m_transid;
    net_info m_info;
    clientmsg::ClientInit m_PlayerData;
    clientmsg::CharMove m_MoveInfo;
    bool m_MoveStateEnable;
};


#endif