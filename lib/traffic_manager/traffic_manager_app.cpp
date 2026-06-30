#include "traffic_manager_app.h"
#include "LED_HAL.h"

TaskHandle_t traffic_manager_app_handler;

// Vehicle counts
int total_count_N = 0;
int total_count_S = 0;
int total_count_E = 0;
int total_count_W = 0;

int total_count_NS = 0;
int total_count_EW = 0;

// Timing
#define MIN_GREEN_TIME 10
#define MAX_GREEN_TIME 60
#define TIME_PER_VEHICLE 2
#define ALL_RED_TIME 5
#define ORANGE_EW_TIME 3
#define ORANGE_NS_TIME 3

void showNumberDisplay_NS(int number);
void showNumberDisplay_EW(int number);

//----------------------------------------------------
int calculateGreenTime(int vehicles)
{
    int time = MIN_GREEN_TIME + (vehicles * TIME_PER_VEHICLE);
    if (time > MAX_GREEN_TIME)
        time = MAX_GREEN_TIME;
    return time;
}

//----------------------------------------------------
void runCountdown_AllRed()
{
    for (int i = ALL_RED_TIME; i > 0; i--)
    {
        showNumberDisplay_NS(i);
        showNumberDisplay_EW(i);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

//----------------------------------------------------
void runDualCountdown(int greenTime, bool isNS)
{
    for (int i = greenTime; i > 0; i--)
    {
        if (isNS)
        {
            showNumberDisplay_NS(i);
            showNumberDisplay_EW(i);
        }
        else
        {
            showNumberDisplay_EW(i);
            showNumberDisplay_NS(i);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

//----------------------------------------------------
void traffic_manager_app(void *pvParameters)
{
    Serial.println("Traffic Signal Started");

    IR_Init();
    LED_init();
    initDisplays();

    while (1)
    {
        //------------------------------------------------
        // STEP 1: SENSOR READ FIRST
        //------------------------------------------------
        total_count_N = max(0, count_N2 - count_N1);
        total_count_S = max(0, count_S2 - count_S1);
        total_count_E = max(0, count_E2 - count_E1);
        total_count_W = max(0, count_W2 - count_W1);

        total_count_NS = total_count_N + total_count_S;
        total_count_EW = total_count_E + total_count_W;

        Serial.println("\n==============================");
        Serial.println("Sensor Update");
        Serial.print("N: "); Serial.print(total_count_N);
        Serial.print(" | S: "); Serial.print(total_count_S);
        Serial.print(" | NS Total: "); Serial.println(total_count_NS);

        Serial.print("E: "); Serial.print(total_count_E);
        Serial.print(" | W: "); Serial.print(total_count_W);
        Serial.print(" | EW Total: "); Serial.println(total_count_EW);

        //------------------------------------------------
        // STEP 2: DECISION
        //------------------------------------------------
        bool ewPriority = (total_count_EW >= total_count_NS);

        int ewGreen = calculateGreenTime(total_count_EW);
        int nsGreen = calculateGreenTime(total_count_NS);

        Serial.println("Decision Phase");
        Serial.print("EW Priority: ");
        Serial.println(ewPriority ? "YES" : "NO");

        Serial.print("EW Green Time: ");
        Serial.print(ewGreen);
        Serial.println(" sec");

        Serial.print("NS Green Time: ");
        Serial.print(nsGreen);
        Serial.println(" sec");

        //------------------------------------------------
        // STEP 3: ALL RED
        //------------------------------------------------
        Serial.println("Phase: ALL RED");
        all_red();
        runCountdown_AllRed();

        //------------------------------------------------
        // STEP 4: EXECUTION
        //------------------------------------------------

        if (ewPriority)
        {
            Serial.println("Flow: EW PRIORITY ROUTE");

            Serial.println("Phase: EW ORANGE");
            ew_orange();
            ns_red();

            for (int i = ORANGE_EW_TIME; i > 0; i--)
            {
                showNumberDisplay_EW(i);
                showNumberDisplay_NS(i);
                Serial.print("EW Orange Countdown: ");
                Serial.println(i);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }

            Serial.println("Phase: EW GREEN START");
            ew_green();
            ns_red();

            Serial.print("EW Green Duration: ");
            Serial.println(ewGreen);

            runDualCountdown(ewGreen, false);

            Serial.println("Phase: END WARNING (EW->NS)");
            ew_green();
            ns_orange();

            for (int i = 3; i > 0; i--)
            {
                Serial.print("End Warning EW: ");
                Serial.println(i);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }

            Serial.println("Phase: NS GREEN START");
            ew_red();
            ns_green();

            Serial.print("NS Green Duration: ");
            Serial.println(nsGreen);

            runDualCountdown(nsGreen, true);
        }
        else
        {
            Serial.println("Flow: NS PRIORITY ROUTE");

            Serial.println("Phase: NS ORANGE");
            ns_orange();
            ew_red();

            for (int i = ORANGE_NS_TIME; i > 0; i--)
            {
                showNumberDisplay_NS(i);
                showNumberDisplay_EW(i);
                Serial.print("NS Orange Countdown: ");
                Serial.println(i);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }

            Serial.println("Phase: NS GREEN START");
            ns_green();
            ew_red();

            Serial.print("NS Green Duration: ");
            Serial.println(nsGreen);

            runDualCountdown(nsGreen, true);

            Serial.println("Phase: END WARNING (NS->EW)");
            ns_green();
            ew_orange();

            for (int i = 3; i > 0; i--)
            {
                Serial.print("End Warning NS: ");
                Serial.println(i);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }

            Serial.println("Phase: EW GREEN START");
            ns_red();
            ew_green();

            Serial.print("EW Green Duration: ");
            Serial.println(ewGreen);

            runDualCountdown(ewGreen, false);
        }

        Serial.println("Cycle Complete → Restarting with ALL RED next loop");
    }
}