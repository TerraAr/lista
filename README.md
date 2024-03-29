# lista
`lista` é uma biblioteca de strings e listas lincadas criada em C++ que
tem como objetivo fornecer listas e strings intuitivas para a criação de
códigos em C++ e demais linguagens, através de arquivos objetos, sem
perder de vista a velocidade.

## lista lincada
A lista lincada está implementada como um template de classe, de
forma que é possível criar uma lista de qualquer tipo existente
na hora da compilação, inclusive de classes, uniões e enumerações
criadas pelo usuário ou implementadas por bibliotecas.

Sugere-se atenção na hora de ordenar os membros das classes que
sejam usadas em listas com mais de 1.000 posições ou em aplicações
em sistemas embarcados para evitar espaços ociosos entre eles e
consequente "perda" de memória.

### Operadores
 - `[unsigned long long pos]`
   Retorna a posição da lista lincada como variável endereço.
 - `+ elemento`
   Cria uma lista lincada que é a primeira acrecida do elemento a
   direita.
 - `+ lista`
   Cria uma lista lincada que é a primeira acrecida da segunda.
 - `-`
   Cria uma lista lincada que é a primeira retirada as últimas n
   posições.
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
   Verifica se a lista tem um número menor ou igual de elementos que a
   outra.
 - `>=`
   Verifica se a lista tem um número maior ou igual de elementos que a
   outra.

### Funções
 - construtor `lista()`
   Cria a lista e inicializa a primeira posição com o valor recebido
 - destruidor `~lista()`
   Desaloca as posições alocadas dinamicamente e destrói as variáveis
   estáticas.
 - operador `Type*()`
   Converte a lista lincada em um vetor alocado dinamicamente do
   mesmo tipo.
 - `tam_lista()`
   Devolve o tamanho da lista.
 - `eVazia()`
   Verifica se a lista é vazia.
 - `esvazia()`
   Esvazia a lista lincada.
 - `have_elem(Type elem)`
   Verifica se há o elemento na lista.
 - `count_elem(Type elem)`
   Conta a quantidade de vezes que o elemento aparece na lista.
 - `count_elems(Type *elems)`
   Conta a quantidade de vezes que os elementos aparecem na lista.
 - `vetor_para_lista(Type* vetor, const unsigned tam)`
   Transforma o vetor dado em uma lista lincada do mesmo tipo.

#### Funções de baixo nível
 Funções para controle fino da lista, permitindo inclusive a adição e
 retirada de elementos do meio da lista.

 - `gotopos(unsigned long long pos)`
   Manda o cursor da lista para a posição especificada.
 - `addpos(unsigned long long qte_celulas)`
   Adiciona `qte_celulas` imediatamente após a posição atual.
 - `rmpos(unsigned long long qte_celulas = 1)`
   Remove `qte_celulas` da lista a partir da posição atual.
 - `escreve(Type a)`
   Escreve o valor recebido na posição atual da lista.
 - `Type le()`
   Retorna o valor armazenado na posição atual da lista.

## String

A string é uma classe filha da classe `lista<char>`, sendo estendida de
forma a operar também com variáveis e constantes do tipo vetor de `char`,
além de fazer as adaptações necessárias por conta do `'\0'` em seu fim.

### Funções específicas

 - `word(lista<string>, const char)`
   Forma uma string com as palavras da lista usando o caractere como
   conector.
 - `unword(const char)`
   Quebra a string nos pontos onde o caractere aparece, formando uma
   lista de palavras.

## ToDo

Seção que lista novas funções e recursos para serem implementados,
*bugs* a serem corrigidos e demais pontos por fazer na biblioteca.

 - Implementar funções `word` e `unword` com vetor de caracteres e
   *strings* como último argumento;
 - Implementar função para remover *strings* vazias de uma lista de
   *strings*;
 - Implementar funções de classe para busca de sub-*strings* numa
   *string* (verificação de existência e contagem de aparições);
 - Implementação de testes automáticos para novos *commits* da
   biblioteca;
 - Adicionar e melhorar comentários ao longo do código-fonte.
