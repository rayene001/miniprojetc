#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_IDENTIFIANTS 50

typedef struct
{
    int tab[MAX_IDENTIFIANTS];
    int tete;

    int taille;
} file;

typedef struct
{
    char fullname[50];
    int cin;
} client;

typedef struct
{
    client c;
    struct liste *suivant;

} liste;

int estvide(file f)
{
    if (f.taille == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

file defiler(file f)
{
    if (estvide(f) == 0)
    {
        f.tete = f.tete + 1;
    }
    return f;
}

int verifcation(int carte, liste *tete)
{
    while (tete != NULL)
    {
        if (tete->c.cin == carte)
        {
            return 1;
        }
        tete = tete->suivant;
    }
    return 0;
}

liste *ajouterclient(char name[], int carte, liste *tete)
{
    liste *nv = (liste *)malloc(sizeof(liste));
    strcpy(nv->c.fullname, name);
    nv->c.cin = carte;
    nv->suivant = tete;
    return nv;
}

typedef struct
{
    char nom[10];
    float prixu;
    file f;
    int qte;
} produit;

void enfiler(file *f, int x)
{
    if (f->taille >= MAX_IDENTIFIANTS)
    {
        printf("Erreur : La file est pleine !\n");
    }
    else
    {
        f->tab[f->taille] = x;
        f->taille++;
    }
}

void afficher(FILE *fptr)
{
    char string[50];
    while (fgets(string, 50, fptr))
    {
        printf("%s", string);
    }
};

void verif(char string[])
{
    while (strcmp(string, "oui") != 0 && strcmp(string, "non") != 0)
    {
        printf("Reponse invalide ! Veuillez introduire une des deux reponses possibles (oui/non).\n");
        scanf("%s", string);
    }
}

int main()
{

    produit T[30];
    int n;
    n = 3;

    //*T = malloc(n * sizeof(produit));
    strcpy(T[0].nom, "lait");
    T[0].prixu = 1.5;
    T[0].f.taille = 5;
    T[0].f.tab[0] = 0001;
    T[0].f.tab[1] = 0002;
    T[0].f.tab[2] = 0003;
    T[0].f.tab[3] = 0004;
    T[0].f.tab[4] = 0005;
    T[0].qte = T[0].f.taille;

    T[0].f.tete = 0;

    T[1].prixu = 3.5;
    strcpy(T[1].nom, "chocolat");
    T[1].f.taille = 5;
    T[1].f.tab[0] = 1;
    T[1].f.tab[1] = 2;
    T[1].f.tab[2] = 3;
    T[1].f.tab[3] = 4;
    T[1].f.tab[4] = 5;
    T[1].qte = 5;
    T[1].f.tete = 0;

    T[2].prixu = 2;
    strcpy(T[2].nom, "biscuit");
    T[2].f.taille = 5;
    T[2].f.tab[0] = 1;
    T[2].f.tab[1] = 2;
    T[2].f.tab[2] = 3;
    T[2].f.tab[3] = 4;
    T[2].f.tab[4] = 5;
    T[2].qte = 5;
    T[2].f.tete = 0;
    FILE *fptr;
    fptr = fopen("produits.txt", "w");
    if (fptr == NULL)
        printf("impossible d'ouvrir le fichier");

    for (int i = 0; i < n; i++)
    {
        fprintf(fptr, "produit: %s\n", T[i].nom);
        fprintf(fptr, "prix : %f\n", T[i].prixu);
        fprintf(fptr, "Quantite disponible de %s: %d\n\n", T[i].nom, T[i].qte);
    }
    fclose(fptr);

    char a[20];
    printf("BIENVENUE DANS NOTRE E-SUPERMARCHE. NOUS ESPERONS QUE PASSIEZ UNE BELLE EXPERIENCE!\n\n");
    printf("Etes-vous client ou fournisseur ?\n");
    scanf("%s", a);
    while ((strcmp(a, "fournisseur")) && (strcmp(a, "client")))
    {
        printf("Reponse invalide! Veuillez reessayer.\n");
        scanf("%s", a);
    }
    if (strcmp(a, "fournisseur") == 0)
    {
        /*on fait le parcours du tableau des produits et on tire une
        liste de produits dont nous n'en avons la quantit� suffisante
        (par exemple une quantit� < 10 ) et on demande au fournisseur
        de fournir ces produits.
        le fournisseur, � son tour va, ou bien suffir le besoin, ou bien
        s'excuser pour certains produits.*/

        for (int i = 0; i < n; i++)
        {
            if (T[i].qte <= 10)
            {
                printf("Est ce que vous pouvez nous fournir du %s ?(oui/non)\n", T[i].nom);
                char rep[10];
                scanf("%s", rep);
                verif(rep);

                if (strcmp(rep, "oui") == 0)
                {
                    printf("Quelle est la quantite disponible ?\n");
                    int qtedisp;
                    scanf("%i", &qtedisp);
                    printf("Enter l\'identifiant de chaque produit\n");
                    for (int k = 0; k < qtedisp; k++)
                    {
                        printf("identifiant %d", k + 1);
                        int id1;
                        scanf("%d", &id1);
                        enfiler(&T[i].f, id1);
                    }
                    T[i].qte += qtedisp;
                    T[i].f.taille = T[i].qte;
                    FILE *fptr1;
                    fptr1 = fopen("produits.txt", "a");
                }
                else if (strcmp(rep, "non") == 0)
                    continue;
            }
        }

        printf("Est ce que vous proposez un nouveau produit ? (oui/non)\n");
        char rep2[10];
        scanf("%s", &rep2);
        verif(rep2);

        if (strcmp(rep2, "oui") == 0)
        {
            char rep3[5] = "oui";
            while (strcmp(rep3, "oui") == 0)
            {
                printf("Qu'est ce que vous proposez ? Entrer le nom du produit, son prix unitaire et la quantite disponoble.\n");
                printf("Nom du produit:");
                char nomprod[20];
                scanf("%s", nomprod);
                printf("Prix unitaire du produit:");
                float prix;
                scanf("%f", &prix);
                printf("La quantite disponible:");
                int quantite;
                scanf("%d", &quantite);
                strcpy(T[n].nom, nomprod);
                T[n].prixu = prix;
                T[n].qte = quantite;
                T[n].f.taille = 0;
                T[n].f.tete = 0;
                FILE *fptr2;
                fptr2 = fopen("produits.txt", "a");
                fprintf(fptr, "produit: %s\n", T[n].nom);
                fprintf(fptr, "prix : %d\n", T[n].prixu);
                fprintf(fptr, "Quantite disponible : %d\n\n", T[n].qte);

                printf("Entrer l\'identifiant de chaque unite\n");
                for (int j = 0; j < quantite; j++)
                {
                    printf("L'dientifiant du produit %d: ", j + 1);
                    int id;
                    scanf("%i", &id);
                    enfiler(&T[n].f, id);
                    T[n].f.taille = T[n].qte;
                }
                n += 1;
                printf("Est ce que vous proposez autre chose ? (oui/non)\n");
                scanf("%s", rep3);
                verif(rep3);
            }
        }
    }

    else if (strcmp(a, "client") == 0)
    {
        printf("voici les produits disponibles \n\n");
        FILE *fptr6;
        fptr6 = fopen("produits.txt", "r");
        afficher(fptr6);
        fclose(fptr6);
        printf("Est ce que vous voulez acheter quelque chose ? (oui/non)\n");
        char rep4[10];
        scanf("%s", rep4);
        verif(rep4);
        float s;
        if (strcmp(rep4, "oui") == 0)
        {
            char continuer[10] = "oui";
            s = 0;
            FILE *fptr5;
            fptr5 = fopen("facture.txt", "a");
            fprintf(fptr5, "facture\n\n");
            while (strcmp(continuer, "oui") == 0)
            {
                int qtep;
                char nomp[10];

                printf("donnez le nom du produit:");
                scanf("%s", nomp);
                printf("donnez la quantité:");
                scanf("%d", &qtep);
                int i = -1;
                while (i != n)
                {

                    i = i + 1;
                    int x = strcmp(T[i].nom, nomp);
                    if (x == 0)
                    {

                        if (T[i].qte < qtep)
                        {

                            printf("Stock insuffisant ! On ne peut pas vous fournir la quantite demandee. \n");
                            break;
                        }
                        else
                        {

                            s = s + qtep * T[i].prixu;
                            T[i].qte = T[i].qte - qtep;

                            for (int j = 0; j < qtep; j++)
                            {

                                T[i].f = defiler(T[i].f);
                            }

                            FILE *fichier;

                            char buffer[256];


                            fichier = fopen("produits.txt", "r");
                            if (fichier == NULL) {
                                perror("Erreur lors de l'ouverture du fichier");
                                return 1;
                            }


                            fgets(buffer, sizeof(buffer), fichier);
                            fclose(fichier);

                            char ancientexte[50];
                            char nouveautexte[50];
                            sprintf(ancientexte,"Quantite disponible de %s: %d", T[i].nom, T[i].qte);
                            sprintf(nouveautexte,"Quantite disponible de %s: %d", T[i].nom, T[i].qte + qtep);
                            if (strstr(buffer,ancientexte ) != NULL) {
                                strcpy(buffer,nouveautexte );
                            }


                            fichier = fopen("produits.txt", "w");
                            if (fichier == NULL) {
                                perror("Erreur lors de l'ouverture du fichier pour écriture");
                            }


                            fprintf(fichier, "%s", buffer);
                            fclose(fichier);
                                break;

                            }
                            break;
                        }
                    }

                if (i == n)
                {

                    printf("produit invalide \n");
                }
                printf("votre somme totale est %f ,si vous voulez continuer, veuillez repondre par oui( sinon non)\n", s);
                printf("tapez votre choix :");
                verif(continuer);
                scanf("%s", continuer);
                if (strcmp(continuer, "non") == 0)
                    break;
                else if (strcmp(continuer, "oui") == 0)
                    printf("choisir un autre produit \n");
            }

            printf("prix total : %f \n", s);
            fprintf(fptr5, "Montant total a payer avant remise:  %f\n\n", s);
            fprintf(fptr5, "Montant a payer apres remise:  %f \n\n", s - s * 0.15);
            fclose(fptr5);
        }
        printf("Est ce que vous avez une carte de fidelite ? (oui/non) \n ");
        printf("votre choix:");
        char x[10];
        scanf("%s", x);
        verif(x);
        printf("donnez-nous vos coordon�es \n");
        printf("nom et prenom : \n");
        char name[50];
        getchar();
        fgets(name, 50, stdin);
        printf("num de la carte cin:");
        int carte;
        scanf("%d", &carte);
        struct liste *tete = NULL;
        tete = ajouterclient("flen el fouleni", 123456, tete);

        if (strcmp(x, "non") == 0)
        {

            tete = ajouterclient(name, carte, tete);
            printf("vous etes ajoutes avec succes \n");
        }
        else
        {
            if (verifcation(carte, tete) == 1)
            {
                int solde;
                solde = s - s * 0.15;
                printf("vous avez une r�duction de 15% , votre solde est %d", solde);
            }
            else
            {
                printf("vous n'etes pas un client , on va vous ajouter \n");
                tete = ajouterclient(name, carte, tete);
                printf("vous etes ajoutes avec succes \n");
            }
        }
    }
    printf("\n\nAU REVOIR !\n");
    return 0;
}
