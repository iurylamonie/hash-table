# Autores

Iury Lamonie
& 
Leonardo Igor

# 1. Introdução:

Este projeto contém a implementação da estrutura de dados tabela de dispersão em C++.

# 2. O programa de testes:

Foi utilizado uma copia do arquivo de testes(Google Test) disponibilizado no SIGAA.

## Compilando o arquivo de testes:

Crie uma pata build no mesmo nível da pasta hash-table ```mkdir build```; 
Entre na pasta build ```cd build``` e dentro da build use o comando ```cmake -G "Unix Makefiles" ../hash-table```.
Utilize o comando ```make``` e execute o aplicativo de testes com ```./run_tests```.

# 2. Makefile/Compiling:

Verifica se o setup está configurado, caso contrario, fará um novo setup chamando "make dir" e compila. Ele chama "make all" internamente.

```
make
```

Você também pode passar argumentos para o compilador. Como o exemplo abaixo:
```
make args="-D something=212"
```
Para ativar o modo debug, faça:

```
make args="-D DEBUG"
```

Fará tods os diretórios de trabalho. Você pode fazer isso manualmente ou automaticamente se você usar "make".
```
make dir
```

Limpa todo o diretorio de trabalho, irá apagar todos os arquivos contidos em bin e docs
```
make clean
```

Fará a documentação para o projeto atual.
```
make doxy
```

Irá chamar "make clear" e "make dir"
```
make fresh
```