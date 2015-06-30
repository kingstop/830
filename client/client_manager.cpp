#include "stdafx.h"
#include "client.h"
#include "json_help.h"

ClientTest::ClientTest()
    :m_EventHold(WORLD_INSTANCE)
{
    m_maxCount = m_onceCount = m_curCount = m_accountBegin = 0;
    m_Online = 0;
    m_TransCount = 0;
    m_accountBegin = 1;
    m_onceTime = 1000;
    m_WaitReconnet.clear();
    m_Reconns.clear();
};
bool ClientTest::init()
{
    ServerFrame::init();
    Client::initPBModule();

    JsonHelper help("conf/robot.json");
    if (!help.loadJson())
    {
        return false;
    }

    const Json::Value& Root = help.root();
    LAZY_JSON_GET_UINT(m_maxCount,		        "max_count",			    Root);			
    LAZY_JSON_GET_UINT(m_onceCount	,	        "once_count",	            Root);
    LAZY_JSON_GET_UINT(m_accountBegin	,	    "account_start",	        Root);
    LAZY_JSON_GET_UINT(m_info._port	,	        "port",	                Root);
    LAZY_JSON_GET_UINT(m_onceTime	,	        "once_time",	            Root);
    LAZY_JSON_GET_STRING(m_info._ip,            "ip",                   Root);

    if (m_onceTime < 10)
    {   m_onceTime = 100;}

    addRobot();
    gEventMgr.addEvent(this, &ClientTest::reConnetClient, EVENT_ADD_TEST_ACCOUNT, m_onceTime, 0, 0);
    //gEventMgr.addEvent(this, &ClientTest::reConnetClient, EVENT_RECONN_TEST_ACCOUNT, m_onceTime, 0, 0);
    return true;
}
void ClientTest::addToReconn(Client* p)
{
    m_WaitReconnet.push_back(p);
}
void ClientTest::removeFromReconn(Client* p)
{
    m_Reconns.erase(p);
}
void ClientTest::reConnetClient()
{
    Client* p = NULL;
    m_curCount ++;
    
    while( !m_WaitReconnet.empty() &&  m_Reconns.size() < m_onceCount)
    {
        p = m_WaitReconnet.front();
        if (p)
        {
            p->reConnect();
            m_Reconns.insert(p);
            m_WaitReconnet.pop_front();
        }
    }
    
}
void ClientTest::addRobot()
{
    for (u32 i = 0; i < m_onceCount * m_maxCount; ++i)
    {
        Client* p = new Client(i + m_accountBegin, m_info);
        m_Clients.push_back(p);
        addToReconn(p);
    }
}
bool ClientTest::onKey()
{
    return true;
}
void ClientTest::runOnce(u32 nDiff)
{
    m_Online = 0;
    m_TransCount = 0;
    net_global::update_net_service();
    std::vector<Client*>::iterator it = m_Clients.begin();
    std::vector<Client*>::iterator itEnd = m_Clients.end();

    u32  reconn_count = m_onceCount;
    for (it; it!= itEnd; ++it)
    {
        Client* p = (*it);
        if (p)
        {
            p->update(nDiff);
            if (p->IsOK())
            { m_Online ++;}
            if (p->IsGetTrans())
            { m_TransCount++;}
        }
    }

    m_EventHold.update(nDiff);

    //reConnetClient();

    static u32 curtime = 0;
    curtime += nDiff;
    if (curtime > 10000 && m_Online > 0)
    {
        Mylog::log_server(LOG_INFO, "Onlines:[%u], trans:[%u], wait connet Count:[%u]", m_Online, m_TransCount, m_WaitReconnet.size());
        curtime = 0;
    }
}
void ClientTest::shutDown()
{
    
}
void ClientTest::memoryLog() 
{

}
void ClientTest::setStop()
{

}
void ClientTest::checkStop()
{

}