#ifndef UTILITIES_H
#define UTILITIES_H

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

#endif // UTILITIES_H
