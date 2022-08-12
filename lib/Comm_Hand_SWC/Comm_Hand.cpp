#include <Comm_Hand.h>
#include <Rte.h>
#include <Arduino.h>
#define CHECK_BIT(var, position) ((var) & (1 << (position)))
uint8_t readData;
uint8_t lastRead;

void commHand()
{
    Rte_Call_ParkPilotSWC_WriteEmergencyFlag(0);
    if (Serial.available() > 0)
    {
        readData = Serial.read();
    }
    if ((readData & 0x04) == 0x04)
    {
        Rte_Call_Comm_HandSWC_WriteLeftSteering(1);
    }
    else if (!(readData & (1<<leftSteeringRequest)))
    {
        Rte_Call_Comm_HandSWC_WriteLeftSteering(0);
    }
    if ((readData & 0x40) == 0x40)
    {
        Rte_Call_Comm_HandSWC_WriteDriveMode(1);
    }
    else
    {
        Rte_Call_Comm_HandSWC_WriteDriveMode(0);
    }
    if ((readData & 0x08) == 0x08)
    {
        Rte_Call_Comm_HandSWC_WriteRightSteering(1);
    }
    else if (!(readData & (1<<rightSteeringRequest)))
    {
        Rte_Call_Comm_HandSWC_WriteRightSteering(0);
    }
    if ((readData & 0x01) == 0x01)
    {
        Rte_Call_Comm_HandSWC_WriteDriveInput(FWD);
    }
    if ((readData & 0x02) == 0x02)
    {
        Rte_Call_Comm_HandSWC_WriteDriveInput(REV);
    }
    if (!(readData & (1 << backwards)) && !(readData & (1 << forwards)))
    {
        Rte_Call_Comm_HandSWC_WriteDriveInput(0);
    }
    if (CHECK_BIT(readData, LightSwitch) == 0 && CHECK_BIT(readData, LightSwitch2) != 0)
        {
            // AUTO
            Rte_Call_Low_Beam_SWC_WriteLightData(2);
        }
        else if (CHECK_BIT(readData, LightSwitch) == 0 && CHECK_BIT(readData, LightSwitch2) == 0)
        {
            // OFF
            Rte_Call_Low_Beam_SWC_WriteLightData(0);
        }
        else if (CHECK_BIT(readData, LightSwitch) != 0 && CHECK_BIT(readData, LightSwitch2) == 0)
        {
            // ON
            Rte_Call_Low_Beam_SWC_WriteLightData(1);
        }
    lastRead = readData;
}
