//
// "$Id: Fl_Guess_Image.cxx,v 1.8 2002/12/09 04:52:23 spitzak Exp $"
//
// Guessing image type code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

// Draw an image that is stored compressed in a file or in memory. 
// Keep uncompressed images in memory for later use. 

#include <config.h>
#include <fltk/draw.h>
#include <fltk/SharedImage.h>
#include <fltk/xbmImage.h>
//#include <fltk/xpmImage.h>
#include <fltk/x.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace fltk;

// Bitmap used when we couldn't guess the filetype
#define nosuch_width 16
#define nosuch_height 16
static unsigned char nosuch_bits[] = {
   0xff, 0xf0, 0x81, 0x88, 0xd5, 0x90, 0x69, 0xa8, 0x55, 0x94, 0x69, 0xaa,
   0x55, 0x94, 0x69, 0xaa, 0xd5, 0x94, 0xa9, 0xa8, 0x55, 0x95, 0xa9, 0xa9,
   0x55, 0x95, 0xa9, 0xab, 0x01, 0x81, 0xff, 0xff};

FL_IMAGES_API xbmImage nosuch_bitmap(nosuch_bits, nosuch_width, nosuch_height);

ImageType fltk::image_filetypes[] = {
  //  { "xpm", xpmImage::test, xpmImage::get},
  { "gif", gifImage::test, gifImage::get},
  { "png", pngImage::test, pngImage::get},
  { "bmp", bmpImage::test, bmpImage::get},
  { "jpeg",jpegImage::test, jpegImage::get},
  { 0, 0, 0}
};

FL_IMAGES_API ImageType* SharedImage::guess(const char* name, const uchar* datas)
{
  uchar* read_data = 0;
  const uchar* test_data = datas;
  size_t size = 1024;
  if (!datas) {
    FILE* fp = fopen(get_filename(name), "rb");
    if (!fp)
      return image_filetypes + 
	sizeof(image_filetypes)/sizeof(image_filetypes[0]) - 1;
    test_data = read_data = new uchar[1025];
    read_data[1024] = 0; // null-terminate so strstr() works
    size = fread(read_data, 1, size, fp);
    fclose(fp);
  }
  ImageType* ft;
  for (ft=image_filetypes; ft->name; ft++)
    if (ft->test(test_data, size)) break;
  delete[] read_data;
  return ft;
}

//
// End of "$Id: Fl_Guess_Image.cxx,v 1.8 2002/12/09 04:52:23 spitzak Exp $"
//
