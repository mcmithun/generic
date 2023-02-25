/* 
 * File which represents the Player and its features
 */
#include "CardDecks.h"

class PlayCards
{
private:
    /* data */
    shared_ptr<CardDecks> deckOfCards;
    vector<Card> listOfCardShuffled;
    vector<Card> player1Hand;
    vector<Card> player2Hand;
    vector<Card> player3Hand;

    void DrawFiveInHands();
    void SortInHands();
    void Show();

public:
    PlayCards();
    ~PlayCards();
    void SetupCards();
    const vector<Card> &GetPlayer1Hand() { return player1Hand; }
    const vector<Card> &GetPlayer2Hand() { return player2Hand; }
    const vector<Card> &GetPlayer3Hand() { return player3Hand; }
};

PlayCards::PlayCards()
    : deckOfCards(make_shared<CardDecks>())
{
}

PlayCards::~PlayCards()
{
}

void PlayCards::SetupCards()
{
    listOfCardShuffled = deckOfCards->getDeck();
    //deckOfCards->Show(listOfCardShuffled);
    DrawFiveInHands();
    SortInHands();
    Show();
}

void PlayCards::DrawFiveInHands()
{
    for (size_t i = 0; i < deckOfCards->maxCardInHand; i++)
    {
        player1Hand.emplace_back(Card(listOfCardShuffled.back().getSuit(), listOfCardShuffled.back().getValue()));
        listOfCardShuffled.pop_back();

        player2Hand.emplace_back(Card(listOfCardShuffled.back().getSuit(), listOfCardShuffled.back().getValue()));
        listOfCardShuffled.pop_back();

        // player3Hand.emplace_back(Card(listOfCardShuffled.back().getSuit(), listOfCardShuffled.back().getValue()));
        // listOfCardShuffled.pop_back();

        if (listOfCardShuffled.empty())
        {
            break;
        }
    }
}

void PlayCards::SortInHands()
{
    sort(player1Hand.begin(), player1Hand.end(), [&](Card &a, Card &b)
         { return a.getValue() < b.getValue(); });
    sort(player2Hand.begin(), player2Hand.end(), [&](Card &a, Card &b)
         { return a.getValue() < b.getValue(); });
    // sort(player3Hand.begin(), player3Hand.end(), [&](Card &a, Card &b)
    //      { return a.getValue() < b.getValue(); });
}

void PlayCards::Show()
{
    cout << "\n-------------Player 1-------------------" << endl;
    deckOfCards->Show(player1Hand);
    cout << "\n-------------Player 2-------------------" << endl;
    deckOfCards->Show(player2Hand);
    // cout << "\n-------------Player 3-------------------" << endl;
    // deckOfCards->Show(player3Hand);
}
