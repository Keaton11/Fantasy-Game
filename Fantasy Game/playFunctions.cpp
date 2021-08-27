/*  Name: Keaton Lee
 *  Date: May 20, 2021
 *  Title: Fantasy Game
 *
 *  Description: Contains functions used for character and difficulty
 *  selection
*/

// imports header files
#include "header.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *title_font;
extern ALLEGRO_FONT *subtitle_font;
extern ALLEGRO_FONT *regular_font;
extern ALLEGRO_TIMER *timer;

/// Play Function

bool play() {
// function recieves no parameters
// calls functions to allow user to select a character and difficulty
// calls menu method until player loses, wins, or exits the game
// returns true if player wants to play again and false if they do not

    //variables are declared
    Character* character;   // pointer used to stores the address of either a Warrior or Hunter object
    Warrior warrior;        // object from Warrior class
    Hunter hunter;          // object from Hunter class
    int difficulty;         // integer used to store value corresponding to selected difficulty

    // selectCharacter function is called to determine player's character selection
    CharacterType selectedCharacter = selectCharacter();

    if (selectedCharacter == WARRIOR) {
        // if warrior is selected, character pointer stores the address of the Warrior object
        character = &warrior;
    } else if (selectedCharacter == HUNTER) {
        // if hunter is selected, character pointer stores the address of the Harrior object
        character = &hunter;
    } else {
        // if user exits the character selection menu, function returns false
        return false;
    }

    // getDifficulty function is called to determine player's difficulty selection
    if (!getDifficulty(difficulty)) {
        // if user exits the difficulty selection menu, function returns false
        return false;
    } else {
        // difficulty is set based on user's selection
        character->setDifficulty(difficulty);
    }

    // while loop calls menu method until exitGame is set to true
    while (!character->getExitGame()) {
        character->menu();
    }

    if (character->getPlayAgain()){
        // if playAgain is true, function returns true
        return true;
    } else {
        // if playAgain is false, function returns false
        return false;
    }
}

/// Character Selection Function

CharacterType selectCharacter() {
// function recieves no parameters
// displays character selection options
// once a character has been selected, function calls character confirmation function to confirm selection
// returns selected character or NONE if user clicks exit button

    // exit variable is declared
    bool exit = false;      // used to determine if user has closed the allegro display

    // buttons are declared
    Button warriorButton("Warrior", 150, 100, 80, 250, IRIS, LIGHT_BLUE);
    Button hunterButton("Hunter", 150, 100, 490, 250, IRIS, LIGHT_BLUE);

    // basic warrior sprite bitmap is loaded
    ALLEGRO_BITMAP *warriorSpriteBasic;
    warriorSpriteBasic = al_load_bitmap("fantasyAssets/WarriorSpriteBasic.png");
    if (!warriorSpriteBasic) {
        // an error message is displayed if bitmap does not load
        al_show_native_message_box(display, "Error", "Error", "Could not load fantasyAssets/WarriorSpriteBasic.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    }

    // basic hunter sprite bitmap is loaded
    ALLEGRO_BITMAP *hunterSpriteBasic;
    hunterSpriteBasic = al_load_bitmap("fantasyAssets/HunterSpriteBasic.png");
    if (!hunterSpriteBasic) {
        // an error message is displayed if bitmap does not load
        al_show_native_message_box(display, "Error", "Error", "Could not load fantasyAssets/HunterSpriteBasic.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    }

    ALLEGRO_EVENT ev;

    while (true) {

        // timer event source is unregistered
        al_unregister_event_source(event_queue, al_get_timer_event_source(timer));

        // background colour, title, and description message is added to the allegro display
        al_clear_to_color(LIGHT_BLUE);
        al_draw_text(title_font, IRIS, 360, 30, ALLEGRO_ALIGN_CENTRE, "Select a Character");
        al_draw_text(regular_font, IRIS, 360, 100, ALLEGRO_ALIGN_CENTRE, "Welcome to the Fantasy Character Game! You can play as one of two characters.");
        al_draw_text(regular_font, IRIS, 360, 125, ALLEGRO_ALIGN_CENTRE, "You will need to manage your health, fame, and money in order to survive!");

        // buttons are drawn (added to the allegro display)
        warriorButton.draw(ev);
        hunterButton.draw(ev);

        if (warriorButton.checkClicked(ev)) {
            // if warrior button is clicked, character confirmation function is called
            if (characterConfirmation(warriorSpriteBasic, WARRIOR, exit)) {
                cout << "Character Selected: Warrior" << endl;
                // if warrior selection is confirmed, function returns WARRIOR
                return WARRIOR;
            } else if (exit) {
                // function returns NONE if user closes the allegro display
                return NONE;
            }
            al_register_event_source(event_queue, al_get_timer_event_source(timer));
        } else if (hunterButton.checkClicked(ev)) {
            // if hunter button is clicked, character confirmation function is called
            if (characterConfirmation(hunterSpriteBasic, HUNTER, exit)) {
                cout << "Character Selected: Hunter" << endl;
                // if hunter selection is confirmed, function returns HUNTER
                return HUNTER;
            } else if (exit) {
                // function returns NONE if user closes the allegro display
                return NONE;
            }
            al_register_event_source(event_queue, al_get_timer_event_source(timer));
        } else if (warriorButton.checkHover(ev)) {
            // warrior bitmap is displayed if player hovers over the warrior button
            al_draw_bitmap(warriorSpriteBasic, 250, 170, 0);
        } else if (hunterButton.checkHover(ev)) {
            // hunter bitmap is displayed if player hovers over the hunter button
            al_draw_bitmap(hunterSpriteBasic, 256.5, 203, 0);
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // function returns NONE if user closes the allegro display
            return NONE;
        } else {
            // player is prompted to select a character if they are not currently hovering over a character button
            al_draw_text(regular_font, IRIS, 360, 275, ALLEGRO_ALIGN_CENTRE, "Who would you like");
            al_draw_text(regular_font, IRIS, 360, 300, ALLEGRO_ALIGN_CENTRE, "to play as?");
        }

        al_flip_display();

        al_wait_for_event(event_queue, &ev);
    }
}

/// Character Confirmation Function

bool characterConfirmation(ALLEGRO_BITMAP *spriteBasic, CharacterType characterChoice, bool &exit) {
// function recieves character bitmap, character choice, and exit boolean as parameters
// displays base stats of selected character
// returns true if character selection is cnfirmed by the player
// returns false if player clicks back button or allegro display is closed

    // buttons are declared
    Button backButton("Back", 150, 50, 80, 380, IRIS, LIGHT_BLUE);
    Button confirmButton("Confirm", 150, 50, 490, 380, IRIS, LIGHT_BLUE);

    ALLEGRO_EVENT ev;

    while (true) {

        // background colour and message are added to the allegro display
        al_clear_to_color(LIGHT_BLUE);
        al_draw_text(regular_font, IRIS, 360, 440, ALLEGRO_ALIGN_CENTRE, "Make sure to keep your health, fame, and money above zero to survive!");

        if (characterChoice == WARRIOR) {
            // if warrior is selected, warrior bitmap, description, and base stats are added to the allegro display
            al_draw_text(title_font, IRIS, 360, 30, ALLEGRO_ALIGN_CENTRE, "Warrior");
            al_draw_text(regular_font, IRIS, 360, 90, ALLEGRO_ALIGN_CENTRE, "Warriors are experts in warfare and almost never lose in battle");
            al_draw_bitmap(spriteBasic, 130, 117, 0);
            al_draw_text(subtitle_font, IRIS, 490, 180, ALLEGRO_ALIGN_CENTRE, "Base Stats:");
            al_draw_line(430, 210, 550, 210, IRIS, 2);
            al_draw_text(subtitle_font, IRIS, 490, 220, ALLEGRO_ALIGN_CENTRE, "Health: 17");
            al_draw_text(subtitle_font, IRIS, 490, 250, ALLEGRO_ALIGN_CENTRE, "Fame: 15");
            al_draw_text(subtitle_font, IRIS, 490, 280, ALLEGRO_ALIGN_CENTRE, "Money: 20");
        } else {
            // if hunter is selected, hunter bitmap, description, and base stats are added to the allegro display
            al_draw_text(title_font, IRIS, 360, 30, ALLEGRO_ALIGN_CENTRE, "Hunter");
            al_draw_text(regular_font, IRIS, 360, 90, ALLEGRO_ALIGN_CENTRE, "Skilled in survival, hunters use their bow and arrows to catch wild animals");
            al_draw_bitmap(spriteBasic, 126.5, 131, 0);
            al_draw_text(subtitle_font, IRIS, 490, 180, ALLEGRO_ALIGN_CENTRE, "Base Stats:");
            al_draw_line(430, 210, 550, 210, IRIS, 2);
            al_draw_text(subtitle_font, IRIS, 490, 220, ALLEGRO_ALIGN_CENTRE, "Health: 17");
            al_draw_text(subtitle_font, IRIS, 490, 250, ALLEGRO_ALIGN_CENTRE, "Fame: 17");
            al_draw_text(subtitle_font, IRIS, 490, 280, ALLEGRO_ALIGN_CENTRE, "Money: 17");
        }

        // buttons are drawn (added to the allegro display)
        backButton.draw(ev);
        confirmButton.draw(ev);

        al_flip_display();

        if (backButton.checkClicked(ev)) {
            // if back button is clicked, function returns false
            return false;
        } else if (confirmButton.checkClicked(ev)) {
            // if confirm button is clicked, funtion returns true
            return true;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // if allegro display is closed, function returns false
            // exit boolean is set to true, and is returned via pass by reference
            exit = true;
            return false;
        }

        al_wait_for_event(event_queue, &ev);
    }
}

/// Difficulty Selection Function

bool getDifficulty(int &difficulty) {
// function recieves integer corresponding to difficulty as input
// displays difficulties the player can choose from as buttons
// returns true is difficulty is selected and false if player closes the allegro display
// returns integer corresponding to difficulty via pass by reference

    // buttons are declared
    Button easyButton("Easy", 150, 100, 80, 250, IRIS, LIGHT_BLUE);
    Button mediumButton("Medium", 150, 100, 285, 250, IRIS, LIGHT_BLUE);
    Button hardButton("Hard", 150, 100, 490, 250, IRIS, LIGHT_BLUE);

    ALLEGRO_EVENT ev;

    while (true) {

        // background colour, title, and description message is added to the allegro display
        al_clear_to_color(LIGHT_BLUE);
        al_draw_text(title_font, IRIS, 360, 30, ALLEGRO_ALIGN_CENTRE, "Select a Difficulty");
        al_draw_text(regular_font, IRIS, 360, 100, ALLEGRO_ALIGN_CENTRE, "Select one of the following difficulties to begin the game");
        al_draw_text(regular_font, IRIS, 360, 125, ALLEGRO_ALIGN_CENTRE, "These will determine how challenging your tasks will be");

        // buttons are drawn (added to the allegro display)
        easyButton.draw(ev);
        mediumButton.draw(ev);
        hardButton.draw(ev);

        // depending on the difficulty the user selects, the difficulty integer is updated
        // difficulty integer determines how many tasks the user must complete
        // easy = 3, medium = 5, hard = 10
        if (easyButton.checkClicked(ev)) {
            // if user clicks the easy button, difficulty is set to 3, and true is returned
            difficulty = 3;
            cout << "Difficulty Selected: Easy" << endl << endl;
            return true;
        } else if (mediumButton.checkClicked(ev)) {
            // if user clicks the medium button, difficulty is set to 5, and true is returned
            difficulty = 5;
            cout << "Difficulty Selected: Medium" << endl << endl;
            return true;
        } else if (hardButton.checkClicked(ev)) {
            // if user clicks the hard button, difficulty is set to 10, and true is returned
            cout << "Difficulty Selected: Hard" << endl << endl;
            difficulty = 10;
            return true;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // false is returned if allegro display is closed
            return false;
        }

        al_flip_display();

        al_wait_for_event(event_queue, &ev);
    }
}
