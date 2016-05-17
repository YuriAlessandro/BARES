# Projeto BARES #
Basic ARithmetic Expression evaluator based on Stacks.

BARES é um programa que analisa uma expressão matemática simples, que contenha
constantes numéricas inteiras. Ela faz uso de dois Tipos Abstratos de Dados (TADs),
pilha e fila, que foram apresentados em sala de aula durante a disciplina de Estrutura 
de Dados Básica do curso de Bacharelado em Tecnologia da Informação da Universidade 
Federal do  Rio Grande do Norte.

O objetivo final dessa aplicação, portanto, é fixar o conteúdo ministrado em sala de aula
com relação a essas duas TADs e incitar a criação de um programa mais complexo.

Esse programa será capaz de analisar a expressão e dizer se ocorre erros, onde 
esse erro ocorre, qual o erro e, caso a expressão seja válida, o valor da expressão.


## Como rodar o programa
Antes de rodar o programa, você deve criar um arquivo contendo as expressões que
você deseja que sejam analisadas (desde que essas expressões sigam as condições 
descritas na descrição do projeto).

Um exemplo de um arquivo de entrada:

```Shell
    10000000 - 2
    3 * d
     (5 % 3) ^4
```

Acesse a pasta principal do programa, abra-a no terminal e dê o comando:

    $ ./bin/exe <arquivo>

Você pode ser capaz de mandar a saída para um outro arquivo externo, executando
o programa da seguinte maneira:

    $ ./bin/exe <arquivo_entrada> > <arquivo_saida>

## Detalhes
Este programa foi desenvolvido em C++11. Para compilar, abra no terminal e 
a pasta principal do programa e dê o comando:

```Shell
    & make
``` 

## Documentação
A documentação completa desse programa pode ser encontrada em 'html/index.html'

## Autoria
- Gustavo Carvalho
- Yuri Alessandro Martins


Realizado como proposta da disciplina de Linguagem de Programação, do curso de
Bacharelado em Tecnologia da Informação da UFRN.