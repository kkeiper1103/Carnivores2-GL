//
// Created by kkeiper on 4/21/2022.
//

#ifndef OPEN_CAR2_NUKLEAR_H
#define OPEN_CAR2_NUKLEAR_H

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include <nuklear/nuklear.h>
#include <nuklear/nuklear_sdl_gl3.h>

extern nk_context* nkCtx;
extern nk_font_atlas* nkFontAtlas;

#endif //OPEN_CAR2_NUKLEAR_H
