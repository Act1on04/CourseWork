#include <stdio.h>
#include <stdlib.h>

#include "plant.h"

// Структура типа очередь. В ней прописаны указатели на первый и последний элементы очереди.
typedef struct plant_queue_st  {
  plant* first;
  plant* last;
} plant_queue;

// Функция инициализации очереди
void init_plant_queue(plant_queue* queue) {
  queue->first = NULL;
  queue->last = NULL;
}

// Функция добавления элемента в очередь
void add_plant_queue(plant_queue* queue, plant* new_plant) {
  // Если очередь пустая, то добавляем в неё первый элемент.
  // А если не пустая, то последнему элементу добавляем указатель на новый элемент.
  if (queue->first == NULL) {
    queue->first = new_plant;
  } else {
    queue->last->next = new_plant;
  }
  // После добавления последним элементом становится новый элемент.
  queue->last = new_plant;
  new_plant->next = NULL;
}

// Функция создаёт новое растение и добавляет его в Сад
void add_plant(plant_queue* queue) {
  // Создаём новое растение
  plant* new_plant = create_plant();
  // Заполняем его данными
  fill_plant(new_plant);
  // Добавляем его в очередь
  add_plant_queue(queue, new_plant);
  printf("\n[+] Add the plant to the garden successfully!\n");
}		

// Функция удаляет растение из очереди
void delete_plant_queue(plant_queue* queue) {
  if (queue->first == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else {
    // Временно сохраняем указатель на первый элемент очереди
    // это позволит нам не потерять его при назначении нового первого элемента очереди
    plant* first = queue->first;
    // Присваиваем первому элементу очереди указатель на следующий элемент после первого
    queue->first = queue->first->next;
    // теперь, имея сохранённый указатель, можем удалить из памяти бывший первый элемент очереди
    free(first);
    printf("\n[+] Remove the plant from the garden successfully!\n");
  }
}

// Функция редактирует растение в очереди по инвентарному номеру
int edit_plant_in_queue(plant_queue* queue) {
  unsigned inventory_number;
  inventory_number = get_num("Enter the INVENTORY number of plant for edit: ");
  // Перебираем все элементы очереди пока не найдём тот, который нужно редактировать 
  plant* cur_plant = queue->first;
  while (cur_plant != NULL) {
    // Если нашли элемент с таким инвентарным номером, то редактируем его и выходим из функции
    if (cur_plant->inventory_number == inventory_number) {
      printf("\nPlant with inventory number %d in Garden:", inventory_number);
      print_plant(cur_plant);
      printf("\nLet`s edit Plant:");
      fill_plant(cur_plant);
      printf("\n[+] Plant edited successfully!");
      return EXIT_SUCCESS;
    }
    cur_plant = cur_plant->next;
  }
  // если прошли до конца цикла, значит не нашли элемент с таким инвентарным номером
  printf("\n[-] Plant with inventory number %d not found in Garden!\n", inventory_number);

  return EXIT_SUCCESS;
}

void print_shapka()
{
  printf("\n-----------------------------------------------------------------------------------------------------------");
  printf("\n| N |        Name        |      Type     |Inventory| Site |Year of |Estimated|   Gardener    |   Plant    |");
  printf("\n|   |                    |               |  number |number|planting|  cost   |               |watering map|");
  printf("\n-----------------------------------------------------------------------------------------------------------");
}

// Функция просто распечатывает растение в табличном виде
void print_stroka(unsigned num, plant* cur_plant)
{
  printf("\n|%-3d|%-20s|%-15s|%9d|%6d|%8d|%9.2f|%-15s|%-12s|", num, cur_plant->name, cur_plant->type, cur_plant->inventory_number, cur_plant->planting_site, cur_plant->year_of_planting, cur_plant->estimated_cost, cur_plant->gardener, plant_map[cur_plant->plant_watering_map-1]);
  printf("\n-----------------------------------------------------------------------------------------------------------");
}

// Функция выводит на экран все растения в Саду-очереди в табличном виде
void print_plant_queue(plant_queue* queue) {
  int num = 0;
  // Проверяем не пуста ли очередь
  // Если не пуста, то выводим все элементы очереди
  plant* cur_plant = queue->first;
  if (cur_plant == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else 
  {
    printf("\n[+] Plants in Garden:");
    print_shapka();
    while (cur_plant != NULL) {
      print_stroka(++num, cur_plant);
      cur_plant = cur_plant->next;
    }
  }
}

// Функция выводит на экран список растений указанного вида
void print_plants_same_type(plant_queue* queue) 
{
  int num = 0;
  char type[15];
  // Проверяем не пуста ли очередь
  plant* cur_plant = queue->first;
  if (cur_plant == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else 
  {
    // Получаем тип растения для которого нужно вывести список
    get_str(type, 15, "Enter the TYPE of the plants you want print (only letters and -): ");
    printf("\n[+] Plants of type %s in Garden:", type);
    print_shapka();
    while (cur_plant != NULL) {
      // Если тип растения совпадает с типом который ввел пользователь, то выводим его
      if (stricmp(cur_plant->type, type) == 0) print_stroka(++num, cur_plant);
      cur_plant = cur_plant->next;
    }
  }
}


// Функция выводит на экран список растений указанного садовника
void print_plants_same_gardener(plant_queue* queue) 
{
  int num = 0;
  char gardener[15];
  // Проверяем не пуста ли очередь
  plant* cur_plant = queue->first;
  if (cur_plant == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else 
  {
    // Получаем имя садовника для которого нужно вывести список
    get_str(gardener, 15, "Enter the NAME of the GARDENER you want print (only letters and -): ");
    printf("\n[+] Plants of GARDENER %s in Garden:", gardener);
    print_shapka();
    while (cur_plant != NULL) {
      // Если имя садовника совпадает с типом который ввел пользователь, то выводим его
      if (stricmp(cur_plant->gardener, gardener) == 0) print_stroka(++num, cur_plant);
      cur_plant = cur_plant->next;
    }
  }
}

// List of plants planted befor or after a certain year
// Функция выводит на экран список растений посаженных до или после определенного года
void print_plants_for_year(plant_queue* queue) 
{
  int num = 0;
  int before_after = 1;
  unsigned year;
  // Проверяем не пуста ли очередь
  plant* cur_plant = queue->first;
  if (cur_plant == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else 
  {
    // Получаем год для которого нужно вывести список
    year = get_year_plant();
    // Получаем параметр по которому определяем до или после введенного года
    printf("Enter 0-before or 1-after the year %4d of planting plants you want print (0 or 1): ", year);
    scanf("%d", &before_after);
    if (before_after == 0) {
      printf("\n[+] Plants before the year %4d in Garden:", year);
    } else {
      printf("\n[+] Plants after the year %4d in Garden:", year);
    }
    print_shapka();
    while (cur_plant != NULL) {
      // Если год посадки меньше введёного года И пользователь таки выбрал выводить растения посаженные до введенного года
      // ИЛИ
      // год посадки больше введёного года И пользователь выбрал выводить растения посаженные после введенного года
      if ((cur_plant->year_of_planting < year && before_after==0) || (cur_plant->year_of_planting > year && before_after==1)) 
        print_stroka(++num, cur_plant);
      cur_plant = cur_plant->next;
    }
  }
}

// Функция выводит на экран список растений которые нужно поливать в определенное время
void print_plants_same_watermap(plant_queue* queue) 
{
  int num = 0;
  unsigned watermap;
  // Проверяем не пуста ли очередь
  plant* cur_plant = queue->first;
  if (cur_plant == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else 
  {
    // Получаем время полива для которого нужно вывести список
    watermap = get_plant_watering_map();
    printf("\n[+] Plants that need to be watered at %s:", plant_map[watermap-1]);
    print_shapka();
    while (cur_plant != NULL) {
      // Если время полива равно введёному пользователем, то выводим его
      if (cur_plant->plant_watering_map == watermap) print_stroka(++num, cur_plant);
      cur_plant = cur_plant->next;
    }
  }
}

// Функция выводит на экран полную информацию о растении по его инвентарному номеру
void print_plant_for_inventory_number(plant_queue* queue) 
{
  unsigned inventory_number;
  // Проверяем не пуста ли очередь
  plant* cur_plant = queue->first;
  if (cur_plant == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else 
  {
    // Получаем инвентарный номер для которого нужно вывести информацию о растении
    inventory_number = get_num("Enter the INVENTORY number : ");
    printf("\n[+] Plant with inventory number %d in Garden:", inventory_number);
    while (cur_plant != NULL) {
      // Если инвентарный номер равен введёному пользователем, то выводим его
      if (cur_plant->inventory_number == inventory_number) {
        print_plant(cur_plant);
        // Выходим из цикла так как нашли нужное растение и второго с таким инвентарным номером не должно быть
        break;
      }
      cur_plant = cur_plant->next;
    }
  }
}

// Функция вычисляет общую стоимость посаженных растений на указанном участке
void print_total_cost_plants_same_site(plant_queue* queue) 
{
  unsigned planting_site;
  // Проверяем не пуста ли очередь
  plant* cur_plant = queue->first;
  if (cur_plant == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else 
  {
    // Получаем номер участка для которого нужно вывести стоимость посаженных растений
    planting_site = get_num("Enter the PLANTING SITE number : ");
    // Начальную общую сумму обнуляем
    float total_cost = 0;
    while (cur_plant != NULL) {
      // Если номер участка равен введёному пользователем, то увеличиваем общую сумму на стоимость растения
      if (cur_plant->planting_site == planting_site) total_cost += cur_plant->estimated_cost;
      cur_plant = cur_plant->next;
    }
    printf("\n[+] Total cost of plants on planting site number %d equals: %.2f", planting_site, total_cost);
  }
}

// Функция меняет местами ДВА растения в очереди (ТЕКУЩЕЕ и СЛЕДУЮЩЕЕ). 
// Принимает на вход очередь и номера ТРЁХ растений, 
// т.к. нам надо ещё поменять указатель в ПРЕДЫДУЩЕМ растении на СЛЕДУЮЩЕЕ растение
void swap_plants_point(plant_queue* queue, plant* prev_plant, plant* cur_plant, plant* next_plant)
{
  // Если ПРЕДЫДУЩЕГО растения нет, то значит ТЕКУЩЕЕ растение было первым в очереди
  // и тогда просто ставим СЛЕДУЮЩЕЕ растение первым в очереди
  // Если же ПРЕДЫДУЩЕЕ растение есть, то меняем его указатель на следующий элемент на СЛЕДУЮЩЕЕ растение
  if (prev_plant == NULL) queue->first = next_plant;
  else prev_plant->next = next_plant;
  // Если СЛЕДУЮЩЕЕ растение было последним в очереди (ТЕКУЩЕЕ - предпоследним), 
  // то надо поменять указатель на последний элемент в очереди на ТЕКУЩЕЕ растение
  if (next_plant->next == NULL) queue->last = cur_plant;
  // Затем меняем указатель на следующий элемент ТЕКУЩЕГО растения на указатель следующего элемента СЛЕДУЮЩЕГО растения
  cur_plant->next = next_plant->next;
  // И указатель на следующий элемент СЛЕДУЮЩЕГО растения устанавливаем на ТЕКУЩЕЕ растение
  next_plant->next = cur_plant;
  // Важно менять указатели именно в таком порядке что бы не потерять указатель следующего элемента СЛЕДУЮЩЕГО растения
}

// Функция получет указатель на растение по его порядковому номеру в очереди
// Для перебора очереди не использовал цикл, т.к. может случится, что в очереди будет меньше растений, 
// чем указано в параметре index. 
plant* get_plant_by_index(plant_queue* queue, int index)
{
  int num = 0;
  plant* cur_plant = queue->first;
  while (cur_plant != NULL) {
    // просто перебираем очередь пока не дойдём до растения с нужным номером и сразу возвращаем указатель на него
    if (num == index) return cur_plant;
    cur_plant = cur_plant->next;
    num++;
  }
  return NULL;
}

// Функция вычисляет количество элементов в очереди
// Просто перебираем очередь и увеличиваем счётчик на один при каждом переходе по списку
int get_queue_size(plant_queue* queue)
{
  int size = 0;
  plant* cur_plant = queue->first;
  while (cur_plant != NULL) {
    size++;
    cur_plant = cur_plant->next;
  }
  return size;
}

// Функция сортирует очередь по возрастанию ориентировочной стоимости растений
// Для этого пришлось внедрить в нашу структуру, так сказать, свойства массива (количество элементов и индексы)
// и это позволило нам отсортировать очередь методом пузырька
void sort_by_estimated_cost(plant_queue* queue) 
{
  // определяем количество элементов в очереди
  int SIZE = get_queue_size(queue);
  // Метод пузырька как для массива
  for (int i = 0; i < SIZE-1; i++)
    for (int j = 0; j < SIZE-1-i; j++) 
      // если ориентировочная стоимость растения в очереди больше чем у следующего растения, то меняем местами
      if (get_plant_by_index(queue, j)->estimated_cost > get_plant_by_index(queue, j+1)->estimated_cost)
        // Т.к. мы используем односвязную очередь, то для перестановки элементов необходимо использовать три элемента очереди
        swap_plants_point(queue, get_plant_by_index(queue, j-1), get_plant_by_index(queue, j), get_plant_by_index(queue, j+1));
  printf("\n[+] Sorted by estimated cost");
  print_plant_queue(queue);
}
