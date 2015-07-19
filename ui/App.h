/*
 * Copyright 2013, Stephan Aßmus <superstippi@gmx.de>.
 * All rights reserved. Distributed under the terms of the MIT License.
 */
#ifndef APP_H
#define APP_H


#include <Application.h>


class BEntry;
class MainWindow;


class App : public BApplication {
public:
								App();
	virtual						~App();

	virtual	bool				QuitRequested();
	virtual	void				ReadyToRun();
	virtual	void				MessageReceived(BMessage* message);
	virtual void				RefsReceived(BMessage* message);
	virtual void				ArgvReceived(int32 argc, char* argv[]);

private:
			void				_Open(const BEntry& entry);
			void				_ShowWindow(MainWindow* window);

			bool				_LoadSettings(BMessage& settings);
			void				_StoreSettings(const BMessage& windowSettings);
			BRect				_GetNextWindowFrame(bool singlePackageMode);

			void				_CheckPackageDaemonRuns();
			bool				_LaunchPackageDaemon();

private:
			MainWindow*			fMainWindow;
			int32				fWindowCount;

			BMessage			fSettings;
			bool				fSettingsRead;
};


#endif // APP_H
