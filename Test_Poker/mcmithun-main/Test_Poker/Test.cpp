/**
 * @file
 * @copyright (C) 2022 mcm
 * @copyright (C) 2022 mcm testpoker
 *
 * Test functionalities which contain a main()
 */
// Example poker program

#include <iostream>
#include <string>
#include "PlayCards.h"
#include "HandEvaluator.h"
int main()
{
        shared_ptr<PlayCards> playCards = make_shared<PlayCards>();
        playCards->SetupCards();
        shared_ptr<HandEvaluator> hand1Evaluator = make_shared<HandEvaluator>(playCards->GetPlayer1Hand());
        hand1Evaluator->EvaluavateHand();
        shared_ptr<HandEvaluator> hand2Evaluator = make_shared<HandEvaluator>(playCards->GetPlayer2Hand());
        hand2Evaluator->EvaluavateHand();
        //     shared_ptr<HandEvaluator> hand3Evaluator
        //             = make_shared<HandEvaluator>(playCards->GetPlayer3Hand());
        //     hand3Evaluator->EvaluavateHand();

        //
        // Compare the handEvalutor Objects
        // can be implemented via operator overloading
        // according to specific logic of comparisons
        // on HandEvaluatedValue total and high;
        //
        if (*hand1Evaluator.get() > *hand2Evaluator.get())
        {
                cout << "Player 1 Wins" << endl;
        }
        else
        {
                cout << "Player 2 Wins" << endl;
        }
        return 0;
}
