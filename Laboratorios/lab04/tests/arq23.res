A��o: # Teste 23
A��o: a A 2 3.0           A <- 3x^2 
A��o: a B 1 2.0           B <- 2x
A��o: r C AB*~            C <- -(A*B)
A��o: i C                 imprime C
----> ( 3, -6.0) 
A��o: r D CC~+            D <- C +(-C)
A��o: i D                 imprime D
----> Polin�mio nulo
A��o: r E AB+C+D*         E <- (A+B+C)*D
A��o: i E 
----> Polin�mio nulo
A��o: l A                 libera A
A��o: l B                 libera B 
A��o: l C                 libera C
A��o: l D                 libera D
A��o: l E                 libera E
A��o: x                   termina 
Processamento terminado
