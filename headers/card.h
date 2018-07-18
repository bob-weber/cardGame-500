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
		Q_PROPERTY(Suit suit READ GetSuit)
		Suit GetSuit() const;

		enum Pip { PIP_2 = 0, PIP_3, PIP_4, PIP_5, PIP_6, PIP_7, PIP_8, PIP_9, PIP_10,
			         PIP_JACK, PIP_QUEEN, PIP_KING, PIP_ACE, PIP_JOKER, PIP_NUMBER_OF_PIPS };
		Q_ENUM(Pip)
		Q_PROPERTY(Pip pip READ GetPip)
		Pip GetPip() const;

		/* Orientation properties. Can be read and written.
		 */
		enum Orientation { FACE_UP, FACE_DOWN };
		Q_ENUM(Orientation)
		Q_PROPERTY(Orientation orientation
		           READ GetOrientation
		           WRITE SetOrientation
		           NOTIFY OrientationChanged)
		Orientation GetOrientation() const;
		void SetOrientation(Orientation orientation);
		Orientation FlipOrientation();

		Q_PROPERTY(QImage m_backImage
		           READ GetBackImage)
		QImage GetBackImage() const;
		void SetBackImage();

		Q_PROPERTY(bool m_Selected
		           READ IsSelected
		           WRITE SetSelected)
		bool IsSelected() const;
		void SetSelected(bool raise);

		// Get the card's face image
		QImage GetFaceImage();

		/** Construcors/destrucors
		 * If no suit or PIP is specified, a 2 of spades will be created.
		 */
		explicit Card(Pip pip = PIP_2, Suit suit = SUIT_SPADE,
		              Orientation orientation = FACE_DOWN);
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
		void OrientationChanged(Orientation orientation);

	public slots:

	private:
		Pip m_pip;
		Suit m_suit;

		string GetCardImagePath(Pip pip, Suit suit);

		/* Beyond the specifics of each card, there are useful fields that can be used different games, such
		 * as whether the card is face up/down, or rotated.
		 */
		Orientation m_orientation;		// Is the card face-up or down.
		bool m_Selected;									// Raised up to show it's selected

		// Scale images to 1/4 their size. TODO: Make this adjustable based on table size.
		const float m_imageSizeDivisor = 4.0;

		QImage m_faceImage;
		// Map all pips and suits to a resource path
		const string basePath = ":/resources/cardImages/cards-compact/faces/";
		const string cardImageName[PIP_NUMBER_OF_PIPS][SUIT_NUMBER_OF_SUITS] = {
		  //Spades                      Clubs                      Diamonds                      Hearts
		  //-------------------         -----------------          -------------------           -------------------
		  {	"2_of_spades.svg",          "2_of_clubs.svg",          "2_of_diamonds.svg",          "2_of_hearts.svg" },
		  {	"3_of_spades.svg",          "3_of_clubs.svg",          "3_of_diamonds.svg",          "3_of_hearts.svg" },
		  {	"4_of_spades.svg",          "4_of_clubs.svg",          "4_of_diamonds.svg",          "4_of_hearts.svg" },
		  {	"5_of_spades.svg",          "5_of_clubs.svg",          "5_of_diamonds.svg",          "5_of_hearts.svg" },
		  {	"6_of_spades.svg",          "6_of_clubs.svg",          "6_of_diamonds.svg",          "6_of_hearts.svg" },
		  {	"7_of_spades.svg",          "7_of_clubs.svg",          "7_of_diamonds.svg",          "7_of_hearts.svg" },
		  {	"8_of_spades.svg",          "8_of_clubs.svg",          "8_of_diamonds.svg",          "8_of_hearts.svg" },
		  {	"9_of_spades.svg",          "9_of_clubs.svg",          "9_of_diamonds.svg",          "9_of_hearts.svg" },
		  {	"10_of_spades.svg",         "10_of_clubs.svg",         "10_of_diamonds.svg",         "10_of_hearts.svg" },
		  {	"jack_of_spades_face.svg",  "jack_of_clubs_face.svg",  "jack_of_diamonds_face.svg",  "jack_of_hearts_face.svg" },
		  {	"queen_of_spades_face.svg", "queen_of_clubs_face.svg", "queen_of_diamonds_face.svg", "queen_of_hearts_face.svg" },
		  {	"king_of_spades_face.svg",  "king_of_clubs_face.svg",  "king_of_diamonds_face.svg",  "king_of_hearts_face.svg" },
		  {	"ace_of_spades_fancy.svg",  "ace_of_clubs.svg",        "ace_of_diamonds.svg",        "ace_of_hearts.svg" },
		  {	"joker_black.svg",          "joker_black.svg",         "joker_red.svg",              "joker_red.svg" }
		};

		// Set the deck's back image
		static QImage m_backImage;
		const QString m_cardBackImagePath = ":/resources/cardImages/cards-compact/backs/blue_solid.svg";
};

Q_DECLARE_METATYPE(Card::Orientation)

#endif // CARD_H
