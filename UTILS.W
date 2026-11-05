@* Palette Utilities.  These routines provide color interpolation, palette
interpolation, and palette fade in/fade out services.

@ This routine does a linear interpolation between |target| and |*color|,
interpreted as Genesis color values.  It determines a color at
point $time/duration$ between them.  It does not check that $time \le
duration$, nor does it verify that $duration > 0$.@^Unsafe behavior@>

@c
void InterpolateColor(short target, short time, short duration, short *color){
short dr, dg, db;
short tr, tg, tb;
short r, g, b;
int i;

    r = *color & 0x00e;
    g = (*color & 0x0e0) >> 4;
    b = (*color & 0xe00) >> 8;
    tr = target & 0x00e;
    tg = (target & 0x0e0) >> 4;
    tb = (target & 0xe00) >> 8;
    dr = r - tr + 1;
    dg = g - tg + 1;
    db = b - tb + 1;
    r = tr + (dr * time) / duration;
    g = tg + (dg * time) / duration;
    b = tb + (db * time) / duration;
    *color = (r & 0x00e) | ((g & 0x00e) << 4) | ((b & 0x00e) << 8);
}

@ This routine uses |InterpolateColor| to interpolate a full palette toward a
given color.

@c
void InterpolatePalette(short target, short time, short duration, short *palette){
int i;

    for(i = 0; i < 16; i++){
        InterpolateColor(target, time, duration, &palette[i]);
    }
}

@ This routine uses |InterpolateColor| to interpolate four full palettes toward
a given color.

@c
void InterpolateFullPalette(short target, short time, short duration, short* palette){
int i;

    for(i = 0; i < 64; i++){
        InterpolateColor(target, time, duration, &palette[i]);
    }
}

@ This routine uses |InterpolateColor| to interpolate a full palette
toward a given palette.

@c
void Interpolate2Palettes(short *target, short time, short duration, short *palette){
int i;

    for(i = 0; i < 16; i++){
        InterpolateColor(target[i], time, duration, &palette[i]);
    }
}

@ This routine uses |InterpolateColor| to interpolate four full palettes toward
a given set of palettes.

@c
void Interpolate2FullPalettes(short *target, short time, short duration, short *palette){
int i;

    for(i = 0; i < 64; i++){
        InterpolateColor(target[i], time, duration, &palette[i]);
    }
}

@ This routine fades the screen from black to the given palette set in |time|
frames.

@c
void FadeIn(short *palette, short time){
int i, j;
short workpal[64];

    for(i = 1; i <= time; i++){
        for(j = 0; j < 64; j++){
            workpal[j] = palette[j];
        }
        InterpolateFullPalette(0, i, time, workpal);
        SendPalettes(workpal);
        WaitTOF();
    }
}

@ This routine fades the screen from the given palette set to black in |time|
frames.

@c
void FadeOut(short *palette, short time){
int i, j;
short workpal[64];

    for(i = time-1; i >= 0; i--){
        for(j = 0; j < 64; j++){
            workpal[j] = palette[j];
        }
        InterpolateFullPalette(0, i, time, &workpal);
        SendPalettes(workpal);
        WaitTOF();
    }
}

@ @<Function prototypes@>=
void InterpolateColor
             (short target, short time, short duration, short *color);@#
void InterpolatePalette
             (short target, short time, short duration, short *palette);@#
void InterpolateFullPalette
             (short target, short time, short duration, short *palette);@#
void Interpolate2Palettes
             (short *target, short time, short duration, short *palette);@#
void Interpolate2FullPalettes
             (short *target, short time, short duration, short *palette);@#

void FadeIn(short *palette, short time);@#
void FadeOut(short *palette, short time);@#
