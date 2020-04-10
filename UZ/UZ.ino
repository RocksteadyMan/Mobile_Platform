#define TRIGGER_PIN 19   // Вывод Trig подключен к 25-у порту .
#define ECHO_PIN 18 // Вывод Echo подключен к 26-у порт.

void setup()
{
  Serial.begin(115200);             // Инициализация передачи по COM порту.
  pinMode(TRIGGER_PIN, OUTPUT);   // Устанавливаем режим работы вывода, как "выход".
  pinMode(ECHO_PIN, INPUT);       // Устанавливаем режим работы вывода, как "вход".
  digitalWrite(TRIGGER_PIN, LOW); // Приводим порт Trig к состоянию по умолчанию.
  delayMicroseconds(50);          // Делаем небольшую задержку в 50 мкс.
}

void loop()
{
  long duration, cm, inch, mm;        // Объявляем переменные для расчетов.
  digitalWrite(TRIGGER_PIN, HIGH);    // Подаем логическую единицу (5В) на порт Trig (Включаем передатчик).
  delayMicroseconds(10);              // Ждем 10-11 мкс.
  digitalWrite(TRIGGER_PIN, LOW);     // Подаем логический ноль на порт Trig (Выключаем передатчик).
  duration = pulseIn(ECHO_PIN, HIGH); // Засекаем время ответного импульса на порту Echo.
  // Пересчет и вывод результата в сантиметрах.
  cm = duration / 58;
  Serial.print("cm: ");
  Serial.println(cm);
  // Выводим разделитель и ждем 1 секунду.
  Serial.println("");
  delay(1000);
}

