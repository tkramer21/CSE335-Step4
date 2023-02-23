/**
 * @file AquariumView.h
 * @author timan
 *
 *
 */

#ifndef AQUARIUM_AQUARIUMLIB_AQUARIUMVIEW_H
#define AQUARIUM_AQUARIUMLIB_AQUARIUMVIEW_H
#include "Aquarium.h"
#include "ids.h"
#include "Item.h"

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Class creating the window view
 *
 * Objects will be displayed on this view
 */
class AquariumView : public wxWindow
{
private:
	/// An object that describes our aquarium
	Aquarium mAquarium;

	/// Any item we are currently dragging
	std::shared_ptr<Item> mGrabbedItem;

	/// The timer that allows for animation
	wxTimer mTimer;

	/// Stopwatch used to measure elapsed time
	wxStopWatch mStopWatch;

	/// The last stopwatch time
	long mTime = 0;

	void OnAddFishBetaFish(wxCommandEvent& event);
	void OnAddFishAnglerFish(wxCommandEvent& event);
	void OnAddNemoFish(wxCommandEvent& event);
	void OnAddDecorCastle(wxCommandEvent& event);


	void OnFileSaveAs(wxCommandEvent &event);
	void OnFileOpen(wxCommandEvent& event);
	void OnTimer(wxTimerEvent &event);


	void OnLeftDown(wxMouseEvent &event);
	void OnLeftUp(wxMouseEvent &event);
	void OnMouseMove(wxMouseEvent &event);


	void OnPaint(wxPaintEvent& event);


public:
	void Initialize(wxFrame* parent);
};

#endif //AQUARIUM_AQUARIUMLIB_AQUARIUMVIEW_H
