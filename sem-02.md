#  ДЗ №2 #
## Markdown report <br> ##

### 1. Ганина Ксения Андреевна (тг для вопросов: @kgnn47) <br> ###
### 2. БПИ212 <br> ###

![image](https://user-images.githubusercontent.com/114473740/215325864-8aafd28d-9ce1-4ccb-8e33-45319a293596.png)
________________________

### 3. Пример-if. <br> ###
<br>
```sh
#!/bin/bash
# объявление переменных 
num1=1
num2=10
# секция условия
if [ $num1 -lt $num2 ]
then
# команда, если условие истинно
echo "$num1 is less than $num2"
# команда, если условие ложно
else
echo "$num1 is not less than $num2"
# конец секции
fi
```

________________________

### 4. Пример-while. <br> ###
<br>
```bash
#!/bin/bash
# объявление переменных
i=0
n=10
# начало цикла
while ((i < n)); do
# вывод значения счётчика 
echo "$i"
# увеличение переменной счётчика на 1
i=$((i + 1))
# конец цикла
done
```

________________________

### 5. Пример-function. <br> ###
<br>
```bash
#!/bin/bash
# объявление функции
function factorial {
# начало условной секции
if [ $1 -eq 0 ] || [ $1 -eq 1 ]
then
# выводим 1, если на вход получили 0 или 1
echo 1
else
# используем локальную переменную
local temp=$(( $1 - 1 ))
# получить факториал от переменной (argument - 1)
local result=$(factorial $temp)
echo $(( $result * $1 ))
# конец условной секции
fi
}

# начало основной программы
read -p "Enter value: " x
result=$(factorial $x)
# вывод результата
echo "The factorial of $x is: $result"
```

