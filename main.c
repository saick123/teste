/* main.c */
/* teste do tipo de dados meudouble */
#include <stdio.h>
#include "meu_complexo.h"
#include "meu_racional.h"
int main ()
{

/** ------ PARTE ORIGINAL DO PROGRAMA: MEU_COMPLEXO ------*/
	MeuComplexo_pt ptC1=NULL, ptC2=NULL, ptC3=NULL;

	/*veja que aqui neste ponto faço chamadas de algumas funções
	 * através dos ponteiros que estão na tabela vtbl (ponteiro "metodo")
	 * da superclasse "Numero". Como as funções desta tabela esperam
	 * receber "ponteiro para Numero_t", preciso converter o ptX1 para
	 * Numero_pt e depois converter o resultado "de volta" para
	 * MeuDouble_pt */
   MeuRacional_pt ptR1=NULL, ptR2 = NULL, ptR3= NULL;

	ptC1 = Complexo_constroi (ptC1, 10.0, 20.0);

   ptR1 = Racional_Constroi (ptR1, 10, -20 );

	ptC2 = ptC1->Metodo->copia (ptC1);

   ptR2 = ptR1->Metodo->copia(ptR1);

	printf ("Os dois numeros sao %s %s \n",
				ptC1->Metodo->imprime (ptC1),
				ptC2->Metodo->imprime (ptC2));

   printf ("Os dois numeros sao %s %s \n",
				ptR1->Metodo->imprime (ptR1),
				ptR2->Metodo->imprime (ptR2));

    ptC3 = Complexo_constroi (ptC3, 0.0, 0.0);
    ptC3 = ptC2->Metodo->atribui (ptC2, ptC3);
    printf ("ptC3 recebeu o valor de Y2 = %s \n",
				ptC3->Metodo->imprime (ptC3));

   ptR3 = Racional_Constroi(ptR3, 0, 1);
   ptR3 = ptR2->Metodo->atribui(ptR2, ptR3);
   printf ("ptR3 recebeu o valor de R2 = %s \n",
				ptR3->Metodo->imprime (ptR3));


    ptC3 = ptC1->Metodo->soma(ptC1, ptC2, ptC3);
    printf ("ptC3 recebeu a soma de Y1 com Y2 = %s \n",
				ptC3->Metodo->imprime (ptC3));

   ptR3 = ptR1->Metodo->soma(ptR1, ptR2, ptR3);
   printf ("ptR3 recebeu a soma de R1 com R2 = %s \n",
				ptR3->Metodo->imprime (ptR3));

    ptC3 = ptC3->Metodo->subt(ptC3, ptC2, ptC3);
    printf ("ptC3 recebeu a subtracao de Y3 com Y2 = %s \n",
				ptC3->Metodo->imprime (ptC3));

   ptR3 = ptR3->Metodo->subt(ptR3, ptR2, ptR3);
   printf ("ptR3 recebeu a subtracao de R3 com R2 = %s \n",
				ptR3->Metodo->imprime (ptR3));

    ptC3 = ptC1->Metodo->mult(ptC1, ptC2, ptC3);
    printf ("ptC3 recebeu a multiplicacao de Y1 com Y2 = %s \n",
                 ptC3->Metodo->imprime (ptC3));

   ptR3 =ptR1->Metodo->mult(ptR1,ptR2,ptR3);
   printf ("ptR3 recebeu a multiplicacao de R1 com R2 = %s \n",
                 ptR3->Metodo->imprime (ptR3));


    ptC3 = ptC1->Metodo->divd(ptC1, ptC2, ptC3);
    printf ("ptC3 recebeu a divisão de Y1 com Y2 = %s \n",
                 ptC3->Metodo->imprime (ptC3));

   ptR3 = ptR1->Metodo->divd(ptR1, ptR2, ptR3);
   printf ("ptR3 recebeu a divisão de R1 com R2 = %s \n",
                 ptR3->Metodo->imprime (ptR3));


    ptC3 = ptC1->Metodo->ac_soma(ptC3, ptC2);
    printf ("ptC3 foi somado com Y2 = %s \n",
				ptC3->Metodo->imprime (ptC3));

    ptR3 = ptR1->Metodo->ac_soma(ptR3, ptR2);
    printf ("ptR3 foi somado com R2 = %s \n",
				ptR3->Metodo->imprime (ptR3));  

    ptC3 = ptC3->Metodo->ac_subt(ptC3, ptC2);
    printf ("ptC3 foi subtraido de Y2 = %s \n",
				ptC3->Metodo->imprime (ptC3));
   
   ptR3 = ptR3->Metodo->ac_subt(ptR3, ptR2);
    printf ("ptR3 foi subtraido de R2 = %s \n",
				ptR3->Metodo->imprime (ptR3));

   ptC3 = ptC1->Metodo->ac_mult(ptC3, ptC2);
   printf ("ptC3 foi multiplicado por Y2 = %s \n",
                 ptC3->Metodo->imprime (ptC3));

   ptR3 = ptR1->Metodo->ac_mult(ptR3, ptR2);
   printf ("ptR3 foi multiplicado por R2 = %s \n",
   ptR3->Metodo->imprime (ptR3));

    ptC3 = ptC1->Metodo->ac_divd(ptC3, ptC2);
    printf ("ptC3 foi dividido por Y2 = %s \n",
                 ptC3->Metodo->imprime (ptC3));

   ptR3 = ptR1->Metodo->ac_divd(ptR3, ptR2);
   printf ("ptR3 foi dividido por R2 = %s \n",
                 ptR3->Metodo->imprime (ptR3));


    if (ptC1->Metodo->compara(ptC1,ptC2)==0)
    {
       printf ("Y1 eh igual a Y2 = %s\n", ptC1->Metodo->imprime(ptC1));
    }
    if (ptC1->Metodo->compara(ptC2,ptC3)>0)
    {
       printf ("Y2 eh maior que Y3 \n");
    }
    if (ptC1->Metodo->compara(ptC2,ptC3)<0)
    {
       printf ("Y2 eh menor que Y3 \n");
    }

   if (ptR1->Metodo->compara(ptR1,ptR2)==0)
    {
       printf ("R1 eh igual a R2 = %s\n", ptR1->Metodo->imprime(ptR1));
    }
    if (ptR1->Metodo->compara(ptR2,ptR3) == 1)
    {
       printf ("R2 eh maior que R3 \n");
    }
    if (ptR1->Metodo->compara(ptR2,ptR3) == 2)
    {
       printf ("R2 eh menor que R3 \n");
    }

      printf("modulo de R3:%Lf\n modulo de R2:%Lf\nModulo de R1:%Lf", ptR3->Metodo->modulo(ptR3), ptR3->Metodo->modulo(ptR2), ptR3->Metodo->modulo(ptR1));
     

      ptR3->Metodo->destroi(ptR3);
      ptR1->Metodo->destroi(ptR1);
      ptR2->Metodo->destroi(ptR2);
	   ptC1->Metodo->destroi (ptC1);
	   ptC2->Metodo->destroi (ptC2);
      ptC3->Metodo->destroi (ptC3);
	return (0);
}








