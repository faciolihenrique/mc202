A��o: # Teste 31
A��o: C 1          v[1] := 0
A��o: T 1  1  1.0    acrescenta (1,1.0) a v[1]
A��o: I 1          imprime v[1]               
----> ( 1,  1.0) 
A��o: C 2          v[2] := 0                  
A��o: T 2  2  2.0    acrescenta (2,2.0) a v[2]  
A��o: I 2	     imprime v[2]               
----> ( 2,  2.0) 
A��o: S 3 1 2      v[3] := v[1]+v[2]
A��o: I 3          imprime v[3]    
----> ( 1,  1.0) ( 2,  2.0) 
A��o: L 1          libera v[1]
A��o: L 2          libera v[2]
A��o: L 3          libera v[3]
A��o: X            termina
Processamento terminado
