/*  Name: Keaton Lee
 *  Date: May 20, 2021
 *  Title: Fantasy Game
 *
 *  Description: Protoype for Hunter class
*/

// checks if header was defined to avoid double inclusions
#ifndef HUNTER_H
#define HUNTER_H

// imports header files
#include "Character.h"  // parent class

#include <allegro5/allegro_native_dialog.h>

#include <iostream>
#include <string>

using namespace std;

class Hunter : public Character {

    public:

        /// Constructor
        Hunter();

        /// Destructor
        ~Hunter();

        /// Method Protoypes
        void menu();
        void toString();
        bool selection(int choice);

        // method protypes used to display and respond to user's action selection
        bool findFood();
        bool fightMonsters();
        bool searchTreasure();
};

#endif // HUNTER_H
