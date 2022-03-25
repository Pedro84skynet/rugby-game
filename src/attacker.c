// Standard headers
#include <stdio.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {

        static int e1 = 1;
        static int x = 0;
        static int y = 0;

        int xp = (int) attacker_position.i;
        int yp = (int) attacker_position.j;


        if (e1) {
            position_t opponent = get_spy_position(defender_spy);
            x = (int) opponent.i - xp;
            if (x > 0) x += 2;
            else x -= 2;
            y = (int) opponent.j - yp;
            e1--;
        }

        while (x != 0) {
            if (x < 0) {
                x++;
                attacker_position = move_position(attacker_position, DIR_UP);
                return DIR_UP;
            } else {
                x--;
                attacker_position = move_position(attacker_position, DIR_DOWN);
                return DIR_DOWN;
            }
        }

        while (y != 0) {
            if (y < 0) y++;
            else y--;
            return DIR_RIGHT;
        }

        return DIR_RIGHT;
}

/*----------------------------------------------------------------------------*/
