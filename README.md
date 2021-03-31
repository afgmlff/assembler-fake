#Trabalho Prático 1
Nome: Aécio Fernandes Galiza Magalhães
Matrícula: 15/0115121
Disciplina: CIC 116432 – Software Básico

#Como executar o programa
1) Extrair o arquivo entregue pelo Moodle;
2) Na raiz do arquivo, digite o comando 'make' para construir o projeto (montador + simulador);
3) Ainda na raiz, para MONTAR um arquivo exemplo basta utilizar 
   
    $ ./montador <caminho/arquivo>
    # ex.: ./montador test_files_asm/ex1.asm

4) Assim, é gerado o arquivo ex1.obj dentro da pasta "test_files_asm", caso NÃO hajam erros na montagem.
5) Ainda na raiz, para SIMULAR um arquivo exemplo basta utilizar

    $ ./simulador <caminho/arquivo>
    # ex.: ./simulador test_files_asm/ex1.obj (atente-se a extenção .OBJ)

6) Assim, o simulador mostrará na tela o valor de PC e ACC após cada instrução, bem como o valor de OUTPUT para instruções do tipo OUTPUT.
7) Também é gerado um arquivo de saida, ex1.out, dentro da pasta "test_files_asm".

