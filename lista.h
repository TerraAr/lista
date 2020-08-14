#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static const char* fora_da_lista = "ERRO: Posição inexistente.\n";
static const char* lista_vazia = "ERRO: Lista vazia.\n";

template <class Type> class lista{
	protected:
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

		inline unsigned long long tam_lista()
				__attribute__((always_inline));

		void escreve(Type a) __attribute__((always_inline));

		inline Type le() __attribute__((always_inline));

		lista<Type> operator+(const Type valor);
		lista<Type> operator+(const lista<Type> seg_lista);
		lista<Type> operator-(const unsigned long long quant_pos);

		inline void operator+=(const Type valor)
				__attribute__((always_inline));

		inline void operator=(const lista<Type>)
				__attribute__((always_inline));
		inline void operator+=(const lista<Type> seg_lista)
				__attribute__((always_inline));
		inline void operator-=
				(const unsigned long long quant_pos)
				__attribute__((always_inline));

		inline void operator--() __attribute__((always_inline));

		inline bool operator==(const lista<Type>)
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

		Type& operator[](const unsigned long long);

		unsigned long long count_elem(Type elem);
		unsigned long long count_elems(Type *elems, const unsigned tam);
};

template <class Type> lista<Type> vetor_para_lista
			(Type* vetor, const unsigned tam);

class string: protected lista<char>{

public:
	string();

	string operator+(const char);
	string operator+(const char*);
	string operator+(const string);

	/* Operador para adicionar um caractere no final da string.
	 * É usado como base para as demais funções */
	inline void operator+=(const char)
			__attribute__((always_inline));

	void operator+=(const string);
	void operator-=(const unsigned long long);

	void operator=(const char*);
	void operator+=(const char*);

	bool operator==(const char*);
	bool operator!=(const char*);
};
