#include <ESP8266WiFi.h>

// Pinos de controle motor A
int IN1 = 0;
int IN2 = 2;

// Pinos de controle motor B
int IN3 = 4;
int IN4 = 5;

const char* ssid = "******";
const char* password = "******";

int ledPin = 13; // GPIO13 = D7
WiFiServer server(80);


void setup() {

  Serial.begin(115200);
  delay(10);

  // Ponte H
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}


// Funções de movimentação do rover
// FRENTE
void andarFrente() {
  //Gira o Motor A no sentido horario
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //Gira o Motor B no sentido antihorario
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(2000); //aguarda 2.5s, enquanto anda para frente
  //Para o motor A e B
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

// TRAS
void andarTras() {
  //Gira o Motor A no sentido horario
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //Gira o Motor B no sentido anti-horario
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(2000); //aguarda 2.5s, enquanto anda para tras
  //Para o motor A e B
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

// ESQUERDA
void girarAAntiHorario() {
  //Gira o Motor A no sentido horario
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //Gira o Motor B no sentido horario
  //digitalWrite(IN3, LOW);
  //digitalWrite(IN4, HIGH);
  // aguarda 1s, enquanto anda para esquerda
  delay(2000);
  //Para o motor A e B
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

// DIREITA
void girarAHorario() {
  //Gira o Motor A no sentido horario
  //digitalWrite(IN1, HIGH);
  //digitalWrite(IN2, LOW);
  //Gira o Motor B no sentido horario
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // aguarda 1s, enquanto anda para direita
  delay(2000);
  //Para o motor A e B
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}


void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request
  int value = LOW;
  if (request.indexOf("/ROVER=ESQUERDA") != -1)  {
    digitalWrite(ledPin, HIGH);
    girarAHorario();
    delay(50);
    //value = HIGH;
  }
  if (request.indexOf("/ROVER=DIREITA") != -1)  {
    digitalWrite(ledPin, HIGH);
    girarAAntiHorario();
    delay(50);
    //value = LOW;
  }
  if (request.indexOf("/ROVER=FRENTE") != -1)  {
    digitalWrite(ledPin, HIGH);
    andarFrente();
    delay(50);
    //value = LOW;
  }
  if (request.indexOf("/ROVER=TRAS") != -1)  {
    digitalWrite(ledPin, HIGH);
    andarTras();
    delay(50);
    //value = LOW;
  }

  // Set ledPin according to the request
  digitalWrite(ledPin, value);
  delay(3000);

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  /*
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");

    client.println("<head><title>Rover Home</title>");

    client.print("<center><h1> Rover CVT-E </></center>");
  */
  /*
    if(value == HIGH) {
     client.print("On");
    } else {
     client.print("Off");
    }
  */
  /*
    client.println("<br><br>");

    client.println("<center><a href=\"/ROVER=FRENTE\"\"><button> FRENTE </button></a><br/></center>");
    client.println("<center><a href=\"/ROVER=DIREITA\"\"><button>     DIREITA </button></a><br /></center>");
    client.println("<center><a href=\"/ROVER=ESQUERDA\"\"><button> ESQUERDA    </button></a><br/></center>");
    client.println("<center><a href=\"/ROVER=TRAS\"\"><button> TRAS </button></a><br/></center>");

    client.println("</html>");

    delay(1);
    Serial.println("Client disonnected");
    Serial.println("");


    // Reinicia conexão
    //setup();
  */

}
