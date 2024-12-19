# Sistema de Cadastro e Venda de Produtos - Loja de Produtos Naturais

Este projeto é um sistema simples de gerenciamento de uma loja de produtos naturais. O sistema permite cadastrar clientes, produtos, realizar vendas, e consultar o estoque de produtos, tudo de forma interativa via terminal.

## Funcionalidades

- **Cadastro de Clientes**: Permite cadastrar clientes com informações como nome, CPF, telefone, e endereço.
- **Cadastro de Produtos**: Permite cadastrar produtos com nome, descrição, preço, validade, e quantidade em estoque.
- **Venda de Produtos**: Realiza a venda de produtos, com opções de pagamento à vista (com desconto) ou parcelado (com juros).
- **Consultas**: Permite consultar clientes e produtos cadastrados, além de verificar a quantidade disponível em estoque de um produto específico.

## Funcionalidades detalhadas

### 1. Cadastro de Clientes
Os dados do cliente incluem nome, CPF, telefone, data de nascimento e endereço completo (rua, número da casa, bairro, complemento e CEP). 
- O CPF é verificado para evitar duplicação.
  
### 2. Cadastro de Produtos
Os dados do produto incluem código, nome, descrição, preço, validade e quantidade em estoque.
- O código do produto é verificado para evitar duplicação.
  
### 3. Venda de Produtos
O sistema permite que um cliente compre produtos, com opções de pagamento:
- **À vista**: Desconto de 10%.
- **Parcelado**: Em até 3x sem juros, ou acima disso com 10% de juros.

### 4. Consultas
- **Consultar Clientes**: Exibe os dados cadastrados de um cliente a partir do CPF.
- **Consultar Produtos**: Exibe todos os produtos cadastrados, com nome, descrição, validade e quantidade em estoque.
- **Consultar Quantidade de Produto**: Permite verificar a quantidade disponível de um produto específico.
