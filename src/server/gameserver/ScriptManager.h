//////////////////////////////////////////////////////////////////////////////
// Filename    : ScriptManager.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SCRIPT_MANAGER_H__
#define __SCRIPT_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Script.h"
#include <map>

//////////////////////////////////////////////////////////////////////////////
// class ScriptManager
//
// ��� NPC���� �����ϴ� public script �Ǵ� Ư�� NPC ���� ����ϴ� private script db
// �� ��Ÿ���� script manager �̴�.
//////////////////////////////////////////////////////////////////////////////

class XMLTree;

class ScriptManager 
{
public:
	void init() throw(Error) { load("PUBLIC"); }
	void load(const string & name) throw(Error);

public:
	Script* getScript(ScriptID_t scriptID) const throw(NoSuchElementException, Error);
	void setScript(ScriptID_t scriptID, Script* pScript) throw(DuplicatedException, Error);

	string toString() const throw();

	// ���� ���� ������.
	XMLTree*	getXML(const string& owner) { return m_XMLS[owner]; }
	XMLTree*	getScriptXML(ScriptID_t scriptID) { return m_ScriptXMLs[scriptID]; }

private:
	map< ScriptID_t, Script* > m_Scripts; // hash map of script
	map< string, XMLTree* > m_XMLS;
	map< ScriptID_t, XMLTree* > m_ScriptXMLs;

};

// global variable declaration
extern ScriptManager* g_pPublicScriptManager;

#endif