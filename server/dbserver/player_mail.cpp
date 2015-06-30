#include "stdafx.h"
MailData*  MailManager::addMailData(u32 guid, MailData* p)
{
	MailData* pkData = m_mails.getData(guid);
	if (pkData && pkData != p)
	{
		return NULL;
	}else
	{
		pkData = p;
		m_mails.addData(guid, p);
	}
	return pkData;
}
MailData* MailManager::getMailData(u32 guid)
{
	return m_mails.getData(guid);
}
void MailManager::deleteMail(u32 guid, clientmsg::DelMail* p)
{
	MailData* pMailData = m_mails.getData(guid);
	if (pMailData && p)
	{
		for (int i = 0; i < p->mail_ids_size(); ++i)
		{
			u32 id = p->mail_ids(i);
			std::vector<msgs2s::PlayerMail*>::iterator it = pMailData->mails.begin();
			std::vector<msgs2s::PlayerMail*>::iterator end = pMailData->mails.begin();
			for (it ; it != end; ++it)
			{
				if ((*it)->mailid() == id)
				{
					delete (*it);
					pMailData->mails.erase(it);
					gDBQuestMgr.mailDelete(id);
					break;
				}
			}
		}
		
	}
}
void MailManager::readMail(u32 guid, clientmsg::ReadMail* p)
{
	MailData* pMailData = gDBMailMgr.getMailData(guid);
	if (pMailData && p)
	{
		for (u32 i = 0; i < pMailData->mails.size(); ++i)
		{
			for (int j = 0; j < p->mail_ids_size(); ++j)
			{
				u32 id = p->mail_ids(j);
				if (id == pMailData->mails[i]->mailid())
				{
					pMailData->mails[i]->set_flag(_MAIL_READED_);
					gDBQuestMgr.mailRead(id, _MAIL_READED_);
				}
			}

		}
	}
}
void MailManager::addMail(const std::string& name, u32 guid, clientmsg::UserSendMailByid* p)
{
	msgs2s::PlayerMail* pm = new msgs2s::PlayerMail;
	pm->set_mailid( ++ m_curMailId);
	pm->set_sender(guid);
	pm->set_sendername(name);
	pm->set_reciver((u32)p->remoteid());
	pm->set_mailtype((u32)p->type());
	pm->set_content(p->content());
	pm->set_flag(_MAIL_NOT_READ_);
	pm->set_createtime((u32)gDBServerTime);

	gDBQuestMgr.addMail( pm );
	MailData* pkData = m_mails.getData((u32)p->remoteid());
	tran_id_type t = INVALID_TRANS_ID;
	u16 gs = INVALID_GAME_ID ;
	
	if (pkData)
	{
		pkData->mails.push_back(pm);
		if (gDBCache.getTransAndgs((u32)p->remoteid(), t, gs) && t !=  INVALID_TRANS_ID && gs != INVALID_GAME_ID)
		{
			clientmsg::SendMailContent msg;
			clientmsg::UserOneMailContent* pContent = msg.mutable_mail_contents(0);
			pContent->set_mailid(pm->mailid());
			pContent->set_content(pm->content());
			pContent->set_type((clientmsg::enumMailType)pm->mailtype());
			pContent->set_isread(pm->flag());
			pContent->set_isdelete(0);
			gDBGameManager.sendMessage(&msg, t, gs);
		}
		
	}else
	{
		delete pm;
	}
}