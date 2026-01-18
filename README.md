# uno_project
линкове към изизскванията: 
за проекта
https://docs.google.com/document/d/1iaWMhfIaKd_Tq9C_L0kLRvwc442nyZJCZiZmHrvsoOw/edit?tab=t.0
за предаването
https://docs.google.com/document/d/1yCpn_00QmQigdwqthp-Y0ayEiWbuCC-nMrhBHr03oRs/edit?tab=t.0

# UNO - Console Edition

Конзолна имплементация на популярната карточна игра UNO, разработена като курсов проект по Увод в програмирането.

## Съдържание
1. [Описание](#описание)
2. [Функционалности](#функционалности)
3. [Инсталация и стартиране](#инсталация-и-стартиране)
4. [Как се играе](#как-се-играе)
5. [Правила на играта](#правила-на-играта)
6. [Интерфейс и команди](#интерфейс-и-команди)
7. [Система за запазване](#система-за-запазване)
8. [Структура на проекта](#структура-на-проекта)
9. [Технически детайли](#технически-детайли)
10. [Примери](#примери)
11. [Често задавани въпроси](#често-задавани-въпроси)
12. [Автор и лиценз](#автор-и-лиценз)
## Описание

UNO Console Edition е пълнофункционална имплементация на класическата карточна игра UNO, адаптирана за игра в конзолата. Проектът включва всички стандартни правила на UNO, система за множество играчи, цветна визуализация на картите и напреднала система за запазване и зареждане на игри.

Играта поддържа от 2 до 4 играчи, които играят на един компютър, като всеки играч получава своя ред за действие. Програмата автоматично валидира ходовете, управлява специалните карти и следи за победител.

## Функционалности

### Основни игрови механики

- **Многопотребителска игра**: Поддръжка за 2 до 4 играчи на един компютър
- **Пълно UNO тесте**: 108 карти с всички стандартни типове
- **Автоматична валидация**: Системата проверява дали избраната карта е валидна
- **Разбъркване на тестето**: Използва се модерен random generator за справедливо разбъркване
- **Цветна визуализация**: Всяка карта се показва в своя цвят благодарение на ANSI escape кодове
- **Интуитивен интерфейс**: Ясни менюта и инструкции на всяка стъпка

### Специални карти

Играта поддържа всички стандартни специални карти от UNO:

- **Skip (Прескачане)**: Следващият играч пропуска своя ход
- **Reverse (Обръщане)**: Посоката на играта се обръща (при 2 играчи действа като Skip)
- **+2 (Тегли 2)**: Следващият играч тегли 2 карти и пропуска хода си
- **Wild (Джокер)**: Играчът избира нов активен цвят за играта
- **Wild +4 (Джокер +4)**: Следващият играч тегли 4 карти, пропуска ход, а текущият играч избира цвят

### Напреднала система за запазване

- **3 отделни слота**: Можете да поддържате до 3 различни игри едновременно
- **Информация за слотовете**: При избор на слот виждате детайли за запазената игра
- **Индикация за текущ слот**: Системата показва кой слот е използван за текущата игра
- **Автоматично запазване**: При запазване се съхраняват всички детайли на играта
- **Визуален преглед**: Всеки слот показва брой играчи, текущ играч и горна карта с цвят

### Правило "UNO"

Класическото правило на UNO е напълно имплементирано:

- При оставане с една карта играчът трябва да въведе "uno" (case-insensitive)
- Ако играчът забрави да каже "uno", автоматично тегли 1 наказателна карта
- Ако играчът каже "uno" без да има точно 1 карта, също тегли наказателна карта
- Системата дава обратна връзка за всяко действие

### Автоматично управление на тестето

- **Reshuffling**: Когато тестето свърши, discard купчината се разбърква и става ново тесте
- **Умно разбъркване**: Горната карта остава на мястото си при reshuffling
- **Информация за играча**: Системата уведомява играчите при reshuffling
- **Защита от грешки**: Ако няма карти за разбъркване, играта продължава безопасно

### Интерактивни елементи

- **Плавен преход между играчи**: След всеки ход има съобщение за смяна на играч
- **Визуализация на ръката**: Всички карти в ръката се показват с номера за лесен избор
- **Потвърждение на действия**: При важни действия (като запазване) се иска потвърждение
- **Помощни съобщения**: Програмата винаги дава ясни инструкции какво да правите

## Инсталация и стартиране

### Системни изисквания

- **Операционна система**: Windows (поради използване на `system("CLS")`)
- **Компилатор**: Visual C++ (VC) или GCC
- **Конзола**: Windows Command Prompt или PowerShell с ANSI поддръжка
- **Памет**: Минимум 1MB RAM
- **Дисково пространство**: ~5MB за изпълним файл и save файлове

### Файлове в проекта

Основен файл:

- Изходен код с всички функции и структури

### Стартиране на програмата

1. Компилирайте програмата с Visual C++ или GCC компилатор
2. Стартирайте изпълнимия файл
3. Следвайте инструкциите на екрана

### Първи стъпки

При първо стартиране ще видите:

```
Welcome to Uno tm console edition :D
Do you want to start a new game or continue the game from last time?
(if no previous game exists new game will start)
[0] start new game    [1] continue last game
```

- Изберете `[0]` за нова игра
- Изберете `[1]` за зареждане на запазена игра (ако има такава)

## Как се играе

### Начало на играта

#### Нова игра

1. Изберете `[0] start new game`
2. Въведете брой играчи (между 2 и 4):
    
    ```
    How many players are gonna play the game? (from 2 to 4):
    ```
    
3. Програмата автоматично:
    - Създава и разбърква тестето от 108 карти
    - Раздава по 7 карти на всеки играч
    - Поставя първата карта като начална горна карта
    - Ако началната карта е Wild, се избира цвят автоматично

#### Зареждане на игра

1. Изберете `[1] continue last game`
2. Ще видите списък с наличните save слотове:
    
    ```
    [0] Slot 0: 3 players, Player 1, Top: R 5[1] Slot 1: EMPTY[2] Slot 2: 2 players, Player 0, Top: W +4 (current save file)[3] start new game instead
    ```
    
3. Изберете слот за зареждане или `[3]` за нова игра вместо това
4. Играта се зарежда от точното място, където е била запазена

### Ход на играч

Всеки играч на свой ред вижда екран като този:

```
Current player: 0
Current card: R 5
Your hand:
[0] R 7  [1] G 5  [2] Y 8  [3] W +4  [4] B 2
[5] Draw card
[6] Save game and exit
What do you want to do?
```

#### Опции в хода

1. **Изиграване на карта**: Въведете номера на картата (0-4 в примера)
    
    - Картата трябва да е валидна (същия цвят или стойност, или Wild)
    - Ако картата е невалидна, ще ви помоли да изберете отново
2. **Теглене на карта**: Изберете номера за "Draw card" (5 в примера)
    
    - Автоматично теглите 1 карта от тестето
    - Ако картата е валидна, ще ви попита дали искате да я изиграете
    - Ако не искате или не можете, редът преминава
3. **Запазване и изход**: Изберете номера за "Save game and exit" (6 в примера)
    
    - Ще ви попита за потвърждение
    - След това избирате слот за запазване
    - Играта завършва и можете да продължите по-късно

### Валидни ходове

Карта е валидна за изиграване, ако:

1. **Има същия цвят** като горната карта (R, G, Y, B)
2. **Има същата стойност** като горната карта (0-9, Skip, Reverse, +2)
3. **Е Wild карта** (W или W +4) - винаги валидна
4. **Има цвета на активния Wild** (когато горната карта е Wild с избран цвят)

#### Примери за валидни ходове

Горна карта: `R 5`

- Валидни: `R 7` (същ цвят), `G 5` (съща стойност), `W` (Wild), `W +4` (Wild)
- Невалидни: `B 3`, `G 2`, `Y Skip`

Горна карта: `W` с активен цвят Green

- Валидни: `G 3` (зелен цвят), `G Skip`, `W`, `W +4`
- Невалидни: `R 5`, `B 2`, `Y 7`

### Изиграване на специални карти

#### Skip карта

```
>>> SKIP! Player 2 is skipped! <

```

- Следващият играч автоматично пропуска хода си
- Играта продължава със следващия след него

#### Reverse карта

```
>>> REVERSE! Direction changed! <

```

- Посоката на играта се обръща
- При 2 играчи: действа като Skip
- При 3-4 играчи: следващите ходове са в обратна посока

#### +2 карта

```
>>> DRAW +2! <
Player 2 must draw 2 cards!
Player 2 drew 2 card(s) and skips their turn!

```

- Следващият играч тегли 2 карти автоматично
- Теглените карти се добавят към ръката му
- Играчът пропуска своя ход

#### Wild карта

```
You played a Wild card!
player 0 please choose color for wild card
[0] R 7  [1] G 5  [2] Y 8
Player 0, choose a color for the Wild card:
[0] Red [1] Green [2] Yellow [3] Blue
Your choice:
```

- Избирате нов активен цвят (0-3)
- Избраният цвят става активен за следващите ходове
- Следващият играч трябва да играе карта от този цвят (или друга Wild)

#### Wild +4 карта

```
>>> WILD +4! <
Player 1 must draw 4 cards!
Player 1 drew 4 card(s) and skips their turn!

```

- Първо избирате цвят (същото като Wild)
- След това следващият играч тегли 4 карти
- Играчът пропуска своя ход

### Правило "UNO"

Когато играч изиграе карта и му остане точно 1 карта, вижда:

```
enter Uno, or something else to continue(entering Uno means you are saying it)
```

#### Правилно казване на "UNO"

Ако въведете "uno" (или "UNO", "Uno" - не е case-sensitive):

```
You Said Uno!
You Said Uno Correctly!
No need to draw cards as penalty
```

#### Забравяне да кажете "UNO"

Ако въведете нещо друго или натиснете Enter:

```
You Forgot to say Uno! Draw 1 card as penalty.
Press Enter to continue...
```

#### Грешно казване на "UNO"

Ако кажете "uno" без да имате точно 1 карта:

```
You Said Uno incorrectly!
Draw 1 card as penalty.
```

### Теглене на карти

#### Нормално теглене

```
Drawing a card...
You drew: G 3

```

#### Reshuffling на тестето

Когато тестето свърши:

```
>>> Reshuffling discard pile into draw deck! <

Reshuffled 45 cards back into draw deck!

Drawing a card...
You drew: B Skip

```

#### Изиграване на изтеглена карта

```
Drawing a card...
You drew: R 7

can play R 7 on top card R 5
Do you want to play R 7?
[1] play card   [2/anyting else] don't play card
```

- Въведете `1` за да изиграете картата веднага
- Въведете друго число или натиснете Enter за да запазите картата

### Край на играта

Когато играч остане без карти:

```
====================================
   PLAYER 2 WINS!
   CONGRATULATIONS!
====================================

Press Enter to exit...
```

Играта автоматично завършва и програмата се затваря след натискане на Enter.

### Преход между играчи

След всеки ход има екран за смяна на играчи:

```
give pc to next player: player 1
and press enter...
```

Това дава време на играчите да си предадат компютъра без другите да видят техните карти.

## Правила на играта

### Основни правила

1. **Начало на играта**
    
    - Всеки играч получава 7 карти
    - Една карта се поставя с лице нагоре като начална
    - Играта започва с Играч 0
2. **Ред на играта**
    
    - Играчите играят по ред (0 → 1 → 2 → 3 → 0...)
    - Посоката може да се обърне с Reverse карта
    - Skip картите прескачат играчи
3. **Валидни ходове**
    
    - Трябва да съвпаднете цвят ИЛИ стойност
    - Wild картите винаги са валидни
    - Ако няма валидна карта - теглите от тестето
4. **Победа**
    
    - Печели първият играч, който остане без карти
    - Играта завършва веднага при победител

### Детайлни правила

#### Числови карти (0-9)

- **Брой в тестето**:
    
    - По 1 карта "0" за всеки цвят (4 общо)
    - По 2 карти "1-9" за всеки цвят (72 общо)
- **Как се играят**: Трябва да съвпадат по цвят или число с горната карта
    
- **Ефект**: Обикновена карта, няма специален ефект
    

#### Skip карти

- **Брой в тестето**: По 2 за всеки цвят (8 общо)
    
- **Как се играят**: Трябва да съвпадат по цвят с горната карта, или горната да е Skip
    
- **Ефект**:
    
    - Следващият играч пропуска своя ход
    - Играта продължава със следващия след него
- **Пример**:
    
    ```
    Играч 0 играе R Skip
    Играч 1 пропуска
    Играч 2 продължава
    ```
    

#### Reverse карти

- **Брой в тестето**: По 2 за всеки цвят (8 общо)
    
- **Как се играят**: Трябва да съвпадат по цвят с горната карта, или горната да е Reverse
    
- **Ефект**:
    
    - При 2 играчи: Действа като Skip
    - При 3-4 играчи: Обръща посоката на играта
- **Примери**:
    
    ```
    При 4 играчи, нормална посока: 0 → 1 → 2 → 3 → 0
    Играч 1 играе Reverse
    Нова посока: 1 → 0 → 3 → 2 → 1
    ```
    
    ```
    При 2 играчи: 0 → 1 → 0
    Играч 0 играе Reverse
    Играч 1 пропуска
    Играч 0 играе отново
    ```
    

#### +2 карти

- **Брой в тестето**: По 2 за всеки цвят (8 общо)
    
- **Как се играят**: Трябва да съвпадат по цвят с горната карта, или горната да е +2
    
- **Ефект**:
    
    - Следващият играч тегли 2 карти автоматично
    - След теглене, той пропуска своя ход
    - Не може да играе никоя от теглените карти веднага
- **Пример**:
    
    ```
    Играч 0 играе G +2
    Играч 1 автоматично тегли 2 карти
    Играч 1 пропуска хода си
    Играч 2 продължава
    ```
    

#### Wild карти

- **Брой в тестето**: 4 карти
    
- **Как се играят**: Винаги валидни, могат да се играят върху всяка карта
    
- **Ефект**:
    
    - Играчът избира нов активен цвят (R, G, Y или B)
    - Следващият играч трябва да играе карта от избрания цвят
    - Или друга Wild карта
- **Използване**:
    
    ```
    Играч 0 играе Wild
    Избира Green
    Следващият играч трябва да играе зелена карта или Wild
    ```
    

#### Wild +4 карти

- **Брой в тестето**: 4 карти
    
- **Как се играят**: Винаги валидни, могат да се играят върху всяка карта
    
- **Ефект**:
    
    - Играчът избира нов активен цвят
    - Следващият играч тегли 4 карти автоматично
    - След теглене, той пропуска своя ход
- **Пример**:
    
    ```
    Играч 0 играе Wild +4
    Избира Blue
    Играч 1 тегли 4 карти
    Играч 1 пропуска
    Играч 2 трябва да играе синя карта или Wild
    ```
    

### Правило "UNO"

#### Основно правило

Когато играч има точно 1 карта в ръката си (след изиграване на карта), той ТРЯБВА да каже "UNO".

#### Как се казва

- След изиграване на картата, програмата пита:
    
    ```
    enter Uno, or something else to continue(entering Uno means you are saying it)
    ```
    
- Въведете "uno" (или "UNO", "Uno" - регистърът не е важен)
- Или натиснете Enter / въведете нещо друго за да продължите

#### Наказания

**Забравяне на "UNO"** (имате 1 карта, но не казвате):

- Теглите 1 наказателна карта
- Сега имате 2 карти

**Грешно казване** (казвате "UNO", но имате повече от 1 карта):

- Теглите 1 наказателна карта
- Например: имахте 3 карти, сега имате 4

**Правилно казване** (имате точно 1 карта и казвате "UNO"):

- Няма наказание
- Продължавате с 1 карта
- Ако я изиграете следващия ход - печелите!

### Управление на тестето

#### Начално тесте

- При начало на играта: 108 карти общо
- Раздадени на играчите: 7 × брой играчи
- Първа карта: 1 (става горна карта)
- Оставащи в тестето: 107 - (7 × брой играчи)

Примери:

- 2 играчи: 93 карти в тестето
- 3 играчи: 86 карти в тестето
- 4 играчи: 79 карти в тестето

#### Теглене на карти

Карти се теглят при:

- Доброволно теглене (нямате валидна карта или избирате да теглите)
- +2 наказание (2 карти)
- +4 наказание (4 карти)
- UNO наказание (1 карта)

#### Reshuffling

**Кога се случва**:

- Когато тестето е празно (currentDrawDeckId >= MAX_DECK_SIZE)
- И някой се опита да тегли карта

**Какво се случва**:

1. Горната карта остава на мястото си
2. Всички останали карти от discard купчината се вземат
3. Тези карти се разбъркват
4. Разбърканите карти стават новото тесте
5. Теглената карта се взема от новото тесте

**Пример**:

```
>>> Reshuffling discard pile into draw deck! <

Reshuffled 45 cards back into draw deck!

Drawing a card...
You drew: Y 3
```

**Специален случай** - Само горна карта в discard:

```
>>> Cannot reshuffle - only top card in discard pile. <
>>> Continuing without reshuffling... <
```

(Теоретично не трябва да се случва в нормална игра)

## Интерфейс и команди

### Главно меню

```
Welcome to Uno tm console edition :D
Do you want to start a new game or continue the game from last time?
(if no previous game exists new game will start)
[0] start new game    [1] continue last game
```

**Команди**:

- `0` - Стартира нова игра
- `1` - Зарежда запазена игра

### Избор на брой играчи

```
How many players are gonna play the game? (from 2 to 4):
```

**Валиден вход**: Число между 2 и 4

**Невалиден вход**: Програмата ще ви помоли да въведете отново

### Игрови екран

```
Current player: 0
Current card: R 5
Your hand:
[0] R 7  [1] G 5  [2] Y 8  [3] W +4  [4] B 2
[5] Draw card
[6] Save game and exit
What do you want to do?
```

**Елементи на екрана**:

- **Current player**: Номерът на текущия играч (0, 1, 2, 3)
- **Current card**: Горната карта с цвят и стойност
- **Your hand**: Всички ваши карти с номера за избор
- **Draw card**: Опция за теглене на карта
- **Save game and exit**: Опция за запазване

**Валиден вход**:

- Число от 0 до броя на опциите (включително)
- Програмата валидира входа автоматично

### Избор на цвят за Wild

```
player 0 please choose color for wild card
[0] R 7  [1] G 5
Player 0, choose a color for the Wild card:
[0] Red [1] Green [2] Yellow [3] Blue
Your choice:
```

**Команди**:

- `0` - Червен (Red)
- `1` - Зелен (Green)
- `2` - Жълт (Yellow)
- `3` - Син (Blue)

### Изиграване на изтеглена карта

```
can play R 7 on top card R 5
Do you want to play R 7?
[1] play card   [2/anyting else] don't play card
```

**Команди**:

- `1` - Играй картата веднага
- Всяко друго число или Enter - Запази картата

### Казване на UNO

```
enter Uno, or something else to continue(entering Uno means you are saying it)
```

**Валиден вход**:

- `uno`, `UNO`, `Uno`, `uNo` и т.н. - Казвате UNO
- Всичко друго или Enter - Не казвате UNO

### Меню за запазване

```
Choose a save file:
[0] Slot 0: 3 players, Player 1, Top: R 5
[1] Slot 1: EMPTY
[2] Slot 2: 2 players, Player 0, Top: W +4 (current save file)
[3] exit game without saving
```

**Команди**:

- `0`, `1`, `2` - Избор на слот за запазване
- `3` - Изход без запазване

**Индикатори**:

- `EMPTY` - Празен слот
- `(current save file)` - Текущо използваният слот
- Информация за играта: Брой играчи, текущ играч, горна карта с цвят

### Съобщения за грешки

**Невалиден вход**:

```
Invalid input! Please enter a number.
```

**Невалиден избор**:

```
Invalid choice! Please choose between 0 and 5
```

**Невалидна карта**:

```
Invalid choice - you cannot play this card!
```

**Невъзможно изиграване на изтеглена карта**:

```
can't play G 3 on top card R 5
```

## Система за запазване

### Файлове за запазване

Програмата използва 3 отделни файла:

1. `UnoSaveState.txt` - Слот 0
2. `UnoSaveState2.txt` - Слот 1
3. `UnoSaveState3.txt` - Слот 2

### Структура на save файла

Файловете са в текстов формат със следната структура:

```
[Брой играчи]
[Текущ играч ID]
[Посока на играта: 1 или -1]
[Активен Wild цвят или '-']

[Размер на ръката на играч 0]
[Цвят на карта 1]
[Стойност на карта 1 или '-']
[Цвят на карта 2]
[Стойност на карта 2 или '-']
...

[Размер на ръката на играч 1]
...

[ID на текуща позиция в draw deck]
[Цвят на оставаща карта 1]
[Стойност на оставаща карта 1]
...

[ID на горна карта в discard deck]
[Цвят на карта 1 в discard]
[Стойност на карта 1 в discard]
...
[Цвят на горна карта]
[Стойност на горна карта]
```

### Пример за save файл

```
3
1
1
G

7
R
5
G
3
B
Skip
W
+4
Y
7
R
Reverse
G
9

5
B
2
R
8
G
Skip
Y
4
W
-

6
R
7
G
5
B
3
Y
6
W
+4
R
9

85
R
0
G
0
B
0
...

3
R
3
G
7
B
Skip
R
5
```

**Обяснение**:

- 3 играчи в играта
- Текущият играч е Играч 1
- Посоката е нормална (1)
- Активният Wild цвят е зелен (G)
- Играч 0 има 7 карти (R 5, G 3, B Skip, W +4, Y 7, R Reverse, G 9)
- Играч 1 има 5 карти
- Играч 2 има 6 карти
- Draw deck започва от позиция 85 (малко карти останали)
- Discard deck има 3 карти под горната
- Горната карта е R 5

### Запазване на игра

**Процес**:

1. По време на своя ход изберете опцията за запазване
    
    ```
    [6] Save game and exit
    ```
    
2. Потвърдете избора
    
    ```
    Are you sure?
    [0] Save game and exit [1] Continue current game:
    ```
    
3. Изберете слот за запазване
    
    ```
    Choose a save file:
    [0] Slot 0: EMPTY
    [1] Slot 1: 3 players, Player 2, Top: B +2
    [2] Slot 2: EMPTY
    [3] exit game without saving
    ```
    
4. Играта се запазва

```
Game saved successfully.
```

5. Програмата завършва

**Важно**:

- Можете да презапишете съществуващи слотове
- Текущо използваният слот е маркиран с "(current save file)"
- Ако изберете `[3]`, играта завършва БЕЗ запазване

### Зареждане на игра

**Процес**:

1. При стартиране изберете `[1] continue last game`
    
2. Изберете слот за зареждане
    
    ```
    [0] Slot 0: 2 players, Player 1, Top: G Skip
    [1] Slot 1: EMPTY
    [2] Slot 2: 4 players, Player 3, Top: W +4
    [3] start new game instead
    ```
    
3. Играта се зарежда
    
    ```
    Game loaded successfully.
    ```
    
4. Продължавате от точното място, където сте спрели
    

**Важно**:

- Не можете да заредите празен слот
- Ако изберете `[3]`, започва нова игра
- Всички детайли се запазват: ръце, тесте, текущ играч, посока, активен цвят

### Информация за слотовете

Всеки слот показва:

**Празен слот**:

```
[1] Slot 1: EMPTY
```

**Запазена игра**:

```
[0] Slot 0: 3 players, Player 1, Top: R 5
```

- **3 players** - Брой играчи в играта
- **Player 1** - Кой играч е на ход
- **Top: R 5** - Горната карта с цвят (червена 5)

**Текущ слот**:

```
[2] Slot 2: 2 players, Player 0, Top: W +4 (current save file)
```

- **(current save file)** - Това е слотът на текущата игра

## Структура на проекта

### Основни структури

#### `struct card`

Представя една карта от UNO.

```cpp
struct card {
    char color;              // Цвят: 'R', 'G', 'Y', 'B', 'W'
    char value[10];          // Стойност: "0"-"9", "Skip", "Reverse", "+2", "+4", ""
    char text[20];           // Визуален текст: "R 5", "W +4" и т.н.
};
```

**Полета**:

- `color`: Цветът на картата (R/G/Y/B за обикновени, W за Wild)
- `value`: Стойността като низ (празна за обикновени Wild карти)
- `text`: Форматиран текст за показване (генерира се автоматично)

**Примери**:

```cpp
// Червена 5
card c1 = {'R', "5", "R 5"};

// Wild +4
card c2 = {'W', "+4", "W +4"};

// Обикновен Wild
card c3 = {'W', "", "W"};

// Зелен Skip
card c4 = {'G', "Skip", "G Skip"};
```

#### `struct player`

Представя един играч и неговата ръка.

```cpp
struct player {
    struct card hand[108];   // Картите в ръката
    int handSize;            // Брой карти в ръката
};
```

**Полета**:

- `hand`: Масив с всички карти на играча (макс 108)
- `handSize`: Текущ брой карти в ръката (започва от 7)

**Пример**:

```cpp
player p;
p.handSize = 7;  // Играчът има 7 карти
p.hand[0] = {'R', "5", "R 5"};
p.hand[1] = {'G', "Skip", "G Skip"};
// ...
```

#### `struct savestate`

Представя цялото състояние на играта.

```cpp
struct savestate {
    struct card discardDeck[108];     // Discard купчина
    struct card drawDeck[108];        // Тесте за теглене
    struct player players[4];         // Всички играчи
    char activeWildColor;             // Активен Wild цвят или '\0'
    int currentDrawDeckId;            // Позиция в draw deck
    int topDiscardDeckId;             // Позиция на горна карта
    int numberOfPlayers;              // Брой играчи (2-4)
    int currentPlayerId;              // Текущ играч (0-3)
    int playerOrder;                  // Посока: 1 или -1
    int currentSaveFileId;            // ID на save файл или -1
};
```

**Полета**:

- `discardDeck`: Купчината с изхвърлени карти
- `drawDeck`: Тестето за теглене
- `players`: Масив с всички играчи
- `activeWildColor`: Активен цвят когато има Wild карта ('R', 'G', 'Y', 'B' или '\0')
- `currentDrawDeckId`: Индекс на следващата карта за теглене
- `topDiscardDeckId`: Индекс на горната карта в discard
- `numberOfPlayers`: Общ брой играчи
- `currentPlayerId`: Кой играч е на ход
- `playerOrder`: 1 за нормална посока, -1 за обратна
- `currentSaveFileId`: Кой save файл се използва (-1 ако няма)

#### `struct SaveFileInfo`

Информация за един save slot (за показване).

```cpp
struct SaveFileInfo {
    bool exists;              // Файлът съществува ли
    bool isEmpty;             // Файлът празен ли е
    int numPlayers;           // Брой играчи
    int currentPlayer;        // Текущ играч
    card topCard;             // Горна карта
    char activeColor;         // Активен цвят
};
```

### Основни функции

#### Инициализация и игрови цикъл

**`int main()`**

- Инициализира random generator
- Създава структурата savestate
- Извиква GameBegining()
- Стартира главния игрови цикъл

**`int GameLoop(savestate& unoSavestate, std::mt19937& gen)`**

- Основен безкраен цикъл на играта
- Извиква GameFlow() за всеки ход
- Показва съобщение за смяна на играч
- Връща код при излизане

**`void GameBegining(int& userAnswer, savestate& unoSavestate, std::mt19937& gen)`**

- Показва начално меню
- Обработва избора за нова/продължаване на игра
- Извиква StartNewGame() или LoadGameFromFile()

**`void StartNewGame(savestate& uss, std::mt19937& gen)`**

- Пита за брой играчи
- Създава и разбърква тестето
- Раздава карти на играчите
- Обработва специално случая с Wild начална карта

**`bool LoadGameFromFile(savestate& uss)`**

- Показва меню за избор на save slot
- Зарежда данните от избрания файл
- Валидира и парсва save файла
- Връща true при успех, false при грешка

#### Управление на хода

**`int GameFlow(savestate& uss, int& userAnswer, bool& retFlag, std::mt19937& gen)`**

- Извършва един пълен ход на играч
- Показва екрана за избор
- Обработва теглене, запазване или изиграване на карта
- Управлява UNO правилото

**`void ChooseActionToPlay(savestate& uss, int& userAnswer, const card& currentCard)`**

- Показва опциите на играча
- Чете и валидира избора
- Повтаря при невалиден вход

**`void PlayAction(int& userAnswer, savestate& uss, bool& isValidOption, const card& currentCard)`**

- Проверява дали избраното действие е валидно
- За карти: проверява дали могат да се играят
- За теглене/запазване: маркира като валидно

**`void PlayCard(int cardIndex, player& currentPlayer, std::mt19937& gen, savestate& uss)`**

- Изиграва избраната карта
- Премества картата в discard deck
- Премахва от ръката на играча
- Обработва Wild избор на цвят
- Проверява за победител
- Прилага специални ефекти

**`void MoveToNextPlayer(savestate& uss)`**

- Преминава към следващия играч
- Взима предвид посоката (playerOrder)
- Използва modulo за циклично преминаване

#### Специални карти

**`void SkipCardAction(savestate& uss)`**

- Показва съобщение за Skip
- Извиква MoveToNextPlayer() два пъти

**`void ReverseCardAction(savestate& uss)`**

- Обръща playerOrder (× -1)
- При 2 играчи: действа като Skip
- При 3-4 играчи: само обръща посоката

**`void Draw2CardAction(std::mt19937& gen, savestate& uss)`**

- Преминава към следващия играч
- Тегли 2 карти на този играч
- Прескача играча (втори MoveToNextPlayer)

**`void Draw4CardAction(std::mt19937& gen, savestate& uss)`**

- Преминава към следващия играч
- Тегли 4 карти на този играч
- Прескача играча

**`char ChooseColorForWild(savestate& uss)`**

- Показва менюто за избор на цвят
- Чете и валидира избора (0-3)
- Връща избрания цвят ('R', 'G', 'Y', 'B')

#### Теглене на карти

**`void DrawCard(savestate& uss, int prevUserId, std::mt19937& gen)`**

- Тегли 1 карта за играч
- Проверява дали тестето е празно
- При нужда извиква ReshuffleDiscardPile()
- Добавя картата в ръката на играча

**`int DrawMultipleCards(int playerId, int numCards, std::mt19937& gen, savestate& uss)`**

- Тегли няколко карти наведнъж
- Използва се за +2 и +4 ефекти
- Връща броя реално изтеглени карти
- Обработва празно тесте

**`void ReshuffleDiscardPile(savestate& uss, std::mt19937& gen)`**

- Взема всички карти от discard освен горната
- Разбърква ги
- Добавя ги към draw deck
- Показва информационно съобщение

#### Валидация и проверки

**`bool CheckIfPlayerCanPlayCard(char activeWildColor, card currentCard, card playerCard)`**

- Проверява дали картата може да се играе
- Сравнява цветове и стойности
- Обработва Wild и активен Wild цвят
- Връща true ако е валидна

**`void CheckIfPlayerIsWinner(player& currentPlayer, int currentPlayerId)`**

- Проверява дали играчът е останал без карти
- При победа: показва съобщение и завършва програмата

**`void SaveGameConsoleText(int& userAnswer, player& currentPlayer, bool& isValidOption)`**

- Пита за потвърждение за запазване
- Актуализира userAnswer според избора

**`void SayUnoAction(int currPlayerIdBeforePlay, std::mt19937& gen, savestate& uss)`**

- Чете входа за UNO
- Проверява дали играчът има точно 1 карта
- Прилага наказания според правилата

#### Тесте и карти

**`void FillUnoDeck(card drawDeck[108])`**

- Създава пълно UNO тесте от 108 карти
- Числови карти: 0-9 за всеки цвят
- Специални карти: Skip, Reverse, +2 за всеки цвят
- Wild карти: 4× Wild и 4× Wild +4

**`void ShuffleDeck(card drawDeck[], int arrSize, std::mt19937& gen)`**

- Разбърква масив с карти
- Използва std::shuffle с mt19937 генератор

**`void FillPlayersHands(player players[], int numberOfPlayers, card drawDeck[], int currentDrawDeckId)`**

- Раздава по 7 карти на всеки играч
- Взема карти от началото на тестето
- Актуализира currentDrawDeckId

**`void BuildCardText(card& c)`**

- Генерира визуален текст за картата
- Формат: "R 5", "W +4", "B Skip" и т.н.
- Обработва специално Wild без стойност

#### Запазване и зареждане

**`void SaveGameInFile(savestate& uss, char filename[])`**

- Отваря файл за запис
- Записва всички данни на играта
- Използва специален формат (вж. Система за запазване)
- Показва съобщение при успех

**`void ChooseSaveFIleForSaveGame(savestate uss)`**

- Показва менюто за избор на save slot
- Извиква chooseSaveFile()
- При избор: извиква SaveGameInFile()

**`int chooseSaveFile(char textForCancel[], int currentSaveFileId)`**

- Показва информация за всички слотове
- Маркира текущия слот
- Връща избрания слот или брой слотове за отказ

**`SaveFileInfo GetSaveFileInfo(const char* filename)`**

- Чете информация от save файл
- Парсва първите редове за детайли
- Връща структура със информация

**`void DisplaySaveSlot(int slotNumber, const SaveFileInfo& info, bool isCurrentSaveFile)`**

- Показва информация за един слот
- Форматира визуално: номер, играчи, текущ играч, горна карта
- Маркира текущия слот

#### Помощни функции

**`void DisplayCurrentPlayerHand(player& currentPlayer)`**

- Показва всички карти в ръката с номера
- Използва цветна визуализация

**`void ColorInCard(card currentCard, char activeWildColor)`**

- Показва картата в нейния цвят
- Обработва Wild с активен цвят
- Използва ANSI escape кодове

**`void PlayDrawnCard(const card& drawnCard, int& userAnswer, std::mt19937& gen, savestate& uss)`**

- Обработва изиграването на току-що изтеглена карта
- Пита играча дали иска да я играе
- Изиграва картата при избор

**`bool ReadIntFromConsole(int& outValue)`**

- Чете число от конзолата
- Валидира че входът е само цифри
- Връща true при успех, false при невалиден вход

**`int ReadValidInteger(const char* prompt, int minValue, int maxValue)`**

- Показва prompt и чете число
- Повтаря докато не получи валидно число в диапазона
- Връща валидното число

**`bool ReadValidIntegerWhileCycle(int minValue, int maxValue, int& value)`**

- Помощна функция за ReadValidInteger
- Прави една итерация на четене и валидация

#### Низови операции

**`bool CharEquals(const char a[], const char b[], int size)`**

- Сравнява два низа до определена дължина
- Връща true ако са еднакви

**`char ToLower(char c)`**

- Преобразува символ към малка буква
- Използва се за case-insensitive сравнения

**`bool EqualsIgnoreCase(const char* a, const char* b)`**

- Сравнява два низа без значение на регистъра
- Използва се за "UNO" проверка

**`void MyStrCopy(const char src[], char dest[])`**

- Копира един низ в друг
- Ръчна имплементация на strcpy

#### Визуализация

**`void ClearConsole()`**

- Изчиства екрана
- Използва `system("CLS")` за Windows

**`void SetConsoleColor(int textColor)`**

- Задава цвят на текста с ANSI код

**`void ResetConsoleColor()`**

- Връща цвета на текста към нормалния

**`void PrintTextInColor(const char text[], int color)`**

- Показва текст в определен цвят
- След това връща нормалния цвят

## Технически детайли

### Константи

#### Размери на масиви

```cpp
const int MAX_CHAR_ARRAY_SIZE = 1000;  // Макс размер на низове
const int MAX_VALUE_LENGTH = 10;       // Макс дължина на стойност на карта
const int MAX_TEXT_LENGTH = 20;        // Макс дължина на визуален текст
const int MAX_DECK_SIZE = 108;         // Брой карти в тестето
const int MAX_PLAYERS = 4;             // Максимален брой играчи
```

#### Игрови константи

```cpp
const int ZERO_NUMBER_CARD = 0;              // Най-малка числова карта
const int LAST_NUMBER_CARD = 9;              // Най-голяма числова карта
const int STARTING_NUMBER_OF_CARDS = 7;      // Начален брой карти
const int SKIP_STRING_SIZE = 5;              // Дължина на "Skip"
const int REVERSE_STRING_SIZE = 8;           // Дължина на "Reverse"
const int PLUS_2_STRING_SIZE = 3;            // Дължина на "+2"
const int PLUS_4_STRING_SIZE = 3;            // Дължина на "+4"
```

#### Цветове

```cpp
const char COLORS[] = {'R', 'G', 'Y', 'B'};  // Основни цветове
const int COLORS_SIZE = 4;                    // Брой цветове
const char WILD_COLOR = 'W';                  // Wild карти

// ANSI кодове
const int RED_COLOR_CODE = 91;
const int GREEN_COLOR_CODE = 92;
const int YELLOW_COLOR_CODE = 93;
const int BLUE_COLOR_CODE = 94;
const int MAGENTA_COLOR_CODE = 95;  // За Wild
const int WILD_COLOR_CODE = MAGENTA_COLOR_CODE;

const int COLOR_CODES[] = {
    RED_COLOR_CODE,
    GREEN_COLOR_CODE,
    YELLOW_COLOR_CODE,
    BLUE_COLOR_CODE
};
```

#### Файлове

```cpp
const char FILENAME_1[] = "UnoSaveState.txt";
const char FILENAME_2[] = "UnoSaveState2.txt";
const char FILENAME_3[] = "UnoSaveState3.txt";
const int numberOfSaveFiles = 3;

const char* SAVEFILE_NAMES[] = {
    FILENAME_1,
    FILENAME_2,
    FILENAME_3
};
```

#### Други

```cpp
const char UNO_STR[] = "uno";  // Текст за UNO правило
```

### Използвани библиотеки

```cpp
#include <iostream>   // Вход/изход
#include <algorithm>  // std::shuffle
#include <random>     // std::mt19937, std::random_device
#include <fstream>    // Файлове
```

**Забележка**: Използването на `<algorithm>` и `<random>` е изрично разрешено в условието за проект №4.

### Структура на тестето

#### Числови карти (80 карти)

За всеки от 4-те цвята (R, G, Y, B):

- **1× карта "0"** (4 общо за всички цветове)
- **2× карти "1"** (8 общо)
- **2× карти "2"** (8 общо)
- ...
- **2× карти "9"** (8 общо)

**Общо**: 1×4 + 9×2×4 = 4 + 72 = 76 + 4 = 80 карти

#### Специални карти (28 карти)

За всеки от 4-те цвята:

- **2× Skip** (8 общо)
- **2× Reverse** (8 общо)
- **2× +2** (8 общо)

**Общо**: 3×2×4 = 24 карти

#### Wild карти (8 карти)

- **4× Wild** (обикновен Wild)
- **4× Wild +4**

**Общо**: 8 карти

#### Общо карти

80 + 24 + 8 = **108 карти**

### ANSI Escape кодове

Програмата използва ANSI escape кодове за цветен текст:

```
\033[91m - Червен
\033[92m - Зелен
\033[93m - Жълт
\033[94m - Син
\033[95m - Magenta (за Wild)
\033[0m  - Reset (връща нормалния цвят)
```

**Съвместимост**:

- Windows 10+ Command Prompt: Поддържа ANSI escape кодове
- Windows Terminal: Пълна поддръжка
- PowerShell: Пълна поддръжка
- Стари Windows конзоли: Може да не поддържат (ще се виждат странни символи)

### Random генератор

```cpp
std::random_device rd;
unsigned int seed = rd();
std::mt19937 gen(seed);
```

- **std::random_device**: Истински произволен източник (hardware-based)
- **std::mt19937**: Mersenne Twister псевдо-случаен генератор
- Използва се за разбъркване на тестето

### Управление на паметта

- **Няма динамична памет**: Всички структури са статични масиви
- **Няма утечки**: Не се използва new/delete
- **Файлове**: Всички файлове се затварят коректно с `.close()` или автоматично при излизане от scope

## Примери

### Пример 1: Цяла игра за 2 играчи

```
Welcome to Uno tm console edition :D
Do you want to start a new game or continue the game from last time?
(if no previous game exists new game will start)
[0] start new game    [1] continue last game
> 0

starting new game : D
How many players are gonna play the game? (from 2 to 4): 2

give pc to next player: player 0
and press enter...

--- Ход 1: Играч 0 ---

Current player: 0
Current card: R 5
Your hand:
[0] R 7  [1] G 3  [2] Y 8  [3] B 2  [4] W  [5] G Skip  [6] R Reverse
[7] Draw card
[8] Save game and exit
What do you want to do?
> 1

enter Uno, or something else to continue(entering Uno means you are saying it)
> 

give pc to next player: player 1
and press enter...

--- Ход 2: Играч 1 ---

Current player: 1
Current card: G 3
Your hand:
[0] R 5  [1] B 4  [2] G 7  [3] Y Skip  [4] W +4  [5] R +2  [6] B Reverse
[6] Draw card
[7] Save game and exit
What do you want to do?
> 2

enter Uno, or something else to continue(entering Uno means you are saying it)
> 

give pc to next player: player 0
and press enter...

--- Ход 3: Играч 0 ---

Current player: 0
Current card: G 7
Your hand:
[0] R 7  [1] Y 8  [2] B 2  [3] W  [4] G Skip  [5] R Reverse
[6] Draw card
[7] Save game and exit
What do you want to do?
> 0

enter Uno, or something else to continue(entering Uno means you are saying it)
> 

give pc to next player: player 1
and press enter...

--- Играч 0 играе R 7, Играч 1 тегли... ---

[Игра продължава]

--- Играч 0 играе последната си карта ---

Current player: 0
Current card: Y 8
Your hand:
[0] Y 3
[1] Draw card
[2] Save game and exit
What do you want to do?
> 0

enter Uno, or something else to continue(entering Uno means you are saying it)
> uno

You Said Uno!
You Said Uno Correctly!
No need to draw cards as penalty
Press Enter to continue...

====================================
   PLAYER 0 WINS!
   CONGRATULATIONS!
====================================

Press Enter to exit...
```

### Пример 2: Запазване и зареждане

**Запазване**:

```
Current player: 2
Current card: B Skip
Your hand:
[0] B 5  [1] R 3  [2] G Skip  [3] W +4
[4] Draw card
[5] Save game and exit
What do you want to do?
> 5

Are you sure?
[0] Save game and exit [1] Continue current game: 0

Choose a save file:
[0] Slot 0: 2 players, Player 1, Top: R 7
[1] Slot 1: EMPTY
[2] Slot 2: 3 players, Player 2, Top: G 5 (current save file)
[3] exit game without saving
> 1

Game saved successfully.
```

**Зареждане**:

```
Welcome to Uno tm console edition :D
Do you want to start a new game or continue the game from last time?
(if no previous game exists new game will start)
[0] start new game    [1] continue last game
> 1

[0] Slot 0: 2 players, Player 1, Top: R 7
[1] Slot 1: 3 players, Player 2, Top: B Skip
[2] Slot 2: 3 players, Player 2, Top: G 5
[3] start new game instead
> 1

Game loaded successfully.
Loading successful

give pc to next player: player 2
and press enter...

Current player: 2
Current card: B Skip
Your hand:
[0] B 5  [1] R 3  [2] G Skip  [3] W +4
[4] Draw card
[5] Save game and exit
What do you want to do?
```

### Пример 3: Специални карти

**Reverse в игра с 4 играчи**:

```
--- Нормална посока: 0 → 1 → 2 → 3 → 0 ---

Current player: 1
Current card: G 5
Your hand:
[0] G Reverse  [1] B 3
[2] Draw card
[3] Save game and exit
What do you want to do?
> 0

>>> REVERSE! Direction changed! <

enter Uno, or something else to continue(entering Uno means you are saying it)
> 

give pc to next player: player 0
and press enter...

--- Обратна посока: 1 → 0 → 3 → 2 → 1 ---

Current player: 0
...
```

**Wild +4**:

```
Current player: 3
Current card: R 5
Your hand:
[0] W +4  [1] B 2
[2] Draw card
[3] Save game and exit
What do you want to do?
> 0

You played a Wild card!
player 3 please choose color for wild card
[0] B 2
Player 3, choose a color for the Wild card:
[0] Red [1] Green [2] Yellow [3] Blue
Your choice: 1

>>> WILD +4! <
Player 0 must draw 4 cards!
Player 0 drew 4 card(s) and skips their turn!

enter Uno, or something else to continue(entering Uno means you are saying it)
> uno

You Said Uno!
Press Enter to continue...

give pc to next player: player 1
and press enter...

--- Играч 0 е прескочен, Играч 1 продължава ---

Current player: 1
Current card: W +4  (показва се в зелено)
...
```

### Пример 4: UNO правило

**Правилно казване**:

```
Current player: 0
Current card: R 5
Your hand:
[0] R 7  [1] G 3
[2] Draw card
[3] Save game and exit
What do you want to do?
> 0

enter Uno, or something else to continue(entering Uno means you are saying it)
> UNO

You Said Uno!
You Said Uno Correctly!
No need to draw cards as penalty
Press Enter to continue...
```

**Забравяне**:

```
Current player: 0
Current card: R 5
Your hand:
[0] R 7  [1] G 3
[2] Draw card
[3] Save game and exit
What do you want to do?
> 0

enter Uno, or something else to continue(entering Uno means you are saying it)
> 

You Forgot to say Uno! Draw 1 card as penalty.
Press Enter to continue...

give pc to next player: player 1
and press enter...
```

**Грешно казване**:

```
Current player: 0
Current card: R 5
Your hand:
[0] R 7  [1] G 3  [2] B 2
[3] Draw card
[4] Save game and exit
What do you want to do?
> 0

enter Uno, or something else to continue(entering Uno means you are saying it)
>

uno

You Said Uno! You Said Uno incorrectly! Draw 1 card as penalty. current player: 0 currPlayerIdBeforePlay: 0 Press Enter to continue...

```

### Пример 5: Reshuffling

```

Drawing a card...

> > > Reshuffling discard pile into draw deck! <

Reshuffled 67 cards back into draw deck!

You drew: Y 3

can play Y 3 on top card R 5 Do you want to play Y 3? [1] play card [2/anyting else] don't play card

> 2

Keeping the card. Press Enter to continue...

give pc to next player: player 1 and press enter...

```

## Често задавани въпроси

### Игрови правила

**В: Мога ли да играя няколко карти наведнъж?**

О: Не, само една карта на ход.

**В: Какво се случва ако тестето свърши?**

О: Discard купчината (без горната карта) се разбърква и става ново тесте.

**В: Мога ли да откажа да играя валидна карта?**

О: Да, можете да изберете "Draw card" дори ако имате валидна карта.

**В: Какво се случва ако изтегля валидна карта?**

О: Програмата ви пита дали искате да я изиграете веднага. Можете да откажете.

**В: Как работи Reverse при 2 играчи?**

О: При 2 играчи Reverse действа като Skip - следващият играч пропуска хода си.

**В: Мога ли да си променя избора на цвят за Wild?**

О: Не, след като изберете цвят, той остава до следващата карта.

**В: Какво се случва ако и двамата играчи нямат валидни карти?**

О: Всеки тегли по една карта на свой ход до получаване на валидна.

### Запазване и зареждане

**В: Колко игри мога да запазя?**

О: До 3 игри едновременно (в 3 отделни слота).

**В: Мога ли да презапиша запазена игра?**

О: Да, просто изберете същия слот при запазване.

**В: Запазва ли се автоматично?**

О: Не, трябва ръчно да изберете "Save game and exit".

**В: Мога ли да продължа запазена игра след време?**

О: Да, при старт изберете "continue last game" и изберете слота.

**В: Какво се случва ако зареждането не успее?**

О: Програмата показва съобщение и предлага да започнете нова игра.

### Технически въпроси

**В: Защо картите не се показват в цвят?**

О: Вашата конзола може да не поддържа ANSI escape кодове. Използвайте Windows Terminal или PowerShell.

**В: Работи ли на Mac/Linux?**

О: Не директно - използва се `system("CLS")` което е Windows-specific. Може да смените с `system("clear")` за Unix системи.

**В: Мога ли да играя с повече от 4 играчи?**

О: Не, програмата поддържа максимум 4 играчи.

**В: Защо понякога виждам странни символи в конзолата?**

О: Вероятно конзолата не поддържа ANSI кодове. Опитайте друга конзола.

### Грешки и проблеми

**В: Програмата казва "Invalid input" при число?**

О: Въвеждате невалидно число или символи. Въведете само числото на опцията.

**В: Не мога да играя никоя карта**?

О: Проверете дали картата отговаря на горната по цвят или стойност. Wild картите винаги са валидни.

**В: Програмата "зацикли" при reshuffling?**

О: Това не трябва да се случва - reshuffling винаги трябва да има карти за разбъркване. Ако се случи, моля репортвайте като bug.

**В: Забравих да кажа UNO и загубих?**

О: UNO наказанието е само 1 карта, не загубвате играта. Опитайте пак на следващия ход.

## Автор и лиценз

### Автор

**Стилиян Миленов Матев**  
Факултетен номер: 7MI0600671  
СУ "Св. Климент Охридски", Факултет по Математика и Информатика  
Специалност "Софтуерно Инженерство"  
Зимен семестър 2025/2026

### Курсов проект

Проект №4 - Игра "UNO"  
Курс: Увод в програмирането (практикум)  
Компилатор: Visual C++ (VC)

### Контакти

За въпроси, предложения или проблеми свързани с проекта, моля свържете се чрез:
- Moodle платформата на курса
- Email на университета

### Благодарности

Благодаря на:
- Преподавателите по Увод в програмирането за ясните изисквания и подкрепа
- Създателите на UNO за оригиналната игра
- Всички, които тестваха програмата

---

**Последна актуализация**: Януари 2026  
**Версия**: 1.0  
**Статус**: Завършен курсов проект
