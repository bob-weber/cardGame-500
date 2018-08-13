#include <QRect>
#include <QStringBuilder>

#include "card.h"

using namespace std;

Card::Card(Card::Pip pip, Card::Suit suit, Card::Orientation orientation)
{
	this->m_suit = suit;
	this->m_pip = pip;

	// Set this card's face image
	//cout << "Card " << Print() << ", imagePath=" << GetCardImagePath(pip, suit) << endl;
	QString pathStr = QString::fromStdString(GetCardImagePath(pip, suit));
	QImage image = QImage(pathStr);
	QSize imageSize = image.size() / m_imageSizeDivisor;
	this->m_faceImage = image.scaled(imageSize);

	/* Sorting value is ordered with spades as the lowest, then clubs, diamonds, and hearts.
	 * Jokers are the highest.
	 * Aces are sorted above Kings, not as 1s.
	 */
	this->m_sortValue = uint(pip) + uint(suit) * uint(PIP_NUMBER_OF_PIPS);
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

uint Card::GetSortValue() const
{
	return this->m_sortValue;
}

qreal Card::GetImageDivisor() const
{
	return this->m_imageSizeDivisor;
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
