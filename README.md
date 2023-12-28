# Projet TVID
## TEAM MBA_VT: VINCENT THONG , MAXIME BOY-ARNOULD
TASKS Done :
 - PART A : VINCENT && MAXIME
 - PART B : MAXIME
## SETUP
- Linux environment
- G++, tools for C++
- SDL2 & SDL2_image
## SETUPS COMMANDs
sudo apt-get install libsdl2-2.0 libsdl2-dev
sudo apt-get install libsdl2-image-2.0-0 libsdl2-image-dev 
## COMPILATION
mkdir build; cd build; cmake ..; make
## Execution:
.tvid [--bob][--frame_period] 1000
OR
.tvid [--fps] 1000

During execution : 
 - input pgm directory with pgm files of a video with mpeg2dec (see read me of mpeg2dec)
 - input ppm path (any paths to create files)

# RAPPORT et Réponses à l'énoncé:
## Réponses

### A. Tests avec Flux MPEG-2 Élémentaire
1. **Test avec mpeg2dec sur .m2v** - Sélection de `bw_counting` pour la suite du TP.
3. **Observation des PGM Générées** - Grayscale images de 720x720 pixels, 8 bits de depth, structurées en canneaux YUV (720x480 pour Y, 320x240 pour U et V).
4. **Modification de mpeg2dec** - Utilisation de `print` pour les flags requis pour chaque frame.
7. **Option --fps x** - Permet de changer le nombre d'images par seconde.
8. **Option --frame_period** - Utilisation avec mpeg2dec pour ajuster la cadence.
10. **Utilisation de l'Entrelaceur Bob** - Ajout de `--bob` dans la commande.

### B. Flux Vidéo de Chaîne d'Infos
1. **PID du Flux Vidéo** - Identifié comme `0x1422` ou `5154`.
3. **Observation Post-Désentrelacement** - On observe que la video est de relativement basse resolution due a la methode d'entrelacement mais surtout que l'image tremble verticalement de quelque pixels toute les frames.
4. **Flags Observés** - On remarque que pour les 492 premieres frame les flags progressive_frame et top_field_first sont a 1 ce qui ne devrait pas arriver. On remarque les memes problemes de lectures avec l'entrelaceur bob de vlc.
5. **Flag `progressive_sequence`** - On remarque que le flag de progressive_sequence est toujours nul ce qui indique que l'encodeur c'est probablement trompe et que les images ne sont pas progressives mais toutes top_field_first .
6. **Solution heuristique** - Pour reduire les sacades nous avonc rajoute une option --shake qui retire la motie des frames genere apres l'utilisation de l'entrelaceur bob ce qui rend la video moins fluide mais beaucoup moins dificile a regarder.
