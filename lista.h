/* Copyright (C) 2018 - 2020 Fernando José Carames Vecino
 * (fernando.carames@gmail.com).
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

#ifndef LISTA_H
#define LISTA_H

static const char* fora_da_lista = "ERRO: Posição inexistente.\n";
static const char* lista_vazia = "ERRO: Lista vazia.\n";
static const char* remover_mais = "ERRO: Não há células suficientes para remover. Abortando.\n";

template <class Type> class lista{
private:
	class no{
		public:
		no *anterior;
		no *proximo;

		Type dado;
	};

	no *inicio, *PosicaoAtual;
	unsigned long long posicao, tamanho_lista;

	void gotox(const unsigned long long pos);

public:
	lista();
	lista(const lista&);
	~lista();

	operator Type*();

	void gotopos(const unsigned long long pos);

	/* Adiciona as células logo após a célula atual */
	void addpos(const unsigned long long celulas_a_adicionar);
	void rmpos(const unsigned long long celulas_a_remover);

	/* Retorna o tamanho da lista */
	unsigned long long tam_lista();

	/* Escreve o dado na posição atual da lista */
	void escreve(const Type a);

	/* Lê o dado na posição atual da lista */
	Type le();

	lista<Type> operator+(const Type valor);
	lista<Type> operator+(const lista<Type> seg_lista);
	lista<Type> operator-(const unsigned long long quant_pos);

	void operator=(const  lista<Type>);
	void operator+=(const Type valor);
	void operator+=(const lista<Type> seg_lista);
	void operator-=(const unsigned long long quant_pos);

	void operator--();

	bool operator==(const lista<Type>);
	bool operator!=(const lista<Type>);

	bool operator>(const lista<Type>);
	bool operator<(const lista<Type>);
	bool operator>=(const lista<Type>);
	bool operator<=(const lista<Type>);
	bool eVazia();

	Type& operator[](const unsigned long long);

	void esvazia();

	bool have_elem(const Type elem);

	unsigned long long count_elem(const Type elem);
	unsigned long long count_elems(const Type *elems, const unsigned tam);

	friend class string;
};

template <class Type> lista<Type> vetor_para_lista
			(const Type* vetor, const unsigned tam);

class string: public lista<char> {

public:
	string();
	string(const string&);
	string(const char*);

	/* Retorna o tamanho da lista */
	unsigned long long tam_lista();

	lista<string> unword(const char);

	string operator+(const char);
	string operator+(const char*);
	string operator+(const string);
	string operator-(const unsigned long long);

	/* Operador para adicionar um caractere no final da string.
	 * É usado como base para as demais funções */
	void operator+=(const char);

	void operator=(const string);
	void operator+=(const string);
	void operator-=(const unsigned long long celulas_a_remover);

	void operator--();

	void operator=(const char* str);
	void operator+=(const char* str);

	bool operator==(const string cmp);
	bool operator!=(const string cmp);

	bool operator==(const char* str);
	bool operator!=(const char* str);

	bool eVazia();

	void esvazia();
};

string word(lista<string>, const char);

#endif /* LISTA_H */
