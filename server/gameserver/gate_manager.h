#ifndef __gate_manager_h__
#define __gate_manager_h__
class GateSession ;
class Session;
class GateManager
{
public:
    GateManager();
    ~GateManager();
    bool addGate(u16 nId, GateSession* pkGate);
    void removeGate(GateSession* pkGate);
    Session* getUser(tran_id_type tranid);
    Session* addUser(tran_id_type tranid, u32 accid, u16 gate);
    void removeUser(tran_id_type tranid);
    void sendMessage(google::protobuf::Message* msg, pb_flag_type flag, u16 nGate);
    void sendMsgToAll(google::protobuf::Message* msg, pb_flag_type flag);
    void offlineUser(tran_id_type tranid);
    void removeAllUsers();
protected:
    void removeUserByGate(u16 nGateId);
protected:
private:
    GateSession* m_Gates[MAX_GATE_ID];
    obj_ptr_map<tran_id_type, Session>m_Onlines;
};
#endif