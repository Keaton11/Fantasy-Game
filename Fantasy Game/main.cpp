/***************************************************************************
 *  Name: Keaton Lee                                         May 20, 2021  *
 *  Title: Fantasy Game                                                    *
 *                                                                         *
 *  Description: This program uses inheritance and polymorphism to allow   *
 *  the user to play as one of two characters (a warrior or a hunter).     *
 *  The user can then select a difficulty which will determine the number  *
 *  of tasks they must complete in order to win the game. While trying to  *
 *  complete these tasks, the user must ensure all three of the selected   *
 *  characters fields (health, fame, and money) remain above 0. Each day,  *
 *  the user can make decisions or purchases that can increase their       *
 *  stats to help them win the game. The user interface of the game is     *
 *  entirely on Allegro. However, updates are printed on the console so    *
 *  users can view their previous actions.                                 *
 *                                                                         *
 *  Specific Game Components:                                              *
 *  Characters: Warrior, Hunter                                            *
 *  Fields: Health, Fame, Money                                            *
 *  Difficulties: Easy, Medium, Hard                                       *
 *  Shop Items: Health Boost, Potion of Healing, Fame Boost, Strength      *
 *  Bonus, Money Boost, Lucky Charm                                        *
 ***************************************************************************/

// imports header files
#include "header.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_acodec.h>

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

// global allegro variables
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_FONT *title_font = nullptr;
ALLEGRO_FONT *subtitle_font = nullptr;
ALLEGRO_FONT *regular_font = nullptr;
ALLEGRO_TIMER *timer = nullptr;
ALLEGRO_SAMPLE *music = nullptr;

int main() {

    // seeds rand with a starting value to allow for a random generation of numbers
    srand(time(0));

    // calls function to initialize allegro
    if (!initializeAllegro()) {
        // if allegro fails to initialize, 1 is returned
        return 1;
    }

    // loop continues until player exits the game
    // this allows the player to play the game multiple times
    mainMenu();

    // calls function to close Allegro
    closeAllegro();

    return 0;
}
