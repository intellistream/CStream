#ifndef _GAIACLI_H_
#define _GAIACLI_H_

#include "opcode.h"
#include "ovm.h"
#include "gaiapack.h"
#include "gaia_autoProcess.h"
#include "unitnode.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "gfile.h"
#include "gaia_config.h"
extern GAIACONFIG g_gaiaConfig;
void gaiaCli_start(void);
void vm32_addOneDev(VM32 *vm32);
#endif