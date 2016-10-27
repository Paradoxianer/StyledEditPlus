#ifndef COMMAND_H
#define COMMAND_H

#include "ObjectHelp.h"

#include <app/Message.h>
#include <support/List.h>

class HCommandManager;
/**
 * @class PCommand
 *
 * @brief  PCommand is the BaseObject for all PCommandos wich are executet
 *			Undo and Redo should be implemented as a BArchivable (Memento)
 *			so bevor changing the handed over object we store everything 
 * 			in a BMessage to undo it right
 * 
 *
 * @author Paradoxon
 * @version 0.01
 * @date 2005/10/04
 * @Contact: mail@projectconceptor.de
 *
 * Created on: Wed Oct 28  2005
 * @todo need something for MenuInsertion and for Shortcust so that every PCommand wich is loaded automatic inserted
 *
 */


class PCommand
{

public:
								PCommand(void);
	virtual						~PCommand(void);
	void						Init(void);
	/**
	 *this is called after adding the Command to the Manager
	 */	
	virtual	void				AttachedToManager(void)		= 0;
	/**
	 * is called short befor the Command is removed from the Manager
	 * normally this only happens if the Document is closed ;-)
	 */	
	virtual void				DetachedFromManager(void)	= 0;
	/**
	 * should return the Name of the Command.
	 * This Name ist normally used to find and use this Command
	 */	
	virtual char*				Name(void)					= 0;
	virtual	BMessage*			Do(BArchivable *applyOn, BMessage *settings);
	virtual	void				Undo(BArchivable *applyOn, BMessage *undo);
			void				SetManager(CommandManager *newManager);
			CommandManager*	Manager(void){return manager;};
protected:

			PCommandManager*	manager;
private:

};
#endif
