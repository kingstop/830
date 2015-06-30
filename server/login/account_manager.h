#ifndef _account_manager_h_
#define _account_manager_h_

struct Account : PUBLIC_BASE_OBJECT(Account)
{
	REGISTER_POOL_INFO(Account, 2000, 0)
	
	Account()
	{
		nId = INVALID_ACCOUNT;
		nGateId = INVALID_GATE_ID;
		nTranId = INVALID_TRANS_ID;
	}

    u16 nGateId;
	tran_id_type nId;
	account_type nTranId;
};


struct BanAndMute : PUBLIC_BASE_OBJECT(BanAndMute)
{
	REGISTER_POOL_INFO(BanAndMute, 500, 0)

    BanAndMute()
    {
        nId = INVALID_ACCOUNT;
        nMute = 0;
        nBan = 0;
    }
	
    u32 nId;
	u32 nMute;
	u32 nBan;
};
class UserLoginSession;
class AccountManager
{
public:
	AccountManager();
	~AccountManager();

	bool loadBanCall(const UDBResult& r);
	void checkAccount(const std::string&strName, const std::string& strPwd, UserLoginSession* p);
	void batchQuery(DBQuery* p, const void* data);
	void checkAccountCall(const void* data, bool sucess);
	u32  makeTransId(std::string& str);
	bool isBanned(u32 nAccountId);
	void removeAccount(u32 nAccountId);
	bool addAccount(u32 account, u32 tranid, u16 gate);
    Account* getAccount(u32 nAccId);
protected:
	obj_ptr_map<u32, Account> m_Accts;
	obj_ptr_map<u32, BanAndMute> m_BanAndMute;
};
#endif