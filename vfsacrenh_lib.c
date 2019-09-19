/*
	 vfsacrenh_lib.c (c)
	 
	 Objetivo: Biblioteca de funções do programa 'Mvfsacrenh.c'.
	 Realiza a otimização dos parâmetros RNIP e BETA do CRE zero offset,
	 aplicando a condição CDS (RN=RNIP) à aproximação do CRS não Hiperbólico (Fomel, 2013).
	 
	 Versão 1.0
	 
	 Site: http://www.dirackslounge.online
	 
	 Programador: Rodolfo A. C. Neves (Dirack) 29/08/2019
	 
	 Email: rodolfo_profissional@hotmail.com
	 
	 Licença: Software de uso livre e código aberto.
*/

#define Beta_MAX 1
#define Beta_MIN -1
#define Rnip_MAX 2
#define Rnip_MIN 0
#define hMAX 50
#define mMAX 50
#define ITMAX 10000
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <rsf.h>
/*^*/

float sinal(float s) { 
/*< Função sinal >*/

	if(s >= 0){
		
		return s = 1;		
	}
	
	return s=-1;
		
}

float gerarNumeroAleatorioEntre0e1(){
/*< Função gerar número aleatório entre 0 e 1 >*/

	float numeroAleatorio;
	int u;

	u = rand()%1000;
			
	numeroAleatorio = (float)u/1000;

	return numeroAleatorio;

}

float temperaturaIteracaoVfsa(int iteracao,float fatorDeAmortecimento,float temperaturaInicial){
/*< Função temperatura do algoritmo VFSA >*/

	float temperatura;

	temperatura=temperaturaInicial*expf(-fatorDeAmortecimento*pow(iteracao,0.25));

	return temperatura;
}

void perturbacaoParametros(float temperatura, float* parametrosPerturbados, float* parametros){
/*< Perturbar os parâmetros da iteração anterior >*/

	float u;
	float perturbacao;
	float janelaDeBusca;

	u=gerarNumeroAleatorioEntre0e1();
			
	perturbacao = sinal(u - 0.5) * temperatura * (pow( (1+temperatura),fabs(2*u-1) )-1);

	/* Perturbação e janelamento de RNIP */
	janelaDeBusca = Rnip_MAX - Rnip_MIN;

	parametrosPerturbados[0] = parametros[0] + perturbacao * (janelaDeBusca);
				
	if (parametrosPerturbados[0] >= Rnip_MAX || parametrosPerturbados[0] <= Rnip_MIN) {

		parametrosPerturbados[0] = (janelaDeBusca) * gerarNumeroAleatorioEntre0e1() + Rnip_MIN;
		
	}

	/* Perturbação e janelamento de BETA */
	janelaDeBusca = Beta_MAX - Beta_MIN;

	parametrosPerturbados[1] = parametros[1] + perturbacao * (janelaDeBusca);

	if (parametrosPerturbados[1] >= Beta_MAX || parametrosPerturbados[1] <= Beta_MIN) {

		parametrosPerturbados[1] = (janelaDeBusca) * gerarNumeroAleatorioEntre0e1() + Beta_MIN;

	}		

}

float fomel(float m, float h, float t0, float v0, float RNIP, float BETA){
/*< Aproximação de tempo de trânsito do CRS não hiperbólico (FOMEL; KAZINNIK, 2013) >*/
	float t;
	float a1, a2, b2, c1, Fd, Fdmais, Fdmenos;
	float RN;

	/* Condição CDS */
	RN=RNIP;
			
	a1=(2*sin(BETA))/(v0);		
	a2=(2*cos(BETA)*cos(BETA)*t0)/(v0*RN);
	b2=(2*cos(BETA)*cos(BETA)*t0)/(v0*RNIP);
	c1=2*b2+a1*a1-a2;
												
	Fd=(t0+a1*m)*(t0+a1*m)+a2*m*m;				
	Fdmenos=(t0+a1*(m-h))*(t0+a1*(m-h))+a2*(m-h)*(m-h);
	Fdmais=(t0+a1*(m+h))*(t0+a1*(m+h))+a2*(m+h)*(m+h);					
	return t=sqrt((Fd+c1*h*h+sqrt(Fdmenos*Fdmais))*0.5); 

}

float semblance(float m0, float dm, float om, float oh, float dh, float dt, int nt,float t0, float v0,float RNIP, float BETA, float*** t){
/*< Função Semblance >*/

	int im, ih, numAmostras=0;
	float m, h;
	float amplitude=0.;
	float somaAmplitudesAmostras=0.;
	float somaQuadradoAmplitudesAmostras=0.;
	float semblance=0;
	int tetai;
	float teta;
	int indice_m0;

	indice_m0 = (int)(m0/dm);

	for (im=indice_m0-mMAX; im < indice_m0+mMAX; im++){
			
		for(ih=0;ih<hMAX;ih++){

			m=im*dm+om;
	
			m=m-m0;
			
			h=ih*dh+oh;

			/* Aproximação Fomel (CRS NÃO hiperbólico) */
			teta = fomel(m,h,t0,v0,RNIP,BETA);

			tetai=teta/dt;

			if(tetai>=0 && tetai < nt){
				amplitude = t[im][ih][tetai];
			}else{
				amplitude=0.;
			}
	
			somaAmplitudesAmostras=somaAmplitudesAmostras+amplitude;
					
			somaQuadradoAmplitudesAmostras=somaQuadradoAmplitudesAmostras+(amplitude*amplitude);
				
			numAmostras++;
		}
		
	}		

	if(somaQuadradoAmplitudesAmostras==0 || somaAmplitudesAmostras==0)		
	return semblance=0;
	else
	return semblance=(somaAmplitudesAmostras*somaAmplitudesAmostras)/(numAmostras*somaQuadradoAmplitudesAmostras);

}

