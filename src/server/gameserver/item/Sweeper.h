//////////////////////////////////////////////////////////////////////////////
// Filename    : Sweeper.h
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SWEEPER_H__
#define __SWEEPER_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Sweeper;
//////////////////////////////////////////////////////////////////////////////

class Sweeper : public Item 
{
public:
	Sweeper() throw();
	Sweeper(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw(Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw(Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SWEEPER; }
	virtual string getObjectTableName() const throw() { return "SweeperObject"; }

	virtual ItemType_t getItemType() const throw() { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

public:
	virtual Durability_t getDurability() const throw(Error) { return m_Durability; }
	void setDurability(Durability_t durability) throw(Error) { m_Durability = durability; }

	virtual Defense_t getDefenseBonus() const throw(Error);
	virtual Protection_t getProtectionBonus() const throw(Error);

	virtual EnchantLevel_t getEnchantLevel() const throw() { return m_EnchantLevel; }
	virtual void setEnchantLevel(EnchantLevel_t level) throw() { m_EnchantLevel = level; }

private:
	ItemType_t			m_ItemType;			// ������ Ÿ��
	Durability_t		m_Durability;		// ������
	EnchantLevel_t		m_EnchantLevel; 
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};

//////////////////////////////////////////////////////////////////////////////
// class SweeperInfo;
//////////////////////////////////////////////////////////////////////////////
class SweeperInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SWEEPER; }

	virtual Durability_t getDurability() const throw() { return m_Durability; }
	virtual void setDurability(Durability_t durability) throw() { m_Durability = durability; }

	Defense_t getDefenseBonus() const throw() { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus) throw() { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus() const throw() { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus) throw() { m_ProtectionBonus = acBonus; }

	virtual uint getItemLevel(void) const throw() { return m_ItemLevel; }
	virtual void setItemLevel(uint level) throw() { m_ItemLevel = level; }

	virtual string toString() const throw();

private:
	Durability_t		m_Durability;		// ������
	Defense_t			m_DefenseBonus;		// ���߷� ���ʽ�
	Protection_t		m_ProtectionBonus;
	uint				m_ItemLevel;

};


//////////////////////////////////////////////////////////////////////////////
// class SweeperInfoManager;
//////////////////////////////////////////////////////////////////////////////

class SweeperInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SWEEPER; }
	virtual void load() throw(Error);
};

// global variable declaration
extern SweeperInfoManager* g_pSweeperInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class SweeperFactory
//////////////////////////////////////////////////////////////////////////////

class SweeperFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SWEEPER; }
	virtual string getItemClassName() const throw() { return "Sweeper"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Sweeper(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class SweeperLoader;
//////////////////////////////////////////////////////////////////////////////

class SweeperLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_SWEEPER; }
	virtual string getItemClassName() const throw() { return "Sweeper"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern SweeperLoader* g_pSweeperLoader;
#endif