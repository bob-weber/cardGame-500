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

void SetBit(uint32_t data, uint bit)
{
	uint32_t bitMask = (1 << bit);
	data |= bitMask;
}

void ClearBit(uint32_t data, uint bit)
{
	uint32_t bitMask = (1 << bit);
	data &= ~bitMask;
}

void ToggleBit(uint32_t data, uint bit)
{
	uint32_t bitMask = (1 << bit);
	data ^= bitMask;
}

bool IsBitSet(uint32_t data, uint bit)
{
	uint32_t bitMask = (1 << bit);
	return ((data & bitMask) != 0);
}
