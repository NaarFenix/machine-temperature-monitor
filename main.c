#include <stdio.h>
#include "cJSON/cJSON.h"
#include <stdlib.h>

int main(void)
{
   // Open JSON file for reading
   FILE *file = fopen("report.json", "r");
   if (file== NULL ){
      printf("error couldn open json.\n");
      return 1;
   }

   // Get file size to know how much memory to allocate
   fseek(file, 0, SEEK_END);
   long size = ftell(file);
   rewind(file);

   // Allocate memory for the whole JSON file + null terminator
   char *buffer = malloc(size+1);
   if (buffer == NULL){
      printf("Memory allocation fialed.\n");
      fclose(file);
      return 1;
   }

   // Copy file content into memory
   fread(buffer,1,size,file);
   buffer[size] = '\0';
   fclose(file);

   // Convert JSON text into a cJSON structure
   cJSON *root = cJSON_Parse(buffer);
   if (root == NULL){
      printf("Invalid JSON.\n");
      free(buffer);
      return 1;
   }

   printf("json parsed succ.\n");

   // Get how many machine objects exist in the JSON array
   int count = cJSON_GetArraySize(root);
   printf("\n machines numbers : %d\n", count);

   for (int i = 0; i<count; i++){

   // Select one machine from the JSON array
   cJSON *machine = cJSON_GetArrayItem(root, i);

   // Extract machine values from the object
   cJSON *temp = cJSON_GetObjectItem(machine,"temp");
   cJSON *id = cJSON_GetObjectItem(machine,"id");
   cJSON *name = cJSON_GetObjectItem(machine,"name");
   cJSON *power = cJSON_GetObjectItem(machine,"power");

   if (!temp || !id || !name || !power) {
          printf("Skipping malformed entry at index %d\n", i);
          continue;
   }

   // Check temperature and update machine power state
   if (temp ->valuedouble > 90){
      cJSON_SetBoolValue(power, 0);
      printf("\n WARNING %s is overheating! \n", name ->valuestring);
   }else {
    cJSON_SetBoolValue(power, 1);
   }

   printf("ID:%d\n NAME : %s\n temp :%.1f\n power :%s \n",id->valueint ,name ->valuestring,temp->valuedouble, cJSON_IsTrue(power)? "true" : "false");
   }

   // Convert modified cJSON data back into JSON text
   char *updated_json = cJSON_Print(root);

   if(updated_json == NULL)
   {
       printf("Failed to save JSON\n");
       return 1;
   }

   // Write updated data back into the JSON file
   FILE *out = fopen("report.json", "w");
   if(out){
      fputs(updated_json, out);
      fclose(out);
   }

   // Free allocated memory
   free(updated_json);
   cJSON_Delete(root);
   free(buffer);

   return 0;
}