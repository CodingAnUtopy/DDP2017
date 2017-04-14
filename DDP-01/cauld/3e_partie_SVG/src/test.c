#include "test.h"

void testLlist(void)
{
    Node *list = initList();

    pushBack(&list, "Bonjour");
    pushBack(&list, "azerty!:?");
    pushBack(&list, "3615");

    printList(list, stdout);

    char buffer[2000];
    copyListToBuffer(list, buffer);
    printf("%s\n", buffer);

    freeList(list);


    Node *list2 = initList();

    printList(list2, stdout);

    copyListToBuffer(list2, buffer);
    printf("%s\n", buffer);

    freeList(list2);
}

void testSVG(void)
{
    SvgContainer *data = initSvgContainer(640, 480, WHITE);


    Stroke strokeLine1 = {BLUE, -1};
    SvgLine *line1 = addLine(50, 50, 100, 100, &strokeLine1);
    addLineEndElement(line1);
    addElementToSvgContainer(data, line1);
    freeSvg(line1);

    Stroke strokeLine2 = {GREEN, 8};
    SvgLine *line2 = addLine(150, 150, 620, 300, &strokeLine2);
    addLineEndElement(line2);
    addElementToSvgContainer(data, line2);
    freeSvg(line2);

    SvgRect *rect1 = addRect(400, 20, 50, 50, MAGENTA);
    addRectEndElement(rect1);
    addElementToSvgContainer(data, rect1);
    freeSvg(rect1);

    Stroke strokeRect2 = {RED, 8};
    SvgRect *rect2 = addRect(400, 80, 50, 50, BLUE);
    addStroke(rect2, &strokeRect2);
    addRectEndElement(rect2);
    addElementToSvgContainer(data, rect2);
    freeSvg(rect2);

    Stroke strokeRect3 = {BLACK, 8};
    SvgRect *rect3 = addRect(400, 200, 50, 50, 0x003615);
    addStroke(rect3, &strokeRect3);
    addRotation(rect3, 23.7, 450, 250);
    addRectEndElement(rect3);
    addElementToSvgContainer(data, rect3);
    freeSvg(rect3);

    Stroke strokeText = {RED, 3};
    Font fontText = {100, NULL};
    SvgText *text = initText( 100, 250, BLUE, &fontText);
    addStroke(text, &strokeText);
    addRotation(text, -20, 100, 250);
    addText(text, "Hello");
    addTextEndElement(text);
    addElementToSvgContainer(data, text);
    freeSvg(text);


    svgEndElement(data);

    saveToFile(data, "./essai.svg");
    freeSvg(data);
}

void testBarChart(void)
{
    const double chartData[] = {
    27550, 54150, 81225, 110200, 133000, 165300, 186200, 192850, 189525, 189525, 192850, 186200,
    192850, 186200, 192850, 189525, 189525, 192850, 186200, 192850, 186200, 192850, 189525, 189525, 192850,
    186200, 192850, 197400, 220400, 189525, 162450, 137750, 106400, 82650, 42000};


    const char *day[] = {"03/22", "03/23", "03/24", "03/25", "03/26", "03/27", "03/28", "03/29", "03/30", "03/31",
                         "04/01", "04/02", "04/03", "04/04", "04/05", "04/06", "04/07", "04/08", "04/09", "04/10",
                         "04/11", "04/12", "04/13", "04/14", "04/15", "04/16", "04/17", "04/18", "04/18", "04/20",
                         "04/21", "04/22", "04/23", "04/24", "04/25"};


    BarChart *chart = initBarChart(1200, 800, WHITE);

    setMaxScale(chart, 250000);
    setMinScale(chart, 0);
    setInterval(chart, 50000);

    setXAxisTitleProp(chart, "Jour", 50);
    setYAxisTitleProp(chart, "nombre", 50);
    setMainTitle(chart, "Hello", 50);

    setChartData(chart, chartData);
    setChartLabel(chart, day);

    setXAxisLabelFontSize(chart, 25);
    setYAxisLabelFontSize(chart, 25);

    setXAxisLabelDirection(chart, VERTICAL);

    plot(chart);
    saveBarChart(chart, "./barChart.svg");

    freeBarChart(chart);

    // **********
    const double chartData2[] = {-5, -9, -60, -12, -87, -36, -14};
    const char *day2[] = {"03/22", "03/23", "03/24", "03/25", "03/26", "03/27", "03/28"};

    chart = initBarChart(1200, 800, WHITE);

    setMaxScale(chart, 20);
    setMinScale(chart, -100);
    setInterval(chart, 20);

    setChartData(chart, chartData2);
    setChartLabel(chart, day2);

    setXAxisTitleProp(chart, "AAAAA", 20);
    setYAxisTitleProp(chart, "nombre gggg", 50);

    setXAxisLabelFontSize(chart, 25);
    setYAxisLabelFontSize(chart, 25);

    plot(chart);
    saveBarChart(chart, "./barChart2.svg");

    freeBarChart(chart);

    // **********
    const double chartData3[] = {-5, -9, 60, -12, -87, -36, -14};
    const char *day3[] = {"03/22", "03/23", "03/24", "03/25", "03/26", "03/27", "03/28"};

    chart = initBarChart(1200, 800, WHITE);

    setMaxScale(chart, 100);
    setMinScale(chart, -100);
    setInterval(chart, 25);

    setChartData(chart, chartData3);
    setChartLabel(chart, day3);

    setYAxisTitleProp(chart, "nombre", 50);
    setXAxisLabelFontSize(chart, 25);
    setYAxisLabelFontSize(chart, 25);

    plot(chart);
    saveBarChart(chart, "./barChart3.svg");

    freeBarChart(chart);

    // **********
    const double chartData4[] = {-5, -9, -60, -12, -87, -36, -14};
    const char *day4[] = {"03/22", "03/23", "03/24", "03/25", "03/26", "03/27", "03/28"};

    chart = initBarChart(1200, 800, WHITE);

    setMaxScale(chart, 0);
    setMinScale(chart, -100);
    setYAxisTitleProp(chart, "nombre", 50);
    setXAxisTitleProp(chart, "Bonjour hello o", 50);
    setChartData(chart, chartData4);
    setChartLabel(chart, day4);

    setXAxisLabelFontSize(chart, 25);
    setYAxisLabelFontSize(chart, 25);

    plot(chart);
    saveBarChart(chart, "./barChart4.svg");

    freeBarChart(chart);

/*
    const double chartData[] = {5, 9, 60, 12, 87, 36, 14};
    const char *day[] = {"03/22", "03/23", "03/24", "03/25", "03/26", "03/27", "03/28"};

    // initialisation d'un histogramme de largeur 1200, hauteur 800 et de fond blanc
    BarChart *chart = initBarChart(1200, 800, WHITE);

    // définition de l'axe Y
    setMaxScale(chart, 100);
    setMinScale(chart, 0);

    setInterval(chart, 20);
    setXAxisTitleProp(chart, "TITRE AXE X", 25);
    setYAxisTitleProp(chart, "TITRE AXE Y", 50);
    setMainTitle(chart, "TITRE PRINCIPAL", 100);
    setXAxisLabelFontSize(chart, 40);
    setYAxisLabelFontSize(chart, 25);
    setXAxisLabelDirection(chart, VERTICAL);
    setYAxisLabelPrecision(chart, 10);
    setBarColor(chart, 0x003615);

    // définition des données à tracer
    setChartData(chart, chartData);
    setChartLabel(chart, day);

    plot(chart);
    saveBarChart(chart, "./exemple_2.svg");


    freeBarChart(chart);
*/
}
