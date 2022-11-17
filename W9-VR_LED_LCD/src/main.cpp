#include <Arduino.h>
#include <LiquidCrystal.h>

#define VR_PIN 0

LiquidCrystal lcd(49, 48, 47, 43, 42, 41);

const int led_num = 17;
const int led_pins[led_num] = {9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 2};

void setup()
{
	pinMode(VR_PIN, INPUT);
	lcd.begin(16, 2);
	lcd.clear();

	Serial.begin(9600);

	pinMode(A15, OUTPUT);
	for (int pin = 0; pin < led_num; pin++)
		pinMode(led_pins[pin], OUTPUT);
}

void check_vr(int &vr)
{
	if (abs(analogRead(VR_PIN) - vr) >= 30)
		vr = analogRead(VR_PIN);
}

void scroll(int cursor, String str, int &delay_time)
{
	String first_str = str;

	for (int index = 16; index >= 0; index--)
	{
		lcd.setCursor(index, cursor);
		lcd.print(first_str);
		lcd.print(" ");

		delay(delay_time);

		check_vr(delay_time);

		// off all led
		for (int pin = 0; pin < led_num; pin++)
			digitalWrite(led_pins[pin], HIGH);

		digitalWrite(led_pins[index], LOW);
	}

	double step = led_num / first_str.length();

	for (int index = 0; index < first_str.length(); index++)
	{
		lcd.setCursor(0, cursor);
		lcd.print(first_str.substring(index + 1, 16 + index));

		lcd.print(" ");

		delay(delay_time);

		check_vr(delay_time);

		for (int pin = 0; pin < led_num; pin++)
			digitalWrite(led_pins[pin], HIGH);

		digitalWrite(led_pins[int(index * step)], LOW);
	}
}

void loop()
{

	auto vr_value = analogRead(VR_PIN);
	scroll(0, "The NUTN Test.", vr_value);
}
