/*  Name: Keaton Lee
 *  Date: May 20, 2021
 *  Title: Fantasy Game
 *
 *  Description: Protoype for Button class
*/

// checks if header was defined to avoid double inclusions
#ifndef BUTTON_H
#define BUTTON_H

// imports header files
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#include <string>
#include <vector>

using namespace std;

// defines colours
#define GREY al_map_rgb(155, 155, 155)

extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *subtitle_font;

class Button {
    public:

        /// Constructors
        Button(string t, int l, int w, int x, int y, ALLEGRO_COLOR c, ALLEGRO_COLOR tc);
        Button();       // default constructor

        /// Destructor
        ~Button();

        /// Setters (Mutators)
        void setText(string t);
        void setHover(bool h);

        /// Getters (Accessors)
        bool getHover();

        /// Other Method Prototypes
        void draw(ALLEGRO_EVENT &ev);
        bool checkClicked(ALLEGRO_EVENT &ev);
        bool checkHover(ALLEGRO_EVENT &ev);

        static ALLEGRO_COLOR findHoverColour(ALLEGRO_COLOR c);

    private:

        /// Private Variables
        int length;     // length of the button
        int width;      // width of the button

        int xPos;       // top left x position of button
        int yPos;       // top left y position of button

        string text;    // text written on button

        bool hover;     // boolean determines whether button should respond to hovering

        ALLEGRO_COLOR colour;       // colour of button
        ALLEGRO_COLOR textColour;   // colout of text on button
        ALLEGRO_COLOR hoverColour;  // colour of button when user is hovering over it

        ALLEGRO_SAMPLE *click_sound;                    // allegro sample for button click sound
        ALLEGRO_SAMPLE_INSTANCE *click_sound_instance;  // allegro sample instance for button click sound
};

#endif // BUTTON_H
