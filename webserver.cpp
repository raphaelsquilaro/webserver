#include <WiFi.h>
#include <WebServer.h>

// ==========================================
// CONFIGURAÇÃO DO WI-FI
// ==========================================

const char* ssid = "ESP32-Raphael";
const char* password = "senha123";

// ==========================================
// CONFIGURAÇÃO DO LED
// ==========================================

const int LED_PIN = 4;

// ==========================================
// SERVIDOR WEB
// ==========================================

WebServer server(80);

// ==========================================
// PÁGINA HTML
// ==========================================

String getHTML() {

  String html = R"rawliteral(

<!DOCTYPE html>
<html lang="pt-br">

<head>

  <meta charset="UTF-8">

  <meta name="viewport"
        content="width=device-width, initial-scale=1.0">

  <title>ESP32 | Controle de LED</title>

  <style>

    /* =========================
       RESET
    ========================= */

    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }

    /* =========================
       PÁGINA
    ========================= */

    body {
      min-height: 100vh;

      display: flex;
      flex-direction: column;

      justify-content: center;
      align-items: center;

      font-family: Arial, sans-serif;

      background: #f2f4f7;
      color: #222;

      padding: 20px;
    }

    /* =========================
       TÍTULO
    ========================= */

    h1 {
      margin-bottom: 10px;

      text-align: center;

      font-size: 2rem;
    }

    p {
      margin-bottom: 30px;

      color: #666;

      text-align: center;
    }

    /* =========================
       CONTAINER
    ========================= */

    .container {
      width: 100%;
      max-width: 400px;

      padding: 30px;

      background: white;

      border-radius: 20px;

      box-shadow: 0 10px 30px rgba(0, 0, 0, 0.1);

      text-align: center;
    }

    /* =========================
       BOTÕES
    ========================= */

    button {
      width: 100%;

      padding: 15px;

      margin: 8px 0;

      border: none;

      border-radius: 10px;

      font-size: 18px;

      font-weight: bold;

      cursor: pointer;

      transition: 0.2s;
    }

    /* =========================
       BOTÃO LIGAR
    ========================= */

    button.on {
      background: #22c55e;

      color: white;
    }

    button.on:hover {
      background: #16a34a;

      transform: scale(1.03);
    }

    /* =========================
       BOTÃO DESLIGAR
    ========================= */

    button.off {
      background: #ef4444;

      color: white;
    }

    button.off:hover {
      background: #dc2626;

      transform: scale(1.03);
    }

    /* =========================
       EFEITO AO CLICAR
    ========================= */

    button:active {
      transform: scale(0.97);
    }

    /* =========================
       STATUS
    ========================= */

    #status {
      margin-top: 20px;

      font-size: 18px;

      font-weight: bold;
    }

  </style>

</head>

<body>

  <div class="container">

    <h1>Controle de LED</h1>

    <p>ESP32 via Wi-Fi</p>

    <button class="on" onclick="ligar()">
      Ligar LED
    </button>

    <button class="off" onclick="desligar()">
      Desligar LED
    </button>

    <div id="status">
      LED desligado
    </div>

  </div>

  <script>

    // =========================
    // LIGAR LED
    // =========================

    function ligar() {

      fetch("/on")
        .then(response => response.text())
        .then(data => {

          document.getElementById("status").innerText =
            "LED ligado";

        })
        .catch(error => {

          document.getElementById("status").innerText =
            "Erro ao ligar o LED";

        });

    }


    // =========================
    // DESLIGAR LED
    // =========================

    function desligar() {

      fetch("/off")
        .then(response => response.text())
        .then(data => {

          document.getElementById("status").innerText =
            "LED desligado";

        })
        .catch(error => {

          document.getElementById("status").innerText =
            "Erro ao desligar o LED";

        });

    }

  </script>

</body>

</html>

)rawliteral";

  return html;
}


// ==========================================
// CONFIGURAÇÃO INICIAL
// ==========================================

void setup() {

  // Configura o pino do LED como saída
  pinMode(LED_PIN, OUTPUT);

  // Começa com o LED desligado
  digitalWrite(LED_PIN, LOW);

  // Inicia comunicação serial
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("================================");
  Serial.println("       CONTROLE ESP32");
  Serial.println("================================");

  // ========================================
  // CRIA A REDE WI-FI DO ESP32
  // ========================================

  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.println("Wi-Fi iniciado com sucesso!");

  Serial.print("Nome da rede: ");
  Serial.println(ssid);

  Serial.print("Senha: ");
  Serial.println(password);

  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.softAPIP());

  // ========================================
  // PÁGINA PRINCIPAL
  // ========================================

  server.on("/", []() {

    server.send(
      200,
      "text/html",
      getHTML()
    );

  });


  // ========================================
  // ROTA PARA LIGAR O LED
  // ========================================

  server.on("/on", []() {

    digitalWrite(LED_PIN, HIGH);

    Serial.println("LED ligado!");

    server.send(
      200,
      "text/plain",
      "LED ON"
    );

  });


  // ========================================
  // ROTA PARA DESLIGAR O LED
  // ========================================

  server.on("/off", []() {

    digitalWrite(LED_PIN, LOW);

    Serial.println("LED desligado!");

    server.send(
      200,
      "text/plain",
      "LED OFF"
    );

  });


  // ========================================
  // INICIA O SERVIDOR
  // ========================================

  server.begin();

  Serial.println();
  Serial.println("Servidor iniciado com sucesso!");
  Serial.println();

  Serial.println("Conecte seu celular/computador na rede:");

  Serial.println(ssid);

  Serial.println();

  Serial.println("Depois abra no navegador:");

  Serial.println("http://192.168.4.1");

  Serial.println();
  Serial.println("================================");

}


// ==========================================
// LOOP PRINCIPAL
// ==========================================

void loop() {

  // Aguarda requisições dos clientes
  server.handleClient();

}
