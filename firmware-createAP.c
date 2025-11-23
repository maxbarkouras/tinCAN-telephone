#include <WiFi.h>
#include <WebServer.h>
#include <string.h>
#include <stdlib.h>
#include "driver/twai.h"

const char* ap_ssid = "tinCAN";
const char* ap_pass = "xxx";
WebServer server(80);
const int LED = 2;
static const gpio_num_t CAN_TX_PIN = GPIO_NUM_21;
static const gpio_num_t CAN_RX_PIN = GPIO_NUM_22;

const char* page =
"<!doctype html><html><body>"
"<h2>CAN CONTROL</h2>"
"<form method='POST' action='/set'>"
"<input type='text' name='id', value='7FF', maxlength='3', size='4'>"
"<form method='POST' action='/set'>"
"<input type='text' name='val', value='FFFFFFFFFFFFFFFF', maxlength='16', size='17'>"
"<button>Send</button></form></body></html>";

void setup_server() {
  server.send(200, "text/html", page);
}

void get_data() {
  pinMode(LED, OUTPUT);
  twai_message_t m = {};
  m.extd = 0;
  m.rtr = 0;
  m.data_length_code = 8;

  if (server.hasArg("id")) {
    char current_id[4] = {(server.arg("id"))[0], (server.arg("id"))[1], (server.arg("id"))[2], '\0'};
    m.identifier = strtol(current_id, NULL, 16);
    for (int i=0; i<8; i++){
      char current_byte[3] = {(server.arg("val"))[i*2], (server.arg("val"))[i*2+1], '\0'};
      m.data[i] = strtol(current_byte, NULL, 16);
    }
    if (twai_transmit(&m, pdMS_TO_TICKS(100)) == ESP_OK ) {
      Serial.println("sent");
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
    } else{
      Serial.println("failed");
    }
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void listen(void*) {
  ;
}

void setup() {
  Serial.begin(115200);

  twai_general_config_t g = TWAI_GENERAL_CONFIG_DEFAULT(CAN_TX_PIN, CAN_RX_PIN, TWAI_MODE_NORMAL);
  twai_timing_config_t t = TWAI_TIMING_CONFIG_500KBITS();
  twai_filter_config_t f = TWAI_FILTER_CONFIG_ACCEPT_ALL();

  if (twai_driver_install(&g, &t, &f) != ESP_OK) {
      Serial.println("driver install failed");
      while (true) {delay(1000);}
    }
  if (twai_start() != ESP_OK) {
    Serial.println("driver start failed");
    while (true) {delay(1000);}
  }
  Serial.println("CAN up 500k");

  WiFi.mode(WIFI_AP);
  IPAddress local_IP(192, 168, 1, 1);
  IPAddress gateway (192, 168, 1, 1);
  IPAddress subnet  (255, 255, 255, 0);

  if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
    Serial.println("AP config failed");
  }
  if (!WiFi.softAP(ap_ssid, ap_pass)) {
    Serial.println("AP start failed");
    while (true) { delay(1000); }
  }
  delay(100); 
  server.on("/", setup_server);
  server.on("/set", HTTP_POST, get_data);
  server.begin();
}

void loop() {
  server.handleClient();
}
