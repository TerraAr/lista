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
				__attribute__((always_inline)){
			if(x < posicao){
				posicao = 0ULL;
				PosicaoAtual = inicio;
			}
			for(; x > posicao; posicao++)
				PosicaoAtual = *(void**)PosicaoAtual;
		}

	public:
		lista(Type a = 0ULL) : TamanhoTipo(sizeof(Type) + TAMVOID){
			inicio = malloc(TamanhoTipo);
			PosicaoAtual = inicio;
			posicao = fim = 0ULL;
			* (Type*) (PosicaoAtual+TAMVOID) = a;
		}

		~lista(){
			while(fim > 0ULL){
				gotox(fim--);
				free(PosicaoAtual);
			}
			free(inicio);
		}

		void gotopos(unsigned long long x){
			if(x > fim){
				fputs(fora_da_lista, stderr);
				return (void)1;
			}
			if(x < posicao){
				posicao = 0ULL;
				PosicaoAtual = inicio;
			}
			for(; x>posicao; posicao++){
				PosicaoAtual = *(void**)PosicaoAtual;
			}
			return (void)0;
		}

		void addpos(unsigned long long a){
			for(; a>0ULL; fim++, a--){
				gotox(fim);
				*(void**)PosicaoAtual =
					malloc(TamanhoTipo);
			}
		}

		void escreve(Type a){
			*((Type*) (PosicaoAtual + TAMVOID)) = a;
		}
		Type le() {return * (Type*) (PosicaoAtual + TAMVOID);}

		inline Type& operator[](const unsigned long long)
					__attribute__((always_inline));
};

template <class Type> inline Type& lista<Type>::operator[]
					(const unsigned long long pos){
	gotopos(pos);
	return * (Type*) (PosicaoAtual + TAMVOID);
}
