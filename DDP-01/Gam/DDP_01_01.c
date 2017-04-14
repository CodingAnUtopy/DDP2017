#include <stdio.h>
int conway(int annee);


int		conway(int annee)
{
	int s = 0;
	int t = 0;
	int a = 0;
	int p = 0;
	int jps = 0;
	int jp = 0;
	int g = 0;
	int G = 0;
	int b = 0;
	int r = 0;
	int C = 0;
	int d = 0;
	int h = 0;
	int e = 0;
	int f = 0;
	int R = 0;

	s = annee / 100;
	t = annee % 100;

	a = t / 4;

	p = s % 4;

	jps = (9 - 2 * p) % 7;

	jp = (jps + t + a) % 7;

	g = annee % 19;

	G = g + 1;

	b = s / 4;

	r = ( 8 * (s + 11) ) / 25;

	C = -s + b + r;

	d = (11 * G + C) % 30;

	d = (d + 30) % 30;

	h = (551 - 19 * d + G) / 544;

	e = (50 - d - h)  % 7;

	f = (e + jp) % 7;

	R = 57 - d - f - h;

	return (R);
}


int		main(void)
{
	int annee = 2001;
	int quantieme = 0;

	while (annee <= 2100)
	{
		quantieme = conway(annee);

		if (quantieme <= 31)
			printf("%d/03/%0*d\n", annee, 2, quantieme);

		else
			printf("%d/04/%0*d\n", annee, 2, quantieme - 31);

		annee++;
	}
	
	return (0);
}