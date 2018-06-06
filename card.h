#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <string>
#include <iostream>
#include <vector>
#include <QList>
#include <QPixmap>

using namespace std;

class Card : public QObject
{
		Q_OBJECT

	public:
		/**
		 * Cards have a suit, and a pip. Technically, a pip refers to the dots on numeric cards, but for
		 * this class, we use pip to indicate face cards and jokers.
		 * All pips can be one of 4 suits: heart, diamond, spade or club
		 * Jokers can be one of 2 suits: read or black.
		 */

		/* Provide properties reads for suit and PIP
		 */
		enum Suit { SUIT_SPADE = 0, SUIT_CLUB, SUIT_DIAMOND, SUIT_HEART, SUIT_NUMBER_OF_SUITS };
		Q_ENUM(Suit)
		Q_PROPERTY(Suit suit READ getSuit)
		Suit getSuit() const;

		enum Pip { PIP_2 = 0, PIP_3, PIP_4, PIP_5, PIP_6, PIP_7, PIP_8, PIP_9, PIP_10,
			         PIP_JACK, PIP_QUEEN, PIP_KING, PIP_ACE, PIP_JOKER, PIP_NUMBER_OF_PIPS };
		Q_ENUM(Pip)
		Q_PROPERTY(Pip pip READ getPip)
		Pip getPip() const;

		/* Orientation properties. Can be read and written.
		 */
		enum Orientation { FACE_UP, FACE_DOWN };
		Q_ENUM(Orientation)
		Q_PROPERTY(Orientation orientation
		           READ getOrientation
		           WRITE setOrientation
		           NOTIFY orientationChanged)
		Orientation getOrientation() const;
		void setOrientation(Orientation orientation);

		// Rotation varies from 0 to 359 (degrees)
		const unsigned int MIN_ROTATION = 0;
		const unsigned int MAX_ROTATION = 359;
		Q_PROPERTY(unsigned int rotation
		           READ getRotation
		           WRITE setRotation
		           NOTIFY rotationChanged)
		unsigned int getRotation() const;
		void setRotation(unsigned int rotation);

		// Get the card's face image
		QImage getCardImage();

		/** Construcors/destrucors
		 * If no suit or PIP is specified, a 2 of spades will be created.
		 */
		explicit Card(Pip pip = PIP_2, Suit suit = SUIT_SPADE,
		              Orientation orientation = FACE_DOWN, unsigned int rotation = 0,
		              QObject *parent = nullptr);
		virtual ~Card();

		// Convencience operators
		bool operator==(Card &card) {
			return ((this->m_suit == card.m_suit) && (this->m_pip == card.m_pip)) ? true : false;
		}

		Card& operator=(Card& card) {
			this->m_suit = card.m_suit;
			this->m_pip = card.m_pip;
			return *this;
		}

		string Print();

	signals:
		void orientationChanged(Card::Orientation orientation);
		void rotationChanged(unsigned int);

	public slots:

	private:
		Pip m_pip;
		Suit m_suit;
		QImage m_cardImage;

		QString getCardImagePath(Pip pip, Suit suit);

		/* Beyond the specifics of each card, there are useful fields that can be used different games, such
		 * as whether the card is face up/down, or rotated.
		 */
		Orientation m_orientation;		// Is the card face-up or down.
		unsigned int m_rotation;

		// Map all pips and suits to a resource path
		const QString basePath = ":/resources/cardImages/cards-svg/SVG-cards-1.3/";
		const QString resourcePath[PIP_NUMBER_OF_PIPS][SUIT_NUMBER_OF_SUITS] = {
		  //Spades                 Clubs                 Diamonds                 Hearts
		  //-------------------    -----------------     -------------------      -------------------
		  {	"2_of_spades.svg",     "2_of_clubs.svg",     "2_of_diamonds.svg",     "2_of_hearts.svg" },
		  {	"3_of_spades.svg",     "3_of_clubs.svg",     "3_of_diamonds.svg",     "3_of_hearts.svg" },
		  {	"4_of_spades.svg",     "4_of_clubs.svg",     "4_of_diamonds.svg",     "4_of_hearts.svg" },
		  {	"5_of_spades.svg",     "5_of_clubs.svg",     "5_of_diamonds.svg",     "5_of_hearts.svg" },
		  {	"6_of_spades.svg",     "6_of_clubs.svg",     "6_of_diamonds.svg",     "6_of_hearts.svg" },
		  {	"7_of_spades.svg",     "7_of_clubs.svg",     "7_of_diamonds.svg",     "7_of_hearts.svg" },
		  {	"8_of_spades.svg",     "8_of_clubs.svg",     "8_of_diamonds.svg",     "8_of_hearts.svg" },
		  {	"9_of_spades.svg",     "9_of_clubs.svg",     "9_of_diamonds.svg",     "9_of_hearts.svg" },
		  {	"10_of_spades.svg",    "10_of_clubs.svg",    "10_of_diamonds.svg",    "10_of_hearts.svg" },
		  {	"jack_of_spades.svg",  "jack_of_clubs.svg",  "jack_of_diamonds.svg",  "jack_of_hearts.svg" },
		  {	"queen_of_spades.svg", "queen_of_clubs.svg", "queen_of_diamonds.svg", "queen_of_hearts.svg" },
		  {	"king_of_spades.svg",  "king_of_clubs.svg",  "king_of_diamonds.svg",  "king_of_hearts.svg" },
		  {	"ace_of_spades.svg",   "ace_of_clubs.svg",   "ace_of_diamonds.svg",   "ace_of_hearts.svg" },
		  {	"black_jokcer.svg",    "black_jokcer.svg",   "red_jokcer.svg",        "red_jokcer.svg" }
		};
};

Q_DECLARE_METATYPE(Card::Orientation)

#endif // CARD_H
