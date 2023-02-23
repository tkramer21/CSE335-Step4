/**
 * @file Aquarium.cpp
 * @author timan
 */

#include "pch.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "Nemo.h"
#include "Angler.h"
#include "DecorCastle.h"


using namespace std;

/// Initial fish X location
const int InitialX = 200;

/// Initial fish Y location
const int InitialY = 200;

/**
 * Aquarium Constructor
 */
Aquarium::Aquarium()
{
	mBackground = make_unique<wxBitmap>(
		L"images/background1.png", wxBITMAP_TYPE_ANY);

	// Seed the random number generator
	std::random_device rd;
	mRandom.seed(rd());
}

/**
 * Draw the aquarium
 * @param dc The device context to draw on
 */
void Aquarium::OnDraw(wxDC *dc)
{
	dc->DrawBitmap(*mBackground, 0, 0);

	wxFont font(wxSize(0, 20),
				wxFONTFAMILY_SWISS,
				wxFONTSTYLE_NORMAL,
				wxFONTWEIGHT_NORMAL);
	dc->SetFont(font);
	dc->SetTextForeground(wxColour(0, 64, 0));
	dc->DrawText(L"Under the Sea!", 10, 10);

	for (auto item : mItems)
	{
		item->Draw(dc);
	}
}

/**
 * Add an item to the aquarium
 * @param item New item to add
 */
void Aquarium::Add(std::shared_ptr<Item> item)
{
	double X = InitialX;
	double Y = InitialY;
	item->SetLocation(X, Y);

	for (auto newItem : mItems)
	{
		for (auto newItem : mItems)
		{
			if(newItem->DistanceTo(item) == 0.0)
			{
				X += 10;
				Y += 10;
			}
		}
	}
	item->SetLocation(X, Y);
	mItems.push_back(item);
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the aquarium.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Aquarium::HitTest(int x, int y)
{
	for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}

	return  nullptr;
}
/**
 * Class to move an item to the back of a vector so that the
 * image is displayed on top
 * @param item reference to an item
 */
void Aquarium::MoveToBack(shared_ptr<Item> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
		mItems.push_back(item);
	}
}

/**
 * A Getter for the member mItems of Aquarium
 * @return a vector of shared pointers of type items
 */
std::vector<std::shared_ptr<Item>> Aquarium::GetItems()
{
	return mItems;
}

/**
 * Save the aquarium as a .aqua XML file.
 *
 * Open an XML file and stream the aquarium data to it.
 *
 * @param filename The filename of the file to save the aquarium to
 */
void Aquarium::Save(const wxString &filename)
{
	wxXmlDocument xmlDoc;

	auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"aqua");
	xmlDoc.SetRoot(root);

	// Iterate over all items and save them
	for (auto item : mItems)
	{
		item->XmlSave(root);
	}

	if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
	{
		wxMessageBox(L"Write to XML failed");
		return;
	}
}

/**
 * Load the aquarium from a .aqua XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the aquarium from.
 */
void Aquarium::Load(const wxString &filename)
{
	wxXmlDocument xmlDoc;
	if(!xmlDoc.Load(filename))
	{
		wxMessageBox(L"Unable to load Aquarium file");
		return;
	}

	Clear();

	// Get the XML document root node
	auto root = xmlDoc.GetRoot();

	//
	// Traverse the children of the root
	// node of the XML document in memory!!!!
	//
	auto child = root->GetChildren();
	for( ; child; child=child->GetNext())
	{
		auto name = child->GetName();
		if(name == L"item")
		{
			XmlItem(child);
		}
	}
}

/**
 * Clear the aquarium data.
 *
 * Deletes all known items in the aquarium.
 */
void Aquarium::Clear()
{
	mItems.clear();
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Aquarium::XmlItem(wxXmlNode *node)
{
	// A pointer for the item we are loading
	shared_ptr<Item> item;
	shared_ptr<Fish> fish;

	// We have an item. What type?
	auto type = node->GetAttribute(L"type");

	if(type != L"castle")
	{
		if (type == L"beta")
		{
			fish = make_shared<FishBeta>(this);
		}

		else if (type == L"angler")
		{
			fish = make_shared<Angler>(this);
		}

		else if (type == L"nemo")
		{
			fish = make_shared<Nemo>(this);
		}
	}

	else if (type == L"castle")
	{
		item = make_shared<DecorCastle>(this);
	}

	if (item != nullptr)
	{
		Add(item);
		item->XmlLoad(node);
	}

	else if (fish != nullptr)
	{
		Add(fish);
		fish->XmlLoad(node);
	}
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Aquarium::Update(double elapsed)
{
	for (auto item : mItems)
	{
		item->Update(elapsed);
	}
}
