# DDP-02 : Pâques, des mots et des œufs

Pour ce défi nous allons avoir besoin d'une liste de mots. Je fournis une liste de mots de 5 lettres utilisés dans la francophonie. Ce fichier ne cache aucun «piège», il contient 7823 mots :


* chaque ligne contient exactement un mot
* tous les mots font 5 lettres exactement
* ils sont tous consitutés uniquement de caractères pris parmi ABCDEFGHIJKLMNOPQRSTUVWXYZ
* les mots sont triés par ordre alphabétique

Ce dictionnaire est contenu dans le fichier `FR_len05.dico`

## DDP-02.01 : Motifs - Niveau : débutants

Les œufs de Pâques sont décorés avec des motifs, des motifs que nous allons essayer de découvrir dans les mots.
Nous allons associer à chaque mot de 5 lettres un motif de 4 caractères pris parmis <=\>.
La construction du motif est simple, son caractère en position i sera :


* < si le caractère i en position du mot est inférieur alphabétiquement au caractère en position i+1 du mot
* = si le caractère i en position du mot est identique au caractère en position i+1 du mot
* \> si le caractère i en position du mot est supérieur alphabétiquement au caractère en position i+1 du mot


Par exemple le motif associé au mot **LAPIN** est **><><** car L vient après A dans l'alphabet d'où un \> en première position dans le motif, A précède P dans l'alphabet d'où un < en seconde position dans le motif, P vient après I d'où le \> en troisième position et comme I précède N, le motif finit en <.
De la même manière on trouvera pour le mot **CREEE** le motif **<>==**, un = marquant deux caractères identiques dans le mot.


Le défi consiste dans un premier temps à afficher pour chaque motif possible le nombre de mots ayant ce motif dans le fichiers. Ensuite il faudra afficher:


* le ou les motifs les plus fréquents
* le ou les motifs les moins fréquents mais ayant au moins une occurrence 
* le ou les motifs manquants, ceux qui ne correspondent à aucun mot de la liste


La difficulté principale se situera au niveau de la réflexion. Une piste possible est sans doute de se demander combien de motifs il peut exister et comment associer aisément un motif et un nombre, dans l'optique de stocker des informations dans un tableau.



## DDP-02.02 : Petits sauts - Niveau : débutants et confirmés


Les lapins avancent par petits bonds. On peut aussi sauter d'un mot à un autre, mais uniquement s'ils ne diffèrent que d'une seule lettre. On peut par exemple sauter de **LAPIN** à **LUPIN** (une seule lettre change, la seconde passe de A à U), mais on ne peut pas sauter de **LAPIN** à **MARIN** car deux lettres changent la première (de L à M) et la troisième (de P à R).


Ce second défi va consister à créer un programme en mode console qui va permettre la saisie d'un mot. Que ce mot appartienne ou non à la liste, il devra lister tous les mots de la liste qui sont à un saut de lui. Ce n'est pas la peine de faire une saisie trop complexe, il n'y aura pas de pièges, on pourra supposer qu'on aura toujours un mot de 5 lettres en majuscules. 


Une sortie pourra ressembler à :

```
LAPIN
LAPIN : LADIN LAPIE LAPIS LAPON LATIN LOPIN LUPIN RAPIN SAPIN TAPIN 
OEUFS
OEUFS : KEUFS MEUFS NEUFS PEUFS TEUFS VEUFS 
NANCY
NANCY : FANCY 
FANCY
FANCY : FANNY 
FANNY
FANNY : FANCY 
AAAAA
AAAAA : 
```


Évidemment pour le niveau confirmé il sera demandé d'utiliser une structure de donnée adaptée permettant de ne pas parcourir toutes la liste à chaque demande …


Bonus : Trouver l'entrée qui produit le plus de possibilité de bonds.



## DDP-02.03 : plusieurs bond pour un chemin : confirmés et experts


Pour ce défi il va falloir se frayer un chemin parmi les mots.


Un chemin de mots est simplement une liste de mots du dictionnaire fourni, pour un mot particulier de cette liste son précédant et son suivant sont à un bond de lui comme par exemple dans ce chemin : **CORNE** → **CORSE** → **TORSE** → **TOISE**. Il y a une contrainte supplémentaire, un mot ne peut apparaître qu'une et une seule fois dans un chemin. Par exemple la liste **MARIN** → **TARIN** → **TURIN** → **TURBO** → **TURBO** n'est pas un chemin car **TURIN** n'est pas un mot du dictionnaire, la transition entre **TURIN** et **TURBO** est plus longue qu'un saut et **TURBO** apparaît plus d'une fois.


Ce défi consiste à produire un programme qui va accepter deux mots, s'ils sont tous les deux dans le dictionnaire alors il devra afficher :


* niveau confirmé : un chemin allant de l'un à l'autre, s'il existe
* niveau confirmé ++ : un chemin utilisant le plus petit nombre de bonds de l'un à l'autre, s'il existe
* niveau expert : tous les plus courts chemins de l'un à l'autre, s'ils existent
* niveau expert : un chemin utilisant le plus de bonds de l'un l'autre, s'il existe


Bonus : une manière rapide et simple (sans recherche) pour déterminer si un chemin n'existe pas, …

Super bonus : Une sortie sympa pour aller de **LAPIN** à **OEUFS** (image, source dot, …)
