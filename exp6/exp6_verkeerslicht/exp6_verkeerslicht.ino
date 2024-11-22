enum LightState {
  GREEN,
  ORANGE,
  RED
};

/*
 * TL1 ROOD -> pin 32
 * TL1 ORANJE -> pin 33
 * TL1 GROEN -> pin 25
 *
 * TL2 ROOD -> pin 26
 * TL2 ORANJE -> pin 14
 * TL2 GROEN -> pin 27
*/
int traffic_light1[3] = {25, 33, 32};
int traffic_light2[3] = {27, 14, 26};


LightState update_state(long current_time, long previous_time, LightState current_state){
  const long GREEN_PERIOD = 4000;
  const long ORANGE_PERIOD = 2000;
  const long RED_PERIOD = GREEN_PERIOD + ORANGE_PERIOD;
  long time_diff = current_time - previous_time;
  if (time_diff > RED_PERIOD && current_state == RED) return GREEN; 
  if (time_diff > ORANGE_PERIOD && current_state == ORANGE) return RED; 
  if (time_diff > GREEN_PERIOD && current_state == GREEN) return ORANGE; 
  return current_state;
}

void set_traffic_light(LightState state, int led_pins[3], bool reverse=false){
  for (int i = 0; i < 3; i++) digitalWrite(led_pins[i], LOW);
  if (state == RED) digitalWrite(led_pins[reverse? GREEN : RED], HIGH);
  if (state == ORANGE) digitalWrite(led_pins[ORANGE], HIGH);
  if (state == GREEN) digitalWrite(led_pins[reverse? RED : GREEN], HIGH);
} 

void setup(){
  for (int i = 0; i < 3; i++) pinMode(traffic_light1[i], OUTPUT);
  for (int i = 0; i < 3; i++) pinMode(traffic_light2[i], OUTPUT);
  Serial.begin(9600);
}

long current_time, previous_time = millis();
LightState current_state = GREEN;
LightState previous_state = RED;

void loop(){
  current_time = millis();
  current_state = update_state(current_time, previous_time, current_state);
  if (current_state != previous_state){
    Serial.print("State updated to: ");
    Serial.println(current_state);
    set_traffic_light(current_state, traffic_light1);
    set_traffic_light(current_state, traffic_light2, true);
    previous_state = current_state;
    previous_time = current_time;
  }
}
