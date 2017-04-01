cf https://openclassrooms.com/forum/sujet/defi-de-paques-2017-partie-1

# Défi de Pâques 2017 - Partie 1

## DDP-01 : Pâques, calendrier et stats
 Les dates de Pâques considérées sont celles du rite romain en utilisant le calendrier grégorien.

### DDP-01.01 : Calcul des dates - Niveau : Débutant
Le sujet est simple : il faut calculer et afficher toutes les dates de Pâques du XXIème siècle (selon le rite romain, calendrier grégorien). La sortie attendue du programme est la liste des dates de Pâques entre le 01/01/2001 et le 31/12/2100 par ordre croissant, une date par ligne, la date présentée au format YYYY/MM/DD avec YYYY l'année, MM le mois sur 2 position et DD le quantième du mois sur 2 positions. MM et DD seront préfixés par un 0 s'ils sont inférieurs à 10.

Voici, en exemple, le début du fichier attendu :
```
2001/04/15
2002/03/31
2003/04/20
2004/04/11
2005/03/27
2006/04/16
2007/04/08
2008/03/23
2009/04/12
2010/04/04
...
```

Difficultés : la plus grande difficulté est sans doute de trouver un algorithme (et il y en a plusieurs) puis de l'implémenter (cf wikipedia ?). Comprendre l'algorithme n'est pas nécessaire pour réussir ce challenge. Une petite difficulté pour les grands débutants : le maniement de printf pour forcer l'affichage du 0 … rien d'insurmontable grâce aux pages de manuels :)

### DDP-01.02 : Stats sur les dates - Niveau : Confirmé
Dans cette partie on va essayer d'établir quelques Fun Facts sur les dates de Pâques au XXIème siècle.
Connaissant les dates il va falloir afficher :

* la date (MM/DD) et les années (YYYY) pour lesquelles Pâques tombe au plus tôt
* la date (MM/DD) et les années (YYYY) pour lesquelles Pâques tombe au plus tard
* les dates (MM/DD) les plus fréquentes et les années (YYYY) concernées sachant que la date de Pâques ne peut tomber qu'entre le 03/22 et le 04/25, les dates (MM/DD) comprises entre ces bornes pour lesquelles Pâques ne tombera pas au XXIème siècle.

Difficultés : sans doute bien concevoir les structures de donnée …

### DDP-01.03 : Vers l'infini et au-delà - Niveau : Confirmé entêté et documenté
Les dates de Pâques suivent un cycle de 5 700 000 ans. Cette dernière partie va simplement consister à obtenir les fréquence des dates de Pâques sur cette période. Rien de bien compliqué, mais le programme devra créer une sortie au format SVG qui représentera un histogramme des fréquences. Cette sortie, une fois affichée dans un viewer, pourra ressembler à :

![Fréquences date de Pâques sur un cycle](http://nc233.com/wp-content/uploads/2016/11/graphe_date_paques.png)

Rien ne vous empêche d'être plus créatifs ou plus artistiques … l'exemple manque cruellement du couleurs …

La difficulté principale va résider ici à produire la sortie au format SVG sans utiliser de bibliothèque externe. Il va donc falloir lire la doc … mais je vous rassure ce n'est pas bien compliqué, ce n'est qu'un format texte … ou presque.
Si cela vous fait trop peur alors vous pouvez vous rabattre sur un affichage en mode texte en considérant que ma console a au moins 80 colonnes et 40 lignes.

## Fichiers

À la racine du dépôt se trouvent :

* ddp-01.01.expected      : sortie attendue du programme de la partie DDP-01.01
* ddp-01.02.expected      : exemple de sortie du programme de la partie DDP-01.02
* ddp-01.03.freq.expected : fréquences des dates de Pâques sur un cycle pour vérification
* ddp-01.03.expected.svg  : example de sortie du programme de la partie DD-01.03
