#!/bin/bash

# get data & Doukutsu.exe with English pre-patched translation
wget https://www.cavestory.org/downloads/cavestoryen.zip
sha256sum -c --ignore-missing dl_data.hash || rm cavestoryen.zip ; test -f cavestoryen.zip || exit
unzip cavestoryen.zip
cp -r CaveStory/* . && rm -r CaveStory
rm cavestoryen.zip

# get XM tracks 
wget https://www.cavestory.org/soundtrack/cave-story/xm/all.tar
sha256sum -c --ignore-missing dl_data.hash || rm all.tar ; test -f all.tar || exit
mkdir -p xm
tar xvf all.tar --directory=xm
cd xm
org_names=(\
Access \
Gestation \
"Mimiga Town" \
Plant \
"Balrog's Theme" \
Gravity \
Cemetery \
Safety \
"Mischievous Robot" \
Pulse \
"On to Grasstown" \
"Eyes of Flame" \
"Meltdown 2" \
Tyrant \
"Run!" \
"Jenka 1" \
"Jenka 2" \
"Labyrinth Fight" \
Geothermal \
Oppression \
"Living Waterway" \
Quiet \
"Scorching Back" \
Moonsong \
"Hero's End" \
"Cave Story" \
"Last Cave" \
Balcony \
Charge \
Zombie \
"Last Battle" \
"Break Down" \
"Running Hell" \
"Seal Chamber" \
"The Way Back Home" \
"Got Item!" \
"Get Heart Tank!" \
"Victory!" \
"Gameover" \
"Toroko's Theme" \
White \
XXXX \
"Wind Fortress" \
"Halloween 2" \
"Pier Walk" \
"Untitled (Rockorg)" \
Meltdown \
"People of the Root" \
)

new_names=(access vivi mura plant ginsuke gravity cemetery anzen wanpaku kodou weed fireeye mdown2 dr escape jenka jenka2 maze grand ironh marine quiet wanpak2 oside requiem curly lastcave balcony lastbtl zonbie lastbt3 bdown hell ballos ending fanfale1 fanfale2 fanfale3 gameover toroko white xxxx kaze halloween2 cave rockorg mdown leef)

for i in "${!org_names[@]}"; do mv "${org_names[$i]}.xm" "${new_names[$i]}.xm"; done
ls
cd ..
