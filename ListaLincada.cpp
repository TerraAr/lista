#include<stdlib.h>
#include<stdio.h>
template <class Type> class lista{
private:
void *inicio,**PosicaoAtual;
unsigned long long posicao,fim;
unsigned short TamanhoTipo;
public:
lista(){
TamanhoTipo=sizeof(Type)+sizeof(void*);
inicio=malloc(TamanhoTipo);
PosicaoAtual=(void**)inicio;
posicao=fim=0;
}

~lista(){
while(fim>0){
gotox(--fim);
free(*PosicaoAtual);
}
free(inicio);
}

bool gotox(unsigned long long x){
if(x>fim) return 0;
if(x<posicao){
posicao=0;
PosicaoAtual=(void**)inicio;
}
for(;x>posicao;posicao++){
PosicaoAtual=(void**)*PosicaoAtual;
}
return 1;
}

void addpos(unsigned a){
for(;a>0;a--,fim++){
gotox(fim);
*PosicaoAtual=malloc(TamanhoTipo);
}
}

void escreve(Type a){
Type *aux=(Type*)(PosicaoAtual+8);
*aux=a;
}

Type le(){
Type *aux=(Type*)(PosicaoAtual+8);
return *aux;
}
};

int main(){
lista<int> as;
as.addpos(1);
as.gotox(1);
as.escreve(5210);
as.gotox(0);
as.escreve(30);
printf("%i\n",as.le());
as.gotox(1);
printf("%i\n",as.le());
puts("Funcinou");
return 0;
}
