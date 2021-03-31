# Trabalho Prático 1
Nome: Aécio Fernandes Galiza Magalhães

Matrícula: 15/0115121

Disciplina: Software Básico

# Como executar o programa
Para a execução do programa, é necessário ambiente Ubuntu (foi desenvolvido no 16.04), g++ (foi desenvolvido na versão 5.4) e GNU Make 4.1 (para construir o projeto).

Como executar:

1) Extrair o arquivo entregue pelo Moodle;
2) Na raiz do arquivo (entrar na pasta "150115121_trab1_sb"), digite o comando 'make' para construir o projeto (montador + simulador);
3) Ainda na raiz, para MONTAR um arquivo exemplo basta utilizar

    $ ./montador <caminho/arquivo>

    #ex.: ./montador test_files_asm/ex1.asm

4) Assim, é gerado o arquivo .OBJ é gerado na mesma pasta do arquivo de entrada (por exemplo, ex1.obj dentro da pasta "test_files_asm"), caso NÃO hajam erros na montagem.
5) Ainda na raiz, para SIMULAR um arquivo exemplo basta utilizar

    $ ./simulador <caminho/arquivo>

    #ex.: ./simulador test_files_asm/ex1.obj (atente-se a extenção .OBJ)

6) Assim, o simulador mostrará na tela o valor de PC e ACC após cada instrução, bem como o valor de OUTPUT para instruções do tipo OUTPUT.
7) Também é gerado um arquivo de saida .OUT na mesma pasta do arquivo de entrada (por exemplo, ex1.out, dentro da pasta "test_files_asm"), com os OUTPUTS do programa, separados por um "ENTER".
