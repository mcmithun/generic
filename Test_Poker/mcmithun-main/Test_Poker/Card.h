/* 
 * File which represents the Card and its features
 */
#ifndef Included_Card_h
#define Included_Card_h

#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

class Card
{
public:
    enum Suit
    {
        hearts,   //unicode char 2665
        spades,   //unicode char 2660
        diamonds, //unicode char 2666
        clubs     //unicode char 2663
    };

    enum Value
    {
        two = 2,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        jack,
        queen,
        king,
        ace
    };

    vector<string> unicodeValues = {"\u2665", "\u2660", "\u2666", "\u2663"};

    Card();
    Card(const Suit &_suit, const Value &_value);

    const Suit &getSuit() { return suit; }
    void setSuit(const Suit &_suit) { suit = _suit; }

    const Value &getValue() { return value; }
    void setValue(const Value &_value) { value = _value; }

    friend ostream &operator<<(ostream &os, const Card &_card);

    ~Card();

private:
    Suit suit;
    Value value;
};

Card::Card()
{
    suit = hearts;
    value = two;
}

Card::Card(const Suit &_suit, const Value &_value)
    : suit(_suit), value(_value)
{
}

ostream &operator<<(ostream &os, const Card &_card)
{
    os << "[" << _card.unicodeValues[(int)_card.suit]
       << "," << _card.value << "]"; // This can be eaisly represented into QML widgets
    return os;
}

Card::~Card()
{
}

#endif