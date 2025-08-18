#pragma once

#include <set>
#include "png_image.h"

using namespace std;

//Functor to compare entries in SetPal
struct CmpIntColor {
    // Values accessed as bytes here will be in ABGR8 byte array format. This is
    // due to RGBA:32 packed ints being accessed as bytes on what is assumed to
    // be a little-endian system.
    // So, [3] = Red ... [0] = Alpha

    bool operator() (unsigned int const& c1, unsigned int const& c2) const
    {
        unsigned char* c1_ptr = (unsigned char*)&c1;
        unsigned char* c2_ptr = (unsigned char*)&c2;

        //Compare alpha first, transparent color is considered smaller
        if(c1_ptr[ABGR8_ALPHA] != c2_ptr[ABGR8_ALPHA])
        {
            return c1_ptr[ABGR8_ALPHA] < c2_ptr[ABGR8_ALPHA];
        }
        else
        {
            // If a color is fully transparent then consider it identical to any other
            // fully transparent color and do not insert.
            // If this test is reached then alpha channels are identical for the two entries
            // and entry c1 is the one being tested for insertion.
            if (c1_ptr[ABGR8_ALPHA] == ALPHA_FULLY_TRANSPARENT) return false;

            // Do a compare with luminance in upper bits, and original rgb24 in lower bits. 
            // This prefers luminance, but considers RGB values for equal-luminance cases to
            // make sure the compare functor satisifed the strictly weak ordering requirement
            uint64_t lum_1 = (unsigned int)(c1_ptr[ABGR8_R] * 299 + c1_ptr[ABGR8_G] * 587 + c1_ptr[ABGR8_B] * 114);
            uint64_t lum_2 = (unsigned int)(c2_ptr[ABGR8_R] * 299 + c2_ptr[ABGR8_G] * 587 + c2_ptr[ABGR8_B] * 114);
            uint64_t rgb_1 = RGB24(c1_ptr[ABGR8_R], c1_ptr[ABGR8_G], c1_ptr[ABGR8_B]);
            uint64_t rgb_2 = RGB24(c2_ptr[ABGR8_R], c2_ptr[ABGR8_G], c2_ptr[ABGR8_B]);
            uint64_t all_1 = (lum_1 << 24) | rgb_1;
            uint64_t all_2 = (lum_2 << 24) | rgb_2;
            return all_1 > all_2;
        }
    }
};

//This set will keep colors in the palette ordered based on their grayscale values to ensure they look good on DMG
//This assumes the palette used in DMG will be 00 01 10 11
typedef set< unsigned int, CmpIntColor > SetPal;


SetPal GetPaletteColors(const PNGImage& image, bool packModeSGB, int x, int y, int w, int h);
