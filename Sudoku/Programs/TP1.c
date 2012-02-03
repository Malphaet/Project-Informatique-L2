/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>

/* ========= Defines ==========*/
#define DIM 9
#define DIM_LINE 21

#define GRID_FILE "./grille.txt"
#define GBSIZE (2*DIM+3*(DIM/3)+1)
/* ========= Typedef ==========*/
typedef struct CASE{
	int chiffres[DIM];
	int nb_candidats;
	int chiffre;
} CASE;
typedef CASE GRILLE[DIM][DIM];

/* ======== Prototype =========*/
void init_grille(GRILLE grille);
void affiche_grille(GRILLE grille);
void saisie_grille(GRILLE grille,char adr[]);
void init_case(CASE *c);
void remplir_case(GRILLE grille, CASE *c, int i);

/* =========== Main ===========*/

int main(void){
	char path[]="../Data/grille.txt";
	GRILLE grille;	
	init_grille(grille);
	saisie_grille(grille,path);
	affiche_grille(grille);
	return 0;
}

/* ========= Functions ========*/

void init_grille(GRILLE grille){
	int i,j;
	CASE c;
	init_case(&c);
	for (i=0;i<DIM;i++){
		for (j=0;j<DIM;j++){
			grille[i][j]=c;
		}
	}
}

void affiche_grille(GRILLE grille){
	int i,j;
	printf("\n"); for (j=0;j<GBSIZE;j++) printf("-"); printf("\n");
	for (i=0;i<DIM;i++){ 
		printf("| ");
		for (j=0;j<DIM; j++){ printf("%d ",grille[i][j].chiffre); if ((j+1)%3==0) printf(" | "); }
		if ((i+1)%3==0) { printf("\n"); for (j=0;j<GBSIZE;j++) printf("-"); }
		printf("\n");
	}
	printf("\n");
}

void saisie_grille(GRILLE grille, char adr[]){
	int i,j,nb;
	CASE c;
	FILE* f = fopen(adr, "r");
	
	for (i=0;i<DIM;i++){
		for (j=0;j<DIM;j++) {
			fscanf(f, "%d,", &nb);
			remplir_case(grille,&c,nb);
			grille[i][j]=c;
		}
		fgetc(f);
	}
	fclose(f);
}

void init_case(CASE *c){
	int i;
	for (i=0;i<DIM;i++) c->chiffres[i]=1;
	c->nb_candidats=DIM;
	c->chiffre=0;
}

void afficher_case(CASE *c){
	int i;
	printf("Nombre de candidats : %d\n",c->nb_candidats);
	printf("Candidats : "); for (i=0;i<DIM;i++) printf("%d ",c->chiffres[i]); printf("\n");
	printf("Case remplie : %d",c->chiffre==0);
}
void remplir_case(GRILLE grille, CASE *c, int i){
	c->chiffre=i;
}
