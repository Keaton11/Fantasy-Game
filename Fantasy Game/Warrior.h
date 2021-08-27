/*  Name: Keaton Lee
 *  Date: May 20, 2021
 *  Title: Fantasy Game
 *
 *  Description: Protoype for Warrior class
*/

// checks if header was defined to avoid double inclusions
#ifndef WARRIOR_H
#define WARRIOR_H

// imports header files
#include "Character.h"  // parent class

#include <allegro5/allegro_native_dialog.h>

#include <iostream>
#include <string>

using namespace std;

class Warrior : public Character {

    public:

        /// Constructor
        Warrior();

        /// Destructor
        ~Warrior();

        /// Method Protoypes
        void menu();
        void toString();
        bool selection(int choice);

        // method protypes used to display and respond to user's action selection
        bool findFood();
        bool fightMonsters();
        bool searchTreasure();
};

#endif // WARRIOR_H
