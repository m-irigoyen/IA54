# P15-TX52

Needed : SFML 2.0 (or higher) : http://www.sfml-dev.org/download/sfml/2.2/index-fr.php

Either do a standard CMake install, or configure your own project following SFML's official instructions.

The CMake file requires SFML libraries. Enter those that end with "-d" for debug, and those that don't have a suffix for realease.
Example : 
AUDIO_DEBUG : SFML-2.3.1/lib/sfml-audio-d.lib
AUDIO_RELEASE : SFML-2.3.1/lib/sfml-audio.lib


Don't forget to copy the DLLs next to the executable file, or it won't work.