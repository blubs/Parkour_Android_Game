# Highrise (working title)


## Synopsis
This project is the game that [my NDK Engine](https://github.com/blubs/NDK_Engine) was written for.
This game is a first person parkour game for Android that is set in Highrise buildings.

## Engine Features
Because this game was built on the [NDK Engine](https://github.com/blubs/NDK_Engine), refer to [the NDK Engine GitHub page](https://github.com/blubs/NDK_Engine) for a comprehensive list of Engine features.

## Added Engine Changes
This project includes several added engine features not yet added to the original [NDK Engine](https://github.com/blubs/NDK_Engine) project.
* Rendering the game at a lower screen resolution
* Support for raw rgba 8888 textures
* Audio Source sounds can now be stopped
* Skeletons can now skip frames on update calls (to maintain animation fps)
* Added features for combining separate meshes into a single mesh for batching daw calls
* Added a few additional math functions (clamp, weighted average, etc...)
* Random class now uses PRNG to use Multiply With Carry algorithm
* Changed how engine input is handled
* Support for Android's keybord input handling
* Large refactoring of const identifiers
* Support for Multi-touch input (up to ten fingers)
* The way Shaders are loaded has been improved
* Addition of a Time class that we reference for realtime timing needs 