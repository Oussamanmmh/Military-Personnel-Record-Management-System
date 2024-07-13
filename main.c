#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "affichage.c"
#define nb_wilayas 59// on utilise pas la case 0 (indice=num_wilayas)
#define max 1024

/** TP REALISEE PAR BECHARAI MOHAMED KHALIL ET NEMAMCHA OUSSAMA
    2CP G05
    */


int db;

typedef struct
{
    int matricule;// entre 111111 et 999999
    char nom[30];
    char prenom[30] ;
    char date_naissance[13];// format jj/mm/aaaa
    char Wilaya_Naissance[50];
    char Groupe_Sanguin[4];
    char Grade[50];
    char Force_Armee[50];
    char Region_militaire[50];


}tenrg;

typedef struct
{
    int nb;
    tenrg tab[max];
}tbloc_T_OF;
typedef struct
{
  int nb_bloc;

}entete_T_OF;

typedef struct
{
    entete_T_OF entete;
    FILE *fichier;
}T_OF;

typedef struct
{
    int num_bloc;
    int dep;

}T_couple;
typedef struct
{
  int matricule;
  T_couple adr;


}ind_enrg;// enregistrement du fichier index

typedef struct
{
    int nb;
    ind_enrg tab[8192];
}ind_bloc;// declaration du bloc du fichier index
typedef struct
{
    int nb_bloc;
}entete_ind;//entete du fichier index
typedef struct
{
    FILE *ind_file;
    entete_ind entete;
}ind_TOF;// fichier index



 const char *wilayas[nb_wilayas] = {
       " ", "Adrar", "Chlef", "Laghouat", "Oum El Bouaghi", "Batna", "Bejaia",
        "Biskra", "Bechar", "Blida", "Bouira", "Tamanrasset", "Tebessa",
        "Tlemcen", "Tiaret", "Tizi Ouzou", "Alger", "Djelfa", "Jijel",
        "Setif", "Saida", "Skikda", "Sidi Bel Abbes", "Annaba", "Guelma",
        "Constantine", "Medea", "Mostaganem", "M'Sila", "Mascara", "Ouargla",
        "Oran",       "El Bayadh", "Illizi", "Bordj Bou Arreridj", "Boumerdes",
        "El Tarf", "Tindouf", "Tissemsilt", "El Oued", "Khenchela", "Souk Ahras",
        "Tipaza", "Mila", "Ain Defla", "Naama", "Ain Temouchent", "Ghardaia",
        "Relizane","Timimoun","Bordj Badji Mokhtar","Ouled Djellal","Beni Abbes",
        "Ain Salah","Ain Guezzam","Touggourt","Djanet","El M'Ghair","El Meniaa"
    };
  const  char *grades[19] = {
    "General d'Armee","General de corps d'armee","General-Major","General",
    "Colonel","Lieutenant-colonel","Commandant","Capitaine","Lieutenant",
    "Sous-lieutenant","Aspirant","Adjudant-Major","Adjudant-Chef","Adjudant",
    "Sergent-Chef","Sergent","Caporal-Chef","Caporal","Djoundi"
};
const char *branches[8] = {
    "Armee de terre",
    "Armee de l'air",
    "Marine nationale",
    "Difense aerienne du territoire",
    "Gendarmerie nationale",
    "Garde republicaine",
    "Departement du renseignement et de la securite",
    "Sante militaire"
};
 const char *regions[6] = {
    "1RM-Blida",
    "2RM-Oran",
    "3RM-Bechar",
    "4RM-Ouargla",
    "5RM-Constantine",
    "6RM-Tamanrasset"
};
 const char *groupesSanguins[8] = {
    "O+",
    "A+",
    "B+",
    "O-",
    "A-",
    "AB+",
    "B-",
    "AB-"
};
////////////////////////////////////////////////// Variables Globales///////////////////////////////////////////////////
int nb_engr_ind;
int cout_op;// le cout d'une opération


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LireDir(T_OF F, int i, tbloc_T_OF* Buf) {
    int x=fseek(F.fichier, (i - 1) * sizeof(tbloc_T_OF) + sizeof(entete_T_OF), SEEK_SET);
    if (F.fichier == NULL || i <= 0 || x != 0) {
       printf("lecture impossible x=%d  i=%d  \n",x,i);sleep(5);
        return false;
    }

    if (fread(Buf, sizeof(tbloc_T_OF), 1, F.fichier) != 1) {
        return false;  // Check if the read was successful
    }
    cout_op++;
    return true;
}
//////////////////////////////////////////////////////
char* genererChaineAleatoire() {
    const char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
    int longueurMin = 4;
    int longueurMax = 10;


    int longueur = rand() % (longueurMax - longueurMin + 1) + longueurMin;


    char* chaine = (char*)malloc((longueur + 1) * sizeof(char));


    for (int i = 0; i < longueur; ++i) {
        int indice = rand() % 26;
        chaine[i] = alphabet[indice];
    }


    chaine[longueur] = '\0';

    return chaine;
}

bool EcrireDir(T_OF F, int i, tbloc_T_OF* Buf)
 {
    int x=fseek(F.fichier, (i - 1) * sizeof(tbloc_T_OF) + sizeof(entete_T_OF), SEEK_SET);
    if (F.fichier == NULL || i <= 0 || x != 0) {
       printf("ecriture impossible x=%d  i=%d  \n",x,i);sleep(5);
        return false;
    }

    if (fwrite(Buf, sizeof(tbloc_T_OF), 1, F.fichier) != 1) {
        return false;  // Check if the write was successful
    }
    cout_op++;
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void fermer(T_OF *f)
{
    rewind(f->fichier);
    fwrite(&(f->entete), sizeof(entete_T_OF), 1, f->fichier); // sauvegarder l'entete dans le fichier (bloc 0)
    fclose(f->fichier);
}
void fermer_ind(ind_TOF *f)
{
    rewind(f->ind_file);
    fwrite(&(f->entete), sizeof(entete_T_OF), 1, f->ind_file); // sauvegarder l'entete dans le fichier (bloc 0)
    fclose(f->ind_file);
}
void aff_entete(T_OF *f,int num,int val)
{
    if(num==1)
    {
        f->entete.nb_bloc=val;
    }else
    {
        printf("ERROR!! ce champs n'existe pas");
    }
}
int entete(T_OF *f,int num)
{
  if(num==1)
    {
       return f->entete.nb_bloc;
    }else
    {
        printf("ERROR!! ce champs n'existe pas");
        return -1;
    }
}

void ouvrir(T_OF *f , char nom[] , char mode)
{
    if(mode == 'n' || mode=='N')
    {
        f->fichier = fopen(nom,"wb+");

        f->entete.nb_bloc=0;

    }else if(mode=='a' || mode=='A')

    {

      f->fichier = fopen(nom,"rb+");

      fread(&(f->entete),sizeof(entete_T_OF),1,f->fichier);

      rewind(f->fichier);

    }
}
bool EcrireDir_ind(ind_TOF F, int i, ind_bloc *Buf)
{
    int x = fseek(F.ind_file, (i - 1) * sizeof(ind_bloc) + sizeof(entete_ind), SEEK_SET);
    if (F.ind_file == NULL || i <= 0 || x != 0)
    {
        printf("ecriture impossible x=%d  i=%d  \n", x, i);
        sleep(5);
        return false;
    }

    if (fwrite(Buf, sizeof(ind_bloc), 1, F.ind_file) != 1)
    {
        return false; // Check if the write was successful
    }

    return true;
}
 ////////////////////////////////////////////////////////////////////////////////////
////////////////// /////////////////////// /
bool LireDir_ind(ind_TOF F, int i, ind_bloc *Buf)
{
    int x = fseek(F.ind_file, (i - 1) * sizeof(ind_bloc) + sizeof(entete_ind), SEEK_SET);
    if (F.ind_file == NULL || i <= 0 || x != 0)
    {
        printf("lecture impossible x=%d  i=%d  \n", x, i);
        sleep(5);
        return false;
    }

    if (fread(Buf, sizeof(ind_bloc), 1, F.ind_file) != 1)
    {
        return false; // Check if the read was successful
    }

    return true;
}
void ouvrir_ind(ind_TOF *f, char nom[], char mode)
{
    if (mode == 'n' || mode == 'N')
    {
        f->ind_file = fopen(nom, "wb+");

        f->entete.nb_bloc = 0;
    }
    else if (mode == 'a' || mode == 'A')

    {

        f->ind_file = fopen(nom, "rb+");

        fread(&(f->entete), sizeof(entete_T_OF), 1, f->ind_file);

        rewind(f->ind_file);
    }
}

//////////////////////////////////////////////////// MODULES DU GENERATION   ///////////////////////////////////////////////////////////////
int aleatoire(int a , int b ){
	return rand() % (b - a + 1) + a;

}




int gnr_matricule( )
{

     return  rand() % (999999 - 111111 + 1) + 111111;



}// fonction qui genere aleatoirement des matricule compris entre 111111 et 999999








int estBissextile(int annee)// renvoi si une année est bissextile ou non
 {
    return (2024-annee)%4;
}
bool date_valide(int jj,int mm,int aa)// cette fonction renvoi si une date donnée est valide ou non
{
  static char date[13]; // Tableau statique pour stocker la date (12 caractères + le caractère nul)


    if(aa<1942 || aa>2005)
    {
        return false;
    }



    if(mm<1 || mm>12)
    {
        return false;
    }

    if(jj<1)
    {
        return false;
    }
    switch (mm)
    {
    case 2:
        if (estBissextile(aa)==0)

        {
            if(jj>29)
            {
                return false;
            }
        }
        else
        {
           if(jj>28)
            {
                return false;
            }
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:

           if(jj>30)
            {
                return false;
            }
        break;
    default:

           if(jj>31)
            {
                return false;
            }
        break;
    }


    return true;
}


char* genererDateNaissance()// cette fonction genere un date de naissace aleatoire
 {
    static char date[13];


    int annee = rand() % (2005 - 1942 + 1) + 1942;


    int mois = rand() % 12 + 1;


    int jour;
    switch (mois) {
        case 2:
            if (estBissextile(annee)) {
                jour = rand() % 29 + 1;
            } else {
                jour = rand() % 28 + 1;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            jour = rand() % 30 + 1;
            break;
        default:
            jour = rand() % 31 + 1;
            break;
    }


    snprintf(date, sizeof(date), "%02d/%02d/%04d", jour, mois, annee);

    return date;
}

void rech_dicho(ind_enrg ind[],int matricule,bool *trouve,int *k)// cette procedure recherche un matricule donnee dans la table d'index
{
 int bi=0,bs=nb_engr_ind-1;
*trouve=false;
while(!*trouve && bi<=bs)
{
    *k=(bs+bi)/2;
    if(ind[*k].matricule==matricule)
    {
        *trouve=true;
   db++;
    }else
    {
        if(matricule>ind[*k].matricule)
        {
            bi=*k+1;
        }else
        {
            bs=*k-1;
        }
    }
}
if(!*trouve)
    *k=bi;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


tenrg alea_engr()//cette fonction genere un enregistrement aleatoire
{
 tenrg e;
strcpy(e.Groupe_Sanguin,groupesSanguins[rand()%8]);
strcpy(e.nom,genererChaineAleatoire());
strcpy(e.prenom,genererChaineAleatoire());
strcpy(e.date_naissance,genererDateNaissance());
strcpy(e.Wilaya_Naissance,wilayas[aleatoire(1,58)]);
strcpy(e.Grade,grades[rand()%19]);
strcpy(e.Force_Armee,branches[aleatoire(0,7)]);
strcpy(e.Region_militaire,regions[aleatoire(0,5)]);
e.matricule=(99*rand()+rand()+4*rand()) %  (999999 - 111111 + 1) + 111111;

return e;
}
void affiche_enrg(tenrg e)// cette procedure affiche un enregistrement donnee
{
  textcolor(YELLOW);printf("%d : ",e.matricule); textcolor(WHITE); printf("%s | %s | %s | %s | %s | %s | %s | %s \n",e.nom,e.prenom,e.date_naissance,e.Wilaya_Naissance,e.Groupe_Sanguin,e.Grade,e.Force_Armee,e.Region_militaire);
}
void sauv_ind_fich(ind_TOF *f, ind_enrg ind[100001])// cette procedure sauvgarde la table d'index dans le fichier d'index
{
    ind_bloc buf;
    int i, j = 0, b = 1;

    for (i = 0; i < nb_engr_ind; i++)
    {
        if (j < 8192)
        {
            buf.tab[j] = ind[i];
            j++;
        }
        else
        {
            buf.nb = j;
            EcrireDir_ind(*f, b, &buf);
            b++;
            buf.tab[0] = ind[i];
            j = 1;
        }
    }

    buf.nb = j;
    EcrireDir_ind(*f, b, &buf);

    f->entete.nb_bloc = b;
}
//////////////////////////////////////////////////////////////////////////////////////////
void chargement_ind(ind_enrg *ind, ind_TOF f)// cette procedure charge la table d'index à partir du fichier d'index
{
    ind_bloc buf;
    int i, j;
    int c = 0;



    for (i = 1; i <= f.entete.nb_bloc; i++)
    {
        if (LireDir_ind(f, i, &buf))
        {
            for (j = 0; j < buf.nb; j++)
            {
                ind[c] = buf.tab[j];

                c++;
            }
        }
        else
        {
            // Gérer l'erreur de lecture
            printf("Erreur de lecture du bloc %d\n", i);
            break;
        }
    }

    nb_engr_ind = c;
}
void chargement_initiale(T_OF *f , ind_enrg *ind , int n  )// cette procedure genere un fichier de taille n avec des donnée aleatoires
 {
    tbloc_T_OF buf ;
    tenrg e ;
    bool trouv ;
    FILE *f1 = f->fichier ;

    int i = 1 , j=0 ,k1;
    for (int k = 0 ; k< n ; k++)
    {
        trouv = true ;
        e=alea_engr();
        while (trouv)
        {
            e.matricule =(99*rand()+rand()+4*rand()) %  (999999 - 111111 + 1) + 111111;
            rech_dicho(ind,e.matricule,&trouv,&k1);

        }
        if (j<max)
            {
                buf.tab[j]= e ;
                j++ ;


            }
            else
            {
                buf.nb= j ;
                EcrireDir(*f, i , &buf) ;
                buf.tab[0] = e;
                i++;
                j=1;

            }


        int i1 ;
        for ( i1 = nb_engr_ind-1 ; i1 >= k1 ; i1--)
        {
            ind[i1+1] = ind[i1] ;

        }
        ind[k1].matricule = e.matricule ;
        ind[k1].adr.num_bloc = i ;
        ind[k1].adr.dep= j-1 ;

        nb_engr_ind++;

    }

    buf.nb=j ;
    EcrireDir(*f, i, &buf  ) ;
     f->entete.nb_bloc = i ;


 }



void suppr(T_OF *f,ind_enrg  *ind,int matricule,bool *supprime)// cette procedure permet de supprimer un enregistrement
{                                                              // donnée physiquement en modifiant aussi la table d'index

    tbloc_T_OF buf ;
    tenrg e ;
    int k,i,k1;
    bool trouve ;
    rech_dicho(ind,matricule,&trouve,&k);
    if(trouve)
    {
        LireDir(*f,f->entete.nb_bloc,&buf);
        e=buf.tab[buf.nb-1];
        buf.nb--;
        if(buf.nb==0)
        {
            f->entete.nb_bloc--;
        }else
        {
            EcrireDir(*f,f->entete.nb_bloc,&buf);
        }
         LireDir(*f,ind[k].adr.num_bloc,&buf);
         affiche_enrg(buf.tab[ind[k].adr.dep]);
         buf.tab[ind[k].adr.dep]=e;
         rech_dicho(ind,e.matricule,&trouve,&k1);
         ind[k1].adr=ind[k].adr;
          EcrireDir(*f,ind[k].adr.num_bloc,&buf);
          *supprime=true;
          for(i=k;i<nb_engr_ind-1;i++)
          {
              ind[i]=ind[i+1];
          }
          nb_engr_ind--;
    }else
    {
        *supprime=false;
    }
}
void mod_region(T_OF *f,int matricule,ind_enrg ind[],int nv_region,bool *modif)// cette procedure permet de modifier la region
{                                                                              // militaire d'un enregistrement donnée
    int k;
    bool trouve;
    tbloc_T_OF buf;
  rech_dicho(ind,matricule,&trouve,&k);
  if(trouve && nv_region<6)
  {
      LireDir(*f,ind[k].adr.num_bloc,&buf);
      strcpy(buf.tab[ind[k].adr.dep].Region_militaire,regions[nv_region]);
      EcrireDir(*f,ind[k].adr.num_bloc,&buf);
      *modif=true;
  }else
  {
      *modif=false;
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rech_bl(ind_enrg tab[],int n,int  bl,int *k,bool *trouve)// faire une rechrche dichotomique
{                                                              // dans le tableau tab sur le champ bloc

int bi=0,bs=n-1;
*trouve=false;
while(!*trouve && bi<=bs)
{
    *k=(bs+bi)/2;
    if(tab[*k].adr.num_bloc==bl)
    {
        *trouve=true;
    }else
    {
        if(bl>tab[*k].adr.num_bloc)
        {
            bi=*k+1;
        }else
        {
            bs=*k-1;
        }
    }
}
if(!*trouve)
    *k=bi;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void requette_intervalle(T_OF f,int m1,int m2,ind_enrg ind[])// cette procedure affiche tous les enregistrement que leurs matricule
{                                                            //est entre M1 et M2
ind_enrg tab[10000];
//int tab1[100000];
int nb_elm_tab=0;
bool trouve;
int i,j,k;
tbloc_T_OF buf;

rech_dicho(ind,m1,&trouve,&i);
if(i<nb_engr_ind)
{
    while(ind[i].matricule <= m2 && i<nb_engr_ind)
    {
        rech_bl(tab,nb_elm_tab,ind[i].adr.num_bloc,&k,&trouve);
        j=nb_elm_tab-1;
        while(j>=k)
        {
            tab[j+1]=tab[j];
            j--;
        }
        tab[k]=ind[i];
        nb_elm_tab++;
        i++;
    }
    j=-1;
    for(i=0;i<nb_elm_tab;i++)
    {
        if(j!=tab[i].adr.num_bloc)
        {   j=tab[i].adr.num_bloc;
            LireDir(f,tab[i].adr.num_bloc,&buf);
        }
        affiche_enrg(buf.tab[tab[i].adr.dep]);


    }

}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void inser_enr(T_OF *f, ind_enrg *ind)// cette procedure permet d'inserer un nouveau enregistrement
{
    tenrg e;
    tbloc_T_OF buf, buf1;
int aa,jj,mm;
    int i, j, k,x;
    bool trouve=true;
    char date[13],ch[30];


   textcolor(YELLOW); printf("Veuillez saisir les informations du nouveau millitant : \n");

    printf(" generation automatique du matricule : \n");

    while(trouve)
    {e.matricule=(99 * rand() + rand() + 4 * rand()) % (999999 - 111111 + 1) + 111111;
        rech_dicho(ind, e.matricule, &trouve, &k);
    }

    if (!trouve)
    {

         textcolor(YELLOW);  printf(" LE nom : ");
         textcolor(WHITE);  scanf("%s", &ch);
        strcpy(e.nom,ch);
        textcolor(YELLOW);printf(" LE prenom : ");
         textcolor(WHITE); scanf("%s", &ch);
        strcpy(e.prenom,ch);
        textcolor(YELLOW);printf(" La date_naissance \n");
       bool v=false;
      while(!v)
      {
      textcolor(YELLOW); printf("\t\tjour:"); textcolor(WHITE); scanf("%d",&jj);
      textcolor(YELLOW); printf("\t\tmois:"); textcolor(WHITE); scanf("%d",&mm);
       textcolor(YELLOW);printf("\t\tannee"); textcolor(WHITE); scanf("%d",&aa);

       v=date_valide(jj,mm,aa);
       if(!v)
       {
        textcolor(RED);printf("date non valide veuillez entrer une autre date\n");
       }
       }
       snprintf(date, sizeof(date), "%02d/%02d/%04d", jj, mm, aa);
       strcpy(e.date_naissance,date);

        x=0;
         textcolor(YELLOW) ;
        while(x>58 || x<1)
        {
         printf("La wilaya de naissance(entrer un nombre entre 1 et 58  : ");
             textcolor(WHITE); scanf("%d", &x);textcolor(RED);
        }
         strcpy(e.Wilaya_Naissance, wilayas[x]);


          x=0;
           textcolor(YELLOW) ;
        while(x>8 || x<1)
        {
           printf("La force Armee(entrer un nombre entre 1 et 8  : ");
            textcolor(WHITE);  scanf("%d", &x);textcolor(RED);
        }

       strcpy(e.Force_Armee, branches[x-1]);

          x=0;
        while(x>19 || x<1)
        {
           textcolor(YELLOW);  printf("LE grad (entrer un nombre entre 1 et 19  : ");
             textcolor(WHITE); scanf("%d", &x);textcolor(RED);
        }
        strcpy(e.Grade, grades[x-1]);

         x=0;
          textcolor(YELLOW);
        while(x>8 || x<1)
        {
            printf("LE groupe sanguin (entrer un nombre entre 1 et 8  : ");
             textcolor(WHITE); scanf("%d", &x);textcolor(RED);
        }

       strcpy(e.Groupe_Sanguin, groupesSanguins[x-1]);

         x=0;
          textcolor(YELLOW);
        while(x>6 || x<1)
        {
            printf("La region militaire (entrer un nombre entre 1 et 6  : ");
          textcolor(WHITE);  scanf("%d", &x);textcolor(RED);
        }
       strcpy(e.Region_militaire, regions[x-1]);
        LireDir(*f, f->entete.nb_bloc, &buf);

        for (i = nb_engr_ind - 1; i >= k; i--)
        {
            ind[i + 1] = ind[i];
        }

        if (buf.nb == max)
        {

            buf1.tab[0] = e;
            buf1.nb=1;
            f->entete.nb_bloc++;
            EcrireDir(*f, f->entete.nb_bloc , &buf1);
            ind[k].adr.dep = 0;
        }
        else
        {

            buf.tab[buf.nb] = e;
            buf.nb++;
            EcrireDir(*f, f->entete.nb_bloc, &buf);
            ind[k].adr.dep = buf.nb - 1;
        }
        nb_engr_ind++;
        ind[k].matricule = e.matricule;
        ind[k].adr.num_bloc = f->entete.nb_bloc ;

        affiche_enrg(e);
    }

    else
    {
        printf("Le militant existe deja");
    }
}
/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_fichier(T_OF f)/// afficher tous les enregistrement du fichier
{
  tbloc_T_OF buf1;
  int i,j;

  for(i=1;i<f.entete.nb_bloc+1;i++)
{  // printf("for");

    LireDir(f,i,&buf1);
    for(j=0;j<buf1.nb;j++)
    {
        affiche_enrg(buf1.tab[j]);
    }
}

}
void afficher_ind(ind_enrg ind[])/// affiche la table d'index
{int i1;
    for(i1=0;i1<nb_engr_ind;i1++)
{
    printf("i=%d matricule=%d: <bloc=%d  case=%d > \n",i1,ind[i1].matricule,ind[i1].adr.num_bloc,ind[i1].adr.dep);

}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void suppr_force(T_OF *f,ind_enrg *ind,int force)///
{ printf("void");tbloc_T_OF buf1,buf2;

    int i1=1,j1=0,i,j,nb=0,k;
    bool trouve;
    if(force>=0 && force<8)
    {
      for(i=1;i<f->entete.nb_bloc+1;i++)
      {
    LireDir(*f,i,&buf1);
    for(j=0;j<buf1.nb;j++)
    {  rech_dicho(ind,buf1.tab[j].matricule,&trouve,&k);
       if(strcmp(branches[force], buf1.tab[j].Force_Armee)!=0 )
         {  if (j1<max)
              {
                buf2.tab[j1]=  buf1.tab[j];
                j1++ ;


              }
            else
              {
                buf2.nb= j1 ;
                EcrireDir(*f, i1 , &buf2) ;
                buf2.tab[0] = buf1.tab[j];
                i1++;
                j1=1;

              }
            ind[k].adr.num_bloc=i1;
            ind[k].adr.dep=j1-1;//printf("j1= %d\n",ind[k].adr.dep);
            nb++;

    }else
    {

        ind[k].adr.num_bloc=-1;
    }
    }
    }
      buf2.nb=j1 ;
     EcrireDir(*f, i1, &buf2  ) ;
     f->entete.nb_bloc = i1 ;
     /// mise à jour de la table d'index
    k=0;
    for(i=0;i<nb_engr_ind;i++)
    {
        if(ind[i].adr.num_bloc!=-1)
        {
         ind[k]=ind[i];
         k++;
        }
    }


nb_engr_ind=nb;
}else
{
   textcolor(RED); printf("entrer un nombre entre 0 et 7\n");

}

}
int find_categorie(tenrg e)
{ int grade=0;
  while(strcmp(grades[grade],e.Grade)!=0 && grade<19)
  {
      grade++;//printf("while\n");
  }

       switch (grade) {
        case 0 ... 3:
          return 1;
            break;
        case 4 ... 6:
            return 2;
            break;
        case 7 ... 10:
          return 3;
            break;
        case 11 ... 15:
          return 4;
            break;
        case 16 ... 18:
            return 5;
            break;
        default:

            printf("Out of specified intervals\n");
            break;
    }


}
void afficher_catig(T_OF f,int categorie)
{
  tbloc_T_OF buf1;
  int i,j;

  for(i=1;i<f.entete.nb_bloc+1;i++)
  {  // printf("for");

    LireDir(f,i,&buf1);
    for(j=0;j<buf1.nb;j++)
    {    if(find_categorie(buf1.tab[j])==categorie)
        affiche_enrg(buf1.tab[j]);
    }
  }

}

void fragmentation(T_OF f)
{     printf("fragmentation");
   int region,i,j,i1=1,i2=1,i3=1,i4=1,i5=1,i6=1,j1=0,j2=0,j3=0,j4=0,j5=0,j6=0;
 T_OF f1,f2,f3,f4,f5,f6;
 tbloc_T_OF buf,buf1,buf2,buf3,buf4,buf5,buf6;/*
   ouvrir(&f1,"PERSONNEL-ANP_RM-Blida.bin",'n');
   ouvrir(&f2,"PERSONNEL-ANP_RM-Oran.bin",'n');
   ouvrir(&f3,"PERSONNEL-ANP_RM-Bechar.bin",'n');
    ouvrir(&f4,"PERSONNEL-ANP_RM-Ouargla.bin",'n');
     ouvrir(&f5,"PERSONNEL-ANP_RM-Constantine.bin",'n');
     ouvrir(&f6,"PERSONNEL-ANP_RM-Tamanrasset.bin",'n');
     printf("fragmentation");


 for(i=1;i<f.entete.nb_bloc+1;i++)
  {  // printf("for");

    LireDir(f,i,&buf);
    for(j=0;j<buf.nb;j++)
    {   region=0;
      while(strcmp(regions[region],buf.tab[j].Region_militaire)!=0 && region<6)
      {
          region++;
      }

      switch(region)
      {
      case 0:
          if (j1<max)
            {
                buf1.tab[j1]=buf.tab[j] ;
                j1++ ;


            }
            else
            {
                buf1.nb= j1 ;
                EcrireDir(f1, i1 , &buf1) ;
                buf1.tab[0] = buf.tab[j] ;
                i1++;
                j1=1;

            }
        break;
      case 1:
          if (j2<max)
            {
                buf2.tab[j2]=buf.tab[j] ;
                j2++ ;


            }
            else
            {
                buf2.nb= j2 ;
                EcrireDir(f2, i2 , &buf2) ;
                buf2.tab[0] = buf.tab[j] ;
                i2++;
                j2=1;

            }
        break;
        case 2:
          if (j3<max)
            {
                buf3.tab[j3]=buf.tab[j] ;
                j3++ ;


            }
            else
            {
                buf3.nb= j3 ;
                EcrireDir(f3, i3 , &buf3) ;
                buf3.tab[0] = buf.tab[j] ;
                i3++;
                j3=1;

            }
        break;
        case 3:
          if (j4<max)
            {
                buf4.tab[j4]=buf.tab[j] ;
                j4++ ;


            }
            else
            {
                buf4.nb= j4 ;
                EcrireDir(f4, i4 , &buf4) ;
                buf4.tab[0] = buf.tab[j] ;
                i4++;
                j4=1;

            }
        break;
        case 4:
          if (j5<max)
            {
                buf5.tab[j5]=buf.tab[j] ;
                j5++ ;


            }
            else
            {
                buf5.nb= j5 ;
                EcrireDir(f5, i5 , &buf5) ;
                buf5.tab[0] = buf.tab[j] ;
                i5++;
                j5=1;

            }
        break;
        case 5:
          if (j6<max)
            {
                buf6.tab[j6]=buf.tab[j] ;
                j6++ ;


            }
            else
            {
                buf6.nb= j6 ;
                EcrireDir(f6, i6 , &buf6) ;
                buf6.tab[0] = buf.tab[j] ;
                i6++;
                j6=1;

            }
        break;

      }









    }
  }

  buf1.nb=j1 ;
    EcrireDir(f1, i1, &buf1  ) ;
     f1.entete.nb_bloc = i1 ;
     fermer(&f1);


  buf2.nb=j2 ;
    EcrireDir(f2, i2, &buf2  ) ;
     f2.entete.nb_bloc = i2 ;
     fermer(&f2);


     buf3.nb=j3 ;
    EcrireDir(f3, i3, &buf3  ) ;
     f3.entete.nb_bloc = i3 ;
     fermer(&f3);


     buf4.nb=j4 ;
    EcrireDir(f4, i4, &buf4  ) ;
     f4.entete.nb_bloc = i4 ;
     fermer(&f4);

     buf5.nb=j5 ;
    EcrireDir(f5, i5, &buf5  ) ;
     f5.entete.nb_bloc = i5 ;
     fermer(&f5);

     buf6.nb=j6 ;
    EcrireDir(f6, i6, &buf6  ) ;
     f6.entete.nb_bloc = i6 ;
     fermer(&f6);


*/
}










 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{

    srand((unsigned int)time(NULL));
     T_OF f;

   ind_TOF fi;


   tbloc_T_OF buf1;
   buf1.nb=0;
   ind_enrg ind[90000];
int n,i=0,k,j=0,i1,j1,x,m1,m2;
tenrg e;
nb_engr_ind=0;
bool trouve,supr;int cpt=0;
db=0;


/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
First_Interface();
int choix=0;
ouvrir(&f,"PERSONNEL-ANP_DZ.dat.bin",'a');
ouvrir_ind(&fi,"MATRICULE_INDEX.idx.bin",'a');
chargement_ind(&ind,fi);

while(choix!=10)
{
 system("cls||clear");
 anp();
printf("\n\n");



 choix=menu(10,
                    "\t\t\t\t\t\t\t1>Generer un nouveau fichier ' PERSONNEL-ANP_DZ.dat '.",
                    "\t\t\t\t\t\t\t2>Recherche d'un Militant par matricule.",
                    "\t\t\t\t\t\t\t3>Suppression d'un Militant par matricule.",
                    "\t\t\t\t\t\t\t4>Insertion d'un nouveau Militant.",
                    "\t\t\t\t\t\t\t5>Recherche a intervalle.",
                    "\t\t\t\t\t\t\t6>Affichage du fichier 'PERSONNEL-ANP_DZ.dat'.",
                    "\t\t\t\t\t\t\t7>Affichage de la table d'index.",
                    "\t\t\t\t\t\t\t8>Supprimer tous les enregistrements d'une force.",
                    "\t\t\t\t\t\t\t9>Affichage d'une categorie de grades",
                    "\t\t\t\t\t\t\t10>Quitter le programme");
       switch(choix)
       {
       case 1:
           system("cls||clear");
           fermer(&f);
           fermer_ind(&fi);
           ouvrir_ind(&fi,"MATRICULE_INDEX.idx.bin",'n');
            ouvrir(&f,"PERSONNEL-ANP_DZ.dat.bin",'n');cout_op=0;
           textcolor(WHITE);
            printf("GENERATION AUTOMATIQUE DU FICHIER 'PERSONNEL-ANP_DZ.dat' ");
            textcolor(YELLOW);
           printf("\n\n");
           printf("veuillez entrer la taille du fichier(entre 1 et 100000):  ");textcolor (WHITE);
           scanf("%d",&n);
           while(n<1 || n>100000)
           {
               textcolor(RED);
               printf("[ERROR] entrez un nombreentre 1 et 100000 svp!:  ");
               textcolor (WHITE);
               scanf("%d",&n);

           }
            printf("\n\n");
           textcolor(YELLOW);
          printf("La generation du fichier peut prendre du temps veuillez patienter....\n\n") ;
          nb_engr_ind=0;
         chargement_initiale( &f , &ind , n );
        textcolor(LIGHTCYAN); printf("Generation avec succee\n\n");
          textcolor (WHITE);
         printf("nb_totale du personel:%d  \nnb de blocs utiliser: %d \nle cout de cette operation: %d  \n\n\n",nb_engr_ind,f.entete.nb_bloc,cout_op);
        break;

       case 2:
            system("cls||clear");cout_op=0;
        textcolor(WHITE);printf("RECHERCHE D'UN MILITAN (PAR MATRICULE)\n\n");
         textcolor(YELLOW);printf("entrez le matricule du militant(entre 111111 et 999999: ");
         textcolor(WHITE);scanf("%d",&n);
         while(n<111111 || n>999999)
           {
               textcolor(RED);
               printf("[ERROR] entrez un nombre entre 111111 et 999999 svp!:  ");
               textcolor (WHITE);
               scanf("%d",&n);

           }
           printf("\n\n");
           rech_dicho(ind,n,&trouve,&k);
           if(trouve)
           {
             textcolor(LIGHTCYAN);printf("Millitant existant\n\n");
            textcolor(WHITE);printf("Adresse du matricule %d :\n<bloc: %d  | case: %d>     \n\n",ind[k].matricule,ind[k].adr.num_bloc,ind[k].adr.dep);

           }else
           {
               textcolor(RED);printf("Millitant non existant\n\n");
           }
           textcolor (WHITE);
         printf("nb_totale du personel:%d  \nnb de blocs utiliser: %d \nle cout de cette operation: %d  \n\n\n",nb_engr_ind,f.entete.nb_bloc,cout_op);
             break;
       case 3:
        system("cls||clear");cout_op=0;
        textcolor(WHITE);printf("SUPPRESSION D'UN MILITANT (PAR MATRICULE)\n\n");
        textcolor(YELLOW);printf("entrez le matricule du militant(entre 111111 et 999999: ");
         textcolor(WHITE);scanf("%d",&n);
         while(n<111111 || n>999999)
           {
               textcolor(RED);
               printf("[ERROR] entrez un nombre entre 111111 et 999999 svp!:  ");
               textcolor (WHITE);
               scanf("%d",&n);

           }
           printf("\n\n");
           suppr(&f,&ind,n,&trouve);
            if(trouve)
           {
             textcolor(LIGHTCYAN);printf("Suppression avec succee\n\n");
             textcolor (WHITE);
             printf("nb_totale du personel:%d  \nnb de blocs utiliser: %d \nle cout de cette operation: %d  \n\n\n",nb_engr_ind,f.entete.nb_bloc,cout_op);
            }else
           {
               textcolor(RED);printf("Millitant non existant\n\n");
           }
           break;
       case 4:
        system("cls||clear");cout_op=0;
        textcolor(WHITE);printf("INSERTION D'UN MILITANT \n\n");

        inser_enr(&f,&ind);
          textcolor(LIGHTCYAN);printf("Insertion avec succee\n\n");
             textcolor(WHITE);printf("nb_totale du personel:%d  \nnb de blocs utiliser: %d   \n\n\n",nb_engr_ind,f.entete.nb_bloc);
         textcolor (WHITE);
         printf("nb_totale du personel:%d  \nnb de blocs utiliser: %d \nle cout de cette operation: %d  \n\n\n",nb_engr_ind,f.entete.nb_bloc,cout_op);
        break;
       case 5:
         system("cls||clear");
         cout_op=0;
         textcolor(WHITE);printf("RECHERCHE A INTERVALE \n\n");
         req_int:
         textcolor(YELLOW);printf("entrez la borne inferieure de l'interval(entre 111111 et 999999: ");
         textcolor(WHITE);scanf("%d",&m1);
         textcolor(YELLOW);printf("entrez la borne superieure de l'interval(entre 111111 et 999999: ");
         textcolor(WHITE);scanf("%d",&m2);
         if(m1>m2 || m1<111111 || m2>999999)
         {
            textcolor(RED);
               printf("[ERROR] veuillez resaisir l'interval!:  ");
               goto req_int;
         }
         textcolor(WHITE);requette_intervalle(f,m1,m2,ind);
         textcolor (WHITE);
         printf("nb_totale du personel:%d  \nnb de blocs utiliser: %d \nle cout de cette operation: %d  \n\n\n",nb_engr_ind,f.entete.nb_bloc,cout_op);
        break;
       case 6:
            system("cls||clear");cout_op=0;
           textcolor(YELLOW) ;printf("AFFICHAGE DU FICHIER/\n\n");
            textcolor(WHITE) ;afficher_fichier(f);
         textcolor (WHITE);
         printf("nb_totale du personel:%d  \nnb de blocs utiliser: %d \nle cout de cette operation: %d  \n\n\n",nb_engr_ind,f.entete.nb_bloc,cout_op);
          break;
       case 7:
            system("cls||clear");
          textcolor(YELLOW) ;printf("AFFICHAGE DE LA TABLE D'INDEX /\n\n");
           textcolor(WHITE) ;
              for(i1=0;i1<nb_engr_ind;i1++)
              {
                printf("i=%d matricule=%d: <bloc=%d  case=%d > \n",i1,ind[i1].matricule,ind[i1].adr.num_bloc,ind[i1].adr.dep);

              }
               textcolor (WHITE);
         printf("nb_totale du personel:%d  \nnb de blocs utiliser: %d   \n\n\n",nb_engr_ind,f.entete.nb_bloc);

        break;
       case 8:
         system("cls||clear");cout_op=0;
           textcolor(WHITE) ;printf("SUPPRESSION D'UNE FORCE ARMEE /\n\n");
         textcolor(YELLOW);printf("entrez un nombre entre 0 et 7: ");
         textcolor(WHITE);scanf("%d",&n);
          textcolor(YELLOW);
          printf("suppression peut prendre du temps veuillez patienter....\n\n") ;
         suppr_force(&f,&ind,n);
          textcolor(LIGHTCYAN);printf("Suppression avec succee\n\n");
          textcolor (WHITE);
          printf("nb_totale du personel:%d  \nnb de blocs utiliser: %d \nle cout de cette operation: %d  \n\n\n",nb_engr_ind,f.entete.nb_bloc,cout_op);

           break;
       case 9:
        system("cls||clear");cout_op=0;
        textcolor(WHITE);printf("AFFICHAGE DU PERSONNEL D'UNE CATEGORIE DE GRADES \n\n");
        printf("1-Officiers-generaux\n2-officiers-superieurs\n3-officiers\n4-sous-officiers\n5-hommes de troupes\n");
        textcolor(YELLOW);printf("entrez la categorie (entre 1 et 5: ");
         textcolor(WHITE);scanf("%d",&n);
         while(n<1 || n>5)
           {
               textcolor(RED);
               printf("[ERROR] entrez la categorie (entre 1 et 5) svp!:  ");
               textcolor (WHITE);
               scanf("%d",&n);

           }
           printf("\n\n");
          afficher_catig(f,n);
          textcolor (WHITE);
          printf("nb_totale du personel:%d  \nnb de blocs utiliser: %d \nle cout de cette operation: %d  \n\n\n",nb_engr_ind,f.entete.nb_bloc,cout_op);

            }/// fin swtich
            textcolor (YELLOW);
            printf("Press Any Key to Continue\n");
            getch();

}


sauv_ind_fich(&fi,ind);
fermer_ind(&fi);
fermer(&f);

    return 0;
}
