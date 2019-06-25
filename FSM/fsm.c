#include "fsm.h"
/*==================================================================
* Function  : FSM_StateTransfer
* Description : ״̬ת��
* Input Para  : 
* Output Para : 
* Return Value: 
==================================================================*/
static void FSM_StateTransfer(FSM_T *pFsm, uint8_t state)
{
    pFsm->curState = state;
}
/*==================================================================
* Function  : FSM_EventHandle
* Description : ״̬��������
* Input Para  : pFsm״̬������, event�����¼�, parm����ִ�в���
* Output Para : 
* Return Value: 
==================================================================*/
void FSM_EventHandle(FSM_T *pFsm, uint8_t event, void *parm)
{
    FsmTable_T *pAcTable = pFsm->FsmTable;
    void (*eventActFun)(void *) = NULL;
    uint8_t NextState;
    uint8_t CurState = pFsm->curState;
    uint8_t flag = 0;
    for (uint8_t i = 0; i < pFsm->stuMaxNum; i++)// ����״̬��
    {
        if (event == pAcTable[i].event && CurState == pAcTable[i].CurState)
        {
            flag = 1;
            eventActFun = pAcTable[i].eventActFun;
            NextState = pAcTable[i].NextState;
            break;
        }
    }
    if (flag)
    {
        if (eventActFun != NULL)
        {
            eventActFun(parm);  			   // ִ����Ӧ����
        }
        FSM_StateTransfer(pFsm, NextState);    // ״̬ת��
    }
    else
    {
        // do nothing
    }
}
 
/*==================================================================
* Function  : FSM_Init
* Description : ״̬����ʼ��
* Input Para  : pFsm״̬������pTable״̬Ǩ�Ʊ�stuMaxNumǨ�Ʊ�����
*               curState��ǰ״̬
* Output Para : 
* Return Value: 
==================================================================*/
void FSM_Init(FSM_T *pFsm, FsmTable_T *pTable, uint8_t stuMaxNum, uint8_t curState)
{
    pFsm->FsmTable = pTable;
    pFsm->curState = curState;
    pFsm->stuMaxNum = stuMaxNum;
}
void event1(void *parm)
{
	printf("hello\n");
}

void event2(void *parm)
{
	printf("world\n");
}

void main(void)
{
	FSM_T  *mFsm;
	FsmTable_T *mTable;
	mTable = (FsmTable_T *)malloc(sizeof(FsmTable_T));
	mTable->eventActFun =  event1;
	FSM_Init(mFsm,mTable,1,55);	
}