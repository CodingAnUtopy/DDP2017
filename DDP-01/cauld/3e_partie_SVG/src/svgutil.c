#include "svgutil.h"

#include <string.h>


// fonctions privées
static uint getRedComponent(const uint color);
static uint getGreenComponent(const uint color);
static uint getBlueComponent(const uint color);


SvgContainer *initSvgContainer(uint width, uint height, uint bkgColor)
{
    SvgContainer *data = initList();
    char buffer[BUFFERSIZE];


    int error = pushBack(&data, "<?xml version=\"1.0\" encoding=\"utf-8\"?>");

    if(error)
        goto initSvgError;


    sprintf(buffer, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%u\" height=\"%u\">", width, height);
    error = pushBack(&data, buffer);

    if(error)
        goto initSvgError;


    sprintf(buffer, "\t<rect width=\"%u\" height=\"%u\" fill=\"#%02X%02X%02X\" />",
            width, height, getRedComponent(bkgColor), getGreenComponent(bkgColor), getBlueComponent(bkgColor));

    error = pushBack(&data, buffer);

    if(error)
        goto initSvgError;


    return data;


initSvgError:
    freeSvg(data);
    return NULL;
}

void freeSvg(Svg_t *data)
{
    freeList(data);
}

int svgEndElement(SvgContainer *data)
{
    int error = pushBack(&data, "</svg>");

    if(error) return error;

    return SUCCESS;
}

int saveToFile(SvgContainer *data, const char *filename)
{
    FILE *fp = fopen(filename, "w");

    if(!fp)
    {
        setError(FOPEN_ERROR);
        return ERROR;
    }

    printList(data, fp);

    fclose(fp);

    return SUCCESS;
}

int addElementToSvgContainer(SvgContainer *container, SvgElement *element)
{
    char buffer[BUFFERSIZE];

    copyListToBuffer(element, buffer);

    int error = pushBack(&container, buffer);

    if(error) return error;

    return SUCCESS;
}

int addStroke(SvgElement *element, Stroke *stroke)
{
    char buffer[BUFFERSIZE];

    sprintf(buffer, " stroke=\"#%02X%02X%02X\"", getRedComponent(stroke->color),
            getGreenComponent(stroke->color), getBlueComponent(stroke->color));

    int error = pushBack(&element, buffer);

    if(error) return error;

    if(stroke->width > 0)
    {
        sprintf(buffer, " stroke-width=\"%d\"", stroke->width);

        error = pushBack(&element, buffer);

        if(error) return error;
    }

    return SUCCESS;
}

int addFill(SvgElement *element, uint color)
{
    char buffer[BUFFERSIZE];

    sprintf(buffer, " fill=\"#%02X%02X%02X\"", getRedComponent(color),
            getGreenComponent(color), getBlueComponent(color));

    int error = pushBack(&element, buffer);

    if(error) return error;

    return SUCCESS;
}

int addFont(SvgElement *element, Font *font)
{
    char buffer[BUFFERSIZE];

    sprintf(buffer, " font-size=\"%u\"", font->pixelSize);

    int error = pushBack(&element, buffer);

    if(error) return error;


    if(font->font_family != 0)
    {
        sprintf(buffer, " font-family=\"%s\"", font->font_family);

        error = pushBack(&element, buffer);

        if(error) return error;
    }

    return SUCCESS;
}

int addRotation(SvgElement *element, double angle, uint centerX, uint centerY)
{
    char buffer[BUFFERSIZE];

    sprintf(buffer, " transform=\"rotate(%.2f,%u,%u)\"", angle, centerX, centerY);

    int error = pushBack(&element, buffer);

    if(error) return error;

    return SUCCESS;
}

SvgLine *addLine(uint x1, uint y1, uint x2, uint y2, Stroke *stroke)
{
    SvgLine *data = initList();
    char buffer[BUFFERSIZE];

    sprintf(buffer, "\t<line x1=\"%u\" y1=\"%u\" x2=\"%u\" y2=\"%u\"", x1, y1, x2, y2);

    int error = pushBack(&data, buffer);

    if(error)
        goto addLineError;


    if(stroke)
    {
        error = addStroke(data, stroke);

        if(error)
            goto addLineError;
    }

    return data;


addLineError:
    freeSvg(data);
    return NULL;
}

int addLineEndElement(SvgLine *line)
{
    int error = pushBack(&line, " />");

    if(error) return error;

    return SUCCESS;
}

SvgRect *addRect(uint x, uint y, uint width, uint height, uint color)
{
    SvgRect *data = initList();
    char buffer[BUFFERSIZE];

    sprintf(buffer, "\t<rect x=\"%u\" y=\"%u\" width=\"%u\" height=\"%u\" fill=\"#%02X%02X%02X\"",
            x, y, width, height,getRedComponent(color), getGreenComponent(color), getBlueComponent(color));

    int error = pushBack(&data, buffer);

    if(error) return NULL;

    return data;
}


int addRectEndElement(SvgRect *rect)
{
    int error = pushBack(&rect, " />");

    if(error) return error;

    return SUCCESS;
}

SvgText *initText(uint x, uint y, uint color, Font *font)
{
    SvgText *data = initList();
    char buffer[BUFFERSIZE];

    sprintf(buffer, "\t<text x=\"%u\" y=\"%u\" fill=\"#%02X%02X%02X\"",
            x, y, getRedComponent(color), getGreenComponent(color), getBlueComponent(color));

    int error = pushBack(&data, buffer);

    if(error)
        goto initTextError;


    if(font)
    {
        error = addFont(data, font);

        if(error)
            goto initTextError;
    }

    return data;


initTextError:
    freeSvg(data);
    return NULL;
}

int addText(SvgText *element, const char *text)
{
    char buffer[BUFFERSIZE];

    sprintf(buffer, ">%s", text);

    int error = pushBack(&element, buffer);

    if(error) return error;

    return SUCCESS;
}

int addTextEndElement(SvgRect *text)
{
    int error = pushBack(&text, "</text>");

    if(error) return error;

    return SUCCESS;
}




// fonctions privées
uint getRedComponent(const uint color)
{
    return (color & 0xFF0000) / 0x10000;
}

uint getGreenComponent(const uint color)
{
    return (color & 0x00FF00) / 0x100;
}

uint getBlueComponent(const uint color)
{
    return (color & 0x0000FF);
}
