#ifndef __gate_session_h__
#define __gate_session_h__
class GateSession : public tcp_session, public ProtocMsgBase<GateSession>
{
public:
	GateSession(void);
	~GateSession(void);

	struct GateInfo
	{
		GateInfo()
		{
			gate_id = 0 ;
			onlines = 0 ;
            out_ip = "127.0.0.1";
            out_port = 0;
		}
		u8	gate_id;
		u32 onlines;
        std::string out_ip;
        u16 out_port;
	};

	static void initPBModule();
	void parseGateRegister(google::protobuf::Message* p, pb_flag_type flag);
    void parseGateOnlines(google::protobuf::Message* p, pb_flag_type flag);
    void parseGateUserPrepar(google::protobuf::Message* p, pb_flag_type flag);


	const GateInfo& getGateInfo(){return m_GateInfo;}
	u32 getOnlines() const{return m_GateInfo.onlines;}
	u8  getGateId() const{return m_GateInfo.gate_id;}
public:
	virtual void proc_message( const message_t& msg );
	virtual void on_close( const boost::system::error_code& error );
private:
	GateInfo m_GateInfo;
};
#endif