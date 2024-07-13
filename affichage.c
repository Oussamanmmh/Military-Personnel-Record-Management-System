
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#include "conio.c"
#include <dirent.h>
#include "Display.c"

#define selected_color 0
#define not_selected_color 15
#define not_selected_background 0

void First_Interface ( void )
{
    Clear_Screen();
    textcolor (WHITE);
    printf("\n\n\n\n");
    printf("\t      ");
    printf("     *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *  *   *   *   *   *\n");
    printf("\t      ");
    printf("   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *  *   *   *   *   *\n");
    usleep(40000);
    for ( int i = 1 ; i<=13 ; i++ )
    {
        printf("\t      ");
        printf(" *                                                                                                                                    *\n");
        printf("\t      ");
        printf("   *                                                                                                                                *\n");
        usleep(40000);
    }
    printf("\t     ");
    printf("    *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *     *    *   *   *\n");
    printf("\t     ");
    printf("      *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *    *     *   *   *\n");
    usleep(40000);
    Go_up(26);

    textcolor (GREEN);
    int t=40000;
textcolor (GREEN);printf("\t\t\t ________  _______    ______       ");textcolor (RED);printf("   ______   ________  ______   _______        ");textcolor (WHITE);printf("            ______   __    __  _______  \n");usleep(t);
textcolor (GREEN);printf("\t\t\t/        |/       \\  /      \\    ");textcolor (RED);printf("    /      \\ /        |/      \\ /       \\  ");textcolor (WHITE);printf("                /      \\ /  \\  /  |/       \\ \n");usleep(t);
textcolor (GREEN);printf("\t\t\t$$$$$$$$/ $$$$$$$  |/$$$$$$  |     ");textcolor (RED);printf(" /$$$$$$  |$$$$$$$$//$$$$$$  |$$$$$$$  |      ");textcolor (WHITE);printf(" __       /$$$$$$  |$$  \\ $$ |$$$$$$$  | \n");usleep(t);
textcolor (GREEN);printf("\t\t\t   $$ |   $$ |__$$ |$$____$$ |     ");textcolor (RED);printf(" $$ \\__$$/ $$ |__   $$ \\__$$/ $$ |  $$ |    ");textcolor (WHITE);printf("  /  |      $$ |__$$ |$$$  \\$$ |$$ |__$$ | \n");usleep(t);
textcolor (GREEN);printf("\t\t\t   $$ |   $$    $$/  /    $$/      ");textcolor (RED);printf(" $$      \\ $$    |  $$      \\ $$ |  $$ |    ");textcolor (WHITE);printf("  $$/       $$    $$ |$$$$  $$ |$$    $$/ \n");usleep(t);
textcolor (GREEN);printf("\t\t\t   $$ |   $$$$$$$/  /$$$$$$/       ");textcolor (RED);printf("  $$$$$$  |$$$$$/    $$$$$$  |$$ |  $$ |      ");textcolor (WHITE);printf(" __       $$$$$$$$ |$$ $$ $$ |$$$$$$$/ \n");usleep(t);
textcolor (GREEN);printf("\t\t\t   $$ |   $$ |      $$ |_____      ");textcolor (RED);printf(" /  \\__$$ |$$ |     /  \\__$$ |$$ |__$$ |    ");textcolor (WHITE);printf("  /  |      $$ |  $$ |$$ |$$$$ |$$ |      \n");usleep(t);
textcolor (GREEN);printf("\t\t\t   $$ |   $$ |      $$       |     ");textcolor (RED);printf(" $$    $$/ $$ |     $$    $$/ $$    $$/       ");textcolor (WHITE);printf("$$/       $$ |  $$ |$$ | $$$ |$$ |      \n");usleep(t);
textcolor (GREEN);printf("\t\t\t   $$/    $$/       $$$$$$$$/      ");textcolor (RED);printf("  $$$$$$/  $$/       $$$$$$/  $$$$$$$/        ");textcolor (WHITE);printf("          $$/   $$/ $$/   $$/ $$/       \n");usleep(t);



    Reset();
    textcolor (WHITE);
    printf("\t\t\t\t\t\t           ");
    Animate_str("*************************************************\n\n",30000);
    printf("\t\t\t\t\t\t\t\t     ");
    textcolor (YELLOW);
    Animate_str("TP2 SFSD : Gestion du personnel de l'ANP",30000);
    printf("\n\n");
    printf("\t\t\t\t\t\t\t");
    Animate_str("Nom :",0);
    printf("\n");
    printf("\t\t\t\t\t\t\t");
    Animate_str("Prenom :",0);
    printf("\n");
    Go_up(2);
    printf("\t\t\t\t\t\t\t\t\t\t");
    Animate_str("1-NEMAMCHA",0);
    printf("\n");
    printf("\t\t\t\t\t\t\t\t\t        ");
    Animate_str("1-OUSSAMA",0);
    printf("\n");
    Go_up(2);
    printf("\t\t\t\t\t\t\t\t\t\t\t\t      ");
    Animate_str("2-BECHARAI",0);
    printf("\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t      ");
    Animate_str("2-MOHAMED KHALIL",0);
    printf("\n\n");
    printf("\t\t\t\t\t\t\t\t");
    Animate_str("Groupe :",0);
    printf("               ");
    Animate_str("2CP  G-05",0);
    printf("\n\n");
    printf("\t\t\t\t\t\t\t\t    ");
     textcolor (LIGHTCYAN);
    Animate_str("Encadre par : DR. Kermi Adel",0);
    printf("\n\n");
    printf("\t\t\t\t\t\t\t   ");
    textcolor (WHITE);
    Animate_str("*************************************************",30000);
    printf("\n\n\t\t\t\t\t\t\t\t");
    textcolor (LIGHTCYAN);
    Animate_str("Appuyer sur une touche pour continuer ...",0);
    Reset();
    fflush(stdin);
    getch();
}
int menu(int max, ...)
{
    if (max > 0)
    {

        int choi, a, i, b, d, y;
        char p[50];
        char **choix = NULL;
        choix = malloc(max * sizeof(p));
        va_list marker;
        va_start(marker, max); /* Initialize variable arguments. */
        for (i = 0; i < max; i++)
        {
            choix[i] = va_arg(marker, char *);
        }
        va_end(marker);
        d = wherey();
        y = d;
        textcolor(BLACK);
        textbackground(YELLOW);
        printf("%s\n", choix[0]);
        textbackground(not_selected_background);
        textcolor(not_selected_color);
        for (i = 1; i < max; i++)
        {
            printf("%s\n", choix[i]);
        }
    eticette:
        while ((a = getch()) == 224)
        {
            b = getch();
            if ((b == 80) && (y < d + max - 1))
            {
                gotoxy(1, y);
                textcolor(not_selected_color);
                i = y - d;
                textbackground(not_selected_background);
                printf("%s", choix[i]);
                y++;
                textcolor(BLACK);
                gotoxy(1, y);
                textbackground(YELLOW);
                printf("%s", choix[i + 1]);
            }
            if (b == 72 && y > d)
            {
                gotoxy(1, y);
                textcolor(not_selected_color);
                i = y - d;
                textbackground(not_selected_background);
                printf("%s", choix[i]);
                y--;
                textcolor(BLACK);
                gotoxy(1, y);
                textbackground(YELLOW);
                printf("%s", choix[i - 1]);
            }
        }
        if (a != 13)
            goto eticette;

        choi = y - d;
        textbackground(not_selected_background);
        textcolor(not_selected_color);
        gotoxy(1, d + max);
        return choi + 1;
    }
    else
        return -1;
}
void anp()
{int i;
    Clear_Screen();
    textcolor (YELLOW);
    printf("\n\n\n\n");
    printf("\t      ");
    printf("     *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *  *   *   *   *   *\n");
    printf("\t      ");
    printf("   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *  *   *   *   *   *\n");
    usleep(40000);
    for ( int i = 1 ; i<=13 ; i++ )
    {
        printf("\t      ");
        printf(" *                                                                                                                                    *\n");
        printf("\t      ");
        printf("   *                                                                                                                                *\n");
        usleep(40000);
    }
    printf("\t     ");
    printf("    *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *     *    *   *   *\n");
    printf("\t     ");
    printf("      *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *    *     *   *   *\n");
    usleep(40000);
    Go_up(26);
    int t=40000;
textcolor (GREEN);printf("\t\t\t\t\t\t  ______   __    __  _______               ");/*textcolor (RED)*/;printf("          __                \n");usleep(t);
textcolor (GREEN);printf("\t\t\t\t\t\t /      \\ /  \\  /  |/       \\           ");/*textcolor (RED)*/;printf("            /  |            \n");usleep(t);
textcolor (GREEN);printf("\t\t\t\t\t\t/$$$$$$  |$$  \\ $$ |$$$$$$$  |            ");/*textcolor (RED)*/;printf("      ____$$ | ________     \n");usleep(t);
textcolor (GREEN);printf("\t\t\t\t\t\t$$ |__$$ |$$$  \\$$ |$$ |__$$ |            ");/*textcolor (RED)*/;printf("     /    $$ |/        |    \n");usleep(t);
textcolor (GREEN);printf("\t\t\t\t\t\t$$    $$ |$$$$  $$ |$$    $$/              ");/*textcolor (RED)*/;printf("   /$$$$$$$ |$$$$$$$$/      \n");usleep(t);
textcolor (RED);printf("\t\t\t\t\t\t$$$$$$$$ |$$ $$ $$ |$$$$$$$/               ");/*textcolor (RED)*/;printf("   $$ |  $$ |  /  $$/       \n");usleep(t);
textcolor (WHITE);printf("\t\t\t\t\t\t$$ |  $$ |$$ |$$$$ |$$ |           ");/*textcolor (WHITE)*/;printf("  __    ");textcolor (WHITE);printf("   $$ \\__$$ | /$$$$/__     \n");usleep(t);
textcolor (WHITE);printf("\t\t\t\t\t\t$$ |  $$ |$$ | $$$ |$$ |           ");/*textcolor (WHITE)*/;printf(" /  |   ");textcolor (WHITE);printf("   $$    $$ |/$$      |     \n");usleep(t);
textcolor (WHITE);printf("\t\t\t\t\t\t$$/   $$/ $$/   $$/ $$/            ");/*textcolor (WHITE)*/;printf(" $$/    ");textcolor (WHITE);printf("    $$$$$$$/ $$$$$$$$/      \n");usleep(t);

textcolor(YELLOW);printf("\n\t\t\t\t\t\tGestion du personel de l'armee national\n");
                         }


int main1()
{
 ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
//First_Interface();
int choix=0;

while(choix!=7)
{
 system("cls||clear");
 anp();
printf("\n\n\n\n\n");

 choix=menu(7,
                    "\t\t\t\t\t\t\t1>Generer un nouveau fichier ' PERSONNEL-ANP_DZ.dat '",
                    "\t\t\t\t\t\t\t2>Recherche d'un Militant par matricule",
                    "\t\t\t\t\t\t\t3>Suppression d'un Militant par matricule",
                    "\t\t\t\t\t\t\t4>Insertion d'un nouveau Militant",
                    "\t\t\t\t\t\t\t5>Recherche a intervalle",
                    "\t\t\t\t\t\t\t6>Affichage du fichier'PERSONNEL-ANP_DZ.dat'",
                    "\t\t\t\t\t\t\t7>Quitter le programme");
       switch(choix)
       {
       case 1:
           system("cls||clear");
           int n;
           textcolor(YELLOW);
           printf("\n\n");
           printf("veuillez entrer la taille du fichier(entre 1 et 100000)");
           scanf("%d",&n);
           while(n<1 || n>100000)
           {
               textcolor(RED);
               printf("[ERROR] entrez un nombreentre 1 et 100000 svp!");
               scanf("%d",&n);

           }
           textcolor(YELLOW);
          printf("La generation du fichier peut prendre du temps veuillez patienter\n") ;
         ///chargement_initiale( &f , &ind , n );
       //  printf("nb_totale du personel=%d   nb de blocsutiliser %d ")
        break;

                    }

}



/// menu principale


}
