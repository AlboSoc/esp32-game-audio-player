/* ActionTriggering.h
 * This file contains the declaration of the action triggering functions.
 * which are responsible for triggering the actions (primarily playing of audio tracks) of a game.
 */
#ifndef ACTION_TRIGGERING_H
#define ACTION_TRIGGERING_H
#include <iostream>
#include <Arduino.h>
#include <esp_attr.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t xHandle = NULL;

#define NULL_NOTIFICATION (-1)

volatile int globalActionTriggeringNotification = NULL_NOTIFICATION;

typedef void callBackFunction(int action);

callBackFunction* globalCallback = nullptr;

void IRAM_ATTR pollTask(void *unusedParam){

  while (true) {
    if (globalActionTriggeringNotification != NULL_NOTIFICATION && globalCallback != nullptr) {
        globalCallback(globalActionTriggeringNotification);
        globalActionTriggeringNotification = NULL_NOTIFICATION;
    }
  }
}

void startListeningForActionTrigger(callBackFunction* callback, uint8_t initialNotificationValue=NULL_NOTIFICATION) {
  globalCallback = callback;
  static uint8_t ucParameterToPass;

  globalActionTriggeringNotification = initialNotificationValue;
  
  // Setup new task.  Note: the main Arduino loop() is on core 1, hence why I want the new task pinned to core 0 (the last param below)
  // (see https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/01-Tasks-and-co-routines/03-Task-priorities)
  // Note that configMAX_PRIORITIES is 25
  xTaskCreatePinnedToCore(pollTask, "pollTask", 10000, &ucParameterToPass, tskIDLE_PRIORITY, &xHandle, 0);
  configASSERT( xHandle );      
}

void stopListeningForActionTrigger(void) {
  if( xHandle != NULL ){
      vTaskDelete( xHandle );
      globalActionTriggeringNotification = action;
  }
}

void triggerAction(int action) {
  if( xHandle != NULL ){
    globalActionTriggeringNotification = action;
  }
}

#endif