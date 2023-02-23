/**
 * @file Item.h
 * @author timan
 *
 * Base class for any item in our aquarium.
 */

#ifndef AQUARIUM_ITEM_H
#define AQUARIUM_ITEM_H

class Aquarium;
class Fish;

/**
 * Base class for any item in our aquarium.
 */
class Item {
private:
	/// The aquarium this item is contained in
	Aquarium *mAquarium;

	// Item location in the aquarium
	double  mX = 0;     ///< X location for the center of the item
	double  mY = 0;     ///< Y location for the center of the item

	/// The underlying fish image
	std::unique_ptr<wxImage> mItemImage;

	/// The bitmap we can display for this fish
	std::unique_ptr<wxBitmap> mItemBitmap;

	bool mMirror = false;   ///< True mirrors the item image

protected:
	/// Constructor
	Item(Aquarium *aquarium, const std::wstring &filename);

public:
	~Item();

	/// Default constructor (disabled)
	Item() = delete;

	/// Copy constructor (disabled)
	Item(const Item &) = delete;

	/// distance equations between items
	double DistanceTo(std::shared_ptr<Item> item);

	/**
	 * The X location of the item
	 * @return X location in pixels
	 */
	double GetX() const { return mX; }

	/**
	 * The Y location of the item
	 * @return Y location in pixels
	 */
	double GetY() const { return mY; }

	/**
	 * Setter for item position mX
	 * @param x double holding item position
	 */
	void SetX(double x) {mX = x;}

	/**
 	* Setter for item position mX
 	* @param y double holding item position
 	*/
	void SetY(double y) {mY = y;}

	/**
	 * a getter for the mItemBitmap member function
	 *  @return the bitmap member
	 */
	wxBitmap GetBitmap() {return *mItemBitmap;}

	/**
	 * Set the item location
	 * @param x X location in pixels
	 * @param y Y location in pixels
	 */
	void SetLocation(double x, double y) { mX = x; mY = y; }

	void Draw(wxDC *dc);

	/**
	 * Test this item to see if it has been clicked on
	 * @param x X location on the aquarium to test in pixels
	 * @param y Y location on the aquarium to test in pixels
	 * @return true if clicked on
	 */
	bool HitTest(int x, int y);

	/**
 	* Get the pointer to the Aquarium object
 	* @return Pointer to Aquarium object
 	*/
	Aquarium *GetAquarium() { return mAquarium;  }

	virtual wxXmlNode* XmlSave(wxXmlNode *node);

	void XmlLoad(wxXmlNode *node);

	/**
 	* Handle updates for animation
 	* @param elapsed The time since the last update
 	*/
	virtual void Update(double elapsed) {}

	void SetMirror(bool m);

	};

#endif //AQUARIUM_ITEM_H