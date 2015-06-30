#include "stdafx.h"
#include "session.h"
#include "gate_session.h"
#include "player.h"
#include "message/map.pb.h"
GateManager::GateManager()
{
    memset( m_Gates, 0 , sizeof(GateSession*) * MAX_GATE_ID);
}
GateManager::~GateManager()
{

}
bool GateManager::addGate(u16 nId, GateSession* pkGate)
{
    if (!pkGate)
    {
        Mylog::log_server( LOG_ERROR, "Add Gate[%d] error!  Gate Pointer is null", nId);
        return false;
    }

    if (nId > INVALID_GATE_ID && nId < MAX_GATE_ID )
    {
        m_Gates[nId] = pkGate;
        Mylog::log_server( LOG_INFO, "Add Gate[%d] Active", nId);
        return true;
    }
    Mylog::log_server( LOG_ERROR, "Add Gate[%d] error!", nId);
    return false;
}
void GateManager::removeAllUsers()
{
    std::map< tran_id_type, Session*>& smap = const_cast<std::map< tran_id_type, Session*>&>(m_Onlines.getDataMap());
    std::map< tran_id_type, Session*>::iterator it = smap.begin();
    std::map< tran_id_type, Session*>::iterator itend = smap.end();
    for (it ; it != itend; ++it)
    {
        Session* pkSession = it->second;
        if (pkSession)
        {
            pkSession->close();
            Memory::releaseObject<Session>(pkSession);
        }
    }
    smap.clear();
}
void GateManager::removeGate(GateSession* pkGate)
{
    if (pkGate)
    {
        u16 nId = pkGate->getGateId();
        if (nId > INVALID_GATE_ID && nId < MAX_GATE_ID )
        {
            if (m_Gates[ nId ] == pkGate)
            {
                removeUserByGate(nId);
                m_Gates[ nId ] = NULL;
                Mylog::log_server( LOG_ERROR, "Remove Active Gate[%d] ", nId);
            }
        }
    }
}
Session* GateManager::getUser(tran_id_type tranid)
{
   return m_Onlines.getData(tranid);
}

Session* GateManager::addUser(tran_id_type tranid, u32 accid, u16 gate)
{
    Session* pkSession = getUser(tranid);
    if (!pkSession)
    {
        pkSession = Memory::createObject<Session, tran_id_type, account_type, u16>(tranid, accid, gate);
        m_Onlines.addData(tranid, pkSession);
        return pkSession;
        Mylog::log_server(LOG_INFO,"add a transid [%u] ", tranid);
    }else
    {
        if (pkSession->getGateId() == gate && pkSession->getAccount() == accid)
        {
            // add log
            Mylog::log_server( LOG_INFO, "reconnet session[%u] account[%u] ", tranid, accid);
            pkSession->setReconnet();
            return pkSession;
        }else
        {
            // add log
            return NULL;
        }
    }
}
void GateManager::removeUserByGate(u16 nGateId)
{
    std::map< tran_id_type, Session*>& smap = const_cast<std::map< tran_id_type, Session*>&>(m_Onlines.getDataMap());
    std::map< tran_id_type, Session*>::iterator it = smap.begin();
    std::map< tran_id_type, Session*>::iterator itend = smap.end();
    for (it ; it != itend; )
    {
        std::map< u32, Session*>::iterator it2 = it ++;
        Session* pkSession = it2->second;
        if (pkSession && pkSession->getGateId() == nGateId)
        {
            pkSession->close();
            Memory::releaseObject<Session>(pkSession);
            smap.erase( it2);
        }
    }
}
void GateManager::offlineUser(tran_id_type tranid)
{
    Session* p = m_Onlines.getData(tranid);
    if (p)
    {
        //Mylog::log_server(LOG_INFO,"off line a transid [%u] ", tranid);
        p->setWaitReconnet();
    }
}
void GateManager::removeUser(tran_id_type tranid)
{
    Session* p = m_Onlines.eraseData(tranid);
    if (p)
    {
        p->close();
        //Mylog::log_server(LOG_INFO,"remove  a transid [%u] ", tranid);
        Memory::releaseObject<Session>(p);
    }
}
void GateManager::sendMsgToAll(google::protobuf::Message* msg, pb_flag_type flag)
{
    for (u16 i = 0 ; i < MAX_GATE_ID; ++i)
    {
        if (m_Gates[i])
        {
            m_Gates[i]->sendPBMessage(msg, flag);
        }
    }
}
void GateManager::sendMessage(google::protobuf::Message* msg, pb_flag_type flag, u16 nGate)
{
    if (nGate > INVALID_GATE_ID && nGate < MAX_GATE_ID )
    {
        if (m_Gates[nGate] )
        {
            m_Gates[nGate]->sendPBMessage(msg, flag);
            return ;
        }
    }
}