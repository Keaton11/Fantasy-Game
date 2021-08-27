/*  Name: Keaton Lee
 *  Date: May 20, 2021
 *  Title: Fantasy Game
 *
 *  Description: Contains definitions and function prototypes
*/

// checks if header was defined to avoid double inclusions
#ifndef HEADER_H
#define HEADER_H

// imports header files
#include "Character.h"
#include "Warrior.h"
#include "Hunter.h"
#include "Button.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

/// Definitions

// defines colours
#define BLACK	    al_map_rgb(0, 0, 0)
#define LIGHT_BLUE  al_map_rgb(173, 216, 230)
#define WHITE	    al_map_rgb(255, 255, 255)
#define IRIS        al_map_rgb(93, 63, 211)

// defines enum used for character selection
typedef enum {
    WARRIOR,
    HUNTER,
    NONE
} CharacterType;

/// Function Prototypes

// prototype for functions in allegroFunctions.cpp
bool initializeAllegro();
void closeAllegro();

// prototypes for functions in mainMenuFunctions.cpp
void mainMenu();
bool instructions();

// prototypes for functions in function playFunctions.cpp
bool play();
CharacterType selectCharacter();
bool characterConfirmation(ALLEGRO_BITMAP *spriteBasic, CharacterType characterChoice, bool &exit);
bool getDifficulty(int &difficulty);

#endif // HEADER_H
