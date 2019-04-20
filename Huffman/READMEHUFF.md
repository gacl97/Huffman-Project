#Como funciona a compactação:

### Frequencia:

Primeiramente iremos ler a frequencia de um caracter do arquivo para os de maior frequencia gastarem menos memoria no novo mapeamento.

### Fila de prioridade:

Criamos uma fila de prioridade, usando a estrutura de dados Heap, nessa heap, fazemos cada posição do array, apontar para um nó, um nó possui o caracter presente no arquivo com sua respectiva frequência, possui um ponteiro pra esquerda e um ponteiro pra direita para quando for montar a Árvore de Huffman.

### Como funciona a heap:

Como teremos uma Heap mínima, para retirarmos sempre o de menor frequência no nó raiz, então:

1. Função enqueue:

    Ao chegar um novo nó, aumentamos o tamanho atual da Heap e colocamos esse nó na ultima posição, para isso, precisamos do índice atual e do índice do "pai" desse nó.
    Fazemos um loop em que enquanto o nó filho, for menor que seu pai e menor que o índice da raiz, trocamos os nós.
    Com isso garantimos que mantemos todos os nós com menor frequência na frente.

2. Função dequeue:

    Retiramos o nó da raiz, pois sempre será o de menor valor, pegamos o ultimo nó da Heap e colamos na raiz, decrementamos 1 no tamanho da Heap, pois retiramos um nó, e como colocamos o ultimo na raiz, precisamos voltar a manter a propriedade da Heap e assim retornamos o nó retirado para a função de criar a árvore.

3. Função min_heap:

    Como alteramos a propriedade da Heap, e colocamos o ultimo nó cujo o valor da frequência é maior, precisamos reogarnizar a Heap, para isso, nessa função recebemos a Heap e o índice da raiz. Para isso, precisamos verificar o nó da esquerda e o nó da direita, o menor entre eles irá "subir" para a raiz, então verificamos se ele já não é a própria raiz, se não for, trocamos o nó, e recursivamente, iremos verificar os próximos nós.


### Criando a árvore:

Agora iremos criar a árvore de huffman, para isso, precisamos retirar todos os nós da fila de prioridade de dois em dois, criar um novo nó que por definição é um "*", com a soma das frequências, e um nó irá para a esquerda e outro nó irá para a direita do novo nó criado.

# Função merge_nodes:
    
    Nessa função temos uma condição para que se tiver apenas um nó na heap, esse nó será a raiz da árvore, logo enquanto não for usamos a função dequeue da Heap. Então retiramos dois nós e mandamos esse novo nó para a Heap.

### Tamanho da Árvore:

Foi definido que no cabeçalho do novo arquivo compactado, vamos salvar o lixo dos novos bytes e o tamanho da árvore. Para salvarmos o tamanho da árvore, percorremos ela lembrando da condição definida de que se for um nó folha, e for um "*", então é um devemos colocar um "\"
e quando for "\" colocamos "\\", para identificar quando for descompactar o arquivo. Logo incrementamos o tamanho da árvore nesses casos.

### Definir os bytes:

Para isso, precisamos da árvore recursivamente e para obtermos uma busca em O(1) salvamos em uma Hash. Para definir os novos bits, percorremos na árvore. Foi definido que se para a esquerda da árvore, colocamos no novo mapeamento 0, e se direita 1.

# Como salvamos (Função define_new_bits):

    Com uma variavel que possui no máximo 16 bits zerado, quando vamos para a esquerda, deslocamos 1 vez o byte todo para a esquerda, com isso, como o byte está zerado, garantimos que "colocamos" um zero. e quando iremos para a esquerda, basta adicionar 1 no byte.

Quando chegar em uma folha da árvore salvamos na Hash usando a função put_in_hash, nessa função apenas salvamos na posição do item que está na folha o seu novo mapeamento, e o tamanho do novo mapeamento para quando for "setar" os novos bits, sabermos onde começar.

### Colocar a árvore no arquivo:

Antes de colocar os novos bytes no arquivo, precisamos colocar a árvore no arquivo, mas antes para não sobre-escrever o arquivo, precisamos deixar um espaço para o cabeçalho, para isso, basta colocarmos dois bytes zerados, pois foi definido que o cabeçalho possui 16 bits, sendo 3 bits do lixo e 13 bits com o tamanho da árvore. Então recursivamente percorremos a árvore escrevendo no arquivo, e quando for um nó folha fazemos a verificação se é o "*" ou o "\".

### "Setar" os novos bytes:

Com o novo mapeamento na hash, iremos preencher bytes zerados, para compactar o arquivo. Lemos o arquivo original todo novamente, e para cada caracter lido iremos preenchendo o novo byte até completa-lo.

# Como fazemos? 

    Com um byte zerado (8 bits) começamos de 7 pois iremos até 0, o mesmo para quando acessarmos o mapeamento na hash (size - 1) pois vamos até 0. Para verificar se um bit está setado no mapeamento, ou seja, se ele é 1, empurramos o byte com a posição que estamos verificando atualmente, ou seja, de "j". Se o bit está setado, o resto dele por 2 será 1, e se não estiver, será 0. Usamos a função setar_bit para colocarmos na posição atual do byte, assim decrementemos sua posição atual.
    Quando a posição atual do byte chegar a -1, significa que preenchemos um byte inteiro, então basta colocarmos no arquivo, e zeramos o byte e inicializar sua posição inicial
    novamente.
    Para verificarmos se há lixo ou não, temos uma flag, em que se sobrar lixo, ela será falsa, assim precisamos salvar esse valor e retornarmos para a função principal.

Após definirmos os novos bytes, temos que terminar o cabeçalho, pois necessitavamos do lixo.

### Cabeçalho: 

Para o cabeçalho, com o lixo e o tamanho da árvore, como são 16 bits, e só usamos 3 bits para o lixo, basta "empurrarmos" em 13 para a esquerda, e então com uma operção de "ou" juntamos o lixo com o trash, mas para colocar no arquivo, precisamos separar em 2 bytes, logo, se "empurrarmos" em 8 para a direita, temos um byte e o outro basta atribuirmos visto que se um byte possui 8 bits, quando fizermos essa atribuição iremos receber só os 8 bits.

### Com isso foi feito a compactação. ###

### Descompactação: 

Para começarmos a descompactação, primeiramente precisamos de fazer o inverso do que fizemos para o cabeçalho para recuperarmos o valor do tamanho da árvore e o valor do lixo.

# Como fazemos ?

    Como separamos em dois bytes na hora de colocar no arquivo, para recebermos novamente, lemos em dois bytes, assim precisamos separar o lixo de um pedaço da árvore, para isso usamos um auxiliar para pegar um pedaço restante da árvore, logo "empurramos" 3 para a esquerda que é reservado para o lixo, como sabemos que são 13 bits para a árvore, logo colocamos em um short int que possui 16 bits, e como essa é a parte que fica na frente precisamos de "empurrar" em 5 para a esquerda, para sobrar apenas os 8 bits restantes da árvore, assim temos o tamanho completo dela. Para o lixo, basta pegar o primeiro byte e "empurrarmos" em 5 para a direita, restando assim somente os 3 bits iniciais que são o tamanho da árvore.

Agora precisamos montar a árvore.

# Como montar a árvore: 

    Recursivamente, lemos um caracter do arquivo e criamos um nó para ele, se for for diferente de "*" é uma folha da árvore, então, criamos um nó e retornamos ele. Lembrando de verificar se a folha é uma "\" ou um "*".

Após montar a árvore, precisamos percorrer todos os bytes que está no arquivo para saber quando é o ultimo byte pois se houver lixo temos que saber onde parar. Logo a função number_of_bytes retorna esse valor.

Voltamos o ponteiro do arquivo ignorando o tamanho da árvore e os dois bytes iniciais para pergarmos os bytes "setados".

### Voltar ao arquivo original: 

Para isso, usamos nossa função put_caracter_in_file.

# Função put_caracter_in_file:

    Para isso, usaremos a árvore, ao ler um caracter no arquivo, percorremos o byte dele 1 a 1, e caminhos em uma árvore auxiliar, usamos a função is_bit_set, para verificar se o bit está "setado" naquela posição, se estiver, caminhamos na árvore auxiliar para a direita, caso não para a direita, assim verificamos se a posição atual é uma folha, quando for uma folha, colocamos no arquivo quem é essa folha, e voltamos o ponteiro da árvore auxiliar para a raiz. Como sabemos quando será o ultimo byte, verificamos se ele possui lixo, pois se possuir, percorremos somente até onde é o lixo.

Após isso teremos nosso arquivo original e terminamos de descompactar o arquivo.

### Fim da descompactação ###


    