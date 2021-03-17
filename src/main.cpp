#include <stdio.h>
#include <stdlib.h>

using namespace std;

void increCam(int c){
    printf("\n\t Caminho %d: ", c);
}

void increDist(int d){
    printf("\n\t Distancia %d: ", d);
}

void init(){
   printf(
    "\n\t    0 1 2 3 4 5 6 7 8 9 10\n\n\t 0  0 1 0 2 6 0 0 0 0 0 0\n\t 1  1 0 2 0 5 3 9 0 0 0 0\n\t 2  0 2 0 0 0 0 7 9 0 0 0\n\t 3  2 0 0 0 8 0 0 0 1 0 0\n\t 4  6 5 0 8 0 1 0 0 7 2 0\n\t 5  0 3 0 0 1 0 6 0 0 4 0\n\t 6  0 9 7 0 0 6 0 2 0 3 1\n\t 7  0 0 9 0 0 0 2 0 0 0 4\n\t 8  0 0 0 1 7 0 0 0 0 9 0\n\t 9  0 0 0 0 2 4 3 0 9 0 1\n\t10  0 0 0 0 0 0 1 4 0 1 0"
    );
   printf("\n\n\tAcima o grafo em matriz adjacente: \n\n");
}

void infoVert(){
    printf("\n  Informe os vertices \n\n\n");
}

typedef struct caminhos{
    int vi,vf;
    struct caminhos * proximo;
}t_cam;

typedef struct distancias{
    int valor;
    struct distancias * proximo;
}t_dist;

int main()
{

    ///Definicoes para struct Caminhos
    t_cam * ini_cam; t_cam * proximo_cam;
    ini_cam = (t_cam *)malloc(sizeof(t_cam));
    if(ini_cam == NULL){ exit(1);}
    proximo_cam = ini_cam;

    /// Definicoes para struct Distancias
    t_dist * ini_dist; t_dist * proximo_dist;
    ini_dist = (t_dist *)malloc(sizeof(t_dist));
    if(ini_dist == NULL){exit(1);}
    proximo_dist = ini_dist;

    int grafo[11][11] = {
        {0,1,0,2,6,0,0,0,0,0,0},
        {1,0,2,0,5,3,9,0,0,0,0},
        {0,2,0,0,0,0,7,9,0,0,0},
        {2,0,0,0,8,0,0,0,1,0,0},
        {6,5,0,8,0,1,0,0,7,2,0},
        {0,3,0,0,1,0,6,0,0,4,0},
        {0,9,7,0,0,6,0,2,0,3,1},
        {0,0,9,0,0,0,2,0,0,0,4},
        {0,0,0,1,7,0,0,0,0,9,0},
        {0,0,0,0,2,4,3,0,9,0,1},
        {0,0,0,0,0,0,1,4,0,1,0}
    };

    int i=0,f=0,c,k=0,z=1,totalDist=0,menorDist=0; /// dist = distancia, l = linha (vertice 1), c = coluna (vertice 2)
    bool lig0 = false;
    char R;

    /*** testando o total de caminhos
    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
           if(grafo[i][j] > 0){
                camPoss++;
           }
        }
    }

    printf("\n A quantidade de caminhos possiveis: %d \n\n",camPoss);
    system("pause");
    ***/

    prox_tentativa:
    totalDist=0;
    c=0;

    do{
        init();
        printf("\n\t  Informe os vertices \n\n");
        printf("\n\t  distancia %d \n",++c);
        if(c<2){
            reset1:
            printf("\n\n\t  Informe o vertice incial: ");
            scanf("%d",&(proximo_cam->vi));
            printf("\n\t  Informe o vertice final: ");
            scanf("%d",&(proximo_cam->vf));
            i = proximo_cam->vi;
            f = proximo_cam->vf;
            if(((int)i<0) || ((int)i>11) || ((int)f<0) || ((int)f>11)){proximo_cam->vi=0; proximo_cam->vf=0; if(c==1){c=1;}else{c=c;} system("cls"); init(); printf("\n\t  Informe os vertices \n\n"); printf("\n\t  Msg Error: informe o valor de acordo com o grafo \n"); goto reset1;}
        }else{
            proximo_cam->vi = f;
            i=f;
            reset2:
            printf("\n\n\t  Informe os vertices restantes: ");
            scanf("%d",&(proximo_cam->vf));
            f = proximo_cam->vf;
            if((f<0) || (f>11)){proximo_cam->vf=0; if(c==1){c=1;}else{c=c;} system("cls"); init(); printf("\n\t  Msg Error: informe o valor de acordo com o grafo \n"); goto reset2;}
            proximo_cam->vf = f;
        }
        if(proximo_cam -> vf != 7){
            proximo_cam -> proximo = (t_cam *)malloc(sizeof(t_cam));
            proximo_cam = proximo_cam->proximo;
        }
        if(grafo[i][f] > 0){
         totalDist += grafo[i][f];
        }else{
            lig0 = true;
        }
        system("cls");
    }while(proximo_cam -> vf != 7);

    if(lig0){
        totalDist=0;
    }

    proximo_dist -> valor = totalDist;

    printf("\n\n\t ### OPCOES PARA CONTINUAR ###\n\n\t [s] Sim \n\n\t [n] Nao \n\n\n\t Voce deseja realizar outro teste de caminho ? \n\n\t Resposta: ");
    scanf(" %c",&R);

    if(R == 's' || R == 'S'){
        proximo_cam -> proximo = (t_cam *)malloc(sizeof(t_cam));
        proximo_cam = proximo_cam->proximo;
        proximo_dist -> proximo = (t_dist *)malloc(sizeof(t_dist));
        proximo_dist = proximo_dist->proximo;
        goto prox_tentativa;
    }

    system("cls");

    printf("\n\n   Lista de Caminhos Escolhidos: \n\n");
    proximo_cam -> proximo = NULL;
    proximo_cam = ini_cam;
    increCam(z);
    while(proximo_cam != NULL){

        if(k==0){
            printf(" %d -- %d", ++(proximo_cam->vi),++(proximo_cam->vf));
        }else{
            printf(" -- %d", ++(proximo_cam->vf));
        }

        k++;

        if(proximo_cam->vf == 8){
            printf("\n");
            k=0;
            if(proximo_cam -> proximo != NULL){
                increCam(++z);
            }
        }
        proximo_cam = proximo_cam -> proximo;
    }

    z=1;
    k=0;

    printf("\n\n\n   Lista de Distancias Totais: \n\n");
    proximo_dist -> proximo = NULL;
    proximo_dist = ini_dist;
    increDist(z);
    while(proximo_dist != NULL){

        if(z==1){menorDist = (proximo_dist -> valor);}

        if(proximo_dist->valor != 0){
          printf(" %d\n", proximo_dist->valor);
        }else{
          printf(" nao foi calculada, caminho incorreto \n");
        }

        if((proximo_dist -> valor) < menorDist){
            menorDist = (proximo_dist -> valor);
        }else{
            menorDist = menorDist;
        }

        if(proximo_dist -> proximo != NULL){
          increDist(++z);
        }
        proximo_dist = proximo_dist -> proximo;
    }
    printf("\n\n   Calculos do Grafo: ");
    printf("\n\n\t A menor distancia calculada foi: %d \n\n\n",menorDist);
    system("pause");
    system("taskkill /IM cb_console_runner.exe");
}
