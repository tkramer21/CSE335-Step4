/**
 * @file Gus.h
 * @author timan
 *
 * a class that describes the fish gus
 */

#ifndef AQUARIUM_AQUARIUM_AQUARIUMLIB_GUS_H
#define AQUARIUM_AQUARIUM_AQUARIUMLIB_GUS_H

#include "Item.h"

/**
 * Class for a fish of type Gus
 */
class Gus : public Item {
private:
	/// The underlying fish image
	std::unique_ptr<wxImage> mFishImage;

	/// The bitmap we can display for this fish
	std::unique_ptr<wxBitmap> mFishBitmap;


public:
	/// Default constructor (disabled)
	Gus() = delete;

	/// Copy constructor (disabled)
	Gus(const Gus &) = delete;

	/// Assignment operator
	void operator=(const Gus &) = delete;

	Gus(Aquarium* aquarium);

	void Draw(wxDC* dc) override;

	/// function to test if we hit the item
	bool HitTest(int x, int y) override;

	/// function to test if click or double click was executed
	void OnGusClick(wxMouseEvent &event, std::shared_ptr<Gus> &gus, Aquarium* aquarium);

	void FishImageSet(const wxString& imagePath);


	wxImage& GetFishImage();

};

#endif //AQUARIUM_AQUARIUM_AQUARIUMLIB_GUS_H
