# KanaFun
Japanese Kana training application: generates random romaji sillables for you to translate into the japanese sillabaries. Then shows the hiragana or katakana for them. Written entirely in SDL2 and C++ so it can be ported to a variety of systems.

You are supposed to write the kana with pen and paper. This is supposed to be an educative tool, not a game.

In order to build it be sure to build libdansdl2 and herramientas_proyecto first.

Features:

- Choose from hiragana or katakana sillabaries to practice.
- Choose from 1 or 20 sillables to practice at once.
- Configurable translation direction (romaji to kana or kana to romaji).
- Allow for user selected sillable groups (ie. practice only the vowels and the "K" group).
- Configurable kana database via json-like files, in case I forgot to put some in.
- Quick and to the point. Entirely controlled via keyboard (because mouse pointing is slooooow).
- Multiple languages in the user interface.
- Support for multiple screen modes (actually, dirty resizes from a base of 800x500).
- Save user preferences with respect to kanas to practice into configuration files.
- Configurable backgrounds (up to five preinstalled) for a more pleasant visual experience.

None of these features are planned, but maybe we could:

- Quick translation from the command line (input the romaji sillables to get the kana on the console or screen).
- Support to practice both hiragana and katakana at the same time.
- Recorded samples of the sillables, so you can listen as well as write.

Thanks to:

- Ed Merritt for the Akashi font.
- Kagura Zakayuzu for the Yuzu Pop A font.
- Astigmatic One Eye Typographic Institute, their Shojumaru font was used to create the logo.

