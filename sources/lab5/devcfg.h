/*
 * devcfg.h
 *
 *  Created on: Aug 15, 2012
 *      Author: ckohn
 */

#ifndef DEVCFG_H_
#define DEVCFG_H_


#include "xdevcfg.h"


XDcfg *XDcfg_Initialize(u16 DeviceId);
int XDcfg_TransferBitfile(XDcfg *Instance, u32 StartAddress, u32 WordLength);


#endif /* DEVCFG_H_ */
