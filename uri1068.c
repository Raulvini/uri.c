#include<stdio.h>
#include<stdlib.h>


typedef struct pilha{
    char parentese;
    struct pilha *prox;
}Pilha;

Pilha * push (Pilha * p, char v){
    Pilha * novo = (Pilha*)malloc(sizeof(Pilha));
    novo->parentese = v;
    novo->prox = p;
   
    return novo;
 }


void imprimir (Pilha * p){
    Pilha * p1;
    for (p1=p ; p1!=NULL ; p1=p1->prox)
    printf ("%c", p1->parentese);
}
Pilha * pop(Pilha * p){
    if (p == NULL){
    return p;
    }
    Pilha * aux = p;
    p = p -> prox;
    free(aux);
    return p;
}

Pilha * criar (){
    return NULL;
}



int main(){
    Pilha *aberto = NULL;
    Pilha *fechado = NULL;
    
    char expressao[1000];
    char parentese;
    int i;
    scanf("%s", expressao);
    
        for(i = 0;  i<1000 ;i++)
        {
            parentese = expressao[i];
            if (parentese==40){
                aberto = push(aberto,parentese);
            }
            if (parentese==41){
                fechado = push(fechado,parentese);
                if (aberto == NULL){
                    break;
                }
                else{
                    pop(aberto);
                    pop(fechado);
                }
            }
        }
        imprimir(aberto);
        imprimir(fechado);
        if(aberto==NULL && fechado==NULL){
            printf("correct\n");
        }
        else{
            printf("incorrect\n");
        }
    
    return 0;
}