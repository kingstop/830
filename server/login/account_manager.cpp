#include "Stdafx.h"
#include "user_session.h"
struct CheckAcct
{
	enum
	{
		_check_pass_,
        _not_found_,
		_error_name_pwd,
		
	};
	CheckAcct( const std::string& name, const std::string& password, UserLoginSession* p)
	{
		acct = INVALID_ACCOUNT;
		str = name;
		pwd = password;
		ower = p;
		result = _check_pass_;
	}
	std::string str;
	std::string pwd;
	u8 result;
	UserLoginSession* ower;
	u32 acct;
};
AccountManager::AccountManager()
{
}
AccountManager::~AccountManager()
{

}

bool AccountManager::loadBanCall(const UDBResult& r)
{
	u32 count = 0;
	while (DBRow row = r.fetch_row()) 
	{
		u32 nId = row[0];
		BanAndMute* pkBan = m_BanAndMute.getData(nId);
		if (NULL == pkBan)
		{ pkBan = Memory::createObject<BanAndMute>();}

		pkBan->nId = nId;
		pkBan->nBan = row[1];
		pkBan->nMute = row[2];
		m_BanAndMute.addData(nId, pkBan);
	}
	Mylog::log_server( LOG_INFO, "load  Ban And Mute success!", count);
	return true;
}
bool AccountManager::isBanned(u32 nAccountId)
{
// 	std::map<u32, BanAndMute*>::iterator it = m_BanAndMute.find(nAccountId);
// 	if (it != m_BanAndMute.end())
// 	{
// 		BanAndMute* pkBan = it->second;
// 		if (pkBan)
// 		{
// 			return SYSTEM_TIME <= pkBan->nBan;
// 		}
// 	}
	return false;
}
bool AccountManager::addAccount(u32 account, u32 tranid, u16 gate)
{
	Account* pkAccount = getAccount( account);
	if (NULL == pkAccount)
	{	
		pkAccount = Memory::createObject<Account>();
		m_Accts.addData(account, pkAccount);
	}
	pkAccount->nTranId = tranid;
	pkAccount->nGateId = gate;
	pkAccount->nId = account;
	return true;
}
Account* AccountManager::getAccount(u32 nAccId)
{
	return m_Accts.getData(nAccId);
}
void AccountManager::removeAccount(u32 nAccountId)
{
	Memory::releaseObject<Account>(m_Accts.eraseData(nAccountId));
}
u32 AccountManager::makeTransId(std::string& str)
{
    std::stringstream stream ;
    stream << str;
    stream << time(NULL);
	return ssl::sslCrc32(stream.str().c_str(), stream.str().length());
}
void AccountManager::checkAccountCall(const void* data, bool sucess)
{
 	const CheckAcct* pkData = static_cast<const CheckAcct*>(data);
 	if (!pkData)
 	{ return ;}

	UserLoginSession* pksession = pkData->ower;
	if (pksession && pksession->is_valid())
	{
		clientmsg::LoginResponse msg;
		if (!sucess)
		{
			msg.set_result(clientmsg::enumLoginResult_Fail);
			pksession->sendPBMessage(&msg);
            pksession->setState(UserLoginSession::_wait_close_);
		}else
		{
			if (INVALID_ACCOUNT != pkData->acct)
			{
				Account* p = getAccount(pkData->acct);
				if (NULL != p)
				{
					gLGGateManager.kickUserFromGate(p);
               
				}else
				{
					p = Memory::createObject<Account>();
                    m_Accts.addData(pkData->acct, p);
				}

                std::string str = pkData->str + pkData->pwd + pkData->ower->get_remote_address_string();
				p->nId = pkData->acct;
				p->nTranId = makeTransId(str);
				p->nGateId = INVALID_GAME_ID;
				if(!gLGGateManager.giveUserToGate( p, pksession))
				{
					removeAccount(p->nId);
					msg.set_result(clientmsg::enumLoginResult_Fail);
					pksession->sendPBMessage(&msg);
                    pksession->setState(UserLoginSession::_wait_close_);
				}else
				{
					//Mylog::log_player( LOG_INFO, "add Account[%d] Login info to gate.!", p->nId);
				}
			}else
			{
				if (pkData->result == CheckAcct::_error_name_pwd)
				{
					msg.set_result(clientmsg::enumLoginResult_NameFail);
				}else
				{
					msg.set_result(clientmsg::enumLoginResult_Fail);
				}
                pksession->setState(UserLoginSession::_wait_close_);
				pksession->sendPBMessage(&msg);
			}
		}


	}
	delete pkData;
}
void AccountManager::batchQuery(DBQuery* p, const void* data)
{
	CheckAcct* pkData = static_cast<CheckAcct*>(const_cast<void*>(data));
	if (pkData)
	{
		DBQuery& query = *p;
		DBQParms parms;
		parms.clear();
		query.reset();
		parms << pkData->str;
		parms << pkData->pwd;
		query << "CALL CheckAccount(%0q, %1q)";
		query.parse();
		SDBResult r = query.store(parms);
		if (r.num_rows() > 0)
		{
			pkData->acct = r[0][0];
			pkData->result  = r[0][1];
			//Mylog::log_server( LOG_INFO, "Acct:Find Acct[%s] Acct[%u]", pkData->str.c_str(), pkData->acct);
		}else
		{
			Mylog::log_server( LOG_ERROR, "Acct:Not Find Acct[%s] Or Password error", pkData->str.c_str());
		}
		FREESTOREPROCEDURE(query);
	}
}

void AccountManager::checkAccount(const std::string&strName, const std::string& strPwd,UserLoginSession* p)
{
	gLGCenterDB.addBatchTask<AccountManager>(this, &AccountManager::batchQuery, &AccountManager::checkAccountCall, new CheckAcct(strName, strPwd, p),"check account");
}