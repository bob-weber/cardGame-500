#include <QRect>
#include <QStringBuilder>

#include "card.h"

using namespace std;

Card::Card(Card::Pip pip, Card::Suit suit, Card::Orientation orientation, unsigned int rotation, QObject *parent)
{
	this->m_suit = suit;
	this->m_pip = pip;
	this->m_orientation = orientation;
	this->m_rotation = rotation;
	cout << "Card " << Print() << ", imagePath=" << getCardImagePath(pip, suit) << endl;
	QString pathStr = QString::fromStdString(getCardImagePath(pip, suit));
	this->m_cardImage = QImage(pathStr);
}

Card::~Card()
{
}

/** Property functions
 */
Card::Suit Card::getSuit() const {
	return this->m_suit;
}

Card::Pip Card::getPip() const {
	return this->m_pip;
}

Card::Orientation Card::getOrientation() const {
	return this->m_orientation;
}

void Card::setOrientation(Orientation orientation) {
	if (orientation != this->m_orientation) {
		this->m_orientation = orientation;
		emit orientationChanged(orientation);
	}
}

unsigned int Card::getRotation() const {
	return this->m_rotation;
}

/* Only change rotation if it's valid, and different than the current rotation.
 * Requiring the rotation to be different means we only send a notification when the rotation has really changed.
 */
void Card::setRotation(unsigned int rotation) {
	if ((rotation >= MIN_ROTATION) &&
	    (rotation <= MAX_ROTATION) &&
	    (rotation != this->m_rotation))
	{
		this->m_rotation = rotation;
		emit rotationChanged(rotation);
	}
}

QImage Card::getCardImage()
{
	return m_cardImage;
}


string Card::getCardImagePath(Card::Pip pip, Card::Suit suit)
{
	string imagePath = basePath + resourcePath[pip][suit];
	return imagePath;
}

string Card::Print(void)
{
	string zPip = "";
	string zSuit = "";
	switch (m_pip)
	{
		case PIP_2:     zPip = "2";     break;
		case PIP_3:     zPip = "3";     break;
		case PIP_4:     zPip = "4";     break;
		case PIP_5:     zPip = "5";     break;
		case PIP_6:     zPip = "6";     break;
		case PIP_7:     zPip = "7";     break;
		case PIP_8:     zPip = "8";     break;
		case PIP_9:     zPip = "9";     break;
		case PIP_10:    zPip = "10";    break;
		case PIP_JACK:  zPip = "J";     break;
		case PIP_QUEEN: zPip = "Q";     break;
		case PIP_KING:  zPip = "K";     break;
		case PIP_ACE:   zPip = "A";     break;
		case PIP_JOKER: zPip = "Joker"; break;
		default:                        break; // Invalid pip
	}

	switch (m_suit)
	{
		case SUIT_HEART:   zSuit = "H"; break;
		case SUIT_DIAMOND: zSuit = "D"; break;
		case SUIT_SPADE:   zSuit = "S"; break;
		case SUIT_CLUB:    zSuit = "C"; break;
		default:                        break;	// Invalid suit
	}

	return zPip + ":" + zSuit;
}
