#include "svgbarchart.h"

#include <string.h>
#include <stdlib.h>

typedef struct
{
    // hauteur et largeur en pixels
    uint height;
    uint width;
    uint widthSpace;
} FontDim;

typedef struct
{
    uint height;
    uint width;
} TextDim;

typedef struct
{
    uint x;
    uint y;
    uint width;
    uint height;
} Rect;

struct BarChart
{
    double minScale_;
    double maxScale_;

    double interval_;
    bool isIntervalSet_;

    char *xAxisTitle_;
    uint xAxisTitleFontSize_;

    char *yAxisTitle_;
    uint yAxisTitleFontSize_;

    char *mainTitle_;
    uint mainTitleFontSize_;

    uint xAxisLabelFonsize_;
    uint yAxisLabelFontSize_;

    Rotation xAxisLabelDirection_;

    uint YAxisLabelPrecision_;

    SvgContainer *svgData_;

    const char **chartLabel_; // référence
    size_t chartLabelSize_;

    const double *chartData_; // référence sur un tableau de données
    size_t chartDataSize_;

    uint width_;
    uint height_;
    uint barColor_;

    // **********

    Rect chartPos;
    Rect titleXPos;
    Rect titleYPos;
    Rect labelXPos;
    Rect labelYPos;
    Rect mainTitlePos;

    double Ymin;
    double Ymax;
    double scaleY;
    double Yzero;
    double intervalX;
    double angle;
    double margin;
    double p;
    double r;

};

// fonctions privées
static FontDim getFontDimensions(uint fontSize);
static TextDim getTextDimensions_char(const char *text, uint fontSize);
static TextDim getTextDimensions_uint(uint textLength, uint fontSize);
static TextDim getMaxXAxisLabelSize(BarChart *barChart);
static TextDim getMaxYAxisLabelSize(BarChart *barChart);
static int addTextChart(BarChart *barChart, uint x, uint y, const char *text, uint fontSize, double Rotation);
static int addLineChart(BarChart *barChart, uint x1, uint y1, uint x2, uint y2, Stroke *stroke);
static int addRectChart(BarChart *barChart, uint x, uint y, uint width, uint height, uint color);
static int plotBarChart(BarChart *barChart);
static void preCompute(BarChart *barChart);
static void chartCompute(BarChart *barChart);



int plot(BarChart *barChart)
{
    barChart->chartPos.x = 0;
    barChart->chartPos.y = 0;
    barChart->chartPos.width = 0;
    barChart->chartPos.height = 0;

    barChart->titleXPos.x = 0;
    barChart->titleXPos.y = barChart->height_;
    barChart->titleXPos.width = 0;
    barChart->titleXPos.height = 0;

    barChart->titleYPos.x = 0;
    barChart->titleYPos.y = 0;
    barChart->titleYPos.width = 0;
    barChart->titleYPos.height = 0;

    barChart->labelXPos.x = 0;
    barChart->labelXPos.y = 0;
    barChart->labelXPos.width = 0;
    barChart->labelXPos.height = 0;

    barChart->labelYPos.x = 0;
    barChart->labelYPos.y = 0;
    barChart->labelYPos.width = 0;
    barChart->labelYPos.height = 0;

    barChart->mainTitlePos.x = 0;
    barChart->mainTitlePos.y = 0;
    barChart->mainTitlePos.width = 0;
    barChart->mainTitlePos.height = 0;


    // effectue un pré calcul, en effet, certaines coordonnées des différents objets
    // (titres, étiquettes, graphique ne peuvent pas etre calculé complement. Ils
    // dépendent de l'emplacement de l'axe X sur la fenetre graphique
    preCompute(barChart);

    chartCompute(barChart);

    Rect chart = barChart->chartPos;
    Rect titleX = barChart->titleXPos;
    Rect titleY = barChart->titleYPos;
    Rect labelX = barChart->labelXPos;
    Rect labelY = barChart->labelYPos;

    double Ymin = barChart->Ymin;
    double Ymax = barChart->Ymax;
    double scaleY = barChart->scaleY;
    double Yzero = barChart->Yzero;
    double intervalX = barChart->intervalX;
    double angle = barChart->angle;

    int error;

    // affichage de la fenetre graphique et / ou des étiquettes de l'axe X
    if(barChart->chartLabel_ && (barChart->xAxisLabelFonsize_ > 0))
    {
        error = plotBarChart(barChart);
        if(error) return error;

        for(size_t i = 0; i < barChart->chartDataSize_; i++)
        {
            error = addTextChart(barChart,
                                (uint)(labelX.x + i * intervalX),
                                labelX.y,
                                barChart->chartLabel_[i],
                                barChart->xAxisLabelFonsize_,
                                angle);

            if(error) return error;
        }
    }
    else
    {
        error = plotBarChart(barChart);
        if(error) return error;
    }


    // affichage titre principal
    if(barChart->mainTitle_ && (barChart->mainTitleFontSize_ > 0))
    {
         error = addTextChart(barChart, barChart->mainTitlePos.x, barChart->mainTitlePos.y, barChart->mainTitle_, barChart->mainTitleFontSize_, 0);
         if(error) return error;
    }

    // affichage du titre de l'axe Y
    if(barChart->yAxisTitle_ && (barChart->yAxisTitleFontSize_ > 0))
    {
        titleY.y = chart.y + chart.height - (chart.height - titleY.height) / 2;
        error = addTextChart(barChart, titleY.x, titleY.y, barChart->yAxisTitle_, barChart->yAxisTitleFontSize_, -90);
        if(error) return error;
    }

    // affichage du titre de l'axe X
    if(barChart->xAxisTitle_ && (barChart->xAxisTitleFontSize_ > 0))
    {
        titleX.x = chart.x + (chart.width - titleX.width) / 2;
        error = addTextChart(barChart, titleX.x, titleX.y, barChart->xAxisTitle_, barChart->xAxisTitleFontSize_, 0);
        if(error) return error;
    }

    // étiquettes axe Y
    if(barChart->isIntervalSet_ && (barChart->yAxisLabelFontSize_ > 0))
    {
        double step = Yzero + labelY.height / 2;
        double value = 0;
        char buffer[BUFFERSIZE];

        // pour les valeurs de Y >= 0
        while(step >= Ymin)
        {
            sprintf(buffer, "%0.*f", barChart->YAxisLabelPrecision_, value);
            error = addTextChart(barChart, labelY.x - labelY.width, (uint)step, buffer, barChart->yAxisLabelFontSize_, 0);
            if(error) return error;

            value += barChart->interval_;
            step -= barChart->interval_ * scaleY;
        }


        step = Yzero + barChart->interval_ * scaleY;
        value = -barChart->interval_;
        // pour les valeurs de Y <= 0
        while(step <= Ymax)
        {
            sprintf(buffer, "%0.*f", barChart->YAxisLabelPrecision_, value);
            error = addTextChart(barChart, labelY.x - labelY.width, (uint)step, buffer, barChart->yAxisLabelFontSize_, 0);
            if(error) return error;

            value -= barChart->interval_;
            step += barChart->interval_ * scaleY;
        }
    }


    svgEndElement(barChart->svgData_);

    return SUCCESS;
}

BarChart *initBarChart(uint width, uint height, uint color)
{
    BarChart *chart = malloc(sizeof(BarChart));

    if(!chart)
    {
        setError(MALLOC_ERROR);
        return NULL;
    }

    chart->svgData_ = initSvgContainer(width, height, color);

    if(!chart->svgData_)
    {
        free(chart);
        return NULL;
    }

    chart->minScale_ = 0;
    chart->maxScale_ = 0;

    chart->interval_ = 0;
    chart->isIntervalSet_ = false;

    chart->xAxisTitle_ = NULL;
    chart->xAxisTitleFontSize_ = 0;

    chart->yAxisTitle_ = NULL;
    chart->yAxisTitleFontSize_ = 0;

    chart->mainTitle_ = NULL;
    chart->mainTitleFontSize_ = 0;

    chart->xAxisLabelFonsize_ = 0;
    chart->yAxisLabelFontSize_ = 0;

    chart->xAxisLabelDirection_ = HORIZONTAL;

    chart->YAxisLabelPrecision_ = 0;

    chart->chartLabel_ = NULL;
    chart->chartLabelSize_ = 0;

    chart->chartData_ = NULL;
    chart->chartDataSize_ = 0;

    chart->width_ = width;
    chart->height_ = height;
    chart->barColor_ = 0x004586;

    chart->angle = 0; // zéro car par défault l'orientation des étiquettes est horizontal
    chart->margin = MARGIN;
    chart->p = P;
    chart->r = R;

    return chart;
}

void freeBarChart(BarChart *barChart)
{
    free(barChart->xAxisTitle_);
    free(barChart->yAxisTitle_);
    free(barChart->mainTitle_);
    freeSvg(barChart->svgData_);
    free(barChart);
}

void setMaxScale(BarChart *barChart, double maxScale)
{
    barChart->maxScale_ = maxScale;
}

void setMinScale(BarChart *barChart, double minScale)
{
    barChart->minScale_ = minScale;
}

void setInterval(BarChart *barChart, double interval)
{
    barChart->interval_ = interval;
    barChart->isIntervalSet_ = true;
}

int setXAxisTitleProp(BarChart *barChart, const char *xAxis, uint size)
{
    free(barChart->xAxisTitle_);
    barChart->xAxisTitle_ = strdup(xAxis);

    if(!barChart->xAxisTitle_) return -1;

    barChart->xAxisTitleFontSize_ = size;

    return SUCCESS;
}

int setYAxisTitleProp(BarChart *barChart, const char *yAxis, uint size)
{
    free(barChart->yAxisTitle_);
    barChart->yAxisTitle_ = strdup(yAxis);

    if(!barChart->yAxisTitle_) return -1;

    barChart->yAxisTitleFontSize_ = size;

    return SUCCESS;
}

int setMainTitle(BarChart *barChart, const char *mainTitle, uint size)
{
    free(barChart->mainTitle_);
    barChart->mainTitle_ = strdup(mainTitle);

    if(!barChart->mainTitle_) return -1;

    barChart->mainTitleFontSize_ = size;

    return SUCCESS;
}

void setXAxisLabelFontSize(BarChart *barChart, uint size)
{
    barChart->xAxisLabelFonsize_ = size;
}

void setYAxisLabelFontSize(BarChart *barChart, uint size)
{
    barChart->yAxisLabelFontSize_ = size;
}

void setXAxisLabelDirection(BarChart *barChart, Rotation direction)
{
    barChart->xAxisLabelDirection_ = direction;
}

void setYAxisLabelPrecision(BarChart *barChart, uint precision)
{
    barChart->YAxisLabelPrecision_ = precision;
}

void setBarColor(BarChart *BarChart, uint color)
{
    BarChart->barColor_ = color;
}

void setChartLabel_impl(BarChart *barChart, const char **chartLabel, size_t chartLabelSize)
{
    barChart->chartLabel_ = chartLabel;
    barChart->chartLabelSize_ = chartLabelSize;
}

void setChartData_impl(BarChart *barChart, const double *chartData, size_t chartDataSize)
{
    barChart->chartData_ = chartData;
    barChart->chartDataSize_ = chartDataSize;
}

int saveBarChart(BarChart *barChart, const char *filename)
{
    int error = saveToFile(barChart->svgData_, filename);

    if(error) return error;

    return SUCCESS;
}




// fonctions privées
FontDim getFontDimensions(uint fontSize)
{
    // coefficient pour la police standard, a voir si c'est toujours vrai !?
    // a revoir car les titres ne sont pas alignés
    FontDim dim;

    dim.height = (uint)((double)fontSize * 0.8);
    dim.width = (uint)((double)fontSize * 0.28);
    dim.widthSpace = (uint)((double)fontSize * 0.12);

    return dim;
}

TextDim getTextDimensions_char(const char *text, uint fontSize)
{
    uint textLength = (uint)strlen(text);
    FontDim font = getFontDimensions(fontSize);
    TextDim textD;

    textD.height = font.height;
    textD.width = textLength * font.width + (textLength - 1) * font.widthSpace;

    return textD;
}

TextDim getTextDimensions_uint(uint textLength, uint fontSize)
{
    FontDim font = getFontDimensions(fontSize);
    TextDim textD;

    textD.height = font.height;
    textD.width = textLength * font.width + (textLength - 1) * font.widthSpace;

    return textD;
}

TextDim getMaxXAxisLabelSize(BarChart *barChart)
{
    uint maxTextLength = 0;

    // cherche le mot le plus long
    for(size_t i = 0; i < barChart->chartLabelSize_; i++)
    {
        uint temp = (uint)strlen(barChart->chartLabel_[i]);

        if(temp > maxTextLength)
            maxTextLength = temp;
    }

    return getTextDimensions_uint(maxTextLength, barChart->xAxisLabelFonsize_);
}

TextDim getMaxYAxisLabelSize(BarChart *barChart)
{
    // recherche du nombre le plus long en terme de chiffres
    double max = barChart->chartData_[0];
    double min = barChart->chartData_[0];

    for(size_t i = 1; i < barChart->chartDataSize_; i++)
    {
        max = fmax(barChart->chartData_[i], max);
        min = fmin(barChart->chartData_[i], min);
    }


    uint nMaxLength = 0;
    uint nMinLength = 0;

    if(max < 0)
    {
        nMaxLength++;
        max = -max;
    }

    if(min < 0)
    {
        nMinLength++;
        min = -min;
    }

    nMaxLength += ceil(log10(max));
    nMinLength += ceil(log10(min));

    if(nMaxLength < nMinLength)
        nMaxLength = nMinLength;


    // si l'on ajout des chiffres après la virgule avec la fonction setYAxisLabelPrecision
    if(barChart->YAxisLabelPrecision_)
        nMaxLength += 1 + barChart->YAxisLabelPrecision_;


    return getTextDimensions_uint(nMaxLength, barChart->yAxisLabelFontSize_);
}

int addTextChart(BarChart *barChart, uint x, uint y, const char *text, uint fontSize, double rotation)
{
    Font titleFont = {fontSize, NULL};
    SvgText *titleText = initText(x, y, BLACK, &titleFont);

    if(!titleText) return ERROR;


    int error = addRotation(titleText, rotation, x, y);
    if(error) return error;

    error = addText(titleText, text);
    if(error) return error;

    error = addTextEndElement(titleText);
    if(error) return error;

    error = addElementToSvgContainer(barChart->svgData_, titleText);
    if(error) return error;

    freeSvg(titleText);

    return SUCCESS;
}

int addLineChart(BarChart *barChart, uint x1, uint y1, uint x2, uint y2, Stroke *stroke)
{
    SvgLine *line = addLine(x1, y1, x2 ,y2, stroke);

    if(!line) return ERROR;

    int error = addLineEndElement(line);
    if(error) return error;

    error = addElementToSvgContainer(barChart->svgData_, line);
    if(error) return error;

    freeSvg(line);

    return SUCCESS;
}

int addRectChart(BarChart *barChart, uint x, uint y, uint width, uint height, uint color)
{
    SvgRect *rect = addRect(x, y, width ,height, color);

    if(!rect) return ERROR;

    int error = addRectEndElement(rect);
    if(error) return error;


    error = addElementToSvgContainer(barChart->svgData_, rect);
    if(error) return error;

    freeSvg(rect);

    return SUCCESS;
}

int plotBarChart(BarChart *barChart)
{
    /* cette fonction trace les barres de l'histogramme, l'axe X, l'axe Y, les graduations de l'axe X et les axes
       verticaux correspondants aux intervalles
     */
    int error;

    uint x = barChart->chartPos.x;
    uint y = barChart->chartPos.y;
    uint width = barChart->chartPos.width;
    uint height = barChart->chartPos.height;
    double Yzero = barChart->Yzero;
    double scaleY = barChart->scaleY;
    double intervalX = barChart->intervalX;
    double r = barChart->r;

    // les données
    double gap = GAP; // intervalle entre les barres

    for(size_t i = 0; i < barChart->chartDataSize_; i++)
    {
        double value = barChart->chartData_[i];
        double Yrect;

        // pour les valeurs positives ou négatives les coordonnées de l'origine du rectangle sont différents
        if(value >= 0)
            Yrect = Yzero - value * scaleY;

        else
        {
            Yrect = Yzero;
            value = -value;
        }


        error = addRectChart(barChart,
                            (uint)(x + width * r + intervalX * gap+ i * intervalX), // x
                            (uint)(Yrect),                                         // y
                            (uint)(intervalX - 2 * intervalX * gap),               // width
                            (uint)(value * scaleY),                                // height
                            barChart->barColor_);

        if(error) return error;
    }

    Stroke lineStroke = {BLACK, 3}; // TODO : l'utilisateur choisis les valeurs

    // axe Y = 0
    error = addLineChart(barChart,(uint)x, (uint)Yzero, (uint)(x + width), (uint)Yzero, &lineStroke);
    if(error) return error;


    // axe des Y
    error = addLineChart(barChart, (uint)(x + width * r),
                         (uint)(y + height * r),
                         (uint)(x + width * r),
                         (uint)(y + height - height * r),
                         &lineStroke);

    if(error) return error;


    // axe Y, intervalles
    if(barChart->isIntervalSet_ && (barChart->yAxisLabelFontSize_ > 0))
    {
        double Ymin = barChart->Ymin;
        double Ymax = barChart->Ymax;

        Stroke line = {0xBBBBBB, 2}; // TODO : l'utilisateur choisis les valeurs

        double step = Yzero - barChart->interval_ * scaleY;
        // pour les valeurs de Y >= 0
        while(step >= Ymin)
        {
            error = addLineChart(barChart,
                                 (uint)(x + width * r),
                                 (uint)step,
                                 (uint)(x + width),
                                 (uint)step,
                                 &line);
            if(error) return error;

            error = addLineChart(barChart,
                                 (uint)x,
                                 (uint)step,
                                 (uint)(x + width * r),
                                 (uint)step,
                                 &lineStroke);
            if(error) return error;

            step -= barChart->interval_ * scaleY;
        }

        step = Yzero + barChart->interval_ * scaleY;
        // pour les valeurs de Y <= 0
        while(step <= Ymax)
        {
            error = addLineChart(barChart,
                                 (uint)(x + width * r),
                                 (uint)step,
                                 (uint)(x + width),
                                 (uint)step,
                                 &line);
            if(error) return error;

            error = addLineChart(barChart,
                                 (uint)x,
                                 (uint)step,
                                 (uint)(x + width * r),
                                 (uint)step,
                                 &lineStroke);
            if(error) return error;

            step += barChart->interval_ * scaleY;
        }
    }


    // graduation
    for(size_t i = 0; i < barChart->chartDataSize_; i++)
    {
        error = addLineChart(barChart,
                             (uint)(x+ width * r + i * intervalX), // x1
                             (uint)(Yzero - height * r),           // y1
                             (uint)(x+ width * r + i * intervalX), // x2
                             (uint)(Yzero + height * r),           // y2
                             &lineStroke);

        if(error) return error;
    }

    return SUCCESS;
}

void preCompute(BarChart *barChart)
{
    // calcul partiel des coordonnées, afin de connaitre l'endroit où sera tracé le graphique

    double margin = barChart->margin;
    uint width = barChart->width_;
    uint height = barChart->height_;

    TextDim temp;

    // titre de l'axe Y
    if(barChart->yAxisTitle_ && (barChart->yAxisTitleFontSize_ > 0))
    {
        temp = getTextDimensions_char(barChart->yAxisTitle_, barChart->yAxisTitleFontSize_);
        barChart->titleYPos.width = temp.height; // car le titre est tourné de 90 degrés
        barChart->titleYPos.height = temp.width;
        barChart->titleYPos.x = (uint)(width * margin + barChart->titleYPos.width);
        //titleY.y = height / 2; // valeur temporaire pour test / valeur incalculable à ce point
    }


    // label de l'axe Y
    temp = getMaxYAxisLabelSize(barChart);
    barChart->labelYPos.width = temp.width;
    barChart->labelYPos.height = temp.height;
    barChart->labelYPos.x = (uint)(barChart->titleYPos.x + width * margin + barChart->labelYPos.width);
    // labelY.y = width; // valeur temporaire pour test / valeur incalculable à ce point


    // titre principal
    if(barChart->mainTitle_ && (barChart->mainTitleFontSize_ > 0))
    {
        temp = getTextDimensions_char(barChart->mainTitle_, barChart->mainTitleFontSize_);
        barChart->mainTitlePos.width = temp.width;
        barChart->mainTitlePos.height = temp.height;
        barChart->mainTitlePos.x = width / 2 - barChart->mainTitlePos.width / 2;
        barChart->mainTitlePos.y = (uint)(height * margin + barChart->mainTitlePos.height);
    }


    // titre de l'axe X
    if(barChart->xAxisTitle_ && (barChart->xAxisTitleFontSize_ > 0))
    {
        temp = getTextDimensions_char(barChart->xAxisTitle_, barChart->xAxisTitleFontSize_);
        barChart->titleXPos.width = temp.width;
        barChart->titleXPos.height = temp.height;
        //titleX.x = width / 2; // valeur temporaire pour test / valeur incalculable à ce point
        barChart->titleXPos.y = (uint)(height - height * margin);
    }


    // zone graphique, les labels de l'axe X sont intégrés dans cette zone
    barChart->chartPos.x = (uint)(barChart->labelYPos.x + width * margin);
    barChart->chartPos.y = (uint)(barChart->mainTitlePos.y + height * margin);
    barChart->chartPos.width = (uint)(width - width * margin - barChart->chartPos.x);
    barChart->chartPos.height = (uint)(barChart->titleXPos.y - barChart->titleXPos.height - height * margin - barChart->chartPos.y);
}

void chartCompute(BarChart *barChart)
{
    // calcul de la fenetre graphique
    double p = barChart->p; // marge entre la ligne zéro et les étiquettes
    double r = barChart->r; // marge supérieur, inférieur et gauche dans la fenetre du graphique
                            // ainsi que la hauteur de la graduation en fonction de la hauteur du graphique

    barChart->Ymin = barChart->chartPos.y + barChart->chartPos.height * r;
    barChart->Ymax= barChart->chartPos.y + barChart->chartPos.height - barChart->chartPos.height * r;
    barChart->scaleY = (barChart->chartPos.height - 2 * barChart->chartPos.height * r) / (barChart->maxScale_ - barChart->minScale_);
    barChart->Yzero = barChart->chartPos.y + barChart->chartPos.height * r + barChart->scaleY * barChart->maxScale_;
    barChart->intervalX = (barChart->chartPos.width - barChart->chartPos.width * r) / barChart->chartDataSize_;

    // le graphique est redimensionné en fonction des étiquettes de l'axe X
    if(barChart->chartLabel_ && (barChart->xAxisLabelFonsize_ > 0)) // si les labels de l'axe X sont définis et la police d'écriture > 0
    {
        double Ylabel; // alias labelX.y
        TextDim temp = getMaxXAxisLabelSize(barChart);


        if(barChart->xAxisLabelDirection_ == HORIZONTAL)
        {
            barChart->labelXPos.height = temp.height; // pas de rotation
            barChart->labelXPos.width = temp.width;
            barChart->angle = 0;
        }
        else
        {
            barChart->labelXPos.height = temp.width; // rotation de 90 degres
            barChart->labelXPos.width = temp.height;
            barChart->angle = 90;
        }

        // si l'axe Y = 0 est trop bas, scaleY et Yzero sont recalculées
        if(barChart->Ymax < barChart->Yzero + barChart->chartPos.height * p + barChart->labelXPos.height)
        {
            barChart->chartPos.height -= barChart->chartPos.height * p + barChart->labelXPos.height;
            barChart->scaleY = (barChart->chartPos.height - 2 * barChart->chartPos.height * r) / (barChart->maxScale_ - barChart->minScale_);
            barChart->Yzero = barChart->chartPos.y + barChart->chartPos.height * r + barChart->scaleY * barChart->maxScale_;

            if(barChart->xAxisLabelDirection_ == HORIZONTAL)
                Ylabel = barChart->Yzero + barChart->chartPos.height * p + barChart->labelXPos.height;
            else
                Ylabel = barChart->Yzero + barChart->chartPos.height * p;
        }

        // si l'axe Y = 0 est trop haut
        else if(barChart->Ymin > barChart->Yzero - barChart->chartPos.height * p - barChart->labelXPos.height)
        {
            barChart->chartPos.y += barChart->chartPos.height * p + barChart->labelXPos.height;
            barChart->chartPos.height -= barChart->chartPos.height * p + barChart->labelXPos.height;
            barChart->scaleY= (barChart->chartPos.height - 2 * barChart->chartPos.height * r) / (barChart->maxScale_ - barChart->minScale_);
            barChart->Yzero = barChart->chartPos.y + barChart->chartPos.height * r + barChart->scaleY * barChart->maxScale_;

            if(barChart->xAxisLabelDirection_ == HORIZONTAL)
                Ylabel = barChart->Yzero - barChart->chartPos.height * p;
            else
                Ylabel = barChart->Yzero - barChart->chartPos.height * p - barChart->labelXPos.height;
        }
        else
        {
            if(barChart->xAxisLabelDirection_ == HORIZONTAL)
                Ylabel = barChart->Yzero + barChart->chartPos.height * p + barChart->labelXPos.height;
            else
                Ylabel = barChart->Yzero + barChart->chartPos.height * p;
        }

        barChart->labelXPos.x = (uint)(barChart->chartPos.x + barChart->chartPos.width * r + (barChart->intervalX - barChart->labelXPos.width) / 2);
        barChart->labelXPos.y = (uint)Ylabel;
    }
}
