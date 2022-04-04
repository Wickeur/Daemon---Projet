#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

/*Projet de Julian Wicke et Thomas Lyautey*/

void state()
{
    if (access("monFifo.lnk", F_OK) != -1)
    {
        printf("Le deamon est en vie");
    }
    else
    {
        printf("Aucun deamon à l'horizon");
    }
}

int main(int argc, char **argv) // argc = varaible nb d'élément et argv = la variable
{
    // Communiquer (ouverture en écriture)
    int fd;
    FILE *fp;
    char *nomfich = "monFifo"; /* nom du fichier */

    fd = open(nomfich, O_WRONLY); /* ouverture en écriture */
    fp = fdopen(fd, "w");         /* ouverture du flot */

    //  Démarrer le daemon (--start)
    if (strcmp(argv[1], "--start") == 0) // strcmp = comparer les chaines de caractère et retourne 0 si c'est la même chose
    {
        execl("./daemon", "./daemon", NULL);
    }

    // Obtenir une aide sur l’utilisation de votre programme (--help)
    if (strcmp(argv[1], "--help") == 0)
    {
        fprintf(fp, "%s", argv[1]);
    }

    // Connaitre l’heure (--date)
    if (strcmp(argv[1], "--date") == 0)
    {
        fprintf(fp, "%s", argv[1]);
    }

    // La durée depuis le lancement (--duration)
    if (strcmp(argv[1], "--duration") == 0)
    {
        fprintf(fp, "%s", argv[1]);
    }

    // Remettre à zéro le « chronomètre » (--reset).
    if (strcmp(argv[1], "--reset") == 0)
    {
        fprintf(fp, "%s", argv[1]);
    }

    // Connaitre l’état du daemon (vivant, mort) (--state)
    if (strcmp(argv[1], "--state") == 0)
    {
        state();
    }

    // Eteindre le daemon (--stop)
    if (strcmp(argv[1], "--stop") == 0)
    {
        fprintf(fp, "%s", argv[1]);
    }

    // Redémarrer le daemon (arrête le daemon puis le relancer) (--restart).
    if (strcmp(argv[1], "--restart") == 0)
    {
        fprintf(fp, "%s", argv[1]);
    }

    unlink(nomfich); /* fermeture du tube */
    fclose(fp);

    if (strcmp(argv[1], "--restart") == 0)
    {
        execl("./daemon", "./daemon", NULL);
    }

    return 0;
}
