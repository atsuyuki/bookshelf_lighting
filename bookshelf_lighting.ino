/*
本棚の下のLEDテープをかっこよくフェードさせるスケッチ。
*/

const int light_pin = 0; // LEDテープのコントロール
const int led_pin = 1; // Digisparkの内蔵LED
const int button_pin = 2; // プッシュボタン
const int max_value = 255; // PWM出力の最大値
const int fade_step = 10; // フェードのステップ数
const double C = 255.0; // 用いるLEDに依存する定数

void setup() {
  pinMode(light_pin, OUTPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);

  // 初期状態は点灯
  fade(0, max_value);
}

void loop() {
  // 一旦ボタンを離してね
  button_wait(0);

  // fade_step刻みで暗くする
  for (int i = fade_step; i > 0; i--) {
    button_wait(1);
    fade(max_value / fade_step * i, max_value / fade_step * (i - 1));
  }

  // 一旦ボタンを離してね
  button_wait(0);
  button_wait(1);
  // リセット（点灯）
  fade(0, max_value);

}

void button_wait(boolean flag) {
  // ボタンが押／離されるまで待つ
  while (digitalRead(button_pin) == flag) {
    delay(100);
  }
}

void fade(int start_value, int end_value) {
  // 開始値をセット
  int current_value = start_value;


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

    // 明るさを出力
    analogWrite(light_pin, get_duty(current_value));
    delay(5);
  }
}

int get_duty(double ratio) {
  // Weber-Fechnerの法則
  return round(exp(log(255.0) - (1 - (ratio / 255.0)) * log(C))) - 1;
}
