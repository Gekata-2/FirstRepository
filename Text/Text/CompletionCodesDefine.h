#pragma once

#define TEXT_OK 0 //Ошибок нет	
		//Коды ситуаций
#define TEXT_NO_DOWN_LEVEL_EXIST 101		//Нет подуровоня для текущей позиции
#define TEXT_NO_NEXT_SAME_LEVEL_EXIST 102	//Нет следующего раздела текущего уровня
#define TEXT_NO_PREV_LINK_EXIST 103		//Нет уровней выще(Текущая позиция в начале текста)
		//Коды ошибок
#define TEXT_ERROR_IN_TEXT -102				//Ошибка в тексте
#define TEXT_MEMORY_OWERFLOW  -101			//Кончилась память