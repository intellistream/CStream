#include "gaiacli.h"
#include "o12864.h"
#include "gfile.h"
#include "vm32_devs.h"
int g_helperPort;
extern float g_pitch, g_roll, g_yaw;
int32_t gaia_myIsr_debug(NETSOCKET *netsocket) {
  float backData[3];
  backData[0] = g_pitch;
  backData[1] = g_roll;
  backData[2] = g_yaw;
  GAIAPACK gpack = {
      .packId=GAIAPACK_ID_V1,
      .packType=GAIAPACK_DEBUG,
      .thisLen=sizeof(float) * 3,
      .allLen=sizeof(float) * 3,
      .followingCnt=0,
      .userAttr=0,
      .userAttr2=0,
      .userAttr3=0,
      .blockdata=(uint8_t *) backData,
  };
  gaiasock_send(netsocket, &gpack);
  return 1;
}
extern char g_cliIp[64];
int32_t gaiasock_testConnect(NETSOCKET *netsocket) {
  UNITNODE *unode = g_gaiaConfig.myNode;
  // unitnode_init(unode,2,"ESP32","192.168.1.3","192.168.1.3",2800,g_helperPort,g_helperPort);

  //
  //unitnode_print(unode);
  char str[128];
  sprintf(str, "id:%d-%d", unode->ownerId, unode->subType);
  OLED_ShowString(0, 48, (unsigned char *) str);
  gaiasock_sendUnode(netsocket, unode, 1);
  // printf("connect succeed \r\n");
  return 1;
}
void gaiaCli_start(void) {
  gaiaPlatform_config();
  gaia_initIsrHandles();
  uint16_t port = 8220;
  int8_t *ip = (int8_t *) "10.42.0.1";
  int8_t str[64];
  //create server
  // printf("creat help server \r\n");

  NETSERVER *netserver = (NETSERVER *) malloc(sizeof(NETSERVER));
  netserver_init(netserver, port, (int8_t *) "0.0.0.0");
  netserver->netsocket_userGet = gaiasock_defaultGet;
  netserver_establishV4(netserver);
  OLED_ShowString(0, 48, (unsigned char *) ("gaia START"));

//printf("open helper server at port %d \r\n",netserver->port);

  g_helperPort = netserver->port;
  port = 8216;

  NETSOCKET *cli = (NETSOCKET *) malloc(sizeof(NETSOCKET));
  OLED_ShowString(0, 48, (uint8_t *) "GAIA MALLOC");


  //GAIAPACK gpack;

  //gpack.packId=GAIAPACK_ID_V1;
  gaiaPlatform_setRouteSock(cli);
  gaia_registerIsrByType(GAIAPACK_DEBUG, gaia_myIsr_debug);
//get mynode

  GFILE *gfile = gfile_open((uint8_t *) "ESPCONF", GFILE_R);
  uint8_t *tdata;
  UNITNODE *myNode;
  if (gfile) {
    tdata = gfile_readAll(gfile);

    OLED_ShowString(0, 30, (unsigned char *) "found config");
    myNode = unitnode_fromBin(tdata);
    free(tdata);
    gfile_free(gfile);
    free(myNode->inAddr);
    myNode->inAddr = (uint8_t *) g_cliIp;
    myNode->inAddrSize = vstrLen(myNode->inAddr);
    myNode->inPort = g_helperPort;
  } else {
    myNode = (UNITNODE *) malloc(sizeof(UNITNODE));
    OLED_ShowString(0, 30, (unsigned char *) "not found config");
    unitnode_init(myNode,
                  2,
                  (uint8_t *) "ESP32",
                  (uint8_t *) g_cliIp,
                  (uint8_t *) g_cliIp,
                  240,
                  g_helperPort,
                  g_helperPort);
  }

  /*UNITNODE *myNode=(UNITNODE *)malloc(sizeof(UNITNODE));
       OLED_ShowString(0,30,(unsigned char*)"not found config");
    unitnode_init(myNode,2,(uint8_t *)"ESP32",(uint8_t *)g_cliIp,(uint8_t *)g_cliIp,240,g_helperPort,g_helperPort);*/
  gaiaPlatform_setNode(myNode);
  netsocket_connetctToServerWithNoDefaults(cli,
                                           port,
                                           ip,
                                           gaiasock_testConnect,
                                           gaiasock_defaultGet,
                                           netsocket_userDisConnect_defaultNull);
  gaiasock_testConnect(cli);
  //g_gaiaConfig.routeSock=cli;//must assign the routeSock!!!


}
//must be providede by user
void vm32_addDevs(VM32 *vm32) {
  vm32_addZeroDev(vm32);
  vm32_addOneDev(vm32);
}