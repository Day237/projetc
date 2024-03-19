#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition de la structure person
typedef struct person {
    char prenom[30];
    int age;
    struct person *frere_soeur;
    struct person *fils;   
    struct person *parent;
} Person;

// Définition du type Arbre pour un pointeur de structure person
typedef struct person *Arbre;

// Fonction pour initialiser un arbre
void init_arbre(Arbre *pa) {
    *pa = NULL;
}

// Fonction pour ajouter un membre à l'arbre
void ajout_membre(Arbre *pa, char nom_parent[30], char prenom[30], int age, char *affiliation) {
    if (strlen(prenom) >= 30) {
        printf("Erreur: le prénom est trop long.\n");
        return;
    }
    
    Person *nouveau = (Person *)malloc(sizeof(Person));
    if (nouveau == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        return;
    }

    strcpy(nouveau->prenom, prenom);
    nouveau->age = age;
    nouveau->frere_soeur = NULL;
    nouveau->fils = NULL;

    if (*pa == NULL) {
        *pa = nouveau;
        return;
    }

    if (strcmp(affiliation, "frere") == 0 || strcmp(affiliation, "soeur") == 0) {
        if (strcmp((*pa)->prenom, nom_parent) == 0) {
            nouveau->frere_soeur = *pa;
            *pa = nouveau;
        } else {
            ajout_membre(&((*pa)->frere_soeur), nom_parent, prenom, age, affiliation);
        }
    } else if (strcmp(affiliation, "enfant") == 0) {
        if (strcmp((*pa)->prenom, nom_parent) == 0) {
            if ((*pa)->fils == NULL) {
                (*pa)->fils = nouveau;
            } else {
                Person *temp = (*pa)->fils;
                while (temp->frere_soeur != NULL) {
                    temp = temp->frere_soeur;
                }
                temp->frere_soeur = nouveau;
            }
        } else {
            ajout_membre(&((*pa)->fils), nom_parent, prenom, age, affiliation);
        }
    } else {
        printf("Type d'affiliation invalide.\n");
        free(nouveau);
    }
}

// Fonction pour vérifier si un membre est dans l'arbre
int est_membre(Arbre *pa, char prenom[30]) {
    if (*pa == NULL)
        return 0;
    if (strcmp((*pa)->prenom, prenom) == 0)
        return 1;
    return est_membre(&((*pa)->frere_soeur), prenom) || est_membre(&((*pa)->fils), prenom);
}

// Fonction pour afficher les frères/sœurs d'un membre
void freres(Arbre *pa, char prenom[30]) {
    if (*pa == NULL) {
        printf("Arbre vide.\n");
        return;
    }
    if (strcmp((*pa)->prenom, prenom) == 0) {
        Person *frere = (*pa)->frere_soeur;
        while (frere != NULL) {
            printf("%s, %d\n", frere->prenom, frere->age);
            frere = frere->frere_soeur;
        }
    } else {
        freres(&((*pa)->frere_soeur), prenom);
        freres(&((*pa)->fils), prenom);
    }
}

// Fonction pour afficher les enfants d'un membre
void enfants(Arbre *pa, char prenom[30]) {
    if (*pa == NULL) {
        printf("Arbre vide.\n");
        return;
    }
    if (strcmp((*pa)->prenom, prenom) == 0) {
        Person *enfant = (*pa)->fils;
        while (enfant != NULL) {
            printf("%s, %d\n", enfant->prenom, enfant->age);
            enfant = enfant->frere_soeur;
        }
    } else {
        enfants(&((*pa)->frere_soeur), prenom);
        enfants(&((*pa)->fils), prenom);
    }
}

// Fonction pour afficher le parent d'un membre
void parent(Arbre *pa, char prenom[30]) {
    if (*pa == NULL) {
        printf("Arbre vide.\n");
        return;
    }
    if ((*pa)->fils != NULL) {
        Person *enfant = (*pa)->fils;
        while (enfant != NULL) {
            if (strcmp(enfant->prenom, prenom) == 0) {
                printf("Le parent de %s est %s.\n", prenom, (*pa)->prenom);
                return;
            }
            enfant = enfant->frere_soeur;
        }
    }
    parent(&((*pa)->frere_soeur), prenom);
    parent(&((*pa)->fils), prenom);
}

// Fonction pour afficher l'arbre
void affiche_arbre(Arbre *pa) {
    if (*pa != NULL) {
        printf("%s, %d\n", (*pa)->prenom, (*pa)->age);
        affiche_arbre(&((*pa)->fils));
        affiche_arbre(&((*pa)->frere_soeur));
    }
}

// Fonction principale
int main() {
    Arbre arbre;
    init_arbre(&arbre);
    
    int choix;
    char prenom[30], nom_parent[30], affiliation[10];
    int age;
    
    do {
        printf("\n/**********MENU**********/\n");
        printf("Quelles operations voulez-vous effectuer sur l'arbre?\n");
        printf("1. Verifier l'appartenance d'une personne à la famille\n");
        printf("2. Connaitre les frères et sœurs d'un membre de la famille\n");
        printf("3. Connaitre les enfants d'un membre de la famille\n");
        printf("4. Connaitre le parent d'un membre de la famille\n");
        printf("5. Afficher l'arbre de la famille\n");
        printf("6. Ajouter un membre\n");
        printf("7. Reinitialiser l'arbre\n");
        printf("8. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez le prénom de la personne à vérifier : ");
                scanf("%s", prenom);
                if (est_membre(&arbre, prenom))
                    printf("%s est un membre de la famille.\n", prenom);
                else
                    printf("%s n'est pas un membre de la famille.\n", prenom);
                break;
            case 2:
                printf("Entrez le prénom du membre : ");
                scanf("%s", prenom);
                printf("Frères et sœurs de %s :\n", prenom);
                freres(&arbre, prenom);
                break;
            case 3:
                printf("Entrez le prénom du membre : ");
                scanf("%s", prenom);
                printf("Enfants de %s :\n", prenom);
                enfants(&arbre, prenom);
                break;
            case 4:
                printf("Entrez le prénom du membre : ");
                scanf("%s", prenom);
                printf("Parent de %s :\n", prenom);
                parent(&arbre, prenom);
                break;
            case 5:
                // printf("Arbre de la famille :\n");
                // affiche_arbre(&arbre);
                // break;
                
                printf("Arbre de la famille :\n");
                affiche_arbre(&arbre);
                printf("\nAppuyez sur Entrée pour retourner au menu...");
                while (getchar() != '\n'); // Vidage du tampon d'entrée
                getchar(); // Attendre que l'utilisateur appuie sur Entrée
                break;

            case 6:
                printf("Entrez le prénom du nouveau membre : ");
                scanf("%s", prenom);
                printf("Entrez l'age du nouveau membre : ");
                scanf("%d", &age);
                printf("Entrez le prénom du parent : ");
                scanf("%s", nom_parent);
                printf("Entrez l'affiliation (frere/soeur/enfant) : ");
                scanf("%s", affiliation);
                ajout_membre(&arbre, nom_parent, prenom, age, affiliation);
                break;
            case 7:
                init_arbre(&arbre);
                printf("Arbre reinitialise.\n");
                break;
            case 8:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 8);

    return 0;
}

