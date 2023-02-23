/**
 * @file Nemo.h
 * @author timan
 *
 * a class to describe the nemo image
 */

#ifndef AQUARIUM_AQUARIUM_AQUARIUMLIB_NEMO_H
#define AQUARIUM_AQUARIUM_AQUARIUMLIB_NEMO_H

#include "Fish.h"

/**
 * Class for a fish of type Nemo
 */
class Nemo : public Fish {
private:


public:
	/// Default constructor (disabled)
	Nemo() = delete;

	/// Copy constructor (disabled)
	Nemo(const Nemo &) = delete;

	/// Assignment operator
	void operator=(const Nemo &) = delete;

	Nemo(Aquarium* aquarium);

	wxXmlNode* XmlSave(wxXmlNode* node) override;


};
#endif //AQUARIUM_AQUARIUM_AQUARIUMLIB_NEMO_H
