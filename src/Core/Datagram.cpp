//////////////////////////////////////////////////////////////////////
//
// Filename    : Datagram.cpp
// Written By  : reiot@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Datagram.h"
#include "Assert1.h"
#include "PacketFactoryManager.h"
#include "DatagramPacket.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
Datagram::Datagram () 
	throw() 
: m_Length(0), m_InputOffset(0), m_OutputOffset(0), m_Data(NULL) 
{
	__BEGIN_TRY

	memset(&m_SockAddr , 0 , sizeof(m_SockAddr));
	m_SockAddr.sin_family = AF_INET;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
Datagram::~Datagram () 
	throw() 
{ 
	__BEGIN_TRY

	if (m_Data != NULL ) {
		SAFE_DELETE_ARRAY(m_Data);
		m_Data = NULL;
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// ���� ���ۿ� ����ִ� ������ �ܺ� ���۷� �����Ѵ�.
//////////////////////////////////////////////////////////////////////
void Datagram::read (char * buf , uint len )
	throw(Error )
{
	__BEGIN_TRY

	// boundary check
	Assert(m_InputOffset + len <= m_Length);

	memcpy(buf , &m_Data[m_InputOffset] , len);

	m_InputOffset += len;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// ���� ���ۿ� ����ִ� ������ �ܺ� ��Ʈ������ �����Ѵ�.
//////////////////////////////////////////////////////////////////////
void Datagram::read (string & str , uint len )
	throw(Error )
{
	__BEGIN_TRY

	// boundary check
	Assert(m_InputOffset + len <= m_Length);

	str.reserve(len);
	str.assign(&m_Data[m_InputOffset] , len);

	m_InputOffset += len;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 
// Datagram ��ü���� Packet ��ü�� �������.
// DatagramSocket �� ���� ������ ũ�⸸ �����(?) ũ�ٸ�,
// peer���� ���� ��Ŷ�� �߷��� ���� ���ɼ��� ����. 
// 
// (Ư�� �츮 ���ӿ����� UDP�� ���� ���󿡼��� ���Ǳ� ������
// Ȯ���� �� ����..)
// 
// *CAUTION*
// 
// �Ʒ��� �˰�������, (1) ���� �ּҿ��� ���ƿ� 2���� ���� �ٸ� ��Ŷ��
// recvfrom()���� ���� ���� ���ϵǾ�� �ϸ�, (2) �ϳ��� ��Ŷ�� �Ѳ�����
// ��������.. ��� �����Ͽ����� �ǹ̰� �ִ�.
// 
//////////////////////////////////////////////////////////////////////
void Datagram::read (DatagramPacket * & pPacket )
	throw(ProtocolException , Error )
{
	__BEGIN_TRY

	Assert(pPacket == NULL);

	PacketID_t packetID;
	PacketSize_t packetSize;

	// initialize packet header
	read((char*)&packetID , szPacketID);
	read((char*)&packetSize , szPacketSize);

	//cout << "DatagramPacket I  D : " << packetID << endl;

	// ��Ŷ ���̵� �̻��� ���
	if (packetID >= Packet::PACKET_MAX )
		throw InvalidProtocolException("invalid packet id");

	// ��Ŷ ����� �̻��� ���
	if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID) )
		throw InvalidProtocolException("too large packet size");

	// �����ͱ׷��� ũ�Ⱑ ��Ŷ�� ũ�⺸�� ���� ���
	if (m_Length < szPacketHeader + packetSize )
		throw Error("�����ͱ׷� ��Ŷ�� �ѹ��� �������� �ʾҽ��ϴ�.");

	// �����ͱ׷��� ũ�Ⱑ ��Ŷ�� ũ�⺸�� Ŭ ���
	if (m_Length > szPacketHeader + packetSize )
		throw Error("���� ���� �����ͱ׷� ��Ŷ�� �Ѳ����� ���������ϴ�.");

	// ��Ŷ�� �����Ѵ�.
	pPacket = (DatagramPacket*)g_pPacketFactoryManager->createPacket(packetID);

	Assert(pPacket != NULL);

	// ��Ŷ�� �ʱ�ȭ�Ѵ�.
	pPacket->read(*this);

	// ��Ŷ�� ���� �ּ�/��Ʈ�� �����Ѵ�.
	pPacket->setHost(getHost());
	pPacket->setPort(getPort());

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �ܺ� ���ۿ� ����ִ� ������ ���� ���۷� �����Ѵ�.
//////////////////////////////////////////////////////////////////////
void Datagram::write (const char * buf , uint len )
	throw(Error )
{
	__BEGIN_TRY

	// boundary check
	Assert(m_OutputOffset + len <= m_Length);
//	if (m_OutputOffset + len > m_Length)
//	{
//		throw Error("Datagram::write(): ������ ������ ������ ũ�⺸�� Ů�ϴ�.");
//	}

	memcpy(&m_Data[m_OutputOffset] , buf , len);

	m_OutputOffset += len;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �ܺ� ��Ʈ���� ����ִ� ������ ���� ���۷� �����Ѵ�.
//
// *CAUTION*
//
// ��� write()���� write(const char*,uint)�� ����ϹǷ�, m_OutputOffset
// �� �������� �ʿ�� ����.
//
//////////////////////////////////////////////////////////////////////
void Datagram::write (const string & str )
	throw(Error )
{
	__BEGIN_TRY

	// boundary check
	Assert(m_OutputOffset + str.size() <= m_Length);

	// write string body
	write(str.c_str() , str.size());

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// write packet
//
// ��Ŷ�� ���̳ʸ� �̹����� �����ͱ׷����� ����ִ´�.
// ��Ŷ�� �����ϴ� �ʿ��� �� �޽�带 ȣ���ϸ�, �� ���¿��� �����ͱ׷���
// ���� ���۴� NULL �̾�� �Ѵ�. �� �� �޽�带 ȣ���� �� ���۰� �Ҵ�
// �Ǿ�� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////
void Datagram::write (const DatagramPacket * pPacket )
	throw(ProtocolException , Error )
{
	__BEGIN_TRY

	Assert(pPacket != NULL);

	PacketID_t packetID = pPacket->getPacketID();
	PacketSize_t packetSize = pPacket->getPacketSize();

	// ����Ÿ�׷��� ���۸� ������ ũ��� �����Ѵ�.
	setData(szPacketHeader + packetSize);

	// ��Ŷ ����� �����Ѵ�.
	write((char*)&packetID , szPacketID);
	write((char*)&packetSize , szPacketSize);

	// ��Ŷ �ٵ� �����Ѵ�.
	pPacket->write(*this);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// set data
//
// �����ͱ׷����Ͽ��� �о���� �����͸� ���ι��ۿ� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////
void Datagram::setData (char * data , uint len ) 
	throw(Error ) 
{ 
	__BEGIN_TRY

	Assert(data != NULL && m_Data == NULL);

	m_Length = len; 
	m_Data = new char[m_Length]; 
	memcpy(m_Data , data , m_Length); 

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void Datagram::setData (uint len )
	throw(Error )
{
	__BEGIN_TRY

	Assert(m_Data == NULL);

	m_Length = len;
	m_Data = new char[ m_Length ];

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
// set address
//////////////////////////////////////////////////////////////////////
void Datagram::setAddress (SOCKADDR_IN * pSockAddr ) 
	throw(Error ) 
{ 
	__BEGIN_TRY

	Assert(pSockAddr != NULL);

	memcpy(&m_SockAddr , pSockAddr , szSOCKADDR_IN); 

	//char str[80];
	//sprintf(str, "0x%X - 0x%X", m_SockAddr.sin_port, ntohs(m_SockAddr.sin_port));
    //cout << "[Datagram::setAddress] " << inet_ntoa(m_SockAddr.sin_addr) << ":" << ntohs(m_SockAddr.sin_port) << " - " << str << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////
string Datagram::toString () const
	throw()
{
	StringStream msg;
	msg << "Datagram("
		<< "Length:" << m_Length
		<< ",InputOffset:" << m_InputOffset
		<< ",OutputOffset:" << m_OutputOffset
		<< ")";
	return msg.toString();
}