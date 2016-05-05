## DONE
### Insira seu progresso abaixo
#### Gustavo
- Copiei o Stack template que já tinha feito, mas tem que modificar os pops e os
cleans pra dar destroy (como visto naquela aula de LP).
- Fiz a tokenização no Main.

## TODO
- O Makefile (Pra aprender logo de uma vez).
- Copiar a fila pra cá também.
- Tokenização [DONE].
- Tratamento de erro sagaz na Tokenização.
- Mover a Tokenização para uma classe que ainda nem existe.
- Transformação em notação polonesa.
- A parte da calculadora que calcula (a calculadora em si).

## Planejamento
- Uma classe para os operandos e operadores (Term (Trocar esse nome)) e outra
para a sequência deles (Provavelmente Expression pra invejar os amiguinhos que
já fizeram na nossa frente).
- Possivelmente uma classe para erros (Aroma de functors no ar(?)).

## Cuidados e Pensamentos Altos
- O operador unário atrapalha tudo, complicado.
- Alguns erros são melhores tratados no parsing, e outros na transformação.
- Identificar a coluna dos erros será um problema ~~grande e chato~~. ~~Mentiraaa!~~
Mentira de novo. Pela complexidade dos erros, o melhor é fazer mesmo uma função de
parsing que aja antes da tokenização (pois a mesma apaga espaços e etc), porém as
especificações do trabalho implicam em continuar o processo mesmo quando der errado
(Por qual motivo?), complicado. Clarificações serão procuradas.
