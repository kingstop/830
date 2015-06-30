#ifndef __client_manager_h__
#define __client_manager_h__

class Client;
class ClientTest : public ServerFrame , public EventableObject
{
public:
    ClientTest();
    virtual bool init() ;
    virtual bool onKey() ;
    virtual void runOnce(u32 nDiff) ;
    virtual void shutDown() ;
    virtual void memoryLog() ;
    virtual void setStop(); 
    virtual void checkStop();

    void addRobot();
    void reConnetClient();
    void addToReconn(Client* p);
    void removeFromReconn(Client* p);
protected:
    u32 m_maxCount;
    u32 m_curCount;
    u32 m_onceCount;
    u32 m_Online;
    u32 m_onceTime;
    u32 m_TransCount;
    u32 m_accountBegin;
    EventableObjectHolder m_EventHold;
    std::vector<Client*> m_Clients;
    std::list<Client*>m_WaitReconnet;
    std::set<Client*>m_Reconns;
    net_info m_info;
private:
};

#endif