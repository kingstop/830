#ifndef __db_quest_h__
#define __db_quest_h__

class DBQuestManager
{
public:
	void queryPlayerInfo(account_type a,tran_id_type t, u16 gs);
    void createPlayer(tran_id_type t, clientmsg::CreateChar* p, u16 gs);
    void savePlayerInfo(const msgs2s::PlayerInfo& info);
	void queryPlayerRelation(u32 a,tran_id_type t, u16 gs);
	void queryPlayerMail(u32 a,tran_id_type t, u16 gs);
	void mailRead(u32 mailid, u32 flag);
	void mailDelete(u32 mailid);
	void addMail(msgs2s::PlayerMail* p);


	void savePlayerRelation(const msgs2s::PlayerRelation& info);
	void savePlaterInvite(const msgs2s::PlayerInvite& info);
	void savePlayerMail(const msgs2s::PlayerMail&info);
	
protected:
    //���߲�ѯ���.
	void dbDoQueryChar(DBQuery*p, const void* d);
	void dbCallQueryChar(const void* d, bool s);

    //�������
    void dbDoCreateChar(DBQuery*p, const void* d);
    void dbCallCreateChar(const void* d, bool s);
	
	//��ѯ��ϵ����
	void dbDoQueryRelation(DBQuery*p, const void* d);
	void dbCallQueryRelation(const void* d, bool s);
    
    void dbCallNothing(const SDBResult* , const void* , bool){;}
	//�ʼ��б�
	void dbCallQueryMail(const SDBResult* , const void* , bool);
	

	
protected:
    msgs2s::PlayerInfo* getPlayerInfo(SDBResult& sResult);
private:
};
#endif