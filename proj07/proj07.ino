int notes[]={262,294,330,349};

void setup() {
  Serial.begin(9600); 
}

void loop() {
  int keyVal=analogRead(A0);
  Serial.println(keyVal);
  
  if (keyVal == 1023) {
    tone(8,notes[0]);
  } else if (keyVal >= 1000 && keyVal <= 1005) {
      tone(8,notes[1]);  
  } else if (keyVal >= 510 && keyVal <= 515) {
      tone(8,notes[2]);
  } else if (keyVal >= 5 && keyVal <= 13) {
      tone(8,notes[3]);
  } else {
      noTone(8);
  } 
}
