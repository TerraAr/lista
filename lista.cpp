#include"lista.h"

template <class Type> inline void lista<Type>::gotox(unsigned long long x){
	if(x < posicao){
		posicao = 0ULL;
		PosicaoAtual = inicio;
	}
	for(; x > posicao; posicao++)
		PosicaoAtual = *(void**)PosicaoAtual;
	}

template <class Type> lista<Type>::lista(Type a){
	inicio = malloc(TamanhoTipo);
	PosicaoAtual = inicio;
	posicao = fim = 0ULL;
	* (Type*) (PosicaoAtual+TAMVOID) = a;
}

template <class Type> lista<Type>::~lista(){
	while(fim > 0ULL){
		gotox(fim--);
		free(PosicaoAtual);
	}
	free(inicio);
}

template <class Type> void lista<Type>::gotopos(unsigned long long x){
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

template <class Type> void lista<Type>::addpos(unsigned long long a){
	for(; a>0ULL; fim++, a--){
		gotox(fim);
		*(void**)PosicaoAtual = malloc(TamanhoTipo);
	}
}

template <class Type> void lista<Type>::escreve(Type a){
	*((Type*) (PosicaoAtual + TAMVOID)) = a;
}

template <class Type> Type lista<Type>::le(){
	return * (Type*) (PosicaoAtual + TAMVOID);
}

template <class Type> inline Type& lista<Type>::operator[]
					(const unsigned long long pos){
	gotopos(pos);
	return * (Type*) (PosicaoAtual + TAMVOID);
}
