#ifndef __RECORDER_H
#define __RECORDER_H
#include "sys.h"
#include "ff.h"
#include "wavplay.h" 
 	
 
#define SAI_RX_DMA_BUF_SIZE    	4096		//定义RX DMA 数组大小
#define SAI_RX_FIFO_SIZE		10			//定义接收FIFO大小

#define REC_SAMPLERATE			44100		//采样率,44.1Khz

u8 rec_sai_fifo_read(u8 **buf);
u8 rec_sai_fifo_write(u8 *buf);

void rec_sai_dma_rx_callback(void);
void recoder_enter_rec_mode(void);
void recoder_wav_init(__WaveHeader* wavhead);
void recoder_msg_show(u32 tsec,u32 kbps);
void recoder_remindmsg_show(u8 mode);
void recoder_new_pathname(u8 *pname); 
void wav_recorder(void);

#endif












