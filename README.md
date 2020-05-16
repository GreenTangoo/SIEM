Данная SIEM система состоит из нескольких модулей:
1) Модуль Аггрегации(сборщик)
2) Модуль Корреляции



По умолчанию в модуль корреляции встроено распознавание симптомов кибератак APT группировок. 
В модуль аггрегации встроен сбор необходимых для распознавания данных из лог-файлов системы.

Также можно добавлять свои правила корреляции и аггрегации.
Для этого необходимо в файлы aggr.json и corr.json прописать необходимые правила.

Устройство конфигурационного файла corr.json:



type-config - Тип конфигурационной записи. Может быть amount, что значит искать по количеству
	вхождений. Может быть found, что значит искать по вхождению.
type-node - Тип конфигурационной записи, обозначающей запись в json файле. Может быть
	object, обозначающей json объект. array, обозначающей json массив. string, обозначающей
	json строку.
key-value - Тип конфигурационной записи, обозначающей значение ключевевого слова(само слово).
parameter-value - Тип конфигурационной записи, обозначающей значение параметра ключевого слова.
high-threshold - Тип конфигурационной записи, обозначающей верхний порог числа определенных
	вхождений слов.
