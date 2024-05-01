// Yahtzee
// Parker Ellmann
// CSC2034 - WolfCasino2024

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <time.h>
#include <algorithm>
#include "S02921882A.h"
#include "S02921882B.h"

namespace S02921882 {
    using namespace std;

// public member functions
    Yahtzee::Yahtzee() {
}

    Yahtzee* Yahtzee::makeGame() {
    return new Yahtzee;
}

void Yahtzee::start() {
    Dice myDice = S02921882::Dice(Yahtzee::NUM_DICE);
    ifstream instructions;
    string instructLine, rerollInput, rollOrScore, playAgainStr;
    int highScore = 0;
    bool didScore, playAgain;
    
    srand((int)time(NULL)); // seed random number generator
    
    instructions.open("Yahtzee_Instruct.txt");
    if (!instructions.is_open()) {
        std::cout << "Failed to open file" << std::endl;
        return;
    }
    while (instructions.peek() != EOF) {
        std::getline(instructions, instructLine);
        cout << instructLine << std::endl;
    }
    std::cout << std::endl;
    instructions.close();
    
    do {
        // initialize
        for (string allCategories : SCORECARD) {
            scores[allCategories] = -1;
        }
        scores["UPPER TOTAL"] = 0;
        scores["LOWER TOTAL"] = 0;
        scores["GRAND TOTAL"] = 0;
        displayScore(myDice);
        
        // turn loop
        for (int turn = 1; turn <= 13; turn++) {
            for (int d = 1; d <= NUM_DICE; d++) {
                myDice.roll(d);
            }
            showDice(myDice);
            
            // rolling
            for (int roll = 1; roll < 3; roll++) {
                cout << "Reroll dice? (Y or N): ";
                rollOrScore = validateYesNoInput();
                if (rollOrScore == "N" || rollOrScore == "n")
                    break;
                for (int die = 1; die <= NUM_DICE; die++) {
                    printf("Reroll die #%d? (Y or N): ", die);
                    rerollInput = validateYesNoInput();
                    if (rerollInput == "Y" || rerollInput == "y")
                        myDice.roll(die);
                }
                
                showDice(myDice);
                if (maxOfKind(myDice) == 5) {
                    cout << "Yahtzee!" << endl << endl;
                    break;
                }
            }
            
            // scoring
            didScore = false;
            do {
                if (maxOfKind(myDice) == 5)
                    didScore = scoringYahtzee(myDice);
                else
                    didScore = scoringNonYahtzee(myDice, getCategory());
            } while (!didScore);
            displayScore(myDice);
        }
        if (scores["GRAND TOTAL"] > highScore)
            highScore = scores["GRAND TOTAL"];
        cout << "High Score: " << highScore << endl;
        cout << "Play again? (Y or N)";
        playAgainStr = validateYesNoInput();
        playAgain = (playAgainStr == "Y" || playAgainStr == "y") ? true : false;
    } while (playAgain);
    cout << "Thanks for playing!" << endl;
    return;
} // end start

void Yahtzee::displayScore(S02921882::Dice& dice) {
    string category;
    
    cout << setw(40) << setfill('*') << "" << endl;
    for (string category : SCORECARD) {
        if (scores[category] != -1)
            printf("%13s: %3d\n", category.c_str(), scores[category]);
        else
            printf("%13s:  --\n", category.c_str());
        if (category == "UPPER TOTAL" || category == "LOWER TOTAL")
            cout << endl;
    }
    cout << setw(40) << setfill('*') << "" << endl << endl;
} // end displayScore

// private member functions
string Yahtzee::getCategory() {
    string toScore;
    
    while (true) {
        cout << "Enter the category you wish to score: ";
        getline(cin, toScore, '\n');
        for (string category : CATEGORIES) {
            if (toScore == category)
                return toScore;
        }
        cout << "Invalid Category" << endl;
    }
}

int Yahtzee::ofKindTest(S02921882::Dice& dice, int value) {
    int ofKindCount = 0;
    for (int index = 0; index < NUM_DICE; index++) {
        if (dice.getValue(index + 1) == value)
            ofKindCount++;
    }
    return ofKindCount;
}

int Yahtzee::maxOfKind(S02921882::Dice& dice) {
    int max = 1;
    int current;
    for (int values = 1; values <= 6; values++) {
        current = ofKindTest(dice, values);
        if (current > max)
            max = current;
    }
    return max;
}

bool Yahtzee::isFullHouseTest(S02921882::Dice& dice) {
    bool twoOfKind = false;
    bool threeOfKind = false;
    int current;
    for (int values = 1; values <= 6; values++) {
        current = ofKindTest(dice, values);
        if (current == 2)
            twoOfKind = true;
        if (current == 3)
            threeOfKind = true;
    }
    return twoOfKind && threeOfKind ? true : false;
}

bool Yahtzee::jokerRules(S02921882::Dice& dice) {
    int dieValue = -1;
    bool scoreLower, didScore = false;
    string upperCategory, lowerCategory;
    
    cout << "Scoring with Joker Rules:" << endl;
    
    for (int val = 1; val <= 6; val++) {
        if (ofKindTest(dice, val) == NUM_DICE) {
            dieValue = val;
            break;
        }
    }
    
    // Try scoring Upper Section
    switch (dieValue) {
        case 1: didScore = scoringNonYahtzee(dice, "Aces");
            break;
        case 2: didScore = scoringNonYahtzee(dice, "Twos");
            break;
        case 3: didScore = scoringNonYahtzee(dice, "Threes");
            break;
        case 4: didScore = scoringNonYahtzee(dice, "Fours");
            break;
        case 5: didScore = scoringNonYahtzee(dice, "Fives");
            break;
        case 6: didScore = scoringNonYahtzee(dice, "Sixes");
            break;
    }
    if (didScore)
        return true;
    
    // Try scoring Lower Section
    scoreLower = false;
    for (int categoryIndex = 6; categoryIndex <= 11; categoryIndex++) {
        if (scores[CATEGORIES[categoryIndex]] == -1) {
            scoreLower = true;
            cout << CATEGORIES[categoryIndex] << endl;
        }
    }
    if (scoreLower) {
        while (true) {
            cout << "Choose available Lower Section category from list above" << endl;
            lowerCategory = getCategory();
            for (int categoryIndex = 6; categoryIndex <= 11; categoryIndex++) {
                if (lowerCategory == CATEGORIES[categoryIndex])
                    return scoringNonYahtzee(dice, lowerCategory);
            }
            cout << "Must choose Lower Section category" << endl;
        }
    }
    
    // Score 0 in Upper Section
    while(true) {
        for (int categoryIndex = 0; categoryIndex < 6; categoryIndex++) {
            if (scores[CATEGORIES[categoryIndex]] == -1)
                cout << CATEGORIES[categoryIndex] << endl;
        }
        cout << "Choose available Upper Section category from list above (must score 0)" << endl;
        upperCategory = getCategory();
        for (int categoryIndex = 0; categoryIndex <= 5; categoryIndex++) {
            if (upperCategory == CATEGORIES[categoryIndex])
                return scoringNonYahtzee(dice, upperCategory);
        }
        cout << "Must choose Upper Section category" << endl;
    }
    
    return false;
}

int Yahtzee::straightTest(S02921882::Dice& dice) {
    int sortedDice[NUM_DICE];
    int curStraight = 1, maxStraight = 1;
    int size = sizeof(sortedDice) / sizeof(sortedDice[0]);
    
    for (int die = 1; die <= NUM_DICE; die++) {
        sortedDice[die - 1] = dice.getValue(die);
    }
    sort(sortedDice, sortedDice + size);
    
    for (int index = 0; index < NUM_DICE; index++) {
        if (sortedDice[index] == sortedDice[index + 1])
            continue;
        if (sortedDice[index + 1] == (sortedDice[index] + 1))
            curStraight++;
        else {
            if (curStraight > maxStraight)
                maxStraight = curStraight;
            curStraight = 1;
        }
    }
    return maxStraight;
}

int Yahtzee::sumOfDice(Dice& dice) {
    int sum = 0;
    for (int die = 1; die <= NUM_DICE; die++) {
        sum += dice.getValue(die);
    }
    return sum;
}

bool Yahtzee::scoringNonYahtzee(Dice& dice, string toScore) {
    int categoryIndex, score;
    bool found = false, upperFull = true;
    bool didScore = false;
    
    for (categoryIndex = 0; categoryIndex < NUM_CATEGORIES; categoryIndex++) {
        if (toScore == CATEGORIES[categoryIndex]) {
            found = true;
            break;
        }
    }
    if (found) {
        switch (categoryIndex) {
            case 0:
                if (scores["Aces"] == -1) {
                    score = ofKindTest(dice, 1);
                    scores["Aces"] = score;
                    scores["UPPER TOTAL"] += score;
                    didScore = true;
                }
                else
                    cout << "Already scored 'Aces'" << endl;
                break;
            case 1:
                if (scores["Twos"] == -1) {
                    score = 2 * ofKindTest(dice, 2);
                    scores["Twos"] = score;
                    scores["UPPER TOTAL"] += score;
                    didScore = true;
                }
                else
                    cout << "Already scored 'Twos'" << endl;
                break;
            case 2:
                if (scores["Threes"] == -1) {
                    score = 3 * ofKindTest(dice, 3);
                    scores["Threes"] = score;
                    scores["UPPER TOTAL"] += score;
                    didScore = true;
                }
                else
                    cout << "Already scored 'Threes'" << endl;
                break;
            case 3:
                if (scores["Fours"] == -1) {
                    score = 4 * ofKindTest(dice, 4);
                    scores["Fours"] = score;
                    scores["UPPER TOTAL"] += score;
                    didScore = true;
                }
                else
                    cout << "Already scored 'Fours'" << endl;
                break;
            case 4:
                if (scores["Fives"] == -1) {
                    score = 5 * ofKindTest(dice, 5);
                    scores["Fives"] = score;
                    scores["UPPER TOTAL"] += score;
                    didScore = true;
                }
                else
                    cout << "Already scored 'Fives'" << endl;
                break;
            case 5:
                if (scores["Sixes"] == -1) {
                    score = 6 * ofKindTest(dice, 6);
                    scores["Sixes"] = score;
                    scores["UPPER TOTAL"] += score;
                    didScore = true;
                }
                else
                    cout << "Already scored 'Sixes'" << endl;
                break;
            case 6:
                if (scores["3 of a Kind"] == -1) {
                    score = (maxOfKind(dice) >= 3) ? sumOfDice(dice) : 0;
                    scores["3 of a Kind"] = score;
                    scores["LOWER TOTAL"] += score;
                    didScore = true;
                }
                else
                    cout << "Already scored '3 of a Kind'" << endl;
                break;
            case 7:
                if (scores["4 of a Kind"] == -1) {
                    score = (maxOfKind(dice) >= 4) ? sumOfDice(dice) : 0;
                    scores["4 of a Kind"] = score;
                    scores["LOWER TOTAL"] += score;
                    didScore = true;
                }
                else
                    cout << "Already scored '4 of a Kind'" << endl;
                break;
            case 8:
                if (scores["Full House"] == -1) {
                    score = isFullHouseTest(dice) ? 25 : 0;
                    scores["Full House"] = score;
                    scores["LOWER TOTAL"] += score;
                    didScore = true;
                }
                else
                    cout << "Already scored 'Full House'" << endl;
                break;
            case 9:
                if (scores["Sm. Straight"] == -1) {
                    score = (straightTest(dice) >= 4) ? 30 : 0;
                    scores["Sm. Straight"] = score;
                    scores["LOWER TOTAL"] += score;
                    didScore = true;
                }
                else
                    cout << "Already scored 'Sm. Straight'" << endl;
                break;
            case 10:
                if (scores["Lg. Straight"] == -1) {
                    score = (straightTest(dice) == 5) ? 40 : 0;
                    scores["Lg. Straight"] = score;
                    scores["LOWER TOTAL"] += score;
                    didScore = true;
                }
                else
                    cout << "Already scored 'Lg. Straight'" << endl;
                break;
            case 11:
                if (scores["Chance"] == -1) {
                    score = sumOfDice(dice);
                    scores["Chance"] = score;
                    scores["LOWER TOTAL"] += score;
                    didScore = true;
                }
                else
                    cout << "Already scored 'Chance'" << endl;
                break;
            case 12:
                if (scores["YAHTZEE"] == -1) {
                    scores["YAHTZEE"] = 0;
                    scores["YAHTZEE BNS"] = 0;
                    didScore = true;
                }
                else
                    cout << "Already scored 'YAHTZEE'" << endl;
                break;
            default:
                cout << "ERROR - COULD NOT SCORE CATEGORY IN SWITCH - scoring()" << endl;
        }
        if (scores["UPPER TOTAL"] >= 63 && scores["UPPER BNS"] == -1) {
            scores["UPPER BNS"] = 35;
            scores["UPPER TOTAL"] += 35;
        }
        if (scores["UPPER BNS"] == -1) {
            for (int upperIndex = 0; upperIndex < 6; upperIndex++) {
                if (scores[CATEGORIES[upperIndex]] == -1)
                    upperFull = false;
            }
            if (upperFull)
                scores["UPPER BNS"] = 0;
        }
        scores["GRAND TOTAL"] = scores["UPPER TOTAL"] + scores["LOWER TOTAL"];
    }
    else
        cout << "ERROR - CATEGORY NOT FOUND. SKIPPED SWITCH - scoring()" << endl;
    return didScore;
}

bool Yahtzee::scoringYahtzee(S02921882::Dice& dice) {
    if (scores["YAHTZEE"] == -1) {
        scores["YAHTZEE"] = 50;
        return true;
    }
    else if (scores["YAHTZEE"] == 0)
        return jokerRules(dice);
    else if (scores["YAHTZEE"] == 50) {
        (scores["YAHTZEE BNS"] == -1) ? scores["YAHTZEE BNS"] = 100 : scores["YAHTZEE BNS"] += 100;
        return jokerRules(dice);
    }
    else {
        cout << "ERROR SCORING YAHTZEE - scoringYahtzee()" << endl;
        return false;
    }
}

void Yahtzee::showDice(S02921882::Dice& dice) {
    printf("%d %d %d %d %d\n", dice.getValue(1), dice.getValue(2), dice.getValue(3), dice.getValue(4), dice.getValue(5));
} // end showDice

string Yahtzee::validateYesNoInput() {
    bool invalid = true;
    string input;
    
    while (invalid) {
        getline(cin, input);
        if (input == "Y" || input == "y" || input == "N" || input == "n")
            break;
        cout << "Enter 'Y' or 'N'" << endl;
    }
    return input;
}
}
