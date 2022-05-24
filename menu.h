#include <stdio.h>
#include <stdlib.h>

int choice_menu()
{
  int choice;
  do
  {
    printf("\n1. Add a plant to the garden");
    printf("\n2. Remove a plant from the garden");
    printf("\n3. Editing a plant in the garden");
    printf("\n4. Print all plants in the garden");
    printf("\n5. List of plants of the same type");
    printf("\n6. List of plants planted befor or after a certain year");
    printf("\n7. Print full information about a plant for a given inventory number");
    printf("\n8. List of plants planted by a given gardener");
    printf("\n9. Calculation of the total cost of plants on same planting site");
    printf("\n10. List of plants that need to be watered in a given time");
    printf("\n11. Sort by estimated cost");
    printf("\n12. Exit");
    printf("\n\nEnter your choice (1-12): ");
    scanf("%d", &choice);
  } while (choice < 1 || choice > 12);
  return choice;
}
