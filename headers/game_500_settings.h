#ifndef GAME500_SETTINGS_H
#define GAME500_SETTINGS_H

/* Define some game parameters that are needed by various classes.
 */
#define NUM_OF_CARDS_PER_PLAYER		10
#define NUM_OF_CARDS_IN_KITTY			5
#define NUM_OF_CARDS_TO_PLAY			4

#define NUM_OF_TEAMS							2
#define NUM_OF_PLAYERS						4
#define NUM_OF_HANDS_TO_DEAL			5		// We deal to 4 players plus the kitty
#define NUM_OF_HANDS							(NUM_OF_PLAYERS + 2)	// includes the kitty and the play area

/* Index into array of hands to get to the kitty
 * Players are indices 0 through 3
 */
#define KITTY_INDEX								4
#define PLAY_AREA_INDEX						5

#endif // GAME500_SETTINGS_H
