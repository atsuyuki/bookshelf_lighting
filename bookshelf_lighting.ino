
const double C = 255.0; // 用いるLEDに依存する定数

int light_pin = 0;
int led_pin = 1;
int button_pin = 2;

void setup() {
 pinMode(light_pin, OUTPUT);
 pinMode(led_pin, OUTPUT);
 pinMode(button_pin, INPUT_PULLUP);

 fade(0, 255);
}

void loop() {
 button_wait();
 fade(250, 200);

 button_wait();
 fade(200, 100);

 button_wait();
 fade(100, 0);

 button_wait();
 fade(0, 255);
 delay(200);
}

void button_wait() {
 while (digitalRead(button_pin)) {
   delay(100);
 }
}

void fade(int start_value, int end_value) {
 int current_value = start_value; // 開始値をセット


 // 目標値に達していないうちはループ
 while (current_value != end_value) {

   // 目標値より小さい
   if (current_value < end_value) {
     ++current_value;
   }

   // 目標値より大きい
   if (current_value > end_value) {
     --current_value;
   }
   analogWrite(light_pin, get_duty(current_value));
   delay(5);
 }
}

int get_duty(double ratio) {
 return round(exp(log(255.0) - (1 - (ratio / 255.0)) * log(C))) - 1; // Weber-Fechnerの法則
}
