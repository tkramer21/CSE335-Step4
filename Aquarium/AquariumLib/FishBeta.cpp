/**
 * @file FishBeta.cpp
 * @author timan
 */

#include "pch.h"
#include "FishBeta.h"
#include "Aquarium.h"

using namespace std;

/// Fish filename
const wstring FishBetaImageName = L"images/beta.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishBeta::FishBeta(Aquarium *aquarium) : Fish(aquarium, FishBetaImageName)
{

}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* FishBeta::XmlSave(wxXmlNode* node)
{
	auto itemNode = Item::XmlSave(node);
	itemNode->AddAttribute(L"type", L"beta");
	itemNode->AddAttribute(L"speedx", wxString::FromDouble(this->GetSpeedX()));
	itemNode->AddAttribute(L"speedy", wxString::FromDouble(this->GetSpeedY()));

	return itemNode;
}