#ifndef Included_HandEvaluator_h
#define Included_HandEvaluator_h

#include "Card.h"
using namespace std;

enum HandType
{
    nothing,
    onePair,
    twoPair,
    threeOfKind,
    straight,
    flush,
    fullHouse,
    fourOfKind
};

class HandEvaluator
{
public:
    HandType EvaluavateHand();
    struct HandEvaluatedValue
    {
        HandEvaluatedValue(int _total, int _high)
        {
            totalOfCards = _total;
            highValueOfCards = _high;
        }
        int totalOfCards;
        int highValueOfCards;
    };

    HandEvaluator(const vector<Card> &_phand);
    friend bool operator< (const HandEvaluator& h1, const HandEvaluator& h2);
    friend bool operator> (const HandEvaluator& h1, const HandEvaluator& h2);

private:
    const int maxCardInHand = 5;
    int heartsSum;
    int spadesSum;
    int diamondsSum;
    int clubsSum;
    vector<Card> phand;
    shared_ptr<HandEvaluatedValue> handValue;

    bool FourOfAKind();
    bool FullHouse();
    bool Flush();
    bool Straight();
    bool ThreeOfAKind();
    bool TwoPair();
    bool OnePair();
};

#endif

HandEvaluator::HandEvaluator(const vector<Card> &_phand)
    : phand(_phand)
{
    handValue = make_shared<HandEvaluatedValue>(0, 0);
    heartsSum = 0;
    spadesSum = 0;
    diamondsSum = 0;
    clubsSum = 0;

    // Make sure that the basic evaluation starts here
    // to check whether the cards are in same suits.
    for (auto elem : phand)
    {
        if (elem.getSuit() == Card::Suit::hearts)
        {
            heartsSum++;
        }
        else if (elem.getSuit() == Card::Suit::spades)
        {
            spadesSum++;
        }
        else if (elem.getSuit() == Card::Suit::diamonds)
        {
            diamondsSum++;
        }
        else if (elem.getSuit() == Card::Suit::clubs)
        {
            clubsSum++;
        }
    }
}

HandType HandEvaluator::EvaluavateHand()
{
    if (FourOfAKind())
        return HandType::fourOfKind;
    else if (FullHouse())
        return HandType::fullHouse;
    else if (Flush())
        return HandType::flush;
    else if (Straight())
        return HandType::straight;
    else if (ThreeOfAKind())
        return HandType::threeOfKind;
    else if (OnePair())
        return HandType::onePair;
    else
        return HandType::nothing;
}
/*
 * Function to check cards at 1,2,3,4 are same or 2,3,4,5 are same
 */
bool HandEvaluator::FourOfAKind()
{
    bool ret = false;
    if ((phand[0].getValue() | phand[1].getValue() | phand[2].getValue()) == phand[3].getValue())
    {
        handValue->totalOfCards = phand[0].getValue() * 4;
        handValue->highValueOfCards = phand[4].getValue();
        ret = true;
    }
    else if ((phand[1].getValue() | phand[2].getValue() | phand[3].getValue()) == phand[4].getValue())
    {
        handValue->totalOfCards = phand[1].getValue() * 4;
        handValue->highValueOfCards = phand[0].getValue();
        ret = true;
    }
    return ret;
}

/*
 * Function to check cards at 1,2,3 are same and 4,5 are same
 * Similarly 1,2 are paired and 3,4,5 are paired
 */
bool HandEvaluator::FullHouse()
{
    bool ret = false;
    if (((phand[0].getValue() | phand[1].getValue()) == phand[2].getValue() && (phand[3].getValue() == phand[4].getValue())) || (phand[0].getValue() == phand[1].getValue()) && ((phand[2].getValue() | phand[3].getValue()) == phand[4].getValue()))
    {
        handValue->totalOfCards = phand[0].getValue() + phand[1].getValue() + phand[2].getValue() + phand[3].getValue() + phand[4].getValue();
        ret = true;
    }
    return ret;
}

/*
 * Function to check cards are same Suit with highest value
 */
bool HandEvaluator::Flush()
{
    bool ret = false;
    if ((heartsSum | spadesSum | diamondsSum | clubsSum) == maxCardInHand)
    {
        handValue->totalOfCards = phand[4].getValue();
        ret = true;
    }
    return ret;
}

/*
 * Function to check cards are with consecutive values
 */
bool HandEvaluator::Straight()
{
    bool ret = false;
    for (int i = 0; i < maxCardInHand; i++)
    {
        if ((phand[i].getValue() + 1) != (phand[i + 1].getValue()))
        {
            ret = false;
            break;
        }
        handValue->totalOfCards = phand[4].getValue();
        ret = true;
    }
    return ret;
}

/*
 * Find the Cards 1,2,3 or 2,3,4 or 3,4,5 are same to become three of a kind.
 */
bool HandEvaluator::ThreeOfAKind()
{
    bool ret = false;
    if ((phand[0].getValue() | phand[1].getValue()) == phand[2].getValue() || (phand[1].getValue() | phand[2].getValue()) == phand[3].getValue())
    {
        handValue->totalOfCards = phand[2].getValue() * 3;
        handValue->highValueOfCards = phand[4].getValue();
        ret = true;
    }
    else if ((phand[0].getValue() | phand[1].getValue()) == phand[2].getValue())
    {
        handValue->totalOfCards = phand[2].getValue() * 3;
        handValue->highValueOfCards = phand[2].getValue();
        ret = true;
    }
    return ret;
}

/*
 * Check 1,2 and 3,4
 *       1,2 and 4,5
 *       2,3 and 4,5 
 * are same to get a two pair hand
 */
bool HandEvaluator::TwoPair()
{
    bool ret = false;
    if ((phand[0].getValue() == phand[1].getValue()) && (phand[2].getValue() == phand[3].getValue()))
    {
        handValue->totalOfCards = phand[1].getValue() * 2 + phand[3].getValue() * 2;
        handValue->highValueOfCards = phand[4].getValue();
        ret = true;
    }
    else if ((phand[0].getValue() == phand[1].getValue()) && (phand[3].getValue() == phand[4].getValue()))
    {
        handValue->totalOfCards = phand[1].getValue() * 2 + phand[3].getValue() * 2;
        handValue->highValueOfCards = phand[2].getValue();
        ret = true;
    }
    else if ((phand[1].getValue() == phand[2].getValue()) && (phand[3].getValue() == phand[4].getValue()))
    {
        handValue->totalOfCards = phand[1].getValue() * 2 + phand[3].getValue() * 2;
        handValue->highValueOfCards = phand[0].getValue();
        ret = true;
    }
    return ret;
}

/*
 * Check 1,2 | 2,3 | 3,4 | 4,5
 * are same to get a pair hand
 */
bool HandEvaluator::OnePair()
{
    bool ret = false;
    if ((phand[0].getValue() == phand[1].getValue()))
    {
        handValue->totalOfCards = phand[0].getValue() * 2;
        handValue->highValueOfCards = phand[4].getValue();
        ret = true;
    }
    else if ((phand[1].getValue() == phand[2].getValue()))
    {
        handValue->totalOfCards = phand[1].getValue() * 2;
        handValue->highValueOfCards = phand[4].getValue();
        ret = true;
    }
    else if ((phand[2].getValue() == phand[3].getValue()))
    {
        handValue->totalOfCards = phand[2].getValue() * 2;
        handValue->highValueOfCards = phand[4].getValue();
        ret = true;
    }
    else if ((phand[3].getValue() == phand[4].getValue()))
    {
        handValue->totalOfCards = phand[3].getValue() * 2;
        handValue->highValueOfCards = phand[2].getValue();
        ret = true;
    }
    return ret;
}


bool operator< (const HandEvaluator& h1, const HandEvaluator& h2)
{
    return h1.handValue->totalOfCards < h2.handValue->totalOfCards;
}
bool operator> (const HandEvaluator& h1, const HandEvaluator& h2)
{
    return h1.handValue->totalOfCards < h2.handValue->totalOfCards;
}
