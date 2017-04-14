#ifndef SVGBARCHART_H
#define SVGBARCHART_H

#include <math.h>
#include <stdbool.h>

#include "svgutil.h"
#include "error.h"

#define MARGIN 0.02 // marge de la feuille
#define P 0.02 // marge entre la ligne zéro et les étiquettes
#define R 0.01 // marge supérieur, inférieur et gauche dans la fenetre du graphique
               // ainsi que la hauteur de la graduation en fonction de la hauteur du graphique
#define GAP 0.1 // intervalle entre les barres

// rotation pour les étiquettes de l'axe X
typedef enum
{
    HORIZONTAL,
    VERTICAL
} Rotation;

typedef struct BarChart BarChart;

#define setChartData(barChart, chartData) setChartData_impl(barChart, chartData, sizeof chartData / sizeof chartData[0])
#define setChartLabel(barChart, chartLabel) setChartLabel_impl(barChart, chartLabel, sizeof chartLabel / sizeof chartLabel[0])

int plot(BarChart *barChart);
BarChart *initBarChart(uint width, uint height, uint color);
void freeBarChart(BarChart *barChart);
void setMaxScale(BarChart *barChart, double maxScale);
void setMinScale(BarChart *barChart, double minScale);
void setInterval(BarChart *barChart, double interval);
int setXAxisTitleProp(BarChart *barChart, const char *xAxis, uint size);
int setYAxisTitleProp(BarChart *barChart, const char *yAxis, uint size);
int setMainTitle(BarChart *barChart, const char *mainTitle, uint size);
void setXAxisLabelFontSize(BarChart *barChart, uint size);
void setYAxisLabelFontSize(BarChart *barChart, uint size);
void setXAxisLabelDirection(BarChart *barChart, Rotation direction);
void setYAxisLabelPrecision(BarChart *barChart, uint precision);
void setBarColor(BarChart *BarChart, uint color);
void setChartLabel_impl(BarChart *barChart, const char **chartLabel, size_t chartLabelSize);
void setChartData_impl(BarChart *barChart, const double *chartData, size_t chartDataSize);
int saveBarChart(BarChart *barChart, const char *filename);


#endif // SVGBARCHART_H
