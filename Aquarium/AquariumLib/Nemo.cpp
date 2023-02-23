/**
 * @file Nemo.cpp
 * @author timan
 */


#include "pch.h"
#include "Nemo.h"
#include "Aquarium.h"

using namespace std;

/// Fish filename
const wstring FishNemoImageName = L"images/nemo.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
Nemo::Nemo(Aquarium *aquarium) : Fish(aquarium, FishNemoImageName)
{
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* Nemo::XmlSave(wxXmlNode* node)
{
	auto itemNode = Item::XmlSave(node);
	itemNode->AddAttribute(L"type", L"nemo");
	itemNode->AddAttribute(L"speedx", wxString::FromDouble(this->GetSpeedX()));
	itemNode->AddAttribute(L"speedy", wxString::FromDouble(this->GetSpeedY()));

	return itemNode;
}