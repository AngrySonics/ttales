% This file is part of Treasure Tales
% This program by Ken Rose

% Copyright (C) 1993 Sega
% All rights reserved

% Here is TeX material that gets inserted after \input webmac
\font\headerfont=cmr9 scaled\magstep1
\def\hang{\hangindent 3em\indent\ignorespaces}
\def\Pascal{Pascal}
\def\pb{$\.|\ldots\.|$} % C brackets (|...|)
\def\v{\char'174} % vertical (|) in typewriter font
\def\dleft{[\![} \def\dright{]\!]} % double brackets
\mathchardef\RA="3221 % right arrow
\mathchardef\BA="3224 % double arrow
\def\({} % kludge for alphabetizing certain section names

\def\Title{Treasure Tales}
\def\TT{{\sl\Title}}

\def\title{\Title}
\def\topofcontents{\null\vfill
  \centerline{\headerfont{Sega Technical Institute}}
  \vskip 15pt
  \centerline{presents}
  \vskip 15pt
  \centerline{\titlefont\Title}
  \centerline{starring Miles ``Tails'' Prower}
  \vskip 15pt
  \centerline{\eightrm{Game Design by}}
  \centerline{Hoyt Ng}
  \centerline{Tsuneko Aoki}
  \vskip 15pt
  \centerline{\eightrm{Programming by}}
  \centerline{Ken Rose}
  \centerline{Earl Stratton}
  \vskip 15pt
  \centerline{\eightrm{Graphic Art by}}
  \centerline{Craig Stitt}
  \vskip 15pt
  \centerline{\eightrm{Produced by}}
  \centerline{Yutaka Sugano}
  \vfill}
\def\botofcontents{\vfill
\noindent
\centerline{Copyright \copyright\ 1993 Sega}
}
\pageno=\contentspagenumber \advance\pageno by 1
\let\maybe=\iftrue
\datethis

@i ttmain.w
@i mmgr.w
@i ttworld.w
@i fsm.w
@i io.w
@i startup.w
@i utils.w
@i expand.w
@i path.w
@i player.w
@i squares.w
@i anim.w
@i art.w
@i display.w

@* Index.
