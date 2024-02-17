#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <addons/TokenHelper.h>
#include <ArduinoJson.h>
#define FIREBASE_USE_PSRAM

//Conectar a una red WiFi 
const char* WIFI_SSID = "DiQueEresMiPerra";//el nombre de la red
const char* WIFI_PASSWORD = "soytuperra";//la contraseña de la red
//Recursos de Firebase
const char* API_KEY = "AIzaSyDoRz1GT8Ew61oVTu4Kkyih_tu7WGcQYdQ";
const char* FIREBASE_PROJECT_ID = "iotpagejsgc";
//CONFIGURAR UN EMAIL Y CONTRASEÑA EN AUTHENTICATION de Firebase
const char* USER_EMAIL = "espgaibor@esp.com";
const char* USER_PASSWORD = "espGaibor";

const int LED1 = 23;
const int LED2 = 19;
const int LED3 = 22;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setupWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase() {
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.token_status_callback = tokenStatusCallback;  // Ver addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void setup() {
  Serial.begin(115200);
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);//Verificamos la version
  setupWiFi();
  setupFirebase();
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

}

void loop(){
  String path = "controlLED";//RUTA DE COLECCION
  FirebaseJson json;

  if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), "")) {

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, fbdo.payload().c_str());

    if (!error) {
      for (JsonObject document : doc["documents"].as<JsonArray>()) {
        const char* document_name = document["name"];//PARAMETRO NOMBRE == ID Documento
        //Serial.print(document);
        const bool state = document["fields"]["encender"]["booleanValue"];//PARAMETRO DE CAMPOS A REVISAR
        Serial.print(" : ");
        if (strstr(document_name, "LED1") != nullptr) {//COMPARAR NOMBRE CON  RESULTADO ESPERADO LED1
          state ? Serial.print("LED1 On") : Serial.print("LED1 OFF");
          if (state==false){
            digitalWrite(LED1, 0);
          }
          else{
            digitalWrite(LED1, 1);
          }
        }
      }


      for (JsonObject document : doc["documents"].as<JsonArray>()) {
        const char* document_name = document["name"];//PARAMETRO NOMBRE == ID Documento
        //Serial.print(document);
        const bool state = document["fields"]["encender2"]["booleanValue"];//PARAMETRO DE CAMPOS A REVISAR
        Serial.print(" : ");
        if (strstr(document_name, "LED2") != nullptr) {//COMPARAR NOMBRE CON  RESULTADO ESPERADO LED1
          state ? Serial.print("LED2 On") : Serial.print("LED2 OFF");
          if (state==false){
            digitalWrite(LED2, 0);
          }
          else{
            digitalWrite(LED2, 1);
          }
        }
      }

      for (JsonObject document : doc["documents"].as<JsonArray>()) {
        const char* document_name = document["name"];//PARAMETRO NOMBRE == ID Documento
        //Serial.print(document);
        const bool state = document["fields"]["encender3"]["booleanValue"];//PARAMETRO DE CAMPOS A REVISAR
        Serial.print(" : ");
        if (strstr(document_name, "LED3") != nullptr) {//COMPARAR NOMBRE CON  RESULTADO ESPERADO LED1
          state ? Serial.print("LED3 On") : Serial.print("LED3 OFF");
        
        if(state==false){
          digitalWrite(LED3, 0);
        }
        else{
            digitalWrite(LED3, 1);
          }
        
      }
    }
  } 
}}
      


