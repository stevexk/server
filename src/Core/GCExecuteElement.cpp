//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCExecuteElement.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCExecuteElement.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCExecuteElement::GCExecuteElement () 
     throw()
{
	__BEGIN_TRY
	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCExecuteElement::~GCExecuteElement () 
    throw()
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCExecuteElement::execute (Player * pPlayer ) 
	 throw(ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCExecuteElementHandler::execute(this , pPlayer);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCExecuteElement::toString () 
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCExecuteElement("
		<< ")";
	return msg.toString();

	__END_CATCH
}
