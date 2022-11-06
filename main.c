/* 
  author: Tomas Herrera taherrera@uc.cl
*/

#include "FreeRTOS.h"
#include "task.h"

#include "nvs_flash.h"
#include "nvs.h"

#include <esp_ota_ops.h>
#include <esp_partition.h>
#include <esp_vfs_fat.h>
#include <string.h>
#define OTA_READ_BLOCK_SIZE (256)

static const char* TAG = "afr-test-ota";

/* program entry */
int app_main(void){

  nvs_flash_init(); 
  vTaskStartScheduler();

  const esp_partition_t *next_update_partition = esp_ota_get_next_update_partition(NULL);
  if (next_update_partition == NULL) {
    ESP_LOGE(TAG, "[E] update_from_file: Invalid OTA data partition or no eligible OTA app slot partition was found\n");
    return -1;
  }
  ESP_LOGI(TAG, "[I] update_from_file: Got OTA partition!\n");


  static esp_ota_handle_t handle = 0;
  ESP_LOGI(TAG, "[I] update_from_file: Begin OTA process\n");
  esp_err_t ota_begin_status = esp_ota_begin(next_update_partition, OTA_SIZE_UNKNOWN, &handle);

  ESP_LOGI(TAG, "[I] OTA process started\n");

  while(1){
    vTaskDelay(100);
  }

  return 0;
}

extern void esp_vApplicationTickHook();
void IRAM_ATTR vApplicationTickHook(){
    esp_vApplicationTickHook();
}

extern void esp_vApplicationIdleHook();
void vApplicationIdleHook(){
    esp_vApplicationIdleHook();
}

void vApplicationDaemonTaskStartupHook( void ){
}
