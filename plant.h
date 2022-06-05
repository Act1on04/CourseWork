#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAP_COUNT 3
const char plant_map[MAP_COUNT][10] = {"Morning", "Afternoon", "Evening"};

int get_current_year();
int get_year_plant();
int get_plant_watering_map();
void get_str(char* str, unsigned size, char* message);
int get_num(char* message);
float get_float(char* message);

// Структура для объекта растение в ботаническом саду 
// с именем, видом, инвентарным номером, номером садового участка, годом посадки,
// оценочной стоимостью, именем садовника и картой полива
// плюс указатель на следующий объект
typedef struct plant_st
{
  char name[20];
  char type[15];
  unsigned inventory_number;
  unsigned planting_site;
  unsigned year_of_planting;
  float estimated_cost;
  char gardener[15];
  unsigned plant_watering_map;
  struct plant_st* next;
} plant;

// функция создаёт новую структуру типа растение и выделяет память под неё
// возвращает указатель на созданную структуру
plant* create_plant() {
  plant* new_plant = malloc(sizeof(plant));
  return new_plant;
}

// функция заполняет структуру типа растение данными
void fill_plant(plant* p)
{
  get_str(p->name, 20, "\nEnter the NAME of the plant (only letters and -): ");
  get_str(p->type, 15, "Enter the TYPE of the plant (only letters and -): ");
  p->inventory_number = get_num("Enter the INVENTORY number (above zero): ");
  p->planting_site = get_num("Enter the planting SITE number (above zero): ");
  p->year_of_planting = get_year_plant();
  p->estimated_cost = get_float("Enter the estimated COST of the plant (XXXX,XX and above zero): ");
  get_str(p->gardener, 15, "Enter the NAME of the GARDENER (only letters and -): ");
  p->plant_watering_map = get_plant_watering_map();
}

// Функция выводит на экран данные структуры типа растение
void print_plant(plant* p)
{
  printf("\n Name: %s", p->name);
  printf("\n Type: %s", p->type);
  printf("\n Inventory number: %d", p->inventory_number);
  printf("\n Planting site number: %d", p->planting_site);
  printf("\n Year of planting: %d", p->year_of_planting);
  printf("\n Estimated cost: %.2f", p->estimated_cost);
  printf("\n Gardener: %s", p->gardener);
  printf("\n Plant watering map: %s", plant_map[p->plant_watering_map-1]);
  printf("\n");
}

//получить текущий год
int get_current_year() {
  // получаем текущее время в виде количества секунд от 01.01.1970
  time_t t = time(NULL);
  // преобразуем их в локальное время и сохраняем во временнУю структуру tm
  struct tm tm = *localtime(&t);
  // и так как в структуре tm год хранится как Количество лет с 1900, 
  // то прибавляем 1900 для получения текущего года
  return tm.tm_year + 1900;
}

//проверка ввода года
int get_year_plant() {
  int year;
  do {
    printf("Enter the year of planting (1500 - current year): ");
    scanf("%d", &year);
    // если введённый год меньше 1500 или больше текущего года, то просим ввести заново 
  } while (year < 1500 || year > get_current_year());
  return year;
}

//ввод plant_watering_map с проверкой
int get_plant_watering_map() {
  int map;
  do {
    printf("Enter the plant watering map (Morning-1 Afternoon-2 Evening-3): ");
    scanf("%d", &map);
    // введённое значение не должно выходить за рамки перечисленных значений в справочнике
  } while (map < 1 || map > MAP_COUNT);
  return map;
}

//ввод строки с проверкой
void get_str(char* str, unsigned size, char* message) {
  do {
    printf("%s", message);
    scanf("%s", str);
    // проверяем введённую строку на наличие недопустимых символов
    // и длину - не менее чем 2 символа и не больше указанной в параметре size
  } while (strpbrk(str, "0123456789") != NULL || strlen(str) < 2 || strlen(str) > size );
}

//ввод номера с проверкой чтобы значение было больше нуля
int get_num(char* message) {
  int num; 
  do {
    printf("%s", message);
    scanf("%d", &num);
  } while (num < 1);
  return num;
}

// ввод ориетировочной цены с проверкой чтобы значение не было отрицательным 
float get_float(char* message) {
  float num; 
  do {
    printf("%s", message);
    scanf("%f", &num);
  } while (num < 0);
  return num;
}
