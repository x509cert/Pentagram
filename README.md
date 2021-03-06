# Pentagram
C and ASM source to a D&amp;D-style game I wrote YEARS ago when I was a kid!

There's a long story to this. I was living in New Zealand, and my girlfriend at the time was heading to Europe for six months with her girlfriends. So I had to come up with something to do to keep me out of trouble. So I decided to write a role-playing game (RPG)! 

I was asked by a Reddit user, u/Abounding, if I would post the code to the game. Here's the thread https://www.reddit.com/r/ProgrammerHumor/comments/pzu1fu/comment/hf3z7hc/?utm_source=reddit&utm_medium=web2x&context=3.

So here's the code!

Please don't judge me on this! I am older and wiser now :)

Here's some points of interest...

1) This code was written in 1989!
2) I uncovered the code on a couple of 5.25" disks I had safely stored (in the Reddit post, I said 3.5", which is incorrect) - I used a USB 5.25" drive to read the disks.
3) I was not a seasoned, grumpy developer at the time, it was a hobby!
4) This ran on an IBM XT compatible machine, with an Intel 8086 CPU in 640kB of RAM and 8MHz
5) It ran on MS-DOS 3.2
6) The game did not take advantage of the extra 384kB of extended RAM, by design!
7) The video card of the day was EGA (https://en.wikipedia.org/wiki/Enhanced_Graphics_Adapter)
8) I used Microsoft C Compiler 5.1 (https://www.pcjs.org/software/pcx86/lang/microsoft/c/5.10/) and MASM 5.1
9) This code predates C++!
10) I wrote the code on an Amstrad PC1640 (https://en.wikipedia.org/wiki/PC1512) in my bedroom!
11) The Microsoft Linker that came with the MS C compiler could not handle this code, so I had to use the Phoenix Linker (plink86, https://everything2.com/title/plink) - it allows for more control of overlaid code with better memory management.
12) The ASM code is primarily to handle video manipulation, such as smooth pixel scrolling of the main window.
13) I have an EXE of the code, and it runs in DOSBox. My 20yr old son has played it, and says "It doesn't suck!"
14) To aid installation of the resulting binary and supporting files (bitmaps, maps, dungeons etc.), I wrote my own installation tool, installation language (I called it MELT - Michael's Experimental Language Translator) and compression tool - it used Limpel-Zev and Huffman, whichever offered the best compression based on the data.
15) I wrote a bunch of supporting tools - a map editor, a dungeon builder and a tool to create sprites and other graphics.
16) Remember, filenames back then were only 8.3!
17) I wrote a manual for the game using Windows and Aldus PageMaker and the game won a New Zealand Software Award in 1990 :) 
18) It's fun to see me thinking about optimization back then. Look at ffplot.asm - line 20! 
19) I kept out of trouble :) 
