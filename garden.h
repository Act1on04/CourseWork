#include <stdio.h>
#include <stdlib.h>

#include "plant.h"

typedef struct plant_queue_st  {
  plant* first;
  plant* last;
} plant_queue;

void init_plant_queue(plant_queue* queue) {
  queue->first = NULL;
  queue->last = NULL;
}

void add_plant_queue(plant_queue* queue, plant* new_plant) {
  new_plant->next = NULL;
  if (queue->first == NULL) {
    queue->first = new_plant;
  } else {
    queue->last->next = new_plant;
  }
  queue->last = new_plant;
}

void add_plant(plant_queue* queue) {
  plant* new_plant = create_plant();
  fill_plant(new_plant);
  add_plant_queue(queue, new_plant);
  printf("\n[+] Add the plant to the garden successfully!\n");
}		

void delete_plant_queue(plant_queue* queue) {
  if (queue->first == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else {
    plant* first = queue->first;
    queue->first = queue->first->next;
    free(first);
    printf("\n[+] Remove the plant from the garden successfully!\n");
  }
}

int edit_plant_in_queue(plant_queue* queue) {
  unsigned inventory_number;
  inventory_number = get_num("Enter the INVENTORY number of plant for edit: ");
  plant* cur_plant = queue->first;
  while (cur_plant != NULL) {
    if (cur_plant->inventory_number == inventory_number) {
      printf("\nPlant with inventory number %d in Garden:", inventory_number);
      print_plant(cur_plant);
      printf("\nLet`s edit Plant:");
      fill_plant(cur_plant);
      printf("\n[+] Plant edited successfully!");
      return 1;
    }
    cur_plant = cur_plant->next;
  }
  printf("\n[-] Plant with inventory number %d not found in Garden!\n", inventory_number);

  return 0;
}

void print_shapka()
{
  printf("\n-----------------------------------------------------------------------------------------------------------");
  printf("\n| N |        Name        |      Type     |Inventory| Site |Year of |Estimated|   Gardener    |   Plant    |");
  printf("\n|   |                    |               |  number |number|planting|  cost   |               |watering map|");
  printf("\n-----------------------------------------------------------------------------------------------------------");
}

void print_stroka(unsigned num, plant* cur_plant)
{
  printf("\n|%-3d|%-20s|%-15s|%9d|%6d|%8d|%9.2f|%-15s|%-12s|", num, cur_plant->name, cur_plant->type, cur_plant->inventory_number, cur_plant->planting_site, cur_plant->year_of_planting, cur_plant->estimated_cost, cur_plant->gardener, plant_map[cur_plant->plant_watering_map-1]);
  printf("\n-----------------------------------------------------------------------------------------------------------");
}

// Print all plants in the garden
void print_plant_queue(plant_queue* queue) {
  int num = 0;
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

// List of plants of the same type
void print_plants_same_type(plant_queue* queue) 
{
  int num = 0;
  char type[15];
  get_str(type, 15, "Enter the TYPE of the plants you want print (only letters and -): ");
  plant* cur_plant = queue->first;
  if (cur_plant == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else 
  {
    printf("\n[+] Plants of type %s in Garden:", type);
    print_shapka();
    while (cur_plant != NULL) {
      if (stricmp(cur_plant->type, type) == 0) print_stroka(++num, cur_plant);
      cur_plant = cur_plant->next;
    }
  }
}

// List of plants planted by a given gardener
void print_plants_same_gardener(plant_queue* queue) 
{
  int num = 0;
  char gardener[15];
  get_str(gardener, 15, "Enter the NAME of the GARDENER you want print (only letters and -): ");
  plant* cur_plant = queue->first;
  if (cur_plant == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else 
  {
    printf("\n[+] Plants of GARDENER %s in Garden:", gardener);
    print_shapka();
    while (cur_plant != NULL) {
      if (stricmp(cur_plant->gardener, gardener) == 0) print_stroka(++num, cur_plant);
      cur_plant = cur_plant->next;
    }
  }
}

// List of plants planted befor or after a certain year
void print_plants_for_year(plant_queue* queue) 
{
  int num = 0;
  int before_after = 1;
  unsigned year;
  year = get_year_plant();
  printf("Enter 0-before or 1-after the year %4d of planting plants you want print (0 or 1): ", year);
  scanf("%d", &before_after);
  plant* cur_plant = queue->first;
  if (cur_plant == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else 
  {
    if (before_after == 0) {
      printf("\n[+] Plants before the year %4d in Garden:", year);
    } else {
      printf("\n[+] Plants after the year %4d in Garden:", year);
    }
    print_shapka();
    while (cur_plant != NULL) {
      if ((cur_plant->year_of_planting < year && before_after==0) || (cur_plant->year_of_planting > year && before_after==1)) 
        print_stroka(++num, cur_plant);
      cur_plant = cur_plant->next;
    }
  }
}

// List of plants that need to be watered in a given time
void print_plants_same_watermap(plant_queue* queue) 
{
  int num = 0;
  unsigned watermap;
  watermap = get_plant_watering_map();
  plant* cur_plant = queue->first;
  if (cur_plant == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else 
  {
    printf("\n[+] Plants that need to be watered at %s:", plant_map[watermap-1]);
    print_shapka();
    while (cur_plant != NULL) {
      if (cur_plant->plant_watering_map == watermap) print_stroka(++num, cur_plant);
      cur_plant = cur_plant->next;
    }
  }
}

// Print full information about a plant for a given inventory number
void print_plant_for_inventory_number(plant_queue* queue) 
{
  unsigned inventory_number;
  inventory_number = get_num("Enter the INVENTORY number : ");
  plant* cur_plant = queue->first;
  if (cur_plant == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else 
  {
    printf("\n[+] Plant with inventory number %d in Garden:", inventory_number);
    while (cur_plant != NULL) {
      if (cur_plant->inventory_number == inventory_number) {
        print_plant(cur_plant);
        break;
      }
      cur_plant = cur_plant->next;
    }
  }
}

// Calculation of the total cost of plants on same planting site
void print_total_cost_plants_same_site(plant_queue* queue) 
{
  unsigned planting_site;
  planting_site = get_num("Enter the PLANTING SITE number : ");
  plant* cur_plant = queue->first;
  if (cur_plant == NULL) {
    printf("\n[-] Garden is empty!\n");
  } else 
  {
    float total_cost = 0;
    while (cur_plant != NULL) {
      if (cur_plant->planting_site == planting_site) total_cost += cur_plant->estimated_cost;
      cur_plant = cur_plant->next;
    }
    printf("\n[+] Total cost of plants on planting site number %d equals: %.2f", planting_site, total_cost);
  }
}

void swap_plants_point(plant_queue* queue, plant* prev_plant, plant* cur_plant, plant* next_plant)
{
  if (prev_plant == NULL) queue->first = next_plant;
  else prev_plant->next = next_plant;
  cur_plant->next = next_plant->next;
  next_plant->next = cur_plant;
}

plant* get_plant_by_index(plant_queue* queue, int index)
{
  int num = 0;
  plant* cur_plant = queue->first;
  while (cur_plant != NULL) {
    if (num == index) return cur_plant;
    cur_plant = cur_plant->next;
    num++;
  }
  return NULL;
}

//Sort by estimated cost
void sort_by_estimated_cost(plant_queue* queue) 
{
  int SIZE = 0;
  plant* cur_plant = queue->first;
  while (cur_plant != NULL) {
    SIZE++;
    cur_plant = cur_plant->next;
  }
  
  for (int i = 0; i < SIZE - 1; i++)
    for (int j = SIZE - 1; j > i; j--) 
      if (get_plant_by_index(queue, j)->estimated_cost < get_plant_by_index(queue, j - 1)->estimated_cost)
        swap_plants_point(queue, get_plant_by_index(queue, j-2), get_plant_by_index(queue, j-1), get_plant_by_index(queue, j));
  printf("\n[+] Sorted by estimated cost");
  print_plant_queue(queue);
}
