# kana_dictation
Japanese Kana training application: generates random romaji sillables for you to translate into the japanese sillabaries. Then shows the hiragana or katakana for them. Written entirely in SDL2 and C++ so it can be ported to a variety of systems.

You are supposed to write the kana with pen and paper. This is supposed to be an educative tool, not a game.

In order to build it be sure to build libdansdl2 and herramientas_proyecto first.

Features:

- Choose from hiragana or katakana sillabaries to practice.
- Choose from 1 or 20 sillables to practice at once.
- Allow for user selected sillable groups (ie. practice only the vowels and the "K" group).
- Configurable kana database via json-like files, in case I forgot to put some in.
- Quick and to the point. Entirely controlled via keyboard (because mouse pointing is slooooow).

Planned features:

- Invert translation direction: kana to romaji / romaji to kana.
- A title logo somewhere :P.
- Save user preferences to configuration files.
- Multiple languages in the user interface.
- Quick translation from the command line (input the romaji sillables to get the kana on the console or screen).
- Support for multiple screen modes (if SDL2 allows it). So far it's only 800x500, windowed.
- Support to practice both hiragana and katakana at the same time.

Thanks to:

Ed Merritt for the Akashi font.
Kagura Zakayuzu for the Yuzu Pop A font.
The background image comes from www.filemorgue.com and is a fragment from an original by Kevin Connors.
