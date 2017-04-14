#include "svg.h"

void SVG_debut(FILE* fichier)
{
    fprintf (fichier,   "<?xml version=\"1.0\" standalone=\"no\"?>\n\n"
                        "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n\n"
                        "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n\n"
                        "<svg xmlns=\"http://www.w3.org/2000/svg\"\n\n"
                        "width=\"%d\" height=\"%d\">\n\n"
                        "<title>DDP-01.03 by Kefka1988</title>\n\n"
                        ,SVG_WIN_W , SVG_WIN_H);
}
void SVG_fin(FILE* fichier)
{
    fprintf (fichier, "</svg>");
}
void SVG_rect(FILE* fichier, int pos_x, int pos_y, int size_x, int size_y)
{
    fprintf(fichier, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\"\n", SVG_BORDER_X + pos_x, pos_y, size_x, size_y);
    fprintf(fichier, "style=\" fill:%s; stroke:%s\" />\n\n", SVG_BAR_COLOR, SVG_BAR_STROKE);
}
void SVG_background(FILE* fichier)
{
    fprintf(fichier, "<rect   x=\"0\" y=\"0\" width=\"%d\" height=\"%d\"\n", SVG_WIN_W, SVG_WIN_H);
    fprintf(fichier, "style=\" fill:%s; \" />\n\n", SVG_BG_COLOR);
}
void SVG_date(FILE* fichier, int pos_x, int pos_y, int mois, int jour)
{
    fprintf(fichier, "<text x=\"%d\" y=\"%d\"\n", SVG_BORDER_X + (SVG_BAR_W / 2) + pos_x, pos_y + (SVG_BAR_W / 3));
    fprintf(fichier, "style=\"font-size:%dpx;text-anchor:middle;\">%02d/%02d</text>\n\n", SVG_TXT_SIZE, mois, jour);
}
void SVG_freq(FILE* fichier, int pos_x, int pos_y, double freq)
{
    fprintf(fichier, "<text x=\"%d\" y=\"%d\"\n", SVG_BORDER_X + (SVG_BAR_W / 2) + pos_x, pos_y - (SVG_BAR_W / 3));
    fprintf(fichier, "style=\"font-size:%dpx;text-anchor:middle;\">%.2f%%</text>\n\n", SVG_TXT_SIZE2, freq);
}
void SVG_txt_horizontal(FILE* fichier, int pos_x, int pos_y, char* txt, int taille_txt)
{
    fprintf(fichier, "<text x=\"%d\" y=\"%d\"\n", pos_x, pos_y);
    fprintf(fichier, "style=\"font-size:%dpx;text-anchor:middle;\">%s</text>\n\n", taille_txt, txt);
}
void SVG_txt_vertical(FILE* fichier, int pos_x, int pos_y, char* txt, int taille_txt)
{
    fprintf(fichier, "<text transform='rotate(-90)' x=\"%d\" y=\"%d\"\n", pos_x, pos_y);
    fprintf(fichier, "style=\"font-size:%dpx;text-anchor:middle;\">%s</text>\n\n", taille_txt, txt);
}
