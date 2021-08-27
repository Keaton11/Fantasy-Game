/*  Name: Keaton Lee
 *  Date: May 20, 2021
 *  Title: Fantasy Game
 *
 *  Description: Holds the implementations of the methods associated with the
 *  Hunter class
*/

// includes header file
#include "Hunter.h"

/// Constructor
// parameter-less constructor
Hunter::Hunter() {
    // character base stats are set (integers correspond to health, fame, and money respectively)
    Character::setCharacter(17, 17, 17);
    // exitGame is set to false
    Character::setExitGame(false);
}

/// Destructor
Hunter::~Hunter() {
}

/// Method Implementations
// calls game methods (for 1 day) in an appropriate order
void Hunter::menu() {
    if (!Character::getExitGame()) {
        // if getExit is false, toString method and menu method (from Character class) are called
        toString();
        Character::menu();
        // getChoice method (from Character class) and selection method are called
        if (selection(Character::getChoice())) {
            // dailyLoss method (from Character class) is called
            Character::dailyLoss();
        }
        if (!Character::getExitGame()) {
            // if getExit is still false, checkProgress method (from Character class) is called
            Character::checkProgress();
        }
    }
}
// prints stats regarding character type, the three fields, and tasks completed onto console
void Hunter::toString() {
    // prints character type (Hunter)
    cout << "Character: Hunter" << endl;
    // calls stats method (from Character class) to print other character stats (the three fields and the tasks completed)
    Character::stats();
}
// recieves an integer corresponding to the user's action selection (choice)
// calls appropriate method depending on such choice
// returns false if user closes allegro display and true is user does not
bool Hunter::selection(int choice) {
    if (choice == 0) {
        // if choice equals 0, exitGame is set to true
        Character::setExitGame(true);
    } else if (choice == 1) {
        // if choice equals 1, findFood method is called
        if (!findFood()) {
            // if user closes allegro display, exitGame is set to true
            Character::setExitGame(true);
        }
    } else if (choice == 2) {
        // if choice equals 2, fightMonsters method is called
        if (!fightMonsters()) {
            // if user closes allegro display, exitGame is set to true
            Character::setExitGame(true);
        }
    } else if (choice == 3) {
        // if choice equals 3, searchTreasure method is called
        if (!searchTreasure()) {
            // if user closes allegro display, exitGame is set to true
            Character::setExitGame(true);
        }
    }

    if (Character::getExitGame()) {
        // returns false if getExit equals true
        return false;
    } else {
        // returns true if getExit does not equal true
        return true;
    }
}
// preforms "hunt for food" action
// displays action on allegro display and updates stats based on action
// returns false if user closes allegro display and true is user does not
bool Hunter::findFood() {
    // variables are declared
    string message;
    // gained health is set to a random value from 6 to 11
    int gainedHealth = (rand() % 5) + 6;

    // characters health is updated based on such random number (gainedHealth)
    Character::setHealth(Character::getHealth() + gainedHealth);

    // message is updated accordingly (based on how much health was gained)
    message = "You enter a forest and hunt for animals. You gain ";
    message += to_string(gainedHealth);
    message += " HP after a day of hunting.";

    // console is updated based on the selected day and the impact of the action
    cout << endl << "Day " << Character::getDay() - 1 << " - Selected Action: Hunt for food" << endl;
    cout << message << endl << endl;

    // allegro bitmap corresponding to character and action is loaded
    ALLEGRO_BITMAP *hunterFood;
    hunterFood = al_load_bitmap("fantasyAssets/HunterFood.png");
    if (!hunterFood) {
        // an error message is displayed if bitmap does not load
        al_show_native_message_box(display, "Error", "Error", "Could not load fantasyAssets/HunterFood.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    }

    // next button is declared
    Button nextButton("Next", 150, 50, 510, 400, IRIS, LIGHT_BLUE);

    ALLEGRO_EVENT ev;

    while (true) {
        // background colour, and action description message is added to the allegro display
        al_clear_to_color(LIGHT_BLUE);
        for (int i = 0; i <= message.length() / 50; i++) {
            al_draw_text(subtitle_font, IRIS, 360, 30 + 30 * i, ALLEGRO_ALIGN_CENTRE, message.substr(i*50, 50).c_str());
        }

        // method (from Character class) is used to draw the characters stats
        Character::drawStats();

        // previously loaded bitmap is drawn (added to the allegro display)
        al_draw_bitmap(hunterFood, 145, 165, 0);

        // next button is drawn (added to the allegro display)
        nextButton.draw(ev);

        al_flip_display();

        if (nextButton.checkClicked(ev)) {
            // returns true if next button was clicked
            return true;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // returns false if allegro display was closed
            return false;
        }
        al_wait_for_event(event_queue, &ev);
    }
}
// preforms "fight monsters" action
// displays action on allegro display and updates stats based on action
// returns false if user closes allegro display and true is user does not
bool Hunter::fightMonsters() {
    // variable declared
    string message;

    // 20% chance of losing the battle, 80% chance of winning the battle
    // chance of losing is reduced if user has bought at least 1 stengths bonus for the character
    if (rand() % (5 + Character::getStrengthBonus()) != 0) {
        // variable is declared and gained fame set to a random value from 6 to 10
        int gainedFame = (rand() % 4) + 6;

        // fame is increased by randomized value and health is decreased by half that value
        // if fame is an odd number, loss of health is rounded down
        Character::setFame(Character::getFame() + gainedFame);
        Character::setHealth(Character::getHealth() - gainedFame / 2);

        // message is updated accordingly (based on how much fame was gained and how much health was lost)
        message = "You enter a battle against a strong opponent. You lose ";
        message += to_string(gainedFame / 2);
        message += " HP in the process, but gain ";
        message += to_string(gainedFame);
        message += " fame points.";
    } else {
        // if character loses the battle, health is reduced by 10, and fame is reduced by 3
        Character::setFame(Character::getFame() - 3);
        Character::setHealth(Character::getHealth() - 10);

        // message is updated accordingly
        message = "You come across a monster that is too powerful for you to beat. Your health is reduced by 10 and you lose 3 fame points";
    }

    // console is updated based on the selected day and the impact of the action
    cout << endl << "Day " << Character::getDay() - 1 << " - Selected Action: Fight Monsters" << endl;
    cout << message << endl << endl;

    // allegro bitmap corresponding to character and action is loaded
    ALLEGRO_BITMAP *hunterAttack;
    hunterAttack = al_load_bitmap("fantasyAssets/HunterAttack.png");
    if (!hunterAttack) {
        // an error message is displayed if bitmap does not load
        al_show_native_message_box(display, "Error", "Error", "Could not load fantasyAssets/HunterAttack.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    }

    // next button is declared
    Button nextButton("Next", 150, 50, 510, 400, IRIS, LIGHT_BLUE);

    ALLEGRO_EVENT ev;

    while (true) {
        // background colour, and action description message is added to the allegro display
        al_clear_to_color(LIGHT_BLUE);
        for (int i = 0; i <= message.length() / 50; i++) {
            al_draw_text(subtitle_font, IRIS, 360, 30 + 30 * i, ALLEGRO_ALIGN_CENTRE, message.substr(i*50, 50).c_str());
        }

        // method (from Character class) is used to draw the characters stats
        Character::drawStats();

        // previously loaded bitmap is drawn (added to the allegro display)
        al_draw_bitmap(hunterAttack, 148, 165, 0);

        // next button is drawn (added to the allegro display)
        nextButton.draw(ev);

        al_flip_display();

        if (nextButton.checkClicked(ev)) {
            // calls method to check whether any of the characters stats reached 0
            checkGameOver();
            if (Character::getExitGame()) {
                // returns false if exitGame is true (one of the characters stats reached 0)
                return false;
            }
            // returns true if next button was clicked
            return true;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // returns true if next button was clicked
            return false;
        }
        al_wait_for_event(event_queue, &ev);
    }

}
// preforms "search for treasure" action
// displays action on allegro display and updates stats based on action
// returns false if user closes allegro display and true is user does not
bool Hunter::searchTreasure() {
    // variable declared
    string message;

    // money is increased by 7
    // money increases by a greater amount if the player has purchased at least one lucky charm for the character
    Character::setMoney(Character::getMoney() + 7 + Character::getLuckyCharm());

    // message is updated accordingly (based on how much money was gained)
    message = "While searching for treasure, you come across some precious artifacts. You decide to sell them all, and gain ";
    message += to_string(7 + Character::getLuckyCharm());
    message += " coins.";

    // console is updated based on the selected day and the impact of the action
    cout << endl << "Day " << Character::getDay() - 1 << " - Selected Action: Fight Monsters" << endl;
    cout << message << endl << endl;

    // allegro bitmap corresponding to character and action is loaded
    ALLEGRO_BITMAP *hunterTreasure;
    hunterTreasure = al_load_bitmap("fantasyAssets/HunterTreasure.png");
    if (!hunterTreasure) {
        // an error message is displayed if bitmap does not load
        al_show_native_message_box(display, "Error", "Error", "Could not load fantasyAssets/HunterTreasure.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    }

    // next button is declared
    Button nextButton("Next", 150, 50, 510, 400, IRIS, LIGHT_BLUE);

    ALLEGRO_EVENT ev;

    while (true) {
        // background colour, and action description message is added to the allegro display
        al_clear_to_color(LIGHT_BLUE);
        for (int i = 0; i <= message.length() / 50; i++) {
            al_draw_text(subtitle_font, IRIS, 360, 30 + 30 * i, ALLEGRO_ALIGN_CENTRE, message.substr(i*50, 50).c_str());
        }

        // method (from Character class) is used to draw the characters stats
        Character::drawStats();

        // previously loaded bitmap is drawn (added to the allegro display)
        al_draw_bitmap(hunterTreasure, 54, 163, 0);

        // next button is drawn (added to the allegro display)
        nextButton.draw(ev);

        al_flip_display();

        if (nextButton.checkClicked(ev)) {
            // returns true if next button was clicked
            return true;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // returns false if allegro display was closed
            return false;
        }
        al_wait_for_event(event_queue, &ev);
    }

}
