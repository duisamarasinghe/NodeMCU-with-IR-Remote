#include <IRremoteESP8266.h>

int RECV_PIN = D1;
int analogValue = 0;

IRrecv irrecv(RECV_PIN);
decode_results result;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if(irrecv.decode(&result)){
    Serial.println(result.value, HEX);
    
    String irMessage = "";
    irMessage = irMessage + result.value;
    long int code = result.value;
    Serial.println(irMessage);
    Serial.println(code);

    if(irMessage == "16753245"){  //No 1 in Remote
      Serial.println("Remote No 1 pressed");
      analogValue = 255;
    }else if(irMessage == "16736925"){  //No 2 in Remote
      Serial.println("Remote No 2 pressed");
      analogValue = 0;
    }else if(irMessage == "16718055"){  //Up button in Remote
      Serial.println("Remote Up button pressed");
      analogValue += 1;
    }else if(irMessage == "16730805"){  //Down button in Remote
      Serial.println("Remote Down button pressed");
      analogValue -= 1;
    }

    analogWrite(D5, analogValue);

    irrecv.resume();
  }
}

