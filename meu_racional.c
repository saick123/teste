#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "meu_racional.h"

static  Numero_pt copia_ (Numero_t const * const  me);

static  Numero_pt atribui_ (Numero_t const * const  me,
							         Numero_t       * const  outro) ;

static  Numero_pt soma_  (Numero_t const * const  me,
								   Numero_t const * const  outro,
							       Numero_t       * const  res);

static  Numero_pt subt_  (	Numero_t const * const  me,
									Numero_t const * const  outro,
									Numero_t       * const  res);

static  Numero_pt mult_  ( Numero_t const * const  me,
									Numero_t const * const  outro,
									Numero_t       * const  res);

static  Numero_pt divd_  ( Numero_t const * const  me,
									Numero_t const * const  outro,
									Numero_t       * const  res);

static  Numero_pt ac_soma_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  Numero_pt ac_subt_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  Numero_pt ac_mult_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  Numero_pt ac_divd_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  int	compara_ 	(Numero_t const * const  me,
							 Numero_t const * const  outro);

static  char * imprime_  (Numero_t const * const  me);

static  void destroi_ (Numero_t   *   me);

/* implementação para racional */

static MeuRacional_pt Copia_ (MeuRacional_t const * const me);

static MeuRacional_pt Atribui_ (MeuRacional_t const * const me, MeuRacional_t * const outro);

static MeuRacional_pt Soma_ (MeuRacional_t const * const me, MeuRacional_t const * const outro,
                                MeuRacional_t * const res);

static MeuRacional_pt Subt_ (MeuRacional_t const * const me, MeuRacional_t const * const outro,
                                MeuRacional_t * const res);

static MeuRacional_pt Mult_ (MeuRacional_t const * const me, MeuRacional_t const * const outro,
                                MeuRacional_t * const res);

static MeuRacional_pt Divd_ (MeuRacional_t const * const me, MeuRacional_t const * const outro,
                                MeuRacional_t * const res);

static MeuRacional_pt Ac_Soma_ (MeuRacional_t * const me, 
                                MeuRacional_t const * const outro);

static MeuRacional_pt Ac_Subt_ (MeuRacional_t * const me, 
                                MeuRacional_t const * const outro);
static MeuRacional_pt Ac_Mult_ (MeuRacional_t * const me, 
                                MeuRacional_t const * const outro);

static MeuRacional_pt Ac_Divd_ (MeuRacional_t * const me, 
                                MeuRacional_t const * const outro);

static  int	Compara_ 	    (MeuRacional_t const * const  me,
							 MeuRacional_t const * const  outro);

static  char *      Imprime_  (MeuRacional_t const * const  me);

static  void        Destroi_ (MeuRacional_t  *   me);

static void       Get_      (MeuRacional_t  const * const me,
							long int               * ValorNumerador,
	                        long int 				 * ValorDenominador);

static void   	   Set_      (MeuRacional_t        * const me,
	                          long int            ValorNumerador,
	                          long int		     ValorDenominador);

static long int      GetNumerador_  (MeuRacional_t  const * const me);

static void   	   SetNumerador_  (MeuRacional_t        * const me,
	                          long int             ValorNumerador);

static long int       GetDenominador_ (MeuRacional_t  const * const me);

static void   	   SetDenominador_ (MeuRacional_t        * const me,
	                          long int           valorDenominador);

static void Reduz_Racional_ (MeuRacional_t * const me, MeuRacional_t * const outro);

static long double Modulo_ (MeuRacional_t const * const me);     

/*Retorna (void *)NULL se o denominador for 0 (inválido!) */
MeuRacional_pt Racional_Constroi(MeuRacional_pt me, long int ValorNumerador, long int ValorDenominador){

    if(ValorDenominador==0){
       
        printf("não há numero racional com denominador igual a 0, crie um numero válido!");
        return (void*) NULL;

    }

    static struct NumeroVtbl const vtbl = {
        &copia_,
        &atribui_,
        &soma_,
        &subt_,
        &mult_,
        &divd_,
        &ac_soma_,
        &ac_subt_,
        &ac_mult_,
        &ac_divd_,
        &compara_,
        &imprime_,
        &destroi_
    };

    me = (MeuRacional_pt) Num_constroi ((Numero_pt) me);
    me->super.metodo = &vtbl;

    static struct MeuRacional_Interface_st const interface ={
        &Copia_,
        &Atribui_,
        &Soma_,
        &Subt_,
        &Mult_,
        &Divd_,
        &Ac_Soma_,
        &Ac_Subt_,
        &Ac_Mult_,
        &Ac_Divd_,
        &Compara_,
        &Imprime_,
        &Destroi_,
        &Get_,
        &Set_,
        &GetNumerador_,
        &SetNumerador_,
        &GetDenominador_,
        &SetDenominador_,
        &Reduz_Racional_,
        &Modulo_,
    };

     me->Metodo = &interface;   
    
    me->Valor = (long int *) malloc (sizeof(long int )*2);
    if(me->Valor == NULL){
        printf("não foi possivel alocar 'valor'");
        exit(1);
    }

    me->Valor[0]= ValorNumerador;
    me->Valor[1]= ValorDenominador;

    Reduz_Racional_(me,me); // reduz antes de ser retornado

    return me;
}

static inline void Get_ (MeuRacional_t const * const me, long int * ValorNumerador, 
                            long int * ValorDenominador ){
*ValorNumerador = me->Valor[0];
*ValorDenominador = me->Valor[1];
}

static inline void Set_ (MeuRacional_t * const me, long int ValorNumerador, long int ValorDenominador){

    me->Valor[0] = ValorNumerador;
    me->Valor[1] = ValorDenominador;

}


static inline long int GetNumerador_ (MeuRacional_t const * const me){

    return (me->Valor[0]);

}

static inline  void   	   SetNumerador_  (MeuRacional_t        * const me, long int ValorNumerador){

 me->Valor[0] = ValorNumerador;

}

static long int       GetDenominador_ (MeuRacional_t  const * const me){
    return (me->Valor[1]);
}           

static void   	   SetDenominador_ (MeuRacional_t        * const me, long int valorDenominador){

    me->Valor[1] = valorDenominador;
}

static void Reduz_Racional_ (MeuRacional_t * const me, MeuRacional_t * const outro){
    
    int sinal;
	if ((GetNumerador_(me) * GetDenominador_(me)) < 0) 
	{ sinal = -1 ;}
	else
	{sinal = + 1;}
	
	long int a, b, rem;
	
	if ((GetNumerador_(me) > GetDenominador_(me)))
	{	a =  labs (GetNumerador_(me));
		b =  labs (GetDenominador_(me)); 
	}
	else
	{
		a = labs(GetDenominador_(me));
		b = labs(GetNumerador_(me));
	}
	while (b > 0)
	{
		rem = b;
		b = a % b;
		a = rem;
	}
	SetNumerador_(outro, labs(GetNumerador_(me))  / a * sinal );
    SetDenominador_(outro, labs(GetDenominador_(me)) / a );
}

static long double Modulo_ (MeuRacional_t const * const me){
    
    if(GetNumerador_(me) >=0){
        return ((long double)GetNumerador_(me)/GetDenominador_(me));
    }else{
        return (-1)*((long double)GetNumerador_(me)/GetDenominador_(me));
    }
}


static inline MeuRacional_pt Copia_ (MeuRacional_t const * const me){

    return ((MeuRacional_pt) copia_ ((Numero_pt) me));

}

static  Numero_pt copia_ (Numero_t const * const  me) {
    assert(me!= NULL);
    Numero_pt outro = NULL;
    outro = (Numero_pt) Racional_Constroi ((MeuRacional_pt) outro , 
                GetNumerador_((MeuRacional_pt) me), GetDenominador_((MeuRacional_pt) me));
    return (outro);
}

static inline MeuRacional_pt Atribui_ (MeuRacional_t const * const me, MeuRacional_t * const outro){

    return ((MeuRacional_pt) atribui_ ((Numero_pt) me, (Numero_pt) outro));
}

static  Numero_pt atribui_ (Numero_t const * const  me, Numero_t  * const  outro){

    Set_((MeuRacional_pt) outro, GetNumerador_((MeuRacional_pt) me), GetDenominador_((MeuRacional_pt) me));
    return ((Numero_pt) outro);
}   

static inline MeuRacional_pt Soma_ (MeuRacional_t const * const me, MeuRacional_t const * const outro,
                                MeuRacional_t * const res){
return ((MeuRacional_pt) soma_ ((Numero_pt) me, (Numero_pt) outro, (Numero_pt) res));

}



static  Numero_pt soma_  (Numero_t const * const  me, Numero_t const * const  outro, Numero_t * const  res){

    MeuRacional_pt temp = NULL;

    temp = Racional_Constroi(temp, 0,1);

    SetNumerador_(temp,GetNumerador_((MeuRacional_pt) me)*GetDenominador_((MeuRacional_pt)outro) + GetNumerador_((MeuRacional_pt)outro)*GetDenominador_((MeuRacional_pt)me));

    SetDenominador_(temp,GetDenominador_((MeuRacional_pt) me)*GetDenominador_((MeuRacional_pt) outro) );

    Reduz_Racional_(temp, (MeuRacional_pt) res);

    if(GetDenominador_((MeuRacional_pt) res) < 0){
        Set_((MeuRacional_pt) res, GetNumerador_((MeuRacional_pt)res)*(-1), GetDenominador_((MeuRacional_pt)res)*(-1));
    }

    Destroi_(temp);

    return ((Numero_pt) res);
}


static inline MeuRacional_pt Subt_ (MeuRacional_t const * const me, MeuRacional_t const * const outro,
                                MeuRacional_t * const res){
return ((MeuRacional_pt) subt_((Numero_pt) me, (Numero_pt) outro, (Numero_pt) res));
}

static  Numero_pt subt_  (	Numero_t const * const  me,Numero_t const * const  outro,Numero_t * const  res){

    MeuRacional_pt temp = NULL;

    temp = Racional_Constroi(temp, 0,1);

    SetNumerador_(temp,GetNumerador_((MeuRacional_pt) me)*GetDenominador_((MeuRacional_pt)outro) - GetNumerador_((MeuRacional_pt)outro)*GetDenominador_((MeuRacional_pt)me));

    SetDenominador_(temp,GetDenominador_((MeuRacional_pt) me)*GetDenominador_((MeuRacional_pt) outro) );

    Reduz_Racional_(temp, (MeuRacional_pt) res);

    if(GetDenominador_((MeuRacional_pt) res) < 0){
        Set_((MeuRacional_pt) res, GetNumerador_((MeuRacional_pt)res)*(-1), GetDenominador_((MeuRacional_pt)res)*(-1));
    }

    Destroi_(temp);

    return ((Numero_pt) res);

}


static inline MeuRacional_pt Mult_ (MeuRacional_t const * const me, MeuRacional_t const * const outro, MeuRacional_t * const res){

    return ((MeuRacional_pt) mult_((Numero_pt)me, (Numero_pt) outro, (Numero_pt) res));

}

static  Numero_pt mult_  ( Numero_t const * const  me, Numero_t const * const  outro, Numero_t * const  res){

    Set_((MeuRacional_pt) res, GetNumerador_((MeuRacional_pt)me)*GetNumerador_((MeuRacional_pt)outro),
    GetDenominador_((MeuRacional_pt)me)*GetDenominador_((MeuRacional_pt) outro));

    Reduz_Racional_((MeuRacional_pt) res,(MeuRacional_pt) res);

    if(GetDenominador_((MeuRacional_pt) res) < 0){
        Set_((MeuRacional_pt) res, GetNumerador_((MeuRacional_pt)res)*(-1), GetDenominador_((MeuRacional_pt)res)*(-1));
    }
    
    return ((Numero_pt) res);
}


static inline  MeuRacional_pt Divd_ (MeuRacional_t const * const me, MeuRacional_t const * const outro,
                                MeuRacional_t * const res){
    if(GetNumerador_(outro) ==0 ){
        printf("erro na funcao 'Divd', divisao por zero detectada");
        return (void*) NULL;
    }                                
    return ((MeuRacional_pt) divd_((Numero_pt)me, (Numero_pt) outro, (Numero_pt) res));
}

 static  Numero_pt divd_  ( Numero_t const * const  me, Numero_t const * const  outro, Numero_t * const  res){

     Set_((MeuRacional_pt) res, GetNumerador_((MeuRacional_pt)me)*GetDenominador_((MeuRacional_pt)outro), 
                            GetDenominador_((MeuRacional_pt)me)*GetNumerador_((MeuRacional_pt)outro)); 
        
        Reduz_Racional_ ((MeuRacional_pt) res,(MeuRacional_pt) res);
        
        if(GetDenominador_((MeuRacional_pt) res) < 0){
            Set_((MeuRacional_pt) res, GetNumerador_((MeuRacional_pt)res)*(-1), 
                                        GetDenominador_((MeuRacional_pt)res)*(-1));
        }
    return ((Numero_pt) res);
}
									
static inline MeuRacional_pt Ac_Soma_ (MeuRacional_t * const me,  MeuRacional_t const * const outro){

    return ((MeuRacional_pt) ac_soma_((Numero_pt) me, (Numero_pt) outro));

}

static  Numero_pt ac_soma_ (Numero_t * const  me,Numero_t const * const  outro){

     
    SetNumerador_((MeuRacional_pt) me,GetNumerador_((MeuRacional_pt) me)*GetDenominador_((MeuRacional_pt)outro) + GetNumerador_((MeuRacional_pt)outro)*GetDenominador_((MeuRacional_pt)me));

    SetDenominador_((MeuRacional_pt) me, GetDenominador_((MeuRacional_pt) me)*GetDenominador_((MeuRacional_pt) outro) );

    Reduz_Racional_((MeuRacional_pt) me, (MeuRacional_pt) me);

    if(GetDenominador_((MeuRacional_pt) me) < 0){
        Set_((MeuRacional_pt)me, GetNumerador_((MeuRacional_pt)me)*(-1), GetDenominador_((MeuRacional_pt)me)*(-1));
    }


    return ((Numero_pt) me);
									 
}                    


static inline MeuRacional_pt Ac_Subt_ (MeuRacional_t * const me,  MeuRacional_t const * const outro){

    return ((MeuRacional_pt) ac_subt_((Numero_pt)me, (Numero_pt) outro));

}


static  Numero_pt ac_subt_ (Numero_t * const  me, Numero_t const * const  outro){

    SetNumerador_((MeuRacional_pt) me,GetNumerador_((MeuRacional_pt) me)*GetDenominador_((MeuRacional_pt)outro) - GetNumerador_((MeuRacional_pt)outro)*GetDenominador_((MeuRacional_pt)me));

    SetDenominador_((MeuRacional_pt) me, GetDenominador_((MeuRacional_pt) me)*GetDenominador_((MeuRacional_pt) outro) );

    Reduz_Racional_((MeuRacional_pt) me,(MeuRacional_pt) me);

    if(GetDenominador_((MeuRacional_pt) me) < 0){
        Set_((MeuRacional_pt)me, GetNumerador_((MeuRacional_pt)me)*(-1), GetDenominador_((MeuRacional_pt)me)*(-1));
    }


    return ((Numero_pt) me);

}

static inline MeuRacional_pt Ac_Mult_ (MeuRacional_t * const me, MeuRacional_t const * const outro){
    return ((MeuRacional_pt) ac_mult_ ((Numero_pt)me, (Numero_pt) outro));

}

static  Numero_pt ac_mult_ (Numero_t       * const  me, Numero_t const * const  outro){

    Set_((MeuRacional_pt) me, GetNumerador_((MeuRacional_pt)me)*GetNumerador_((MeuRacional_pt)outro),
    GetDenominador_((MeuRacional_pt)me)*GetDenominador_((MeuRacional_pt) outro));

    Reduz_Racional_((MeuRacional_pt) me,(MeuRacional_pt) me);

    if(GetDenominador_((MeuRacional_pt) me) < 0){
        Set_((MeuRacional_pt) me, GetNumerador_((MeuRacional_pt)me)*(-1), GetDenominador_((MeuRacional_pt)me)*(-1));
    }
    
    return ((Numero_pt) me);

}
									
                                

                            
                                


static inline MeuRacional_pt Ac_Divd_ (MeuRacional_t * const me, MeuRacional_t const * const outro){

    return ((MeuRacional_pt) ac_divd_((Numero_pt) me , (Numero_pt) outro));
}

static  Numero_pt ac_divd_ (Numero_t       * const  me, Numero_t const * const  outro){

    Set_((MeuRacional_pt) me, GetNumerador_((MeuRacional_pt)me)*GetDenominador_((MeuRacional_pt)outro), 
                            GetDenominador_((MeuRacional_pt)me)*GetNumerador_((MeuRacional_pt)outro)); 
        
        Reduz_Racional_ ((MeuRacional_pt) me,(MeuRacional_pt) me);
        
        if(GetDenominador_((MeuRacional_pt) me) < 0){
            Set_((MeuRacional_pt) me, GetNumerador_((MeuRacional_pt) me)*(-1), 
                                        GetDenominador_((MeuRacional_pt) me)*(-1));
        }

    return ((Numero_pt) me);
}

/* retorna '0' para igual
   retorna '1' para 'me' > 'outro'
   retorna '2' para 'me' < 'outro'
   retorna '-1' para '**ERRO**'*/
static inline int	Compara_ (MeuRacional_t const * const  me, MeuRacional_t const * const  outro){

return (compara_((Numero_pt) me, (Numero_pt) outro));

}
    /*como critério de comparação, dividi os dois numeros, assim se a fraçaõ resultatante tiver o numerador maior
    que o denominador, significa q o resultado da divisao foi maior que 1, ou seja, o primeiro é maior q o segundo,
    se o deno foi igual ao numera, entao sao iguais, e se a fracao for menor que 1, o primeiro é menor */
static  int	compara_ 	(Numero_t const * const  me, Numero_t const * const  outro){

    if(GetNumerador_((MeuRacional_pt)me) <0 && GetNumerador_((MeuRacional_pt)outro) >=0){
        return 2;// me menor
    }
    if(GetNumerador_((MeuRacional_pt)me) >=0 && GetNumerador_((MeuRacional_pt)outro) <0){
        return 1;// me maior
    }

    MeuRacional_pt temp = NULL;
    temp = Racional_Constroi(temp, 0, 1);
    temp = Subt_((MeuRacional_pt) me, (MeuRacional_pt) outro,(MeuRacional_pt) temp);

    if(GetNumerador_(temp) == 0){
        Destroi_(temp);
        return 0; //iguais
    }

    if(GetNumerador_((MeuRacional_pt)me) >=0 && GetNumerador_((MeuRacional_pt) outro) >=0){
        if(GetNumerador_(temp) > 0 ){
            Destroi_(temp);
            return 1; //me maior
        } else{
            Destroi_(temp);
            return 2; //me menor
        }
    }

     if(GetNumerador_((MeuRacional_pt)me) <=0 && GetNumerador_((MeuRacional_pt) outro) <=0){
        if(GetNumerador_(temp) > 0 ){
            Destroi_(temp);
            return 2;//me maior
        } else{
            Destroi_(temp);
            return 1;// me menor
        }
    }


    Destroi_(temp);

    printf("erro na funcao comaparação");
    return -1;
}
							
static inline  char *      Imprime_  (MeuRacional_t const * const  me){ 
    return (imprime_((Numero_pt) me));
}

static  char * imprime_  (Numero_t const * const  me){

    static char buffer[50];
    if((GetNumerador_((MeuRacional_pt)me) == 0) || 
                (GetDenominador_((MeuRacional_pt)me) ==1 )){
       
        sprintf(buffer, "%li", GetNumerador_((MeuRacional_pt) me));

    }else{
        sprintf(buffer,"%li/%li", GetNumerador_((MeuRacional_pt)me), GetDenominador_((MeuRacional_pt) me));
    }
    return buffer;
}

static  inline void  Destroi_ (MeuRacional_t  *   me){
    destroi_((Numero_pt) me);
}

static void  destroi_ (Numero_t  *   me){
    free(((MeuRacional_pt) me)->Valor);

    free((Numero_t *) me);

}