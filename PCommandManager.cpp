#include <set>

#include <string.h>
#include <interface/Alert.h>
#include <interface/MenuItem.h>
#include <interface/TextView.h>
#include <support/ClassInfo.h>
#include "CommandManager.h"
#include "InputRequest.h"


using namespace std;

CommandManager::CommandManager(BArchivable *initDoc) {
	TRACE();
	doc	= initDoc;
	Init();
}

CommandManager::~CommandManager(void) {
	delete undoList;
	delete macroList;
}

void CommandManager::Init(void) {
	commandMap		= map<BString,Command *>();
	undoList		= new BList();
	macroList		= new BList();
	undoStatus		= 0;
	recording		= NULL;
}

status_t CommandManager::Archive(BMessage *archive, bool deep) {
	int32	i	= 0;
	for (i = 0; i<undoList->CountItems(); i++) {
		BMessage	*undoMessage	= (BMessage*)undoList->ItemAt(i);
		archive->AddMessage("undo",undoMessage);
	}
	for (i = 0; i<macroList->CountItems(); i++) {
		BMessage	*macroMessage	= (BMessage*)macroList->ItemAt(i);
		archive->AddMessage("macro",macroMessage);
	}
	if (deep)
		archive->AddInt32("undoStatus",undoStatus);
	//** need a good Errorcheck
	return B_OK;
}

status_t CommandManager::RegisterCommand(Command *cmd) {
	TRACE();
	status_t err	= B_OK;
	if (cmd) {
		cmd->SetManager(this);
		PRINT(("Register Command %s",command->Name()));
		commandMap[BString(command->Name())]=command;
	}
	else
		err = B_BAD_VALUE;
	return err;
}


void CommandManager::UnregisterCommand(Command *cmd) {
	TRACE();
	if (name)
		commandMap.erase(cmd->Name());
}


void CommandManager::UnregisterCommand(char* name) {
	TRACE();
	if (name)
		commandMap.erase(name);
}


BMessage *CommandManager::StartMacro(void) {
	TRACE();
	if (recording == NULL) {
		recording		= new BMessage(MACRO_TYPE);
	}
	else {
		int32 choice	= (new BAlert("Error!",_T("Macro Recording already started!"),_T("Restart Recording"),_T("Contiune Recording"),NULL, B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_STOP_ALERT))->Go();
		if (choice == 0) {
			delete recording;
			recording	= new BMessage(MACRO_TYPE);
		}
	}
	return recording;
}


void CommandManager::StopMacro() {
	TRACE();
	if (IsRecording())
	{
		InputRequest	*inputAlert = new InputRequest(_T("Input Macroname"),_T("Name"), _T("Macro"), _T("OK"),_T("Cancel"));
		char			*input		= NULL;
		char			*inputstr	= NULL;
		if  (recording != NULL)	{
			if (inputAlert->Go(&input)<1) {
				inputstr	= new char[strlen(input)+1];
				strcpy(inputstr,input);
				recording->AddString("Name",input);
				// 
				macroList->AddItem(new BMessage(*recording));
			}
			inputAlert->Lock();
			inputAlert->Quit();
			delete recording;
			recording		= NULL;
		}
	}
}


void CommandManager::PlayMacro(BMessage *makro,slowdown) {
	int32 		i				= 0;
	BMessage	*message		= new BMessage();
	status_t	err				= B_OK;
	while ( (makro->FindMessage("Macro::Commmand", i,message) == B_OK) && (err==B_OK) )
	{
		err = Execute(C);
		snooze(slowdown);
		i++;
	}

}


status_t CommandManager::Execute(BMessage *settings) {
	TRACE();
	status_t	err	= B_OK;
	if (doc->Lock()) {
		bool		shadow			= false;
		char		*commandName	= NULL;
		Command	*command			= NULL;
		settings->FindString("Command::Name",(const char**)&commandName);
		command		= GetCommand(commandName);
		if (command != NULL) {
			BMessage	*tmpMessage;
			try  {
				tmpMessage = command->Do(doc, settings);
			}
			catch(...){
				BAlert *alert = new BAlert(commandName, "Error on execution of Command.", "OK");
				alert->Go();
				err=B_ERROR;
			}
			if (err==B_OK){
				err				= settings->FindBool("shadow",&shadow);
				if (err != B_OK && shadow == false  ) {
					if (recording)
						recording->AddMessage("Macro::Commmand", macroIndexer->IndexMacroCommand(settings));
					if (!shadow) {
						undoList->RemoveItems(undoStatus+1,undoList->CountItems()-undoStatus);
						undoList->AddItem(new BMessage(*tmpMessage));
						undoStatus	= undoList->CountItems()-1;
					}
					err=B_OK;
				}
			}
			doc->Unlock();
		}
		else
		{
			char	*error	= new char[255];
			sprintf(error,"%s: %s",_T("Coud not Find Command"),commandName);
			(new BAlert("Error!",error, "OK",NULL,NULL, B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_STOP_ALERT))->Go();
			delete error;
			err = B_ERROR;
		}
	}
	return err;
}


Command* CommandManager::GetCommand(char* name)
{
	TRACE();
	return commandMap[BString(name)];
}


void CommandManager::Undo(BMessage *undo) {
	TRACE();
	int32 			i					= undoStatus;
	int32 			index				= undoList->IndexOf(undo);
	char			*commandName		= NULL;
	Command		*undoCommand		= NULL;
	BMessage		*msg				= NULL;
	if (doc->Lock()) {
		if (index<0)
			index=undoStatus;
		while (i>=index) {
			msg	= (BMessage *) undoList->ItemAt(i);
			if (msg != NULL) {
				msg->FindString("Command::Name",(const char**)&commandName);
				undoCommand	= GetCommand(commandName);
				if (undoCommand != NULL)
					undoCommand->Undo(doc,msg);
				else
					PRINT(("ERROR:\t CommandManager - Didnt found the Command\n"));
				undoStatus--;
				if (undoStatus<0)
					undoStatus = -1;
			}
			i--;
		}
		doc->Unlock();
	}
}


void CommandManager::Redo(BMessage *redo) {
	TRACE();
	int32 			i				= undoStatus+1;
	int32			index			= undoList->IndexOf(redo);
	char			*commandName	= NULL;
	Command		*redoCommand	= NULL;
	BMessage		*msg			= NULL;
	if (doc->Lock()) {
		if (index<0)
			index=undoStatus+1;
		while (i<=index) {
			msg	= (BMessage *) undoList->ItemAt(i);
			if 	(msg != NULL) {
				msg->FindString("Command::Name",(const char**)&commandName);
				redoCommand	= GetCommand(commandName);
				if (redoCommand)
					redoCommand->Do(doc,msg);
				else
					PRINT(("ERROR\tCommandManager - Coudn´t find the Command\n"));
			}
			i++;
			undoStatus++;
			if (undoStatus > (undoList->CountItems()-1))
				undoStatus = undoList->CountItems()-1;
		}
		doc->Unlock();
	}
}

void CommandManager::SetUndoIndex(uint32 newIndex){
	//if the newIndex is smalle as the old undoIndex means we need to go
	//some steps "backwards(undo)" down until we are at the newIndex
	int32 i = 0;
	if (undoIndex>newIndex)
		for (i = undoIndex;i>newIndex;i--){
			
		}
	//if the newIndex is bigger as the undoIndex this means we need to go
	//some steps "upwardss(Do)" until we are at the newIndex
	if (undoIndex<newIndex)
	for (i = newIndex;i<undoIndex;i++){
			
		}
}


Command* CommandManager::CommandAt(int32 index) {
	map<BString, Command*>::iterator iter;
	iter=commandMap.begin();
	for (int i=0;i< index;i++)
		iter++;
  	return iter->second;
}
