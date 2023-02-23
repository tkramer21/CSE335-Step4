/**
 * @file AquariumView.cpp
 * @author timan
 */

#include "pch.h"
#include "AquariumView.h"
#include <wx/dcbuffer.h>
#include "FishBeta.h"
#include "Angler.h"
#include "Nemo.h"
#include "DecorCastle.h"

using namespace std;

/**
 * Initialize the aquarium view class.
 * @param parent The parent window for this class
 */
void AquariumView::Initialize(wxFrame* parent)
{
	mTimer.SetOwner(this);
	mTimer.Start(FrameDuration);

	Create(parent, wxID_ANY);
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Bind(wxEVT_PAINT, &AquariumView::OnPaint, this);

	parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
				 &AquariumView::OnAddFishBetaFish, this, IDM_ADDFISHBETA);

	parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
				 &AquariumView::OnAddFishAnglerFish, this, IDM_ADDFISHANGEL);

	parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
				 &AquariumView::OnAddNemoFish, this, IDM_ADDFISHNEMO);

	parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
				 &AquariumView::OnAddDecorCastle, this, IDM_ADDCASTLE);

	Bind(wxEVT_LEFT_DOWN, &AquariumView::OnLeftDown, this);
	Bind(wxEVT_LEFT_UP, &AquariumView::OnLeftUp, this);
	Bind(wxEVT_MOTION, &AquariumView::OnMouseMove, this);
	Bind(wxEVT_TIMER, &AquariumView::OnTimer, this);

	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileSaveAs, this, wxID_SAVEAS);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileOpen, this, wxID_OPEN);

	mStopWatch.Start();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void AquariumView::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);

	// Compute the time that has elapsed
	// since the last call to OnPaint.
	auto newTime = mStopWatch.Time();
	auto elapsed = (double)(newTime - mTime) * 0.001;
	mTime = newTime;

	mAquarium.Update(elapsed);

	wxBrush background(*wxWHITE);
	dc.SetBackground(background);
	dc.Clear();

	mAquarium.OnDraw(&dc);

}

/**
 * Menu hander for Add Fish>Beta Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishBetaFish(wxCommandEvent& event)
{
	auto fish = make_shared<FishBeta>(&mAquarium);
	mAquarium.Add(fish);
	fish->SetSpeedY(fish->GetSpeedY()*2);
	Refresh();
}

/**
 * Menu hander for Add Fish>Angler Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishAnglerFish(wxCommandEvent& event)
{
	auto fish = make_shared<Angler>(&mAquarium);
	mAquarium.Add(fish);
	fish->SetSpeedX(fish->GetSpeedX()*.1);
	Refresh();
}

/**
 * Menu hander for Add Fish>Nemo Fish
 * @param event Mouse event
 */
void AquariumView::OnAddNemoFish(wxCommandEvent& event)
{
	auto fish = make_shared<Nemo>(&mAquarium);
	mAquarium.Add(fish);
	fish->SetSpeedX(fish->GetSpeedX()*5);
	fish->SetSpeedY(fish->GetSpeedY()*5);
	Refresh();
}

/**
 * Menu hander for Add Fish>Castle
 * @param event Mouse event
 */
void AquariumView::OnAddDecorCastle(wxCommandEvent& event)
{
	auto fish = make_shared<DecorCastle>(&mAquarium);
	mAquarium.Add(fish);
	Refresh();
}


/**
 * Handle the left mouse button down event
 * @param event
 */
void AquariumView::OnLeftDown(wxMouseEvent &event)
{
	mGrabbedItem = mAquarium.HitTest(event.GetX(), event.GetY());
	if (mGrabbedItem != nullptr)
	{
		mAquarium.MoveToBack(mGrabbedItem);
	}
}

/**
* Handle the left mouse button down event
* @param event
*/
void AquariumView::OnLeftUp(wxMouseEvent &event)
{
	OnMouseMove(event);
}

/**
* Handle the left mouse button down event
* @param event
*/
void AquariumView::OnMouseMove(wxMouseEvent &event)
{
	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		// If an item is being moved, we only continue to
		// move it while the left button is down.
		if (event.LeftIsDown())
		{
			mGrabbedItem->SetLocation(event.GetX(), event.GetY());
		}
		else
		{
			// When the left button is released, we release the
			// item.
			mGrabbedItem = nullptr;
		}

		// Force the screen to redraw
		Refresh();
	}
}

/**
 * Function that saves the contents of the window
 *
 * @param event a wxCommand Event
 */
void AquariumView::OnFileSaveAs(wxCommandEvent &event)
{
	wxFileDialog saveFileDialog(this, L"Save Aquarium file", L"", L"",
								L"Aquarium Files (*.aqua)|*.aqua", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}

	auto filename = saveFileDialog.GetPath();
	mAquarium.Save(filename);

}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void AquariumView::OnFileOpen(wxCommandEvent& event)
{
	wxFileDialog loadFileDialog(this, L"Load Aquarium file", L"", L"",
								L"Aquarium Files (*.aqua)|*.aqua", wxFD_OPEN);
	if (loadFileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}

	auto filename = loadFileDialog.GetPath();

	mAquarium.Load(filename);

	Refresh();

}
/**
 * Event handler for updating the view
 *
 * @param event a Timer Event
 */
void AquariumView::OnTimer(wxTimerEvent &event)
{
	Refresh();
}