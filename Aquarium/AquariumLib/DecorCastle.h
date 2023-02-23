/**
 * @file DecorCastle.h
 * @author timan
 *
 * Describes a class that displays an image of a castle in the aquarium
 */

#ifndef AQUARIUM_AQUARIUM_AQUARIUMLIB_DECORCASTLE_H
#define AQUARIUM_AQUARIUM_AQUARIUMLIB_DECORCASTLE_H

#include "Aquarium.h"
/**
 * Class describing the Castle Item in the aquarium
 */
class DecorCastle : public Item {
private:

public:
	/// Default constructor (disabled)
	DecorCastle() = delete;

	/// Copy constructor (disabled)
	DecorCastle(const DecorCastle &) = delete;

	/// Assignment operator
	void operator=(const DecorCastle &) = delete;

	DecorCastle(Aquarium* aquarium);

	wxXmlNode* XmlSave(wxXmlNode* node) override;


};

#endif //AQUARIUM_AQUARIUM_AQUARIUMLIB_DECORCASTLE_H
