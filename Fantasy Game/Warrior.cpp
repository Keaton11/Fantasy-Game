/*  Name: Keaton Lee
 *  Date: May 20, 2021
 *  Title: Fantasy Game
 *
 *  Description: Holds the implementations of the methods associated with the
 *  Warrior class
*/

// includes header file
#include "Warrior.h"

/// Constructor
// parameter-less constructor
Warrior::Warrior() {
    // character base stats are set (integers correspond to health, fame, and money respectively)
    Character::setCharacter(17, 15, 20);
    // exitGame is set to false
    Character::setExitGame(false);
}

/// Destructor
Warrior::~Warrior() {
}

/// Method Implementations
// calls game methods (for 1 day) in an appropriate order
void Warrior::menu() {
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
void Warrior::toString() {
    // prints character type (Warrior)
    cout << "Character: Warrior" << endl;
    // calls stats method (from Character class) to print other character stats (the three fields and the tasks completed)
    Character::stats();
}
// recieves an integer corresponding to the user's action selection (choice)
// calls appropriate method depending on such choice
// returns false if user closes allegro display and true is user does not
bool Warrior::selection(int choice) {
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
bool Warrior::findFood() {
    // variable declared
    string message;

    // 50% chance to fully replenish the health, 50% for nothing to happen
    if ((rand() % 2) == 0) {
        Character::setHealth(Character::getMaxHealth());
        message = "You manage to come home feeling replenished after a bountiful feast.";
    } else {
        message = "After spending the entire day searching for food, you unfortunately find nothing.";
    }

    // console is updated based on the selected day and the impact of the action
    cout << endl << "Day " << Character::getDay() - 1 << " - Selected Action: Hunt for food" << endl;
    cout << message << endl << endl;

    // allegro bitmap corresponding to character and action is loaded
    ALLEGRO_BITMAP *warriorFood;
    warriorFood = al_load_bitmap("fantasyAssets/WarriorFood.png");
    if (!warriorFood) {
        // an error message is displayed if bitmap does not load
        al_show_native_message_box(display, "Error", "Error", "Could not load fantasyAssets/WarriorFood.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
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
        al_draw_bitmap(warriorFood, 71, 133, 0);

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
bool Warrior::fightMonsters() {
    // variable declared
    string message;

    // 10% chance of losing the battle, 90% chance of winning the battle
    // chance of losing is reduced if user has bought at least 1 stengths bonus for the character
    if (rand() % (10 + Character::getStrengthBonus()) != 0) {
        // variable is declared and gained fame set to a random value from 7 to 14
        int gainedFame = (rand() % 7) + 7;

        // fame is increased by randomized value and health is decreased by 2
        Character::setFame(Character::getFame() + gainedFame);
        Character::setHealth(Character::getHealth() - 2);

        // message is updated accordingly (based on how much fame was gained)
        message = "You find a worthy opponent but managed to beat it after a lengthy battle. Although you lose 2 HP in the process, you gain ";
        message += to_string(gainedFame);
        message += " fame points.";

    } else {
        // if character loses the battle, health is reduced by 12, and fame is reduced by 5
        Character::setFame(Character::getFame() - 5);
        Character::setHealth(Character::getHealth() - 12);

        // message is updated accordingly
        message = "You come across a monster that is too powerful for you to beat. Your health is reduced by 12 and you lose 5 fame points";

    }

    // console is updated based on the selected day and the impact of the action
    cout << endl << "Day " << Character::getDay() - 1 << " - Selected Action: Fight Monsters" << endl;
    cout << message << endl << endl;

    // allegro bitmap corresponding to character and action is loaded
    ALLEGRO_BITMAP *warriorAttack;
    warriorAttack = al_load_bitmap("fantasyAssets/WarriorAttack.png");
    if (!warriorAttack) {
        // an error message is displayed if bitmap does not load
        al_show_native_message_box(display, "Error", "Error", "Could not load fantasyAssets/WarriorAttack.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
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
        al_draw_bitmap(warriorAttack, 118, 148, 0);

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
            // returns false if allegro display was closed
            return false;
        }
        al_wait_for_event(event_queue, &ev);
    }

}
// preforms "search for treasure" action
// displays action on allegro display and updates stats based on action
// returns false if user closes allegro display and true is user does not
bool Warrior::searchTreasure() {
    // variable declared
    string message;

    // money is increased by 5
    // money increases by a greater amount if the player has purchased at least one lucky charm for the character
    Character::setMoney(Character::getMoney() + 5 + Character::getLuckyCharm());

    // message is updated accordingly (based on how much money was gained)
    message = "You sneak into a castle and find a treasure chest. Inside, you find ";
    message += to_string(5 + Character::getLuckyCharm());
    message += " gold coins.";

    // console is updated based on the selected day and the impact of the action
    cout << endl << "Day " << Character::getDay() - 1 << " - Selected Action: Fight Monsters" << endl;
    cout << message << endl << endl;

    // allegro bitmap corresponding to character and action is loaded
    ALLEGRO_BITMAP *warriorTreasure;
    warriorTreasure = al_load_bitmap("fantasyAssets/WarriorTreasure.png");
    if (!warriorTreasure) {
        // an error message is displayed if bitmap does not load
        al_show_native_message_box(display, "Error", "Error", "Could not load fantasyAssets/WarriorTreasure.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
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
        al_draw_bitmap(warriorTreasure, 34, 143, 0);

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
