#ifndef __player_relation_h__
#define __player_relation_h__

struct RelationData
{
	u32 guid;
	std::vector<msgs2s::PlayerRelation*> relations;		//friend list
	std::vector<msgs2s::PlayerInvite*> invites;			//invites
};

class RelationManager
{
public:
	RelationData* addRelationData(u32 guid, RelationData* p);
	RelationData* getRelationData(u32 guid);
protected:
private:
	obj_ptr_map<u32, RelationData> m_relations;
};
#endif