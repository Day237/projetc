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

//typedef person *arbre;

typedef struct arbre arbre;
struct arbre{
    person *racine;
};

void init_arbre(arbre *pa){
    pa->racine = NULL;

};

//2.)***************************************








//3.)****************************************

int est_membre(arbre *A,char prenom[30]){

    if(A->racine = NULL){ //Si l'arbre est vide 
        return 0;     //on ne peut pas etre mbr d'un arbre arbre vide(donc il n'est pas mbr)
    }
    if(strcmp(A->racine->prenom,prenom)==0){// on verifie d'abord si le mbr est la racine
        return 1;                           //si c'est le cas on return 1(il est mbr)
    }
    else {//sinon on recommence sur le flanc gauche ou le flanc droit
        return est_membre(A->racine->frere_soeur,prenom) || est_membre(A->racine->fils,prenom);
    } //l'opérateur ou || permet de faire un parcour en profondeur préfixé(la première fois que je vois un noeud je l'affiche)
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
                scanf("%c",personne);
                    if (est_membre(&day,personne) == 1)
                    {
                        printf("%c est membre de la famille",personne);
                    }
                    else
                    {
                     printf("%c n'est pas membre de la famille",personne);
                    }
                printf("Voulez vous retourner au menu?(o/n):");
                scanf("%c",&choix);
            
            break;

            case 2:
            /* code */
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
             scanf("%c",nomparent);
             printf("Entrez le prenom de la personne : \n");
             scanf("%s", prenom);
             printf("Entrez l'age de la personne : \n");
             scanf("%d", &age);
             printf("Entrez l'affiliation de la personne :\n ");
             scanf("%s", affiliation);
            //  if (/*l'arbest est vide */)
            //  {
            //     /* ajout_membre(&arbre,NULL,age,prenom,NULL);*/
            //  }
            //  else
            //  {
            //     /* ajout_membre(&arbre,nomparent,age,prenom,affiliation) */
            //  }
             
            break;

        
        default:
            break;
        }
        
            


    } while (choix == 'o');
   
   
    






 return 0;

}
