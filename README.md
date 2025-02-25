# GW2MusicMacroMender
## Overview
A simple C++ program that tries to fix Guild Wars 2 Music Macros

In Guild Wars 2, there are instruments which can play music ingame for others to hear. Due to the limitations of the game itself, it is very
difficult to play complex music by hand. Hence users have created macros meant to be used with programs such as Autohotkey/External plugins that automatically
play what would normally be humanly impossible sequences. This is allowed within the Terms of Service of the game.

Instruments usually have 3 octaves: Low, Mid and High
Only 1 octave can be active at a time, and the user must swap to another octave entirely to access any of that octave's notes.

However, an update to the game many years ago introduced a 100ms delay between octaves, making it impossible to transition from Low -> High or High -> Low instantly,
breaking many songs that required multi-octave swaps like that.

This program attempts to fix the issue by scanning a music macro and identifying any possible Low -> High and High -> Low transitions, and replacing the notes on the low octave with
notes on the middle octave instead. There is also an option to remove low notes entirely when these cases arise.

Obviously, this changes the way the music will sound, and its success rate is highly variable due to the nature of music. Notable, higher BPM/extremely complex songs
don't work well, but simpler songs tend to have a higher success rate. There is still much room for improvement in this program, but I made this in 1 night.

## How to Use
(Sample files included)

Drag a text file containing the macro into the same directory where the .exe file is. When you open the program, type the name of the file, followed by ".txt" (eg. "Candyman Theme.txt")
The program will then ask whether or not you want to remove low notes, then create a file in the same directory prefixed with the word "Fixed" (eg. "Fixed Candyman Theme.txt")

## Where to get Music Macros?
[Guild Wars 2 Music Box](http://gw2mb.com/archive.php)
