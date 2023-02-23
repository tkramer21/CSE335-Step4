/**
 * @file AquariumApp.cpp
 * @author timan
 */

#include "pch.h"
#include "AquariumApp.h"
#include <MainFrame.h>

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif



/**
 * Initialize the application.
 * @return a boolean
 */
bool AquariumApp::OnInit()
{
	#ifdef WIN32
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	if (!wxApp::OnInit())
		return false;

	// Add image type handlers
	wxInitAllImageHandlers();

	auto frame = new MainFrame();
	frame->Initialize();
	frame->Show(true);

	return true;
}