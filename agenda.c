#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>a
#include <ctype.h>


#define TAM_VET 100

enum tipoEndereco {Alameda, Avenida, Praca, Rua, Travessa};
enum tipoContato {Celular, comercial, fixo, pessoal, fax};
enum tipoRedeSocial {Instagram, Facebook, Linkedin};

struct registro{ 
    char nome[ TAM_VET];
    enum tipoContato TpCon;
    char numero_tel [11];
    enum tipoEndereco TpEnd;                    
    char endereco [TAM_VET]; 
    int numero[TAM_VET];
    enum tipoRedeSocial TpRS;
    char RedeSocial[TAM_VET];
    char email [TAM_VET];
}agenda[200];

char *obtertipodecont ( enum tipoContato TpCon )
{
    const char *tipodecont[] =
    {
        "", "Celular", "Comercial", "Fixo", "Pessoal", "Fax"
    };

    return ( tipodecont [ TpCon ] );
}

char *obterNomeEndereco ( enum tipoEndereco TpEnd )
{
    const char *nomeEndereco[] =
    {
        "Al.", "Av.", "Pr.", "Rod.", "R.", "Tr."
    };

    return ( nomeEndereco [ TpEnd ] );
}
char *obterRede ( enum tipoRedeSocial TpRS )
{
    const char *nomedarede[] =
    {
        "", "Instagram", "Facebook", "linkedin"
    };

    return ( nomedarede [ TpRS ] );
}
int menuAgenda (){
    int opcao;
    printf ("MENU AGENDA\n");
    printf ("1 - Adicionar\n2 - Editar\n3 - Ver contato\n4 - Excluir\n5 - Ver agenda\n6 - Sair\n");
    printf ("Digite sua opção: ");
    scanf("%i", &opcao);

    limparTela();

    return opcao;
}

void limparTela(void){
    #ifdef linux
        system ("clear");
    #elif _WIN32
        system ("cls");
    #endif
    }

void criarContato (int *total){
        int verificanum = 0, verificaemail = 0;
        
        printf("Nome: ");
        fflush(stdin);
        scanf("%[^\n]s", agenda[*total].nome);

        printf ("Tipo de Telefone: \n");
        printf ("1 - Celular\n2 - Comercial\n3 - Fixo\n4 - Pessoal\n5 - Fax\n");
        fflush (stdin);
        scanf ("%i", &agenda[*total].TpCon);

        while(verificanum == 0){
            printf("Número : ");
            fflush(stdin);
            scanf("%[^\n]s", agenda[*total].numero_tel);
        
            verificanum = verificarNumero_Tel(agenda->numero_tel);
        }
        
        while(verificaemail == 0){
            printf("Email: ");
            fflush(stdin);
            scanf("%[^\n]s", agenda[*total].email);
            verificaemail = verificarEmail(agenda->email);
        }

        limparTela();
        
        printf ("Tipo de endereço: \n");
        printf ("1 - Alameda\n2 - Avenida\n3 - Praça\n4 - Rua\n5 - Travessa\n");
        printf ("Digite sua opção: ");
        fflush (stdin);
        scanf ("%i", &agenda[*total].TpEnd);

        printf("Endereço: ");
        fflush(stdin);
        scanf("%[^\n]s", agenda[*total].endereco);

        printf("Número (casa): ");
        fflush(stdin);
        scanf("%i", agenda[*total].numero);

        limparTela();

        printf ("Tipo de rede social: \n");
        printf ("1 - Instagram\n2 - Facebook\n3 - Linkedln\n");
        fflush (stdin);
        scanf ("%i", &agenda[*total].TpRS);

        printf ("Digite seu Username: ");
        fflush(stdin);
        scanf("%[^\n]s", agenda[*total].RedeSocial);
        fflush(stdin);

        limparTela();

        if(*total != 0){
            ordenarCont(*total);

        }

        (*total)++;
        
}

void mostrarContatos (int *total){
    int i, j = 20;
    char enter;
    if (*total == 0){
        printf("Agenda vazia\n!");
    }
    else{
         for (i = 0; i < *total; i++){
    
            printf ("Nome: %-20s|", agenda[i].nome);
            printf ("%s: %-15s|", obtertipodecont(agenda[i].TpCon), agenda[i].numero_tel);
            printf ("Email: %-25s|", agenda[i].email);
            printf ("%s: %-15s|", obterRede(agenda[i].TpRS), agenda[i].RedeSocial);
            printf ("%s %-15s|\n", obterNomeEndereco(agenda[i].TpEnd), agenda[i].endereco);
            if (i == j){
                printf("Digite Enter para continuar.");
                while(scanf("%c", &enter)){
                    if(enter == 13){
                       j += j;
                       break;
                    }
                    
                }



            }
        } 
    }
   
}


void salvarArquivo(int total){

    FILE *ptrArquivo;

    ptrArquivo = fopen("dados.csv","w");

    if(ptrArquivo == NULL){
        printf("Erro!");   
    }

    int i;
    for (i = 0; i < total; i++){
        fprintf(ptrArquivo, "%s;%i;%s;%s;%i;%s;%i;%s", agenda[i].nome,  agenda[i].TpCon, agenda[i].numero_tel, agenda[i].email, agenda[i].TpEnd, agenda[i].endereco, agenda[i].TpRS, agenda[i].RedeSocial);
        fprintf(ptrArquivo, "\n");
    }

    fclose(ptrArquivo);

}


int lerArquivo(){

    FILE *ptrArquivo = NULL;

    char line[TAM_VET];

    int aux;

    int total = 0;
    char *tok;


    ptrArquivo = fopen("dados.csv","r");

    if(ptrArquivo == NULL){
        printf("Não há arquivos pra ler!\n");   
        return 0;
    }

    while((fgets(line, sizeof(line), ptrArquivo)) != NULL){

        tok = strtok(line, ";");
        strcpy(agenda[total].nome, tok);

        tok = strtok(NULL, ";");
        aux = atoi(tok);
        agenda[total].TpCon = aux;

        tok = strtok(NULL, ";");
        strcpy(agenda[total].numero_tel, tok);

        tok = strtok(NULL, ";");
        strcpy(agenda[total].email, tok);

        tok = strtok(NULL, ";");
        aux = atoi(tok);
        agenda[total].TpEnd = aux;

        tok = strtok(NULL, ";");
        strcpy(agenda[total].endereco, tok);

        tok = strtok(NULL, ";");
        aux = atoi(tok);
        agenda[total].TpRS = aux;

        tok = strtok(NULL, ";");
        strcpy(agenda[total].RedeSocial, tok);
            
        total++;
    }

    fclose(ptrArquivo);

    return total;

}


int verificarNumero_Tel (char numero_tel[]){
    int i , aux;
    aux = strlen(numero_tel);
    if(aux>11){
        printf ("Número inválido, digite apenas 11 caracteres!\n");
        return 0;
    }
    else if(aux<11){
        printf ("Número inválido, digite  11 caracteres!\n");
        return 0;
    }
    for (i = 0; i < 10; i++){
        if (numero_tel[i] <48 || numero_tel[i]>57){
            printf ("Número inválido, digite apenas numeros!\n");
            return 0;
        }
     
        }
        return 1;
    }


int verificarEmail (char email[]){
    int i, contarroba = 0, contponto = 0, arroba;
    for(i = 0 ; i < TAM_VET; i++){
        if (email[i] == 64){
            contarroba += 1;
        }
        else if(email[i] == 46){
            contponto += 1;
        }
    }
    if (contarroba!= 1 || contponto == 0){
         printf ("Email inválido!\n");
         return 0;
    }
    else{
        for (i = 0; i < TAM_VET; i++){
            if (email[0] == 64){
                printf ("Email inválido!\n");
                return 0;
            }
            else if(email[i+1] == 64){
                arroba =i+1;
            }
        }
        
        for(i = arroba; i < TAM_VET; i++){
            if(email[i+1] == 46){
                return 1;
            }
        }
        printf ("Email inválido!\n");
        return 0;
    }
   
 }
    

void editarcontato (int *total){
    int *i, comparacao;
    char opc = 'N', nome[TAM_VET];
    while(opc == 78){
        printf("digite um nome:\n");
        scanf("%s", nome);

        for (i = 0; i < *total; i++){
            comparacao = strcmp(nome, agenda[*i].nome);
            if (comparacao == 0){
                printf ("%s\n", agenda[*i].nome);
                printf ("%s:%s\n", obtertipodecont(agenda[*i].TpCon), agenda[*i].numero_tel);
                printf ("%s\n", agenda[*i].email);
                printf ("%s %s\n", obterNomeEndereco(agenda[*i].TpEnd), agenda[*i].endereco);
                printf ("%s:%s\n", obterRede(agenda[*i].TpRS), agenda[*i].RedeSocial);
                printf("Deseja editar esse contato: s/n");
                scanf("%c", &opc);
            
                if(opc == 110 || opc == 115){
                    opc -= 32;
                }
                if(opc == 83){
                    criarContato(*i);
                    break;
                }

            
            }
        }
    }
}
void ordenarCont(int *total){
    int comparador, i , j;
    struct registro aux;
    int TAM_STR = strlen(agenda[*total].nome);
    for ( i = 0; i < *total; i++){
        for(j = i+ 1; j <TAM_STR; j++)
        agenda[i].nome[j-1] = tolower(agenda[i].nome[j-1]);
    }
    for ( i = 0; i < *total; i++){
        for ( j = i + 1; j < *total; j++){
            comparador = strcmp(agenda[i].nome, agenda[j].nome);
            if (comparador > 0){
                aux = agenda[i];
                agenda[i] = agenda[j];
                agenda[j] = aux;
            }
        }
    }
    for ( i = 0; i < *total; i++){
        agenda[i].nome[0] = toupper(agenda[i].nome[0]);
    }
}

char *obtertipodecont (enum tipoContato TpCon );
char *obterNomeEndereco (enum tipoEndereco tpEnd );
char *obterRede (enum tipoRedeSocial TpRS );
int menuAgenda ();
void limparTela ();
void criarContato (int *total);
void mostrarContatos (int *total);
int verificarNumero_Tel (char numero_tel[]);
int verificarEmail (char email[]);
void editarcontato (int *total);
void salvarArquivo (int total);


int main (){
    setlocale (LC_ALL, "");

    int total = lerArquivo();
    int opcao = 0;

    while(opcao != 6){
        opcao = menuAgenda ();

        switch (opcao)
        {
        case 1:
            criarContato (&total);
            break;

        case 2:
            editarcontato(&total);
            break;

        case 3:
            
            break;

        case 4:
            
            break;

        case 5:
            mostrarContatos (&total);
            break;

        case 6:
            
            break;
        
        default:
            printf ("Opção inválida!\n");
            printf ("----------------------------\n");
            break;

        }

    }

    
    salvarArquivo(total);


    return 0;
}