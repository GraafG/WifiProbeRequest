#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}

String alfa = "1234567890qwertyuiopasdfghjkklzxcvbnm QWERTYUIOPASDFGHJKLZXCVBNM_";
byte channel;

// Probe request Packet buffer
uint8_t packet[128] = { 0x40, 0x00, 0x00, 0x00, 
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                /*16*/  0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                /*22*/  0x40, 0x37, 

                /* SSID */
                /*24*/  0x00, 0x06, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72,
                        0x01, 0x08, 0x82, 0x84, 0x8b, 0x0c, 0x12, 0x96, 0x18, 0x24,
                        0x32, 0x04, 0x30, 0x48, 0x60, 0x6c
                        };                       



void setup() {
  delay(500);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1); 
}



void loop() {
    // Randomize channel //
   
    channel = random(1,13); 
    wifi_set_channel(channel);

    // Randomize SRC MAC
    packet[10] = random(256);
    packet[11] = random(256);
    packet[12] = random(256);
    packet[13] = random(256);
    packet[14] = random(256);
    packet[15] = random(256);

    // SSID (Fixed size 6. Lazy right?)
    packet[26] = alfa[random(65)];
    packet[27] = alfa[random(65)];
    packet[28] = alfa[random(65)];
    packet[29] = alfa[random(65)];
    packet[30] = alfa[random(65)];
    packet[31] = alfa[random(65)];
    
    //packet[56] = channel;
    
    wifi_send_pkt_freedom(packet, 48, 0);
    wifi_send_pkt_freedom(packet, 48, 0);
    wifi_send_pkt_freedom(packet, 48, 0);
    delay(1);
}
