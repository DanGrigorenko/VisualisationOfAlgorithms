# Курсовая работа "_Визуализация алгоритмов и структур данных_"

## Описание
Это desktop приложения под ОС Linux Ubuntu 20.04 и выше. Целью курсового проекта было передать как можно точно и детально, анимацию работы алгоритма или структуры данных. Вдохнавлением для создания данного приложения, послужил сайт [visualgo](https://visualgo.net/en).
___

## Инструменты
+ С++ 17
+ Qt/QT Creator
+ Standard Template Library (STL)
+ Figma
___

## Функционал приложения
При входе в приложение пользователю доступны 4 категории:

### Алгоритмы
1. Сортировки (__Bubble, Selection, Insertion, Shaker__)
2. Графы (Нахождение кратчайшего пути по алгоритму __Дейкстры__)
### Структуры данных
3. Односвязный список (__Односвязный список, Стек__)
4. Хеш-таблица (__Линейное, Квадротичное зондирование__)
___

## Запуск 

Для запуска приложения необходимо иметь ОС Linux Ubuntu 20.04 и выше, а также установленный Qt Creator с версией Qt 5 и выше.
___
## Пример реализации QGraphicsScene
Для управления большим числом графических 2D элементов использовался класс ``QGraphicsScene``.


 Фрагмент кода, создания сцены.

```c++
QGraphicsScene *scene = new QGraphicsScene(this);;
scene->setItemIndexMethod(QGraphicsScene::NoIndex);
scene->setSceneRect(-300, -300, 600, 600);
setScene(scene);
setCacheMode(CacheBackground);
setViewportUpdateMode(BoundingRectViewportUpdate);
setRenderHint(QPainter::Antialiasing);
setTransformationAnchor(AnchorUnderMouse);
setMinimumSize(400, 400);
```






