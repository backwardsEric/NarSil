===================
Version Information
===================

Sil is a roguelike game technically forked from NPPAngband, but very different
in play.  It was written by Toby Ord and Owen Cotton-Barratt.  The last version
of Sil by its original authors was 1.3.0, released in 2016.

NarSil was written using the Angband 4.2 codebase, and altering that to produce
an almost faithful copy of Sil 1.3.0.

Below is some history of Angband.

Angband History
===============

Angband has been maintained and developed by a succession of volunteers since
it was written in the early 1990s. The current maintainer is Nick McConnell.

The current version is 4.2.3. Detailed information about this version and
previous versions can be found at http://angband.github.io/angband.  Also additional
information can be found at the angband forums (https://angband.live/forums/).

This file was last updated for Angband 3.1.2 and remains here mainly
for historical purposes.

Angband has an incredibly complex history, and is the result of a lot
of work by a lot of people, all of whom have contributed their time and
energy for free, being rewarded only by the pleasure of keeping alive one
of the best freeware games available anywhere.

The version control files, if they existed, would span more than ten years
time, and more than six different primary developers. Without such files,
we must rely on simpler methods, such as change logs, source file diffs,
and word of mouth. Some of this information is summarised in this file.

Please be sure to read the 'Copying and licence information'.

Brief Version History
=====================

First came "VMS Moria", by Robert Alan Koeneke (1985).

Then came "Umoria" (Unix Moria), by James E. Wilson (1989).

Details about the history of the various flavors of "Moria", the direct
ancestor to Angband, can be found elsewhere, and a note from Robert Alan
Koeneke is included in this file. Note that "Moria" has been ported to a
variety of platforms, and has its own newsgroup, and its own fans.

In 1990, Alex Cutler and Andy Astrand, with the help of other students at
the University of Warwick, created Angband 1.0, based on the existing code
for Umoria 5.2.1. They wanted to expand the game, keeping or even
strengthening the grounding in Tolkien lore, while adding more monsters and
items, including unique monsters and artifact items, plus activation,
pseudo-sensing, level feelings, and special dungeon rooms.

Over time, Sean Marsh, Geoff Hill, Charles Teague, and others, worked on
the source, releasing a copy known as "Angband 2.4.frog_knows" at some
point, which ran only on Unix systems, but which was ported by various
people to various other systems. One of the most significant ports was the
"PC Angband 1.4" port, for old DOS machines, which added color and various
other significant changes, only some of which ever made it back into the
official source.

Then Charles Swiger (cs4w+@andrew.cmu.edu) took over, sometime in late
1993, cleaning up the code, fixing a lot of bugs, and bringing together
various patches from various people, resulting in several versions of
Angband, starting with Angband 2.5.1 (?), and leading up to the release of
Angband 2.6.1 (and Angband 2.6.2) in late 1994. Some of the changes during
this period were based on suggestions from the "net", and from various
related games, including "UMoria 5.5", "PC Angband 1.4", and "FAngband".

Angband 2.6.1 was primarily targeted towards Unix/NeXT machines, and it
required the use of the low level "curses" commands for all screen
manipulation and keypress interaction. Each release had to be ported from
scratch to any new platforms, normally by creating visual display code that
acted as a "curses" emulator. One such port was "Macintosh Angband 2.6.1",
by Keith Randall, which added support for color, and which formed the basis
for the first release of Angband 2.7.0.

During the last half of 1994, Ben Harrison had been playing with the
Angband source, primarily to investigate the possibility of making some
kind of automatic player for Angband, like the old "rogue-o-matic" program
for the game "Rogue". The difficulty of compiling a version for the
Macintosh, and the complexity of the code, prevented this, and so Ben began
cleaning up the code in various ways for his personal use.

In late 1994, Charles Swiger announced that he was starting a real job and
would no longer be able to be the Angband maintainer. This induced some
amount of uproar in the Angband community (as represented by the Angband
newsgroup), with various people attempting to form "committees" to take
over the maintenance of Angband. Since committees have never given us
anything but trouble (think "COBOL"), there was very little resistance
when, on the first day of 1995, Ben made his code available, calling it
"Angband 2.7.0", and by default, taking over as the new maintainer of
Angband.

Angband 2.7.0 was a very clean (but very buggy) rewrite that, among other
things, allowed extremely simple porting to multiple platforms, starting
with Unix and Macintosh, and by the time most of the bugs were cleaned up,
in Angband 2.7.2, including X11, and various IBM machines. Angband 2.7.4
was released to the "ftp.cis.ksu.edu" site, and quickly gained acceptance,
perhaps helped by the OS2 and Windows and Amiga and Linux ports. Angband
2.7.5 and 2.7.6 added important capabilities such as macros and user pref
files, and continued to clean up the source. Angband 2.7.8 was released to
the major ftp archives as the first "stable" version in a year or so, with
new "help files" and "spoiler files" for the "online help", plus a variety
of minor tweaks and some new features.

After Angband 2.7.8 was released, Ben created a web site to keep track of
all the changes made in each version (though a few may have been missed),
and acquired the use of a new development ftp server to supplement the
official "mirror" server. This web site is now permanently located at the
Official Angband Home Page (http://www.thangorodrim.net/). Unfortunately,
the next six versions were numbered Angband 2.7.9v1 to Angband 2.7.9v6, but
really each were rather major updates. Angband 2.8.0 and 2.8.1 were
released using a more normal version scheme. Angband 2.8.2 and 2.8.3 add a
few random features, clean up some code, and provide graphics support and
such for a few more platforms.

After the release of Angband 2.8.3 Ben's free time was more and more
occupied by his work. He released a beta version of Angband 2.8.5,
introducing many new features, but couldn't give as much attention to
maintaining the game as he wanted to. Meanwhile, an "unofficial" version by
Robert Ruehlmann, incorporating three popular patches (the "Easy Patch" by
Tim Baker, for opening doors and disarming traps without specifying the
direction: Greg Wooledge's "Random Artifacts" patch: and Keldon Jones's
"Optional Monster AI Improvement"), named "2.8.3h", was gaining popularity.

So in March 2000, Robert Ruehlmann offered to take over Angband and started
to fix the remaining bugs in the Angband 2.8.5 beta. The resulting version
was to be released as Angband 2.9.0. Further bugfixes and a couple of new
features - including many in the realms of user-customizability, with
greater control over ego-items, player races and classes, monsters, items
and artifacts - have led to the current version.

And with the greater amount of user-customizability that is now possible,
it was inevitable that SOMEBODY would eventually go and actually do
something with it. Jonathan Ellis started customizing the user-editable
text files in the 'edit' directory for his own personal use - originally,
only by fixing bugs and inconsistencies (less powerful monsters being worth
more experience per kill than more powerful ones, dragons doing a decent
amount of damage in melee, monsters with two claws and one mouth getting
one claw and three bite attacks, and so on).

At first, this was all that could really be done with it: adding new
monsters and items was impossible, as the limits were fixed. And so only
three new monsters made an appearance, each of them replacing an existing
monster in the order: and one new artifact - "The Palantir of Westernesse".
Gameplay balance could be tweaked somewhat, by changing the level, power
and rarity of certain items and monsters: and some changes were made,
mostly with the attempt to reduce the notorious "triple whammy" effect of
needing poison, confusion and nether resistance (or over 550 hps, if
without nether resistance) all at once, straight after passing 2000',
forcing excessive scumming before this depth or risking unavoidable instant
death: and then having nothing left to do but dive straight to 4000' and
scum for speed items, missing out on some of the most interesting depths of
the dungeon. This problem, at least, could be addressed, but actual new
things were less easy to add...

That all changed with Angband 2.9.1, which for the first time moved the
limits themselves to a separate user-editable file, and allowed more
monsters and items to be created without removing the old ones. At the same
time, a patch by Matthias Kurzke was incorporated which allowed the
creation of new ego-items. Various new powers, for the player and monsters,
were added to the game - but no items or monsters yet had these powers
(resist fear, poison brand, lose charisma, summon greater demons, and so
on): indeed, arguably it could be said that the game had not even adjusted
properly to Ben Harrison's fractional speed system (Angband 2.7.0) or the
addition of the other attack forms such as shards, sound, chaos, nexus and
so on (even before Ben.)

The Official Angband Home Page (http://rephial.org/) serves not only as the
most up to date description of Angband, but also lists changes made between
versions, and changes planned for upcoming versions, and lists various
email addresses and web sites related to Angband.

Some of the changes between Angband 2.6.1 and 3.0.6
===================================================

It is very hard to pin down, along the way from 2.6.2 to 3.0.6, exactly
what changes were made, and exactly when they were made. Most releases
involved so many changes from the previous release as to make "diff files"
not very useful, since often the diff files are as long as the code itself.
Most of the changes, with the notable exception of the creation of some of
the new 'main-xxx.c' files for the various new platforms, and a few other
minor exceptions generally noted directly in comments in the source, were
written by Ben or Robert, either spontaneously, or, more commonly, as the
result of a suggestion or comment by an Angband player.

The most important modification was a massive "code level cleanup" for
2.7.x, largely completed in 2.7.8, that made all other modifications much
simpler and safer. This cleanup was so massive that in many places the code
is no longer recognizable, for example, via "diff -r", often because it was
rewritten from scratch.

The second most important modification was the design of a generic
'z-term.c' package, which allows Angband to be ported to a new machine
with as few as 50 lines of code. Angband 2.9.3 thus runs without
modification on many machines, including Macintosh, PowerMac, Unix/X11,
Unix/Curses, Amiga, Windows, OS2-386, DOS-386, and even DOS-286.

It would be difficult to list all of the changes between Angband 2.6.1 and
3.0.6, because many of them were made in passing during the massive code
level cleanup. Many of the changes are invisible to the user, but still
provide increased simplicity and efficiency, and decreased code size, or
make other more visable changes possible. For example, the new
'project()' code that handles all bolts, beams, and balls, the new
'update_view()' code that simplifies line of sight computation, or the
new 'generate()' code that builds new levels in the dungeon. Many changes
have been made to increase efficiency, including the new
'process_monsters()' and 'update_monsters()' functions, and the new
'objdes()' and 'light_spot()' routines. The generic 'z-term.c'
package yielded efficient screen updates, and enabled the efficient use of
color.

The most visible (to ordinary players) changes that happened as a result of 
Ben Harrison's maintainership were:

- a far greater degree of user-customizability as shown by the 'info.txt'
  files 
- the "fractional" speed system, with +10 in the new scheme equalling +1
  in old money 
- object stacking, the ability to have more than one object in a square: 
  first tried in 2.7.9, completed in 2.8.2.

It should also be pointed out at this point that the far cleaner nature of
Ben's code as compared to previous versions has given many other people the
opportunity to base code for their own Angband variants on it. And so a
plethora of new variants have appeared, many of them far more different
from Angband now than Angband ever was from Moria, and yet still based on
Ben's coding ideals for Angband.

For Angband 2.9.0, the first few new visible features were a random
artifact generator (originally developed from a variant by Greg Wooledge),
an option to improve monster AI (believed to have originally started out
life in a patch written by Keldon Jones), and a patch to allow easier
handling of opening and closing doors and disarming traps (by Tim Baker).
For Angband 2.9.1 has also come such things as the ability to increase the
size of the editable text files and thus the number of monsters, artifacts,
items, ego-items and vaults in the game (many new vaults were written by
Chris Weisiger, some by others, and the number of vaults in the game at
this time was doubled), and much greater customizability of ego-items has
become possible thanks to a patch written by Matthias Kurzke. It is also
now possible to add new character races to the game, and to edit the
shopkeepers with respect to their greed, tolerance of haggling and
reactions to the character based on his race. Angband 2.9.2 adds support
for poison branded weapons to the game. Angband 2.9.3 made the character
class itself customizable to an extent.

A Posting from the Original Author
==================================

  | From: koeneke@ionet.net (Robert Alan Koeneke) 
  | Newsgroups: rec.games.roguelike.angband,rec.games.roguelike.moria 
  | Subject: Early history of Moria 
  | Date: Wed, 21 Feb 1996 04:20:51 GMT

  I had some email show up asking about the origin of Moria, and its
  relation to Rogue. So I thought I would just post some text on the early
  days of Moria.

  First of all, yes, I really am the Robert Koeneke who wrote the first
  Moria. I had a lot of mail accussing me of pulling their leg and such. I
  just recently connected to Internet (yes, I work for a company in the
  dark ages where Internet is concerned) and was real surprised to find
  Moria in the news groups... Angband was an even bigger surprise, since I
  have never seen it. I probably spoke to its originator though... I have
  given permission to lots of people through the years to enhance, modify,
  or whatever as long as they freely distributed the results. I have always
  been a proponent of sharing games, not selling them.

  Anyway...

  Around 1980 or 81 I was enrolled in engineering courses at the University
  of Oklahoma. The engineering lab ran on a PDP 1170 under an early version
  of UNIX. I was always good at computers, so it was natural for me to get
  to know the system administrators. They invited me one night to stay and
  play some games, an early startrek game, The Colossal Cave Adventure
  (later just 'Adventure'), and late one night, a new dungeon game called
  'Rogue'.

  So yes, I was exposed to Rogue before Moria was even a gleam in my eye.
  In fact, Rogue was directly responsible for millions of hours of play
  time wasted on Moria and its descendents...

  Soon after playing Rogue (and man, was I HOOKED), I got a job in a
  different department as a student assistant in computers. I worked on one
  of the early VAX 11/780's running VMS, and no games were available for it
  at that time. The engineering lab got a real geek of an administrator who
  thought the only purpose of a computer was WORK! Imagine... Soooo, no
  more games, and no more rogue!

  This was intolerable! So I decided to write my own rogue game, Moria Beta
  1.0. I had three languages available on my VMS system. Fortran IV, PASCAL
  V1.?, and BASIC. Since most of the game was string manipulation, I wrote
  the first attempt at Moria in VMS BASIC, and it looked a LOT like Rogue,
  at least what I could remember of it. Then I began getting ideas of how
  to improve it, how it should work differently, and I pretty much didn't
  touch it for about a year.

  Around 1983, two things happened that caused Moria to be born in its
  recognizable form. I was engaged to be married, and the only cure for
  THAT is to work so hard you can't think about it; and I was enrolled for
  fall to take an operating systems class in PASCAL.

  So, I investigated the new version of VMS PASCAL and found out it had a
  new feature. Variable length strings! Wow...

  That summer I finished Moria 1.0 in VMS PASCAL. I learned more about data
  structures, optimization, and just plain programming that summer then in
  all of my years in school. I soon drew a crowd of devoted Moria
  players... All at OU.

  I asked Jimmey Todd, a good friend of mine, to write a better character
  generator for the game, and so the skills and history were born. Jimmey
  helped out on many of the functions in the game as well. This would have
  been about Moria 2.0

  In the following two years, I listened a lot to my players and kept
  making enhancements to the game to fix problems, to challenge them, and
  to keep them going. If anyone managed to win, I immediately found out
  how, and 'enhanced' the game to make it harder. I once vowed it was
  'unbeatable', and a week later a friend of mine beat it! His character,
  'Iggy', was placed into the game as 'The Evil Iggy', and immortalized...
  And of course, I went in and plugged up the trick he used to win...

  Around 1985 I started sending out source to other universities. Just
  before a OU / Texas football clash, I was asked to send a copy to the
  Univeristy of Texas... I couldn't resist... I modified it so that the
  begger on the town level was 'An OU football fan' and they moved at
  maximum rate. They also multiplied at maximum rate... So the first step
  you took and woke one up, it crossed the floor increasing to hundreds of
  them and pounded you into oblivion... I soon received a call and provided
  instructions on how to 'de-enhance' the game!

  Around 1986 - 87 I released Moria 4.7, my last official release. I was
  working on a Moria 5.0 when I left OU to go to work for American Airlines
  (and yes, I still work there). Moria 5.0 was a complete rewrite, and
  contained many neat enhancements, features, you name it. It had water,
  streams, lakes, pools, with water monsters. It had 'mysterious orbs'
  which could be carried like torches for light but also gave off magical
  aura's (like protection from fire, or aggravate monster...). It had new
  weapons and treasures... I left it with the student assistants at OU to be
  finished, but I guess it soon died on the vine. As far as I know, that
  source was lost...

  I gave permission to anyone who asked to work on the game. Several people
  asked if they could convert it to C, and I said fine as long as a
  complete credit history was maintained, and that it could NEVER be sold,
  only given. So I guess one or more of them succeeded in their efforts to
  rewrite it in C.

  I have since received thousands of letters from all over the world from
  players telling about their exploits, and from administrators cursing the
  day I was born... I received mail from behind the iron curtain (while it
  was still standing) talking about the game on VAX's (which supposedly
  couldn't be there due to export laws). I used to have a map with pins for
  every letter I received, but I gave up on that!

  I am very happy to learn my creation keeps on going... I plan to download
  it and Angband and play them... Maybe something has been added that will
  surprise me! That would be nice... I never got to play Moria and be
  surprised...

  | Robert Alan Koeneke
  | koeneke@ionet.net

Previous Versions (outdated)
============================

VMS Moria Version 4.8
---------------------

===========   ========
Version 0.1   03/25/83
Version 1.0   05/01/84
Version 2.0   07/10/84
Version 3.0   11/20/84
Version 4.0   01/20/85
===========   ========

Modules:

+------+------------------------+-----------+
| V1.0 | Dungeon Generator      | RAK       |
+      +------------------------+-----------+
|      | Character Generator    | RAK & JWT |
+      +------------------------+-----------+
|      | Moria Module           | RAK       |
+      +------------------------+-----------+
|      | Miscellaneous          | RAK & JWT | 
+------+------------------------+-----------+
| V2.0 | Town Level & Misc      | RAK       |
+------+------------------------+-----------+
| V3.0 | Internal Help & Misc   | RAK       |
+------+------------------------+-----------+
| V4.0 | Source Release Version | RAK       |
+------+------------------------+-----------+

===============================   ================================
Robert Alan Koeneke               Jimmey Wayne Todd Jr.
Student/University of Oklahoma    Student/University of Oklahoma
===============================   ================================

Umoria Version 5.2 (formerly UNIX Moria)
----------------------------------------

============ ========
Version 4.83  5/14/87
Version 4.85 10/26/87
Version 4.87  5/27/88
Version 5.0   11/2/89
Version 5.2    5/9/90
============ ========

James E. Wilson, U.C. Berkeley
                 wilson@ernie.Berkeley.EDU
                 ...!ucbvax!ucbernie!wilson

Other contributors:

======================  ==================================================
\D. G. Kneller          MSDOS Moria port
Christopher J. Stuart   recall, options, inventory, and running code
Curtis McCauley         Macintosh Moria port
Stephen A. Jacobs       Atari ST Moria port
William Setzer          object naming code
David J. Grabiner       numerous bug reports, and consistency checking
Dan Bernstein           UNIX hangup signal fix, many bug fixes
and many others...
======================  ==================================================

| Copyright (c) 1989 James E. Wilson, Robert A. Koeneke
| This software may be copied and distributed for educational, research, 
  and not for profit purposes provided that this copyright and statement 
  are included in all such copies.

Early Angband credits
---------------------

Version 2.0
  Alex Cutler, Andy Astrand, Sean Marsh, Geoff Hill, Charles Teague.

Version 2.4
  05/09/1993

Version 2.5
  12/05/1993 Charles Swiger

Version 2.6
  09/04/1994 Charles Swiger

Version 2.7
  01/01/1995 Ben Harrison

Version 2.8
  01/01/1997 Ben Harrison

Version 2.9
  04/10/2000 Robert Ruehlmann

Contributors (incomplete)
=========================

Peter Berger, "Prfnoff", Arcum Dagsson, Ed Cogburn, Matthias Kurzke,
Ben Harrison, Steven Fuerst, Julian Lighton, Andrew Hill, Werner Baer,
Tom Morton, "Cyric the Mad", Chris Kern, Tim Baker, Jurriaan Kalkman,
Alexander Wilkins, Mauro Scarpa, John I'anson-Holton, "facade",
Dennis van Es, Kenneth A. Strom, Wei-Hwa Huang, Nikodemus, Timo Pietilä,
Greg Wooledge, Keldon Jones, Shayne Steele, Dr. Andrew White, Musus Umbra,
Jonathan Ellis
