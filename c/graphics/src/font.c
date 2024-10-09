#include "font.h"

#include <fontconfig/fontconfig.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdio.h>
#include <stdlib.h>

void font_get_path(char **path)
{
    FcConfig *conf = NULL;
    FcPattern *pat = NULL;
    FcPattern *match = NULL;
    FcChar8 *fontfile = NULL;
    FcResult result;

    *path = NULL;

    conf = FcInitLoadConfigAndFonts();
    if (!conf)
    {
        printf("Failed to load fonts\n");
        goto cleanup;
    }

    pat = FcPatternBuild(0, FC_LANG, FcTypeString, "ja", (char *)0);
    if (!pat)
    {
        printf("Failed to create font pattern\n");
        goto cleanup;
    }

    if (FcConfigSubstitute(conf, pat, FcMatchPattern) == FcFalse)
    {
        printf("Failed to substitute pattern\n");
        goto cleanup;
    }

    FcDefaultSubstitute(pat);

    match = FcFontMatch(conf, pat, &result);
    if (!match)
    {
        printf("Failed to match font\n");
        goto cleanup;
    }

    if (FcPatternGetString(match, FC_FILE, 0, &fontfile) != FcResultMatch)
    {
        printf("Failed to get pattern string\n");
        goto cleanup;
    }

    *path = (char *)FcStrCopy(fontfile);

cleanup:
    if (match)
        FcPatternDestroy(match);
    if (pat)
        FcPatternDestroy(pat);
    if (conf)
        FcConfigDestroy(conf);
}
