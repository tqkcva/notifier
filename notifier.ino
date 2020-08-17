#define LED 13

typedef enum {
  LED_OFF = 0,
  LED_ON,
  LED_BLINK
} led_state_t;

led_state_t led_state = LED_OFF;

void led_process()
{
  static int blink_state = LOW;
  static unsigned long led_time = millis();
  if (millis() - led_time > 100)
  {
    switch(led_state)
    {
      case LED_OFF:
        blink_state = LOW;
        break;
      case LED_ON:
        blink_state = HIGH;
        break;
      case LED_BLINK:
        if (blink_state == LOW)
        {
          blink_state = HIGH;
        }
        else
        {
          blink_state = LOW;
        }
        break;
      default:
      break;
    }
    digitalWrite(LED, blink_state);
    led_time = millis();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    String res = Serial.readStringUntil('\n');
    Serial.print(res);
    if (res == "led blink")
    {
      led_state = LED_BLINK;
    }
    if (res == "led on")
    {
      led_state = LED_ON;
    }
    if (res == "led off")
    {
      led_state = LED_OFF;
    }
  }
  led_process();
}
