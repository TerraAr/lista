#include"lista.h"

template <class Type> inline void lista<Type>::gotox
				(const unsigned long long pos){
	/* Se tiver a frente, retorna até a posição */
	for(; posicao > pos; posicao--)
		PosicaoAtual = PosicaoAtual -> anterior;

	/* Se tiver atrás, vai até a posição */
	for(; posicao < pos; posicao++)
		PosicaoAtual = PosicaoAtual -> proximo;
}

template <class Type> lista<Type>::lista(){
	PosicaoAtual = inicio = NULL;
	posicao = tamanho_lista = 0ULL;
}

template <class Type> lista<Type>::~lista(){
	while(tamanho_lista > 0ULL){
		gotox(--tamanho_lista);
		free(PosicaoAtual);
	}
}

template <class Type> void lista<Type>::gotopos(const unsigned long long pos){
	if(pos > tamanho_lista){
		fputs(fora_da_lista, stderr);
		return (void)1;
	}

	/* Se tiver a frente, retorna até a posição */
	for(; posicao > pos; posicao--)
		PosicaoAtual = PosicaoAtual -> anterior;

	/* Se tiver atrás, vai até a posição */
	for(; posicao < pos; posicao++)
		PosicaoAtual = PosicaoAtual -> proximo;

	return (void)0;
}

template <class Type> void lista<Type>::addpos(unsigned long long a){
	/* Se a lista está vazia, cria o primeiro nó */
	if(tamanho_lista == 0ULL){
		PosicaoAtual = inicio = (no*)malloc(sizeof(no));
		PosicaoAtual -> anterior = NULL;
		PosicaoAtual -> proximo = NULL;

		a--;
	}

	/* Cria os nós logo depois da posição atual */
	for(; a > 0ULL; tamanho_lista++, a--){
		no *aux = (no*) malloc(sizeof(no));

		/* Trava o nó auxiliar neste */
		aux -> anterior = PosicaoAtual;
		/* Trava o nó auxiliar no próximo */
		aux -> proximo = PosicaoAtual -> proximo;

		/* Trava o proximo nó no auxiliar */
		if(PosicaoAtual -> proximo != NULL)
			(PosicaoAtual -> proximo) -> anterior = aux;
		/* Trava este nó no auxiliar */
		PosicaoAtual -> proximo = aux;
	}
}

template <class Type> inline void lista<Type>::rmpos
			(unsigned long long qte_celulas){
	for(; qte_celulas > 0ULL; qte_celulas--){
		/* Verifica a lista é não-vazia */
		if(tamanho_lista == 0ULL){
			fputs(lista_vazia, stderr);
			return;
		}

		/* Verifica se é a última posição */
		if(PosicaoAtual -> proximo != NULL){	// Se não é
			/* Desvincula a próxima célula desta */
			(PosicaoAtual -> proximo) -> anterior =
				PosicaoAtual -> anterior;

			/* Desvincula a célula anterior desta */
			(PosicaoAtual -> anterior) -> proximo =
				PosicaoAtual -> proximo;

			/* Salva o ponteiro do nó */
			no* apagando = PosicaoAtual;

			/* Manda o marcador de posição para o próximo nó */
			PosicaoAtual = PosicaoAtual -> proximo;

			/* Libera o nó */
			free(apagando);

			/* Diminui o marcador de tamanho da lista */
			tamanho_lista--;
		}else{	//Se é
			/* Vai para a posição anterior */
			PosicaoAtual = PosicaoAtual -> anterior;
			posicao--;

			/* Libera a última posição */
			free(PosicaoAtual -> proximo);
			PosicaoAtual -> proximo = NULL;

			/* Diminui o marcador de tamanho da lista */
			tamanho_lista--;
		}
	}
}

template <class Type> inline unsigned long long lista<Type>::tam_lista(){
	return tamanho_lista;
}

template <class Type> void lista<Type>::escreve(Type a){
	PosicaoAtual -> dado = a;
}

template <class Type> Type lista<Type>::le(){
	return PosicaoAtual -> dado;
}

template <class Type> lista<Type> lista<Type>::operator+(const Type valor){
	lista<Type> lista_mais = *this;
	lista_mais += valor;
	return lista_mais;
}

template <class Type> lista<Type> lista<Type>::operator+
				(const lista<Type> seg_lista){
	lista<Type> lista_mais = *this;
	lista_mais += seg_lista;
	return lista_mais;
}

template <class Type> lista<Type> lista<Type>::operator-
				(const unsigned long long quant_pos){
	lista<Type> lista_menos = *this;
	lista_menos -= quant_pos;
	return lista_menos;
}

template <class Type> inline void lista<Type>::operator=
				(const lista<Type> seg_lista){
	for(unsigned long long i = 0ULL; i < seg_lista.tamanho_lista; i++){
		if(tamanho_lista <= i)
			addpos(1ULL);
		*this[i] = seg_lista[i];
	}

	if(tamanho_lista > seg_lista.tamanho_lista)
		*this -= tamanho_lista - seg_lista.tamanho_lista;
}

template <class Type> inline void lista<Type>::operator+=(const Type valor){
	/* Vai para o fim da lista */
	gotox(tamanho_lista - 1ULL);

	/* Adiciona mais uma célula */
	addpos(1ULL);

	/* Coloca o dado na última célula */
	gotox(tamanho_lista - 1ULL);
	PosicaoAtual -> dado = valor;
}

template <class Type> inline void lista<Type>::operator+=
				(const lista<Type> seg_lista){
	for(unsigned long long i = 0ULL; i < seg_lista.tamanho_lista; i++)
		*this += seg_lista[i];
}

template <class Type> inline void lista<Type>::operator-=
				(const unsigned long long quant_pos){
	for(unsigned long long i = 0ULL; i< quant_pos; i++)
		(*this)--;
}

template <class Type> inline void lista<Type>::operator--(){
	/* Verifica se a lista é vazia */
	if(tamanho_lista ==0ULL){
		/* Se for, dá mensagem de erro */
		fputs(lista_vazia, stderr);
		return;
	}
	/* Verifica se é célula única */
	if(tamanho_lista == 1ULL){
		/* Libera a única célula */
		free(inicio);
		PosicaoAtual = inicio = NULL;
		tamanho_lista = 0ULL;
		return;
	}

	/* Vai até a penultima posição */
	gotox(tamanho_lista - 2ULL);

	/* Libera a última posição */
	free(PosicaoAtual -> proximo);

	/* Ajusta a célula e o cabeçalho da lista */
	PosicaoAtual -> proximo = NULL;
	tamanho_lista--;
}

template <class Type> inline bool lista<Type>::operator==
				(const lista<Type> cmp){
	/* Verifica se as duas listas tem o mesmo tamanho */
	if(tamanho_lista != cmp.tamanho_lista)
		return false;

	/* Se tiverem, verifica a igualdade célula a célula */
	for(unsigned long long i = 0ULL; i < tamanho_lista; i++)
		if(*this[i] != cmp[i])
			return false;

	/* Se não tiver nenhuma diferença, é igual */
	return true;
}

template <class Type> inline bool lista<Type>::operator!=
				(const lista<Type> cmp){
	return !(*this == cmp);
}

template <class Type> inline bool lista<Type>::operator>(const lista<Type> cmp){
	return tamanho_lista > cmp.tamanho_lista;
}

template <class Type> inline bool lista<Type>::operator<(const lista<Type> cmp){
	return tamanho_lista < cmp.tamanho_lista;
}

template <class Type> inline bool lista<Type>::operator>=
				(const lista<Type> cmp){
	return tamanho_lista >= cmp.tamanho_lista;
}

template <class Type> inline bool lista<Type>::operator<=
				(const lista<Type> cmp){
	return tamanho_lista <= cmp.tamanho_lista;
}

template <class Type> Type& lista<Type>::operator[]
				(const unsigned long long pos){
	gotopos(pos);
	return PosicaoAtual -> dado;
}

template <class Type> unsigned long long lista<Type>::count_elem(Type elem){
	unsigned long long cont = 0ULL;

	for(unsigned long long i = 0ULL; i < tamanho_lista; i++)
		if(*this[i] == elem)
			cont++;

	return cont;
}

template <class Type> unsigned long long lista<Type>::count_elems
					(Type *elems, const unsigned tam){
	unsigned long long cont;

	for(unsigned i=0; i < tam; i++)
		cont += (*this).count_elem(elems[i]);

	return cont;
}

template <class Type> lista<Type> vetor_para_lista
				(Type* vetor, const unsigned tam){
	lista<Type> lista_return;
	for(unsigned i = 0U; i < tam; i++)
		lista_return += vetor[i];
	return lista_return;
}

string::string(){
	PosicaoAtual = inicio = (no*)malloc(sizeof(char));
	posicao = 0ULL;
	tamanho_lista = 1ULL;

	/* Seta a primeira célula */
	PosicaoAtual -> dado = '\0';
	PosicaoAtual -> proximo = PosicaoAtual -> anterior= NULL;
}

string string::operator+(const char caractere){
	string resultado = *this;

	/* Vai para a penúltima célula */
	resultado.gotox(tamanho_lista - 2ULL);

	/* Adiciona uma célula antes do '\0' */
	resultado.addpos(1ULL);

	/* Agora a string resultado tem tamanho tamanho_lista+1 */
	resultado[tamanho_lista - 1ULL] = caractere;

	return resultado;
}

string string::operator+(const char *str){
	string resultado = *this;

	for(unsigned long long i = 0ULL; *(str + i); i++)
		resultado += *(str + i);

	return resultado;
}

string string::operator+(string str){
	string resultado = *this;

	for(unsigned long long i = 0ULL; str[i]; i++)
		resultado += str[i];

	return resultado;
}

void string::operator+=(const char caractere){
	/* Vai para a penúltima célula */
	gotox(tamanho_lista - 2ULL);

	/* Adiciona uma célula antes do '\0' */
	addpos(1ULL);

	/* Colocando o caractere antes do '\0' */
	gotox(tamanho_lista - 2ULL);
	PosicaoAtual -> dado = caractere;
}

void string::operator+=(string str){
	for(unsigned long long i = 0ULL; str[i]; i++)
		*this += str[i];
}

void string::operator-=(unsigned long long quant_pos){
// TODO: Escrever o operador -=
#pragma mensage TODO: escrever o operador -=
}

void string::operator=(const char* str){
	/* Copia até acabar as posições de um deles */
	unsigned long long i;
	for(i = 0ULL; str[i] && (*this)[i]; i++)
		(*this)[i] = str[i];

	/* Se a string acabou e o vetor char não, continua a cópia */
	if(str[i])
		*this += str + i;

	/* Se o vetor char acabou e a string não, destruir até o '\0' */
	if(str[i])
		*this -= tamanho_lista - i - 1ULL;
}

void string::operator+=(const char* str){
	for(unsigned long long i = 0ULL; str[i]; i++)
		*this += str[i];
}

bool string::operator==(const char* str){
	for(unsigned long long i = 0ULL; str[i] || (*this)[i]; i++)
		if((*this)[i] != str[i])
			return false;
	return true;
}

bool string::operator!=(const char* str){
	return !(*this == str);
}
