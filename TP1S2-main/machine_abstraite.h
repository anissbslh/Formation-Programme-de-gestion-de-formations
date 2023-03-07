#ifndef MACHINE_ABSTRAITE_H_INCLUDED
#define MACHINE_ABSTRAITE_H_INCLUDED

// On définit l'enregistrement Participant
typedef struct Participant Participant;
struct Participant
{
    char NomP[25];
    char PrenomP[25];
    float NoteP;
};

//On définit un type ListeFormation qui est un maillon contenant un participant
typedef struct ListeFormation ListeFormation;
struct ListeFormation
{
    Participant participant;
    ListeFormation* suivant;
};


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

//FONCTION: Retourne la valeur du maillon (La valeur est un participant)
Participant Val(ListeFormation* p)
{
    return p->participant;
}

ListeFormation* Suivant(ListeFormation* p)
{
    return p->suivant;
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

//FONCTION: Copie une liste et retourne une nouvelle tete
ListeFormation* CopierListe(ListeFormation* L)
{
    ListeFormation* L2;
    if(L == NULL)
    {
        L2 = NULL;
    }
    else
    {
        Allouer(&L2);
        Aff_Val(L2,L->participant);
        L = Suivant(L);
        ListeFormation* p;
        ListeFormation* q = L2;
        while(L != NULL)
        {
            Allouer(&p);
            Aff_Val(p,L->participant);
            Aff_Adr(q,p);
            L = Suivant(L);
            q = p;
        }
        Aff_Adr(q,NULL);
    }

    return L2;
}

//PROCEDURE: Libere tous de la maillons de la liste
void LibererListe(ListeFormation* L)
{
    ListeFormation* p = L;
    ListeFormation* suivant;
    while(p != NULL)
    {
        suivant = Suivant(p);
        free(p);
        p = suivant;
    }
}

//PROCEDURE: Affiche toutes les valeurs de la liste sur la console
void Affich_Liste(ListeFormation* L)
{
    ListeFormation* p = L;
    while(p != NULL)
    {
        printf("\t\t%20s ",p->participant.NomP);
        printf("%20s ",p->participant.PrenomP);
        printf("%10.2f\n",p->participant.NoteP);
        p = Suivant(p);
    }
}

//PROCEDURE: Affiche toutes les valeurs de la liste dans un fichier
void Affich_Liste_File(FILE *fptr,ListeFormation* L)
{
    ListeFormation* p = L;
    while(p != NULL)
    {
        fprintf(fptr,"\t\t%s ",p->participant.NomP);
        fprintf(fptr,"%s ",p->participant.PrenomP);
        fprintf(fptr,"%0.2f\n",p->participant.NoteP);
        p = Suivant(p);
    }
}

#endif // MACHINE_ABSTRAITE_H_INCLUDED
