#ifndef __gate_manager_h__
#define __gate_manager_h__
class GateSession ;
class UserLoginSession;
struct Account;
class GateManager
{
public:
    GateManager();
    ~GateManager();
    void addGate(u16 nId, GateSession* pkGate);
    void removeGate(GateSession* pkGate);

    bool kickUserFromGate(Account* pkAccount);
    bool giveUserToGate(Account* pkAccount, UserLoginSession* pkSession);
    void receiveUserPrepar(u32 ntran, const std::string& ip, u16 port);
    GateSession* getIdleGate();
    UserLoginSession* getWaiteSession(u32 nAccountId);
    void removeWaitSession(u32 nAccountId);
protected:
private:
    GateSession* m_Gates[MAX_GATE_ID];
    obj_ptr_map<u32, UserLoginSession>m_WaitSessions;
};
#endif