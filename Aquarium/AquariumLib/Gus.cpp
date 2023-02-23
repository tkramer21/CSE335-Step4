/**
 * @file Gus.cpp
 * @author timan
 */

#include "pch.h"
#include "Gus.h"
#include "Aquarium.h"


using namespace std;

/// Fish filename for gus png
const wstring FishGusImageName = L"images/gus.png";
/// Fish filenam for gus-f png
const wstring FishGusImageName2 = L"images/gus-f.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
Gus::Gus(Aquarium *aquarium) : Item(aquarium)
{
	mFishImage = make_unique<wxImage>(FishGusImageName, wxBITMAP_TYPE_ANY);
	mFishBitmap = make_unique<wxBitmap>(*mFishImage);
}

/**
 * Class that changes Gus' image to the gus-f image
 * @param imagePath
 */
void Gus::FishImageSet(const wxString& imagePath)
{
	mFishImage = make_unique<wxImage>(imagePath, wxBITMAP_TYPE_ANY);
	mFishBitmap = make_unique<wxBitmap>(*mFishImage);
}

/**
 * getter for the data member mFishImage
 * @return wxImage type
 */
wxImage& Gus::GetFishImage()
{
	return *mFishImage;
}

/**
 * Draw this fish
 * @param dc Device context to draw on
 */
void Gus::Draw(wxDC *dc)
{
	double wid = mFishBitmap->GetWidth();
	double hit = mFishBitmap->GetHeight();
	dc->DrawBitmap(*mFishBitmap,
				   int(GetX() - wid / 2),
				   int(GetY() - hit / 2));
}

/**
 * Test to see if we hit this object with a mouse.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Gus::HitTest(int x, int y)
{
	double wid = mFishBitmap->GetWidth();
	double hit = mFishBitmap->GetHeight();

	// Make x and y relative to the top-left corner of the bitmap image
	// Subtracting the center makes x, y relative to the image center
	// Adding half the size makes x, y relative to theimage top corner
	double testX = x - GetX() + wid / 2;
	double testY = y - GetY() + hit / 2;

	// Test to see if x, y are in the image
	if(testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the image
		return false;
	}

	// Test to see if x, y are in the drawn part of the image
	// If the location is transparent, we are not in the drawn
	// part of the image
	return !mFishImage->IsTransparent((int)testX, (int)testY);
}
/**
 * Test to see if a click or double click on gus was executed
 * @param event a wxMouseEvent
 * @param gus a ref to a shared_ptr of class gus
 * @param aquarium a pointer to aquarium class
 */
void Gus::OnGusClick(wxMouseEvent &event, std::shared_ptr<Gus> &gus, Aquarium* aquarium)
{
	if (event.LeftDClick())
	{
		FishImageSet(FishGusImageName2);
		for(auto fishies : aquarium->GetItems())
		{
			if(fishies != gus)
			{
				fishies->MoveFish(gus);
			}
		}
	}
	else if (event.LeftDown())
	{
		FishImageSet(FishGusImageName);
	}
}