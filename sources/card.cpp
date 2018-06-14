#include <QRect>
#include <QStringBuilder>

#include "card.h"

using namespace std;

// Declare our deck's back image
// There's only one image used for all cards
QImage Card::m_backImage;

Card::Card(Card::Pip pip, Card::Suit suit, Card::Orientation orientation, unsigned int rotation)
{
	this->m_suit = suit;
	this->m_pip = pip;
	this->m_orientation = orientation;
	this->m_rotation = rotation;

	// Set this card's face image
	//cout << "Card " << Print() << ", imagePath=" << GetCardImagePath(pip, suit) << endl;
	QString pathStr = QString::fromStdString(GetCardImagePath(pip, suit));
	QImage image = QImage(pathStr);
	QSize imageSize = image.size() / m_imageSizeDivisor;
	this->m_faceImage = image.scaled(imageSize);
}

Card::~Card()
{
}

/** Property functions
 */
Card::Suit Card::GetSuit() const {
	return this->m_suit;
}

Card::Pip Card::GetPip() const {
	return this->m_pip;
}

Card::Orientation Card::GetOrientation() const {
	return this->m_orientation;
}

void Card::SetOrientation(Orientation orientation) {
	if (orientation != this->m_orientation) {
		this->m_orientation = orientation;
		emit OrientationChanged(orientation);
	}
}

Card::Orientation Card::FlipOrientation()
{
	Orientation orientation = GetOrientation();
	orientation = (orientation == FACE_DOWN) ? FACE_UP : FACE_DOWN;
	SetOrientation(orientation);
	return orientation;
}

QImage Card::GetBackImage() const
{
	return m_backImage;
}

void Card::SetBackImage()
{
	QImage image = QImage(m_cardBackImagePath);
	QSize imageSize = image.size() / m_imageSizeDivisor;
	m_backImage = image.scaled(imageSize);
}

unsigned int Card::GetRotation() const {
	return this->m_rotation;
}

/* Only change rotation if it's valid, and different than the current rotation.
 * Requiring the rotation to be different means we only send a notification when the rotation has really changed.
 */
void Card::SetRotation(unsigned int rotation) {
	if ((rotation >= MIN_ROTATION) &&
	    (rotation <= MAX_ROTATION) &&
	    (rotation != this->m_rotation))
	{
		this->m_rotation = rotation;
		emit RotationChanged(rotation);
	}
}

QImage Card::GetFaceImage()
{
	return m_faceImage;
}


string Card::GetCardImagePath(Card::Pip pip, Card::Suit suit)
{
	string imagePath = basePath + cardImageName[pip][suit];
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
