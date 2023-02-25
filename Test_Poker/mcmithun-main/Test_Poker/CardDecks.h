/* 
 * File which represents the Card deck and its features
 */
#include "Card.h"
#include <memory>
#include <random>
#include <algorithm>

using namespace std;

const int TOTAL_CARDS = 52;

class CardDecks : public Card
{
public:
    const int maxCardInHand = 5;
    CardDecks();
    ~CardDecks();

    const vector<Card> &getDeck() const { return deck; }
    void CreateDeckOfCard();
    void DoShuffleCards();
    void Show(const vector<Card> &);

private:
    vector<Card> deck; // Deck of Cards
};

CardDecks::CardDecks()
{
    CreateDeckOfCard();
}

CardDecks::~CardDecks()
{
}

void CardDecks::CreateDeckOfCard()
{
    for (size_t i = hearts; i <= clubs; i++)
    {
        for (size_t j = two; j <= ace; j++)
        {
            deck.emplace_back(Card((Suit)i, (Value)j));
        }
    }
    // After creating all the combinations, do shuffle the cards.
    DoShuffleCards();
    return;
}

void CardDecks::DoShuffleCards()
{
    auto rand_eng = std::default_random_engine{};
    std::shuffle(deck.begin(), deck.end(), rand_eng);
    return;
}

void CardDecks::Show(const vector<Card> &_list)
{
    for_each(_list.begin(), _list.end(), [&](const Card &_card)
             { std::cout << _card << std::endl; });
}