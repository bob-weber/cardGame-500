# Phase 0
## Major tasks
* Goall: Working game, with manual play. User must control each player's hand.
- [x] Add card rotation
- [x] Add Menu new game
- [x] Add menu quit
- [ ] Add menu about, game information
- [ ] Add teams
- [x] Add bidding capability
  * Complete. Bids are verified to be valid, including double nellow, which requires partner bid nellow.
  * Bids are displayed on the table as they're made.
  * Invalid bids result in player being able to rebid.
- [x] Add card play to merge winning bid with kitty.
- [ ] Test card play for validity/prevent illegal moves
- [ ] Add scoring
- [ ] Pop-up after each hand, indicating:
  * score for that round
  * total game score
- [ ] Handle completing a game

## Minor tasks
- [ ] Save game settings to a file, accessible to various dialogs, like window position.
  - [ ] Then save bidding dialog position, so bidding on different rounds can get the position.
- [ ] When removing cards from the table, remove the image. Right now, this problem isn't obvious because we redeal.
- [ ] Find a better way to map label events from the GUI to which object to update.
- [x] Sort cards in hands by suit, allowing for a trump suit.
- [x] Add version information

# Phase 0.5
- [ ] Add testing for card class
- [ ] Add testing for deck class
- [ ] Add testing for player class
- [ ] Add testing for team class
- [ ] Add testing for game logic class

# Phase 1
* Ability to play against the computer
- [ ] Add computerized game play
* TODO: Much improvement expected to be needed.

# Phase 2
* Rewrite graphics to support card motion, overlay, etc.
* Purposely left vague at this time. Define better when it's time.
* Likely use graphics view.
