/*  Name: Keaton Lee
 *  Date: May 20, 2021
 *  Title: Fantasy Game
 *
 *  Description: Contains functions used to initialize and close Allegro
*/

// imports header files
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *title_font;
extern ALLEGRO_FONT *subtitle_font;
extern ALLEGRO_FONT *regular_font;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_SAMPLE *music;

/// Allegro Initialization Function

bool initializeAllegro() {
// function recieves no parameters
// initializes allegro
// error message is displayed if initializion fails
// returns true if allegro is correctly initialized and false if it is not

    // allegro is initialized
	al_init();

    // allegro display is initialized
    display = al_create_display(720, 480);
    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // title is added to display
    al_set_window_title(display, "Keaton Lee: ICS4U - Fantasy Game Assignment");

    // primitives addon is initialized
    if (!al_init_primitives_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return false;
	}

	// audio is installed
    if (!al_install_audio()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to install audio", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return false;
	}

	// acodec addon is initialized
    if (!al_init_acodec_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize acodec addon", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return false;
	}

    // sample is reserved (for music)
    if (!al_reserve_samples(1)) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to reserve sample", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return false;
	}

	// image addon is initialized
 	if (!al_init_image_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return false;
	}

	// font addon is initialized
    if (!al_init_font_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize font add on", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // ttf addon is initialized
    if (!al_init_ttf_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize font ttf on", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // regular font (sniglet) is initialized
    regular_font = al_load_ttf_font("sniglet.ttf", 18, 0);
    if (!regular_font){
        al_show_native_message_box(display, "Error", "Error", "Could not load sniglet.ttf", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // subtitle font (sniglet) is initialized
    subtitle_font = al_load_ttf_font("sniglet.ttf", 24, 0);
    if (!subtitle_font){
        al_show_native_message_box(display, "Error", "Error", "Could not load sniglet.ttf", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // title font (sniglet) is initialized
    title_font = al_load_ttf_font("mauikea.otf", 70, 0);
    if (!title_font){
        al_show_native_message_box(display, "Error", "Error", "Could not load mauikea.otf", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // keyboard is initialized
    if (!al_install_keyboard()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize the keyboard", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // mouse is initialized
    if (!al_install_mouse()){
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize mouse", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // music is loaded
    music = al_load_sample("sounds/music.wav");
    if (!music) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize music", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // timer is created
    timer = al_create_timer(1.0 / 20);
    if (!timer) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create timer", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // event queue is created
    event_queue = al_create_event_queue();
    if (!event_queue) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // event sources are registered
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

 	// music begins playing
 	al_play_sample(music, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);

 	// timer is started
 	al_start_timer(timer);

    // returns true if allegro is correctly initialized
	return true;
}

/// Close Allegro Function

void closeAllegro() {
// function recieves no parameters
// function destroys display, fonts, timer, event queue, and music

    // samples are stopped
    al_stop_samples();

    // display, fonts, timer, event queue, and music is destroyed
    al_destroy_display(display);
    al_destroy_font(title_font);
    al_destroy_font(subtitle_font);
    al_destroy_font(regular_font);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_sample(music);
}
