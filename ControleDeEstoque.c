#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CONTA 10
#define MAX_PROD 20

typedef struct Endereco
{
    char rua[40];
    int numeroCasa;
    char bairro[30];
    char complemento[30];
    char cep[20];
} Endereco;

typedef struct CadastroCliente
{
    char nome[30];
    int cpf;
    char telefone[15];
    char dataNascimento[11];
    Endereco endereco;
} CadastroCliente;

typedef struct CadastrarProd
{
    int codigoProd;
    char nomeProd[20];
    char descricaoProd[200];
    float valorProd;
    char validade[11];
    int QteProdEst; // Quantidade do produto em estoque
} CadastrarProd;

// função cadastrar clientes
int CadastrarCliente(CadastroCliente clientes[], int *qte)
{
    if (*qte >= MAX_CONTA)
    {
        printf("Limite de clientes atingido.\n");
        return 0;
    }

    CadastroCliente novoCliente;

    printf("Digite o nome: ");
    scanf(" %[^\n]", novoCliente.nome);
    printf("Digite o CPF(Sem pontos apenas numeros): ");
    scanf("%d", &novoCliente.cpf);

    // Verificando se o CPF ja esta cadastrado
    for (int i = 0; i < *qte; i++)
    {
        if (clientes[i].cpf == novoCliente.cpf)
        {
            printf("CPF ja cadastrado. Tente outro.\n");
            return 0;
        }
    }

    printf("Digite o telefone: ");
    scanf("%s", novoCliente.telefone);
    printf("Digite a data de nascimento (dd/mm/aaaa): ");
    scanf("%s", novoCliente.dataNascimento);

    printf("Digite a rua: ");
    scanf(" %[^\n]", novoCliente.endereco.rua);
    printf("Digite o cep: ");
    scanf("%s", novoCliente.endereco.cep);
    printf("Digite o numero da casa: ");
    scanf("%d", &novoCliente.endereco.numeroCasa);
    printf("Digite o bairro: ");
    scanf(" %[^\n]", novoCliente.endereco.bairro);
    printf("Digite o complemento: ");
    scanf(" %[^\n]", novoCliente.endereco.complemento);

    clientes[*qte] = novoCliente;
    (*qte)++;
    printf("Cliente cadastrado com sucesso!\n");
    return 1; // Sucesso
}

int CadastrarProdutos(CadastrarProd produtos[], int *qteProdutos)
{
    if (*qteProdutos >= MAX_PROD)
    {
        printf("Limite de produtos atingidos.\n");
        return 0;
    }

    CadastrarProd novoProduto;

    printf("Digite o codigo do produto: ");
    scanf("%d", &novoProduto.codigoProd);

    // Verificacao de codigo duplicado
    for (int i = 0; i < *qteProdutos; i++)
    {
        if (produtos[i].codigoProd == novoProduto.codigoProd)
        {
            printf("Codigo ja cadastrado. Tente outro.\n");
            return 0; // Retorna a zero sem cadastrar
        }
    }

    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", novoProduto.nomeProd);
    printf("\n");

    printf("Digite a descricao do produto: ");
    scanf(" %[^\n]", novoProduto.descricaoProd);
    printf("\n");

    printf("Digite o valor do produto: ");
    scanf("%f", &novoProduto.valorProd);
    printf("\n");

    printf("Digite a validade (dd/mm/aaaa): ");
    scanf("%s", novoProduto.validade);
    printf("\n");
    printf("Digite a quantidade do produto no estoque: ");
    scanf("%d", &novoProduto.QteProdEst);

    produtos[*qteProdutos] = novoProduto;
    (*qteProdutos)++;
    printf("Produto cadastrado com sucesso!\n");
    return 1; // Sucesso
}

void VenderProduto(CadastrarProd produtos[], int *qteProdutos)
{
    int ProdComprar;
    int FormaPGTO;
    int QteProdComprar;

    printf("Digite o codigo do produto que deseja comprar: ");
    scanf("%d", &ProdComprar);

    int produtoEncontrado = -1;

    // Procurar o produto pelo código
    for (int i = 0; i < *qteProdutos; i++)
    {
        if (ProdComprar == produtos[i].codigoProd)
        {
            produtoEncontrado = i; // Salva o índice do produto encontrado
            printf("\nProduto encontrado: %s, Valor: %.2f, Quantidade em estoque: %d\n",
                   produtos[i].nomeProd, produtos[i].valorProd, produtos[i].QteProdEst);

            // Solicitar a quantidade desejada
            printf("\nDigite a quantidade que voce deseja comprar: ");
            scanf("%d", &QteProdComprar);

            // Verificar se a quantidade desejada está disponível no estoque
            if (QteProdComprar > produtos[i].QteProdEst)
            {
                printf("Quantidade solicitada nao disponivel. Estoque atual: %d\n", produtos[i].QteProdEst);
                return; // Sai da função se a quantidade não estiver disponível
            }

            // Solicitar a forma de pagamento
            printf("\nEscolha a forma de pagamento\n[1] A vista\n[2] Credito: ");
            scanf("%d", &FormaPGTO);

            // Calcular o valor total da compra
            float valorTotal = QteProdComprar * produtos[i].valorProd;
            float ValorParcelado;
            int Parcelas;

            // Exibir o valor total dependendo da forma de pagamento
            if (FormaPGTO == 1)
            {
                // Desconto de 10% para pagamento à vista
                printf("Valor total: %.2f (A vista - 10%% de desconto)\n", valorTotal * 0.9);
            }
            else if (FormaPGTO == 2)
            {
                printf("Vai parcelar em quantas vezes? (em até 3x sem juros, acima disso com juros de 10%%): ");
                scanf("%d", &Parcelas);

                // Calcular o valor total com juros caso o parcelamento seja superior a 3 vezes
                if (Parcelas <= 3)
                {
                    // Para até 3 parcelas, sem juros
                    printf("Valor total: %.2f (Credito - %dx de %.2f)\n", valorTotal, Parcelas, valorTotal / Parcelas);
                }
                else
                {
                    // Acima de 3 parcelas, com juros de 10%
                    float valorComJuros = valorTotal * 1.1; // Aplica 10% de juros
                    printf("Valor total com juros de 10%%: %.2f (Credito - %dx de %.2f)\n", valorComJuros, Parcelas, valorComJuros / Parcelas);
                }
            }
            else
            {
                printf("Opcao de pagamento invalida!\n");
                return; // Sai se a opção de pagamento for inválida
            }

            // Reduzir a quantidade do produto em estoque
            produtos[i].QteProdEst -= QteProdComprar;
            printf("Venda realizada com sucesso! Quantidade restante no estoque: %d\n", produtos[i].QteProdEst);
            break; // Sai do loop quando o produto for encontrado e a venda for realizada
        }
    }

    // Se o produto não for encontrado
    if (produtoEncontrado == -1)
    {
        printf("Produto nao encontrado!\n");
    }
}

// função para consultar cadastro de clientes
int CadastroCL(CadastroCliente clientes[], int qte)
{
    int cpfEncontrado;
    int indiceEncontrado = 0;

    printf("Digite o numero de cpf do cliente: ");
    scanf("%d", &cpfEncontrado);

    for (int i = 0; i < qte; i++)
    {
        if (cpfEncontrado == clientes[i].cpf)
        {
            printf("Dados do cliente:\n\n");
            printf("Dados do cliente:\n\n");
            printf("CPF: %d\n", clientes[i].cpf);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Telefone: %s\n", clientes[i].telefone);
            printf("Data Nascimento: %s\n", clientes[i].dataNascimento);
            printf("Endereco: Rua: %s, N: %d\n", clientes[i].endereco.rua, clientes[i].endereco.numeroCasa);
            printf("Bairro: %s\n", clientes[i].endereco.bairro);
            printf("Cep: %s\n", clientes[i].endereco.cep);
            indiceEncontrado = 1;
            break; // Sai do loop quando encontrar o cliente
        }
        if (!indiceEncontrado)
        {
            printf("Cliente com CPF %d nao encontrado.\n", cpfEncontrado);
        }

        return 0;
    }
}

// Consultar produto especifico estoque
void ConsultarQuantidadeEstoqueProdEspecifico(CadastrarProd produtos[], int qteProdutos)
{
    int codigoProduto;

    if (qteProdutos == 0)
    {
        printf("Nenhum produto cadastrado.\n");
        return; // Sai da função se não houver produtos cadastrados
    }
    printf("Digite o codigo do produto para verificar a quantidade em estoque: ");
    scanf("%d", &codigoProduto);

    // Verifica o código digitado
    printf("Voce digitou o codigo: %d\n", codigoProduto);

    // Procurar o produto pelo código
    int produtoEncontrado = 0; // Variável para verificar se o produto foi encontrado
    for (int i = 0; i < qteProdutos; i++)
    {
        if (codigoProduto == produtos[i].codigoProd)
        {
            // Produto encontrado, exibe as informações
            printf("\nProduto encontrado: %s\n", produtos[i].nomeProd);
            printf("Quantidade em estoque: %d\n", produtos[i].QteProdEst);
            produtoEncontrado = 1; // Marca que o produto foi encontrado
            break;                 // Sai do loop após encontrar o produto
        }
    }

    // Se o produto não for encontrado
    if (produtoEncontrado == 0)
    {
        printf("Produto nao encontrado!\n");
    }
}

// Função para consultar produtos cadastrados
void ConsultarProdCadastrado(CadastrarProd produtos[], int *qteProdutos)
{
    if (*qteProdutos == 0)
    {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    for (int i = 0; i < *qteProdutos; i++)
    {
        printf("\nCodigo: %d\n"
               "Nome: %s\n"
               "Descricao: %s\n"
               "Validade: %s\n"
               "Quantidade em estoque: %d\n",
               produtos[i].codigoProd,
               produtos[i].nomeProd,
               produtos[i].descricaoProd,
               produtos[i].validade,
               produtos[i].QteProdEst);
    }
}

// Funcao para consultar produtos
void Consultar(CadastrarProd produtos[], int qteProdutos, int *qte, CadastroCliente clientes[])
{
    int opcoes = -1;

    do
    {
        printf("\nDigite:\n"
               "[1] - Produtos cadastrados\n"
               "[4] - Clientes cadastrados\n"
               "[6] - Quantidade em estoque de determinado produto\n"
               "[0] - Para voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcoes);

        switch (opcoes)
        {
        case 1:
            ConsultarProdCadastrado(produtos, &qteProdutos);
            break;

        case 4:
            CadastroCL(clientes, *qte);
            break;

        case 6:
            ConsultarQuantidadeEstoqueProdEspecifico(produtos, qteProdutos);
            break;
        default:
            break;
        }

    } while (opcoes != 0);
}

int main()
{
    CadastroCliente clientes[MAX_CONTA];
    CadastrarProd produtos[MAX_PROD];
    int opcoes = 0;
    int qte = 0;
    int qteProdutos = 0;  // Corrigido de int *qteProdutos para int qteProdutos

    printf("Bem-vindo a loja de produtos naturais, aperte [ENTER] para continuar\n");
    getchar();

    do
    {
        printf("\n----[Menu]----\n");
        printf("\n [1]: Cadastrar cliente");
        printf("\n [2]: Cadastrar Produtos");
        printf("\n [3]: Consultas");
        printf("\n [4]: Vender um produto");
        printf("\n [8]: Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcoes);

        switch (opcoes)
        {
        case 1:
            CadastrarCliente(clientes, &qte);
            printf("Total de clientes cadastrados: %d\n", qte);
            break;
        case 2:
            CadastrarProdutos(produtos, &qteProdutos);
            printf("Total de produtos cadastrados: %d\n", qteProdutos);
            break;
        case 3:
            Consultar(produtos, qteProdutos, &qte, clientes);
            break;
        case 4:
            VenderProduto(produtos, &qteProdutos);
            break;
        case 8:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcoes != 8);

    return 0;
}
