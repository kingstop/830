#ifndef __player_mail_h__
#define __player_mail_h__

struct MailData
{
	MailData()
	{
		mails.clear();
	}
	~MailData()
	{
		for (u32 i = 0; i < mails.size(); ++i)
		{
			delete mails[i];
		}
		mails.clear();
	}
	u32 guid;
	std::vector<msgs2s::PlayerMail*> mails;
};
class MailManager
{
public:
	MailManager():m_curMailId(0){}
	void InitMailId(u32 id){m_curMailId = id;}
	MailData* addMailData(u32 guid, MailData* p);
	MailData* getMailData(u32 guid);
	void deleteMail(u32 guid, clientmsg::DelMail* p);
	void readMail(u32 guid, clientmsg::ReadMail* p);
	void addMail(const std::string& name, u32 guid, clientmsg::UserSendMailByid* p);
protected:
	obj_ptr_map<u32, MailData> m_mails;
	u32 m_curMailId;
private:
};
#endif