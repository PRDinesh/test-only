//
// "$Id$"
//
// MacOS font selection routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#include <config.h>

//: MeasureText, FontMetrics, WidthTabHandle, GetSysFont, SysFontSize
//: TextSize, TextFont
//: GetFNum (theName: Str255; VAR familyID: Integer);
//: FUNCTION FMSwapFont (inRec: FMInput): FMOutPtr;
//: SetFractEnable

Fl_FontSize::Fl_FontSize(const char* name, int Size) {
  next = 0;
#  if HAVE_GL
  listbase = 0;
#  endif
#ifdef __APPLE_QD__
  knowMetrics = 0;
  switch (*name++) {
  case 'I': face = italic; break;
  case 'P': face = italic | bold; break;
  case 'B': face = bold; break;
  default: face = 0; break;
  }
  unsigned char fn[80]; 
  fn[0] = strlen(name); strcpy((char*)(fn+1), name);
  GetFNum(fn, &font);
  size = Size;
  FMInput fIn = { font, size, face, 0, 0, { 1, 1}, { 1, 1} };
  FMOutput *fOut = FMSwapFont(&fIn);
  ascent = fOut->ascent;	//: the following three lines give only temporary aproimations
  descent = fOut->descent;
  for (int i=0; i<256; i++) width[i] = fOut->widMax;
  minsize = maxsize = size;
#elif defined(__APPLE_QUARTZ__)
  q_name = strdup(name);
  size = Size;
  ascent = Size*3/4;
  descent = Size-ascent;
  q_width = Size*2/3;
  minsize = maxsize = Size;
  // Using ATS to get the genral Glyph size information
  CFStringRef cfname = CFStringCreateWithCString(0L, q_name, kCFStringEncodingASCII);
  ATSFontRef font = ATSFontFindFromName(cfname, kATSOptionFlagsDefault);
  if (font) {
    ATSFontMetrics m = { 0 };
    ATSFontGetHorizontalMetrics(font, kATSOptionFlagsDefault, &m);
    if (m.avgAdvanceWidth) q_width = int(m.avgAdvanceWidth*size);
    // playing with the offsets a little to make standard sizes fit
    if (m.ascent) ascent  = int(m.ascent*size-0.5f);
    if (m.descent) descent = -int(m.descent*size-1.5f);
  }
  CFRelease(cfname);
#endif
}

Fl_FontSize* fl_fontsize = 0L;

Fl_FontSize::~Fl_FontSize() {
/*
#if HAVE_GL
 // ++ todo: remove OpenGL font alocations
// Delete list created by gl_draw().  This is not done by this code
// as it will link in GL unnecessarily.  There should be some kind
// of "free" routine pointer, or a subclass?
// if (listbase) {
//  int base = font->min_char_or_byte2;
//  int size = font->max_char_or_byte2-base+1;
//  int base = 0; int size = 256;
//  glDeleteLists(listbase+base,size);
// }
#endif
  */
  if (this == fl_fontsize) fl_fontsize = 0;
#ifdef __APPLE_QUARTZ__
  free(q_name);
#endif
}

////////////////////////////////////////////////////////////////

static Fl_Fontdesc built_in_table[] = {
#ifdef __APPLE_QD__
{" Arial"},
{"BArial"},
{"IArial"},
{"PArial"},
{" Courier New"},
{"BCourier New"},
{"ICourier New"},
{"PCourier New"},
{" Times New Roman"},
{"BTimes New Roman"},
{"ITimes New Roman"},
{"PTimes New Roman"},
{" Symbol"},
{" Chicago"},
{"BChicago"},
{" Webdings"},
#elif defined(__APPLE_QUARTZ__)
{"Arial"},
{"Arial Bold"},
{"Arial Italic"},
{"Arial Bold Italic"},
{"Courier New"},
{"Courier New Bold"},
{"Courier New Italic"},
{"Courier New Bold Italic"},
{"Times New Roman"},
{"Times New Roman Bold"},
{"Times New Roman Italic"},
{"Times New Roman Bold Italic"},
{"Symbol"},
{"Monaco"},
{"Andale Mono"}, // there is no bold Monaco font on standard Mac
{"Webdings"},
#endif
};

Fl_Fontdesc* fl_fonts = built_in_table;

void fl_font(Fl_FontSize* s) {
  fl_fontsize = s;
#ifdef __APPLE_QD__
  if (fl_window) SetPort( GetWindowPort(fl_window) );
  TextFont(fl_fontsize->font);	//: select font into current QuickDraw GC
  TextFace(fl_fontsize->face);
  TextSize(fl_fontsize->size);
  if (!fl_fontsize->knowMetrics) {	//: get the true metrics for the currnet GC 
                                        //: (fails on multiple monitors with different dpi's!)
    FontInfo fi; GetFontInfo(&fi);
    fl_fontsize->ascent = fi.ascent;
    fl_fontsize->descent = fi.descent;
    FMetricRec mr; FontMetrics(&mr);
    short *f = (short*)*mr.wTabHandle; //: get the char size table
    for (int i=0; i<256; i++) fl_fontsize->width[i] = f[2*i];
    fl_fontsize->knowMetrics = 1;
  }
#elif defined(__APPLE_QUARTZ__)
  if (!s) return;
  if (!fl_gc) return; // no worries, we will assign the font to the context later
  CGContextSelectFont(fl_gc, s->q_name, (float)s->size, kCGEncodingMacRoman);
#else
# error : need to defined either Quartz or Quickdraw
#endif
}

static Fl_FontSize* find(int fnum, int size) {
  Fl_Fontdesc* s = fl_fonts+fnum;
  if (!s->name) s = fl_fonts; // use 0 if fnum undefined
  Fl_FontSize* f;
  for (f = s->first; f; f = f->next)
    if (f->minsize <= size && f->maxsize >= size) return f;
  f = new Fl_FontSize(s->name, size);
  f->next = s->first;
  s->first = f;
  return f;
}

////////////////////////////////////////////////////////////////
// Public interface:

int fl_font_ = 0;
int fl_size_ = 0;

void fl_font(int fnum, int size) {
  fl_font_ = fnum;
  fl_size_ = size;
  fl_font(find(fnum, size));
}

int fl_height() {
  if (fl_fontsize) return fl_fontsize->ascent+fl_fontsize->descent;
  else return -1;
}

int fl_descent() {
  if (fl_fontsize) return fl_fontsize->descent;
  else return -1;
}

double fl_width(const char* txt, int n) {
#ifdef __APPLE_QD__
  return (double)TextWidth( txt, 0, n );
#else
  if (!fl_gc) {
    Fl_Window *w = Fl::first_window();
    if (w) w->make_current();
    if (!fl_gc) return -1;
  }
  // according to the Apple developer docs, this is the correct way to
  // find the length of a rendered text...
  CGContextSetTextPosition(fl_gc, 0, 0);
  CGContextSetTextDrawingMode(fl_gc, kCGTextInvisible);
  CGContextShowText(fl_gc, txt, n);
  CGContextSetTextDrawingMode(fl_gc, kCGTextFill);
  CGPoint p = CGContextGetTextPosition(fl_gc);
  return p.x;
#endif
}

double fl_width(uchar c) {
  return fl_width((const char*)(&c), 1);
}

void fl_draw(const char *str, int n, float x, float y);

void fl_draw(const char* str, int n, int x, int y) {
#ifdef __APPLE_QD__
  MoveTo(x, y);
  DrawText((const char *)str, 0, n);
#elif defined(__APPLE_QUARTZ__)
  fl_draw(str, n, (float)x, (float)y);
#else
#  error : neither Quartz no Quickdraw chosen
#endif
}

void fl_draw(const char *str, int n, float x, float y) {
#ifdef __APPLE_QD__
  fl_draw(str, n, (int)x, (int)y);
#elif defined(__APPLE_QUARTZ__)
  CGContextShowTextAtPoint(fl_gc, x, y, str, n);
#else
#  error : neither Quartz no Quickdraw chosen
#endif
}

//
// End of "$Id$".
//
