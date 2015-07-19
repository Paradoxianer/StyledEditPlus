#include "Command.h"
#include "CommandManager.h"
#include "PDocument.h"


Command::Command(void)
{
	TRACE();
	Init();
}


Command::~Command(void)
{
	TRACE();

}

void Command::Init(void)
{
	TRACE();
	manager			= NULL;
}

BMessage* Command::Do(BArchivable *applyOn,BMessage *settings)
{
	TRACE();
	int32		i					= 0;
	BMessage	*subCommandMessage	= new BMessage;
	Command	*subCommand			= NULL;
	char		*commandName		= NULL;
	//Check if there are settings vor SubCommands
	while 	(settings->FindMessage("Command::SubCommand",i,subCommandMessage) == B_OK)
	{		
		subCommandMessage->FindString("Command::Name",(const char **)&commandName);
		subCommandMessage=manager->GetCommand(commandName);
		if (subCommand)
		{
			subCommandMessage = subCommand->Do(applyOn,subCommandMessage);
			settings->ReplaceMessage("Command::SubCommand",subCommandMessage);
		}
		i++;
	}
	return settings;
}

void Command::Undo(BArchivable *applyOn,BMessage *undo)
{
	TRACE();
	BMessage	*subCommandMessage	= new BMessage();
	Command		*subCommand			= NULL;
	char		*commandName		= NULL;
	int32		i					= 0;
	while (undo->FindMessage("Command::SubCommand",i,subCommandMessage) == B_OK)
	{
		subCommand	= NULL;
		commandName	= NULL;
		subCommandMessage->FindString("Command::Name",(const char **)&commandName);
		subCommand=manager->GetCommand(commandName);
		if (subCommand)
			subCommand->Undo(applyOn,subCommandMessage);
		i++;
	}
}

void Command::SetManager(CommandManager *newManager)
{
	TRACE();
	if (newManager != NULL)
	{
		manager=newManager;
		AttachedToManager();
	}
	else
	{
		DetachedFromManager();
		manager=newManager;
	}
}
