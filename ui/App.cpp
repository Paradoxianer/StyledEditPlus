/*
 * Copyright 2013, Stephan Aßmus <superstippi@gmx.de>.
 * All rights reserved. Distributed under the terms of the MIT License.
 */

#include "App.h"

#include <stdio.h>

#include <Alert.h>
#include <Catalog.h>
#include <Entry.h>
#include <Message.h>
#include <package/PackageInfo.h>
#include <Path.h>
#include <Roster.h>
#include <String.h>

#include "support.h"


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "App"


App::App()
	:
	BApplication("application/x-vnd.StyledEditPlus"),
	fMainWindow(NULL),
	fWindowCount(0),
	fSettingsRead(false)
{
	
}


App::~App()
{
	// We cannot let global destructors cleanup static BitmapRef objects,
	// since calling BBitmap destructors needs a valid BApplication still
	// around. That's why we do it here.
	
}


bool
App::QuitRequested()
{
	if (fMainWindow != NULL
		&& fMainWindow->LockLooperWithTimeout(1500000) == B_OK) {
		BMessage windowSettings;
		fMainWindow->StoreSettings(windowSettings);

		fMainWindow->UnlockLooper();

		_StoreSettings(windowSettings);
	}

	return true;
}


void
App::ReadyToRun()
{
	if (fWindowCount > 0)
		return;

	BMessage settings;
	_LoadSettings(settings);

	fMainWindow = new MainWindow(_GetNextWindowFrame(false), settings);
	_ShowWindow(fMainWindow);
}


void
App::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case MSG_MAIN_WINDOW_CLOSED:
		{
			BMessage windowSettings;
			if (message->FindMessage("window settings",
					&windowSettings) == B_OK) {
				_StoreSettings(windowSettings);
			}

			fWindowCount--;
			if (fWindowCount == 0)
				Quit();
			break;
		}

		default:
			BApplication::MessageReceived(message);
			break;
	}
}


void
App::RefsReceived(BMessage* message)
{
	entry_ref ref;
	int32 index = 0;
	while (message->FindRef("refs", index++, &ref) == B_OK) {
		BEntry entry(&ref, true);
		_Open(entry);
	}
}


void

App::ArgvReceived(int32 argc, char* argv[])
{
	for (int i = 1; i < argc; i++) {
		BEntry entry(argv[i], true);
		_Open(entry);
	}
}


// #pragma mark - private


void
App::_Open(const BEntry& entry)
{

}


void
App::_ShowWindow(MainWindow* window)
{
	window->Show();
	fWindowCount++;
}


bool
App::_LoadSettings(BMessage& settings)
{
	if (!fSettingsRead) {
		fSettings = true;
		if (load_settings(&fSettings, "main_settings", "StyledEditPlus") != B_OK)
			fSettings.MakeEmpty();
	}
	settings = fSettings;
	return !fSettings.IsEmpty();
}


void
App::_StoreSettings(const BMessage& settings)
{
	// Take what is in settings and replace data under the same name in
	// fSettings, leaving anything in fSettings that is not contained in
	// settings.
	int32 i = 0;

	char* name;
	type_code type;
	int32 count;

	while (settings.GetInfo(B_ANY_TYPE, i++, &name, &type, &count) == B_OK) {
		fSettings.RemoveName(name);
		for (int32 j = 0; j < count; j++) {
			const void* data;
			ssize_t size;
			if (settings.FindData(name, type, j, &data, &size) != B_OK)
				break;
			fSettings.AddData(name, type, data, size);
		}
	}

	save_settings(&fSettings, "main_settings", "StyledEditPlus");
}


BRect
App::_GetNextWindowFrame(bool singlePackageMode)
{
	BRect frame;
	if (singlePackageMode)
		frame = BRect(50.0, 50.0, 649.0, 349.0);
	else
		frame = BRect(50.0, 50.0, 749.0, 549.0);

	BMessage settings;
	if (_LoadSettings(settings)) {
		if (singlePackageMode)
			settings.FindRect("small window frame", &frame);
		else
			settings.FindRect("window frame", &frame);
	}

	make_sure_frame_is_on_screen(frame);
	return frame;
}
