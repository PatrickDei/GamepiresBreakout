# Breakout game

Simple remake of the breakout game

### All necessary libraries are incuded
...
Using tinyxml2 library to parse thourgh xml files quickly and with ease

Using SFML API to easily manipulate objects on screen
> It does not contain any game loop or a physics engine
...

## To play the game
Simply follow the path Breakout_Gamepires/Breakout_Gamepires and launch Breakout_Gamepires.exe from there.

## To view source code
If using Visual Studio simply follow the path Breakout_Gamepires/ and launch the Breakout_Gamepires.sln from there

## To change game settings
Most of games ssettings can be changed from 2 files:
...
### Parameters.xml
They define basic elements like default launch angle, player width, ball speed...
Found in: Breakout_Gamepires/Breakout_Gamepires/Parameters/Parameters.xml
...
...
### Items.xml
...
Block elements are defined such as block health, score, sounds...
Found in: Breakout_Gamepires/Breakout_Gamepires/Profiles/Items.xml
...

### Side note
Platform x64 has been disabled in the project because the sfml libraries included are only supported on the 32-bit architecture
SFML developers note:
> Choose 64-bit packages only if you have good reasons.
...

Sound effects obtained from www.zapsplat.com