#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#include "garden.h"
#include "menu.h"

void LoadGardenFromFile(plant_queue* queue);
void SaveGardenToFile(plant_queue* queue);


int main()
{
  setlocale(LC_ALL,"Rus");

	// создаём Сад (структура типа очередь) для растений и указатель на него,
  plant_queue plants_queue;
	plant_queue* garden = &plants_queue;
  // инициализируем очередь нулевыми значениями, т.к. она ещё пустая
	init_plant_queue(garden);
  // затем заполняем очередь данными из файла
  LoadGardenFromFile(garden);

	bool press_exit = false;
  // зацикливаем меню пока пользователь не выберет пункт меню 12 (выход) 
  // и значение press_exit не поменяется на true
	while (!press_exit)
	{
		switch (choice_menu())
		{
			case 1:
        // printf("\n1. Add a plant to the garden");
				add_plant(garden);
				break;
			case 2:
        // printf("\n2. Remove a plant from the garden");
				delete_plant_queue(garden);
				break;
			case 3:
				// printf("\n3. Editing a plant in the garden");
        edit_plant_in_queue(garden);
				break;
			case 4:
        // printf("\n4. Print all plants in the garden");
				print_plant_queue(garden);
				break;
			case 5:
				// printf("\n5. List of plants of the same type");
        print_plants_same_type(garden);
				break;
			case 6:
				// printf("\n6. List of plants planted befor or after a certain year");
        print_plants_for_year(garden);
				break;
			case 7:			
				// printf("\n7. Print full information about a plant for a given inventory number");
        print_plant_for_inventory_number(garden);  
				break;
			case 8:
				// printf("\n8. List of plants planted by a given gardener");
        print_plants_same_gardener(garden);
				break;
			case 9:
				// printf("\n9. Calculation of the total cost of plants on same planting site");
        print_total_cost_plants_same_site(garden);
				break;
			case 10:
				// printf("\n10. List of plants that need to be watered in a given time");
        print_plants_same_watermap(garden);
				break;
			case 11:
				// printf("\n11. Sort by estimated cost");
        sort_by_estimated_cost(garden);
				break;
			case 12:
				press_exit = true;
				break;
			default:
				printf(" Wrong choice!\n");
		}
		if (!press_exit)
      printf("\n\nPress any key to continue...\n");
		else
      printf("\n Goodbye!\n");
    // тут просто жду нажатия любой клавиши, чтобы надписи не пропадали сразу
    getch();
  }
  
  // на выходе из программы записываем в файл данные из очереди
  SaveGardenToFile(garden);
	return EXIT_SUCCESS;
}

// Загрузка данных из текстового файла.
// В каждой строке файла записаны данные о одном объекте типа plant.
// Данные считываются из файла последовательно, 
// тем самым позволяя восстановить очерёдность очереди.
// Не использовал бинарные файлы т.к. с работой с ними ознакомился уже после написания этого кода
// и текстовый файл был удобнее в плане манипулирования данными в ручном режиме
void LoadGardenFromFile(plant_queue* queue)
{
  FILE *data_file = fopen("garden.txt", "r");
  char name[20];
  char type[15];
  unsigned inventory_number;
  unsigned planting_site;
  unsigned year_of_planting;
  float estimated_cost;
  char gardener[15];
  unsigned plant_watering_map;

  if (data_file == NULL)
  {
    printf("\n[-] Error! Can`t open file garden.txt!\n");
    return;
  }
  while (fscanf(data_file, "%s %s %u %u %u %f %s %u ", name, type, &inventory_number, &planting_site, &year_of_planting, &estimated_cost, gardener, &plant_watering_map) != EOF)
  {
    // Создаю новый объект типа plant и заполняю его данными из файла
    plant* new_plant = create_plant();

    strcpy(new_plant->name, name);
    strcpy(new_plant->type, type);
    new_plant->inventory_number = inventory_number;
    new_plant->planting_site = planting_site;
    new_plant->year_of_planting = year_of_planting;
    new_plant->estimated_cost = estimated_cost;
    strcpy(new_plant->gardener, gardener);
    new_plant->plant_watering_map = plant_watering_map;
    
    // после добавляю этот объект в очередь
    add_plant_queue(queue, new_plant);
  }
  
  fclose(data_file);
}

// Загрузка данных в текстовый файл.
// В каждой строке файла записаны данные о одном объекте типа plant.
// Данные записываются последовательно в файл тем самым позволяя сохранить очерёдность очереди,
// т.к. сохранять в файле указатели на объекты нельзя
void SaveGardenToFile(plant_queue* queue)
{
  FILE *data_file = fopen("garden.txt", "w");
  if (data_file != NULL)
  {
    // перебираю все элементы очереди и сохраняю их в файл
    plant* cur_plant = queue->first;
    while (cur_plant != NULL) {
      fprintf(data_file,"%s ", cur_plant->name);
      fprintf(data_file,"%s ", cur_plant->type);
      fprintf(data_file,"%d ", cur_plant->inventory_number);
      fprintf(data_file,"%d ", cur_plant->planting_site);
      fprintf(data_file,"%d ", cur_plant->year_of_planting);
      fprintf(data_file,"%.2f ", cur_plant->estimated_cost);
      fprintf(data_file,"%s ", cur_plant->gardener);
      fprintf(data_file,"%d ", cur_plant->plant_watering_map);
      fprintf(data_file,"\n");
      cur_plant = cur_plant->next;
    }
  }
  else
  {
    printf("\n[-] Error! Can`t save to file garden.txt!\n");
    return;
  }

  fclose(data_file);
}