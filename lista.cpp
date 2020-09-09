/* Copyright (C) 2018 - 2020 Fernando José Carames Vecino
 * (fernando.carames@gmail.com)
 ************************************************************************
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>
 ************************************************************************
 *
 * Este programa é um software livre; você pode redistribuí-lo e/ou
 * modificá-lo sob os termos da Licença Pública Geral GNU como publicada
 * pela Free Software Foundation; na versão 3 da Licença, ou
 * (a seu critério) qualquer versão posterior.
 *
 * Este programa é distribuído na esperança de que possa ser útil,
 * mas SEM NENHUMA GARANTIA; sem uma garantia implícita de ADEQUAÇÃO
 * a qualquer MERCADO ou APLICAÇÃO EM PARTICULAR. Veja a
 * Licença Pública Geral GNU para mais detalhes.
 *
 * Você deve ter recebido uma cópia da Licença Pública Geral GNU junto
 * com este programa. Se não, veja <http://www.gnu.org/licenses/>
 ************************************************************************
 */

#include"lista.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

template <class Type> void lista<Type>::gotox
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

template <class Type> lista<Type>::lista(const lista<Type>& list){
	PosicaoAtual = inicio = NULL;
	posicao = tamanho_lista = 0ULL;

	/* Ponteiro auxiliar para percorrer a lista do início ao
	 * fim sem precisar modificar as variáveis de controle */
	{no* aux = list.inicio;
	for(unsigned long long i = 0ULL; i < list.tamanho_lista; i++){
		*this += aux -> dado;
		aux = aux -> proximo;
	}}
}

template <class Type> lista<Type>::~lista(){
	for(; tamanho_lista > 1ULL; tamanho_lista--){
		gotox(tamanho_lista - 2ULL);
		free(PosicaoAtual -> proximo);
	}
	free(inicio);
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
		do{
			PosicaoAtual = inicio = (no*)malloc(sizeof(no));
		}while(inicio == NULL);
		PosicaoAtual -> anterior = NULL;
		PosicaoAtual -> proximo = NULL;

		tamanho_lista = 1ULL;
		a--;
	}

	/* Cria os nós logo depois da posição atual */
	for(; a > 0ULL; a--){
		no *aux;
		do{
			aux = (no*) malloc(sizeof(no));
		}while(aux == NULL);

		/* Trava o nó auxiliar neste */
		aux -> anterior = PosicaoAtual;
		/* Trava o nó auxiliar no próximo */
		aux -> proximo = PosicaoAtual -> proximo;

		/* Trava o proximo nó no auxiliar */
		if(PosicaoAtual -> proximo != NULL)
			(PosicaoAtual -> proximo) -> anterior = aux;
		/* Trava este nó no auxiliar */
		PosicaoAtual -> proximo = aux;

		/* Incrementa o tamanho da lista */
		tamanho_lista++;
	}
}

template <class Type> void lista<Type>::rmpos
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

template <class Type> unsigned long long lista<Type>::tam_lista(){
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

template <class Type> void lista<Type>::operator=
					(lista<Type> seg_lista){
	/* Ponteiro auxiliar para percorrer a lista do início ao
	 * fim sem precisar modificar as variáveis de controle */
	{no *aux = seg_lista.inicio;
	for(unsigned long long i = 0ULL; i < seg_lista.tamanho_lista; i++){
		if(tamanho_lista <= i)
			addpos(1ULL);
		gotox(i);
		PosicaoAtual -> dado = aux -> dado;
		aux = aux -> proximo;
	}}

	if(tamanho_lista > seg_lista.tamanho_lista)
		*this -= tamanho_lista - seg_lista.tamanho_lista;
}

template <class Type> void lista<Type>::operator+=
					(const Type valor){
	/* Se não é vazia, vai para o fim da lista */
	if(tamanho_lista != 0ULL){
		gotox(tamanho_lista - 1ULL);
	}

	/* Adiciona mais uma célula */
	addpos(1ULL);

	/* Vai para a última posição */
	gotox(tamanho_lista - 1ULL);

	/* Coloca o dado na última célula */
	PosicaoAtual -> dado = valor;
}

template <class Type> void lista<Type>::operator+=
				(const lista<Type> seg_lista){
	/* Ponteiro auxiliar para percorrer a lista do início ao
	 * fim sem precisar modificar as variáveis de controle */
	{no *aux = seg_lista.inicio;
	for(unsigned long long i = 0ULL; i < seg_lista.tamanho_lista; i++){
		*this += aux -> dado;
		aux = aux -> proximo;
	}}
}

template <class Type> void lista<Type>::operator-=
				(unsigned long long quant_pos){
	for(; quant_pos > 0ULL; quant_pos--)
		(*this)--;
}

template <class Type> void lista<Type>::operator--(){
	/* Verifica se a lista é vazia */
	if(tamanho_lista == 0ULL){
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

template <class Type> bool lista<Type>::operator==
				(const lista<Type> cmp){
	/* Verifica se as duas listas tem o mesmo tamanho */
	if(tamanho_lista != cmp.tamanho_lista)
		return false;

	/* Se tiverem, verifica a igualdade célula a célula */
	{no *aux = cmp.inicio;
	for(unsigned long long i = 0ULL; i < tamanho_lista; i++){
		if((*this)[i] != aux -> dado)
			return false;
		aux = aux -> proximo;
	}}

	/* Se não tiver nenhuma diferença, é igual */
	return true;
}

template <class Type> bool lista<Type>::operator!=
				(const lista<Type> cmp){
	return !(*this == cmp);
}

template <class Type> bool lista<Type>::operator>(const lista<Type> cmp){
	return tamanho_lista > cmp.tamanho_lista;
}

template <class Type> bool lista<Type>::operator<(const lista<Type> cmp){
	return tamanho_lista < cmp.tamanho_lista;
}

template <class Type> bool lista<Type>::operator>=
				(const lista<Type> cmp){
	return tamanho_lista >= cmp.tamanho_lista;
}

template <class Type> bool lista<Type>::operator<=
				(const lista<Type> cmp){
	return tamanho_lista <= cmp.tamanho_lista;
}

template <class Type> bool lista<Type>::eVazia(){
	return tamanho_lista == 0ULL;
}

template <class Type> Type& lista<Type>::operator[]
				(const unsigned long long pos){
	gotopos(pos);
	return PosicaoAtual -> dado;
}

template <class Type> void lista<Type>::esvazia(){
	(*this) -= tamanho_lista;
}

template <class Type> bool lista<Type>::have_elem(Type elem){
	for(unsigned long long i = 0ULL; i < tamanho_lista; i++)
		if((*this)[i] == elem)
			return true;

	return false;
}

template <class Type> unsigned long long lista<Type>::count_elem(Type elem){
	unsigned long long cont = 0ULL;

	for(unsigned long long i = 0ULL; i < tamanho_lista; i++)
		if((*this)[i] == elem)
			cont++;

	return cont;
}

template <class Type> unsigned long long lista<Type>::count_elems
					(Type *elems, const unsigned tam){
	unsigned long long cont;

	for(unsigned i = 0U, cont = 0ULL; i < tam; i++)
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
	do{
		PosicaoAtual = inicio = (no*)malloc(sizeof(no));
	}while(inicio == NULL);
	posicao = 0ULL;
	tamanho_lista = 1ULL;

	/* Seta a primeira célula */
	PosicaoAtual -> dado = '\0';
	PosicaoAtual -> proximo = PosicaoAtual -> anterior = NULL;
}

string::string(const string& str){
	PosicaoAtual = inicio = NULL;
	posicao = tamanho_lista = 0ULL;

	addpos(str.tamanho_lista);

	/* Ponteiro auxiliar para percorrer a lista do início ao
	 * fim sem precisar modificar as variáveis de controle */
	{no* aux = str.inicio;
	for(unsigned long long i = 0ULL; i < tamanho_lista; i++){
		(*this)[i] = aux -> dado;
		aux = aux -> proximo;
	}}
}

string::string(const char* str){
	PosicaoAtual = inicio = NULL;
	posicao = tamanho_lista = 0ULL;

	addpos(strlen(str) + 1ULL);

	for(unsigned long long i = 0ULL; i < tamanho_lista; i++)
		(*this)[i] = *(str + i);
}

unsigned long long string::tam_lista(){
	return tamanho_lista;
}

lista<string> string::unword(const char caractere){
	lista<string> resultado;
	string palavra;

	for(unsigned long long i = 0ULL; (*this)[i]; i++){
		if((*this)[i] != caractere)
			palavra += (*this)[i];
		else{
			resultado += palavra;
			palavra -= palavra.tamanho_lista - 1ULL;
		}
	}

	return resultado;
}

string string::operator+(const char caractere){
	string resultado = *this;

	resultado += caractere;

	return resultado;
}

string string::operator+(const char *str){
	string resultado = *this;

	for(unsigned long long i = 0ULL; *(str + i); i++)
		resultado += *(str + i);

	return resultado;
}

string string::operator+(const string str){
	string resultado = *this;

	/* Ponteiro auxiliar para percorrer a lista do início ao
	 * fim sem precisar modificar as variáveis de controle */
	{no *aux = str.inicio;
	for(unsigned long long i = 0ULL; aux -> dado; i++){
		/* Adiciona o dado da célula na lista */
		resultado += aux -> dado;
		/* Vai para a próxima célula */
		aux = aux -> proximo;
	}}

	return resultado;
}

string string::operator-(const unsigned long long quant_pos){
	string resultado = *this;

	resultado -= quant_pos;

	return resultado;
}

void string::operator+=(const char caractere){
	if(tamanho_lista == 1ULL){
		no* aux;

		/* Garante que vai alocar a célula */
		do{
			aux = (no*) malloc(sizeof(no));
		}while(aux == NULL);

		/* Trava o nó */
		aux -> anterior = NULL;
		aux -> proximo = inicio;
		inicio -> anterior = aux;
		inicio = aux;

		/* Incrementa o tamanho da lista */
		tamanho_lista++;

		/* Recolocando o marcador de posição na 1ª posição */
		PosicaoAtual = inicio;

		/* Carrega o caractere */
		inicio -> dado = caractere;
	}else{
		/* Vai para a última célula */
		gotox(tamanho_lista - 2ULL);

		/* Adiciona uma célula antes do '\0' */
		addpos(1ULL);

		/* Colocando o caractere antes do '\0' */
		gotox(tamanho_lista - 2ULL);
		PosicaoAtual -> dado = caractere;
	}
}

void string::operator=(const string str){
	(*this).esvazia();
	(*this) += str;
}

void string::operator+=(const string str){
	/* Ponteiro auxiliar para percorrer a lista do
	 * início ao fim sem precisar modificar as
	 * variáveis de controle */
	{no *aux = str.inicio;
	for(unsigned long long i = 0ULL; aux -> dado; i++){
		/* Adiciona o dado da célula na lista */
		*this += aux -> dado;
		/* Vai para a próxima célula */
		aux = aux -> proximo;
	}}
}

void string::operator-=(unsigned long long quant_pos){
	for(; quant_pos > 0ULL; quant_pos--)
		--(*this);
}

void string::operator--(){
	/* Verifica se a lista é vazia */
	if(tamanho_lista == 1ULL){
		/* Se for, dá mensagem de erro */
		fputs(lista_vazia, stderr);
		return;
	}
	/* Verifica se é célula única */
	if(tamanho_lista == 2ULL){
		/* Libera a única célula */
		PosicaoAtual = inicio -> proximo;
		free(inicio);
		inicio = PosicaoAtual;
		tamanho_lista = 1ULL;
		return;
	}

	/* Vai até o penúltimo caractere */
	gotox(tamanho_lista - 3ULL);

	/* Libera a última posição */
	no *no_remover = PosicaoAtual -> proximo;
	(no_remover -> proximo) -> anterior = PosicaoAtual;
	PosicaoAtual -> proximo = no_remover -> proximo;
	free(no_remover);

	/* Decrementa o tamanho da lista */
	tamanho_lista--;
}

void string::operator=(const char* str){
	(*this).esvazia();
	*this += str;
}

void string::operator+=(const char* str){
	for(unsigned long long i = 0ULL; str[i]; i++)
		*this += str[i];
}

bool string::operator==(const string cmp){
	/* Verifica se as duas listas tem o mesmo tamanho */
	if(tamanho_lista != cmp.tamanho_lista)
		return false;

	/* Se tiverem, verifica a igualdade célula a célula */
	{no *aux = cmp.inicio;
	for(unsigned long long i = 0ULL; i < tamanho_lista; i++){
		if((*this)[i] != aux -> dado)
			return false;
		aux = aux-> proximo;
	}}

	/* Se não tiver nenhuma diferença, é igual */
	return true;
}

bool string::operator!=(const string cmp){
	return !(*this == cmp);
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

void string::esvazia(){
	(*this) -= tamanho_lista - 1ULL;
}

bool string::eVazia(){
	return tamanho_lista == 1ULL;
}

string word(lista<string> palavras, const char caractere){
	string word = palavras[0ULL];
	for(unsigned long long i = 1ULL; i < palavras.tam_lista(); i++){
		word += caractere;
		word += palavras[i];
	}
}

