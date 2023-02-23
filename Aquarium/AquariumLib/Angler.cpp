/**
 * @file Angler.cpp
 * @author timan
 */

#include "pch.h"
#include "Angler.h"
#include "Aquarium.h"
#include "Fish.h"

using namespace std;

/// Fish filename
const wstring FishAnglerImageName = L"images/angler.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
Angler::Angler(Aquarium *aquarium) : Fish(aquarium, FishAnglerImageName)
{
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* Angler::XmlSave(wxXmlNode* node)
{
	auto itemNode = Item::XmlSave(node);
	itemNode->AddAttribute(L"type", L"angler");
	itemNode->AddAttribute(L"speedx", wxString::FromDouble(this->GetSpeedX()));
	itemNode->AddAttribute(L"speedy", wxString::FromDouble(this->GetSpeedY()));

	return itemNode;
}