A��o: # Teste 33
A��o: C 1          v[1] := 0
A��o: T 1  1 -1.0   acrescenta (1,-1.0) a v[1]
A��o: T 1  4  4.0   acrescenta (4,4.0) a v[1]
A��o: T 1  3  6.0   acrescenta (3,6.0) a v[1]
A��o: T 1 10  1.0   acrescenta (10,1.0) a v[1]
A��o: T 1  7 -8.0   acrescenta (7,-8.0) a v[1]
A��o: I 1          imprime v[1]     
----> ( 1, -1.0) ( 3,  6.0) ( 4,  4.0) ( 7, -8.0) (10,  1.0) 
A��o: S 2 1 1      v[2] := v[1]+v[1]
A��o: I 2          imprime v[1]     
----> ( 1, -2.0) ( 3, 12.0) ( 4,  8.0) ( 7,-16.0) (10,  2.0) 
A��o: L 1          libera v[1]
A��o: L 2          libera v[2]
A��o: X            termina
Processamento terminado
