//#include "test.h"
#include "svgbarchart.h"

int main(void)
{
    const double chartData[] = {
    27550, 54150, 81225, 110200, 133000, 165300, 186200, 192850, 189525, 189525, 192850, 186200,
    192850, 186200, 192850, 189525, 189525, 192850, 186200, 192850, 186200, 192850, 189525, 189525, 192850,
    186200, 192850, 197400, 220400, 189525, 162450, 137750, 106400, 82650, 42000};


    const char *day[] = {"03/22", "03/23", "03/24", "03/25", "03/26", "03/27", "03/28", "03/29", "03/30", "03/31",
                         "04/01", "04/02", "04/03", "04/04", "04/05", "04/06", "04/07", "04/08", "04/09", "04/10",
                         "04/11", "04/12", "04/13", "04/14", "04/15", "04/16", "04/17", "04/18", "04/18", "04/20",
                         "04/21", "04/22", "04/23", "04/24", "04/25"};


    BarChart *chart = initBarChart(1200, 800, 0xFFDCA0);

    setMaxScale(chart, 250000);
    setMinScale(chart, 0);
    setInterval(chart, 50000);

    setXAxisTitleProp(chart, "Jour", 35);
    setYAxisTitleProp(chart, "Nombre", 35);
    setMainTitle(chart, "Fréquence des dates de Paques sur une période", 50);

    setChartData(chart, chartData);
    setChartLabel(chart, day);

    setXAxisLabelFontSize(chart, 25);
    setYAxisLabelFontSize(chart, 25);

    //setBarColor(chart, 0x0003FF);

    setXAxisLabelDirection(chart, VERTICAL);

    plot(chart);
    saveBarChart(chart, "./paques.svg");

    freeBarChart(chart);


    return 0;
}
