#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#define TAILLE_MAX 1000

/*Projet de Julian Wicke et Thomas Lyautey*/

void help()
{
    FILE *fichier = NULL;
    char chaine[TAILLE_MAX] = "";
    fichier = fopen("help.txt", "r");

    if (fichier != NULL)
    {
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            printf("%s\n", chaine); // On affiche la chaîne qu'on vient de lire
        }

        fclose(fichier);
    }
}

void date()
{
    int h, min, s, day, mois, an;
    time_t now;

    // Renvoie l'heure actuelle
    time(&now);
    // Convertir au format heure locale
    // printf("Aujourd'hui est : %s", ctime(&now));
    struct tm *local = localtime(&now);

    h = local->tm_hour;
    min = local->tm_min;
    s = local->tm_sec;
    day = local->tm_mday;
    mois = local->tm_mon + 1;
    an = local->tm_year + 1900;

    // Affiche l'heure actuelle
    printf("L'heure : %02d:%02d:%02d\n", h, min, s);
    // Afficher la date courante
    printf("La date : %02d/%02d/%d\n", day, mois, an);
}

void duration(time_t begin)
{
    time_t now = time(NULL);
    printf("Duree : %lf\n", difftime(now, begin));
}

int main()
{
    printf("Un deamon sauvage apparait !!!\n");

    time_t begin = time(NULL);

    int est_vivant = 0;
    while (est_vivant == 0)
    {
        // Communiquer (ouverture en écriture)
        int fd;
        FILE *fp;
        char *nomfich = "monFifo", chaine[50];
        if (mkfifo(nomfich, 0644) != 0) /* création du fichier */
        {
            perror("Problème de création du noeud de tube");
            exit(1);
        }
        fd = open(nomfich, O_RDONLY); /* ouverture du tube */
        fp = fdopen(fd, "r");         /* ouverture du flot */
        fscanf(fp, "%s", chaine);     /* lecture dans le flot */

        // Obtenir une aide sur l’utilisation de votre programme (--help)
        if (strcmp(chaine, "--help") == 0)
        {
            help();
        }

        // Connaitre l’heure (--date)
        if (strcmp(chaine, "--date") == 0)
        {
            date();
        }

        // Remettre à zéro le « chronomètre » (--reset).
        if (strcmp(chaine, "--reset") == 0)
        {
            begin = time(NULL);
            printf("Le chronomètre a été remis à zéro\n");
        }

        // La durée depuis le lancement (--duration)
        if (strcmp(chaine, "--duration") == 0)
        {
            duration(begin);
        }

        if (strcmp(chaine, "--stop") == 0 || strcmp(chaine, "--restart") == 0)
        {
            est_vivant = 1;
            printf("Le deamon n'est plus !!!\n");
        }

        unlink(nomfich); /* fermeture du flot */
    }

    return 0;
}

// faire des puts et non des printf