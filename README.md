# Projeto de Compiladores

Este projeto consiste no desenvolvimento de um compilador para a linguagem Juc, que é um subconjunto da linguagem Java de acordo com a especificação Java SE 9 (disponível na página https://docs.oracle.com/javase/specs/jls/se9/html/index.html).
Na linguagem Juc é possível usar variáveis e literais dos tipos boolean, int e double (estes dois últimos com sinal). É também possível usar literais do tipo String, apenas para efeito de escrita no stdout. A linguagem Juc inclui expressões aritméticas e lógicas, instruções de atribuição, operadores relacionais e instruções de controlo (while e if-else). Inclui também métodos estáticos com os tipos de dados já referidos e ainda o tipo especial String[], sendo a passagem de parâmetros sempre feita por valor e podendo ou não ter valor de retorno. A ausência de valor de retorno é identificada pela palavra-chave void.
Os programas da linguagem Juc são compostos por uma única classe (principal) contendo métodos e atributos, todos eles estáticos. O método main(...) invocado no início de cada programa pode receber parâmetros, que deverão ser literais inteiros, através da linha de comandos. Supondo que o parâmetro formal do método main(...) é args, os respetivos valores podem ser obtidos através do método pré-definido Integer.parseInt(args[...]) e a expressão args.length dá o número de parâmetros. O método pré-definido System.out.print(...) permite escrever na consola valores lógicos, inteiros, reais e strings.
O significado de um programa na linguagem Juc será o mesmo que na linguagem Java, assumindo a pré-definição dos métodos Integer.parseInt(...) e System.out.print(...), bem como da construção .length. Por fim, são aceites comentários nas formas /* ... */ e // ... que deverão ser ignorados.