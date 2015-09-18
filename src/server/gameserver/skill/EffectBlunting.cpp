//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBlunting.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectBlunting.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "Player.h"
#include "GCModifyInformation.h"
#include "GCStatusCurrentHP.h"
#include "GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectBlunting::EffectBlunting(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBlunting::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
																															    	
	__END_CATCH
}

void EffectBlunting::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBlunting::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectBlunting" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	// �ɷ�ġ�� ���������� �ǵ����� ���ؼ��� �÷��׸� ����,
	// initAllStat�� �ҷ��� �Ѵ�.
	pCreature->removeFlag(Effect::EFFECT_CLASS_BLUNTING);

	if (pCreature->isVampire())
	{
		Vampire* pTargetVampire = dynamic_cast<Vampire*>(pCreature);
		VAMPIRE_RECORD prev;

		pTargetVampire->getVampireRecord(prev);
		pTargetVampire->initAllStat();
		pTargetVampire->sendRealWearingInfo();
		pTargetVampire->sendModifyInfo(prev);
    }
	else if (pCreature->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		pMonster->initAllStat();
	}
	else if (pCreature->isSlayer())
	{
		Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pCreature);
		SLAYER_RECORD prev;

		pTargetSlayer->getSlayerRecord(prev);
		pTargetSlayer->initAllStat();
		pTargetSlayer->sendRealWearingInfo();
		pTargetSlayer->sendModifyInfo(prev);
    }
	else if (pCreature->isOusters())
	{
		Ousters* pTargetOusters = dynamic_cast<Ousters*>(pCreature);
		OUSTERS_RECORD prev;

		pTargetOusters->getOustersRecord(prev);
		pTargetOusters->initAllStat();
		pTargetOusters->sendRealWearingInfo();
		pTargetOusters->sendModifyInfo(prev);
	}

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_BLUNTING);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectBlunting" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectBlunting::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectBlunting("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}