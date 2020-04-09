// Source: https://www.dfrobot.com/blog-948.html

#include <Arduino.h>    // Inkludere Arduino bibliotek
#include <WiFi.h>       // Inkludere WiFi bibliotek

const char* ssid = "AndroidAPF790";   // Navnet på WiFi netværk du tilslutter
const char* password = "ylwv3155";    // Password til WiFi netværk du tilslutter

String translateEncryptionType(wifi_auth_mode_t encryptionType) {
  /* Identificere krypteringen på WiFi. Denne gives i en klasse kaldet "Enum", som 
     repræsentere en gruppe konstanter, som kun skal læses, ikke ændres. Funktionen her 
     modtager denne enum som input, og retunere en tekst, som indikere typen af kryptering 
     på WiFi-netværket, med strings, i stedet for en integer. */
  
  switch (encryptionType){            // Switchcase der kører mulige krypteringstyper igennem
    case (WIFI_AUTH_OPEN):
      return "OPEN";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
  }
}

void scanNetworks(){
  /* Funktionen scanner og viser omkringliggende WiFi-netværker, og viser disse netværkers 
     navn, styrke på signal, MAC adresse, og krypteringstype. */
int numberOfNetworks = WiFi.scanNetworks();

Serial.print("Number of networks found: "); Serial.println(numberOfNetworks);
  for (int i = 0; i < numberOfNetworks; i++){
    Serial.print("Network name: "); Serial.println(WiFi.SSID(i));
    Serial.print("Signal strength: "); Serial.println(WiFi.RSSI(i));
    Serial.print("MAC address: "); Serial.println(WiFi.BSSIDstr(i)); // Medium Access Control

    Serial.print("Encryption type: ");
    String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
    Serial.println(encryptionTypeDescription);
    Serial.println("-----------------------");
  }
}

void connectToNetwork(){              // Tilslutter WiFi-netværk
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Establishing connection to WiFi...");
  }

  Serial.println("Connected to network");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  scanNetworks();       // Leder efter netværk, og printer informationer
  connectToNetwork();   // Tilslutter netværk

  Serial.println(WiFi.localIP());     // Printer lokal IP adresse til ESP32
  Serial.println(WiFi.macAddress());  // Printer MAC adresse til ESP32
  WiFi.disconnect(true);              // Afbryder forbindelsen til netværket
  Serial.println(WiFi.localIP());     // Tjekker at forbindelsen til netværket er afbrudt
}

void loop() {
  // put your main code here, to run repeatedly:
}