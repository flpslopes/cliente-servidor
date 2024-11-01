Cabeçalho do Trabalho
grupo 11 
--- observação: fiz tudo  apenas com a ajuda do Nicolas, desde o tinkard aos cliente- servidor , a unica coisa que fizeram foi jogar um codigo do chatgpt no grupo esperando que alguem integrasse tudo

Felipe Lopes Ferreira 
Matrícula: 202403458039

Yago Renato de Oliveira Prata Costa 
Matrícula: 202302232027

Nicolas Armani Marins
Matrícula: 202402312014


Hudson Mata Neves 
Matrícula: 202402852175






# Trabalho de Transmissão de TCP e UDP

## 1. Descrição do Projeto

Este projeto implementa um servidor e um cliente utilizando os protocolos TCP e UDP. O cliente envia um arquivo de texto para o servidor, que o recebe e salva em um local especificado.

## 2. Instruções para Compilação

### Requisitos

- Certifique-se de ter o MinGW instalado e configurado corretamente no seu sistema.
- O arquivo deve estar no mesmo diretório em que você está executando os comandos.

### Compilação dos Arquivos

Para compilar cada um dos arquivos, você deve usar o seguinte comando no terminal:

- Para compilar o servidor UDP:
  ```bash
  gcc -o servidor_udp servidor_udp.c -lws2_32


###Para compilar o cliente UDP:gcc -o cliente_udp cliente_udp.c -lws2_32

####Para compilar o servidor TCP:gcc -o servidor_tcp servidor_tcp.c -lws2_32

####Para compilar o cliente TCP:gcc -o cliente_tcp cliente_tcp.c -lws2_32

3. Instruções de Execução
Executando os Programas
Inicie o Servidor UDP:

Abra um terminal e navegue até o diretório onde o servidor_udp.exe está localizado.
Execute o comando:.\servidor_udp

Inicie o Cliente UDP:

Abra outro terminal e navegue até o diretório onde o cliente_udp.exe está localizado.
Execute o comando:
.\cliente_udp


Observações
Ordem de Execução: Sempre inicie o servidor antes de executar o cliente para garantir que o servidor esteja pronto para receber os dados.


4. Resultados Esperados
Servidor:

O servidor deve mostrar uma mensagem indicando que está esperando por mensagens, por exemplo:Servidor UDP esperando por mensagens na porta 8080...

Cliente:

Ao enviar o arquivo, você deve ver a mensagem:Arquivo enviado com sucesso.

###No Servidor:

Após o cliente enviar o arquivo, o servidor deve salvar o arquivo com o nome especificado (por exemplo, documento recebido udp.txt na área de trabalho ou no local definido no código).

Observação sobre UDP
Como o UDP não é um protocolo orientado à conexão, pode ocorrer perda de pacotes. Se o arquivo não for recebido no servidor, isso pode ser uma consequência do comportamento do protocolo, e não necessariamente um erro no código.