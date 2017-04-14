#ifndef SVGUTIL_H
#define SVGUTIL_H

#include "llist.h"
#include "error.h"

#define BUFFERSIZE 2000

typedef Node Svg_t;
typedef Svg_t SvgContainer;
typedef Svg_t SvgElement;
typedef SvgElement SvgLine;
typedef SvgElement SvgRect;
typedef SvgElement SvgText;
typedef unsigned int uint;

enum
{
    RED = 0xFF0000,
    GREEN = 0x00FF00,
    BLUE = 0x0000FF,
    BLACK = 0x000000,
    WHITE = 0xFFFFFF,
    YELLOW = 0xFFFF00,
    MAGENTA = 0xFF00FF,
    CYAN = 0x00FFFF,
    TRANSPARENT = 0x1000000
};

typedef struct
{
    uint color;
    int width;
} Stroke;

typedef struct
{
    uint pixelSize;
    char *font_family;
} Font;

SvgContainer *initSvgContainer(uint width, uint height, uint bkgColor);
void freeSvg(Svg_t *data);
int svgEndElement(SvgContainer *data);
int saveToFile(SvgContainer *data, const char *filename);
int addElementToSvgContainer(SvgContainer *container, SvgElement *element);


int addStroke(SvgElement *element, Stroke *stroke);
int addFill(SvgElement *element, uint color);
int addFont(SvgElement *element, Font *font);
int addRotation(SvgElement *element, double angle, uint centerX, uint centerY);

SvgLine *addLine(uint x1, uint y1, uint x2, uint y2, Stroke *stroke);
int addLineEndElement(SvgLine *line);

SvgRect *addRect(uint x, uint y, uint width, uint height, uint color);
int addRectEndElement(SvgRect *rect);

SvgText *initText(uint x, uint y, uint color, Font *font);
int addText(SvgText *element, const char *text);
int addTextEndElement(SvgRect *text);


#endif // SVGUTIL_H
