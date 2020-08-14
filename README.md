# lista
Protópipo de classe de lista lincada.

## Operadores
 - `[unsigned long long pos]`
   Retorna a posição da lista linkada como variável endereço.
 - `+ elemento`
   Cria uma lista linkada que é a primeira acrecida do elemento a direita.
 - `+ lista`
   Cria uma lista linkada que é a primeira acrecida da segunda.
 - `-`
   Cria uma lista linkada que é a primeira retirada as últimas n posições.
 - `=`
   Copia uma lista para a outra.
 - `+= elemento`
   Adiciona um elemento à lista.
 - `+= lista`
   Adiciona a segunda lista no final da primeira.
 - `-=`
   Retira as últimas n posições da lista.
 - `==`
   Verifica se todos os elementos da lista são iguais.
 - `!=`
   Verifica se há pelo menos um par de elementos diferentes na lista.
 - `<`
   Verifica se a lista tem um número menor de elementos que a outra.
 - `>`
   Verifica se a lista tem um número maior de elementos que a outra.
 - `<=`
   Verifica se a lista tem um número menor ou igual de elementos que a outra.
 - `>=`
   Verifica se a lista tem um número maior ou igual de elementos que a outra.

## Funções
 - construtor `lista()`
   Cria a lista e inicializa a primeira posição com o valor recebido
 - destruidor `~lista()`
   Desaloca as posições alocadas dinamicamente e destrói as variáveis estáticas.
 - `gotopos(unsigned long long pos)`
   Manda o cursor da lista para a posição especificada.
 - `escreve(Type a)`
   Escreve o valor mandado na posição atual da lista.
 - `Type le()`
   Retorna a posição atual da lista.
