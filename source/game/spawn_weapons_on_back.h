/*
SPAWN_WEAPONS_ON_BACK.H

port: tap vs hold for game.spawn_weapons_on_back (cheats.c). A short release
of Back (View) drops weapons; a longer hold is still the scoreboard. Shared
so the predicates can be tested without the game.
*/

#ifndef SPAWN_WEAPONS_ON_BACK_H
#define SPAWN_WEAPONS_ON_BACK_H

#ifdef __cplusplus
extern "C" {
#endif

enum
{
	/* 0.4s at 30 Hz: a tap drops weapons; hold Back for the scoreboard */
	SPAWN_WEAPONS_ON_BACK_TAP_TICKS = 12,
	/* 3s between drops so a pile is not spawned every tap */
	SPAWN_WEAPONS_ON_BACK_COOLDOWN_TICKS = 90
};

/* previous_held is last tick's Back hold count; now_held is this tick's
(0 when released). A tap is a release after 1..TAP_TICKS. */
static int spawn_weapons_on_back_is_tap(
	unsigned char previous_held,
	unsigned char now_held)
{
	return previous_held > 0 && previous_held <= SPAWN_WEAPONS_ON_BACK_TAP_TICKS && now_held == 0;
}

/* last_tick < 0 means never dropped. now_tick is game_time_get(). */
static int spawn_weapons_on_back_cooldown_ready(
	long now_tick,
	long last_tick)
{
	return last_tick < 0 || now_tick - last_tick >= SPAWN_WEAPONS_ON_BACK_COOLDOWN_TICKS;
}

#ifdef __cplusplus
}
#endif

#endif
