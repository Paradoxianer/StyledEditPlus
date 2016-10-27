#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include "Command.h"
#include "BasePlugin.h"
#include "Indexer.h"

#include <app/Message.h>
#include <support/List.h>
#include <support/String.h>

#include <map>
using namespace std;


/**
 * @class CommandManager
 * @brief  a Class wich manage all Commands in an App
 * 
 *
 * @author Paradoxon
 * @version 0.01
 * @date 2015/06/14
 * @Contact: 
 *
 * Created on: Sat Jun 06  2015
 *
 *
 */

class CommandManager 
{

public:
						CommandManager(BArchivable *initDoc);
	virtual				~CommandManager(void);
	/**
	 * call this Method to start recording a Macro
	 * the Macro is stored in a BMEssage while recording
	 * you have acces to this BMessage... after finishing recording
	 * this message will be copied over and returned buy StopMacro
	 * and will be destroyed
	 */	
			BMessage	*StartMacro(void);
	/**
	 * call this Method to stop the recording of a Macro
	 * this function returns a fnished Macro as a BMessage
	 * the Name of the Macro is stored in the a Stringfield "Name"
	 */	

			BMessage	*StopMacro(void);
	/**
	 * returns true if there is a Macro recording in progress
	 */	
			bool		IsRecording(void){return recording!=NULL;};
	/**
	 * Plays back the macro wich is handed over to this Method
	 */			
			void		PlayMacro(BMessage *makro,bigtime_t slowdown=100000);
			
	virtual	status_t	RegisterCommand(Command *cmd);
	virtual	void		UnregisterCommand(char *name);
	virtual	void		UnregisterCommand(Command *cmd);

	virtual status_t	Archive(BMessage *archive, bool deep = true);

	
	virtual	Command*	GetCommand(char* name);
	virtual BList*		GetUndoList(void){return undoList;};
	virtual BList*		GetMacroList(void){return macroList;};
	
	virtual void		SetUndoIndex(uint32 newIndex);
	virtual int32		GetUndoIndex(void){return undoStatus;};

	virtual	void		Undo(BMessage *undo);
	virtual	void		Redo(BMessage *redo);

	virtual	status_t	Execute(BMessage *settings);
	
	virtual	int32		CountCommand(void){return commandMap.size();};
	virtual	Command*	CommandAt(int32 index);
	

protected:
	virtual void		Init(void);

			BList		*undoList;
			BList		*macroList;
			int32		undoStatus;
			BArchivable	*doc;
			map<BString, Command*>	 commandMap;
			BMessage	*recording;
private:

};
#endif
