#include <stdio.h>
#include <stdlib.h>


typedef struct person person;
struct person
{
    char prenom[30];
    int age;
    char affiliation[10];
    person *fg;
    person *fd;
    person *parent;
} ;

typedef person *arbre;

void init_arbre(arbre *pa){
    *pa == NULL;

};

void Ajoutmembre(arbre *pa ,parent, )



//espaaaaaaaaaaaaaaaaaaaaace


int main()
{

}

