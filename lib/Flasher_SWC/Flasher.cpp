#include <Flasher.h>
#include <Rte.h>

void flasherInit(){
    Rte_Call_Flasher_SWC_WriteFlasherData(0);
    Rte_Call_Low_Beam_SWC_WriteLightData(0);
}