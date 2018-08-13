#ifndef UTILITIES_H
#define UTILITIES_H

#include <QObject>

/******************************************************************************************************************
 * Utility function to wrap around a uint that counts through a set number of items.
 *
 * Inputs:
 *	itemIndex:	The index to increment.
 *	numOfItems: Number of items in the list.
 *
 * Outputs:
 *	Returns the new index value.
 *
 * Notes:
 *	If numOfItems is 4, then itemIndex will be between 0 and 3.
 ******************************************************************************************************************/
unsigned int advanceIndex(unsigned int itemIndex, const unsigned int numOfItems);


/******************************************************************************************************************
 * Set, clear and determine if a bit is set. This is to make bit-packing flags easier.
 *
 * Inputs:
 *	data:		32-bit data to manipulte.
 *	bit:		The bit to set, clear or check.
 *
 * Outputs:
 *	SetBit/ClearBit/ToggleBit:	The specified bit is updated.
 *	IsBitSet:	If the bit is set, returns true; otherwise returns false.
 ******************************************************************************************************************/
void SetBit(uint32_t data, uint bit);
void ClearBit(uint32_t data, uint bit);
void ToggleBit(uint32_t data, uint bit);
bool IsBitSet(uint32_t data, uint bit);

#endif // UTILITIES_H
