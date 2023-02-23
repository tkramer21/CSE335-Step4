/**
 * @file Fish.cpp
 * @author timan
 */

#include "pch.h"
#include "Fish.h"

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 50;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 20;

/**
 * Constructor
 * @param aquarium The aquarium we are in
 * @param filename Filename for the image we use
 */
Fish::Fish(Aquarium *aquarium, const std::wstring &filename) : Item(aquarium, filename)
{
	std::uniform_real_distribution<> distribution(MinSpeedX, MaxSpeedX);
	mSpeedX = distribution(aquarium->GetRandom());
	mSpeedY = distribution(aquarium->GetRandom());
}

/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * @param elapsed Time elapsed since the class call
 */
void Fish::Update(double elapsed)
{
	SetLocation(GetX() + mSpeedX * elapsed,
				GetY() + mSpeedY * elapsed);

	if (mSpeedX > 0 && GetX() + GetBitmap().GetWidth()/2 + 10 >= GetAquarium()->GetWidth())
	{
		mSpeedX = -mSpeedX;
		SetMirror(true);
	}

	else if (mSpeedX < 0 && GetX() - GetBitmap().GetWidth()/2 - 10 <= 0)
		{
			mSpeedX = -mSpeedX;
			SetMirror(false);
		}

	else if (mSpeedY > 0 && GetY() + GetBitmap().GetHeight()/2 + 10 >= GetAquarium()->GetHeight())
	{
		mSpeedY = -mSpeedY;
	}

	else if (mSpeedY < 0 && GetY() - GetBitmap().GetHeight()/2 - 10 <= 0)
	{
		mSpeedY = -mSpeedY;
	}
}
/**
 * This function gets information from the XML node and uses the Fish getter & setter
 * to set
 * @param node
 */
void Fish::XmlLoad(wxXmlNode *node)
{
	double tempX;
	double tempY;

	node->GetAttribute(L"speedx", L"0").ToDouble(&mSpeedX);
	node->GetAttribute(L"speedy", L"0").ToDouble(&mSpeedY);

	node->GetAttribute(L"x", L"0").ToDouble(&tempX);
	node->GetAttribute(L"y", L"0").ToDouble(&tempY);

	this->SetX(tempX);
	this->SetY(tempY);

	if(this->mSpeedX < 0)
	{
		this->SetMirror(true);
	}
}
