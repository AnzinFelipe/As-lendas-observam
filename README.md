# Como experienciar a noite no Recife Antigo

## Windows
```
Instale a biblioteca raylib em
https://www.raylib.com

Instale também a pasta raylib-
5.0_win64_mingw-w64 

(Pode diferenciar de computador para
computador)

Descompacte e coloque ela dentro da pasta
raylib no disco local

Instale o make usando choco install make
dentro do Windows Powershell

Baixar https://curl.se/windows/ para Windows 64 -> extrair e deixar a pasta do arquivo com nome "curl" no diretório C:/

Criar uma pasta e dar git clone https://github.com/AnzinFelipe/As-lendas-observam.git

Entrar dentro da pasta com vscode e usar o comando: copy C:\curl\bin\libcurl-x64.dll C:\NOME-DA-PASTA\As-lendas-observam\

make run

Para usar da funcionalidade IA, você vai precisar criar um arquivo "groq.key" na pasta principal do jogo e colocar uma chave do groq IA
```

## Linux

```
Comece entrando no terminal de comandos do Linux e rode esses comandos em ordem

sudo apt install build-essential git

sudo apt update

sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev  libglu1-mesa-dev


Para instalar a raylib e configurá-la:

git clone raylib

cd raylib/src

make PLATFORM=PLATFORM_DESKTOP 

sudo make install 

Após isso, clone o projeto: git clone https://github.com/AnzinFelipe/As-lendas-observam.git

Também baixe: sudo apt install libcurl4-openssl-dev

Para usar da funcionalidade IA, você vai precisar criar um arquivo "groq.key" na pasta principal do jogo e colocar uma chave do groq IA

Após isso de make run

```