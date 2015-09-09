/*******************************************************************************
    OpenAirInterface
    Copyright(c) 1999 - 2014 Eurecom

    OpenAirInterface is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.


    OpenAirInterface is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with OpenAirInterface.The full GNU General Public License is
   included in this distribution in the file called "COPYING". If not,
   see <http://www.gnu.org/licenses/>.

  Contact Information
  OpenAirInterface Admin: openair_admin@eurecom.fr
  OpenAirInterface Tech : openair_tech@eurecom.fr
  OpenAirInterface Dev  : openair4g-devel@eurecom.fr

  Address      : Eurecom, Compus SophiaTech 450, route des chappes, 06451 Biot, France.

 *******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "TLVEncoder.h"
#include "TLVDecoder.h"
#include "MsNetworkFeatureSupport.h"

int decode_ms_network_feature_support(MsNetworkFeatureSupport *msnetworkfeaturesupport, uint8_t iei, uint8_t *buffer, uint32_t len)
{
  int decoded = 0;
 
  
  if (iei > 0) {
    CHECK_IEI_DECODER(iei, (*buffer & 0xc0));
  }
  msnetworkfeaturesupport->spare_bits= (*(buffer + decoded) >> 3) & 0x7;
  msnetworkfeaturesupport->extended_periodic_timers= *(buffer + decoded) & 0x1;
  decoded++;
  
#if NAS_DEBUG
  dump_ms_network_feature_support_xml(msnetworkfeaturesupport, iei);
#endif
  return decoded;
}
int encode_ms_network_feature_support(MsNetworkFeatureSupport *msnetworkfeaturesupport, uint8_t iei, uint8_t *buffer, uint32_t len)
{
  uint8_t *lenPtr;
  uint32_t encoded = 0;
  int encode_result;
  /* Checking IEI and pointer */
  CHECK_PDU_POINTER_AND_LENGTH_ENCODER(buffer, MS_NETWORK_FEATURE_SUPPORT_MINIMUM_LENGTH, len);
#if NAS_DEBUG
  dump_ms_network_feature_support_xml(msnetworkfeaturesupport, iei);
#endif

  
  *(buffer + encoded) = 0x00 | ((msnetworkfeaturesupport->spare_bits & 0x7) << 3)  
                             | (msnetworkfeaturesupport->extended_periodic_timers & 0x1);
  encoded++;
  return encoded;
}

void dump_ms_network_feature_support_xml(MsNetworkFeatureSupport *msnetworkfeaturesupport, uint8_t iei)
{
  printf("<Ms Network Feature Support>\n");

  if (iei > 0)
    /* Don't display IEI if = 0 */
    printf("    <IEI>0x%X</IEI>\n", iei);
  
  printf("    <spare_bits>%u<spare_bits>\n",msnetworkfeaturesupport->spare_bits);
  printf("    <extended_periodic_timer>%u<extended_periodic_timer>\n",msnetworkfeaturesupport->extended_periodic_timers);
  printf("</Ms Network Feature Support>\n");
}

