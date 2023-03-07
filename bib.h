#ifndef BIB_H_INCLUDED
#define BIB_H_INCLUDED

#include <ctype.h>
#include <time.h>
#include "machine_abstraite.h"

#define MAX_NOTE 20
#define MIN_NOTE 7
#define True 1
#define False 0

typedef int bool;

//PROCEDURE: Convertit la chaine de caractères en majuscules
char* Upcase(char s[],int tai)
{
    for(int i=0;i<tai;i++)
    {
        s[i] = toupper(s[i]);
    }
    return s;
}


//FONCTION : Créé les listes linéaires chainées de participants des formations
void InitListe(ListeFormation* Formations[],int* erreur)
{
    FILE *fptr;
    char s[100];
    int cpt = -1;
    ListeFormation* templist;
    ListeFormation* queue;
    fptr = fopen("Participants.txt","r");

    if(fptr == NULL)
    {
        printf("Erreur: Fichier 'Participants.txt' introuvable.");
        *erreur = True;
    }
    else
    {
        *erreur = False;

        srand((unsigned int)time(NULL));

        int ch = 0;
        while(ch != EOF)
        {
            fscanf(fptr, "%s", s);
            if(strcmp(s,"Formation:") != 0)
            {
                Participant participant;

                strcpy(participant.NomP,s);

                fscanf(fptr, "%s", s);
                strcpy(participant.PrenomP,s);

                participant.NoteP = (((float)rand()/(float)RAND_MAX) * (MAX_NOTE - MIN_NOTE)) + MIN_NOTE;

                Ajouter(&templist,&queue,participant);
            }
            else
            {
                if(cpt>-1)
                {
                    Formations[cpt] = templist;
                }
                cpt+=1;
                fscanf(fptr, "%s", s);
                CreerListe(&templist,&queue);

                Participant participant;
                strncpy(participant.NomP,"Nom_Formation",25);
                strncpy(participant.PrenomP,s,25);
                participant.NoteP = 0;
                Ajouter(&templist,&queue,participant);
            }
            ch = getc(fptr);
        }
        Formations[cpt] = templist;
        fclose(fptr);
    }
}

//PROCEDURE: Affiche le nom de la formation et la note d'un participant donné
void Affich_F_N(ListeFormation* Formations[],char nom[],char prenom[],char nom_formation[],float* note,int* trouv)
{
    *trouv = False;
    int i=0;
    while((i<7)&&(*trouv == False))
    {
        ListeFormation* p;
        p = Formations[i];
        while(p != NULL)
        {
            if((strcmp(Upcase(Val(p).NomP,25),Upcase(nom,25)) == 0)&&(strcmp(Upcase(Val(p).PrenomP,25),Upcase(prenom,25)) == 0))
            {
                strcpy(nom_formation,Val(Formations[i]).PrenomP);
                *note = Val(p).NoteP;
                *trouv = True;
            }
            p = Suivant(p);
        }
        i+=1;
    }
}

//FONCTION: Affiche la moyenne des participants d'une formation donnée
float Moy_Formation(ListeFormation* Formations[],char nom_formation[],int* trouv)
{
    *trouv = False;
    float moy = 0;
    int i=0;
    int cpt = 0;
    while((i<7)&&(*trouv == False))
    {
        if(strcmp(Formations[i]->participant.PrenomP,nom_formation) == 0)
        {
            *trouv = True;
        }
        else
        {
            i+=1;
        }
    }

    if(*trouv == True)
    {
        ListeFormation* p;
        p = Formations[i];
        while(p != NULL)
        {
            moy += Val(p).NoteP;
            cpt+=1;
            p = Suivant(p);
        }
        moy = moy/cpt;
    }

    return moy;
}

//PROCEDURE: Affiche les participants qui n'ont pas réussi ordonné par formation
void Affich_Echec(ListeFormation* Formations[])
{
    for(int i=0;i<7;i++)
    {
        Color(12,0);
        printf("\t\tFormation %s :\n",Formations[i]->participant.PrenomP);
        Color(15,0);
        ListeFormation* p;
        p = Formations[i];
        while(p != NULL)
        {
            if((strcmp(p->participant.NomP,"Nom_Formation") != 0) && (p->participant.NoteP < 10))
            {
                printf("\t\t%20s ",p->participant.NomP);
                printf("%20s\n",p->participant.PrenomP);
            }
            p = Suivant(p);
        }
        printf("\n");
    }
}

void Change_Formation (ListeFormation* Formations[], char nom[], char prenom[], char nom_formation[])
{
    int trouvP = False;
    int trouvF=False;
    int i=0;
    int j=0;
    ListeFormation* p;

    while ((j<7) && (trouvF==False))
    {
       if (strcmp(nom_formation,Formations[j]->participant.PrenomP) == 0)
       {
           trouvF=True;

       }
       else
       {
           j++;
       }
    }

    while((i<7)&&(trouvP == False))
    {

        p = Formations[i];
        ListeFormation* q = NULL;
        while((p != NULL)&&(trouvP==False))
        {
            if((strcmp(Upcase(Val(p).NomP,25),Upcase(nom,25)) == 0)&&(strcmp(Upcase(Val(p).PrenomP,25),Upcase(prenom,25)) == 0))
            {
               trouvP=True;
               if(trouvF == True)
               {
                   if (q==NULL)
                   {
                       Formations[i]=Suivant(p);
                   }
                   else
                   {
                       Aff_Adr(q,Suivant(p));
                   }
               }
            }
            else
            {
                q = p;
                p = Suivant(p);
            }
        }
        i+=1;
    }

    if ((trouvP==True)&&(trouvF == True))
    {
        trouvP=False;
        ListeFormation* p1=Formations[j];
        ListeFormation* q1=NULL;
        while ((p1 != NULL) && (trouvP==False))
        {
            if ((strcmp(Upcase(nom,25),Upcase(Val(p1).NomP,25))<0) && (strcmp(p1->participant.NomP,"Nom_Formation") != 0))
            {
                trouvP=True;
            }
            else
            {
                q1=p1;
                p1=Suivant(p1);
            }
        }
        Aff_Adr(p,p1);
        if (q1 != NULL)
        {
            Aff_Adr(q1,p);
        }
        else
        {
            Formations[j]=p;
        }
        Color(10,0);
        printf("\n\t\t> Transfert effectue\n");
        Color(15,0);
    }
    else
    {
        Color(12,0);
        if(trouvP == False && trouvF == True)
            printf("\n\t\t>> ERREUR: Ce participant ne figure pas dans la liste!\n");
        if(trouvF == False && trouvP == True)
            printf("\n\t\t>> ERREUR: Cette formation ne figure pas dans la liste!\n");
        if(trouvF == False && trouvP == False)
        {
            printf("\n\t\t>> ERREUR: Ce participant ne figure pas dans la liste!");
            printf("\n\t\t>> ERREUR: Cette formation ne figure pas dans la liste!\n");
        }
        Color(15,0);
    }
}

void Change_Note(ListeFormation* Formations[],char nom[],char prenom[],float note)
{
    int trouv = False;
    int i=0;
    ListeFormation* p;
    while((i<7)&&(trouv == False))
    {
        p = Formations[i];
        while((p != NULL)&&(trouv==False))
        {
            if((strcmp(Upcase(Val(p).NomP,25),Upcase(nom,25)) == 0)&&(strcmp(Upcase(Val(p).PrenomP,25),Upcase(prenom,25)) == 0))
            {
                trouv=True;
            }
            else
            {
                p = Suivant(p);
            }
        }
        i+=1;
    }

    if(trouv == True)
    {
        p->participant.NoteP = note;
        Color(10,0);
        printf("\n\t\t> Changement de note effectue\n");
        Color(15,0);
    }
    else
    {
        Color(12,0);
        printf("\n\t\t>> ERREUR: Ce participant ne figure pas dans la liste!\n");
        Color(15,0);
    }
}

void Affich_Formation_Tri(ListeFormation* Formations[],char nom_formation[])
{
    int trouv = False;
    int i=0;
    while ((i<7) && (trouv==False))
    {
       if (strcmp(nom_formation,Formations[i]->participant.PrenomP) == 0)
       {
           trouv=True;
       }
       else
       {
           i++;
       }
    }

    if(trouv == True)
    {
        int permut = True;
        ListeFormation* liste = CopierListe(Suivant(Formations[i]));
        ListeFormation* p = liste;
        ListeFormation* q = NULL;
        Participant temp;
        while(permut == True)
        {
            permut = False;
            while(Suivant(p) != q)
            {
                if((p->participant).NoteP < (Suivant(p)->participant).NoteP)
                {
                    permut = True;
                    temp = (Suivant(p))->participant;
                    Aff_Val(Suivant(p),p->participant);
                    Aff_Val(p,temp);
                }
                p = Suivant(p);
            }
            q = p;
            p = liste;
        }

        Affich_Liste(p);
        LibererListe(p);
    }
    else
    {
        Color(12,0);
        printf("\n\t\t>> ERREUR: Cette formation ne figure pas dans la liste!\n");
        Color(15,0);
    }
}

void Sauvegarder(ListeFormation* Formations[])
{
    FILE *fptr;
    fptr = fopen("Resultats.txt","w");
    for(int i=0;i<7;i++)
    {
        fprintf(fptr,"Formation: %s\n",Formations[i]->participant.PrenomP);
        ListeFormation* p = Suivant(Formations[i]);
        Affich_Liste_File(fptr,p);
        fprintf(fptr,"\n");
    }
    fclose(fptr);
}

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage en couleurs
{
    /*
        LES NOMBRES QUI REPRESENTENT CHAQUE COULEUR:
        0 : Noir
        1 : Bleu foncé
        2 : Vert foncé
        3 : Turquoise
        4 : Rouge foncé
        5 : Violet
        6 : Vert caca d'oie
        7 : Gris clair
        8 : Gris foncé
        9 : Bleu fluo
        10 : Vert fluo
        11 : Turquoise
        12 : Rouge fluo
        13 : Violet 2
        14 : Jaune
        15 : Blanc
        */

        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void Menu ()
{
     Color(0,3);
            printf("\n                                                    MENU PRINCIPAL:                                                     ");
            Color(3,0);
            printf("\n\n\t\t[1] ");
            Color(15,0);
            printf("Afficher le nom de la formation et la note d'un participant                         \n");
            Color(3,0);
            printf("\n\t\t[2] ");
            Color(15,0);
            printf("Afficher la moyenne des participants d'une formation\n");
            Color(3,0);
            printf("\n\t\t[3] ");
            Color(15,0);
            printf("Afficher les participants n'ayant pas reussi durant la session\n");
            Color(3,0);
            printf("\n\t\t[4] ");
            Color(15,0);
            printf("Changer la formation d'un participant\n");
            Color(3,0);
            printf("\n\t\t[5] ");
            Color(15,0);
            printf("Changer la note d'un participant\n");
            Color(3,0);
            printf("\n\t\t[6] ");
            Color(15,0);
            printf("Afficher la liste des participants d'une formation par ordre de merite\n");
            Color(3,0);
            printf("\n\t\t[7] ");
            Color(15,0);
            printf("Sauvegarder les donnees dans le fichier 'Resultats.txt'\n");
            Color(0,3);
            printf("\n                                                                                                                        \n");
}
//Decor en haut de l'acceuil (logo ESI + informations)
void logoESI ()
{
    Color(15,0);
    printf("%c%c%c%c%c %c%c%c%c%c ",219,219,219,219,219,219,219,219,219,219);
    Color(3,0);
    printf("%c",219);
    Color(15,0);
    printf("                                                      \t\tALGORTHIMIQUE ET STRUCTURES\n");
    Color(15,0);
    printf("%c     %c     \t\t\t\t\t\t\t\t\tDE DONNEES DYNAMIQUES\n",219,219,219);
    printf("%c%c%c%c%c %c%c%c%c%c %c\t\t\t\t\t\t\t\t\t1ere annee classe preparatoire\n",219,219,219,219,219,219,219,219,219,219,219);
    printf("%c         %c %c\t\t\t\t\t\t\t\t\t2020/2021\n",219,219,219);
    printf("%c%c%c%c%c %c%c%c%c%c %c\n",219,219,219,219,219,219,219,219,219,219,219);
    Color(3,3);
    printf("                                                                                                                        \n\n");
}
//logo FORMATION+
void logoFORMATION()
{
    printf("                                  %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c %c   %c %c%c%c%c%c %c%c%c%c%c %c %c%c%c%c%c %c   %c     \n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        _sleep(100);
        printf("                                  %c     %c   %c %c   %c %c%c %c%c %c   %c   %c   %c %c   %c %c%c  %c   %c  \n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        _sleep(100);
        printf("                                  %c%c%c%c%c %c   %c %c%c%c%c  %c %c %c %c%c%c%c%c   %c   %c %c   %c %c %c %c  %c%c%c \n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        _sleep(100);
        printf("                                  %c     %c   %c %c  %c  %c   %c %c   %c   %c   %c %c   %c %c  %c%c   %c \n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        _sleep(100);
        printf("                                  %c     %c%c%c%c%c %c   %c %c   %c %c   %c   %c   %c %c%c%c%c%c %c   %c    \n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
        _sleep(100);
        printf("\n                                        ");
}

void slogon()
{
    Color(0,3);
    printf("~N");_sleep(20);
    printf("O");_sleep(20);printf(" ");_sleep(20);printf("L");_sleep(20);printf("I");_sleep(20);printf("N");_sleep(20);printf("E");_sleep(20);printf(" ");_sleep(20);printf("O");_sleep(20);printf("F");_sleep(20);printf(" ");_sleep(20);printf("C");_sleep(20);printf("O");_sleep(20);printf("D");_sleep(20);printf("E");_sleep(20);printf(" ");_sleep(20);printf("S");_sleep(20);printf("H");_sleep(20);printf("A");_sleep(20);printf("L");_sleep(20);printf("L");_sleep(20);printf("L");_sleep(20);printf(" ");_sleep(20);printf("E");_sleep(20);printf("S");_sleep(20);printf("C");_sleep(20);printf("A");_sleep(20);printf("P");_sleep(20);printf("E");_sleep(20);printf(" ");_sleep(20);printf("Y");_sleep(20);printf("O");_sleep(20);printf("U");_sleep(20);printf("R");_sleep(20);printf(" ");_sleep(20);printf("S");_sleep(20);printf("I");_sleep(20);printf("G");_sleep(20);printf("H");_sleep(20);printf("T");_sleep(20);printf("~\n");
}

void acceuil()
{
    logoESI();
    Color(3,0);
    logoFORMATION();
    slogon();
    Color(15,0);
    printf("\n\n\n\t\t\t\t\t\tCliquez pour continuer..");
    printf("\n\n\n\t\t     Realise par : \t\t\t\t\t\t\tEncadre par : \n");
    printf("\t\t     ------\t\t\t\t\t\t\t\t------\n");
    printf("\t\t     Bessalah Aniss\t\t\t\t\t\t\tMr. Benmalek Mourad\n");
    printf("\t\t     Ameur Nassim\n");
    getch();
}

void bienvenue()
{
    system("cls");
    printf("FORMATION +");
    Color(0,3);
    printf("\n                                                 BIENVENUE ! WELCOME !                                                  ");
    printf("\n\n\n");
    Color(15,0);
    printf("\t\t>> FORMATION + est un institut de formation specialise en informatique\n");
    printf("\t\t   Des experts en informatique venus des quatre coins du monde offrent\n");
    printf("\t\t   la possibilte a nos chers abonnes de decouvrir le monde de l'informatique\n");
    printf("\t\t   et tous ses secrets...\n\n");
    getchar();
    printf("\t\t>> FORMATION + propose une nouvelle serie de formations : FORMATIONS EN PROGRAMMATION\n");
    printf("\t\t   Interessant n'est ce pas ?\n");
    printf("\t\t   Les formations proposees : C, C++, C#, Java, JavaScript, Python et PHP\n\n");
    getchar();
    printf("\t\t>> Chaque formation contient une vingtaine de participants que VOUS devez gerer !\n");
    getchar();
    printf("\t\t>> Mais ne vous inquietez pas, je suis la pour vous aider. Rassurez-vous ^^ \n\n");
    getchar();
    printf("\t\t>> Je me presente, je suis ");
    Color(0,3);
    printf("l'assistant de gestion de formations");
    Color(15,0);
    printf(" ! et je vais vous\n");
    printf("\t\t   guider a gerer les formations, ");
    Color(3,0);
    printf("SUIVEZ-MOI");
    Color(15,0);
    printf("\n\n\n\n                                                                                    >> Cliquez pour continuer..");
    Color(3,3);
    printf("\n\n                                                                                                                        ");
    getchar();
}

void fintuto ()
{
    printf("\t\t>> Vous avez reussi votre premiere tache BRAVO ! *applaudissement*\n\n");
            getch();
            printf("\n\t\t>> Maintenant que vous savez comment fonctionne l'apllication de gestion de formations,\n");
            printf("\t\t   effectuer vos differentes taches !\n");
            getch();
            printf("\n\n\t\t>> je n'ai plus qu'a vous dire bonne courage pour la suite et ca a ete un plaisir de vous\n");
            printf("\t\t   de vous rencontrer, on compte sur vous !\n\n");
            getch();
            Color(3,0);
            printf("\n\t\t>> UN DERNIER TRUC ! ");
            Color(15,0);
            printf("N'oubliez pas de sauvegarder les donnees en utilisant l'option ");
            Color(3,0);
            printf("[7]");
            printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t  ENTRER pour revenir vers le MENU..");
            getch();
}




#endif // BIB_H_INCLUDED
