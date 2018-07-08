#include "utilities.h"

unsigned int advanceIndex(unsigned int itemIndex, const unsigned int numOfItems)
{
	if (itemIndex >= (numOfItems - 1))
	{	// We're at the end of the list of items
		itemIndex = 0;
	}
	else {
		// Not at the end of the items. Advance the index.
		++itemIndex;
	}
	return itemIndex;
}
