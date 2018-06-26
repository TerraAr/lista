#include<stdlib.h>
#include<stdio.h>

static const char* fora_da_lista = "ERRO: Posição inexistente.\n";

const unsigned short TAMVOID=sizeof(void*);

template <class Type> class lista{
private:
void *inicio,**PosicaoAtual;
unsigned long long posicao,fim;
const unsigned short TamanhoTipo;

void gotox(unsigned long long x){
if(x<posicao){
posicao=0;
PosicaoAtual=(void**)inicio;
}
for(;x>posicao;posicao++)
PosicaoAtual=(void**)*PosicaoAtual;
}

public:
lista(Type a=0) : TamanhoTipo(sizeof(Type)+TAMVOID){
inicio=malloc(TamanhoTipo);
PosicaoAtual=(void**)inicio;
posicao=fim=0;
*(Type*)(PosicaoAtual+TAMVOID)=a;
}

~lista(){
while(fim>0){
gotox(--fim);
free(*PosicaoAtual);
}
free(inicio);
}

bool gotopos(unsigned long long x){
if(x>fim) return 0;
if(x<posicao){
posicao=0;
PosicaoAtual=(void**)inicio;
}
for(;x>posicao;posicao++)
PosicaoAtual=(void**)*PosicaoAtual;
return 1;
}

void addpos(unsigned long long a){
for(;a>0;a--,fim++){
gotox(fim);
*PosicaoAtual=malloc(TamanhoTipo);
}
}

void escreve(Type a) {*(Type*)(PosicaoAtual+TAMVOID)=a;}
Type le() {return *(Type*)(PosicaoAtual+TAMVOID);}

inline Type& operator[](const unsigned long long);
};

template <class Type> inline Type& lista<Type>::operator[](const unsigned long long pos){
if(!gotopos(pos)) fprintf(stderr,"%s",fora_da_lista);
return *(Type*)(PosicaoAtual+TAMVOID);
}
