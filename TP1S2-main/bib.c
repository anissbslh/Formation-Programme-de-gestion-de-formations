

#define MAX_NOTE 20
#define MIN_NOTE 7

//PROCEDURE: Affecter une valeur au maillon
void Aff_Val(ListeFormation* p,Participant val)
{
    p->participant = val;
}

//PROCEDURE: Chainer le maillon à l'adresse suivante
void Aff_Adr(ListeFormation* p,ListeFormation* q)
{
    p->suivant = q;
}

//PROCEDURE: Allouer un maillon
void Allouer(ListeFormation** p)
{
    *p = (ListeFormation*)malloc(sizeof(ListeFormation));
}

//PROCEDURE: Creer une nouvelle file
void CreerListe(ListeFormation** L,ListeFormation** queue)
{
    *L = NULL;
    *queue = NULL;
}

//PROCEDURE: Ajouter une valeur à la fin de la liste
void Ajouter(ListeFormation** L,ListeFormation** queue,Participant val)
{
    ListeFormation* p;
    Allouer(&p);
    Aff_Val(p,val);
    Aff_Adr(p,NULL);
    if(*L == NULL)
    {
        *L = p;
        *queue = p;
    }
    else
    {
        Aff_Adr(*queue,p);
        *queue = p;
    }
}

//FONCTION : Créé les listes linéaires chainées de participants des formations
void InitListe(ListeFormation* Formations[])
{
    FILE *fptr;
    char s[100];
    int cpt = -1;
    ListeFormation* templist;
    ListeFormation* queue;
    fptr = fopen("Participants.txt","r");

    if(fptr == NULL)
    {
        printf("Erreur: Fichier introuvable.");
    }
    else
    {
        int ch = 0;
        while(ch != EOF)
        {
            fscanf(fptr, "%s", s);
            if(strcmp(s,"Formation:") != 0)
            {
                Participant participant;

                strncpy(participant.NomP,s,25);
                printf("%s\n",participant.NomP);
                fscanf(fptr, "%s", s);
                strncpy(participant.PrenomP,s,25);
                printf("%s\n",participant.PrenomP);

                participant.NoteP = (((float)rand()/(float)RAND_MAX) * (MAX_NOTE - MIN_NOTE)) + MIN_NOTE;
                printf("%0.2f\n",participant.NoteP);

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
