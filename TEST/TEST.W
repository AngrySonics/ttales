% This file is part of Treasure Tales
% This program by Ken Rose

% Copyright (C) 1993 Sega
% All rights reserved

% Here is TeX material that gets inserted after \input webmac
\def\pb{$\.|\ldots\.|$} % C brackets (|...|)
\def\v{\char'174} % vertical (|) in typewriter font
\def\dleft{[\![} \def\dright{]\!]} % double brackets
\mathchardef\RA="3221 % right arrow
\mathchardef\BA="3224 % double arrow
\def\({} % kludge for alphabetizing certain section names

@* Treasure Tales Puzzle test program.
@c
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graph.h>
#define PutCursor(a, b) _settextposition(b, a)
main(int argc, char *argv[]){
@<Variables@>
  @<Program Initialization@>
  while(1){
    @<Check and eliminate groups@>
    if(firsttime){
        firsttime = 0;
        score = 0;
    }
    @<Get a legal keypress@>
  }
}

@ @<Variables@>=
unsigned char board[32][32];
int xsize;
int ysize;
int void_x;
int void_y;
int in;
unsigned int seed;
int firsttime = 1;
int score = 0;

@ @<Program Initialization@>=
{
  int i, j;
  if(argc != 3){
    printf("\ntest <width> <height>\n\n");
    exit(1);
  }
  xsize = atoi(argv[1]);
  ysize = atoi(argv[2]);
  if(xsize > 32) xsize = 32;
  if(ysize > 32) ysize = 32;
  for(i = 0; i < 100;i++) printf("\n");
  for(i = 0; i < ysize; i++){
      for(j = 0; j < xsize; j++){
          @<Randomizer@>
          board[j][i] = (7 & (seed >> 13)) + 1;
          PutCursor(j+1, i+1);
          _settextcolor((short)board[j][i]);
          putch('A'-1+board[j][i]);
      }
  }
  do{
      @<Randomizer@>
      void_x = 31 & (seed >> 11);
  }while(void_x >= xsize);
  do{
      @<Randomizer@>
      void_y = 31 & (seed >> 11);
  }while(void_y >= ysize);
  board[void_x][void_y] = 0;
  PutCursor(void_x+1, void_y+1);
  _settextcolor((short)board[void_x][void_y]);
  putch(' ');
  PutCursor(void_x+1, void_y+1);
}

@ @<Randomizer@>=
{seed=seed*521+40001;}

@ @<Get a legal keypress@>=
{
int done = 0;
  do{
    switch(in = getch()){
      case 'i':
        if(void_y == 0) break;
        board[void_x][void_y] = board[void_x][void_y-1];
        board[void_x][void_y-1] = 0;
        PutCursor(void_x+1, void_y+1);
        _settextcolor((short)board[void_x][void_y]);
        putch('A'-1+board[void_x][void_y]);
        PutCursor(void_x+1, void_y-1+1);
        _settextcolor((short)board[void_x][void_y-1]);
        putch(' ');
        PutCursor(void_x+1, void_y-1+1);
        void_y--;
        done = 1;
        break;
      case 'j':
        if(void_x == 0) break;
        board[void_x][void_y] = board[void_x-1][void_y];
        board[void_x-1][void_y] = 0;
        PutCursor(void_x+1, void_y+1);
        _settextcolor((short)board[void_x][void_y]);
        putch('A'-1+board[void_x][void_y]);
        PutCursor(void_x-1+1, void_y+1);
        _settextcolor((short)board[void_x-1][void_y]);
        putch(' ');
        PutCursor(void_x-1+1, void_y-1+1);
        void_x--;
        done = 1;
        break;
      case 'l':
        if(void_x == xsize-1) break;
        board[void_x][void_y] = board[void_x+1][void_y];
        board[void_x+1][void_y] = 0;
        PutCursor(void_x+1, void_y+1);
        _settextcolor((short)board[void_x][void_y]);
        putch('A'-1+board[void_x][void_y]);
        PutCursor(void_x+1+1, void_y+1);
        _settextcolor((short)board[void_x+1][void_y]);
        putch(' ');
        PutCursor(void_x+1, void_y+1);
        void_x++;
        done = 1;
        break;
      case 'm':
      case 'k':
        if(void_y == ysize-1) break;
        board[void_x][void_y] = board[void_x][void_y+1];
        board[void_x][void_y+1] = 0;
        PutCursor(void_x+1, void_y+1);
        _settextcolor((short)board[void_x][void_y]);
        putch('A'-1+board[void_x][void_y]);
        PutCursor(void_x+1, void_y+1+1);
        _settextcolor((short)board[void_x][void_y+1]);
        putch(' ');
        PutCursor(void_x+1, void_y+1+1);
        void_y++;
        done = 1;
        break;
      case 'q':
        for(done = 0; done < 100; done++) printf("\n");
        exit(0);

      default:
        break;
    }
  }while(!done);
}

@ This is the heart of the gameplay, separating this puzzle from the ones we
played with in grade school.  In this version we will eliminate only
rectangular groups, as edge-connected groups are a pain to identify correctly.
Groups of four or more squares of the same color are eliminated from the
playfield.  The squares above them drop down (the void retains its position)
and the empty area is filled with random stuff.  Then we scan the whole thing
again until there are no more groups removed.

@<Check and eliminate groups@>=
{
int x, y, color, xcount, ycount;
int a, b, c;

  for(y = 0; y < ysize; y++){
    for(x = 0; x < xsize; x++){
      color = board[x][y];
      if((board[x][y+1] == color) &&
          (board[x][y+2] == color) &&
           (board[x+1][y+0] == color) &&
            (board[x+1][y+1] == color) &&
             (board[x+1][y+2] == color)){
        for(a = 0; a < 2; a++){
          for(c = 0; c < 3; c++){
            for(b = y-1+c; b >= 0; b--){
              board[x+a][b+1] = board[x+a][b];
              PutCursor(x+a+1, b+1+1);
              _settextcolor((short)board[x+a][b+1]);
              putch('A'-1+board[x+a][b+1]);
            }
            @<Randomizer@>
            board[x+a][0] = (7 & (seed >> 13)) + 1;
            PutCursor(x+a+1, 1);
            _settextcolor((short)board[x+a][0]);
            putch('A'-1+board[x+a][0]);
            @<Try to move the cursor's column down@>
          }
        }
        x = xsize;
        y = -1;
      }
      if((board[x][y+1] == color) &&
          (board[x+1][y+0] == color) &&
           (board[x+1][y+1] == color) &&
            (board[x+2][y+0] == color) &&
             (board[x+2][y+1] == color)){
        for(a = 0; a < 3; a++){
          for(c = 0; c < 2; c++){
            for(b = y-1+c; b >= 0; b--){
              board[x+a][b+1] = board[x+a][b];
              PutCursor(x+a+1, b+1+1);
              _settextcolor((short)board[x+a][b+1]);
              putch('A'-1+board[x+a][b+1]);
            }
            @<Randomizer@>
            board[x+a][0] = (7 & (seed >> 13)) + 1;
            PutCursor(x+a+1, 1);
            _settextcolor((short)board[x+a][0]);
            putch('A'-1+board[x+a][0]);
            @<Try to move the cursor's column down@>
          }
        }
        x = xsize;
        y = -1;
      }
    }
  }
  PutCursor(void_x+1, void_y+1);
}

@ @<Try to move...@>=
if((x+a == void_x) && (y > void_y)){
  board[x+a][y] = board[x+a][y-1];
  PutCursor(x+a+1, y+1);
  _settextcolor((short)board[x+a][y]);
  putch('A'-1+board[x+a][y]);
  board[void_x][void_y] = 0;
  PutCursor(void_x+1, void_y+1);
  _settextcolor((short)board[void_x][void_y]);
  putch(' ');
}
