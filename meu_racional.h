#ifndef MEURACIONAL_H
#define MEURACIONAL_H


#include "numero.h"

struct MeuRacional_Interface_st;

struct MeuRacional_st {

    struct Numero_st super;

    struct MeuRacional_Interface_st const * Metodo;

    long int * Valor;

};

typedef struct MeuRacional_st *MeuRacional_pt;
typedef struct MeuRacional_st MeuRacional_t;

struct MeuRacional_Interface_st{
    MeuRacional_pt (*copia)	(MeuRacional_t const * const me);

    MeuRacional_pt (*atribui)	(MeuRacional_t const * const  me,
							 MeuRacional_t       * const  outro);

   MeuRacional_pt (*soma)	(MeuRacional_t const * const  me,
							 MeuRacional_t const * const  outro,
							 MeuRacional_t       * const res);

    MeuRacional_pt (*subt)	(MeuRacional_t const * const  me,
							 MeuRacional_t const * const  outro,
							 MeuRacional_t       * const res);

    MeuRacional_pt (*mult)	(MeuRacional_t const * const  me,
							 MeuRacional_t const * const  outro,
							MeuRacional_t        * const res);

    MeuRacional_pt (*divd)	(MeuRacional_t const * const  me,
							 MeuRacional_t const * const  outro,
							 MeuRacional_t       * const res);

    MeuRacional_pt (*ac_soma)	(MeuRacional_t       * const  me,
							    MeuRacional_t const * const  outro);

    MeuRacional_pt (*ac_subt)	(MeuRacional_t       * const  me,
							     MeuRacional_t const * const outro);

    MeuRacional_pt (*ac_mult)	(MeuRacional_t       * const  me,
							     MeuRacional_t const * const outro);

    MeuRacional_pt (*ac_divd)	(MeuRacional_t        * const  me,
							     MeuRacional_t const * const outro);

    int			(*compara)	(MeuRacional_t const * const  me,
							 MeuRacional_t const * const  outro);

    char *      (*imprime)  (MeuRacional_t const * const  me);

    void        (*destroi)  (MeuRacional_t       *        me);
    /*------------------------------------------------------*/
    void       (*get     ) (MeuRacional_t  const * const me,
							long int               * ValorNumerador,
	                        long int 				 * ValorDenominador);

	void   	   (*set     ) (MeuRacional_t        * const me,
	                          long int            ValorNumerador,
	                          long int		     ValorDenominador);

	long int      (*getNumerador ) (MeuRacional_t  const * const me);

	void   	   (*setNumerador ) (MeuRacional_t        * const me,
	                          long int             ValorNumerador);


	long int       (*getDenominador ) (MeuRacional_t  const * const me);

	void   	   (*setDenominador ) (MeuRacional_t        * const me,
	                          long int           valorDenominador);

    void (*reduz_racional) (MeuRacional_t * const me, MeuRacional_t * const outro);

	long double (*modulo) (MeuRacional_t const * const me);                               
};

typedef struct MeuRacional_Interface_st *MeuRacional_Interface_pt;
/* constroi um racional      */
MeuRacional_pt Racional_Constroi (MeuRacional_pt me, long int ValorNumerador, long int ValorDenominador);

#endif
