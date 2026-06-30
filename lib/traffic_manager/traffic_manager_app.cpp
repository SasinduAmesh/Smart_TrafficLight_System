#include "traffic_manager_app.h"
#include "LED_HAL.h"

TaskHandle_t traffic_manager_app_handler;

// Vehicle counts
int total_count_N = 0;
int total_count_S = 0;
int total_count_E = 0;
int total_count_W = 0;

// Timing Parameters
#define MIN_GREEN_TIME 10  // seconds
#define MAX_GREEN_TIME 60  // seconds
#define TIME_PER_VEHICLE 2 // seconds per vehicle
#define ORANGE_TIME 3      // seconds
#define ALL_RED_TIME 1     // seconds

//----------------------------------------------------
// Calculate Green Time
//----------------------------------------------------
int calculateGreenTime(int vehicles)
{
    int greenTime = MIN_GREEN_TIME + (vehicles * TIME_PER_VEHICLE);

    if (greenTime > MAX_GREEN_TIME)
        greenTime = MAX_GREEN_TIME;

    return greenTime;
}

//----------------------------------------------------
// Traffic Manager Task
//----------------------------------------------------
void traffic_manager_app(void *pvParameters)
{
    Serial.println();
    Serial.println("========================================");
    Serial.println(" Demand Actuated Traffic Signal Started ");
    Serial.println("========================================");

    IR_Init();
    LED_init();

    all_red();

    while (1)
    {
        //----------------------------------------------------
        // Read Vehicle Counts
        //----------------------------------------------------
        total_count_N = max(0, count_N2 - count_N1);
        total_count_S = max(0, count_S2 - count_S1);
        total_count_E = max(0, count_E2 - count_E1);
        total_count_W = max(0, count_W2 - count_W1);

        int NS_Count = total_count_N + total_count_S;
        int EW_Count = total_count_E + total_count_W;

        //----------------------------------------------------
        // Debug Information
        //----------------------------------------------------
        Serial.println();
        Serial.println("========================================");
        Serial.println("Current Vehicle Counts");
        Serial.println("----------------------------------------");

        Serial.printf("North : %d\n", total_count_N);
        Serial.printf("South : %d\n", total_count_S);
        Serial.printf("East  : %d\n", total_count_E);
        Serial.printf("West  : %d\n", total_count_W);

        Serial.println("----------------------------------------");
        Serial.printf("North-South Total : %d\n", NS_Count);
        Serial.printf("East-West Total   : %d\n", EW_Count);
        Serial.println("========================================");

        //----------------------------------------------------
        // NORTH - SOUTH has Priority
        //----------------------------------------------------
        if (NS_Count >= EW_Count)
        {
            int greenTime = calculateGreenTime(NS_Count);

            Serial.println();
            Serial.println(">>> SELECTED : NORTH - SOUTH");
            Serial.printf("Green Time : %d seconds\n", greenTime);

            ns_green();

            Serial.println("Signal : GREEN");

            for (int t = greenTime; t > 0; t--)
            {
                Serial.printf("NS GREEN  | Remaining : %2d s\r", t);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }

            Serial.println();

            Serial.println("Signal : ORANGE");

            ns_orange();

            for (int t = ORANGE_TIME; t > 0; t--)
            {
                Serial.printf("NS ORANGE | Remaining : %d s\r", t);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }

            Serial.println();

            // Reset served lane counters
            count_N1 = count_N2;
            count_S1 = count_S2;
        }

        //----------------------------------------------------
        // EAST - WEST has Priority
        //----------------------------------------------------
        else
        {
            int greenTime = calculateGreenTime(EW_Count);

            Serial.println();
            Serial.println(">>> SELECTED : EAST - WEST");
            Serial.printf("Green Time : %d seconds\n", greenTime);

            ew_green();

            Serial.println("Signal : GREEN");

            for (int t = greenTime; t > 0; t--)
            {
                Serial.printf("EW GREEN  | Remaining : %2d s\r", t);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }

            Serial.println();

            Serial.println("Signal : ORANGE");

            ew_orange();

            for (int t = ORANGE_TIME; t > 0; t--)
            {
                Serial.printf("EW ORANGE | Remaining : %d s\r", t);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }

            Serial.println();

            // Reset served lane counters
            count_E1 = count_E2;
            count_W1 = count_W2;
        }

        //----------------------------------------------------
        // ALL RED
        //----------------------------------------------------
        Serial.println();
        Serial.println("Signal : ALL RED");

        all_red();

        for (int t = ALL_RED_TIME; t > 0; t--)
        {
            Serial.printf("ALL RED   | Remaining : %d s\r", t);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

        Serial.println();
        Serial.println("----------------------------------------");
        Serial.println("Traffic Cycle Completed");
        Serial.println("----------------------------------------");
    }
}