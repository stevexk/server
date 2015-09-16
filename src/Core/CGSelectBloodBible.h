
//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSelectBloodBible.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SELECT_BLOOD_BIBLE_H__
#define __CG_SELECT_BLOOD_BIBLE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGSelectBloodBible;
//
//////////////////////////////////////////////////////////////////////

class CGSelectBloodBible : public Packet
{
public:
	CGSelectBloodBible() {};
    virtual ~CGSelectBloodBible() {};
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_SELECT_BLOOD_BIBLE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szItemType; }

	// get packet name
	string getPacketName() const throw() { return "CGSelectBloodBible"; }

	// get packet's debug string
	string toString() const throw();

	// get/set BloodBibleID
	ItemType_t getBloodBibleID() const throw() { return m_BloodBibleID; }
	void setBloodBibleID(ItemType_t BloodBibleID ) throw() { m_BloodBibleID = BloodBibleID; }


private :

	// BloodBible ID
	ItemType_t m_BloodBibleID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGSelectBloodBibleFactory;
//
// Factory for CGSelectBloodBible
//
//////////////////////////////////////////////////////////////////////

class CGSelectBloodBibleFactory : public PacketFactory {

public:
	
	// constructor
	CGSelectBloodBibleFactory() throw() {}
	
	// destructor
	virtual ~CGSelectBloodBibleFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGSelectBloodBible(); }

	// get packet name
	string getPacketName() const throw() { return "CGSelectBloodBible"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_SELECT_BLOOD_BIBLE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szItemType; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGSelectBloodBibleHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSelectBloodBibleHandler {

public:

	// execute packet's handler
	static void execute(CGSelectBloodBible* pCGSelectBloodBible, Player* pPlayer) throw(Error);

};

#endif