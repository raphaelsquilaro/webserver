# ESP32 — Controle de LED via Wi‑Fi

Projeto para **ESP32** que cria uma rede Wi‑Fi própria e disponibiliza uma página web para controlar um LED conectado ao pino GPIO 4.

## 📋 Visão geral

O ESP32 funciona como um **Access Point (AP)**, ou seja, cria sua própria rede Wi‑Fi. Um celular ou computador pode se conectar diretamente a essa rede e acessar uma interface web para:

- 💡 Ligar o LED
- 🔴 Desligar o LED
- 📡 Controlar o ESP32 pelo navegador
- 📊 Visualizar o status do LED na página

## 🔧 Hardware

- 1 × ESP32
- 1 × LED
- 1 × resistor apropriado para o LED
- Jumpers e protoboard (opcional)

### Ligação do LED

O código utiliza:

```cpp
const int LED_PIN = 4;
```

Portanto, o LED deve ser conectado ao **GPIO 4**, respeitando a polaridade do LED e utilizando um resistor limitador de corrente.

> Se estiver usando um LED integrado ou uma placa diferente, confirme qual GPIO está disponível antes de alterar o circuito.

## 💻 Software

O projeto utiliza as bibliotecas:

```cpp
#include <WiFi.h>
#include <WebServer.h>
```

Essas bibliotecas fazem parte do ambiente de desenvolvimento para ESP32.

### Ambiente recomendado

- Arduino IDE
- Placa ESP32 configurada na Arduino IDE
- Cabo USB para programação
- Navegador web em um celular ou computador

## 📡 Configuração da rede Wi‑Fi

O ESP32 cria uma rede própria com as seguintes configurações:

| Configuração | Valor |
|---|---|
| Nome da rede (SSID) | `ESP32-Raphael` |
| Senha | `senha123` |
| IP do ESP32 | `192.168.4.1` |
| Porta do servidor | `80` |

Esses valores podem ser alterados no código:

```cpp
const char* ssid = "ESP32-Raphael";
const char* password = "senha123";
```

> **Segurança:** para um projeto real, altere a senha padrão e evite publicar credenciais reais em repositórios públicos.

## 🚀 Como instalar

### 1. Preparar a Arduino IDE

Instale/configure o suporte à placa ESP32 na Arduino IDE.

Depois, selecione a placa ESP32 correspondente ao seu hardware.

### 2. Abrir o código

Abra o arquivo `.ino` do projeto na Arduino IDE e confirme as configurações:

```cpp
const char* ssid = "ESP32-Raphael";
const char* password = "senha123";

const int LED_PIN = 4;
```

### 3. Conectar o ESP32

Conecte o ESP32 ao computador utilizando um cabo USB.

Selecione:

- A placa correta
- A porta serial correta

### 4. Fazer o upload

Compile e envie o código para o ESP32.

Após o upload, abra o **Monitor Serial** com a velocidade:

```text
115200 baud
```

## 🌐 Como usar

Depois que o ESP32 iniciar:

1. Procure a rede Wi‑Fi `ESP32-Raphael`.
2. Conecte o celular ou computador utilizando a senha configurada no código.
3. Abra um navegador.
4. Acesse:

```text
http://192.168.4.1
```

Será exibida a interface **Controle de LED**.

### Controles disponíveis

**Ligar LED**

A página envia uma requisição para:

```text
/on
```

O ESP32 executa:

```cpp
digitalWrite(LED_PIN, HIGH);
```

**Desligar LED**

A página envia uma requisição para:

```text
/off
```

O ESP32 executa:

```cpp
digitalWrite(LED_PIN, LOW);
```

## 🔌 Rotas HTTP

O servidor possui três rotas principais:

| Rota | Método | Função |
|---|---|---|
| `/` | GET | Exibe a página de controle |
| `/on` | GET | Liga o LED |
| `/off` | GET | Desliga o LED |

Exemplo:

```text
http://192.168.4.1/on
```

Resposta:

```text
LED ON
```

E:

```text
http://192.168.4.1/off
```

Resposta:

```text
LED OFF
```

## 🧠 Funcionamento

O fluxo do projeto é:

```text
Celular / Computador
        │
        │ Wi‑Fi
        ▼
   ESP32 Access Point
        │
        │ HTTP
        ▼
   WebServer na porta 80
        │
        ├── /  → Página HTML
        │
        ├── /on  → GPIO 4 HIGH
        │
        └── /off → GPIO 4 LOW
```

### Inicialização

No `setup()`, o programa:

1. Configura o GPIO 4 como saída.
2. Mantém o LED inicialmente desligado.
3. Inicializa a comunicação serial em 115200 baud.
4. Cria a rede Wi‑Fi com `WiFi.softAP()`.
5. Configura as rotas HTTP.
6. Inicia o servidor web.

### Loop principal

No `loop()`:

```cpp
server.handleClient();
```

Essa função verifica e processa as requisições recebidas pelos clientes.

## 🎨 Interface web

A página HTML é criada diretamente pelo ESP32 através da função:

```cpp
String getHTML()
```

A interface possui:

- Layout responsivo
- Botão verde para ligar
- Botão vermelho para desligar
- Indicador de status
- CSS incorporado
- JavaScript utilizando `fetch()`

O JavaScript envia as requisições sem precisar recarregar a página:

```javascript
fetch("/on")
```

ou:

```javascript
fetch("/off")
```

## 🖥️ Monitor Serial

Ao iniciar, o ESP32 informa dados úteis no Monitor Serial, incluindo:

```text
Wi-Fi iniciado com sucesso!
Nome da rede: ESP32-Raphael
Senha: senha123
IP do ESP32: 192.168.4.1
Servidor iniciado com sucesso!
```

Isso facilita a identificação da rede e do endereço que deve ser acessado.

## 🛠️ Solução de problemas

### A rede Wi‑Fi não aparece

Verifique:

- Se o ESP32 está ligado.
- Se o upload foi concluído corretamente.
- Se o Monitor Serial apresenta a mensagem de inicialização.
- Se a alimentação do ESP32 está adequada.

### Não consigo acessar `192.168.4.1`

Confirme que o celular/computador está conectado à rede criada pelo ESP32.

A rede deve ser:

```text
ESP32-Raphael
```

E o endereço:

```text
http://192.168.4.1
```

### O LED não acende

Verifique:

- Conexão do LED.
- Polaridade do LED.
- Resistor limitador de corrente.
- Conexão ao GPIO 4.
- Se o GPIO 4 corresponde ao pino físico utilizado na sua placa.

### O navegador mostra erro ao executar o comando

Verifique se o dispositivo continua conectado à rede Wi‑Fi do ESP32 e se o servidor continua ativo.

## 📁 Estrutura sugerida

```text
esp32-controle-led/
├── esp32-controle-led.ino
└── README.md
```

## 🔐 Observação sobre segurança

Este projeto foi desenvolvido para fins educacionais e para uso em uma rede local criada pelo próprio ESP32.

A senha:

```text
senha123
```

é apenas uma configuração de exemplo. Em projetos reais, utilize uma senha mais forte e não compartilhe credenciais reais em código público.

## 📄 Licença

Este projeto pode ser utilizado e modificado para fins de estudo e experimentação.
