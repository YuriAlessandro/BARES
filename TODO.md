## DONE
### Insira seu progresso abaixo
#### Gustavo
- Copiei o Stack e Fila template feitos anteriormente.
- Tokenização.
- Parsing.
- Parsing que Tokeniza.

#### Yuri
- Transformação para pós-fixo.
- Fez um arquivo legal pra FMC2.

## TODO
- [x] Tokenização.
- [x] Parsing.
- [x] Parsing que Tokeniza.
- [x] O Makefile (Pra aprender logo de uma vez).
- [x] O MAKEFILE.
- [x] O Makefile, serião.
- [ ] Fazer o Makefile notar mudanças nos .h
- [ ] Começar a comentar no estilo Doxygen.
- [x] Organizar o programa em .h's e partes que fazem sentido.
- [ ] Mover a Tokenização para uma classe que ainda nem existe?
- [x] Transformação em notação polonesa.
- [ ] A parte da calculadora que calcula (a calculadora em si).

## Planejamento
- Uma classe para os operandos e operadores e outra
para a sequência deles (Provavelmente Expression pra invejar os amiguinhos que
já fizeram na nossa frente).
- Possivelmente uma classe para erros (Aroma de functors no ar(?)).

## Cuidados e Pensamentos Altos
- ~~O operador unário atrapalha tudo, complicado.~~ Não mais!
- Alguns erros são melhores tratados no parsing, e outros na transformação.
- Identificar a coluna dos erros será um problema ~~grande e chato~~. ~~Mentiraaa!~~
Mentira de novo. Pela complexidade dos erros, o melhor é fazer mesmo uma função de
parsing que aja antes da tokenização (pois a mesma apaga espaços e etc) [ DONE ;^) ].
- Você sabe (ou acha) que tá com tempo extra quando tem uma seção chamada "Opcionais"

## Opcionais
- Fazer os MakeEmpty de ambas as TADs darem destroy nos objetos (para paz de espírito)
- Uma forma mais sofisticada de jogar os erros.


## Dúvidas
- Ordem dos erros ( (3 +d) é E2? E (3 += 4)? )
- 3 + () é uma entrada possível e errada? (Certeza que é, resolva)
- E 3 + () 4? (Mesma coisa)
- 2 + (((3)))
- ++++4 ---5 -> Válido?
- +-+-+--+6 -> Válido?
- -----10000000 -> Erro de overflow na coluna 1 ou 6?
- 3 ) 4 -> é E3 ou E5?
- 3 + ) -> é E3 ou E5?
- 2 + ( -> é E2 ou E7?
- 3 + ( ) -> Erro em qual coluna?
- Na calculadora, nós temos que converter os operadores em "operações" ou faz
com algo estilo switch case?
