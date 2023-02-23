/**
 * @file Fish.h
 * @author timan
 *
 * A class describing the fish in the aquarium
 */

#ifndef AQUARIUM_AQUARIUM_AQUARIUMLIB_FISH_H
#define AQUARIUM_AQUARIUM_AQUARIUMLIB_FISH_H

#include "Item.h"
#include "Aquarium.h"
#include <string>

/**
 * Base class for a fish
 * This applies to all of the fish, but not the decor items in the aquarium
 */
class Fish : public Item
{
private:
	/// Fish speed in the X direction
	/// in pixels per second
	double mSpeedX;

	/// Fish speed in the Y direction
	/// in pixels per second
	double mSpeedY;

public:
	/// Default constructor (disabled)
	Fish() = delete;

	/// Copy constructor (disabled)
	Fish(const Fish &) = delete;

	/// Assignment operator
	void operator=(const Fish &) = delete;

	///
	void Update(double elapsed);

	/**
	 * getter for the Fish speed on x-axis
	 * @return
	 */
	double GetSpeedX() {return mSpeedX;}

	/**
	 * getter for the Fish speed on y-axis
	 * @return
	 */
	double GetSpeedY() {return mSpeedY;}

	/**
	 * A setter for the fish speed on the x-axis
	 *
	 * @param speedX double to set speedX
	 */
	void SetSpeedX(double speedX) {mSpeedX = speedX;}

	/**
	 * A setter for the fish speed on the y-axis
	 *
	 * @param speedY doubel to set speedY
	 */
	void SetSpeedY(double speedY) {mSpeedY = speedY;}

	void XmlLoad(wxXmlNode *node);



protected:
	Fish(Aquarium *aquarium, const std::wstring &filename);


};

#endif //AQUARIUM_AQUARIUM_AQUARIUMLIB_FISH_H
