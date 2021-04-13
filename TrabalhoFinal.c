#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Livro
{
    char titulo[100];
    int ISBN;
    float valor;
    int quantidadeEmEstoque;
} Livro;

Livro** livrosEmEstoque;

int numeroDeTitulos = 0; //quantidade de livros diferentes em estoque
float saldo;

void estoqueLivros()
{
    FILE* arq;

    char temp[50];
    char* token; //guarda os pedaços do arquivo
    int ISBN;
    float valor;
    int quantidadeEmEstoque;

    arq = fopen("estoque.txt", "r");

    if(arq==NULL)
    {
        printf("O estoque nao foi encontrado\n");

        return;
        system("pause");
    }

//conta o numero de linhas que tem dentro do arquivo
    int contador = 0;

    while(!feof(arq))
    {
        fgets(temp, 50, arq);
        contador++;
    }

    numeroDeTitulos = contador;

    rewind(arq); //volta o arquivo no inicio

    livrosEmEstoque = malloc(numeroDeTitulos * sizeof(Livro*));

    for (int i=0; i<numeroDeTitulos; i++)
    {
        livrosEmEstoque[i] = malloc(sizeof(Livro));
        fgets(temp, 50, arq);
        token = strtok(temp, "@");
        strcpy (livrosEmEstoque[i], token);
        token = strtok(NULL, "@");
        livrosEmEstoque[i] -> ISBN = atoi(token);
        token = strtok(NULL, "@");
        livrosEmEstoque[i] -> valor = atoi(token);
        token = strtok(NULL, "@");
        livrosEmEstoque[i] -> quantidadeEmEstoque = atoi(token);

    }
    fclose(arq); //fecha o arquivo
}


void salvaDados()
{
FILE* arq;
FILE* arq2;

arq = fopen("estoque.txt", "w");

for(int i=0; i<numeroDeTitulos-1; i++)
{
    fprintf(arq, "%s@%d@%0.2f@%d\n", livrosEmEstoque[i], livrosEmEstoque[i]->ISBN, livrosEmEstoque[i]->valor, livrosEmEstoque[i]->quantidadeEmEstoque);
}
fprintf(arq, "%s@%d@%0.2f@%d", livrosEmEstoque[numeroDeTitulos-1], livrosEmEstoque[numeroDeTitulos-1]->ISBN, livrosEmEstoque[numeroDeTitulos-1]->valor, livrosEmEstoque[numeroDeTitulos-1]->quantidadeEmEstoque);

fclose(arq);

arq2 = fopen("saldo.txt", "w");

fprintf(arq2, "%0.2f",saldo);

rewind(arq2);
fclose(arq2);

}

void cadastraLivro()
{
    char titulo[100];
    char temp[50], temp2[50], temp3[50]; //variaveis auxiliares
    int ISBN;
    float valor;
    int quantidadeEmEstoque2, posicao, elementoEncontrado;

    printf("Digite o titulo do livro: ");
    fgets(titulo, 100, stdin);
    strtok(titulo, "\n");

    printf("Digite o ISBN do livro: ");
    fgets(temp, 50, stdin);
    ISBN = atoi(temp);

    printf("Digite o valor unitario do livro: ");
    fgets(temp2, 50, stdin);
    valor = atoi(temp2);

    printf("Digite a quantidade em estoque do livro: ");
    fgets(temp3, 50, stdin);
    quantidadeEmEstoque2 = atoi(temp3);

    for(int i=0; i<numeroDeTitulos; i++)
    {
       posicao = livrosEmEstoque[i]->ISBN;

        if(posicao==ISBN)
        {
            livrosEmEstoque[i]-> quantidadeEmEstoque = livrosEmEstoque[i]-> quantidadeEmEstoque + quantidadeEmEstoque2;

            printf("Livro adicionado ao estoque!\n");

            elementoEncontrado = 1;
        }
    }
    if (elementoEncontrado == 0)
    {

        livrosEmEstoque = realloc(livrosEmEstoque, (numeroDeTitulos + 1)* sizeof(Livro*)); //Aumenta a quantidade de memoria ao adicionar um novo livro
        livrosEmEstoque[numeroDeTitulos] = malloc(sizeof(Livro));
        strcpy(livrosEmEstoque[numeroDeTitulos]-> titulo, titulo);
        livrosEmEstoque[numeroDeTitulos] ->ISBN = ISBN;
        livrosEmEstoque[numeroDeTitulos] ->valor = valor;
        livrosEmEstoque[numeroDeTitulos] ->quantidadeEmEstoque = quantidadeEmEstoque2;

        numeroDeTitulos++;

        printf("Livro adicionado com sucesso!\n");
    }
    system("pause");
}

void consultaEstoqueTitulo()
//Consulta a existencia de um titulo no arquivo estoque.txt
{
    char titulo[100];
    char* posicao;

    int elementoEncontrado = 0;

    printf("Digite o titulo do livro: ");
    fgets(titulo, 50, stdin);
    strtok(titulo, "\n");

    for(int i=0; i<numeroDeTitulos; i++)
    {
        posicao = strstr( strupr (livrosEmEstoque[i] -> titulo) , strupr(titulo)); //procura a existencia do titulo no arquivo

        if(posicao!=NULL)
        {
            printf("Titulo: %s \n ISBN: %d \n Valor Unitario: %0.2f \n Quantidade em Estoque: %d \n", livrosEmEstoque[i], livrosEmEstoque[i]->ISBN, livrosEmEstoque[i]->valor, livrosEmEstoque[i]->quantidadeEmEstoque);

            elementoEncontrado = 1;
        }
    }
    if (elementoEncontrado == 0)
    {
        printf("Titulo nao encontrado. \n");
    }
    system("pause");
}

void consultaEstoqueISBN()
//Consulta a existencia de um ISBN no arquivo estoque.txt
{
    int ISBN;
    char temp[50];
    char* posicao;

    int elementoEncontrado = 0;

    printf("Digite o ISBN do livro: ");
    fgets(temp, 50, stdin);
    ISBN = atoi(temp);


    for(int i=0; i<numeroDeTitulos; i++)
    {
       posicao = livrosEmEstoque[i]->ISBN;


        if(posicao==ISBN)
        {
            printf("Titulo: %s \n ISBN: %d \n Valor Unitario: %0.2f \n Quantidade em Estoque: %d \n", livrosEmEstoque[i], livrosEmEstoque[i]->ISBN, livrosEmEstoque[i]->valor, livrosEmEstoque[i]->quantidadeEmEstoque);

            elementoEncontrado = 1;
        }
    }
    if (elementoEncontrado == 0)
    {
        printf("ISBN nao encontrado. \n");
    }
    system("pause");
}

void consultaEstoque()
{
    char temp[10];
    int opcao;

    printf("Escolha o tipo de consulta que deseja: \n");
    printf("1. Consulta com o titulo do livro \n");
    printf("2. Consulta com o ISBN do livro \n");


    fgets(temp, 10, stdin);
    opcao = atoi(temp);

    if(opcao==1)
    {
        consultaEstoqueTitulo();
    } else if (opcao==2)
    {
        consultaEstoqueISBN();
    } else
    {
        printf("Comando nao encontrado!");
    }
    system("pause");
}


int lerSaldo()
{
    FILE* arq;
    char temp[50];

    arq = fopen("saldo.txt", "a+"); //Abre para adição ou leitura no final do arquivo. Se o arquivo não existir, a função o cria.

    while(!feof(arq)){
        fgets(temp, 50, arq);
    }

    rewind(arq);

    saldo = atoi(temp);
    fputc(saldo,arq);

    fclose(arq);
}


void vendeLivro()
{
    int ISBN, quantidadeVendida; //quantidadeVendida = quantidade de livros a ser vendida
    char temp[50], temp2[50];
    int elementoEncontrado = 0;
    int posicao, novaQuantidade; //novaQuantidade = nova quantidade do livro em estoque depois de vendido
    float adicionarSaldo; //saldo adicionado após a venda

    printf("Digite o ISBN do livro: \n");
    fgets(temp, 50, stdin);

    ISBN = atoi(temp);
    for(int i=0; i<numeroDeTitulos; i++)
    {
        posicao = livrosEmEstoque[i]->ISBN;


        if(posicao==ISBN)
        {
            printf("Titulo: %s \n ISBN: %d \n Valor Unitario: %0.2f \n Quantidade em Estoque: %d \n", livrosEmEstoque[i], livrosEmEstoque[i]->ISBN, livrosEmEstoque[i]->valor, livrosEmEstoque[i]->quantidadeEmEstoque);

            elementoEncontrado = 1;
        }
    }
    if (elementoEncontrado == 0)
    {
        printf("ISBN NAO RECONHECIDA! \n O estoque nao possui esse livro. \n");
        system("pause");
    }

    printf("Digite a quantidade de livros a ser vendida: \n");
    fgets(temp2, 50, stdin);
    quantidadeVendida = atoi(temp2);

    //diminuindo o estoque
    for(int i=0; i<numeroDeTitulos; i++)
    {
        if(livrosEmEstoque[i]->ISBN==ISBN)
        {
            novaQuantidade = livrosEmEstoque[i]->quantidadeEmEstoque - quantidadeVendida;

            while (novaQuantidade<0){
                printf("Erro: nao existe livro suficiente em estoque.\n");
                printf("Digite a quantidade de livros a ser vendida: \n");
                fgets(temp2, 50, stdin);
                quantidadeVendida = atoi(temp2);
                novaQuantidade = livrosEmEstoque[i]->quantidadeEmEstoque - quantidadeVendida;
            }

            livrosEmEstoque[i]->quantidadeEmEstoque = livrosEmEstoque[i]->quantidadeEmEstoque - quantidadeVendida;

            printf("Livro vendido com sucesso!\n");
            printf("Titulo: %s \n Nova Quantidade em Estoque: %d \n", livrosEmEstoque[i], livrosEmEstoque[i]->quantidadeEmEstoque);


            adicionarSaldo = quantidadeVendida * livrosEmEstoque[i]->valor;
            printf ("Saldo adicionado ao caixa: %0.2f\n", adicionarSaldo);

            lerSaldo();
            saldo = saldo + adicionarSaldo;
            }
            system("pause");
        }
}

int consultarSaldo()
{
lerSaldo();
printf("Saldo: %0.2f reais\n", saldo);
system("pause");
}

void limparEstoque()
{
    for(int i=0; i<numeroDeTitulos; i++)
    {
        free(livrosEmEstoque[i]);
    }

}


void menuPrincipal()
{
    int opcao;
    int sair = 0;
    char temp[10];

    do
    {
        system("cls"); //limpa a tela

        printf("Menu de Opcoes\n");

        printf("1. Cadastra Livro\n");
        printf("2. Consulta Estoque\n");
        printf("3. Vender um Livro\n");
        printf("4. Consultar Saldo da Loja\n");
        printf("5. Salvar Dados\n");
        printf("9. Sair\n");

        fgets(temp, 10, stdin);
        opcao = atoi(temp);

        switch(opcao)
        {
            case 1: {
                cadastraLivro();
                break;
            }
            case 2: {
                consultaEstoque();
                break;
            }
            case 3: {
                vendeLivro();
                break;
            }
            case 4: {
                consultarSaldo();
                break;
            }
            case 5: {
                salvaDados();
                printf("Os dados foram salvos com sucesso!\n");
                system("pause");
                break;
            }
            case 9: {
                sair = 1;
                break;
            }
        }
    } while (sair==0);
}


int main()
{
    estoqueLivros();
    menuPrincipal();
    limparEstoque();
    return 0;
}
