/*  Name: Keaton Lee
 *  Date: May 20, 2021
 *  Title: Fantasy Game
 *
 *  Description: Protoype for Character class
*/

// checks if header was defined to avoid double inclusions
#ifndef CHARACTER_H
#define CHARACTER_H

// imports header files
#include "Button.h"

#include <allegro5/allegro_primitives.h>

#include <iostream>

using namespace std;

// defines colours
#define BLACK       al_map_rgb(0, 0, 0)
#define LIGHT_BLUE  al_map_rgb(173, 216, 230)
#define IRIS        al_map_rgb(93, 63, 211)
#define GREEN1      al_map_rgb(42, 170, 138)
#define GREEN2      al_map_rgb(40, 121, 105)
#define GREEN3      al_map_rgb(64, 181, 173)
#define RED         al_map_rgb(184, 15, 40)

extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *title_font;
extern ALLEGRO_FONT *subtitle_font;
extern ALLEGRO_FONT *regular_font;
extern ALLEGRO_TIMER *timer;

class Character {
    public:

        /// Constructor
        Character();

        /// Destructor
        ~Character();

        /// Setters (Mutators)
        // the setters of the Character class are small methods that are called very often
        // inline methods are used to speed up the code

        // sets the character's starting and max health, fame, and money
        inline void setCharacter(int h, int f, int m) {
            health = h;
            maxHealth = h;
            fame = f;
            maxFame = f;
            money = m;
            maxMoney = m;
        };
        // sets the character's health
        inline void setHealth(int h) {
            // if statement error checks health to ensure health remains between 0 and maxHealth
            if (h > maxHealth) {
                health = maxHealth;
            } else if (h > 0) {
                health = h;
            } else {
                health = 0;
            }
        };
        // sets the character's fame
        inline void setFame(int f) {
            // if statement error checks health to ensure health remains between 0 and maxFame
            if (f > maxFame) {
                fame = maxFame;
            } else if (f > 0) {
                fame = f;
            } else {
                fame = 0;
            }
        };
        // sets the character's money
        inline void setMoney(int m) {
            // if statement error checks health to ensure health remains between 0 and maxMoney
            if (m > maxMoney) {
                money = maxMoney;
            } else if (m > 0) {
                money = m;
            } else {
                money = 0;
            }
        };
        // sets difficulty of the character
        inline void setDifficulty(int d) {
            difficulty = d;
        }
        // sets boolean value for exitGame
        inline void setExitGame(bool e) {
            exitGame = e;
        };


        /// Getters (Accessors)
        // the getters of the Character class are small methods that are called very often
        // inline methods are used to speed up the code

        // returns integer value for health
        inline int getHealth() {
            return health;
        };
        // returns integer value for fame
        inline int getFame() {
            return fame;
        };
        // returns integer value for money
        inline int getMoney() {
            return money;
        };
        // returns integer value for maxHealth
        inline int getMaxHealth() {
            return maxHealth;
        };
        // returns integer value for stengthBonus
        inline int getStrengthBonus() {
            return strengthBonus;
        };
        // returns integer value for luckyCharm
        inline int getLuckyCharm() {
            return luckyCharm;
        };
        // returns integer value for choice
        inline int getChoice() {
            return choice;
        };
        // returns boolean value for exitGame
        inline bool getExitGame() {
            return exitGame;
        };
        // returns boolean value for playAgain
        inline bool getPlayAgain() {
            return playAgain;
        };
        // returns integer value for day
        static inline int getDay() {
            return day;
        };

        /// Other Method Prototypes

        // virtual keyword is used as menu function is overidden by child classes (Warrior and Hunter class)
        // this ensures reference from a child class object using a pointer will execute the child class’s version of the method
        virtual void menu();

        // method prototypes to display the character's current stats on allegro display
        bool currentStats();
        void drawCurrentStats(int y, string m, int f, int mf, ALLEGRO_COLOR c);

        // method prototypes to display item shop for the character on allegro display
        bool itemShop();
        void itemHover(Button &i, string m1, string m2, ALLEGRO_EVENT &ev);
        void purchaseItem(string m, int c);

        // method prototypes to display the character's progress in regards to the tasks that have been completed
        bool tasksMenu();
        void drawTasks(int y, string m1, string m2, int t, int mt);

        // method prototpes to display the characters stats (on the console and on the allegro display)
        void stats();
        void drawStats();

        // method prototypes to display the characters daily stats drops on the allegro display
        void dailyLoss();
        void drawLoss(int y, string m, int f, int mf, ALLEGRO_COLOR c);

        // method protoypes used once the character has completed all the tasks or reached 0 in a field (health, fame, money)
        void checkProgress();
        void checkGameOver();
        void gameOver(string m);

    private:

        /// Private Variables
        int health;         // the character's current health
        int fame;           // the character's current fame
        int money;          // the character's current money

        int maxHealth;      // the character's max health
        int maxFame;        // the character's max fame
        int maxMoney;       // the character's max money

        int difficulty;     // integer value for the character's difficulty
                            // value corresponds to the number of tasks the user must complete for the character

        int choice;         // the choice that has been selected for the character

        int healthPotion;   // the number of health potions bought for the character
        int strengthBonus;  // the number of strength bonuses bought for the character
        int luckyCharm;     // the number of lucky charms bought for the character

        int food;           // the number of times hunt for food has been chosen for the character
        int attack;         // the number of times fight monsters has been chosen for the character
        int treasure;       // the number of times search for treasures has been chosen for the character
        int purchases;      // the number of purchases that have been made for the character

        int tasksComplete;  // the number of tasks that have been completed with the character

        bool wonGame;       // whether the user has completed all the tasks with the character
        bool exitGame;      // whether the game should exit (user has lost / won with the character or decided to exit the game)
        bool playAgain;     // whether the user has chosen to play again

        static int day;     // static variable used to keep track of the number of days that have passed
};

#endif // CHARACTER_H
