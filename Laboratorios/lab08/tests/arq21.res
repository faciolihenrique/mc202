A��o: # Testes sem rota��o para a fun��o remove
A��o: # Remove a raiz 
A��o: i 036462 Jo�o Moreira
A��o: r 036462
Ra 036462 removido.
A��o: n
N�mero de n�s na base de dados: 0.
A��o: d

�rvore vazia

A��o: l
A��o: # Remove raiz contendo apenas o filho direito
A��o: i 036462 Jo�o Moreira
A��o: i 661116 Jos� Neves
A��o: r 036462
Ra 036462 removido.
A��o: p
661116 Jos� Neves
A��o: d

 661116

A��o: l
A��o: # Remove raiz contendo apenas o filho esquerdo
A��o: i 661116 Jos� Neves
A��o: i 036462 Jo�o Moreira
A��o: r 661116
Ra 661116 removido.
A��o: p
036462 Jo�o Moreira
A��o: d

  36462

A��o: l
A��o: # Remove folha da sub-�rvore esquerda
A��o: i 013774 M�rio Bragan�a
A��o: i 032875 Jos� Souza
A��o: i 006924 Ricardo Silva
A��o: r 006924
Ra 006924 removido.
A��o: p  
013774 M�rio Bragan�a
032875 Jos� Souza
A��o: d

   / 32875
  13774

A��o: l
A��o: # Remove folha da sub-�rvore direita
A��o: i 013774 M�rio Bragan�a
A��o: i 032875 Jos� Souza
A��o: i 006924 Ricardo Silva
A��o: r 032875
Ra 032875 removido.
A��o: p  
006924 Ricardo Silva
013774 M�rio Bragan�a
A��o: d

  13774
   \  6924

A��o: l
A��o: # Remove n� contendo apenas o filho esquerdo
A��o: i 031780 Elaine Ferreira
A��o: i 036206 Carlos Nogueira
A��o: i 025680 Renato de Souza
A��o: i 014098 Pedro Silveira
A��o: r 025680
Ra 025680 removido.
A��o: p
014098 Pedro Silveira
031780 Elaine Ferreira
036206 Carlos Nogueira
A��o: a
Altura da base de dados: 2.
A��o: d

   / 36206
  31780
   \ 14098

A��o: l
A��o: # Remove folha 
A��o: i 031780 Elaine Ferreira
A��o: i 036206 Carlos Nogueira
A��o: i 025680 Renato de Souza
A��o: i 014098 Pedro Silveira
A��o: r 014098
Ra 014098 removido.
A��o: p
025680 Renato de Souza
031780 Elaine Ferreira
036206 Carlos Nogueira
A��o: a
Altura da base de dados: 2.
A��o: d

   / 36206
  31780
   \ 25680

A��o: l
A��o: # Remove n� contendo apenas o filho direito
A��o: i 031780 Elaine Ferreira
A��o: i 036206 Carlos Nogueira
A��o: i 014098 Pedro Silveira
A��o: i 025680 Renato de Souza
A��o: r 014098
Ra 014098 removido.
A��o: p
025680 Renato de Souza
031780 Elaine Ferreira
036206 Carlos Nogueira
A��o: a
Altura da base de dados: 2.
A��o: d

   / 36206
  31780
   \ 25680

A��o: l
A��o: # Remove folha 
A��o: i 031780 Elaine Ferreira
A��o: i 036206 Carlos Nogueira
A��o: i 014098 Pedro Silveira
A��o: i 025680 Renato de Souza
A��o: r 025680
Ra 025680 removido.
A��o: # Testa remo��o de elemento ausente
A��o: r 021470
Ra 021470 n�o encontrado na base de dados.
A��o: p
014098 Pedro Silveira
031780 Elaine Ferreira
036206 Carlos Nogueira
A��o: a
Altura da base de dados: 2.
A��o: d

   / 36206
  31780
   \ 14098

A��o: l
A��o: x
Processamento terminado
