/**
 * @file Angler.h
 * @author timan
 *
 * A class describing the angler class
 */

#ifndef AQUARIUM_AQUARIUM_AQUARIUMLIB_ANGLER_H
#define AQUARIUM_AQUARIUM_AQUARIUMLIB_ANGLER_H

#include "Fish.h"

/**
 * Class for a fish of type Angler
 */
class Angler : public Fish {
private:

public:
	/// Default constructor (disabled)
	Angler() = delete;

	/// Copy constructor (disabled)
	Angler(const Angler &) = delete;

	/// Assignment operator
	void operator=(const Angler &) = delete;

	Angler(Aquarium* aquarium);

	wxXmlNode* XmlSave(wxXmlNode* node) override;


};


#endif //AQUARIUM_AQUARIUM_AQUARIUMLIB_ANGLER_H
