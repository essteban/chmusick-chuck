/*----------------------------------------------------------------------------
    ChucK Concurrent, On-the-fly Audio Programming Language
      Compiler and Virtual Machine

    Copyright (c) 2004 Ge Wang and Perry R. Cook.  All rights reserved.
      http://chuck.cs.princeton.edu/
      http://soundlab.cs.princeton.edu/

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
    U.S.A.
-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// name: util_math.c
// desc: ...
//
// author: Ge Wang (gewang@cs.princeton.edu)
//         Perry R. Cook (prc@cs.princeton.edu)
//         Philip Davidson (philipd@alumni.princeton.edu)
// date: Spring 2004
//-----------------------------------------------------------------------------
#include "util_math.h"
#include <math.h>

// windows / visual c++
#ifdef __PLATFORM_WIN32__

//-----------------------------------------------------------------------------
// name: round()
// desc: ...
//-----------------------------------------------------------------------------
double round( double a )
{
    if( a >= 0 ) return (double)(long)( a + .5 );
    else return (double)(long)( a - .5 );
}


//-----------------------------------------------------------------------------
// name: trunc()
// desc: ...
//-----------------------------------------------------------------------------
double trunc( double a )
{
    return (double)(long)a;
}


//-----------------------------------------------------------------------------
// name: remainder()
// desc: ...
//-----------------------------------------------------------------------------
double remainder( long a, long b )
{
    long div = a/b;
    return a - b*div;
}


#endif

//-----------------------------------------------------------------------------
// name: mtos()
// desc: midi to string note
// author: Esteban Betancur (essteb@gmail.com)
//-----------------------------------------------------------------------------

char mtos( int f )
{
    int modul;
    char str;
    for(int i = 12; i > 0; i--)
    {
        if(f % i == 0)
            modul = i;
    }
    switch (modul) {
        case 12:
            str = "C";
            break;
        case 11:
            str = "B";
            break;
        case 10:
            str = "Bb/A#";
            break;
        case 9:
            str = "A";
            break;
        case 8:
            str = "Ab/G#";
            break;
        case 7:
            str = "G";
            break;
        case 6:
            str = "Gb/F#";
            break;
        case 5:
            str = "F";
            break;
        case 4:
            str = "E";
            break;
        case 3:
            str = "Eb/D#";
            break;
        case 2:
            str = "D";
            break;
        case 1:
            str = "Db/C#";
            break;
    }
    return str;
}
//-----------------------------------------------------------------------------
// name: ftos()
// desc: frecuency to string note
//-----------------------------------------------------------------------------
char ftos( double f )
{
    int num = ftom(f);
    return mtos(num);
}

// the following 6 functions are
// lifted from  PD source
// specifically x_acoustics.c
// http://puredata.info/downloads
#define LOGTWO 0.69314718055994528623
#define LOGTEN 2.302585092994

//-----------------------------------------------------------------------------
// name: mtof()
// desc: midi to freq
//-----------------------------------------------------------------------------
double mtof( double f )
{
    if( f <= -1500 ) return (0);
    else if( f > 1499 ) return (mtof(1499));
    // else return (8.17579891564 * exp(.0577622650 * f));
    // TODO: optimize
    else return ( pow(2,(f-69)/12.0) * 440.0 );
}


//-----------------------------------------------------------------------------
// name: ftom()
// desc: freq to midi
//-----------------------------------------------------------------------------
double ftom( double f )
{   
    // return (f > 0 ? 17.3123405046 * log(.12231220585 * f) : -1500);
    // TODO: optimize
    return (f > 0 ? (log(f/440.0) / LOGTWO) * 12.0 + 69 : -1500);
}


//-----------------------------------------------------------------------------
// name: powtodb()
// desc: ...
//-----------------------------------------------------------------------------
double powtodb( double f )
{
    if( f <= 0 ) return (0);
    else
    {
        double val = 100 + 10./LOGTEN * log(f);
        return (val < 0 ? 0 : val);
    }
}


//-----------------------------------------------------------------------------
// name: rmstodb()
// desc: ...
//-----------------------------------------------------------------------------
double rmstodb( double f )
{
    if( f <= 0 ) return (0);
    else
    {
        double val = 100 + 20./LOGTEN * log(f);
        return (val < 0 ? 0 : val);
    }
}


//-----------------------------------------------------------------------------
// name: dbtopow()
// desc: ...
//-----------------------------------------------------------------------------
double dbtopow( double f )
{
    if( f <= 0 )
        return (0);
    else
    {
        if( f > 870 ) f = 870;
        return (exp((LOGTEN * 0.1) * (f-100.)));
    }
}


//-----------------------------------------------------------------------------
// name: dbtorms()
// desc: ...
//-----------------------------------------------------------------------------
double dbtorms( double f )
{
    if( f <= 0 )
        return (0);
    else
    {
        if( f > 485 ) f = 485;
        return (exp((LOGTEN * 0.05) * (f-100.)));
    }
}




//-----------------------------------------------------------------------------
// name: nextpow2()
// desc: ...
//-----------------------------------------------------------------------------
unsigned long nextpow2( unsigned long n )
{
    unsigned long nn = n;
    for( ; n &= n-1; nn = n );
    return nn * 2;
}




//-----------------------------------------------------------------------------
// name: ensurepow2()
// desc: ...
//-----------------------------------------------------------------------------
unsigned long ensurepow2( unsigned long n )
{
    return nextpow2( n-1 );
}
