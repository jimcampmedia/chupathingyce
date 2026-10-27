/*
SPAWN_WEAPONS_ON_BACK_TEST.C

Tap vs hold and the drop cooldown for game.spawn_weapons_on_back
(source/game/spawn_weapons_on_back.h). Compiled by
tools/test_spawn_weapons_on_back.py.
*/

#include "game/spawn_weapons_on_back.h"

#include <stdio.h>
#include <stdlib.h>

static int failures;

static void expect(
	int condition,
	char const *message)
{
	if (!condition)
	{
		fprintf(stderr, "FAIL: %s\n", message);
		failures++;
	}
}

int main(
	void)
{
	expect(!spawn_weapons_on_back_is_tap(0, 0), "idle is not a tap");
	expect(!spawn_weapons_on_back_is_tap(0, 1), "press is not a tap");
	expect(spawn_weapons_on_back_is_tap(1, 0), "one-tick release is a tap");
	expect(spawn_weapons_on_back_is_tap(SPAWN_WEAPONS_ON_BACK_TAP_TICKS, 0),
		"release at the tap limit is a tap");
	expect(!spawn_weapons_on_back_is_tap(SPAWN_WEAPONS_ON_BACK_TAP_TICKS + 1, 0),
		"longer hold is the scoreboard, not a tap");
	expect(!spawn_weapons_on_back_is_tap(20, 21), "still holding is not a tap");
	expect(!spawn_weapons_on_back_is_tap(20, 0), "scoreboard release is not a tap");

	expect(spawn_weapons_on_back_cooldown_ready(0, -1), "never dropped is ready");
	expect(spawn_weapons_on_back_cooldown_ready(90, 0), "exactly the cooldown is ready");
	expect(!spawn_weapons_on_back_cooldown_ready(89, 0), "before the cooldown is not ready");
	expect(spawn_weapons_on_back_cooldown_ready(200, 100), "later than the cooldown is ready");

	if (failures)
	{
		fprintf(stderr, "%d failed\n", failures);
		return 1;
	}
	puts("ok");
	return 0;
}
