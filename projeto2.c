#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>


typedef struct data DATA;
        struct data
        {
            int dia;
            int mes;
            int ano;
        };


typedef struct inventario INVENTARIO;
    
        struct inventario{
            char  nome[30];
            char  produtor[30];
            DATA validade;
            DATA entrega;
        };

void inicial();
void novo();
void lista();
void pesquisa();
void remover();


int main()
{
    int x;
    do{
        inicial();
        printf("1 - PARA CADASTRAR UM PRODUTO NOVO\n2 - PARA VERIFICAR O ESTOQUE\n3 - PARA LIMPAR OS ESTOQUE\n4 - PARA PESQUISAR UM PRODUTO\n5 - SAIR");
        printf("\nESCOLHA UMA OPCAO: \n");
        scanf("%d", &x);
    

    switch (x)
    {
    case 1:
        novo();
        break;
    case 2:
        lista();
        break;
    case 3:
        remover();
        break;
    case 4:
        pesquisa();
        break;
    case 5:
        printf("Volte sempre!");
        printf("\n");
        printf("Vou sentir sua falta!");
        getch();
        break;
    default:
        printf("--NUMERO INCORRETO--");
        getch();
        break;
     } 
  }  while(x == 5);

}

void inicial(){
    system("cls");
    printf("-----------------------------\n");
    printf("     SISTEMA DE CONTROLE\n");
    printf("-----------------------------\n\n");
}
void novo(){
    FILE *file;

    INVENTARIO nm;

    file = fopen("estoque.txt", "ab");
    if (file == NULL)
    {
        printf("O PROGRAMA ENCONTROU PROBLEMAS PARA ABRIR O ARQUIVO");
    }
    else
    {
        do
        {
            inicial();

            fflush(stdin);
            printf("Digite o nome do produto: \n");
            gets(nm.nome);

            fflush(stdin);
            printf("Digite o nome do produtor: \n");
            gets(nm.produtor);

            fflush(stdin);
            printf("Digite a data de validade: \n");
            scanf("%d%d%d", &nm.validade.dia, &nm.validade.mes, &nm.validade.ano);

            fflush(stdin);
            printf("Digite a data de entrega: \n");
            scanf("%d%d%d", &nm.entrega.dia, &nm.entrega.mes, &nm.entrega.ano);
            
            fwrite(&nm, sizeof(INVENTARIO), 1, file);

            printf("Prosseguir com a operação ?\n");
            printf("Digite S para CONTINUAR\nDigite N para PARAR\n");

        } while (getche() == 'S');
            fclose(file);
    }
    
}
void lista()
{
    FILE *file;

    INVENTARIO nm;

    file = fopen("estoque.txt", "rb");

    inicial();

    if (file == NULL)
    {
        printf("O PROGRAMA ENCONTROU PROBLEMAS PARA ABRIR O ARQUIVO");
    }
    else
    {
       while(fread(&nm, sizeof(INVENTARIO),1, file)==1)
       {

        printf("Nome: %s\n", nm.nome);
        printf("Produtor: %s\n", nm.produtor);
        printf("Validade: %d/%d/%d\n", nm.validade.dia, nm.validade.mes, nm.validade.ano);
        printf("Entregue: %d/%d/%d\n", nm.entrega.dia, nm.entrega.mes, nm.entrega.ano);
        printf("---------------------------------------\n\n");
       }
    }
    fclose(file);
    getch();
}
void pesquisa()
{
    FILE *file;

    INVENTARIO nm;
    char nome[30];

    file = fopen("estoque.txt", "rb");

    inicial();

    if (file == NULL)
    {
        printf("O PROGRAMA ENCONTROU PROBLEMAS PARA ABRIR O ARQUIVO");
    }
    else
    {
        fflush(stdin);
        printf("DIGITE O NOME DO PRODUTO: ");
        gets(nome);

        while(fread(&nm, sizeof(INVENTARIO), 1, file)==1)
        {
            if(strcmp(nome,nm.nome)==0)
            {
                printf("Nome: %s\n", nm.nome);
                printf("Produtor: %s\n", nm.produtor);
                printf("Validade: %d/%d/%d\n", nm.validade.dia, nm.validade.mes, nm.validade.ano);
                printf("Entregue: %d/%d/%d\n", nm.entrega.dia, nm.entrega.mes, nm.entrega.ano);
                printf("---------------------------------------\n\n");
            }
        }    
    }
    
    fclose(file);
    getch();
}
void remover()
{
    FILE *file;
	FILE *fileF;
	INVENTARIO nm;

	char pesquisa[30];

	inicial();

	fileF = fopen("estoqueC.txt", "w");
    file = fopen("estoque.txt", "rb");
   

	if (file ==NULL || fileF == NULL)
    {
		printf("O PROGRAMA ENCONTROU PROBLEMAS PARA ABRIR O ARQUIVO");
	}
	else{
		fflush(stdin);
		printf("DIGITE O PRODUTO A SER APAGADO:\n");
		gets(pesquisa);

		while(!feof(file))
        {
            fread(&nm,sizeof(INVENTARIO),1,file);

			if (strcmp(pesquisa,nm.nome)==0){
                printf("PRODUTO ENCONTRADO: %s!\n",nm.nome);
                fwrite(NULL, sizeof(INVENTARIO), 1, fileF);
			}else{
			    if(feof(file)) break;
                fwrite(&nm, sizeof(INVENTARIO),1,fileF);
            }
		}
	}

	fclose(file);
	fclose(fileF);

   
    remove("estoqueC.txt");
  	rename("estoque.txt", "estoqueC.txt");
  	rename("estoqueN.txt", "estoque.txt");
	getch();
}
