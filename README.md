# LED_controller

Это контроллер, основанный на базе ардуино, для управления RGB лентой. Например для подсветки компьютера.
Управление производится с помощью всего одной кнопки. 

Длительное нажатие (3 сек) отключает или включает подсветку.
Короткое включает следующий "режим".

**```Для входа в режим программирования удерживайте кнопку во время включения или перезагрузки.```**


Программируется контроллер через монитор порта с помощю комманд:
- help - отображает список всех доступных комадн (**дальше вы увидете только главные**).

- dir - обзор данных в оперативной памяти.
- new - добавление одной ячейки данных (цвета, яркости, режима работы).
- del - удаление одной ячейки данных (цвета, яркости, режима работы).

- mem_dir - обзор данных во внутренней памяти.
- mem_read - для считывания данных из внутренней памяти в оперативную.
- mem_write - для записи измененных в оперативной памяти данных во внутреннюю (**НЕ ЗАБУДЬ МЕНЯ!**). 

- light_ON - для включения подсветки 
- light_OFF - для выключения подсветки 


## Сам контроллер:
![](https://github.com/TopProHatsker/LED_controller/blob/master/20180427_181451.jpg)
![](https://github.com/TopProHatsker/LED_controller/blob/master/20180427_181514.jpg)
 
## RGB лента:
![](https://github.com/TopProHatsker/LED_controller/blob/master/20180427_181649.jpg)
![]()
