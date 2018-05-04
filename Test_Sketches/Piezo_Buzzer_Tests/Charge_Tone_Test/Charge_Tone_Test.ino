/*
 * "Victory" or "Charge" Tone Music for use with
 * Keyes L-298P Shield
 * By LeRoy Miller, Dec 2017
 * 
 */
 
#define BUZZER 4 //D4

int note[] = {262, 262, 392, 523, 392, 523};
int duration[] = {100, 100, 100, 300, 100, 300};
 
void setup() {

//Plays Song once, hit reset to hear again.
  
for (int thisNote = 0; thisNote < 6; thisNote ++) {
     // play the next note:
     tone(BUZZER, note[thisNote]);
     // hold the note:
     delay(duration[thisNote]);
     // stop for the next note:
     noTone(BUZZER);
     delay(25);
}
}

void loop() {
  // put your main code here, to run repeatedly:

}
