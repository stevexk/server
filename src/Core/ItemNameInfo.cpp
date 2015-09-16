//////////////////////////////////////////////////////////////////////
// 
// Filename    : ItemNameInfo.cpp 
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "ItemNameInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
/*ItemNameInfo::ItemNameInfo () 
     throw()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
ItemNameInfo::~ItemNameInfo () 
    throw()
{
	__BEGIN_TRY
	__END_CATCH
}*/


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void ItemNameInfo::read (SocketInputStream & iStream ) 
	 throw(ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szName;
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read(m_ObjectID);
	iStream.read(szName);
	iStream.read(m_Name, szName);

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void ItemNameInfo::write (SocketOutputStream & oStream ) 
     const throw(ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szName = m_Name.size();
	oStream.write(m_ObjectID);
	oStream.write(szName);
	oStream.write(m_Name);

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t ItemNameInfo::getSize() const
	throw()
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();

	PacketSize_t PacketSize = szObjectID + szBYTE + szName;

	return PacketSize;

	__END_CATCH
}

/////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string ItemNameInfo::toString () 
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ItemNameInfo("
		<< "ObjectID : " << m_ObjectID
		<< "Name : " << m_Name
		<< ")";

	return msg.toString();

	__END_CATCH
}