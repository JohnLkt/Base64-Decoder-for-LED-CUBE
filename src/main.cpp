#include <Arduino.h>

// Function to decode a base-64 character to its 6-bit value
uint8_t base64Decode(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return 0;  // Invalid character
}

// Function to decode a base-64 string to RGB values
void decodeBase64ToRGB(const char *base64String) {
    size_t len = strlen(base64String);

    // Ensure the length is a multiple of 4
    if (len % 4 != 0) {
        fprintf(stderr, "Invalid base-64 string length\n");
        return;
    }

    for (size_t i = 0; i < len; i += 4) {
        uint8_t b1 = base64Decode(base64String[i]);
        uint8_t b2 = base64Decode(base64String[i + 1]);
        uint8_t b3 = base64Decode(base64String[i + 2]);
        uint8_t b4 = base64Decode(base64String[i + 3]);

        // Combine 4 base-64 values into 3 bytes
        uint32_t combined = (b1 << 18) | (b2 << 12) | (b3 << 6) | b4;

        // Extract RGB values
        uint8_t r = (combined >> 16) & 0xFF;
        uint8_t g = (combined >> 8) & 0xFF;
        uint8_t b = combined & 0xFF;

        // Print RGB values
        printf("RGB: %3u, %3u, %3u\n", r, g, b);
    }
}

void setup() {
  Serial.begin(9600);
  delay(3000);
    Serial.println("Start Decode");
    unsigned int start = micros();

    const char *base64String = "b2ZmaWNlZ2FpbmFza2hlYWRpbmdwZXJmZWN0bWFzc2FnZW1pbmVyYWxzaGF2aW5nbWVldHRha2Vuc2lsZW5jZWRpbm5lcmhhcHB5ZmlmdGhjYWxsa2l0Y2hlbnRyaWNrdHJ1dGhwaWNrb3JjYWJpbmFjY2lkZW50YmVzaWRlZGlzaHJlbWVtYmVycGFyZW50c2xvd2Jsb3dhbHNvZnJvemVuY29udmVyc2F0aW9ubm91bmxlYWRzb29uZGFya2dpZnRwYXJ0YmVzaWRlYmxhY2ttYWtpbmdzcGVlY2hzdGVhbXRlbXBlcmF0dXJlY29tcGFyZW5lZ2F0aXZlc2hvd25ib3hiZXNpZGVob25vcnNldHRsZXJlYXNvbnBsYXRlc2RlZXJwbGF5c2hlbGxzZGlyZWN0bHliZWF0YXR0ZW50aW9uZGVjaWRldGFsbGNyeXZlZ2V0YWJsZWdyZWVuZXhwZXJpbWVudHRoYW5zbGVlcGFkZGl0aW9uYWxtYXNzYWdlaW5kaWNhdGVjYXVzZWRpc2Vhc2VzdXJwcmlzZWZlZXRicm9rZWRpdmlzaW9ubm9zZWxvdmVseXRpZXllbGxvd3NlYXRiZXNpZGVsYXdoYWxmY3JvcGVxdWF0b3JiZWNhbWVjb2xsZWN0c2V0dGluZ2Nvb2tpZXN0aG91c2Es";
    decodeBase64ToRGB(base64String);

    unsigned int end = micros();
  Serial.println("Complete");
  Serial.print("Decoding completed in: ");
  Serial.println(end - start);
}

void loop() {
  // Your code here
}

