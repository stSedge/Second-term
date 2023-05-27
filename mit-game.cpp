// Задание EnemyAI.
//
// Данная функция реализует искусственный интеллект для врагов в игровой сцене.
//
// Реализация достаточно свободная. Мы предлагаем следующее: противник будет
// преследовать игрока.
//
// Внутри функции определяется объект игрока путем вызова функции find_player,
// которая возвращает указатель на объект игрока в сцене.
//
// Затем функция должна вычислить разницу между позицией противника и позицией
// игрока, чтобы понять, в каком направлении нужно двигаться. Значение
// перемещения move вычисляется, умножая скорость движения врага на время,
// прошедшее с последнего кадра.
//
// Затем функция изменяет позицию врага, добавляя или вычитая значение move из
// его текущей позиции в зависимости от того, находится ли противник слева или
// справа от игрока.
//
// Рекомендуемые функции для выполнения задания:
// - find_player
//
// При выполнении этого задания у вас есть возможность добавить свою текстуру
// противника Assets/enemy1.png
//
// Возможное решение может занимать примерно 16-20 строк.
// Ваше решение может сильно отличаться.
//
void EnemyAI(Object &enemy, Scene &scene, float dt)
{
	Object &player = *find_player(scene);
    	float dx = player.position.x - enemy.position.x;
    	float move = enemy.enemy.speed * dt;
    	if (dx > 0) 
        	enemy.position.x += move;
    	else
        	enemy.position.x -= move;
}
