#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <set>
#include <stdio.h>
#include <fstream>
#include <cstdint>

#include "lodepng.h"
#include "mttile.h"

#include "cmp_int_color.h"

using namespace std;

#include "png2asset.h"
#include "png_image.h"
#include "image_utils.h"

SetPal GetPaletteColors(const PNGImage& image, bool isPackModeSGB, int x, int y, int w, int h)
{
    SetPal ret;

    // If this is SGB mode then every 16 color palette must have a
    // transparent color as the first entry.
    //
    // For most SGB Borders the Game Boy screen region is transparent and those
    // tiles will all be uniform and therefore using only the first palette where
    // they already have a transparent entry. Which means any additional SGB palettes
    // will lack the needed transparent entry at their start.
    //
    // The solution is to automatically insert a transparent color to every palette
    // created for an SGB tile. If another transparent entry is present then they
    // will get automatically merged (regardless of RGB value *fully* transparent
    // colors are now considered identical. see the CmpIntColor functor for details).
    //
    // The use of RGB(255,255,255) (0xFFFFFF) for the color is due to colors being sorted
    // light to dark, and historical use of transparent white in existing examples.
    if (isPackModeSGB) {
        ret.insert( RGBA32_TRANSPARENT_WHITE );
    }

    // Now scan the tile for colors
    for(int j = y; j < (y + h); ++j)
    {
        for(int i = x; i < (x + w); ++i)
        {
            const unsigned char* color = &image.data[(j * image.w + i) * RGBA32_SZ];
            int color_int = RGBA32(color[RGBA8_R], color[RGBA8_G], color[RGBA8_B], color[RGBA8_ALPHA]);
            ret.insert(color_int);
        }
    }

    for(SetPal::iterator it = ret.begin(); it != ret.end(); ++it)
    {
        if(it != ret.begin() && ((0xFF & *it) != 0xFF)) //ret.begin() should be the only one transparent
            printf("Warning: found more than one transparent color in tile at x:%d, y:%d of size w:%d, h:%d\n", x, y, w, h);
    }

    return ret;
}