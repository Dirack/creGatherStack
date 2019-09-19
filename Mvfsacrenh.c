/* Versão 1.0 - Inversão dos parâmetros do CRE zero offset (RNIP, BETA) utilizando o VFSA

Este programa utiliza o algoritmo de otimização global Very Fast Simulated Aneeling (VFSA),
e aplica a condição CDS (RN=RNIP) à aproximação não hiperbólica do CRS (Fomel, 2013).

Programador: Rodolfo A. C. Neves (Dirack) 29/08/2019

Email(Manutenção):  rodolfo_profissional@hotmail.com  

 */
/*
  Copyright (C) 2018 grupo de programação aplicada à geofísica (GPGEOF)
  da Universidade Federal do Pará (UFPA); Belém, Pará, Brasil. 

  Esse programa é um software livre; você pode redistribuir e/ou modificar
  sobre os termos da licensa pública geral (LPG) publicada pela Free 
  Software Foundation; na versão 2 da licensa, ou (a seu critério) qualquer
  versão posterior.

  Este programa é distribuído na esperança que será útil, mas SEM NENHUMA
  GARANTIA; nem mesmo a garantia implícita de MERCANTILIDADE ou SERVENTIA
  A UM PROPÒSITO DETERMINADO. veja a LPG licensa pública geral para mais
  detalhes.

  Você deve ter recebido uma cópia da LPG licensa pública geral junto com
  este programa; se não, escreva para a Free Software Foundation, Inc., 
  51 Franklin Street, Quinquagésimo andar, Boston, MA  02110-1301, USA.
*/

#include "vfsacrenh_lib.h"

int main(int argc, char* argv[])
{

	float m0; // CMP central da aproximação
	float om; // Origem do eixo dos CMP's
	float dm; // intervalo de amostragem dos CMP's
	int nm; // Número de CMP's
	float oh; // Origem da coordenada do meio afastamento
	float dh; // Intervalo de amostragem entre os meios-afastamentos
	int nh; // Número de meio-afastamentos
	int nt; // Número de amostras no eixo do tempo
	float ot; // Origem do eixo dos tempos
	float dt; // Amostragem no eixo do tempo
	bool verb; // Chave modo silencioso 0 e modo ativo 1
	float v0; // velocidade próxima a superfície
	float t0; // Tempo do raio normal para m0
	float cnew[2]; // Vetor temporário de parâmetros
	float c[2]; // Vetor temporário de parâmetros
	float *otm; // Vetor temporário de parâmetros otimizados
	float otrnip, otbeta, otsemb; // Parâmetros otimizados da iteração
	float deltaE, PM; // Parâmetros utilizados na verificação do critério de Metrópolis
	float Em0=0, u; // Semblance atual e número aleatório
	float ***t; // Cubo de dados
	int q; // Contador de laço
	float semb; // Semblance da iteração atual
	float RNIP, BETA; // Parâmetros desta iteração
	float temp; // Temperatura da iteração atual
	float semb0; // Maior semblance das iterações passadas
	float c0; // Fator de amortecimento VFSA
	float temp0; // Temperatura inicial VFSA

	/* Arquivos RSF E/S */  
	sf_file in, out;

	/* Eixos do arquivo RSF */
	sf_axis ax,ay,az;

	sf_init(argc,argv); 

	in = sf_input("in");
	out = sf_output("out");

	if (!sf_getfloat("m0",&m0)) m0=0;
	/* CMP central da aproximação (Km) */

	if (!sf_getfloat("v0",&v0)) v0=1.5;
	/* Velocidade próxima da superfície (Km/s) */

	if (!sf_getfloat("t0",&t0)) t0=1.5;
	/* Tempo do raio normal para m0 (s) */

	if (!sf_getfloat("c0",&c0)) c0=0.5;
	/* Fator de amortecimento VFSA */

	if (!sf_getfloat("temp0",&temp0)) temp0=10;
	/* Temperatura inicial VFSA */

	if (!sf_histint(in,"n1",&nt)) sf_error("Sem n1= no arquivo de entrada");
	if (!sf_histfloat(in,"d1",&dt)) sf_error("Sem d1= no arquivo de entrada");
	if (!sf_histfloat(in,"o1",&ot)) sf_error("Sem o1= no arquivo de entrada");
	if (!sf_histint(in,"n2",&nh)) sf_error("Sem n2= no arquivo de entrada");
	if (!sf_histfloat(in,"d2",&dh)) sf_error("Sem d2= no arquivo de entrada");
	if (!sf_histfloat(in,"o2",&oh)) sf_error("Sem o2= no arquivo de entrada");
	if (!sf_histint(in,"n3",&nm)) sf_error("Sem n3= no arquivo de entrada");
	if (!sf_histfloat(in,"d3",&dm)) sf_error("Sem d3= no arquivo de entrada");
	if (!sf_histfloat(in,"o3",&om)) sf_error("Sem o3= no arquivo de entrada");

	if(! sf_getbool("verb",&verb)) verb=0;
	/* Modo= 1: modo ativo;	0: modo silencioso */

	if (verb) {

		sf_warning("Modo ativo ligado!!!");
		sf_warning("Parâmetros lidos da linha de comandos: "); 
		sf_warning("m0=%f v0=%f t0=%f",m0,v0,t0);
		sf_warning("Parâmetros do arquivo de entrada: ");
		sf_warning("n1=%i d1=%f o1=%f",nt,dt,ot);
		sf_warning("n2=%i d2=%f o2=%f",nh,dh,oh);
		sf_warning("n3=%i d3=%f o3=%f",nm,dm,om);
	}
	
	c[0] = 0;
	c[1] = 0;
	cnew[0] = 0;
	cnew[1] = 0;

	srand(time(NULL));

	/* Ler o cubo de dados */
	t=sf_floatalloc3(nt,nh,nm);
	sf_floatread(t[0][0],nh*nm*nt,in);

	semb0=0;

	for (q=0; q <ITMAX; q++){
			
		/* Temperatura da iteração */
		temp=temperaturaIteracaoVfsa(q,c0,temp0);
						
		/* perturbação no parâmetro */
		perturbacaoParametros(temp,cnew,c);
																
		/* os parâmetros são atualizados 
		 após serem perturbados e janelados */
		RNIP=cnew[0];
		BETA=cnew[1];
	
		/* inicializando o valor do semblance */
		semb=0;
		
		/* Calcule o semblance da aproximação de tempo de trânsito CRS */		
		semb=semblance(m0,dm,om,oh,dh,dt,nt,t0,v0,RNIP,BETA,t);

		//sf_warning("(%i) RNIP=%f, BETA=%f, SEMB=%f, Em0=%f",q,RNIP,BETA,semb, semb0);
						
		/* condição de convergência dos parâmetros no algoritmo VFSA */		
		if(fabs(semb) > fabs(semb0) ){
			otsemb=semb;
			otrnip=RNIP;
			otbeta=BETA;
			semb0 = semb;
			//sf_warning("entrou!");			
		}
		
		/* condições de atualização dos parâmetros do VFSA */
		deltaE = -semb - Em0;
		
		/* Critério de metrópolis */
		PM = expf(-deltaE/temp);
		
		if (deltaE<=0){
			c[0] = cnew[0];
			c[1] = cnew[1];
			Em0 = -semb;
			//sf_warning("entrou!");
		} else {
			u=gerarNumeroAleatorioEntre0e1();
			if (PM > u){
				c[0] = cnew[0];
				c[1] = cnew[1];
				Em0 = -semb;
				//sf_warning("entrou!");
			}	
		}	
		
	} /*loop sobre as iterações*/


	/* Salvar os parâmetros otimizados no arquivo 'param' */
	otm=sf_floatalloc(5);
	otm[0] = otrnip;
	otm[1] = otbeta;
	otm[2] = otsemb;
	otm[3] = c0;
	otm[4] = temp0;

	/* Mostre os parâmetros otimizados ao usuário antes de salvar */
	sf_warning("Parâmetros otimizados:\n RNIP=%f, BETA=%f, SEMB=%f",otrnip,otbeta,otsemb);

	/* eixo = sf_maxa(n,o,d)*/
	ax = sf_maxa(5, 0, 1);
	ay = sf_maxa(1, 0, 1);
	az = sf_maxa(1, 0, 1);

	/* sf_oaxa(arquivo, eixo, índice do eixo) */
	sf_oaxa(out,ax,1);
	sf_oaxa(out,ay,2);
	sf_oaxa(out,az,3);
	sf_floatwrite(otm,5,out);

	exit(0);
}
