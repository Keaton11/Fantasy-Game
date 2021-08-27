/*  Name: Keaton Lee
 *  Date: May 20, 2021
 *  Title: Fantasy Game
 *
 *  Description: Contains functions used to display main menu and
 *  instructions menu
*/

// imports header files
#include "header.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *title_font;
extern ALLEGRO_FONT *regular_font;
extern ALLEGRO_TIMER *timer;

/// Main Menu Function

void mainMenu() {
// function recieves no parameters
// main menu is displayed
// play function is called if player clicks play button
// instructions function is called if player clicks instructions button
// function returns once player clicks exit or closes the allegro display

    // buttons are declared
    Button playButton("Play", 150, 50, 285, 230, IRIS, LIGHT_BLUE);
    Button instructionsButton("Instructions", 150, 50, 470, 360, IRIS, LIGHT_BLUE);
    Button exitButton("Exit", 150, 50, 100, 360, IRIS, LIGHT_BLUE);

    // warrior attack bitmap is loaded
    ALLEGRO_BITMAP *warriorAttack;
    warriorAttack = al_load_bitmap("fantasyAssets/WarriorAttack.png");
    if (!warriorAttack) {
        // an error message is displayed if bitmap does not load
        al_show_native_message_box(display, "Error", "Error", "Could not load fantasyAssets/WarriorAttack.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    }

    // hunter attack bitmap is loaded
    ALLEGRO_BITMAP *hunterAttack;
    hunterAttack = al_load_bitmap("fantasyAssets/HunterAttack.png");
    if (!hunterAttack) {
        // an error message is displayed if bitmap does not load
        al_show_native_message_box(display, "Error", "Error", "Could not load fantasyAssets/HunterAttack.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    }

    ALLEGRO_EVENT ev;

    while (true) {
        // timer event source is unregistered
        al_unregister_event_source(event_queue, al_get_timer_event_source(timer));

        // background colour and title are added to the allegro display
        al_clear_to_color(LIGHT_BLUE);
        al_draw_text(title_font, IRIS, 360, 30, ALLEGRO_ALIGN_CENTRE, "Fantasy Game");

        // hunter and warrior attack bitmaps are added to the allegro display
        al_draw_bitmap(warriorAttack, 430, 135, 0);
        al_draw_bitmap(hunterAttack, 110, 183, 0);

        // buttons are drawn (added to the allegro display)
        playButton.draw(ev);
        instructionsButton.draw(ev);
        exitButton.draw(ev);

        al_flip_display();

        if (playButton.checkClicked(ev)) {
            // play function is called if the play button is clicked
            if (play()) {
                // if player chooses to play again, the timer event source is registered
                // this allows the while loop to redisplay the main menu
                al_register_event_source(event_queue, al_get_timer_event_source(timer));
            } else {
                return;
            }
        } else if (instructionsButton.checkClicked(ev)) {
            // instructions function is called if instructions button is clicked
            if (!instructions()) {
                return;
            }
            // if player clicks back in the instructions menu, the timer event source is registered
            // this allows the while loop to redisplay the main menu
            al_register_event_source(event_queue, al_get_timer_event_source(timer));
        } else if (exitButton.checkClicked(ev) || ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // function is returned if exit button is clicked
            return;
        }

        al_wait_for_event(event_queue, &ev);
    }
}

/// Instructions Menu Function

bool instructions() {
// function recieves no parameters
// displays game instructions
// true is returned if player clicks the back button
// false is returned if player clicks the exit button or closes the allegro display

    // Buttons are declared
    Button backButton("Back", 150, 50, 150, 400, IRIS, BLACK);
    Button exitButton("Exit", 150, 50, 420, 400, IRIS, BLACK);

    ALLEGRO_EVENT ev;

    while (true) {

        if (ev.type != ALLEGRO_EVENT_TIMER) {

            // background colour, title, and instructions are added to the allegro display
            al_clear_to_color(BLACK);
            al_draw_text(title_font, IRIS, 360, 30, ALLEGRO_ALIGN_CENTRE, "Game Instructions");
            al_draw_text(subtitle_font, IRIS, 360, 100, ALLEGRO_ALIGN_CENTRE, "In this game, you will select a character and a difficulty.");
            al_draw_text(subtitle_font, IRIS, 360, 140, ALLEGRO_ALIGN_CENTRE, "Each character has different base stats that you will have");
            al_draw_text(subtitle_font, IRIS, 360, 180, ALLEGRO_ALIGN_CENTRE, "to maintain above zero in order to survive. The difficulty");
            al_draw_text(subtitle_font, IRIS, 360, 220, ALLEGRO_ALIGN_CENTRE, "you choose will determine how many tasks you need to");
            al_draw_text(subtitle_font, IRIS, 360, 260, ALLEGRO_ALIGN_CENTRE, "complete in order to win. Make sure to visit the item shop");
            al_draw_text(subtitle_font, IRIS, 360, 300, ALLEGRO_ALIGN_CENTRE, "to pick up useful upgrades that can help you on your");
            al_draw_text(subtitle_font, IRIS, 360, 340, ALLEGRO_ALIGN_CENTRE, "journey. Good luck!");

            // buttons are drawn (added to the allegro display)
            backButton.draw(ev);
            exitButton.draw(ev);

            if (backButton.checkClicked(ev)) {
                // returns true if the back button has been clicked
                return true;
            } else if (exitButton.checkClicked(ev) || ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                // returns false if the exit button has been clicked
                return false;
            }

            al_flip_display();
        }
        al_wait_for_event(event_queue, &ev);
    }
}
