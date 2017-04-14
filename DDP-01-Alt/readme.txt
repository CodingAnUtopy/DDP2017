Voici ma version du défi. Enfin, de ma version du défi.

Sujet : calculer et afficher toutes les dates de Pâques du XXIème siècle (selon le rite romain, calendrier grégorien). La sortie attendue du programme est la liste des dates de Pâques entre le 01/01/2001 et le 31/12/2100 par ordre croissant, une date par ligne, la date présentée au format YYYY/MM/DD avec YYYY l'année, MM le mois sur 2 position et DD le quantième du mois sur 2 positions. MM et DD seront préfixés par un 0 s'ils sont inférieurs à 10.

Contrainte supplémentaire : il faut réaliser ce programme sans utiliser d'algorithme tout fait. Il faut donc tout réinventer.

Pour que cela soit possible, on utilisera une « définition astronomique » de la date de Pâques : c'est le dimanche qui suit la première pleine lune après l'équinoxe de printemps. Cette définition ne coïncide pas tout à fait avec la définition adoptée au concile de Nicée, on pourra d'ailleurs le mettre en évidence en examinant la sortie du programme.

1/ MES FICHIERS

Mon envoi est constitué de plusieurs fichiers :
    ‒ "readme.txt" : ce texte
    ‒ "paq.txt" : un fichier texte dans lequel j'explique ma démarche. Je l'ai écrit en temps réel en même temps que je réalisais le programme.
    ‒ "dates.h" et "dates.c" : fonctions liées à la gestion des dates.
    ‒ "astro.h" et "astro.c" : foncitons de calcul des équinoxes et pleines lunes.
    ‒ "paq.c" : le programme principal.
    ‒ "tests.c" : un programme de test de mes fonctions. Je ne l'envoie que pour montrer comment je procède pour tester mes fonctions au fur et à mesure que je les écris, ce qui évite d'avoir de grosses erreurs (donc pas la peine de le compiler !).

Je les ai mis chez "pastebin" aux adresses suivantes :

    "paq.txt" : https://pastebin.com/Vs9HQSvB
    "dates.h" : https://pastebin.com/JWvYPfe1
    "dates.c" : https://pastebin.com/WRxGREVX
    "astro.h" : https://pastebin.com/YN2D3456
    "astro.c" : https://pastebin.com/LsPUCRGv
    "paq.c"   : https://pastebin.com/LYgQnrcB
    "tests.c" : https://pastebin.com/3wPX4pQm

(Tu as parlé de dépôt git, je ne sais pas ce que c'est.)

Je n'ai pas fait de fichier "make" car je ne sais pas comment on fait (je m'étais intéressé à la question à une époque mais j'ai tout oublié.)

Pour compiler le programme de défi avec gcc (par exemple) :

> gcc paq.c dates.c astro.c -o executable

Avec les options -Wall -Wextra -pedantic -std=gnu11, je n'ai ni erreur ni warning.

2/ COMMENTAIRES

J'ai réalisé ce défi en pensant en permanence à toutes les discussions, et notamment demandes d'aide, lues sur le forum. C'est pour cette raison que j'ai ajouté des fichiers annexes. Je me souviens d'un participant qui n'arrivait pas à faire son TP parce qu'il avait commencé à coder au lieu de se poser des questions. J'avais essayé de lui expliquer la démarche descendante et comment imaginer des fonctions à chaque étape de la « descente ». Le fichier "paq.txt" en est une illustration.

Je suis un « programmeur du dimanche » et j'ai appris le C seul (à la fac on m'a toutefois enseigné le Pascal et le Fortran). Il y a plein de choses que je ne sais pas faire en C. Ne pas l'oublier lors de l'évaluation !

J'ai trouvé vraiment intéressant de modifier le sujet de départ. Intéressant d'un point de vue de programmation, bien sûr, car il a fallu refaire le bon vieil exercice classique « calculer le nombre de jours écoulés entre telle et telle date » (qui m'avait fait m'arracher les cheveux lors de mes cours de Pascal ‒ ici moins car je me suis contenté de dates juliennes et non grégoriennes). Un truc intéressant, par exemple, c'est d'utiliser un pointeur pour travailler sur un tableau que je ne connais pas à l'avance (lignes 73 et 83 de "dates.c"). Il a fallu aussi réviser les formats de 'printf' (mais je les connaissais).

C'était intéressant aussi d'un point de vue de culture générale, car ça m'a appris que la définition de Pâques n'est pas purement astronomique comme je le croyais, de sorte que mon programme n'est pas exact pour certaines années. J'ai appris aussi que la durée entre deux équinoxes de printemps est légèrement irrégulière (je ne m'y attendais pas), et que la durée entre deux pleines lunes est nettement irrégulière (je le craignais), de sorte que ma méthode est très approximative.

Personnellement, c'est ça qui me stimule, plus que chercher des algorithmes casse-tête comme dans certains sujets du défi de Noël ou de Pâques. Peut-être justement parce que je ne suis pas un pro, que je programme juste pour mes loisirs ?

D'ailleurs je me permets une petite remarque : je trouve dommage que les défis soient si stricts, qu'ils ne prévoient pas un peu de liberté comme je me suis permis d'en prendre en modifiant le sujet à ma sauce. Ça bride l'imagination et la créativité... (j'y vais un peu fort ?). On aurait pu imaginer un sujet comme « faites un programme en rapport avec la date de Pâques ». Oui, c'était un peu trop vague. Mais on pourrait définir un sujet qui soit situé à mi-chemin du trop vague et du trop strict, non ?

J'espère que tu auras le temps de regarder ce que je fais et d'en faire quelques commentaires. Avec tout ces fichiers, j'imagine que je t'apporte beaucoup de boulot. Mais il n'y a pas eu trop de participants...

En tout cas, merci pour l'idée du défi ! Je ne regrette pas d'y avoir participé, même si c'était à ma façon...