// Standard headers
#include <stdio.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(position_t defender_position,
                                      Spy attacker_spy) {

    static int e1 = 1;
    static int e2 = 1;
    static int x = 0;
    static int y = 0;
    static int boolean = 0;
    static int ogx = 0;
    static int lastx = 0;
    static int lasty = 0;

    int xp = (int) defender_position.i;
    int yp = (int) defender_position.j;
    int change = 0;

    if (lastx == xp && lasty == yp) {
        change = 1;
    }

    lastx = xp;
    lasty = yp;

    if (e1) {
        position_t opponent = get_spy_position(attacker_spy);
        ogx = xp;
        x = (int) opponent.i - xp;
        y = (int) opponent.j - yp;
        if (x > 0) boolean = 1;
        e1 = 0;
    }

    if ((x || y) == 0) {
        if ((ogx - xp) > 0) {
            x = ogx - xp + 2;
        } else  if ((ogx - xp) < 0) {
            x = ogx - xp - 2;
        } else {
            x = ogx - xp;
        }
        e2 = 0;
    }

    while (x != 0 && e2) {
        if (y < 0) y++;
        else y--;
        if (x < 0) {
            x++;
            if (change ) {
                defender_position = move_position(defender_position, DIR_UP);
                return DIR_UP;
            } else {
                y++;
                defender_position = move_position(defender_position, DIR_UP_LEFT);
                return DIR_UP_LEFT;
            }

        } else {
            x--;
            if (change) {
                defender_position = move_position(defender_position, DIR_DOWN);
                return DIR_DOWN;
            } else {
                y++;
                defender_position = move_position(defender_position, DIR_DOWN_LEFT);
                return DIR_DOWN_LEFT;
            }
        }
    }

    while (x != 0 && !e2) {
        if (x < 0) {
            x++;
            if (change) {
                defender_position = move_position(defender_position, DIR_UP_RIGHT);
                return DIR_UP_RIGHT;
            } else {
                y++;
                defender_position = move_position(defender_position, DIR_UP);
                return DIR_UP;
            }

        } else {
            x--;
            if (change) {
                defender_position = move_position(defender_position, DIR_DOWN_RIGHT);
                return DIR_DOWN_RIGHT;
            } else {
                y++;
                defender_position = move_position(defender_position, DIR_DOWN);
                return DIR_DOWN;
            }
        }
    }

    while (y != 0 || e2 == 0) {
        if (y < 0) y++;
        else y--;
        if (boolean) {
            boolean = 0;
            defender_position = move_position(defender_position, DIR_UP);
            return DIR_UP;
        } else {
            boolean = 1;
            defender_position = move_position(defender_position, DIR_DOWN);
            return DIR_DOWN;
        }
    }
    return DIR_LEFT;
}

/*----------------------------------------------------------------------------*/
