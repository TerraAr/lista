#include<stdio.h>
#include<stdlib.h>

static const char* fora_da_lista = "ERRO: Posição inexistente.\n";

const size_t TAMVOID=sizeof(void*);

template <class Type> class lista{
	private:
		void *inicio, *PosicaoAtual;
		unsigned long long posicao, fim;
		const size_t TamanhoTipo;

		inline void gotox(unsigned long long x)
				__attribute__((always_inline));

	public:
		lista(Type a = 0ULL);

		~lista();

		void gotopos(unsigned long long x);

		void addpos(unsigned long long a);

		void escreve(Type a);

		Type le();

		inline Type& operator[](const unsigned long long)
					__attribute__((always_inline));
};
