/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_spi.h"

/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : SPI_WriteByte
**功能 : Transmit 1Byte Data
**輸入 : SPIx, WriteByte
**輸出 : None
**使用 : SPI_WriteByte(SPI1, 0xFF);
**=====================================================================================================*/
/*=====================================================================================================*/
void SPI_WriteByte( SPI_TypeDef* SPIx, u8 WriteByte )
{
  while((SPIx->SR & SPI_I2S_FLAG_TXE) == (u16)RESET);
  SPIx->DR = WriteByte;
  while((SPIx->SR & SPI_I2S_FLAG_RXNE) == (u16)RESET);
  SPIx->DR;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : SPI_ReadByte
**功能 : Receive 1Byte Data
**輸入 : SPIx
**輸出 : None
**使用 : Read = SPI_ReadByte(SPI1);
**=====================================================================================================*/
/*=====================================================================================================*/
u8 SPI_ReadByte( SPI_TypeDef* SPIx )
{
  while((SPIx->SR & SPI_I2S_FLAG_TXE) == (u16)RESET);
  SPIx->DR = 0xFF;
  while((SPIx->SR & SPI_I2S_FLAG_RXNE) == (u16)RESET);

  return SPIx->DR;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
