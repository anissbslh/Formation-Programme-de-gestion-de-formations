/*
    ----------------------------------------------------------------------
    TP ALSDD Semestre 2 Réalisé par Ameur Nassim G05 et Aniss Bessalah G05
    ----------------------------------------------------------------------

    Sous le thème : Application de gestion des formations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "bib.h"

ListeFormation* Formations[7];
bool erreur;
char choix;
char nom[25];
char prenom[25];
char nom_formation[25];
float note;
bool trouv;
bool sortie = False;
int a,i;

int main()
{
       // Color(3,3);
    //Initialiser le tableau Formations et lire les informations du fichier
    InitListe(Formations,&erreur);
    if(erreur == False)
    {
        acceuil(); //page d'acceuil
        bienvenue(); //page de bienvenu
        Color(15,0);
        system("cls");
        //debut du tuto
            Menu(); //page de menu
            Color(15,0);
            printf("\n\t\t>> Voici ci-dessus la liste d'operations que vous pouvez faire.\n");
            getch();
            printf("\n\t\t>> OH ! La secretaire vient de m'informer que le participant TAIBI KAMYL\n");
            printf("\t\t   actuellement en formation PHP veut changer sa formation en Javascript !\n");
            getch();
            printf("\n\t\t>> Voyons voir si ce participant existe en choisissant l'option ");
            Color(3,0);
            printf("[1]");
            Color(15,0);
            printf("\n\n\t\t\t\t\t\t\t\t\t ENTRER pour continuer ...");
            getch();
            //verification de l'existance du participant
            do {
            system("cls");
            Menu();
            Color(15,0);
            printf("\n\t\t>> Voyons voir si TAIBI Kamyl figure dans nos formations :\n");
            printf("\n\t\t>> Entrez le nom du participant : ");
            scanf("%s",nom);
            printf("\t\t>> Entrez le prenom du participant : ");
            scanf("%s",prenom);
            Affich_F_N(Formations,nom,prenom,nom_formation,&note,&trouv);//Affiche le nom de la formation et la note d'un participant existant donné, sinon ERREUR
            if(trouv == True)
            {
                Color(3,0);
                printf("\t\t  >> Formation : %s\n",nom_formation);
                printf("\t\t  >> Note : %0.2f\n",note);
                getchar();
                Color(15,0);
            }
            else
            {   Color(12,0);
                printf("\n\t\t  >> ERREUR: Ce participant ne figure pas dans la liste!");
                Color(15,0);
                getch();
            }
            }while (trouv == False);
            printf("\n\t\t\t\t\t\t\t ENTRER pour continuer ...");
            //fin de la verification de l'existance
            getch();
            system("cls");
            //debut du transfert
            Menu();
            Color(15,0);
            printf("\t\t>> Maintenant on va proceder au transfert de TAIBI kamyl vers JavaScript,\n");
            printf("\t\t   et cela en choisisant l'option ");
            Color(3,0);
            printf("[4]\n");
            printf("\n\t\t>> PS : Faites attention au nom de la formation, ecrivez-le sans faute !\n");
            Color(15,0);
            printf("\n\t\t>> Entrez le nom du participant : ");
            scanf("%s",nom);
            printf("\t\t>> Entrez le prenom du participant : ");
            scanf("%s",prenom);
            printf("\n\t\t>> Entrez le nom de la nouvelle formation: ");
            scanf("%s",nom_formation);
            Change_Formation(Formations,nom,prenom,nom_formation); //procedure de transfert
            printf("\t\t\t\t\t\t\t\t\t\t ENTRER pour continuer..");
            getch();
            system("cls");
            printf("FORMATION +");
            Color(0,3);
            printf("\n                                                      FELICITATIONS                                                     ");
            printf("\n\n\n");
            Color(15,0);
            fintuto();
        //fin du tuto

        while(sortie == False)
        {
            system("cls");
            Menu();
            Color(15,0);
            printf("\n\t\t>> Veuillez entrer votre choix : ");
            scanf("%s",&choix);
            switch(choix)
            {
                case '1':
                {
                    printf("\n\t\t>> Entrez le nom du participant : ");
                    scanf("%s",nom);
                    printf("\t\t>> Entrez le prenom du participant : ");
                    scanf("%s",prenom);
                    Affich_F_N(Formations,nom,prenom,nom_formation,&note,&trouv);
                    if(trouv == True)
                    {
                        printf("\t\t  >> Formation : %s\n",nom_formation);
                        printf("\t\t  >> Note : %0.2f\n",note);
                    }
                    else
                    {
                        Color(12,0);
                        printf("\n\t\t  >> ERREUR: Ce participant ne figure pas dans la liste!");
                        Color(15,0);
                    }
                    break;
                }
                case '2':
                {
                    printf("\n\t\t>> Entrez le nom de la formation : ");
                    scanf("%s",nom_formation);
                    note = Moy_Formation(Formations,nom_formation,&trouv);
                    if(trouv == True)
                    {
                        printf("\t\t  >> Moyenne : %0.2f\n",note);
                    }
                    else
                    {
                        Color(12,0);
                        printf("\t\t  >> ERREUR: Cette formation ne figure pas dans la liste!\n");
                        Color(15,0);
                    }
                    break;
                }
                case '3':
                {
                    printf("\n\t\t>> Les participants n'ayant pas reussi durant la session : \n");
                    Affich_Echec(Formations);
                    break;
                }
                case '4':
                {
                    printf("\n\t\t>> Entrez le nom du participant : ");
                    scanf("%s",nom);
                    printf("\t\t>> Entrez le prenom du participant : ");
                    scanf("%s",prenom);
                    printf("\n\t\t>> Entrez le nom de la nouvelle formation: ");
                    scanf("%s",nom_formation);
                    Change_Formation(Formations,nom,prenom,nom_formation);
                    break;
                }
                case '5':
                {
                    printf("\n\t\t>> Entrez le nom du participant : ");
                    scanf("%s",nom);
                    printf("\t\t>> Entrez le prenom du participant : ");
                    scanf("%s",prenom);
                    printf("\n\t\t>> Entrez la nouvelle note : ");
                    scanf("%f",&note);
                    Change_Note(Formations,nom,prenom,note);
                    Sauvegarder(Formations);
                    break;
                }
                case '6':
                {
                    printf("\n\t\t>> Entrez le nom de la formation: ");
                    scanf("%s",nom_formation);
                    printf("\n");
                    Affich_Formation_Tri(Formations,nom_formation);
                    break;
                }
                case '7':
                {
                    Sauvegarder(Formations);
                    printf("\n\t\t>> Donnees sauvegardees");
                    break;
                }
                default:
                {
                    break;
                }
            }

            printf("\n\nVoulez vous quitter (O/N) ? ");
            scanf("%s",&choix);
            if((choix == 'o')||(choix == 'O'))
            {
                sortie = True;
            }
            else
                system("cls");
        }
    }
    system("cls");
    return 0;
}
