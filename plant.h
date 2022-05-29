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

//type of structure for a plant in a botanical garden 
//with name, type, inventory number, lot number, year of planting, estimated cost, gardener, plant watering map.
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

plant* create_plant() {
  plant* new_plant = malloc(sizeof(plant));
  return new_plant;
}

//function to fill the plant structure with data
void fill_plant(plant* p)
{
  // printf("\nEnter the name of the plant: ");
  // scanf("%s", p->name);
  get_str(p->name, 20, "\nEnter the NAME of the plant (only letters and -): ");
  // printf("Enter the type of the plant: ");
  // scanf("%s", p->type);
  get_str(p->type, 15, "Enter the TYPE of the plant (only letters and -): ");
  // printf("Enter the INVENTORY number: ");
  // scanf("%u", &p->inventory_number);
  p->inventory_number = get_num("Enter the INVENTORY number (above zero): ");
  // printf("Enter the planting SITE number: ");
  // scanf("%u", &p->planting_site);
  p->planting_site = get_num("Enter the planting SITE number (above zero): ");
  p->year_of_planting = get_year_plant();
  // printf("Enter the estimated COST of the plant (XXXX,XX): ");
  // scanf("%f", &p->estimated_cost);
  p->estimated_cost = get_float("Enter the estimated COST of the plant (XXXX,XX and above zero): ");
  // printf("Enter the name of the gardener: ");
  // scanf("%s", p->gardener);
  get_str(p->gardener, 15, "Enter the NAME of the GARDENER (only letters and -): ");
  p->plant_watering_map = get_plant_watering_map();
}

//function to print the plant structure
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
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  return tm.tm_year + 1900;
}

//проверка ввода года
int get_year_plant() {
  int year;
  do {
    printf("Enter the year of planting (1500 - current year): ");
    scanf("%d", &year);
  } while (year < 1500 || year > get_current_year());
  return year;
}

//ввод plant_watering_map с проверкой
int get_plant_watering_map() {
  int map;
  do {
    printf("Enter the plant watering map (Morning-1 Afternoon-2 Evening-3): ");
    scanf("%d", &map);
  } while (map < 1 || map > MAP_COUNT);
  return map;
}

//ввод строки с проверкой
void get_str(char* str, unsigned size, char* message) {
  do {
    printf("%s", message);
    scanf("%s", str);
  } while (strpbrk(str, "0123456789") != NULL || strlen(str) < 2 || strlen(str) > size );
}

//ввод номера с проверкой на значение больше 0
int get_num(char* message) {
  int num; 
  do {
    printf("%s", message);
    scanf("%d", &num);
  } while (num < 1);
  return num;
}

float get_float(char* message) {
  float num; 
  do {
    printf("%s", message);
    scanf("%f", &num);
  } while (num < 0);
  return num;
}
