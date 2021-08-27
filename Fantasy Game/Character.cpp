/*  Name: Keaton Lee
 *  Date: May 20, 2021
 *  Title: Fantasy Game
 *
 *  Description: Holds the implementations of the methods associated with the
 *  Character class
*/

// includes header file
#include "Character.h"

// declares the class variable (day)
int Character::day = 1;     // by default, day is set to 1

/// Constructor
// parameter-less constructor
Character::Character() {
    day = 1;           // day is set to 1 whenever a new Character object is created
    food = 0;          // the number of times hunt for food has been chosen for the character is set to 0 by default
    attack = 0;        // the number of times fight monsters has been chosen for the character is set to 0 by default
    treasure = 0;      // the number of times hunt for treasure has been chosen for the character is set to 0 by default
    purchases = 0;     // the number of purchases that have been made for the character is set to 0 by default
    healthPotion = 0;  // the number of health potions bought for the character is set to 0 by default
    strengthBonus = 0; // the number of strength bonuses bought for the character is set to 0 by default
    luckyCharm = 0;    // the number of strength bonuses bought for the character is set to 0 by default
    tasksComplete = 0; // the number of tasks that have been completed with the character is set to 0 by default
    wonGame = false;   // won game is set to false by default
    playAgain = false; // play again is set to false by default
}

/// Destructor
Character::~Character() {
}

/// Method Implementations
// displays menu on allegro display and responds to user input
void Character::menu() {
    // buttons are declared
    Button findFoodButton("Hunt for Food", 600, 70, 60, 125, GREEN1, BLACK);
    Button fightMonstersButton("Fight Monsters", 600, 70, 60, 210, GREEN2, BLACK);
    Button searchTreasureButton("Search for Treasure", 600, 70, 60, 295, GREEN3, BLACK);
    Button itemShopButton("Item Shop", 190, 50, 60, 400, IRIS, BLACK);
    Button statsButton("View Stats", 190, 50, 470, 400, IRIS, BLACK);
    Button tasksButton("Tasks", 190, 50, 265, 400, IRIS, BLACK);

    ALLEGRO_EVENT ev;

    while (true) {
        // timer event source is unregistered
        al_unregister_event_source(event_queue, al_get_timer_event_source(timer));

        // background colour, title, and description message is added to the allegro display
        al_clear_to_color(BLACK);
        al_draw_textf(title_font, IRIS, 360, 30, ALLEGRO_ALIGN_CENTRE, "DAY %d", day);
        al_draw_text(regular_font, IRIS, 360, 90, ALLEGRO_ALIGN_CENTRE, "What would you like to do?");

        // buttons are drawn (added to the allegro display)
        findFoodButton.draw(ev);
        fightMonstersButton.draw(ev);
        searchTreasureButton.draw(ev);
        itemShopButton.draw(ev);
        statsButton.draw(ev);
        tasksButton.draw(ev);

        al_flip_display();

        if (findFoodButton.checkClicked(ev)) {
            food++;     // if hunt for food button is clicked, choice is set to 1 and food integer is incremented
            choice = 1;
            break;
        } else if (fightMonstersButton.checkClicked(ev)) {
            attack++;   // if fight monsters button is clicked, choice is set to 2 and attack integer is incremented
            choice = 2;
            break;
        } else if (searchTreasureButton.checkClicked(ev)) {
            treasure++; // if search for treasures button is clicked, choice is set to 3 and treasure integer is incremented
            choice = 3;
            break;
        } else if (itemShopButton.checkClicked(ev)) {
            // if item shop is clicked, item shop method is called
            if (!itemShop()) {
                choice = 0; // choice is set to 0 if item shop method returns false (user has closed allegro display)
                break;
            }
            al_register_event_source(event_queue, al_get_timer_event_source(timer)); // timer is registered to update allegro display
        } else if (statsButton.checkClicked(ev)) {
            // if current stats button is clicked, current stats method is called
            if (!currentStats()) {
                choice = 0; // choice is set to 0 if item shop method returns false (user has closed allegro display)
                break;
            }
            al_register_event_source(event_queue, al_get_timer_event_source(timer)); // timer is registered to update allegro display
        } else if (tasksButton.checkClicked(ev)) {
            // if tasks button is clicked, tasks menu method is called
            if (!tasksMenu()) {
                choice = 0; // choice is set to 0 if tasks menu method returns false (user has closed allegro display)
                break;
            }
            al_register_event_source(event_queue, al_get_timer_event_source(timer)); // timer is registered to update allegro display
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            choice = 0; // choice is set to zero if user has closed the allegro display
            break;
        }
        al_wait_for_event(event_queue, &ev);
    }
    day++;  // day is incremented
}
// displays item shop on allegro display and responds to user input
// returns true if user click back button and false is user closes the allegro display
bool Character::itemShop() {
    // buttons are drawn (added to the allegro display)
    Button item1Button("Health Boost - Cost: 2 Coins", 600, 35, 60, 125, IRIS, LIGHT_BLUE);
    Button item2Button("Potion of Healing - Cost: 5 Coins", 600, 35, 60, 170, IRIS, LIGHT_BLUE);
    Button item3Button("Fame Boost - Cost: 2 Coins", 600, 35, 60, 215, IRIS, LIGHT_BLUE);
    Button item4Button("Strength Bonus - Cost: 5 Coins", 600, 35, 60, 260, IRIS, LIGHT_BLUE);
    Button item5Button("Money Boost - Cost: 2 Coins", 600, 35, 60, 305, IRIS, LIGHT_BLUE);
    Button item6Button("Lucky Charm - Cost: 5 Coins", 600, 35, 60, 350, IRIS, LIGHT_BLUE);
    Button backButton("Back", 150, 50, 60, 400, IRIS, BLACK);

    ALLEGRO_EVENT ev;

    while (true) {
        // timer event source is unregistered
        al_unregister_event_source(event_queue, al_get_timer_event_source(timer));

        // background colour, title, description message, and number of coins is added to the allegro display
        al_clear_to_color(BLACK);
        al_draw_text(title_font, IRIS, 360, 30, ALLEGRO_ALIGN_CENTRE, "Item Shop");
        al_draw_text(regular_font, IRIS, 360, 90, ALLEGRO_ALIGN_CENTRE, "These upgrades will help you on your journey!");
        al_draw_textf(subtitle_font, IRIS, 360, 416, ALLEGRO_ALIGN_CENTRE, "Coins: %d", money);

        // if the user lacks suffient money to buy certain items, hover is set to false for the items
        // this prevents users from buying items that they cannot afford (survive after buying)
        if (money < 6) {        // character must have 6 coins to but items 2, 4, and 6
            item2Button.setHover(false);
            item4Button.setHover(false);
            item6Button.setHover(false);
            if (money < 3) {    // character must have 3 coins to but items 1, 3, and 5
                item1Button.setHover(false);
                item3Button.setHover(false);
                item5Button.setHover(false);
            }
        }
        // buttons are drawn (added to the allegro display)
        // item hover method is called for each button (this updates the text displayed depending on if the user is hovering over them)
        itemHover(item1Button, "Health Boost - Cost: 2 Coins", "Increases Maximum Health Points by 1", ev);
        itemHover(item2Button, "Potion of Healing - Cost: 5 Coins", "Heals 2 extra HP per Day", ev);
        itemHover(item3Button, "Fame Boost - Cost: 2 Coins", "Increases Maximum Fame Points by 1", ev);
        itemHover(item4Button, "Strength Bonus - Cost: 5 Coins", "Reduces Chance of Losing Battles", ev);
        itemHover(item5Button, "Money Boost - Cost: 2 Coins", "Increases Maximum Money by 1", ev);
        itemHover(item6Button, "Lucky Charm - Cost: 5 Coins", "Increases Loot while Treasure Hunting", ev);
        backButton.draw(ev);

        al_flip_display();

        if (item1Button.checkClicked(ev)) {
            maxHealth++;        // if item 1 is clicked, max health increases by 1, and purchase item method is called
            purchaseItem("Purchase: You bought a health boost from the item shop.", 2);
        } else if (item2Button.checkClicked(ev)) {
            healthPotion += 2;  // if item 2 is clicked, health potion increases by 2, and purchase item method is called
            purchaseItem("Purchase: You bought a potion of healing from the item shop.", 5);
        } else if (item3Button.checkClicked(ev)) {
            maxFame++;          // if item 3 is clicked, max fame increases by 1, and purchase item method is called
            purchaseItem("Purchase: You bought a fame boost from the item shop.", 2);
        } else if (item4Button.checkClicked(ev)) {
            strengthBonus += 2; // if item 4 is clicked, strength increases by 2, and purchase item method is called
            purchaseItem("Purchase: You bought a strength bonus from the item shop.", 5);
        } else if (item5Button.checkClicked(ev)) {
            maxMoney++;         // if item 5 is clicked, max money increases by 1, and purchase item method is called
            purchaseItem("Purchase: You bought a money boost from the item shop.", 2);
        } else if (item6Button.checkClicked(ev)) {
            luckyCharm += 2;    // if item 6 is clicked, lucky charm increases by 2, and purchase item method is called
            purchaseItem("Purchase: You bought a lucky charm from the item shop.", 5);
        } else if (backButton.checkClicked(ev)) {
            return true;    // if back button is clicked, method returns true
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            return false;   // if allegro display is closed, method returns false
        }
        al_wait_for_event(event_queue, &ev);
    }
}
// method recieves a button, two strings, and an allegro event as parameters
// method draws shop item button (text is determined by whether user is hovering over button)
void Character::itemHover(Button &i, string m1, string m2, ALLEGRO_EVENT &ev) {
    if (i.checkHover(ev)) {
        if (i.getHover()) {
            i.setText(m2);  // if the user is hovering over the button, text is set to item description
        } else {
            i.setText("Insuffient Funds");  // text is set to insuffient funds if user hovers over the button but cannot afford the item
        }
    } else {
        i.setText(m1);  // if the user is not hovering over the button, text is set default item title
    }
    i.draw(ev); // button is drawn
}
// method recieves a string and an integer (item cost) as parameters
// updates money and purchases, and prints purchase to console
void Character::purchaseItem(string m, int c) {
    cout << endl << m << endl;  // purchase is printed on console
    setMoney(money - c);    // item cost is subtracted from current money
    al_register_event_source(event_queue, al_get_timer_event_source(timer));    // timer is registered to update allegro display
    purchases++;    // purchases is increased by 1
}
// displays current stats on allegro display and responds to user input
// returns true if user click back button and false is user closes the allegro display
bool Character::currentStats() {
    // back button is declared
    Button backButton("Back", 150, 50, 60, 400, IRIS, BLACK);

    ALLEGRO_EVENT ev;

    while (true) {
        // background colour, title, and description message is added to the allegro display
        al_clear_to_color(BLACK);
        al_draw_textf(title_font, IRIS, 360, 30, ALLEGRO_ALIGN_CENTRE, "Current Stats", day);
        al_draw_text(regular_font, IRIS, 360, 90, ALLEGRO_ALIGN_CENTRE, "All stats must stay above zero in order for you to survive");
        al_draw_text(regular_font, IRIS, 360, 115, ALLEGRO_ALIGN_CENTRE, "Make careful decisions! Every day, each field will drop by three");

        // draw current stats method is called for each field to draw the character's stats
        drawCurrentStats(145, "Health: %d / %d", health, maxHealth, GREEN1);
        drawCurrentStats(230, "Fame: %d / %d", fame, maxFame, GREEN2);
        drawCurrentStats(315, "Money: %d / %d", money, maxMoney, GREEN3);

        // back button is drawn (added to the allegro display)
        backButton.draw(ev);

        al_flip_display();

        if (backButton.checkClicked(ev)) {
            return true;    // if back button is clicked, method returns true
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            return false;   // if allegro display is closed, method returns false
        }
        al_wait_for_event(event_queue, &ev);
    }
}
// recieves integer for y value, a string, the field value, the max field value, and an allegro colour as parameters
// draws bars to represent the character's current stats
void Character::drawCurrentStats(int y, string m, int f, int mf, ALLEGRO_COLOR c) {
    // draws bar at the given y value in the given colour
    al_draw_filled_rounded_rectangle(80, y, 640, y + 70, 10, 10, c);
    if (560 * f / mf != 0) {
        // fills bar (in a darker colour - found using hover colour method) based on field percentage out of the max field value
        al_draw_filled_rounded_rectangle(80, y, 80 + 560 * f / mf, y + 70, 10, 10, Button::findHoverColour(c));
    }
    // draws outline around bar and the given message (displaying the field and its corresponding stats)
    al_draw_rounded_rectangle(80, y, 640, y + 70, 10, 10, LIGHT_BLUE, 3);
    al_draw_textf(subtitle_font, LIGHT_BLUE, 360, y + 20, ALLEGRO_ALIGN_CENTRE, m.c_str(), f, mf);
}
// displays tasks menu on allegro display and responds to user input
// returns true if user click back button and false is user closes the allegro display
bool Character::tasksMenu() {
    // back button is declared
    Button backButton("Back", 150, 50, 60, 400, IRIS, BLACK);

    ALLEGRO_EVENT ev;

    while (true) {
        // background colour, title, and description message is added to the allegro display
        al_clear_to_color(BLACK);
        al_draw_textf(title_font, IRIS, 360, 30, ALLEGRO_ALIGN_CENTRE, "Tasks", day);
        al_draw_text(regular_font, IRIS, 360, 90, ALLEGRO_ALIGN_CENTRE, "Complete all tasks to win!");

        // draw tasks method is called for each field to draw the character's progres in terms of tasks completed
        drawTasks(125, "Hunt for Food ", " Times: ", food, difficulty);
        drawTasks(180, "Fight Monster ", " Times: ", attack, difficulty);
        drawTasks(235, "Search for Treasure ", " Times: ", treasure, difficulty);
        drawTasks(290, "Survive for ", " Days: ", day - 1, difficulty * 4);
        drawTasks(345, "Purchase ", " Items: ", purchases, difficulty);

        // back button is drawn (added to the allegro display)
        backButton.draw(ev);

        al_flip_display();

        if (backButton.checkClicked(ev)) {
            return true;    // if back button is clicked, method returns true
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            return false;   // if allegro display is closed, method returns false
        }
        al_wait_for_event(event_queue, &ev);
    }
}
// recieves integer for y value, two strings, the number of tasks completed, and the total number of tasks that need to completed
// draws bars to represent the character's progess in terms of tasks completed
void Character::drawTasks(int y, string m1, string m2, int t, int mt) {
    // messages are combined to produce message that will appear on the given task bar
    m1 += to_string(mt);
    m1 += m2;
    // draws bar at the given y value
    al_draw_filled_rounded_rectangle(80, y, 640, y + 40, 10, 10, IRIS);
    if (t >= mt) {
        // if all necessary tasks have been completed, bar is filled and "completed" is added to the message
        al_draw_filled_rounded_rectangle(80, y, 80 + 560, y + 40, 10, 10, Button::findHoverColour(IRIS));
        m1 += "Completed";
    } else {
        // if not all necessary tasks have been completed, bar is filled based on tasks complete and the number of tasks complete is added to the message
        m1 += "%d / %d";
        if (t > 0) {
            al_draw_filled_rounded_rectangle(80, y, 80 + 560 * t / mt, y + 40, 10, 10, Button::findHoverColour(IRIS));
        }
    }
    // draws outline around bar and the given message (displaying the user's progress in completing the character's tasks)
    al_draw_rounded_rectangle(80, y, 640, y + 40, 10, 10, LIGHT_BLUE, 3);
    al_draw_textf(subtitle_font, LIGHT_BLUE, 360, y + 5, ALLEGRO_ALIGN_CENTRE, m1.c_str(), t, mt);
}
// method prints stats regarding the three fields and the tasks complete onto the console
void Character::stats() {
    // method access private variables to display stats on the console
    cout << "Health: " << health << "/" << maxHealth << endl;
    cout << "Fame: " << fame << "/" << maxFame << endl;
    cout << "Money: " << money << "/" << maxMoney << endl;
    cout << "Tasks Complete: " << tasksComplete << "/5" << endl;
}
// method draws stats regarding the three fields onto the allegro display
void Character::drawStats() {
    al_draw_text(subtitle_font, IRIS, 490, 180, ALLEGRO_ALIGN_CENTRE, "Current Stats:");
    al_draw_line(415, 210, 565, 210, IRIS, 2);      // used to underline "Current Stats"
    al_draw_textf(subtitle_font, IRIS, 490, 220, ALLEGRO_ALIGN_CENTRE, "Health: %d / %d", health, maxHealth);
    al_draw_textf(subtitle_font, IRIS, 490, 250, ALLEGRO_ALIGN_CENTRE, "Fame: %d / %d", fame, maxFame);
    al_draw_textf(subtitle_font, IRIS, 490, 280, ALLEGRO_ALIGN_CENTRE, "Money: %d / %d", money, maxMoney);
}
// method displays characters daily loss in the three fields, then method updates variables corresponding to each field
void Character::dailyLoss() {
    // next button is declared
    Button nextButton("Next", 150, 50, 510, 400, IRIS, BLACK);

    // background colour, title, and description message is added to the allegro display
    al_clear_to_color(BLACK);
    al_draw_textf(title_font, IRIS, 360, 30, ALLEGRO_ALIGN_CENTRE, "Daily Loss", day);
    al_draw_text(regular_font, IRIS, 360, 90, ALLEGRO_ALIGN_CENTRE, "All stats must stay above zero in order for you to survive");
    al_draw_text(regular_font, IRIS, 360, 115, ALLEGRO_ALIGN_CENTRE, "Make careful decisions! Every day, each field will drop by three");

    // all fields are reduced by 3
    setHealth(getHealth() - 3);
    setFame(getFame() - 3);
    setMoney(getMoney() - 3);

    drawLoss(145, "Health: %d / %d", health, maxHealth, GREEN1);    // draw loss method is called for health to draw drop in health

    if (healthPotion > 0) {
        int startingHealth = getHealth();   // variable used to hold starting health
        if (startingHealth == 0) {
            // if starting health is 0, healing potion does not activate
            al_draw_filled_rounded_rectangle(80, 145, 640, 215, 10, 10, GREEN1);
            // message showing healing potion failed is displayed
            al_draw_text(subtitle_font, LIGHT_BLUE, 360, 165, ALLEGRO_ALIGN_CENTRE, "Health Reached 0 - Potion of Healing Failed");
            al_draw_rounded_rectangle(80, 145, 640, 215, 10, 10, LIGHT_BLUE, 3);
        } else {
            // if at least 1 healing potion has been purchased, and health is greater than 0, potion activates
            setHealth(getHealth() + healthPotion);
            for (int i = 560 * startingHealth / maxHealth; i < 560 * health / maxHealth; i++) {
                al_draw_filled_rounded_rectangle(80, 145, 640, 215, 10, 10, GREEN1);
                al_draw_filled_rounded_rectangle(80, 145, 80 + i, 215, 10, 10, RED);    // bar is red while potion of health is activated
                if (i * maxHealth / 560 + 1 == health) {
                    // once potion finishes activating, health bar is displayed normally
                    al_draw_filled_rounded_rectangle(80, 145, 80 + i, 215, 10, 10, Button::findHoverColour(GREEN1));
                    al_draw_textf(subtitle_font, LIGHT_BLUE, 360, 165, ALLEGRO_ALIGN_CENTRE, "Health: %d / %d", health, maxHealth);
                } else {
                    // while potion of healing is activated, message is updated
                    al_draw_text(subtitle_font, LIGHT_BLUE, 360, 165, ALLEGRO_ALIGN_CENTRE, "Potion of Healing");
                }
                al_draw_rounded_rectangle(80, 145, 640, 215, 10, 10, LIGHT_BLUE, 3);
                al_flip_display();
                al_rest(0.01);      // a brief delay is added, so user can watch the health potion take effect
            }
        }
    }
    drawLoss(230, "Fame: %d / %d", fame, maxFame, GREEN2);      // draw loss method is called for fame to draw drop in health
    drawLoss(315, "Money: %d / %d", money, maxMoney, GREEN3);   // draw loss method is called for money to draw drop in health

    ALLEGRO_EVENT ev;

    while (true) {
        // next button is drawn
        al_draw_filled_rectangle(508, 398, 662, 452, BLACK);
        nextButton.draw(ev);

        al_flip_display();

        if (nextButton.checkClicked(ev)) {
            break;  // while loop breaks if user clicks next button
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exitGame = true;
            break;  // exitGame is set to true while loop breaks if user closes allegro display
        }
        al_wait_for_event(event_queue, &ev);
    }
    checkGameOver();    // checks if player has lost (if any field has reached 0)
}
// recieves integer for y value, a string, the field value, the max field value, and an allegro colour as parameters
// draws bars to represent the character's drop in stats
void Character::drawLoss(int y, string m, int f, int mf, ALLEGRO_COLOR c) {
    // for loop increments from current field value to decreased field value
    for (int i = 560 * (f + 3) / mf; i > 560 * f / mf; i--) {
        // draws bar at the given y value in the given colour
        al_draw_filled_rounded_rectangle(80, y, 640, y + 70, 10, 10, c);
        if (i * mf / 560 != 0) {
            // fills bar (in a darker colour - found using hover colour method) based on field percentage out of the max field value
            al_draw_filled_rounded_rectangle(80, y, 80 + i, y + 70, 10, 10, Button::findHoverColour(c));
        }
        // draws outline around bar and the given message (displaying the field and its corresponding stats)
        al_draw_rounded_rectangle(80, y, 640, y + 70, 10, 10, LIGHT_BLUE, 3);
        al_draw_textf(subtitle_font, LIGHT_BLUE, 360, y + 20, ALLEGRO_ALIGN_CENTRE, m.c_str(), i * mf / 560, mf);
        al_flip_display();
        al_rest(0.001);     // a very brief delay is added, so user can watch their fields decrease
    }
}
// checks how many tasks the user has completed for the character and calls game over function if all tasks are complete
void Character::checkProgress() {
    tasksComplete = 0;  // tasks complete is set to zero
    // tasks complete is incremented for every task that has been complete
    // the number of tasks that must be completed is depedant on the difficulty
    if (food >= difficulty)
        tasksComplete++;
    if (attack >= difficulty)
        tasksComplete++;
    if (treasure >= difficulty)
        tasksComplete++;
    if (day - 1 >= difficulty * 4)
        tasksComplete++;
    if (purchases >= difficulty)
        tasksComplete++;
    if (tasksComplete == 5) {
        if (!wonGame && !exitGame) {
            // if all tasks have been complete, game over method is called and wonGame is set to true
            gameOver("won");
            wonGame = true;
        }
    }
}
// checks if character has reached 0 in any field and calls game over method if necessary
void Character::checkGameOver() {
    // if game over method is called, it is passed a string corresponding to the reason for the character's loss
    if (health == 0) {
        gameOver("health");
    } else if (fame == 0) {
        gameOver("fame");
    } else if (money == 0) {
        gameOver("money");
    }
}
// method recieves a string as parameters (which states the reason the game has ended)
// displays game over screen on allegro display and responds to user input
void Character::gameOver(string m) {
    // variables are declared
    string message1, message2, title;
    exitGame = true;    // exitGame is set to true

    if (m != "won") {
        // if string from parameters is not "won", title is set to "Game Over"
        title = "Game Over";

        checkProgress(); // calls method to update number of tasks the player completed

        // based on the reason in which the player lost, the first message is updated
        if (m == "health") {
            message1 = "Unfortunately, you ran out of HP. ";
        } else if (m == "fame") {
            message1 = "Unfortunately, you lost all your fame. ";
        } else {
            message1 = "Unfortunately, you have gone broke. ";
        }
        // the first message is updated based on the number of days the player survived
        message1 += "You survived for ";
        message1 += to_string(day - 1);
        message1 += " days,";
        // the second message is updated based on the number of tasks the player completed
        message2 = "and completed ";
        message2 += to_string(tasksComplete);
        message2 += " out of the 5 tasks.";
    } else {
        // if string from parameters is "won", title is set to "You Won"
        title = "You Won";
        // the first message is updated based on the number of days it took the player to complete all the tasks
        message1 = "Congratulations you completed all the tasks in only ";
        message1 += to_string(day - 1);
        message1 += " days.";
        // the second message prompts the user to either continue playing or to try again
        message2 = "Feel free to continue playing or to try again.";
    }

    // title and messages are printed to the console
    cout << title << ": " << message1 << endl << message2 << endl << endl;

    // buttons are declared
    Button playAgainButton("Play Again", 150, 50, 80, 300, IRIS, BLACK);
    Button exitButton("Exit", 150, 50, 490, 300, IRIS, BLACK);
    Button continueButton("Continue", 150, 50, 285, 300, IRIS, BLACK);

    ALLEGRO_EVENT ev;

    while (true) {
        // background colour, title, and description message is added to the allegro display
        al_clear_to_color(BLACK);
        al_draw_text(title_font, IRIS, 360, 130, ALLEGRO_ALIGN_CENTRE, title.c_str());
        al_draw_text(subtitle_font, IRIS, 360, 190, ALLEGRO_ALIGN_CENTRE, message1.c_str());
        al_draw_text(subtitle_font, IRIS, 360, 220, ALLEGRO_ALIGN_CENTRE, message2.c_str());

        // play again and exit button is drawn
        playAgainButton.draw(ev);
        exitButton.draw(ev);

        if (m == "won") {
            // if string from parameters is "won", continue button is drawn
            continueButton.draw(ev);
        }
        al_flip_display();

        if (continueButton.checkClicked(ev) && m == "won") {
            exitGame = false;   // if continue button is clicked, exitGame is set to false (game continues)
            break;              // while loop breaks
        } else if (playAgainButton.checkClicked(ev)) {
            playAgain = true;   // if play again button is clicked, playAgain is set to true
            break;              // while loop breaks
        } else if (exitButton.checkClicked(ev) || ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;  // if exit button is clicked or allegro display is closed, while loop breaks
        }
        al_wait_for_event(event_queue, &ev);
    }
}
