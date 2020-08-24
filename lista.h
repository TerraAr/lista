/* Copyright (C) 2018 - 2020 Fernando José Carames Vecino.
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

	inline void gotox(const unsigned long long pos)
			__attribute__((always_inline));

public:
	lista();
	~lista();

	inline void gotopos(const unsigned long long pos)
			__attribute__((always_inline));

	/* Adiciona as células logo após a célula atual */
	void addpos(unsigned long long qte_celulas);
	void rmpos(unsigned long long qte_celulas = 1ULL);

	/* Retorna o tamanho da lista */
	inline unsigned long long tam_lista()
			__attribute__((always_inline));

	/* Escreve o dado na posição atual da lista */
	void escreve(Type a) __attribute__((always_inline));

	/* Lê o dado na posição atual da lista */
	inline Type le() __attribute__((always_inline));

	lista<Type> operator+(const Type valor);
	lista<Type> operator+(const lista<Type> seg_lista);
	lista<Type> operator-(const unsigned long long quant_pos);

	inline void operator+=(const Type valor)
			__attribute__((always_inline));

	inline void operator=(lista<Type>)
			__attribute__((always_inline));
	inline void operator+=(lista<Type> seg_lista)
			__attribute__((always_inline));
	inline void operator-=
			(unsigned long long quant_pos)
			__attribute__((always_inline));

	inline void operator--()
		__attribute__((always_inline));

	inline bool operator==(lista<Type>)
			__attribute__((always_inline));
	inline bool operator!=(const lista<Type>)
			__attribute__((always_inline));

	inline bool operator>(const lista<Type>)
			__attribute__((always_inline));
	inline bool operator<(const lista<Type>)
			__attribute__((always_inline));
	inline bool operator>=(const lista<Type>)
			__attribute__((always_inline));
	inline bool operator<=(const lista<Type>)
			__attribute__((always_inline));
	inline bool eVazia()
		__attribute__((always_inline));

	Type& operator[](const unsigned long long);

	inline void esvazia()
		__attribute__((always_inline));

	bool have_elem(Type elem);

	unsigned long long count_elem(Type elem);
	unsigned long long count_elems(Type *elems, const unsigned tam);

	friend class string;
};

template <class Type> lista<Type> vetor_para_lista
			(Type* vetor, const unsigned tam);

class string: public lista<char>{

public:
	string();

	inline void esvazia()
		__attribute__((always_inline));

	lista<string> unword(const char);

	string operator+(const char);
	string operator+(const char*);
	string operator+(string);
	string operator-(unsigned long long);

	/* Operador para adicionar um caractere no final da string.
	 * É usado como base para as demais funções */
	inline void operator+=(const char)
			__attribute__((always_inline));

	void operator=(string);
	void operator+=(string);
	void operator-=(unsigned long long);

	inline void operator--()
			__attribute__((always_inline));

	void operator=(const char*);
	void operator+=(const char*);

	inline bool operator==(string);
	inline bool operator!=(string);

	inline bool operator==(const char*);
	inline bool operator!=(const char*);

	inline bool eVazia()
		__attribute__((always_inline));
};

string word(lista<string>, const char);

#endif /* LISTA_H */
