# Duck Atari - University Project

Duck Atari is an Atari-style game, reminiscent of River Raid, developed in the C programming language using SDL 2.0. It utilizes SDL_image, SDL_TTF, and SDL_Mixel init.

## Game Elements:

1. **Mines:**
   - *Type:* Just mines, no additional actions.

2. **Cargo Spaceships:**
   - *Type:* Non-shooting, dropping supplies when destroyed.
   - *Supplies:* Power bullet, shield, health, fuel.

3. **Bomber:**
   - *Behavior:* Descends from the top and ascends from the bottom, shooting bombs forward.

4. **Jets:**
   - *Behavior:* Fast-moving enemies from the right, with bullets that track the player's spaceship.

## Menu Features:

- Settings and Leaderboard included.
- Leaderboard displays the last top 10 players by score.

## Technical Details:

- Developed using C for the Fundamental Programming course at the University of Amirkabir.
- **Dependencies:** SDL2.0 SDL_image, SDL_TTF, and SDL_Mixel init.

## Known Issues:

1. After the second gameplay session, certain problems arise.
2. Bombers and cargos do not respawn.
3. Segmentation fault occurs upon closing the game, possibly related to texture deallocation.
4. Power bullet activation requires pressing a, w, s, d once while holding space.

## To-Do List:

1. Improve the aesthetics and scroll functionality of the leaderboard (extend beyond the top 10).
2. Store the start and end times of each game in leaderboard.csv and display them.
3. Enhance the visual appeal of the menu.
4. Implement settings saving functionality.
5. Expand the range of available settings.
6. Balance game levels for a more enjoyable experience.

---

## Contributing to Duck Atari
Contributions to the Duck Atari project are welcome! If you wish to contribute, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Make your changes and ensure that the codebase passes all tests.
4. Submit a pull request describing your changes.
