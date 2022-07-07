#include<stdio.h>
#include<stdlib.h>

typedef struct lista{
    int info;
    struct lista *prox;
}Lista;

Lista * criar(){
    return NULL;
}

Lista * novo(){
    Lista * new = (Lista*)malloc(sizeof(Lista));
    return new;
}

Lista * inserir(Lista * L, int valor){
    Lista * new = novo();
    new->info = valor;
    new->prox = L;
    return new;
}
Lista *inserir_final(Lista * L , int num){
    Lista * new = novo();
    new->prox = NULL;
    new->info = num;
    if (L == NULL){
        return new;
    }
    else{
        Lista * aux = L;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = new;
    }
    return L;
}


void imprimir(Lista * L){
    Lista * aux = L;
    while(aux!=NULL){
        printf ("A%d ",aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

int main(){
    Lista *leste = criar(), *oeste = criar(), *norte = criar(), *sul = criar(), *resultado = criar();
    int num;

    scanf("%d", &num);

    while (num != 0)
    {
        if(num == -4){
            
            while(num == -4 || num >0){
                
                scanf ("%d", &num);
                if (num > 0 && num <1001){
                   leste = inserir_final(leste,num);
                    
                }
            }
           
            
        }

        else if(num == -1){
            
            while(num == -1 || num >0){
                scanf ("%d", &num);
                if(num >0 && num <1001){
                   oeste = inserir_final(oeste,num);
                    
                }
                
            }
           
        }

        else if(num == -3){
            
            while(num == -3 || num >0){
                scanf ("%d", &num);
                if(num > 0 && num< 1001){
                  norte = inserir_final(norte,num);
                }
                
            }
           
        }

        else if(num == -2){
            
            while(num == -2 ||  num >0){
                scanf ("%d", &num);
                if( num > 0 && num < 1001){
                 sul  = inserir_final(sul,num);
                }
                
            }
           
        }
    }
   
    while(oeste !=NULL || norte !=NULL || sul!=NULL || leste!=NULL){
        if (oeste!= NULL){
           num = oeste->info;
           resultado = inserir_final(resultado,num);
           oeste = oeste->prox;
        }
        if (norte!= NULL){
            num = norte->info;
            resultado = inserir_final(resultado,num);
            norte = norte->prox;
        }
        if (sul!= NULL){
           num = sul->info;
           resultado = inserir_final(resultado,num);
           sul = sul->prox;
            
        }
        if (leste!= NULL){
            num = leste->info;
            resultado = inserir_final(resultado,num);
            leste = leste->prox;
           
        }
    }
    imprimir(resultado);
    return 0;
}