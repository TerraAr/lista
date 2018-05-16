#include<stdlib.h>
#include<stdio.h>

const unsigned short TAMVOID=sizeof(void*);

template <class Type> class lista{
private:
void *inicio,**PosicaoAtual;
unsigned long long posicao,fim;
unsigned short TamanhoTipo;
public:
lista(){
TamanhoTipo=sizeof(Type)+TAMVOID;
inicio=malloc(TamanhoTipo);
PosicaoAtual=(void**)inicio;
posicao=fim=0;
}

lista(Type a){
TamanhoTipo=sizeof(Type)+TAMVOID;
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

bool gotox(unsigned long long x){
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

void escreve(Type a){
*(Type*)(PosicaoAtual+TAMVOID)=a;
}

Type le(){
return *(Type*)(PosicaoAtual+TAMVOID);
}
};

int main(){
lista<int> as(32);
as.addpos(1);
as.gotox(1);
as.escreve(5210);
as.gotox(0);
printf("%i\n",as.le());
as.gotox(1);
printf("%i\n",as.le());
return 0;
}
