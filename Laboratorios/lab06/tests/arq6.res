# Teste com express�es inv�lidas
# Operando esperado
Infixa: +
Erro:    ^
        Operando esperado nesta posi��o.


Infixa: *
Erro:   ^
        Operando esperado nesta posi��o.


Infixa: (
Erro:    ^
        Operando esperado nesta posi��o.


Infixa: )
Erro:   ^
        Operando esperado nesta posi��o.


Infixa: a-
Erro:     ^
        Operando esperado nesta posi��o.


Infixa:   a  -
Erro:         ^
        Operando esperado nesta posi��o.


Infixa: a--b
Erro:     ^
        Operando esperado nesta posi��o.


Infixa: a - - b
Erro:       ^
        Operando esperado nesta posi��o.


Infixa: a*b/  
Erro:         ^
        Operando esperado nesta posi��o.


Infixa:  a * b/
Erro:          ^
        Operando esperado nesta posi��o.


Infixa: a*b/((c+d)-                
Erro:                              ^
        Operando esperado nesta posi��o.


Infixa: ()
Erro:    ^
        Operando esperado nesta posi��o.


Infixa: a+( )
Erro:       ^
        Operando esperado nesta posi��o.


Infixa: ((((a-b)*c)^d^e)-)
Erro:                    ^
        Operando esperado nesta posi��o.


# Operador esperado
Infixa: ab
Erro:    ^
        Operador esperado nesta posi��o.


Infixa: a      b
Erro:          ^
        Operador esperado nesta posi��o.


Infixa: a*b+c*d^e/f-gh^i*j
Erro:                ^
        Operador esperado nesta posi��o.


Infixa: a+b)+c
Erro:      ^
        Operador esperado nesta posi��o.


Infixa: ((a-b)))+c
Erro:          ^
        Operador esperado nesta posi��o.


# Fecha par�nteses esperado
Infixa: (a-b
Erro:       ^
        Fecha par�ntese esperado nesta posi��o.


Infixa: (((a-b))
Erro:           ^
        Fecha par�ntese esperado nesta posi��o.


Infixa: ((a-b)*(b-c)
Erro:               ^
        Fecha par�ntese esperado nesta posi��o.


Infixa: a*b*c-(e-f
Erro:             ^
        Fecha par�ntese esperado nesta posi��o.


# Caracteres inv�lidos
Infixa: !
Erro:   ^
        Caractere inv�lido nesta posi��o.


Infixa: a;
Erro:    ^
        Caractere inv�lido nesta posi��o.


Infixa: a - b @
Erro:         ^
        Caractere inv�lido nesta posi��o.


Infixa: a%c
Erro:    ^
        Caractere inv�lido nesta posi��o.


Processamento terminado
