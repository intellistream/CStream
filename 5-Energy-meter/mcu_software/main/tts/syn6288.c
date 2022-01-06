#include "syn6288.h"

/**************оƬ��������*********************/
uint8_t SYN_StopCom[] = {0xFD, 0X00, 0X02, 0X02, 0XFD};//ֹͣ�ϳ�
uint8_t SYN_SuspendCom[] = {0XFD, 0X00, 0X02, 0X03, 0XFC};//��ͣ�ϳ�
uint8_t SYN_RecoverCom[] = {0XFD, 0X00, 0X02, 0X04, 0XFB};//�ָ��ϳ�
uint8_t SYN_ChackCom[] = {0XFD, 0X00, 0X02, 0X21, 0XDE};//״̬��ѯ
uint8_t SYN_PowerDownCom[] = {0XFD, 0X00, 0X02, 0X88, 0X77};//����POWER DOWN ״̬����

/***********************************************/

void synFrameInfo(uint8_t Music, uint8_t *HZdata) {
  uint8_t Frame_Info[5];
  unsigned char HZ_Length;
  unsigned char ecc = 0;                //����У���ֽ�
  unsigned int i = 0;
  HZ_Length = strlen((const char *) HZdata);            //��Ҫ�����ı��ĳ���
  /*****************֡�̶�������Ϣ**************************************/
  Frame_Info[0] = 0xFD;            //����֡ͷFD
  Frame_Info[1] = 0x00;            //�������������ȵĸ��ֽ�
  Frame_Info[2] = HZ_Length + 3;        //�������������ȵĵ��ֽ�
  Frame_Info[3] = 0x01;            //���������֣��ϳɲ�������
  Frame_Info[4] = 0x01 | Music << 4;    //����������������������趨

  /*******************У�������***************************************/
  for (i = 0; i < 5; i++)                    //���η��͹���õ�5��֡ͷ�ֽ�
  {
    ecc = ecc ^ (Frame_Info[i]);        //�Է��͵��ֽڽ������У��
  }

  for (i = 0; i < HZ_Length; i++)        //���η��ʹ��ϳɵ��ı�����
  {
    ecc = ecc ^ (HZdata[i]);                //�Է��͵��ֽڽ������У��
  }
  /*******************����֡��Ϣ***************************************/


  // memcpy(&Frame_Info[5], HZdata, HZ_Length);

  myUartSend(Frame_Info, 5);
  myUartSend(HZdata, HZ_Length);
  myUartSend(&ecc, 1);

}
void synCmd(uint8_t *cmd) {
  uint8_t Com_Len;
  Com_Len = strlen((const char *) cmd);
  // myUartSend(&ecc,1);
  myUartSend(cmd, Com_Len);

}

