#include "font.h"

void font_list(void)
{
    FcConfig* conf = FcInitLoadConfigAndFonts();
    FcPattern* pattern = FcPatternCreate();
    FcObjectSet* object_set =
        FcObjectSetBuild(FC_FAMILY, FC_STYLE, FC_LANG, FC_FILE, (char*)0);
    FcFontSet* font_set = FcFontList(conf, pattern, object_set);

    if (!font_set)
    {
        fprintf(stderr, "Failed to list fonts\n");
        return;
    }

    printf("Number of fonts: %d\n", font_set->nfont);
    for (int i = 0; i < font_set->nfont; ++i)
    {
        FcPattern* font = font_set->fonts[i];
        FcChar8 *file, *style, *family;
        if (FcPatternGetString(font, FC_FILE, 0, &file) == FcResultMatch &&
            FcPatternGetString(font, FC_STYLE, 0, &style) == FcResultMatch &&
            FcPatternGetString(font, FC_FAMILY, 0, &family) == FcResultMatch)
            printf("%s (%s, %s)\n", file, family, style);
        {
        }
    }

    FcFontSetDestroy(font_set);
}
