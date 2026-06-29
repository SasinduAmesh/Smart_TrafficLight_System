#include "traffic_manager_app.h"
#include "LED_HAL.h"

TaskHandle_t traffic_manager_app_handler;

int total_count_N = 0;
int total_count_S = 0;
int total_count_W = 0;
int total_count_E = 0;

#define MIN_GREEN_TIME 10
#define MAX_GREEN_TIME 60
#define TIME_PER_VEHICLE 2
#define ORANGE_TIME 3

int calculateGreenTime(int vehicles)
{
    int greenTime = MIN_GREEN_TIME + (vehicles * TIME_PER_VEHICLE);
    if (greenTime > MAX_GREEN_TIME)
        greenTime = MAX_GREEN_TIME;

    return greenTime;
}

void traffic_manager_app(void *pvParameters)
{
    Serial.println("Traffic Manager App Started");

    IR_Init();
    LED_init();
    all_red();

    while (1)
    {
        // ---------------- COUNTING ----------------
        total_count_N = max(0, count_N2 - count_N1);
        total_count_S = max(0, count_S2 - count_S1);
        total_count_W = max(0, count_W2 - count_W1);
        total_count_E = max(0, count_E2 - count_E1);

        int NS_Count = total_count_N + total_count_S;
        int EW_Count = total_count_E + total_count_W;

        Serial.printf("NS:%d EW:%d\n", NS_Count, EW_Count);

        int greenTime;

        // ====================================================
        // NORTH-SOUTH GREEN
        // ====================================================
        if (NS_Count >= EW_Count)
        {
            greenTime = calculateGreenTime(NS_Count);

            Serial.println("NS GREEN");

            ns_green();
            vTaskDelay(pdMS_TO_TICKS(greenTime * 1000));

            Serial.println("NS ORANGE");

            ns_orange();
            vTaskDelay(pdMS_TO_TICKS(ORANGE_TIME * 1000));
        }

        // ====================================================
        // EAST-WEST GREEN
        // ====================================================
        else
        {
            greenTime = calculateGreenTime(EW_Count);

            Serial.println("EW GREEN");

            ew_green();
            vTaskDelay(pdMS_TO_TICKS(greenTime * 1000));

            Serial.println("EW ORANGE");

            ew_orange();
            vTaskDelay(pdMS_TO_TICKS(ORANGE_TIME * 1000));
        }

        all_red(); // safety buffer between cycles
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}