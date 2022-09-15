# OS
Лабораторные работы по дисциплине "Операционные системы" ПИиКТ ИТМО 3 курс

## Лабораторная работа №1 ##

Основная цель лабораторной работы - знакомство с системными инструментами анализа производительности и поведения программ. Для этого предлагается для выданной по варианту программы выяснить следующую информацию:

1. Количество потоков создаваемое программой;
2. Список файлов и сетевых соединений с которыми работает программа
3. Карту памяти процесса;
4. Содержимое передаваемых по сети данных;
5. Построить графики:

* Потребления программой cpu;
* Нагрузки генерируемой программой на подсистему ввода-вывода;
* Нагрузки генерируемой программой на сетевую подсистему.
* Смены состояния исполнения потоков;


Отчет должен содержать:

1. Описание шагов выполненных для сбора информации (включая исходные тексты всех использованных скриптов и вспомогательных программ).
2. Полученные графики.
3. Выводы по работе.


Темы для подготовки к защите лабораторной работы:

1. Структура процесса
2. Виртуальная память
3. Системные утилиты сбора статистики ядра
4. Основы ввода-вывода (блочный и последовательный ввод-вывод)
5. Файловая система procfs
6. Использование утилиты strace, ltrace, bpftrace
7. Профилирование и построение flamegraph'а и stap
