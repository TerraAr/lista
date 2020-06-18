# lista
Protópipo de classe de lista lincada.

## Operadores
 - `[unsigned long long pos]`
   Retorna a posição da lista linkada como variável endereço.

## Funções
 - construtor `lista(Type a=0)`
   Cria a lista e inicializa a primeira posição com o valor recebido
 - destruidor `~lista()`
   Desaloca as posições alocadas dinamicamente e destrói as variáveis estáticas.
 - `gotopos(unsigned long long pos)`
   Manda o cursor da lista para a posição especificada.
 - `escreve(Type a)`
   Escreve o valor mandado na posição atual da lista.
 - `Type le()`
   Retorna a posição atual da lista.
