#include<stdio.h>
#include<stdlib.h>
#include<string.h>



//1.)**********************************

typedef struct person person;
struct person
{
    char prenom[30];
    int age;
    person *frere_soeur;
    person *fils;   
    person *parent;
} ;

typedef person *arbre;


void init_arbre(arbre *pa){
    *pa = NULL;

};

//2.)***************************************

void ajout_membre(arbre *pa, char nom_parent[20], char prenom[20], int age, char *affiliation) {
    person *nouveau = (person *)malloc(sizeof(person));
    strcpy(nouveau->prenom, prenom);
    nouveau->age = age;
    nouveau->frere_soeur = NULL;
    nouveau->fils = NULL;

    if (*pa == NULL) {
        *pa = nouveau;
        return;
    }

    if (strcmp(affiliation, "frere") == 0 || strcmp(affiliation, "soeur") == 0) {
        if (strcmp((*pa)->prenom, nom_parent) == 0) { //si la racine est le parent du new mbr
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
                person *temp = (*pa)->fils;
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







//3.)****************************************



int est_membre(arbre *pa, char prenom[20]) {
    if (*pa == NULL)  //Si l'arbre est vide
        return 0;    //on ne peut pas etre mbr d'un arbre arbre vide(donc il n'est pas mbr)
    if (strcmp((*pa)->prenom, prenom) == 0)// on verifie d'abord si le mbr est la racine
        return 1;                         //si c'est le cas on return 1(il est mbr)
    return est_membre(&((*pa)->frere_soeur), prenom) || est_membre(&((*pa)->fils), prenom);
}


//4.)**************************************

void freres(arbre *pa, char prenom[20]) {
    if (*pa == NULL) {
        printf("Arbre vide.\n");
        return;
    }
    if (strcmp((*pa)->prenom, prenom) == 0) {
        person *frere = (*pa)->frere_soeur;
        while (frere != NULL) {
            printf("%s, %d\n", frere->prenom, frere->age);
            frere = frere->frere_soeur;
        }
    } else {
        freres(&((*pa)->frere_soeur), prenom);
        freres(&((*pa)->fils), prenom);
    }
}

//5.)**************************************

void enfants(arbre *pa, char prenom[20]) {
    if (*pa == NULL) {
        printf("Arbre vide.\n");
        return;
    }
    if (strcmp((*pa)->prenom, prenom) == 0) {
        person *enfant = (*pa)->fils;
        while (enfant != NULL) {
            printf("%s, %d\n", enfant->prenom, enfant->age);
            enfant = enfant->frere_soeur;
        }
    } else {
        enfants(&((*pa)->frere_soeur), prenom);
        enfants(&((*pa)->fils), prenom);
    }
}

//6.)**************************************
void parent(arbre *pa, char prenom[20]) {
    if (*pa == NULL) {
        printf("Arbre vide.\n");
        return;
    }
    if ((*pa)->fils != NULL) {
        person *enfant = (*pa)->fils;
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

//7.)**************************************

void affiche_arbre(arbre *pa) {
    if (*pa != NULL) {
        printf("%s, %d\n", (*pa)->prenom, (*pa)->age);
        affiche_arbre(&((*pa)->fils));
        affiche_arbre(&((*pa)->frere_soeur));
    }
}





//8.)**************************************


int main()

{
   arbre day;
   init_arbre(&day);

    char choix;
    char prenom[30];
    int age;
    char affiliation[10];
    char nomparent[30];
    char personne[20];



     
    do
    {
        printf("\n");

        printf("/**********MENU**********/ \n");
        printf("Quelles operation voudraiez vous effectuer sur l'arbre? \n");
        printf("1.Verifier l'appartenance d'une personne à la famille \n");
        printf("2.Connaitre les freres et soeur d'un membre de la famille \n");
        printf("3.Connaitre les enfants d'un membre de la famille \n");
        printf("4.Connaitre le parent d'un membre de la famille \n");
        printf("5.Afficher l'arbre de la famille \n");
        printf("6.Ajouter un membre  \n");

        printf("\n");
        
        int val;
        printf("Veuillez choisi une fonction (1,2,3,4,5):"); 
        scanf("%d",&val);


        switch (val)
        {
            case 1:
                
                printf("Veuillez saisir le prenom de la personne:\n");
                scanf("%s",personne);
                    if (est_membre(&day,personne) == 1)
                    {
                        printf("%s est membre de la famille \n",personne);
                    }
                    else
                    {
                     printf("%s n'est pas membre de la famille \n",personne);
                    }
                printf("Voulez vous retourner au menu?(o/n):");
                scanf(" %c",&choix);
                getchar();
            
            break;

            case 2:
             printf("Veuillez saisir le prenom de la personne:\n");
             scanf("%s",personne);
            
            break;

            case 3:
            /* code */
            break;

            case 4:
            /* code */
            break;

            case 5:
            /* code */
            break;

            case 6:
           
                 printf("Entrez le prenom du parent : \n");
                 scanf("%s",nomparent);
                 getchar();
                 printf("Entrez le prenom de la personne : \n");
                 scanf("%s", prenom);
                 getchar();
                 printf("Entrez l'age de la personne : \n");
                 scanf("%d", &age);
                 getchar();
                 printf("Entrez l'affiliation de la personne : ");
                 scanf("%s", affiliation);
                 getchar();
                 if (day == NULL)
                 {
                    ajout_membre(&day,NULL,age,prenom,NULL);
                 }
                 else
                 {
                    ajout_membre(&day,nomparent,age,prenom,affiliation) ;
                 }

                 printf("Voulez vous retourner au menu?(o/n):");
                 scanf(" %c",&choix);
                 getchar();

             
            break;

        
        default:
            break;
        }
        
            


    } while (choix == 'o');
   
   
    






 return 0;

}
